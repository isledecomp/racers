#include "race/racer/racerouterecord.h"
#include "race/racestate.h"
#include "race/timeracemanager.h"

#include <float.h>

DECOMP_SIZE_ASSERT(RaceRouteRecord, 0x48)
DECOMP_SIZE_ASSERT(Racer::StandingsDeltaEntry, 0x0c)

// FUNCTION: LEGORACERS 0x0043c6e0
Racer* RaceState::FindRacerInCone(
	GolVec3* p_position,
	GolVec3* p_direction,
	LegoFloat p_minDistanceSquared,
	LegoFloat p_maxDistanceSquared,
	LegoFloat p_coneCosine
)
{
	LegoS32 i;
	for (i = 0; i < static_cast<LegoS32>(m_roster.m_racerCount);) {
		GolVec3* origin = p_position;
		Racer* racer = &m_roster.m_racers[i];
		CarVisuals* racerField = &racer->m_visuals;

		GolVec3 position;
		racerField->m_carEntity->VTable0x04(&position);

		LegoFloat deltaX = position.m_x - origin->m_x;
		LegoFloat deltaY = position.m_y - origin->m_y;
		LegoFloat deltaZ = position.m_z - origin->m_z;
		LegoFloat distanceSquared = deltaX * deltaX;
		distanceSquared += deltaY * deltaY;
		distanceSquared += deltaZ * deltaZ;
		if (distanceSquared >= p_minDistanceSquared && distanceSquared <= p_maxDistanceSquared) {
			GolVec3 delta;
			delta.m_x = deltaX;
			delta.m_y = deltaY;
			delta.m_z = deltaZ;
			GolMath::NormalizeVector3(delta, &delta);

			LegoFloat dot = p_direction->m_z;
			dot *= delta.m_z;
			LegoFloat yDot = p_direction->m_y;
			yDot *= delta.m_y;
			dot += yDot;
			dot += delta.m_x * p_direction->m_x;
			if (dot >= p_coneCosine) {
				return &m_roster.m_racers[i];
			}
		}

		i++;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x0043c7f0
Racer* RaceState::FindNextRacerInCone(
	Racer* p_racer,
	GolVec3* p_position,
	GolVec3* p_direction,
	LegoFloat p_minDistanceSquared,
	LegoFloat p_maxDistanceSquared,
	LegoFloat p_coneCosine
)
{
	LegoS32 i;
	for (i = 0; i < static_cast<LegoS32>(m_roster.m_racerCount); i++) {
		Racer* racer = &m_roster.m_racers[i];
		if (racer <= p_racer) {
			continue;
		}

		GolVec3 position;
		racer->m_visuals.m_carEntity->VTable0x04(&position);

		LegoFloat deltaX = position.m_x - p_position->m_x;
		LegoFloat deltaY = position.m_y - p_position->m_y;
		LegoFloat deltaZ = position.m_z - p_position->m_z;
		LegoFloat distanceSquared = deltaZ * deltaZ + deltaY * deltaY + deltaX * deltaX;
		if (distanceSquared >= p_minDistanceSquared && distanceSquared <= p_maxDistanceSquared) {
			GolVec3 delta;
			delta.m_x = deltaX;
			delta.m_y = deltaY;
			delta.m_z = deltaZ;
			GolMath::NormalizeVector3(delta, &delta);

			if (GOLVECTOR3_DOT(*p_direction, delta) >= p_coneCosine) {
				break;
			}
		}
	}

	if (i >= static_cast<LegoS32>(m_roster.m_racerCount)) {
		return NULL;
	}

	return &m_roster.m_racers[i];
}

// FUNCTION: LEGORACERS 0x0043c910
Racer* RaceState::FindFarthestRacerInCone(
	GolVec3* p_position,
	GolVec3* p_direction,
	LegoFloat p_minDistanceSquared,
	LegoFloat p_maxDistanceSquared,
	LegoFloat p_coneCosine
)
{
	LegoFloat farthestDistanceSquared = 0.0f;
	LegoS32 resultIndex = -1;

	for (LegoS32 i = 0; i < static_cast<LegoS32>(m_roster.m_racerCount); i++) {
		Racer* racer = &m_roster.m_racers[i];
		CarVisuals* racerField = &racer->m_visuals;

		GolVec3 position;
		racerField->m_carEntity->VTable0x04(&position);

		LegoFloat distanceSquared = (position.m_x - p_position->m_x) * (position.m_x - p_position->m_x) +
									(position.m_y - p_position->m_y) * (position.m_y - p_position->m_y) +
									(position.m_z - p_position->m_z) * (position.m_z - p_position->m_z);
		if (distanceSquared >= p_minDistanceSquared && distanceSquared <= p_maxDistanceSquared) {
			GolVec3 delta;
			delta.m_x = position.m_x - p_position->m_x;
			delta.m_y = position.m_y - p_position->m_y;
			delta.m_z = position.m_z - p_position->m_z;
			GolMath::NormalizeVector3(delta, &delta);

			if (GOLVECTOR3_DOT(*p_direction, delta) >= p_coneCosine && distanceSquared > farthestDistanceSquared) {
				resultIndex = i;
				farthestDistanceSquared = distanceSquared;
			}
		}
	}

	if (resultIndex < 0) {
		return NULL;
	}

	return &m_roster.m_racers[resultIndex];
}

// FUNCTION: LEGORACERS 0x0043ca60
Racer* RaceState::FindNearestRacerInCone(
	GolVec3* p_position,
	GolVec3* p_direction,
	LegoFloat p_minDistanceSquared,
	LegoFloat p_maxDistanceSquared,
	LegoFloat p_coneCosine
)
{
	LegoFloat nearestDistanceSquared = FLT_MAX;
	LegoS32 resultIndex = -1;

	for (LegoS32 i = 0; i < static_cast<LegoS32>(m_roster.m_racerCount); i++) {
		Racer* racer = &m_roster.m_racers[i];
		CarVisuals* racerField = &racer->m_visuals;

		GolVec3 position;
		racerField->m_carEntity->VTable0x04(&position);

		LegoFloat distanceSquared = (position.m_x - p_position->m_x) * (position.m_x - p_position->m_x) +
									(position.m_y - p_position->m_y) * (position.m_y - p_position->m_y) +
									(position.m_z - p_position->m_z) * (position.m_z - p_position->m_z);
		if (distanceSquared >= p_minDistanceSquared && distanceSquared <= p_maxDistanceSquared) {
			GolVec3 delta;
			delta.m_x = position.m_x - p_position->m_x;
			delta.m_y = position.m_y - p_position->m_y;
			delta.m_z = position.m_z - p_position->m_z;
			GolMath::NormalizeVector3(delta, &delta);

			if (GOLVECTOR3_DOT(*p_direction, delta) >= p_coneCosine && distanceSquared < nearestDistanceSquared) {
				resultIndex = i;
				nearestDistanceSquared = distanceSquared;
			}
		}
	}

	if (resultIndex < 0) {
		return NULL;
	}

	return &m_roster.m_racers[resultIndex];
}

// FUNCTION: LEGORACERS 0x0043cbb0
Racer* RaceState::FindNearestRacerInRange(
	GolVec3* p_position,
	LegoFloat p_minDistanceSquared,
	LegoFloat p_maxDistanceSquared
)
{
	LegoFloat nearestDistanceSquared = FLT_MAX;
	LegoS32 resultIndex = -1;

	for (LegoS32 i = 0; i < static_cast<LegoS32>(m_roster.m_racerCount); i++) {
		Racer* racer = &m_roster.m_racers[i];

		GolVec3 position;
		racer->m_visuals.m_carEntity->VTable0x04(&position);

		LegoFloat deltaX = position.m_x - p_position->m_x;
		LegoFloat deltaY = position.m_y - p_position->m_y;
		LegoFloat deltaZ = position.m_z - p_position->m_z;
		LegoFloat distanceSquared = deltaZ * deltaZ + deltaY * deltaY + deltaX * deltaX;
		if (distanceSquared >= p_minDistanceSquared && distanceSquared <= p_maxDistanceSquared &&
			distanceSquared < nearestDistanceSquared) {
			resultIndex = i;
			nearestDistanceSquared = distanceSquared;
		}
	}

	if (resultIndex < 0) {
		return NULL;
	}

	return &m_roster.m_racers[resultIndex];
}

// STUB: LEGORACERS 0x0043cda0
LegoU32 RaceState::GetTimeBehind(Racer* p_racer)
{
	TimeRaceManager* timeRaceManager = m_roster.m_timeRaceManager;
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
	LegoU32 lapCount = m_setup.m_lapCount;
	if (lapsCompleted > lapCount) {
		lapsCompleted = lapCount;
	}

	for (LegoU32 racerIndex = 0; racerIndex < m_roster.m_racerCount; racerIndex++) {
		Racer* otherRacer = &m_roster.m_racers[racerIndex];
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
void RaceState::ComputeStandingsDeltas(Racer* p_racer, Racer::StandingsDeltaEntry* p_entries)
{
	LegoU32 lapCount = m_setup.m_lapCount;
	LegoS32 racerTime = 0;

	if (lapCount > p_racer->m_lapsCompleted) {
		if (m_roster.m_racerCount > 0) {
			LegoU32 racerIndex = 0;
			Racer::StandingsDeltaEntry* entry = p_entries;

			do {
				entry->m_racer = NULL;
				entry->m_delta = 0;
				entry->m_isValid = FALSE;
				racerIndex++;
				entry++;
			} while (racerIndex < m_roster.m_racerCount);
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

	if (m_roster.m_racerCount > 0) {
		LegoU32 racerIndex = 0;
		Racer::StandingsDeltaEntry* entry = p_entries;

		do {
			entry->m_racer = &m_roster.m_racers[racerIndex];
			entry->m_isValid = TRUE;

			Racer* racers = m_roster.m_racers;
			Racer* otherRacer = &racers[racerIndex];
			if (otherRacer == p_racer) {
				entry->m_delta = 0;
			}
			else if (otherRacer->m_lapsCompleted >= m_setup.m_lapCount) {
				LegoS32 otherTime = 0;
				LegoU32 remaining = m_setup.m_lapCount;

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
		} while (racerIndex < m_roster.m_racerCount);
	}

	if (m_roster.m_racerCount < 6) {
		Racer::StandingsDeltaEntry* entry = &p_entries[m_roster.m_racerCount];
		LegoU32 remaining = 6 - m_roster.m_racerCount;

		do {
			entry->m_isValid = FALSE;
			entry++;
		} while (--remaining);
	}
}

// FUNCTION: LEGORACERS 0x0043d070
RaceRouteRecord* RaceState::FindNearestRouteRecord(Racer* p_racer)
{
	LegoFloat nearestDistanceSquared = FLT_MAX;
	RaceRouteRecord* result = NULL;

	GolVec3 racerPosition;
	p_racer->m_visuals.m_carEntity->VTable0x04(&racerPosition);

	RaceRouteRecord* entry = m_roster.m_routeRecords;
	for (LegoS32 i = 6; i; i--) {
		if (entry->m_pathPoints) {
			GolVec3 position = entry->m_loopPosition;
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
