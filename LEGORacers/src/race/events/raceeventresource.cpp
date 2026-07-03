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
	m_state0x18 = 0;
	m_eventId = 0;
	m_flags0x1c = 0;
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
	m_state0x18 = 0;
	m_eventId = 0;
}

// FUNCTION: LEGORACERS 0x0045edc0
void RaceEventResource::Update(LegoU32)
{
	if (m_state0x18 == c_state0x18Five) {
		OnEnd();
	}
}

// FUNCTION: LEGORACERS 0x0045edd0
void RaceEventResource::NotifyStateChange(LegoU32 p_unk0x04, LegoU32 p_unk0x08)
{
	LegoS32 current = -1;
	LegoS32 next = -1;

	switch (p_unk0x04) {
	case 2:
		p_unk0x04 = 0;
		break;
	case 3:
		p_unk0x04 = 1;
		break;
	case 4:
		p_unk0x04 = 2;
		break;
	default:
		p_unk0x04 = 3;
		break;
	}

	if (p_unk0x04 != 3) {
		current = m_stateEventIds[p_unk0x04];
	}

	if (p_unk0x08 != 3) {
		next = m_stateEventIds[p_unk0x08];
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
	LegoU8 flags = m_flags0x1c;
	if (flags & c_flags0x1cBit2) {
		LegoU32 state = m_state0x18;
		if (state == c_state0x18One || state == c_state0x18Four) {
			OnStartForRacer(p_racer);
			if (m_flags0x1c & c_flags0x1cBit1) {
				return;
			}

			OnEndForRacer(p_racer);
			return;
		}
	}

	if (m_state0x18 != c_state0x18One && !(flags & c_flags0x1cBit1)) {
		OnEndForRacer(p_racer);
	}
}
