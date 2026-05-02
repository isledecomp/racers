#include "magentaribbon0x20.h"

#include "bronzefalcon0xc8770.h"

DECOMP_SIZE_ASSERT(MagentaRibbon0x20, 0x20)

// FUNCTION: GOLDP 0x1002b4d0
MagentaRibbon0x20::MagentaRibbon0x20()
{
	m_renderer = NULL;
	m_next = NULL;
	m_unk0x14 = 0;
	m_numItems = 0;
	m_unk0x18 = 0;
}

// FUNCTION: GOLDP 0x1002b520
MagentaRibbon0x20::~MagentaRibbon0x20()
{
	m_numItems = 0;

	if (m_renderer != NULL) {
		m_renderer->RemoveTextureList(this);
		m_renderer = NULL;
	}

	if (m_nameEntries != NULL) {
		GolNameTable::Clear();
	}
}

// STUB: GOLDP 0x1002b5a0
void MagentaRibbon0x20::VTable0x24(BronzeFalcon0xc8770*, const LegoChar*, LegoBool32)
{
	STUB(0x1002b5a0);
}

// STUB: GOLDP 0x1002ba30
void MagentaRibbon0x20::VTable0x20(BronzeFalcon0xc8770*, undefined4, LegoU32)
{
	STUB(0x1002ba30);
}

// STUB: GOLDP 0x1002ba80
void MagentaRibbon0x20::VTable0x1c(BronzeFalcon0xc8770*, LegoU32)
{
	STUB(0x1002ba80);
}

// FUNCTION: GOLDP 0x1002bac0
void MagentaRibbon0x20::Clear()
{
	m_numItems = 0;

	if (m_renderer != NULL) {
		m_renderer->RemoveTextureList(this);
		m_renderer = NULL;
	}

	if (m_nameEntries != NULL) {
		GolNameTable::Clear();
	}
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void MagentaRibbon0x20::VTable0x0c()
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void MagentaRibbon0x20::VTable0x10()
{
	// empty
}
