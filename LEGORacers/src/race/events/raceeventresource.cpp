#include "race/events/raceeventresource.h"

#include "decomp.h"
#include "race/raceeventtable.h"
#include "race/racer/racer.h"

DECOMP_SIZE_ASSERT(RaceEventResource, 0x20)

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RaceEventResource::OnStartForRacer(Racer*)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RaceEventResource::OnStartAt(GolVec3*)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RaceEventResource::OnEndForRacer(Racer*)
{
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void RaceEventResource::OnEnd()
{
}

// FUNCTION: LEGORACERS 0x0045ed40
RaceEventResource::RaceEventResource()
{
	m_eventTable = NULL;
	m_stateEventIds[0] = -1;
	m_stateEventIds[1] = -1;
	m_stateEventIds[2] = -1;
	m_state = 0;
	m_eventId = 0;
	m_flags = 0;
}

// FUNCTION: LEGORACERS 0x0045ed90
RaceEventResource::~RaceEventResource()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0045eda0
void RaceEventResource::Reset()
{
	m_eventTable = NULL;
	m_stateEventIds[0] = -1;
	m_stateEventIds[1] = -1;
	m_stateEventIds[2] = -1;
	m_state = 0;
	m_eventId = 0;
}

// FUNCTION: LEGORACERS 0x0045edc0
void RaceEventResource::Update(LegoU32)
{
	if (m_state == c_stateEndPending) {
		OnEnd();
	}
}

// FUNCTION: LEGORACERS 0x0045edd0
void RaceEventResource::NotifyStateChange(LegoU32 p_fromState, LegoU32 p_toState)
{
	LegoS32 current = -1;
	LegoS32 next = -1;

	switch (p_fromState) {
	case 2:
		p_fromState = 0;
		break;
	case 3:
		p_fromState = 1;
		break;
	case 4:
		p_fromState = 2;
		break;
	default:
		p_fromState = 3;
		break;
	}

	if (p_fromState != 3) {
		current = m_stateEventIds[p_fromState];
	}

	if (p_toState != 3) {
		next = m_stateEventIds[p_toState];
	}

	if (current != -1) {
		if (next != -1) {
			m_eventTable->FireEventsAt(next, current, NULL);
		}
		else {
			m_eventTable->EndEventsAt(current, NULL);
		}
	}
	else if (next != -1) {
		m_eventTable->StartEventsAt(next, NULL);
	}
}

// FUNCTION: LEGORACERS 0x0045eee0 FOLDED
void RaceEventResource::ForceEventEnd(Racer* p_racer)
{
	LegoU8 flags = m_flags;
	if (flags & c_flagTriggerOnEnd) {
		LegoU32 state = m_state;
		if (state == c_stateIdle || state == c_stateEnded) {
			OnStartForRacer(p_racer);
			if (m_flags & c_flagNoEnd) {
				return;
			}

			OnEndForRacer(p_racer);
			return;
		}
	}

	if (m_state != c_stateIdle && !(flags & c_flagNoEnd)) {
		OnEndForRacer(p_racer);
	}
}
