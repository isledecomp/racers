#include "onyxbreeze0x248.h"

#include "input/inputmanager.h"
#include "input/joystickdevice.h"
#include "input/keyboarddevice.h"
#include "input/mousedevice.h"

DECOMP_SIZE_ASSERT(OnyxBreeze0x248, 0x248)

// FUNCTION: LEGORACERS 0x0041f7b0
OnyxBreeze0x248::OnyxBreeze0x248()
{
	m_inputManager = NULL;
	m_mouse = NULL;
}

// FUNCTION: LEGORACERS 0x0041f810
OnyxBreeze0x248::~OnyxBreeze0x248()
{
	Shutdown();
}

// FUNCTION: LEGORACERS 0x0041f870
void OnyxBreeze0x248::Initialize(InputManager* p_inputManager)
{
	if (m_inputManager != NULL) {
		Shutdown();
	}

	m_inputManager = p_inputManager;
	m_unk0x208.Allocate(32);

	KeyboardInputDevice* keyboard = m_inputManager->GetKeyboard();
	if (keyboard != NULL) {
		keyboard->SetCallback(&m_unk0x208);
		keyboard->SetRepeatDelays(250, 500);
		keyboard->Acquire();
	}

	MouseInputDevice* mouse = m_inputManager->GetMouse();
	m_mouse = mouse;
	if (mouse != NULL) {
		mouse->SetCallback(&m_unk0x208);
		mouse->SetRepeatDelays(250, 500);
		mouse->SetExclusiveMode();
		mouse->Acquire();
	}

	for (LegoS32 i = 0; i < m_inputManager->GetJoystickCount(); i++) {
		JoystickInputDevice* joystick = m_inputManager->GetJoystick(i);
		if (joystick != NULL) {
			joystick->SetCallback(&m_unk0x208);
			joystick->SetAxisButtonEventsEnabled(TRUE);
			joystick->Acquire();
			joystick->SetRepeatDelays(250, 500);
			joystick->SetDeadZonePercent(60);
			LegoS32 sourceId = joystick->AddDirectionalTrigger(&m_unk0x224);
			m_unk0x224.Configure(
				sourceId,
				InputDevice::c_sourceJoystick2 | 0x3,
				InputDevice::c_sourceJoystick2 | 0x0,
				InputDevice::c_sourceJoystick2 | 0x2,
				InputDevice::c_sourceJoystick2 | 0x1
			);
		}
	}

	FUN_0041fac0();
}

// FUNCTION: LEGORACERS 0x0041f9c0
void OnyxBreeze0x248::Shutdown()
{
	if (m_inputManager != NULL) {
		KeyboardInputDevice* keyboard = m_inputManager->GetKeyboard();

		if (keyboard != NULL) {
			keyboard->SetCallback(NULL);
			keyboard->Unacquire();
			keyboard->SetRepeatEnabled(FALSE);
			keyboard->SetEventMappings(NULL, NULL);
		}

		MouseInputDevice* mouse = m_inputManager->GetMouse();
		if (mouse != NULL) {
			mouse->SetCallback(NULL);
			mouse->Unacquire();
			mouse->SetEventMappings(NULL, NULL);
			mouse->SetRepeatEnabled(FALSE);
			m_mouse = NULL;
		}

		for (LegoS32 i = 0; i < m_inputManager->GetJoystickCount(); i++) {
			JoystickInputDevice* joystick = m_inputManager->GetJoystick(i);

			if (joystick != NULL) {
				joystick->SetCallback(NULL);
				joystick->Unacquire();
				joystick->SetEventMappings(NULL, NULL);
				joystick->SetRepeatEnabled(FALSE);
				joystick->SetDeadZonePercent(11);
				joystick->RemoveDirectionalTrigger(&m_unk0x224);
			}
		}

		m_unk0x208.Reset();
		m_inputManager = NULL;
		m_mouse = NULL;
	}
}

// FUNCTION: LEGORACERS 0x0041faa0
LegoBool32 OnyxBreeze0x248::HasKeyboard() const
{
	return m_inputManager->GetKeyboard() != NULL;
}

// FUNCTION: LEGORACERS 0x0041fac0
void OnyxBreeze0x248::FUN_0041fac0()
{
	for (LegoS32 i = 0; i < m_inputManager->GetJoystickCount(); i++) {
		JoystickInputDevice* joystick = m_inputManager->GetJoystick(i);

		if (joystick != NULL) {
			for (LegoS32 j = 0; j < joystick->GetButtonCountFast(); j++) {
				m_unk0x004[j] = 4;
			}

			joystick->SetEventMappings(m_unk0x004, NULL);
		}
	}
}
