#include "race/racestate.h"

#include <float.h>

DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x00c::Entry, 0x48)

// FUNCTION: LEGORACERS 0x0043d070
RaceState::Racer::Field0x00c::Entry* RaceState::Racer::Field0x00c::FUN_0043d070(Racer* p_racer)
{
	LegoFloat nearestDistanceSquared = FLT_MAX;
	Entry* result = NULL;

	GolVec3 racerPosition;
	p_racer->m_unk0x018.m_unk0x044->VTable0x04(&racerPosition);

	Entry* entry = m_entries;
	for (LegoS32 i = 6; i; i--) {
		if (entry->m_unk0x004) {
			GolVec3 position = entry->m_unk0x024;
			LegoFloat deltaX = position.m_x - racerPosition.m_x;
			LegoFloat deltaY = position.m_y - racerPosition.m_y;
			LegoFloat deltaZ = position.m_z - racerPosition.m_z;
			LegoFloat distanceSquared = deltaZ * deltaZ + deltaY * deltaY + deltaX * deltaX;

			if (distanceSquared < nearestDistanceSquared) {
				nearestDistanceSquared = distanceSquared;
				result = entry;
			}
		}

		entry++;
	}

	return result;
}
