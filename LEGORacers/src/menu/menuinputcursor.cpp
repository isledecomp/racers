#include "image/golimage.h"
#include "input/inputmanager.h"
#include "input/mousedevice.h"
#include "menu/menuinputdispatcher.h"
#include "menu/screens/menugamescreen.h"
#include "menu/screens/menuscreen.h"
#include "menu/widgets/menuicon.h"
#include "render/golcommondrawstate.h"
#include "render/gold3drenderdevice.h"
#include "render/goldrawstate.h"

DECOMP_SIZE_ASSERT(MenuInputDispatcher::Cursor, 0x44)

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
		MouseDevice* mouse = m_inputManager->GetMouse();

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

		m_renderer->DrawImageClipped(m_cursorImage, 0, &destRect, &m_sourceRect, 0);
		return TRUE;
	}

	return FALSE;
}
