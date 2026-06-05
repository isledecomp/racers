#include "menu/screens/awardcinematicscreen.h"

DECOMP_SIZE_ASSERT(AwardCinematicScreen::FieldAt0x658, 0x50)
DECOMP_SIZE_ASSERT(AwardCinematicScreen::FieldAt0x658::Lookup0xd0, 0xd0)

// FUNCTION: LEGORACERS 0x00479440
AwardCinematicScreen::FieldAt0x658::FieldAt0x658()
{
}

// FUNCTION: LEGORACERS 0x00479480
AwardCinematicScreen::FieldAt0x658::~FieldAt0x658()
{
	FUN_00479590();
}

// FUNCTION: LEGORACERS 0x00479590
LegoBool32 AwardCinematicScreen::FieldAt0x658::FUN_00479590()
{
	if (m_entities) {
		FUN_00411e90();
	}

	return m_entities == NULL;
}

// FUNCTION: LEGORACERS 0x004795b0
void AwardCinematicScreen::FieldAt0x658::VTable0x08(const GolVec3& p_center)
{
	GolWorldEntityGroup0x38::VTable0x08(p_center);

	if (m_unk0x44) {
		for (LegoU32 i = 0; i < static_cast<LegoU32>(m_count); i++) {
			if (m_unk0x44 == m_entities[i]) {
				Lookup0xd0* lookup = static_cast<Lookup0xd0*>(m_unk0x38->GetName(m_unk0x48));
				GolVec3 center;
				m_unk0x40->VTable0x2c(lookup->m_unk0xc4, &center);
				m_unk0x44->VTable0x08(center);
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00479620
void AwardCinematicScreen::FieldAt0x658::VTable0x40(const GolVec3& p_direction, const GolVec3& p_up)
{
	GolWorldEntityGroup0x38::VTable0x40(p_direction, p_up);

	if (m_unk0x44) {
		for (LegoU32 i = 0; i < static_cast<LegoU32>(m_count); i++) {
			if (m_unk0x44 == m_entities[i]) {
				GolNameTable* nameTable = m_unk0x38;
				const LegoChar* name = m_unk0x48;
				Lookup0xd0* lookup = static_cast<Lookup0xd0*>(nameTable->GetName(name));
				GolVec3 center;
				m_unk0x40->VTable0x2c(lookup->m_unk0xc4, &center);
				m_unk0x44->VTable0x08(center);
			}
		}
	}
}
