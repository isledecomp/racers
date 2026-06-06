#include "menu/screens/racerpickmodelslot0xa0.h"

#include "golworldentity.h"

#include <string.h>

DECOMP_SIZE_ASSERT(RacerPickModelSlot0xa0, 0xa0)
DECOMP_SIZE_ASSERT(RacerPickModelSlot0xa0::CreateParams0x48, 0x48)

// FUNCTION: LEGORACERS 0x004874b0
RacerPickModelSlot0xa0::RacerPickModelSlot0xa0()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00487520
RacerPickModelSlot0xa0::~RacerPickModelSlot0xa0()
{
	VTable0x08();
}

// STUB: LEGORACERS 0x00487570
void RacerPickModelSlot0xa0::Reset()
{
	::memset(&m_unk0x1c, 0, sizeof(m_unk0x1c));

	m_unk0x68 = NULL;
	m_unk0x88.m_x = 0.0f;
	m_unk0x6c = NULL;
	m_unk0x64 = NULL;
	m_unk0x74 = 0;
	m_unk0x88.m_y = 0.0f;
	m_unk0x70 = 0;
	m_unk0x78 = 1.0f;
	m_unk0x84 = 0;
	m_unk0x88.m_z = 0.0f;
	m_unk0x80 = 0;
	m_unk0x7c = 0;
	m_unk0x98 = 0;
	m_unk0x94 = 0;
	m_unk0x9c = TRUE;
}

// FUNCTION: LEGORACERS 0x00487600
void RacerPickModelSlot0xa0::FUN_00487600(GolWorldEntity* p_entity)
{
	m_unk0x68 = p_entity;
	if (p_entity != NULL) {
		p_entity->VTable0x08(m_unk0x1c.m_unk0x2c);
		p_entity->ClearVelocity();
	}
}

// STUB: LEGORACERS 0x00487790
LegoBool32 RacerPickModelSlot0xa0::VTable0x0c()
{
	STUB(0x00487790);
	return TRUE;
}

// STUB: LEGORACERS 0x00487820
LegoBool32 RacerPickModelSlot0xa0::VTable0x10(undefined4)
{
	STUB(0x00487820);
	return TRUE;
}
