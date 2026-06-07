#include "menu/screens/awardcinematicscreen.h"
#include "model/carbuildmodel.h"
#include "racer/aquamarinespirit0x3c.h"

#include <string.h>

DECOMP_SIZE_ASSERT(AwardCinematicScreen::SceneEntityGroup, 0x50)
DECOMP_SIZE_ASSERT(AwardCinematicScreen::SceneEntityGroup::CreateParams, 0x18)
DECOMP_SIZE_ASSERT(AwardCinematicScreen::SceneEntityGroup::LookupEntry, 0xd0)

// FUNCTION: LEGORACERS 0x00479440
AwardCinematicScreen::SceneEntityGroup::SceneEntityGroup()
{
}

// FUNCTION: LEGORACERS 0x00479480
AwardCinematicScreen::SceneEntityGroup::~SceneEntityGroup()
{
	FUN_00479590();
}

// FUNCTION: LEGORACERS 0x004794d0
void AwardCinematicScreen::SceneEntityGroup::FUN_004794d0(OpalHaven0xf4* p_entity)
{
	p_entity->SetFlags(p_entity->GetFlags() | 0x10000);
	p_entity->FUN_0040dad0(0);
	p_entity->FUN_10028710();
	FUN_00411ec0(p_entity);
}

// FUNCTION: LEGORACERS 0x00479510
LegoBool32 AwardCinematicScreen::SceneEntityGroup::FUN_00479510(CreateParams* p_createParams)
{
	FUN_00479590();

	::memcpy(&m_unk0x38, p_createParams, sizeof(*p_createParams));
	FUN_00411e30(4);

	if (m_unk0x40 == NULL) {
		m_unk0x40 = p_createParams->m_unk0x04->GetUnk0x0c();
	}
	FUN_00411ec0(m_unk0x40);

	FUN_004794d0(m_unk0x38->FUN_0041e5b0(m_unk0x48));
	if (m_unk0x44) {
		FUN_004794d0(m_unk0x44);
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00479590
LegoBool32 AwardCinematicScreen::SceneEntityGroup::FUN_00479590()
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

	if (m_unk0x44) {
		for (LegoU32 i = 0; i < static_cast<LegoU32>(m_count); i++) {
			if (m_unk0x44 == m_entities[i]) {
				LookupEntry* lookup = static_cast<LookupEntry*>(m_unk0x38->GetName(m_unk0x48));
				GolVec3 center;
				m_unk0x40->VTable0x2c(lookup->m_unk0xc4, &center);
				m_unk0x44->VTable0x08(center);
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00479620
void AwardCinematicScreen::SceneEntityGroup::VTable0x40(const GolVec3& p_direction, const GolVec3& p_up)
{
	GolWorldEntityGroup0x38::VTable0x40(p_direction, p_up);

	if (m_unk0x44) {
		for (LegoU32 i = 0; i < static_cast<LegoU32>(m_count); i++) {
			if (m_unk0x44 == m_entities[i]) {
				GolNameTable* nameTable = m_unk0x38;
				const LegoChar* name = m_unk0x48;
				LookupEntry* lookup = static_cast<LookupEntry*>(nameTable->GetName(name));
				GolVec3 center;
				m_unk0x40->VTable0x2c(lookup->m_unk0xc4, &center);
				m_unk0x44->VTable0x08(center);
			}
		}
	}
}
