#include "mousedevice.h"

DECOMP_SIZE_ASSERT(MouseInputDevice, 0xe8)

// FUNCTION: LEGORACERS 0x0044f520
MouseInputDevice::MouseInputDevice()
{
	Init();
}

// FUNCTION: LEGORACERS 0x0044f570
LegoS32 MouseInputDevice::VTable0x1c()
{
	return 4;
}

// FUNCTION: LEGORACERS 0x0044f580
undefined4 MouseInputDevice::VTable0x20()
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
void MouseInputDevice::Init()
{
	DirectInputDevice::Init();
	// m_unk0xcc and m_unk0xd8 are contiguous; zero both in a single call so MSVC fuses the stores.
	::memset(m_unk0xcc, 0, sizeof(m_unk0xcc) + sizeof(m_unk0xd8));
	::memset(m_unk0xdc, 0, sizeof(m_unk0xdc));
}

// FUNCTION: LEGORACERS 0x0044f640
LegoBool32 MouseInputDevice::CreateDevice(CreateDirectInputDeviceParams* p_params)
{
	Destroy();
	p_params->m_dataFormat = &c_dfDIMouse;

	if (DirectInputDevice::CreateDevice(p_params)) {
		m_unk0x90 = 0x65;

		HRESULT result1 = m_device->EnumObjects(FUN_0044f6d0, this, DIDFT_PSHBUTTON | DIDFT_TGLBUTTON);
		HRESULT result2 = m_device->EnumObjects(FUN_0044f700, this, DIDFT_RELAXIS | DIDFT_ABSAXIS);

		if (!FUN_00450170(result1) && !FUN_00450170(result2)) {
			return TRUE;
		}
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x0044f6d0
BOOL MouseInputDevice::FUN_0044f6d0(LPCDIDEVICEOBJECTINSTANCE p_object, LPVOID p_context)
{
	MouseInputDevice* mouse = static_cast<MouseInputDevice*>(p_context);
	DWORD offset = p_object->dwOfs - DIMOFS_BUTTON0;

	mouse->m_nameIndices[offset] = mouse->StoreString(p_object->tszName);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0044f700
BOOL MouseInputDevice::FUN_0044f700(LPCDIDEVICEOBJECTINSTANCE p_object, LPVOID p_context)
{
	MouseInputDevice* mouse = static_cast<MouseInputDevice*>(p_context);
	undefined4 mask = mouse->FUN_0044fda0(p_object->guidType);
	DWORD offset = static_cast<LegoS32>(p_object->dwOfs) >> 2;
	LegoS16 v = mouse->StoreString(p_object->tszName);

	mouse->m_unk0x38 |= mask;
	mouse->m_unk0xc8[offset] = v;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0044f750
void MouseInputDevice::VTable0x68(const DIDEVICEOBJECTDATA& p_data)
{
	undefined4 event;

	switch (p_data.dwOfs) {
	case DIMOFS_X:
		m_unk0xcc[0] = p_data.dwData;
		m_unk0xdc[0] += static_cast<LegoFloat>((LegoS32) p_data.dwData);
		return;
	case DIMOFS_Y:
		m_unk0xcc[1] = p_data.dwData;
		m_unk0xdc[1] += static_cast<LegoFloat>((LegoS32) p_data.dwData);
		return;
	case DIMOFS_Z:
		m_unk0xcc[2] = p_data.dwData;
		m_unk0xdc[2] += static_cast<LegoFloat>((LegoS32) p_data.dwData);
		return;
	default:
		return;
	case DIMOFS_BUTTON0:
		m_unk0xd8[0] = static_cast<undefined>(p_data.dwData);
		event = c_sourceMouse | 0x0;
		break;
	case DIMOFS_BUTTON1:
		m_unk0xd8[1] = static_cast<undefined>(p_data.dwData);
		event = c_sourceMouse | 0x1;
		break;
	case DIMOFS_BUTTON2:
		m_unk0xd8[2] = static_cast<undefined>(p_data.dwData);
		event = c_sourceMouse | 0x2;
		break;
	case DIMOFS_BUTTON3:
		m_unk0xd8[3] = static_cast<undefined>(p_data.dwData);
		event = c_sourceMouse | 0x3;
		break;
	}

	SetButtonState(LOWORD(event) | c_sourceMouse, static_cast<LegoU8>(p_data.dwData), TRUE);
}

// FUNCTION: LEGORACERS 0x0044f850
undefined4 MouseInputDevice::VTable0x34(undefined4 p_key)
{
	if (GetKeySource(p_key) == c_sourceMouse) {
		LegoU32 index = p_key & 0xffff;

		if (index < sizeOfArray(m_unk0xd8)) {
			return m_unk0xd8[index];
		}
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x0044f890
LegoFloat MouseInputDevice::VTable0x30(undefined4 p_arg)
{
	switch (p_arg) {
	case c_axisX:
		return m_unk0xdc[0];
	case c_axisY:
		return m_unk0xdc[1];
	case c_axisZ:
		return m_unk0xdc[2];
	default:
		return 0.0f;
	}
}

// FUNCTION: LEGORACERS 0x0044f8d0
void MouseInputDevice::VTable0x08(undefined4 p_arg1, LegoFloat p_arg2)
{
	switch (p_arg1) {
	case c_axisX:
		m_unk0xdc[0] = p_arg2;
		break;
	case c_axisY:
		m_unk0xdc[1] = p_arg2;
		break;
	case c_axisZ:
		m_unk0xdc[2] = p_arg2;
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

	if (p_event < sizeOfArray(m_unk0xd8)) {
		m_unk0xd8[p_event] = p_state;
		keyCode |= m_unk0x2c[p_event];

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
}
