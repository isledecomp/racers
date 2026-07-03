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
	m_items = new GolImage[m_itemCount];
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
void GolImageDefinitionList::ReleaseImages()
{
	LegoU32 i;

	if (m_itemCount > 0) {
		for (i = 0; i < m_itemCount; i++) {
			if (m_items[i].m_stateFlags & GolImage::c_stateCreated) {
				m_items[i].DestroyTiles();
			}
		}
	}
}

// FUNCTION: GOLDP 0x10005f50
void GolImageDefinitionList::RestoreImages()
{
	LegoU32 i;

	if (m_itemCount > 0) {
		for (i = 0; i < m_itemCount; i++) {
			if (m_items[i].m_stateFlags & GolImage::c_stateCreated) {
				m_items[i].RebuildTiles();
			}
		}
	}
}
