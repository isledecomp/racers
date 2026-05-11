#ifndef JOYSTICKDEVICE_H
#define JOYSTICKDEVICE_H

#include "compat.h"
#include "decomp.h"
#include "input/directinputdevice.h"

// VTABLE: LEGORACERS 0x004b1074
// SIZE 0x23c
class JoystickInputDevice : public DirectInputDevice {
public:
	enum {
		c_defaultDeadZonePercent = 35,
		c_directInputDeadZoneScale = 100,
	};

	JoystickInputDevice();

	void Initialize() override;                                                            // vtable+0x00
	void SetButtonState(undefined4 p_event, LegoU8 p_state, LegoBool32 p_notify) override; // vtable+0x04
	void SetAxisValue(undefined4, LegoFloat) override;                                     // vtable+0x08
	~JoystickInputDevice() override;                                                       // vtable+0x0c
	undefined4 Poll(LegoS32 p_elapsedMs) override;                                         // vtable+0x14
	LegoS32 GetButtonCount() override;                                                     // vtable+0x1c
	LegoS32 GetAxisCount() override;                                                       // vtable+0x20
	void SetDeadZonePercent(LegoU32 p_deadZonePercent) override;                           // vtable+0x28
	LegoFloat GetAxisValueByIndex(undefined4) override;                                    // vtable+0x2c
	LegoFloat GetAxisValue(undefined4) override;                                           // vtable+0x30
	undefined4 GetButtonState(undefined4) override;                                        // vtable+0x34
	LegoBool32 CreateDevice(CreateDirectInputDeviceParams* p_params) override;             // vtable+0x64
	void ProcessDeviceData(const DIDEVICEOBJECTDATA& p_data) override;                     // vtable+0x68

	// SYNTHETIC: LEGORACERS 0x0044ea70
	// JoystickInputDevice::`scalar deleting destructor'

	void SetAxisRangeAndDeadZone(DWORD p_object, DWORD p_deadZone);
	static BOOL CALLBACK StoreButtonNameCallback(LPCDIDEVICEOBJECTINSTANCE, LPVOID);
	static BOOL CALLBACK StoreAxisNameCallback(LPCDIDEVICEOBJECTINSTANCE, LPVOID);
	void UpdateAxisValues(const DIJOYSTATE2& p_state);
	void DispatchPolledAxisChanges(const DIJOYSTATE2& p_state);
	void DispatchPolledStateChanges(const DIJOYSTATE2& p_state);

	void SetAxisButtonEventsEnabled(LegoBool p_enabled) { m_axisButtonEventsEnabled = p_enabled; }
	LegoS32 GetButtonCountFast() const { return m_buttonCount; }

private:
	DIJOYSTATE2 m_joyState;        // 0xcc
	LegoFloat m_axisValues[16];    // 0x1dc
	LegoU8 m_axisButtonStates[32]; // 0x21c
};

#endif // JOYSTICKDEVICE_H
