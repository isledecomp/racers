#ifndef INPUTBINDINGSTATE_H
#define INPUTBINDINGSTATE_H

#include "types.h"

// SIZE 0xd0
struct InputBindingState {
	// SIZE 0x28
	struct Entry {
		LegoU8 m_deviceType;    // 0x00
		LegoU8 m_deviceSubType; // 0x01
		LegoU8 m_deviceId;      // 0x02
		LegoU8 m_unk0x03;       // 0x03
		LegoU32 m_events[9];    // 0x04
	};

	// SIZE 0x04
	struct PlayerState {
		LegoU8 m_selectedRecordId;     // 0x00
		LegoU8 m_selectedRecordSource; // 0x01
		LegoU8 m_selectedSaveIndex;    // 0x02
		LegoU8 m_selectedEntryIndex;   // 0x03
	};

	PlayerState m_players[2]; // 0x00
	Entry m_entries[5];       // 0x08

	LegoU8 GetSelectedEntryIndex(LegoU32 p_playerIndex) const { return m_players[p_playerIndex].m_selectedEntryIndex; }

	void SetSelectedEntryIndex(LegoU32 p_playerIndex, LegoU8 p_entryIndex)
	{
		m_players[p_playerIndex].m_selectedEntryIndex = p_entryIndex;
	}
};

#endif // INPUTBINDINGSTATE_H
