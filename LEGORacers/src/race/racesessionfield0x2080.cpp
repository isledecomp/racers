#include "decomp.h"
#include "race/racesession.h"

DECOMP_SIZE_ASSERT(RaceSession::Field0x2080, 0x18)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2080::Entry, 0x58)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2128, 0x14)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2128::Entry, 0x3c)

// FUNCTION: LEGORACERS 0x00463d30
RaceSession::Field0x2080::Field0x2080()
{
	m_unk0x14 = NULL;
}

// FUNCTION: LEGORACERS 0x00463d70
RaceSession::Field0x2080::~Field0x2080()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004640a0
void RaceSession::Field0x2080::Destroy()
{
	if (m_unk0x14) {
		m_unk0x14->VTable0x04(3);
		m_unk0x14 = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004640c0
LegoU32 RaceSession::Field0x2080::VTable0x08(undefined4 p_unk0x04)
{
	LegoU32 i;
	LegoU32 result = m_count;

	for (i = 0; i < result; i++) {
		m_unk0x14[i].VTable0x0c(p_unk0x04);
		result = m_count;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00464100
LegoU32 RaceSession::Field0x2080::VTable0x0c()
{
	LegoU32 i;
	LegoU32 result = m_count;

	for (i = 0; i < result; i++) {
		m_unk0x14[i].VTable0x10();
		result = m_count;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00464fa0
RaceSession::Field0x2128::Field0x2128()
{
	m_entries = NULL;
	m_unk0x04 = 0;
	m_unk0x08 = 0;
	m_count = 0;
}

// FUNCTION: LEGORACERS 0x00464fe0
RaceSession::Field0x2128::~Field0x2128()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004651e0
void RaceSession::Field0x2128::Destroy()
{
	if (m_entries) {
		m_entries->VTable0x04(3);
		m_entries = NULL;
	}

	m_unk0x04 = 0;
	m_unk0x08 = 0;
	m_count = 0;
}

// FUNCTION: LEGORACERS 0x00465450
LegoU32 RaceSession::Field0x2128::VTable0x08(undefined4 p_unk0x04)
{
	LegoU32 i;
	LegoU32 result = m_count;

	for (i = 0; i < result; i++) {
		m_entries[i].VTable0x0c(p_unk0x04);
		result = m_count;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00465490
LegoU32 RaceSession::Field0x2128::VTable0x0c()
{
	LegoU32 i;
	LegoU32 result = m_count;

	for (i = 0; i < result; i++) {
		m_entries[i].VTable0x10();
		result = m_count;
	}

	return result;
}
