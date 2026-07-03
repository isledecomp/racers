#include "race/hazards/hazard.h"

#include "camera/golcamera.h"
#include "decomp.h"
#include "golmath.h"
#include "race/racer/racer.h"
#include "render/gold3drenderdevice.h"
#include "types.h"

DECOMP_SIZE_ASSERT(Hazard, 0x10)

// FUNCTION: LEGORACERS 0x0048a400
Hazard::Hazard()
{
	m_eventTable = NULL;
	m_state = c_stateUnloaded;
	m_triggerId = 0;
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void Hazard::OnEvent(LegoEventQueue::CallbackData*)
{
}

// FUNCTION: LEGORACERS 0x0048a440
Hazard::~Hazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048a450
LegoS32 Hazard::Reset()
{
	m_eventTable = NULL;
	m_state = c_stateUnloaded;
	m_triggerId = 0;

	return 0;
}

// FUNCTION: LEGORACERS 0x0048a460
void Hazard::Update(undefined4)
{
	if (m_state == c_stateDeactivatePending) {
		OnDeactivate(NULL);
	}
}

// FUNCTION: LEGORACERS 0x0048a470
void Hazard::Activate(void* p_context)
{
	if (m_state == c_stateLoaded) {
		OnActivate(p_context);
	}
}

// FUNCTION: LEGORACERS 0x0048a490
void Hazard::Deactivate(void* p_context)
{
	if (m_state != c_stateLoaded) {
		OnDeactivate(p_context);
	}
}

// FUNCTION: LEGORACERS 0x0046c9f0 FOLDED
void Hazard::UpdatePerRacer(GolCamera*, Racer*)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void Hazard::Draw(GolD3DRenderDevice*)
{
}

// FUNCTION: LEGORACERS 0x0044e7e0 FOLDED
LegoBool32 Hazard::CanRetrigger()
{
	return FALSE;
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void Hazard::ResetState()
{
}

// FUNCTION: LEGORACERS 0x0046c9f0 FOLDED
void Hazard::OnEventStart(LegoS32, void*)
{
}

// FUNCTION: LEGORACERS 0x0046c9f0 FOLDED
void Hazard::OnEventEnd(LegoS32, void*)
{
}
