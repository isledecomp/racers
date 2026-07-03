#include "golerror.h"
#include "scene/golbillboard.h"

#include <string.h>

// FUNCTION: LEGORACERS 0x004a00b0 FOLDED
// FUNCTION: GOLDP 0x10025de0 FOLDED
GolBillboard::ManagedMaterialTable::ManagedMaterialTable()
{
	m_renderer = NULL;
	m_count = 0;
	m_entries = NULL;
}

// FUNCTION: LEGORACERS 0x004105c0 FOLDED
// FUNCTION: GOLDP 0x100260d0 FOLDED
GolBillboard::ManagedMaterialTable::~ManagedMaterialTable()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x004105d0 FOLDED
// FUNCTION: GOLDP 0x10025df0 FOLDED
void GolBillboard::ManagedMaterialTable::Initialize(GolRenderDevice* p_renderer, LegoU32 p_count)
{
	if (m_renderer != NULL) {
		Clear();
	}

	m_renderer = p_renderer;
	m_count = p_count;
	m_entries = new void*[p_count];
	if (m_entries == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	::memset(m_entries, 0, sizeof(*m_entries) * m_count);
}

// FUNCTION: LEGORACERS 0x00410630 FOLDED
// FUNCTION: GOLDP 0x100260d0 FOLDED
void GolBillboard::ManagedMaterialTable::Clear()
{
	if (m_entries != NULL) {
		delete[] m_entries;
		m_entries = NULL;
	}

	m_renderer = NULL;
	m_count = 0;
}
