#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "save/persistentgamestate.h"
#include "save/saverecordlist.h"
#include "types.h"
#include "util/displaydriverguid.h"

class GolString;
class InputManager;
class SaveGame;

// SIZE 0x438
class GameState {
public:
	GameState();
	~GameState();

	void Initialize(InputManager* p_inputManager);
	void Reset();
	void InitializeInputBindings(InputManager* p_inputManager);
	void SelectInputBinding(LegoU32 p_playerIndex, LegoU32 p_entryIndex);
	void LoadFromSaveGame(SaveGame* p_saveGame, LegoU32 p_activeSaveIndex);
	LegoU32 GetInputEvent(LegoU32 p_playerIndex, LegoU32 p_entryIndex, LegoU32 p_eventIndex);
	void GetInputBindingEntry(LegoU32 p_playerIndex, LegoU32 p_entryIndex, InputBindingState::Entry* p_entry);
	void SetInputEvent(LegoU32 p_entryIndex, LegoU32 p_eventIndex, LegoU32 p_event);
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
	void SetStereo(LegoU8 p_stereo)
	{
		m_state.m_stereo = p_stereo;
		m_dirty = 1;
	}
	void SetLapCount(LegoU32 p_lapCount)
	{
		m_dirty = 1;
		m_state.m_lapCount = static_cast<LegoU8>(p_lapCount);
	}
	void SetPlayer0SelectedRecordId(undefined4 p_recordId)
	{
		m_state.m_inputBindings.m_players[0].m_selectedRecordId = static_cast<LegoU8>(p_recordId);
		m_dirty = 1;
	}
	void SetPlayer0SelectedRecordSource(undefined4 p_recordSource)
	{
		m_state.m_inputBindings.m_players[0].m_selectedRecordSource = static_cast<LegoU8>(p_recordSource);
		m_dirty = 1;
	}
	void SetPlayer0SelectedSaveIndex(undefined4 p_saveIndex)
	{
		m_state.m_inputBindings.m_players[0].m_selectedSaveIndex = static_cast<LegoU8>(p_saveIndex);
		m_dirty = 1;
	}
	void SetInputBindingPlayer0RecordValues(const SaveRecordList::Record* p_record)
	{
		m_state.m_inputBindings.m_players[0].m_selectedRecordSource = static_cast<LegoU8>(p_record->m_recordSource);
		m_dirty = 1;
		m_state.m_inputBindings.m_players[0].m_selectedSaveIndex = static_cast<LegoU8>(p_record->m_saveIndex);
		m_dirty = 1;
		m_state.m_inputBindings.m_players[0].m_selectedRecordId = static_cast<LegoU8>(p_record->m_recordId);
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
	LegoU8 GetStereo() const { return m_state.m_stereo; }
	LegoU32 GetLanguageIndex() const { return m_state.m_languageIndex; }
	LegoU8 GetLapCount() const { return m_state.m_lapCount; }
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
	void SelectFallbackInputBinding(LegoU32 p_playerIndex);
	LegoU32 FindAvailableInputBindingEntry(LegoU32 p_playerIndex);
	LegoBool32 IsInputEventBound(LegoU32 p_entryIndex, LegoU32 p_event);
	LegoU32 GetDefaultInputEvent(LegoU32 p_entryIndex, LegoU32 p_eventIndex);
	LegoU32 GetRegistryLanguageIndex();

	LegoBool32 m_dirty;           // 0x00
	LegoU32 m_activeSaveIndex;    // 0x04
	InputManager* m_inputManager; // 0x08
	PersistentGameState m_state;  // 0x0c
};

#endif // GAMESTATE_H
