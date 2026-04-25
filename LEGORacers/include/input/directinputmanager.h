#ifndef DIRECTINPUTMANAGER_H
#define DIRECTINPUTMANAGER_H

#include "compat.h"
#include "decomp.h"
#include "input/inputmanager.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004b1224
// SIZE 0xf0
class DirectInputManager : public InputManager {
public:
	DirectInputManager();
	LegoS32 Reset() override;                                                   // vtable+0x00
	~DirectInputManager() override;                                             // vtable+0x04
	LegoS32 Shutdown() override;                                                // vtable+0x08
	LegoS32 Init() override;                                                    // vtable+0x0c
	LegoS32 PollDevices(LegoS32 p_elapsedMs) override;                          // vtable+0x10
	LegoS32 DetectNewJoysticks() override;                                      // vtable+0x14
	virtual LegoBool32 DetectKeyboard();                                        // vtable+0x18
	virtual LegoBool32 DetectMouse();                                           // vtable+0x1c
	virtual LegoBool32 DetectJoysticks();                                       // vtable+0x20
	virtual LegoS32 DestroyDevices();                                           // vtable+0x24
	virtual LegoBool32 AddJoystickDevice(LPCDIDEVICEINSTANCE p_deviceInstance); // vtable+0x28

	// SYNTHETIC: LEGORACERS 0x00450350
	// DirectInputManager::`scalar deleting destructor'

	LegoBool32 Initialize(HINSTANCE p_hInstance, HWND p_hWnd);
	LegoBool32 MarkForceFeedbackJoystick(LPCDIDEVICEINSTANCE p_deviceInfo);

	static BOOL CALLBACK AddAttachedJoystickCallback(LPCDIDEVICEINSTANCE, LPVOID);
	static BOOL CALLBACK MarkForceFeedbackJoystickCallback(LPCDIDEVICEINSTANCE, LPVOID);
};

#endif // DIRECTINPUTMANAGER_H
