#include "race/racestate.h"

#include <float.h>

DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x00c, 0x2a0)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x00c::Entry, 0x48)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x00c::StandingsDeltaEntry, 0x0c)

// FUNCTION: LEGORACERS 0x0043c910
RaceState::Racer* RaceState::Racer::Field0x00c::FUN_0043c910(
	GolVec3* p_unk0x04,
	GolVec3* p_unk0x08,
	LegoFloat p_unk0x0c,
	LegoFloat p_unk0x10,
	LegoFloat p_unk0x14
)
{
	LegoFloat farthestDistanceSquared = 0.0f;
	LegoS32 resultIndex = -1;

	for (LegoS32 i = 0; i < static_cast<LegoS32>(m_racerCount); i++) {
		Racer* racer = &m_racers[i];
		Racer::Field0x018* racerField = &racer->m_unk0x018;

		GolVec3 position;
		racerField->m_unk0x044->VTable0x04(&position);

		LegoFloat distanceSquared = (position.m_x - p_unk0x04->m_x) * (position.m_x - p_unk0x04->m_x) +
									(position.m_y - p_unk0x04->m_y) * (position.m_y - p_unk0x04->m_y) +
									(position.m_z - p_unk0x04->m_z) * (position.m_z - p_unk0x04->m_z);
		if (distanceSquared >= p_unk0x0c && distanceSquared <= p_unk0x10) {
			GolVec3 delta;
			delta.m_x = position.m_x - p_unk0x04->m_x;
			delta.m_y = position.m_y - p_unk0x04->m_y;
			delta.m_z = position.m_z - p_unk0x04->m_z;
			GolMath::NormalizeVector3(delta, &delta);

			if (GOLVECTOR3_DOT(*p_unk0x08, delta) >= p_unk0x14 && distanceSquared > farthestDistanceSquared) {
				resultIndex = i;
				farthestDistanceSquared = distanceSquared;
			}
		}
	}

	if (resultIndex < 0) {
		return NULL;
	}

	return &m_racers[resultIndex];
}

// STUB: LEGORACERS 0x0043ca60
RaceState::Racer* RaceState::Racer::Field0x00c::FUN_0043ca60(
	GolVec3* p_unk0x04,
	GolVec3* p_unk0x08,
	LegoFloat p_unk0x0c,
	LegoFloat p_unk0x10,
	LegoFloat p_unk0x14
)
{
	LegoFloat nearestDistanceSquared = FLT_MAX;
	Racer* result = NULL;

	for (LegoS32 i = 0; i < static_cast<LegoS32>(m_racerCount); i++) {
		Racer* racer = &m_racers[i];

		GolVec3 position;
		racer->m_unk0x018.m_unk0x044->VTable0x04(&position);

		GolVec3 delta = position - *p_unk0x04;
		LegoFloat distanceSquared = delta.m_z * delta.m_z + delta.m_y * delta.m_y + delta.m_x * delta.m_x;
		if (distanceSquared >= p_unk0x0c && distanceSquared <= p_unk0x10) {
			GolVec3 normalized;
			GolMath::NormalizeVector3(delta, &normalized);

			if (GOLVECTOR3_DOT(normalized, *p_unk0x08) >= p_unk0x14 && distanceSquared < nearestDistanceSquared) {
				result = racer;
				nearestDistanceSquared = distanceSquared;
			}
		}
	}

	return result;
}

// STUB: LEGORACERS 0x0043cf30
RaceState::Racer::Field0x00c::StandingsDeltaEntry* RaceState::Racer::Field0x00c::FUN_0043cf30(
	Racer* p_racer,
	StandingsDeltaEntry* p_entries
)
{
	Racer* racer = p_racer;
	LegoU32 lapCount = m_lapCount;
	StandingsDeltaEntry* result = p_entries;
	LegoS32 racerTime = 0;

	if (racer->m_lapsCompleted >= lapCount) {
		if (m_lapCount) {
			LegoU32 remaining = m_lapCount;
			LegoU32* lapTime = racer->m_lapTimes;

			do {
				racerTime += *lapTime++;
			} while (--remaining);
		}

		if (m_racerCount) {
			LegoU32 racerIndex = 0;
			Racer* otherRacer = m_racers;
			StandingsDeltaEntry* entry = p_entries;

			do {
				entry->m_racer = otherRacer;
				entry->m_isValid = TRUE;

				if (otherRacer == racer) {
					entry->m_delta = 0;
				}
				else if (otherRacer->m_lapsCompleted >= m_lapCount) {
					LegoS32 otherTime = 0;
					LegoU32 remaining = m_lapCount;

					if (remaining) {
						LegoU32* lapTime = otherRacer->m_lapTimes;

						do {
							otherTime += *lapTime++;
						} while (--remaining);
					}

					entry->m_delta = otherTime - racerTime;
				}
				else {
					entry->m_delta = otherRacer->m_lapTimes[5] + 2147483641;
				}

				racerIndex++;
				otherRacer++;
				entry++;
			} while (racerIndex < m_racerCount);
		}

		if (m_racerCount < 6) {
			StandingsDeltaEntry* entry = &p_entries[m_racerCount];
			LegoU32 remaining = 6 - m_racerCount;

			do {
				entry->m_isValid = FALSE;
				entry++;
			} while (--remaining);
		}
	}
	else {
		if (m_racerCount) {
			LegoU32 racerIndex = 0;
			StandingsDeltaEntry* entry = p_entries;

			do {
				entry->m_racer = NULL;
				entry->m_delta = 0;
				entry->m_isValid = FALSE;
				racerIndex++;
				entry++;
			} while (racerIndex < m_racerCount);
		}
	}

	return result;
}

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
