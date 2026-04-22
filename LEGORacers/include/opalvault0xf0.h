#ifndef OPALVAULT0XF0_H
#define OPALVAULT0XF0_H

#include "compat.h"
#include "decomp.h"
#include "jaspercore0xf0.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004b1224
// SIZE 0xf0
class OpalVault0xf0 : public JasperCore0xf0 {
public:
	OpalVault0xf0();
	LegoS32 Reset() override;                                            // vtable+0x00
	~OpalVault0xf0() override;                                           // vtable+0x04
	LegoS32 Shutdown() override;                                         // vtable+0x08
	LegoS32 Init() override;                                             // vtable+0x0c
	LegoS32 VTable0x10(LegoS32) override;                                // vtable+0x10
	LegoS32 DetectNewJoysticks() override;                               // vtable+0x14
	virtual LegoBool32 DetectKeyboard();                                 // vtable+0x18
	virtual LegoBool32 DetectMouse();                                    // vtable+0x1c
	virtual LegoBool32 DetectJoysticks();                                // vtable+0x20
	virtual LegoS32 DestroyDevices();                                    // vtable+0x24
	virtual LegoBool32 VTable0x28(LPCDIDEVICEINSTANCE p_deviceInstance); // vtable+0x28

	// SYNTHETIC: LEGORACERS 0x00450350
	// OpalVault0xf0::`scalar deleting destructor'

	LegoBool32 FUN_004503e0(HINSTANCE p_hInstance, HWND p_hWnd);
	LegoBool32 FUN_00450630(LPCDIDEVICEINSTANCE p_deviceInfo);

	static BOOL CALLBACK AddAttachedInputDeviceCallback(LPCDIDEVICEINSTANCE, LPVOID);
	static BOOL CALLBACK AddAttachedForceFeedbackInputDeviceCallback(LPCDIDEVICEINSTANCE, LPVOID);
};

#endif // OPALVAULT0XF0_H
