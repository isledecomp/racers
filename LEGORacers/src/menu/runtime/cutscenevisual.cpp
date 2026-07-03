#include "camera/golcamera.h"
#include "menu/runtime/cutsceneplayer.h"
#include "render/gold3drenderdevice.h"
#include "render/rectangle.h"
#include "surface/golrendertarget.h"

// FUNCTION: LEGORACERS 0x004a3280
CutsceneVisual::CutsceneVisual()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a32f0
CutsceneVisual::~CutsceneVisual()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x004a3340
void CutsceneVisual::Reset()
{
	m_color.m_alp = 0xff;
	m_startX = 0.0f;
	m_startY = 0.0f;
	m_x = 0;
	m_y = 0;
	m_startWidth = 0.0f;
	m_startHeight = 0.0f;
	m_width = 0;
	m_height = 0;
	m_rateX = 0.0f;
	m_rateY = 0.0f;
	m_rateWidth = 0.0f;
	m_rateHeight = 0.0f;
	m_color.m_red = 0;
	m_color.m_grn = 0;
	m_color.m_blu = 0;
	m_flags = 0;
}

// FUNCTION: LEGORACERS 0x004a3380
void CutsceneVisual::ParseVisualToken(
	GolFileParser* p_parser,
	GolFileParser::ParserTokenType p_token,
	CutscenePlayer*,
	GolRenderDevice*
)
{
	switch (p_token) {
	case CutscenePlayer::CebTxtParser::e_startX:
		m_startX = p_parser->ReadFloat();
		m_flags = (m_flags & ~1) | 4;
		break;
	case CutscenePlayer::CebTxtParser::e_startY:
		m_startY = p_parser->ReadFloat();
		m_flags = (m_flags & ~2) | 8;
		break;
	case CutscenePlayer::CebTxtParser::e_centerX:
		m_flags = (m_flags & ~4) | 1;
		break;
	case CutscenePlayer::CebTxtParser::e_centerY:
		m_flags = (m_flags & ~8) | 2;
		break;
	case CutscenePlayer::CebTxtParser::e_startWidth:
		m_startWidth = p_parser->ReadFloat();
		m_flags |= 0x10;
		break;
	case CutscenePlayer::CebTxtParser::e_startHeight:
		m_startHeight = p_parser->ReadFloat();
		m_flags |= 0x20;
		break;
	case CutscenePlayer::CebTxtParser::e_rateX:
		m_rateX = p_parser->ReadFloat();
		break;
	case CutscenePlayer::CebTxtParser::e_rateY:
		m_rateY = p_parser->ReadFloat();
		break;
	case CutscenePlayer::CebTxtParser::e_rateWidth:
		m_rateWidth = p_parser->ReadFloat();
		break;
	case CutscenePlayer::CebTxtParser::e_rateHeight:
		m_rateHeight = p_parser->ReadFloat();
		break;
	case CutscenePlayer::CebTxtParser::e_visualColor:
		m_color.m_red = p_parser->ReadInteger();
		m_color.m_grn = p_parser->ReadInteger();
		m_color.m_blu = p_parser->ReadInteger();
		m_flags |= 0x100;
		break;
	default:
		p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
	}
}

// FUNCTION: LEGORACERS 0x004a3500
void CutsceneVisual::Clear()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a3510
void CutsceneVisual::Start()
{
	if (!(m_flags & 0x40) && m_disabled == 0) {
		LegoU32 flags = m_flags | 0xc0;

		m_x = m_startX;
		m_y = m_startY;
		m_width = m_startWidth;
		m_height = m_startHeight;
		m_flags = flags;
	}
}

// FUNCTION: LEGORACERS 0x004a3540
void CutsceneVisual::Stop()
{
	m_flags &= ~0x40;
}

// FUNCTION: LEGORACERS 0x004a3550
void CutsceneVisual::Update(LegoFloat p_elapsedSeconds)
{
	if ((m_flags & 0x40) && !(m_flags & 0x80)) {
		m_x += m_rateX * p_elapsedSeconds;
		m_y += m_rateY * p_elapsedSeconds;
		m_width += m_rateWidth * p_elapsedSeconds;
		m_height += m_rateHeight * p_elapsedSeconds;
	}
}

// FUNCTION: LEGORACERS 0x004a35a0
void CutsceneVisual::Draw(GolD3DRenderDevice* p_renderer)
{
	if (m_flags & 0x40) {
		LegoS32 sourceWidth;
		LegoS32 sourceHeight;
		LegoS32 renderTargetWidth = p_renderer->GetRenderTargetInfo()->GetWidth();
		LegoFloat width = static_cast<LegoFloat>(renderTargetWidth);
		LegoS32 renderTargetHeight = p_renderer->GetRenderTargetInfo()->GetHeight();
		LegoFloat height = static_cast<LegoFloat>(renderTargetHeight);

		if (m_flags & c_flagLayoutPending) {
			ComputeLayout(p_renderer, width, height);
		}

		if (m_x >= 0.0f && m_y >= 0.0f) {
			LegoFloat scaledX = m_x;
			scaledX *= width;
			LegoS32 x = static_cast<LegoS32>(scaledX);

			LegoFloat scaledY = m_y;
			scaledY *= height;
			LegoS32 y = static_cast<LegoS32>(scaledY);

			LegoFloat scaledWidth = m_width;
			scaledWidth *= width;
			LegoS32 drawWidth = static_cast<LegoS32>(scaledWidth);

			LegoFloat scaledHeight = m_height;
			scaledHeight *= height;
			LegoS32 drawHeight = static_cast<LegoS32>(scaledHeight);

			if (drawWidth) {
				if (drawHeight && drawWidth + x <= static_cast<LegoU32>(renderTargetWidth) &&
					y + drawHeight <= static_cast<LegoU32>(renderTargetHeight)) {
					GetContentSize(&sourceWidth, &sourceHeight);

					LegoFloat scaleY = static_cast<LegoFloat>(drawHeight) / static_cast<LegoFloat>(sourceHeight);
					LegoFloat scaleX = static_cast<LegoFloat>(drawWidth) / static_cast<LegoFloat>(sourceWidth);
					DrawContent(p_renderer, x, y, drawWidth, drawHeight, scaleX, scaleY);
				}
			}
		}
	}
}

// STUB: LEGORACERS 0x004a36e0
void CutsceneVisual::ComputeLayout(GolD3DRenderDevice* p_renderer, LegoFloat p_width, LegoFloat p_height)
{
	const Rect* viewport = &p_renderer->GetCurrentCamera()->m_viewport;
	LegoS32 viewportX = viewport->m_left;
	LegoS32 viewportY = viewport->m_top;
	LegoS32 viewportWidth = viewport->m_right - viewportX;
	LegoS32 viewportHeight = viewport->m_bottom - viewportY;

	LegoS32 imageWidth;
	LegoS32 imageHeight;
	GetContentSize(&imageWidth, &imageHeight);

	LegoU32 flags = m_flags;
	LegoBool32 hasHeight;
	LegoBool32 hasWidth = flags & c_flagWidth;
	if (hasWidth) {
		LegoFloat width = m_width;
		imageWidth = static_cast<LegoS32>(width * p_width);
	}

	hasHeight = flags & c_flagHeight;
	if (hasHeight) {
		LegoFloat height = m_height;
		imageHeight = static_cast<LegoS32>(height * p_height);
	}

	viewportY += (viewportHeight - imageHeight) / 2;
	if (!(flags & c_flagPositionX)) {
		viewportX += (viewportWidth - imageWidth) / 2;
		m_x = static_cast<LegoFloat>(viewportX) / p_width;
	}

	if (!(flags & c_flagPositionY)) {
		m_y = static_cast<LegoFloat>(viewportY) / p_height;
	}

	if (!hasWidth) {
		m_width = static_cast<LegoFloat>(imageWidth) / p_width;
	}

	if (!hasHeight) {
		m_height = static_cast<LegoFloat>(imageHeight) / p_height;
	}

	m_flags = flags & ~c_flagLayoutPending;
}
