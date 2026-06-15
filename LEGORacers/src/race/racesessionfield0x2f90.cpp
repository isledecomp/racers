#include "core/gol.h"
#include "race/racesession.h"

DECOMP_SIZE_ASSERT(RaceSession::Field0x2f90, 0xc8)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2f90::Entry, 0x10)

// STUB: LEGORACERS 0x0041c430
RaceSession::Field0x2f90::Field0x2f90()
{
	STUB(0x0041c430);
}

// STUB: LEGORACERS 0x0041c4b0
RaceSession::Field0x2f90::~Field0x2f90()
{
	STUB(0x0041c4b0);
}

// FUNCTION: LEGORACERS 0x0041c500
void RaceSession::Field0x2f90::Reset()
{
	m_entries = NULL;
	m_count = 0;
	m_unk0xb8 = 0;
	m_unk0xb4 = 0;
	m_unk0xbc = 0;
	m_unk0xc0 = 0;
	m_unk0xa0 = NULL;
	m_unk0xa4 = NULL;
	m_unk0xc4 = 0;
	m_unk0x9c = NULL;
	m_unk0xac = 0;
}

// FUNCTION: LEGORACERS 0x0041cbe0
void RaceSession::Field0x2f90::Clear()
{
	if (m_unk0x9c) {
		m_unk0xa4->VTable0x3c(m_unk0x9c);
		m_unk0x9c = NULL;
	}

	if (m_unk0xa0) {
		m_unk0xa4->VTable0x48(m_unk0xa0);
		m_unk0xa0 = NULL;
	}

	m_unk0xa4 = NULL;
	m_unk0x0c.VTable0x54();

	if (m_nameEntries != NULL) {
		GolNameTable::Clear();
	}

	if (m_entries) {
		LegoU32 i;

		for (i = 0; i < m_count; i++) {
			if (m_entries[i].m_unk0x08) {
				delete[] m_entries[i].m_unk0x08;
				m_entries[i].m_unk0x08 = NULL;
			}
		}

		delete[] m_entries;
		m_entries = NULL;
	}

	Reset();
}

// STUB: LEGORACERS 0x0041ccb0
void RaceSession::Field0x2f90::FUN_0041ccb0(LegoU32)
{
	STUB(0x0041ccb0);
}

// STUB: LEGORACERS 0x0041d040
void RaceSession::Field0x2f90::FUN_0041d040(GolVec3*)
{
	STUB(0x0041d040);
}

// STUB: LEGORACERS 0x0041d0f0
void RaceSession::Field0x2f90::FUN_0041d0f0(GolD3DRenderDevice*)
{
	STUB(0x0041d0f0);
}
