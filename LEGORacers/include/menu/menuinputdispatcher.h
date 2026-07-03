#ifndef MENUINPUTDISPATCHER_H
#define MENUINPUTDISPATCHER_H

#include "decomp.h"
#include "golsurface.h"
#include "input/inputdevice.h"
#include "input/inputeventqueue.h"
#include "types.h"

class GolD3DRenderDevice;
class GolExport;
class GolCommonDrawState;
class MenuScreen;
class MenuGameScreen;
class InputManager;
class MouseDevice;
class MenuIcon;
class GolImage;

// VTABLE: LEGORACERS 0x004b2164
// SIZE 0x60
class MenuInputDispatcher {
public:
	enum {
		c_keyboardTab = 0x1000000f,
		c_keyboardLeftControl = 0x1000001d,
		c_keyboardLeftShift = 0x1000002a,
		c_keyboardRightShift = 0x10000036,
		c_keyboardRightControl = 0x1000009d,
		c_keyboardUp = 0x100000c8,
		c_keyboardDown = 0x100000d0,
		c_joystickButton1 = InputDevice::c_sourceJoystickButton | 0x1,
		c_joystickButton6 = InputDevice::c_sourceJoystickButton | 0x6,
		c_joystickButton8 = InputDevice::c_sourceJoystickButton | 0x8,
		c_joystickAxisButton2 = InputDevice::c_sourceJoystickAxisButton | 0x2,
		c_joystickAxisButton3 = InputDevice::c_sourceJoystickAxisButton | 0x3
	};

	// SIZE 0x18
	struct InitStruct {
		GolExport* m_golExport;         // 0x00
		GolD3DRenderDevice* m_renderer; // 0x04
		GolImage* m_cursorImage;        // 0x08
		InputManager* m_inputManager;   // 0x0c
		InputEventQueue* m_inputEvents; // 0x10
		undefined4 m_unk0x14;           // 0x14
	};

	// SIZE 0x44
	class Cursor {
	public:
		// SIZE 0x24
		struct InitStruct {
			InputManager* m_inputManager;   // 0x00
			GolExport* m_golExport;         // 0x04
			GolD3DRenderDevice* m_renderer; // 0x08
			GolImage* m_cursorImage;        // 0x0c
			Rect* m_bounds;                 // 0x10
			LegoS32 m_initialCursorX;       // 0x14
			LegoS32 m_initialCursorY;       // 0x18
			LegoS32 m_initialOriginX;       // 0x1c
			LegoS32 m_initialOriginY;       // 0x20
		};

		Cursor();
		~Cursor();

		void Reset();
		LegoS32 Initialize(InitStruct* p_initStruct);
		LegoS32 Shutdown();
		LegoS32 UpdatePosition(undefined4 p_elapsedMs);
		LegoS32 Draw();
		void SetCursorEnabled(LegoU8 p_cursorEnabled) { m_cursorEnabled = p_cursorEnabled; }
		LegoU8 IsCursorEnabled() const { return m_cursorEnabled; }

		InputManager* m_inputManager;     // 0x00
		GolExport* m_golExport;           // 0x04
		GolD3DRenderDevice* m_renderer;   // 0x08
		GolImage* m_cursorImage;          // 0x0c
		Rect m_bounds;                    // 0x10
		Rect m_sourceRect;                // 0x20
		LegoS32 m_cursorX;                // 0x30
		LegoS32 m_cursorY;                // 0x34
		LegoS32 m_originX;                // 0x38
		LegoS32 m_originY;                // 0x3c
		LegoU8 m_isCursorVisible;         // 0x40
		LegoU8 m_cursorEnabled;           // 0x41
		undefined m_unk0x42[0x44 - 0x42]; // 0x42
	};

	MenuInputDispatcher();
	virtual LegoS32 Reset();                       // vtable+0x00
	virtual LegoS32 ProcessInputEvents(MenuIcon*); // vtable+0x04
	virtual ~MenuInputDispatcher();                // vtable+0x08
	virtual LegoS32 Shutdown();                    // vtable+0x0c
	virtual LegoS32 Update(undefined4);            // vtable+0x10
	virtual void FocusNext();                      // vtable+0x14
	virtual void FocusPrevious();                  // vtable+0x18

	// SYNTHETIC: LEGORACERS 0x00468f10
	// MenuInputDispatcher::`scalar deleting destructor'

	LegoS32 Initialize(InitStruct* p_initStruct);
	void DrawCursor();
	Cursor* GetCursor() { return &m_cursor; }
	MenuScreen* GetActiveScreen() { return m_activeScreen; }
	void SetActiveScreen(MenuScreen* p_activeScreen) { m_activeScreen = p_activeScreen; }
	void SetCursorInside(LegoU8 p_cursorInside) { m_cursor.m_isCursorVisible = p_cursorInside; }
	void SetCursorPosition(undefined4 p_x, undefined4 p_y)
	{
		m_cursor.m_cursorX = p_x - m_cursor.m_originX;
		m_cursor.m_cursorY = p_y - m_cursor.m_originY;
	}

private:
	LegoS32 InitializeCursor(InitStruct* p_initStruct);
	LegoS32 DispatchMouseButtonEvent(InputEventQueue::Event* p_item);
	void DispatchMouseMove(MouseDevice* p_mouse);

	GolCommonDrawState* m_drawState; // 0x04
	InputManager* m_inputManager;    // 0x08
	InputEventQueue* m_inputEvents;  // 0x0c
	Cursor m_cursor;                 // 0x10
	MenuScreen* m_activeScreen;      // 0x54
	LegoS32 m_screenWidth;           // 0x58
	LegoS32 m_screenHeight;          // 0x5c
};

#endif // MENUINPUTDISPATCHER_H
