#include "surface/gold3dtexturepalette.h"

#include "decomp.h"

DECOMP_SIZE_ASSERT(GolD3DTexturePalette, 0x10)

#include "golerror.h"

#include <string.h>

// GLOBAL: GOLDP 0x10063558
GolSurfaceFormat GolD3DTexturePalette::g_textureFormat;

// FUNCTION: GOLDP 0x100146c0
GolD3DTexturePalette::GolD3DTexturePalette()
{
	m_mappedEntries = NULL;
}

// FUNCTION: GOLDP 0x10014700
GolD3DTexturePalette::~GolD3DTexturePalette()
{
	Destroy();
}

// FUNCTION: GOLDP 0x10014770
void GolD3DTexturePalette::Initialize(const GolSurfaceFormat& p_textureFormat)
{
	if (m_entries != NULL) {
		if (m_mappedEntries != NULL) {
			delete m_mappedEntries;
			m_mappedEntries = NULL;
		}

		Shutdown();
	}

	GolTexturePalette::Initialize(p_textureFormat);

	m_mappedEntries = new LegoU16[m_size];
	if (m_mappedEntries == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	memset(m_mappedEntries, 0, m_size * sizeof(*m_mappedEntries));
}

// FUNCTION: GOLDP 0x100147f0
void GolD3DTexturePalette::Destroy()
{
	if (m_mappedEntries != NULL) {
		delete m_mappedEntries;
		m_mappedEntries = NULL;
	}
	Shutdown();
}

// FUNCTION: GOLDP 0x10014820
void GolD3DTexturePalette::SetEntries(ColorRGBA* p_entries, LegoU32 p_start, LegoU32 p_count)
{
	GolTexturePalette::SetEntries(p_entries, p_start, p_count);

	for (LegoU32 i = 0; i < p_count; i++) {
		m_mappedEntries[p_start + i] = g_textureFormat.MapRGBA(p_entries[i]);
	}
}

// FUNCTION: GOLDP 0x10014870
void GolD3DTexturePalette::CopyEntriesFrom(GolPaletteBase* p_source)
{
	LegoU32 i;
	ColorRGBA entry;

	GolTexturePalette::CopyEntriesFrom(p_source);

	for (i = 0; i < m_size; i++) {
		p_source->GetEntry(&entry, i);
		m_mappedEntries[i] = g_textureFormat.MapRGBA(entry);
	}
}

// FUNCTION: GOLDP 0x100148c0
void GolD3DTexturePalette::SetTextureFormat(const GolSurfaceFormat& p_format)
{
	g_textureFormat = p_format;
}
