#include "floatybuoy0x58.h"

// FUNCTION: GOLDP 0x1001ad90 FOLDED
// FUNCTION: LEGORACERS 0x00403c90
void FloatyBuoy0x58::VTable0x48(GolVec3* p_dest1, GolVec3* p_dest2) const
{
	p_dest1->m_x = m_orientation.m_m[0][0];
	p_dest1->m_y = m_orientation.m_m[0][1];
	p_dest1->m_z = m_orientation.m_m[0][2];
	p_dest2->m_x = m_orientation.m_m[2][0];
	p_dest2->m_y = m_orientation.m_m[2][1];
	p_dest2->m_z = m_orientation.m_m[2][2];
}

// FUNCTION: GOLDP 0x10026ac0
// FUNCTION: LEGORACERS 0x004108a0
FloatyBuoy0x58::FloatyBuoy0x58()
{
	Reset();
}

// FUNCTION: GOLDP 0x10026b10
// FUNCTION: LEGORACERS 0x004108c0
void FloatyBuoy0x58::Reset()
{
	m_velocity.m_x = 0.0f;
	m_velocity.m_y = 0.0f;
	m_velocity.m_z = 0.0f;
	m_orientation.m_m[0][0] = 1.0f;
	m_orientation.m_m[0][1] = 0.0f;
	m_orientation.m_m[0][2] = 0.0f;
	m_orientation.m_m[1][0] = 0.0f;
	m_orientation.m_m[1][1] = 1.0f;
	m_orientation.m_m[1][2] = 0.0f;
	m_orientation.m_m[2][0] = 0.0f;
	m_orientation.m_m[2][1] = 0.0f;
	m_orientation.m_m[2][2] = 1.0f;
	m_position.m_x = 0.0f;
	m_position.m_y = 0.0f;
	m_position.m_z = 0.0f;
}

// FUNCTION: GOLDP 0x10026b50
// FUNCTION: LEGORACERS 0x00410900
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
	LegoFloat* row0 = &m_orientation.m_m[0][0];
	LegoFloat* row1 = &m_orientation.m_m[1][0];
	LegoFloat* row2 = &m_orientation.m_m[2][0];
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
	p_dest->m_m[0][0] = m_orientation.m_m[0][0];
	p_dest->m_m[0][1] = m_orientation.m_m[0][1];
	p_dest->m_m[0][2] = m_orientation.m_m[0][2];
	p_dest->m_m[1][0] = m_orientation.m_m[1][0];
	p_dest->m_m[1][1] = m_orientation.m_m[1][1];
	p_dest->m_m[1][2] = m_orientation.m_m[1][2];
	p_dest->m_m[2][0] = m_orientation.m_m[2][0];
	p_dest->m_m[2][1] = m_orientation.m_m[2][1];
	p_dest->m_m[2][2] = m_orientation.m_m[2][2];
}

// FUNCTION: GOLDP 0x10026c90
// FUNCTION: LEGORACERS 0x00410c00
void FloatyBuoy0x58::VTable0x44(GolMatrix3* p_dest) const
{
	p_dest->m_m[0][0] = m_orientation.m_m[0][0];
	p_dest->m_m[0][1] = m_orientation.m_m[0][1];
	p_dest->m_m[0][2] = m_orientation.m_m[0][2];
	p_dest->m_m[1][0] = m_orientation.m_m[1][0];
	p_dest->m_m[1][1] = m_orientation.m_m[1][1];
	p_dest->m_m[1][2] = m_orientation.m_m[1][2];
	p_dest->m_m[2][0] = m_orientation.m_m[2][0];
	p_dest->m_m[2][1] = m_orientation.m_m[2][1];
	p_dest->m_m[2][2] = m_orientation.m_m[2][2];
}

// FUNCTION: GOLDP 0x10026cd0
// FUNCTION: LEGORACERS 0x00410c40
void FloatyBuoy0x58::VTable0x3c(const GolMatrix34& p_matrix)
{
	m_orientation.m_m[0][0] = p_matrix.m_m[0][0];
	m_orientation.m_m[0][1] = p_matrix.m_m[0][1];
	m_orientation.m_m[0][2] = p_matrix.m_m[0][2];
	m_orientation.m_m[1][0] = p_matrix.m_m[1][0];
	m_orientation.m_m[1][1] = p_matrix.m_m[1][1];
	m_orientation.m_m[1][2] = p_matrix.m_m[1][2];
	m_orientation.m_m[2][0] = p_matrix.m_m[2][0];
	m_orientation.m_m[2][1] = p_matrix.m_m[2][1];
	m_orientation.m_m[2][2] = p_matrix.m_m[2][2];
}

// FUNCTION: GOLDP 0x10026d10
// FUNCTION: LEGORACERS 0x00410c80
void FloatyBuoy0x58::VTable0x34(const GolVec3& p_src, GolVec3* p_dest)
{
	p_dest->m_x = m_orientation.m_m[0][0] * p_src.m_x;
	p_dest->m_y = m_orientation.m_m[0][1] * p_src.m_x;
	p_dest->m_z = m_orientation.m_m[0][2] * p_src.m_x;
	p_dest->m_x += m_orientation.m_m[1][0] * p_src.m_y;
	p_dest->m_y += m_orientation.m_m[1][1] * p_src.m_y;
	p_dest->m_z += m_orientation.m_m[1][2] * p_src.m_y;
	p_dest->m_x += m_orientation.m_m[2][0] * p_src.m_z;
	p_dest->m_y += m_orientation.m_m[2][1] * p_src.m_z;
	p_dest->m_z += m_orientation.m_m[2][2] * p_src.m_z;
}

// FUNCTION: GOLDP 0x10026d80
// FUNCTION: LEGORACERS 0x00410cf0
void FloatyBuoy0x58::VTable0x38(const GolVec3& p_src, GolVec3* p_dest) const
{
	p_dest->m_x = m_orientation.m_m[0][0] * p_src.m_x;
	p_dest->m_y = m_orientation.m_m[1][0] * p_src.m_x;
	p_dest->m_z = m_orientation.m_m[2][0] * p_src.m_x;
	p_dest->m_x += m_orientation.m_m[0][1] * p_src.m_y;
	p_dest->m_y += m_orientation.m_m[1][1] * p_src.m_y;
	p_dest->m_z += m_orientation.m_m[2][1] * p_src.m_y;
	p_dest->m_x += m_orientation.m_m[0][2] * p_src.m_z;
	p_dest->m_y += m_orientation.m_m[1][2] * p_src.m_z;
	p_dest->m_z += m_orientation.m_m[2][2] * p_src.m_z;
}

// FUNCTION: GOLDP 0x10026df0
// FUNCTION: LEGORACERS 0x00410d60
void FloatyBuoy0x58::VTable0x2c(const GolVec3& p_src, GolVec3* p_dest) const
{
	p_dest->m_x = m_orientation.m_m[0][0] * p_src.m_x;
	p_dest->m_y = m_orientation.m_m[0][1] * p_src.m_x;
	p_dest->m_z = m_orientation.m_m[0][2] * p_src.m_x;
	p_dest->m_x += m_orientation.m_m[1][0] * p_src.m_y;
	p_dest->m_y += m_orientation.m_m[1][1] * p_src.m_y;
	p_dest->m_z += m_orientation.m_m[1][2] * p_src.m_y;
	p_dest->m_x += m_orientation.m_m[2][0] * p_src.m_z;
	p_dest->m_y += m_orientation.m_m[2][1] * p_src.m_z;
	p_dest->m_z += m_orientation.m_m[2][2] * p_src.m_z;
	p_dest->m_x += m_position.m_x;
	p_dest->m_y += m_position.m_y;
	p_dest->m_z += m_position.m_z;
}

// FUNCTION: GOLDP 0x10026e70
// FUNCTION: LEGORACERS 0x00410de0
void FloatyBuoy0x58::VTable0x30(const GolVec3& p_src, GolVec3* p_dest) const
{
	LegoFloat x = m_orientation.m_m[0][0];
	x *= p_src.m_x;
	p_dest->m_x = x;
	LegoFloat y = m_orientation.m_m[1][0];
	y *= p_src.m_x;
	p_dest->m_y = y;
	LegoFloat z = m_orientation.m_m[2][0];
	z *= p_src.m_x;
	p_dest->m_z = z;

	x = m_orientation.m_m[0][1];
	x *= p_src.m_y;
	p_dest->m_x += x;
	y = m_orientation.m_m[1][1];
	y *= p_src.m_y;
	p_dest->m_y += y;
	z = m_orientation.m_m[2][1];
	z *= p_src.m_y;
	p_dest->m_z += z;

	x = m_orientation.m_m[0][2];
	x *= p_src.m_z;
	p_dest->m_x += x;
	y = m_orientation.m_m[1][2];
	y *= p_src.m_z;
	p_dest->m_y += y;
	z = m_orientation.m_m[2][2];
	z *= p_src.m_z;
	p_dest->m_z += z;

	x = m_position.m_x * m_orientation.m_m[0][0];
	x += m_orientation.m_m[0][1] * m_position.m_y;
	x += m_position.m_z * m_orientation.m_m[0][2];
	p_dest->m_x -= x;
	y = m_position.m_z * m_orientation.m_m[1][2];
	y += m_orientation.m_m[1][1] * m_position.m_y;
	y += m_position.m_x * m_orientation.m_m[1][0];
	p_dest->m_y -= y;
	z = m_orientation.m_m[2][2] * m_position.m_z;
	z += m_orientation.m_m[2][1] * m_position.m_y;
	z += m_position.m_x * m_orientation.m_m[2][0];
	p_dest->m_z -= z;
}

// FUNCTION: GOLDP 0x10026f30
// FUNCTION: LEGORACERS 0x00410ea0
void FloatyBuoy0x58::VTable0x04(GolVec3* p_dest) const
{
	p_dest->m_x = m_position.m_x;
	p_dest->m_y = m_position.m_y;
	p_dest->m_z = m_position.m_z;
}

// FUNCTION: GOLDP 0x10026f50
// FUNCTION: LEGORACERS 0x00410ec0
void FloatyBuoy0x58::VTable0x08(const GolVec3& p_pos)
{
	m_position.m_x = p_pos.m_x;
	m_position.m_y = p_pos.m_y;
	m_position.m_z = p_pos.m_z;
	m_radius = -1.0;
}

// FUNCTION: GOLDP 0x10026f70
// FUNCTION: LEGORACERS 0x00410ee0
void FloatyBuoy0x58::FUN_10026f70(const GolVec3& p_v)
{
	m_center = p_v;
	m_minX = m_center.m_x - m_radius;
	m_maxX = m_center.m_x + m_radius;
	m_minX = m_center.m_x - m_radius;
	m_maxX = m_center.m_x + m_radius;
}

// FUNCTION: GOLDP 0x10026fa0 FOLDED
// FUNCTION: LEGORACERS 0x00410f10
void FloatyBuoy0x58::FUN_10026fa0(float p_scalar)
{
	m_radius = p_scalar;
	m_minX = m_center.m_x - p_scalar;
	m_maxX = p_scalar + m_center.m_x;
}

// FUNCTION: GOLDP 0x10026fc0
void FloatyBuoy0x58::FUN_10026fc0(GolMatrix4* p_dest, float p_scale) const
{
	LegoFloat value = m_orientation.m_m[0][0];
	p_dest->m_m[0][0] = value * p_scale;
	value = m_orientation.m_m[0][1];
	p_dest->m_m[0][1] = value * p_scale;
	value = m_orientation.m_m[0][2];
	p_dest->m_m[0][2] = value * p_scale;
	value = m_orientation.m_m[1][0];
	p_dest->m_m[1][0] = value * p_scale;
	value = m_orientation.m_m[1][1];
	p_dest->m_m[1][1] = value * p_scale;
	value = m_orientation.m_m[1][2];
	p_dest->m_m[1][2] = value * p_scale;
	value = m_orientation.m_m[2][0];
	p_dest->m_m[2][0] = value * p_scale;
	value = m_orientation.m_m[2][1];
	p_dest->m_m[2][1] = value * p_scale;
	value = m_orientation.m_m[2][2];
	p_dest->m_m[2][2] = value * p_scale;
}
