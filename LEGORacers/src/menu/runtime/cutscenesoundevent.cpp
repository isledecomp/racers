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

DECOMP_SIZE_ASSERT(CutsceneSoundEvent, 0x30)

// GLOBAL: LEGORACERS 0x004b4ab0
const LegoFloat g_cutsceneSoundDefaultVolume = 1.0f;

// GLOBAL: LEGORACERS 0x004b4ab4
const LegoFloat g_cutsceneSoundDefaultPan = 0.0f;

// GLOBAL: LEGORACERS 0x004b4ab8
const LegoFloat g_cutsceneSoundDefaultFrequencyScale = 1.0f;

// FUNCTION: LEGORACERS 0x004a3e70
CutsceneSoundEvent::CutsceneSoundEvent()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a3ec0
void CutsceneSoundEvent::Reset()
{
	m_soundGroup = NULL;
	m_instance = NULL;
	m_volume = g_cutsceneSoundDefaultVolume;
	m_priority = 0;
	m_frequencyScale = g_cutsceneSoundDefaultFrequencyScale;
	m_pan = g_cutsceneSoundDefaultPan;
	m_looping = 0;
	m_soundIndex = 0;
}

// FUNCTION: LEGORACERS 0x004a3ef0
void CutsceneSoundEvent::Parse(GolFileParser* p_parser, CutscenePlayer* p_owner)
{
	if (m_soundGroup != NULL) {
		Clear();
	}

	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		if (!ParseToken(p_parser, p_owner, token)) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
		}

		token = p_parser->GetNextToken();
	}

	if (m_soundGroup == NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
	}
}

// FUNCTION: LEGORACERS 0x004a3f60
LegoBool32 CutsceneSoundEvent::ParseToken(
	GolFileParser* p_parser,
	CutscenePlayer* p_owner,
	GolFileParser::ParserTokenType p_token
)
{
	switch (p_token) {
	case e_soundIndex: {
		LegoU32 index = p_parser->ReadInteger();
		if (index >= p_owner->GetSoundGroupCount()) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_invalidValue);
		}

		m_soundGroup = p_owner->GetSoundGroupByIndex(index);
		m_soundIndex = static_cast<LegoU16>(p_parser->ReadInteger());
		return TRUE;
	}
	case e_priority:
		m_priority = p_parser->ReadInteger();
		return TRUE;
	case e_volume:
		m_volume = p_parser->ReadFloat();
		return TRUE;
	case e_frequencyScale:
		m_frequencyScale = p_parser->ReadFloat();
		return TRUE;
	case e_pan:
		m_pan = p_parser->ReadFloat();
		return TRUE;
	case e_looping:
		m_looping = 1;
		return TRUE;
	default:
		return FALSE;
	}
}

// FUNCTION: LEGORACERS 0x004a4050
void CutsceneSoundEvent::Clear()
{
	Reset();
	CutsceneEvent::Reset();
}

// FUNCTION: LEGORACERS 0x004a4070
void CutsceneSoundEvent::Start()
{
	if (m_instance == NULL) {
		m_instance = m_soundGroup->CreateSoundInstance(m_soundIndex);
		m_instance->Play(m_looping);
		m_instance->SetVolume(m_volume);
		m_instance->SetPan(m_pan);
		m_instance->SetFrequencyScale(m_frequencyScale);
		m_instance->SetPriority(m_priority);
	}
}

// FUNCTION: LEGORACERS 0x004a40d0
void CutsceneSoundEvent::Stop()
{
	if (m_instance != NULL) {
		m_soundGroup->DestroySoundInstance(m_instance);
		m_instance = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004a40f0
void CutsceneSoundEvent::Update()
{
	if (m_instance != NULL) {
		if (!m_instance->IsPlaying()) {
			Stop();
		}
	}
}
