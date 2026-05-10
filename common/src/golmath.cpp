#include "golmath.h"

#include <math.h>

DECOMP_SIZE_ASSERT(GolVec2, 0x8)
DECOMP_SIZE_ASSERT(GolVec3, 0xc)
DECOMP_SIZE_ASSERT(GolMatrix4, 0x40)
DECOMP_SIZE_ASSERT(GolQuat, 0x10)

// FUNCTION: GOLDP 0x1002f3a0
void GolMath::FUN_1002f3a0(const GolMatrix4& p_left, const GolMatrix4& p_right, GolMatrix4* p_dest)
{
	LegoU32 i;
	const LegoFloat(*leftRow)[4] = &p_left.m_m[0];
	LegoFloat(*destRow)[4] = &p_dest->m_m[0];
	for (i = 0; i < 4; i++, leftRow += 1, destRow += 1) {
		(*destRow)[0] = (*leftRow)[0] * p_right.m_m[0][0];
		(*destRow)[1] = (*leftRow)[0] * p_right.m_m[0][1];
		(*destRow)[2] = (*leftRow)[0] * p_right.m_m[0][2];
		(*destRow)[3] = (*leftRow)[0] * p_right.m_m[0][3];

		(*destRow)[0] += (*leftRow)[1] * p_right.m_m[1][0];
		(*destRow)[1] += (*leftRow)[1] * p_right.m_m[1][1];
		(*destRow)[2] += (*leftRow)[1] * p_right.m_m[1][2];
		(*destRow)[3] += (*leftRow)[1] * p_right.m_m[1][3];

		(*destRow)[0] += (*leftRow)[2] * p_right.m_m[2][0];
		(*destRow)[1] += (*leftRow)[2] * p_right.m_m[2][1];
		(*destRow)[2] += (*leftRow)[2] * p_right.m_m[2][2];
		(*destRow)[3] += (*leftRow)[2] * p_right.m_m[2][3];

		(*destRow)[0] += (*leftRow)[3] * p_right.m_m[3][0];
		(*destRow)[1] += (*leftRow)[3] * p_right.m_m[3][1];
		(*destRow)[2] += (*leftRow)[3] * p_right.m_m[3][2];
		(*destRow)[3] += (*leftRow)[3] * p_right.m_m[3][3];
	}
}

// FUNCTION: GOLDP 0x1002f450
void GolMath::FUN_1002f450(const GolMatrix4& p_left, const GolMatrix4& p_right, GolMatrix4* p_dest)
{
	LegoU32 i;
	for (i = 0; i < 3; i++) {
		p_dest->m_m[0][i] = p_left.m_m[0][0] * p_right.m_m[0][i] + p_left.m_m[0][1] * p_right.m_m[1][i] +
							p_left.m_m[0][2] * p_right.m_m[2][i];
		p_dest->m_m[1][i] = p_left.m_m[1][0] * p_right.m_m[0][i] + p_left.m_m[1][1] * p_right.m_m[1][i] +
							p_left.m_m[1][2] * p_right.m_m[2][i];
		p_dest->m_m[2][i] = p_left.m_m[2][0] * p_right.m_m[0][i] + p_left.m_m[2][1] * p_right.m_m[1][i] +
							p_left.m_m[2][2] * p_right.m_m[2][i];
		p_dest->m_m[3][i] = p_left.m_m[3][0] * p_right.m_m[0][i] + p_left.m_m[3][1] * p_right.m_m[1][i] +
							p_left.m_m[3][2] * p_right.m_m[2][i] + p_right.m_m[3][i];
	}
}

// STUB: LEGORACERS 0x00449170
void GolMath::FUN_00449170(LegoFloat, LegoFloat*, LegoFloat*)
{
	STUB(0x00449170);
}

// STUB: LEGORACERS 0x00449190
void GolMath::FUN_00449190(const LegoFloat*, const LegoFloat*, LegoFloat*)
{
	STUB(0x00449190);
}

// FUNCTION: GOLDP 0x1002f4e0
// FUNCTION: LEGORACERS 0x00449280
void __fastcall GolMath::NormalizeVector2(const GolVec2& p_src, GolVec2& p_dest)
{
	LegoFloat x = p_src.m_x;
	LegoFloat y = p_src.m_y;
	LegoFloat lengthSquared = x * x;
	lengthSquared += y * y;
	LegoFloat length = (LegoFloat) sqrt(lengthSquared);

	if (length == 0.0) {
		p_dest.m_x = 0.0f;
		p_dest.m_y = 0.0f;
	}
	else {
		LegoFloat scale = 1.0f / length;
		p_dest.m_x = x * scale;
		p_dest.m_y = y * scale;
	}
}

// FUNCTION: GOLDP 0x1002f530
// FUNCTION: LEGORACERS 0x004492d0
void __fastcall GolMath::NormalizeVector3(const GolVec3& p_src, GolVec3& p_dest)
{
	LegoFloat x = p_src.m_x;
	// TODO: Find the original clean source form. The double cast is only here
	// to make VC6 spill y through the FPU instead of using an integer move.
	LegoFloat y = (LegoFloat) ((double) p_src.m_y);
	LegoFloat z = p_src.m_z;
	LegoFloat lengthSquared = x * x;
	lengthSquared += y * y;
	LegoFloat length = (LegoFloat) sqrt(lengthSquared + (z * z));

	if (length == 0.0) {
		p_dest.m_x = 0.0f;
		p_dest.m_y = 0.0f;
		p_dest.m_z = 0.0f;
	}
	else {
		LegoFloat scale = 1.0f / length;
		p_dest.m_x = x * scale;
		p_dest.m_y = y * scale;
		p_dest.m_z = z * scale;
	}
}

// STUB: LEGORACERS 0x00449340
void GolMath::FUN_00449340(const GolQuat*, LegoFloat*)
{
	STUB(0x00449340);
}

// FUNCTION: GOLDP 0x1002f5a0
// FUNCTION: LEGORACERS 0x00449460
void GolMath::FUN_1002f5a0(const GolMatrix4& p_matrix, GolQuat* p_dest)
{
	LegoFloat v = p_matrix.m_m[0][0] + p_matrix.m_m[1][0] + p_matrix.m_m[2][0];
	if (v > 0.0f) {
		v = static_cast<LegoFloat>(sqrt(v + 1.0f));
		p_dest->m_w = v / 2.0f;
		v = 0.5f / v;
		p_dest->m_x = (p_matrix.m_m[1][3] - p_matrix.m_m[1][1]) * v;
		p_dest->m_y = (p_matrix.m_m[0][2] - p_matrix.m_m[1][2]) * v;
		p_dest->m_z = (p_matrix.m_m[0][3] - p_matrix.m_m[0][1]) * v;
		return;
	}
	LegoS32 major = 0;
	if (p_matrix.m_m[1][0] > p_matrix.m_m[0][0]) {
		major = 1;
	}
	if (p_matrix.m_m[2][0] > p_matrix.m_m[major][0]) {
		major = 2;
	}
	switch (major) {
	case 0:
		v = static_cast<LegoFloat>(sqrtf(p_matrix.m_m[0][0] - (p_matrix.m_m[1][0] + p_matrix.m_m[2][0]) + 1.0f));
		p_dest->m_x = v / 2.0f;
		v = 0.5f / v;
		p_dest->m_w = (p_matrix.m_m[1][3] - p_matrix.m_m[1][1]) * v;
		p_dest->m_y = (p_matrix.m_m[0][3] + p_matrix.m_m[0][1]) * v;
		p_dest->m_z = (p_matrix.m_m[1][2] + p_matrix.m_m[0][2]) * v;
		break;
	case 1:
		v = static_cast<LegoFloat>(sqrtf(p_matrix.m_m[1][0] - (p_matrix.m_m[0][0] + p_matrix.m_m[2][0]) + 1.0f));
		p_dest->m_y = v / 2.0f;
		v = 0.5f / v;
		p_dest->m_w = (p_matrix.m_m[0][2] - p_matrix.m_m[1][2]) * v;
		p_dest->m_z = (p_matrix.m_m[1][3] + p_matrix.m_m[1][1]) * v;
		p_dest->m_x = (p_matrix.m_m[0][3] + p_matrix.m_m[0][1]) * v;
		break;
	case 2:
		v = static_cast<LegoFloat>(sqrtf(p_matrix.m_m[2][0] - (p_matrix.m_m[1][0] + p_matrix.m_m[0][0]) + 1.0f));
		p_dest->m_z = v / 2.0f;
		v = 0.5f / v;
		p_dest->m_w = (p_matrix.m_m[0][3] - p_matrix.m_m[0][1]) * v;
		p_dest->m_x = (p_matrix.m_m[1][2] + p_matrix.m_m[0][2]) * v;
		p_dest->m_y = (p_matrix.m_m[1][3] + p_matrix.m_m[1][1]) * v;
		break;
	}
}

// FUNCTION: GOLDP 0x1002f720
void GolMath::FUN_1002f720(const GolMatrix4& p_matrix, GolQuat* p_dest)
{
	LegoFloat v;
	LegoFloat diag = p_matrix.m_m[0][0] + p_matrix.m_m[1][1] + p_matrix.m_m[2][2];
	if (diag > 0.0f) {
		v = static_cast<LegoFloat>(sqrt(diag + 1.0f));
		p_dest->m_w = v / 2.0f;
		LegoFloat inv = 0.5f / v;
		p_dest->m_x = (p_matrix.m_m[2][1] - p_matrix.m_m[1][2]) * inv;
		p_dest->m_y = (p_matrix.m_m[0][2] - p_matrix.m_m[2][0]) * inv;
		p_dest->m_z = (p_matrix.m_m[1][0] - p_matrix.m_m[0][1]) * inv;
		return;
	}
	LegoU32 major = 0;
	if (p_matrix.m_m[1][1] > p_matrix.m_m[0][0]) {
		major = 1;
	}
	if (p_matrix.m_m[2][2] > p_matrix.m_m[major][major]) {
		major = 2;
	}
	switch (major) {
	case 0:
		v = static_cast<LegoFloat>(sqrt(p_matrix.m_m[0][0] - (p_matrix.m_m[1][1] + p_matrix.m_m[2][2]) + 1.0f));
		p_dest->m_x = v / 2.0f;
		v = 0.5f / v;
		p_dest->m_w = (p_matrix.m_m[2][1] - p_matrix.m_m[1][2]) * v;
		p_dest->m_y = (p_matrix.m_m[1][0] + p_matrix.m_m[0][1]) * v;
		p_dest->m_z = (p_matrix.m_m[2][0] + p_matrix.m_m[0][2]) * v;
		break;
	case 1:
		v = static_cast<LegoFloat>(sqrt(p_matrix.m_m[1][1] - (p_matrix.m_m[0][0] + p_matrix.m_m[2][2]) + 1.0f));
		p_dest->m_y = v / 2.0f;
		v = 0.5f / v;
		p_dest->m_w = (p_matrix.m_m[0][2] - p_matrix.m_m[2][0]) * v;
		p_dest->m_z = (p_matrix.m_m[2][1] + p_matrix.m_m[1][2]) * v;
		p_dest->m_x = (p_matrix.m_m[1][0] + p_matrix.m_m[0][1]) * v;
		break;
	case 2:
		v = static_cast<LegoFloat>(sqrt(p_matrix.m_m[2][2] - (p_matrix.m_m[0][0] + p_matrix.m_m[1][1]) + 1.0f));
		p_dest->m_z = v / 2.0f;
		v = 0.5f / v;
		p_dest->m_w = (p_matrix.m_m[1][0] - p_matrix.m_m[0][1]) * v;
		p_dest->m_x = (p_matrix.m_m[2][0] + p_matrix.m_m[0][2]) * v;
		p_dest->m_y = (p_matrix.m_m[2][1] + p_matrix.m_m[1][2]) * v;
		break;
	}
}

// FUNCTION: GOLDP 0x1002f890
// FUNCTION: LEGORACERS 0x004495e0
void GolMath::FUN_1002f890(const GolQuat& p_from, const GolQuat& p_to, LegoFloat p_amount, GolQuat* p_dest)
{
	if (QuatDot(p_from, p_to) > 0.0f) {
		p_dest->m_x = p_from.m_x + (p_to.m_x - p_from.m_x) * p_amount;
		p_dest->m_y = p_from.m_y + (p_to.m_y - p_from.m_y) * p_amount;
		p_dest->m_z = p_from.m_z + (p_to.m_z - p_from.m_z) * p_amount;
		p_dest->m_w = p_from.m_w + (p_to.m_w - p_from.m_w) * p_amount;
	}
	else {
		p_dest->m_x = p_from.m_x - (p_from.m_x + p_to.m_x) * p_amount;
		p_dest->m_y = p_from.m_y - (p_from.m_y + p_to.m_y) * p_amount;
		p_dest->m_z = p_from.m_z - (p_from.m_z + p_to.m_z) * p_amount;
		p_dest->m_w = p_from.m_w - (p_from.m_w + p_to.m_w) * p_amount;
	}
}

// STUB: LEGORACERS 0x004496a0
void GolMath::FUN_004496a0(const GolVec3*, GolVec3*, const GolVec3*, LegoFloat)
{
	STUB(0x004496a0);
}

// STUB: LEGORACERS 0x004497f0
LegoBool32 GolMath::FUN_004497f0(const GolVec3*, const LegoFloat*)
{
	STUB(0x004497f0);
	return FALSE;
}

// STUB: LEGORACERS 0x00449a90
LegoBool32 GolMath::FUN_00449a90(GolVec3*, GolVec3*, LegoFloat, LegoFloat, LegoFloat)
{
	STUB(0x00449a90);
	return FALSE;
}

// STUB: LEGORACERS 0x00449b90
void GolMath::FUN_00449b90(LegoFloat, LegoFloat, LegoFloat, const LegoFloat*, GolVec3*)
{
	STUB(0x00449b90);
}

// STUB: LEGORACERS 0x00449bf0
void GolMath::FUN_00449bf0(const LegoFloat*, const LegoFloat*, LegoFloat*)
{
	STUB(0x00449bf0);
}
