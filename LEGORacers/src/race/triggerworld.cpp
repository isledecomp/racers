#include "race/triggerworld.h"

#include "golboundedentity.h"
#include "golnametable.h"
#include "race/raceeventtable.h"
#include "world/golworlddatabase.h"

#include <math.h>
#include <string.h>

DECOMP_SIZE_ASSERT(TriggerWorld, 0x10)

// FUNCTION: LEGORACERS 0x0041f430
TriggerWorld::TriggerWorld()
{
	m_triggerDatabase = NULL;
	m_eventTable = 0;
	m_recordNames = NULL;
	m_boundsEntity = NULL;
}

// FUNCTION: LEGORACERS 0x0041f440
GolWorldDatabase* TriggerWorld::Initialize(
	GolWorldDatabase* p_triggerDatabase,
	LegoChar* p_worldName,
	RaceEventTable* p_eventTable,
	GolNameTable* p_recordNames
)
{
	m_triggerDatabase = p_triggerDatabase;

	LegoChar name[8];
	::strncpy(name, p_worldName, sizeof(name));

	m_boundsEntity = m_triggerDatabase->FindBoundedEntity(name);

	m_eventTable = p_eventTable;
	m_recordNames = p_recordNames;

	GolWorldDatabase* result = m_triggerDatabase;
	for (LegoU32 count = 0; count < m_triggerDatabase->GetBoundedEntityCount(); count++) {
		GolBoundedEntity* item = &m_triggerDatabase->GetBoundedEntities()[count];
		LegoU32 flags = item->GetBoundedFlags();
		flags |= 1;
		item->SetBoundedFlags(flags);
		result = m_triggerDatabase;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0041f4d0
LegoBool32 TriggerWorld::IntersectSegment(
	GolVec3* p_start,
	GolVec3* p_end,
	GolBoundingVolume::HitTriangle* p_hitTriangle,
	GolVec3* p_hitPosition,
	RaceEventRecord::Target** p_hitTarget
)
{
	LegoU32 count;
	RaceEventRecord* hitRecord;
	GolVec3 direction;
	GolVec3 center;
	GolVec3 planeLocal;
	GolVec3 planeWorld;
	GolVec3 endLocal;
	GolVec3 startLocal;
	GolVec3 hitLocal;
	GolBoundedEntity* entity;
	GolBoundingVolume* query;

	direction.m_x = p_end->m_x - p_start->m_x;
	direction.m_y = p_end->m_y - p_start->m_y;
	direction.m_z = p_end->m_z - p_start->m_z;
	GolMath::NormalizeVector3(direction, &direction);

	GolBoundingVolume::HitTriangle* record = p_hitTriangle;
	GolWorldDatabase* root = m_triggerDatabase;
	count = 0;
	if (!(0 < root->GetBoundedEntityCount())) {
		goto fallback;
	}

	while (TRUE) {
		entity = &root->GetBoundedEntities()[count];
		if (entity->GetBoundedFlags() & 1) {
			entity->GetBoundsCenter(&center);

			LegoFloat radius = entity->GetBoundsRadius();
			LegoFloat x = center.m_x - p_start->m_x;
			LegoFloat y = center.m_y - p_start->m_y;
			LegoFloat z = center.m_z - p_start->m_z;
			LegoFloat dot = z * direction.m_z + y * direction.m_y + x * direction.m_x;
			LegoFloat discriminant = radius * radius - (y * y + z * z + x * x - dot * dot);
			if (discriminant > 0.0f) {
				LegoFloat distance = static_cast<LegoFloat>(dot - sqrt(discriminant));
				if (distance * distance <= 0.0f) {
					entity->WorldToLocal(*p_start, &startLocal);
					entity->WorldToLocal(*p_end, &endLocal);

					query = entity->GetBoundingVolume();
					query->SetMaterialTable(entity->GetMaterialTable());
					if (query->IntersectSegment(&startLocal, &endLocal, record, &hitLocal, &hitRecord, 0)) {
						goto hit;
					}
				}
			}
		}

		root = m_triggerDatabase;
		count++;
		if (count >= root->GetBoundedEntityCount()) {
			goto fallback;
		}
	}

fallback:
	entity = m_boundsEntity;
	query = entity->GetBoundingVolume();
	query->SetMaterialTable(entity->GetMaterialTable());
	if (!query->IntersectSegment(p_start, p_end, record, p_hitPosition, &hitRecord, 0)) {
		goto fail;
	}

finish:
	if (p_hitTarget) {
		*p_hitTarget = hitRecord->GetTarget();
	}

	return TRUE;

hit:
	entity->LocalToWorld(hitLocal, p_hitPosition);

	planeLocal.m_y = record->m_normal.m_y;
	planeLocal.m_z = record->m_normal.m_z;
	planeLocal.m_x = record->m_normal.m_x;

	entity->RotateToWorld(planeLocal, &planeWorld);

	record->m_normal.m_x = planeWorld.m_x;
	record->m_normal.m_y = planeWorld.m_y;
	record->m_normal.m_z = planeWorld.m_z;
	record->m_planeDistance =
		-(record->m_normal.m_z * p_hitPosition->m_z + record->m_normal.m_y * p_hitPosition->m_y +
		  p_hitPosition->m_x * record->m_normal.m_x);
	goto finish;

fail:
	return FALSE;
}

// FUNCTION: LEGORACERS 0x0041f730
LegoBool32 TriggerWorld::IntersectSegmentAndFireEvents(
	GolVec3* p_start,
	GolVec3* p_end,
	GolBoundingVolume::HitTriangle* p_hitTriangle,
	GolVec3* p_hitPosition
)
{
	RaceEventRecord::Target* hit;
	LegoBool32 result = IntersectSegment(p_start, p_end, p_hitTriangle, p_hitPosition, &hit);

	if (!result) {
		return result;
	}

	if (hit) {
		if (hit->m_flags & RaceEventRecord::Target::c_flagProjectileEvent) {
			m_eventTable->StartEventsAt(hit->m_projectileEventId, p_hitPosition);
			m_eventTable->EndEventsAt(hit->m_projectileEventId, p_hitPosition);
		}

		if (hit->m_flags & RaceEventRecord::Target::c_flagProjectilePassThrough) {
			return FALSE;
		}
	}

	return TRUE;
}
