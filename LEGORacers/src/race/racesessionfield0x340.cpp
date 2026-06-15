#include "decomp.h"
#include "race/racesession.h"

DECOMP_SIZE_ASSERT(RaceSession::Field0x340, 0x28)

// FUNCTION: LEGORACERS 0x00421da0
RaceSession::Field0x340::Field0x340()
{
	m_unk0x00 = NULL;
	m_unk0x04 = 0;
	m_unk0x08 = 0;
	m_unk0x0c = 0;
	m_unk0x10 = 0;
	m_unk0x14 = 0;
	m_unk0x18 = 0;
	m_unk0x1c = 0;
	m_unk0x20 = 0;
	m_unk0x24 = NULL;
}

// FUNCTION: LEGORACERS 0x00421dd0
RaceSession::Field0x340::~Field0x340()
{
	FUN_00421de0();
}

// FUNCTION: LEGORACERS 0x00421de0
void RaceSession::Field0x340::FUN_00421de0()
{
	Field0x24* field0x24 = m_unk0x24;
	m_unk0x00 = NULL;

	if (field0x24) {
		field0x24->VTable0x20();
		m_unk0x24 = NULL;
	}
}

// STUB: LEGORACERS 0x00421e30
void RaceSession::Field0x340::FUN_00421e30(LegoU32, LegoFloat)
{
	STUB(0x00421e30);
}

// FUNCTION: LEGORACERS 0x00422130
void RaceSession::Field0x340::FUN_00422130()
{
	m_unk0x20 = 1;

	Field0x24* field0x24 = m_unk0x24;
	if (field0x24) {
		field0x24->VTable0x1c(1, 0);
	}
}

// FUNCTION: LEGORACERS 0x00422150
void RaceSession::Field0x340::FUN_00422150()
{
	m_unk0x20 = 0;

	Field0x24* field0x24 = m_unk0x24;
	if (field0x24) {
		field0x24->VTable0x20();
	}
}

// FUNCTION: LEGORACERS 0x00422170
void RaceSession::Field0x340::FUN_00422170()
{
	if (m_unk0x00) {
		m_unk0x00->VTable0x60();

		Field0x24* field0x24 = m_unk0x24;
		if (field0x24) {
			if (m_unk0x20) {
				field0x24->VTable0x20();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004221a0
void RaceSession::Field0x340::FUN_004221a0()
{
	if (m_unk0x00) {
		if (m_unk0x18 == 1) {
			m_unk0x00->VTable0x5c();
		}

		Field0x24* field0x24 = m_unk0x24;
		if (field0x24) {
			if (m_unk0x20) {
				field0x24->VTable0x1c(1, 0);
			}
		}
	}
}
