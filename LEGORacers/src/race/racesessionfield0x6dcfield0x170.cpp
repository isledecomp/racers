#include "core/gol.h"
#include "decomp.h"
#include "race/racesession.h"

#include <string.h>

DECOMP_SIZE_ASSERT(RaceSession::Field0x6dc::Field0x170, 0x170)

// FUNCTION: LEGORACERS 0x00493b80
void RaceSession::Field0x6dc::Field0x170::Reset()
{
	m_unk0x000 = NULL;
	m_unk0x004 = NULL;
	m_unk0x008 = 0;
	m_unk0x00c = 0;
	m_unk0x010 = NULL;
	m_unk0x014 = 0;
	m_unk0x0b0 = 0;
	m_unk0x0b4 = 0;
	m_unk0x0b8 = 0;
	m_unk0x0bc = 0;
	m_unk0x0c0 = 0;
	m_unk0x0c4 = 0;
	m_unk0x0c8 = 0;
	m_unk0x0cc = 0;
	m_unk0x0d0 = 0;
	m_unk0x0d4 = 0;
	m_unk0x0dc = 0;
	m_unk0x0e0 = 0;
	m_unk0x0e4 = 0;
	m_unk0x0e8 = 0;
	::memset(m_unk0x0ec, 0, sizeof(m_unk0x0ec));
	::memset(m_unk0x128, 0, sizeof(m_unk0x128));
	m_unk0x13c = 0;
	m_unk0x140 = 0;
	m_unk0x144 = 0;
	m_unk0x148 = 0;
	m_unk0x14c = 0;
	m_unk0x150 = 0;
	m_unk0x160 = 0;
	m_unk0x161 = 0;
	m_unk0x162 = 0;
	m_unk0x164 = 0;
	m_unk0x165 = 0;
	m_unk0x166 = 0;
	m_unk0x168 = 0;
	m_unk0x169 = 0;
	m_unk0x16a = 0;
	m_unk0x16c = 0;
	m_unk0x163 = 0xff;
	m_unk0x167 = 0xff;
	m_unk0x16b = 0xff;
}

// FUNCTION: LEGORACERS 0x00493e60
void RaceSession::Field0x6dc::Field0x170::FUN_00493e60()
{
	m_unk0x018.VTable0x54();

	if (m_unk0x000 != NULL) {
		if (m_unk0x010 != NULL) {
			m_unk0x000->VTable0x4c(m_unk0x010);
		}

		if (m_unk0x004 != NULL) {
			m_unk0x000->VTable0x48(m_unk0x004);
		}
	}

	Reset();
}
