#include "input/inputdevice.h"

#include "golerror.h"

#include <dinput.h>
#include <string.h>

DECOMP_SIZE_ASSERT(InputDevice, 0x9c)
DECOMP_SIZE_ASSERT(InputDevice::DirectionalTrigger, 0x24)

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
	::memset(&m_directionalTriggers, 0, sizeof(m_directionalTriggers));
	m_stringBufferLength = 0;
	m_inputManager = NULL;
	m_buttonCount = 0;
	m_axisCount = 0;
	m_directionalTriggerCount = 0;
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

	for (i = 0; i < m_directionalTriggerCount; i++) {
		m_directionalTriggers[i]->DispatchDelayedStateChange(m_currentTimeMs, this);
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

// FUNCTION: LEGORACERS 0x0044bb60
void InputDevice::DispatchAxisButtonStateChanges(LegoFloat p_newValue, LegoFloat p_oldValue, LegoU32 p_positiveEvent)
{
	LegoU32 originalEvent = p_positiveEvent;
	LegoS32 pressedEvent = -1;
	LegoS32 releasedEvent = -1;
	p_positiveEvent &= c_keyCodeMask;

	if (p_newValue > 0.0f) {
		if (p_oldValue <= 0.0f) {
			pressedEvent = p_positiveEvent;
		}

		if (GetButtonState(originalEvent + 1)) {
			releasedEvent = p_positiveEvent + 1;
		}
	}
	else if (p_newValue < 0.0f) {
		if (p_oldValue >= 0.0f) {
			pressedEvent = p_positiveEvent + 1;
		}

		if (GetButtonState(originalEvent)) {
			releasedEvent = p_positiveEvent;
		}
	}
	else if (GetAxisValue((p_positiveEvent >> 1) + 1) > 0.0f) {
		releasedEvent = p_positiveEvent;
	}
	else {
		LegoU32 axisIndex = (p_positiveEvent >> 1) + 1;

		if (GetAxisValue(axisIndex) >= 0.0f) {
			return;
		}

		releasedEvent = p_positiveEvent + 1;
	}

	if (pressedEvent >= 0) {
		SetButtonState(pressedEvent | c_sourceJoystick2, TRUE, TRUE);
	}

	if (releasedEvent >= 0) {
		SetButtonState(releasedEvent | c_sourceJoystick2, FALSE, TRUE);
	}
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

	for (i = 0; i < m_directionalTriggerCount; i++) {
		m_directionalTriggers[i]->DispatchRepeatEvent(m_currentTimeMs, this);
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
void InputDevice::AddDirectionalTrigger(DirectionalTrigger* p_trigger)
{
	m_directionalTriggers[m_directionalTriggerCount] = p_trigger;
	m_directionalTriggerCount += 1;
}

// FUNCTION: LEGORACERS 0x0044be10
LegoBool32 InputDevice::RemoveDirectionalTrigger(DirectionalTrigger* p_trigger)
{
	LegoS32 i;

	for (i = 0; i < m_directionalTriggerCount; i++) {
		if (m_directionalTriggers[i] == p_trigger) {
			while (i < (LegoS32) sizeOfArray(m_directionalTriggers)) {
				m_directionalTriggers[i] = m_directionalTriggers[i + 1];
				i++;
			}

			m_directionalTriggerCount -= 1;
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

// FUNCTION: LEGORACERS 0x0044c100
InputDevice::DirectionalTrigger::DirectionalTrigger()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0044c140
InputDevice::DirectionalTrigger::~DirectionalTrigger()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0044c150
void InputDevice::DirectionalTrigger::Reset()
{
	m_active = FALSE;
	m_currentDirection = 0;
	m_nextDispatchTimeMs = 0;

	memset(&m_directionEvents, 0, sizeof(m_directionEvents));
}

// FUNCTION: LEGORACERS 0x0044c170
LegoBool32 InputDevice::DirectionalTrigger::Configure(
	LegoU32 p_sourceId,
	LegoU32 p_directionEvent1,
	LegoU32 p_directionEvent2,
	LegoU32 p_directionEvent3,
	LegoU32 p_directionEvent4
)
{
	m_sourceId = p_sourceId;
	m_directionEvents[0] = p_directionEvent1;
	m_directionEvents[1] = p_directionEvent2;
	m_directionEvents[2] = p_directionEvent3;
	m_directionEvents[3] = p_directionEvent4;
	m_active = TRUE;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0044c1a0
LegoBool32 InputDevice::DirectionalTrigger::Destroy()
{
	if (m_active) {
		Reset();
	}

	return !m_active;
}

// FUNCTION: LEGORACERS 0x0044c1c0
LegoBool32 InputDevice::DirectionalTrigger::DispatchDelayedStateChange(LegoU32 p_time, InputDevice* p_device)
{
	if (m_nextDispatchTimeMs) {
		if (m_nextDispatchTimeMs > p_time) {
			return TRUE;
		}

		LegoS32 previousDirection = m_currentDirection;
		m_nextDispatchTimeMs = 0;
		m_currentDirection = GetPressedDirection(p_device);

		if (p_device->m_callback) {
			if (previousDirection) {
				p_device->m_callback->OnKeyUp(*p_device, MakeDirectionEvent(previousDirection), p_time);
			}

			if (m_currentDirection) {
				p_device->m_callback->OnKeyDown(*p_device, MakeDirectionEvent(m_currentDirection), p_time);
			}
		}
	}
	else if (m_currentDirection != GetPressedDirection(p_device)) {
		m_nextDispatchTimeMs = p_time + c_directionChangeDelayMs;
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0044c260
LegoS32 InputDevice::DirectionalTrigger::WrapDirectionIndex(LegoS32 p_index)
{
	if (p_index >= 0) {
		p_index %= c_directionCount;
	}
	else {
		p_index += c_directionCount;
	}

	return p_index;
}

// FUNCTION: LEGORACERS 0x0044c280
LegoBool32 InputDevice::DirectionalTrigger::DispatchRepeatEvent(LegoU32 p_time, InputDevice* p_device)
{
	if (m_currentDirection) {
		Callback* callback = p_device->m_callback;
		callback->OnKeyRepeat(*p_device, MakeDirectionEvent(m_currentDirection), p_time);
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0044c2d0
LegoS32 InputDevice::DirectionalTrigger::GetPressedDirection(InputDevice* p_device)
{
	LegoS32 direction = 0;
	LegoS32 i;

	for (i = 0; i < c_directionCount; i++) {
		if (p_device->GetButtonState(m_directionEvents[i])) {
			direction = (i * 2) + 1;

			if (p_device->GetButtonState(m_directionEvents[WrapDirectionIndex(i - 1)])) {
				direction--;
			}

			if (p_device->GetButtonState(m_directionEvents[WrapDirectionIndex(i + 1)])) {
				direction++;
			}
		}
	}

	return direction;
}

// FUNCTION: LEGORACERS 0x0044c380
LegoS32 InputDevice::DirectionalTrigger::GetDirectionForEvent(InputDevice* p_device, LegoU32 p_event)
{
	LegoS32 direction = 0;
	LegoS32 i;

	for (i = 0; i < c_directionCount; i++) {
		if (p_event == m_directionEvents[i]) {
			direction = (i * 2) + 1;

			if (p_device->GetButtonState(m_directionEvents[WrapDirectionIndex(i - 1)])) {
				direction--;
			}

			if (p_device->GetButtonState(m_directionEvents[WrapDirectionIndex(i + 1)])) {
				direction++;
			}
		}
	}

	return direction;
}

// FUNCTION: LEGORACERS 0x0044c430
LegoBool32 InputDevice::DirectionalTrigger::OnKeyDown(InputDevice& p_device, undefined4 p_keyCode, undefined4 p_time)
{
	LegoS32 direction = GetDirectionForEvent(&p_device, p_keyCode);

	if (direction && direction != m_currentDirection) {
		if (p_device.m_callback) {
			p_device.m_callback->OnKeyUp(p_device, MakeDirectionEvent(m_currentDirection), p_time);
			p_device.m_callback->OnKeyDown(p_device, MakeDirectionEvent(direction), p_time);
		}

		m_currentDirection = direction;
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0044c4a0
LegoBool32 InputDevice::DirectionalTrigger::OnKeyUp(InputDevice& p_device, undefined4, undefined4 p_time)
{
	LegoS32 direction = GetPressedDirection(&p_device);

	if (direction != m_currentDirection && p_device.m_callback) {
		if (m_currentDirection) {
			p_device.m_callback->OnKeyUp(p_device, MakeDirectionEvent(m_currentDirection), p_time);
		}

		if (direction) {
			p_device.m_callback->OnKeyDown(p_device, MakeDirectionEvent(direction), p_time);
		}

		m_currentDirection = direction;
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0044c510
LegoBool32 InputDevice::DirectionalTrigger::OnKeyRepeat(InputDevice& p_device, undefined4 p_keyCode, undefined4 p_time)
{
	LegoS32 direction = GetDirectionForEvent(&p_device, p_keyCode);

	if (direction == m_currentDirection && p_device.m_callback) {
		p_device.m_callback->OnKeyRepeat(p_device, MakeDirectionEvent(m_currentDirection), p_time);
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00451080 FOLDED
LegoS32 InputDevice::GetAxisCount()
{
	return 16;
}
