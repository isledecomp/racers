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
	m_state = 0;
	m_triggerId = 0;
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void Hazard::VTable0x00(LegoEventQueue::CallbackData*)
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
	m_state = 0;
	m_triggerId = 0;

	return 0;
}

// FUNCTION: LEGORACERS 0x0048a460
void Hazard::Update(undefined4)
{
	if (m_state == 3) {
		OnDeactivate(NULL);
	}
}

// FUNCTION: LEGORACERS 0x0048a470
void Hazard::Activate(void* p_unk0x04)
{
	if (m_state == 1) {
		OnActivate(p_unk0x04);
	}
}

// FUNCTION: LEGORACERS 0x0048a490
void Hazard::Deactivate(void* p_unk0x04)
{
	if (m_state != 1) {
		OnDeactivate(p_unk0x04);
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
