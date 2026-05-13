#include "peridottraceroot0x108.h"

#include "golerror.h"

#include <string.h>

DECOMP_SIZE_ASSERT(PeridotTraceRootEntry0x10, 0x10)
DECOMP_SIZE_ASSERT(PeridotTraceRootEntryDerived0x10, 0x10)
DECOMP_SIZE_ASSERT(PeridotTraceRootBase0x08, 0x08)
DECOMP_SIZE_ASSERT(PeridotTraceRoot0x108, 0x108)

// FUNCTION: LEGORACERS 0x00450eb0
PeridotTraceRoot0x108::PeridotTraceRoot0x108()
{
	m_directoryPath = NULL;
}

// FUNCTION: LEGORACERS 0x00450f10
PeridotTraceRootEntryDerived0x10::PeridotTraceRootEntryDerived0x10()
{
}

// FUNCTION: LEGORACERS 0x00450f60
PeridotTraceRoot0x108::~PeridotTraceRoot0x108()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x00450fc0
void PeridotTraceRoot0x108::FUN_00450fc0(const LegoChar* p_path)
{
	if (m_directoryPath) {
		Clear();
	}

	m_directoryPath = new LegoChar[::strlen(p_path) + 1];
	if (!m_directoryPath) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	::strcpy(m_directoryPath, p_path);

	LegoU32 i = 0;
	for (; i < sizeOfArray(m_entries); i++) {
		m_entries[i].FUN_00451130(this, i);
	}
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

// FUNCTION: LEGORACERS 0x004510a0
PeridotTraceRootEntry0x10::PeridotTraceRootEntry0x10()
{
	m_root = NULL;
	m_index = 0;
}

// STUB: LEGORACERS 0x004510e0
PeridotTraceRootEntry0x10::~PeridotTraceRootEntry0x10()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00451130
void PeridotTraceRootEntry0x10::FUN_00451130(PeridotTraceRoot0x108* p_root, LegoU32 p_index)
{
	m_root = p_root;
	m_index = p_index;
	VTable0x04();
}

// FUNCTION: LEGORACERS 0x00451150
void PeridotTraceRootEntry0x10::Reset()
{
	m_root = NULL;
	m_index = 0;
}

// STUB: LEGORACERS 0x00451160
undefined4 PeridotTraceRootEntry0x10::VTable0x04()
{
	STUB(0x00451160);
	return 0;
}

// STUB: LEGORACERS 0x004511c0
undefined4 PeridotTraceRootEntry0x10::VTable0x08()
{
	STUB(0x004511c0);
	return 0;
}

// STUB: LEGORACERS 0x00451200
undefined4 PeridotTraceRootEntry0x10::VTable0x0c(undefined4)
{
	STUB(0x00451200);
	return 0;
}

// STUB: LEGORACERS 0x00451240
undefined4 PeridotTraceRootEntry0x10::VTable0x14(undefined4)
{
	STUB(0x00451240);
	return 0;
}
