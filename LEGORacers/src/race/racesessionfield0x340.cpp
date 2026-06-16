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

// FUNCTION: LEGORACERS 0x00421e30
void RaceSession::Field0x340::FUN_00421e30(LegoU32 p_elapsedMs, LegoFloat p_unk0x08)
{
	FUN_004222b0(p_unk0x08);
	if (m_unk0x00 && m_unk0x18) {
		if (m_unk0x1c) {
			FUN_00421f80(p_unk0x08);
		}

		if (p_elapsedMs >= m_unk0x04) {
			m_unk0x04 = 0;
			FUN_00421ef0();
			return;
		}

		m_unk0x04 -= p_elapsedMs;

		if (p_elapsedMs > m_unk0x08) {
			m_unk0x08 = 0;
		}
		else {
			m_unk0x08 -= p_elapsedMs;
		}

		if (!m_unk0x08) {
			if (m_unk0x18 == 2 && m_unk0x0c) {
				m_unk0x00->VTable0x5c();
				m_unk0x18 = 1;
				m_unk0x08 = m_unk0x0c;
			}
			else {
				m_unk0x00->VTable0x60();
				m_unk0x18 = 2;
				m_unk0x08 = m_unk0x10;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00421ef0
void RaceSession::Field0x340::FUN_00421ef0()
{
	if (m_unk0x00 && m_unk0x18) {
		m_unk0x00->VTable0x60();

		LegoFloat value = m_unk0x14;
		m_unk0x04 = 0;
		m_unk0x08 = 0;
		m_unk0x0c = 0;
		m_unk0x10 = 0;
		m_unk0x18 = 0;

		if (value != 0.0f) {
			FUN_00421f40();
		}
	}
}

// FUNCTION: LEGORACERS 0x00421f40
LegoS32 RaceSession::Field0x340::FUN_00421f40()
{
	LegoFloat value = m_unk0x14 * 20.0f;
	m_unk0x1c = 1;
	m_unk0x04 = 0xffffffff;
	LegoS32 result = static_cast<LegoS32>(value);
	m_unk0x0c = result;
	m_unk0x10 = 50;
	m_unk0x08 = 0;
	m_unk0x18 = 2;
	return result;
}

// FUNCTION: LEGORACERS 0x00421f80
LegoS32 RaceSession::Field0x340::FUN_00421f80(LegoFloat p_unk0x04)
{
	if (p_unk0x04 < 0.0f) {
		p_unk0x04 = -p_unk0x04;
	}

	if (p_unk0x04 > 0.2f) {
		p_unk0x04 = 0.2f;
	}

	LegoFloat value = (p_unk0x04 / 0.2f) * (p_unk0x04 / 0.2f);
	if (value < 0.02f) {
		value = 0.0f;
	}

	value *= 20.0f;
	LegoS32 result = static_cast<LegoS32>(value * m_unk0x14);
	m_unk0x0c = result;
	return result;
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

// FUNCTION: LEGORACERS 0x004222b0
undefined4 RaceSession::Field0x340::FUN_004222b0(LegoFloat p_unk0x04)
{
	undefined4 result = (undefined4) m_unk0x00;
	if (!m_unk0x00) {
		return result;
	}

	Field0x24* field0x24 = m_unk0x24;
	if (!field0x24) {
		return result;
	}

	if (!m_unk0x20) {
		return result;
	}

	if (p_unk0x04 < 0.0f) {
		p_unk0x04 = -p_unk0x04;
	}

	if (p_unk0x04 > 0.2f) {
		p_unk0x04 = 0.2f;
	}

	undefined4 data[4];
	data[0] = 2000;
	data[1] = 0;
	data[2] = 0;
	data[3] = static_cast<LegoS32>((0.2f - p_unk0x04) * 1000000.0f);

	undefined4 params[13];
	params[0] = 52;
	params[11] = 16;
	params[12] = (undefined4) data;
	result = field0x24->VTable0x18(params, 256);
	return result;
}
