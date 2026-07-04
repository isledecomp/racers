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

DECOMP_SIZE_ASSERT(CutsceneAnimationEvent, 0x50)

// FUNCTION: LEGORACERS 0x004a3a50
CutsceneAnimationEvent::CutsceneAnimationEvent()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a3aa0
void CutsceneAnimationEvent::Reset()
{
	m_animation = NULL;
	m_particleRef = NULL;
	m_emitterName[0] = '\0';
	m_position.m_x = 0.0f;
	m_position.m_y = 0.0f;
	m_position.m_z = 0.0f;
	m_direction.m_x = 0.0f;
	m_direction.m_y = 0.0f;
	m_direction.m_z = 0.0f;
	m_up.m_x = 0.0f;
	m_up.m_y = 0.0f;
	m_up.m_z = 0.0f;
	m_flags = 0;
}

// FUNCTION: LEGORACERS 0x004a3ad0
void CutsceneAnimationEvent::Parse(GolFileParser* p_parser, CutscenePlayer* p_owner)
{
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token;
	while ((token = p_parser->GetNextToken()) != GolFileParser::e_rightCurly) {
		switch (token) {
		case e_animationIndex: {
			LegoU32 index = p_parser->ReadInteger();
			if (index >= p_owner->GetAnimationCount()) {
				p_parser->HandleUnexpectedToken(GolFileParser::e_invalidValue);
			}

			m_animation = p_owner->GetAnimationByIndex(index);
			::strncpy(m_emitterName, p_parser->ReadString(), sizeof(GolName));
			break;
		}
		case e_position:
			m_position.m_x = p_parser->ReadFloat();
			m_position.m_y = p_parser->ReadFloat();
			m_position.m_z = p_parser->ReadFloat();
			m_flags |= 1;
			break;
		case e_direction:
			m_direction.m_x = p_parser->ReadFloat();
			m_direction.m_y = p_parser->ReadFloat();
			m_direction.m_z = p_parser->ReadFloat();
			m_up.m_x = p_parser->ReadFloat();
			m_up.m_y = p_parser->ReadFloat();
			m_up.m_z = p_parser->ReadFloat();
			m_flags |= 2;
			break;
		case e_attached:
			m_flags |= 4;
			break;
		case e_joint:
			m_jointIndex = p_parser->ReadInteger();
			m_flags |= 8;
			break;
		default:
			ParseCommonToken(p_parser, p_owner, token);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x004a3c20
void CutsceneAnimationEvent::Start()
{
	if (m_particleRef == NULL) {
		GolVec3 v1, v2, v3;
		v1.m_x = 0.0f;
		v1.m_y = 0.0f;
		v1.m_z = 0.0f;
		v2.m_x = 1.0f;
		v2.m_y = 0.0f;
		v2.m_z = 0.0f;
		v3.m_x = 0.0f;
		v3.m_y = 0.0f;
		v3.m_z = 1.0f;

		StartAt(&v1, &v2, &v3);
	}
}

// FUNCTION: LEGORACERS 0x004a3c90
void CutsceneAnimationEvent::StartAt(const GolVec3* p_a, const GolVec3* p_b, const GolVec3* p_c)
{
	if (m_particleRef == NULL) {
		if ((m_flags & 8) && m_animatedEntity) {
			GetJointPosition(m_jointIndex, &m_position);
			GetJointAxes(m_jointIndex, &m_direction, &m_up);
			Spawn();
			return;
		}

		if (!(m_flags & 1)) {
			if (m_parsedEntity != NULL) {
				m_parsedEntity->GetPosition(&m_position);
			}
			else {
				m_position = *p_a;
			}
		}

		if (!(m_flags & 2)) {
			if (m_parsedEntity != NULL) {
				m_parsedEntity->GetAxes(&m_direction, &m_up);
			}
			else {
				m_direction = *p_b;
				m_up = *p_c;
			}
		}

		Spawn();
	}
}

// FUNCTION: LEGORACERS 0x004a3d70
void CutsceneAnimationEvent::StartOnBsp(GolWorldEntity* p_arg)
{
	if (m_particleRef == NULL) {
		if (m_parsedEntity == NULL) {
			m_parsedEntity = p_arg;
		}

		Start();
	}
}

// FUNCTION: LEGORACERS 0x004a3d90
void CutsceneAnimationEvent::StartOnJointed(GolWorldEntity* p_arg)
{
	if (m_particleRef == NULL) {
		if (m_animatedEntity == NULL) {
			m_animatedEntity = static_cast<GolAnimatedEntity*>(p_arg);
		}

		Start();
	}
}

// FUNCTION: LEGORACERS 0x004a3db0
void CutsceneAnimationEvent::Spawn()
{
	m_particleRef = m_animation->SpawnParticle(m_emitterName, &m_position, &m_direction, &m_up);
}

// FUNCTION: LEGORACERS 0x004a3dd0
void CutsceneAnimationEvent::Stop()
{
	if (m_particleRef) {
		m_animation->ReleaseRef(m_particleRef);
		m_particleRef = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004a3df0
void CutsceneAnimationEvent::Update(LegoU32)
{
	GolVec3 v0, v1, v2;

	if (m_particleRef && (m_flags & 8) && m_animatedEntity) {
		CutsceneEvent::GetJointPosition(m_jointIndex, &v0);
		GetJointAxes(m_jointIndex, &v1, &v2);
		if (m_particleRef->m_particle) {
			m_particleRef->m_particle->SetPosition(&v0);
		}
		if (m_particleRef->m_particle) {
			m_particleRef->m_particle->SetOrientation(&v1, &v2);
		}
	}
}
