#ifndef DIRECTINPUTDEVICE_H
#define DIRECTINPUTDEVICE_H

#include "compat.h"
#include "decomp.h"
#include "input/inputdevice.h"

#include <dinput.h>

struct CreateDirectInputDeviceParams {
	LPDIRECTINPUT m_dinput;       // 0x00
	LPCDIDATAFORMAT m_dataFormat; // 0x04
	HWND m_hWnd;                  // 0x08
	const GUID* m_guid;           // 0x0c
	undefined4 m_deviceId;        // 0x10
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

	void Initialize() override;                         // vtable+0x00
	~DirectInputDevice() override;                      // vtable+0x0c
	LegoBool32 Destroy() override;                      // vtable+0x10
	undefined4 Poll(LegoS32 p_elapsedMs) override;      // vtable+0x14
	LegoS32 GetButtonCount() override = 0;              // vtable+0x1c
	LegoS32 GetAxisCount() override = 0;                // vtable+0x20
	const wchar_t* GetControlName(undefined4) override; // vtable+0x24
	LegoFloat GetAxisValueByIndex(undefined4) override; // vtable+0x2c
	undefined4 SetBackgroundMode() override;            // vtable+0x38
	undefined4 SetForegroundMode() override;            // vtable+0x3c
	undefined4 SetExclusiveMode() override;             // vtable+0x40
	undefined4 SetNonExclusiveMode() override;          // vtable+0x44

	// FUNCTION: LEGORACERS 0x0044f220 FOLDED
	undefined4 IsBackgroundMode() override // vtable+0x48
	{
		return m_cooperativeLevel & DISCL_BACKGROUND;
	}

	// FUNCTION: LEGORACERS 0x0044f230 FOLDED
	undefined4 IsExclusiveMode() override // vtable+0x4c
	{
		return m_cooperativeLevel & DISCL_EXCLUSIVE;
	}

	undefined4 Acquire() override;                                            // vtable+0x50
	undefined4 Unacquire() override;                                          // vtable+0x54
	LegoBool32 CreateForceFeedbackEffect() override;                          // vtable+0x58
	LegoS32 StartForceFeedbackEffect() override;                              // vtable+0x5c
	LegoBool32 StopForceFeedbackEffect() override;                            // vtable+0x60
	virtual LegoBool32 CreateDevice(CreateDirectInputDeviceParams* p_params); // vtable+0x64
	virtual void ProcessDeviceData(const DIDEVICEOBJECTDATA& p_data) = 0;     // vtable+0x68

	// SYNTHETIC: LEGORACERS 0x0044f9e0
	// DirectInputDevice::`scalar deleting destructor'

	void SetBufferSize(undefined4 p_bufferSize);

	const GUID& GetGuid() const { return m_deviceGuid; }

protected:
	void ReadDeviceInfo();
	void AllocateControlNameBuffers();
	undefined4 GetAxisMask(const GUID& p_guid) const;
	LegoBool32 ApplyCooperativeLevel();
	undefined4 TranslateDirectInputResult(HRESULT p_hResult);

	undefined4 m_unk0x9c;           // 0x9c
	LPDIRECTINPUTDEVICE2A m_device; // 0xa0
	HWND m_hWnd;                    // 0xa4
	LPDIRECTINPUTEFFECT m_effect;   // 0xa8
	undefined4 m_unk0xac;           // 0xac
	GUID m_deviceGuid;              // 0xb0
	DWORD m_cooperativeLevel;       // 0xc0
	LegoU16* m_buttonNameIndices;   // 0xc4
	undefined2* m_axisNameIndices;  // 0xc8
};

#endif // DIRECTINPUTDEVICE_H
