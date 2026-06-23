#include "util/legoeventqueue.h"

#include <float.h>
#include <math.h>

DECOMP_SIZE_ASSERT(LegoEventQueue::Descriptor::Field0x10, 0xe4)

// STUB: LEGORACERS 0x00441330
LegoBool32 LegoEventQueue::Descriptor::Field0x10::FUN_00441330(
	Field0x10* p_other,
	LegoFloat* p_unk0x08,
	GolVec3* p_unk0x0c,
	GolVec3* p_unk0x10
)
{
	LegoFloat distance0;
	LegoFloat distance1;
	if (!FUN_00441790(p_other, p_unk0x08, p_unk0x0c, &distance0, &distance1)) {
		return FALSE;
	}

	LegoS32 contactCount = 0;
	LegoU32 shapeIndex = 0;
	p_unk0x10->m_x = 0.0f;
	p_unk0x10->m_y = 0.0f;
	p_unk0x10->m_z = 0.0f;

	while (TRUE) {
		LegoU32 cornerIndex = 0;
		const GolVec3* position;
		LegoFloat distance;
		GolVec3 axis0;
		GolVec3 axis1;
		GolVec3 axis2;
		if (!shapeIndex) {
			position = &m_unk0x020;
			distance = distance0;

			const GolMatrix3& orientation = m_unk0x004->m_orientation;
			LegoFloat halfX = m_unk0x0d0 * 0.5f;
			axis0.m_x = orientation.m_m[0][0] * halfX;
			axis0.m_y = orientation.m_m[0][1] * halfX;
			axis0.m_z = orientation.m_m[0][2] * halfX;

			LegoFloat halfY = m_unk0x0d4 * 0.5f;
			axis1.m_x = orientation.m_m[1][0] * halfY;
			axis1.m_y = orientation.m_m[1][1] * halfY;
			axis1.m_z = orientation.m_m[1][2] * halfY;

			LegoFloat halfZ = m_unk0x0d8 * 0.5f;
			axis2.m_x = orientation.m_m[2][0] * halfZ;
			axis2.m_y = orientation.m_m[2][1] * halfZ;
			axis2.m_z = orientation.m_m[2][2] * halfZ;

			LegoFloat scale = m_unk0x0dc;
			if (scale != 1.0f) {
				if (scale == 0.0f) {
					return FALSE;
				}

				axis0.m_x *= scale;
				axis0.m_y *= scale;
				axis0.m_z *= scale;
				axis1.m_x *= scale;
				axis1.m_y *= scale;
				axis1.m_z *= scale;
				axis2.m_x *= scale;
				axis2.m_y *= scale;
				axis2.m_z *= scale;
			}
		}
		else {
			position = &p_other->m_unk0x020;
			distance = distance1;

			const GolMatrix3& orientation = p_other->m_unk0x004->m_orientation;
			LegoFloat halfX = p_other->m_unk0x0d0 * 0.5f;
			axis0.m_x = orientation.m_m[0][0] * halfX;
			axis0.m_y = orientation.m_m[0][1] * halfX;
			axis0.m_z = orientation.m_m[0][2] * halfX;

			LegoFloat halfY = p_other->m_unk0x0d4 * 0.5f;
			axis1.m_x = orientation.m_m[1][0] * halfY;
			axis1.m_y = orientation.m_m[1][1] * halfY;
			axis1.m_z = orientation.m_m[1][2] * halfY;

			LegoFloat halfZ = p_other->m_unk0x0d8 * 0.5f;
			axis2.m_x = orientation.m_m[2][0] * halfZ;
			axis2.m_y = orientation.m_m[2][1] * halfZ;
			axis2.m_z = orientation.m_m[2][2] * halfZ;

			LegoFloat scale = p_other->m_unk0x0dc;
			if (scale != 1.0f) {
				if (scale == 0.0f) {
					return FALSE;
				}

				axis0.m_x *= scale;
				axis0.m_y *= scale;
				axis0.m_z *= scale;
				axis1.m_x *= scale;
				axis1.m_y *= scale;
				axis1.m_z *= scale;
				axis2.m_x *= scale;
				axis2.m_y *= scale;
				axis2.m_z *= scale;
			}
		}

		do {
			GolVec3 corner;
			if (cornerIndex >= 4) {
				corner.m_x = -axis0.m_x;
				corner.m_y = -axis0.m_y;
				corner.m_z = -axis0.m_z;
			}
			else {
				corner.m_x = axis0.m_x;
				corner.m_y = axis0.m_y;
				corner.m_z = axis0.m_z;
			}

			if (cornerIndex >= 2 && (cornerIndex < 4 || cornerIndex >= 6)) {
				corner.m_x -= axis1.m_x;
				corner.m_y -= axis1.m_y;
				corner.m_z -= axis1.m_z;
			}
			else {
				corner.m_x += axis1.m_x;
				corner.m_y += axis1.m_y;
				corner.m_z += axis1.m_z;
			}

			if (!cornerIndex || cornerIndex == 2 || cornerIndex == 4 || cornerIndex == 6) {
				corner.m_x += axis2.m_x;
				corner.m_y += axis2.m_y;
				corner.m_z += axis2.m_z;
			}
			else {
				corner.m_x -= axis2.m_x;
				corner.m_y -= axis2.m_y;
				corner.m_z -= axis2.m_z;
			}

			LegoFloat projected = p_unk0x0c->m_y * corner.m_y;
			projected += corner.m_z * p_unk0x0c->m_z;
			projected += corner.m_x * p_unk0x0c->m_x;
			if (shapeIndex == 1) {
				projected = -projected;
			}

			if (projected >= distance) {
				contactCount++;
				p_unk0x10->m_x = position->m_x + p_unk0x10->m_x + corner.m_x;
				p_unk0x10->m_y = position->m_y + p_unk0x10->m_y + corner.m_y;
				p_unk0x10->m_z = corner.m_z + position->m_z + p_unk0x10->m_z;
			}
			cornerIndex++;
		} while (cornerIndex < 8);

		shapeIndex++;
		if (shapeIndex >= 2) {
			LegoFloat count = static_cast<LegoFloat>(contactCount);
			p_unk0x10->m_x = p_unk0x10->m_x / count;
			p_unk0x10->m_y = p_unk0x10->m_y / count;
			p_unk0x10->m_z = p_unk0x10->m_z / count;

			return TRUE;
		}
	}
}

// FUNCTION: LEGORACERS 0x00441790
LegoBool32 LegoEventQueue::Descriptor::Field0x10::FUN_00441790(
	Field0x10* p_other,
	LegoFloat* p_unk0x08,
	GolVec3* p_unk0x0c,
	LegoFloat* p_unk0x10,
	LegoFloat* p_unk0x14
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

	m_unk0x004->VTable0x44(&scratch.m_orientation0);
	p_other->m_unk0x004->VTable0x44(&scratch.m_absOrientation);

	GolMath::FUN_00449b90(
		p_other->m_unk0x020.m_x - m_unk0x020.m_x,
		p_other->m_unk0x020.m_y - m_unk0x020.m_y,
		p_other->m_unk0x020.m_z - m_unk0x020.m_z,
		&scratch.m_orientation0.m_m[0][0],
		&scratch.m_delta
	);

	GolMath::FUN_00449bf0(
		&scratch.m_absOrientation.m_m[0][0],
		&scratch.m_orientation0.m_m[0][0],
		&scratch.m_relativeOrientation.m_m[0][0]
	);

	scratch.m_half0x = m_unk0x0d0 * 0.5f;
	scratch.m_half0y = m_unk0x0d4 * 0.5f;
	scratch.m_half0z = m_unk0x0d8 * 0.5f;
	if (m_unk0x0dc != 1.0f) {
		if (m_unk0x0dc == 0.0f) {
			return FALSE;
		}

		scratch.m_half0x = m_unk0x0dc * scratch.m_half0x;
		scratch.m_half0y = m_unk0x0dc * scratch.m_half0y;
		scratch.m_half0z = m_unk0x0dc * scratch.m_half0z;
	}

	scratch.m_half1x = p_other->m_unk0x0d0 * 0.5f;
	scratch.m_half1y = p_other->m_unk0x0d4 * 0.5f;
	scratch.m_half1z = p_other->m_unk0x0d8 * 0.5f;
	if (p_other->m_unk0x0dc != 1.0f) {
		if (p_other->m_unk0x0dc == 0.0f) {
			return FALSE;
		}

		scratch.m_half1x = p_other->m_unk0x0dc * scratch.m_half1x;
		scratch.m_half1y = p_other->m_unk0x0dc * scratch.m_half1y;
		scratch.m_half1z = p_other->m_unk0x0dc * scratch.m_half1z;
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

	*p_unk0x08 = FLT_MAX;
	p_unk0x0c->m_x = 0.0f;
	p_unk0x0c->m_y = 0.0f;
	p_unk0x0c->m_z = 0.0f;

	LegoFloat distance = static_cast<LegoFloat>(fabs(scratch.m_delta.m_x));
	scratch.m_projection = scratch.m_absOrientation.m_m[2][0] * scratch.m_half1z +
						   scratch.m_absOrientation.m_m[1][0] * scratch.m_half1y +
						   scratch.m_absOrientation.m_m[0][0] * scratch.m_half1x;
	LegoFloat total = scratch.m_projection + scratch.m_half0x;
	if (distance > total) {
		return FALSE;
	}
	scratch.m_overlap = total - distance;
	if (scratch.m_overlap < *p_unk0x08) {
		bestAxis = 0;
		*p_unk0x08 = scratch.m_overlap;
		if (p_unk0x10) {
			*p_unk0x10 = scratch.m_half0x - scratch.m_overlap;
		}
		if (p_unk0x14) {
			*p_unk0x14 = scratch.m_projection - *p_unk0x08;
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
	if (scratch.m_overlap < *p_unk0x08) {
		bestAxis = 1;
		*p_unk0x08 = scratch.m_overlap;
		if (p_unk0x10) {
			*p_unk0x10 = scratch.m_half1x - scratch.m_overlap;
		}
		if (p_unk0x14) {
			*p_unk0x14 = scratch.m_projection - *p_unk0x08;
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
	if (scratch.m_overlap < *p_unk0x08) {
		bestAxis = 2;
		*p_unk0x08 = scratch.m_overlap;
		if (p_unk0x10) {
			*p_unk0x10 = scratch.m_half0y - scratch.m_overlap;
		}
		if (p_unk0x14) {
			*p_unk0x14 = scratch.m_projection - *p_unk0x08;
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
	if (scratch.m_overlap < *p_unk0x08) {
		bestAxis = 3;
		*p_unk0x08 = scratch.m_overlap;
		if (p_unk0x10) {
			*p_unk0x10 = scratch.m_half0z - scratch.m_overlap;
		}
		if (p_unk0x14) {
			*p_unk0x14 = scratch.m_projection - *p_unk0x08;
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
	if (scratch.m_overlap < *p_unk0x08) {
		bestAxis = 4;
		*p_unk0x08 = scratch.m_overlap;
		if (p_unk0x10) {
			*p_unk0x10 = scratch.m_half1y - scratch.m_overlap;
		}
		if (p_unk0x14) {
			*p_unk0x14 = scratch.m_projection - *p_unk0x08;
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
	if (scratch.m_overlap < *p_unk0x08) {
		bestAxis = 5;
		*p_unk0x08 = scratch.m_overlap;
		if (p_unk0x10) {
			*p_unk0x10 = scratch.m_half1z - scratch.m_overlap;
		}
		if (p_unk0x14) {
			*p_unk0x14 = scratch.m_projection - *p_unk0x08;
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

	scratch.m_thisRow0X = m_unk0x004->m_orientation.m_m[0][0];
	scratch.m_thisRow0Y = m_unk0x004->m_orientation.m_m[0][1];
	scratch.m_thisRow0Z = m_unk0x004->m_orientation.m_m[0][2];
	scratch.m_thisRow1X = m_unk0x004->m_orientation.m_m[1][0];
	scratch.m_thisRow1Y = m_unk0x004->m_orientation.m_m[1][1];
	scratch.m_thisRow1Z = m_unk0x004->m_orientation.m_m[1][2];
	scratch.m_thisRow2X = m_unk0x004->m_orientation.m_m[2][0];
	scratch.m_thisRow2Y = m_unk0x004->m_orientation.m_m[2][1];
	scratch.m_thisRow2Z = m_unk0x004->m_orientation.m_m[2][2];

	scratch.m_otherRow0X = p_other->m_unk0x004->m_orientation.m_m[0][0];
	scratch.m_otherRow0Y = p_other->m_unk0x004->m_orientation.m_m[0][1];
	scratch.m_otherRow0Z = p_other->m_unk0x004->m_orientation.m_m[0][2];
	scratch.m_otherRow1X = p_other->m_unk0x004->m_orientation.m_m[1][0];
	scratch.m_otherRow1Y = p_other->m_unk0x004->m_orientation.m_m[1][1];
	scratch.m_otherRow1Z = p_other->m_unk0x004->m_orientation.m_m[1][2];
	scratch.m_otherRow2X = p_other->m_unk0x004->m_orientation.m_m[2][0];
	scratch.m_otherRow2Y = p_other->m_unk0x004->m_orientation.m_m[2][1];
	scratch.m_otherRow2Z = p_other->m_unk0x004->m_orientation.m_m[2][2];

	switch (bestAxis) {
	case 0:
		p_unk0x0c->m_x = scratch.m_thisRow0X;
		p_unk0x0c->m_y = scratch.m_thisRow0Y;
		p_unk0x0c->m_z = scratch.m_thisRow0Z;
		break;
	case 1:
		p_unk0x0c->m_x = scratch.m_otherRow0X;
		p_unk0x0c->m_y = scratch.m_otherRow0Y;
		p_unk0x0c->m_z = scratch.m_otherRow0Z;
		break;
	case 2:
		p_unk0x0c->m_x = scratch.m_thisRow1X;
		p_unk0x0c->m_y = scratch.m_thisRow1Y;
		p_unk0x0c->m_z = scratch.m_thisRow1Z;
		break;
	case 3:
		p_unk0x0c->m_x = scratch.m_thisRow2X;
		p_unk0x0c->m_y = scratch.m_thisRow2Y;
		p_unk0x0c->m_z = scratch.m_thisRow2Z;
		break;
	case 4:
		p_unk0x0c->m_x = scratch.m_otherRow1X;
		p_unk0x0c->m_y = scratch.m_otherRow1Y;
		p_unk0x0c->m_z = scratch.m_otherRow1Z;
		break;
	case 5:
		p_unk0x0c->m_x = scratch.m_otherRow2X;
		p_unk0x0c->m_y = scratch.m_otherRow2Y;
		p_unk0x0c->m_z = scratch.m_otherRow2Z;
		break;
	case 6:
		p_unk0x0c->m_x = scratch.m_otherRow0Z * scratch.m_thisRow0Y - scratch.m_otherRow0Y * scratch.m_thisRow0Z;
		p_unk0x0c->m_y = scratch.m_thisRow0Z * scratch.m_otherRow0X - scratch.m_otherRow0Z * scratch.m_thisRow0X;
		p_unk0x0c->m_z = scratch.m_otherRow0Y * scratch.m_thisRow0X - scratch.m_thisRow0Y * scratch.m_otherRow0X;
		GolMath::NormalizeVector3(*p_unk0x0c, p_unk0x0c);
		break;
	case 7:
		p_unk0x0c->m_x = scratch.m_otherRow1Z * scratch.m_thisRow0Y - scratch.m_otherRow1Y * scratch.m_thisRow0Z;
		p_unk0x0c->m_y = scratch.m_thisRow0Z * scratch.m_otherRow1X - scratch.m_otherRow1Z * scratch.m_thisRow0X;
		p_unk0x0c->m_z = scratch.m_otherRow1Y * scratch.m_thisRow0X - scratch.m_thisRow0Y * scratch.m_otherRow1X;
		GolMath::NormalizeVector3(*p_unk0x0c, p_unk0x0c);
		break;
	case 8:
		p_unk0x0c->m_x = scratch.m_otherRow2Z * scratch.m_thisRow0Y - scratch.m_otherRow2Y * scratch.m_thisRow0Z;
		p_unk0x0c->m_y = scratch.m_thisRow0Z * scratch.m_otherRow2X - scratch.m_otherRow2Z * scratch.m_thisRow0X;
		p_unk0x0c->m_z = scratch.m_otherRow2Y * scratch.m_thisRow0X - scratch.m_thisRow0Y * scratch.m_otherRow2X;
		GolMath::NormalizeVector3(*p_unk0x0c, p_unk0x0c);
		break;
	case 9:
		p_unk0x0c->m_x = scratch.m_otherRow0Z * scratch.m_thisRow1Y - scratch.m_otherRow0Y * scratch.m_thisRow1Z;
		p_unk0x0c->m_y = scratch.m_thisRow1Z * scratch.m_otherRow0X - scratch.m_otherRow0Z * scratch.m_thisRow1X;
		p_unk0x0c->m_z = scratch.m_otherRow0Y * scratch.m_thisRow1X - scratch.m_thisRow1Y * scratch.m_otherRow0X;
		GolMath::NormalizeVector3(*p_unk0x0c, p_unk0x0c);
		break;
	case 10:
		p_unk0x0c->m_x = scratch.m_otherRow1Z * scratch.m_thisRow1Y - scratch.m_otherRow1Y * scratch.m_thisRow1Z;
		p_unk0x0c->m_y = scratch.m_thisRow1Z * scratch.m_otherRow1X - scratch.m_otherRow1Z * scratch.m_thisRow1X;
		p_unk0x0c->m_z = scratch.m_otherRow1Y * scratch.m_thisRow1X - scratch.m_thisRow1Y * scratch.m_otherRow1X;
		GolMath::NormalizeVector3(*p_unk0x0c, p_unk0x0c);
		break;
	case 11:
		p_unk0x0c->m_x = scratch.m_otherRow2Z * scratch.m_thisRow1Y - scratch.m_otherRow2Y * scratch.m_thisRow1Z;
		p_unk0x0c->m_y = scratch.m_thisRow1Z * scratch.m_otherRow2X - scratch.m_otherRow2Z * scratch.m_thisRow1X;
		p_unk0x0c->m_z = scratch.m_otherRow2Y * scratch.m_thisRow1X - scratch.m_thisRow1Y * scratch.m_otherRow2X;
		GolMath::NormalizeVector3(*p_unk0x0c, p_unk0x0c);
		break;
	case 12:
		p_unk0x0c->m_x = scratch.m_otherRow0Z * scratch.m_thisRow2Y - scratch.m_otherRow0Y * scratch.m_thisRow2Z;
		p_unk0x0c->m_y = scratch.m_thisRow2Z * scratch.m_otherRow0X - scratch.m_otherRow0Z * scratch.m_thisRow2X;
		p_unk0x0c->m_z = scratch.m_otherRow0Y * scratch.m_thisRow2X - scratch.m_thisRow2Y * scratch.m_otherRow0X;
		GolMath::NormalizeVector3(*p_unk0x0c, p_unk0x0c);
		break;
	case 13:
		p_unk0x0c->m_x = scratch.m_otherRow1Z * scratch.m_thisRow2Y - scratch.m_otherRow1Y * scratch.m_thisRow2Z;
		p_unk0x0c->m_y = scratch.m_thisRow2Z * scratch.m_otherRow1X - scratch.m_otherRow1Z * scratch.m_thisRow2X;
		p_unk0x0c->m_z = scratch.m_otherRow1Y * scratch.m_thisRow2X - scratch.m_thisRow2Y * scratch.m_otherRow1X;
		GolMath::NormalizeVector3(*p_unk0x0c, p_unk0x0c);
		break;
	case 14:
		p_unk0x0c->m_x = scratch.m_otherRow2Z * scratch.m_thisRow2Y - scratch.m_otherRow2Y * scratch.m_thisRow2Z;
		p_unk0x0c->m_y = scratch.m_thisRow2Z * scratch.m_otherRow2X - scratch.m_otherRow2Z * scratch.m_thisRow2X;
		p_unk0x0c->m_z = scratch.m_otherRow2Y * scratch.m_thisRow2X - scratch.m_thisRow2Y * scratch.m_otherRow2X;
		GolMath::NormalizeVector3(*p_unk0x0c, p_unk0x0c);
		break;
	default:
		break;
	}

	if ((m_unk0x020.m_y - p_other->m_unk0x020.m_y) * p_unk0x0c->m_y +
			p_unk0x0c->m_z * (m_unk0x020.m_z - p_other->m_unk0x020.m_z) +
			(m_unk0x020.m_x - p_other->m_unk0x020.m_x) * p_unk0x0c->m_x <
		0.0f) {
		p_unk0x0c->m_x = -p_unk0x0c->m_x;
		p_unk0x0c->m_y = -p_unk0x0c->m_y;
		p_unk0x0c->m_z = -p_unk0x0c->m_z;
	}

	return TRUE;
}
