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

DECOMP_SIZE_ASSERT(CutsceneColorEvent, 0x48)

// FUNCTION: LEGORACERS 0x004a4b60
CutsceneColorEvent::CutsceneColorEvent()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a4bb0
void CutsceneColorEvent::Reset()
{
	m_entity = NULL;
	m_active = FALSE;
	m_shiftRed = 0;
	m_shiftGrn = 0;
	m_shiftBlu = 0;
	m_offsetStartRed = 0;
	m_offsetStartGrn = 0;
	m_offsetStartBlu = 0;
	m_offsetRed = 0.0f;
	m_offsetGrn = 0.0f;
	m_offsetBlu = 0.0f;
	m_offsetRateRed = 0.0f;
	m_offsetRateGrn = 0.0f;
	m_offsetRateBlu = 0.0f;
}

// FUNCTION: LEGORACERS 0x004a4be0
void CutsceneColorEvent::Parse(GolFileParser* p_parser, CutscenePlayer* p_owner)
{
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token;
	while ((token = p_parser->GetNextToken()) != GolFileParser::e_rightCurly) {
		switch (token) {
		case e_shifts:
			m_shiftRed = p_parser->ReadInteger();
			m_shiftGrn = p_parser->ReadInteger();
			m_shiftBlu = p_parser->ReadInteger();
			break;
		case e_offsets:
			m_offsetStartRed = p_parser->ReadInteger();
			m_offsetStartGrn = p_parser->ReadInteger();
			m_offsetStartBlu = p_parser->ReadInteger();
			break;
		case e_offsetRates:
			m_offsetRateRed = p_parser->ReadFloat();
			m_offsetRateGrn = p_parser->ReadFloat();
			m_offsetRateBlu = p_parser->ReadFloat();
			break;
		default:
			ParseCommonToken(p_parser, p_owner, token);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x004a4ca0
void CutsceneColorEvent::Start()
{
	if (!m_active && m_entity != NULL) {
		m_active = TRUE;
		m_offsetRed = static_cast<LegoFloat>(m_offsetStartRed);
		m_offsetGrn = static_cast<LegoFloat>(m_offsetStartGrn);
		m_offsetBlu = static_cast<LegoFloat>(m_offsetStartBlu);
		ApplyColorTransform();
	}
}

// FUNCTION: LEGORACERS 0x004a4cd0
void CutsceneColorEvent::StartOnModel(GolWorldEntity* p_arg)
{
	if (!m_active) {
		if (m_entity == NULL) {
			m_entity = p_arg;
		}

		Start();
	}
}

// FUNCTION: LEGORACERS 0x004a4cf0
void CutsceneColorEvent::Stop()
{
	if (m_active) {
		m_active = FALSE;
		if (m_entity != NULL) {
			m_entity->ClearColorTransform();
		}
	}
}

// FUNCTION: LEGORACERS 0x004a4d10
void CutsceneColorEvent::Update(LegoFloat p_elapsedSeconds)
{
	if (m_active) {
		if (m_entity != 0) {
			LegoFloat deltaX = m_offsetRateRed * p_elapsedSeconds;
			LegoFloat deltaY = m_offsetRateGrn * p_elapsedSeconds;
			LegoFloat deltaZ = m_offsetRateBlu * p_elapsedSeconds;

			if (static_cast<LegoS32>(deltaX) || static_cast<LegoS32>(deltaY) || static_cast<LegoS32>(deltaZ)) {
				m_offsetRed += deltaX;
				m_offsetGrn += deltaY;
				m_offsetBlu += deltaZ;
				ApplyColorTransform();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a4da0
void CutsceneColorEvent::ApplyColorTransform()
{
	ColorTransform transform;
	transform.m_redShift = m_shiftRed;
	transform.m_grnShift = m_shiftGrn;
	transform.m_bluShift = m_shiftBlu;
	transform.m_alpShift = 0;
	transform.m_redOffset = static_cast<LegoS32>(m_offsetRed);
	transform.m_grnOffset = static_cast<LegoS32>(m_offsetGrn);
	transform.m_bluOffset = static_cast<LegoS32>(m_offsetBlu);
	transform.m_alpOffset = 0;

	m_entity->ApplyColorTransform(&transform);
}
