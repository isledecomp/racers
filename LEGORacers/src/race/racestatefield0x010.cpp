#include "race/racestate.h"

#include <math.h>

DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x010, 0x08)

// FUNCTION: LEGORACERS 0x0041e940 FOLDED
RaceState::Racer::Field0xcc4* RaceState::Racer::Field0x010::FUN_0041e940(LegoU32 p_unk0x04)
{
	return &m_entries[p_unk0x04];
}

// STUB: LEGORACERS 0x0041eaf0
void RaceState::Racer::Field0x010::FUN_0041eaf0(GolVec3* p_position, LegoFloat p_distance, Field0xcc4* p_entry)
{
	if (m_count == 0) {
		return;
	}

	if (p_entry == NULL) {
		p_entry = m_entries;
	}

	while (p_distance > 0.0f) {
		GolVec3 target = p_entry->m_unk0x10;

		LegoFloat deltaX = p_position->m_x - target.m_x;
		LegoFloat deltaY = p_position->m_y - target.m_y;
		LegoFloat deltaZ = p_position->m_z - target.m_z;

		LegoFloat distance = static_cast<LegoFloat>(sqrt(deltaZ * deltaZ + deltaY * deltaY + deltaX * deltaX));
		if (distance < p_distance) {
			p_distance -= distance;
			p_position->m_x = target.m_x;
			p_position->m_y = target.m_y;
			p_position->m_z = target.m_z;
		}
		else {
			deltaX = target.m_x - p_position->m_x;
			deltaY = target.m_y - p_position->m_y;
			deltaZ = target.m_z - p_position->m_z;

			deltaX /= distance;
			deltaY /= distance;
			deltaZ /= distance;

			p_position->m_x += deltaX * p_distance;
			p_position->m_y += deltaY * p_distance;
			p_position->m_z += deltaZ * p_distance;
			p_distance = 0.0f;
		}

		p_entry = &m_entries[p_entry->m_unk0x20[0]];
	}
}
