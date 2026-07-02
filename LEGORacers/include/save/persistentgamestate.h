#ifndef PERSISTENTGAMESTATE_H
#define PERSISTENTGAMESTATE_H

#include "save/inputbindingstate.h"
#include "util/displaydriverguid.h"

#include <string.h>

// SIZE 0x42c
struct PersistentGameState {
	void Clear() { ::memset(this, 0, sizeof(*this)); }

	LegoU8 m_racerCount;                               // 0x000
	DisplayDriverGuid::Serialized m_displayDriverGuid; // 0x001
	LegoU8 m_unk0x1d;                                  // 0x011
	LegoU8 m_unk0x1e;                                  // 0x012
	LegoU8 m_musicVolume;                              // 0x013
	LegoU8 m_soundVolume;                              // 0x014
	LegoU8 m_stereo;                                   // 0x015
	LegoU8 m_languageIndex;                            // 0x016
	LegoU8 m_lapCount;                                 // 0x017
	LegoU8 m_partUnlockFlags;                          // 0x018
	LegoU8 m_unlockedCircuits;                         // 0x019
	LegoU16 m_unlockedRaces;                           // 0x01a
	LegoU32 m_bestLapTimes[13];                        // 0x01c
	LegoU32 m_bestRaceTimes[13];                       // 0x050
	LegoU8 m_bestLapHolderNames[13][28];               // 0x084
	LegoU8 m_bestRaceHolderNames[13][28];              // 0x1f0
	InputBindingState m_inputBindings;                 // 0x35c
};

#endif // PERSISTENTGAMESTATE_H
