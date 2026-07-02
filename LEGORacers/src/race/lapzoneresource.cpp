#include "race/racesession.h"

// FUNCTION: LEGORACERS 0x00464570
RaceEventTable::LapZoneResource::LapZoneResource()
{
	OnEnd();
	m_flags0x1c = 0;
}

// FUNCTION: LEGORACERS 0x004645c0
RaceEventTable::LapZoneResource::~LapZoneResource()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00464610
void RaceEventTable::LapZoneResource::Initialize(InitParams* p_params)
{
	if (m_state0x18) {
		Destroy();
	}

	InitParams* params = p_params;
	m_eventId = params->m_unk0x00;
	LegoS32* eventId = params->m_stateEventIds;
	for (LegoS32 i = 0; i < sizeOfArray(m_stateEventIds); i++) {
		m_stateEventIds[i] = *eventId++;
	}

	m_eventTable = params->m_eventTable;
	m_zone = params->m_unk0x14;
	m_state0x18 = c_state0x18Four;
}

// FUNCTION: LEGORACERS 0x00464660
void RaceEventTable::LapZoneResource::Destroy()
{
	OnEndForRacer(NULL);
	Resource::OnEnd();
	Reset();
}

// FUNCTION: LEGORACERS 0x00464680
void RaceEventTable::LapZoneResource::OnStartForRacer(Racer* p_racer)
{
	switch (m_zone) {
	case 0:
		p_racer->EnterOpenTrack();
		break;
	case 1:
		p_racer->CrossFinishLine();
		break;
	case 2:
		p_racer->EnterPostLineZone();
		break;
	default:
		break;
	}

	NotifyStateChange(1, 1);
}

// FUNCTION: LEGORACERS 0x004646e0
void RaceEventTable::LapZoneResource::OnEndForRacer(Racer*)
{
	NotifyStateChange(m_state0x18, 3);
	m_state0x18 = c_state0x18Four;
}
