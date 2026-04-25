#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include "decomp.h"
#include "types.h"

#include <stddef.h> /// wchar_t

class InputManager;

// VTABLE: LEGORACERS 0x004b0e9c
// SIZE 0x9c
class InputDevice {
public:
	class Callback {
	public:
		virtual void OnKeyDown(InputDevice& p_device, undefined4 p_keyCode, undefined4 p_arg3) = 0; // vtable+0x00
		virtual void OnKeyUp(InputDevice& p_device, undefined4 p_keyCode, undefined4 p_arg3) = 0;   // vtable+0x04
	};

	enum {
		c_sourceKeyboard = 0x10000000,
		c_sourceMouse = 0x20000000,
		c_sourceJoystick1 = 0x30000000,
		c_sourceJoystick2 = 0x40000000,
		c_sourceMask = 0xf0000000,
		c_keyCodeMask = 0x0000ffff,
		c_pressed = 0x80,
	};

	InputDevice();
	virtual void Init();                                                                  // vtable+0x00
	virtual void SetButtonState(undefined4 p_event, LegoU8 p_state, LegoBool32 p_notify); // vtable+0x04
	virtual void VTable0x08(undefined4, LegoFloat) = 0;                                   // vtable+0x08
	virtual ~InputDevice();                                                               // vtable+0x0c
	virtual LegoBool32 Destroy();                                                         // vtable+0x10
	virtual undefined4 VTable0x14(undefined4);                                            // vtable+0x14
	virtual undefined4 VTable0x18();                                                      // vtable+0x18
	virtual LegoS32 VTable0x1c();                                                         // vtable+0x1c
	virtual undefined4 VTable0x20();                                                      // vtable+0x20
	virtual const wchar_t* VTable0x24(undefined4);                                        // vtable+0x24
	virtual void SetDeadZonePercent(LegoU32) = 0;                                         // vtable+0x28
	virtual LegoFloat VTable0x2c(undefined4) = 0;                                         // vtable+0x2c
	virtual LegoFloat VTable0x30(undefined4) = 0;                                         // vtable+0x30
	virtual undefined4 VTable0x34(undefined4) = 0;                                        // vtable+0x34
	virtual undefined4 VTable0x38() = 0;                                                  // vtable+0x38
	virtual undefined4 VTable0x3c() = 0;                                                  // vtable+0x3c
	virtual undefined4 VTable0x40() = 0;                                                  // vtable+0x40
	virtual undefined4 VTable0x44() = 0;                                                  // vtable+0x44
	virtual undefined4 VTable0x48() = 0;                                                  // vtable+0x48
	virtual undefined4 VTable0x4c() = 0;                                                  // vtable+0x4c
	virtual undefined4 VTable0x50();                                                      // vtable+0x50
	virtual undefined4 VTable0x54();                                                      // vtable+0x54
	virtual LegoBool32 VTable0x58() = 0;                                                  // vtable+0x58
	virtual LegoS32 VTable0x5c() = 0;                                                     // vtable+0x5c
	virtual LegoBool32 VTable0x60() = 0;                                                  // vtable+0x60

	void FUN_0044b9f0();
	void FUN_0044bab0(undefined4 p_arg1, undefined4 p_arg2);
	void FUN_0044bad0(const LegoChar* p_str);
	void FUN_0044baf0(undefined2* p_arg1, undefined2* p_arg2);
	undefined2* FUN_0044bb20();
	undefined2* FUN_0044bb40();
	void FUN_0044bb60(float p_arg1, float p_arg2, undefined4 p_arg3);
	void FUN_0044bc60(undefined4);
	void FUN_0044bda0();
	void FUN_0044bdf0(undefined4 p_arg);
	LegoBool32 FUN_0044be10(undefined4);
	LegoS16 StoreString(const LegoChar*);

	static LegoU32 GetKeySource(LegoU32 p_event) { return p_event & c_sourceMask; }

	static LegoU32 MakeEvent(LegoU32 p_source, LegoU32 p_value) { return p_source | p_value; }

	LegoBool32 GetUnk0x18() const { return m_unk0x18; }
	void SetUnk0x28(undefined4 p_arg) { m_unk0x28 = p_arg; }

	// SYNTHETIC: LEGORACERS 0x0044b920
	// InputDevice::`scalar deleting destructor'

protected:
	undefined4 m_unk0x04[4];          // 0x04
	InputManager* m_inputManager;     // 0x14
	LegoBool32 m_unk0x18;             // 0x18
	undefined4 m_unk0x1c;             // 0x1c
	undefined4 m_unk0x20;             // 0x20
	undefined4 m_unk0x24;             // 0x24
	undefined4 m_unk0x28;             // 0x28
	undefined2* m_unk0x2c;            // 0x2c
	undefined2* m_unk0x30;            // 0x30
	undefined4 m_unk0x34;             // 0x34
	undefined4 m_unk0x38;             // 0x38
	undefined4 m_unk0x3c;             // 0x3c
	undefined4 m_unk0x40;             // 0x40
	undefined4 m_unk0x44;             // 0x44
	LegoS32 m_buttonCount;            // 0x48
	LegoS32 m_axisCount;              // 0x4c
	LegoS32 m_unk0x50;                // 0x50
	undefined4 m_devSubType;          // 0x54
	undefined4 m_devType;             // 0x58
	undefined4 m_unk0x5c;             // 0x5c
	LegoChar m_unk0x60[32];           // 0x60
	undefined m_unk0x80[0x90 - 0x80]; // 0x80
	undefined4 m_unk0x90;             // 0x90
	wchar_t* m_stringBuffer;          // 0x94
	Callback* m_callback;             // 0x98
};

#include "compat.h"

#endif // INPUTDEVICE_H
