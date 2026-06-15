#include "race/racestate.h"

// FUNCTION: LEGORACERS 0x004202c0
undefined4 RaceState::Racer::Field0xc70::FUN_004202c0()
{
	LegoU32 flags = m_unk0x014;
	flags &= ~4;
	m_unk0x014 = flags;
	m_unk0x000->FUN_00448070();

	flags = m_unk0x014;
	flags &= ~8;
	m_unk0x02c = 0;
	m_unk0x014 = flags;
	return m_unk0x000->FUN_00449090();
}

// FUNCTION: LEGORACERS 0x004202f0
GolVec4* RaceState::Racer::Field0xc70::FUN_004202f0(undefined4 p_unk0x04)
{
	LegoU32 flags = m_unk0x014;
	m_unk0x024 = 1000;
	flags |= 0x40;
	m_unk0x004 = p_unk0x04;
	m_unk0x014 = flags;
	FUN_004202c0();

	undefined4 value = m_unk0x004;
	m_unk0x00c = 0;
	m_unk0x050->FUN_004a5220(value);

	m_unk0x050->m_unk0x2c = 1.0f;
	m_unk0x050->FUN_004a5320(static_cast<LegoFloat>(m_unk0x024));

	Field0x050* field0x50 = m_unk0x050;
	m_unk0x034 = field0x50->m_unk0x00;
	GolVec4* result = &field0x50->m_unk0x0c;
	GolVec4* basis = &m_unk0x040;
	basis->m_x = result->m_x;
	basis->m_y = result->m_y;
	basis->m_z = result->m_z;
	basis->m_u = result->m_u;
	return result;
}
