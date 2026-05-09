#include "moonlitcanvas0x5b0.h"

#include <string.h>

DECOMP_SIZE_ASSERT(MoonlitCanvas0x5b0, 0x5b0)

// GLOBAL: GOLDP 0x1005cdfc
LegoChar g_moonlitCanvasExtension[] = ".img";

// FUNCTION: GOLDP 0x1001fe90
MoonlitCanvas0x5b0::MoonlitCanvas0x5b0()
{
	m_width = 0;
	m_height = 0;
	m_unk0x4c = 0;
	m_unk0x98 = 0;
	m_unk0x6c = 0;
	m_unk0x9c.m_red = 0;
	m_unk0x9c.m_grn = 0;
	m_unk0x9c.m_blu = 0;
	m_unk0x9c.m_alp = 0;
	m_unk0x74 = 0;
	m_unk0x68 = 0;
	m_unk0xa0.m_red = 0;
	m_unk0xa0.m_grn = 0;
	m_unk0xa0.m_blu = 0;
	m_unk0xa0.m_alp = 0;
	m_unk0xa4 = 0;
	m_unk0x5a8 = 0;
	m_unk0x5ac = 0;
	m_unk0x04 = 0;
	m_unk0x08 = 0;
	m_unk0x0c = 0;
	m_unk0x10 = NULL;
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void MoonlitCanvas0x5b0::VTable0x00()
{
	// empty
}

// FUNCTION: GOLDP 0x1001ff50
MoonlitCanvas0x5b0::~MoonlitCanvas0x5b0()
{
	m_file.Dispose();

	if (m_unk0x10 != NULL) {
		delete[] m_unk0x10;
		m_unk0x10 = NULL;
	}
}

// STUB: GOLDP 0x1001ffc0
void MoonlitCanvas0x5b0::VTable0x08(const LegoChar*)
{
	STUB(0x1001ffc0);
}

// FUNCTION: GOLDP 0x100200c0
void MoonlitCanvas0x5b0::VTable0x0c()
{
	m_file.Dispose();

	if (m_unk0x10 != NULL) {
		delete[] m_unk0x10;
		m_unk0x10 = NULL;
	}
}

// FUNCTION: GOLDP 0x100226a0
const LegoChar* MoonlitCanvas0x5b0::VTable0x10()
{
	return g_moonlitCanvasExtension;
}

// FUNCTION: GOLDP 0x100226b0
void MoonlitCanvas0x5b0::VTable0x14(undefined4, undefined4, undefined4, undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x100226c0
void MoonlitCanvas0x5b0::FUN_100226c0(
	const FalconTextureFormat& p_textureFormat,
	LegoU32 p_width,
	LegoU32 p_height,
	LegoU32 p_pitch,
	const ColorRGBA* p_palette,
	LegoU32 p_paletteCount
)
{
	if (m_file.GetFlags() & GolStream::c_flagOpen) {
		VTable0x0c();
	}

	m_textureFormat = p_textureFormat;
	m_width = p_width;
	m_height = p_height;
	m_unk0x4c = p_pitch;
	m_unk0x5a8 = 0;
	m_unk0x5ac = 0;
	m_unk0x6c = 1 << static_cast<LegoU8>(m_textureFormat.m_bitsPerPixel);

	if (p_palette != NULL && p_paletteCount != 0) {
		::memcpy(m_unk0xa8, p_palette, sizeof(ColorRGBA) * p_paletteCount);
	}
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
void MoonlitCanvas0x5b0::VTable0x18(undefined4*)
{
	// empty
}

// FUNCTION: GOLDP 0x100294f0 FOLDED
void MoonlitCanvas0x5b0::VTable0x1c(GoldDune0x38*, LegoU32, undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x100294f0 FOLDED
void MoonlitCanvas0x5b0::VTable0x20(GoldDune0x38*, LegoU32, undefined4)
{
	// empty
}
