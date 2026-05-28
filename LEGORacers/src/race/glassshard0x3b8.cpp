#include "race/glassshard0x3b8.h"

DECOMP_SIZE_ASSERT(GlassShard0x3b8, 0x3b8)

// FUNCTION: LEGORACERS 0x00422350
GlassShard0x3b8::GlassShard0x3b8()
{
	FUN_004223c0();
}

// FUNCTION: LEGORACERS 0x004223b0
GlassShard0x3b8::~GlassShard0x3b8()
{
	FUN_00422670();
}

// STUB: LEGORACERS 0x004223c0
void GlassShard0x3b8::FUN_004223c0()
{
	// TODO
	STUB(0x4223c0);
}

// STUB: LEGORACERS 0x00422420
void GlassShard0x3b8::FUN_00422420(GolD3DRenderDevice*, GolExport*, undefined4, undefined4)
{
	// TODO
	STUB(0x422420);
}

// STUB: LEGORACERS 0x00422670
void GlassShard0x3b8::FUN_00422670()
{
	// TODO
	STUB(0x422670);
}

// FUNCTION: LEGORACERS 0x004230e0
void GlassShard0x3b8::FUN_004230e0()
{
	LegoU32 i;
	LegoU32 previousSum = 0;
	LegoU32 currentSum = 0;

	for (i = 0; i < 3; i++) {
		m_unk0x14[i] = m_unk0x18[0xcec / sizeof(*m_unk0x18) + i];
	}

	for (i = 0; i < 3; i++) {
		previousSum += m_unk0x10[i];
		currentSum += m_unk0x14[i];
	}

	if (currentSum < previousSum || previousSum == 0) {
		undefined4* previousBuffer = m_unk0x10;
		m_unk0x10 = m_unk0x14;
		m_unk0x14 = previousBuffer;
	}

	m_unk0x300.SetFlags0xb4((m_unk0x300.GetFlags0xb4() & 0xfc) | c_flag0x3b4Bit4);
	m_unk0x18 = NULL;
}

// FUNCTION: LEGORACERS 0x004234b0
LegoBool32 GlassShard0x3b8::FUN_004234b0()
{
	LegoU8 flags = m_unk0x300.GetFlags0xb4();
	if (!(flags & (c_flag0x3b4Bit0 | c_flag0x3b4Bit4))) {
		return FALSE;
	}
	if (!(flags & c_flag0x3b4Bit3)) {
		return FALSE;
	}

	LegoU32 previousSum = 0;
	LegoU32 currentSum = 0;

	for (LegoU32 i = 0; i < 3; i++) {
		previousSum += m_unk0x0c[i];
		currentSum += m_unk0x10[i];
	}

	return currentSum < previousSum;
}
