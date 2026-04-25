#include "input/joystickdevice.h"

DECOMP_SIZE_ASSERT(JoystickInputDevice, 0x23c)

// FUNCTION: LEGORACERS 0x0044ea20
JoystickInputDevice::JoystickInputDevice()
{
	Init();
}

// FUNCTION: LEGORACERS 0x0044ea90
JoystickInputDevice::~JoystickInputDevice()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0044eae0
void JoystickInputDevice::Init()
{
	::memset(&m_joyState, 0, sizeof(m_joyState));
	::memset(&m_axisButtonStates, 0, sizeof(m_axisButtonStates));
	::memset(&m_axisValues, 0, sizeof(m_axisValues));
	DirectInputDevice::Init();
}

// FUNCTION: LEGORACERS 0x0044eb20
LegoBool32 JoystickInputDevice::CreateDevice(CreateDirectInputDeviceParams* p_params)
{
	Destroy();
	p_params->m_dataFormat = &c_dfDIJoystick2;

	if (DirectInputDevice::CreateDevice(p_params)) {
		HRESULT result1 = m_device->EnumObjects(StoreButtonNameCallback, this, DIDFT_PSHBUTTON | DIDFT_TGLBUTTON);
		HRESULT result2 = m_device->EnumObjects(StoreAxisNameCallback, this, DIDFT_RELAXIS | DIDFT_ABSAXIS);
		if (!TranslateDirectInputResult(result1) && !TranslateDirectInputResult(result2)) {
			SetDeadZonePercent(c_defaultDeadZonePercent);
			return m_created;
		}
		Destroy();
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x0044ebb0
BOOL JoystickInputDevice::StoreButtonNameCallback(LPCDIDEVICEOBJECTINSTANCE p_object, LPVOID p_context)
{
	JoystickInputDevice* joystick = static_cast<JoystickInputDevice*>(p_context);
	LegoU32 offset = p_object->dwOfs - DIJOFS_BUTTON0;

	joystick->m_buttonNameIndices[offset] = joystick->StoreString(p_object->tszName);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0044ebe0
BOOL JoystickInputDevice::StoreAxisNameCallback(LPCDIDEVICEOBJECTINSTANCE p_object, LPVOID p_context)
{
	JoystickInputDevice* joystick = static_cast<JoystickInputDevice*>(p_context);
	undefined4 mask = joystick->GetAxisMask(p_object->guidType);

	if (mask != 0) {
		undefined2 v = joystick->StoreString(p_object->tszName);
		DWORD offset = p_object->dwOfs >> 2;

		joystick->m_axisMask |= mask;
		joystick->m_axisNameIndices[offset] = v;
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0044ec30
void JoystickInputDevice::SetAxisRangeAndDeadZone(DWORD p_object, DWORD p_deadZone)
{
	undefined4 result = IsAcquired();
	if (result) {
		Unacquire();
	}

	DIPROPRANGE propRange;
	propRange.diph.dwSize = sizeof(propRange);
	propRange.diph.dwHeaderSize = sizeof(propRange.diph);
	propRange.diph.dwObj = p_object;
	propRange.diph.dwHow = DIPH_BYOFFSET;
	propRange.lMin = -1000;
	propRange.lMax = 1000;
	TranslateDirectInputResult(m_device->SetProperty(DIPROP_RANGE, &propRange.diph));

	DIPROPDWORD propDWord;
	propDWord.dwData = p_deadZone;
	propDWord.diph.dwSize = sizeof(propDWord);
	propDWord.diph.dwHeaderSize = sizeof(propDWord.diph);
	propDWord.diph.dwObj = p_object;
	propDWord.diph.dwHow = DIPH_BYOFFSET;
	TranslateDirectInputResult(m_device->SetProperty(DIPROP_DEADZONE, &propDWord.diph));

	if (result) {
		Acquire();
	}
}

// FUNCTION: LEGORACERS 0x0044ecf0
void JoystickInputDevice::SetDeadZonePercent(LegoU32 p_deadZonePercent)
{
	undefined4 result = IsAcquired();
	DWORD deadZone = p_deadZonePercent * c_directInputDeadZoneScale;
	if (result) {
		Unacquire();
	}

	if (m_axisMask & c_axisX) {
		SetAxisRangeAndDeadZone(DIJOFS_X, deadZone);
	}

	if (m_axisMask & c_axisY) {
		SetAxisRangeAndDeadZone(DIJOFS_Y, deadZone);
	}

	if (m_axisMask & c_axisZ) {
		SetAxisRangeAndDeadZone(DIJOFS_Z, deadZone);
	}

	if (m_axisMask & c_axisRx) {
		SetAxisRangeAndDeadZone(DIJOFS_RX, deadZone);
	}

	if (m_axisMask & c_axisRy) {
		SetAxisRangeAndDeadZone(DIJOFS_RY, deadZone);
	}

	if (m_axisMask & c_axisRz) {
		SetAxisRangeAndDeadZone(DIJOFS_RZ, deadZone);
	}

	if (m_axisMask & c_axisSlider) {
		SetAxisRangeAndDeadZone(DIJOFS_SLIDER(0), deadZone);
	}

	if (result) {
		Acquire();
	}
}

// FUNCTION: LEGORACERS 0x0044eda0
void JoystickInputDevice::UpdateAxisValues(const DIJOYSTATE2& p_state)
{
	if (m_axisMask & c_axisX) {
		m_axisValues[0] = static_cast<LegoFloat>(p_state.lX) / 1000.0f;
	}

	if (m_axisMask & c_axisY) {
		m_axisValues[1] = static_cast<LegoFloat>(p_state.lY) / 1000.0f;
	}

	if (m_axisMask & c_axisZ) {
		m_axisValues[2] = static_cast<LegoFloat>(p_state.lZ) / 1000.0f;
	}

	if (m_axisMask & c_axisRx) {
		m_axisValues[3] = static_cast<LegoFloat>(p_state.lRx) / 1000.0f;
	}

	if (m_axisMask & c_axisRy) {
		m_axisValues[4] = static_cast<LegoFloat>(p_state.lRy) / 1000.0f;
	}

	if (m_axisMask & c_axisRz) {
		m_axisValues[5] = static_cast<LegoFloat>(p_state.lRz) / 1000.0f;
	}

	if (m_axisMask & c_axisSlider) {
		m_axisValues[6] = static_cast<LegoFloat>(p_state.rglSlider[0]) / 1000.0f;
	}
}

// FUNCTION: LEGORACERS 0x0044ee40
void JoystickInputDevice::DispatchPolledAxisChanges(const DIJOYSTATE2& p_state)
{
	if (m_axisMask & c_axisX) {
		DispatchAxisButtonStateChanges(
			static_cast<LegoFloat>(p_state.lX) / 1000.0f,
			m_axisValues[0],
			c_sourceJoystick2 | 0x0
		);
	}

	if (m_axisMask & c_axisY) {
		DispatchAxisButtonStateChanges(
			static_cast<LegoFloat>(p_state.lY) / 1000.0f,
			m_axisValues[1],
			c_sourceJoystick2 | 0x2
		);
	}

	if (m_axisMask & c_axisZ) {
		DispatchAxisButtonStateChanges(
			static_cast<LegoFloat>(p_state.lZ) / 1000.0f,
			m_axisValues[2],
			c_sourceJoystick2 | 0x4
		);
	}

	if (m_axisMask & c_axisRx) {
		DispatchAxisButtonStateChanges(
			static_cast<LegoFloat>(p_state.lRx) / 1000.0f,
			m_axisValues[3],
			c_sourceJoystick2 | 0x6
		);
	}

	if (m_axisMask & c_axisRy) {
		DispatchAxisButtonStateChanges(
			static_cast<LegoFloat>(p_state.lRy) / 1000.0f,
			m_axisValues[4],
			c_sourceJoystick2 | 0x8
		);
	}

	if (m_axisMask & c_axisRz) {
		DispatchAxisButtonStateChanges(
			static_cast<LegoFloat>(p_state.lRz) / 1000.0f,
			m_axisValues[5],
			c_sourceJoystick2 | 0xa
		);
	}

	if (m_axisMask & c_axisSlider) {
		DispatchAxisButtonStateChanges(
			static_cast<LegoFloat>(p_state.rglSlider[0]) / 1000.0f,
			m_axisValues[6],
			c_sourceJoystick2 | 0xc
		);
	}
}

// FUNCTION: LEGORACERS 0x0044ef60
void JoystickInputDevice::DispatchPolledStateChanges(const DIJOYSTATE2& p_state)
{
	if (m_callback != NULL) {
		for (LegoS32 i = 0; i < m_buttonCount; i++) {
			if (p_state.rgbButtons[i] != m_joyState.rgbButtons[i]) {
				SetButtonState(i | c_sourceJoystick1, p_state.rgbButtons[i], TRUE);
			}
		}

		if (m_axisButtonEventsEnabled) {
			DispatchPolledAxisChanges(p_state);
		}
	}
}

// FUNCTION: LEGORACERS 0x0044efc0
undefined4 JoystickInputDevice::Poll(LegoS32 p_elapsedMs)
{
	DIJOYSTATE2 joyState;

	if (m_created && IsAcquired()) {
		m_device->Poll();
		HRESULT result = m_device->GetDeviceState(sizeof(joyState), &joyState);

		if (TranslateDirectInputResult(result)) {
			return TranslateDirectInputResult(result);
		}

		DispatchPolledStateChanges(joyState);
		UpdateAxisValues(joyState);
		m_joyState = joyState;
		InputDevice::Poll(p_elapsedMs);
		return 0;
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x0044f080
undefined4 JoystickInputDevice::GetButtonState(undefined4 p_key)
{
	if (!m_created) {
		return 0;
	}

	switch (GetKeySource(p_key)) {
	case c_sourceJoystick1:
		// BUG: should be "< sizeOfArray(m_joyState.rgbButtons))"
		if ((p_key & 0xffff) < 256) {
			return m_joyState.rgbButtons[p_key & 0xffff];
		}
		break;
	case c_sourceJoystick2:
		if ((p_key & 0xffff) < sizeOfArray(m_axisButtonStates)) {
			return m_axisButtonStates[p_key & 0xffff];
		}
		break;
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x0044f0e0
LegoFloat JoystickInputDevice::GetAxisValue(undefined4 p_arg)
{
	LegoU32 flag = 0x01;

	if (m_created) {
		LegoS32 i;
		for (i = 0; i < 7; i++, flag <<= 1) {
			if (p_arg == flag) {
				return m_axisValues[i];
			}
		}
	}

	return 0.0f;
}

// FUNCTION: LEGORACERS 0x0044f120
void JoystickInputDevice::SetButtonState(undefined4 p_event, LegoU8 p_state, LegoBool32 p_notify)
{
	undefined4 keyCode = p_event & c_sourceMask;
	undefined4 originalEvent = p_event;

	if (!m_created) {
		return;
	}

	if (p_state) {
		p_state = c_pressed;
	}

	p_event &= c_keyCodeMask;

	if (keyCode != c_sourceJoystick1) {
		if (keyCode == c_sourceJoystick2 && p_event < sizeOfArray(m_axisButtonStates)) {
			keyCode = m_axisMapping[p_event] | c_sourceJoystick2;
			m_axisButtonStates[p_event] = p_state;
		}
	}
	else {
		// BUG: should be "< sizeOfArray(m_joyState.rgbButtons))"
		if (p_event < 256) {
			m_joyState.rgbButtons[p_event] = p_state;
			keyCode = m_buttonMapping[p_event] | c_sourceJoystick1;
		}
	}

	if (p_notify && m_callback != NULL) {
		if (p_state) {
			m_callback->OnKeyDown(*this, keyCode, m_currentTimeMs);
		}
		else {
			m_callback->OnKeyUp(*this, keyCode, m_currentTimeMs);
		}
	}

	InputDevice::SetButtonState(originalEvent, p_state, p_notify);
}

// FUNCTION: LEGORACERS 0x0044f1e0
void JoystickInputDevice::SetAxisValue(undefined4 p_arg1, LegoFloat p_arg2)
{
	LegoU32 flag = 0x01;

	if (m_created) {
		LegoU32 i;
		for (i = 0; i < 7; i++, flag <<= 1) {
			if (p_arg1 == flag) {
				m_axisValues[i] = p_arg2;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x0044f240
LegoS32 JoystickInputDevice::GetButtonCount()
{
	return m_buttonCount;
}

// TODO: Temporary workaround until we figure out how the original code was written.
// The pragma code_seg is a hack to prevent the linker from folding with InputDevice::GetAxisCount.

// FUNCTION: LEGORACERS 0x0044f250
#pragma code_seg(".text$joy_vt20")
LegoS32 JoystickInputDevice::GetAxisCount()
{
	return 16;
}
#pragma code_seg()

// FUNCTION: LEGORACERS 0x0044f260
LegoFloat JoystickInputDevice::GetAxisValueByIndex(undefined4 p_arg)
{
	return m_axisValues[p_arg];
}

// STUB: LEGORACERS 0x0044f590 FOLDED
void JoystickInputDevice::ProcessDeviceData(const DIDEVICEOBJECTDATA&)
{
	// TODO (empty)
	STUB(0x44f590);
}
