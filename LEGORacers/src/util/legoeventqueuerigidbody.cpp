#include "golorientedentity.h"
#include "util/legoeventqueue.h"

#include <float.h>
#include <math.h>

DECOMP_SIZE_ASSERT(LegoEventQueue::Descriptor::RigidBody, 0xe4)

inline LegoFloat DotContactVectors(const GolVec3& p_left, const GolVec3& p_right)
{
	LegoFloat result = p_left.m_y;
	LegoFloat y = p_right.m_y;
	result *= y;
	LegoFloat z = p_right.m_z;
	LegoFloat leftZ = p_left.m_z;
	z *= leftZ;
	result += z;
	result += p_right.m_x * p_left.m_x;
	return result;
}

// FUNCTION: LEGORACERS 0x00441330
LegoBool32 LegoEventQueue::Descriptor::RigidBody::CalculateBoxContact(
	RigidBody* p_other,
	LegoFloat* p_penetration,
	GolVec3* p_normal,
	GolVec3* p_contactPoint
)
{
	LegoFloat distance0;
	LegoFloat distance1;
	if (!TestBoxOverlap(p_other, p_penetration, p_normal, &distance0, &distance1)) {
		return FALSE;
	}

	LegoS32 contactCount = 0;
	LegoU32 shapeIndex = 0;
	p_contactPoint->m_x = 0.0f;
	p_contactPoint->m_y = 0.0f;
	p_contactPoint->m_z = 0.0f;

	for (; shapeIndex < 2; shapeIndex++) {
		LegoU32 cornerIndex = 0;
		const GolVec3* position;
		LegoFloat distance;
		GolVec3 axisX;
		GolVec3 axisY;
		GolVec3 axisZ;
		if (!shapeIndex) {
			axisX.m_x = m_body->m_orientation.m_m[0][0];
			axisX.m_y = m_body->m_orientation.m_m[0][1];
			axisX.m_z = m_body->m_orientation.m_m[0][2];
			GolMath::ScaleVector3(&axisX, m_boxSizeX * 0.5f, &axisX);
			axisY.m_x = m_body->m_orientation.m_m[1][0];
			axisY.m_y = m_body->m_orientation.m_m[1][1];
			axisY.m_z = m_body->m_orientation.m_m[1][2];
			GolMath::ScaleVector3(&axisY, ((((((((((((((((m_boxSizeY * 0.5f)))))))))))))))), &axisY);
			axisZ = m_body->m_orientation.m_rows[2];
			GolMath::ScaleVector3(&axisZ, m_boxSizeZ * 0.5f, &axisZ);

			if (m_boxScale != 1.0f) {
				if (m_boxScale == 0.0f) {
					return FALSE;
				}

				GolMath::ScaleVector3(&axisX, m_boxScale, &axisX);
				GolMath::ScaleVector3(&axisY, m_boxScale, &axisY);
				GolMath::ScaleVector3(&axisZ, m_boxScale, &axisZ);
			}

			position = &m_centerOfMassWorld;
			distance = distance0;
		}
		else {
			axisX.m_x = p_other->m_body->m_orientation.m_m[0][0];
			axisX.m_y = p_other->m_body->m_orientation.m_m[0][1];
			axisX.m_z = p_other->m_body->m_orientation.m_m[0][2];
			GolMath::ScaleVector3(&axisX, p_other->m_boxSizeX * 0.5f, &axisX);
			axisY.m_x = p_other->m_body->m_orientation.m_m[1][0];
			axisY.m_y = p_other->m_body->m_orientation.m_m[1][1];
			axisY.m_z = p_other->m_body->m_orientation.m_m[1][2];
			GolMath::ScaleVector3(&axisY, ((((((((((((((((p_other->m_boxSizeY * 0.5f)))))))))))))))), &axisY);
			axisZ = p_other->m_body->m_orientation.m_rows[2];
			GolMath::ScaleVector3(&axisZ, p_other->m_boxSizeZ * 0.5f, &axisZ);

			if (p_other->m_boxScale != 1.0f) {
				if (p_other->m_boxScale == 0.0f) {
					return FALSE;
				}

				GolMath::ScaleVector3(&axisX, p_other->m_boxScale, &axisX);
				GolMath::ScaleVector3(&axisY, p_other->m_boxScale, &axisY);
				GolMath::ScaleVector3(&axisZ, p_other->m_boxScale, &axisZ);
			}

			position = &p_other->m_centerOfMassWorld;
			distance = distance1;
		}

		do {
			GolVec3 corner;
			if (cornerIndex < 4) {
				corner.m_x = axisX.m_x;
				corner.m_y = axisX.m_y;
				corner.m_z = axisX.m_z;
			}
			else {
				corner.m_x = -axisX.m_x;
				corner.m_y = -axisX.m_y;
				corner.m_z = -axisX.m_z;
			}

			if (cornerIndex >= 2 && (cornerIndex < 4 || cornerIndex >= 6)) {
				corner -= axisY;
			}
			else {
				corner += axisY;
			}

			if (!cornerIndex || cornerIndex == 2 || cornerIndex == 4 || cornerIndex == 6) {
				corner += axisZ;
			}
			else {
				corner -= axisZ;
			}

			LegoFloat projected = DotContactVectors(*p_normal, corner);
			if (shapeIndex == 1) {
				projected = -projected;
			}

			if (projected >= distance) {
				contactCount++;
				p_contactPoint->m_x = position->m_x + p_contactPoint->m_x + corner.m_x;
				p_contactPoint->m_y = position->m_y + p_contactPoint->m_y + corner.m_y;
				p_contactPoint->m_z = corner.m_z + position->m_z + p_contactPoint->m_z;
			}
			cornerIndex++;
		} while (cornerIndex < 8);
	}

	LegoFloat count = static_cast<LegoFloat>(contactCount);
	p_contactPoint->m_x = p_contactPoint->m_x / count;
	p_contactPoint->m_y = p_contactPoint->m_y / count;
	p_contactPoint->m_z = p_contactPoint->m_z / count;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00441790
LegoBool32 LegoEventQueue::Descriptor::RigidBody::TestBoxOverlap(
	RigidBody* p_other,
	LegoFloat* p_penetration,
	GolVec3* p_normal,
	LegoFloat* p_distance0,
	LegoFloat* p_distance1
)
{
	LegoS32 bestAxis = -1;
	LegoFloat overlap;
	LegoFloat projection;
	LegoFloat half1z;
	LegoFloat half0y;
	LegoFloat half0z;
	LegoFloat half1x;
	LegoFloat half0x;
	LegoFloat half1y;
	GolVec3 delta;
	GolVec3 thisRow2;
	GolVec3 thisRow0;
	GolVec3 otherRow2;
	GolVec3 otherRow0;
	GolVec3 thisRow1;
	GolVec3 otherRow1;
	GolMatrix3 absOrientation;
	GolMatrix3 relativeOrientation;
	GolMatrix3 orientation0;

	m_body->CopyOrientation(&orientation0);
	p_other->m_body->CopyOrientation(&absOrientation);

	delta.m_x = p_other->m_centerOfMassWorld.m_x - m_centerOfMassWorld.m_x;
	delta.m_y = p_other->m_centerOfMassWorld.m_y - m_centerOfMassWorld.m_y;
	delta.m_z = p_other->m_centerOfMassWorld.m_z - m_centerOfMassWorld.m_z;
	GolMath::TransformVector(delta, &orientation0.m_m[0][0], &delta);

	GolMath::MultiplyMatrixByTranspose(
		&absOrientation.m_m[0][0],
		&orientation0.m_m[0][0],
		&relativeOrientation.m_m[0][0]
	);

	half0x = m_boxSizeX * 0.5f;
	half0y = m_boxSizeY * 0.5f;
	half0z = m_boxSizeZ * 0.5f;
	if (m_boxScale != 1.0f) {
		if (m_boxScale == 0.0f) {
			return FALSE;
		}

		half0x = GOL_MUL(m_boxScale, half0x);
		half0y = GOL_MUL(m_boxScale, half0y);
		half0z = GOL_MUL(m_boxScale, half0z);
	}

	half1x = p_other->m_boxSizeX * 0.5f;
	half1y = p_other->m_boxSizeY * 0.5f;
	half1z = p_other->m_boxSizeZ * 0.5f;
	if (p_other->m_boxScale != 1.0f) {
		if (p_other->m_boxScale == 0.0f) {
			return FALSE;
		}

		half1x = GOL_MUL(p_other->m_boxScale, half1x);
		half1y = GOL_MUL(p_other->m_boxScale, half1y);
		half1z = GOL_MUL(p_other->m_boxScale, half1z);
	}

	absOrientation.m_m[0][0] = static_cast<LegoFloat>(fabs(relativeOrientation.m_m[0][0]));
	absOrientation.m_m[0][1] = static_cast<LegoFloat>(fabs(relativeOrientation.m_m[0][1]));
	absOrientation.m_m[0][2] = static_cast<LegoFloat>(fabs(relativeOrientation.m_m[0][2]));
	absOrientation.m_m[1][0] = static_cast<LegoFloat>(fabs(relativeOrientation.m_m[1][0]));
	absOrientation.m_m[1][1] = static_cast<LegoFloat>(fabs(relativeOrientation.m_m[1][1]));
	absOrientation.m_m[1][2] = static_cast<LegoFloat>(fabs(relativeOrientation.m_m[1][2]));
	absOrientation.m_m[2][0] = static_cast<LegoFloat>(fabs(relativeOrientation.m_m[2][0]));
	absOrientation.m_m[2][1] = static_cast<LegoFloat>(fabs(relativeOrientation.m_m[2][1]));
	absOrientation.m_m[2][2] = static_cast<LegoFloat>(fabs(relativeOrientation.m_m[2][2]));

	*p_penetration = FLT_MAX;
	p_normal->Clear();

	LegoFloat distance = (static_cast<LegoFloat>(fabs(delta.m_x)));
	projection = GOL_MUL(absOrientation.m_m[2][0], half1z) + absOrientation.m_m[1][0] * half1y +
				 absOrientation.m_m[0][0] * half1x;
	LegoFloat total = projection + half0x;
	if (distance > total) {
		return FALSE;
	}
	overlap = total - distance;
	if (overlap < *p_penetration) {
		bestAxis = 0;
		*p_penetration = overlap;
		if (p_distance0) {
			*p_distance0 = half0x - overlap;
		}
		if (p_distance1) {
			*p_distance1 = projection - *p_penetration;
		}
	}

	distance = static_cast<LegoFloat>(fabs(
		delta.m_z * relativeOrientation.m_m[0][2] + delta.m_y * relativeOrientation.m_m[0][1] +
		delta.m_x * relativeOrientation.m_m[0][0]
	));
	projection =
		absOrientation.m_m[0][2] * half0z + absOrientation.m_m[0][1] * half0y + absOrientation.m_m[0][0] * half0x;
	total = projection + half1x;
	if (distance > total) {
		return FALSE;
	}
	overlap = total - distance;
	if (overlap < *p_penetration) {
		bestAxis = 1;
		*p_penetration = overlap;
		if (p_distance0) {
			*p_distance0 = half1x - overlap;
		}
		if (p_distance1) {
			*p_distance1 = projection - *p_penetration;
		}
	}

	distance = static_cast<LegoFloat>(fabs(delta.m_y));
	projection =
		absOrientation.m_m[2][1] * half1z + absOrientation.m_m[1][1] * half1y + absOrientation.m_m[0][1] * half1x;
	total = projection + half0y;
	if (distance > total) {
		return FALSE;
	}
	overlap = total - distance;
	if (overlap < *p_penetration) {
		bestAxis = 2;
		*p_penetration = overlap;
		if (p_distance0) {
			*p_distance0 = half0y - overlap;
		}
		if (p_distance1) {
			*p_distance1 = projection - *p_penetration;
		}
	}

	distance = static_cast<LegoFloat>(fabs(delta.m_z));
	projection =
		absOrientation.m_m[2][2] * half1z + absOrientation.m_m[1][2] * half1y + absOrientation.m_m[0][2] * half1x;
	total = projection + half0z;
	if (distance > total) {
		return FALSE;
	}
	overlap = total - distance;
	if (overlap < *p_penetration) {
		bestAxis = 3;
		*p_penetration = overlap;
		if (p_distance0) {
			*p_distance0 = half0z - overlap;
		}
		if (p_distance1) {
			*p_distance1 = projection - *p_penetration;
		}
	}

	distance = static_cast<LegoFloat>(fabs(
		delta.m_z * relativeOrientation.m_m[1][2] + delta.m_y * relativeOrientation.m_m[1][1] +
		delta.m_x * relativeOrientation.m_m[1][0]
	));
	projection =
		absOrientation.m_m[1][2] * half0z + absOrientation.m_m[1][1] * half0y + absOrientation.m_m[1][0] * half0x;
	total = projection + half1y;
	if (distance > total) {
		return FALSE;
	}
	overlap = total - distance;
	if (overlap < *p_penetration) {
		bestAxis = 4;
		*p_penetration = overlap;
		if (p_distance0) {
			*p_distance0 = half1y - overlap;
		}
		if (p_distance1) {
			*p_distance1 = projection - *p_penetration;
		}
	}

	distance = static_cast<LegoFloat>(fabs(
		delta.m_z * relativeOrientation.m_m[2][2] + delta.m_y * relativeOrientation.m_m[2][1] +
		delta.m_x * relativeOrientation.m_m[2][0]
	));
	projection =
		absOrientation.m_m[2][2] * half0z + absOrientation.m_m[2][1] * half0y + absOrientation.m_m[2][0] * half0x;
	total = projection + half1z;
	if (distance > total) {
		return FALSE;
	}
	overlap = total - distance;
	if (overlap < *p_penetration) {
		bestAxis = 5;
		*p_penetration = overlap;
		if (p_distance0) {
			*p_distance0 = half1z - overlap;
		}
		if (p_distance1) {
			*p_distance1 = projection - *p_penetration;
		}
	}

	total = (absOrientation.m_m[2][0] * half1y + absOrientation.m_m[1][0] * half1z) +
			(absOrientation.m_m[0][2] * half0y + absOrientation.m_m[0][1] * half0z);
	if ((total >= 0.001f || total <= -0.001f) &&
		static_cast<LegoFloat>(
			fabs(delta.m_z * relativeOrientation.m_m[0][1] - delta.m_y * relativeOrientation.m_m[0][2])
		) > total) {
		return FALSE;
	}

	total = (((absOrientation.m_m[2][0] * half1x)) + absOrientation.m_m[0][0] * half1z) +
			(absOrientation.m_m[1][2] * half0y + absOrientation.m_m[1][1] * half0z);
	if ((total >= 0.001f || total <= -0.001f) &&
		static_cast<LegoFloat>(
			fabs(delta.m_z * relativeOrientation.m_m[1][1] - delta.m_y * relativeOrientation.m_m[1][2])
		) > total) {
		return FALSE;
	}

	total = (absOrientation.m_m[2][2] * half0y + absOrientation.m_m[2][1] * half0z) +
			(absOrientation.m_m[1][0] * half1x + absOrientation.m_m[0][0] * half1y);
	if ((total >= 0.001f || total <= -0.001f) &&
		static_cast<LegoFloat>(
			fabs(delta.m_z * relativeOrientation.m_m[2][1] - delta.m_y * relativeOrientation.m_m[2][2])
		) > total) {
		return FALSE;
	}

	total = (absOrientation.m_m[2][1] * half1y + absOrientation.m_m[1][1] * half1z) +
			(absOrientation.m_m[0][2] * half0x + absOrientation.m_m[0][0] * half0z);
	if ((total >= 0.001f || total <= -0.001f) &&
		static_cast<LegoFloat>(
			fabs(delta.m_x * relativeOrientation.m_m[0][2] - delta.m_z * relativeOrientation.m_m[0][0])
		) > total) {
		return FALSE;
	}

	total = (absOrientation.m_m[2][1] * half1x + absOrientation.m_m[0][1] * half1z) +
			(absOrientation.m_m[1][2] * half0x + absOrientation.m_m[1][0] * half0z);
	if ((total >= 0.001f || total <= -0.001f) &&
		static_cast<LegoFloat>(
			fabs(delta.m_x * relativeOrientation.m_m[1][2] - delta.m_z * relativeOrientation.m_m[1][0])
		) > total) {
		return FALSE;
	}

	total = (absOrientation.m_m[2][2] * half0x + absOrientation.m_m[2][0] * half0z) +
			(absOrientation.m_m[1][1] * half1x + absOrientation.m_m[0][1] * half1y);
	if ((total >= 0.001f || total <= -0.001f) &&
		static_cast<LegoFloat>(
			fabs(delta.m_x * relativeOrientation.m_m[2][2] - delta.m_z * relativeOrientation.m_m[2][0])
		) > total) {
		return FALSE;
	}

	total = (absOrientation.m_m[2][2] * half1y + absOrientation.m_m[1][2] * half1z) +
			(absOrientation.m_m[0][1] * half0x + absOrientation.m_m[0][0] * half0y);
	if ((total >= 0.001f || total <= -0.001f) &&
		static_cast<LegoFloat>(
			fabs(delta.m_y * relativeOrientation.m_m[0][0] - delta.m_x * relativeOrientation.m_m[0][1])
		) > total) {
		return FALSE;
	}

	total = (absOrientation.m_m[2][2] * half1x + absOrientation.m_m[0][2] * half1z) +
			(absOrientation.m_m[1][1] * half0x + absOrientation.m_m[1][0] * half0y);
	if ((total >= 0.001f || total <= -0.001f) &&
		static_cast<LegoFloat>(
			fabs(delta.m_y * relativeOrientation.m_m[1][0] - delta.m_x * relativeOrientation.m_m[1][1])
		) > total) {
		return FALSE;
	}

	total = (absOrientation.m_m[2][1] * half0x + absOrientation.m_m[2][0] * half0y) +
			(absOrientation.m_m[1][2] * half1x + absOrientation.m_m[0][2] * half1y);
	if ((total >= 0.001f || total <= -0.001f) &&
		static_cast<LegoFloat>(
			fabs(delta.m_y * relativeOrientation.m_m[2][0] - delta.m_x * relativeOrientation.m_m[2][1])
		) > total) {
		return FALSE;
	}

	thisRow0.m_x = m_body->m_orientation.m_m[0][0];
	thisRow0.m_y = m_body->m_orientation.m_m[0][1];
	thisRow0.m_z = m_body->m_orientation.m_m[0][2];
	thisRow1.m_x = m_body->m_orientation.m_m[1][0];
	thisRow1.m_y = m_body->m_orientation.m_m[1][1];
	thisRow1.m_z = m_body->m_orientation.m_m[1][2];
	thisRow2.m_x = m_body->m_orientation.m_m[2][0];
	thisRow2.m_y = m_body->m_orientation.m_m[2][1];
	thisRow2.m_z = m_body->m_orientation.m_m[2][2];

	otherRow0.m_x = p_other->m_body->m_orientation.m_m[0][0];
	otherRow0.m_y = p_other->m_body->m_orientation.m_m[0][1];
	otherRow0.m_z = p_other->m_body->m_orientation.m_m[0][2];
	otherRow1.m_x = p_other->m_body->m_orientation.m_m[1][0];
	otherRow1.m_y = p_other->m_body->m_orientation.m_m[1][1];
	otherRow1.m_z = p_other->m_body->m_orientation.m_m[1][2];
	otherRow2.m_x = p_other->m_body->m_orientation.m_m[2][0];
	otherRow2.m_y = p_other->m_body->m_orientation.m_m[2][1];
	otherRow2.m_z = p_other->m_body->m_orientation.m_m[2][2];

	switch (bestAxis) {
	case 0:
		*p_normal = thisRow0;
		break;
	case 1:
		*p_normal = otherRow0;
		break;
	case 2:
		*p_normal = thisRow1;
		break;
	case 3:
		*p_normal = thisRow2;
		break;
	case 4:
		*p_normal = otherRow1;
		break;
	case 5:
		*p_normal = otherRow2;
		break;
	case 6:
		GolMath::CrossVector3(&thisRow0, &otherRow0, p_normal);
		GolMath::NormalizeVector3(*p_normal, p_normal);
		break;
	case 7:
		GolMath::CrossVector3(&thisRow0, &otherRow1, p_normal);
		GolMath::NormalizeVector3(*p_normal, p_normal);
		break;
	case 8:
		GolMath::CrossVector3(&thisRow0, &otherRow2, p_normal);
		GolMath::NormalizeVector3(*p_normal, p_normal);
		break;
	case 9:
		GolMath::CrossVector3(&thisRow1, &otherRow0, p_normal);
		GolMath::NormalizeVector3(*p_normal, p_normal);
		break;
	case 10:
		GolMath::CrossVector3(&thisRow1, &otherRow1, p_normal);
		GolMath::NormalizeVector3(*p_normal, p_normal);
		break;
	case 11:
		GolMath::CrossVector3(&thisRow1, &otherRow2, p_normal);
		GolMath::NormalizeVector3(*p_normal, p_normal);
		break;
	case 12:
		GolMath::CrossVector3(&thisRow2, &otherRow0, p_normal);
		GolMath::NormalizeVector3(*p_normal, p_normal);
		break;
	case 13:
		GolMath::CrossVector3(&thisRow2, &otherRow1, p_normal);
		GolMath::NormalizeVector3(*p_normal, p_normal);
		break;
	case 14:
		GolMath::CrossVector3(&thisRow2, &otherRow2, p_normal);
		GolMath::NormalizeVector3(*p_normal, p_normal);
		break;
	default:
		break;
	}

	GolVec3 direction = m_centerOfMassWorld - p_other->m_centerOfMassWorld;
	LegoFloat dot = direction.m_y * p_normal->m_y + direction.m_z * p_normal->m_z + direction.m_x * p_normal->m_x;
	if (dot < 0.0f) {
		p_normal->m_x = -p_normal->m_x;
		p_normal->m_y = -p_normal->m_y;
		p_normal->m_z = -p_normal->m_z;
	}

	return TRUE;
}
