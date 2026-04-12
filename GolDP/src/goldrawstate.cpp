#include "goldrawstate.h"

#include <stdlib.h>

DECOMP_SIZE_ASSERT(GolDrawState, 0x18)

// FUNCTION: GOLDP 0x1001d570
GolDrawState::GolDrawState()
{
	m_width = 0;
	m_height = 0;
	m_bpp = 0;
	m_flags = 0;
	m_unk0x14 = NULL;
}

// STUB: GOLDP 0x1001d5c0
undefined4 GolDrawState::VTable0x44(undefined4 p_width, undefined4 p_height, undefined4 p_bpp, undefined4 p_flags)
{
	// TODO
	STUB(0x1001d5c0);
	return 0;
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
void GolDrawState::VTable0x0c(undefined4, undefined4)
{
}

// STUB: GOLDP 0x100016f0 FOLDED
undefined4 GolDrawState::VTable0x10()
{
	STUB(0x100016f0);
	return 0;
}

// STUB: GOLDP 0x1001d640
void GolDrawState::VTable0x50()
{
	// TODO
	STUB(0x1001d640);
}

// STUB: GOLDP 0x1001d660
void GolDrawState::VTable0x54(undefined4, undefined4, undefined4, undefined4)
{
	// TODO
	STUB(0x1001d660);
}

// STUB: GOLDP 0x1001d6d0
void GolDrawState::VTable0x4c()
{
	// TODO
	STUB(0x1001d6d0);
}

// STUB: GOLDP 0x1001d6e0
void GolDrawState::VTable0x48()
{
	// TODO
	STUB(0x1001d6e0);
}

// FUNCTION: GOLDP 0x1001d700 FOLDED
undefined4 GolDrawState::VTable0x14(undefined4)
{
	return 0;
}

// FUNCTION: GOLDP 0x1001d700 FOLDED
undefined4 GolDrawState::VTable0x18(undefined4)
{
	return 0;
}

// FUNCTION: GOLDP 0x1001d700 FOLDED
undefined4 GolDrawState::VTable0x1c(undefined4)
{
	return 0;
}

// FUNCTION: GOLDP 0x1001d710
void GolDrawState::VTable0x2c(undefined4, undefined4* p_arg2, undefined4* p_arg3)
{
	*p_arg2 = 0;
	*p_arg3 = 0;
}

// FUNCTION: GOLDP 0x10029950 FOLDED
undefined4 GolDrawState::VTable0x20(undefined4, undefined4)
{
	return 0;
}

// FUNCTION: GOLDP 0x10029950 FOLDED
undefined4 GolDrawState::VTable0x24(undefined4, undefined4)
{
	return 0;
}

// FUNCTION: GOLDP 0x10029950 FOLDED
undefined4 GolDrawState::VTable0x28(undefined4, undefined4)
{
	return 0;
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
void GolDrawState::VTable0x30(undefined4, undefined4*)
{
}

// FUNCTION: GOLDP 0x100294f0
void GolDrawState::VTable0x34(undefined4, undefined4, undefined4*)
{
}

// STUB: GOLDP 0x100016f0 FOLDED
undefined4 GolDrawState::VTable0x38()
{
	STUB(0x100016f0);
	return 0;
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void GolDrawState::VTable0x3c()
{
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void GolDrawState::VTable0x40()
{
}
