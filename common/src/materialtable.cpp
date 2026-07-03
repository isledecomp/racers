#include "material/materialtable.h"

#include "decomp.h"
#include "golerror.h"
#include "golmaterial.h"
#include "golname.h"
#include "render/golrenderdevice.h"

#include <string.h>

DECOMP_SIZE_ASSERT(MaterialTable, 0x0c)

// FUNCTION: GOLDP 0x10025de0 FOLDED
// FUNCTION: LEGORACERS 0x004a00b0 FOLDED
MaterialTable* MaterialTable::Reset()
{
	m_renderer = NULL;
	m_count = 0;
	m_entries = NULL;

	return this;
}

// FUNCTION: LEGORACERS 0x004105c0 FOLDED
// FUNCTION: GOLDP 0x100260d0 FOLDED
void MaterialTable::Destroy()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x004105d0 FOLDED
// FUNCTION: GOLDP 0x10025df0 FOLDED
void MaterialTable::Initialize(GolRenderDevice* p_renderer, LegoU32 p_count)
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
void MaterialTable::Clear()
{
	if (m_entries != NULL) {
		delete[] m_entries;
		m_entries = NULL;
	}

	m_renderer = NULL;
	m_count = 0;
}

// FUNCTION: LEGORACERS 0x00410660
LegoS32 MaterialTable::FindEntryIndexByName(const LegoChar* p_name) const
{
	LegoS32 index = 0;
	if (m_count <= 0) {
		return -1;
	}

	while (TRUE) {
		GolMaterial* material = static_cast<GolMaterial*>(m_entries[index]);
		if (material != NULL) {
			GolMaterial::NameRecord materialName;
			materialName = material->GetNameRecord();
			if (::strncmp(p_name, materialName.m_name, sizeof(GolName)) == 0) {
				break;
			}
		}

		if (++index >= m_count) {
			return -1;
		}
	}

	return index;
}

// FUNCTION: LEGORACERS 0x004106d0
void MaterialTable::AssignEntryByName(LegoS32 p_index, const LegoChar* p_name)
{
	m_entries[p_index] = m_renderer->FindMaterialByName(p_name);
	if (m_entries[p_index] == NULL) {
		LegoChar message[64];
		::strncpy(message, p_name, sizeof(GolName));
		message[sizeof(GolName) - 1] = '\0';
		::strcat(message, ": Material assignment failed");
		GOL_FATALERROR_MESSAGE(message);
	}
}

// FUNCTION: LEGORACERS 0x00410750
void MaterialTable::SetEntry(LegoU32 p_index, void* p_entry)
{
	m_entries[p_index] = p_entry;
}
