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
		VTable0x04(p_data.dwOfs | c_sourceKeyboard, static_cast<LegoBool>(p_data.dwData), TRUE);
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
void KeyboardInputDevice::VTable0x04(undefined4 p_scancode, LegoBool p_arg2, LegoBool32 p_arg3)
{
	undefined4 scanCode = LOWORD(p_scancode);
	undefined4 origin = GetKeySource(p_scancode);
	char buttonState = p_arg2 ? 0x80 : 0;

	if (scanCode < sizeOfArray(m_unk0xcc)) {
		m_unk0xcc[scanCode] = buttonState;
		undefined4 keyCode = origin | m_unk0x2c[scanCode];

		if (p_arg3 && m_callback != NULL) {
			if (buttonState) {
				m_callback->OnKeyDown(*this, keyCode, m_unk0x34);
			}
			else {
				m_callback->OnKeyUp(*this, keyCode, m_unk0x34);
			}
		}

		InputDevice::VTable0x04(p_scancode, buttonState, p_arg3);
	}
}

// STUB: LEGORACERS 0x0044f590 FOLDED
void KeyboardInputDevice::VTable0x28(undefined4)
{
	// TODO
	STUB(0x44f590);
}
