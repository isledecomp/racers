#ifndef MOUSEDEVICE_H
#define MOUSEDEVICE_H

#include "compat.h"
#include "decomp.h"
#include "directinputdevice.h"

// VTABLE: LEGORACERS 0x004b114c
// SIZE 0xe8
class MouseInputDevice : public DirectInputDevice {
public:
	MouseInputDevice();

	void Init() override;                                                                  // vtable+0x00
	void SetButtonState(undefined4 p_event, LegoU8 p_state, LegoBool32 p_notify) override; // vtable+0x04
	void VTable0x08(undefined4, LegoFloat) override;                                       // vtable+0x08
	~MouseInputDevice() override;                                                          // vtable+0x0c
	LegoS32 VTable0x1c() override;                                                         // vtable+0x1c
	undefined4 VTable0x20() override;                                                      // vtable+0x20
	void SetDeadZonePercent(LegoU32) override;                                             // vtable+0x28
	LegoFloat VTable0x30(undefined4) override;                                             // vtable+0x30
	undefined4 VTable0x34(undefined4) override;                                            // vtable+0x34
	undefined4 CreateDevice(CreateDirectInputDeviceParams* p_params) override;             // vtable+0x64
	void VTable0x68(const DIDEVICEOBJECTDATA& p_data) override;                            // vtable+0x68

	// SYNTHETIC: LEGORACERS 0x0044f5a0
	// MouseInputDevice::`scalar deleting destructor'

private:
	static BOOL CALLBACK FUN_0044f6d0(LPCDIDEVICEOBJECTINSTANCE, LPVOID);
	static BOOL CALLBACK FUN_0044f700(LPCDIDEVICEOBJECTINSTANCE, LPVOID);

	undefined4 m_unk0xcc[3]; // 0xcc
	undefined m_unk0xd8[4];  // 0xd8
	LegoFloat m_unk0xdc[3];  // 0xdc
};

#endif // MOUSEDEVICE_H
