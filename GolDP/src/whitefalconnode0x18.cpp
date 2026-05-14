#include "whitefalconnode0x18.h"

#include "jadeorbitbase0x10.h"

DECOMP_SIZE_ASSERT(WhiteFalconNode0x18, 0x18)

// FUNCTION: GOLDP 0x10029980
WhiteFalconNode0x18::WhiteFalconNode0x18()
{
	m_capacity = 0;
	m_unk0x14 = 0;
	m_unk0x0c = 0;
}

// FUNCTION: GOLDP 0x100299c0
WhiteFalconNode0x18::~WhiteFalconNode0x18()
{
	GolNameTable::Clear();
	m_capacity = 0;
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
	if (m_capacity != 0) {
		Clear();
	}

	m_capacity = p_capacity;
	GolNameTable::Allocate(m_capacity);
	VTable0x0c();
}

// FUNCTION: GOLDP 0x10029c40
void WhiteFalconNode0x18::Clear()
{
	GolNameTable::Clear();
	m_capacity = 0;
	m_unk0x0c = 0;
}

// FUNCTION: GOLDP 0x1001d700 FOLDED
LegoU32 WhiteFalconNode0x18::VTable0x1c(const JadeOrbitBase0x10&) const
{
	return 0;
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
void WhiteFalconNode0x18::VTable0x20(const GolMatrix4&)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
void WhiteFalconNode0x18::VTable0x24(const GolMatrix34* p_m)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
void WhiteFalconNode0x18::VTable0x28(undefined4, undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
void WhiteFalconNode0x18::VTable0x2c(LegoU32 p_index, GolMatrix34* p_dest) const
{
	// empty
}
