#include "race/events/timerresource.h"

#include "decomp.h"

DECOMP_SIZE_ASSERT(TimerResource::InitParams, 0x20)
DECOMP_SIZE_ASSERT(TimerResource, 0x30)

// FUNCTION: LEGORACERS 0x0045e730
TimerResource::TimerResource()
{
	ClearFields();
	m_flags0x1c = 0;
}

// FUNCTION: LEGORACERS 0x0045e780
TimerResource::~TimerResource()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0045e7d0
void TimerResource::ClearFields()
{
	m_holdEventId = -1;
	m_durationMs = 0;
	m_remainingMs = 0;
	m_flags0x2c = 0;
}

// FUNCTION: LEGORACERS 0x0045e7f0
void TimerResource::Initialize(InitParams* p_params)
{
	if (m_state0x18) {
		Destroy();
	}

	m_eventId = p_params->m_eventId;
	LegoS32* eventId = p_params->m_stateEventIds;
	LegoU32 i;
	for (i = 0; i < sizeOfArray(m_stateEventIds); i++) {
		m_stateEventIds[i] = *eventId++;
	}

	m_eventTable = p_params->m_eventTable;
	m_holdEventId = p_params->m_holdEventId;
	m_durationMs = p_params->m_durationMs;
	m_remainingMs = 0;
	if (p_params->m_forceable) {
		m_flags0x1c |= c_flags0x1cBit2;
	}

	m_state0x18 = c_state0x18Four;
}

// FUNCTION: LEGORACERS 0x0045e860
void TimerResource::Destroy()
{
	OnEnd();
	ClearFields();
	Reset();
}

// FUNCTION: LEGORACERS 0x0045e880
void TimerResource::OnStartAt(GolVec3*)
{
	m_remainingMs = m_durationMs;
	NotifyStateChange(1, 1);
	m_state0x18 = c_state0x18Three;
}

// FUNCTION: LEGORACERS 0x0045e8a0
void TimerResource::OnEnd()
{
	if (m_remainingMs <= 0 && !(m_flags0x2c & 1)) {
		NotifyStateChange(m_state0x18, 3);
		m_state0x18 = c_state0x18Four;
	}
}

// FUNCTION: LEGORACERS 0x0045e8d0
void TimerResource::Update(LegoU32 p_elapsedMs)
{
	RaceEventResource::Update(p_elapsedMs);
	if (m_state0x18 != c_state0x18Four) {
		if (p_elapsedMs > m_remainingMs) {
			m_remainingMs = 0;
		}
		else {
			m_remainingMs -= p_elapsedMs;
		}

		if (!m_remainingMs) {
			OnEnd();
		}
	}
}

// FUNCTION: LEGORACERS 0x0045e910
LegoU32 TimerResource::GetKind()
{
	return 6;
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void TimerResource::FUN_004513d0(undefined4)
{
}
