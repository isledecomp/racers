#include "golerror.h"
#include "race/racesession.h"

#include <stdlib.h>

DECOMP_SIZE_ASSERT(RaceSession::Field0x32c4, 0x3c)
DECOMP_SIZE_ASSERT(RaceSession::Field0x32c4::Field0x1c, 0xac)

// FUNCTION: LEGORACERS 0x0045e350
RaceSession::Field0x32c4::Field0x32c4()
{
	for (LegoS32 i = 0; i < sizeOfArray(m_unk0x04); i++) {
		m_unk0x04[i] = NULL;
		m_unk0x20[i] = NULL;
	}

	m_unk0x38 = 0;
	m_unk0x1c = NULL;
}

// FUNCTION: LEGORACERS 0x0045e3a0
RaceSession::Field0x32c4::~Field0x32c4()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0045e3b0
void RaceSession::Field0x32c4::Destroy()
{
	for (LegoS32 i = 0; i < sizeOfArray(m_unk0x04); i++) {
		m_unk0x04[i] = NULL;

		if (m_unk0x20[i]) {
			delete[] m_unk0x20[i];
			m_unk0x20[i] = NULL;
		}
	}

	m_unk0x38 = 0;
	m_unk0x1c = NULL;
}

// FUNCTION: LEGORACERS 0x0045e3f0
void RaceSession::Field0x32c4::FUN_0045e3f0(Field0x1c* p_unk0x04, RaceState* p_raceState)
{
	m_unk0x38 = p_unk0x04->m_field0x000.m_unk0x064;
	if (m_unk0x38) {
		m_unk0x1c = p_unk0x04;

		for (LegoU32 racerIndex = 0; racerIndex < c_racerCount; racerIndex++) {
			m_unk0x04[racerIndex] = &p_raceState->GetRacers()[racerIndex];
			m_unk0x20[racerIndex] = new LegoU8[m_unk0x38];
			if (!m_unk0x20[racerIndex]) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}

			for (LegoU32 i = 0; i < m_unk0x38; i++) {
				m_unk0x20[racerIndex][i] = 0;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x0045e470
void RaceSession::Field0x32c4::FUN_0045e470(LegoU32 p_elapsedMs)
{
	if (m_unk0x38) {
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

			for (LegoU32 racerIndex = 0; racerIndex < sizeOfArray(m_unk0x04); racerIndex++) {
				LegoU32 entryIndex = 0;
				if (m_unk0x38 > 0) {
					do {
						LegoU8 value = m_unk0x20[racerIndex][entryIndex];
						LegoU8* timer = &m_unk0x20[racerIndex][entryIndex];
						if (value > 0) {
							if (elapsedStep >= value) {
								*timer = 0;
								m_unk0x04[racerIndex]->m_unk0x3e8.FUN_00448930(m_unk0x1c->m_unk0x0a8 + entryIndex);
								elapsedStep = savedElapsedStep;
							}
							else {
								*timer = value - elapsedStep;
							}
						}

						++entryIndex;
					} while (entryIndex < m_unk0x38);
				}
			}

			p_elapsedMs -= savedElapsedStep;
		}
	}
}

// STUB: LEGORACERS 0x0045e520
void RaceSession::Field0x32c4::FUN_0045e520(RaceState::Racer* p_racer, LegoU32 p_unk0x08)
{
	RaceState::Racer* target = p_racer;
	Field0x32c4* field = this;
	LegoU32 racerIndex = 0;
	if (field->m_unk0x04[0] != target) {
		RaceState::Racer** racer = field->m_unk0x04;
		RaceState::Racer* nextRacer;
		while (racerIndex < sizeOfArray(m_unk0x04)) {
			nextRacer = racer[1];
			racer++;
			racerIndex++;
			if (nextRacer == target) {
				break;
			}
		}
	}

	if (!field->m_unk0x20[racerIndex][p_unk0x08]) {
		target->m_unk0x3e8.FUN_004488e0(field->m_unk0x1c->m_unk0x0a8 + p_unk0x08);
	}

	LegoU32 result = 0;
	RaceState::Racer** racer = field->m_unk0x04;
	for (; *racer != target; racer++) {
		if (++result >= sizeOfArray(field->m_unk0x04)) {
			field->m_unk0x20[result][p_unk0x08] = 150;
			return;
		}
	}

	field->m_unk0x20[result][p_unk0x08] = 150;
}

// FUNCTION: LEGORACERS 0x0045e5b0
LegoU32 RaceSession::Field0x32c4::FUN_0045e5b0()
{
	LegoU32 result = 0;

	for (LegoS32 racerIndex = 0; racerIndex < c_racerCount; racerIndex++) {
		result = 0;
		for (; result < m_unk0x38; result++) {
			m_unk0x20[racerIndex][result] = 0;
		}
	}

	return result;
}
