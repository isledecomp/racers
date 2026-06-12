#include "save/savesystem.h"

#include "golerror.h"
#include "golfile.h"
#include "golstream.h"

#include <string.h>

DECOMP_SIZE_ASSERT(SaveSystem, 0x1f4c)
DECOMP_SIZE_ASSERT(SaveSystem::Directory, 0x108)

// GLOBAL: LEGORACERS 0x004bef80
const LegoChar* g_defaultSaveFileName = "default.lrs";

// GLOBAL: LEGORACERS 0x004bef84
const LegoChar* g_quickBuildSaveFileName = "qbuild.lrs";

// FUNCTION: LEGORACERS 0x00443120
SaveSystem::SaveSystem()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00443210
SaveSystem::~SaveSystem()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004432d0
void SaveSystem::Reset()
{
	m_memoryCardSaveCount = 0;
}

// FUNCTION: LEGORACERS 0x004432e0
void SaveSystem::Initialize(InputManager* p_inputManager, LegoBool32 p_createIfMissing)
{
	char path[128];

	m_gameState.Initialize(p_inputManager);
	if (g_searchPaths[0] != NULL) {
		::strcpy(path, g_searchPaths[0]);
		size_t len = strlen(path);
		if ((LegoS32) len > 0 && path[len - 1] != '\\') {
			path[len] = '\\';
			path[len + 1] = '\0';
		}
	}
	else {
		path[0] = '\0';
	}

	::strcat(path, "Save\\");
	m_directory.Initialize(path);
	m_sessionSave.Initialize(5, 1, 0);
	m_gameState.WriteToSaveGame(&m_sessionSave);
	LoadMemoryCardSaves(p_createIfMissing);
	m_defaultSave.Initialize(4, 3, 0);
	LoadSaveFile(g_defaultSaveFileName, &m_defaultSave);
	m_quickBuildSave.Initialize(36, 3, 0);
	LoadSaveFile(g_quickBuildSaveFileName, &m_quickBuildSave);
	m_activeRecord.FUN_0042b2f0(4, 0, 0, 0);
}

// FUNCTION: LEGORACERS 0x00443420
undefined4 SaveSystem::FUN_00443420(LegoU32 p_index, undefined4 p_createIfMissing)
{
	MemoryCardSaveGame* save = &m_memoryCardSaves[p_index];
	undefined4 status = save->FUN_00443910();

	if (status == 0) {
		undefined4 result = save->FUN_00443980();

		if (result == 0 && m_gameState.GetActiveSaveIndex() == -1) {
			m_gameState.FUN_0042eb60(save, p_index);
		}

		return result;
	}
	else if (status == 8) {
		if (p_createIfMissing != 0) {
			undefined4 result = save->FUN_00443940();

			if (m_gameState.GetActiveSaveIndex() == -1) {
				m_gameState.FUN_0042eb60(save, p_index);
			}

			return result;
		}
	}

	return status;
}

// FUNCTION: LEGORACERS 0x004434a0
undefined4 SaveSystem::FUN_004434a0(undefined4 p_index)
{
	if (m_gameState.IsDirty() && m_gameState.GetActiveSaveIndex() == p_index) {
		m_gameState.WriteToSaveGame(&m_memoryCardSaves[p_index]);
		m_gameState.SetDirty(0);
		return m_memoryCardSaves[p_index].FUN_004439b0();
	}

	if (m_memoryCardSaves[p_index].IsDirty()) {
		return m_memoryCardSaves[p_index].FUN_004439b0();
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x00443520
void SaveSystem::LoadMemoryCardSaves(undefined4 p_createIfMissing)
{
	SaveDirectoryBase& root = m_directory;
	m_memoryCardSaveCount = root.GetEntryCount();
	if (m_memoryCardSaveCount > 2) {
		m_memoryCardSaveCount = 2;
	}

	for (LegoU32 i = 0; i < m_memoryCardSaveCount; i++) {
		MemoryCardSaveGame* save = &m_memoryCardSaves[i];
		save->Initialize(root.GetEntry(i), 100, 2, i);
		m_gameState.WriteToSaveGame(save);

		undefined4 status = save->FUN_00443910();
		if (status == 0) {
			save->FUN_00443980();
		}
		else if (status == 8 && p_createIfMissing) {
			save->FUN_00443940();
		}
	}

	LoadFirstOpenSave();
}

// FUNCTION: LEGORACERS 0x004435c0
void SaveSystem::LoadFirstOpenSave()
{
	for (LegoU32 i = 0; i < m_memoryCardSaveCount; i++) {
		if (m_memoryCardSaves[i].HasUnk0x4b4Flag0x01() && m_gameState.GetActiveSaveIndex() == 0xffffffff) {
			m_gameState.FUN_0042eb60(&m_memoryCardSaves[i], i);
			return;
		}
	}
}

// FUNCTION: LEGORACERS 0x00443620
void SaveSystem::LoadSaveFile(const LegoChar* p_fileName, SaveGame* p_saveGame)
{
	GolFile* file = new GolFile;
	if (file == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	if (file->BufferedOpen(p_fileName, GolFile::c_modeRead, 1024)) {
		if (file != NULL) {
			delete file;
		}

		return;
	}

	if (p_saveGame->FUN_00442770(*file)) {
		GOL_FATALERROR_MESSAGE("Corrupt install - invalid default save file");
	}

	file->Dispose();
	if (file != NULL) {
		delete file;
	}
}

// FUNCTION: LEGORACERS 0x004436e0
void SaveSystem::Destroy()
{
	m_activeRecord.Destroy();
	m_sessionSave.Destroy();
	m_defaultSave.Destroy();
	m_quickBuildSave.Destroy();

	for (LegoU32 i = 0; i < m_memoryCardSaveCount; i++) {
		m_memoryCardSaves[i].Destroy();
	}

	SaveDirectoryBase& root = m_directory;
	root.Clear();
	m_gameState.Reset();
	Reset();
}

// FUNCTION: LEGORACERS 0x00443760
LegoU32 SaveSystem::GetMaxUnlockedCircuitIndex()
{
	LegoU8 flags = m_gameState.GetUnlockedCircuits();

	LegoU32 mask = 2;
	for (LegoU32 index = 1; index < 7;) {
		if (!(flags & mask)) {
			return index - 1;
		}

		index++;
		mask <<= 1;
	}

	return 6;
}

// FUNCTION: LEGORACERS 0x004437a0
void SaveSystem::ReinitializeInputBindings(InputManager* p_inputManager)
{
	m_gameState.WriteToSaveGame(&m_sessionSave);
	m_gameState.InitializeInputBindings(p_inputManager);
	m_gameState.FUN_0042eb60(&m_sessionSave, m_gameState.GetActiveSaveIndex());
}
