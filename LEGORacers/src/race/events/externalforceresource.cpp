#include "race/events/externalforceresource.h"

#include "decomp.h"
#include "race/racer/racer.h"

DECOMP_SIZE_ASSERT(ExternalForceResource::InitParams, 0x30)
DECOMP_SIZE_ASSERT(ExternalForceResource, 0x38)

// FUNCTION: LEGORACERS 0x00462e70
ExternalForceResource::ExternalForceResource()
{
	ClearFields();
}

// FUNCTION: LEGORACERS 0x00462ec0
ExternalForceResource::~ExternalForceResource()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00462f10
void ExternalForceResource::ClearFields()
{
	m_armEventId = -1;
	m_eventTable = NULL;
	m_state0x18 = 0;
	m_eventId = 0;
	m_force.m_x = 0.0f;
	m_force.m_y = 0.0f;
	m_force.m_z = 0.0f;
	m_channel = 0;
	m_flags0x34 = 0;
}

// FUNCTION: LEGORACERS 0x00462f40
void ExternalForceResource::Initialize(InitParams* p_params)
{
	if (m_state0x18) {
		Destroy();
	}

	m_eventId = p_params->m_eventId;
	LegoS32* eventId = p_params->m_stateEventIds;
	for (LegoU32 i = 0; i < sizeOfArray(m_stateEventIds); i++) {
		m_stateEventIds[i] = *eventId++;
	}

	m_eventTable = p_params->m_eventTable;
	m_force = p_params->m_force;
	m_channel = p_params->m_channel;
	m_armEventId = p_params->m_armEventId;
	if (p_params->m_unk0x28) {
		m_flags0x1c |= c_flagNoEnd;
	}
	if (p_params->m_unk0x2c) {
		m_flags0x1c |= c_flagTriggerOnEnd;
	}

	m_state0x18 = c_stateIdle;
}

// FUNCTION: LEGORACERS 0x00462fc0
void ExternalForceResource::Destroy()
{
	ClearFields();
	Reset();
}

// FUNCTION: LEGORACERS 0x00462fe0
void ExternalForceResource::OnStartForRacer(Racer* p_racer)
{
	if (m_flags0x34 & c_flags0x34Bit0) {
		if (p_racer) {
			switch (m_channel) {
			case 0:
				p_racer->m_physics.StartExternalForce0(&m_force);
				break;
			case 1:
				p_racer->m_physics.StartExternalForce1(&m_force);
				break;
			}
		}

		NotifyStateChange(1, 1);
		m_state0x18 = c_stateActive;
	}
}

// FUNCTION: LEGORACERS 0x00463040
void ExternalForceResource::OnEndForRacer(Racer* p_racer)
{
	if (p_racer) {
		switch (m_channel) {
		case 0:
			p_racer->m_physics.EndExternalForce0();
			break;
		case 1:
			p_racer->m_physics.EndExternalForce1();
			break;
		}
	}

	NotifyStateChange(m_state0x18, 3);
	m_state0x18 = c_stateIdle;
}

// FUNCTION: LEGORACERS 0x00463090
LegoU32 ExternalForceResource::GetKind()
{
	return 12;
}
