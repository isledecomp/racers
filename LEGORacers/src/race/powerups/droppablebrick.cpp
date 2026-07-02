#include "race/racesession.h"

DECOMP_SIZE_ASSERT(RaceState::Racer::DroppableBrick, 0x68)

// GLOBAL: LEGORACERS 0x004b1480
extern const LegoFloat g_unk0x004b1480 = 5.0f;

// GLOBAL: LEGORACERS 0x004b1488
extern const LegoFloat g_unk0x004b1488 = 25.0f;

// FUNCTION: LEGORACERS 0x00453790
LegoU8 RaceState::Racer::DroppableBrick::DropAt(GolVec3 p_unk0x04)
{
	GolVec3 position;

	position.m_x = p_unk0x04.m_x;
	position.m_y = p_unk0x04.m_y;
	position.m_z = p_unk0x04.m_z;

	SnapToGround(&position);
	m_worldEntity.VTable0x08(position);

	LegoU8 flags = m_flags0x64;
	m_state = 2;
	LegoU8 result = flags | 1;
	m_stateTimerMs = 0;
	m_flags0x64 = result;
	return result;
}

// FUNCTION: LEGORACERS 0x004537f0
void RaceState::Racer::DroppableBrick::ReturnHome()
{
	LegoU32 state = m_state;
	LegoU8 flags = m_flags0x64;
	flags &= 0xfe;
	m_droppedTimeMs = 0;
	m_flags0x64 = flags;

	if (!state) {
		flags |= 2;
		m_state = 3;
		m_flags0x64 = flags;
		m_stateTimerMs = 0;
		return;
	}

	m_worldEntity.VTable0x08(m_homePosition);
	m_state = 2;
	m_stateTimerMs = 0;
}

// FUNCTION: LEGORACERS 0x00453840
LegoS32 RaceState::Racer::DroppableBrick::SnapToGround(GolVec3* p_unk0x04)
{
	GolVec3 start;
	GolVec3 end;
	GolBoundingVolume::Field0x0c record;

	start.m_x = p_unk0x04->m_x;
	start.m_y = p_unk0x04->m_y;
	start.m_z = p_unk0x04->m_z + g_unk0x004b1488;

	end.m_x = p_unk0x04->m_x;
	end.m_y = p_unk0x04->m_y;
	end.m_z = p_unk0x04->m_z - g_unk0x004b1488;

	LegoS32 result = m_manager->m_collisionWorld->FUN_0041f4d0(&start, &end, &record, p_unk0x04, NULL);
	p_unk0x04->m_z = p_unk0x04->m_z + g_unk0x004b1480;
	return result;
}
