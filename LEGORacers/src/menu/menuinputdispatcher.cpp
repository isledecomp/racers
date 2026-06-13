#include "menu/menuinputdispatcher.h"

#include "image/utopianpan0xa4.h"
#include "input/inputmanager.h"
#include "input/mousedevice.h"
#include "menu/screens/menugamescreen.h"
#include "menu/screens/menuscreen.h"
#include "menu/widgets/menuicon.h"
#include "render/golcommondrawstate.h"
#include "render/gold3drenderdevice.h"
#include "render/goldrawstate.h"

#include <memory.h>

DECOMP_SIZE_ASSERT(MenuInputDispatcher, 0x60)
DECOMP_SIZE_ASSERT(MenuInputDispatcher::Cursor, 0x44)
DECOMP_SIZE_ASSERT(MenuInputDispatcher::Cursor::InitStruct, 0x24)
DECOMP_SIZE_ASSERT(MenuInputDispatcher::InitStruct, 0x18)

// GLOBAL: LEGORACERS 0x004c7648
LegoBool32 g_shiftPressed;

// GLOBAL: LEGORACERS 0x004c764c
LegoBool32 g_controlPressed;

// FUNCTION: LEGORACERS 0x00467c60
MenuInputDispatcher::Cursor::Cursor()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00467c70
MenuInputDispatcher::Cursor::~Cursor()
{
	Shutdown();
}

// FUNCTION: LEGORACERS 0x00467c80
void MenuInputDispatcher::Cursor::Reset()
{
	::memset(&m_bounds, 0, sizeof(m_bounds));
	::memset(&m_sourceRect, 0, sizeof(m_sourceRect));
	m_golExport = NULL;
	m_renderer = NULL;
	m_inputManager = NULL;
	m_cursorImage = NULL;
	m_originY = 0;
	m_originX = 0;
	m_cursorY = 0;
	m_cursorX = 0;
	m_isCursorVisible = TRUE;
	m_cursorEnabled = TRUE;
}

// FUNCTION: LEGORACERS 0x00467cc0
LegoS32 MenuInputDispatcher::Cursor::Initialize(InitStruct* p_initStruct)
{
	if (m_golExport && !Shutdown()) {
		return FALSE;
	}

	if (!p_initStruct->m_inputManager->IsMouseAvailable()) {
		return TRUE;
	}

	m_bounds = *p_initStruct->m_bounds;
	m_cursorImage = p_initStruct->m_cursorImage;
	m_golExport = p_initStruct->m_golExport;
	m_renderer = p_initStruct->m_renderer;
	m_inputManager = p_initStruct->m_inputManager;
	m_cursorX = p_initStruct->m_initialCursorX;
	m_cursorY = p_initStruct->m_initialCursorY;
	m_originX = p_initStruct->m_initialOriginX;
	m_originY = p_initStruct->m_initialOriginY;
	m_sourceRect.m_top = 0;
	m_sourceRect.m_left = 0;
	m_sourceRect.m_right = m_cursorImage->m_width;
	m_sourceRect.m_bottom = m_cursorImage->m_height;

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00467d70
LegoS32 MenuInputDispatcher::Cursor::Shutdown()
{
	Reset();
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00467d80
LegoS32 MenuInputDispatcher::Cursor::UpdatePosition(undefined4)
{
	if (m_golExport && m_isCursorVisible && m_cursorEnabled) {
		MouseInputDevice* mouse = m_inputManager->GetMouse();

		m_cursorX += (LegoS32) mouse->GetAxisValue(1);
		m_cursorY += (LegoS32) mouse->GetAxisValue(2);

		if (m_cursorX < m_bounds.m_left) {
			m_cursorX = m_bounds.m_left;
		}
		else if (m_cursorX > m_bounds.m_right) {
			m_cursorX = m_bounds.m_right;
		}

		if (m_cursorY < m_bounds.m_top) {
			m_cursorY = m_bounds.m_top;
		}
		else if (m_cursorY > m_bounds.m_bottom) {
			m_cursorY = m_bounds.m_bottom;
		}
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00467e00
LegoS32 MenuInputDispatcher::Cursor::Draw()
{
	if (m_golExport && m_isCursorVisible && m_cursorEnabled) {
		Rect destRect;

		destRect.m_left = m_cursorX;
		destRect.m_right = m_cursorX + m_sourceRect.m_right;
		destRect.m_top = m_cursorY;
		destRect.m_bottom = m_cursorY + m_sourceRect.m_right;

		m_renderer->VTable0x7c(m_cursorImage, 0, &destRect, &m_sourceRect, 0);
		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00468ec0
MenuInputDispatcher::MenuInputDispatcher()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00468f30
MenuInputDispatcher::~MenuInputDispatcher()
{
	Shutdown();
}

// FUNCTION: LEGORACERS 0x00468f80
LegoS32 MenuInputDispatcher::Reset()
{
	m_inputManager = NULL;
	m_inputEvents = NULL;
	m_activeScreen = NULL;
	m_screenWidth = 0;
	m_screenHeight = 0;

	return m_cursor.Shutdown();
}

// FUNCTION: LEGORACERS 0x00468fa0
LegoS32 MenuInputDispatcher::InitializeCursor(InitStruct* p_initStruct)
{
	m_screenWidth = m_drawState->m_width;
	m_screenHeight = m_drawState->m_height;

	if (!p_initStruct->m_inputManager->IsMouseAvailable() || !p_initStruct->m_cursorImage) {
		return TRUE;
	}

	Rect bounds;
	Cursor::InitStruct cursorInit;

	bounds.m_left = 0;
	bounds.m_top = 0;
	bounds.m_right = m_screenWidth - p_initStruct->m_cursorImage->m_width;
	LegoS32 bottom = m_screenHeight;
	bottom -= p_initStruct->m_cursorImage->m_height;
	bounds.m_bottom = bottom;

	cursorInit.m_cursorImage = p_initStruct->m_cursorImage;
	cursorInit.m_golExport = p_initStruct->m_golExport;
	cursorInit.m_renderer = p_initStruct->m_renderer;
	cursorInit.m_inputManager = p_initStruct->m_inputManager;
	cursorInit.m_bounds = &bounds;
	cursorInit.m_initialCursorX = 0;
	cursorInit.m_initialCursorY = 0;
	cursorInit.m_initialOriginX = 0;
	cursorInit.m_initialOriginY = 0;

	return m_cursor.Initialize(&cursorInit);
}

// FUNCTION: LEGORACERS 0x00469040
LegoS32 MenuInputDispatcher::Initialize(InitStruct* p_initStruct)
{
	m_inputManager = p_initStruct->m_inputManager;
	m_inputEvents = p_initStruct->m_inputEvents;
	m_drawState = p_initStruct->m_renderer->GetDrawState();

	return InitializeCursor(p_initStruct);
}

// FUNCTION: LEGORACERS 0x00469070
LegoS32 MenuInputDispatcher::Shutdown()
{
	if (!m_drawState) {
		return TRUE;
	}

	if (m_cursor.Shutdown()) {
		Reset();

		return m_drawState == NULL;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x004690b0
void MenuInputDispatcher::FocusNext()
{
	MenuIcon* icon = m_activeScreen->GetUnk0xd8();

	if (!icon->VTable0x60()) {
		icon->VTable0x68();
	}
}

// FUNCTION: LEGORACERS 0x004690d0
void MenuInputDispatcher::FocusPrevious()
{
	MenuIcon* icon = m_activeScreen->GetUnk0xd8();

	if (!icon->VTable0x64()) {
		icon->VTable0x6c();
	}
}

// FUNCTION: LEGORACERS 0x004690f0
LegoS32 MenuInputDispatcher::DispatchMouseButtonEvent(InputEventQueue::Event* p_item)
{
	MenuIcon* icon = m_activeScreen->GetUnk0xd8();
	MenuWidget* active = icon->FindFocusedLeaf();
	undefined4 x = m_cursor.m_originX + m_cursor.m_cursorX;
	undefined4 y = m_cursor.m_originY + m_cursor.m_cursorY;

	if (p_item->m_isPressed) {
		if (m_activeScreen->VTable0x18(icon, p_item, x, y)) {
			return TRUE;
		}
		if (active) {
			Rect* rect = active->GetGlobalRect();

			if (active->VTable0x30(p_item, x - rect->m_left, y - rect->m_top)) {
				return TRUE;
			}
		}
	}
	else {
		if (m_activeScreen->VTable0x1c(icon, p_item, x, y)) {
			return TRUE;
		}
		if (active) {
			Rect* rect = active->GetGlobalRect();

			if (active->VTable0x34(p_item, x - rect->m_left, y - rect->m_top)) {
				return TRUE;
			}
		}
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x004691e0
void MenuInputDispatcher::DispatchMouseMove(MouseInputDevice* p_mouse)
{
	MenuIcon* icon = m_activeScreen->GetUnk0xd8();
	MenuWidget* active = icon->FindFocusedLeaf();
	UtopianPan0xa4* cursorImage = m_cursor.m_cursorImage;
	LegoS32 right = m_screenWidth - (cursorImage->m_width >> 2);
	LegoS32 bottom = m_screenHeight - (cursorImage->m_height >> 2);
	Rect* bounds = &m_cursor.m_bounds;

	bounds->m_left = 0;
	Cursor* cursor = &m_cursor;
	bounds->m_top = 0;
	bounds->m_right = right;
	bounds->m_bottom = bottom;

	undefined4 x = cursor->m_originX + cursor->m_cursorX;
	undefined4 y = cursor->m_originY + cursor->m_cursorY;

	if (!m_activeScreen->VTable0x14(icon, cursor, x, y)) {
		if (active) {
			if (active->VTable0x2c(cursor, (LegoS32) p_mouse->GetAxisValue(1), (LegoS32) p_mouse->GetAxisValue(2))) {
				return;
			}
		}

		icon->VTable0x20(cursor, x, y);
	}
}

// FUNCTION: LEGORACERS 0x004692b0
LegoS32 MenuInputDispatcher::ProcessInputEvents(MenuIcon*)
{
	undefined4 x = m_cursor.m_originX + m_cursor.m_cursorX;
	undefined4 y = m_cursor.m_originY + m_cursor.m_cursorY;
	InputEventQueue::Event* item;

	while (m_inputEvents->GetSize()) {
		item = m_inputEvents->Dequeue();
		if (!DispatchMouseButtonEvent(item)) {
			switch (item->m_keyCode) {
			case c_keyboardLeftShift:
			case c_keyboardRightShift:
				g_shiftPressed = item->m_isPressed != FALSE;
				break;
			case c_keyboardLeftControl:
			case c_keyboardRightControl:
				g_controlPressed = item->m_isPressed != FALSE;
				break;
			case c_keyboardTab:
				if (item->m_isPressed) {
					if (g_shiftPressed) {
						FocusPrevious();
					}
					else {
						FocusNext();
					}
				}
				break;
			case c_keyboardDown:
			case c_joystickButton8:
			case c_joystickAxisButton2:
				if (item->m_isPressed) {
					FocusNext();
				}
				break;
			case c_keyboardUp:
			case c_joystickButton6:
			case c_joystickAxisButton3:
				if (item->m_isPressed) {
					FocusPrevious();
				}
				break;
			case c_joystickButton1:
				break;
			default:
				MenuIcon* icon = m_activeScreen->GetUnk0xd8();

				if (item->m_isPressed) {
					icon->VTable0x24(item, x, y);
				}
				else {
					icon->VTable0x28(item, x, y);
				}
				break;
			}
		}
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x004694b0
LegoS32 MenuInputDispatcher::Update(undefined4 p_elapsedMs)
{
	MenuIcon* icon = m_activeScreen->GetUnk0xd8();

	if (icon) {
		icon->VTable0x18(p_elapsedMs);
		if (!ProcessInputEvents(icon)) {
			return FALSE;
		}
	}

	if (m_cursor.m_golExport) {
		MouseInputDevice* mouse = m_inputManager->GetMouse();

		if (mouse->GetAxisValue(1) != 0.0f || mouse->GetAxisValue(2) != 0.0f) {
			DispatchMouseMove(mouse);
		}

		if (m_drawState->m_flags & GolDrawState::c_flagBit9) {
			m_cursor.UpdatePosition(p_elapsedMs);
		}
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00469550
void MenuInputDispatcher::DrawCursor()
{
	Rect rect1;
	Rect rect2;

	rect2.m_left = 0;
	rect2.m_top = 0;
	rect1.m_left = 0;
	rect1.m_top = 0;
	rect2.m_right = rect1.m_right = m_drawState->m_width;
	rect2.m_bottom = rect1.m_bottom = m_drawState->m_height;

	if (m_activeScreen->VTable0x7c(&rect2, &rect1)) {
		m_cursor.Draw();
	}
}
