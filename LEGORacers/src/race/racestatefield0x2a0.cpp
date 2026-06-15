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
	m_unk0x00 = 0;
	m_unk0x04 = 0;
	m_unk0x08 = 0;
	m_unk0x0c = 0;
	m_unk0x10 = 0;
	m_unk0x14 = 0;
	m_unk0x18 = 1.0f;
	m_unk0x1c = 0;
	m_unk0x28 = 0;
	m_unk0x2c = 1.0f;
	m_unk0x30 = 0;
	m_unk0x34 = 0xffffffff;
	m_unk0x38 = 0;
	m_unk0x3c = 0;
	m_unk0x40 = 0;
	m_unk0x44 = 0;
	m_unk0x48 = 0;
	m_unk0x4c = 0;
	m_unk0x50 = 0;
	m_unk0x54 = 0;
	m_unk0x58 = 0;
	m_unk0x5c = 0;
	m_unk0x60 = 1.0f;
	m_unk0x64 = 0;
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
