#include "save/savegame.h"

#include "golbyteorder.h"

#include <string.h>

DECOMP_SIZE_ASSERT(SaveGame, 0x4a8)
DECOMP_SIZE_ASSERT(MemoryCardFile, 0x34)
DECOMP_SIZE_ASSERT(MemoryCardSaveGame, 0x4e0)

// GLOBAL: LEGORACERS 0x004befd4
const LegoChar* g_memoryCardSaveFileName = "LEGORac1";

// GLOBAL: LEGORACERS 0x004c6b38
LegoU8 g_saveFileBlock[SaveGame::c_saveFileBlockSize];

// FUNCTION: LEGORACERS 0x00442660
SaveGame::SaveGame()
{
	::memset(m_fileImage, 0, sizeof(m_fileImage));
	m_fileOffset = 0;
}

// FUNCTION: LEGORACERS 0x00442680
SaveGame::~SaveGame()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004426d0
void SaveGame::Initialize(undefined4 p_count, undefined4 p_unk0x08, undefined4 p_unk0x0c)
{
	if (m_records) {
		Destroy();
	}

	AllocateRecords(p_count, p_unk0x08, p_unk0x0c);
}

// FUNCTION: LEGORACERS 0x00442700
LegoS32 SaveGame::WriteFileImage(GolFile& p_file)
{
	LegoU32 recordCount = m_recordCount;

	m_fileImage[0] = c_saveFileMagic0;
	m_fileImage[1] = c_saveFileMagic1;
	m_fileImage[2] = static_cast<LegoU8>(recordCount);
	m_fileImage[3] = c_saveFileBlockSize;
	m_fileImage[4] = 4;
	m_fileOffset = 0;

	LegoS32 result = WriteBlocks(&p_file, m_fileImage, c_saveFileHeaderSize);
	if (result) {
		return result;
	}

	for (LegoU32 i = 0; i < recordCount; i++) {
		Record* record = GetRecord(i);
		result = WriteBlocks(&p_file, record->m_data, sizeof(record->m_data));
		if (result) {
			return result;
		}
	}

	m_dirty = 0;
	return GolStream::e_ioSuccess;
}

// FUNCTION: LEGORACERS 0x00442770
LegoS32 SaveGame::LoadFromFile(GolFile& p_file)
{
	m_fileOffset = 0;

	LegoS32 result = ReadBlocks(p_file, m_fileImage, c_saveFileHeaderSize);
	if (result) {
		return result;
	}

	if (m_fileImage[0] != c_saveFileMagic0 || m_fileImage[1] != c_saveFileMagic1) {
		return c_saveFileInvalidStatus;
	}

	LegoU32 recordCount = m_fileImage[2];
	if (recordCount > m_recordCapacity) {
		return c_saveFileInvalidStatus;
	}

	m_recordCount = 0;
	RebuildFreeList();
	m_fileOffset = static_cast<LegoU16>(m_fileImage[3] + (m_fileImage[4] << 8));

	for (LegoU32 i = 0; i < recordCount; i++) {
		Record* record = AllocateRecord();
		record->FUN_0042b2f0(m_unk0x08, m_unk0x0c, i, NULL);
		result = ReadBlocks(p_file, record->m_data, sizeof(record->m_data));
		if (result) {
			return result;
		}
	}

	m_unk0x10 = recordCount;
	m_dirty = 0;
	return GolStream::e_ioSuccess;
}

// FUNCTION: LEGORACERS 0x00442840
LegoS32 SaveGame::WriteBlocks(GolStream* p_file, const LegoU8* p_source, LegoU32 p_size)
{
	SaveGame* saveGame = this;
	const LegoU8* end = p_source + p_size;
	LegoU32 fileOffset;

	while (p_source < end) {
		LegoU32 chunkSize = end - p_source;
		if (chunkSize >= c_saveFileBlockDataSize) {
			chunkSize = c_saveFileBlockDataSize;
		}
		else {
			::memset(&g_saveFileBlock[chunkSize], 0, c_saveFileBlockDataSize - chunkSize);
		}

		::memcpy(g_saveFileBlock, p_source, chunkSize);
		g_saveFileBlock[c_saveFileBlockDataSize] =
			static_cast<LegoU8>(CalculateBlockChecksum(g_saveFileBlock, c_saveFileBlockDataSize));

		LegoS32 result = p_file->BufferedWrite(saveGame->m_fileOffset, g_saveFileBlock, c_saveFileBlockSize);
		if (result) {
			return result;
		}

		fileOffset = saveGame->m_fileOffset;
		fileOffset += c_saveFileBlockSize;
		saveGame->m_fileOffset = fileOffset;
		p_source += chunkSize;
	}

	return GolStream::e_ioSuccess;
}

// FUNCTION: LEGORACERS 0x00442910
LegoS32 SaveGame::ReadBlocks(GolStream& p_file, LegoU8* p_dest, LegoU32 p_size)
{
	LegoU8* end = p_dest + p_size;

	while (p_dest < end) {
		LegoS32 bytesRead;
		LegoS32 result = p_file.BufferedRead(m_fileOffset, g_saveFileBlock, c_saveFileBlockSize, &bytesRead);
		if (result) {
			return result;
		}

		if (bytesRead != c_saveFileBlockSize ||
			g_saveFileBlock[c_saveFileBlockDataSize] !=
				static_cast<LegoU8>(CalculateBlockChecksum(g_saveFileBlock, c_saveFileBlockDataSize))) {
			return c_saveFileInvalidStatus;
		}

		LegoU32 chunkSize = end - p_dest;
		if (chunkSize >= c_saveFileBlockDataSize) {
			chunkSize = c_saveFileBlockDataSize;
		}

		::memcpy(p_dest, g_saveFileBlock, chunkSize);
		p_dest += chunkSize;
		m_fileOffset += c_saveFileBlockSize;
	}

	return GolStream::e_ioSuccess;
}

// FUNCTION: LEGORACERS 0x004429d0
LegoU32 SaveGame::CalculateBlockChecksum(const LegoU8* p_source, LegoU32 p_size)
{
	LegoU32 result = 0;

	for (LegoU32 i = 0; i < p_size; i++) {
		result += p_source[i];
	}

	return result;
}

// STUB: LEGORACERS 0x00442a00
void SaveGame::FUN_00442a00(PersistentGameState* p_state)
{
	const LegoU8* source;
	LegoU32 i;
	LegoU32 j;

	p_state->m_racerCount = m_fileImage[c_persistentHeaderOffset];
	source = &m_fileImage[c_persistentHeaderOffset + 1];
	for (i = 0; i < sizeof(p_state->m_displayDriverGuid.m_bytes); i++) {
		p_state->m_displayDriverGuid.m_bytes[i] = source[i];
	}
	p_state->m_unk0x1d = m_fileImage[c_persistentHeaderOffset + 0x11];
	p_state->m_unk0x1e = m_fileImage[c_persistentHeaderOffset + 0x12];
	p_state->m_musicVolume = m_fileImage[c_persistentHeaderOffset + 0x13];
	p_state->m_soundVolume = m_fileImage[c_persistentHeaderOffset + 0x14];
	p_state->m_unk0x21 = m_fileImage[c_persistentHeaderOffset + 0x15];
	p_state->m_languageIndex = m_fileImage[c_persistentHeaderOffset + 0x16];
	p_state->m_unk0x23 = m_fileImage[c_persistentHeaderOffset + 0x17];

	source = &m_fileImage[c_inputBindingHeaderOffset + 1];
	for (i = 0; i < sizeOfArray(p_state->m_inputBindings.m_players); i++) {
		InputBindingPlayerState* player = &p_state->m_inputBindings.m_players[i];
		player->m_selectedRecordId = source[-1];
		player->m_selectedRecordSource = source[0];
		player->m_selectedSaveIndex = source[1];
		player->m_selectedEntryIndex = source[2];
		source += sizeof(InputBindingPlayerState);
	}

	source = &m_fileImage[c_inputBindingEntryOffset + 2];
	for (i = 0; i < sizeOfArray(p_state->m_inputBindings.m_entries); i++) {
		InputBindingEntry* entry = &p_state->m_inputBindings.m_entries[i];
		entry->m_deviceType = source[-2];
		entry->m_deviceSubType = source[-1];
		entry->m_deviceId = source[0];

		for (j = 0; j < sizeOfArray(entry->m_events); j++) {
			entry->m_events[j] = ReadLittleEndianU32(&source[1 + (j * sizeof(LegoU32))]);
		}

		source += c_inputBindingEntrySize;
	}

	p_state->m_partUnlockFlags = m_fileImage[c_unlockStateOffset];
	p_state->m_unlockedCircuits = m_fileImage[c_unlockStateOffset + 1];
	p_state->m_unlockedRaces = ReadLittleEndianU16(&m_fileImage[c_unlockStateOffset + 2]);

	source = &m_fileImage[c_scoreRecordsOffset];
	for (i = 0; i < sizeOfArray(p_state->m_bestLapTimes); i++) {
		p_state->m_bestLapTimes[i] = ReadLittleEndianU32(source);
		for (j = 0; j < sizeof(p_state->m_bestLapHolderNames[i]); j++) {
			p_state->m_bestLapHolderNames[i][j] = source[4 + j];
		}
		p_state->m_bestRaceTimes[i] = ReadLittleEndianU32(&source[0x20]);
		for (j = 0; j < sizeof(p_state->m_bestRaceHolderNames[i]); j++) {
			p_state->m_bestRaceHolderNames[i][j] = source[0x24 + j];
		}

		source += c_scoreRecordSize;
	}
}

// STUB: LEGORACERS 0x00442c20
void SaveGame::FUN_00442c20(PersistentGameState* p_state)
{
	LegoU8* dest;
	LegoU32 i;
	LegoU32 j;

	m_fileImage[c_persistentHeaderOffset] = p_state->m_racerCount;
	for (i = 0; i < sizeof(p_state->m_displayDriverGuid.m_bytes); i++) {
		m_fileImage[c_persistentHeaderOffset + 1 + i] = p_state->m_displayDriverGuid.m_bytes[i];
	}
	m_fileImage[c_persistentHeaderOffset + 0x11] = p_state->m_unk0x1d;
	m_fileImage[c_persistentHeaderOffset + 0x12] = p_state->m_unk0x1e;
	m_fileImage[c_persistentHeaderOffset + 0x13] = p_state->m_musicVolume;
	m_fileImage[c_persistentHeaderOffset + 0x14] = p_state->m_soundVolume;
	m_fileImage[c_persistentHeaderOffset + 0x15] = p_state->m_unk0x21;
	m_fileImage[c_persistentHeaderOffset + 0x16] = p_state->m_languageIndex;
	m_fileImage[c_persistentHeaderOffset + 0x17] = p_state->m_unk0x23;

	dest = &m_fileImage[c_inputBindingHeaderOffset + 1];
	for (i = 0; i < sizeOfArray(p_state->m_inputBindings.m_players); i++) {
		InputBindingPlayerState* player = &p_state->m_inputBindings.m_players[i];
		dest[-1] = player->m_selectedRecordId;
		dest[0] = player->m_selectedRecordSource;
		dest[1] = player->m_selectedSaveIndex;
		dest[2] = player->m_selectedEntryIndex;
		dest += sizeof(InputBindingPlayerState);
	}

	dest = &m_fileImage[c_inputBindingEntryOffset];
	for (i = 0; i < sizeOfArray(p_state->m_inputBindings.m_entries); i++) {
		InputBindingEntry* entry = &p_state->m_inputBindings.m_entries[i];
		dest[0] = entry->m_deviceType;
		dest[1] = entry->m_deviceSubType;
		dest[2] = entry->m_deviceId;

		for (j = 0; j < sizeOfArray(entry->m_events); j++) {
			WriteLittleEndianU32(&dest[3 + (j * sizeof(LegoU32))], entry->m_events[j]);
		}

		dest += c_inputBindingEntrySize;
	}

	m_fileImage[c_unlockStateOffset] = p_state->m_partUnlockFlags;
	m_fileImage[c_unlockStateOffset + 1] = p_state->m_unlockedCircuits;
	m_fileImage[c_unlockStateOffset + 2] = static_cast<LegoU8>(p_state->m_unlockedRaces);
	m_fileImage[c_unlockStateOffset + 3] = static_cast<LegoU8>(p_state->m_unlockedRaces >> 8);

	dest = &m_fileImage[c_scoreRecordsOffset];
	for (i = 0; i < sizeOfArray(p_state->m_bestLapTimes); i++) {
		WriteLittleEndianU32(dest, p_state->m_bestLapTimes[i]);
		for (j = 0; j < sizeof(p_state->m_bestLapHolderNames[i]); j++) {
			dest[4 + j] = p_state->m_bestLapHolderNames[i][j];
		}
		WriteLittleEndianU32(&dest[0x20], p_state->m_bestRaceTimes[i]);
		for (j = 0; j < sizeof(p_state->m_bestRaceHolderNames[i]); j++) {
			dest[0x24 + j] = p_state->m_bestRaceHolderNames[i][j];
		}

		dest += c_scoreRecordSize;
	}
}

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
void MemoryCardSaveGame::Initialize(SaveSlot* p_slot, undefined4 p_count, undefined4 p_unk0x0c, undefined4 p_unk0x10)
{
	if (m_records) {
		Destroy();
	}

	SaveGame::Initialize(p_count, p_unk0x0c, p_unk0x10);
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
	return m_file.VTable0x3c(m_slot, g_memoryCardSaveFileName, GolStream::c_unk0x40, c_fileBufferSize, 0);
}

// FUNCTION: LEGORACERS 0x00443940
LegoS32 MemoryCardSaveGame::CreateSaveFile()
{
	LegoS32 result =
		m_file
			.VTable0x3c(m_slot, g_memoryCardSaveFileName, GolStream::c_modeCreate, c_fileBufferSize, c_fileBufferSize);
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
