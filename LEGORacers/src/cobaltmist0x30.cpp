#include "cobaltmist0x30.h"

#include "types.h"

DECOMP_SIZE_ASSERT(ListLink, 0x08)
DECOMP_SIZE_ASSERT(ListHead, 0x0c)
DECOMP_SIZE_ASSERT(CobaltMist0x30, 0x30)

// STUB: LEGORACERS 0x418f20
void CobaltMist0x30::VTable0x28(undefined4)
{
	// TODO
	STUB(0x418f20);
}

// STUB: LEGORACERS 0x41bd00
CobaltMist0x30::~CobaltMist0x30()
{
}

// FUNCTION: LEGORACERS 0x41bd50
undefined4 CobaltMist0x30::VTable0x04(undefined4)
{
	VTable0x08();
	return 1;
}

// FUNCTION: LEGORACERS 0x41bd60
void CobaltMist0x30::VTable0x08()
{
	while (TRUE) {
		if (!m_unk0x18.m_first->m_prev || !m_unk0x18.m_first) {
			break;
		}

		VTable0x18((CrimsonRay0x20*) m_unk0x18.m_first);
	}

	while (TRUE) {
		if (!m_unk0x24.m_first->m_prev || !m_unk0x24.m_first) {
			break;
		}

		VTable0x20((EmberDust0x28*) m_unk0x24.m_first);
	}

	while (m_unk0x0c) {
		VTable0x28(m_unk0x0c);
	}

	while (m_unk0x08) {
		VTable0x28(m_unk0x08);
	}
}

// STUB: LEGORACERS 0x41bdd0
void CobaltMist0x30::VTable0x14()
{
	// TODO
	STUB(0x41bdd0);
}

// FUNCTION: LEGORACERS 0x41be50
void CobaltMist0x30::VTable0x18(CrimsonRay0x20* p_node)
{
	p_node->m_next->m_prev = p_node->m_prev;
	p_node->m_prev->m_next = p_node->m_next;
	delete p_node;
}

// STUB: LEGORACERS 0x41be80
void CobaltMist0x30::VTable0x1c()
{
	// TODO
	STUB(0x41be80);
}

// FUNCTION: LEGORACERS 0x41bf00
void CobaltMist0x30::VTable0x20(EmberDust0x28* p_node)
{
	p_node->m_next->m_prev = p_node->m_prev;
	p_node->m_prev->m_next = p_node->m_next;
	delete p_node;
}

// STUB: LEGORACERS 0x41bf30
void CobaltMist0x30::VTable0x24()
{
	// TODO
	STUB(0x41bf30);
}

// FUNCTION: LEGORACERS 0x4164c0 FOLDED
void CobaltMist0x30::VTable0x0c()
{
}

// FUNCTION: LEGORACERS 0x4164c0 FOLDED
void CobaltMist0x30::VTable0x10()
{
}
