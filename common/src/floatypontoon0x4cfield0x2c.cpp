#include "duskwindbananarelic0x24.h"
#include "floatypontoon0x4c.h"
#include "golerror.h"
#include "whitefalcon0x140.h"

#include <string.h>

DECOMP_SIZE_ASSERT(MaterialTable0x0c, 0x0c)

// FUNCTION: LEGORACERS 0x004a00b0 FOLDED
// FUNCTION: GOLDP 0x10025de0 FOLDED
FloatyPontoon0x4c::Field0x2c::Field0x2c()
{
	m_renderer = NULL;
	m_count = 0;
	m_entries = NULL;
}

// FUNCTION: LEGORACERS 0x004105c0 FOLDED
// FUNCTION: GOLDP 0x100260d0 FOLDED
FloatyPontoon0x4c::Field0x2c::~Field0x2c()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x004105d0
// FUNCTION: GOLDP 0x10025df0 FOLDED
void FloatyPontoon0x4c::Field0x2c::Initialize(WhiteFalcon0x140* p_renderer, LegoU32 p_count)
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

// FUNCTION: LEGORACERS 0x00410630
// FUNCTION: GOLDP 0x100260d0 FOLDED
void FloatyPontoon0x4c::Field0x2c::Clear()
{
	if (m_entries != NULL) {
		delete[] m_entries;
		m_entries = NULL;
	}

	m_renderer = NULL;
	m_count = 0;
}

// STUB: LEGORACERS 0x00410660
LegoS32 FloatyPontoon0x4c::Field0x2c::FindEntryIndexByName(const LegoChar* p_name) const
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
void* FloatyPontoon0x4c::Field0x2c::AssignEntryByName(LegoS32 p_index, const LegoChar* p_name)
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
void FloatyPontoon0x4c::Field0x2c::SetPosition(LegoU32 p_index, void* p_position)
{
	m_entries[p_index] = p_position;
}
