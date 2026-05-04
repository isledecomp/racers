#include "bronzedune0x4c.h"

#include "golerror.h"

DECOMP_SIZE_ASSERT(BronzeDune0x4c, 0x4c)

// GLOBAL: GOLDP 0x10063c50
BronzeDune0x4c g_bronzeDune0x4c;

// STUB: GOLDP 0x10004f80
void BronzeDune0x4c::VTable0x30(WhiteFalcon0x140& p_renderer, undefined4* p_arg2)
{
	GoldDune0x38::VTable0x30(p_renderer, p_arg2);
}

// FUNCTION: GOLDP 0x1001de50
BronzeDune0x4c::BronzeDune0x4c()
{
}

// FUNCTION: GOLDP 0x1002a360
BronzeDune0x4c::~BronzeDune0x4c()
{
	VTable0x38();
}

// FUNCTION: GOLDP 0x1002a3e0
void BronzeDune0x4c::VTable0x34(
	WhiteFalcon0x140& p_renderer,
	const FalconTextureFormat& p_textureFormat,
	LegoU32 p_width,
	LegoU32 p_height
)
{
	if (m_pixelFlags & c_lockRequestRead) {
		VTable0x38();
	}
	m_pixelFlags |= c_lockRequestRead;
	m_width = static_cast<LegoU16>(p_width);
	m_height = static_cast<LegoU16>(p_height);
	m_textureFormat = p_textureFormat;
	if (p_textureFormat.m_paletteMask) {
		m_unk0x40.FUN_1002a120(p_textureFormat);
	}
	LegoU16 pitch = (p_textureFormat.m_bitsPerPixel * p_width + 8 - 1) / 8U;
	m_pitch = static_cast<LegoU16>(pitch);
	m_pixels = new LegoU8[pitch * p_height];
	if (m_pixels == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
}

// FUNCTION: GOLDP 0x1002a470
void BronzeDune0x4c::VTable0x38()
{
	m_unk0x40.FUN_1002a1b0();
	if (m_pixels != NULL) {
		delete[] m_pixels;
		m_pixels = NULL;
	}
	m_pixelFlags = 0;
}

// FUNCTION: GOLDP 0x1002a4a0
IPalette0x4* BronzeDune0x4c::GetPalette()
{
	return &m_unk0x40;
}
