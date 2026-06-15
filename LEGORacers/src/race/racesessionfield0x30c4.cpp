#include "race/racesession.h"

DECOMP_SIZE_ASSERT(RaceSession::Field0x30c4, 0x2c)

// FUNCTION: LEGORACERS 0x0043a640
RaceSession::Field0x30c4::Field0x30c4()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0043a650
RaceSession::Field0x30c4::~Field0x30c4()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0043a660
void RaceSession::Field0x30c4::Reset()
{
	m_unk0x00[0] = 0;
	m_unk0x00[1] = 0;
	m_unk0x00[2] = 0;
	m_unk0x00[3] = 0;
	m_unk0x00[4] = 0;
	m_unk0x00[5] = 0;
	m_unk0x00[6] = 0;
	m_unk0x00[7] = 0;
	m_unk0x00[8] = 0;
	m_unk0x00[9] = 0;
	m_unk0x00[10] = 0;
}

// STUB: LEGORACERS 0x0043a6e0
void RaceSession::Field0x30c4::FUN_0043a6e0()
{
	STUB(0x0043a6e0);
}
