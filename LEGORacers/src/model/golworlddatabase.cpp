#include "world/golworlddatabase.h"

#include "cmbmodelpart.h"
#include "golanimatedentity.h"
#include "golboundedentity.h"
#include "golcamerabase.h"
#include "golcollidableentity.h"
#include "golmodelbase.h"
#include "golmodelentity.h"
#include "golscenenode.h"
#include "golworldentity.h"
#include "mabmaterialanimation.h"

// FUNCTION: LEGORACERS 0x00416040
void GolWorldDatabase::DrawWorld()
{
	if (m_collidableEntityCount) {
		VTable0x1c(m_unk0x04);
	}

	if (m_animatedEntityCount) {
		VTable0x24(m_unk0x04);
	}

	if (m_modelEntityCount) {
		VTable0x20(m_unk0x04);
	}

	if (m_unk0x6c) {
		VTable0x28(m_unk0x04);
	}
}

// FUNCTION: LEGORACERS 0x00416090
void GolWorldDatabase::Update(LegoS32 p_elapsedMs)
{
	LegoU32 i;

	for (i = 0; i < m_unk0x74; i++) {
		VTable0x4c(i)->FUN_00410300(p_elapsedMs);
	}

	for (i = 0; i < m_modelEntityCount; i++) {
		m_modelEntities[i].VTable0x10(p_elapsedMs);
	}

	for (i = 0; i < m_animatedEntityCount; i++) {
		m_animatedEntities[i].VTable0x10(p_elapsedMs);
	}

	for (i = 0; i < m_unk0x7c; i++) {
		VTable0x50(i)->UpdateFromTrackedEntity();
	}
}

// FUNCTION: LEGORACERS 0x00416140
void GolWorldDatabase::ResetEntities()
{
	LegoU32 i;

	for (i = 0; i < m_modelEntityCount; i++) {
		m_modelEntities[i].FUN_00411040();
	}

	for (i = 0; i < m_animatedEntityCount; i++) {
		m_animatedEntities[i].FUN_00411040();
	}

	for (i = 0; i < m_collidableEntityCount; i++) {
		m_collidableEntities[i].FUN_00403c60();
	}

	for (i = 0; i < m_boundedEntityCount; i++) {
		m_boundedEntities[i].FUN_00403f80();
	}

	for (i = 0; i < m_unk0x24; i++) {
		VTable0x38(i)->FUN_00411090();
	}

	for (i = 0; i < m_unk0x6c; i++) {
		GolWorldEntity* entity = VTable0x48(i);
		GolVec3 center;
		entity->FUN_100286d0(&center);
		center.m_y = -center.m_y;
		entity->VTable0x08(center);
	}

	for (i = 0; i < m_unk0x1c; i++) {
		VTable0x34(i)->FUN_004015e0();
	}

	for (i = 0; i < m_unk0x34; i++) {
		VTable0x40(i)->FUN_00413310();
	}
}

// FUNCTION: LEGORACERS 0x00416290
LegoU32 GolWorldDatabase::SetWorldScale(LegoFloat p_scale)
{
	LegoU32 i = 0;
	LegoU32 result = m_unk0x7c;
	if (result > 0) {
		do {
			VTable0x50(i)->SetAspectRatio(p_scale);
			result = m_unk0x7c;
			i++;
		} while (i < result);
	}

	return result;
}
