#include "goltexturepalette.h"

#include "decomp.h"
#include "golerror.h"

DECOMP_SIZE_ASSERT(GolTexturePalette, 0x0c)

// FUNCTION: GOLDP 0x1002a090
// FUNCTION: LEGORACERS 0x004133e0
GolTexturePalette::GolTexturePalette()
{
	m_entries = NULL;
	m_size = 0;
}

// FUNCTION: GOLDP 0x1002a0f0
// FUNCTION: LEGORACERS 0x00413420
GolTexturePalette::~GolTexturePalette()
{
	Shutdown();
}

// FUNCTION: GOLDP 0x1002a120
// FUNCTION: LEGORACERS 0x00413430
void GolTexturePalette::Initialize(const GolSurfaceFormat& p_textureFormat)
{
	LegoU32 i;

	if (m_entries != NULL) {
		Shutdown();
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
// FUNCTION: LEGORACERS 0x004134b0
void GolTexturePalette::Shutdown()
{
	m_size = 0;
	if (m_entries != NULL) {
		delete[] m_entries;
		m_entries = NULL;
	}
}

// FUNCTION: GOLDP 0x1002a1e0
// FUNCTION: LEGORACERS 0x004134e0
void GolTexturePalette::GetEntries(ColorRGBA* p_entries, LegoU32 p_start, LegoU32 p_count)
{
	for (LegoU32 i = 0; i < p_count; i++) {
		p_entries[i].m_red = m_entries[p_start + i].m_red;
		p_entries[i].m_grn = m_entries[p_start + i].m_grn;
		p_entries[i].m_blu = m_entries[p_start + i].m_blu;
		p_entries[i].m_alp = m_entries[p_start + i].m_alp;
	}
}

// FUNCTION: GOLDP 0x1002a230
// FUNCTION: LEGORACERS 0x00413530
void GolTexturePalette::SetEntries(ColorRGBA* p_entries, LegoU32 p_start, LegoU32 p_count)
{
	for (LegoU32 i = 0; i < p_count; i++) {
		m_entries[p_start].m_red = p_entries[i].m_red;
		m_entries[p_start].m_grn = p_entries[i].m_grn;
		m_entries[p_start].m_blu = p_entries[i].m_blu;
		m_entries[p_start].m_alp = p_entries[i].m_alp;
		p_start++;
	}
}

// FUNCTION: GOLDP 0x1002a290
// FUNCTION: LEGORACERS 0x00413590
void GolTexturePalette::GetEntry(ColorRGBA* p_entry, LegoU32 p_index)
{
	p_entry->m_red = m_entries[p_index].m_red;
	p_entry->m_grn = m_entries[p_index].m_grn;
	p_entry->m_blu = m_entries[p_index].m_blu;
	p_entry->m_alp = m_entries[p_index].m_alp;
}

// FUNCTION: GOLDP 0x1002a2d0
// FUNCTION: LEGORACERS 0x004135d0
void GolTexturePalette::CopyEntriesFrom(GolPaletteBase* p_source)
{
	p_source->GetEntries(m_entries, 0, p_source->GetEntryCount());
}

// FUNCTION: GOLDP 0x1002a300
// FUNCTION: LEGORACERS 0x00413600
LegoS32 GolTexturePalette::FindEntry(const ColorRGBA& p_entry)
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

// FUNCTION: GOLDP 0x100016f0 FOLDED
// FUNCTION: LEGORACERS 0x0044e7e0 FOLDED
LegoU32 GolTexturePalette::GetFirstEntry()
{
	return 0;
}

// FUNCTION: GOLDP 0x1002a350 FOLDED
// FUNCTION: LEGORACERS 0x00413650 FOLDED
LegoU32 GolTexturePalette::GetEntryCount()
{
	return m_size;
}

// FUNCTION: GOLDP 0x1002a350 FOLDED
// FUNCTION: LEGORACERS 0x00413650 FOLDED
LegoU32 GolTexturePalette::GetPaletteSize()
{
	return m_size;
}
