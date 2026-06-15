#include "race/racesession.h"

#include <stdlib.h>

DECOMP_SIZE_ASSERT(RaceSession::Field0x3104, 0x48)

// FUNCTION: LEGORACERS 0x004a4e10
RaceSession::Field0x3104::Field0x3104()
{
	FUN_004a50c0();
}

// FUNCTION: LEGORACERS 0x004a4e20
RaceSession::Field0x3104::~Field0x3104()
{
	FUN_004a50a0();
}

// FUNCTION: LEGORACERS 0x004a50a0
void RaceSession::Field0x3104::FUN_004a50a0()
{
	if (m_unk0x04) {
		delete[] m_unk0x04;
	}

	FUN_004a50c0();
}

// FUNCTION: LEGORACERS 0x004a50c0
void RaceSession::Field0x3104::FUN_004a50c0()
{
	m_unk0x00 = 0;
	m_unk0x04 = NULL;
	m_unk0x08 = 0;
	m_unk0x0c = 0;
	m_unk0x10 = 0;
	m_unk0x14 = 0;
	m_unk0x18 = 0;
	m_unk0x1c = 0;
	m_unk0x20 = 1.0f;
	m_unk0x24 = 0;
	m_unk0x28 = 0;
	m_unk0x2c = 0;
	m_unk0x30 = 0;
	m_unk0x34 = 0;
	m_unk0x38 = 0;
	m_unk0x3c = 1.0f;
	m_unk0x40 = 0;
	m_unk0x44 = 0;
}
