#include "race/events/lapzoneresource.h"

#include "decomp.h"
#include "race/racer/racer.h"

DECOMP_SIZE_ASSERT(LapZoneResource, 0x24)
DECOMP_SIZE_ASSERT(LapZoneResource::InitParams, 0x18)

// FUNCTION: LEGORACERS 0x00464570
LapZoneResource::LapZoneResource()
{
	OnEnd();
	m_flags = 0;
}

// FUNCTION: LEGORACERS 0x004645c0
LapZoneResource::~LapZoneResource()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00464610
void LapZoneResource::Initialize(InitParams* p_params)
{
	if (m_state) {
		Destroy();
	}

	InitParams* params = p_params;
	m_eventId = params->m_eventId;
	LegoS32* eventId = params->m_stateEventIds;
	for (LegoS32 i = 0; i < sizeOfArray(m_stateEventIds); i++) {
		m_stateEventIds[i] = *eventId++;
	}

	m_eventTable = params->m_eventTable;
	m_zone = params->m_zone;
	m_state = c_stateEnded;
}

// FUNCTION: LEGORACERS 0x00464660
void LapZoneResource::Destroy()
{
	OnEndForRacer(NULL);
	RaceEventResource::OnEnd();
	Reset();
}

// FUNCTION: LEGORACERS 0x00464680
void LapZoneResource::OnStartForRacer(Racer* p_racer)
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
void LapZoneResource::OnEndForRacer(Racer*)
{
	NotifyStateChange(m_state, 3);
	m_state = c_stateEnded;
}

// FUNCTION: LEGORACERS 0x00464700
LegoU32 LapZoneResource::GetKind()
{
	return 8;
}
