#include "race/racestate.h"

// FUNCTION: LEGORACERS 0x00448930
void RaceState::Racer::Field0x3e8::FUN_00448930(LegoS32 p_unk0x04)
{
	LegoU32 count = m_unk0x154;
	LegoU32 index = 0;
	if (count > 0) {
		for (; index < count; index++) {
			if (m_unk0x140[index] == p_unk0x04) {
				LegoU32 nextIndex = index + 1;
				if (nextIndex < count) {
					LegoS32* entry = &m_unk0x140[nextIndex - 1];
					do {
						nextIndex++;
						*entry = entry[1];
						entry++;
					} while (nextIndex < m_unk0x154);
				}

				m_unk0x154--;
				return;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00448c70
void RaceState::Racer::Field0x3e8::FUN_00448c70()
{
	GolOrientedEntity* entity = &m_unk0x0e4;
	Field0x198* points = m_unk0x198;
	GolVec3* anchor = &points[1].m_unk0x00c;
	entity->VTable0x2c(m_unk0x358, anchor);

	GolVec3 lengthOffset;
	entity->GetOrientationRow0(&lengthOffset);
	LegoFloat lengthScale = m_unk0x368;
	LegoFloat lengthY = lengthOffset.m_y;
	lengthOffset.m_x *= lengthScale;
	lengthOffset.m_y = lengthY * lengthScale;
	lengthOffset.m_z *= lengthScale;

	GolVec3 widthOffset;
	entity->GetUnk0x34(&widthOffset);
	LegoFloat widthScale = m_unk0x364;
	LegoFloat widthY = widthOffset.m_y;
	widthOffset.m_x *= widthScale;
	widthOffset.m_y = widthY * widthScale;
	widthOffset.m_z *= widthScale;

	points[0].m_unk0x00c.m_x = anchor->m_x - widthOffset.m_x;
	points[0].m_unk0x00c.m_y = anchor->m_y - widthOffset.m_y;
	points[0].m_unk0x00c.m_z = anchor->m_z - widthOffset.m_z;

	points[3].m_unk0x00c.m_x = anchor->m_x - lengthOffset.m_x;
	points[3].m_unk0x00c.m_y = anchor->m_y - lengthOffset.m_y;
	points[3].m_unk0x00c.m_z = anchor->m_z - lengthOffset.m_z;

	points[2].m_unk0x00c.m_x = points[0].m_unk0x00c.m_x - lengthOffset.m_x;
	points[2].m_unk0x00c.m_y = points[0].m_unk0x00c.m_y - lengthOffset.m_y;
	points[2].m_unk0x00c.m_z = points[0].m_unk0x00c.m_z - lengthOffset.m_z;
}
