#include "gdbmodelindexarraybase.h"

DECOMP_SIZE_ASSERT(GdbModelIndexArrayBase, 0x8)

// FUNCTION: GOLDP 0x1001d7d0
GdbModelIndexArrayBase::GdbModelIndexArrayBase()
{
	m_count = 0;
}

// FUNCTION: GOLDP 0x1001d810
GdbModelIndexArrayBase::~GdbModelIndexArrayBase()
{
	VTable0x08();
}

// FUNCTION: GOLDP 0x1001d820
void GdbModelIndexArrayBase::VTable0x08()
{
	m_count = 0;
}
