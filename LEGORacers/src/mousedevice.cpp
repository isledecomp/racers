#include "mousedevice.h"

DECOMP_SIZE_ASSERT(MouseInputDevice, 0xe8);

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
void MouseInputDevice::VTable0x28(undefined4)
{
	// TODO
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
	::memset(m_unk0xcc, 0, sizeof(m_unk0xcc));
	::memset(m_unk0xdc, 0, sizeof(m_unk0xdc));
	::memset(m_unk0xd8, 0, sizeof(m_unk0xd8));
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
		m_unk0xdc[0] += static_cast<LegoFloat>((int) p_data.dwData);
		return;
	case DIMOFS_Y:
		m_unk0xcc[1] = p_data.dwData;
		m_unk0xdc[1] += static_cast<LegoFloat>((int) p_data.dwData);
		return;
	case DIMOFS_Z:
		m_unk0xcc[2] = p_data.dwData;
		m_unk0xdc[2] += static_cast<LegoFloat>((int) p_data.dwData);
		return;
	default:
		return;
	case DIMOFS_BUTTON0:
		m_unk0xd8[0] = static_cast<undefined>(p_data.dwData);
		event = c_source_mouse | 0x0;
		break;
	case DIMOFS_BUTTON1:
		m_unk0xd8[1] = static_cast<undefined>(p_data.dwData);
		event = c_source_mouse | 0x1;
		break;
	case DIMOFS_BUTTON2:
		m_unk0xd8[2] = static_cast<undefined>(p_data.dwData);
		event = c_source_mouse | 0x2;
		break;
	case DIMOFS_BUTTON3:
		m_unk0xd8[3] = static_cast<undefined>(p_data.dwData);
		event = c_source_mouse | 0x3;
		break;
	}
	VTable0x04(LOWORD(event) | c_source_mouse, static_cast<LegoBool>(p_data.dwData), TRUE);
}

// FUNCTION: LEGORACERS 0x0044f850
undefined4 MouseInputDevice::VTable0x34(undefined4 p_key)
{
	if (GetKeySource(p_key) == c_source_mouse) {
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
	case 1:
		return m_unk0xdc[0];
	case 2:
		return m_unk0xdc[1];
	case 4:
		return m_unk0xdc[2];
	default:
		return 0.0f;
	}
}

// FUNCTION: LEGORACERS 0x0044f8d0
void MouseInputDevice::VTable0x08(undefined4 p_arg1, LegoFloat p_arg2)
{
	switch (p_arg1) {
	case 1:
		m_unk0xdc[0] = p_arg2;
		break;
	case 2:
		m_unk0xdc[1] = p_arg2;
		break;
	case 4:
		m_unk0xdc[2] = p_arg2;
		break;
	}
}

// FUNCTION: LEGORACERS 0x0044f910
void MouseInputDevice::VTable0x04(undefined4 p_scancode, LegoBool p_arg2, LegoBool32 p_arg3)
{
	undefined4 scanCode = p_scancode & 0xffff;
	undefined4 origin = GetKeySource(p_scancode);
	LegoU32 buttonState = p_arg2 ? 0x80 : 0x00;
	if (scanCode < sizeOfArray(m_unk0xd8)) {
		m_unk0xd8[scanCode] = buttonState;
		scanCode = origin | m_unk0x2c[scanCode];
		if (p_arg3 && m_callback != NULL) {
			if (buttonState) {
				m_callback->OnKeyDown(*this, scanCode);
			}
			else {
				m_callback->OnKeyUp(*this, scanCode);
			}
		}
		InputDevice::VTable0x04(p_scancode, FALSE, p_arg3);
	}
}
