#include "joystickdevice.h"

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
	::memset(&m_unk0x21c, 0, sizeof(m_unk0x21c));
	::memset(&m_unk0x1dc, 0, sizeof(m_unk0x1dc));
	DirectInputDevice::Init();
}

// FUNCTION: LEGORACERS 0x0044eb20
LegoBool32 JoystickInputDevice::CreateDevice(CreateDirectInputDeviceParams* p_params)
{
	Destroy();
	p_params->m_dataFormat = &c_dfDIJoystick2;

	if (DirectInputDevice::CreateDevice(p_params)) {
		HRESULT result1 = m_device->EnumObjects(FUN_0044ebb0, this, DIDFT_PSHBUTTON | DIDFT_TGLBUTTON);
		HRESULT result2 = m_device->EnumObjects(FUN_0044ebe0, this, DIDFT_RELAXIS | DIDFT_ABSAXIS);
		if (!FUN_00450170(result1) && !FUN_00450170(result2)) {
			SetDeadZonePercent(c_defaultDeadZonePercent);
			return m_unk0x18;
		}
		Destroy();
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x0044ebb0
BOOL JoystickInputDevice::FUN_0044ebb0(LPCDIDEVICEOBJECTINSTANCE p_object, LPVOID p_context)
{
	JoystickInputDevice* joystick = static_cast<JoystickInputDevice*>(p_context);
	LegoU32 offset = p_object->dwOfs - DIJOFS_BUTTON0;

	joystick->m_nameIndices[offset] = joystick->StoreString(p_object->tszName);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0044ebe0
BOOL JoystickInputDevice::FUN_0044ebe0(LPCDIDEVICEOBJECTINSTANCE p_object, LPVOID p_context)
{
	JoystickInputDevice* joystick = static_cast<JoystickInputDevice*>(p_context);
	undefined4 mask = joystick->FUN_0044fda0(p_object->guidType);

	if (mask != 0) {
		undefined2 v = joystick->StoreString(p_object->tszName);
		DWORD offset = p_object->dwOfs >> 2;

		joystick->m_unk0x38 |= mask;
		joystick->m_unk0xc8[offset] = v;
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0044ec30
void JoystickInputDevice::SetAxisRangeAndDeadZone(DWORD p_object, DWORD p_deadZone)
{
	undefined4 result = VTable0x18();
	if (result) {
		VTable0x54();
	}

	DIPROPRANGE propRange;
	propRange.diph.dwSize = sizeof(propRange);
	propRange.diph.dwHeaderSize = sizeof(propRange.diph);
	propRange.diph.dwObj = p_object;
	propRange.diph.dwHow = DIPH_BYOFFSET;
	propRange.lMin = -1000;
	propRange.lMax = 1000;
	FUN_00450170(m_device->SetProperty(DIPROP_RANGE, &propRange.diph));

	DIPROPDWORD propDWord;
	propDWord.dwData = p_deadZone;
	propDWord.diph.dwSize = sizeof(propDWord);
	propDWord.diph.dwHeaderSize = sizeof(propDWord.diph);
	propDWord.diph.dwObj = p_object;
	propDWord.diph.dwHow = DIPH_BYOFFSET;
	FUN_00450170(m_device->SetProperty(DIPROP_DEADZONE, &propDWord.diph));

	if (result) {
		VTable0x50();
	}
}

// FUNCTION: LEGORACERS 0x0044ecf0
void JoystickInputDevice::SetDeadZonePercent(LegoU32 p_deadZonePercent)
{
	undefined4 result = VTable0x18();
	DWORD deadZone = p_deadZonePercent * c_directInputDeadZoneScale;
	if (result) {
		VTable0x54();
	}

	if (m_unk0x38 & c_axisX) {
		SetAxisRangeAndDeadZone(DIJOFS_X, deadZone);
	}

	if (m_unk0x38 & c_axisY) {
		SetAxisRangeAndDeadZone(DIJOFS_Y, deadZone);
	}

	if (m_unk0x38 & c_axisZ) {
		SetAxisRangeAndDeadZone(DIJOFS_Z, deadZone);
	}

	if (m_unk0x38 & c_axisRx) {
		SetAxisRangeAndDeadZone(DIJOFS_RX, deadZone);
	}

	if (m_unk0x38 & c_axisRy) {
		SetAxisRangeAndDeadZone(DIJOFS_RY, deadZone);
	}

	if (m_unk0x38 & c_axisRz) {
		SetAxisRangeAndDeadZone(DIJOFS_RZ, deadZone);
	}

	if (m_unk0x38 & c_axisSlider) {
		SetAxisRangeAndDeadZone(DIJOFS_SLIDER(0), deadZone);
	}

	if (result) {
		VTable0x50();
	}
}

// FUNCTION: LEGORACERS 0x0044eda0
void JoystickInputDevice::FUN_0044eda0(const DIJOYSTATE2& p_state)
{
	if (m_unk0x38 & c_axisX) {
		m_unk0x1dc[0] = static_cast<LegoFloat>(p_state.lX) / 1000.0f;
	}

	if (m_unk0x38 & c_axisY) {
		m_unk0x1dc[1] = static_cast<LegoFloat>(p_state.lY) / 1000.0f;
	}

	if (m_unk0x38 & c_axisZ) {
		m_unk0x1dc[2] = static_cast<LegoFloat>(p_state.lZ) / 1000.0f;
	}

	if (m_unk0x38 & c_axisRx) {
		m_unk0x1dc[3] = static_cast<LegoFloat>(p_state.lRx) / 1000.0f;
	}

	if (m_unk0x38 & c_axisRy) {
		m_unk0x1dc[4] = static_cast<LegoFloat>(p_state.lRy) / 1000.0f;
	}

	if (m_unk0x38 & c_axisRz) {
		m_unk0x1dc[5] = static_cast<LegoFloat>(p_state.lRz) / 1000.0f;
	}

	if (m_unk0x38 & c_axisSlider) {
		m_unk0x1dc[6] = static_cast<LegoFloat>(p_state.rglSlider[0]) / 1000.0f;
	}
}

// FUNCTION: LEGORACERS 0x0044ee40
void JoystickInputDevice::DispatchPolledAxisChanges(const DIJOYSTATE2& p_state)
{
	if (m_unk0x38 & c_axisX) {
		FUN_0044bb60(static_cast<LegoFloat>(p_state.lX) / 1000.0f, m_unk0x1dc[0], c_sourceJoystick2 | 0x0);
	}

	if (m_unk0x38 & c_axisY) {
		FUN_0044bb60(static_cast<LegoFloat>(p_state.lY) / 1000.0f, m_unk0x1dc[1], c_sourceJoystick2 | 0x2);
	}

	if (m_unk0x38 & c_axisZ) {
		FUN_0044bb60(static_cast<LegoFloat>(p_state.lZ) / 1000.0f, m_unk0x1dc[2], c_sourceJoystick2 | 0x4);
	}

	if (m_unk0x38 & c_axisRx) {
		FUN_0044bb60(static_cast<LegoFloat>(p_state.lRx) / 1000.0f, m_unk0x1dc[3], c_sourceJoystick2 | 0x6);
	}

	if (m_unk0x38 & c_axisRy) {
		FUN_0044bb60(static_cast<LegoFloat>(p_state.lRy) / 1000.0f, m_unk0x1dc[4], c_sourceJoystick2 | 0x8);
	}

	if (m_unk0x38 & c_axisRz) {
		FUN_0044bb60(static_cast<LegoFloat>(p_state.lRz) / 1000.0f, m_unk0x1dc[5], c_sourceJoystick2 | 0xa);
	}

	if (m_unk0x38 & c_axisSlider) {
		FUN_0044bb60(static_cast<LegoFloat>(p_state.rglSlider[0]) / 1000.0f, m_unk0x1dc[6], c_sourceJoystick2 | 0xc);
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

		if (m_unk0x24) {
			DispatchPolledAxisChanges(p_state);
		}
	}
}

// FUNCTION: LEGORACERS 0x0044efc0
undefined4 JoystickInputDevice::VTable0x14(undefined4 p_arg)
{
	DIJOYSTATE2 joyState;

	if (m_unk0x18 && VTable0x18()) {
		m_device->Poll();
		HRESULT result = m_device->GetDeviceState(sizeof(joyState), &joyState);

		if (FUN_00450170(result)) {
			return FUN_00450170(result);
		}

		DispatchPolledStateChanges(joyState);
		FUN_0044eda0(joyState);
		m_joyState = joyState;
		InputDevice::VTable0x14(p_arg);
		return 0;
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x0044f080
undefined4 JoystickInputDevice::VTable0x34(undefined4 p_key)
{
	if (!m_unk0x18) {
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
		if ((p_key & 0xffff) < sizeOfArray(m_unk0x21c)) {
			return m_unk0x21c[p_key & 0xffff];
		}
		break;
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x0044f0e0
LegoFloat JoystickInputDevice::VTable0x30(undefined4 p_arg)
{
	LegoU32 flag = 0x01;

	if (m_unk0x18) {
		LegoS32 i;
		for (i = 0; i < 7; i++, flag <<= 1) {
			if (p_arg == flag) {
				return m_unk0x1dc[i];
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

	if (!m_unk0x18) {
		return;
	}

	if (p_state) {
		p_state = c_pressed;
	}

	p_event &= c_keyCodeMask;

	if (keyCode != c_sourceJoystick1) {
		if (keyCode == c_sourceJoystick2 && p_event < sizeOfArray(m_unk0x21c)) {
			keyCode = m_unk0x30[p_event] | c_sourceJoystick2;
			m_unk0x21c[p_event] = p_state;
		}
	}
	else {
		// BUG: should be "< sizeOfArray(m_joyState.rgbButtons))"
		if (p_event < 256) {
			m_joyState.rgbButtons[p_event] = p_state;
			keyCode = m_unk0x2c[p_event] | c_sourceJoystick1;
		}
	}

	if (p_notify && m_callback != NULL) {
		if (p_state) {
			m_callback->OnKeyDown(*this, keyCode, m_unk0x34);
		}
		else {
			m_callback->OnKeyUp(*this, keyCode, m_unk0x34);
		}
	}

	InputDevice::SetButtonState(originalEvent, p_state, p_notify);
}

// FUNCTION: LEGORACERS 0x0044f1e0
void JoystickInputDevice::VTable0x08(undefined4 p_arg1, LegoFloat p_arg2)
{
	LegoU32 flag = 0x01;

	if (m_unk0x18) {
		LegoU32 i;
		for (i = 0; i < 7; i++, flag <<= 1) {
			if (p_arg1 == flag) {
				m_unk0x1dc[i] = p_arg2;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x0044f240
LegoS32 JoystickInputDevice::VTable0x1c()
{
	return m_buttonCount;
}

// TODO: Temporary workaround until we figure out how the original code was written.
// The pragma code_seg is a hack to prevent the linker from folding with InputDevice::VTable0x20.

// FUNCTION: LEGORACERS 0x0044f250
#pragma code_seg(".text$joy_vt20")
undefined4 JoystickInputDevice::VTable0x20()
{
	return 16;
}
#pragma code_seg()

// FUNCTION: LEGORACERS 0x0044f260
LegoFloat JoystickInputDevice::VTable0x2c(undefined4 p_arg)
{
	return m_unk0x1dc[p_arg];
}

// STUB: LEGORACERS 0x0044f590 FOLDED
void JoystickInputDevice::VTable0x68(const DIDEVICEOBJECTDATA& p_data)
{
	// TODO (empty)
	STUB(0x44f590);
}
