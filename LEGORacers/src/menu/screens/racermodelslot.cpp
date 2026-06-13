#include "menu/screens/racermodelslot.h"

#include "golworldentity.h"
#include "render/gold3drenderdevice.h"

#include <string.h>

DECOMP_SIZE_ASSERT(RacerModelSlot, 0xa0)
DECOMP_SIZE_ASSERT(RacerModelSlot::CreateParams, 0x48)

// FUNCTION: LEGORACERS 0x004874b0
RacerModelSlot::RacerModelSlot()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00487520
RacerModelSlot::~RacerModelSlot()
{
	VTable0x08();
}

// STUB: LEGORACERS 0x00487570
void RacerModelSlot::Reset()
{
	STUB(0x00487570);

	::memset(&m_unk0x1c, 0, sizeof(m_unk0x1c));

	GolVec3* vector = &m_unk0x88;
	LegoS32 zero = 0;
	m_unk0x68 = NULL;
	vector->m_x = static_cast<LegoFloat>(zero);
	m_unk0x6c = NULL;
	m_unk0x64 = NULL;
	m_unk0x70.m_y = 0.0f;
	vector->m_y = static_cast<LegoFloat>(zero);
	m_unk0x70.m_x = 0.0f;
	m_unk0x70.m_z = 1.0f;
	m_unk0x84 = 0;
	vector->m_z = static_cast<LegoFloat>(zero);
	m_unk0x80 = 0;
	m_unk0x7c = 0;
	m_unk0x98 = 0;
	m_unk0x94 = 0;
	m_unk0x9c = TRUE;
}

// FUNCTION: LEGORACERS 0x004875d0
LegoBool32 RacerModelSlot::FUN_004875d0(CreateParams* p_createParams)
{
	VTable0x08();
	m_unk0x1c = *p_createParams;
	return MenuSceneElement::FUN_0046b300(p_createParams);
}

// FUNCTION: LEGORACERS 0x00487600
void RacerModelSlot::FUN_00487600(GolWorldEntity* p_entity)
{
	m_unk0x68 = p_entity;
	if (p_entity != NULL) {
		p_entity->VTable0x08(m_unk0x1c.m_unk0x2c);
		p_entity->ClearVelocity();
	}
}

// FUNCTION: LEGORACERS 0x00487630
LegoBool32 RacerModelSlot::FUN_00487630(LegoU32 p_elapsed)
{
	if (m_unk0x64 != NULL) {
		LegoU32 elapsed = p_elapsed;
		if (elapsed > m_unk0x94) {
			elapsed = m_unk0x94;
		}

		m_unk0x64->VTable0x10(elapsed);
		m_unk0x94 -= elapsed;

		if (m_unk0x94 == 0) {
			if (m_unk0x9c) {
				FUN_00487600(m_unk0x64);
			}

			m_unk0x64 = NULL;
		}
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00487690
LegoBool32 RacerModelSlot::FUN_00487690(LegoU32 p_elapsed)
{
	if (m_unk0x6c != NULL) {
		LegoU32 elapsed = p_elapsed;
		if (elapsed > m_unk0x98) {
			elapsed = m_unk0x98;
		}

		m_unk0x6c->VTable0x10(elapsed);
		m_unk0x98 -= elapsed;

		if (m_unk0x98 == 0) {
			if (!m_unk0x9c) {
				FUN_00487600(m_unk0x6c);
			}

			m_unk0x6c = NULL;
		}
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x004876f0
LegoBool32 RacerModelSlot::FUN_004876f0(LegoS32 p_elapsed)
{
	if (m_unk0x68 == NULL) {
		return TRUE;
	}

	if (m_unk0x1c.m_unk0x44) {
		m_unk0x68->VTable0x10(p_elapsed);
	}

	if (m_unk0x1c.m_unk0x40 == 0.0f) {
		return TRUE;
	}

	LegoFloat angle = static_cast<LegoFloat>(p_elapsed) * m_unk0x1c.m_unk0x40;
	GolVec3 right;
	GolVec3 forward;
	m_unk0x68->VTable0x48(&right, &forward);

	GolMath::FUN_004496a0(&right, &forward, &m_unk0x70, angle);
	m_unk0x68->VTable0x40(forward, m_unk0x70);

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00487790
LegoBool32 RacerModelSlot::VTable0x0c()
{
	GolVec3 center;

	if (m_unk0x64 != NULL) {
		m_unk0x64->VTable0x04(&center);
		m_unk0x64->VTable0x08(center);
		m_unk0x64->VTable0x1c(*m_unk0x10);
	}

	if (m_unk0x68 != NULL) {
		m_unk0x68->VTable0x04(&center);
		m_unk0x68->VTable0x08(center);
		m_unk0x68->VTable0x1c(*m_unk0x10);
	}

	if (m_unk0x6c != NULL) {
		m_unk0x6c->VTable0x04(&center);
		m_unk0x6c->VTable0x08(center);
		m_unk0x6c->VTable0x1c(*m_unk0x10);
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00487820
LegoBool32 RacerModelSlot::VTable0x10(LegoU32 p_elapsed)
{
	FUN_00487630(p_elapsed);
	FUN_004876f0(p_elapsed);
	FUN_00487690(p_elapsed);

	return TRUE;
}
