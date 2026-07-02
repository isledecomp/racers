#include "menu/screens/awardcinematicscreen.h"
#include "model/carbuildmodel.h"
#include "racer/chassismodeltable.h"

#include <string.h>

DECOMP_SIZE_ASSERT(AwardCinematicScreen::SceneEntityGroup, 0x50)
DECOMP_SIZE_ASSERT(AwardCinematicScreen::SceneEntityGroup::CreateParams, 0x18)

// FUNCTION: LEGORACERS 0x00479440
AwardCinematicScreen::SceneEntityGroup::SceneEntityGroup()
{
}

// FUNCTION: LEGORACERS 0x00479480
AwardCinematicScreen::SceneEntityGroup::~SceneEntityGroup()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004794d0
void AwardCinematicScreen::SceneEntityGroup::AddAnimatedEntity(GolAnimatedEntity* p_entity)
{
	p_entity->SetFlags(p_entity->GetFlags() | 0x10000);
	p_entity->FUN_0040dad0(0);
	p_entity->FUN_10028710();
	FUN_00411ec0(p_entity);
}

// FUNCTION: LEGORACERS 0x00479510
LegoBool32 AwardCinematicScreen::SceneEntityGroup::Create(CreateParams* p_createParams)
{
	Destroy();

	::memcpy(&m_chassisModels, p_createParams, sizeof(*p_createParams));
	FUN_00411e30(4);

	if (m_carEntity == NULL) {
		m_carEntity = p_createParams->m_buildModel->GetModelEntity();
	}
	FUN_00411ec0(m_carEntity);

	AddAnimatedEntity(m_chassisModels->GetPrimaryModel(m_chassisName));
	if (m_driverEntity) {
		AddAnimatedEntity(m_driverEntity);
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00479590
LegoBool32 AwardCinematicScreen::SceneEntityGroup::Destroy()
{
	if (m_entities) {
		FUN_00411e90();
	}

	return m_entities == NULL;
}

// FUNCTION: LEGORACERS 0x004795b0
void AwardCinematicScreen::SceneEntityGroup::VTable0x08(const GolVec3& p_center)
{
	GolWorldEntityGroup0x38::VTable0x08(p_center);

	if (m_driverEntity) {
		for (LegoU32 i = 0; i < static_cast<LegoU32>(m_count); i++) {
			if (m_driverEntity == m_entities[i]) {
				ChassisModelTable::Item* item =
					static_cast<ChassisModelTable::Item*>(m_chassisModels->GetName(m_chassisName));
				GolVec3 center;
				m_carEntity->VTable0x2c(item->m_driverMountOffset, &center);
				m_driverEntity->VTable0x08(center);
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00479620
void AwardCinematicScreen::SceneEntityGroup::VTable0x40(const GolVec3& p_direction, const GolVec3& p_up)
{
	GolWorldEntityGroup0x38::VTable0x40(p_direction, p_up);

	if (m_driverEntity) {
		for (LegoU32 i = 0; i < static_cast<LegoU32>(m_count); i++) {
			if (m_driverEntity == m_entities[i]) {
				GolNameTable* nameTable = m_chassisModels;
				const LegoChar* name = m_chassisName;
				ChassisModelTable::Item* item = static_cast<ChassisModelTable::Item*>(nameTable->GetName(name));
				GolVec3 center;
				m_carEntity->VTable0x2c(item->m_driverMountOffset, &center);
				m_driverEntity->VTable0x08(center);
			}
		}
	}
}
