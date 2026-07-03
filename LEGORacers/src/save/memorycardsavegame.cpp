#include "save/memorycardsavegame.h"

#include "golstream.h"

DECOMP_SIZE_ASSERT(MemoryCardSaveGame, 0x4e0)

// GLOBAL: LEGORACERS 0x004befd4
const LegoChar* g_memoryCardSaveFileName = "LEGORac1";

// FUNCTION: LEGORACERS 0x004437e0
MemoryCardSaveGame::MemoryCardSaveGame()
{
	m_slot = NULL;
}

// FUNCTION: LEGORACERS 0x00443840
MemoryCardSaveGame::~MemoryCardSaveGame()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004438a0
void MemoryCardSaveGame::Initialize(
	SaveSlot* p_slot,
	undefined4 p_count,
	undefined4 p_recordSource,
	undefined4 p_saveIndex
)
{
	if (HasRecords()) {
		Destroy();
	}

	SaveGame::Initialize(p_count, p_recordSource, p_saveIndex);
	m_slot = p_slot;
}

// FUNCTION: LEGORACERS 0x004438e0
void MemoryCardSaveGame::Destroy()
{
	if (m_file.GetFlags() & GolStream::c_flagOpen) {
		MemoryCardFileBase* file = &m_file;
		file->Dispose();
	}

	SaveRecordList::Destroy();
}

// FUNCTION: LEGORACERS 0x00443910
LegoS32 MemoryCardSaveGame::OpenExistingFile()
{
	return m_file
		.BufferedOpenSlotFile(m_slot, g_memoryCardSaveFileName, GolStream::c_modeNoFileSource, c_fileBufferSize, 0);
}

// FUNCTION: LEGORACERS 0x00443940
LegoS32 MemoryCardSaveGame::CreateSaveFile()
{
	LegoS32 result = m_file.BufferedOpenSlotFile(
		m_slot,
		g_memoryCardSaveFileName,
		GolStream::c_modeCreate,
		c_fileBufferSize,
		c_fileBufferSize
	);
	if (!result) {
		result = SaveToFile();
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00443980
LegoS32 MemoryCardSaveGame::LoadFromFile()
{
	if (!m_file.IsOpen()) {
		LegoS32 result = OpenExistingFile();
		if (result) {
			return result;
		}
	}

	return SaveGame::LoadFromFile(m_file);
}

// FUNCTION: LEGORACERS 0x004439b0
LegoS32 MemoryCardSaveGame::SaveToFile()
{
	LegoS32 result = 0;

	if (!m_file.IsOpen()) {
		result = OpenExistingFile();
	}

	if (!result) {
		MemoryCardFile* file = &m_file;
		result = WriteFileImage(*file);
		if (!result) {
			result = file->FlushWriteBuffer();
		}
	}

	return result;
}
