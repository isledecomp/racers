#include "whitefalconnode0x18.h"

DECOMP_SIZE_ASSERT(WhiteFalconNode0x18, 0x18)

// FUNCTION: GOLDP 0x10029980
WhiteFalconNode0x18::WhiteFalconNode0x18()
{
	m_unk0x10 = 0;
	m_unk0x14 = 0;
	m_unk0x0c = 0;
}

// FUNCTION: GOLDP 0x100299c0
WhiteFalconNode0x18::~WhiteFalconNode0x18()
{
	GolNameTable::Clear();
	m_unk0x10 = 0;
	m_unk0x0c = 0;
}

// STUB: GOLDP 0x10029a20
void WhiteFalconNode0x18::VTable0x14(undefined4, undefined4)
{
	STUB(0x10029a20);
}

// STUB: GOLDP 0x10029b50
void WhiteFalconNode0x18::VTable0x10(undefined4)
{
	STUB(0x10029b50);
}

// FUNCTION: GOLDP 0x10029c10
void WhiteFalconNode0x18::Allocate(LegoU32 p_capacity)
{
	if (m_unk0x10 != 0) {
		Clear();
	}

	m_unk0x10 = p_capacity;
	GolNameTable::Allocate(m_unk0x10);
	VTable0x0c();
}

// FUNCTION: GOLDP 0x10029c40
void WhiteFalconNode0x18::Clear()
{
	GolNameTable::Clear();
	m_unk0x10 = 0;
	m_unk0x0c = 0;
}

// FUNCTION: GOLDP 0x1001d700 FOLDED
undefined4 WhiteFalconNode0x18::VTable0x1c(undefined4)
{
	return 0;
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
void WhiteFalconNode0x18::VTable0x20(undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
void WhiteFalconNode0x18::VTable0x24(undefined4)
{
	// empty
}

// STUB: GOLDP 0x1002c010 FOLDED
void WhiteFalconNode0x18::VTable0x28(undefined4, undefined4)
{
	MATCHING(0x1002c010);
}

// STUB: GOLDP 0x1002c010 FOLDED
void WhiteFalconNode0x18::VTable0x2c(undefined4, undefined4)
{
	MATCHING(0x1002c010);
}
