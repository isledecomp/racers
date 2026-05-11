#include "input/mousedevice.h"

DECOMP_SIZE_ASSERT(MouseInputDevice, 0xe8)

// FUNCTION: LEGORACERS 0x0044f520
MouseInputDevice::MouseInputDevice()
{
	Initialize();
}

// FUNCTION: LEGORACERS 0x0044f570
LegoS32 MouseInputDevice::GetButtonCount()
{
	return 4;
}

// FUNCTION: LEGORACERS 0x0044f580
LegoS32 MouseInputDevice::GetAxisCount()
{
	return 3;
}

// STUB: LEGORACERS 0x0044f590 FOLDED
void MouseInputDevice::SetDeadZonePercent(LegoU32)
{
	STUB(0x44f590);
}

// FUNCTION: LEGORACERS 0x0044f5c0
MouseInputDevice::~MouseInputDevice()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0044f610
void MouseInputDevice::Initialize()
{
	DirectInputDevice::Initialize();
	// These arrays are contiguous; zero both in a single call so MSVC fuses the stores.
	::memset(m_rawAxisValues, 0, sizeof(m_rawAxisValues) + sizeof(m_buttonStates));
	::memset(m_axisValues, 0, sizeof(m_axisValues));
}

// FUNCTION: LEGORACERS 0x0044f640
LegoBool32 MouseInputDevice::CreateDevice(CreateDirectInputDeviceParams* p_params)
{
	Destroy();
	p_params->m_dataFormat = &c_dfDIMouse;

	if (DirectInputDevice::CreateDevice(p_params)) {
		m_deviceId = 0x65;

		HRESULT result1 = m_device->EnumObjects(StoreButtonNameCallback, this, DIDFT_PSHBUTTON | DIDFT_TGLBUTTON);
		HRESULT result2 = m_device->EnumObjects(StoreAxisNameCallback, this, DIDFT_RELAXIS | DIDFT_ABSAXIS);

		if (!TranslateDirectInputResult(result1) && !TranslateDirectInputResult(result2)) {
			return TRUE;
		}
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x0044f6d0
BOOL MouseInputDevice::StoreButtonNameCallback(LPCDIDEVICEOBJECTINSTANCE p_object, LPVOID p_context)
{
	MouseInputDevice* mouse = static_cast<MouseInputDevice*>(p_context);
	DWORD offset = p_object->dwOfs - DIMOFS_BUTTON0;

	mouse->m_buttonNameIndices[offset] = mouse->StoreString(p_object->tszName);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0044f700
BOOL MouseInputDevice::StoreAxisNameCallback(LPCDIDEVICEOBJECTINSTANCE p_object, LPVOID p_context)
{
	MouseInputDevice* mouse = static_cast<MouseInputDevice*>(p_context);
	undefined4 mask = mouse->GetAxisMask(p_object->guidType);
	DWORD offset = static_cast<LegoS32>(p_object->dwOfs) >> 2;
	LegoS16 v = mouse->StoreString(p_object->tszName);

	mouse->m_axisMask |= mask;
	mouse->m_axisNameIndices[offset] = v;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0044f750
void MouseInputDevice::ProcessDeviceData(const DIDEVICEOBJECTDATA& p_data)
{
	undefined4 event;

	switch (p_data.dwOfs) {
	case DIMOFS_X:
		m_rawAxisValues[0] = p_data.dwData;
		m_axisValues[0] += static_cast<LegoFloat>((LegoS32) p_data.dwData);
		return;
	case DIMOFS_Y:
		m_rawAxisValues[1] = p_data.dwData;
		m_axisValues[1] += static_cast<LegoFloat>((LegoS32) p_data.dwData);
		return;
	case DIMOFS_Z:
		m_rawAxisValues[2] = p_data.dwData;
		m_axisValues[2] += static_cast<LegoFloat>((LegoS32) p_data.dwData);
		return;
	default:
		return;
	case DIMOFS_BUTTON0:
		m_buttonStates[0] = static_cast<undefined>(p_data.dwData);
		event = c_sourceMouse | 0x0;
		break;
	case DIMOFS_BUTTON1:
		m_buttonStates[1] = static_cast<undefined>(p_data.dwData);
		event = c_sourceMouse | 0x1;
		break;
	case DIMOFS_BUTTON2:
		m_buttonStates[2] = static_cast<undefined>(p_data.dwData);
		event = c_sourceMouse | 0x2;
		break;
	case DIMOFS_BUTTON3:
		m_buttonStates[3] = static_cast<undefined>(p_data.dwData);
		event = c_sourceMouse | 0x3;
		break;
	}

	SetButtonState(LOWORD(event) | c_sourceMouse, static_cast<LegoU8>(p_data.dwData), TRUE);
}

// FUNCTION: LEGORACERS 0x0044f850
undefined4 MouseInputDevice::GetButtonState(undefined4 p_key)
{
	if (GetKeySource(p_key) == c_sourceMouse) {
		LegoU32 index = p_key & 0xffff;

		if (index < sizeOfArray(m_buttonStates)) {
			return m_buttonStates[index];
		}
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x0044f890
LegoFloat MouseInputDevice::GetAxisValue(undefined4 p_arg)
{
	switch (p_arg) {
	case c_axisX:
		return m_axisValues[0];
	case c_axisY:
		return m_axisValues[1];
	case c_axisZ:
		return m_axisValues[2];
	default:
		return 0.0f;
	}
}

// FUNCTION: LEGORACERS 0x0044f8d0
void MouseInputDevice::SetAxisValue(undefined4 p_arg1, LegoFloat p_arg2)
{
	switch (p_arg1) {
	case c_axisX:
		m_axisValues[0] = p_arg2;
		break;
	case c_axisY:
		m_axisValues[1] = p_arg2;
		break;
	case c_axisZ:
		m_axisValues[2] = p_arg2;
		break;
	}
}

// FUNCTION: LEGORACERS 0x0044f910
void MouseInputDevice::SetButtonState(undefined4 p_event, LegoU8 p_state, LegoBool32 p_notify)
{
	undefined4 keyCode = p_event & c_sourceMask;
	undefined4 originalEvent = p_event;

	p_event &= c_keyCodeMask;

	if (p_state) {
		p_state = c_pressed;
	}

	if (p_event < sizeOfArray(m_buttonStates)) {
		m_buttonStates[p_event] = p_state;
		keyCode |= m_buttonMapping[p_event];

		if (p_notify && m_callback != NULL) {
			if (p_state) {
				m_callback->OnKeyDown(this, keyCode, m_currentTimeMs);
			}
			else {
				m_callback->OnKeyUp(this, keyCode, m_currentTimeMs);
			}
		}

		InputDevice::SetButtonState(originalEvent, p_state, p_notify);
	}
}
