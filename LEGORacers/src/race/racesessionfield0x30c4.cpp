#include "race/racesession.h"
#include "race/timeracemanager.h"

DECOMP_SIZE_ASSERT(RaceSession::Field0x30c4, 0x2c)

// FUNCTION: LEGORACERS 0x0043a640
RaceSession::Field0x30c4::Field0x30c4()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0043a650
RaceSession::Field0x30c4::~Field0x30c4()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0043a660
void RaceSession::Field0x30c4::Reset()
{
	m_context = NULL;
	m_raceState = NULL;
	m_unk0x08 = NULL;
	m_unk0x0c = NULL;
	m_unk0x10 = NULL;
	m_unk0x14 = NULL;
	m_timeRaceManager = NULL;
	m_unk0x1c = NULL;
	m_unk0x20 = NULL;
	m_unk0x24 = NULL;
	m_unk0x28 = NULL;
}

// FUNCTION: LEGORACERS 0x0043a690
void RaceSession::Field0x30c4::FUN_0043a690(const Field0x30c4* p_source)
{
	m_context = p_source->m_context;
	m_raceState = p_source->m_raceState;
	m_unk0x08 = p_source->m_unk0x08;
	m_unk0x0c = p_source->m_unk0x0c;
	m_unk0x10 = p_source->m_unk0x10;
	m_unk0x14 = p_source->m_unk0x14;
	m_timeRaceManager = p_source->m_timeRaceManager;
	m_unk0x1c = p_source->m_unk0x1c;
	m_unk0x20 = p_source->m_unk0x20;
	m_unk0x24 = p_source->m_unk0x24;
	m_unk0x28 = p_source->m_unk0x28;
}

// FUNCTION: LEGORACERS 0x0043a6e0
void RaceSession::Field0x30c4::FUN_0043a6e0()
{
	m_raceState->RecordBestTimes(m_context);
	m_unk0x28->FUN_00462c60();

	for (LegoU32 racerIndex = 0; racerIndex < m_raceState->GetRacerCount(); racerIndex++) {
		m_unk0x28->FUN_00462da0(&m_raceState->GetRacers()[racerIndex]);
	}

	m_unk0x20->VTable0x0c();
	m_unk0x1c->VTable0x0c();
	m_unk0x24->FUN_0045e5b0();
	m_unk0x0c->FUN_0048ae60();
	m_unk0x08->FUN_0045bb30();

	if (m_timeRaceManager) {
		m_timeRaceManager->FUN_004234f0();
	}

	FUN_0043a780();
	m_unk0x10->FUN_00489f60();
	m_unk0x14->FUN_00489f60();
}

// FUNCTION: LEGORACERS 0x0043a780
void RaceSession::Field0x30c4::FUN_0043a780()
{
	m_raceState->FUN_0043d120();

	for (LegoU32 racerIndex = 0; racerIndex < m_raceState->GetRacerCount(); racerIndex++) {
		RaceState::Racer* racer = &m_raceState->GetRacers()[racerIndex];

		for (LegoU32 lapIndex = 0; lapIndex < racer->m_unk0xce0; lapIndex++) {
			racer->m_lapTimes[lapIndex] = 0;
		}

		racer->FUN_00439210(0);
		racer->FUN_00439520();
		racer->FUN_00439790();
		racer->FUN_004395a0();
		racer->FUN_00439660();
		racer->FUN_00439730();
		racer->FUN_004397b0();
		racer->FUN_00439b00();
		racer->FUN_0043a1a0();
		racer->FUN_00439870();
		racer->FUN_0043a210(racerIndex + 1);

		if (racer->m_unk0xd04 & RaceState::Racer::c_flags0xd04Bit21) {
			racer->m_unk0xd04 &= ~RaceState::Racer::c_flags0xd04Bit21;
		}

		RaceState::Racer::Field0x018* field = &racer->m_unk0x018;
		field->FUN_0043fdb0();
		field->FUN_0043db60();
		field->FUN_0043dcd0();
		field->FUN_0043da30();
		field->FUN_0043d9f0();
		field->m_unk0x000 |= RaceState::Racer::Field0x018::c_flags0x000Bit2;
		field->FUN_00440130();
		field->FUN_004400e0();
		field->FUN_00440160(1.0f);

		field->m_unk0x044->SetUnk0xb8(0.0f);
		if (field->m_unk0x040) {
			field->m_unk0x040->SetUnk0xb8(0.0f);
		}

		field->FUN_004401a0();

		for (LegoU32 particleIndex = 0; particleIndex < 4; particleIndex++) {
			field->FUN_0043de90(particleIndex);
		}

		LegoU32 startIndex = m_raceState->GetUnk0x17c(racerIndex);
		GolVec3 position = m_raceState->GetUnk0x0a4(startIndex);
		GolVec3 up;
		GolVec3 direction = m_raceState->GetUnk0x0ec(startIndex);
		up = m_raceState->GetUnk0x134(startIndex);
		racer->m_unk0x018.m_unk0x044->VTable0x08(position);
		racer->m_unk0x018.m_unk0x044->VTable0x40(direction, up);
		field->FUN_0043e620();
		racer->FUN_0043a3e0();

		if (!m_context->m_playerSetupSlots[racerIndex].m_unk0x10) {
			racer->m_unk0xd08 = 0;
			racer->m_unk0xe2c = NULL;
		}

		racer->FUN_004371c0(NULL, 0.0f);
		racer->m_unk0xc70.m_unk0x050 = m_raceState->GetUnk0x2a0();
		racer->FUN_004374c0();
		racer->FUN_00438500();
	}
}
