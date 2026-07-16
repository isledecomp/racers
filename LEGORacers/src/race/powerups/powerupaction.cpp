#include "race/powerups/powerupaction.h"

#include "decomp.h"

DECOMP_SIZE_ASSERT(PowerupAction, 0x18)

// FUNCTION: LEGORACERS 0x00451350
PowerupAction::PowerupAction()
{
	m_state = 0;
	m_stateTimerMs = 0;
	m_next = NULL;
	m_soundSource = NULL;
	m_level = 0;
}

// FUNCTION: LEGORACERS 0x00451390
PowerupAction::~PowerupAction()
{
}

// FUNCTION: LEGORACERS 0x004513a0 FOLDED
void PowerupAction::Update(LegoU32 p_elapsedMs)
{
	if (p_elapsedMs >= m_stateTimerMs) {
		m_stateTimerMs = 0;
		AdvanceState();
	}
	else {
		m_stateTimerMs -= p_elapsedMs;
	}
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void PowerupAction::OnEvent(LegoEventQueue::CallbackData*)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void PowerupAction::Draw(GolD3DRenderDevice*)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void PowerupAction::DrawTransparent(GolD3DRenderDevice*)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void PowerupAction::AdvanceState()
{
}

// FUNCTION: LEGORACERS 0x004513e0 FOLDED
void PowerupAction::Deactivate()
{
	m_state = 1;
}
