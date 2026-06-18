#include "decomp.h"
#include "race/racesession.h"

DECOMP_SIZE_ASSERT(RaceSession::Field0x6dc::Field0xf8, 0xf8)

// FUNCTION: LEGORACERS 0x00423590
RaceSession::Field0x6dc::Field0xf8::Field0xf8()
{
	m_unk0x0c4 = 0;
	m_unk0x0c8 = 0;
	m_unk0x0cc = 0;
	m_unk0x0d4 = 0;
	m_unk0x0d8 = 0;
	m_unk0x0a8 = 0;
	m_unk0x0ac = 0;
	m_unk0x0b0 = 0;
	m_unk0x0b4 = 0;
	m_unk0x0b8 = 0;
	m_unk0x0bc = 0;
	m_unk0x0c0 = 0;
	m_unk0x0e8 = 0;
	m_unk0x0ec = 0;
	m_unk0x0f0 = 0;
	m_unk0x0d0 = 1.0f;
}
