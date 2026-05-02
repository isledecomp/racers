#include "amberhaze0x1c.h"

#include "bronzefalcon0xc8770.h"

DECOMP_SIZE_ASSERT(AmberHaze0x1c, 0x1c)

// FUNCTION: GOLDP 0x100261b0
AmberHaze0x1c::AmberHaze0x1c()
{
	m_renderer = NULL;
	m_next = NULL;
	m_unk0x14 = 0;
	m_numItems = 0;
}

// FUNCTION: GOLDP 0x100261f0
AmberHaze0x1c::~AmberHaze0x1c()
{
	m_numItems = 0;

	if (m_renderer != NULL) {
		m_renderer->RemoveMaterialList(this);
		m_renderer = NULL;
	}

	if (m_nameEntries != NULL) {
		GolNameTable::Clear();
	}
}

// STUB: GOLDP 0x10026270
void AmberHaze0x1c::VTable0x24(BronzeFalcon0xc8770*, const LegoChar*, LegoBool32)
{
	STUB(0x10026270);
}

// STUB: GOLDP 0x10026a00
void AmberHaze0x1c::VTable0x20(BronzeFalcon0xc8770*, undefined4, LegoU32)
{
	STUB(0x10026a00);
}

// FUNCTION: GOLDP 0x10026a50
void AmberHaze0x1c::Clear()
{
	m_numItems = 0;

	if (m_renderer != NULL) {
		m_renderer->RemoveMaterialList(this);
		m_renderer = NULL;
	}

	if (m_nameEntries != NULL) {
		GolNameTable::Clear();
	}
}

// STUB: GOLDP 0x10026a80
void AmberHaze0x1c::VTable0x1c(BronzeFalcon0xc8770*, LegoU32)
{
	STUB(0x10026a80);
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void AmberHaze0x1c::VTable0x0c()
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void AmberHaze0x1c::VTable0x10()
{
	// empty
}
