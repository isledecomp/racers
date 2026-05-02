#include "peridottraceroot0x108.h"

DECOMP_SIZE_ASSERT(PeridotTraceRootEntry0x10, 0x10)
DECOMP_SIZE_ASSERT(PeridotTraceRootBase0x08, 0x08)
DECOMP_SIZE_ASSERT(PeridotTraceRoot0x108, 0x108)

// FUNCTION: LEGORACERS 0x00450eb0
PeridotTraceRoot0x108::PeridotTraceRoot0x108()
{
	m_directoryPath = NULL;
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
	Clear();
}

// FUNCTION: LEGORACERS 0x00451040
void PeridotTraceRoot0x108::Clear()
{
	if (m_directoryPath) {
		delete[] m_directoryPath;
		m_directoryPath = NULL;
	}

	PeridotTraceRootEntry0x10* entry = m_entries;
	for (LegoS32 i = 0; i < sizeOfArray(m_entries); i++, entry++) {
		entry->Reset();
	}
}

// FUNCTION: LEGORACERS 0x00451080 FOLDED
LegoU32 PeridotTraceRoot0x108::GetEntryCount()
{
	return 16;
}

// FUNCTION: LEGORACERS 0x00451090
PeridotTraceRootEntry0x10* PeridotTraceRoot0x108::GetEntry(LegoU32 p_index)
{
	return &m_entries[p_index];
}

// FUNCTION: LEGORACERS 0x00451150
void PeridotTraceRootEntry0x10::Reset()
{
	m_root = NULL;
	m_index = 0;
}
