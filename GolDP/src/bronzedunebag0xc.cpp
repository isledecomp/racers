#include "bronzedunebag0xc.h"

#include "decomp.h"
#include "golerror.h"

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

// FUNCTION: GOLDP 0x1002a120
void BronzeDuneBag0xc::FUN_1002a120(const GolSurfaceFormat& p_textureFormat)
{
	LegoU32 i;
	if (m_entries != NULL) {
		m_size = 0;
		delete[] m_entries;
		m_entries = 0;
	}
	m_size = 1 << p_textureFormat.m_bitsPerPixel;
	m_entries = new ColorRGBA[m_size];
	if (m_entries == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	for (i = 0; i < m_size; i++) {
		m_entries[i].m_red = 0;
		m_entries[i].m_grn = 0;
		m_entries[i].m_blu = 0;
		m_entries[i].m_alp = 0;
	}
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
void BronzeDuneBag0xc::GetEntries(ColorRGBA* p_entries, LegoU32 p_start, LegoU32 p_count)
{
	for (LegoU32 i = 0; i < p_count; i++) {
		p_entries[i].m_red = m_entries[p_start + i].m_red;
		p_entries[i].m_grn = m_entries[p_start + i].m_grn;
		p_entries[i].m_blu = m_entries[p_start + i].m_blu;
		p_entries[i].m_alp = m_entries[p_start + i].m_alp;
	}
}

// FUNCTION: GOLDP 0x1002a230
void BronzeDuneBag0xc::SetEntries(ColorRGBA* p_entries, LegoU32 p_start, LegoU32 p_count)
{
	for (LegoU32 i = 0; i < p_count; i++) {
		m_entries[p_start + i].m_red = p_entries[i].m_red;
		m_entries[p_start + i].m_grn = p_entries[i].m_grn;
		m_entries[p_start + i].m_blu = p_entries[i].m_blu;
		m_entries[p_start + i].m_alp = p_entries[i].m_alp;
	}
}

// FUNCTION: GOLDP 0x1002a290
void BronzeDuneBag0xc::GetEntry(ColorRGBA* p_entry, LegoU32 p_index)
{
	p_entry->m_red = m_entries[p_index].m_red;
	p_entry->m_grn = m_entries[p_index].m_grn;
	p_entry->m_blu = m_entries[p_index].m_blu;
	p_entry->m_alp = m_entries[p_index].m_alp;
}

// FUNCTION: GOLDP 0x1002a2d0
void BronzeDuneBag0xc::CopyEntriesFrom(IPalette0x4* p_source)
{
	p_source->GetEntries(m_entries, 0, p_source->GetEntryCount());
}

// FUNCTION: GOLDP 0x1002a300
LegoS32 BronzeDuneBag0xc::FindEntry(const ColorRGBA& p_entry)
{
	LegoU32 i;

	for (i = 0; i < m_size; i++) {
		if (m_entries[i].m_red == p_entry.m_red && m_entries[i].m_grn == p_entry.m_grn &&
			m_entries[i].m_blu == p_entry.m_blu && m_entries[i].m_alp == p_entry.m_alp) {
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
