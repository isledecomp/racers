#include "input/inputdevice.h"

#include "golerror.h"

#include <dinput.h>
#include <string.h>

DECOMP_SIZE_ASSERT(InputDevice, 0x9c)

// GLOBAL: LEGORACERS 0x004c7080
undefined2 g_defaultMapping[256];

// FUNCTION: LEGORACERS 0x0044b8f0
InputDevice::InputDevice()
{
	LegoU16 i;
	undefined2* writePtr;

	for (i = 0, writePtr = g_defaultMapping; i < sizeOfArray(g_defaultMapping); i++, writePtr++) {
		*writePtr = i;
	}

	Init();
}

// FUNCTION: LEGORACERS 0x0044b940
InputDevice::~InputDevice()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0044b950
void InputDevice::Init()
{
	m_forceFeedbackAvailable = 0;
	m_axisButtonEventsEnabled = 0;
	m_repeatEnabled = 0;
	m_acquired = 0;
	m_created = FALSE;
	m_axisMapping = g_defaultMapping;
	m_buttonMapping = g_defaultMapping;
	::memset(&m_timedTriggers, 0, sizeof(m_timedTriggers));
	m_stringBufferLength = 0;
	m_inputManager = NULL;
	m_buttonCount = 0;
	m_axisCount = 0;
	m_timedTriggerCount = 0;
	m_deviceType = 0;
	m_deviceSubType = 0;
	m_axisMask = 0;
	m_deviceId = 0;
	m_currentTimeMs = 0;
	m_repeatDelayMs = 0;
	m_repeatTimerMs = 0;
	m_deviceName[0] = '\0';
	m_stringBuffer = NULL;
	m_callback = NULL;
}

// FUNCTION: LEGORACERS 0x0044b9c0
LegoBool32 InputDevice::Destroy()
{
	if (!m_created) {
		return true;
	}

	Init();
	return !m_created;
}

// FUNCTION: LEGORACERS 0x0044b9f0
void InputDevice::ReleasePressedButtons()
{
	LegoU32 flag = 0;

	switch (m_deviceType) {
	case DIDEVTYPE_MOUSE:
		flag = c_sourceMouse;
		break;
	case DIDEVTYPE_KEYBOARD:
		flag = c_sourceKeyboard;
		break;
	case DIDEVTYPE_JOYSTICK:
		flag = c_sourceJoystick1;
		break;
	}

	LegoS32 i;
	for (i = 0; i < GetButtonCount(); i++) {
		if (GetButtonState(i | flag)) {
			SetButtonState(i | flag, FALSE, TRUE);
		}
	}
}

// FUNCTION: LEGORACERS 0x0044ba60
undefined4 InputDevice::Poll(LegoS32 p_elapsedMs)
{
	LegoS32 i;

	m_currentTimeMs += p_elapsedMs;

	for (i = 0; i < m_timedTriggerCount; i++) {
		m_timedTriggers[i]->FUN_0044c1c0(m_currentTimeMs, this);
	}

	DispatchRepeatEvents(p_elapsedMs);
	return 0;
}

// FUNCTION: LEGORACERS 0x0044bab0
void InputDevice::SetRepeatDelays(LegoS32 p_repeatDelayMs, LegoS32 p_initialRepeatDelayMs)
{
	m_initialRepeatDelayMs = p_initialRepeatDelayMs;
	m_repeatDelayMs = p_repeatDelayMs;
	m_repeatEnabled = 1;
	m_repeatTimerMs = p_initialRepeatDelayMs;
}

// FUNCTION: LEGORACERS 0x0044bad0
void InputDevice::SetDeviceName(const LegoChar* p_deviceName)
{
	strncpy(m_deviceName, p_deviceName, sizeOfArray(m_deviceName) - 1);
	m_deviceName[sizeOfArray(m_deviceName) - 1] = '\0';
}

// FUNCTION: LEGORACERS 0x0044baf0
void InputDevice::SetEventMappings(undefined2* p_buttonMapping, undefined2* p_axisMapping)
{
	if (p_buttonMapping == NULL) {
		p_buttonMapping = g_defaultMapping;
	}

	m_buttonMapping = p_buttonMapping;

	if (p_axisMapping == NULL) {
		p_axisMapping = g_defaultMapping;
	}

	m_axisMapping = p_axisMapping;
}

// FUNCTION: LEGORACERS 0x0044bb20
undefined2* InputDevice::GetCustomButtonMapping()
{
	if (m_buttonMapping == g_defaultMapping) {
		return NULL;
	}
	return m_buttonMapping;
}

// FUNCTION: LEGORACERS 0x0044bb40
undefined2* InputDevice::GetCustomAxisMapping()
{
	if (m_axisMapping == g_defaultMapping) {
		return NULL;
	}
	return m_axisMapping;
}

// STUB: LEGORACERS 0x0044bb60
void InputDevice::DispatchAxisButtonStateChanges(float, float, undefined4)
{
	// TODO
	STUB(0x0044bb60);
}

// FUNCTION: LEGORACERS 0x0044bc60
void InputDevice::DispatchRepeatEvents(LegoS32 p_elapsedMs)
{
	LegoU32 source = 0;

	m_repeatTimerMs -= p_elapsedMs;
	if (!m_repeatEnabled || m_repeatTimerMs > 0 || !m_callback) {
		return;
	}

	switch (m_deviceType) {
	case DIDEVTYPE_MOUSE:
		source = c_sourceMouse;
		break;
	case DIDEVTYPE_KEYBOARD:
		source = c_sourceKeyboard;
		break;
	case DIDEVTYPE_JOYSTICK:
		source = c_sourceJoystick1;
		break;
	}

	LegoS32 repeatCount = 0;
	LegoS32 i;
	for (i = 0; i < GetButtonCount(); i++) {
		if (GetButtonState(i | source)) {
			undefined4 keyCode = source | m_buttonMapping[i];
			m_callback->OnKeyRepeat(*this, keyCode, m_currentTimeMs);
			repeatCount++;
		}
	}

	if (m_axisButtonEventsEnabled) {
		for (i = 0; i < (LegoS32) (GetAxisCount() << 1); i++) {
			if (GetButtonState(i | c_sourceJoystick2)) {
				undefined4 keyCode = c_sourceJoystick2 | m_axisMapping[i];
				m_callback->OnKeyRepeat(*this, keyCode, m_currentTimeMs);
				repeatCount++;
			}
		}
	}

	m_repeatTimerMs = repeatCount ? m_repeatDelayMs : m_initialRepeatDelayMs;

	for (i = 0; i < m_timedTriggerCount; i++) {
		m_timedTriggers[i]->FUN_0044c280(m_currentTimeMs, this);
	}
}

// FUNCTION: LEGORACERS 0x0044bda0
void InputDevice::ResetAxisValues()
{
	LegoU32 flag = 0x1;
	LegoU32 bits = m_axisMask;
	LegoS32 i;

	for (i = 16; i != 0; flag <<= 1, i--) {
		if (bits & flag) {
			SetAxisValue(flag, 0.0f);
		}
	}
}

// FUNCTION: LEGORACERS 0x0044bdd0
void InputDevice::SetButtonState(undefined4, LegoU8 p_state, LegoBool32)
{
	if (p_state) {
		m_repeatTimerMs = m_initialRepeatDelayMs;
	}
}

// FUNCTION: LEGORACERS 0x0044bdf0
void InputDevice::AddTimedTrigger(TimedTrigger* p_trigger)
{
	m_timedTriggers[m_timedTriggerCount] = p_trigger;
	m_timedTriggerCount += 1;
}

// FUNCTION: LEGORACERS 0x0044be10
LegoBool32 InputDevice::RemoveTimedTrigger(TimedTrigger* p_trigger)
{
	LegoS32 i;

	for (i = 0; i < m_timedTriggerCount; i++) {
		if (m_timedTriggers[i] == p_trigger) {
			while (i < (LegoS32) sizeOfArray(m_timedTriggers)) {
				m_timedTriggers[i] = m_timedTriggers[i + 1];
				i++;
			}

			m_timedTriggerCount -= 1;
			return TRUE;
		}
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x0044be70
LegoS16 InputDevice::StoreString(const LegoChar* p_str)
{
	wchar_t* ptr = m_stringBuffer;

	if (m_stringBuffer == NULL) {
		return -1;
	}

	while (ptr[0] != L'\0' || ptr[1] != L'\0') {
		ptr += 1;
	}

	if (m_stringBuffer != ptr) {
		ptr += 1;
	}

	LegoS16 result = ((LegoU16) ((LegoChar*) ptr - (LegoChar*) m_stringBuffer)) / (sizeof(*ptr));

	while (*p_str != '\0') {
		*ptr++ = (LegoU8) *p_str++;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0044bed0
LegoS32 InputDevice::GetButtonCount()
{
	return sizeOfArray(g_defaultMapping);
}

// FUNCTION: LEGORACERS 0x0044bee0
const wchar_t* InputDevice::GetControlName(undefined4)
{
	return L"";
}

// FUNCTION: LEGORACERS 0x0044bef0
undefined4 InputDevice::IsAcquired()
{
	return m_acquired;
}

// FUNCTION: LEGORACERS 0x0044bf00
undefined4 InputDevice::Acquire()
{
	m_acquired = 1;
	return m_acquired;
}

// FUNCTION: LEGORACERS 0x0044bf10
undefined4 InputDevice::Unacquire()
{
	m_acquired = 0;
	return m_acquired;
}

// STUB: LEGORACERS 0x0044c1c0
LegoBool32 InputDevice::TimedTrigger::FUN_0044c1c0(LegoS32, InputDevice*)
{
	STUB(0x0044c1c0);
	return TRUE;
}

// STUB: LEGORACERS 0x0044c280
LegoBool32 InputDevice::TimedTrigger::FUN_0044c280(LegoS32, InputDevice*)
{
	STUB(0x0044c280);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00451080 FOLDED
LegoS32 InputDevice::GetAxisCount()
{
	return 16;
}
