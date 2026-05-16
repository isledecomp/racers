#include "floatybuoy0x58.h"

// FUNCTION: GOLDP 0x10026ac0
FloatyBuoy0x58::FloatyBuoy0x58()
{
	Initialize();
}

// FUNCTION: GOLDP 0x10026b10
void FloatyBuoy0x58::Reset()
{
	Initialize();
}

// FUNCTION: GOLDP 0x10026b50
void FloatyBuoy0x58::VTable0x40(const GolVec3& p_v1, const GolVec3& p_v2)
{
	GolVec3 unit;
	GolMath::NormalizeVector3(p_v1, &unit);

	LegoFloat dot = p_v2.m_y;
	dot *= unit.m_y;
	dot += unit.m_z * p_v2.m_z;
	dot += unit.m_x * p_v2.m_x;
	GolVec3 mult = dot * unit;
	GolVec3 perp;
	perp.m_x = p_v2.m_x - mult.m_x;
	perp.m_y = p_v2.m_y - mult.m_y;
	perp.m_z = p_v2.m_z - mult.m_z;
	GolMath::NormalizeVector3(perp, &perp);

	GolVec3 cross;
	cross.m_x = perp.m_y * unit.m_z - perp.m_z * unit.m_y;
	cross.m_y = perp.m_z * unit.m_x - perp.m_x * unit.m_z;
	cross.m_z = perp.m_x * unit.m_y - perp.m_y * unit.m_x;
	LegoFloat* row0 = &m_unk0x28.m_m[0][0];
	LegoFloat* row1 = &m_unk0x28.m_m[1][0];
	LegoFloat* row2 = &m_unk0x28.m_m[2][0];
	row0[0] = unit.m_x;
	row0[1] = unit.m_y;
	row1[0] = cross.m_x;
	row0[2] = unit.m_z;
	row1[1] = cross.m_y;
	row1[2] = cross.m_z;
	row2[0] = perp.m_x;
	row2[1] = perp.m_y;
	row2[2] = perp.m_z;
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
	LegoFloat x = m_unk0x28.m_m[0][0];
	x *= p_src.m_x;
	p_dest->m_x = x;
	LegoFloat y = m_unk0x28.m_m[1][0];
	y *= p_src.m_x;
	p_dest->m_y = y;
	LegoFloat z = m_unk0x28.m_m[2][0];
	z *= p_src.m_x;
	p_dest->m_z = z;

	x = m_unk0x28.m_m[0][1];
	x *= p_src.m_y;
	p_dest->m_x += x;
	y = m_unk0x28.m_m[1][1];
	y *= p_src.m_y;
	p_dest->m_y += y;
	z = m_unk0x28.m_m[2][1];
	z *= p_src.m_y;
	p_dest->m_z += z;

	x = m_unk0x28.m_m[0][2];
	x *= p_src.m_z;
	p_dest->m_x += x;
	y = m_unk0x28.m_m[1][2];
	y *= p_src.m_z;
	p_dest->m_y += y;
	z = m_unk0x28.m_m[2][2];
	z *= p_src.m_z;
	p_dest->m_z += z;

	x = m_unk0x28.m_m[3][0] * m_unk0x28.m_m[0][0];
	x += m_unk0x28.m_m[0][1] * m_unk0x28.m_m[3][1];
	x += m_unk0x28.m_m[3][2] * m_unk0x28.m_m[0][2];
	p_dest->m_x -= x;
	y = m_unk0x28.m_m[3][2] * m_unk0x28.m_m[1][2];
	y += m_unk0x28.m_m[1][1] * m_unk0x28.m_m[3][1];
	y += m_unk0x28.m_m[3][0] * m_unk0x28.m_m[1][0];
	p_dest->m_y -= y;
	z = m_unk0x28.m_m[2][2] * m_unk0x28.m_m[3][2];
	z += m_unk0x28.m_m[2][1] * m_unk0x28.m_m[3][1];
	z += m_unk0x28.m_m[3][0] * m_unk0x28.m_m[2][0];
	p_dest->m_z -= z;
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
	LegoFloat value = m_unk0x28.m_m[0][0];
	p_dest->m_m[0][0] = value * p_scale;
	value = m_unk0x28.m_m[0][1];
	p_dest->m_m[0][1] = value * p_scale;
	value = m_unk0x28.m_m[0][2];
	p_dest->m_m[0][2] = value * p_scale;
	value = m_unk0x28.m_m[1][0];
	p_dest->m_m[1][0] = value * p_scale;
	value = m_unk0x28.m_m[1][1];
	p_dest->m_m[1][1] = value * p_scale;
	value = m_unk0x28.m_m[1][2];
	p_dest->m_m[1][2] = value * p_scale;
	value = m_unk0x28.m_m[2][0];
	p_dest->m_m[2][0] = value * p_scale;
	value = m_unk0x28.m_m[2][1];
	p_dest->m_m[2][1] = value * p_scale;
	value = m_unk0x28.m_m[2][2];
	p_dest->m_m[2][2] = value * p_scale;
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
