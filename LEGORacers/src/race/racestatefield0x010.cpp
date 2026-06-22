#include "race/racesessionfield0x27f4.h"

#include <math.h>

// FUNCTION: LEGORACERS 0x0041eaf0
void RaceSessionField0x27f4::FUN_0041eaf0(GolVec3* p_position, LegoFloat p_distance, Entry* p_entry)
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
			*p_position = target;
		}
		else {
			GolVec3 step;
			step.m_x = target.m_x - p_position->m_x;
			step.m_y = target.m_y - p_position->m_y;
			step.m_z = target.m_z - p_position->m_z;

			step.m_x /= distance;
			step.m_y /= distance;
			step.m_z /= distance;

			p_position->m_x += step.m_x * p_distance;
			p_position->m_y += step.m_y * p_distance;
			p_position->m_z += step.m_z * p_distance;
			p_distance = 0.0f;
		}

		p_entry = &m_entries[p_entry->m_unk0x20.m_items[0]];
	}
}
