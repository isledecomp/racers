#include "jadeorbit0x220.h"

DECOMP_SIZE_ASSERT(JadeOrbit0x220, 0x220)

// FUNCTION: GOLDP 0x10002890
JadeOrbit0x220::JadeOrbit0x220()
{
	m_unk0x50 = 1.0f;
	m_unk0x54 = 0.0f;
	m_unk0x58 = 0.0f;
	m_unk0x5c = 0.0f;
	m_unk0x60 = 0.0f;
	m_unk0x64 = 1.0f;
	m_unk0x68 = 0.0f;
	m_unk0x6c = 0.0f;
	m_unk0x70 = 0.0f;
	m_unk0x74 = 0.0f;
	m_unk0x78 = 1.0f;
	m_unk0x7c = 0.0f;
	m_unk0x80 = 0.0f;
	m_unk0x84 = 0.0f;
	m_unk0x88 = 0.0f;
	m_unk0x8c = 1.0f;
	m_unk0x94 = 0.0f;
	m_unk0x98 = 0.0f;
	m_unk0x9c = 0.0f;
	m_unk0xa0 = 0.0f;
	m_unk0xa8 = 0.0f;
	m_unk0xac = 0.0f;
	m_unk0xb0 = 0.0f;
	m_unk0xb4 = 0.0f;
	m_unk0xbc = 0.0f;
	m_unk0xc0 = 0.0f;
	m_unk0xc4 = 0.0f;
	m_unk0xc8 = 0.0f;
	m_up.m_y = 0.0f;
	m_up.m_z = 0.0f;
	m_unk0x1c = 0.0f;
	m_forward.m_x = 0.0f;
	m_forward.m_z = 0.0f;
	m_unk0x2c = 0.0f;
	m_right.m_x = 0.0f;
	m_right.m_y = 0.0f;
	m_unk0x3c = 0.0f;
	m_position.m_x = 0.0f;
	m_position.m_y = 0.0f;
	m_position.m_z = 0.0f;
	m_unk0x90 = 1.0f;
	m_unk0xa4 = 1.0f;
	m_unk0xb8 = 1.0f;
	m_unk0xcc = 1.0f;
	m_up.m_x = 1.0f;
	m_forward.m_y = 1.0f;
	m_right.m_z = 1.0f;
	m_unk0x4c = 1.0f;
}

// FUNCTION: GOLDP 0x10002980
void JadeOrbit0x220::GetBasis(GolVec3* p_right, GolVec3* p_forward, GolVec3* p_up)
{
	p_up->m_x = m_up.m_x;
	p_up->m_y = m_up.m_y;
	p_up->m_z = m_up.m_z;
	p_forward->m_x = m_forward.m_x;
	p_forward->m_y = m_forward.m_y;
	p_forward->m_z = m_forward.m_z;
	p_right->m_x = m_right.m_x;
	p_right->m_y = m_right.m_y;
	p_right->m_z = m_right.m_z;
}

// FUNCTION: GOLDP 0x100029d0
void JadeOrbit0x220::VTable0x1c(GolVec3* p_right, GolVec3* p_forward)
{
	p_forward->m_x = m_forward.m_x;
	p_forward->m_y = m_forward.m_y;
	p_forward->m_z = m_forward.m_z;
	p_right->m_x = m_right.m_x;
	p_right->m_y = m_right.m_y;
	p_right->m_z = m_right.m_z;
}

// FUNCTION: GOLDP 0x10002a00
void JadeOrbit0x220::VTable0x20(GolVec3* p_up, GolVec3* p_right)
{
	p_up->m_x = m_up.m_x;
	p_up->m_y = m_up.m_y;
	p_up->m_z = m_up.m_z;
	p_right->m_x = m_right.m_x;
	p_right->m_y = m_right.m_y;
	p_right->m_z = m_right.m_z;
}

// FUNCTION: GOLDP 0x10002a30
void JadeOrbit0x220::VTable0x24(GolVec3* p_right, GolVec3* p_forward)
{
	GolVec3 right;
	GolMath::NormalizeVector3(*p_right, right);

	LegoFloat dot = p_forward->m_y;
	dot *= right.m_y;
	dot += right.m_z * p_forward->m_z;
	dot += right.m_x * p_forward->m_x;

	GolVec3 forward;
	forward.m_x = p_forward->m_x - (right.m_x * dot);
	forward.m_y = p_forward->m_y - (right.m_y * dot);
	forward.m_z = p_forward->m_z - (right.m_z * dot);
	GolMath::NormalizeVector3(forward, forward);

	GolVec3 up;
	up.m_x = right.m_z;
	up.m_x *= forward.m_y;
	up.m_x -= forward.m_z * right.m_y;
	up.m_y = forward.m_z * right.m_x;
	LegoFloat rightZForwardX = right.m_z;
	rightZForwardX *= forward.m_x;
	up.m_y -= rightZForwardX;
	up.m_z = right.m_y;
	up.m_z *= forward.m_x;
	up.m_z -= forward.m_y * right.m_x;

	// TODO: This is behaviorally complete, but the final member-store schedule
	// remains 92.65% in reccmp.
	m_up.m_x = up.m_x;
	m_up.m_y = up.m_y;
	m_up.m_z = up.m_z;
	m_forward.m_x = forward.m_x;
	m_forward.m_y = forward.m_y;
	m_forward.m_z = forward.m_z;
	m_right.m_x = right.m_x;
	m_right.m_y = right.m_y;
	m_right.m_z = right.m_z;
}

// STUB: GOLDP 0x10002b20
void JadeOrbit0x220::VTable0x28()
{
	STUB(0x10002b20);
}

// STUB: GOLDP 0x10002c10
void JadeOrbit0x220::VTable0x04()
{
	STUB(0x10002c10);
}

// STUB: GOLDP 0x10002c90
void JadeOrbit0x220::VTable0x0c()
{
	STUB(0x10002c90);
}

// STUB: GOLDP 0x10002d00
void JadeOrbit0x220::VTable0x08(undefined4, undefined4)
{
	STUB(0x10002d00);
}

// STUB: GOLDP 0x10002dc0
void JadeOrbit0x220::VTable0x10()
{
	STUB(0x10002dc0);
}

// STUB: GOLDP 0x10002e30
void JadeOrbit0x220::VTable0x2c()
{
	STUB(0x10002e30);
}

// FUNCTION: GOLDP 0x10002f50
void JadeOrbit0x220::GetUp(GolVec3* p_up)
{
	p_up->m_x = m_up.m_x;
	p_up->m_y = m_up.m_y;
	p_up->m_z = m_up.m_z;
}

// FUNCTION: GOLDP 0x10002f70
void JadeOrbit0x220::GetForward(GolVec3* p_forward)
{
	p_forward->m_x = m_forward.m_x;
	p_forward->m_y = m_forward.m_y;
	p_forward->m_z = m_forward.m_z;
}

// FUNCTION: GOLDP 0x10002f90
void JadeOrbit0x220::GetRight(GolVec3* p_right)
{
	p_right->m_x = m_right.m_x;
	p_right->m_y = m_right.m_y;
	p_right->m_z = m_right.m_z;
}

// STUB: GOLDP 0x10002fb0
void JadeOrbit0x220::VTable0x3c()
{
	STUB(0x10002fb0);
}

// FUNCTION: GOLDP 0x10002fe0
void JadeOrbit0x220::GetPosition(GolVec3* p_position)
{
	p_position->m_x = m_position.m_x;
	p_position->m_y = m_position.m_y;
	p_position->m_z = m_position.m_z;
}

// FUNCTION: GOLDP 0x10003000
void JadeOrbit0x220::SetPosition(GolVec3* p_position)
{
	m_position.m_x = p_position->m_x;
	m_position.m_y = p_position->m_y;
	m_position.m_z = p_position->m_z;
}

// STUB: GOLDP 0x10003020
void JadeOrbit0x220::VTable0x14()
{
	STUB(0x10003020);
}

// STUB: GOLDP 0x10003080
void JadeOrbit0x220::VTable0x48()
{
	STUB(0x10003080);
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void JadeOrbit0x220::VTable0x00()
{
	// empty
}
