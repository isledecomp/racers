#include "amberwolf0x98.h"

#include "crimsonray0x20.h"
#include "emberdust0x28.h"
#include "frostpetal0x34.h"
#include "goldenoak0x128.h"
#include "silvernode0x50.h"
#include "types.h"

DECOMP_SIZE_ASSERT(AmberWolf0x98, 0x98)

// FUNCTION: LEGORACERS 0x004185d0
AmberWolf0x98::AmberWolf0x98()
{
	m_unk0x28 = 2;
	m_unk0x34 = 2;
	m_unk0x20 = 0;
	m_unk0x1c = 0;
	m_unk0x24 = NULL;
	m_unk0x2c = 0;
	m_unk0x30 = NULL;
	m_unk0x38 = 22050;
	m_unk0x35 = 16;
	m_unk0x18 = 0;
	m_unk0x58 = 0;
	m_unk0x54 = 0;
}

// FUNCTION: LEGORACERS 0x004186a0
AmberWolf0x98::~AmberWolf0x98()
{
	VTable0x08();
}

// STUB: LEGORACERS 0x004186f0
undefined4 AmberWolf0x98::VTable0x04(undefined4)
{
	// TODO
	STUB(0x4186f0);
	return 0;
}

// FUNCTION: LEGORACERS 0x004188b0
void AmberWolf0x98::VTable0x08()
{
	while (TRUE) {
		if (!m_unk0x3c.m_first->m_prev || !m_unk0x3c.m_first) {
			break;
		}

		VTable0x18((CrimsonRay0x20*) m_unk0x3c.m_first);
	}

	while (TRUE) {
		if (!m_unk0x48.m_first->m_prev || !m_unk0x48.m_first) {
			break;
		}

		VTable0x20((EmberDust0x28*) m_unk0x48.m_first);
	}

	while (m_unk0x0c) {
		VTable0x28(m_unk0x0c);
	}

	while (m_unk0x08) {
		VTable0x28(m_unk0x08);
	}

	if (m_unk0x30) {
		m_unk0x30->Release();
		m_unk0x30 = NULL;
	}

	if (m_unk0x24) {
		m_unk0x24->Release();
		m_unk0x24 = NULL;
	}

	m_unk0x58 = 0;
	m_unk0x54 = 0;
}

// STUB: LEGORACERS 0x00418940
void AmberWolf0x98::VTable0x34(undefined4)
{
	STUB(0x418940);
}

// STUB: LEGORACERS 0x00418cc0
void AmberWolf0x98::VTable0x0c()
{
	STUB(0x418cc0);
}

// FUNCTION: LEGORACERS 0x00418d60
void AmberWolf0x98::VTable0x10()
{
	if (m_unk0x24) {
		m_unk0x18 = 0;
		VTable0x34(0);
	}
}

// FUNCTION: LEGORACERS 0x00418d80
CrimsonRay0x20* AmberWolf0x98::VTable0x14()
{
	GoldenOak0x128* node = new GoldenOak0x128();

	if (node) {
		node->SetUnk0x10(this);

		GolListLink* link = node;
		link->m_prev = m_unk0x3c.m_first;
		link->m_next = (GolListLink*) &m_unk0x3c.m_first;
		m_unk0x3c.m_first->m_next = link;
		m_unk0x3c.m_first = link;
	}

	// TODO: GoldenOak0x128 does not inherit from CrimsonRay0x20
	return (CrimsonRay0x20*) node;
}

// FUNCTION: LEGORACERS 0x00418e00
EmberDust0x28* AmberWolf0x98::VTable0x1c()
{
	FrostPetal0x34* node = new FrostPetal0x34();

	if (node) {
		node->SetUnk0x0c(this);

		GolListLink* link = node;
		link->m_prev = m_unk0x48.m_first;
		link->m_next = (GolListLink*) &m_unk0x48.m_first;
		m_unk0x48.m_first->m_next = link;
		m_unk0x48.m_first = link;
	}

	// TODO: FrostPetal0x34 does not inherit from EmberDust0x28
	return (EmberDust0x28*) node;
}

// STUB: LEGORACERS 0x00418e80
void AmberWolf0x98::VTable0x20(EmberDust0x28* p_node)
{
	STUB(0x418e80);
}

// FUNCTION: LEGORACERS 0x00418eb0
SilverNode0x50* AmberWolf0x98::VTable0x24()
{
	SilverNode0x50* node = new SilverNode0x50();

	if (node) {
		FUN_00417ab0(node);
	}

	return node;
}

// FUNCTION: LEGORACERS 0x00418f20 FOLDED
void AmberWolf0x98::VTable0x28(SilverNode0x50* p_node)
{
	VTable0x30(p_node);
	FUN_00417ae0(p_node);
	delete p_node;
}

// FUNCTION: LEGORACERS 0x0041be50 FOLDED
void AmberWolf0x98::VTable0x18(CrimsonRay0x20* p_node)
{
	p_node->m_next->m_prev = p_node->m_prev;
	p_node->m_prev->m_next = p_node->m_next;
	delete p_node;
}
