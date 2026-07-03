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
	GolWorldDatabase* p_unk0x04,
	LegoChar* p_unk0x08,
	RaceEventTable* p_unk0x0c,
	GolNameTable* p_unk0x10
)
{
	m_triggerDatabase = p_unk0x04;

	LegoChar name[8];
	::strncpy(name, p_unk0x08, sizeof(name));

	m_boundsEntity = m_triggerDatabase->FindBoundedEntity(name);

	m_eventTable = p_unk0x0c;
	m_recordNames = p_unk0x10;

	GolWorldDatabase* result = m_triggerDatabase;
	for (LegoU32 count = 0; count < m_triggerDatabase->GetBoundedEntityCount(); count++) {
		GolBoundedEntity* item = &m_triggerDatabase->GetBoundedEntities()[count];
		LegoU32 flags = item->GetUnk0x60();
		flags |= 1;
		item->SetUnk0x60(flags);
		result = m_triggerDatabase;
	}

	return result;
}

// STUB: LEGORACERS 0x0041f4d0
LegoBool32 TriggerWorld::IntersectSegment(
	GolVec3* p_unk0x04,
	GolVec3* p_unk0x08,
	GolBoundingVolume::HitTriangle* p_unk0x0c,
	GolVec3* p_unk0x10,
	RaceEventRecord::Target** p_unk0x14
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

	direction.m_x = p_unk0x08->m_x - p_unk0x04->m_x;
	direction.m_y = p_unk0x08->m_y - p_unk0x04->m_y;
	direction.m_z = p_unk0x08->m_z - p_unk0x04->m_z;
	GolMath::NormalizeVector3(direction, &direction);

	GolBoundingVolume::HitTriangle* record = p_unk0x0c;
	GolWorldDatabase* root = m_triggerDatabase;
	count = 0;
	if (!(0 < root->GetBoundedEntityCount())) {
		goto fallback;
	}

	while (TRUE) {
		entity = &root->GetBoundedEntities()[count];
		if (entity->GetUnk0x60() & 1) {
			entity->FUN_100286d0(&center);

			LegoFloat radius = entity->FUN_10028710();
			LegoFloat x = center.m_x - p_unk0x04->m_x;
			LegoFloat y = center.m_y - p_unk0x04->m_y;
			LegoFloat z = center.m_z - p_unk0x04->m_z;
			LegoFloat dot = z * direction.m_z + y * direction.m_y + x * direction.m_x;
			LegoFloat discriminant = radius * radius - (y * y + z * z + x * x - dot * dot);
			if (discriminant > 0.0f) {
				LegoFloat distance = static_cast<LegoFloat>(dot - sqrt(discriminant));
				if (distance * distance <= 0.0f) {
					entity->VTable0x30(*p_unk0x04, &startLocal);
					entity->VTable0x30(*p_unk0x08, &endLocal);

					query = entity->GetUnk0x58();
					query->SetUnk0x24(entity->GetMaterialTable());
					if (query->FUN_00403fa0(&startLocal, &endLocal, record, &hitLocal, &hitRecord, 0)) {
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
	query = entity->GetUnk0x58();
	query->SetUnk0x24(entity->GetMaterialTable());
	if (!query->FUN_00403fa0(p_unk0x04, p_unk0x08, record, p_unk0x10, &hitRecord, 0)) {
		goto fail;
	}

finish:
	if (p_unk0x14) {
		*p_unk0x14 = hitRecord->m_target;
	}

	return TRUE;

hit:
	entity->VTable0x2c(hitLocal, p_unk0x10);

	planeLocal.m_y = record->m_normal.m_y;
	planeLocal.m_z = record->m_normal.m_z;
	planeLocal.m_x = record->m_normal.m_x;

	entity->VTable0x34(planeLocal, &planeWorld);

	record->m_normal.m_x = planeWorld.m_x;
	record->m_normal.m_y = planeWorld.m_y;
	record->m_normal.m_z = planeWorld.m_z;
	record->m_unk0x30 =
		-(record->m_normal.m_z * p_unk0x10->m_z + record->m_normal.m_y * p_unk0x10->m_y +
		  p_unk0x10->m_x * record->m_normal.m_x);
	goto finish;

fail:
	return FALSE;
}

// FUNCTION: LEGORACERS 0x0041f730
LegoBool32 TriggerWorld::IntersectSegmentAndFireEvents(
	GolVec3* p_unk0x04,
	GolVec3* p_unk0x08,
	GolBoundingVolume::HitTriangle* p_unk0x0c,
	GolVec3* p_unk0x10
)
{
	RaceEventRecord::Target* hit;
	LegoBool32 result = IntersectSegment(p_unk0x04, p_unk0x08, p_unk0x0c, p_unk0x10, &hit);

	if (!result) {
		return result;
	}

	if (hit) {
		if (hit->m_flags & 0x10) {
			m_eventTable->StartEventsAt(hit->m_unk0x18, p_unk0x10);
			m_eventTable->EndEventsAt(hit->m_unk0x18, p_unk0x10);
		}

		if (hit->m_flags & 0x20000) {
			return FALSE;
		}
	}

	return TRUE;
}
