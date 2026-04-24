#include "peridottraceroot0x108.h"

DECOMP_SIZE_ASSERT(PeridotTraceRootEntry0x10, 0x10)
DECOMP_SIZE_ASSERT(PeridotTraceRootBase0x08, 0x08)
DECOMP_SIZE_ASSERT(PeridotTraceRoot0x108, 0x108)

// FUNCTION: LEGORACERS 0x00450eb0
PeridotTraceRoot0x108::PeridotTraceRoot0x108()
{
	m_unk0x04 = NULL;
}

// STUB: LEGORACERS 0x00450f10
PeridotTraceRootEntry0x10::PeridotTraceRootEntry0x10()
{
	// TODO
	STUB(0x450f10);
}

// STUB: LEGORACERS 0x00450f30
PeridotTraceRootEntry0x10::~PeridotTraceRootEntry0x10()
{
	// TODO
	STUB(0x450f30);
}

// FUNCTION: LEGORACERS 0x00450f60
PeridotTraceRoot0x108::~PeridotTraceRoot0x108()
{
	VTable0x00();
}

// STUB: LEGORACERS 0x00451040
void PeridotTraceRoot0x108::VTable0x00()
{
	// TODO
	STUB(0x451040);
}

// FUNCTION: LEGORACERS 0x00451080 FOLDED
LegoU32 PeridotTraceRoot0x108::VTable0x04()
{
	return 16;
}

// FUNCTION: LEGORACERS 0x00451090
PeridotTraceRootEntry0x10* PeridotTraceRoot0x108::VTable0x08(LegoU32 p_index)
{
	return &m_unk0x08[p_index];
}

// STUB: LEGORACERS 0x00451150
void PeridotTraceRootEntry0x10::FUN_00451150()
{
	// TODO
	STUB(0x451150);
}
