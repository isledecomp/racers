#include "race/racesession.h"

#include <stdlib.h>

DECOMP_SIZE_ASSERT(RaceSession::Field0x32c4, 0x3c)

// FUNCTION: LEGORACERS 0x0045e350
RaceSession::Field0x32c4::Field0x32c4()
{
	for (LegoS32 i = 0; i < sizeOfArray(m_unk0x04); i++) {
		m_unk0x04[i] = 0;
		m_unk0x20[i] = NULL;
	}

	m_unk0x38 = 0;
	m_unk0x1c = 0;
}

// FUNCTION: LEGORACERS 0x0045e3a0
RaceSession::Field0x32c4::~Field0x32c4()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0045e3b0
void RaceSession::Field0x32c4::Destroy()
{
	for (LegoS32 i = 0; i < sizeOfArray(m_unk0x04); i++) {
		m_unk0x04[i] = 0;

		if (m_unk0x20[i]) {
			delete[] m_unk0x20[i];
			m_unk0x20[i] = NULL;
		}
	}

	m_unk0x38 = 0;
	m_unk0x1c = 0;
}

// STUB: LEGORACERS 0x0045e470
void RaceSession::Field0x32c4::FUN_0045e470(LegoU32)
{
	STUB(0x0045e470);
}
