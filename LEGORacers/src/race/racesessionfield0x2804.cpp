#include "race/racesession.h"

DECOMP_SIZE_ASSERT(RaceSession::Field0x2804::Entry, 0x14)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2804, 0x08)

// FUNCTION: LEGORACERS 0x0045c340
RaceSession::Field0x2804::Entry::Entry()
{
	m_unk0x00.m_x = 0.0f;
	m_unk0x00.m_y = 0.0f;
	m_unk0x00.m_z = 0.0f;
	m_unk0x0c = -1;
	m_flags0x10 = 0;
}

// FUNCTION: LEGORACERS 0x0045c360
RaceSession::Field0x2804::Entry::~Entry()
{
	m_unk0x0c = -1;
	m_unk0x00.m_x = 0.0f;
	m_unk0x00.m_y = 0.0f;
	m_unk0x00.m_z = 0.0f;
	m_flags0x10 = 0;
}

// FUNCTION: LEGORACERS 0x0045c380
void RaceSession::Field0x2804::Entry::FUN_0045c380(GolVec3* p_unk0x04, LegoS32 p_unk0x08)
{
	m_unk0x00.m_x = p_unk0x04->m_x;
	m_unk0x00.m_y = p_unk0x04->m_y;
	m_unk0x00.m_z = p_unk0x04->m_z;
	m_unk0x0c = p_unk0x08;
	m_flags0x10 |= 3;
}

// FUNCTION: LEGORACERS 0x0045c3b0 FOLDED
RaceSession::Field0x2804::Field0x2804()
{
	m_entries = NULL;
	m_count = 0;
}

// FUNCTION: LEGORACERS 0x0045c3c0
RaceSession::Field0x2804::~Field0x2804()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0045c620
void RaceSession::Field0x2804::Reset()
{
	if (m_entries) {
		delete[] m_entries;
		m_entries = NULL;
	}

	m_count = 0;
}
