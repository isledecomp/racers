#include "amberwolf0x98.h"

#include "crimsonray0x20.h"
#include "silvernode0x50.h"
#include "types.h"

DECOMP_SIZE_ASSERT(AmberWolf0x98, 0x98)

// FUNCTION: LEGORACERS 0x4186a0
AmberWolf0x98::~AmberWolf0x98()
{
	VTable0x08();
}

// STUB: LEGORACERS 0x4186f0
undefined4 AmberWolf0x98::VTable0x04(undefined4)
{
	// TODO
	STUB(0x4186f0);
	return 0;
}

// STUB: LEGORACERS 0x4188b0
void AmberWolf0x98::VTable0x08()
{
	// TODO
	STUB(0x4188b0);
}

// STUB: LEGORACERS 0x418940
void AmberWolf0x98::VTable0x34(undefined4)
{
	STUB(0x418940);
}

// STUB: LEGORACERS 0x418cc0
void AmberWolf0x98::VTable0x0c()
{
	STUB(0x418cc0);
}

// FUNCTION: LEGORACERS 0x418d60
void AmberWolf0x98::VTable0x10()
{
	if (m_unk0x24) {
		m_unk0x18 = 0;
		VTable0x34(0);
	}
}

// STUB: LEGORACERS 0x418d80
CrimsonRay0x20* AmberWolf0x98::VTable0x14()
{
	STUB(0x418d80);
	return NULL;
}

// STUB: LEGORACERS 0x418e00
EmberDust0x28* AmberWolf0x98::VTable0x1c()
{
	STUB(0x418e00);
	return NULL;
}

// STUB: LEGORACERS 0x418e80
void AmberWolf0x98::VTable0x20(EmberDust0x28* p_node)
{
	STUB(0x418e80);
}

// FUNCTION: LEGORACERS 0x418eb0
SilverNode0x50* AmberWolf0x98::VTable0x24()
{
	SilverNode0x50* node = new SilverNode0x50();

	if (node) {
		FUN_00417ab0(node);
	}

	return node;
}

// STUB: LEGORACERS 0x418f20 FOLDED
void AmberWolf0x98::VTable0x28(SilverNode0x50*)
{
	STUB(0x418f20);
}

// FUNCTION: LEGORACERS 0x41be50 FOLDED
void AmberWolf0x98::VTable0x18(CrimsonRay0x20* p_node)
{
	p_node->m_next->m_prev = p_node->m_prev;
	p_node->m_prev->m_next = p_node->m_next;
	delete p_node;
}
