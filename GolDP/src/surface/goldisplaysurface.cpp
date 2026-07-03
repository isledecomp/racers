#include "surface/goldisplaysurface.h"

DECOMP_SIZE_ASSERT(GolDisplaySurface, 0x38)

// FUNCTION: GOLDP 0x1001d730
GolDisplaySurface::GolDisplaySurface()
{
	m_unk0x30 = NULL;
	m_unk0x34 = 0;
}

// FUNCTION: GOLDP 0x1001d770
GolDisplaySurface::~GolDisplaySurface()
{
	m_unk0x30 = NULL;
	m_unk0x34 = 0;
}

// FUNCTION: GOLDP 0x1001d790
void GolDisplaySurface::VTable0x30(GolDrawState* p_drawState, undefined4 p_width, undefined4 p_height, undefined4 p_bpp)
{
	m_unk0x30 = p_drawState;
	m_width = (LegoU16) p_width;
	m_height = (LegoU16) p_height;
	m_textureFormat.m_bitsPerPixel = (LegoU16) p_bpp;
}

// FUNCTION: GOLDP 0x1001d7c0
void GolDisplaySurface::VTable0x34()
{
	m_unk0x30 = NULL;
	m_unk0x34 = 0;
}
