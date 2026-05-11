#ifndef KEYBOARDDEVICE_H
#define KEYBOARDDEVICE_H

#include "compat.h"
#include "decomp.h"
#include "input/directinputdevice.h"

// VTABLE: LEGORACERS 0x004b10e0
// SIZE 0x2cc
class KeyboardInputDevice : public DirectInputDevice {
public:
	KeyboardInputDevice();

	void Initialize() override;                                                            // vtable+0x00
	void SetButtonState(undefined4 p_event, LegoU8 p_state, LegoBool32 p_notify) override; // vtable+0x04
	void SetAxisValue(undefined4, LegoFloat) override;                                     // vtable+0x08
	~KeyboardInputDevice() override;                                                       // vtable+0x0c
	LegoS32 GetButtonCount() override;                                                     // vtable+0x1c
	LegoS32 GetAxisCount() override;                                                       // vtable+0x20
	void SetDeadZonePercent(LegoU32) override;                                             // vtable+0x28
	LegoFloat GetAxisValue(undefined4) override;                                           // vtable+0x30
	undefined4 GetButtonState(undefined4) override;                                        // vtable+0x34
	undefined4 CreateDevice(CreateDirectInputDeviceParams* p_params) override;             // vtable+0x64
	void ProcessDeviceData(const DIDEVICEOBJECTDATA& p_data) override;                     // vtable+0x68

	// SYNTHETIC: LEGORACERS 0x0044f300
	// KeyboardInputDevice::`scalar deleting destructor'

	static BOOL CALLBACK StoreKeyNameCallback(LPCDIDEVICEOBJECTINSTANCE, LPVOID);

private:
	undefined2 m_keyStates[256]; // 0xcc
};

#endif // KEYBOARDDEVICE_H
