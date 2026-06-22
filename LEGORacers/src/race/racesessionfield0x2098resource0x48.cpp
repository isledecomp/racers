#include "decomp.h"
#include "race/racesession.h"

DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::Resource0x48::InitParams, 0x3c)

// FUNCTION: LEGORACERS 0x004654c0
RaceSession::Field0x2098::Resource0x48::Resource0x48()
{
	FUN_00465560();
}

// FUNCTION: LEGORACERS 0x00465510
RaceSession::Field0x2098::Resource0x48::~Resource0x48()
{
	FUN_004655e0();
}

// FUNCTION: LEGORACERS 0x00465560
void RaceSession::Field0x2098::Resource0x48::FUN_00465560()
{
	m_unk0x04 = NULL;
	m_flags0x20 = 0;
	m_state0x18 = 0;
	m_unk0x14 = 0;
}

// FUNCTION: LEGORACERS 0x00465570
void RaceSession::Field0x2098::Resource0x48::FUN_00465570(InitParams* p_params)
{
	if (m_state0x18) {
		FUN_004655e0();
	}

	m_unk0x14 = p_params->m_unk0x00;
	LegoS32* eventId = p_params->m_eventIds;
	for (LegoU32 i = 0; i < sizeOfArray(m_eventIds); i++) {
		m_eventIds[i] = *eventId++;
	}

	m_unk0x04 = p_params->m_eventTable;
	LegoU32 flags = p_params->m_flags0x14;
	m_flags0x20 = flags;
	m_unk0x24 = p_params->m_unk0x18;
	m_unk0x44 = p_params->m_unk0x38;
	if (flags & 1) {
		m_flags0x1c |= c_flags0x1cBit2;
	}
	if (flags & 4) {
		m_flags0x1c |= c_flags0x1cBit1;
	}

	m_state0x18 = c_state0x18Four;
}

// FUNCTION: LEGORACERS 0x004655e0
void RaceSession::Field0x2098::Resource0x48::FUN_004655e0()
{
	VTable0x08(NULL);
	FUN_00465560();
	Reset();
}

// FUNCTION: LEGORACERS 0x00465600
void RaceSession::Field0x2098::Resource0x48::VTable0x00(RaceState::Racer* p_racer)
{
	LegoU8 flags = static_cast<LegoU8>(m_flags0x20);
	GolWorldEntity* entity = m_unk0x44;
	if (flags & c_flags0x20Bit1) {
		if (entity) {
			entity->VTable0x28();
		}
		else if (p_racer) {
			p_racer->m_unk0x018.FUN_004400e0();
		}

		FUN_0045edd0(c_state0x18One, c_state0x18One);
		return;
	}

	if (entity) {
		entity->VTable0x24(&m_unk0x24);
	}
	else if (p_racer) {
		p_racer->m_unk0x018.FUN_004400a0(&m_unk0x24);
	}

	FUN_0045edd0(c_state0x18One, c_state0x18One);
}

// FUNCTION: LEGORACERS 0x00465690
void RaceSession::Field0x2098::Resource0x48::VTable0x08(RaceState::Racer* p_racer)
{
	if (!(static_cast<LegoU8>(m_flags0x20) & c_flags0x20Bit1)) {
		GolWorldEntity* entity = m_unk0x44;
		if (entity) {
			entity->VTable0x28();
		}
		else if (p_racer) {
			p_racer->m_unk0x018.FUN_004400e0();
		}
	}

	FUN_0045edd0(m_state0x18, c_state0x18Three);
	m_state0x18 = c_state0x18Four;
}

// FUNCTION: LEGORACERS 0x004656d0
LegoU32 RaceSession::Field0x2098::Resource0x48::VTable0x18()
{
	return 7;
}
