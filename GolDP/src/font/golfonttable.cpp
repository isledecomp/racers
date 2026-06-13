#include "font/golfonttable.h"

#include "decomp.h"
#include "font/golfont.h"
#include "golerror.h"
#include "golstring.h"

DECOMP_SIZE_ASSERT(GolFontTable, 0x2c)

// FUNCTION: GOLDP 0x10003fb0
GolFontTable::GolFontTable()
{
	m_fonts = NULL;
	m_charStrings = NULL;
	m_charCodes = NULL;
	m_charCounts = NULL;
}

// FUNCTION: GOLDP 0x10003ff0
GolFontTable::~GolFontTable()
{
	if (m_fonts != NULL) {
		delete[] m_fonts;
		m_fonts = NULL;
	}

	static_cast<GolFontLibrary*>(this)->ReleaseDefinitionBuffers();
	GolFontLibrary::Clear();
}

// FUNCTION: GOLDP 0x10004060
void GolFontTable::AllocateItems()
{
	m_fonts = new GolFont[m_numItems];
	if (m_fonts == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_charStrings = new GolString[m_numItems];
	if (m_charStrings == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_charCodes = new undefined2*[m_numItems];
	if (m_charCodes == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_charCounts = new LegoU16[m_numItems];
	if (m_charCounts == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
}

// FUNCTION: GOLDP 0x100041f0
void GolFontTable::AllocateDefinitionBuffer(undefined4 p_index)
{
	m_charCodes[p_index] = new undefined2[m_charCounts[p_index] + 1];
	if (m_charCodes[p_index] == NULL) {
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
	GolFontLibrary::Clear();
}

// FUNCTION: GOLDP 0x10004270
void GolFontTable::ReleaseDefinitionBuffers()
{
	if (m_charStrings != NULL) {
		delete[] m_charStrings;
		m_charStrings = NULL;
	}

	if (m_charCodes != NULL) {
		for (LegoU32 i = 0; i < m_numItems; i++) {
			delete[] m_charCodes[i];
			m_charCodes[i] = NULL;
		}

		delete[] m_charCodes;
		m_charCodes = NULL;
	}

	if (m_charCounts != NULL) {
		delete[] m_charCounts;
		m_charCounts = NULL;
	}
}

// FUNCTION: GOLDP 0x10004300
GolFontBase* GolFontTable::GetItem(LegoU32 p_index)
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
