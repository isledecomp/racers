#include "golfonttable.h"

#include "decomp.h"
#include "golerror.h"
#include "golfont0xa0.h"
#include "golstring.h"

DECOMP_SIZE_ASSERT(GolFontTable, 0x2c)

// FUNCTION: GOLDP 0x10003fb0
GolFontTable::GolFontTable()
{
	m_fonts = NULL;
	m_unk0x18 = NULL;
	m_unk0x1c = NULL;
	m_unk0x20 = NULL;
}

// FUNCTION: GOLDP 0x10003ff0
GolFontTable::~GolFontTable()
{
	if (m_fonts != NULL) {
		delete[] m_fonts;
		m_fonts = NULL;
	}

	static_cast<CinderBasin0x28*>(this)->ReleaseDefinitionBuffers();
	CinderBasin0x28::Clear();
}

// FUNCTION: GOLDP 0x10004060
void GolFontTable::VTable0x0c()
{
	m_fonts = new GolFont0xa0[m_numItems];
	if (m_fonts == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x18 = new GolString[m_numItems];
	if (m_unk0x18 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x1c = new undefined2*[m_numItems];
	if (m_unk0x1c == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x20 = new LegoU16[m_numItems];
	if (m_unk0x20 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
}

// FUNCTION: GOLDP 0x100041f0
void GolFontTable::VTable0x10(undefined4 p_index)
{
	m_unk0x1c[p_index] = new undefined2[m_unk0x20[p_index] + 1];
	if (m_unk0x1c[p_index] == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
}

// FUNCTION: GOLDP 0x10004240
void GolFontTable::Clear()
{
	if (m_fonts != NULL) {
		delete[] m_fonts;
		m_fonts = NULL;
	}

	ReleaseDefinitionBuffers();
	CinderBasin0x28::Clear();
}

// FUNCTION: GOLDP 0x10004270
void GolFontTable::ReleaseDefinitionBuffers()
{
	if (m_unk0x18 != NULL) {
		delete[] m_unk0x18;
		m_unk0x18 = NULL;
	}

	if (m_unk0x1c != NULL) {
		for (LegoU32 i = 0; i < m_numItems; i++) {
			delete[] m_unk0x1c[i];
			m_unk0x1c[i] = NULL;
		}

		delete[] m_unk0x1c;
		m_unk0x1c = NULL;
	}

	if (m_unk0x20 != NULL) {
		delete[] m_unk0x20;
		m_unk0x20 = NULL;
	}
}

// FUNCTION: GOLDP 0x10004300
void* GolFontTable::VTable0x24(LegoU32 p_index)
{
	return &m_fonts[p_index];
}

// FUNCTION: GOLDP 0x10004320
void GolFontTable::ReleaseFontSurfaces()
{
	if (m_numItems > 0) {
		for (LegoU32 i = 0; i < m_numItems; i++) {
			if (m_fonts[i].HasLoadedData()) {
				m_fonts[i].ReleaseSurfaces();
			}
		}
	}
}

// FUNCTION: GOLDP 0x10004360
void GolFontTable::RefreshFontSurfaces()
{
	if (m_numItems > 0) {
		for (LegoU32 i = 0; i < m_numItems; i++) {
			if (m_fonts[i].HasLoadedData()) {
				m_fonts[i].RefreshSurfaces(m_renderer);
			}
		}
	}
}
