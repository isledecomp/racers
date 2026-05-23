#include "amberlensbase0x120.h"

#include "jadeorbit0xd0.h"

// FUNCTION: LEGORACERS 0x004046a0
void AmberLensBase0x120::FUN_004046a0(GolVec3* p_position, GolVec3* p_target, GolVec3* p_up)
{
	GolVec3 up;
	GolVec3 forward;
	forward.m_x = p_target->m_x - p_position->m_x;
	forward.m_y = p_target->m_y - p_position->m_y;
	forward.m_z = p_target->m_z - p_position->m_z;

	up.m_x = -p_up->m_x;
	up.m_y = -p_up->m_y;
	up.m_z = -p_up->m_z;

	m_unk0x04->VTable0x24(&forward, &up);
	m_unk0x04->SetPosition(p_position);
}

// FUNCTION: LEGORACERS 0x00404740
void AmberLensBase0x120::FUN_00404740(LegoFloat p_aspect)
{
	if (p_aspect > 0.0f) {
		m_unk0x0c = p_aspect;
		m_flags |= 8;
	}
	else {
		m_flags &= ~8;
	}

	m_flags |= 3;
}
