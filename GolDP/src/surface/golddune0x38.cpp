#include "surface/golddune0x38.h"

#include "golimgfile.h"
#include "render/golrenderdevice.h"

DECOMP_SIZE_ASSERT(GoldDune0x38, 0x38)

extern const ColorRGBA g_unk0x10057668;

// FUNCTION: GOLDP 0x1002bb00
GoldDune0x38::GoldDune0x38()
{
	m_unk0x34 = 0;
	m_unk0x36 = 0;
}

// FUNCTION: GOLDP 0x1002bb20
void GoldDune0x38::VTable0x30(GolRenderDevice& p_renderer, GolImgFile* p_source)
{
	GoldDune0x38* texture = this;
	GolImgFile* source = p_source;
	GolSurfaceFormat requestedFormat = source->GetTextureFormat();
	GolSurfaceFormat textureFormat;
	LegoU32 rendererAlphaFlag = GolRenderDevice::c_flagBit9;

	if (p_renderer.VTable0x110()) {
		texture->m_unk0x36 |= c_unk0x36Bit6;
	}
	if ((texture->m_unk0x36 & c_unk0x36Bit5) && (p_renderer.GetFlags() & rendererAlphaFlag)) {
		texture->m_unk0x36 |= c_unk0x36Bit7;
	}

	p_renderer.SelectTextureFormat(requestedFormat, &textureFormat, texture->m_unk0x36 & c_unk0x36Bit5);
	texture->VTable0x34(p_renderer, textureFormat, source->GetWidth(), source->GetHeight());

	if (texture->m_unk0x36 & c_unk0x36Bit5) {
		ColorRGBA colorKey = texture->m_colorKey;
		if (p_renderer.GetFlags() & rendererAlphaFlag) {
			source->SetUnk0x0a0(g_unk0x10057668);
		}
		else {
			source->SetUnk0x0a0(texture->m_colorKey);
		}

		source->VTable0x20(texture, texture->m_unk0x36 & c_unk0x36Bit2, &colorKey);
	}
	else {
		source->VTable0x20(texture, texture->m_unk0x36 & c_unk0x36Bit2, NULL);
	}
}
