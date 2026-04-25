#include "keyboarddevice.h"

DECOMP_SIZE_ASSERT(KeyboardInputDevice, 0x2cc)

// FUNCTION: LEGORACERS 0x0044f270
KeyboardInputDevice::KeyboardInputDevice()
{
	Init();
}

// FUNCTION: LEGORACERS 0x0044f2c0 FOLDED
LegoFloat KeyboardInputDevice::VTable0x30(undefined4)
{
	return 0.0f;
}

// TODO: Temporary workaround until we figure out how the original code was written.
// The pragma code_seg is a hack to prevent the linker from folding these trivial bodies
// with identical functions elsewhere.

// FUNCTION: LEGORACERS 0x0044f2d0
#pragma code_seg(".text$kbd_vt1c")
LegoS32 KeyboardInputDevice::VTable0x1c()
{
	return sizeOfArray(m_unk0xcc);
}
#pragma code_seg()

// FUNCTION: LEGORACERS 0x0044f2e0
#pragma code_seg(".text$kbd_vt20")
undefined4 KeyboardInputDevice::VTable0x20()
{
	return 0;
}
#pragma code_seg()

// FUNCTION: LEGORACERS 0x0044f2f0
#pragma code_seg(".text$kbd_vt08")
void KeyboardInputDevice::VTable0x08(undefined4, LegoFloat)
{
}
#pragma code_seg()

// FUNCTION: LEGORACERS 0x0044f320
KeyboardInputDevice::~KeyboardInputDevice()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0044f370
void KeyboardInputDevice::Init()
{
	::memset(m_unk0xcc, 0, sizeof(m_unk0xcc));
	DirectInputDevice::Init();
}

// FUNCTION: LEGORACERS 0x0044f390
undefined4 KeyboardInputDevice::CreateDevice(CreateDirectInputDeviceParams* p_params)
{
	Destroy();
	p_params->m_dataFormat = &c_dfDIKeyboard;

	if (!DirectInputDevice::CreateDevice(p_params)) {
		return FALSE;
	}

	if (FUN_00450170(m_device->EnumObjects(FUN_0044f400, this, DIDFT_TGLBUTTON | DIDFT_PSHBUTTON))) {
		Destroy();
		return FALSE;
	}

	m_unk0x90 = 100;
	return m_unk0x18;
}

// FUNCTION: LEGORACERS 0x0044f400
BOOL KeyboardInputDevice::FUN_0044f400(LPCDIDEVICEOBJECTINSTANCE p_object, LPVOID p_context)
{
	KeyboardInputDevice* keyboard = static_cast<KeyboardInputDevice*>(p_context);
	DWORD offset = p_object->dwOfs;

	keyboard->m_nameIndices[offset] = keyboard->StoreString(p_object->tszName);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0044f430
void KeyboardInputDevice::VTable0x68(const DIDEVICEOBJECTDATA& p_data)
{
	m_unk0xcc[p_data.dwOfs] = static_cast<undefined2>(p_data.dwData);

	if (m_callback != NULL) {
		SetButtonState(p_data.dwOfs | c_sourceKeyboard, static_cast<LegoU8>(p_data.dwData), TRUE);
	}
}

// FUNCTION: LEGORACERS 0x0044f470
undefined4 KeyboardInputDevice::VTable0x34(undefined4 p_key)
{
	p_key = LOWORD(p_key);

	if (p_key < sizeOfArray(m_unk0xcc)) {
		return m_unk0xcc[p_key];
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x0044f4a0
void KeyboardInputDevice::SetButtonState(undefined4 p_event, LegoU8 p_state, LegoBool32 p_notify)
{
	undefined4 keyCode = p_event & c_sourceMask;
	undefined4 originalEvent = p_event;

	p_event &= c_keyCodeMask;

	if (p_state) {
		p_state = c_pressed;
	}

	if (p_event < sizeOfArray(m_unk0xcc)) {
		m_unk0xcc[p_event] = static_cast<LegoS8>(p_state);
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

// STUB: LEGORACERS 0x0044f590 FOLDED
void KeyboardInputDevice::SetDeadZonePercent(LegoU32)
{
	STUB(0x44f590);
}
