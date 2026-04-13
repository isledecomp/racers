#include "goldenoak0x128.h"

#include "amberleaf0x10.h"

DECOMP_SIZE_ASSERT(GoldenOak0x128, 0x128)

// FUNCTION: LEGORACERS 0x41a650
GoldenOak0x128::GoldenOak0x128() : m_unk0x10(NULL)
{
	// TODO: effective match only; m_unk0x10 init store scheduled early - class hierarchy may be wrong
	m_unk0x20 = 0;
	m_unk0x124 = 0;
}

// FUNCTION: LEGORACERS 0x41a6b0
GoldenOak0x128::~GoldenOak0x128()
{
	VTable0x08();
}

// STUB: LEGORACERS 0x41a700
GolListLink* GoldenOak0x128::VTable0x04(undefined4)
{
	STUB(0x41a700);
	return NULL;
}

// STUB: LEGORACERS 0x41a850
GolListLink* GoldenOak0x128::VTable0x08()
{
	STUB(0x41a850);
	return NULL;
}

// FUNCTION: LEGORACERS 0x41a890
undefined4 GoldenOak0x128::VTable0x0c()
{
	return m_unk0x04 != 0;
}

// STUB: LEGORACERS 0x41a8a0
AmberLeaf0x10* GoldenOak0x128::VTable0x10(undefined4)
{
	STUB(0x41a8a0);
	return NULL;
}

// FUNCTION: LEGORACERS 0x41a9d0 FOLDED
void GoldenOak0x128::VTable0x14(AmberLeaf0x10* p_node)
{
	delete p_node;
}

// FUNCTION: LEGORACERS 0x41a9f0 FOLDED
void* GoldenOak0x128::VTable0x18()
{
	return m_unk0x10;
}
