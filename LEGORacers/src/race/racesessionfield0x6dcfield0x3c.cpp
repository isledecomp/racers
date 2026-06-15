#include "decomp.h"
#include "race/racesession.h"

// FUNCTION: LEGORACERS 0x00443c10
void RaceSession::Field0x6dc::Field0x3c::FUN_00443c10(Resource* p_resource)
{
	if (m_unk0x00 != 0) {
		Resource* resource = p_resource->VTable0x10();
		resource->VTable0x24(p_resource);
	}
}
