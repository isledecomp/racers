#include "jadeorbit0xd0.h"

#include "jadeorbit0x220.h"

DECOMP_SIZE_ASSERT(JadeOrbit0xd0, 0xd0)
DECOMP_SIZE_ASSERT(JadeOrbit0x220, 0x220)

// FUNCTION: GOLDP 0x10002890
JadeOrbit0xd0::JadeOrbit0xd0()
{
	m_unk0x50.m_m[0][0] = 1.0f;
	m_unk0x50.m_m[0][1] = 0.0f;
	m_unk0x50.m_m[0][2] = 0.0f;
	m_unk0x50.m_m[0][3] = 0.0f;
	m_unk0x50.m_m[1][0] = 0.0f;
	m_unk0x50.m_m[1][1] = 1.0f;
	m_unk0x50.m_m[1][2] = 0.0f;
	m_unk0x50.m_m[1][3] = 0.0f;
	m_unk0x50.m_m[2][0] = 0.0f;
	m_unk0x50.m_m[2][1] = 0.0f;
	m_unk0x50.m_m[2][2] = 1.0f;
	m_unk0x50.m_m[2][3] = 0.0f;
	m_unk0x50.m_m[3][0] = 0.0f;
	m_unk0x50.m_m[3][1] = 0.0f;
	m_unk0x50.m_m[3][2] = 0.0f;
	m_unk0x50.m_m[3][3] = 1.0f;
	m_unk0x90.m_m[0][1] = 0.0f;
	m_unk0x90.m_m[0][2] = 0.0f;
	m_unk0x90.m_m[0][3] = 0.0f;
	m_unk0x90.m_m[1][0] = 0.0f;
	m_unk0x90.m_m[1][2] = 0.0f;
	m_unk0x90.m_m[1][3] = 0.0f;
	m_unk0x90.m_m[2][0] = 0.0f;
	m_unk0x90.m_m[2][1] = 0.0f;
	m_unk0x90.m_m[2][3] = 0.0f;
	m_unk0x90.m_m[3][0] = 0.0f;
	m_unk0x90.m_m[3][1] = 0.0f;
	m_unk0x90.m_m[3][2] = 0.0f;
	m_unk0x10.m_m[0][1] = 0.0f;
	m_unk0x10.m_m[0][2] = 0.0f;
	m_unk0x10.m_m[0][3] = 0.0f;
	m_unk0x10.m_m[1][0] = 0.0f;
	m_unk0x10.m_m[1][2] = 0.0f;
	m_unk0x10.m_m[1][3] = 0.0f;
	m_unk0x10.m_m[2][0] = 0.0f;
	m_unk0x10.m_m[2][1] = 0.0f;
	m_unk0x10.m_m[2][3] = 0.0f;
	m_unk0x10.m_m[3][0] = 0.0f;
	m_unk0x10.m_m[3][1] = 0.0f;
	m_unk0x10.m_m[3][2] = 0.0f;
	m_unk0x90.m_m[0][0] = 1.0f;
	m_unk0x90.m_m[1][1] = 1.0f;
	m_unk0x90.m_m[2][2] = 1.0f;
	m_unk0x90.m_m[3][3] = 1.0f;
	m_unk0x10.m_m[0][0] = 1.0f;
	m_unk0x10.m_m[1][1] = 1.0f;
	m_unk0x10.m_m[2][2] = 1.0f;
	m_unk0x10.m_m[3][3] = 1.0f;
}

// FUNCTION: GOLDP 0x10002980
void JadeOrbit0xd0::GetBasis(GolVec3* p_right, GolVec3* p_forward, GolVec3* p_up)
{
	p_up->m_x = m_unk0x10.m_m[0][0];
	p_up->m_y = m_unk0x10.m_m[0][1];
	p_up->m_z = m_unk0x10.m_m[0][2];
	p_forward->m_x = m_unk0x10.m_m[1][0];
	p_forward->m_y = m_unk0x10.m_m[1][1];
	p_forward->m_z = m_unk0x10.m_m[1][2];
	p_right->m_x = m_unk0x10.m_m[2][0];
	p_right->m_y = m_unk0x10.m_m[2][1];
	p_right->m_z = m_unk0x10.m_m[2][2];
}

// FUNCTION: GOLDP 0x100029d0
void JadeOrbit0xd0::VTable0x1c(GolVec3* p_right, GolVec3* p_forward)
{
	p_forward->m_x = m_unk0x10.m_m[1][0];
	p_forward->m_y = m_unk0x10.m_m[1][1];
	p_forward->m_z = m_unk0x10.m_m[1][2];
	p_right->m_x = m_unk0x10.m_m[2][0];
	p_right->m_y = m_unk0x10.m_m[2][1];
	p_right->m_z = m_unk0x10.m_m[2][2];
}

// FUNCTION: GOLDP 0x10002a00
void JadeOrbit0xd0::VTable0x20(GolVec3* p_up, GolVec3* p_right)
{
	p_up->m_x = m_unk0x10.m_m[0][0];
	p_up->m_y = m_unk0x10.m_m[0][1];
	p_up->m_z = m_unk0x10.m_m[0][2];
	p_right->m_x = m_unk0x10.m_m[2][0];
	p_right->m_y = m_unk0x10.m_m[2][1];
	p_right->m_z = m_unk0x10.m_m[2][2];
}

// FUNCTION: GOLDP 0x10002a30
void JadeOrbit0xd0::VTable0x24(GolVec3* p_right, GolVec3* p_forward)
{
	GolVec3 right;
	GolMath::NormalizeVector3(*p_right, &right);

	LegoFloat dot = p_forward->m_y;
	dot *= right.m_y;
	dot += right.m_z * p_forward->m_z;
	dot += right.m_x * p_forward->m_x;

	GolVec3 forward;
	forward.m_x = p_forward->m_x - (right.m_x * dot);
	forward.m_y = p_forward->m_y - (right.m_y * dot);
	forward.m_z = p_forward->m_z - (right.m_z * dot);
	GolMath::NormalizeVector3(forward, &forward);

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
	m_unk0x10.m_m[0][0] = up.m_x;
	m_unk0x10.m_m[0][1] = up.m_y;
	m_unk0x10.m_m[0][2] = up.m_z;
	m_unk0x10.m_m[1][0] = forward.m_x;
	m_unk0x10.m_m[1][1] = forward.m_y;
	m_unk0x10.m_m[1][2] = forward.m_z;
	m_unk0x10.m_m[2][0] = right.m_x;
	m_unk0x10.m_m[2][1] = right.m_y;
	m_unk0x10.m_m[2][2] = right.m_z;
}

// STUB: GOLDP 0x10002b20
void JadeOrbit0xd0::VTable0x28()
{
	STUB(0x10002b20);
}

// STUB: GOLDP 0x10002c10
void JadeOrbit0xd0::VTable0x04(const GolVec3*, GolVec3*)
{
	STUB(0x10002c10);
}

// STUB: GOLDP 0x10002c90
void JadeOrbit0xd0::VTable0x0c(const GolVec3*, GolVec3*)
{
	STUB(0x10002c90);
}

// STUB: GOLDP 0x10002d00
void JadeOrbit0xd0::VTable0x08(undefined4, undefined4)
{
	STUB(0x10002d00);
}

// STUB: GOLDP 0x10002dc0
void JadeOrbit0xd0::VTable0x10()
{
	STUB(0x10002dc0);
}

// FUNCTION: GOLDP 0x10002e30
void JadeOrbit0xd0::VTable0x2c(LegoFloat* p_unk0x04)
{
	LegoFloat scale = 2.0f / ((p_unk0x04[0] * p_unk0x04[0]) + (p_unk0x04[1] * p_unk0x04[1]) +
							  (p_unk0x04[2] * p_unk0x04[2]) + (p_unk0x04[3] * p_unk0x04[3]));
	LegoFloat v0 = scale * p_unk0x04[0];
	LegoFloat v1 = p_unk0x04[1];
	v1 *= scale;
	LegoFloat v2 = scale * p_unk0x04[2];
	LegoFloat v3 = p_unk0x04[3];
	v3 *= v0;
	LegoFloat v4 = p_unk0x04[3];
	v4 *= v1;
	LegoFloat v5 = p_unk0x04[3];
	v5 *= v2;
	LegoFloat v6 = v0 * p_unk0x04[0];
	LegoFloat v7 = v1 * p_unk0x04[0];
	LegoFloat v8 = v2 * p_unk0x04[0];
	LegoFloat v9 = p_unk0x04[1];
	v9 *= v1;
	LegoFloat v10 = p_unk0x04[1];
	v10 *= v2;
	LegoFloat v11 = v2 * p_unk0x04[2];

	m_unk0x10.m_m[0][0] = 1.0f - (v11 + v9);
	m_unk0x10.m_m[0][1] = v7 - v5;
	m_unk0x10.m_m[0][2] = v8 + v4;
	m_unk0x10.m_m[1][0] = v7 + v5;
	m_unk0x10.m_m[1][1] = 1.0f - (v11 + v6);
	m_unk0x10.m_m[1][2] = v10 - v3;
	m_unk0x10.m_m[2][0] = v8 - v4;
	m_unk0x10.m_m[2][1] = v10 + v3;
	m_unk0x10.m_m[2][2] = 1.0f - (v9 + v6);
}

// FUNCTION: GOLDP 0x10002f50
void JadeOrbit0xd0::GetUp(GolVec3* p_up)
{
	p_up->m_x = m_unk0x10.m_m[0][0];
	p_up->m_y = m_unk0x10.m_m[0][1];
	p_up->m_z = m_unk0x10.m_m[0][2];
}

// FUNCTION: GOLDP 0x10002f70
void JadeOrbit0xd0::GetForward(GolVec3* p_forward)
{
	p_forward->m_x = m_unk0x10.m_m[1][0];
	p_forward->m_y = m_unk0x10.m_m[1][1];
	p_forward->m_z = m_unk0x10.m_m[1][2];
}

// FUNCTION: GOLDP 0x10002f90
void JadeOrbit0xd0::GetRight(GolVec3* p_right)
{
	p_right->m_x = m_unk0x10.m_m[2][0];
	p_right->m_y = m_unk0x10.m_m[2][1];
	p_right->m_z = m_unk0x10.m_m[2][2];
}

// STUB: GOLDP 0x10002fb0
void JadeOrbit0xd0::VTable0x3c()
{
	STUB(0x10002fb0);
}

// FUNCTION: GOLDP 0x10002fe0
void JadeOrbit0xd0::GetPosition(GolVec3* p_position)
{
	p_position->m_x = m_unk0x10.m_m[3][0];
	p_position->m_y = m_unk0x10.m_m[3][1];
	p_position->m_z = m_unk0x10.m_m[3][2];
}

// FUNCTION: GOLDP 0x10003000
void JadeOrbit0xd0::SetPosition(GolVec3* p_position)
{
	m_unk0x10.m_m[3][0] = p_position->m_x;
	m_unk0x10.m_m[3][1] = p_position->m_y;
	m_unk0x10.m_m[3][2] = p_position->m_z;
}

// STUB: GOLDP 0x10003020
void JadeOrbit0xd0::VTable0x14()
{
	STUB(0x10003020);
}

// STUB: GOLDP 0x10003080
void JadeOrbit0xd0::VTable0x48()
{
	STUB(0x10003080);
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void JadeOrbit0xd0::VTable0x00()
{
	// empty
}
