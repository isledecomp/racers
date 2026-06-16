#include "race/raceresourcemanager.h"

DECOMP_SIZE_ASSERT(RaceResourceManager, 0x04)
DECOMP_SIZE_ASSERT(RaceResourceManager::Resource, 0x04)

// FUNCTION: LEGORACERS 0x00443c10
void RaceResourceManager::FUN_00443c10(Resource* p_resource)
{
	if (m_soundManager != NULL) {
		Resource* resource = p_resource->VTable0x10();
		resource->VTable0x24(p_resource);
	}
}
