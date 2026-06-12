#include "golhashtable.h"
#include "golstream.h"
#include "golstring.h"
#include "input/inputdevice.h"
#include "input/inputmanager.h"
#include "input/joystickdevice.h"
#include "input/keyboarddevice.h"
#include "save/savegame.h"

#include <string.h>
#include <windows.h>

DECOMP_SIZE_ASSERT(GameState, 0x438)
DECOMP_SIZE_ASSERT(DisplayDriverGuid::SerializedWord, 0x04)
DECOMP_SIZE_ASSERT(DisplayDriverGuid::Serialized, 0x10)
DECOMP_SIZE_ASSERT(InputBindingEntry, 0x28)
DECOMP_SIZE_ASSERT(InputBindingPlayerState, 0x04)
DECOMP_SIZE_ASSERT(InputBindingState, 0xd0)
DECOMP_SIZE_ASSERT(PersistentGameState, 0x42c)

// GLOBAL: LEGORACERS 0x004b0624
const LegoU32 g_keyboardInputBindingEvents[3][9] = {
	{
		InputDevice::c_sourceKeyboard | 0xcb,
		InputDevice::c_sourceKeyboard | 0xcd,
		InputDevice::c_sourceKeyboard | 0xc8,
		InputDevice::c_sourceKeyboard | 0xd0,
		InputDevice::c_sourceKeyboard | 0x1c,
		InputDevice::c_sourceKeyboard | 0x9d,
		InputDevice::c_sourceKeyboard | 0x32,
		InputDevice::c_sourceKeyboard | 0x39,
		InputDevice::c_sourceKeyboard | 0xb8,
	},
	{
		InputDevice::c_sourceKeyboard | 0x1e,
		InputDevice::c_sourceKeyboard | 0x20,
		InputDevice::c_sourceKeyboard | 0x11,
		InputDevice::c_sourceKeyboard | 0x2d,
		InputDevice::c_sourceKeyboard | 0x38,
		InputDevice::c_sourceKeyboard | 0x10,
		InputDevice::c_sourceKeyboard | 0x12,
		InputDevice::c_sourceKeyboard | 0x2a,
		InputDevice::c_sourceKeyboard | 0x2c,
	},
	{
		InputDevice::c_sourceKeyboard | 0x4b,
		InputDevice::c_sourceKeyboard | 0x4d,
		InputDevice::c_sourceKeyboard | 0x48,
		InputDevice::c_sourceKeyboard | 0x50,
		InputDevice::c_sourceKeyboard | 0x36,
		InputDevice::c_sourceKeyboard | 0x51,
		InputDevice::c_sourceKeyboard | 0x47,
		InputDevice::c_sourceKeyboard | 0x9c,
		InputDevice::c_sourceKeyboard | 0x49,
	},
};

// GLOBAL: LEGORACERS 0x004becd8
const LegoChar* g_menuLanguageDirectories[9] =
	{"english", "spanish", "french", "german", "italian", "danish", "swedish", "norwegi", "dutch"};

extern DisplayDriverGuid g_displayDriverGuid;

// FUNCTION: LEGORACERS 0x0042e880
GameState::GameState()
{
	Initialize();
}

// FUNCTION: LEGORACERS 0x0042e890
GameState::~GameState()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0042e8a0
void GameState::Initialize()
{
	m_dirty = 0;
	m_activeSaveIndex = 0xffffffff;

	m_state.Clear();
	m_state.m_racerCount = 5;
	m_state.m_unk0x1e = 0x80;
	m_state.m_musicVolume = 0xff;
	m_state.m_soundVolume = 0xff;
	m_state.m_unk0x21 = 1;
	m_state.m_languageIndex = GetRegistryLanguageIndex();
	m_state.m_unk0x23 = 3;
	m_state.m_inputBindings.m_players[0].m_unk0x00 = 0;
	m_state.m_inputBindings.m_players[0].m_unk0x01 = 2;
	m_state.m_inputBindings.m_players[0].m_unk0x02 = 0;
	m_state.m_inputBindings.m_players[0].m_selectedEntryIndex = 0;
	m_state.m_inputBindings.m_players[1].m_unk0x00 = 0;
	m_state.m_inputBindings.m_players[1].m_unk0x01 = 2;
	m_state.m_inputBindings.m_players[1].m_unk0x02 = 0;
	m_state.m_inputBindings.m_players[1].m_selectedEntryIndex = 1;
	m_inputManager = NULL;
}

// FUNCTION: LEGORACERS 0x0042e920
void GameState::Initialize(InputManager* p_inputManager)
{
	Reset();
	m_inputManager = p_inputManager;
	InitializeInputBindings(p_inputManager);
	SetDisplayDriverGuid(g_displayDriverGuid);
	m_dirty = 0;
}

// FUNCTION: LEGORACERS 0x0042e950
void GameState::Reset()
{
	Initialize();
}

// FUNCTION: LEGORACERS 0x0042e960
void GameState::InitializeInputBindings(InputManager* p_inputManager)
{
	LegoS32 i;
	LegoS32 j;

	for (i = 0; i < 2; i++) {
		InputBindingEntry* entry = &m_state.m_inputBindings.m_entries[i];
		JoystickInputDevice* joystick = p_inputManager->FindJoystickByDeviceId(i);

		if (joystick == NULL) {
			entry->m_deviceType = 4;
			entry->m_deviceSubType = 2;
		}
		else {
			entry->m_deviceType = joystick->GetDeviceType();
			entry->m_deviceSubType = joystick->GetDeviceSubType();
		}

		entry->m_deviceId = i;
		::memset(entry->m_events, 0, sizeof(entry->m_events));

		if (joystick != NULL) {
			if (joystick->GetDeviceSubType() == 4) {
				entry->m_events[0] = InputDevice::c_sourceJoystickAxisButton | 1;
				entry->m_events[1] = InputDevice::c_sourceJoystickAxisButton;
			}

			for (LegoS32 button = 2; button < joystick->GetButtonCountFast(); button++) {
				entry->m_events[button] = InputDevice::c_sourceJoystickButton | (button - 2);
			}
		}
	}

	KeyboardInputDevice* keyboard = p_inputManager->GetKeyboard();

	for (i = 0; i < sizeOfArray(g_keyboardInputBindingEvents); i++) {
		if (keyboard == NULL) {
			m_state.m_inputBindings.m_entries[4].m_deviceSubType = 4;
		}
		else {
			m_state.m_inputBindings.m_entries[4].m_deviceSubType = keyboard->GetDeviceSubType();
		}

		InputBindingEntry* entry = &m_state.m_inputBindings.m_entries[i + 2];
		entry->m_deviceType = 3;
		entry->m_deviceId = 0;

		for (j = 0; j < sizeOfArray(entry->m_events); j++) {
			entry->m_events[j] = g_keyboardInputBindingEvents[i][j];
		}
	}
}

// STUB: LEGORACERS 0x0042ea50
void GameState::FUN_0042ea50(LegoU32 p_playerIndex)
{
	LegoU32 otherPlayerIndex = p_playerIndex == 0 ? 1 : 0;
	LegoU32 otherEntryIndex = m_state.m_inputBindings.GetSelectedEntryIndex(otherPlayerIndex);

	for (LegoU32 i = 0; i < c_joystickBindingCount; i++) {
		if (otherEntryIndex != i) {
			InputBindingEntry* entry = &m_state.m_inputBindings.m_entries[i];
			if (m_inputManager->FindJoystickByDeviceId(entry->m_deviceId) != NULL) {
				SelectInputBinding(p_playerIndex, i);
				return;
			}
		}
	}

	SelectInputBinding(p_playerIndex, FindAvailableInputBindingEntry(p_playerIndex));
}

// FUNCTION: LEGORACERS 0x0042eac0
LegoU32 GameState::FindAvailableInputBindingEntry(LegoU32 p_playerIndex)
{
	LegoU32 otherPlayerIndex = p_playerIndex == 0 ? 1 : 0;
	LegoU32 otherEntryIndex = m_state.m_inputBindings.GetSelectedEntryIndex(otherPlayerIndex);

	if (p_playerIndex && otherEntryIndex < c_joystickBindingCount) {
		InputBindingEntry* entry = &m_state.m_inputBindings.m_entries[otherEntryIndex];
		LegoU32 deviceId = entry->m_deviceId;
		JoystickInputDevice* joystick = m_inputManager->FindJoystickByDeviceId(deviceId);

		if (joystick != NULL && static_cast<LegoU32>(joystick->GetButtonCountFast()) >= c_inputBindingEventCount) {
			return c_keyboardBindingStart;
		}
	}

	LegoU32 result = otherEntryIndex == c_keyboardBindingStart;
	return c_keyboardBindingStart + result;
}

// FUNCTION: LEGORACERS 0x0042eb20
void GameState::SelectInputBinding(LegoU32 p_playerIndex, LegoU32 p_entryIndex)
{
	LegoU32 otherPlayerIndex = p_playerIndex == 0 ? 1 : 0;

	m_dirty = 1;
	m_state.m_inputBindings.SetSelectedEntryIndex(p_playerIndex, static_cast<LegoU8>(p_entryIndex));

	if (p_entryIndex == m_state.m_inputBindings.GetSelectedEntryIndex(otherPlayerIndex)) {
		FUN_0042ea50(otherPlayerIndex);
	}
}

// STUB: LEGORACERS 0x0042eb60
void GameState::FUN_0042eb60(SaveGame* p_saveGame, undefined4 p_index)
{
	PersistentGameState state;
	LegoU32 i;

	m_activeSaveIndex = p_index;
	m_dirty = 0;
	p_saveGame->FUN_00442a00(&state);

	m_state.m_racerCount = state.m_racerCount;
	m_state.m_displayDriverGuid = state.m_displayDriverGuid;
	m_state.m_unk0x1d = state.m_unk0x1d;
	m_state.m_unk0x1e = state.m_unk0x1e;
	m_state.m_musicVolume = state.m_musicVolume;
	m_state.m_soundVolume = state.m_soundVolume;
	m_state.m_unk0x21 = state.m_unk0x21;
	m_state.m_languageIndex = state.m_languageIndex;
	m_state.m_unk0x23 = state.m_unk0x23;

	LegoU8* destBindingEntry = &m_state.m_inputBindings.m_entries[0].m_deviceSubType;
	LegoU8* sourceBindingEntry = &state.m_inputBindings.m_entries[0].m_deviceSubType;
	for (i = 0; i < c_inputBindingEntryCount; i++) {
		if (destBindingEntry[-1] == sourceBindingEntry[-1] && destBindingEntry[0] == sourceBindingEntry[0] &&
			destBindingEntry[1] == sourceBindingEntry[1]) {
			::memcpy(
				destBindingEntry + 3,
				sourceBindingEntry + 3,
				sizeof(m_state.m_inputBindings.m_entries[0].m_events)
			);
		}

		sourceBindingEntry += sizeof(InputBindingEntry);
		destBindingEntry += sizeof(InputBindingEntry);
	}

	InputBindingPlayerState* sourcePlayer = state.m_inputBindings.m_players;
	InputBindingPlayerState* destPlayer = m_state.m_inputBindings.m_players;
	LegoU8* selectedEntryIndex = &destPlayer->m_selectedEntryIndex;
	for (i = 0; i < c_joystickBindingCount; i++) {
		*destPlayer = *sourcePlayer;

		InputBindingEntry* entry = &m_state.m_inputBindings.m_entries[*selectedEntryIndex];

		if (entry->m_deviceType == c_joystickDeviceType &&
			m_inputManager->FindJoystickByDeviceId(entry->m_deviceId) == NULL) {
			FUN_0042ea50(i);
		}

		sourcePlayer++;
		destPlayer++;
		selectedEntryIndex += sizeof(InputBindingPlayerState);
	}

	m_state.m_partUnlockFlags = state.m_partUnlockFlags;
	m_state.m_unlockedCircuits = state.m_unlockedCircuits;
	m_state.m_unlockedRaces = state.m_unlockedRaces;

	for (i = 0; i < sizeOfArray(m_state.m_unk0x28); i++) {
		m_state.m_unk0x28[i] = state.m_unk0x28[i];
		m_state.m_unk0x5c[i] = state.m_unk0x5c[i];
		::memcpy(m_state.m_unk0x90[i], state.m_unk0x90[i], sizeof(m_state.m_unk0x90[i]));
		::memcpy(m_state.m_unk0x1fc[i], state.m_unk0x1fc[i], sizeof(m_state.m_unk0x1fc[i]));
	}
}

// FUNCTION: LEGORACERS 0x0042ed10
LegoBool32 GameState::IsInputEventBound(LegoU32 p_entryIndex, LegoU32 p_event)
{
	InputBindingEntry* entry = &m_state.m_inputBindings.m_entries[p_entryIndex];
	LegoS32 i;
	LegoS32 j;

	if ((p_event & InputDevice::c_sourceMask) == InputDevice::c_sourceJoystickButton) {
		for (i = 0; i < c_inputBindingEventCount; i++) {
			if (entry->m_events[i] == p_event) {
				return TRUE;
			}
		}

		return FALSE;
	}

	for (i = 0; i < c_inputBindingEntryCount; i++) {
		entry = &m_state.m_inputBindings.m_entries[i];

		for (j = 0; j < c_inputBindingEventCount; j++) {
			if (entry->m_events[j] == p_event) {
				return TRUE;
			}
		}
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x0042ed80
LegoU32 GameState::GetInputEvent(LegoU32 p_playerIndex, LegoU32 p_entryIndex, LegoU32 p_eventIndex)
{
	LegoU32 event = m_state.m_inputBindings.m_entries[p_entryIndex].m_events[p_eventIndex];

	if (event) {
		return event;
	}

	event = GetDefaultInputEvent(p_entryIndex, p_eventIndex);
	if (event) {
		if (!IsInputEventBound(p_entryIndex, event)) {
			FUN_0042ee70(p_entryIndex, p_eventIndex, event);
			return event;
		}
	}

	if (p_entryIndex < 1 && p_eventIndex > 1) {
		LegoU32 fallbackEntryIndex = FindAvailableInputBindingEntry(p_playerIndex);
		return m_state.m_inputBindings.m_entries[fallbackEntryIndex].m_events[p_eventIndex];
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x0042ee10
void GameState::GetInputBindingEntry(LegoU32 p_playerIndex, LegoU32 p_entryIndex, InputBindingEntry* p_entry)
{
	LegoS32 i;

	p_entry->m_deviceType = m_state.m_inputBindings.m_entries[p_entryIndex].m_deviceType;
	p_entry->m_deviceId = m_state.m_inputBindings.m_entries[p_entryIndex].m_deviceId;
	p_entry->m_deviceSubType = m_state.m_inputBindings.m_entries[p_entryIndex].m_deviceSubType;

	for (i = 0; i < c_inputBindingEventCount; i++) {
		p_entry->m_events[i] = GetInputEvent(p_playerIndex, p_entryIndex, i);
	}
}

// STUB: LEGORACERS 0x0042ee70
void GameState::FUN_0042ee70(LegoU32 p_entryIndex, LegoU32 p_eventIndex, LegoU32 p_event)
{
	LegoU32 i;
	LegoU32 j;

	if (m_state.m_inputBindings.m_entries[p_entryIndex].m_events[p_eventIndex] == p_event) {
		return;
	}

	if ((p_event & InputDevice::c_sourceMask) != InputDevice::c_sourceKeyboard) {
		for (i = 0; i < c_inputBindingEventCount; i++) {
			if (m_state.m_inputBindings.m_entries[p_entryIndex].m_events[i] == p_event) {
				m_state.m_inputBindings.m_entries[p_entryIndex].m_events[i] = 0;
			}
		}
	}
	else {
		for (i = 0; i < c_inputBindingEntryCount; i++) {
			InputBindingEntry* otherEntry = &m_state.m_inputBindings.m_entries[i];

			for (j = 0; j < c_inputBindingEventCount; j++) {
				if (otherEntry->m_events[j] == p_event) {
					otherEntry->m_events[j] = 0;
				}
			}
		}
	}

	m_state.m_inputBindings.m_entries[p_entryIndex].m_events[p_eventIndex] = p_event;
	m_dirty = 1;
}

// FUNCTION: LEGORACERS 0x0042ef00
LegoU32 GameState::GetDefaultInputEvent(LegoU32 p_entryIndex, LegoU32 p_eventIndex)
{
	InputBindingEntry* entry = &m_state.m_inputBindings.m_entries[p_entryIndex];
	LegoU32 result = 0;

	if (entry->m_deviceType == c_joystickDeviceType) {
		if (p_eventIndex < 2 && entry->m_deviceSubType != c_axisJoystickDeviceSubType) {
			return result;
		}

		JoystickInputDevice* joystick = m_inputManager->FindJoystickByDeviceId(entry->m_deviceId);
		p_eventIndex -= 2;

		if (joystick != NULL && static_cast<LegoU32>(joystick->GetButtonCountFast()) > p_eventIndex) {
			result = InputDevice::c_sourceJoystickButton | p_eventIndex;
		}
	}
	else if (p_entryIndex >= c_keyboardBindingStart) {
		result = g_keyboardInputBindingEvents[p_entryIndex - c_keyboardBindingStart][p_eventIndex];
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0042ef80
void GameState::WriteToSaveGame(SaveGame* p_saveGame)
{
	p_saveGame->FUN_00442c20(&m_state);
}

// FUNCTION: LEGORACERS 0x0042ef90
void GameState::SetLanguageResourcePath()
{
	LegoChar path[24];

	::strcpy(path, "MENUDATA\\");
	::strcat(path, g_menuLanguageDirectories[m_state.m_languageIndex]);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString(path);
	}
}

// FUNCTION: LEGORACERS 0x0042f020
void GameState::SetDisplayDriverGuid(const DisplayDriverGuid& p_guid)
{
	const LegoU32* source = p_guid.GetWords();

	m_dirty = 1;

	DisplayDriverGuid::SerializedWord* dest = m_state.m_displayDriverGuid.m_words;
	for (LegoU32 i = 0; i < sizeOfArray(m_state.m_displayDriverGuid.m_words); i++, source++, dest++) {
		dest->Set(*source);
	}
}

// FUNCTION: LEGORACERS 0x0042f060
void GameState::GetDisplayDriverGuid(DisplayDriverGuid& p_guid)
{
	const DisplayDriverGuid::SerializedWord* source = m_state.m_displayDriverGuid.m_words;
	LegoU32* dest = p_guid.GetWords();
	for (LegoU32 i = 0; i < sizeOfArray(m_state.m_displayDriverGuid.m_words); i++, source++, dest++) {
		*dest = source->Get();
	}
}

// FUNCTION: LEGORACERS 0x0042f0b0
LegoU32 GameState::GetRegistryLanguageIndex()
{
	struct RegistryLanguageQuery {
		LegoU32 m_languageId;
		DWORD m_dataType;
		HKEY m_key;
		DWORD m_dataSize;
	};

	RegistryLanguageQuery query;
	query.m_languageId = 0;

	if (RegOpenKey(HKEY_LOCAL_MACHINE, "Software\\LEGO Media\\Games\\LEGO Racers\\0.90.000", &query.m_key) ==
		ERROR_SUCCESS) {
		query.m_dataType = REG_DWORD;
		query.m_dataSize = sizeof(query.m_languageId);

		if (RegQueryValueEx(
				query.m_key,
				"LangID",
				NULL,
				&query.m_dataType,
				(LPBYTE) &query.m_languageId,
				&query.m_dataSize
			) != ERROR_SUCCESS ||
			query.m_dataType != REG_DWORD) {
			query.m_languageId = 0;
		}

		RegCloseKey(query.m_key);
	}

	switch (query.m_languageId) {
	case 0x0006:
		return 5;
	case 0x0007:
		return 3;
	case 0x0009:
		return 0;
	case 0x000a:
		return 1;
	case 0x000b:
		return 10;
	case 0x0010:
		return 4;
	case 0x0013:
		return 8;
	case 0x0014:
		return 7;
	case 0x001d:
		return 6;
	case 0x040c:
		return 2;
	default:
		return 0;
	}
}

// FUNCTION: LEGORACERS 0x0042f1e0
LegoU8 GameState::GetPartUnlockFlags() const
{
	return m_state.m_partUnlockFlags;
}

// FUNCTION: LEGORACERS 0x0042f1f0
LegoU8 GameState::GetUnlockedCircuits() const
{
	return m_state.m_unlockedCircuits | 1;
}

// FUNCTION: LEGORACERS 0x0042f200
void GameState::UnlockParts(LegoU8 p_flags)
{
	m_dirty = 1;
	m_state.m_partUnlockFlags |= p_flags;
}

// FUNCTION: LEGORACERS 0x0042f220
void GameState::UnlockCircuits(LegoU8 p_flags)
{
	m_dirty = 1;
	m_state.m_unlockedCircuits |= p_flags;
}

// FUNCTION: LEGORACERS 0x0042f240
LegoU16 GameState::GetUnlockedRaces() const
{
	return m_state.m_unlockedRaces;
}

// FUNCTION: LEGORACERS 0x0042f250
LegoBool32 GameState::UnlockRace(LegoU32 p_mask)
{
	LegoBool32 result = FALSE;

	if (!static_cast<LegoU16>(m_state.m_unlockedRaces & p_mask)) {
		result = TRUE;
		m_state.m_unlockedRaces |= p_mask;
		m_dirty = result;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0042f280
LegoBool32 GameState::AreAllRacesUnlocked() const
{
	return m_state.m_unlockedRaces == 0x0fff;
}

// FUNCTION: LEGORACERS 0x0042f290
LegoU32 GameState::GetBestTime(LegoU32 p_raceIndex, LegoBool32 p_alternate, GolString* p_string) const
{
	if (p_raceIndex < 13 || (p_raceIndex -= 13) < 13) {
		LegoBool32 alternate = p_alternate;
		LegoU32 result;
		if (!alternate) {
			result = m_state.m_unk0x28[p_raceIndex];
			ActiveRecordBuffer::CopyBufferToString(p_string, m_state.m_unk0x90[p_raceIndex], 14);
		}
		else {
			result = m_state.m_unk0x5c[p_raceIndex];
			ActiveRecordBuffer::CopyBufferToString(p_string, m_state.m_unk0x1fc[p_raceIndex], 14);
		}

		return result;
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x0042f310
LegoBool32 GameState::SetBestTime(LegoU32 p_raceIndex, LegoBool32 p_alternate, LegoU32 p_time, GolString* p_string)
{
	if (p_raceIndex >= 13) {
		p_raceIndex -= 13;
		if (p_raceIndex >= 13) {
			return FALSE;
		}
	}

	LegoU32 current;
	if (!p_alternate) {
		current = m_state.m_unk0x28[p_raceIndex];
	}
	else {
		current = m_state.m_unk0x5c[p_raceIndex];
	}

	if (current && p_time >= current) {
		return FALSE;
	}

	if (!p_alternate) {
		m_state.m_unk0x28[p_raceIndex] = p_time;
		ActiveRecordBuffer::CopyStringToBuffer(p_string, m_state.m_unk0x90[p_raceIndex], 14);
	}
	else {
		m_state.m_unk0x5c[p_raceIndex] = p_time;
		ActiveRecordBuffer::CopyStringToBuffer(p_string, m_state.m_unk0x1fc[p_raceIndex], 14);
	}

	m_dirty = 1;
	return TRUE;
}
