#include "race/racesessionfield0x32b4.h"

#include "race/raceeventtable0x90.h"

#include <math.h>
#include <string.h>

DECOMP_SIZE_ASSERT(RaceSessionField0x32b4::Field0x0c, 0x34)
DECOMP_SIZE_ASSERT(RaceSessionField0x32b4::Field0x10, 0x18)
DECOMP_SIZE_ASSERT(RaceSessionField0x32b4::Field0x058::VertexTable, 0x0c)
DECOMP_SIZE_ASSERT(RaceSessionField0x32b4::Field0x058::Node, 0x14)
DECOMP_SIZE_ASSERT(RaceSessionField0x32b4::Field0x058::Triangle, 0x08)
DECOMP_SIZE_ASSERT(RaceSessionField0x32b4::Field0x058::Field0x18, 0x0c)
DECOMP_SIZE_ASSERT(RaceSessionField0x32b4::Field0x058::TraversalEntry, 0x0c)
DECOMP_SIZE_ASSERT(RaceSessionField0x32b4::Field0x058, 0x64)
DECOMP_SIZE_ASSERT(RaceSessionField0x32b4::Field0x000::Field0x0a8, 0x64)
DECOMP_SIZE_ASSERT(RaceSessionField0x32b4, 0x10)

// FUNCTION: LEGORACERS 0x0041f430
RaceSessionField0x32b4::RaceSessionField0x32b4()
{
	m_unk0x00 = NULL;
	m_unk0x04 = 0;
	m_unk0x08 = 0;
	m_unk0x0c = NULL;
}

// FUNCTION: LEGORACERS 0x0041f440
RaceSessionField0x32b4::Field0x000* RaceSessionField0x32b4::FUN_0041f440(
	Field0x000* p_unk0x04,
	LegoChar* p_unk0x08,
	RaceEventTable0x90* p_unk0x0c,
	undefined4 p_unk0x10
)
{
	m_unk0x00 = p_unk0x04;

	LegoChar name[8];
	::strncpy(name, p_unk0x08, sizeof(name));

	Field0x000::Field0x0a8* entry;
	if (!m_unk0x00->m_unk0x0d8.GetNameEntries()) {
		entry = NULL;
	}
	else {
		entry = static_cast<Field0x000::Field0x0a8*>(m_unk0x00->m_unk0x0d8.GetName(name));
	}
	m_unk0x0c = entry;

	m_unk0x04 = p_unk0x0c;
	m_unk0x08 = p_unk0x10;

	Field0x000* result = m_unk0x00;
	for (LegoU32 count = 0; count < m_unk0x00->m_unk0x064; count++) {
		Field0x000::Field0x0a8* item = &m_unk0x00->m_unk0x0a8[count];
		LegoU32 flags = item->m_unk0x60;
		flags |= 1;
		item->m_unk0x60 = flags;
		result = m_unk0x00;
	}

	return result;
}

// STUB: LEGORACERS 0x0041f4d0
LegoBool32 RaceSessionField0x32b4::FUN_0041f4d0(
	GolVec3* p_unk0x04,
	GolVec3* p_unk0x08,
	Field0x0c* p_unk0x0c,
	GolVec3* p_unk0x10,
	Field0x14** p_unk0x14
)
{
	LegoU32 count;
	Field0x10* hitRecord;
	GolVec3 direction;
	GolVec3 center;
	GolVec3 planeLocal;
	GolVec3 planeWorld;
	GolVec3 endLocal;
	GolVec3 startLocal;
	GolVec3 hitLocal;
	Field0x000::Field0x0a8* entity;
	Field0x058* query;

	direction.m_x = p_unk0x08->m_x - p_unk0x04->m_x;
	direction.m_y = p_unk0x08->m_y - p_unk0x04->m_y;
	direction.m_z = p_unk0x08->m_z - p_unk0x04->m_z;
	GolMath::NormalizeVector3(direction, &direction);

	Field0x0c* record = p_unk0x0c;
	Field0x000* root = m_unk0x00;
	count = 0;
	if (!(0 < root->m_unk0x064)) {
		goto fallback;
	}

	while (TRUE) {
		entity = &root->m_unk0x0a8[count];
		if (entity->m_unk0x60 & 1) {
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

					query = entity->m_unk0x58;
					query->m_unk0x24 = entity->m_unk0x5c ? entity->m_unk0x5c : &query->m_unk0x18;
					if (query->FUN_00403fa0(&startLocal, &endLocal, record, &hitLocal, &hitRecord, 0)) {
						goto hit;
					}
				}
			}
		}

		root = m_unk0x00;
		count++;
		if (count >= root->m_unk0x064) {
			goto fallback;
		}
	}

fallback:
	entity = m_unk0x0c;
	query = entity->m_unk0x58;
	query->m_unk0x24 = entity->m_unk0x5c ? entity->m_unk0x5c : &query->m_unk0x18;
	if (!query->FUN_00403fa0(p_unk0x04, p_unk0x08, record, p_unk0x10, &hitRecord, 0)) {
		goto fail;
	}

finish:
	if (p_unk0x14) {
		*p_unk0x14 = hitRecord->m_unk0x14;
	}

	return TRUE;

hit:
	entity->VTable0x2c(hitLocal, p_unk0x10);

	planeLocal.m_y = record->m_unk0x24.m_y;
	planeLocal.m_z = record->m_unk0x24.m_z;
	planeLocal.m_x = record->m_unk0x24.m_x;

	entity->VTable0x34(planeLocal, &planeWorld);

	record->m_unk0x24.m_x = planeWorld.m_x;
	record->m_unk0x24.m_y = planeWorld.m_y;
	record->m_unk0x24.m_z = planeWorld.m_z;
	record->m_unk0x30 =
		-(record->m_unk0x24.m_z * p_unk0x10->m_z + record->m_unk0x24.m_y * p_unk0x10->m_y +
		  p_unk0x10->m_x * record->m_unk0x24.m_x);
	goto finish;

fail:
	return FALSE;
}

// FUNCTION: LEGORACERS 0x0041f730
LegoBool32 RaceSessionField0x32b4::FUN_0041f730(
	GolVec3* p_unk0x04,
	GolVec3* p_unk0x08,
	Field0x0c* p_unk0x0c,
	GolVec3* p_unk0x10
)
{
	Field0x14* hit;
	LegoBool32 result = FUN_0041f4d0(p_unk0x04, p_unk0x08, p_unk0x0c, p_unk0x10, &hit);

	if (!result) {
		return result;
	}

	if (hit) {
		if (hit->m_unk0x08 & 0x10) {
			m_unk0x04->FUN_00461ef0(hit->m_unk0x18, p_unk0x10);
			m_unk0x04->FUN_00462140(hit->m_unk0x18, p_unk0x10);
		}

		if (hit->m_unk0x08 & 0x20000) {
			return FALSE;
		}
	}

	return TRUE;
}
