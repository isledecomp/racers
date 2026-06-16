#include "race/racestate.h"

DECOMP_SIZE_ASSERT(RaceState::Field0x2a0, 0x78)

// FUNCTION: LEGORACERS 0x004a5170
RaceState::Field0x2a0::Field0x2a0()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a5180
RaceState::Field0x2a0::~Field0x2a0()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004a5190
void RaceState::Field0x2a0::Reset()
{
	m_unk0x00.m_x = 0.0f;
	m_unk0x00.m_y = 0.0f;
	m_unk0x00.m_z = 0.0f;
	m_unk0x0c.m_x = 0.0f;
	m_unk0x0c.m_y = 0.0f;
	m_unk0x0c.m_z = 0.0f;
	m_unk0x0c.m_u = 1.0f;
	m_unk0x1c = 0;
	m_unk0x28 = NULL;
	m_unk0x2c = 1.0f;
	m_unk0x30 = 0;
	m_unk0x34 = 0xffffffff;
	m_unk0x38 = 0;
	m_unk0x3c.m_x = 0.0f;
	m_unk0x3c.m_y = 0.0f;
	m_unk0x3c.m_z = 0.0f;
	m_unk0x48.m_x = 0.0f;
	m_unk0x48.m_y = 0.0f;
	m_unk0x48.m_z = 0.0f;
	m_unk0x54.m_x = 0.0f;
	m_unk0x54.m_y = 0.0f;
	m_unk0x54.m_z = 0.0f;
	m_unk0x54.m_u = 1.0f;
	m_unk0x64 = 0.0f;
	m_unk0x68 = 0;
	m_unk0x6c = 0;
	m_unk0x70 = 1.0f;
	m_unk0x74 = 0;
}

// FUNCTION: LEGORACERS 0x004a51f0
void RaceState::Field0x2a0::Destroy()
{
	Reset();
}

// STUB: LEGORACERS 0x004a5220
void RaceState::Racer::Field0xc70::Field0x050::FUN_004a5220(Field0x00c::Entry*)
{
	STUB(0x004a5220);
}

// STUB: LEGORACERS 0x004a5320
void RaceState::Racer::Field0xc70::Field0x050::FUN_004a5320(LegoFloat)
{
	STUB(0x004a5320);
}
