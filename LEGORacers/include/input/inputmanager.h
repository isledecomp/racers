#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "decomp.h"
#include "types.h"

#include <dinput.h>

class JoystickInputDevice;
class KeyboardInputDevice;
class MouseInputDevice;

// VTABLE: LEGORACERS 0x004b0f00
// SIZE 0xf0
class InputManager {
public:
	InputManager();
	virtual LegoS32 Reset();                              // vtable+0x00
	virtual ~InputManager();                              // vtable+0x04
	virtual LegoS32 Shutdown() = 0;                       // vtable+0x08
	virtual LegoS32 Initialize() = 0;                     // vtable+0x0c
	virtual LegoS32 PollDevices(LegoS32 p_elapsedMs) = 0; // vtable+0x10
	virtual LegoS32 DetectNewJoysticks() = 0;             // vtable+0x14

	// SYNTHETIC: LEGORACERS 0x0044bf40
	// InputManager::`scalar deleting destructor'

	MouseInputDevice* GetMouse() { return m_mouse; }
	KeyboardInputDevice* GetKeyboard() { return m_keyboard; }
	LegoBool32 IsMouseAvailable() const { return m_mouseAvailable; }
	LegoS32 GetJoystickCount() const { return m_joystickCount; }
	JoystickInputDevice* GetJoystick(LegoS32 p_index) const { return m_joysticks[p_index]; }

	void RestoreSuspendedDevices();
	void SuspendActiveDevices();

protected:
	LegoBool32 m_suspendedJoysticks[16]; // 0x04
	LegoBool32 m_keyboardSuspended;      // 0x44
	LegoBool32 m_mouseSuspended;         // 0x48
	LegoBool32 m_joystickPresent[16];    // 0x4c
	LegoBool32 m_initialized;            // 0x8c
	LegoBool32 m_keyboardAvailable;      // 0x90
	LegoBool32 m_mouseAvailable;         // 0x94
	LegoS32 m_joystickCount;             // 0x98
	KeyboardInputDevice* m_keyboard;     // 0x9c
	MouseInputDevice* m_mouse;           // 0xa0

protected:
	JoystickInputDevice* m_joysticks[16]; // 0xa4
	LPDIRECTINPUT m_directInput;          // 0xe4
	undefined m_unk0xe8[0xec - 0xe8];     // 0xe8
	HWND m_hWnd;                          // 0xec
};

#endif // INPUTMANAGER_H
