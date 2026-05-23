#include "golddune0x38.h"

#include "golimgfile.h"
#include "whitefalcon0x140.h"

DECOMP_SIZE_ASSERT(GoldDune0x38, 0x38)

// FUNCTION: GOLDP 0x1002bb00
GoldDune0x38::GoldDune0x38()
{
	m_unk0x34 = 0;
	m_unk0x36 = 0;
}

// FUNCTION: GOLDP 0x1002bb20
void GoldDune0x38::VTable0x30(WhiteFalcon0x140& p_renderer, GolImgFile* p_source)
{
	GolSurfaceFormat requestedFormat = p_source->GetTextureFormat();
	GolSurfaceFormat textureFormat;

	if (p_renderer.VTable0x110()) {
		m_unk0x36 |= c_unk0x36Bit6;
	}
	if ((m_unk0x36 & c_unk0x36Bit5) && (p_renderer.GetFlags() & WhiteFalcon0x140::c_flagBit9)) {
		m_unk0x36 |= c_unk0x36Bit7;
	}

	p_renderer.SelectTextureFormat(requestedFormat, &textureFormat, m_unk0x36 & c_unk0x36Bit5);
	VTable0x34(p_renderer, textureFormat, p_source->GetWidth(), p_source->GetHeight());

	if (m_unk0x36 & c_unk0x36Bit5) {
		ColorRGBA colorKey = m_colorKey;
		if (m_unk0x36 & c_unk0x36Bit9) {
			ColorRGBA black = {0, 0, 0, 0};
			p_source->SetUnk0x0a0(black);
		}
		else {
			p_source->SetUnk0x0a0(m_colorKey);
		}

		p_source->VTable0x20(this, m_unk0x36 & c_unk0x36Bit2, &colorKey);
	}
	else {
		p_source->VTable0x20(this, m_unk0x36 & c_unk0x36Bit2, NULL);
	}
}
