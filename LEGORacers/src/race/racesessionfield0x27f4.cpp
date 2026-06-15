#include "race/racesession.h"

DECOMP_SIZE_ASSERT(RaceSession::Field0x27f4::Entry, 0x24)
DECOMP_SIZE_ASSERT(RaceSession::Field0x27f4, 0x08)

// FUNCTION: LEGORACERS 0x0041e5e0
RaceSession::Field0x27f4::Entry::Entry()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0041e5f0
RaceSession::Field0x27f4::Entry::~Entry()
{
	FUN_0041e630();
}

// FUNCTION: LEGORACERS 0x0041e600
void RaceSession::Field0x27f4::Entry::Reset()
{
	m_unk0x20 = -1;
	m_unk0x00 = 0;
	m_unk0x04 = 0;
	m_unk0x08 = 0;
	m_unk0x0c = 0;
	m_unk0x10 = 0;
	m_unk0x14 = 0;
	m_unk0x18 = 0;
	m_unk0x1c = -1.0f;
}

// FUNCTION: LEGORACERS 0x0041e630
void RaceSession::Field0x27f4::Entry::FUN_0041e630()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0041e720
RaceSession::Field0x27f4::~Field0x27f4()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0041e730
void RaceSession::Field0x27f4::Reset()
{
	if (m_entries) {
		delete[] m_entries;
		m_entries = NULL;
	}

	m_count = 0;
}

// FUNCTION: LEGORACERS 0x0045c3b0 FOLDED
RaceSession::Field0x27f4::Field0x27f4()
{
	m_entries = NULL;
	m_count = 0;
}
