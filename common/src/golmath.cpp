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
void GolMath::FUN_00449170(LegoFloat p_angle, LegoFloat* p_sin, LegoFloat* p_cos)
{
	*p_sin = static_cast<LegoFloat>(sin(p_angle));
	*p_cos = static_cast<LegoFloat>(cos(p_angle));
}

// FUNCTION: LEGORACERS 0x00449190
void GolMath::FUN_00449190(const LegoFloat* p_left, const LegoFloat* p_right, LegoFloat* p_dest)
{
	LegoFloat value = p_left[1] * p_right[3];
	value += p_left[2] * p_right[6];
	value += p_left[0] * p_right[0];
	p_dest[0] = value;

	value = p_right[4] * p_left[1];
	value += p_right[7] * p_left[2];
	value += p_right[1] * p_left[0];
	p_dest[1] = value;

	value = p_right[8] * p_left[2];
	value += p_left[1] * p_right[5];
	value += p_right[2] * p_left[0];
	p_dest[2] = value;

	value = p_left[4] * p_right[3];
	value += p_left[5] * p_right[6];
	value += p_left[3] * p_right[0];
	p_dest[3] = value;

	value = p_left[5] * p_right[7];
	value += p_left[3] * p_right[1];
	value += p_left[4] * p_right[4];
	p_dest[4] = value;

	value = p_left[3] * p_right[2];
	value += p_right[8] * p_left[5];
	value += p_left[4] * p_right[5];
	p_dest[5] = value;

	value = p_left[8] * p_right[6];
	value += p_right[3] * p_left[7];
	value += p_left[6] * p_right[0];
	p_dest[6] = value;

	value = p_right[1] * p_left[6];
	value += p_left[8] * p_right[7];
	value += p_right[4] * p_left[7];
	p_dest[7] = value;

	value = p_left[7] * p_right[5];
	value += p_left[8] * p_right[8];
	value += p_left[6] * p_right[2];
	p_dest[8] = value;
}

// FUNCTION: GOLDP 0x1002f4e0
// FUNCTION: LEGORACERS 0x00449280
void __fastcall GolMath::NormalizeVector2(const GolVec2& p_src, GolVec2* p_dest)
{
	LegoFloat x = p_src.m_x;
	LegoFloat y = p_src.m_y;
	LegoFloat lengthSquared = x * x;
	lengthSquared += y * y;
	LegoFloat length = (LegoFloat) sqrt(lengthSquared);

	if (length == 0.0) {
		p_dest->m_x = 0.0f;
		p_dest->m_y = 0.0f;
	}
	else {
		LegoFloat scale = 1.0f / length;
		p_dest->m_x = x * scale;
		p_dest->m_y = y * scale;
	}
}

// FUNCTION: GOLDP 0x1002f530
// FUNCTION: LEGORACERS 0x004492d0
void __fastcall GolMath::NormalizeVector3(const GolVec3& p_src, GolVec3* p_dest)
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
		p_dest->m_x = 0.0f;
		p_dest->m_y = 0.0f;
		p_dest->m_z = 0.0f;
	}
	else {
		LegoFloat scale = 1.0f / length;
		p_dest->m_x = x * scale;
		p_dest->m_y = y * scale;
		p_dest->m_z = z * scale;
	}
}

// FUNCTION: LEGORACERS 0x00449340
void GolMath::FUN_00449340(const GolQuat* p_quat, LegoFloat* p_dest)
{
	LegoFloat scale = 2.0f / (p_quat->m_x * p_quat->m_x + p_quat->m_y * p_quat->m_y + p_quat->m_z * p_quat->m_z +
							  p_quat->m_w * p_quat->m_w);
	LegoFloat sx = scale * p_quat->m_x;
	LegoFloat sy = p_quat->m_y * scale;
	LegoFloat sz = scale * p_quat->m_z;
	LegoFloat wx = p_quat->m_w * sx;
	LegoFloat wy = p_quat->m_w * sy;
	LegoFloat wz = p_quat->m_w * sz;
	LegoFloat xx = sx * p_quat->m_x;
	LegoFloat xy = sy * p_quat->m_x;
	LegoFloat xz = sz * p_quat->m_x;
	LegoFloat yy = p_quat->m_y * sy;
	LegoFloat yz = p_quat->m_y * sz;
	LegoFloat zz = sz * p_quat->m_z;

	p_dest[0] = 1.0f - (zz + yy);
	p_dest[1] = xy - wz;
	p_dest[2] = xz + wy;
	p_dest[3] = xy + wz;
	p_dest[4] = 1.0f - (zz + xx);
	p_dest[5] = yz - wx;
	p_dest[6] = xz - wy;
	p_dest[7] = yz + wx;
	p_dest[8] = 1.0f - (yy + xx);
}

// FUNCTION: GOLDP 0x1002f5a0
// FUNCTION: LEGORACERS 0x00449460
void GolMath::FUN_1002f5a0(const GolMatrix3& p_matrix, GolQuat* p_dest)
{
	LegoFloat v = p_matrix.m_m[0][0] + p_matrix.m_m[1][1] + p_matrix.m_m[2][2];
	if (v > 0.0f) {
		v = static_cast<LegoFloat>(sqrt(v + 1.0f));
		p_dest->m_w = v / 2.0f;
		v = 0.5f / v;
		p_dest->m_x = (p_matrix.m_m[2][1] - p_matrix.m_m[1][2]) * v;
		p_dest->m_y = (p_matrix.m_m[0][2] - p_matrix.m_m[2][0]) * v;
		p_dest->m_z = (p_matrix.m_m[1][0] - p_matrix.m_m[0][1]) * v;
		return;
	}

	LegoS32 major = 0;
	if (p_matrix.m_m[1][1] > p_matrix.m_m[0][0]) {
		major = 1;
	}
	if (p_matrix.m_m[2][2] > p_matrix.m_m[major][major]) {
		major = 2;
	}

	switch (major) {
	case 0:
		v = static_cast<LegoFloat>(sqrtf(p_matrix.m_m[0][0] - (p_matrix.m_m[1][1] + p_matrix.m_m[2][2]) + 1.0f));
		p_dest->m_x = v / 2.0f;
		v = 0.5f / v;
		p_dest->m_w = (p_matrix.m_m[2][1] - p_matrix.m_m[1][2]) * v;
		p_dest->m_y = (p_matrix.m_m[1][0] + p_matrix.m_m[0][1]) * v;
		p_dest->m_z = (p_matrix.m_m[2][0] + p_matrix.m_m[0][2]) * v;
		break;
	case 1:
		v = static_cast<LegoFloat>(sqrtf(p_matrix.m_m[1][1] - (p_matrix.m_m[0][0] + p_matrix.m_m[2][2]) + 1.0f));
		p_dest->m_y = v / 2.0f;
		v = 0.5f / v;
		p_dest->m_w = (p_matrix.m_m[0][2] - p_matrix.m_m[2][0]) * v;
		p_dest->m_z = (p_matrix.m_m[2][1] + p_matrix.m_m[1][2]) * v;
		p_dest->m_x = (p_matrix.m_m[1][0] + p_matrix.m_m[0][1]) * v;
		break;
	case 2:
		v = static_cast<LegoFloat>(sqrtf(p_matrix.m_m[2][2] - (p_matrix.m_m[1][1] + p_matrix.m_m[0][0]) + 1.0f));
		p_dest->m_z = v / 2.0f;
		v = 0.5f / v;
		p_dest->m_w = (p_matrix.m_m[1][0] - p_matrix.m_m[0][1]) * v;
		p_dest->m_x = (p_matrix.m_m[2][0] + p_matrix.m_m[0][2]) * v;
		p_dest->m_y = (p_matrix.m_m[2][1] + p_matrix.m_m[1][2]) * v;
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

// FUNCTION: LEGORACERS 0x004496a0
void GolMath::FUN_004496a0(const GolVec3* p_src, GolVec3* p_dest, const GolVec3* p_axis, LegoFloat p_angle)
{
	LegoFloat s = (LegoFloat) sin(p_angle);

	GolVec3 src = *p_src;

	LegoFloat c = (LegoFloat) cos(p_angle);
	LegoFloat oneMinusC = 1.0f - c;
	LegoFloat matrix[3][3];

	LegoFloat xy = p_axis->m_y;
	xy *= p_axis->m_x;
	xy *= oneMinusC;
	LegoFloat xz = p_axis->m_z;
	xz *= p_axis->m_x;
	xz *= oneMinusC;
	LegoFloat yz = p_axis->m_z * p_axis->m_y;
	yz *= oneMinusC;
	LegoFloat xs = s * p_axis->m_x;
	LegoFloat ys = p_axis->m_y;
	ys *= s;
	LegoFloat zs = s * p_axis->m_z;

	matrix[0][0] = p_axis->m_x * p_axis->m_x * oneMinusC + c;
	matrix[0][1] = xy + zs;
	matrix[0][2] = xz - ys;
	matrix[1][0] = xy - zs;
	matrix[1][1] = p_axis->m_y * p_axis->m_y * oneMinusC + c;
	matrix[1][2] = yz + xs;
	matrix[2][0] = xz + ys;
	matrix[2][1] = yz - xs;
	GolVec3* dest = p_dest;
	matrix[2][2] = p_axis->m_z * p_axis->m_z * oneMinusC + c;

	dest->m_x = src.m_z * matrix[0][2] + src.m_y * matrix[0][1] + src.m_x * matrix[0][0];
	dest->m_y = src.m_z * matrix[1][2] + src.m_y * matrix[1][1] + src.m_x * matrix[1][0];
	dest->m_z = src.m_z * matrix[2][2] + src.m_y * matrix[2][1] + src.m_x * matrix[2][0];
}

// STUB: LEGORACERS 0x004497f0
LegoBool32 GolMath::FUN_004497f0(const GolVec3* p_point, const LegoFloat* p_triangle)
{
	LegoFloat normalX = p_triangle[9];
	if (normalX < 0.0f) {
		normalX = -normalX;
	}

	LegoFloat normalY = p_triangle[10];
	if (normalY < 0.0f) {
		normalY = -normalY;
	}

	LegoFloat normalZ = p_triangle[11];
	if (normalZ < 0.0f) {
		normalZ = -normalZ;
	}

	LegoFloat a0;
	LegoFloat a1;
	LegoFloat b0;
	LegoFloat b1;
	LegoFloat c0;
	LegoFloat c1;
	LegoFloat point0;
	LegoFloat point1;

	if (normalX > normalY) {
		if (normalZ > normalX) {
			a0 = p_triangle[0];
			a1 = p_triangle[1];
			b0 = p_triangle[3];
			b1 = p_triangle[4];
			c0 = p_triangle[6];
			c1 = p_triangle[7];
			point0 = p_point->m_x;
			point1 = p_point->m_y;
		}
		else {
			a0 = p_triangle[1];
			a1 = p_triangle[2];
			b0 = p_triangle[4];
			b1 = p_triangle[5];
			c0 = p_triangle[7];
			c1 = p_triangle[8];
			point0 = p_point->m_y;
			point1 = p_point->m_z;
		}
	}
	else if (normalZ > normalY) {
		a0 = p_triangle[0];
		a1 = p_triangle[1];
		b0 = p_triangle[3];
		b1 = p_triangle[4];
		c0 = p_triangle[6];
		c1 = p_triangle[7];
		point0 = p_point->m_x;
		point1 = p_point->m_y;
	}
	else {
		a0 = p_triangle[0];
		a1 = p_triangle[2];
		b0 = p_triangle[3];
		b1 = p_triangle[5];
		c0 = p_triangle[6];
		c1 = p_triangle[8];
		point0 = p_point->m_x;
		point1 = p_point->m_z;
	}

	LegoFloat edgeAC0 = c0 - a0;
	LegoFloat edgeAC1 = a1 - c1;
	LegoFloat edgeACDotC = edgeAC1 * c0 + edgeAC0 * c1;
	LegoFloat edgeAB0 = a0 - b0;
	LegoFloat edgeAB1 = b1 - a1;
	LegoFloat edgeABDotB = edgeAB1 * b0 + edgeAB0 * b1;
	LegoFloat edgeCB0 = b0 - c0;
	LegoFloat edgeCB1 = c1 - b1;
	LegoFloat edgeCBDotC = edgeCB1 * c0 + edgeCB0 * c1;

	if (edgeCB1 * edgeAB0 + edgeCB0 * edgeAB1 <= edgeAC1 * point1 + edgeAC0 * point0) {
		if (edgeAC1 * point1 + edgeAC0 * point0 < edgeACDotC) {
			return FALSE;
		}
		if (edgeAB0 * point1 + edgeAB1 * point0 < edgeABDotB) {
			return FALSE;
		}
		if (edgeCB0 * point1 + edgeCB1 * point0 < edgeCBDotC) {
			return FALSE;
		}
	}
	else {
		if (edgeAC1 * point1 + edgeAC0 * point0 >= edgeACDotC) {
			return FALSE;
		}
		if (edgeAB0 * point1 + edgeAB1 * point0 >= edgeABDotB) {
			return FALSE;
		}
		if (edgeCB0 * point1 + edgeCB1 * point0 >= edgeCBDotC) {
			return FALSE;
		}
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00449a90
LegoBool32 GolMath::FUN_00449a90(
	GolVec3* p_target,
	GolVec3* p_current,
	LegoFloat p_minDistSq,
	LegoFloat p_speed,
	LegoFloat p_dt
)
{
	GolVec3 delta;
	delta.m_x = p_target->m_x - p_current->m_x;
	delta.m_y = p_target->m_y - p_current->m_y;
	delta.m_z = p_target->m_z - p_current->m_z;

	LegoFloat distanceSquared = delta.m_z * delta.m_z + delta.m_y * delta.m_y + delta.m_x * delta.m_x;
	if (distanceSquared < p_minDistSq) {
		return TRUE;
	}

	NormalizeVector3(delta, &delta);
	LegoFloat step = p_speed * p_dt;
	GolVec3 stepDelta;
	LegoFloat y = delta.m_y;
	stepDelta.m_x = step * delta.m_x;
	stepDelta.m_y = y * step;
	stepDelta.m_z = step * delta.m_z;

	p_current->m_x += stepDelta.m_x;
	p_current->m_y += stepDelta.m_y;
	p_current->m_z += stepDelta.m_z;

	GolVec3 remaining;
	remaining.m_x = p_target->m_x - p_current->m_x;
	remaining.m_y = p_target->m_y - p_current->m_y;
	remaining.m_z = p_target->m_z - p_current->m_z;

	if (remaining.m_z * delta.m_z + remaining.m_y * delta.m_y + remaining.m_x * delta.m_x <= 0.0f) {
		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00449b90
void GolMath::FUN_00449b90(LegoFloat p_x, LegoFloat p_y, LegoFloat p_z, const LegoFloat* p_matrix, GolVec3* p_dest)
{
	LegoFloat x = p_matrix[2] * p_z;
	x += p_matrix[1] * p_y;
	x += p_x * p_matrix[0];
	p_dest->m_x = x;

	LegoFloat y = p_matrix[5] * p_z;
	y += p_matrix[4] * p_y;
	y += p_matrix[3] * p_x;
	p_dest->m_y = y;

	LegoFloat z = p_matrix[8] * p_z;
	z += p_matrix[7] * p_y;
	z += p_matrix[6] * p_x;
	p_dest->m_z = z;
}

// FUNCTION: LEGORACERS 0x00449bf0
void GolMath::FUN_00449bf0(const LegoFloat* p_left, const LegoFloat* p_right, LegoFloat* p_dest)
{
	LegoFloat value = p_left[1] * p_right[1];
	value += p_left[2] * p_right[2];
	value += p_left[0] * p_right[0];
	p_dest[0] = value;

	value = p_right[4] * p_left[1];
	value += p_right[5] * p_left[2];
	value += p_right[3] * p_left[0];
	p_dest[1] = value;

	value = p_right[8] * p_left[2];
	value += p_left[1] * p_right[7];
	value += p_right[6] * p_left[0];
	p_dest[2] = value;

	value = p_left[4] * p_right[1];
	value += p_left[5] * p_right[2];
	value += p_left[3] * p_right[0];
	p_dest[3] = value;

	value = p_left[5] * p_right[5];
	value += p_left[3] * p_right[3];
	value += p_left[4] * p_right[4];
	p_dest[4] = value;

	value = p_left[3] * p_right[6];
	value += p_right[8] * p_left[5];
	value += p_left[4] * p_right[7];
	p_dest[5] = value;

	value = p_left[8] * p_right[2];
	value += p_right[1] * p_left[7];
	value += p_left[6] * p_right[0];
	p_dest[6] = value;

	value = p_right[3] * p_left[6];
	value += p_left[8] * p_right[5];
	value += p_right[4] * p_left[7];
	p_dest[7] = value;

	value = p_left[7] * p_right[7];
	value += p_left[8] * p_right[8];
	value += p_left[6] * p_right[6];
	p_dest[8] = value;
}
