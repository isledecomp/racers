#include "floatybuoy0x58.h"

// FUNCTION: GOLDP 0x10026ac0
FloatyBuoy0x58::FloatyBuoy0x58()
{
	m_v2.m_x = 0.0f;
	m_v2.m_y = 0.0f;
	m_v2.m_z = 0.0f;
	m_unk0x28.m_m[0][1] = 0.0f;
	m_unk0x28.m_m[0][2] = 0.0f;
	m_unk0x28.m_m[1][0] = 0.0f;
	m_unk0x28.m_m[1][2] = 0.0f;
	m_unk0x28.m_m[2][0] = 0.0f;
	m_unk0x28.m_m[2][1] = 0.0f;
	m_unk0x28.m_m[3][0] = 0.0f;
	m_unk0x28.m_m[3][1] = 0.0f;
	m_unk0x28.m_m[3][2] = 0.0f;
	m_unk0x28.m_m[0][0] = 1.0f;
	m_unk0x28.m_m[1][1] = 1.0f;
	m_unk0x28.m_m[2][2] = 1.0f;
}

// FUNCTION: GOLDP 0x10026b10
void FloatyBuoy0x58::FUN_10026b10()
{
	m_v2.m_x = 0.0f;
	m_v2.m_y = 0.0f;
	m_v2.m_z = 0.0f;
	m_unk0x28.m_m[0][0] = 1.0f;
	m_unk0x28.m_m[0][1] = 0.0f;
	m_unk0x28.m_m[0][2] = 0.0f;
	m_unk0x28.m_m[1][0] = 0.0f;
	m_unk0x28.m_m[1][1] = 1.0f;
	m_unk0x28.m_m[1][2] = 0.0f;
	m_unk0x28.m_m[2][0] = 0.0f;
	m_unk0x28.m_m[2][1] = 0.0f;
	m_unk0x28.m_m[2][2] = 1.0f;
	m_unk0x28.m_m[3][0] = 0.0f;
	m_unk0x28.m_m[3][1] = 0.0f;
	m_unk0x28.m_m[3][2] = 0.0f;
}

// FUNCTION: GOLDP 0x10026b50
void FloatyBuoy0x58::VTable0x40(const GolVec3& p_v1, const GolVec3& p_v2)
{
	GolVec3 v1Unit;
	GolMath::NormalizeVector3(p_v1, &v1Unit);
	LegoFloat dot = GOLVECTOR3_DOT(v1Unit, p_v2);
	GolVec3 mult = dot * v1Unit;
	GolVec3 v1Perp = p_v2;
	v1Perp -= mult;
	GolMath::NormalizeVector3(v1Perp, &v1Perp);
	m_unk0x28.m_m[0][0] = v1Unit.m_x;
	m_unk0x28.m_m[0][1] = v1Unit.m_y;
	m_unk0x28.m_m[0][2] = v1Unit.m_z;
	m_unk0x28.m_m[1][0] = v1Perp.m_y * v1Unit.m_z - v1Perp.m_z * v1Unit.m_y;
	m_unk0x28.m_m[1][1] = v1Perp.m_z * v1Unit.m_x - v1Perp.m_x * v1Unit.m_z;
	m_unk0x28.m_m[1][2] = v1Perp.m_x * v1Unit.m_y - v1Perp.m_y * v1Unit.m_x;
	m_unk0x28.m_m[2][0] = v1Perp.m_x;
	m_unk0x28.m_m[2][1] = v1Perp.m_y;
	m_unk0x28.m_m[2][2] = v1Perp.m_z;
}

// FUNCTION: GOLDP 0x10026c50
void FloatyBuoy0x58::FUN_10026c50(GolMatrix4* p_dest)

{
	p_dest->m_m[0][0] = m_unk0x28.m_m[0][0];
	p_dest->m_m[0][1] = m_unk0x28.m_m[0][1];
	p_dest->m_m[0][2] = m_unk0x28.m_m[0][2];
	p_dest->m_m[1][0] = m_unk0x28.m_m[1][0];
	p_dest->m_m[1][1] = m_unk0x28.m_m[1][1];
	p_dest->m_m[1][2] = m_unk0x28.m_m[1][2];
	p_dest->m_m[2][0] = m_unk0x28.m_m[2][0];
	p_dest->m_m[2][1] = m_unk0x28.m_m[2][1];
	p_dest->m_m[2][2] = m_unk0x28.m_m[2][2];
}

// FUNCTION: GOLDP 0x10026c90
void FloatyBuoy0x58::VTable0x44(GolMatrix3* p_dest) const

{
	p_dest->m_m[0][0] = m_unk0x28.m_m[0][0];
	p_dest->m_m[0][1] = m_unk0x28.m_m[0][1];
	p_dest->m_m[0][2] = m_unk0x28.m_m[0][2];
	p_dest->m_m[1][0] = m_unk0x28.m_m[1][0];
	p_dest->m_m[1][1] = m_unk0x28.m_m[1][1];
	p_dest->m_m[1][2] = m_unk0x28.m_m[1][2];
	p_dest->m_m[2][0] = m_unk0x28.m_m[2][0];
	p_dest->m_m[2][1] = m_unk0x28.m_m[2][1];
	p_dest->m_m[2][2] = m_unk0x28.m_m[2][2];
}

// FUNCTION: GOLDP 0x10026cd0
void FloatyBuoy0x58::VTable0x3c(const GolMatrix34& p_matrix)
{
	m_unk0x28.m_m[0][0] = p_matrix.m_m[0][0];
	m_unk0x28.m_m[0][1] = p_matrix.m_m[0][1];
	m_unk0x28.m_m[0][2] = p_matrix.m_m[0][2];
	m_unk0x28.m_m[1][0] = p_matrix.m_m[1][0];
	m_unk0x28.m_m[1][1] = p_matrix.m_m[1][1];
	m_unk0x28.m_m[1][2] = p_matrix.m_m[1][2];
	m_unk0x28.m_m[2][0] = p_matrix.m_m[2][0];
	m_unk0x28.m_m[2][1] = p_matrix.m_m[2][1];
	m_unk0x28.m_m[2][2] = p_matrix.m_m[2][2];
}

// FUNCTION: GOLDP 0x10026d10
void FloatyBuoy0x58::VTable0x34(const GolVec3& p_src, GolVec3* p_dest)

{
	p_dest->m_x = m_unk0x28.m_m[0][0] * p_src.m_x;
	p_dest->m_y = m_unk0x28.m_m[0][1] * p_src.m_x;
	p_dest->m_z = m_unk0x28.m_m[0][2] * p_src.m_x;
	p_dest->m_x += m_unk0x28.m_m[1][0] * p_src.m_y;
	p_dest->m_y += m_unk0x28.m_m[1][1] * p_src.m_y;
	p_dest->m_z += m_unk0x28.m_m[1][2] * p_src.m_y;
	p_dest->m_x += m_unk0x28.m_m[2][0] * p_src.m_z;
	p_dest->m_y += m_unk0x28.m_m[2][1] * p_src.m_z;
	p_dest->m_z += m_unk0x28.m_m[2][2] * p_src.m_z;
}

// FUNCTION: GOLDP 0x10026d80
void FloatyBuoy0x58::VTable0x38(const GolVec3& p_src, GolVec3* p_dest) const
{
	p_dest->m_x = m_unk0x28.m_m[0][0] * p_src.m_x;
	p_dest->m_y = m_unk0x28.m_m[1][0] * p_src.m_x;
	p_dest->m_z = m_unk0x28.m_m[2][0] * p_src.m_x;
	p_dest->m_x += m_unk0x28.m_m[0][1] * p_src.m_y;
	p_dest->m_y += m_unk0x28.m_m[1][1] * p_src.m_y;
	p_dest->m_z += m_unk0x28.m_m[2][1] * p_src.m_y;
	p_dest->m_x += m_unk0x28.m_m[0][2] * p_src.m_z;
	p_dest->m_y += m_unk0x28.m_m[1][2] * p_src.m_z;
	p_dest->m_z += m_unk0x28.m_m[2][2] * p_src.m_z;
}

// FUNCTION: GOLDP 0x10026df0
void FloatyBuoy0x58::VTable0x2c(const GolVec3& p_src, GolVec3* p_dest) const
{
	p_dest->m_x = m_unk0x28.m_m[0][0] * p_src.m_x;
	p_dest->m_y = m_unk0x28.m_m[0][1] * p_src.m_x;
	p_dest->m_z = m_unk0x28.m_m[0][2] * p_src.m_x;
	p_dest->m_x += m_unk0x28.m_m[1][0] * p_src.m_y;
	p_dest->m_y += m_unk0x28.m_m[1][1] * p_src.m_y;
	p_dest->m_z += m_unk0x28.m_m[1][2] * p_src.m_y;
	p_dest->m_x += m_unk0x28.m_m[2][0] * p_src.m_z;
	p_dest->m_y += m_unk0x28.m_m[2][1] * p_src.m_z;
	p_dest->m_z += m_unk0x28.m_m[2][2] * p_src.m_z;
	p_dest->m_x += m_unk0x28.m_m[3][0];
	p_dest->m_y += m_unk0x28.m_m[3][1];
	p_dest->m_z += m_unk0x28.m_m[3][2];
}

// FUNCTION: GOLDP 0x10026e70
void FloatyBuoy0x58::VTable0x30(const GolVec3& p_src, GolVec3* p_dest) const
{
	p_dest->m_x = m_unk0x28.m_m[0][0] * p_src.m_x;
	p_dest->m_y = m_unk0x28.m_m[1][0] * p_src.m_x;
	p_dest->m_z = m_unk0x28.m_m[2][0] * p_src.m_x;
	p_dest->m_x += m_unk0x28.m_m[0][1] * p_src.m_y;
	p_dest->m_y += m_unk0x28.m_m[1][1] * p_src.m_y;
	p_dest->m_z += m_unk0x28.m_m[2][1] * p_src.m_y;
	p_dest->m_x += m_unk0x28.m_m[0][2] * p_src.m_z;
	p_dest->m_y += m_unk0x28.m_m[1][2] * p_src.m_z;
	p_dest->m_z += m_unk0x28.m_m[2][2] * p_src.m_z;

	p_dest->m_x = p_dest->m_x - (m_unk0x28.m_m[3][0] * m_unk0x28.m_m[0][0] + m_unk0x28.m_m[3][1] * m_unk0x28.m_m[0][1] +
								 m_unk0x28.m_m[3][2] * m_unk0x28.m_m[0][2]);
	p_dest->m_y = p_dest->m_y - (m_unk0x28.m_m[3][0] * m_unk0x28.m_m[1][0] + m_unk0x28.m_m[3][1] * m_unk0x28.m_m[1][1] +
								 m_unk0x28.m_m[3][2] * m_unk0x28.m_m[1][2]);
	p_dest->m_z = p_dest->m_z - (m_unk0x28.m_m[3][0] * m_unk0x28.m_m[2][0] + m_unk0x28.m_m[3][1] * m_unk0x28.m_m[2][1] +
								 m_unk0x28.m_m[2][2] * m_unk0x28.m_m[3][2]);
}

// FUNCTION: GOLDP 0x10026f30
void FloatyBuoy0x58::VTable0x04(GolVec3* p_dest) const
{
	p_dest->m_x = m_unk0x28.m_m[3][0];
	p_dest->m_y = m_unk0x28.m_m[3][1];
	p_dest->m_z = m_unk0x28.m_m[3][2];
}

// FUNCTION: GOLDP 0x10026f50
void FloatyBuoy0x58::VTable0x08(const GolVec3& p_pos)

{
	m_unk0x28.m_m[3][0] = p_pos.m_x;
	m_unk0x28.m_m[3][1] = p_pos.m_y;
	m_unk0x28.m_m[3][2] = p_pos.m_z;
	m_v1.m_x = -1.0;
}

// FUNCTION: GOLDP 0x10026f70
void FloatyBuoy0x58::FUN_10026f70(const GolVec3& p_v)
{

	m_v0 = p_v;
	m_v1.m_y = m_v0.m_x - m_v1.m_x;
	m_v1.m_z = m_v0.m_x + m_v1.m_x;
	m_v1.m_y = m_v0.m_x - m_v1.m_x;
	m_v1.m_z = m_v0.m_x + m_v1.m_x;
}

// FUNCTION: GOLDP 0x10026fa0 FOLDED
void FloatyBuoy0x58::FUN_10026fa0(float p_scalar)
{
	m_v1.m_x = p_scalar;
	m_v1.m_y = m_v0.m_x - p_scalar;
	m_v1.m_z = p_scalar + m_v0.m_x;
}

// FUNCTION: GOLDP 0x10026fc0
void FloatyBuoy0x58::FUN_10026fc0(GolMatrix4* p_dest, float p_scale) const

{
	p_dest->m_m[0][0] = m_unk0x28.m_m[0][0] * p_scale;
	p_dest->m_m[0][1] = m_unk0x28.m_m[0][1] * p_scale;
	p_dest->m_m[0][2] = m_unk0x28.m_m[0][2] * p_scale;
	p_dest->m_m[1][0] = m_unk0x28.m_m[1][0] * p_scale;
	p_dest->m_m[1][1] = m_unk0x28.m_m[1][1] * p_scale;
	p_dest->m_m[1][2] = m_unk0x28.m_m[1][2] * p_scale;
	p_dest->m_m[2][0] = m_unk0x28.m_m[2][0] * p_scale;
	p_dest->m_m[2][1] = m_unk0x28.m_m[2][1] * p_scale;
	p_dest->m_m[2][2] = m_unk0x28.m_m[2][2] * p_scale;
}

// FUNCTION: GOLDP 0x1001ad90 FOLDED
void FloatyBuoy0x58::VTable0x48(GolVec3* p_dest1, GolVec3* p_dest2) const

{
	p_dest1->m_x = m_unk0x28.m_m[0][0];
	p_dest1->m_y = m_unk0x28.m_m[0][1];
	p_dest1->m_z = m_unk0x28.m_m[0][2];
	p_dest2->m_x = m_unk0x28.m_m[2][0];
	p_dest2->m_y = m_unk0x28.m_m[2][1];
	p_dest2->m_z = m_unk0x28.m_m[2][2];
}
