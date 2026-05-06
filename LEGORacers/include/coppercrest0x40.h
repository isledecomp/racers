#ifndef COPPERCREST0X40_H
#define COPPERCREST0X40_H

#include "decomp.h"
#include "onyxcircularbuffer0x1c.h"
#include "silverdune0x30.h"
#include "types.h"

class BronzeFalcon0xc8770;
class GolExport;
class GolCommonDrawState;
class ImaginaryTool0x368;
class InputManager;
class MouseInputDevice;
class ObscureIcon0x1a8;
class UtopianPan0xa4;

// VTABLE: LEGORACERS 0x004b2164
// SIZE 0x60
class CopperCrest0x40 {
public:
	enum {
		c_keyboardTab = 0x1000000f,
		c_keyboardLeftControl = 0x1000001d,
		c_keyboardLeftShift = 0x1000002a,
		c_keyboardRightShift = 0x10000036,
		c_keyboardRightControl = 0x1000009d,
		c_keyboardUp = 0x100000c8,
		c_keyboardDown = 0x100000d0,
		c_joystick1Button1 = 0x30000001,
		c_joystick1Button6 = 0x30000006,
		c_joystick1Button8 = 0x30000008,
		c_joystick2Button2 = 0x40000002,
		c_joystick2Button3 = 0x40000003
	};

	// SIZE 0x18
	struct InitStruct {
		GolExport* m_golExport;                          // 0x00
		BronzeFalcon0xc8770* m_renderer;                 // 0x04
		UtopianPan0xa4* m_rendererObject;                // 0x08
		InputManager* m_inputManager;                    // 0x0c
		OnyxCircularBuffer0x1c* m_inputBindingContainer; // 0x10
		undefined4 m_unk0x14;                            // 0x14
	};

	// SIZE 0x44
	class Helper0x44 {
	public:
		// SIZE 0x24
		struct InitStruct {
			InputManager* m_inputManager;     // 0x00
			GolExport* m_golExport;           // 0x04
			BronzeFalcon0xc8770* m_renderer;  // 0x08
			UtopianPan0xa4* m_rendererObject; // 0x0c
			Rect* m_bounds;                   // 0x10
			undefined4 m_unk0x14;             // 0x14
			undefined4 m_unk0x18;             // 0x18
			undefined4 m_unk0x1c;             // 0x1c
			undefined4 m_unk0x20;             // 0x20
		};

		Helper0x44();
		~Helper0x44();

		void FUN_00467c80();
		LegoS32 FUN_00467cc0(InitStruct* p_initStruct);
		LegoS32 FUN_00467d70();
		LegoS32 FUN_00467d80(undefined4 p_elapsedMs);
		LegoS32 FUN_00467e00();

		InputManager* m_inputManager;     // 0x00
		GolExport* m_golExport;           // 0x04
		BronzeFalcon0xc8770* m_renderer;  // 0x08
		UtopianPan0xa4* m_rendererObject; // 0x0c
		Rect m_bounds;                    // 0x10
		Rect m_sourceRect;                // 0x20
		LegoS32 m_unk0x30;                // 0x30
		LegoS32 m_unk0x34;                // 0x34
		LegoS32 m_unk0x38;                // 0x38
		LegoS32 m_unk0x3c;                // 0x3c
		LegoU8 m_unk0x40;                 // 0x40
		LegoU8 m_unk0x41;                 // 0x41
		undefined m_unk0x42[0x44 - 0x42]; // 0x42
	};

	CopperCrest0x40();
	virtual LegoS32 VTable0x00();                  // vtable+0x00
	virtual LegoS32 VTable0x04(ObscureIcon0x1a8*); // vtable+0x04
	virtual ~CopperCrest0x40();                    // vtable+0x08
	virtual LegoS32 VTable0x0c();                  // vtable+0x0c
	virtual LegoS32 VTable0x10(undefined4);        // vtable+0x10
	virtual void VTable0x14();                     // vtable+0x14
	virtual void VTable0x18();                     // vtable+0x18

	// SYNTHETIC: LEGORACERS 0x00468f10
	// CopperCrest0x40::`scalar deleting destructor'

	LegoS32 FUN_00469040(InitStruct* p_initStruct);
	void FUN_00469550();
	void* GetUnk0x10() { return &m_unk0x10; }
	void SetUnk0x54(ImaginaryTool0x368* p_unk0x54) { m_unk0x54 = p_unk0x54; }
	void SetCursorInside(LegoU8 p_cursorInside) { m_unk0x10.m_unk0x40 = p_cursorInside; }
	void SetCursorPosition(undefined4 p_x, undefined4 p_y)
	{
		m_unk0x10.m_unk0x30 = p_x - m_unk0x10.m_unk0x38;
		m_unk0x10.m_unk0x34 = p_y - m_unk0x10.m_unk0x3c;
	}

private:
	LegoS32 FUN_00468fa0(InitStruct* p_initStruct);
	LegoS32 FUN_004690f0(OnyxCircularBuffer0x1c::Item* p_item);
	void FUN_004691e0(MouseInputDevice* p_mouse);

	GolCommonDrawState* m_drawState;                 // 0x04
	InputManager* m_inputManager;                    // 0x08
	OnyxCircularBuffer0x1c* m_inputBindingContainer; // 0x0c
	Helper0x44 m_unk0x10;                            // 0x10
	ImaginaryTool0x368* m_unk0x54;                   // 0x54
	LegoS32 m_unk0x58;                               // 0x58
	LegoS32 m_unk0x5c;                               // 0x5c
};

#endif // COPPERCREST0X40_H
