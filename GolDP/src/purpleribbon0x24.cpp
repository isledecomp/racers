#include "purpleribbon0x24.h"

#include "bronzefalcon0xc8770.h"
#include "golerror.h"
#include "purpledune0x7c.h"

DECOMP_SIZE_ASSERT(PurpleRibbon0x24, 0x24)

// FUNCTION: GOLDP 10015920
PurpleRibbon0x24::PurpleRibbon0x24()
{
	m_items = NULL;
}

// FUNCTION: GOLDP 0x10015940
PurpleRibbon0x24::~PurpleRibbon0x24()
{
	Clear();
}

// FUNCTION: GOLDP 0x100159b0
void PurpleRibbon0x24::AllocateItems()
{
	if (GetItemCount() >= 1) {
		m_items = new PurpleDune0x7c[GetItemCount()];
		if (m_items == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}
}

// FUNCTION: GOLDP 0x10015a50
void PurpleRibbon0x24::VTable0x0c()
{
	LegoU32 i;
	if (m_renderer != NULL) {
		for (i = 0; i < GetItemCount(); i++) {
			if (m_items[i].GetPixelFlags() & SilverDune0x30::c_lockRequestRead) {
				m_items[i].FUN_10016380();
			}
		}
	}
}

// FUNCTION: GOLDP 0x10015a90
void PurpleRibbon0x24::VTable0x10()
{
	LegoU32 i;
	if (m_renderer != NULL) {
		for (i = 0; i < GetItemCount(); i++) {
			if (m_items[i].GetPixelFlags() & SilverDune0x30::c_lockRequestRead) {
				m_items[i].FUN_10016440(*m_renderer);
			}
		}
	}
}

// FUNCTION: GOLDP 0x10015ad0
void PurpleRibbon0x24::Clear()
{
	if (m_items != NULL) {
		delete[] m_items;
		m_items = NULL;
	}
	MagentaRibbon0x20::Clear();
}

// FUNCTION: GOLDP 0x10015af0
GoldDune0x38* PurpleRibbon0x24::GetItem(LegoU32 p_index)
{
	return &m_items[p_index];
}

// FUNCTION: GOLDP 0x10015b10
void PurpleRibbon0x24::VTable0x18(
	LegoU32 p_index,
	const GolSurfaceFormat& p_textureFormat,
	LegoU32 p_width,
	LegoU32 p_height
)
{
	m_items[p_index].VTable0x34(*m_renderer, p_textureFormat, p_width, p_height);
}
