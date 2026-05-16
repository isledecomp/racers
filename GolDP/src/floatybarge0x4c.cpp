#include "floatybarge0x4c.h"

// STUB: GOLDP 0x10014e50
LegoBool32 FloatyPontoon0x4c::FUN_10014e50(const GolVec3* p_arg1, const GolVec3* p_arg2, GolMatrix4* p_matrix)
{
	GolVec3 row0;
	GolVec3 row1;
	GolVec3 position;
	const GolVec3* row2;

	FUN_100286d0(&position);

	row0.m_x = -p_arg1->m_x;
	row0.m_y = -p_arg1->m_y;
	row0.m_z = -p_arg1->m_z;

	if (m_flags & c_flagBit1) {
		row2 = &m_unk0x30;
		LegoFloat dot = row2->m_z * row0.m_z + row0.m_y * row2->m_y + row0.m_x * row2->m_x;
		row0.m_x -= dot * row2->m_x;
		row0.m_y -= row2->m_y * dot;
		row0.m_z -= row2->m_z * dot;
	}
	else {
		row2 = p_arg2;
	}

	GolMath::NormalizeVector3(row0, &row0);

	row1.m_x = row0.m_z * row2->m_y - row2->m_z * row0.m_y;
	row1.m_y = row2->m_z * row0.m_x - row0.m_z * row2->m_x;
	row1.m_z = row0.m_y * row2->m_x - row2->m_y * row0.m_x;

	p_matrix->m_m[0][0] = row0.m_x;
	p_matrix->m_m[0][1] = row0.m_y;
	p_matrix->m_m[0][2] = row0.m_z;
	p_matrix->m_m[0][3] = 0.0f;

	p_matrix->m_m[1][0] = row1.m_x;
	p_matrix->m_m[1][1] = row1.m_y;
	p_matrix->m_m[1][2] = row1.m_z;
	p_matrix->m_m[1][3] = 0.0f;

	p_matrix->m_m[2][0] = row2->m_x;
	p_matrix->m_m[2][1] = row2->m_y;
	p_matrix->m_m[2][2] = row2->m_z;
	p_matrix->m_m[2][3] = 0.0f;

	LegoFloat halfWidth = m_width * 0.5f;
	LegoFloat halfHeight = m_height * 0.5f;
	p_matrix->m_m[3][0] = position.m_x - halfWidth * row1.m_x - halfHeight * row2->m_x;
	p_matrix->m_m[3][1] = position.m_y - halfWidth * row1.m_y - halfHeight * row2->m_y;
	p_matrix->m_m[3][2] = position.m_z - halfWidth * row1.m_z - halfHeight * row2->m_z;
	p_matrix->m_m[3][3] = 1.0f;

	return TRUE;
}

// FUNCTION: GOLDP 0x10014fd0
void FloatyBarge0x4c::VTable0x4c(
	undefined4* p_position,
	LegoFloat p_width,
	LegoFloat p_height,
	LegoFloat p_maxDistanceSquared
)
{
	FloatyPontoon0x4c::VTable0x4c(p_position, p_width, p_height, p_maxDistanceSquared);
}

// STUB: GOLDP 0x10014ff0
void FloatyPontoon0x4c::FUN_10014ff0(BronzeFalcon0xc8770*)
{
	// TODO
	STUB(0x10014ff0);
}
