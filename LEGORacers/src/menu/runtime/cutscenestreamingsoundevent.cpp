#include "audio/soundgroup.h"
#include "audio/soundinstance.h"
#include "audio/soundmanager.h"
#include "audio/spatialsoundinstance.h"
#include "audio/streamingsoundinstance.h"
#include "camera/golcamera.h"
#include "core/gol.h"
#include "font/golfont.h"
#include "font/golfonttable.h"
#include "golanimatedentity.h"
#include "golbinparser.h"
#include "golconstants.h"
#include "golerror.h"
#include "golfileparser.h"
#include "golmodelbase.h"
#include "golname.h"
#include "golscenenode.h"
#include "golstream.h"
#include "goltxtparser.h"
#include "golworldentity.h"
#include "image/golimage.h"
#include "mabmaterialanimation.h"
#include "mabmaterialtrack.h"
#include "material/golimagedefinitionlist.h"
#include "menu/menuanimationlist.h"
#include "menu/runtime/cutscenedefinition.h"
#include "menu/runtime/cutsceneparticle.h"
#include "menu/runtime/cutsceneplayer.h"
#include "render/gold3drenderdevice.h"
#include "render/golrenderdevice.h"
#include "render/rectangle.h"

#include <string.h>

DECOMP_SIZE_ASSERT(CutsceneStreamingSoundEvent, 0x50)

// FUNCTION: LEGORACERS 0x004a4110
CutsceneStreamingSoundEvent::CutsceneStreamingSoundEvent()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a4160
void CutsceneStreamingSoundEvent::Reset()
{
	m_streamInstance = NULL;
	m_minDistance = 100.0f;
	m_maxDistance = 500.0f;
	m_position.m_x = 0.0f;
	m_position.m_y = 0.0f;
	m_position.m_z = 0.0f;
	m_flags = 0;
	m_jointIndex = 0;
	CutsceneSoundEvent::Reset();
	CutsceneEvent::Reset();
}

// FUNCTION: LEGORACERS 0x004a41a0
void CutsceneStreamingSoundEvent::Parse(GolFileParser* p_parser, CutscenePlayer* p_owner)
{
	if (m_soundGroup != NULL) {
		Clear();
	}

	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case e_minDistance:
			m_minDistance = p_parser->ReadFloat();
			break;
		case e_maxDistance:
			m_maxDistance = p_parser->ReadFloat();
			break;
		case e_position:
			m_position.m_x = p_parser->ReadFloat();
			m_position.m_y = p_parser->ReadFloat();
			m_position.m_z = p_parser->ReadFloat();
			m_flags |= 1;
			break;
		case e_positional:
			m_flags = (m_flags & ~4) | 2;
			break;
		case e_joint:
			m_jointIndex = p_parser->ReadInteger();
			m_flags = (m_flags & ~2) | 4;
			break;
		default:
			if (!ParseToken(p_parser, p_owner, token)) {
				ParseCommonToken(p_parser, p_owner, token);
			}
			break;
		}

		token = p_parser->GetNextToken();
	}

	if (m_soundGroup == NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
	}
}

// FUNCTION: LEGORACERS 0x004a42a0
void CutsceneStreamingSoundEvent::Clear()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a42b0
void CutsceneStreamingSoundEvent::Start()
{
	if (m_streamInstance == NULL) {
		GolVec3 velocity;
		GolVec3 position;
		velocity.m_x = 0.0f;
		velocity.m_y = 0.0f;
		velocity.m_z = 0.0f;

		if ((m_flags & c_flagTrackJoint) && m_animatedEntity != NULL) {
			GetJointPosition(m_jointIndex, &position);
			m_animatedEntity->GetVelocity(&velocity);
		}
		else if (m_flags & c_flagHasPosition) {
			position = m_position;
		}
		else if (m_parsedEntity != NULL) {
			m_parsedEntity->GetPosition(&position);
			m_parsedEntity->GetVelocity(&velocity);
		}
		else {
			position.m_x = 0.0f;
			position.m_y = 0.0f;
			position.m_z = 0.0f;
		}

		CreateInstance(&position);
		m_streamInstance->SetVelocity(velocity);
	}
}

// STUB: LEGORACERS 0x004a43a0
void CutsceneStreamingSoundEvent::CreateInstance(const GolVec3* p_position)
{
	if (m_streamInstance == NULL) {
		m_streamInstance = m_soundGroup->CreateStreamingSoundInstance(m_soundIndex);
		m_streamInstance->Play(m_looping);
		m_streamInstance->SetVolume(m_volume);
		m_streamInstance->SetFrequencyScale(m_frequencyScale);
		LegoFloat maxDistance = m_maxDistance;
		LegoFloat minDistance = m_minDistance;
		m_streamInstance->SetDistanceRange(minDistance, maxDistance);

		m_flags &= ~c_flagWasPlaying;
		if (m_flags & c_flagHasPosition) {
			m_streamInstance->SetPosition(&m_position);
			return;
		}

		m_streamInstance->SetPosition(p_position);
	}
}

// FUNCTION: LEGORACERS 0x004a4450
void CutsceneStreamingSoundEvent::StartAt(const GolVec3* p_a, const GolVec3*, const GolVec3*)
{
	if (m_streamInstance == NULL) {
		if (m_parsedEntity == NULL && !(m_flags & 1)) {
			CreateInstance(p_a);
		}
		else {
			Start();
		}
	}
}

// FUNCTION: LEGORACERS 0x004a4480
void CutsceneStreamingSoundEvent::StartOnBsp(GolWorldEntity* p_arg)
{
	if (m_streamInstance == NULL) {
		if (m_parsedEntity == NULL) {
			m_parsedEntity = p_arg;
		}

		Start();
	}
}

// FUNCTION: LEGORACERS 0x004a44a0
void CutsceneStreamingSoundEvent::StartOnJointed(GolWorldEntity* p_arg)
{
	if (m_streamInstance == NULL) {
		if (m_animatedEntity == NULL) {
			m_animatedEntity = static_cast<GolAnimatedEntity*>(p_arg);
			m_parsedEntity = p_arg;
		}

		Start();
	}
}

// FUNCTION: LEGORACERS 0x004a44c0
void CutsceneStreamingSoundEvent::Stop()
{
	if (m_streamInstance) {
		m_flags &= ~c_flagWasPlaying;
		m_soundGroup->DestroyStreamingSoundInstance(m_streamInstance);
		m_streamInstance = NULL;
	}
}

// STUB: LEGORACERS 0x004a44f0
void CutsceneStreamingSoundEvent::Update()
{
	if (m_streamInstance) {
		if (!m_streamInstance->IsPlaying()) {
			if (m_flags & c_flagWasPlaying) {
				Stop();
				return;
			}
		}
		else {
			m_flags |= c_flagWasPlaying;
		}

		GolVec3 position;
		GolVec3 velocity;
		GolWorldEntity* entity;

		if (m_flags & c_flagTrackJoint) {
			GetJointPosition(m_jointIndex, &position);
			m_streamInstance->SetPosition(&position);
			entity = m_animatedEntity;
		}
		else if (m_flags & c_flagTrackEntity) {
			m_parsedEntity->GetPosition(&position);
			m_streamInstance->SetPosition(&position);
			entity = m_parsedEntity;
		}
		else {
			return;
		}

		entity->GetVelocity(&velocity);
		m_streamInstance->SetVelocity(velocity);
	}
}
