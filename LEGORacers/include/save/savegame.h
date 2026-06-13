#ifndef SAVEGAME_H
#define SAVEGAME_H

#include "decomp.h"
#include "golfile.h"
#include "golname.h"
#include "save/savedirectory.h"
#include "types.h"
#include "util/displaydriverguid.h"

#include <string.h>

class GolFile;
class GolString;
class InputManager;
class ActiveRecordBuffer;
class MemoryCardSaveGame;
struct DriverCosmetics;

typedef undefined SaveRecordData[0x22d];

// SIZE 0x28
struct InputBindingEntry {
	LegoU8 m_deviceType;    // 0x00
	LegoU8 m_deviceSubType; // 0x01
	LegoU8 m_deviceId;      // 0x02
	LegoU8 m_unk0x03;       // 0x03
	LegoU32 m_events[9];    // 0x04
};

// SIZE 0x04
struct InputBindingPlayerState {
	LegoU8 m_unk0x00;            // 0x00
	LegoU8 m_unk0x01;            // 0x01
	LegoU8 m_unk0x02;            // 0x02
	LegoU8 m_selectedEntryIndex; // 0x03
};

// SIZE 0xd0
struct InputBindingState {
	InputBindingPlayerState m_players[2]; // 0x00
	InputBindingEntry m_entries[5];       // 0x08

	LegoU8 GetSelectedEntryIndex(LegoU32 p_playerIndex) const { return m_players[p_playerIndex].m_selectedEntryIndex; }

	void SetSelectedEntryIndex(LegoU32 p_playerIndex, LegoU8 p_entryIndex)
	{
		m_players[p_playerIndex].m_selectedEntryIndex = p_entryIndex;
	}
};

// SIZE 0x42c
struct PersistentGameState {
	void Clear() { ::memset(this, 0, sizeof(*this)); }

	LegoU8 m_racerCount;                               // 0x000
	DisplayDriverGuid::Serialized m_displayDriverGuid; // 0x001
	LegoU8 m_unk0x1d;                                  // 0x011
	LegoU8 m_unk0x1e;                                  // 0x012
	LegoU8 m_musicVolume;                              // 0x013
	LegoU8 m_soundVolume;                              // 0x014
	LegoU8 m_unk0x21;                                  // 0x015
	LegoU8 m_languageIndex;                            // 0x016
	LegoU8 m_unk0x23;                                  // 0x017
	LegoU8 m_partUnlockFlags;                          // 0x018
	LegoU8 m_unlockedCircuits;                         // 0x019
	LegoU16 m_unlockedRaces;                           // 0x01a
	LegoU32 m_bestLapTimes[13];                        // 0x01c
	LegoU32 m_bestRaceTimes[13];                       // 0x050
	LegoU8 m_bestLapHolderNames[13][28];               // 0x084
	LegoU8 m_bestRaceHolderNames[13][28];              // 0x1f0
	InputBindingState m_inputBindings;                 // 0x35c
};

// SIZE 0x24
class SaveRecordList {
public:
	// SIZE 0x244
	struct Record {
		Record();
		~Record();

		void FUN_0042b2f0(undefined4 p_unk0x08, undefined4 p_unk0x0c, undefined4 p_recordId, SaveRecordList* p_owner);
		void Destroy();
		void MarkDirty();
		void GetCosmetics(DriverCosmetics* p_cosmetics) const;
		void CopyCarData(LegoU8* p_dest) const;
		void GetChassisName(GolName p_dest) const;
		void GetName(GolString* p_string) const;
		LegoBool32 IsCarSaved() const;
		void MarkCarSaved();
		void MarkCarModified();
		void SetCosmetics(const DriverCosmetics* p_cosmetics);
		void SetChassisName(const GolName p_source);
		void SetName(GolString* p_string);
		void CopyFrom(const Record* p_source);
		LegoU32 GetTrophy(undefined4 p_raceIndex) const;
		LegoBool32 FUN_0042b640(LegoU32 p_raceIndex, LegoU32 p_trophy);
		LegoU8* GetCarData() { return &m_data[0x29]; }
		const LegoU8* GetCarData() const { return &m_data[0x29]; }

		SaveRecordList* m_owner; // 0x00
		Record* m_next;          // 0x04
		undefined4 m_unk0x08;    // 0x08
		undefined4 m_unk0x0c;    // 0x0c
		undefined4 m_recordId;   // 0x10
		SaveRecordData m_data;   // 0x14
		undefined m_unk0x241[0x244 - 0x241];

	private:
		void Initialize();
	};

	// SIZE 0x241
	struct SerializedRecord {
		undefined m_unk0x00[0x14]; // 0x00
		SaveRecordData m_data;     // 0x14
	};

	SaveRecordList();
	~SaveRecordList();

	Record* AllocateRecord();
	Record* FUN_0042b8f0(Record* p_record);
	void FUN_0042b920(Record* p_record);
	Record* GetRecord(LegoU32 p_index);
	Record* FindRecordById(undefined4 p_recordId);
	LegoU32 GetRecordCount() const { return m_recordCount; }
	LegoBool32 HasRecords() const { return m_records != 0; }
	LegoS32 GetAvailableRecordCount() const { return m_recordCapacity - m_recordCount; }
	LegoBool32 IsDirty() const { return m_dirty; }
	void Destroy();

private:
	friend struct Record;

	void Initialize();
	void AllocateRecords(LegoU32 p_count, undefined4 p_unk0x08, undefined4 p_unk0x0c);
	void FreeRecords();
	void FUN_0042b830();

	friend class SaveGame;
	friend class MemoryCardSaveGame;

	LegoU32 m_recordCount;    // 0x00
	Record* m_records;        // 0x04
	undefined4 m_unk0x08;     // 0x08
	undefined4 m_unk0x0c;     // 0x0c
	undefined4 m_unk0x10;     // 0x10
	Record* m_freeRecords;    // 0x14
	Record* m_usedRecords;    // 0x18
	LegoU32 m_recordCapacity; // 0x1c
	LegoBool32 m_dirty;       // 0x20
};

// SIZE 0x4a8
class SaveGame : public SaveRecordList {
public:
	SaveGame();
	~SaveGame();

	LegoU8* GetFileImage() { return m_fileImage; }
	void Initialize(undefined4 p_count, undefined4 p_unk0x08, undefined4 p_unk0x0c);
	undefined4 FUN_00442770(GolFile& p_file);
	void FUN_00442a00(PersistentGameState* p_state);
	void FUN_00442c20(PersistentGameState* p_state);
	undefined4 FUN_004439b0();

private:
	enum {
		c_scoreRecordsOffset = 0x09,
		c_scoreRecordSize = 0x40,
		c_persistentHeaderOffset = 0x349,
		c_inputBindingHeaderOffset = 0x361,
		c_inputBindingEntryOffset = 0x369,
		c_inputBindingEntrySize = 0x27,
		c_inputBindingHeaderSize = 8,
	};

	LegoU8 m_fileImage[0x4a4 - 0x24]; // 0x24
	undefined4 m_unk0x4a4;
};

// VTABLE: LEGORACERS 0x004b0fac
// SIZE 0x30
class SaveGameFile : public GolFile {
public:
	~SaveGameFile() override; // vtable+0x18

	LegoS32 BufferedOpen(const LegoChar* p_fileName, LegoS32 p_mode, LegoU32 p_bufferSize) override; // vtable+0x1c
	LegoS32 Dispose() override;                                                                      // vtable+0x20

	// SYNTHETIC: LEGORACERS 0x0044e110
	// SaveGameFile::`scalar deleting destructor'
};

// VTABLE: LEGORACERS 0x004b1288
// SIZE 0x34
class MemoryCardFileBase : public SaveGameFile {
public:
	MemoryCardFileBase();

	// SYNTHETIC: LEGORACERS 0x00450e70 FOLDED
	// MemoryCardFileBase::~MemoryCardFileBase

	// SYNTHETIC: LEGORACERS 0x00450e50 FOLDED
	// MemoryCardFileBase::`scalar deleting destructor'

private:
	undefined4 m_unk0x30; // 0x30
};

// VTABLE: LEGORACERS 0x004b0ba4
// SIZE 0x34
class MemoryCardFile : public MemoryCardFileBase {
public:
	// SYNTHETIC: LEGORACERS 0x00450e70 FOLDED
	// MemoryCardFile::~MemoryCardFile

	// SYNTHETIC: LEGORACERS 0x00450e50 FOLDED
	// MemoryCardFile::`scalar deleting destructor'
};

// SIZE 0x4e0
class MemoryCardSaveGame : public SaveGame {
public:
	MemoryCardSaveGame();
	~MemoryCardSaveGame();

	LegoBool32 HasUnk0x4b4Flag0x01() const { return !m_slot->HasUnk0x04() && m_file.IsOpen(); }

	void Initialize(SaveSlot* p_slot, undefined4 p_count, undefined4 p_unk0x0c, undefined4 p_unk0x10);
	void Destroy();
	undefined4 FUN_00443910();
	undefined4 FUN_00443940();
	undefined4 FUN_00443980();

private:
	SaveSlot* m_slot;      // 0x4a8
	MemoryCardFile m_file; // 0x4ac
};

// SIZE 0x438
class GameState {
public:
	GameState();
	~GameState();

	void Initialize(InputManager* p_inputManager);
	void Reset();
	void InitializeInputBindings(InputManager* p_inputManager);
	void SelectInputBinding(LegoU32 p_playerIndex, LegoU32 p_entryIndex);
	void FUN_0042eb60(SaveGame*, undefined4);
	LegoU32 GetInputEvent(LegoU32 p_playerIndex, LegoU32 p_entryIndex, LegoU32 p_eventIndex);
	void GetInputBindingEntry(LegoU32 p_playerIndex, LegoU32 p_entryIndex, InputBindingEntry* p_entry);
	void FUN_0042ee70(LegoU32 p_entryIndex, LegoU32 p_eventIndex, LegoU32 p_event);
	void WriteToSaveGame(SaveGame*);
	void SetLanguageResourcePath();
	void SetDisplayDriverGuid(const DisplayDriverGuid& p_guid);
	void GetDisplayDriverGuid(DisplayDriverGuid& p_guid);
	void UnlockParts(LegoU8 p_flags);
	void UnlockCircuits(LegoU8 p_flags);
	LegoU16 GetUnlockedRaces() const;
	LegoBool32 UnlockRace(LegoU32 p_mask);
	LegoBool32 AreAllRacesUnlocked() const;
	LegoU32 GetBestTime(LegoU32 p_raceIndex, LegoBool32 p_raceTime, GolString* p_string) const;
	LegoBool32 SetBestTime(LegoU32 p_raceIndex, LegoBool32 p_raceTime, LegoU32 p_time, GolString* p_string);

	void SetDirty(LegoBool32 p_dirty) { m_dirty = p_dirty; }
	void SetRacerCount(LegoU32 p_racerCount)
	{
		m_dirty = 1;
		m_state.m_racerCount = static_cast<LegoU8>(p_racerCount);
	}
	void SetMusicVolume(LegoU8 p_musicVolume)
	{
		m_state.m_musicVolume = p_musicVolume;
		m_dirty = 1;
	}
	void SetSoundVolume(LegoU8 p_soundVolume)
	{
		m_state.m_soundVolume = p_soundVolume;
		m_dirty = 1;
	}
	void SetUnk0x21(LegoU8 p_unk0x21)
	{
		m_state.m_unk0x21 = p_unk0x21;
		m_dirty = 1;
	}
	void SetUnk0x23(LegoU32 p_unk0x23)
	{
		m_dirty = 1;
		m_state.m_unk0x23 = static_cast<LegoU8>(p_unk0x23);
	}
	void SetInputBindingPlayer0Unk0x00(undefined4 p_unk0x00)
	{
		m_state.m_inputBindings.m_players[0].m_unk0x00 = static_cast<LegoU8>(p_unk0x00);
		m_dirty = 1;
	}
	void SetInputBindingPlayer0Unk0x01(undefined4 p_unk0x01)
	{
		m_state.m_inputBindings.m_players[0].m_unk0x01 = static_cast<LegoU8>(p_unk0x01);
		m_dirty = 1;
	}
	void SetInputBindingPlayer0Unk0x02(undefined4 p_unk0x02)
	{
		m_state.m_inputBindings.m_players[0].m_unk0x02 = static_cast<LegoU8>(p_unk0x02);
		m_dirty = 1;
	}
	void SetInputBindingPlayer0RecordValues(const SaveRecordList::Record* p_record)
	{
		m_state.m_inputBindings.m_players[0].m_unk0x01 = p_record->m_unk0x08;
		m_dirty = 1;
		m_state.m_inputBindings.m_players[0].m_unk0x02 = p_record->m_unk0x0c;
		m_dirty = 1;
		m_state.m_inputBindings.m_players[0].m_unk0x00 = p_record->m_recordId;
		m_dirty = 1;
	}
	void SetLanguageIndex(LegoU8 p_languageIndex) { m_state.m_languageIndex = p_languageIndex; }
	LegoU8 GetSelectedInputBindingEntryIndex(LegoU32 p_playerIndex) const
	{
		return m_state.m_inputBindings.GetSelectedEntryIndex(p_playerIndex);
	}
	LegoBool32 IsDirty() const { return m_dirty; }
	undefined4 GetActiveSaveIndex() const { return m_activeSaveIndex; }
	PersistentGameState& GetState() { return m_state; }
	LegoU8 GetRacerCount() const { return m_state.m_racerCount; }
	LegoU8 GetMusicVolume() const { return m_state.m_musicVolume; }
	LegoU8 GetSoundVolume() const { return m_state.m_soundVolume; }
	LegoU8 GetUnk0x21() const { return m_state.m_unk0x21; }
	LegoU32 GetLanguageIndex() const { return m_state.m_languageIndex; }
	LegoU8 GetUnk0x23() const { return m_state.m_unk0x23; }
	LegoU8 GetPartUnlockFlags() const;
	LegoU8 GetUnlockedCircuits() const;

private:
	enum {
		c_joystickBindingCount = 2,
		c_keyboardBindingStart = 2,
		c_inputBindingEntryCount = 5,
		c_inputBindingEventCount = 9,
		c_joystickDeviceType = 4,
		c_axisJoystickDeviceSubType = 4,
	};

	void Initialize();
	void FUN_0042ea50(LegoU32 p_playerIndex);
	LegoU32 FindAvailableInputBindingEntry(LegoU32 p_playerIndex);
	LegoBool32 IsInputEventBound(LegoU32 p_entryIndex, LegoU32 p_event);
	LegoU32 GetDefaultInputEvent(LegoU32 p_entryIndex, LegoU32 p_eventIndex);
	LegoU32 GetRegistryLanguageIndex();

	LegoBool32 m_dirty;           // 0x00
	undefined4 m_activeSaveIndex; // 0x04
	InputManager* m_inputManager; // 0x08
	PersistentGameState m_state;  // 0x0c
};

// SIZE 0x250
class ActiveRecordBuffer : public SaveRecordList::Record {
public:
	static void CopyBufferToString(GolString* p_string, const LegoU8* p_source, LegoU32 p_count);
	static void CopyStringToBuffer(GolString* p_string, LegoU8* p_dest, LegoU32 p_count);

	void SetCarData(const LegoU8* p_source);
	void Reset() { m_selectedRecordCount = 0; }
	undefined4 GetSelectedRecordCount() const { return m_selectedRecordCount; }
	undefined2 GetSelectedRecordCountAsU16() const { return static_cast<undefined2>(m_selectedRecordCount); }
	SaveRecordList::Record* GetSelectedRecord() const { return m_selectedRecords[0]; }
	SaveRecordList::Record* GetSelectedRecord(LegoU32 p_index) const { return m_selectedRecords[p_index]; }
	void SetSelectedRecordCount(undefined4 p_count) { m_selectedRecordCount = p_count; }
	void SetSelectedRecord(SaveRecordList::Record* p_record) { m_selectedRecords[0] = p_record; }
	void SetSelectedRecord(LegoU32 p_index, SaveRecordList::Record* p_record) { m_selectedRecords[p_index] = p_record; }

private:
	undefined4 m_selectedRecordCount;             // 0x244
	SaveRecordList::Record* m_selectedRecords[2]; // 0x248
};

#endif // SAVEGAME_H
