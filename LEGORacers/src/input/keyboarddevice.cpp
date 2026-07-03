#include "input/keyboarddevice.h"

DECOMP_SIZE_ASSERT(KeyboardDevice, 0x2cc)

// FUNCTION: LEGORACERS 0x0044f270
KeyboardDevice::KeyboardDevice()
{
	Initialize();
}

// FUNCTION: LEGORACERS 0x0044f2c0 FOLDED
LegoFloat KeyboardDevice::GetAxisValue(undefined4)
{
	return 0.0f;
}

// TODO: Temporary workaround until we figure out how the original code was written.
// The pragma code_seg is a hack to prevent the linker from folding these trivial bodies
// with identical functions elsewhere.

// FUNCTION: LEGORACERS 0x0044f2d0
#pragma code_seg(".text$kbd_vt1c")
LegoS32 KeyboardDevice::GetButtonCount()
{
	return sizeOfArray(m_keyStates);
}
#pragma code_seg()

// FUNCTION: LEGORACERS 0x0044f2e0 FOLDED
#pragma code_seg(".text$kbd_vt20")
LegoS32 KeyboardDevice::GetAxisCount()
{
	return 0;
}
#pragma code_seg()

// FUNCTION: LEGORACERS 0x0044f2f0
#pragma code_seg(".text$kbd_vt08")
void KeyboardDevice::SetAxisValue(undefined4, LegoFloat)
{
}
#pragma code_seg()

// FUNCTION: LEGORACERS 0x0044f320
KeyboardDevice::~KeyboardDevice()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0044f370
void KeyboardDevice::Initialize()
{
	::memset(m_keyStates, 0, sizeof(m_keyStates));
	DirectInputDevice::Initialize();
}

// FUNCTION: LEGORACERS 0x0044f390
undefined4 KeyboardDevice::CreateDevice(DirectInputDevice::CreateParams* p_params)
{
	Destroy();
	p_params->m_dataFormat = &c_dfDIKeyboard;

	if (!DirectInputDevice::CreateDevice(p_params)) {
		return FALSE;
	}

	if (TranslateDirectInputResult(
			m_device->EnumObjects(StoreKeyNameCallback, this, DIDFT_TGLBUTTON | DIDFT_PSHBUTTON)
		)) {
		Destroy();
		return FALSE;
	}

	m_deviceId = 100;
	return m_created;
}

// FUNCTION: LEGORACERS 0x0044f400
BOOL KeyboardDevice::StoreKeyNameCallback(LPCDIDEVICEOBJECTINSTANCE p_object, LPVOID p_context)
{
	KeyboardDevice* keyboard = static_cast<KeyboardDevice*>(p_context);
	DWORD offset = p_object->dwOfs;

	keyboard->m_buttonNameIndices[offset] = keyboard->StoreString(p_object->tszName);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0044f430
void KeyboardDevice::ProcessDeviceData(const DIDEVICEOBJECTDATA& p_data)
{
	m_keyStates[p_data.dwOfs] = static_cast<undefined2>(p_data.dwData);

	if (m_callback != NULL) {
		SetButtonState(p_data.dwOfs | c_sourceKeyboard, static_cast<LegoU8>(p_data.dwData), TRUE);
	}
}

// FUNCTION: LEGORACERS 0x0044f470
undefined4 KeyboardDevice::GetButtonState(undefined4 p_key)
{
	p_key = LOWORD(p_key);

	if (p_key < sizeOfArray(m_keyStates)) {
		return m_keyStates[p_key];
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x0044f4a0
void KeyboardDevice::SetButtonState(undefined4 p_event, LegoU8 p_state, LegoBool32 p_notify)
{
	undefined4 keyCode = p_event & c_sourceMask;
	undefined4 originalEvent = p_event;

	p_event &= c_keyCodeMask;

	if (p_state) {
		p_state = c_pressed;
	}

	if (p_event < sizeOfArray(m_keyStates)) {
		m_keyStates[p_event] = static_cast<LegoS8>(p_state);
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

// FUNCTION: LEGORACERS 0x0044f590 FOLDED
#pragma code_seg(".text$fold_44f590")
void KeyboardDevice::SetDeadZonePercent(LegoU32)
{
}
#pragma code_seg()
