#include "race/racestate.h"

// FUNCTION: LEGORACERS 0x00448930
void RaceState::Racer::Field0x3e8::FUN_00448930(LegoS32 p_unk0x04)
{
	LegoU32 count = m_unk0x154;
	LegoU32 index = 0;
	if (count > 0) {
		for (; index < count; index++) {
			if (m_unk0x140[index] == p_unk0x04) {
				LegoU32 nextIndex = index + 1;
				if (nextIndex < count) {
					LegoS32* entry = &m_unk0x140[nextIndex - 1];
					do {
						nextIndex++;
						*entry = entry[1];
						entry++;
					} while (nextIndex < m_unk0x154);
				}

				m_unk0x154--;
				return;
			}
		}
	}
}
