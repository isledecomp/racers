#ifndef MEMORYCARDSAVEGAME_H
#define MEMORYCARDSAVEGAME_H

#include "save/memorycardfile.h"
#include "save/savedirectory.h"
#include "save/savegame.h"

// SIZE 0x4e0
class MemoryCardSaveGame : public SaveGame {
public:
	MemoryCardSaveGame();
	~MemoryCardSaveGame();

	LegoBool32 IsUsable() const { return !m_slot->HasUnk0x04() && m_file.IsOpen(); }

	void Initialize(SaveSlot* p_slot, undefined4 p_count, undefined4 p_recordSource, undefined4 p_saveIndex);
	void Destroy();
	LegoS32 OpenExistingFile();
	LegoS32 CreateSaveFile();
	LegoS32 LoadFromFile();
	LegoS32 SaveToFile();

private:
	enum {
		c_fileBufferSize = 0x3e00,
	};

	SaveSlot* m_slot;      // 0x4a8
	MemoryCardFile m_file; // 0x4ac
};

#endif // MEMORYCARDSAVEGAME_H
