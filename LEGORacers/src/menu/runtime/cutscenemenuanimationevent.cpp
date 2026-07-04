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

DECOMP_SIZE_ASSERT(CutsceneMenuAnimationEvent, 0x2c)

// FUNCTION: LEGORACERS 0x004a4970
CutsceneMenuAnimationEvent::CutsceneMenuAnimationEvent()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a49c0
void CutsceneMenuAnimationEvent::Reset()
{
	m_animationList = NULL;
	m_material = NULL;
	m_activeEntry = NULL;
	m_durationMs = 0;
	m_mode = 0;
	m_color.m_red = 0;
	m_color.m_grn = 0;
	m_color.m_blu = 0;
	m_color.m_alp = 0;
}

// FUNCTION: LEGORACERS 0x004a49e0
void CutsceneMenuAnimationEvent::Parse(
	GolFileParser* p_parser,
	CutscenePlayer* p_owner,
	MenuAnimationList* p_animationList,
	GolD3DRenderDevice* p_renderer
)
{
	GolName materialName;

	materialName[0] = '\0';
	m_animationList = p_animationList;
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token;
	while ((token = p_parser->GetNextToken()) != GolFileParser::e_rightCurly) {
		switch (token) {
		case e_durationMs:
			m_durationMs = p_parser->ReadInteger();
			break;
		case e_mode: {
			GolFileParser::ParserTokenType mode = p_parser->GetNextToken();
			switch (mode) {
			case e_modeOn:
				m_mode |= 1;
				break;
			case e_modeOff:
				m_mode |= 2;
				break;
			default:
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
			break;
		}
		case e_material:
			::strncpy(materialName, p_parser->ReadString(), sizeof(GolName));
			break;
		case e_color:
			m_color.m_red = static_cast<LegoU8>(p_parser->ReadInteger());
			m_color.m_grn = static_cast<LegoU8>(p_parser->ReadInteger());
			m_color.m_blu = static_cast<LegoU8>(p_parser->ReadInteger());
			break;
		default:
			ParseCommonToken(p_parser, p_owner, token);
			break;
		}
	}

	if (materialName[0] != '\0') {
		m_material = p_renderer->FindMaterialByName(materialName);
	}
}

// FUNCTION: LEGORACERS 0x004a4af0
void CutsceneMenuAnimationEvent::Start()
{
	if (m_mode & 1) {
		m_activeEntry = m_animationList->Activate(m_durationMs, TRUE, m_material, NULL);
	}
	else if (m_mode & 2) {
		m_activeEntry = m_animationList->Activate(m_durationMs, FALSE, m_material, NULL);
	}

	if (m_activeEntry != NULL) {
		m_activeEntry->SetColor(m_colorPacked);
	}
}

// FUNCTION: LEGORACERS 0x004a4b40
void CutsceneMenuAnimationEvent::Stop()
{
	if (m_activeEntry != NULL) {
		m_animationList->Deactivate(m_activeEntry);
		m_activeEntry = NULL;
	}
}
