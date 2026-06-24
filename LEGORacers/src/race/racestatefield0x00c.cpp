#include "race/racerouterecord.h"
#include "race/racestate.h"
#include "race/timeracemanager.h"

#include <float.h>

DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x00c::Entry, 0x48)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x00c::StandingsDeltaEntry, 0x0c)

// FUNCTION: LEGORACERS 0x0043c6e0
RaceState::Racer* RaceState::FUN_0043c6e0(
	GolVec3* p_unk0x04,
	GolVec3* p_unk0x08,
	LegoFloat p_unk0x0c,
	LegoFloat p_unk0x10,
	LegoFloat p_unk0x14
)
{
	LegoS32 i;
	for (i = 0; i < static_cast<LegoS32>(m_unk0x0f0.m_racerCount);) {
		GolVec3* origin = p_unk0x04;
		Racer* racer = &m_unk0x0f0.m_racers[i];
		Racer::Field0x018* racerField = &racer->m_unk0x018;

		GolVec3 position;
		racerField->m_unk0x044->VTable0x04(&position);

		LegoFloat deltaX = position.m_x - origin->m_x;
		LegoFloat deltaY = position.m_y - origin->m_y;
		LegoFloat deltaZ = position.m_z - origin->m_z;
		LegoFloat distanceSquared = deltaX * deltaX;
		distanceSquared += deltaY * deltaY;
		distanceSquared += deltaZ * deltaZ;
		if (distanceSquared >= p_unk0x0c && distanceSquared <= p_unk0x10) {
			GolVec3 delta;
			delta.m_x = deltaX;
			delta.m_y = deltaY;
			delta.m_z = deltaZ;
			GolMath::NormalizeVector3(delta, &delta);

			LegoFloat dot = p_unk0x08->m_z;
			dot *= delta.m_z;
			LegoFloat yDot = p_unk0x08->m_y;
			yDot *= delta.m_y;
			dot += yDot;
			dot += delta.m_x * p_unk0x08->m_x;
			if (dot >= p_unk0x14) {
				return &m_unk0x0f0.m_racers[i];
			}
		}

		i++;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x0043c7f0
RaceState::Racer* RaceState::FUN_0043c7f0(
	Racer* p_racer,
	GolVec3* p_unk0x08,
	GolVec3* p_unk0x0c,
	LegoFloat p_unk0x10,
	LegoFloat p_unk0x14,
	LegoFloat p_unk0x18
)
{
	LegoS32 i;
	for (i = 0; i < static_cast<LegoS32>(m_unk0x0f0.m_racerCount); i++) {
		Racer* racer = &m_unk0x0f0.m_racers[i];
		if (racer <= p_racer) {
			continue;
		}

		GolVec3 position;
		racer->m_unk0x018.m_unk0x044->VTable0x04(&position);

		LegoFloat deltaX = position.m_x - p_unk0x08->m_x;
		LegoFloat deltaY = position.m_y - p_unk0x08->m_y;
		LegoFloat deltaZ = position.m_z - p_unk0x08->m_z;
		LegoFloat distanceSquared = deltaZ * deltaZ + deltaY * deltaY + deltaX * deltaX;
		if (distanceSquared >= p_unk0x10 && distanceSquared <= p_unk0x14) {
			GolVec3 delta;
			delta.m_x = deltaX;
			delta.m_y = deltaY;
			delta.m_z = deltaZ;
			GolMath::NormalizeVector3(delta, &delta);

			if (GOLVECTOR3_DOT(*p_unk0x0c, delta) >= p_unk0x18) {
				break;
			}
		}
	}

	if (i >= static_cast<LegoS32>(m_unk0x0f0.m_racerCount)) {
		return NULL;
	}

	return &m_unk0x0f0.m_racers[i];
}

// FUNCTION: LEGORACERS 0x0043c910
RaceState::Racer* RaceState::FUN_0043c910(
	GolVec3* p_unk0x04,
	GolVec3* p_unk0x08,
	LegoFloat p_unk0x0c,
	LegoFloat p_unk0x10,
	LegoFloat p_unk0x14
)
{
	LegoFloat farthestDistanceSquared = 0.0f;
	LegoS32 resultIndex = -1;

	for (LegoS32 i = 0; i < static_cast<LegoS32>(m_unk0x0f0.m_racerCount); i++) {
		Racer* racer = &m_unk0x0f0.m_racers[i];
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

	return &m_unk0x0f0.m_racers[resultIndex];
}

// FUNCTION: LEGORACERS 0x0043ca60
RaceState::Racer* RaceState::FUN_0043ca60(
	GolVec3* p_unk0x04,
	GolVec3* p_unk0x08,
	LegoFloat p_unk0x0c,
	LegoFloat p_unk0x10,
	LegoFloat p_unk0x14
)
{
	LegoFloat nearestDistanceSquared = FLT_MAX;
	LegoS32 resultIndex = -1;

	for (LegoS32 i = 0; i < static_cast<LegoS32>(m_unk0x0f0.m_racerCount); i++) {
		Racer* racer = &m_unk0x0f0.m_racers[i];
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

			if (GOLVECTOR3_DOT(*p_unk0x08, delta) >= p_unk0x14 && distanceSquared < nearestDistanceSquared) {
				resultIndex = i;
				nearestDistanceSquared = distanceSquared;
			}
		}
	}

	if (resultIndex < 0) {
		return NULL;
	}

	return &m_unk0x0f0.m_racers[resultIndex];
}

// FUNCTION: LEGORACERS 0x0043cbb0
RaceState::Racer* RaceState::FUN_0043cbb0(GolVec3* p_unk0x04, LegoFloat p_unk0x08, LegoFloat p_unk0x0c)
{
	LegoFloat nearestDistanceSquared = FLT_MAX;
	LegoS32 resultIndex = -1;

	for (LegoS32 i = 0; i < static_cast<LegoS32>(m_unk0x0f0.m_racerCount); i++) {
		Racer* racer = &m_unk0x0f0.m_racers[i];

		GolVec3 position;
		racer->m_unk0x018.m_unk0x044->VTable0x04(&position);

		LegoFloat deltaX = position.m_x - p_unk0x04->m_x;
		LegoFloat deltaY = position.m_y - p_unk0x04->m_y;
		LegoFloat deltaZ = position.m_z - p_unk0x04->m_z;
		LegoFloat distanceSquared = deltaZ * deltaZ + deltaY * deltaY + deltaX * deltaX;
		if (distanceSquared >= p_unk0x08 && distanceSquared <= p_unk0x0c && distanceSquared < nearestDistanceSquared) {
			resultIndex = i;
			nearestDistanceSquared = distanceSquared;
		}
	}

	if (resultIndex < 0) {
		return NULL;
	}

	return &m_unk0x0f0.m_racers[resultIndex];
}

// STUB: LEGORACERS 0x0043cda0
LegoU32 RaceState::FUN_0043cda0(Racer* p_racer)
{
	TimeRaceManager* timeRaceManager = m_unk0x0f0.m_timeRaceManager;
	LegoU32 lapsCompleted = p_racer->m_lapsCompleted;

	if (timeRaceManager) {
		LegoU32 racerLapTime = 0;
		LegoU32 recordLapTime = 0;
		LegoU32 bestLapTime = 0;

		for (LegoU32 i = 0; i < lapsCompleted; i++) {
			racerLapTime += p_racer->m_lapTimes[i];
		}

		if (timeRaceManager->HasRecordRunLapTimes()) {
			const LegoU32* lapTimes = timeRaceManager->GetRecordLapTimes();
			for (LegoU32 i = 0; i < lapsCompleted; i++) {
				recordLapTime += lapTimes[i];
			}
		}

		if (timeRaceManager->HasBestRunLapTimes()) {
			const LegoU32* lapTimes = timeRaceManager->GetBestLapTimes();
			for (LegoU32 i = 0; i < lapsCompleted; i++) {
				bestLapTime += lapTimes[i];
			}

			if (bestLapTime != 0 && (recordLapTime == 0 || recordLapTime > bestLapTime)) {
				recordLapTime = bestLapTime;
			}
		}

		if (recordLapTime != 0 && recordLapTime < racerLapTime) {
			return racerLapTime - recordLapTime;
		}

		return 0;
	}

	if (p_racer->m_lapTimes[5] == 1) {
		return 0;
	}

	LegoS32 result = 0;
	LegoU32 lapCount = m_unk0x284.m_lapCount;
	if (lapsCompleted > lapCount) {
		lapsCompleted = lapCount;
	}

	for (LegoU32 racerIndex = 0; racerIndex < m_unk0x0f0.m_racerCount; racerIndex++) {
		Racer* otherRacer = &m_unk0x0f0.m_racers[racerIndex];
		if (otherRacer == p_racer) {
			continue;
		}

		LegoU32 otherLapsCompleted = otherRacer->m_lapsCompleted;
		if (otherLapsCompleted > lapCount) {
			otherLapsCompleted = lapCount;
		}

		if (lapsCompleted <= otherLapsCompleted) {
			LegoS32 delta = 0;
			for (LegoU32 completedLapIndex = 0; completedLapIndex < lapsCompleted; completedLapIndex++) {
				delta += static_cast<LegoS32>(p_racer->m_lapTimes[completedLapIndex]) -
						 static_cast<LegoS32>(otherRacer->m_lapTimes[completedLapIndex]);
			}

			for (LegoU32 remainingLapIndex = lapsCompleted; remainingLapIndex < otherLapsCompleted;
				 remainingLapIndex++) {
				delta += static_cast<LegoS32>(otherRacer->m_lapTimes[remainingLapIndex]);
			}

			if (delta > result) {
				result = delta;
			}
		}
	}

	return result;
}

// STUB: LEGORACERS 0x0043cf30
void RaceState::FUN_0043cf30(Racer* p_racer, Racer::Field0x00c::StandingsDeltaEntry* p_entries)
{
	LegoU32 lapCount = m_unk0x284.m_lapCount;
	LegoS32 racerTime = 0;

	if (lapCount > p_racer->m_lapsCompleted) {
		if (m_unk0x0f0.m_racerCount > 0) {
			LegoU32 racerIndex = 0;
			Racer::Field0x00c::StandingsDeltaEntry* entry = p_entries;

			do {
				entry->m_racer = NULL;
				entry->m_delta = 0;
				entry->m_isValid = FALSE;
				racerIndex++;
				entry++;
			} while (racerIndex < m_unk0x0f0.m_racerCount);
		}

		return;
	}

	if (lapCount > 0) {
		LegoU32 remaining = lapCount;
		LegoU32* lapTime = p_racer->m_lapTimes;

		do {
			racerTime += *lapTime++;
		} while (--remaining);
	}

	if (m_unk0x0f0.m_racerCount > 0) {
		LegoU32 racerIndex = 0;
		Racer::Field0x00c::StandingsDeltaEntry* entry = p_entries;

		do {
			entry->m_racer = &m_unk0x0f0.m_racers[racerIndex];
			entry->m_isValid = TRUE;

			Racer* racers = m_unk0x0f0.m_racers;
			Racer* otherRacer = &racers[racerIndex];
			if (otherRacer == p_racer) {
				entry->m_delta = 0;
			}
			else if (otherRacer->m_lapsCompleted >= m_unk0x284.m_lapCount) {
				LegoS32 otherTime = 0;
				LegoU32 remaining = m_unk0x284.m_lapCount;

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
			entry++;
		} while (racerIndex < m_unk0x0f0.m_racerCount);
	}

	if (m_unk0x0f0.m_racerCount < 6) {
		Racer::Field0x00c::StandingsDeltaEntry* entry = &p_entries[m_unk0x0f0.m_racerCount];
		LegoU32 remaining = 6 - m_unk0x0f0.m_racerCount;

		do {
			entry->m_isValid = FALSE;
			entry++;
		} while (--remaining);
	}
}

// FUNCTION: LEGORACERS 0x0043d070
RaceState::Racer::Field0x00c::Entry* RaceState::FUN_0043d070(Racer* p_racer)
{
	LegoFloat nearestDistanceSquared = FLT_MAX;
	Racer::Field0x00c::Entry* result = NULL;

	GolVec3 racerPosition;
	p_racer->m_unk0x018.m_unk0x044->VTable0x04(&racerPosition);

	Racer::Field0x00c::Entry* entry = m_unk0x0f0.m_routeRecords;
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
