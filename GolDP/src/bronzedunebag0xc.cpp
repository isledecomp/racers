#include "bronzedunebag0xc.h"

#include "decomp.h"

// FUNCTION: GOLDP 0x1002a090
BronzeDuneBag0xc::BronzeDuneBag0xc()
{
	m_entries = NULL;
	m_size = 0;
}

// FUNCTION: GOLDP 0x1002a0f0
BronzeDuneBag0xc::~BronzeDuneBag0xc()
{
	m_size = 0;
	if (m_entries != NULL) {
		delete[] m_entries;
		m_entries = NULL;
	}
}

// STUB: GOLDP 0x1002a120
void BronzeDuneBag0xc::FUN_1002a120(undefined4*)
{
	// TODO
	STUB(0x1002a120);
}

// FUNCTION: GOLDP 0x1002a1b0
void BronzeDuneBag0xc::FUN_1002a1b0()
{
	m_size = 0;
	if (m_entries != NULL) {
		delete[] m_entries;
		m_entries = NULL;
	}
}

// FUNCTION: GOLDP 0x1002a1e0
void BronzeDuneBag0xc::GetEntries(PALETTEENTRY* p_entries, LegoU32 p_start, LegoU32 p_count)
{
	for (LegoU32 i = 0; i < p_count; i++) {
		p_entries[i].peRed = m_entries[p_start + i].peRed;
		p_entries[i].peGreen = m_entries[p_start + i].peGreen;
		p_entries[i].peBlue = m_entries[p_start + i].peBlue;
		p_entries[i].peFlags = m_entries[p_start + i].peFlags;
	}
}

// FUNCTION: GOLDP 0x1002a230
void BronzeDuneBag0xc::SetEntries(PALETTEENTRY* p_entries, LegoU32 p_start, LegoU32 p_count)
{
	for (LegoU32 i = 0; i < p_count; i++) {
		m_entries[p_start + i].peRed = p_entries[i].peRed;
		m_entries[p_start + i].peGreen = p_entries[i].peGreen;
		m_entries[p_start + i].peBlue = p_entries[i].peBlue;
		m_entries[p_start + i].peFlags = p_entries[i].peFlags;
	}
}

// FUNCTION: GOLDP 0x1002a290
void BronzeDuneBag0xc::GetEntry(PALETTEENTRY* p_entry, LegoU32 p_index)
{
	p_entry->peRed = m_entries[p_index].peRed;
	p_entry->peGreen = m_entries[p_index].peGreen;
	p_entry->peBlue = m_entries[p_index].peBlue;
	p_entry->peFlags = m_entries[p_index].peFlags;
}

// FUNCTION: GOLDP 0x1002a2d0
void BronzeDuneBag0xc::CopyEntriesFrom(IPalette0x4* p_source)
{
	p_source->GetEntries(m_entries, 0, p_source->GetEntryCount());
}

// FUNCTION: GOLDP 0x1002a300
LegoS32 BronzeDuneBag0xc::FindEntry(PALETTEENTRY* p_entry)
{
	LegoU32 i;

	for (i = 0; i < m_size; i++) {
		if (m_entries[i].peRed == p_entry->peRed && m_entries[i].peGreen == p_entry->peGreen &&
			m_entries[i].peBlue == p_entry->peBlue && m_entries[i].peFlags == p_entry->peFlags) {
			return i;
		}
	}
	return -1;
}

// STUB: GOLDP 0x100016f0 FOLDED
LegoU32 BronzeDuneBag0xc::GetFirstEntry()
{
	MATCHING(0x100016f0);
	return 0;
}

// STUB: GOLDP 0x1002a350 FOLDED
LegoU32 BronzeDuneBag0xc::GetEntryCount()
{
	return m_size;
}

// STUB: GOLDP 0x1002a350 FOLDED
LegoU32 BronzeDuneBag0xc::GetPaletteSize()
{
	return m_size;
}
