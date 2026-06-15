#include "core/gol.h"
#include "race/racesession.h"

#include <stdlib.h>

DECOMP_SIZE_ASSERT(RaceSession::Field0x280c, 0x30)

// FUNCTION: LEGORACERS 0x0042f3b0
RaceSession::Field0x280c::Field0x280c()
{
	m_unk0x00 = 0;
	m_unk0x04 = NULL;
	m_unk0x08 = NULL;
	m_unk0x0c = 0;
	m_unk0x10 = 0;
	m_unk0x14 = 0;
	m_unk0x18 = NULL;
	m_unk0x28 = 0;
	m_unk0x2c = 0;
}

// FUNCTION: LEGORACERS 0x0042f3e0
RaceSession::Field0x280c::~Field0x280c()
{
	FUN_0042f430();
}

// FUNCTION: LEGORACERS 0x0042f430
void RaceSession::Field0x280c::FUN_0042f430()
{
	m_unk0x1c.Reset();
	AwakeKite0x20* field0x08 = m_unk0x08;
	m_unk0x00 = 0;
	m_unk0x28 = 0;

	if (field0x08) {
		m_unk0x04->VTable0x68(field0x08);
		m_unk0x08 = NULL;
	}

	undefined* field0x18 = m_unk0x18;
	m_unk0x04 = NULL;
	m_unk0x0c = 0;
	m_unk0x10 = 0;
	m_unk0x14 = 0;

	if (field0x18) {
		delete[] field0x18;
		m_unk0x18 = NULL;
	}
}
