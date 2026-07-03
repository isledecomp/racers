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
	p_entity->PlayPart(0);
	p_entity->GetBoundsRadius();
	AddEntity(p_entity);
}

// FUNCTION: LEGORACERS 0x00479510
LegoBool32 AwardCinematicScreen::SceneEntityGroup::Create(CreateParams* p_createParams)
{
	Destroy();

	::memcpy(&m_chassisModels, p_createParams, sizeof(*p_createParams));
	Allocate(4);

	if (m_carEntity == NULL) {
		m_carEntity = p_createParams->m_buildModel->GetModelEntity();
	}
	AddEntity(m_carEntity);

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
		GolWorldEntityGroup::Destroy();
	}

	return m_entities == NULL;
}

// FUNCTION: LEGORACERS 0x004795b0
void AwardCinematicScreen::SceneEntityGroup::SetPosition(const GolVec3& p_center)
{
	GolWorldEntityGroup::SetPosition(p_center);

	if (m_driverEntity) {
		for (LegoU32 i = 0; i < static_cast<LegoU32>(m_count); i++) {
			if (m_driverEntity == m_entities[i]) {
				ChassisModelTable::Item* item =
					static_cast<ChassisModelTable::Item*>(m_chassisModels->GetName(m_chassisName));
				GolVec3 center;
				m_carEntity->LocalToWorld(item->m_driverMountOffset, &center);
				m_driverEntity->SetPosition(center);
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00479620
void AwardCinematicScreen::SceneEntityGroup::SetDirectionUp(const GolVec3& p_direction, const GolVec3& p_up)
{
	GolWorldEntityGroup::SetDirectionUp(p_direction, p_up);

	if (m_driverEntity) {
		for (LegoU32 i = 0; i < static_cast<LegoU32>(m_count); i++) {
			if (m_driverEntity == m_entities[i]) {
				GolNameTable* nameTable = m_chassisModels;
				const LegoChar* name = m_chassisName;
				ChassisModelTable::Item* item = static_cast<ChassisModelTable::Item*>(nameTable->GetName(name));
				GolVec3 center;
				m_carEntity->LocalToWorld(item->m_driverMountOffset, &center);
				m_driverEntity->SetPosition(center);
			}
		}
	}
}
