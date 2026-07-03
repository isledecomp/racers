#include "race/events/looktargetresource.h"

#include "decomp.h"
#include "race/racer/racer.h"

DECOMP_SIZE_ASSERT(LookTargetResource::InitParams, 0x20)
DECOMP_SIZE_ASSERT(LookTargetResource, 0x2c)

// FUNCTION: LEGORACERS 0x0045e5e0
LookTargetResource::LookTargetResource()
{
	m_lookPosition.m_x = 0.0f;
	m_lookPosition.m_y = 0.0f;
	m_lookPosition.m_z = 0.0f;
}

// FUNCTION: LEGORACERS 0x0045e600
LookTargetResource::~LookTargetResource()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0045e650
void LookTargetResource::Initialize(InitParams* p_params)
{
	if (m_state) {
		Destroy();
	}

	m_eventId = p_params->m_eventId;
	LegoS32* eventId = p_params->m_stateEventIds;
	LegoU32 i;
	for (i = 0; i < sizeOfArray(m_stateEventIds); i++) {
		m_stateEventIds[i] = *eventId++;
	}

	m_eventTable = p_params->m_eventTable;
	m_lookPosition.m_x = p_params->m_lookPosition.m_x;
	m_lookPosition.m_y = p_params->m_lookPosition.m_y;
	m_lookPosition.m_z = p_params->m_lookPosition.m_z;
	m_state = c_stateEnded;
}

// FUNCTION: LEGORACERS 0x0045e6b0
void LookTargetResource::Destroy()
{
	m_lookPosition.m_x = 0.0f;
	m_lookPosition.m_y = 0.0f;
	m_lookPosition.m_z = 0.0f;
	Reset();
}

// FUNCTION: LEGORACERS 0x0045e6c0
void LookTargetResource::OnStartForRacer(Racer* p_racer)
{
	NotifyStateChange(1, 1);
	if (p_racer) {
		p_racer->SetLookTarget(&m_lookPosition);
	}
}

// FUNCTION: LEGORACERS 0x0045e6f0
void LookTargetResource::OnEndForRacer(Racer* p_racer)
{
	NotifyStateChange(m_state, 3);
	if (p_racer) {
		p_racer->ClearLookTarget();
	}

	m_state = c_stateEnded;
}

// FUNCTION: LEGORACERS 0x0045e720
LegoU32 LookTargetResource::GetKind()
{
	return 11;
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void LookTargetResource::FUN_004513d0(undefined4)
{
}
