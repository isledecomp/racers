#include "material/golsoftwaremateriallibrary.h"

#include "golerror.h"
#include "material/golsoftwarematerial.h"

// FUNCTION: GOLDP 0x10006680
GolSoftwareMaterialLibrary::GolSoftwareMaterialLibrary()
{
	m_items = NULL;
}

// FUNCTION: GOLDP 0x100066a0
GolSoftwareMaterialLibrary::~GolSoftwareMaterialLibrary()
{
	Clear();
}

// FUNCTION: GOLDP 0x10006710
void GolSoftwareMaterialLibrary::AllocateItems()
{
	m_items = new GolSoftwareMaterial[m_numItems];
	if (m_items == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
}

// FUNCTION: GOLDP 0x100067a0
void GolSoftwareMaterialLibrary::VTable0x0c()
{
	LegoU32 i;

	for (i = 0; i < m_numItems; i++) {
		m_items[i].Destroy();
	}
}

// FUNCTION: GOLDP 0x100067d0
void GolSoftwareMaterialLibrary::VTable0x10()
{
	FUN_10026970();
}

// FUNCTION: GOLDP 0x100067e0
void GolSoftwareMaterialLibrary::Clear()
{
	if (m_items != NULL) {
		delete[] m_items;
		m_items = NULL;
	}

	GolMaterialLibrary::Clear();
}

// FUNCTION: GOLDP 0x10006800
GolMaterial* GolSoftwareMaterialLibrary::GetItem(LegoU32 p_index) const
{
	return &m_items[p_index];
}

// FUNCTION: GOLDP 0x10006820
void GolSoftwareMaterialLibrary::VTable0x18(LegoU32 p_index)
{
	m_items[p_index].FUN_10006320(*m_renderer);
}
