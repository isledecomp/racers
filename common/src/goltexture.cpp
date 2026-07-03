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
	GolTexture* texture = this;
	GolImgFile* source = p_source;
	GolSurfaceFormat requestedFormat = source->GetTextureFormat();
	GolSurfaceFormat textureFormat;
	LegoU32 rendererAlphaFlag = GolRenderDevice::c_flagBlackColorKey;

	if (p_renderer.VTable0x110()) {
		texture->m_textureFlags |= c_textureFlagBit6;
	}
	if ((texture->m_textureFlags & c_textureFlagColorKeyed) && (p_renderer.GetFlags() & rendererAlphaFlag)) {
		texture->m_textureFlags |= c_textureFlagBlackColorKey;
	}

	p_renderer.SelectTextureFormat(requestedFormat, &textureFormat, texture->m_textureFlags & c_textureFlagColorKeyed);
	texture->Allocate(p_renderer, textureFormat, source->GetWidth(), source->GetHeight());

	if (texture->m_textureFlags & c_textureFlagColorKeyed) {
		ColorRGBA colorKey = texture->m_colorKey;
		if (p_renderer.GetFlags() & rendererAlphaFlag) {
			source->SetColorKeyReplacement(g_transparentBlack);
		}
		else {
			source->SetColorKeyReplacement(texture->m_colorKey);
		}

		source->LoadSurface(texture, texture->m_textureFlags & c_textureFlagFlipVertically, &colorKey);
	}
	else {
		source->LoadSurface(texture, texture->m_textureFlags & c_textureFlagFlipVertically, NULL);
	}
}
