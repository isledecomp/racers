#include "camera/golcamera.h"
#include "menu/runtime/cutsceneplayer.h"
#include "render/gold3drenderdevice.h"
#include "render/rectangle.h"
#include "surface/slatepeak0x58.h"

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
	m_unk0x14 = 0.0f;
	m_unk0x18 = 0.0f;
	m_unk0x1c = 0;
	m_unk0x20 = 0;
	m_unk0x24 = 0.0f;
	m_unk0x28 = 0.0f;
	m_unk0x2c = 0;
	m_unk0x30 = 0;
	m_unk0x34 = 0.0f;
	m_unk0x38 = 0.0f;
	m_unk0x3c = 0.0f;
	m_unk0x40 = 0.0f;
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
	case GolFileParser::e_unknown0x43:
		m_unk0x14 = p_parser->ReadFloat();
		m_flags = (m_flags & ~1) | 4;
		break;
	case GolFileParser::e_unknown0x44:
		m_unk0x18 = p_parser->ReadFloat();
		m_flags = (m_flags & ~2) | 8;
		break;
	case GolFileParser::e_unknown0x45:
		m_flags = (m_flags & ~4) | 1;
		break;
	case GolFileParser::e_unknown0x46:
		m_flags = (m_flags & ~8) | 2;
		break;
	case GolFileParser::e_unknown0x47:
		m_unk0x24 = p_parser->ReadFloat();
		m_flags |= 0x10;
		break;
	case GolFileParser::e_unknown0x48:
		m_unk0x28 = p_parser->ReadFloat();
		m_flags |= 0x20;
		break;
	case GolFileParser::e_unknown0x49:
		m_unk0x34 = p_parser->ReadFloat();
		break;
	case GolFileParser::e_unknown0x4a:
		m_unk0x38 = p_parser->ReadFloat();
		break;
	case GolFileParser::e_unknown0x4b:
		m_unk0x3c = p_parser->ReadFloat();
		break;
	case GolFileParser::e_unknown0x4c:
		m_unk0x40 = p_parser->ReadFloat();
		break;
	case GolFileParser::e_unknown0x66:
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
void CutsceneVisual::VTable0x14()
{
	if (!(m_flags & 0x40) && m_unk0x10 == 0) {
		LegoU32 flags = m_flags | 0xc0;

		m_unk0x1c = m_unk0x14;
		m_unk0x20 = m_unk0x18;
		m_unk0x2c = m_unk0x24;
		m_unk0x30 = m_unk0x28;
		m_flags = flags;
	}
}

// FUNCTION: LEGORACERS 0x004a3540
void CutsceneVisual::VTable0x18()
{
	m_flags &= ~0x40;
}

// FUNCTION: LEGORACERS 0x004a3550
void CutsceneVisual::FUN_004a3550(LegoFloat p_elapsedSeconds)
{
	if ((m_flags & 0x40) && !(m_flags & 0x80)) {
		m_unk0x1c += m_unk0x34 * p_elapsedSeconds;
		m_unk0x20 += m_unk0x38 * p_elapsedSeconds;
		m_unk0x2c += m_unk0x3c * p_elapsedSeconds;
		m_unk0x30 += m_unk0x40 * p_elapsedSeconds;
	}
}

// FUNCTION: LEGORACERS 0x004a35a0
void CutsceneVisual::FUN_004a35a0(GolD3DRenderDevice* p_renderer)
{
	if (m_flags & 0x40) {
		LegoS32 sourceWidth;
		LegoS32 sourceHeight;
		LegoS32 renderTargetWidth = p_renderer->GetRenderTargetInfo()->GetWidth();
		LegoFloat width = static_cast<LegoFloat>(renderTargetWidth);
		LegoS32 renderTargetHeight = p_renderer->GetRenderTargetInfo()->GetHeight();
		LegoFloat height = static_cast<LegoFloat>(renderTargetHeight);

		if (m_flags & c_flagLayoutPending) {
			FUN_004a36e0(p_renderer, width, height);
		}

		if (m_unk0x1c >= 0.0f && m_unk0x20 >= 0.0f) {
			LegoFloat scaledX = m_unk0x1c;
			scaledX *= width;
			LegoS32 x = static_cast<LegoS32>(scaledX);

			LegoFloat scaledY = m_unk0x20;
			scaledY *= height;
			LegoS32 y = static_cast<LegoS32>(scaledY);

			LegoFloat scaledWidth = m_unk0x2c;
			scaledWidth *= width;
			LegoS32 drawWidth = static_cast<LegoS32>(scaledWidth);

			LegoFloat scaledHeight = m_unk0x30;
			scaledHeight *= height;
			LegoS32 drawHeight = static_cast<LegoS32>(scaledHeight);

			if (drawWidth) {
				if (drawHeight && drawWidth + x <= static_cast<LegoU32>(renderTargetWidth) &&
					y + drawHeight <= static_cast<LegoU32>(renderTargetHeight)) {
					VTable0x1c(&sourceWidth, &sourceHeight);

					LegoFloat scaleY = static_cast<LegoFloat>(drawHeight) / static_cast<LegoFloat>(sourceHeight);
					LegoFloat scaleX = static_cast<LegoFloat>(drawWidth) / static_cast<LegoFloat>(sourceWidth);
					VTable0x20(p_renderer, x, y, drawWidth, drawHeight, scaleX, scaleY);
				}
			}
		}
	}
}

// STUB: LEGORACERS 0x004a36e0
void CutsceneVisual::FUN_004a36e0(GolD3DRenderDevice* p_renderer, LegoFloat p_width, LegoFloat p_height)
{
	STUB(0x004a36e0);

	const Rect* viewport = &p_renderer->GetUnk0x0c()->m_viewport;
	LegoS32 viewportX = viewport->m_left;
	LegoS32 viewportY = viewport->m_top;
	LegoS32 viewportWidth = viewport->m_right - viewportX;
	LegoS32 viewportHeight = viewport->m_bottom - viewportY;

	LegoS32 imageWidth;
	LegoS32 imageHeight;
	VTable0x1c(&imageWidth, &imageHeight);

	LegoU32 flags = m_flags;
	LegoBool32 hasHeight;
	LegoBool32 hasWidth = flags & c_flagWidth;
	if (hasWidth) {
		LegoFloat width = m_unk0x2c;
		imageWidth = static_cast<LegoS32>(width * p_width);
	}

	hasHeight = flags & c_flagHeight;
	if (hasHeight) {
		LegoFloat height = m_unk0x30;
		imageHeight = static_cast<LegoS32>(height * p_height);
	}

	viewportY += (viewportHeight - imageHeight) / 2;
	if (!(flags & c_flagPositionX)) {
		viewportX += (viewportWidth - imageWidth) / 2;
		m_unk0x1c = static_cast<LegoFloat>(viewportX) / p_width;
	}

	if (!(flags & c_flagPositionY)) {
		m_unk0x20 = static_cast<LegoFloat>(viewportY) / p_height;
	}

	if (!hasWidth) {
		m_unk0x2c = static_cast<LegoFloat>(imageWidth) / p_width;
	}

	if (!hasHeight) {
		m_unk0x30 = static_cast<LegoFloat>(imageHeight) / p_height;
	}

	m_flags = flags & ~c_flagLayoutPending;
}
