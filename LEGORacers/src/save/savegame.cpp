#include "save/savegame.h"

#include "golbyteorder.h"
#include "golfile.h"
#include "save/persistentgamestate.h"

#include <string.h>

DECOMP_SIZE_ASSERT(SaveGame, 0x4a8)

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
void SaveGame::Initialize(undefined4 p_count, undefined4 p_recordSource, undefined4 p_saveIndex)
{
	if (m_records) {
		Destroy();
	}

	AllocateRecords(p_count, p_recordSource, p_saveIndex);
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
		record->Initialize(m_recordSource, m_saveIndex, i, NULL);
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
void SaveGame::ReadPersistentGameState(PersistentGameState* p_state)
{
	LegoU8* dest;
	const LegoU8* source;
	LegoU32 i;
	LegoU32 j;

	dest = &p_state->m_racerCount;
	dest[0] = m_fileImage[c_persistentHeaderOffset];
	source = &m_fileImage[c_persistentHeaderOffset + 1];
	for (i = 0; i < sizeof(p_state->m_displayDriverGuid.m_bytes); i++) {
		dest[i + 1] = source[i];
	}

	dest[0x11] = m_fileImage[c_persistentHeaderOffset + 0x11];
	dest[0x12] = m_fileImage[c_persistentHeaderOffset + 0x12];
	dest[0x13] = m_fileImage[c_persistentHeaderOffset + 0x13];
	dest[0x14] = m_fileImage[c_persistentHeaderOffset + 0x14];
	dest[0x15] = m_fileImage[c_persistentHeaderOffset + 0x15];
	dest[0x16] = m_fileImage[c_persistentHeaderOffset + 0x16];
	dest[0x17] = m_fileImage[c_persistentHeaderOffset + 0x17];

	source = &m_fileImage[c_inputBindingHeaderOffset + 1];
	dest = &p_state->m_inputBindings.m_players[0].m_selectedRecordSource;
	for (i = 0; i < sizeOfArray(p_state->m_inputBindings.m_players); i++) {
		dest[-1] = source[-1];
		dest[0] = source[0];
		dest[1] = source[1];
		dest[2] = source[2];

		source += sizeof(InputBindingState::PlayerState);
		dest += sizeof(InputBindingState::PlayerState);
	}

	source = &m_fileImage[c_inputBindingEntryOffset + 2];
	for (i = 0; i < sizeOfArray(p_state->m_inputBindings.m_entries); i++) {
		InputBindingState::Entry* entry = &p_state->m_inputBindings.m_entries[i];
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

	source = &m_fileImage[c_scoreRecordsOffset + c_scoreRecordCursorOffset];
	for (i = 0; i < c_scoreRecordCount; i++) {
		LegoU32 time = source[c_scoreRecordLapTimeOffset + 3 - c_scoreRecordCursorOffset];
		time <<= 8;
		time += source[c_scoreRecordLapTimeOffset + 2 - c_scoreRecordCursorOffset];
		time <<= 8;
		time += source[c_scoreRecordLapTimeOffset + 1 - c_scoreRecordCursorOffset];
		time <<= 8;
		time += source[c_scoreRecordLapTimeOffset - c_scoreRecordCursorOffset];
		p_state->m_bestLapTimes[i] = time;

		for (j = 0; j < c_scoreHolderNameSize; j++) {
			p_state->m_bestLapHolderNames[i][j] =
				source[c_scoreRecordLapHolderNameOffset - c_scoreRecordCursorOffset + j];
		}

		time = source[c_scoreRecordRaceTimeOffset + 3 - c_scoreRecordCursorOffset];
		time <<= 8;
		time += source[c_scoreRecordRaceTimeOffset + 2 - c_scoreRecordCursorOffset];
		time <<= 8;
		time += source[c_scoreRecordRaceTimeOffset + 1 - c_scoreRecordCursorOffset];
		time <<= 8;
		time += source[c_scoreRecordRaceTimeOffset - c_scoreRecordCursorOffset];
		p_state->m_bestRaceTimes[i] = time;

		for (j = 0; j < c_scoreHolderNameSize; j++) {
			p_state->m_bestRaceHolderNames[i][j] =
				source[c_scoreRecordRaceHolderNameOffset - c_scoreRecordCursorOffset + j];
		}

		source += c_scoreRecordSize;
	}
}

// STUB: LEGORACERS 0x00442c20
void SaveGame::WritePersistentGameState(PersistentGameState* p_state)
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
	m_fileImage[c_persistentHeaderOffset + 0x15] = p_state->m_stereo;
	m_fileImage[c_persistentHeaderOffset + 0x16] = p_state->m_languageIndex;
	m_fileImage[c_persistentHeaderOffset + 0x17] = p_state->m_lapCount;

	dest = &m_fileImage[c_inputBindingHeaderOffset + 1];
	for (i = 0; i < sizeOfArray(p_state->m_inputBindings.m_players); i++) {
		InputBindingState::PlayerState* player = &p_state->m_inputBindings.m_players[i];
		dest[-1] = player->m_selectedRecordId;
		dest[0] = player->m_selectedRecordSource;
		dest[1] = player->m_selectedSaveIndex;
		dest[2] = player->m_selectedEntryIndex;
		dest += sizeof(InputBindingState::PlayerState);
	}

	dest = &m_fileImage[c_inputBindingEntryOffset];
	for (i = 0; i < sizeOfArray(p_state->m_inputBindings.m_entries); i++) {
		InputBindingState::Entry* entry = &p_state->m_inputBindings.m_entries[i];
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

	dest = &m_fileImage[c_scoreRecordsOffset + c_scoreRecordCursorOffset];
	for (i = 0; i < c_scoreRecordCount; i++) {
		dest[c_scoreRecordLapTimeOffset - c_scoreRecordCursorOffset] = static_cast<LegoU8>(p_state->m_bestLapTimes[i]);
		dest[c_scoreRecordLapTimeOffset + 1 - c_scoreRecordCursorOffset] =
			static_cast<LegoU8>(p_state->m_bestLapTimes[i] >> 8);
		dest[c_scoreRecordLapTimeOffset + 2 - c_scoreRecordCursorOffset] =
			static_cast<LegoU8>(p_state->m_bestLapTimes[i] >> 16);
		dest[c_scoreRecordLapTimeOffset + 3 - c_scoreRecordCursorOffset] =
			static_cast<LegoU8>(p_state->m_bestLapTimes[i] >> 24);

		for (j = 0; j < c_scoreHolderNameSize; j++) {
			dest[c_scoreRecordLapHolderNameOffset - c_scoreRecordCursorOffset + j] =
				p_state->m_bestLapHolderNames[i][j];
		}

		dest[c_scoreRecordRaceTimeOffset - c_scoreRecordCursorOffset] =
			static_cast<LegoU8>(p_state->m_bestRaceTimes[i]);
		dest[c_scoreRecordRaceTimeOffset + 1 - c_scoreRecordCursorOffset] =
			static_cast<LegoU8>(p_state->m_bestRaceTimes[i] >> 8);
		dest[c_scoreRecordRaceTimeOffset + 2 - c_scoreRecordCursorOffset] =
			static_cast<LegoU8>(p_state->m_bestRaceTimes[i] >> 16);
		dest[c_scoreRecordRaceTimeOffset + 3 - c_scoreRecordCursorOffset] =
			static_cast<LegoU8>(p_state->m_bestRaceTimes[i] >> 24);

		for (j = 0; j < c_scoreHolderNameSize; j++) {
			dest[c_scoreRecordRaceHolderNameOffset - c_scoreRecordCursorOffset + j] =
				p_state->m_bestRaceHolderNames[i][j];
		}

		dest += c_scoreRecordSize;
	}
}
