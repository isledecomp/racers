#ifndef JOYSTICKDEVICE_H
#define JOYSTICKDEVICE_H

#include "compat.h"
#include "decomp.h"
#include "directinputdevice.h"

// VTABLE: LEGORACERS 0x004b1074
// SIZE 0x23c
class JoystickInputDevice : public DirectInputDevice {
public:
	enum {
		c_defaultDeadZonePercent = 35,
		c_directInputDeadZoneScale = 100,
	};

	JoystickInputDevice();

	void Init() override;                                                                  // vtable+0x00
	void SetButtonState(undefined4 p_event, LegoU8 p_state, LegoBool32 p_notify) override; // vtable+0x04
	void VTable0x08(undefined4, LegoFloat) override;                                       // vtable+0x08
	~JoystickInputDevice() override;                                                       // vtable+0x0c
	undefined4 VTable0x14(undefined4) override;                                            // vtable+0x14
	LegoS32 VTable0x1c() override;                                                         // vtable+0x1c
	undefined4 VTable0x20() override;                                                      // vtable+0x20
	void SetDeadZonePercent(LegoU32 p_deadZonePercent) override;                           // vtable+0x28
	LegoFloat VTable0x2c(undefined4) override;                                             // vtable+0x2c
	LegoFloat VTable0x30(undefined4) override;                                             // vtable+0x30
	undefined4 VTable0x34(undefined4) override;                                            // vtable+0x34
	LegoBool32 CreateDevice(CreateDirectInputDeviceParams* p_params) override;             // vtable+0x64
	void VTable0x68(const DIDEVICEOBJECTDATA& p_data) override;                            // vtable+0x68

	// SYNTHETIC: LEGORACERS 0x0044ea70
	// JoystickInputDevice::`scalar deleting destructor'

	void SetAxisRangeAndDeadZone(DWORD p_object, DWORD p_deadZone);
	static BOOL CALLBACK FUN_0044ebb0(LPCDIDEVICEOBJECTINSTANCE, LPVOID);
	static BOOL CALLBACK FUN_0044ebe0(LPCDIDEVICEOBJECTINSTANCE, LPVOID);
	void FUN_0044eda0(const DIJOYSTATE2& p_limits);
	void DispatchPolledAxisChanges(const DIJOYSTATE2& p_state);
	void DispatchPolledStateChanges(const DIJOYSTATE2& p_state);

private:
	DIJOYSTATE2 m_joyState;   // 0xcc
	LegoFloat m_unk0x1dc[16]; // 0x1dc
	LegoU8 m_unk0x21c[32];    // 0x21c
};

#endif // JOYSTICKDEVICE_H
