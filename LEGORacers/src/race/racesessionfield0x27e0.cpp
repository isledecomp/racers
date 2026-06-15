#include "race/racesession.h"

#include <stdlib.h>

DECOMP_SIZE_ASSERT(RaceSession::Field0x27e0, 0x14)

// FUNCTION: LEGORACERS 0x00443fa0
RaceSession::Field0x27e0::Field0x27e0()
{
	m_unk0x0c = 0;
	m_unk0x10 = NULL;
}

// FUNCTION: LEGORACERS 0x00443fe0
RaceSession::Field0x27e0::~Field0x27e0()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x00444210
void RaceSession::Field0x27e0::Clear()
{
	if (m_unk0x10) {
		delete[] m_unk0x10;
		m_unk0x10 = NULL;
	}

	if (m_nameEntries) {
		GolNameTable::Clear();
	}

	m_unk0x0c = 0;
}
