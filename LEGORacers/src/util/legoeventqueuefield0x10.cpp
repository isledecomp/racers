#include "util/legoeventqueue.h"

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
	LegoU32 cornerIndex = 0;
	LegoU32 shapeIndex = 0;
	p_unk0x10->m_x = 0.0f;
	p_unk0x10->m_y = 0.0f;
	p_unk0x10->m_z = 0.0f;

	while (TRUE) {
		Field0x10* shape;
		LegoFloat distance;
		GolVec3 axis0;
		GolVec3 axis1;
		GolVec3 axis2;
		if (!shapeIndex) {
			shape = this;
			distance = distance0;

			const GolMatrix3& orientation = m_unk0x004->GetOrientation();
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
			shape = p_other;
			distance = distance1;

			const GolMatrix3& orientation = p_other->m_unk0x004->GetOrientation();
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

			LegoFloat projected =
				p_unk0x0c->m_y * corner.m_y + corner.m_z * p_unk0x0c->m_z + corner.m_x * p_unk0x0c->m_x;
			if (shapeIndex == 1) {
				projected = -projected;
			}

			if (projected >= distance) {
				contactCount++;
				p_unk0x10->m_x = shape->m_unk0x020.m_x + p_unk0x10->m_x + corner.m_x;
				p_unk0x10->m_y = shape->m_unk0x020.m_y + p_unk0x10->m_y + corner.m_y;
				p_unk0x10->m_z = corner.m_z + shape->m_unk0x020.m_z + p_unk0x10->m_z;
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

		cornerIndex = 0;
	}
}

// STUB: LEGORACERS 0x00441790
LegoBool32 LegoEventQueue::Descriptor::Field0x10::FUN_00441790(Field0x10*, LegoFloat*, GolVec3*, LegoFloat*, LegoFloat*)
{
	STUB(0x00441790);
	return FALSE;
}
