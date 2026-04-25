#ifndef DIRECTINPUTDEVICE_H
#define DIRECTINPUTDEVICE_H

#include "compat.h"
#include "decomp.h"
#include "inputdevice.h"

#include <dinput.h>

struct CreateDirectInputDeviceParams {
	LPDIRECTINPUT m_dinput;       // 0x00
	LPCDIDATAFORMAT m_dataFormat; // 0x04
	HWND m_hWnd;                  // 0x08
	const GUID* m_guid;           // 0x0c
	undefined4 m_unk0x10;         // 0x10
	InputManager* m_inputManager; // 0x14
};

// VTABLE: LEGORACERS 0x004b11b8
// SIZE 0xcc
class DirectInputDevice : public InputDevice {
public:
	enum {
		c_axisX = 0x01,
		c_axisY = 0x02,
		c_axisZ = 0x04,
		c_axisRx = 0x08,
		c_axisRy = 0x10,
		c_axisRz = 0x20,
		c_axisSlider = 0x40,
	};

	DirectInputDevice();

	void Init() override;                           // vtable+0x00
	~DirectInputDevice() override;                  // vtable+0x0c
	LegoBool32 Destroy() override;                  // vtable+0x10
	undefined4 VTable0x14(undefined4) override;     // vtable+0x14
	LegoS32 VTable0x1c() override = 0;              // vtable+0x1c
	undefined4 VTable0x20() override = 0;           // vtable+0x20
	const wchar_t* VTable0x24(undefined4) override; // vtable+0x24
	LegoFloat VTable0x2c(undefined4) override;      // vtable+0x2c
	undefined4 VTable0x38() override;               // vtable+0x38
	undefined4 VTable0x3c() override;               // vtable+0x3c
	undefined4 VTable0x40() override;               // vtable+0x40
	undefined4 VTable0x44() override;               // vtable+0x44

	// FUNCTION: LEGORACERS 0x0044f220 FOLDED
	undefined4 VTable0x48() override // vtable+0x48
	{
		return m_cooperativeLevel & DISCL_BACKGROUND;
	}

	// FUNCTION: LEGORACERS 0x0044f230 FOLDED
	undefined4 VTable0x4c() override // vtable+0x4c
	{
		return m_cooperativeLevel & DISCL_EXCLUSIVE;
	}

	undefined4 VTable0x50() override;                                         // vtable+0x50
	undefined4 VTable0x54() override;                                         // vtable+0x54
	LegoBool32 VTable0x58() override;                                         // vtable+0x58
	LegoS32 VTable0x5c() override;                                            // vtable+0x5c
	LegoBool32 VTable0x60() override;                                         // vtable+0x60
	virtual LegoBool32 CreateDevice(CreateDirectInputDeviceParams* p_params); // vtable+0x64
	virtual void VTable0x68(const DIDEVICEOBJECTDATA& p_data) = 0;            // vtable+0x68

	// SYNTHETIC: LEGORACERS 0x0044f9e0
	// DirectInputDevice::`scalar deleting destructor'

	void FUN_0044ff50(undefined4);

	const GUID& GetGuid() const { return m_deviceGuid; }

protected:
	void FUN_0044fa50();
	void FUN_0044faa0();
	void FUN_0044fb30();
	undefined4 FUN_0044fda0(const GUID& p_guid) const;
	LegoBool32 FUN_0044fef0();
	undefined4 FUN_00450170(HRESULT p_hResult);

	undefined4 m_unk0x9c;           // 0x9c
	LPDIRECTINPUTDEVICE2A m_device; // 0xa0
	HWND m_hWnd;                    // 0xa4
	LPDIRECTINPUTEFFECT m_effect;   // 0xa8
	undefined4 m_unk0xac;           // 0xac
	GUID m_deviceGuid;              // 0xb0
	DWORD m_cooperativeLevel;       // 0xc0
	LegoU16* m_nameIndices;         // 0xc4
	undefined2* m_unk0xc8;          // 0xc8
};

#endif // DIRECTINPUTDEVICE_H
