#include "material/golimagedefinitionlist.h"

#include "golerror.h"
#include "render/gold3drenderdevice.h"

DECOMP_SIZE_ASSERT(GolImageDefinitionList, 0x20)

// FUNCTION: GOLDP 0x10005d10
GolImageDefinitionList::GolImageDefinitionList()
{
	m_items = NULL;
}

// FUNCTION: GOLDP 0x10005d50
GolImageDefinitionList::~GolImageDefinitionList()
{
	if (m_items) {
		delete[] m_items;
		m_items = NULL;
	}

	GolImageList::Clear();
}

// FUNCTION: GOLDP 0x10005dc0
void GolImageDefinitionList::AllocateItems()
{
	m_items = new GolImage[m_numItems];
	if (m_items == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
}

// FUNCTION: GOLDP 0x10005ec0
void GolImageDefinitionList::Clear()
{
	if (m_items) {
		delete[] m_items;
		m_items = NULL;
	}

	GolImageList::Clear();
}

// FUNCTION: GOLDP 0x10005ef0
GolImage* GolImageDefinitionList::GetItem(undefined4 p_index)
{
	return &m_items[p_index];
}

// FUNCTION: GOLDP 0x10005f10
void GolImageDefinitionList::VTable0x10()
{
	LegoU32 i;

	if (m_numItems > 0) {
		for (i = 0; i < m_numItems; i++) {
			if (m_items[i].m_unk0x3c & 1) {
				m_items[i].FUN_100051c0();
			}
		}
	}
}

// FUNCTION: GOLDP 0x10005f50
void GolImageDefinitionList::VTable0x14()
{
	LegoU32 i;

	if (m_numItems > 0) {
		for (i = 0; i < m_numItems; i++) {
			if (m_items[i].m_unk0x3c & 1) {
				m_items[i].FUN_10005210();
			}
		}
	}
}
