#include "golcamerabase.h"
#include "race/racestate.h"

extern const LegoFloat g_maxTurnRadius;

// GLOBAL: LEGORACERS 0x004b0d3c
extern const LegoFloat g_slideBankMaxAngle = 0.78539819f;

// GLOBAL: LEGORACERS 0x004b0d40
extern const LegoS32 g_wheelDiagonalIndices[] = {3, 2, 1, 0};

// GLOBAL: LEGORACERS 0x004b0d50
extern const LegoS32 g_wheelLengthwiseIndices[] = {2, 3, 0, 1};

// GLOBAL: LEGORACERS 0x004b0d60
extern const LegoS32 g_wheelSidewaysIndices[] = {1, 0, 3, 2};

// FUNCTION: LEGORACERS 0x00448840
void RacerCarBody::ComputeSlideBankTarget()
{
	if (m_turnRadius > 0.0f) {
		LegoFloat value = m_turnRadius / g_maxTurnRadius;
		if (value > 1.0f) {
			value = 1.0f;
		}

		m_slideBankTarget = -(1.0f - value) * g_slideBankMaxAngle;
	}
	else if (m_turnRadius < 0.0f) {
		LegoFloat value = -m_turnRadius / g_maxTurnRadius;
		if (value > 1.0f) {
			value = 1.0f;
		}

		m_slideBankTarget = (1.0f - value) * g_slideBankMaxAngle;
	}
	else {
		m_slideBankTarget = 0.0f;
	}
}

// FUNCTION: LEGORACERS 0x004488e0
LegoU32 RacerCarBody::AddCollisionWorld(GolBoundedEntity* p_world)
{
	LegoU32 result = m_collisionWorldCount;
	LegoU32 i = 0;
	for (; i < result; i++) {
		if (m_collisionWorlds[i] == p_world) {
			return result;
		}
	}

	if (result < sizeOfArray(m_collisionWorlds)) {
		m_collisionWorlds[result] = p_world;
		result = m_collisionWorldCount + 1;
		m_collisionWorldCount = result;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00448930
void RacerCarBody::RemoveCollisionWorld(GolBoundedEntity* p_world)
{
	LegoU32 count = m_collisionWorldCount;
	LegoU32 index = 0;
	if (count > 0) {
		for (; index < count; index++) {
			if (m_collisionWorlds[index] == p_world) {
				LegoU32 nextIndex = index + 1;
				if (nextIndex < count) {
					GolBoundedEntity** entry = &m_collisionWorlds[nextIndex - 1];
					do {
						nextIndex++;
						*entry = entry[1];
						entry++;
					} while (nextIndex < m_collisionWorldCount);
				}

				m_collisionWorldCount--;
				return;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00448990
LegoFloat RacerCarBody::GetAverageSupportThreshold()
{
	LegoFloat result = 0.0f;
	WheelProbe* entry = m_wheelProbes;
	while (entry < &m_wheelProbes[sizeOfArray(m_wheelProbes)]) {
		result += entry->m_supportThreshold;
		entry++;
	}

	return result * 0.25f;
}

// FUNCTION: LEGORACERS 0x004489c0
LegoFloat RacerCarBody::GetAverageFriction()
{
	LegoFloat result = 0.0f;
	WheelProbe* entry = m_wheelProbes;
	while (entry < &m_wheelProbes[sizeOfArray(m_wheelProbes)]) {
		result += entry->m_friction;
		entry++;
	}

	return result * 0.25f;
}

// FUNCTION: LEGORACERS 0x00448a50
void RacerCarBody::AgePlaneCache()
{
	CollisionCacheRecord* entry = m_planeCache;
	CollisionCacheRecord* end = &m_planeCache[sizeOfArray(m_planeCache)];
	while (entry < end) {
		entry->m_age++;
		entry++;
	}
}

// FUNCTION: LEGORACERS 0x00448a70
RacerPhysics::CollisionCacheRecord* RacerCarBody::CachePlane(
	GolBoundingVolume::HitTriangle* p_plane,
	RaceEventRecord* p_record
)
{
	CollisionCacheRecord* result;
	LegoU32 count = m_planeCacheCount;
	if (count < sizeOfArray(m_planeCache)) {
		result = &m_planeCache[count];
		m_planeCacheCount = count + 1;
	}
	else {
		CollisionCacheRecord* entry = m_planeCache;
		CollisionCacheRecord* end = &m_planeCache[sizeOfArray(m_planeCache)];
		LegoU32 age = 0;
		result = entry;
		while (entry < end) {
			if (age < entry->m_age) {
				result = entry;
				age = entry->m_age;
			}

			entry++;
		}
	}

	result->m_plane = *p_plane;
	result->m_record = p_record;
	result->m_age = 0;

	return result;
}

// FUNCTION: LEGORACERS 0x00448ae0
LegoBool32 RacerCarBody::TestCachedPlanes(WheelProbe* p_probe)
{
	if (p_probe->m_cachedPlane != NULL) {
		if (TestCachedPlane(p_probe, p_probe->m_cachedPlane)) {
			p_probe->m_cachedPlane->m_age = 0;
			p_probe->m_hitRecord = p_probe->m_cachedPlane->m_record;

			return TRUE;
		}
	}

	CollisionCacheRecord* entry = m_planeCache;
	CollisionCacheRecord* end = &m_planeCache[m_planeCacheCount];
	while (entry < end) {
		if (p_probe->m_cachedPlane != entry && TestCachedPlane(p_probe, entry)) {
			p_probe->m_cachedPlane = entry;
			p_probe->m_hitRecord = entry->m_record;
			entry->m_age = 0;

			return TRUE;
		}

		entry++;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00448b80
LegoBool32 RacerCarBody::TestCachedPlane(WheelProbe* p_probe, CollisionCacheRecord* p_record)
{
	GolVec3 scaled;
	LegoFloat start = p_record->m_plane.m_normal.m_z * p_probe->m_rayStart.m_z;
	start += p_record->m_plane.m_normal.m_y * p_probe->m_rayStart.m_y;
	start += p_probe->m_rayStart.m_x * p_record->m_plane.m_normal.m_x;
	start += p_record->m_plane.m_unk0x30;
	LegoFloat end = p_record->m_plane.m_normal.m_z * p_probe->m_rayEnd.m_z;
	end += p_probe->m_rayEnd.m_y * p_record->m_plane.m_normal.m_y;
	end += p_probe->m_rayEnd.m_x * p_record->m_plane.m_normal.m_x;
	end += p_record->m_plane.m_unk0x30;

	LegoBool32 startNonNegative = start >= 0.0f;
	LegoBool32 endNonNegative = end >= 0.0f;
	if (startNonNegative == endNonNegative) {
		return FALSE;
	}

	if (startNonNegative) {
		end = -end;
	}
	else {
		start = -start;
	}

	GolVec3* point = &p_probe->m_hitPoint;
	point->m_x = p_probe->m_rayEnd.m_x - p_probe->m_rayStart.m_x;
	point->m_y = p_probe->m_rayEnd.m_y - p_probe->m_rayStart.m_y;
	point->m_z = p_probe->m_rayEnd.m_z - p_probe->m_rayStart.m_z;

	LegoFloat amount = start / (start + end);
	scaled.m_x = amount * point->m_x;
	scaled.m_y = point->m_y;
	scaled.m_y *= amount;
	scaled.m_z = amount;
	scaled.m_z *= p_probe->m_hitPoint.m_z;

	point->m_x = scaled.m_x + p_probe->m_rayStart.m_x;
	point->m_y = scaled.m_y + p_probe->m_rayStart.m_y;
	point->m_z = scaled.m_z + p_probe->m_rayStart.m_z;

	return GolMath::FUN_004497f0(point, p_record->m_plane.GetFloatData());
}

// FUNCTION: LEGORACERS 0x00448c70
void RacerCarBody::ComputeWheelPositions()
{
	GolOrientedEntity* entity = &m_physicsEntity;
	WheelProbe* points = m_wheelProbes;
	GolVec3* anchor = &points[1].m_wheelPosition;
	entity->LocalToWorld(m_anchorWheelOffset, anchor);

	GolVec3 lengthOffset;
	entity->GetOrientationRow0(&lengthOffset);
	LegoFloat lengthScale = m_wheelbase;
	LegoFloat lengthY = lengthOffset.m_y;
	lengthOffset.m_x *= lengthScale;
	lengthOffset.m_y = lengthY * lengthScale;
	lengthOffset.m_z *= lengthScale;

	GolVec3 widthOffset;
	entity->GetUnk0x34(&widthOffset);
	LegoFloat widthScale = m_trackWidth;
	LegoFloat widthY = widthOffset.m_y;
	widthOffset.m_x *= widthScale;
	widthOffset.m_y = widthY * widthScale;
	widthOffset.m_z *= widthScale;

	points[0].m_wheelPosition.m_x = anchor->m_x - widthOffset.m_x;
	points[0].m_wheelPosition.m_y = anchor->m_y - widthOffset.m_y;
	points[0].m_wheelPosition.m_z = anchor->m_z - widthOffset.m_z;

	points[3].m_wheelPosition.m_x = anchor->m_x - lengthOffset.m_x;
	points[3].m_wheelPosition.m_y = anchor->m_y - lengthOffset.m_y;
	points[3].m_wheelPosition.m_z = anchor->m_z - lengthOffset.m_z;

	points[2].m_wheelPosition.m_x = points[0].m_wheelPosition.m_x - lengthOffset.m_x;
	points[2].m_wheelPosition.m_y = points[0].m_wheelPosition.m_y - lengthOffset.m_y;
	points[2].m_wheelPosition.m_z = points[0].m_wheelPosition.m_z - lengthOffset.m_z;
}

// STUB: LEGORACERS 0x00448d90
void RacerCarBody::ComputeWheelRaysLocal(GolBoundedEntity* p_world, LegoFloat p_sweepHeight, LegoFloat p_sweepDistance)
{
	const GolMatrix3& resourceOrientation = p_world->GetOrientation();
	GolVec3 zHeight;
	zHeight.m_x = resourceOrientation.m_m[0][2] * p_sweepDistance;
	zHeight.m_y = resourceOrientation.m_m[1][2] * p_sweepDistance;
	zHeight.m_z = resourceOrientation.m_m[2][2] * p_sweepDistance;

	GolVec3 zDistance;
	zDistance.m_x = resourceOrientation.m_m[0][2] * p_sweepHeight;
	zDistance.m_y = resourceOrientation.m_m[1][2] * p_sweepHeight;
	zDistance.m_z = resourceOrientation.m_m[2][2] * p_sweepHeight;

	WheelProbe* entries = m_wheelProbes;

	GolVec3 center;
	p_world->WorldToLocal(entries[1].m_wheelPosition, &center);

	entries[1].m_rayStart.m_x = center.m_x + zHeight.m_x;
	entries[1].m_rayStart.m_y = center.m_y + zHeight.m_y;
	entries[1].m_rayStart.m_z = center.m_z + zHeight.m_z;
	entries[1].m_rayEnd.m_x = center.m_x - zDistance.m_x;
	entries[1].m_rayEnd.m_y = center.m_y - zDistance.m_y;
	entries[1].m_rayEnd.m_z = center.m_z - zDistance.m_z;

	GolVec3 row0;
	row0.m_x = m_physicsEntity.GetOrientation().m_m[0][0];
	row0.m_y = m_physicsEntity.GetOrientation().m_m[0][1];
	row0.m_z = m_physicsEntity.GetOrientation().m_m[0][2];

	GolVec3 row1;
	row1.m_x = m_physicsEntity.GetOrientation().m_m[1][0];
	row1.m_y = m_physicsEntity.GetOrientation().m_m[1][1];
	row1.m_z = m_physicsEntity.GetOrientation().m_m[1][2];

	GolVec3 localRow0;
	p_world->RotateToLocal(row0, &localRow0);

	GolVec3 localRow1;
	p_world->RotateToLocal(row1, &localRow1);

	localRow0.m_x *= m_wheelbase;
	localRow0.m_y *= m_wheelbase;
	localRow0.m_z *= m_wheelbase;
	localRow1.m_x *= m_trackWidth;
	localRow1.m_y *= m_trackWidth;
	localRow1.m_z *= m_trackWidth;

	GolVec3 corner;
	corner.m_x = center.m_x - localRow1.m_x;
	corner.m_y = center.m_y - localRow1.m_y;
	corner.m_z = center.m_z - localRow1.m_z;

	entries[0].m_rayStart.m_x = corner.m_x + zHeight.m_x;
	entries[0].m_rayStart.m_y = corner.m_y + zHeight.m_y;
	entries[0].m_rayStart.m_z = corner.m_z + zHeight.m_z;
	entries[0].m_rayEnd.m_x = corner.m_x - zDistance.m_x;
	entries[0].m_rayEnd.m_y = corner.m_y - zDistance.m_y;
	entries[0].m_rayEnd.m_z = corner.m_z - zDistance.m_z;

	GolVec3 corner2;
	corner2.m_x = center.m_x - localRow0.m_x;
	corner2.m_y = center.m_y - localRow0.m_y;
	corner2.m_z = center.m_z - localRow0.m_z;

	entries[3].m_rayStart.m_x = corner2.m_x + zHeight.m_x;
	entries[3].m_rayStart.m_y = corner2.m_y + zHeight.m_y;
	entries[3].m_rayStart.m_z = corner2.m_z + zHeight.m_z;
	GolCameraBase::FUN_00404580(&corner2, &zDistance, &entries[3].m_rayEnd);

	GolCameraBase::FUN_00404580(&corner, &localRow0, &corner2);
	GolCameraBase::FUN_00404550(&corner2, &zHeight, &entries[2].m_rayStart);
	GolCameraBase::FUN_00404580(&corner2, &zDistance, &entries[2].m_rayEnd);
}
