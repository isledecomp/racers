#include "amberleaf0x10.h"

DECOMP_SIZE_ASSERT(AmberLeaf0x10, 0x10)

// FUNCTION: LEGORACERS 0x004113b0
undefined4 AmberLeaf0x10::VTable0x04(undefined4)
{
	return 0;
}

// FUNCTION: LEGORACERS 0x0041bfa0
AmberLeaf0x10::AmberLeaf0x10()
{
	m_unk0x0c = 0;
}

// FUNCTION: LEGORACERS 0x0041bfe0
AmberLeaf0x10::~AmberLeaf0x10()
{
	if (m_unk0x0c) {
		m_next->m_prev = m_prev;
		m_prev->m_next = m_next;
	}
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void AmberLeaf0x10::VTable0x08()
{
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void AmberLeaf0x10::VTable0x0c()
{
}
