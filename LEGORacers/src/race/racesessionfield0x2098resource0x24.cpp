#include "race/racesession.h"

// FUNCTION: LEGORACERS 0x00464570
RaceSession::Field0x2098::Resource0x24::Resource0x24()
{
	VTable0x0c();
	m_flags0x1c = 0;
}

// FUNCTION: LEGORACERS 0x004645c0
RaceSession::Field0x2098::Resource0x24::~Resource0x24()
{
	FUN_00464660();
}

// FUNCTION: LEGORACERS 0x00464610
void RaceSession::Field0x2098::Resource0x24::FUN_00464610(InitParams* p_params)
{
	if (m_state0x18) {
		FUN_00464660();
	}

	InitParams* params = p_params;
	m_unk0x14 = params->m_unk0x00;
	LegoS32* eventId = params->m_eventIds;
	for (LegoS32 i = 0; i < sizeOfArray(m_eventIds); i++) {
		m_eventIds[i] = *eventId++;
	}

	m_unk0x04 = params->m_eventTable;
	m_unk0x20 = params->m_unk0x14;
	m_state0x18 = c_state0x18Four;
}

// FUNCTION: LEGORACERS 0x00464660
void RaceSession::Field0x2098::Resource0x24::FUN_00464660()
{
	VTable0x08(NULL);
	Resource::VTable0x0c();
	Reset();
}

// FUNCTION: LEGORACERS 0x00464680
void RaceSession::Field0x2098::Resource0x24::VTable0x00(RaceState::Racer* p_racer)
{
	switch (m_unk0x20) {
	case 0:
		p_racer->FUN_00439b70();
		break;
	case 1:
		p_racer->FUN_00439ba0();
		break;
	case 2:
		p_racer->FUN_00439c40();
		break;
	default:
		break;
	}

	FUN_0045edd0(1, 1);
}

// FUNCTION: LEGORACERS 0x004646e0
void RaceSession::Field0x2098::Resource0x24::VTable0x08(RaceState::Racer*)
{
	FUN_0045edd0(m_state0x18, 3);
	m_state0x18 = c_state0x18Four;
}
