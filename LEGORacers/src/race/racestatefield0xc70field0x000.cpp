#include "race/racestate.h"

// GLOBAL: LEGORACERS 0x004b0d80
LegoU32 g_unk0x004b0d80 = 0x3e4ccccd;

// FUNCTION: LEGORACERS 0x00448070
void RaceState::Racer::Field0xc70::Field0x000::FUN_00448070()
{
	LegoU32 flags = m_flags0x6c0;
	RaceResourceManager::Resource* resource = m_unk0x6e8;

	flags &= ~(c_flags0x6c0Bit0 | c_flags0x6c0Bit9);
	m_unk0x6c8 = -1.0f;
	m_unk0x6cc = 3.1415927f;
	m_flags0x6c0 = flags;

	if (resource != NULL) {
		m_unk0x158->FUN_00443c10(resource);
		m_unk0x6e8 = NULL;
	}
}

// FUNCTION: LEGORACERS 0x00449090
undefined4 RaceState::Racer::Field0xc70::Field0x000::FUN_00449090()
{
	LegoU32 flags = m_flags0x6c0;
	flags &= ~c_flags0x6c0Bit10;
	m_flags0x6c0 = flags;

	LegoU32 value = g_unk0x004b0d80;
	m_unk0x6d8 = value;
	return value;
}
