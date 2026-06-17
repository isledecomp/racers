#include "race/racestate.h"

DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x010, 0x04)

// FUNCTION: LEGORACERS 0x0041e940
RaceState::Racer::Field0xcc4* RaceState::Racer::Field0x010::FUN_0041e940(LegoU32 p_unk0x04)
{
	return &m_entries[p_unk0x04];
}
