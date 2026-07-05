#include "camera/goltransform.h"

#include "camera/golcameramatrices.h" // IWYU pragma: keep
#include "decomp.h"

DECOMP_SIZE_ASSERT(GolTransform, 0xd0)
DECOMP_SIZE_ASSERT(GolCameraMatrices, 0x220)

// FUNCTION: GOLDP 0x10002890
GolTransform::GolTransform()
{
	m_worldViewMatrix.m_m[0][0] = 1.0f;
	m_worldViewMatrix.m_m[0][1] = 0.0f;
	m_worldViewMatrix.m_m[0][2] = 0.0f;
	m_worldViewMatrix.m_m[0][3] = 0.0f;
	m_worldViewMatrix.m_m[1][0] = 0.0f;
	m_worldViewMatrix.m_m[1][1] = 1.0f;
	m_worldViewMatrix.m_m[1][2] = 0.0f;
	m_worldViewMatrix.m_m[1][3] = 0.0f;
	m_worldViewMatrix.m_m[2][0] = 0.0f;
	m_worldViewMatrix.m_m[2][1] = 0.0f;
	m_worldViewMatrix.m_m[2][2] = 1.0f;
	m_worldViewMatrix.m_m[2][3] = 0.0f;
	m_worldViewMatrix.m_m[3][0] = 0.0f;
	m_worldViewMatrix.m_m[3][1] = 0.0f;
	m_worldViewMatrix.m_m[3][2] = 0.0f;
	m_worldViewMatrix.m_m[3][3] = 1.0f;
	m_worldMatrix.m_m[0][1] = 0.0f;
	m_worldMatrix.m_m[0][2] = 0.0f;
	m_worldMatrix.m_m[0][3] = 0.0f;
	m_worldMatrix.m_m[1][0] = 0.0f;
	m_worldMatrix.m_m[1][2] = 0.0f;
	m_worldMatrix.m_m[1][3] = 0.0f;
	m_worldMatrix.m_m[2][0] = 0.0f;
	m_worldMatrix.m_m[2][1] = 0.0f;
	m_worldMatrix.m_m[2][3] = 0.0f;
	m_worldMatrix.m_m[3][0] = 0.0f;
	m_worldMatrix.m_m[3][1] = 0.0f;
	m_worldMatrix.m_m[3][2] = 0.0f;
	m_matrix.m_m[0][1] = 0.0f;
	m_matrix.m_m[0][2] = 0.0f;
	m_matrix.m_m[0][3] = 0.0f;
	m_matrix.m_m[1][0] = 0.0f;
	m_matrix.m_m[1][2] = 0.0f;
	m_matrix.m_m[1][3] = 0.0f;
	m_matrix.m_m[2][0] = 0.0f;
	m_matrix.m_m[2][1] = 0.0f;
	m_matrix.m_m[2][3] = 0.0f;
	m_matrix.m_m[3][0] = 0.0f;
	m_matrix.m_m[3][1] = 0.0f;
	m_matrix.m_m[3][2] = 0.0f;
	m_worldMatrix.m_m[0][0] = 1.0f;
	m_worldMatrix.m_m[1][1] = 1.0f;
	m_worldMatrix.m_m[2][2] = 1.0f;
	m_worldMatrix.m_m[3][3] = 1.0f;
	m_matrix.m_m[0][0] = 1.0f;
	m_matrix.m_m[1][1] = 1.0f;
	m_matrix.m_m[2][2] = 1.0f;
	m_matrix.m_m[3][3] = 1.0f;
}

// FUNCTION: GOLDP 0x10002980
void GolTransform::GetBasis(GolVec3* p_direction, GolVec3* p_up, GolVec3* p_right)
{
	p_right->m_x = m_matrix.m_m[0][0];
	p_right->m_y = m_matrix.m_m[0][1];
	p_right->m_z = m_matrix.m_m[0][2];
	p_up->m_x = m_matrix.m_m[1][0];
	p_up->m_y = m_matrix.m_m[1][1];
	p_up->m_z = m_matrix.m_m[1][2];
	p_direction->m_x = m_matrix.m_m[2][0];
	p_direction->m_y = m_matrix.m_m[2][1];
	p_direction->m_z = m_matrix.m_m[2][2];
}

// FUNCTION: GOLDP 0x100029d0
void GolTransform::GetDirectionUp(GolVec3* p_direction, GolVec3* p_up)
{
	p_up->m_x = m_matrix.m_m[1][0];
	p_up->m_y = m_matrix.m_m[1][1];
	p_up->m_z = m_matrix.m_m[1][2];
	p_direction->m_x = m_matrix.m_m[2][0];
	p_direction->m_y = m_matrix.m_m[2][1];
	p_direction->m_z = m_matrix.m_m[2][2];
}

// FUNCTION: GOLDP 0x10002a00
void GolTransform::GetRightDirection(GolVec3* p_right, GolVec3* p_direction)
{
	p_right->m_x = m_matrix.m_m[0][0];
	p_right->m_y = m_matrix.m_m[0][1];
	p_right->m_z = m_matrix.m_m[0][2];
	p_direction->m_x = m_matrix.m_m[2][0];
	p_direction->m_y = m_matrix.m_m[2][1];
	p_direction->m_z = m_matrix.m_m[2][2];
}

// FUNCTION: GOLDP 0x10002a30
void GolTransform::SetDirectionUp(GolVec3* p_direction, GolVec3* p_up)
{
	GolVec3 direction;
	GolMath::NormalizeVector3(*p_direction, &direction);

	LegoFloat dot = p_up->m_y;
	dot *= direction.m_y;
	dot += direction.m_z * p_up->m_z;
	dot += direction.m_x * p_up->m_x;

	GolVec3 up;
	up.m_x = p_up->m_x - (direction.m_x * dot);
	up.m_y = p_up->m_y - (direction.m_y * dot);
	up.m_z = p_up->m_z - (direction.m_z * dot);
	GolMath::NormalizeVector3(up, &up);

	GolVec3 right;
	right.m_x = direction.m_z;
	right.m_x *= up.m_y;
	right.m_x -= up.m_z * direction.m_y;
	right.m_y = up.m_z * direction.m_x;
	LegoFloat directionZUpX = direction.m_z;
	directionZUpX *= up.m_x;
	right.m_y -= directionZUpX;
	right.m_z = direction.m_y;
	right.m_z *= up.m_x;
	right.m_z -= up.m_y * direction.m_x;

	m_matrix.m_m[0][0] = right.m_x;
	m_matrix.m_m[0][1] = right.m_y;
	m_matrix.m_m[0][2] = right.m_z;
	m_matrix.m_m[1][0] = up.m_x;
	m_matrix.m_m[1][1] = up.m_y;
	m_matrix.m_m[1][2] = up.m_z;
	m_matrix.m_m[2][0] = direction.m_x;
	m_matrix.m_m[2][1] = direction.m_y;
	m_matrix.m_m[2][2] = direction.m_z;
}

// FUNCTION: GOLDP 0x10002b20
void GolTransform::SetRightDirection(GolVec3* p_right, GolVec3* p_direction)
{
	GolVec3 right;
	GolMath::NormalizeVector3(*p_right, &right);

	LegoFloat dot = p_direction->m_y;
	dot *= right.m_y;
	dot += right.m_z * p_direction->m_z;
	dot += right.m_x * p_direction->m_x;

	GolVec3 direction;
	direction.m_x = p_direction->m_x - (right.m_x * dot);
	direction.m_y = p_direction->m_y - (right.m_y * dot);
	direction.m_z = p_direction->m_z - (right.m_z * dot);
	GolMath::NormalizeVector3(direction, &direction);

	GolVec3 up;
	up.m_x = right.m_z;
	up.m_x *= direction.m_y;
	up.m_x -= direction.m_z * right.m_y;
	up.m_y = direction.m_z * right.m_x;
	LegoFloat rightZDirectionX = right.m_z;
	rightZDirectionX *= direction.m_x;
	up.m_y -= rightZDirectionX;
	up.m_z = right.m_y;
	up.m_z *= direction.m_x;
	up.m_z -= direction.m_y * right.m_x;

	m_matrix.m_m[0][0] = right.m_x;
	m_matrix.m_m[0][1] = right.m_y;
	m_matrix.m_m[0][2] = right.m_z;
	m_matrix.m_m[1][0] = up.m_x;
	m_matrix.m_m[1][1] = up.m_y;
	m_matrix.m_m[1][2] = up.m_z;
	m_matrix.m_m[2][0] = direction.m_x;
	m_matrix.m_m[2][1] = direction.m_y;
	m_matrix.m_m[2][2] = direction.m_z;
}

// FUNCTION: GOLDP 0x10002c10
void GolTransform::TransformPoint(const GolVec3* p_src, GolVec3* p_dest)
{
	LegoFloat product = m_matrix.m_m[0][0];
	product *= p_src->m_x;
	p_dest->m_x = product;
	p_dest->m_y = m_matrix.m_m[0][1] * p_src->m_x;
	p_dest->m_z = m_matrix.m_m[0][2] * p_src->m_x;

	p_dest->m_x += m_matrix.m_m[1][0] * p_src->m_y;
	p_dest->m_y += m_matrix.m_m[1][1] * p_src->m_y;
	p_dest->m_z += m_matrix.m_m[1][2] * p_src->m_y;

	p_dest->m_x += m_matrix.m_m[2][0] * p_src->m_z;
	p_dest->m_y += m_matrix.m_m[2][1] * p_src->m_z;
	p_dest->m_z += m_matrix.m_m[2][2] * p_src->m_z;

	p_dest->m_x += m_matrix.m_m[3][0];
	p_dest->m_y += m_matrix.m_m[3][1];
	p_dest->m_z += m_matrix.m_m[3][2];
}

// FUNCTION: GOLDP 0x10002c90
void GolTransform::TransformVector(const GolVec3* p_src, GolVec3* p_dest)
{
	LegoFloat product = m_matrix.m_m[0][0];
	product *= p_src->m_x;
	p_dest->m_x = product;
	p_dest->m_y = m_matrix.m_m[0][1] * p_src->m_x;
	p_dest->m_z = m_matrix.m_m[0][2] * p_src->m_x;

	p_dest->m_x += m_matrix.m_m[1][0] * p_src->m_y;
	p_dest->m_y += m_matrix.m_m[1][1] * p_src->m_y;
	p_dest->m_z += m_matrix.m_m[1][2] * p_src->m_y;

	p_dest->m_x += m_matrix.m_m[2][0] * p_src->m_z;
	p_dest->m_y += m_matrix.m_m[2][1] * p_src->m_z;
	p_dest->m_z += m_matrix.m_m[2][2] * p_src->m_z;
}

// FUNCTION: GOLDP 0x10002d00
void GolTransform::InverseTransformPoint(const GolVec3* p_src, GolVec3* p_dest)
{
	LegoFloat product = m_matrix.m_m[0][0];
	product *= p_src->m_x;
	p_dest->m_x = product;
	p_dest->m_y = m_matrix.m_m[1][0] * p_src->m_x;
	product = m_matrix.m_m[2][0];
	product *= p_src->m_x;
	p_dest->m_z = product;

	p_dest->m_x = (p_src->m_y * m_matrix.m_m[0][1]) + p_dest->m_x;
	p_dest->m_y = (p_src->m_y * m_matrix.m_m[1][1]) + p_dest->m_y;
	product = m_matrix.m_m[2][1];
	product *= p_src->m_y;
	p_dest->m_z = product + p_dest->m_z;

	p_dest->m_x = (p_src->m_z * m_matrix.m_m[0][2]) + p_dest->m_x;
	p_dest->m_y = (p_src->m_z * m_matrix.m_m[1][2]) + p_dest->m_y;
	product = m_matrix.m_m[2][2];
	product *= p_src->m_z;
	p_dest->m_z = product + p_dest->m_z;

	LegoFloat offset = m_matrix.m_m[3][0] * m_matrix.m_m[0][0];
	product = m_matrix.m_m[0][1];
	product *= m_matrix.m_m[3][1];
	offset += product;
	offset += m_matrix.m_m[3][2] * m_matrix.m_m[0][2];
	p_dest->m_x -= offset;

	offset = m_matrix.m_m[3][2] * m_matrix.m_m[1][2];
	product = m_matrix.m_m[1][1];
	product *= m_matrix.m_m[3][1];
	offset += product;
	product = m_matrix.m_m[3][0];
	product *= m_matrix.m_m[1][0];
	offset += product;
	p_dest->m_y -= offset;

	offset = m_matrix.m_m[2][2];
	offset *= m_matrix.m_m[3][2];
	product = m_matrix.m_m[2][1];
	product *= m_matrix.m_m[3][1];
	offset += product;
	product = m_matrix.m_m[3][0];
	product *= m_matrix.m_m[2][0];
	offset += product;
	p_dest->m_z -= offset;
}

// FUNCTION: GOLDP 0x10002dc0
void GolTransform::InverseTransformVector(const GolVec3* p_src, GolVec3* p_dest)
{
	LegoFloat product = m_matrix.m_m[0][0];
	product *= p_src->m_x;
	p_dest->m_x = product;
	p_dest->m_y = m_matrix.m_m[1][0] * p_src->m_x;
	p_dest->m_z = m_matrix.m_m[2][0] * p_src->m_x;

	p_dest->m_x += m_matrix.m_m[0][1] * p_src->m_y;
	p_dest->m_y += m_matrix.m_m[1][1] * p_src->m_y;
	p_dest->m_z += m_matrix.m_m[2][1] * p_src->m_y;

	p_dest->m_x += m_matrix.m_m[0][2] * p_src->m_z;
	p_dest->m_y += m_matrix.m_m[1][2] * p_src->m_z;
	p_dest->m_z += m_matrix.m_m[2][2] * p_src->m_z;
}

// FUNCTION: GOLDP 0x10002e30
void GolTransform::SetRotation(LegoFloat* p_quat)
{
	LegoFloat scale =
		2.0f / ((p_quat[0] * p_quat[0]) + (p_quat[1] * p_quat[1]) + (p_quat[2] * p_quat[2]) + (p_quat[3] * p_quat[3]));
	LegoFloat v0 = scale * p_quat[0];
	LegoFloat v1 = p_quat[1];
	v1 *= scale;
	LegoFloat v2 = scale * p_quat[2];
	LegoFloat v3 = p_quat[3];
	v3 *= v0;
	LegoFloat v4 = p_quat[3];
	v4 *= v1;
	LegoFloat v5 = p_quat[3];
	v5 *= v2;
	LegoFloat v6 = v0 * p_quat[0];
	LegoFloat v7 = v1 * p_quat[0];
	LegoFloat v8 = v2 * p_quat[0];
	LegoFloat v9 = p_quat[1];
	v9 *= v1;
	LegoFloat v10 = p_quat[1];
	v10 *= v2;
	LegoFloat v11 = v2 * p_quat[2];

	m_matrix.m_m[0][0] = 1.0f - (v11 + v9);
	m_matrix.m_m[0][1] = v7 - v5;
	m_matrix.m_m[0][2] = v8 + v4;
	m_matrix.m_m[1][0] = v7 + v5;
	m_matrix.m_m[1][1] = 1.0f - (v11 + v6);
	m_matrix.m_m[1][2] = v10 - v3;
	m_matrix.m_m[2][0] = v8 - v4;
	m_matrix.m_m[2][1] = v10 + v3;
	m_matrix.m_m[2][2] = 1.0f - (v9 + v6);
}

// FUNCTION: GOLDP 0x10002f50
void GolTransform::GetUp(GolVec3* p_up)
{
	p_up->m_x = m_matrix.m_m[0][0];
	p_up->m_y = m_matrix.m_m[0][1];
	p_up->m_z = m_matrix.m_m[0][2];
}

// FUNCTION: GOLDP 0x10002f70
void GolTransform::GetForward(GolVec3* p_forward)
{
	p_forward->m_x = m_matrix.m_m[1][0];
	p_forward->m_y = m_matrix.m_m[1][1];
	p_forward->m_z = m_matrix.m_m[1][2];
}

// FUNCTION: GOLDP 0x10002f90
void GolTransform::GetRight(GolVec3* p_right)
{
	p_right->m_x = m_matrix.m_m[2][0];
	p_right->m_y = m_matrix.m_m[2][1];
	p_right->m_z = m_matrix.m_m[2][2];
}

// FUNCTION: GOLDP 0x10002fb0
LegoFloat GolTransform::DistanceSquaredTo(GolVec3* p_position)
{
	LegoFloat x = m_matrix.m_m[3][0] - p_position->m_x;
	LegoFloat y = m_matrix.m_m[3][1] - p_position->m_y;
	LegoFloat z = m_matrix.m_m[3][2] - p_position->m_z;

	return (x * x) + (y * y) + (z * z);
}

// FUNCTION: GOLDP 0x10002fe0
void GolTransform::GetPosition(GolVec3* p_position)
{
	p_position->m_x = m_matrix.m_m[3][0];
	p_position->m_y = m_matrix.m_m[3][1];
	p_position->m_z = m_matrix.m_m[3][2];
}

// FUNCTION: GOLDP 0x10003000
void GolTransform::SetPosition(GolVec3* p_position)
{
	m_matrix.m_m[3][0] = p_position->m_x;
	m_matrix.m_m[3][1] = p_position->m_y;
	m_matrix.m_m[3][2] = p_position->m_z;
}

// FUNCTION: GOLDP 0x10003020
void GolTransform::GetRotation(GolQuat* p_rotation)
{
	GolMatrix34 basis;
	basis.m_m[0][0] = m_matrix.m_m[0][0];
	basis.m_m[0][1] = m_matrix.m_m[0][1];
	basis.m_m[0][2] = m_matrix.m_m[0][2];
	basis.m_m[1][0] = m_matrix.m_m[1][0];
	basis.m_m[1][1] = m_matrix.m_m[1][1];
	basis.m_m[1][2] = m_matrix.m_m[1][2];
	basis.m_m[2][0] = m_matrix.m_m[2][0];
	basis.m_m[2][1] = m_matrix.m_m[2][1];
	basis.m_m[2][2] = m_matrix.m_m[2][2];

	GolMath::Matrix3ToQuat(basis.m_orientation, p_rotation);
}

// FUNCTION: GOLDP 0x10003080
void GolTransform::CopyFrom(GolTransformBase* p_source)
{
	GolTransform* source = static_cast<GolTransform*>(p_source);
	m_matrix.m_m[0][0] = source->m_matrix.m_m[0][0];
	m_matrix.m_m[0][1] = source->m_matrix.m_m[0][1];
	m_matrix.m_m[0][2] = source->m_matrix.m_m[0][2];
	m_matrix.m_m[1][0] = source->m_matrix.m_m[1][0];
	m_matrix.m_m[1][1] = source->m_matrix.m_m[1][1];
	m_matrix.m_m[1][2] = source->m_matrix.m_m[1][2];
	m_matrix.m_m[2][0] = source->m_matrix.m_m[2][0];
	m_matrix.m_m[2][1] = source->m_matrix.m_m[2][1];
	m_matrix.m_m[2][2] = source->m_matrix.m_m[2][2];
	m_matrix.m_m[3][0] = source->m_matrix.m_m[3][0];
	m_matrix.m_m[3][1] = source->m_matrix.m_m[3][1];
	m_matrix.m_m[3][2] = source->m_matrix.m_m[3][2];
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void GolTransform::VTable0x00()
{
	// empty
}
