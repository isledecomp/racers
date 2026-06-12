#ifndef SAVESYSTEM_H
#define SAVESYSTEM_H

#include "decomp.h"
#include "save/savedirectory.h"
#include "save/savegame.h"
#include "types.h"

class InputManager;

// SIZE 0x1f4c
class SaveSystem {
public:
	// VTABLE: LEGORACERS 0x004b0b94
	// SIZE 0x108
	class Directory : public SaveDirectory {
	public:
		// SYNTHETIC: LEGORACERS 0x004431e0
		// SaveSystem::Directory::~Directory

		// SYNTHETIC: LEGORACERS 0x004431f0
		// SaveSystem::Directory::`scalar deleting destructor'
	};

	SaveSystem();
	~SaveSystem();

	SaveGame& GetSessionSave() { return m_sessionSave; }
	SaveGame& GetDefaultSave() { return m_defaultSave; }
	Directory& GetDirectory() { return m_directory; }
	MemoryCardSaveGame* GetMemoryCardSaves() { return m_memoryCardSaves; }
	SaveGame& GetQuickBuildSave() { return m_quickBuildSave; }
	LegoU32 GetMemoryCardSaveCount() const { return m_memoryCardSaveCount; }
	GameState& GetGameState() { return m_gameState; }
	LegoU8 GetLanguageIndex() const { return m_gameState.GetLanguageIndex(); }
	ActiveRecordBuffer& GetActiveRecord() { return m_activeRecord; }

	void Reset();
	void Initialize(InputManager* p_inputManager, LegoBool32 p_createIfMissing);
	undefined4 FUN_00443420(LegoU32 p_index, undefined4 p_createIfMissing);
	undefined4 FUN_004434a0(undefined4);
	void LoadMemoryCardSaves(undefined4 p_createIfMissing);
	void LoadFirstOpenSave();
	void LoadSaveFile(const LegoChar*, SaveGame*);
	void Destroy();
	LegoU32 GetMaxUnlockedCircuitIndex();
	void ReinitializeInputBindings(InputManager* p_inputManager);

private:
	Directory m_directory;                   // 0x00
	SaveGame m_sessionSave;                  // 0x108
	SaveGame m_defaultSave;                  // 0x5b0
	MemoryCardSaveGame m_memoryCardSaves[2]; // 0xa58
	SaveGame m_quickBuildSave;               // 0x1418
	LegoU32 m_memoryCardSaveCount;           // 0x18c0
	GameState m_gameState;                   // 0x18c4
	ActiveRecordBuffer m_activeRecord;       // 0x1cfc
};

#endif // SAVESYSTEM_H
