#include "pearldew0x0c.h"

#include "golerror.h"

#include <stdio.h>

DECOMP_SIZE_ASSERT(PearlDew0x0c, 0x0c)

// GLOBAL: GOLDP 0x10063150
PALETTEENTRY g_paletteEntries[256];

// FUNCTION: GOLDP 0x10007190
PearlDew0x0c::PearlDew0x0c()
{
	m_palette = 0;
	m_firstEntry = 0;
	m_entryCount = 0;
}

// FUNCTION: GOLDP 0x100071b0
PearlDew0x0c::~PearlDew0x0c()
{
	if (m_palette) {
		m_palette->Release();
		m_palette = 0;
	}
	m_firstEntry = 0;
	m_entryCount = 0;
}

// FUNCTION: GOLDP 0x100073f0
void PearlDew0x0c::Release()
{
	if (m_palette) {
		m_palette->Release();
		m_palette = 0;
	}

	m_firstEntry = 0;
	m_entryCount = 0;
}

// FUNCTION: GOLDP 0x10007420
void PearlDew0x0c::GetEntries(PALETTEENTRY* p_entries, LegoU32 p_start, LegoU32 p_count)
{
	LegoChar buffer[128];

	if (p_start < m_firstEntry) {
		p_entries->peRed = 0;
		p_entries->peGreen = 0;
		p_entries->peBlue = 0;
		p_entries->peFlags = 0;
		p_count += p_start - m_firstEntry;
		p_start = m_firstEntry;
	}

	if (p_start + p_count >= (LegoU32) (m_firstEntry + m_entryCount)) {
		p_count--;
		p_entries[p_count].peRed = 0xff;
		p_entries[p_count].peGreen = 0xff;
		p_entries[p_count].peBlue = 0xff;
		p_entries[p_count].peFlags = 0xff;
	}

	if (p_count) {
		HRESULT result = m_palette->GetEntries(0, p_start, p_count, g_paletteEntries);
		if (result) {
			::sprintf(buffer, "Unable to get palette entries\nerror number = %x", result);
			GOL_FATALERROR_MESSAGE(buffer);
		}

		for (LegoU32 i = 0; i < p_count; i++) {
			p_entries[i].peRed = g_paletteEntries[i].peRed;
			p_entries[i].peGreen = g_paletteEntries[i].peGreen;
			p_entries[i].peBlue = g_paletteEntries[i].peBlue;
		}
	}
}

// FUNCTION: GOLDP 0x10007500
void PearlDew0x0c::SetEntries(PALETTEENTRY* p_entries, LegoU32 p_start, LegoU32 p_count)
{
	LegoChar buffer[128];

	for (LegoU32 i = 0; i < p_count; i++) {
		g_paletteEntries[i].peRed = p_entries[i].peRed;
		g_paletteEntries[i].peGreen = p_entries[i].peGreen;
		g_paletteEntries[i].peBlue = p_entries[i].peBlue;
		g_paletteEntries[i].peFlags = PC_NOCOLLAPSE;
	}

	HRESULT result = m_palette->SetEntries(0, p_start, p_count, g_paletteEntries);
	if (result) {
		::sprintf(buffer, "Unable to set palette entries\nerror number = %x", result);
		GOL_FATALERROR_MESSAGE(buffer);
	}
}

// FUNCTION: GOLDP 0x100075b0
void PearlDew0x0c::GetEntry(PALETTEENTRY* p_entry, LegoU32 p_index)
{
	PALETTEENTRY entry;
	LegoChar buffer[128];

	HRESULT result = m_palette->GetEntries(0, p_index, 1, &entry);
	if (result) {
		::sprintf(buffer, "Unable to get palette entries\nerror number = %x", result);
		GOL_FATALERROR_MESSAGE(buffer);
	}

	p_entry->peRed = entry.peRed;
	p_entry->peGreen = entry.peGreen;
	p_entry->peBlue = entry.peBlue;
	p_entry->peFlags = 0xff;
}

// FUNCTION: GOLDP 0x10007620
void PearlDew0x0c::CopyEntriesFrom(PearlDew0x0c* p_source)
{
	PALETTEENTRY entry;
	LegoChar buffer[128];

	m_entryCount = p_source->GetEntryCount();
	for (LegoU32 i = 0; i < m_entryCount; i++) {
		p_source->GetEntry(&entry, i);
		g_paletteEntries[i].peRed = entry.peRed;
		g_paletteEntries[i].peGreen = entry.peGreen;
		g_paletteEntries[i].peBlue = entry.peBlue;
		g_paletteEntries[i].peFlags = PC_NOCOLLAPSE;
	}

	HRESULT result = m_palette->SetEntries(0, 0, m_entryCount, g_paletteEntries);
	if (result) {
		::sprintf(buffer, "Unable to set palette entries\nerror number = %x", result);
		GOL_FATALERROR_MESSAGE(buffer);
	}
}

// FUNCTION: GOLDP 0x100076d0
LegoS32 PearlDew0x0c::FindEntry(PALETTEENTRY* p_entry)
{
	DWORD caps;
	LegoChar buffer[128];

	HRESULT result = m_palette->GetCaps(&caps);
	if (result) {
		::sprintf(buffer, "Unable to get palette caps\nerror number = %x", result);
		GOL_FATALERROR_MESSAGE(buffer);
	}

	LegoU32 entryCount;
	if (caps & DDPCAPS_8BIT) {
		entryCount = 0x100;
	}
	else if (caps & DDPCAPS_4BIT) {
		entryCount = 0x10;
	}
	else {
		entryCount = (caps & DDPCAPS_2BIT) ? 4 : 2;
	}

	result = m_palette->GetEntries(0, 0, entryCount, g_paletteEntries);
	if (result) {
		::sprintf(buffer, "Unable to get palette entries\nerror number = %x", result);
		GOL_FATALERROR_MESSAGE(buffer);
	}

	for (LegoU32 i = 0; i < entryCount; i++) {
		if (g_paletteEntries[i].peRed == p_entry->peRed && g_paletteEntries[i].peGreen == p_entry->peGreen &&
			g_paletteEntries[i].peBlue == p_entry->peBlue) {
			return i;
		}
	}

	return -1;
}

// FUNCTION: GOLDP 0x100077b0
LegoU32 PearlDew0x0c::GetFirstEntry()
{
	return m_firstEntry;
}

// FUNCTION: GOLDP 0x100077c0
LegoU32 PearlDew0x0c::GetEntryCount()
{
	return m_entryCount;
}

// FUNCTION: GOLDP 0x100077d0
LegoU32 PearlDew0x0c::GetPaletteSize()
{
	if (m_entryCount == 0xfe) {
		return 0x100;
	}
	return m_entryCount;
}

// STUB: GOLDP 0x100077f0
void PearlDew0x0c::Set332PaletteEntries()
{
	LegoChar buffer[128];

	if (m_entryCount > 0x10) {
		LegoU32 red = 0;
		LegoU8* redEntries = &g_paletteEntries[0].peGreen;
		do {
			LegoU32 green = 0;
			LegoU8 redValue = red;
			redValue <<= 3;
			redValue |= red;
			redValue <<= 2;
			redValue |= red >> 1;

			LegoU8* greenEntries = redEntries;
			redEntries += 0x80;
			do {
				LegoU8 greenValue = green;
				greenValue <<= 3;
				greenValue |= green;
				greenValue <<= 2;
				greenValue |= green >> 1;

				LegoU8* entry = greenEntries;
				greenEntries += 0x10;
				LegoU32 blue = 0;
				do {
					entry[-1] = redValue;
					LegoU8 blueValue = blue;
					blueValue <<= 2;
					blueValue |= blue;
					entry[0] = greenValue;
					blueValue <<= 2;
					blueValue |= blue;
					entry += sizeof(PALETTEENTRY);
					blueValue <<= 2;
					blueValue |= blue;
					entry[-3] = blueValue;
					entry[-2] = PC_NOCOLLAPSE;
					blue++;
				} while (blue < 4);

				green++;
			} while (green < 8);

			red++;
		} while (red < 8);

		HRESULT result = m_palette->SetEntries(0, 0, 0x100, g_paletteEntries);
		if (result) {
			::sprintf(buffer, "Unable to set 332 palette entries\nerror number = %x", result);
			GOL_FATALERROR_MESSAGE(buffer);
		}
	}
}
