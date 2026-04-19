#include "cobaltmist0x30.h"

#include "types.h"

DECOMP_SIZE_ASSERT(GolListLink, 0x08)
DECOMP_SIZE_ASSERT(GolListHead, 0x0c)
DECOMP_SIZE_ASSERT(CobaltMist0x30, 0x30)

// FUNCTION: LEGORACERS 0x00418f20 FOLDED
void CobaltMist0x30::VTable0x28(SoundNode* p_node)
{
	VTable0x30(p_node);
	RemoveNode(p_node);
	delete p_node;
}

// FUNCTION: LEGORACERS 0x0041bca0
CobaltMist0x30::CobaltMist0x30()
{
}

// FUNCTION: LEGORACERS 0x0041bd00
CobaltMist0x30::~CobaltMist0x30()
{
	Shutdown();
}

// FUNCTION: LEGORACERS 0x0041bd50
undefined4 CobaltMist0x30::VTable0x04(undefined4)
{
	Shutdown();
	return 1;
}

// FUNCTION: LEGORACERS 0x0041bd60
void CobaltMist0x30::Shutdown()
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

// FUNCTION: LEGORACERS 0x0041bdd0
CrimsonRay0x20* CobaltMist0x30::VTable0x14()
{
	CrimsonRay0x20* node = new CrimsonRay0x20();

	if (node) {
		node->SetUnk0x10(this);

		GolListLink* link = node;
		link->m_prev = m_unk0x18.m_first;
		link->m_next = (GolListLink*) &m_unk0x18.m_first;
		m_unk0x18.m_first->m_next = link;
		m_unk0x18.m_first = link;
	}

	return node;
}

// FUNCTION: LEGORACERS 0x0041be50 FOLDED
void CobaltMist0x30::VTable0x18(CrimsonRay0x20* p_node)
{
	p_node->m_next->m_prev = p_node->m_prev;
	p_node->m_prev->m_next = p_node->m_next;
	delete p_node;
}

// FUNCTION: LEGORACERS 0x0041be80
EmberDust0x28* CobaltMist0x30::VTable0x1c()
{
	EmberDust0x28* node = new EmberDust0x28();

	if (node) {
		node->SetUnk0x0c(this);

		GolListLink* link = node;
		link->m_prev = m_unk0x24.m_first;
		link->m_next = (GolListLink*) &m_unk0x24.m_first;
		m_unk0x24.m_first->m_next = link;
		m_unk0x24.m_first = link;
	}

	return node;
}

// FUNCTION: LEGORACERS 0x0041bf00
void CobaltMist0x30::VTable0x20(EmberDust0x28* p_node)
{
	p_node->m_next->m_prev = p_node->m_prev;
	p_node->m_prev->m_next = p_node->m_next;
	delete p_node;
}

// FUNCTION: LEGORACERS 0x0041bf30
SoundNode* CobaltMist0x30::VTable0x24()
{
	SoundNode* node = new SoundNode();

	if (node) {
		AddNode(node);
	}

	return node;
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void CobaltMist0x30::VTable0x0c()
{
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void CobaltMist0x30::VTable0x10()
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void CobaltMist0x30::VTable0x34(undefined4)
{
}
