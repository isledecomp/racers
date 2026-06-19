#include "race/racestate.h"

extern const LegoFloat g_unk0x004b0cd4;

// GLOBAL: LEGORACERS 0x004b0d3c
extern const LegoFloat g_unk0x004b0d3c = 0.78539819f;

// GLOBAL: LEGORACERS 0x004b0d40
extern const LegoS32 g_raceStateField0x3e8MirrorEntryIndices[] = {3, 2, 1, 0};

// GLOBAL: LEGORACERS 0x004b0d50
extern const LegoS32 g_raceStateField0x3e8ContactEntryIndices0x4b0d50[] = {2, 3, 0, 1};

// GLOBAL: LEGORACERS 0x004b0d60
extern const LegoS32 g_raceStateField0x3e8ContactEntryIndices0x4b0d60[] = {1, 0, 3, 2};

// FUNCTION: LEGORACERS 0x00448840
void RaceState::Racer::Field0x3e8::FUN_00448840()
{
	if (m_unk0x64c > 0.0f) {
		LegoFloat value = m_unk0x64c / g_unk0x004b0cd4;
		if (value > 1.0f) {
			value = 1.0f;
		}

		m_unk0x67c = -(1.0f - value) * g_unk0x004b0d3c;
	}
	else if (m_unk0x64c < 0.0f) {
		LegoFloat value = -m_unk0x64c / g_unk0x004b0cd4;
		if (value > 1.0f) {
			value = 1.0f;
		}

		m_unk0x67c = (1.0f - value) * g_unk0x004b0d3c;
	}
	else {
		m_unk0x67c = 0.0f;
	}
}

// FUNCTION: LEGORACERS 0x004488e0
LegoU32 RaceState::Racer::Field0x3e8::FUN_004488e0(LegoS32 p_unk0x04)
{
	LegoU32 result = m_unk0x154;
	LegoU32 i = 0;
	if (result) {
		for (; i < result; i++) {
			if (m_unk0x140[i] == p_unk0x04) {
				return result;
			}
		}
	}

	if (result < sizeOfArray(m_unk0x140)) {
		m_unk0x140[result] = p_unk0x04;
		result = m_unk0x154 + 1;
		m_unk0x154 = result;
	}

	return result;
}

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

// FUNCTION: LEGORACERS 0x00448990
LegoFloat RaceState::Racer::Field0x3e8::FUN_00448990()
{
	LegoFloat result = 0.0f;
	Field0x198* entry = m_unk0x198;
	while (entry < &m_unk0x198[sizeOfArray(m_unk0x198)]) {
		result += entry->m_unk0x054;
		entry++;
	}

	return result * 0.25f;
}

// FUNCTION: LEGORACERS 0x004489c0
LegoFloat RaceState::Racer::Field0x3e8::FUN_004489c0()
{
	LegoFloat result = 0.0f;
	Field0x198* entry = m_unk0x198;
	while (entry < &m_unk0x198[sizeOfArray(m_unk0x198)]) {
		result += entry->m_unk0x058;
		entry++;
	}

	return result * 0.25f;
}

// FUNCTION: LEGORACERS 0x00448a50
void RaceState::Racer::Field0x3e8::FUN_00448a50()
{
	CollisionCacheRecord* entry = m_unk0x3f4;
	CollisionCacheRecord* end = &m_unk0x3f4[sizeOfArray(m_unk0x3f4)];
	while (entry < end) {
		entry->m_unk0x034++;
		entry++;
	}
}

// FUNCTION: LEGORACERS 0x00448a70
RaceState::Racer::Field0x3e8::CollisionCacheRecord* RaceState::Racer::Field0x3e8::FUN_00448a70(
	EventContext* p_unk0x04,
	EventRecord* p_unk0x08
)
{
	CollisionCacheRecord* result;
	LegoU32 count = m_unk0x5d4;
	if (count < sizeOfArray(m_unk0x3f4)) {
		result = &m_unk0x3f4[count];
		m_unk0x5d4 = count + 1;
	}
	else {
		CollisionCacheRecord* entry = m_unk0x3f4;
		CollisionCacheRecord* end = &m_unk0x3f4[sizeOfArray(m_unk0x3f4)];
		LegoU32 age = 0;
		result = entry;
		while (entry < end) {
			if (age < entry->m_unk0x034) {
				result = entry;
				age = entry->m_unk0x034;
			}

			entry++;
		}
	}

	result->m_unk0x000 = *p_unk0x04;
	result->m_unk0x038 = p_unk0x08;
	result->m_unk0x034 = 0;

	return result;
}

// FUNCTION: LEGORACERS 0x00448ae0
LegoBool32 RaceState::Racer::Field0x3e8::FUN_00448ae0(Field0x198* p_unk0x04)
{
	if (p_unk0x04->m_unk0x044 != NULL) {
		if (FUN_00448b80(p_unk0x04, p_unk0x04->m_unk0x044)) {
			p_unk0x04->m_unk0x044->m_unk0x034 = 0;
			p_unk0x04->m_unk0x03c = p_unk0x04->m_unk0x044->m_unk0x038;

			return TRUE;
		}
	}

	CollisionCacheRecord* entry = m_unk0x3f4;
	CollisionCacheRecord* end = &m_unk0x3f4[m_unk0x5d4];
	while (entry < end) {
		if (p_unk0x04->m_unk0x044 != entry && FUN_00448b80(p_unk0x04, entry)) {
			p_unk0x04->m_unk0x044 = entry;
			p_unk0x04->m_unk0x03c = entry->m_unk0x038;
			entry->m_unk0x034 = 0;

			return TRUE;
		}

		entry++;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00448b80
LegoBool32 RaceState::Racer::Field0x3e8::FUN_00448b80(Field0x198* p_unk0x04, CollisionCacheRecord* p_unk0x08)
{
	GolVec3 scaled;
	LegoFloat start = p_unk0x08->m_unk0x000.m_unk0x24.m_z * p_unk0x04->m_unk0x018.m_z;
	start += p_unk0x08->m_unk0x000.m_unk0x24.m_y * p_unk0x04->m_unk0x018.m_y;
	start += p_unk0x04->m_unk0x018.m_x * p_unk0x08->m_unk0x000.m_unk0x24.m_x;
	start += p_unk0x08->m_unk0x000.m_unk0x30;
	LegoFloat end = p_unk0x08->m_unk0x000.m_unk0x24.m_z * p_unk0x04->m_unk0x024.m_z;
	end += p_unk0x04->m_unk0x024.m_y * p_unk0x08->m_unk0x000.m_unk0x24.m_y;
	end += p_unk0x04->m_unk0x024.m_x * p_unk0x08->m_unk0x000.m_unk0x24.m_x;
	end += p_unk0x08->m_unk0x000.m_unk0x30;

	LegoBool32 startNonNegative = start >= 0.0f;
	LegoBool32 endNonNegative = end >= 0.0f;
	if (startNonNegative == endNonNegative) {
		return FALSE;
	}

	if (startNonNegative) {
		end = -end;
	}
	else {
		start = -start;
	}

	GolVec3* point = &p_unk0x04->m_unk0x030;
	point->m_x = p_unk0x04->m_unk0x024.m_x - p_unk0x04->m_unk0x018.m_x;
	point->m_y = p_unk0x04->m_unk0x024.m_y - p_unk0x04->m_unk0x018.m_y;
	point->m_z = p_unk0x04->m_unk0x024.m_z - p_unk0x04->m_unk0x018.m_z;

	LegoFloat amount = start / (start + end);
	scaled.m_x = amount * point->m_x;
	scaled.m_y = point->m_y;
	scaled.m_y *= amount;
	scaled.m_z = amount;
	scaled.m_z *= p_unk0x04->m_unk0x030.m_z;

	point->m_x = scaled.m_x + p_unk0x04->m_unk0x018.m_x;
	point->m_y = scaled.m_y + p_unk0x04->m_unk0x018.m_y;
	point->m_z = scaled.m_z + p_unk0x04->m_unk0x018.m_z;

	return GolMath::FUN_004497f0(point, p_unk0x08->m_unk0x000.GetFloatData());
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
