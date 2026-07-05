#include "race/powerups/whitebrick.h"

#include "audio/soundnode.h"
#include "decomp.h"
#include "race/racer/racer.h"

// FUNCTION: LEGORACERS 0x004535a0
WhiteBrick::WhiteBrick()
{
	m_droppedTimeMs = 0;
	m_flags = 0;
}

// FUNCTION: LEGORACERS 0x004535c0
WhiteBrick::~WhiteBrick()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00453610
void WhiteBrick::Reset()
{
	m_droppedTimeMs = 0;
	m_flags = 0;
	Destroy();
}

// FUNCTION: LEGORACERS 0x00453620
void WhiteBrick::CaptureHomePosition()
{
	m_worldEntity.GetPosition(&m_homePosition);
	m_state = c_stateActive;
	m_droppedTimeMs = 0;
	m_flags = 0;
}

// FUNCTION: LEGORACERS 0x00453650
void WhiteBrick::Respawn()
{
	PickupBrick::Respawn();
	m_worldEntity.SetPosition(m_homePosition);
	m_state = c_stateActive;
	m_droppedTimeMs = 0;
	m_flags = 0;
	m_stateTimerMs = 0;
	SetTouchable(FALSE);
}

// FUNCTION: LEGORACERS 0x00453690
void WhiteBrick::Update(LegoU32 p_elapsedMs)
{
	if (m_state == c_stateInactive) {
		return;
	}

	PickupBrick::Update(p_elapsedMs);

	if (m_flags & c_flagDropped) {
		m_droppedTimeMs += p_elapsedMs;
		if (m_droppedTimeMs > 10000) {
			ReturnHome();
		}
	}

	LegoU32 state = m_state;
	if (state != c_stateActive) {
		if (state == c_stateTransition && m_stateTimerMs > 250) {
			LegoU8 flags = m_flags;
			if (flags & c_flagReturnHome) {
				m_flags = flags & ~c_flagReturnHome;
				m_worldEntity.SetPosition(m_homePosition);
				m_state = c_stateActive;
			}
			else {
				m_state = c_stateWait;
			}

			m_stateTimerMs = 0;
			SetTouchable(FALSE);
		}
	}
	else if (m_stateTimerMs > 500) {
		m_state = c_stateIdle;
		m_stateTimerMs = 0;
		SetTouchable(TRUE);
	}
}

// FUNCTION: LEGORACERS 0x00453750
void WhiteBrick::OnTouched(Racer* p_racer)
{
	if (m_state == c_stateIdle && p_racer->CollectWhiteBrick(this)) {
		m_nextState = c_stateWait;
		m_state = c_stateTransition;
		m_stateTimerMs = 0;
		m_flags &= ~c_flagDropped;
		m_droppedTimeMs = 0;
	}
}
