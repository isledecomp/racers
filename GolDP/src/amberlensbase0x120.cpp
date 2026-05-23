#include "amberlensbase0x120.h"

DECOMP_SIZE_ASSERT(AmberLensBase0x120, 0x120)

// FUNCTION: GOLDP 0x1001bf30
AmberLensBase0x120::AmberLensBase0x120()
{
	m_unk0x04 = 0;
	m_unk0x08 = 40.0f;
	m_unk0x0c = 1.3333334f;
	m_unk0x10 = 2.0f;
	m_unk0x14 = 200.0f;
	m_unk0x18 = 0.0f;
	m_unk0x1c = 0.0f;
	m_unk0x24 = 0.0f;
	m_unk0x20 = 0.0f;
	m_flags = 3;
	m_viewportMinX = 0;
	m_viewportMaxX = 0;
	m_viewportMinY = 0;
	m_viewportMaxY = 0;
	m_unk0x28 = 0;
	m_unk0x2c = 0;
}

// FUNCTION: GOLDP 0x1001bfb0
AmberLensBase0x120::~AmberLensBase0x120()
{
}

// STUB: GOLDP 0x1001bfc0
void AmberLensBase0x120::FUN_1001bfc0(undefined*)
{
	STUB(0x1001bfc0);
}

// STUB: GOLDP 0x1001c450
void AmberLensBase0x120::FUN_1001c450(undefined*)
{
	STUB(0x1001c450);
}

// STUB: GOLDP 0x1001c900
void AmberLensBase0x120::VTable0x24(undefined4, undefined4, undefined4)
{
	STUB(0x1001c900);
}

// FUNCTION: GOLDP 0x1001cb30
void AmberLensBase0x120::FUN_1001cb30(FloatyFerry0xf4* p_arg1, LegoU32 p_arg2)
{
	m_unk0x28 = p_arg1;
	m_unk0x2c = p_arg2;
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
void AmberLensBase0x120::VTable0x20(const GolVec3*, GolVec3*)
{
	// empty
}
