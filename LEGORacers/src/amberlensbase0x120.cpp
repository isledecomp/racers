#include "amberlensbase0x120.h"

#include "floatyferry0xf4.h"
#include "jadeorbit0xd0.h"
#include "jadeorbitbase0x10.h"
#include "whitefalconnode0x18.h"

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

// FUNCTION: LEGORACERS 0x004047b0
void AmberLensBase0x120::FUN_004047b0()
{
	if (m_unk0x28 == NULL) {
		return;
	}

	m_unk0x28->VTable0x5c(0);
	WhiteFalconNode0x18* frameSet = m_unk0x28->VTable0x58(0);
	JadeOrbitBase0x10* orbit = frameSet->VTable0x18(m_unk0x2c);

	GolVec3 position;
	GolVec3 right;
	GolVec3 forward;
	orbit->GetPosition(&position);
	orbit->VTable0x20(&right, &forward);

	for (JadeOrbitBase0x10* parent = orbit->m_unk0x04; parent != NULL; parent = parent->m_unk0x04) {
		GolVec3 transformedPosition;
		GolVec3 transformedRight;
		GolVec3 transformedForward;

		parent->VTable0x04(&position, &transformedPosition);
		parent->VTable0x0c(&right, &transformedRight);
		parent->VTable0x0c(&forward, &transformedForward);

		position = transformedPosition;
		right = transformedRight;
		forward = transformedForward;
	}

	GolVec3 worldPosition;
	GolVec3 worldRight;
	GolVec3 worldForward;
	m_unk0x28->VTable0x2c(position, &worldPosition);
	m_unk0x28->VTable0x34(right, &worldRight);
	m_unk0x28->VTable0x34(forward, &worldForward);

	m_unk0x04->SetPosition(&worldPosition);
	worldForward.m_x = -worldForward.m_x;
	worldForward.m_y = -worldForward.m_y;
	worldForward.m_z = -worldForward.m_z;

	m_flags |= 1;
	m_unk0x04->VTable0x24(&worldRight, &worldForward);
	m_flags |= 1;
}
