#include "crimsonray0x20.h"

#include "types.h"

DECOMP_SIZE_ASSERT(OpalStar0x20, 0x20)
DECOMP_SIZE_ASSERT(CrimsonRay0x20, 0x20)

// FUNCTION: LEGORACERS 0x41a9d0 FOLDED
void CrimsonRay0x20::VTable0x14(AmberLeaf0x10* p_node)
{
	delete p_node;
}

// FUNCTION: LEGORACERS 0x41a9f0 FOLDED
void* CrimsonRay0x20::VTable0x18()
{
	return m_unk0x10;
}

// FUNCTION: LEGORACERS 0x41c010
CrimsonRay0x20::CrimsonRay0x20()
{
	m_unk0x10 = NULL;
}

// FUNCTION: LEGORACERS 0x41c070
CrimsonRay0x20::~CrimsonRay0x20()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x41c0c0
ListLink* CrimsonRay0x20::VTable0x04(undefined4)
{
	return VTable0x08();
}

// FUNCTION: LEGORACERS 0x41c0d0
ListLink* CrimsonRay0x20::VTable0x08()
{
	ListLink* result;

	while (TRUE) {
		result = m_unk0x14.m_first;

		if (!result->m_prev || !result) {
			break;
		}

		VTable0x14((AmberLeaf0x10*) result);
	}

	m_unk0x04 = 0;
	return result;
}

// FUNCTION: LEGORACERS 0x41c100
AmberLeaf0x10* CrimsonRay0x20::VTable0x10(undefined4)
{
	AmberLeaf0x10* node = new AmberLeaf0x10();

	if (node) {
		node->SetUnk0x0c(this);

		ListLink* link = node;
		link->m_prev = m_unk0x14.m_first;
		link->m_next = (ListLink*) &m_unk0x14.m_first;
		m_unk0x14.m_first->m_next = link;
		m_unk0x14.m_first = link;
	}

	return node;
}

// FUNCTION: LEGORACERS 0x44a1e0 FOLDED
undefined4 CrimsonRay0x20::VTable0x0c()
{
	return 1;
}
