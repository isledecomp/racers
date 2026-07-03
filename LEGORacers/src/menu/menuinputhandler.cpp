#include "menu/menuinputhandler.h"

#include "input/inputmanager.h"
#include "input/joystickdevice.h"
#include "input/keyboarddevice.h"
#include "input/mousedevice.h"

DECOMP_SIZE_ASSERT(MenuInputHandler, 0x248)

// FUNCTION: LEGORACERS 0x0041f7b0
MenuInputHandler::MenuInputHandler()
{
	m_inputManager = NULL;
	m_mouse = NULL;
}

// FUNCTION: LEGORACERS 0x0041f810
MenuInputHandler::~MenuInputHandler()
{
	Shutdown();
}

// FUNCTION: LEGORACERS 0x0041f870
void MenuInputHandler::Initialize(InputManager* p_inputManager)
{
	if (m_inputManager != NULL) {
		Shutdown();
	}

	m_inputManager = p_inputManager;
	m_inputEvents.Allocate(32);

	KeyboardDevice* keyboard = m_inputManager->GetKeyboard();
	if (keyboard != NULL) {
		keyboard->SetCallback(&m_inputEvents);
		keyboard->SetRepeatDelays(250, 500);
		keyboard->Acquire();
	}

	MouseDevice* mouse = m_inputManager->GetMouse();
	m_mouse = mouse;
	if (mouse != NULL) {
		mouse->SetCallback(&m_inputEvents);
		mouse->SetRepeatDelays(250, 500);
		mouse->SetExclusiveMode();
		mouse->Acquire();
	}

	for (LegoS32 i = 0; i < m_inputManager->GetJoystickCount(); i++) {
		JoystickDevice* joystick = m_inputManager->GetJoystick(i);
		if (joystick != NULL) {
			joystick->SetCallback(&m_inputEvents);
			joystick->SetAxisButtonEventsEnabled(TRUE);
			joystick->Acquire();
			joystick->SetRepeatDelays(250, 500);
			joystick->SetDeadZonePercent(60);

			LegoS32 sourceId = joystick->AddDirectionalTrigger(&m_unk0x224);
			m_unk0x224.Configure(
				sourceId,
				InputDevice::c_sourceJoystickAxisButton | 0x3,
				InputDevice::c_sourceJoystickAxisButton | 0x0,
				InputDevice::c_sourceJoystickAxisButton | 0x2,
				InputDevice::c_sourceJoystickAxisButton | 0x1
			);
		}
	}

	MapAllJoystickButtons();
}

// FUNCTION: LEGORACERS 0x0041f9c0
void MenuInputHandler::Shutdown()
{
	if (m_inputManager != NULL) {
		KeyboardDevice* keyboard = m_inputManager->GetKeyboard();

		if (keyboard != NULL) {
			keyboard->SetCallback(NULL);
			keyboard->Unacquire();
			keyboard->SetRepeatEnabled(FALSE);
			keyboard->SetEventMappings(NULL, NULL);
		}

		MouseDevice* mouse = m_inputManager->GetMouse();
		if (mouse != NULL) {
			mouse->SetCallback(NULL);
			mouse->Unacquire();
			mouse->SetEventMappings(NULL, NULL);
			mouse->SetRepeatEnabled(FALSE);
			m_mouse = NULL;
		}

		for (LegoS32 i = 0; i < m_inputManager->GetJoystickCount(); i++) {
			JoystickDevice* joystick = m_inputManager->GetJoystick(i);

			if (joystick != NULL) {
				joystick->SetCallback(NULL);
				joystick->Unacquire();
				joystick->SetEventMappings(NULL, NULL);
				joystick->SetRepeatEnabled(FALSE);
				joystick->SetDeadZonePercent(11);
				joystick->RemoveDirectionalTrigger(&m_unk0x224);
			}
		}

		m_inputEvents.Reset();
		m_inputManager = NULL;
		m_mouse = NULL;
	}
}

// FUNCTION: LEGORACERS 0x0041faa0
LegoBool32 MenuInputHandler::HasKeyboard() const
{
	return m_inputManager->GetKeyboard() != NULL;
}

// FUNCTION: LEGORACERS 0x0041fac0
void MenuInputHandler::MapAllJoystickButtons()
{
	for (LegoS32 i = 0; i < m_inputManager->GetJoystickCount(); i++) {
		JoystickDevice* joystick = m_inputManager->GetJoystick(i);

		if (joystick != NULL) {
			for (LegoS32 j = 0; j < joystick->GetButtonCountFast(); j++) {
				m_unk0x004[j] = 4;
			}

			joystick->SetEventMappings(m_unk0x004, NULL);
		}
	}
}
