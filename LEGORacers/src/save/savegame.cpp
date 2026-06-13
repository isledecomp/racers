#include "save/savegame.h"

#include "golbyteorder.h"

#include <string.h>

DECOMP_SIZE_ASSERT(SaveGame, 0x4a8)
DECOMP_SIZE_ASSERT(MemoryCardSaveGame, 0x4e0)

// FUNCTION: LEGORACERS 0x00442660
SaveGame::SaveGame()
{
	::memset(m_fileImage, 0, sizeof(m_fileImage));
	m_unk0x4a4 = 0;
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

// STUB: LEGORACERS 0x00442770
undefined4 SaveGame::FUN_00442770(GolFile& p_file)
{
	// TODO
	STUB(0x00442770);
	return 0;
}

// STUB: LEGORACERS 0x00442a00
void SaveGame::FUN_00442a00(PersistentGameState* p_state)
{
	const LegoU8* data = m_fileImage;
	const LegoU8* source = &data[c_persistentHeaderOffset];
	LegoU32 i;
	LegoU32 j;

	p_state->m_racerCount = source[0];
	::memcpy(&p_state->m_displayDriverGuid, &source[1], sizeof(p_state->m_displayDriverGuid));
	p_state->m_unk0x1d = source[0x11];
	p_state->m_unk0x1e = source[0x12];
	p_state->m_musicVolume = source[0x13];
	p_state->m_soundVolume = source[0x14];
	p_state->m_unk0x21 = source[0x15];
	p_state->m_languageIndex = source[0x16];
	p_state->m_unk0x23 = source[0x17];

	::memcpy(&p_state->m_inputBindings, &data[c_inputBindingHeaderOffset], c_inputBindingHeaderSize);

	source = &data[c_inputBindingEntryOffset];
	for (i = 0; i < sizeOfArray(p_state->m_inputBindings.m_entries); i++) {
		InputBindingEntry* entry = &p_state->m_inputBindings.m_entries[i];
		entry->m_deviceType = source[0];
		entry->m_deviceSubType = source[1];
		entry->m_deviceId = source[2];

		for (j = 0; j < sizeOfArray(entry->m_events); j++) {
			entry->m_events[j] = ReadLittleEndianU32(&source[3 + (j * sizeof(LegoU32))]);
		}

		source += c_inputBindingEntrySize;
	}

	p_state->m_partUnlockFlags = data[c_scoreRecordsOffset + (13 * c_scoreRecordSize)];
	p_state->m_unlockedCircuits = data[c_scoreRecordsOffset + (13 * c_scoreRecordSize) + 1];
	p_state->m_unlockedRaces =
		static_cast<LegoU16>(ReadLittleEndianU32(&data[c_scoreRecordsOffset + (13 * c_scoreRecordSize)]) >> 16);

	source = &data[c_scoreRecordsOffset];
	for (i = 0; i < sizeOfArray(p_state->m_bestLapTimes); i++) {
		p_state->m_bestLapTimes[i] = ReadLittleEndianU32(source);
		::memcpy(p_state->m_bestLapHolderNames[i], &source[4], sizeof(p_state->m_bestLapHolderNames[i]));
		p_state->m_bestRaceTimes[i] = ReadLittleEndianU32(&source[0x20]);
		::memcpy(p_state->m_bestRaceHolderNames[i], &source[0x24], sizeof(p_state->m_bestRaceHolderNames[i]));

		source += c_scoreRecordSize;
	}
}

// STUB: LEGORACERS 0x00442c20
void SaveGame::FUN_00442c20(PersistentGameState* p_state)
{
	LegoU8* data = m_fileImage;
	LegoU8* dest = &data[c_persistentHeaderOffset];
	LegoU32 i;
	LegoU32 j;

	dest[0] = p_state->m_racerCount;
	::memcpy(&dest[1], &p_state->m_displayDriverGuid, sizeof(p_state->m_displayDriverGuid));
	dest[0x11] = p_state->m_unk0x1d;
	dest[0x12] = p_state->m_unk0x1e;
	dest[0x13] = p_state->m_musicVolume;
	dest[0x14] = p_state->m_soundVolume;
	dest[0x15] = p_state->m_unk0x21;
	dest[0x16] = p_state->m_languageIndex;
	dest[0x17] = p_state->m_unk0x23;

	::memcpy(&data[c_inputBindingHeaderOffset], &p_state->m_inputBindings, c_inputBindingHeaderSize);

	dest = &data[c_inputBindingEntryOffset];
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

	data[c_scoreRecordsOffset + (13 * c_scoreRecordSize)] = p_state->m_partUnlockFlags;
	data[c_scoreRecordsOffset + (13 * c_scoreRecordSize) + 1] = p_state->m_unlockedCircuits;
	data[c_scoreRecordsOffset + (13 * c_scoreRecordSize) + 2] = static_cast<LegoU8>(p_state->m_unlockedRaces);
	data[c_scoreRecordsOffset + (13 * c_scoreRecordSize) + 3] = static_cast<LegoU8>(p_state->m_unlockedRaces >> 8);

	dest = &data[c_scoreRecordsOffset];
	for (i = 0; i < sizeOfArray(p_state->m_bestLapTimes); i++) {
		WriteLittleEndianU32(dest, p_state->m_bestLapTimes[i]);
		::memcpy(&dest[4], p_state->m_bestLapHolderNames[i], sizeof(p_state->m_bestLapHolderNames[i]));
		WriteLittleEndianU32(&dest[0x20], p_state->m_bestRaceTimes[i]);
		::memcpy(&dest[0x24], p_state->m_bestRaceHolderNames[i], sizeof(p_state->m_bestRaceHolderNames[i]));

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

// STUB: LEGORACERS 0x00443910
undefined4 MemoryCardSaveGame::FUN_00443910()
{
	// TODO
	STUB(0x00443910);
	return 0;
}

// STUB: LEGORACERS 0x00443940
undefined4 MemoryCardSaveGame::FUN_00443940()
{
	// TODO
	STUB(0x00443940);
	return 0;
}

// STUB: LEGORACERS 0x00443980
undefined4 MemoryCardSaveGame::FUN_00443980()
{
	// TODO
	STUB(0x00443980);
	return 0;
}

// STUB: LEGORACERS 0x004439b0
undefined4 SaveGame::FUN_004439b0()
{
	// TODO
	STUB(0x004439b0);
	return 0;
}
