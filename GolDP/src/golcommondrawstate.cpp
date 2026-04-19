#include "golcommondrawstate.h"

DECOMP_SIZE_ASSERT(GolCommonDrawState, 0x20)

// FUNCTION: GOLDP 0x100184a0
GolCommonDrawState::GolCommonDrawState()
{
	m_unk0x18 = 0;
	m_hashTable = NULL;
}

// FUNCTION: GOLDP 0x100184e0
LegoS32 GolCommonDrawState::VTable0x44(LegoU32 p_width, LegoU32 p_height, LegoU32 p_bpp, LegoU32 p_flags)
{
	LegoS32 result = GolDrawState::VTable0x44(p_width, p_height, p_bpp, p_flags);
	if (!result) {
		result = VTable0x58();
	}

	return result;
}

// STUB: GOLDP 0x10018510
void GolCommonDrawState::VTable0x48()
{
	// TODO
	STUB(0x10018510);
}

// STUB: GOLDP 0x10018540
void GolCommonDrawState::VTable0x50()
{
	// TODO
	STUB(0x10018540);
}

// STUB: GOLDP 0x10018570
void GolCommonDrawState::VTable0x54(undefined4, undefined4, undefined4, undefined4)
{
	STUB(0x10018570);
	// TODO
}

// FUNCTION: GOLDP 0x10018620
LegoU32 GolCommonDrawState::VTable0x5c() const
{
	return 16;
}

// FUNCTION: GOLDP 0x1001d5b0
GolCommonDrawState::~GolCommonDrawState()
{
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
undefined4 GolCommonDrawState::VTable0x60()
{
	return 1;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::VTable0x64() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::VTable0x68() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::VTable0x6c() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::VTable0x70() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::VTable0x74() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::VTable0x78() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::VTable0x7c() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::VTable0x80() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::VTable0x84() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::VTable0x88() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::VTable0x8c() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::VTable0x90() const
{
	return TRUE;
}

// STUB: GOLDP 0x100016f0 FOLDED
undefined4 GolCommonDrawState::VTable0x94()
{
	STUB(0x100016f0);
	return 0;
}

// STUB: GOLDP 0x100016f0 FOLDED
LegoBool32 GolCommonDrawState::VTable0x98() const
{
	STUB(0x100016f0);
	return 0;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::VTable0x9c() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::VTable0xa0() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::VTable0xa4() const
{
	return TRUE;
}

// STUB: GOLDP 0x100016f0 FOLDED
LegoBool32 GolCommonDrawState::VTable0xa8() const
{
	STUB(0x100016f0);
	return FALSE;
}

// FUNCTION: GOLDP 0x10018630 FOLDED
void* GolCommonDrawState::VTable0xac()
{
	return NULL;
}

// FUNCTION: GOLDP 0x10018630 FOLDED
undefined4 GolCommonDrawState::VTable0xb0()
{
	return 0;
}

// FUNCTION: GOLDP 0x10018630 FOLDED
undefined4 GolCommonDrawState::VTable0xb4()
{
	return 0;
}
