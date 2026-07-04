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

DECOMP_SIZE_ASSERT(CutsceneImageVisual, 0x64)

// FUNCTION: LEGORACERS 0x004a37e0
CutsceneImageVisual::CutsceneImageVisual()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a3830
CutsceneImageVisual::~CutsceneImageVisual()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x004a3880
void CutsceneImageVisual::Reset()
{
	m_image = NULL;
	m_imageName[0] = '\0';
	CutsceneVisual::Reset();
}

// FUNCTION: LEGORACERS 0x004a3890
void CutsceneImageVisual::Parse(GolFileParser* p_parser, CutscenePlayer* p_owner, GolRenderDevice* p_renderer)
{
	p_parser->ReadLeftCurly();
	m_flags = 3;

	GolFileParser::ParserTokenType token;
	while ((token = p_parser->GetNextToken()) != GolFileParser::e_rightCurly) {
		if (token != CutscenePlayer::CebTxtParser::e_imageVisuals) {
			ParseVisualToken(p_parser, token, p_owner, p_renderer);
		}
		else {
			::strncpy(m_imageName, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		}
	}

	if (m_imageName[0] == '\0') {
		p_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
	}
}

// FUNCTION: LEGORACERS 0x004a3910
void CutsceneImageVisual::ResolveImage(GolD3DRenderDevice* p_renderer)
{
	m_image = p_renderer->FindImageByName(m_imageName);
	if (m_image == NULL) {
		LegoChar text[64];
		::strncpy(text, m_imageName, sizeof(GolName));
		text[sizeof(GolName)] = '\0';
		::strcat(text, ": Unable to find image");
		GOL_FATALERROR_MESSAGE(text);
	}
}

// FUNCTION: LEGORACERS 0x004a3990
void CutsceneImageVisual::Clear()
{
	Reset();
	CutsceneEvent::Reset();
}

// FUNCTION: LEGORACERS 0x004a39b0
void CutsceneImageVisual::GetContentSize(LegoS32* p_width, LegoS32* p_height)
{
	*p_width = m_image->GetWidth();
	*p_height = m_image->GetHeight();
}

// FUNCTION: LEGORACERS 0x004a39d0
void CutsceneImageVisual::DrawContent(
	GolRenderDevice* p_renderer,
	LegoS32 p_x,
	LegoS32 p_y,
	undefined4 p_width,
	undefined4 p_height,
	LegoFloat,
	LegoFloat
)
{
	Rect destRect;
	destRect.m_left = p_x;
	destRect.m_right = p_x + p_width;
	destRect.m_top = p_y;
	destRect.m_bottom = p_y + p_height;

	if (m_flags & 0x100) {
		m_image->m_tintColor.m_u32 = m_colorPacked;
	}

	p_renderer->DrawImageRect(m_image, 0, &destRect, NULL);

	if (m_flags & 0x100) {
		union {
			ColorRGBA m_color;
			LegoU32 m_colorPacked;
		} color;

		color.m_color.m_red = 0xff;
		color.m_color.m_grn = 0xff;
		color.m_color.m_blu = 0xff;
		color.m_color.m_alp = 0xff;
		m_image->m_tintColor.m_u32 = color.m_colorPacked;
	}
}
