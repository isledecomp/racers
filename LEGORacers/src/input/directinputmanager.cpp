#include "input/directinputmanager.h"

#include "golerror.h"
#include "input/joystickdevice.h"
#include "input/keyboarddevice.h"
#include "input/mousedevice.h"

#include <dinput.h>

DECOMP_SIZE_ASSERT(DirectInputManager, 0xf0)

// FUNCTION: LEGORACERS 0x00450300
DirectInputManager::DirectInputManager()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00450370
DirectInputManager::~DirectInputManager()
{
	Shutdown();
}

// FUNCTION: LEGORACERS 0x004503c0
LegoS32 DirectInputManager::Reset()
{
	m_directInput = NULL;
	m_hWnd = NULL;
	return InputManager::Reset();
}

// FUNCTION: LEGORACERS 0x004503e0
LegoBool32 DirectInputManager::Initialize(HINSTANCE p_hInstance, HWND p_hWnd)
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

	m_initialized = TRUE;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00450460
LegoS32 DirectInputManager::Shutdown()
{
	if (m_initialized) {
		DestroyDevices();

		if (m_directInput) {
			m_directInput->Release();
		}

		Reset();
	}

	return 1;
}

// FUNCTION: LEGORACERS 0x00450490
LegoS32 DirectInputManager::Init()
{
	DestroyDevices();

	if (DetectKeyboard() && DetectMouse() && DetectJoysticks()) {
		return 1;
	}

	Shutdown();
	return 0;
}

// FUNCTION: LEGORACERS 0x004504d0
BOOL DirectInputManager::AddAttachedJoystickCallback(LPCDIDEVICEINSTANCE p_deviceInstance, LPVOID p_context)
{
	return static_cast<DirectInputManager*>(p_context)->AddJoystickDevice(p_deviceInstance);
}

// FUNCTION: LEGORACERS 0x004504f0
BOOL DirectInputManager::MarkForceFeedbackJoystickCallback(LPCDIDEVICEINSTANCEA p_deviceInstance, LPVOID p_context)
{
	return static_cast<DirectInputManager*>(p_context)->MarkForceFeedbackJoystick(p_deviceInstance);
}

// FUNCTION: LEGORACERS 0x00450510
LegoBool32 DirectInputManager::AddJoystickDevice(LPCDIDEVICEINSTANCE p_deviceInstance)
{
	LegoS32 i;
	JoystickInputDevice* joystick;

	for (i = 0; i < m_joystickCount; i++) {
		joystick = m_joysticks[i];
		if (p_deviceInstance->guidInstance == joystick->GetGuid()) {
			m_joystickPresent[i] = TRUE;
			return TRUE;
		}
	}

	joystick = new JoystickInputDevice;

	if (joystick == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_joysticks[m_joystickCount] = joystick;
	m_joystickPresent[m_joystickCount] = TRUE;

	CreateDirectInputDeviceParams params;
	params.m_dinput = m_directInput;
	params.m_hWnd = m_hWnd;
	params.m_guid = &p_deviceInstance->guidInstance;
	params.m_deviceId = m_joystickCount;
	m_joystickCount++;
	params.m_inputManager = this;

	joystick->CreateDevice(&params);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00450630
LegoBool32 DirectInputManager::MarkForceFeedbackJoystick(const LPCDIDEVICEINSTANCE p_deviceInfo)
{
	LegoS32 i;
	JoystickInputDevice* joystick;

	for (i = 0; i < m_joystickCount; i++) {
		joystick = m_joysticks[i];
		if (joystick != NULL && joystick->IsCreated()) {
			if (p_deviceInfo->guidInstance == joystick->GetGuid()) {
				joystick->SetForceFeedbackAvailable(TRUE);
			}
		}
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x004506a0
LegoBool32 DirectInputManager::DetectKeyboard()
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
	params.m_inputManager = this;

	if (!keyboard->CreateDevice(&params)) {
		delete keyboard;
		return FALSE;
	}

	keyboard->SetBufferSize(50);
	m_keyboard = keyboard;
	m_keyboardAvailable = TRUE;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00450790
LegoBool32 DirectInputManager::DetectMouse()
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
	params.m_inputManager = this;

	if (!mouse->CreateDevice(&params)) {
		delete mouse;
		return FALSE;
	}

	mouse->SetBufferSize(100);
	m_mouse = mouse;
	m_mouseAvailable = TRUE;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00450880
LegoBool32 DirectInputManager::DetectJoysticks()
{
	if (FAILED(
			m_directInput->EnumDevices(DIDEVTYPE_JOYSTICK, AddAttachedJoystickCallback, this, DIEDFL_ATTACHEDONLY)
		)) {
		return FALSE;
	}
	m_directInput->EnumDevices(
		DIDEVTYPE_JOYSTICK,
		MarkForceFeedbackJoystickCallback,
		this,
		DIEDFL_FORCEFEEDBACK | DIEDFL_ATTACHEDONLY
	);

	return TRUE;
}

// FUNCTION: LEGORACERS 0x004508d0
LegoS32 DirectInputManager::DestroyDevices()
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

	if (m_joystickCount != 0) {
		for (i = 0; i < m_joystickCount; i++) {
			m_joysticks[i]->Destroy();
			delete m_joysticks[i];
			m_joysticks[i] = NULL;
		}

		m_joystickCount = 0;
	}

	return 1;
}

// FUNCTION: LEGORACERS 0x00450990
LegoS32 DirectInputManager::PollDevices(LegoS32 p_elapsedMs)
{
	LegoS32 i;
	LegoS32 result;

	if (m_keyboardAvailable) {
		result = m_keyboard->Poll(p_elapsedMs);
		if (result) {
			return result;
		}
	}

	if (m_mouseAvailable) {
		m_mouse->ResetAxisValues();
		result = m_mouse->Poll(p_elapsedMs);
		if (result) {
			return result;
		}
	}

	if (m_joystickCount != 0) {
		for (i = 0; i < m_joystickCount; i++) {
			result = m_joysticks[i]->Poll(p_elapsedMs);
			if (result) {
				return result;
			}
		}
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x00450a20
LegoS32 DirectInputManager::DetectNewJoysticks()
{
	LegoS32 originalCountJoysticks = m_joystickCount;
	LegoS32 i;
	LegoS32 count = 0;

	::memset(m_joystickPresent, 0, sizeof(m_joystickPresent));
	m_directInput->EnumDevices(DIDEVTYPE_JOYSTICK, AddAttachedJoystickCallback, this, DIEDFL_ATTACHEDONLY);

	if (m_joystickCount > 0) {
		for (i = 0; i < m_joystickCount; i++) {
			if (m_joystickPresent[i]) {
				count -= 1;
			}
		}

		if (count != 0) {
			return 1;
		}
	}

	return m_joystickCount - originalCountJoysticks;
}
