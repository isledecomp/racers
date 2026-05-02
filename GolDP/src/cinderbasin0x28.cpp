#include "cinderbasin0x28.h"

#include "bronzefalcon0xc8770.h"

DECOMP_SIZE_ASSERT(CinderBasin0x28, 0x28)

// FUNCTION: GOLDP 0x1001d830
CinderBasin0x28::CinderBasin0x28()
{
	m_renderer = NULL;
	m_numItems = 0;
	m_unk0x24 = 0;
}

// FUNCTION: GOLDP 0x1001d870
CinderBasin0x28::~CinderBasin0x28()
{
	m_numItems = 0;

	if (m_renderer != NULL) {
		m_renderer->RemoveFontList(this);
		m_renderer = NULL;
	}

	if (m_nameEntries != NULL) {
		GolNameTable::Clear();
	}
}

// STUB: GOLDP 0x1001d8f0
void CinderBasin0x28::VTable0x20(BronzeFalcon0xc8770*, const LegoChar*, LegoBool32)
{
	STUB(0x1001d8f0);
}

// FUNCTION: GOLDP 0x1001ddf0
void CinderBasin0x28::Clear()
{
	m_numItems = 0;

	if (m_renderer != NULL) {
		m_renderer->RemoveFontList(this);
		m_renderer = NULL;
	}

	if (m_nameEntries != NULL) {
		GolNameTable::Clear();
	}
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void CinderBasin0x28::ReleaseFontSurfaces()
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void CinderBasin0x28::RefreshFontSurfaces()
{
	// empty
}
