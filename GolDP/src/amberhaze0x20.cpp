#include "amberhaze0x20.h"

#include "duskwindbananarelic0x30.h"
#include "golerror.h"

// FUNCTION: GOLDP 0x10006680
AmberHaze0x20::AmberHaze0x20()
{
	m_items = NULL;
}

// FUNCTION: GOLDP 0x100066a0
AmberHaze0x20::~AmberHaze0x20()
{
	Clear();
}

// FUNCTION: GOLDP 0x10006710
void AmberHaze0x20::VTable0x14()
{
	m_items = new DuskwindBananaRelic0x30[m_numItems];
	if (m_items == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
}

// FUNCTION: GOLDP 0x100067a0
void AmberHaze0x20::VTable0x0c()
{
	LegoU32 i;

	for (i = 0; i < m_numItems; i++) {
		m_items[i].Destroy();
	}
}

// STUB: GOLDP 0x100067d0
void AmberHaze0x20::VTable0x10()
{
	FUN_10026970();
}

// FUNCTION: GOLDP 0x100067e0
void AmberHaze0x20::Clear()
{
	if (m_items != NULL) {
		delete[] m_items;
		m_items = NULL;
	}
	AmberHaze0x1c::Clear();
}

// FUNCTION: GOLDP 0x10006800
DuskwindBananaRelic0x24* AmberHaze0x20::VTable0x28(LegoU32 p_index) const
{
	return &m_items[p_index];
}

// FUNCTION: GOLDP 0x10006820
void AmberHaze0x20::VTable0x18(LegoU32 p_index)
{
	m_items[p_index].FUN_10006320(*m_renderer);
}
