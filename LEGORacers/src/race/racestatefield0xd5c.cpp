#include "race/racestate.h"

DECOMP_SIZE_ASSERT(RaceState::Racer::Field0xd5c::Field0x08, 0x04)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0xd5c, 0x68)

// FUNCTION: LEGORACERS 0x00453790
LegoU8 RaceState::Racer::Field0xd5c::FUN_00453790(GolVec3 p_unk0x04)
{
	GolVec3 position;

	position.m_x = p_unk0x04.m_x;
	position.m_y = p_unk0x04.m_y;
	position.m_z = p_unk0x04.m_z;

	FUN_00453840(&position);
	m_unk0x08.VTable0x08(&position);

	LegoU8 flags = m_unk0x64;
	m_unk0x3c = 2;
	LegoU8 result = flags | 1;
	m_unk0x4c = 0;
	m_unk0x64 = result;
	return result;
}

// FUNCTION: LEGORACERS 0x004537f0
LegoU8 RaceState::Racer::Field0xd5c::FUN_004537f0()
{
	LegoU32 state = m_unk0x3c;
	LegoU8 flags = m_unk0x64;
	flags &= 0xfe;
	m_unk0x60 = 0;
	m_unk0x64 = flags;

	LegoU8 result;
	result = flags;
	if (!state) {
		result |= 2;
		m_unk0x3c = 3;
		m_unk0x64 = result;
		m_unk0x4c = 0;
		return result;
	}

	result = m_unk0x08.VTable0x08(&m_unk0x54);
	m_unk0x3c = 2;
	m_unk0x4c = 0;
	return result;
}

// STUB: LEGORACERS 0x00453840
LegoS32 RaceState::Racer::Field0xd5c::FUN_00453840(GolVec3*)
{
	STUB(0x00453840);
	return 0;
}
