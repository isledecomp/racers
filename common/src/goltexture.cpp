#include "goltexture.h"

#include "golimgfile.h"
#include "render/golrenderdevice.h"

DECOMP_SIZE_ASSERT(GolTexture, 0x38)

// GLOBAL: GOLDP 0x10057668
// GLOBAL: LEGORACERS 0x004af924
extern const ColorRGBA g_transparentBlack = {0, 0, 0, 0};

// FUNCTION: GOLDP 0x1002bb00
// FUNCTION: LEGORACERS 0x00415c20
GolTexture::GolTexture()
{
	m_mipmapCount = 0;
	m_textureFlags = 0;
}

// FUNCTION: GOLDP 0x1002bb20
// FUNCTION: LEGORACERS 0x00415c60
void GolTexture::LoadFromImgFile(GolRenderDevice& p_renderer, GolImgFile* p_source)
{
	GolSurfaceFormat requestedFormat;
	GolSurfaceFormat textureFormat;
	LegoU32 rendererAlphaFlag = GolRenderDevice::c_flagBlackColorKey;
	requestedFormat = p_source->GetTextureFormat();

	if (p_renderer.VTable0x110()) {
		m_textureFlags |= c_textureFlagBit6;
	}

	if ((m_textureFlags & c_textureFlagColorKeyed) && (p_renderer.GetFlags() & rendererAlphaFlag)) {
		m_textureFlags |= c_textureFlagBlackColorKey;
	}

	p_renderer.SelectTextureFormat(requestedFormat, &textureFormat, m_textureFlags & c_textureFlagColorKeyed);
	Allocate(p_renderer, textureFormat, p_source->GetWidth(), p_source->GetHeight());

	if (m_textureFlags & c_textureFlagColorKeyed) {
		ColorRGBA colorKey = m_colorKey;
		if (p_renderer.GetFlags() & rendererAlphaFlag) {
			p_source->SetColorKeyReplacement(g_transparentBlack);
		}
		else {
			p_source->SetColorKeyReplacement(m_colorKey);
		}

		p_source->LoadSurface(this, m_textureFlags & c_textureFlagFlipVertically, &colorKey);
	}
	else {
		p_source->LoadSurface(this, m_textureFlags & c_textureFlagFlipVertically, NULL);
	}
}
