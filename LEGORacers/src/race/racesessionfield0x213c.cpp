#include "decomp.h"
#include "race/racesession.h"

DECOMP_SIZE_ASSERT(RaceSession::Field0x213c, 0x0c)

// FUNCTION: LEGORACERS 0x00464a80
RaceSession::Field0x213c::Field0x213c()
{
	m_unk0x08 = NULL;
	m_unk0x00 = 0;
	m_unk0x04 = 0;
}

// FUNCTION: LEGORACERS 0x00464a90
RaceSession::Field0x213c::~Field0x213c()
{
	Destroy();
}

// STUB: LEGORACERS 0x00464dd0
void RaceSession::Field0x213c::FUN_00464dd0(LegoU32)
{
	STUB(0x00464dd0);
}

// FUNCTION: LEGORACERS 0x00464e10
void RaceSession::Field0x213c::Destroy()
{
	if (m_unk0x08) {
		m_unk0x08->VTable0x04(3);
		m_unk0x08 = NULL;
	}

	m_unk0x00 = 0;
	m_unk0x04 = 0;
}
