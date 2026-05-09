#include "softwarerenderer0x58.h"

#include "golcpu.h"

#include <stdlib.h>

DECOMP_SIZE_ASSERT(SoftwareRenderer0x58, 0x58)
DECOMP_SIZE_ASSERT(SoftwareRenderer0x58::Command0x14, 0x14)

// FUNCTION: GOLDP 0x10029920 FOLDED
void NoopSpanRasterizer()
{
	// empty
}

// FUNCTION: GOLDP 0x1003ba20
static void NoopTriangleRasterizer()
{
	// empty
}

// STUB: GOLDP 0x100411b0
void SoftwareRenderer0x58::FUN_100411b0(LegoU8* p_buffer, DuskwindBananaRelic0x24* p_material, LegoU32 p_index)
{
	// TODO
	STUB(0x100411b0);
}

// FUNCTION: GOLDP 0x100416a0
SoftwareRenderer0x58::SoftwareRenderer0x58()
{
	DetectCPU();
	m_unk0x4c = 0;
	m_nodes = NULL;
	m_unk0x54 = 0;
}

// FUNCTION: GOLDP 0x100416c0
LegoBool SoftwareRenderer0x58::Initialize(PixelFormat p_pixelFormat, LegoS32 p_nodeCapacity)
{
	m_unk0x54 = NULL;
	if (m_nodes != NULL) {
		delete[] m_nodes;
		m_nodes = NULL;
	}

	PixelFormat indexedPixelFormat = e_formatIndex8;
	m_currentTriangleRasterizer = NoopTriangleRasterizer;
	m_triangleRasterizer = NoopTriangleRasterizer;
	m_unk0x34 = 0;
	m_unk0x2c = 0;
	m_spanRasterizer = NoopSpanRasterizer;
	m_unk0x38 = 10000.0f;
	m_unk0x3c = 225.0f;

	switch (p_pixelFormat) {
	default:
		m_bitsPerPixel = 16;
		m_bytesPerPixel = indexedPixelFormat;
		m_pixelFormat = p_pixelFormat & 1;
		break;
	case e_formatIndex8:
		m_bitsPerPixel = 8;
		m_bytesPerPixel = 1;
		m_pixelFormat = indexedPixelFormat;
		break;
	}

	if (p_nodeCapacity > 0xffff) {
		p_nodeCapacity = 0xffff;
	}

	m_nodes = new Command0x14[p_nodeCapacity];
	if (m_nodes == NULL) {
		m_unk0x54 = NULL;
		return FALSE;
	}

	m_nodeCapacity = p_nodeCapacity;
	return TRUE;
}

// FUNCTION: GOLDP 0x10041770
SoftwareRenderer0x58::~SoftwareRenderer0x58()
{
	m_unk0x54 = 0;
	if (m_nodes != NULL) {
		delete[] m_nodes;
		m_nodes = NULL;
	}
}

// FUNCTION: GOLDP 0x100417a0
void SoftwareRenderer0x58::FUN_100417a0(Command0x14* p_cmds, LegoU32 p_count, LegoFloat p_arg3)
{
	while (p_count) {
		p_cmds->m_unk0x04 = p_arg3;
		p_cmds++;
		p_count--;
	}
}

// STUB: GOLDP 0x100417c0
void SoftwareRenderer0x58::FUN_100417c0(Command0x14* p_cmds, LegoU32 p_count)
{
	// TODO
	STUB(0x100417c0);
}

// STUB: GOLDP 0x10041830
void SoftwareRenderer0x58::FUN_10041830(LegoS32, LegoBool32)
{
	STUB(0x10041830);
}

// STUB: GOLDP 0x10041a20
void SoftwareRenderer0x58::FUN_10041a20(LegoBool32)
{
	STUB(0x10041a20);
}
