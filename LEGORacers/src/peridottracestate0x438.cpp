#include "golhashtable.h"
#include "golstream.h"
#include "input/inputdevice.h"
#include "input/inputmanager.h"
#include "input/joystickdevice.h"
#include "input/keyboarddevice.h"
#include "peridottrace0x4e0.h"

#include <string.h>
#include <windows.h>

DECOMP_SIZE_ASSERT(PeridotTraceState0x438, 0x438)
DECOMP_SIZE_ASSERT(DisplayDriverGuid::SerializedWord, 0x04)
DECOMP_SIZE_ASSERT(DisplayDriverGuid::Serialized, 0x10)
DECOMP_SIZE_ASSERT(PeridotTraceInputBindingEntry, 0x28)
DECOMP_SIZE_ASSERT(PeridotTraceInputBindingPlayerState, 0x04)
DECOMP_SIZE_ASSERT(PeridotTraceInputBindingState, 0xd0)
DECOMP_SIZE_ASSERT(PeridotTracePersistentState, 0x42c)

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
PeridotTraceState0x438::PeridotTraceState0x438()
{
	Initialize();
}

// FUNCTION: LEGORACERS 0x0042e890
PeridotTraceState0x438::~PeridotTraceState0x438()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0042e8a0
void PeridotTraceState0x438::Initialize()
{
	m_unk0x00 = 0;
	m_unk0x04 = 0xffffffff;

	m_state.Clear();
	m_state.m_unk0x0c = 5;
	m_state.m_unk0x1e = 0x80;
	m_state.m_unk0x1f = 0xff;
	m_state.m_unk0x20 = 0xff;
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
void PeridotTraceState0x438::Initialize(InputManager* p_inputManager)
{
	Reset();
	m_inputManager = p_inputManager;
	InitializeInputBindings(p_inputManager);
	FUN_0042f020(g_displayDriverGuid);
	m_unk0x00 = 0;
}

// FUNCTION: LEGORACERS 0x0042e950
void PeridotTraceState0x438::Reset()
{
	Initialize();
}

// FUNCTION: LEGORACERS 0x0042e960
void PeridotTraceState0x438::InitializeInputBindings(InputManager* p_inputManager)
{
	LegoS32 i;
	LegoS32 j;

	for (i = 0; i < 2; i++) {
		PeridotTraceInputBindingEntry* entry = &m_state.m_inputBindings.m_entries[i];
		JoystickInputDevice* joystick = p_inputManager->FindJoystickByDeviceId(i);

		if (joystick == NULL) {
			entry->m_deviceType = 4;
			entry->m_deviceSubType = 2;
		}
		else {
			entry->m_deviceType = joystick->GetDeviceType();
			entry->m_deviceSubType = joystick->GetDeviceSubType();
		}

		entry->m_unk0x02 = i;
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

		PeridotTraceInputBindingEntry* entry = &m_state.m_inputBindings.m_entries[i + 2];
		entry->m_deviceType = 3;
		entry->m_unk0x02 = 0;

		for (j = 0; j < sizeOfArray(entry->m_events); j++) {
			entry->m_events[j] = g_keyboardInputBindingEvents[i][j];
		}
	}
}

// STUB: LEGORACERS 0x0042ea50
void PeridotTraceState0x438::FUN_0042ea50(LegoU32 p_playerIndex)
{
	LegoU32 otherPlayerIndex = p_playerIndex == 0 ? 1 : 0;
	LegoU32 otherEntryIndex = m_state.m_inputBindings.GetSelectedEntryIndex(otherPlayerIndex);

	for (LegoU32 i = 0; i < c_joystickBindingCount; i++) {
		if (otherEntryIndex != i) {
			PeridotTraceInputBindingEntry* entry = &m_state.m_inputBindings.m_entries[i];
			if (m_inputManager->FindJoystickByDeviceId(entry->m_unk0x02) != NULL) {
				FUN_0042eb20(p_playerIndex, i);
				return;
			}
		}
	}

	FUN_0042eb20(p_playerIndex, FUN_0042eac0(p_playerIndex));
}

// FUNCTION: LEGORACERS 0x0042eac0
LegoU32 PeridotTraceState0x438::FUN_0042eac0(LegoU32 p_playerIndex)
{
	LegoU32 otherPlayerIndex = p_playerIndex == 0 ? 1 : 0;
	LegoU32 otherEntryIndex = m_state.m_inputBindings.GetSelectedEntryIndex(otherPlayerIndex);

	if (p_playerIndex && otherEntryIndex < c_joystickBindingCount) {
		PeridotTraceInputBindingEntry* entry = &m_state.m_inputBindings.m_entries[otherEntryIndex];
		LegoU32 deviceId = entry->m_unk0x02;
		JoystickInputDevice* joystick = m_inputManager->FindJoystickByDeviceId(deviceId);

		if (joystick != NULL && static_cast<LegoU32>(joystick->GetButtonCountFast()) >= c_inputBindingEventCount) {
			return c_keyboardBindingStart;
		}
	}

	LegoU32 result = otherEntryIndex == c_keyboardBindingStart;
	return c_keyboardBindingStart + result;
}

// FUNCTION: LEGORACERS 0x0042eb20
void PeridotTraceState0x438::FUN_0042eb20(LegoU32 p_playerIndex, LegoU32 p_entryIndex)
{
	LegoU32 otherPlayerIndex = p_playerIndex == 0 ? 1 : 0;

	m_unk0x00 = 1;
	m_state.m_inputBindings.SetSelectedEntryIndex(p_playerIndex, static_cast<LegoU8>(p_entryIndex));

	if (p_entryIndex == m_state.m_inputBindings.GetSelectedEntryIndex(otherPlayerIndex)) {
		FUN_0042ea50(otherPlayerIndex);
	}
}

// STUB: LEGORACERS 0x0042eb60
void PeridotTraceState0x438::FUN_0042eb60(PeridotTrace0x4a8* p_trace, undefined4 p_index)
{
	PeridotTracePersistentState state;
	LegoU32 i;

	m_unk0x04 = p_index;
	m_unk0x00 = 0;
	p_trace->FUN_00442a00(&state);

	m_state.m_unk0x0c = state.m_unk0x0c;
	m_state.m_displayDriverGuid = state.m_displayDriverGuid;
	m_state.m_unk0x1d = state.m_unk0x1d;
	m_state.m_unk0x1e = state.m_unk0x1e;
	m_state.m_unk0x1f = state.m_unk0x1f;
	m_state.m_unk0x20 = state.m_unk0x20;
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

		sourceBindingEntry += sizeof(PeridotTraceInputBindingEntry);
		destBindingEntry += sizeof(PeridotTraceInputBindingEntry);
	}

	PeridotTraceInputBindingPlayerState* sourcePlayer = state.m_inputBindings.m_players;
	PeridotTraceInputBindingPlayerState* destPlayer = m_state.m_inputBindings.m_players;
	LegoU8* selectedEntryIndex = &destPlayer->m_selectedEntryIndex;
	for (i = 0; i < c_joystickBindingCount; i++) {
		*destPlayer = *sourcePlayer;

		PeridotTraceInputBindingEntry* entry = &m_state.m_inputBindings.m_entries[*selectedEntryIndex];

		if (entry->m_deviceType == c_joystickDeviceType &&
			m_inputManager->FindJoystickByDeviceId(entry->m_unk0x02) == NULL) {
			FUN_0042ea50(i);
		}

		sourcePlayer++;
		destPlayer++;
		selectedEntryIndex += sizeof(PeridotTraceInputBindingPlayerState);
	}

	m_state.m_unk0x24 = state.m_unk0x24;
	m_state.m_unk0x25 = state.m_unk0x25;
	m_state.m_unk0x26 = state.m_unk0x26;

	for (i = 0; i < sizeOfArray(m_state.m_unk0x28); i++) {
		m_state.m_unk0x28[i] = state.m_unk0x28[i];
		m_state.m_unk0x5c[i] = state.m_unk0x5c[i];
		::memcpy(m_state.m_unk0x90[i], state.m_unk0x90[i], sizeof(m_state.m_unk0x90[i]));
		::memcpy(m_state.m_unk0x1fc[i], state.m_unk0x1fc[i], sizeof(m_state.m_unk0x1fc[i]));
	}
}

// FUNCTION: LEGORACERS 0x0042ed10
LegoBool32 PeridotTraceState0x438::FUN_0042ed10(LegoU32 p_entryIndex, LegoU32 p_event)
{
	PeridotTraceInputBindingEntry* entry = &m_state.m_inputBindings.m_entries[p_entryIndex];
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
LegoU32 PeridotTraceState0x438::FUN_0042ed80(LegoU32 p_playerIndex, LegoU32 p_entryIndex, LegoU32 p_eventIndex)
{
	LegoU32 event = m_state.m_inputBindings.m_entries[p_entryIndex].m_events[p_eventIndex];

	if (event) {
		return event;
	}

	event = FUN_0042ef00(p_entryIndex, p_eventIndex);
	if (event) {
		if (!FUN_0042ed10(p_entryIndex, event)) {
			FUN_0042ee70(p_entryIndex, p_eventIndex, event);
			return event;
		}
	}

	if (p_entryIndex < 1 && p_eventIndex > 1) {
		LegoU32 fallbackEntryIndex = FUN_0042eac0(p_playerIndex);
		return m_state.m_inputBindings.m_entries[fallbackEntryIndex].m_events[p_eventIndex];
	}

	return 0;
}

// STUB: LEGORACERS 0x0042ee10
void PeridotTraceState0x438::FUN_0042ee10(
	LegoU32 p_playerIndex,
	LegoU32 p_entryIndex,
	PeridotTraceInputBindingEntry* p_entry
)
{
	PeridotTraceInputBindingEntry* source = &m_state.m_inputBindings.m_entries[p_entryIndex];
	LegoU32 i;

	p_entry->m_deviceType = source->m_deviceType;
	p_entry->m_deviceSubType = source->m_deviceSubType;
	p_entry->m_unk0x02 = source->m_unk0x02;

	for (i = 0; i < c_inputBindingEventCount; i++) {
		p_entry->m_events[i] = FUN_0042ed80(p_playerIndex, p_entryIndex, i);
	}
}

// STUB: LEGORACERS 0x0042ee70
void PeridotTraceState0x438::FUN_0042ee70(LegoU32 p_entryIndex, LegoU32 p_eventIndex, LegoU32 p_event)
{
	PeridotTraceInputBindingEntry* entry = &m_state.m_inputBindings.m_entries[p_entryIndex];
	LegoU32 i;
	LegoU32 j;

	if (entry->m_events[p_eventIndex] == p_event) {
		return;
	}

	if ((p_event & InputDevice::c_sourceMask) != InputDevice::c_sourceKeyboard) {
		for (i = 0; i < c_inputBindingEventCount; i++) {
			if (entry->m_events[i] == p_event) {
				entry->m_events[i] = 0;
			}
		}
	}
	else {
		for (i = 0; i < c_inputBindingEntryCount; i++) {
			PeridotTraceInputBindingEntry* otherEntry = &m_state.m_inputBindings.m_entries[i];

			for (j = 0; j < c_inputBindingEventCount; j++) {
				if (otherEntry->m_events[j] == p_event) {
					otherEntry->m_events[j] = 0;
				}
			}
		}
	}

	entry->m_events[p_eventIndex] = p_event;
	m_unk0x00 = 1;
}

// STUB: LEGORACERS 0x0042ef00
LegoU32 PeridotTraceState0x438::FUN_0042ef00(LegoU32 p_entryIndex, LegoU32 p_eventIndex)
{
	PeridotTraceInputBindingEntry* entry = &m_state.m_inputBindings.m_entries[p_entryIndex];
	LegoU32 eventIndex = p_eventIndex;
	LegoU32 result = 0;

	if (entry->m_deviceType == c_joystickDeviceType) {
		if (eventIndex < 2 && entry->m_deviceSubType != c_axisJoystickDeviceSubType) {
			return result;
		}

		JoystickInputDevice* joystick = m_inputManager->FindJoystickByDeviceId(entry->m_unk0x02);
		LegoU32 buttonIndex = eventIndex - 2;

		if (joystick != NULL && static_cast<LegoU32>(joystick->GetButtonCountFast()) > buttonIndex) {
			result = InputDevice::c_sourceJoystickButton | buttonIndex;
		}
	}
	else if (p_entryIndex >= c_keyboardBindingStart) {
		result = g_keyboardInputBindingEvents[p_entryIndex - c_keyboardBindingStart][eventIndex];
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0042ef80
void PeridotTraceState0x438::FUN_0042ef80(PeridotTrace0x4a8* p_trace)
{
	p_trace->FUN_00442c20(&m_state);
}

// FUNCTION: LEGORACERS 0x0042ef90
void PeridotTraceState0x438::SetLanguageResourcePath()
{
	LegoChar path[24];

	::strcpy(path, "MENUDATA\\");
	::strcat(path, g_menuLanguageDirectories[m_state.m_languageIndex]);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString(path);
	}
}

// FUNCTION: LEGORACERS 0x0042f020
void PeridotTraceState0x438::FUN_0042f020(const DisplayDriverGuid& p_guid)
{
	const LegoU32* source = p_guid.GetWords();

	m_unk0x00 = 1;

	DisplayDriverGuid::SerializedWord* dest = m_state.m_displayDriverGuid.m_words;
	for (LegoU32 i = 0; i < sizeOfArray(m_state.m_displayDriverGuid.m_words); i++, source++, dest++) {
		dest->Set(*source);
	}
}

// FUNCTION: LEGORACERS 0x0042f060
void PeridotTraceState0x438::FUN_0042f060(DisplayDriverGuid& p_guid)
{
	const DisplayDriverGuid::SerializedWord* source = m_state.m_displayDriverGuid.m_words;
	LegoU32* dest = p_guid.GetWords();
	for (LegoU32 i = 0; i < sizeOfArray(m_state.m_displayDriverGuid.m_words); i++, source++, dest++) {
		*dest = source->Get();
	}
}

// FUNCTION: LEGORACERS 0x0042f0b0
LegoU32 PeridotTraceState0x438::GetRegistryLanguageIndex()
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

// FUNCTION: LEGORACERS 0x0042f1f0
LegoU8 PeridotTraceState0x438::FUN_0042f1f0() const
{
	return m_state.m_unk0x25 | 1;
}

// FUNCTION: LEGORACERS 0x0042f200
void PeridotTraceState0x438::FUN_0042f200(LegoU8 p_unk0x04)
{
	m_unk0x00 = 1;
	m_state.m_unk0x24 |= p_unk0x04;
}

// FUNCTION: LEGORACERS 0x0042f250
LegoBool32 PeridotTraceState0x438::FUN_0042f250(LegoU32 p_unk0x04)
{
	LegoBool32 result = FALSE;

	if (!static_cast<LegoU16>(m_state.m_unk0x26 & p_unk0x04)) {
		result = TRUE;
		m_state.m_unk0x26 |= p_unk0x04;
		m_unk0x00 = result;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0042f280
LegoBool32 PeridotTraceState0x438::FUN_0042f280() const
{
	return m_state.m_unk0x26 == 0x0fff;
}

// FUNCTION: LEGORACERS 0x0042f310
LegoBool32 PeridotTraceState0x438::FUN_0042f310(
	LegoU32 p_unk0x04,
	LegoBool32 p_unk0x08,
	LegoU32 p_unk0x0c,
	GolString* p_string
)
{
	if (p_unk0x04 >= 13) {
		p_unk0x04 -= 13;
		if (p_unk0x04 >= 13) {
			return FALSE;
		}
	}

	LegoU32 current;
	if (!p_unk0x08) {
		current = m_state.m_unk0x28[p_unk0x04];
	}
	else {
		current = m_state.m_unk0x5c[p_unk0x04];
	}

	if (current && p_unk0x0c >= current) {
		return FALSE;
	}

	if (!p_unk0x08) {
		m_state.m_unk0x28[p_unk0x04] = p_unk0x0c;
		PeridotTraceBuffer0x250::CopyStringToBuffer(p_string, m_state.m_unk0x90[p_unk0x04], 14);
	}
	else {
		m_state.m_unk0x5c[p_unk0x04] = p_unk0x0c;
		PeridotTraceBuffer0x250::CopyStringToBuffer(p_string, m_state.m_unk0x1fc[p_unk0x04], 14);
	}

	m_unk0x00 = 1;
	return TRUE;
}
