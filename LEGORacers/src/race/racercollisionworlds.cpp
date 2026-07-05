#include "race/racercollisionworlds.h"

#include "golboundedentity.h"
#include "golerror.h"
#include "race/racestate.h"
#include "world/golworlddatabase.h"

#include <stdlib.h>

DECOMP_SIZE_ASSERT(RacerCollisionWorlds, 0x3c)

// FUNCTION: LEGORACERS 0x0045e350
RacerCollisionWorlds::RacerCollisionWorlds()
{
	for (LegoS32 i = 0; i < sizeOfArray(m_racers); i++) {
		m_racers[i] = NULL;
		m_ttl[i] = NULL;
	}

	m_worldCount = 0;
	m_worldDatabase = NULL;
}

// FUNCTION: LEGORACERS 0x0045e3a0
RacerCollisionWorlds::~RacerCollisionWorlds()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0045e3b0
void RacerCollisionWorlds::Destroy()
{
	for (LegoS32 i = 0; i < sizeOfArray(m_racers); i++) {
		m_racers[i] = NULL;

		if (m_ttl[i]) {
			delete[] m_ttl[i];
			m_ttl[i] = NULL;
		}
	}

	m_worldCount = 0;
	m_worldDatabase = NULL;
}

// FUNCTION: LEGORACERS 0x0045e3f0
void RacerCollisionWorlds::Initialize(GolWorldDatabase* p_worldDatabase, RaceState* p_raceState)
{
	m_worldCount = p_worldDatabase->GetBoundedEntityCount();
	if (m_worldCount) {
		m_worldDatabase = p_worldDatabase;

		for (LegoU32 racerIndex = 0; racerIndex < c_racerCount; racerIndex++) {
			m_racers[racerIndex] = &p_raceState->GetRacers()[racerIndex];
			m_ttl[racerIndex] = new LegoU8[m_worldCount];
			if (!m_ttl[racerIndex]) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}

			for (LegoU32 i = 0; i < m_worldCount; i++) {
				m_ttl[racerIndex][i] = 0;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x0045e470
void RacerCollisionWorlds::Update(LegoU32 p_elapsedMs)
{
	if (m_worldCount) {
		while (p_elapsedMs > 0) {
			LegoU8 elapsedStep;
			LegoU8 savedElapsedStep;
			if (p_elapsedMs > c_maxElapsedChunk) {
				elapsedStep = static_cast<LegoU8>(-1);
				savedElapsedStep = elapsedStep;
			}
			else {
				savedElapsedStep = static_cast<LegoU8>(p_elapsedMs);
				elapsedStep = static_cast<LegoU8>(p_elapsedMs);
			}

			for (LegoU32 racerIndex = 0; racerIndex < sizeOfArray(m_racers); racerIndex++) {
				LegoU32 entryIndex = 0;
				if (m_worldCount > 0) {
					do {
						LegoU8 value = m_ttl[racerIndex][entryIndex];
						LegoU8* timer = &m_ttl[racerIndex][entryIndex];
						if (value > 0) {
							if (elapsedStep >= value) {
								*timer = 0;
								m_racers[racerIndex]->m_physics.RemoveCollisionWorld(
									m_worldDatabase->GetBoundedEntities() + entryIndex
								);
								elapsedStep = savedElapsedStep;
							}
							else {
								*timer = value - elapsedStep;
							}
						}

						++entryIndex;
					} while (entryIndex < m_worldCount);
				}
			}

			p_elapsedMs -= savedElapsedStep;
		}
	}
}

// FUNCTION: LEGORACERS 0x0045e520
void RacerCollisionWorlds::ActivateWorld(Racer* p_racer, LegoU32 p_worldIndex)
{
	Racer* target = p_racer;
	RacerCollisionWorlds* field = this;
	LegoU32 racerIndex = 0;
	if (field->m_racers[0] != target) {
		Racer** racer = field->m_racers;
		Racer* nextRacer;
		while (racerIndex < sizeOfArray(m_racers)) {
			nextRacer = racer[1];
			racer++;
			racerIndex++;
			if (nextRacer == target) {
				break;
			}
		}
	}

	if (!field->m_ttl[racerIndex][p_worldIndex]) {
		target->m_physics.AddCollisionWorld(field->m_worldDatabase->GetBoundedEntities() + p_worldIndex);
	}

	LegoU32 result = 0;
	Racer** racer = field->m_racers;
	for (; *racer != target; racer++) {
		if (++result >= sizeOfArray(field->m_racers)) {
			field->m_ttl[result][p_worldIndex] = c_activationTtl;
			return;
		}
	}

	field->m_ttl[result][p_worldIndex] = c_activationTtl;
}

// FUNCTION: LEGORACERS 0x0045e5b0
LegoU32 RacerCollisionWorlds::Reset()
{
	LegoU32 result = 0;

	for (LegoS32 racerIndex = 0; racerIndex < c_racerCount; racerIndex++) {
		result = 0;
		for (; result < m_worldCount; result++) {
			m_ttl[racerIndex][result] = 0;
		}
	}

	return result;
}
