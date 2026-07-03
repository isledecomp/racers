#include "golorientedentity.h"

#include "decomp.h"

DECOMP_SIZE_ASSERT(GolOrientedEntity, 0x58)

// FUNCTION: GOLDP 0x1001ad90 FOLDED
// FUNCTION: LEGORACERS 0x00403c90
void GolOrientedEntity::GetAxes(GolVec3* p_dest1, GolVec3* p_dest2) const
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
GolOrientedEntity::GolOrientedEntity()
{
	Reset();
}

// FUNCTION: GOLDP 0x10026b10
// FUNCTION: LEGORACERS 0x004108c0
void GolOrientedEntity::Reset()
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
void GolOrientedEntity::SetDirectionUp(const GolVec3& p_v1, const GolVec3& p_v2)
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

// FUNCTION: LEGORACERS 0x00410a00
void GolOrientedEntity::SetDirectionSide(const GolVec3& p_v1, const GolVec3& p_v2)
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
	cross.m_x = unit.m_y * perp.m_z - unit.m_z * perp.m_y;
	cross.m_y = unit.m_z;
	cross.m_y *= perp.m_x;
	cross.m_y -= unit.m_x * perp.m_z;
	cross.m_z = unit.m_x * perp.m_y;
	cross.m_z -= unit.m_y * perp.m_x;
	m_orientation.m_m[0][0] = unit.m_x;
	m_orientation.m_m[0][1] = unit.m_y;
	m_orientation.m_m[0][2] = unit.m_z;
	m_orientation.m_m[1][0] = perp.m_x;
	m_orientation.m_m[1][1] = perp.m_y;
	m_orientation.m_m[1][2] = perp.m_z;
	m_orientation.m_m[2][0] = cross.m_x;
	m_orientation.m_m[2][1] = cross.m_y;
	m_orientation.m_m[2][2] = cross.m_z;
}

// FUNCTION: LEGORACERS 0x00410b00
void GolOrientedEntity::SetUpDirection(const GolVec3& p_v1, const GolVec3& p_v2)
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
	cross.m_x = unit.m_y * perp.m_z - unit.m_z * perp.m_y;
	cross.m_y = unit.m_z * perp.m_x - unit.m_x * perp.m_z;
	cross.m_z = unit.m_x * perp.m_y - unit.m_y * perp.m_x;
	LegoFloat* row0 = &m_orientation.m_m[0][0];
	LegoFloat* row1 = &m_orientation.m_m[1][0];
	LegoFloat* row2 = &m_orientation.m_m[2][0];
	row0[0] = perp.m_x;
	row0[1] = perp.m_y;
	row1[0] = cross.m_x;
	row0[2] = perp.m_z;
	row1[1] = cross.m_y;
	row1[2] = cross.m_z;
	row2[0] = unit.m_x;
	row2[1] = unit.m_y;
	row2[2] = unit.m_z;
}

// FUNCTION: GOLDP 0x10026c50
void GolOrientedEntity::CopyOrientationToMatrix4(GolMatrix4* p_dest)
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
void GolOrientedEntity::CopyOrientation(GolMatrix3* p_dest) const
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
void GolOrientedEntity::SetOrientationMatrix(const GolMatrix3& p_matrix)
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
void GolOrientedEntity::RotateToWorld(const GolVec3& p_src, GolVec3* p_dest)
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
void GolOrientedEntity::RotateToLocal(const GolVec3& p_src, GolVec3* p_dest) const
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
void GolOrientedEntity::LocalToWorld(const GolVec3& p_src, GolVec3* p_dest) const
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
void GolOrientedEntity::WorldToLocal(const GolVec3& p_src, GolVec3* p_dest) const
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
void GolOrientedEntity::GetPosition(GolVec3* p_dest) const
{
	p_dest->m_x = m_position.m_x;
	p_dest->m_y = m_position.m_y;
	p_dest->m_z = m_position.m_z;
}

// FUNCTION: GOLDP 0x10026f50
// FUNCTION: LEGORACERS 0x00410ec0
void GolOrientedEntity::SetPosition(const GolVec3& p_pos)
{
	m_position.m_x = p_pos.m_x;
	m_position.m_y = p_pos.m_y;
	m_position.m_z = p_pos.m_z;
	m_radius = -1.0;
}

// FUNCTION: GOLDP 0x10026f70
// FUNCTION: LEGORACERS 0x00410ee0
void GolOrientedEntity::SetBoundsCenterAndSpan(const GolVec3& p_v)
{
	m_center = p_v;
	m_minX = m_center.m_x - m_radius;
	m_maxX = m_center.m_x + m_radius;
	m_minX = m_center.m_x - m_radius;
	m_maxX = m_center.m_x + m_radius;
}

// FUNCTION: LEGORACERS 0x00410f30
void GolOrientedEntity::TransformMatrixToLocal(const GolMatrix3& p_matrix, GolMatrix3* p_dest) const
{
	GolMatrix3 localMatrix;
	LegoFloat value;
	LegoFloat term;

	value = m_orientation.m_m[1][0];
	value *= p_matrix.m_m[1][0];
	term = m_orientation.m_m[2][0];
	term *= p_matrix.m_m[2][0];
	value += term;
	term = m_orientation.m_m[0][0];
	term *= p_matrix.m_m[0][0];
	localMatrix.m_m[0][0] = value + term;

	value = p_matrix.m_m[2][1] * m_orientation.m_m[2][0];
	value += m_orientation.m_m[1][0] * p_matrix.m_m[1][1];
	localMatrix.m_m[0][1] = value + p_matrix.m_m[0][1] * m_orientation.m_m[0][0];

	value = p_matrix.m_m[2][2] * m_orientation.m_m[2][0];
	value += m_orientation.m_m[1][0] * p_matrix.m_m[1][2];
	localMatrix.m_m[0][2] = value + p_matrix.m_m[0][2] * m_orientation.m_m[0][0];

	value = m_orientation.m_m[2][1] * p_matrix.m_m[2][0];
	value += p_matrix.m_m[1][0] * m_orientation.m_m[1][1];
	localMatrix.m_m[1][0] = value + m_orientation.m_m[0][1] * p_matrix.m_m[0][0];

	value = m_orientation.m_m[2][1] * p_matrix.m_m[2][1];
	value += m_orientation.m_m[0][1] * p_matrix.m_m[0][1];
	localMatrix.m_m[1][1] = value + m_orientation.m_m[1][1] * p_matrix.m_m[1][1];

	value = m_orientation.m_m[2][1] * p_matrix.m_m[2][2];
	value += m_orientation.m_m[0][1] * p_matrix.m_m[0][2];
	localMatrix.m_m[1][2] = value + m_orientation.m_m[1][1] * p_matrix.m_m[1][2];

	value = m_orientation.m_m[2][2] * p_matrix.m_m[2][0];
	value += p_matrix.m_m[1][0] * m_orientation.m_m[1][2];
	localMatrix.m_m[2][0] = value + m_orientation.m_m[0][2] * p_matrix.m_m[0][0];

	value = m_orientation.m_m[2][2] * p_matrix.m_m[2][1];
	value += m_orientation.m_m[0][2] * p_matrix.m_m[0][1];
	localMatrix.m_m[2][1] = value + m_orientation.m_m[1][2] * p_matrix.m_m[1][1];

	value = m_orientation.m_m[2][2] * p_matrix.m_m[2][2];
	value += m_orientation.m_m[0][2] * p_matrix.m_m[0][2];
	localMatrix.m_m[2][2] = value + m_orientation.m_m[1][2] * p_matrix.m_m[1][2];

	GolMath::MultiplyMatrix3(&localMatrix.m_m[0][0], &m_orientation.m_m[0][0], &p_dest->m_m[0][0]);
}

// FUNCTION: LEGORACERS 0x00411040
void GolOrientedEntity::MirrorY()
{
	GolVec3 right;
	right.m_x = m_orientation.m_m[0][0];
	right.m_y = -m_orientation.m_m[0][1];
	right.m_z = m_orientation.m_m[0][2];

	GolVec3 forward;
	forward.m_x = m_orientation.m_m[2][0];
	forward.m_y = -m_orientation.m_m[2][1];
	forward.m_z = m_orientation.m_m[2][2];

	m_position.m_y = -m_position.m_y;
	SetDirectionUp(right, forward);
}

// FUNCTION: GOLDP 0x10026fc0
void GolOrientedEntity::CopyScaledOrientationTo(GolMatrix4* p_dest, LegoFloat p_scale) const
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
