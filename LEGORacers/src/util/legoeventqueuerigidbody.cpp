#include "golorientedentity.h"
#include "util/legoeventqueue.h"

#include <float.h>
#include <math.h>

DECOMP_SIZE_ASSERT(LegoEventQueue::Descriptor::RigidBody, 0xe4)

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

	while (TRUE) {
		LegoU32 cornerIndex = 0;
		const GolVec3* position;
		LegoFloat distance;
		GolVec3 axes[3];
		if (!shapeIndex) {
			position = &m_centerOfMassWorld;
			distance = distance0;

			LegoFloat halfX = m_boxSizeX * 0.5f;
			axes[0].m_x = m_body->m_orientation.m_m[0][0] * halfX;
			axes[0].m_y = m_body->m_orientation.m_m[0][1] * halfX;
			axes[0].m_z = m_body->m_orientation.m_m[0][2] * halfX;

			LegoFloat halfY = m_boxSizeY * 0.5f;
			axes[1].m_x = m_body->m_orientation.m_m[1][0] * halfY;
			axes[1].m_y = m_body->m_orientation.m_m[1][1] * halfY;
			axes[1].m_z = m_body->m_orientation.m_m[1][2] * halfY;

			LegoFloat halfZ = m_boxSizeZ * 0.5f;
			axes[2].m_x = m_body->m_orientation.m_m[2][0] * halfZ;
			axes[2].m_y = m_body->m_orientation.m_m[2][1] * halfZ;
			axes[2].m_z = m_body->m_orientation.m_m[2][2] * halfZ;

			if (m_boxScale != 1.0f) {
				if (m_boxScale == 0.0f) {
					return FALSE;
				}

				axes[0].m_x *= m_boxScale;
				axes[0].m_y *= m_boxScale;
				axes[0].m_z *= m_boxScale;
				axes[1].m_x *= m_boxScale;
				axes[1].m_y *= m_boxScale;
				axes[1].m_z *= m_boxScale;
				axes[2].m_x *= m_boxScale;
				axes[2].m_y *= m_boxScale;
				axes[2].m_z *= m_boxScale;
			}
		}
		else {
			position = &p_other->m_centerOfMassWorld;
			distance = distance1;

			LegoFloat halfX = p_other->m_boxSizeX * 0.5f;
			axes[0].m_x = p_other->m_body->m_orientation.m_m[0][0] * halfX;
			axes[0].m_y = p_other->m_body->m_orientation.m_m[0][1] * halfX;
			axes[0].m_z = p_other->m_body->m_orientation.m_m[0][2] * halfX;

			LegoFloat halfY = p_other->m_boxSizeY * 0.5f;
			axes[1].m_x = p_other->m_body->m_orientation.m_m[1][0] * halfY;
			axes[1].m_y = p_other->m_body->m_orientation.m_m[1][1] * halfY;
			axes[1].m_z = p_other->m_body->m_orientation.m_m[1][2] * halfY;

			LegoFloat halfZ = p_other->m_boxSizeZ * 0.5f;
			axes[2].m_x = p_other->m_body->m_orientation.m_m[2][0] * halfZ;
			axes[2].m_y = p_other->m_body->m_orientation.m_m[2][1] * halfZ;
			axes[2].m_z = p_other->m_body->m_orientation.m_m[2][2] * halfZ;

			if (p_other->m_boxScale != 1.0f) {
				if (p_other->m_boxScale == 0.0f) {
					return FALSE;
				}

				axes[0].m_x *= p_other->m_boxScale;
				axes[0].m_y *= p_other->m_boxScale;
				axes[0].m_z *= p_other->m_boxScale;
				axes[1].m_x *= p_other->m_boxScale;
				axes[1].m_y *= p_other->m_boxScale;
				axes[1].m_z *= p_other->m_boxScale;
				axes[2].m_x *= p_other->m_boxScale;
				axes[2].m_y *= p_other->m_boxScale;
				axes[2].m_z *= p_other->m_boxScale;
			}
		}

		do {
			GolVec3 corner;
			if (cornerIndex >= 4) {
				corner.m_x = -axes[0].m_x;
				corner.m_y = -axes[0].m_y;
				corner.m_z = -axes[0].m_z;
			}
			else {
				corner.m_x = axes[0].m_x;
				corner.m_y = axes[0].m_y;
				corner.m_z = axes[0].m_z;
			}

			if (cornerIndex >= 2 && (cornerIndex < 4 || cornerIndex >= 6)) {
				corner.m_x -= axes[1].m_x;
				corner.m_y -= axes[1].m_y;
				corner.m_z -= axes[1].m_z;
			}
			else {
				corner.m_x += axes[1].m_x;
				corner.m_y += axes[1].m_y;
				corner.m_z += axes[1].m_z;
			}

			if (!cornerIndex || cornerIndex == 2 || cornerIndex == 4 || cornerIndex == 6) {
				corner.m_x += axes[2].m_x;
				corner.m_y += axes[2].m_y;
				corner.m_z += axes[2].m_z;
			}
			else {
				corner.m_x -= axes[2].m_x;
				corner.m_y -= axes[2].m_y;
				corner.m_z -= axes[2].m_z;
			}

			LegoFloat projected = p_normal->m_y * corner.m_y;
			projected += corner.m_z * p_normal->m_z;
			projected += corner.m_x * p_normal->m_x;
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

		shapeIndex++;
		if (shapeIndex >= 2) {
			LegoFloat count = static_cast<LegoFloat>(contactCount);
			p_contactPoint->m_x = p_contactPoint->m_x / count;
			p_contactPoint->m_y = p_contactPoint->m_y / count;
			p_contactPoint->m_z = p_contactPoint->m_z / count;

			return TRUE;
		}
	}
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
	struct CollisionScratch {
		LegoFloat m_overlap;
		LegoFloat m_projection;
		LegoFloat m_half1z;
		LegoFloat m_half0y;
		LegoFloat m_half0z;
		LegoFloat m_half1x;
		LegoFloat m_half0x;
		LegoFloat m_half1y;
		GolVec3 m_delta;
		LegoFloat m_thisRow2X;
		LegoFloat m_thisRow2Y;
		LegoFloat m_thisRow2Z;
		LegoFloat m_thisRow0X;
		LegoFloat m_thisRow0Y;
		LegoFloat m_thisRow0Z;
		LegoFloat m_otherRow2X;
		LegoFloat m_otherRow2Y;
		LegoFloat m_otherRow2Z;
		LegoFloat m_otherRow0X;
		LegoFloat m_otherRow0Y;
		LegoFloat m_otherRow0Z;
		LegoFloat m_thisRow1X;
		LegoFloat m_thisRow1Y;
		LegoFloat m_thisRow1Z;
		LegoFloat m_otherRow1X;
		LegoFloat m_otherRow1Y;
		LegoFloat m_otherRow1Z;
		GolMatrix3 m_absOrientation;
		GolMatrix3 m_relativeOrientation;
		GolMatrix3 m_orientation0;
	};

	CollisionScratch scratch;

	m_body->CopyOrientation(&scratch.m_orientation0);
	p_other->m_body->CopyOrientation(&scratch.m_absOrientation);

	GolMath::TransformVector(
		p_other->m_centerOfMassWorld.m_x - m_centerOfMassWorld.m_x,
		p_other->m_centerOfMassWorld.m_y - m_centerOfMassWorld.m_y,
		p_other->m_centerOfMassWorld.m_z - m_centerOfMassWorld.m_z,
		&scratch.m_orientation0.m_m[0][0],
		&scratch.m_delta
	);

	GolMath::MultiplyMatrixByTranspose(
		&scratch.m_absOrientation.m_m[0][0],
		&scratch.m_orientation0.m_m[0][0],
		&scratch.m_relativeOrientation.m_m[0][0]
	);

	scratch.m_half0x = m_boxSizeX * 0.5f;
	scratch.m_half0y = m_boxSizeY * 0.5f;
	scratch.m_half0z = m_boxSizeZ * 0.5f;
	if (m_boxScale != 1.0f) {
		if (m_boxScale == 0.0f) {
			return FALSE;
		}

		scratch.m_half0x = scratch.m_half0x * m_boxScale;
		scratch.m_half0y = scratch.m_half0y * m_boxScale;
		scratch.m_half0z = scratch.m_half0z * m_boxScale;
	}

	scratch.m_half1x = p_other->m_boxSizeX * 0.5f;
	scratch.m_half1y = p_other->m_boxSizeY * 0.5f;
	scratch.m_half1z = p_other->m_boxSizeZ * 0.5f;
	if (p_other->m_boxScale != 1.0f) {
		if (p_other->m_boxScale == 0.0f) {
			return FALSE;
		}

		scratch.m_half1x = scratch.m_half1x * p_other->m_boxScale;
		scratch.m_half1y = scratch.m_half1y * p_other->m_boxScale;
		scratch.m_half1z = scratch.m_half1z * p_other->m_boxScale;
	}

	scratch.m_absOrientation.m_m[0][0] = static_cast<LegoFloat>(fabs(scratch.m_relativeOrientation.m_m[0][0]));
	scratch.m_absOrientation.m_m[0][1] = static_cast<LegoFloat>(fabs(scratch.m_relativeOrientation.m_m[0][1]));
	scratch.m_absOrientation.m_m[0][2] = static_cast<LegoFloat>(fabs(scratch.m_relativeOrientation.m_m[0][2]));
	scratch.m_absOrientation.m_m[1][0] = static_cast<LegoFloat>(fabs(scratch.m_relativeOrientation.m_m[1][0]));
	scratch.m_absOrientation.m_m[1][1] = static_cast<LegoFloat>(fabs(scratch.m_relativeOrientation.m_m[1][1]));
	scratch.m_absOrientation.m_m[1][2] = static_cast<LegoFloat>(fabs(scratch.m_relativeOrientation.m_m[1][2]));
	scratch.m_absOrientation.m_m[2][0] = static_cast<LegoFloat>(fabs(scratch.m_relativeOrientation.m_m[2][0]));
	scratch.m_absOrientation.m_m[2][1] = static_cast<LegoFloat>(fabs(scratch.m_relativeOrientation.m_m[2][1]));
	scratch.m_absOrientation.m_m[2][2] = static_cast<LegoFloat>(fabs(scratch.m_relativeOrientation.m_m[2][2]));

	*p_penetration = FLT_MAX;
	p_normal->m_x = 0.0f;
	p_normal->m_y = 0.0f;
	p_normal->m_z = 0.0f;

	LegoFloat distance = static_cast<LegoFloat>(fabs(scratch.m_delta.m_x));
	scratch.m_projection = scratch.m_absOrientation.m_m[2][0] * scratch.m_half1z +
						   scratch.m_absOrientation.m_m[1][0] * scratch.m_half1y +
						   scratch.m_absOrientation.m_m[0][0] * scratch.m_half1x;
	LegoFloat total = scratch.m_projection + scratch.m_half0x;
	if (distance > total) {
		return FALSE;
	}
	scratch.m_overlap = total - distance;
	if (scratch.m_overlap < *p_penetration) {
		bestAxis = 0;
		*p_penetration = scratch.m_overlap;
		if (p_distance0) {
			*p_distance0 = scratch.m_half0x - scratch.m_overlap;
		}
		if (p_distance1) {
			*p_distance1 = scratch.m_projection - *p_penetration;
		}
	}

	distance = static_cast<LegoFloat>(fabs(
		scratch.m_delta.m_z * scratch.m_relativeOrientation.m_m[0][2] +
		scratch.m_delta.m_y * scratch.m_relativeOrientation.m_m[0][1] +
		scratch.m_delta.m_x * scratch.m_relativeOrientation.m_m[0][0]
	));
	scratch.m_projection = scratch.m_absOrientation.m_m[0][2] * scratch.m_half0z +
						   scratch.m_absOrientation.m_m[0][1] * scratch.m_half0y +
						   scratch.m_absOrientation.m_m[0][0] * scratch.m_half0x;
	total = scratch.m_projection + scratch.m_half1x;
	if (distance > total) {
		return FALSE;
	}
	scratch.m_overlap = total - distance;
	if (scratch.m_overlap < *p_penetration) {
		bestAxis = 1;
		*p_penetration = scratch.m_overlap;
		if (p_distance0) {
			*p_distance0 = scratch.m_half1x - scratch.m_overlap;
		}
		if (p_distance1) {
			*p_distance1 = scratch.m_projection - *p_penetration;
		}
	}

	distance = static_cast<LegoFloat>(fabs(scratch.m_delta.m_y));
	scratch.m_projection = scratch.m_absOrientation.m_m[2][1] * scratch.m_half1z +
						   scratch.m_absOrientation.m_m[1][1] * scratch.m_half1y +
						   scratch.m_absOrientation.m_m[0][1] * scratch.m_half1x;
	total = scratch.m_projection + scratch.m_half0y;
	if (distance > total) {
		return FALSE;
	}
	scratch.m_overlap = total - distance;
	if (scratch.m_overlap < *p_penetration) {
		bestAxis = 2;
		*p_penetration = scratch.m_overlap;
		if (p_distance0) {
			*p_distance0 = scratch.m_half0y - scratch.m_overlap;
		}
		if (p_distance1) {
			*p_distance1 = scratch.m_projection - *p_penetration;
		}
	}

	distance = static_cast<LegoFloat>(fabs(scratch.m_delta.m_z));
	scratch.m_projection = scratch.m_absOrientation.m_m[2][2] * scratch.m_half1z +
						   scratch.m_absOrientation.m_m[1][2] * scratch.m_half1y +
						   scratch.m_absOrientation.m_m[0][2] * scratch.m_half1x;
	total = scratch.m_projection + scratch.m_half0z;
	if (distance > total) {
		return FALSE;
	}
	scratch.m_overlap = total - distance;
	if (scratch.m_overlap < *p_penetration) {
		bestAxis = 3;
		*p_penetration = scratch.m_overlap;
		if (p_distance0) {
			*p_distance0 = scratch.m_half0z - scratch.m_overlap;
		}
		if (p_distance1) {
			*p_distance1 = scratch.m_projection - *p_penetration;
		}
	}

	distance = static_cast<LegoFloat>(fabs(
		scratch.m_delta.m_z * scratch.m_relativeOrientation.m_m[1][2] +
		scratch.m_delta.m_y * scratch.m_relativeOrientation.m_m[1][1] +
		scratch.m_delta.m_x * scratch.m_relativeOrientation.m_m[1][0]
	));
	scratch.m_projection = scratch.m_absOrientation.m_m[1][2] * scratch.m_half0z +
						   scratch.m_absOrientation.m_m[1][1] * scratch.m_half0y +
						   scratch.m_absOrientation.m_m[1][0] * scratch.m_half0x;
	total = scratch.m_projection + scratch.m_half1y;
	if (distance > total) {
		return FALSE;
	}
	scratch.m_overlap = total - distance;
	if (scratch.m_overlap < *p_penetration) {
		bestAxis = 4;
		*p_penetration = scratch.m_overlap;
		if (p_distance0) {
			*p_distance0 = scratch.m_half1y - scratch.m_overlap;
		}
		if (p_distance1) {
			*p_distance1 = scratch.m_projection - *p_penetration;
		}
	}

	distance = static_cast<LegoFloat>(fabs(
		scratch.m_delta.m_z * scratch.m_relativeOrientation.m_m[2][2] +
		scratch.m_delta.m_y * scratch.m_relativeOrientation.m_m[2][1] +
		scratch.m_delta.m_x * scratch.m_relativeOrientation.m_m[2][0]
	));
	scratch.m_projection = scratch.m_absOrientation.m_m[2][2] * scratch.m_half0z +
						   scratch.m_absOrientation.m_m[2][1] * scratch.m_half0y +
						   scratch.m_absOrientation.m_m[2][0] * scratch.m_half0x;
	total = scratch.m_projection + scratch.m_half1z;
	if (distance > total) {
		return FALSE;
	}
	scratch.m_overlap = total - distance;
	if (scratch.m_overlap < *p_penetration) {
		bestAxis = 5;
		*p_penetration = scratch.m_overlap;
		if (p_distance0) {
			*p_distance0 = scratch.m_half1z - scratch.m_overlap;
		}
		if (p_distance1) {
			*p_distance1 = scratch.m_projection - *p_penetration;
		}
	}

	total =
		scratch.m_absOrientation.m_m[2][0] * scratch.m_half1y + scratch.m_absOrientation.m_m[1][0] * scratch.m_half1z +
		scratch.m_absOrientation.m_m[0][2] * scratch.m_half0y + scratch.m_absOrientation.m_m[0][1] * scratch.m_half0z;
	if ((total >= 0.001f || total <= -0.001f) && static_cast<LegoFloat>(fabs(
													 scratch.m_delta.m_z * scratch.m_relativeOrientation.m_m[0][1] -
													 scratch.m_delta.m_y * scratch.m_relativeOrientation.m_m[0][2]
												 )) > total) {
		return FALSE;
	}

	total =
		scratch.m_absOrientation.m_m[2][0] * scratch.m_half1x + scratch.m_absOrientation.m_m[0][0] * scratch.m_half1z +
		scratch.m_absOrientation.m_m[1][2] * scratch.m_half0y + scratch.m_absOrientation.m_m[1][1] * scratch.m_half0z;
	if ((total >= 0.001f || total <= -0.001f) && static_cast<LegoFloat>(fabs(
													 scratch.m_delta.m_z * scratch.m_relativeOrientation.m_m[1][1] -
													 scratch.m_delta.m_y * scratch.m_relativeOrientation.m_m[1][2]
												 )) > total) {
		return FALSE;
	}

	total =
		scratch.m_absOrientation.m_m[2][2] * scratch.m_half0y + scratch.m_absOrientation.m_m[2][1] * scratch.m_half0z +
		scratch.m_absOrientation.m_m[1][0] * scratch.m_half1x + scratch.m_absOrientation.m_m[0][0] * scratch.m_half1y;
	if ((total >= 0.001f || total <= -0.001f) && static_cast<LegoFloat>(fabs(
													 scratch.m_delta.m_z * scratch.m_relativeOrientation.m_m[2][1] -
													 scratch.m_delta.m_y * scratch.m_relativeOrientation.m_m[2][2]
												 )) > total) {
		return FALSE;
	}

	total =
		scratch.m_absOrientation.m_m[2][1] * scratch.m_half1y + scratch.m_absOrientation.m_m[1][1] * scratch.m_half1z +
		scratch.m_absOrientation.m_m[0][2] * scratch.m_half0x + scratch.m_absOrientation.m_m[0][0] * scratch.m_half0z;
	if ((total >= 0.001f || total <= -0.001f) && static_cast<LegoFloat>(fabs(
													 scratch.m_delta.m_x * scratch.m_relativeOrientation.m_m[0][2] -
													 scratch.m_delta.m_z * scratch.m_relativeOrientation.m_m[0][0]
												 )) > total) {
		return FALSE;
	}

	total =
		scratch.m_absOrientation.m_m[2][1] * scratch.m_half1x + scratch.m_absOrientation.m_m[0][1] * scratch.m_half1z +
		scratch.m_absOrientation.m_m[1][2] * scratch.m_half0x + scratch.m_absOrientation.m_m[1][0] * scratch.m_half0z;
	if ((total >= 0.001f || total <= -0.001f) && static_cast<LegoFloat>(fabs(
													 scratch.m_delta.m_x * scratch.m_relativeOrientation.m_m[1][2] -
													 scratch.m_delta.m_z * scratch.m_relativeOrientation.m_m[1][0]
												 )) > total) {
		return FALSE;
	}

	total =
		scratch.m_absOrientation.m_m[2][2] * scratch.m_half0x + scratch.m_absOrientation.m_m[2][0] * scratch.m_half0z +
		scratch.m_absOrientation.m_m[1][1] * scratch.m_half1x + scratch.m_absOrientation.m_m[0][1] * scratch.m_half1y;
	if ((total >= 0.001f || total <= -0.001f) && static_cast<LegoFloat>(fabs(
													 scratch.m_delta.m_x * scratch.m_relativeOrientation.m_m[2][2] -
													 scratch.m_delta.m_z * scratch.m_relativeOrientation.m_m[2][0]
												 )) > total) {
		return FALSE;
	}

	total =
		scratch.m_absOrientation.m_m[2][2] * scratch.m_half1y + scratch.m_absOrientation.m_m[1][2] * scratch.m_half1z +
		scratch.m_absOrientation.m_m[0][1] * scratch.m_half0x + scratch.m_absOrientation.m_m[0][0] * scratch.m_half0y;
	if ((total >= 0.001f || total <= -0.001f) && static_cast<LegoFloat>(fabs(
													 scratch.m_delta.m_y * scratch.m_relativeOrientation.m_m[0][0] -
													 scratch.m_delta.m_x * scratch.m_relativeOrientation.m_m[0][1]
												 )) > total) {
		return FALSE;
	}

	total =
		scratch.m_absOrientation.m_m[2][2] * scratch.m_half1x + scratch.m_absOrientation.m_m[0][2] * scratch.m_half1z +
		scratch.m_absOrientation.m_m[1][1] * scratch.m_half0x + scratch.m_absOrientation.m_m[1][0] * scratch.m_half0y;
	if ((total >= 0.001f || total <= -0.001f) && static_cast<LegoFloat>(fabs(
													 scratch.m_delta.m_y * scratch.m_relativeOrientation.m_m[1][0] -
													 scratch.m_delta.m_x * scratch.m_relativeOrientation.m_m[1][1]
												 )) > total) {
		return FALSE;
	}

	total =
		scratch.m_absOrientation.m_m[2][1] * scratch.m_half0x + scratch.m_absOrientation.m_m[2][0] * scratch.m_half0y +
		scratch.m_absOrientation.m_m[1][2] * scratch.m_half1x + scratch.m_absOrientation.m_m[0][2] * scratch.m_half1y;
	if ((total >= 0.001f || total <= -0.001f) && static_cast<LegoFloat>(fabs(
													 scratch.m_delta.m_y * scratch.m_relativeOrientation.m_m[2][0] -
													 scratch.m_delta.m_x * scratch.m_relativeOrientation.m_m[2][1]
												 )) > total) {
		return FALSE;
	}

	scratch.m_thisRow0X = m_body->m_orientation.m_m[0][0];
	scratch.m_thisRow0Y = m_body->m_orientation.m_m[0][1];
	scratch.m_thisRow0Z = m_body->m_orientation.m_m[0][2];
	scratch.m_thisRow1X = m_body->m_orientation.m_m[1][0];
	scratch.m_thisRow1Y = m_body->m_orientation.m_m[1][1];
	scratch.m_thisRow1Z = m_body->m_orientation.m_m[1][2];
	scratch.m_thisRow2X = m_body->m_orientation.m_m[2][0];
	scratch.m_thisRow2Y = m_body->m_orientation.m_m[2][1];
	scratch.m_thisRow2Z = m_body->m_orientation.m_m[2][2];

	scratch.m_otherRow0X = p_other->m_body->m_orientation.m_m[0][0];
	scratch.m_otherRow0Y = p_other->m_body->m_orientation.m_m[0][1];
	scratch.m_otherRow0Z = p_other->m_body->m_orientation.m_m[0][2];
	scratch.m_otherRow1X = p_other->m_body->m_orientation.m_m[1][0];
	scratch.m_otherRow1Y = p_other->m_body->m_orientation.m_m[1][1];
	scratch.m_otherRow1Z = p_other->m_body->m_orientation.m_m[1][2];
	scratch.m_otherRow2X = p_other->m_body->m_orientation.m_m[2][0];
	scratch.m_otherRow2Y = p_other->m_body->m_orientation.m_m[2][1];
	scratch.m_otherRow2Z = p_other->m_body->m_orientation.m_m[2][2];

	switch (bestAxis) {
	case 0:
		p_normal->m_x = scratch.m_thisRow0X;
		p_normal->m_y = scratch.m_thisRow0Y;
		p_normal->m_z = scratch.m_thisRow0Z;
		break;
	case 1:
		p_normal->m_x = scratch.m_otherRow0X;
		p_normal->m_y = scratch.m_otherRow0Y;
		p_normal->m_z = scratch.m_otherRow0Z;
		break;
	case 2:
		p_normal->m_x = scratch.m_thisRow1X;
		p_normal->m_y = scratch.m_thisRow1Y;
		p_normal->m_z = scratch.m_thisRow1Z;
		break;
	case 3:
		p_normal->m_x = scratch.m_thisRow2X;
		p_normal->m_y = scratch.m_thisRow2Y;
		p_normal->m_z = scratch.m_thisRow2Z;
		break;
	case 4:
		p_normal->m_x = scratch.m_otherRow1X;
		p_normal->m_y = scratch.m_otherRow1Y;
		p_normal->m_z = scratch.m_otherRow1Z;
		break;
	case 5:
		p_normal->m_x = scratch.m_otherRow2X;
		p_normal->m_y = scratch.m_otherRow2Y;
		p_normal->m_z = scratch.m_otherRow2Z;
		break;
	case 6:
		p_normal->m_x = scratch.m_otherRow0Z * scratch.m_thisRow0Y - scratch.m_otherRow0Y * scratch.m_thisRow0Z;
		p_normal->m_y = scratch.m_thisRow0Z * scratch.m_otherRow0X - scratch.m_otherRow0Z * scratch.m_thisRow0X;
		p_normal->m_z = scratch.m_otherRow0Y * scratch.m_thisRow0X - scratch.m_thisRow0Y * scratch.m_otherRow0X;
		GolMath::NormalizeVector3(*p_normal, p_normal);
		break;
	case 7:
		p_normal->m_x = scratch.m_otherRow1Z * scratch.m_thisRow0Y - scratch.m_otherRow1Y * scratch.m_thisRow0Z;
		p_normal->m_y = scratch.m_thisRow0Z * scratch.m_otherRow1X - scratch.m_otherRow1Z * scratch.m_thisRow0X;
		p_normal->m_z = scratch.m_otherRow1Y * scratch.m_thisRow0X - scratch.m_thisRow0Y * scratch.m_otherRow1X;
		GolMath::NormalizeVector3(*p_normal, p_normal);
		break;
	case 8:
		p_normal->m_x = scratch.m_otherRow2Z * scratch.m_thisRow0Y - scratch.m_otherRow2Y * scratch.m_thisRow0Z;
		p_normal->m_y = scratch.m_thisRow0Z * scratch.m_otherRow2X - scratch.m_otherRow2Z * scratch.m_thisRow0X;
		p_normal->m_z = scratch.m_otherRow2Y * scratch.m_thisRow0X - scratch.m_thisRow0Y * scratch.m_otherRow2X;
		GolMath::NormalizeVector3(*p_normal, p_normal);
		break;
	case 9:
		p_normal->m_x = scratch.m_otherRow0Z * scratch.m_thisRow1Y - scratch.m_otherRow0Y * scratch.m_thisRow1Z;
		p_normal->m_y = scratch.m_thisRow1Z * scratch.m_otherRow0X - scratch.m_otherRow0Z * scratch.m_thisRow1X;
		p_normal->m_z = scratch.m_otherRow0Y * scratch.m_thisRow1X - scratch.m_thisRow1Y * scratch.m_otherRow0X;
		GolMath::NormalizeVector3(*p_normal, p_normal);
		break;
	case 10:
		p_normal->m_x = scratch.m_otherRow1Z * scratch.m_thisRow1Y - scratch.m_otherRow1Y * scratch.m_thisRow1Z;
		p_normal->m_y = scratch.m_thisRow1Z * scratch.m_otherRow1X - scratch.m_otherRow1Z * scratch.m_thisRow1X;
		p_normal->m_z = scratch.m_otherRow1Y * scratch.m_thisRow1X - scratch.m_thisRow1Y * scratch.m_otherRow1X;
		GolMath::NormalizeVector3(*p_normal, p_normal);
		break;
	case 11:
		p_normal->m_x = scratch.m_otherRow2Z * scratch.m_thisRow1Y - scratch.m_otherRow2Y * scratch.m_thisRow1Z;
		p_normal->m_y = scratch.m_thisRow1Z * scratch.m_otherRow2X - scratch.m_otherRow2Z * scratch.m_thisRow1X;
		p_normal->m_z = scratch.m_otherRow2Y * scratch.m_thisRow1X - scratch.m_thisRow1Y * scratch.m_otherRow2X;
		GolMath::NormalizeVector3(*p_normal, p_normal);
		break;
	case 12:
		p_normal->m_x = scratch.m_otherRow0Z * scratch.m_thisRow2Y - scratch.m_otherRow0Y * scratch.m_thisRow2Z;
		p_normal->m_y = scratch.m_thisRow2Z * scratch.m_otherRow0X - scratch.m_otherRow0Z * scratch.m_thisRow2X;
		p_normal->m_z = scratch.m_otherRow0Y * scratch.m_thisRow2X - scratch.m_thisRow2Y * scratch.m_otherRow0X;
		GolMath::NormalizeVector3(*p_normal, p_normal);
		break;
	case 13:
		p_normal->m_x = scratch.m_otherRow1Z * scratch.m_thisRow2Y - scratch.m_otherRow1Y * scratch.m_thisRow2Z;
		p_normal->m_y = scratch.m_thisRow2Z * scratch.m_otherRow1X - scratch.m_otherRow1Z * scratch.m_thisRow2X;
		p_normal->m_z = scratch.m_otherRow1Y * scratch.m_thisRow2X - scratch.m_thisRow2Y * scratch.m_otherRow1X;
		GolMath::NormalizeVector3(*p_normal, p_normal);
		break;
	case 14:
		p_normal->m_x = scratch.m_otherRow2Z * scratch.m_thisRow2Y - scratch.m_otherRow2Y * scratch.m_thisRow2Z;
		p_normal->m_y = scratch.m_thisRow2Z * scratch.m_otherRow2X - scratch.m_otherRow2Z * scratch.m_thisRow2X;
		p_normal->m_z = scratch.m_otherRow2Y * scratch.m_thisRow2X - scratch.m_thisRow2Y * scratch.m_otherRow2X;
		GolMath::NormalizeVector3(*p_normal, p_normal);
		break;
	default:
		break;
	}

	if ((m_centerOfMassWorld.m_y - p_other->m_centerOfMassWorld.m_y) * p_normal->m_y +
			p_normal->m_z * (m_centerOfMassWorld.m_z - p_other->m_centerOfMassWorld.m_z) +
			(m_centerOfMassWorld.m_x - p_other->m_centerOfMassWorld.m_x) * p_normal->m_x <
		0.0f) {
		p_normal->m_x = -p_normal->m_x;
		p_normal->m_y = -p_normal->m_y;
		p_normal->m_z = -p_normal->m_z;
	}

	return TRUE;
}
