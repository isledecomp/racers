#include "input/inputmanager.h"

#include "input/joystickdevice.h"
#include "input/keyboarddevice.h"
#include "input/mousedevice.h"

#include <string.h>

DECOMP_SIZE_ASSERT(InputManager, 0xf0)

// FUNCTION: LEGORACERS 0x0044bf20
InputManager::InputManager()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0044bf60
InputManager::~InputManager()
{
}

// FUNCTION: LEGORACERS 0x0044bf70
LegoS32 InputManager::Reset()
{
	LegoS32 result = 0;
	m_initialized = FALSE;
	m_joystickCount = 0;
	m_mouseAvailable = FALSE;
	m_keyboardAvailable = FALSE;
	m_mouse = NULL;
	m_keyboard = NULL;
	memset(m_joysticks, 0, sizeof(m_joysticks));
	memset(m_suspendedJoysticks, 0, sizeof(m_suspendedJoysticks));
	memset(m_joystickPresent, 0, sizeof(m_joystickPresent));
	m_mouseSuspended = FALSE;
	m_keyboardSuspended = FALSE;
	return result;
}

// FUNCTION: LEGORACERS 0x0044bfd0
void InputManager::RestoreSuspendedDevices()
{
	for (LegoU32 i = 0; i < sizeOfArray(m_suspendedJoysticks); i++) {
		if (m_suspendedJoysticks[i]) {
			m_suspendedJoysticks[i] = !m_joysticks[i]->Acquire();
		}
	}

	if (m_keyboardSuspended && m_keyboard) {
		m_keyboardSuspended = !m_keyboard->Acquire();
	}

	if (m_mouseSuspended && m_mouse) {
		m_mouseSuspended = !m_mouse->Acquire();
	}
}

// FUNCTION: LEGORACERS 0x0044c040
void InputManager::SuspendActiveDevices()
{
	for (LegoU32 i = 0; i < sizeOfArray(m_joysticks); i++) {
		if (m_joysticks[i] && m_joysticks[i]->IsAcquired()) {
			m_suspendedJoysticks[i] = TRUE;
			m_joysticks[i]->Unacquire();
		}
	}

	if (m_keyboard && m_keyboard->IsAcquired()) {
		m_keyboardSuspended = TRUE;
		m_keyboard->Unacquire();
	}

	if (m_mouse && m_mouse->IsAcquired()) {
		m_mouseSuspended = TRUE;
		m_mouse->Unacquire();
	}
}
