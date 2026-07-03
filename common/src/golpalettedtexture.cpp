#include "golpalettedtexture.h"

#include "golerror.h"

DECOMP_SIZE_ASSERT(GolPalettedTexture, 0x4c)

// GLOBAL: GOLDP 0x10063c50
// GLOBAL: LEGORACERS 0x004c28e0
GolPalettedTexture g_palettedTexture;

// FUNCTION: GOLDP 0x10004f80
// FUNCTION: LEGORACERS 0x00408b90
void GolPalettedTexture::LoadFromImgFile(GolRenderDevice& p_renderer, GolImgFile* p_source)
{
	GolTexture::LoadFromImgFile(p_renderer, p_source);
}

// FUNCTION: GOLDP 0x1002a360
// FUNCTION: LEGORACERS 0x00413660
GolPalettedTexture::~GolPalettedTexture()
{
	Destroy();
}

// FUNCTION: GOLDP 0x1002a3e0
// FUNCTION: LEGORACERS 0x004136c0
void GolPalettedTexture::Allocate(
	GolRenderDevice& p_renderer,
	const GolSurfaceFormat& p_textureFormat,
	LegoU32 p_width,
	LegoU32 p_height
)
{
	if (m_pixelFlags & c_lockRequestRead) {
		Destroy();
	}

	m_pixelFlags |= c_lockRequestRead;
	m_width = static_cast<LegoU16>(p_width);
	m_height = static_cast<LegoU16>(p_height);
	m_textureFormat = p_textureFormat;

	if (p_textureFormat.m_paletteMask) {
		m_unk0x40.Initialize(p_textureFormat);
	}

	LegoU16 pitch = (p_textureFormat.m_bitsPerPixel * p_width + 8 - 1) / 8U;
	m_pitch = static_cast<LegoU16>(pitch);
	m_pixels = new LegoU8[pitch * p_height];
	if (m_pixels == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
}

// FUNCTION: GOLDP 0x1002a470
// FUNCTION: LEGORACERS 0x00413750
void GolPalettedTexture::Destroy()
{
	m_unk0x40.Shutdown();
	if (m_pixels != NULL) {
		delete[] m_pixels;
		m_pixels = NULL;
	}

	m_pixelFlags = 0;
}

// FUNCTION: GOLDP 0x1002a4a0
// FUNCTION: LEGORACERS 0x00413780
GolPaletteBase* GolPalettedTexture::GetPalette()
{
	return &m_unk0x40;
}
