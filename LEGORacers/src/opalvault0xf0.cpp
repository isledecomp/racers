#include "opalvault0xf0.h"

#include "golerror.h"
#include "joystickdevice.h"
#include "keyboarddevice.h"
#include "mousedevice.h"

#include <dinput.h>

DECOMP_SIZE_ASSERT(OpalVault0xf0, 0xf0)

// FUNCTION: LEGORACERS 0x00450300
OpalVault0xf0::OpalVault0xf0()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00450370
OpalVault0xf0::~OpalVault0xf0()
{
	Shutdown();
}

// FUNCTION: LEGORACERS 0x004503c0
LegoS32 OpalVault0xf0::Reset()
{
	m_directInput = NULL;
	m_hWnd = NULL;
	return JasperCore0xf0::Reset();
}

// FUNCTION: LEGORACERS 0x004503e0
LegoBool32 OpalVault0xf0::FUN_004503e0(HINSTANCE p_hInstance, HWND p_hWnd)
{
	Shutdown();
	m_hWnd = p_hWnd;

	if (p_hInstance == NULL || p_hWnd == NULL) {
		return FALSE;
	}

	if (DirectInputCreate(p_hInstance, DIRECTINPUT_VERSION, &m_directInput, NULL) != DI_OK) {
		return FALSE;
	}

	if (!(DetectKeyboard() && DetectMouse() && DetectJoysticks())) {
		Shutdown();
		return FALSE;
	}

	m_unk0x8c = 1;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00450460
LegoS32 OpalVault0xf0::Shutdown()
{
	if (m_unk0x8c) {
		DestroyDevices();

		if (m_directInput) {
			m_directInput->Release();
		}

		Reset();
	}

	return 1;
}

// FUNCTION: LEGORACERS 0x00450490
LegoS32 OpalVault0xf0::Init()
{
	DestroyDevices();

	if (DetectKeyboard() && DetectMouse() && DetectJoysticks()) {
		return 1;
	}

	Shutdown();
	return 0;
}

// FUNCTION: LEGORACERS 0x004504d0
BOOL OpalVault0xf0::AddAttachedInputDeviceCallback(LPCDIDEVICEINSTANCE p_deviceInstance, LPVOID p_context)
{
	return static_cast<OpalVault0xf0*>(p_context)->VTable0x28(p_deviceInstance);
}

// FUNCTION: LEGORACERS 0x004504f0
BOOL OpalVault0xf0::AddAttachedForceFeedbackInputDeviceCallback(LPCDIDEVICEINSTANCEA p_deviceInstance, LPVOID p_context)
{
	return static_cast<OpalVault0xf0*>(p_context)->FUN_00450630(p_deviceInstance);
}

// STUB: LEGORACERS 0x00450510
LegoBool32 OpalVault0xf0::VTable0x28(LPCDIDEVICEINSTANCE p_deviceInstance)
{
	// TODO
	STUB(0x450510);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00450630
LegoBool32 OpalVault0xf0::FUN_00450630(const LPCDIDEVICEINSTANCE p_deviceInfo)
{
	LegoS32 i;
	JoystickInputDevice* joystick;

	for (i = 0; i < m_countJoysticks; i++) {
		joystick = m_joysticks[i];
		if (joystick != NULL && joystick->GetUnk0x18()) {
			if (p_deviceInfo->guidInstance == joystick->GetGuid()) {
				joystick->SetUnk0x28(TRUE);
			}
		}
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x004506a0
LegoBool32 OpalVault0xf0::DetectKeyboard()
{
	KeyboardInputDevice* keyboard = new KeyboardInputDevice;

	if (keyboard == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	CreateDirectInputDeviceParams params;
	::memset(&params, 0, sizeof(params));
	params.m_dinput = m_directInput;
	params.m_hWnd = m_hWnd;
	params.m_guid = &GUID_SysKeyboard;
	params.m_opalVault = this;

	if (!keyboard->CreateDevice(&params)) {
		delete keyboard;
		return FALSE;
	}

	keyboard->FUN_0044ff50(50);
	m_keyboard = keyboard;
	m_keyboardAvailable = TRUE;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00450790
LegoBool32 OpalVault0xf0::DetectMouse()
{
	MouseInputDevice* mouse = new MouseInputDevice;

	if (mouse == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	CreateDirectInputDeviceParams params;
	::memset(&params, 0, sizeof(params));
	params.m_dinput = m_directInput;
	params.m_hWnd = m_hWnd;
	params.m_guid = &GUID_SysMouse;
	params.m_opalVault = this;

	if (!mouse->CreateDevice(&params)) {
		delete mouse;
		return FALSE;
	}

	mouse->FUN_0044ff50(100);
	m_mouse = mouse;
	m_mouseAvailable = TRUE;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00450880
LegoBool32 OpalVault0xf0::DetectJoysticks()
{
	if (FAILED(
			m_directInput->EnumDevices(DIDEVTYPE_JOYSTICK, AddAttachedInputDeviceCallback, this, DIEDFL_ATTACHEDONLY)
		)) {
		return FALSE;
	}
	m_directInput->EnumDevices(
		DIDEVTYPE_JOYSTICK,
		AddAttachedForceFeedbackInputDeviceCallback,
		this,
		DIEDFL_FORCEFEEDBACK | DIEDFL_ATTACHEDONLY
	);

	return TRUE;
}

// FUNCTION: LEGORACERS 0x004508d0
LegoS32 OpalVault0xf0::DestroyDevices()
{
	LegoS32 i;

	if (m_keyboardAvailable) {
		m_keyboard->Destroy();
		delete m_keyboard;
		m_keyboard = NULL;
		m_keyboardAvailable = FALSE;
	}

	if (m_mouseAvailable) {
		m_mouse->Destroy();
		delete m_mouse;
		m_mouse = NULL;
		m_mouseAvailable = FALSE;
	}

	if (m_countJoysticks != 0) {
		for (i = 0; i < m_countJoysticks; i++) {
			m_joysticks[i]->Destroy();
			delete m_joysticks[i];
			m_joysticks[i] = NULL;
		}

		m_countJoysticks = 0;
	}

	return 1;
}

// FUNCTION: LEGORACERS 0x00450990
LegoS32 OpalVault0xf0::VTable0x10(LegoS32 p_arg)
{
	LegoS32 i;
	LegoS32 result;

	if (m_keyboardAvailable) {
		result = m_keyboard->VTable0x14(p_arg);
		if (result) {
			return result;
		}
	}

	if (m_mouseAvailable) {
		m_mouse->FUN_0044bda0();
		result = m_mouse->VTable0x14(p_arg);
		if (result) {
			return result;
		}
	}

	if (m_countJoysticks != 0) {
		for (i = 0; i < m_countJoysticks; i++) {
			result = m_joysticks[i]->VTable0x14(p_arg);
			if (result) {
				return result;
			}
		}
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x00450a20
LegoS32 OpalVault0xf0::DetectNewJoysticks()
{
	LegoS32 originalCountJoysticks = m_countJoysticks;
	LegoS32 i;
	LegoS32 count = 0;

	::memset(m_unk0x4c, 0, sizeof(m_unk0x4c));
	m_directInput->EnumDevices(DIDEVTYPE_JOYSTICK, AddAttachedInputDeviceCallback, this, DIEDFL_ATTACHEDONLY);

	if (m_countJoysticks > 0) {
		for (i = 0; i < m_countJoysticks; i++) {
			if (m_unk0x4c[i]) {
				count -= 1;
			}
		}

		if (count != 0) {
			return 1;
		}
	}

	return m_countJoysticks - originalCountJoysticks;
}
