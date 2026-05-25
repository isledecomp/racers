#include "materialtable0x0c.h"

#include "decomp.h"
#include "duskwindbananarelic0x24.h"
#include "golerror.h"
#include "golname.h"
#include "whitefalcon0x140.h"

#include <string.h>

DECOMP_SIZE_ASSERT(MaterialTable0x0c, 0x0c)

// STUB: LEGORACERS 0x00410660
LegoS32 MaterialTable0x0c::FindEntryIndexByName(const LegoChar* p_name) const
{
	STUB(0x00410660);

	if (m_count == 0) {
		return -1;
	}

	for (LegoU32 i = 0; i < m_count; i++) {
		DuskwindBananaRelic0x24* material = static_cast<DuskwindBananaRelic0x24*>(m_entries[i]);
		if (material != NULL && ::strncmp(p_name, material->GetName(), sizeof(GolName)) == 0) {
			return i;
		}
	}

	return -1;
}

// STUB: LEGORACERS 0x004106d0
void* MaterialTable0x0c::AssignEntryByName(LegoS32 p_index, const LegoChar* p_name)
{
	STUB(0x004106d0);

	void* result = m_renderer->FindMaterialByName(p_name);
	m_entries[p_index] = result;
	if (m_entries[p_index] == NULL) {
		LegoChar message[64];
		::strncpy(message, p_name, sizeof(GolName));
		message[sizeof(GolName) - 1] = '\0';
		::strcat(message, ": Material assignment failed");
		GOL_FATALERROR_MESSAGE(message);
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00410750
void MaterialTable0x0c::SetPosition(LegoU32 p_index, void* p_position)
{
	m_entries[p_index] = p_position;
}
