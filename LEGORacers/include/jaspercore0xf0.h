#ifndef JASPERCORE0XF0_H
#define JASPERCORE0XF0_H

#include "decomp.h"
#include "types.h"

#include <dinput.h>

class JoystickInputDevice;
class KeyboardInputDevice;
class MouseInputDevice;

// VTABLE: LEGORACERS 0x004b0f00
// SIZE 0xf0
class JasperCore0xf0 {
public:
	JasperCore0xf0();
	virtual LegoS32 Reset();                  // vtable+0x00
	virtual ~JasperCore0xf0();                // vtable+0x04
	virtual LegoS32 Shutdown() = 0;           // vtable+0x08
	virtual LegoS32 Init() = 0;               // vtable+0x0c
	virtual LegoS32 VTable0x10(LegoS32) = 0;  // vtable+0x10
	virtual LegoS32 DetectNewJoysticks() = 0; // vtable+0x14

	// SYNTHETIC: LEGORACERS 0x0044bf40
	// JasperCore0xf0::`scalar deleting destructor'

	MouseInputDevice* GetMouse() { return m_mouse; }

	void FUN_0044bfd0();
	void FUN_0044c040();

protected:
	undefined m_unk0x04[0x40];       // 0x04
	undefined4 m_unk0x44;            // 0x44
	undefined4 m_unk0x48;            // 0x48
	undefined4 m_unk0x4c[16];        // 0x4c
	undefined4 m_unk0x8c;            // 0x8c
	LegoBool32 m_keyboardAvailable;  // 0x90
	LegoBool32 m_mouseAvailable;     // 0x94
	LegoS32 m_countJoysticks;        // 0x98
	KeyboardInputDevice* m_keyboard; // 0x9c
	MouseInputDevice* m_mouse;       // 0xa0

protected:
	JoystickInputDevice* m_joysticks[16]; // 0xa4
	LPDIRECTINPUT m_directInput;          // 0xe4
	undefined m_unk0xe8[0xec - 0xe8];     // 0xe8
	HWND m_hWnd;                          // 0xec
};

#endif // JASPERCORE0XF0_H
