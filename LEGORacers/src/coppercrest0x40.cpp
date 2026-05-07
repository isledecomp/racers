#include "coppercrest0x40.h"

#include "bronzefalcon0xc8770.h"
#include "golcommondrawstate.h"
#include "goldrawstate.h"
#include "imaginarytool0x368.h"
#include "input/inputmanager.h"
#include "input/mousedevice.h"
#include "obscureicon0x1a8.h"
#include "utopianpan0xa4.h"

#include <memory.h>

DECOMP_SIZE_ASSERT(CopperCrest0x40, 0x60)
DECOMP_SIZE_ASSERT(CopperCrest0x40::Helper0x44, 0x44)
DECOMP_SIZE_ASSERT(CopperCrest0x40::Helper0x44::InitStruct, 0x24)
DECOMP_SIZE_ASSERT(CopperCrest0x40::InitStruct, 0x18)

// GLOBAL: LEGORACERS 0x004c7648
LegoBool32 g_unk0x4c7648;

// GLOBAL: LEGORACERS 0x004c764c
LegoBool32 g_unk0x4c764c;

// FUNCTION: LEGORACERS 0x00467c60
CopperCrest0x40::Helper0x44::Helper0x44()
{
	FUN_00467c80();
}

// FUNCTION: LEGORACERS 0x00467c70
CopperCrest0x40::Helper0x44::~Helper0x44()
{
	FUN_00467d70();
}

// FUNCTION: LEGORACERS 0x00467c80
void CopperCrest0x40::Helper0x44::FUN_00467c80()
{
	::memset(&m_bounds, 0, sizeof(m_bounds));
	::memset(&m_sourceRect, 0, sizeof(m_sourceRect));
	m_golExport = NULL;
	m_renderer = NULL;
	m_inputManager = NULL;
	m_rendererObject = NULL;
	m_unk0x3c = 0;
	m_unk0x38 = 0;
	m_unk0x34 = 0;
	m_unk0x30 = 0;
	m_unk0x40 = TRUE;
	m_unk0x41 = TRUE;
}

// FUNCTION: LEGORACERS 0x00467cc0
LegoS32 CopperCrest0x40::Helper0x44::FUN_00467cc0(InitStruct* p_initStruct)
{
	if (m_golExport && !FUN_00467d70()) {
		return FALSE;
	}

	if (!p_initStruct->m_inputManager->IsMouseAvailable()) {
		return TRUE;
	}

	m_bounds = *p_initStruct->m_bounds;
	m_rendererObject = p_initStruct->m_rendererObject;
	m_golExport = p_initStruct->m_golExport;
	m_renderer = p_initStruct->m_renderer;
	m_inputManager = p_initStruct->m_inputManager;
	m_unk0x30 = p_initStruct->m_unk0x14;
	m_unk0x34 = p_initStruct->m_unk0x18;
	m_unk0x38 = p_initStruct->m_unk0x1c;
	m_unk0x3c = p_initStruct->m_unk0x20;
	m_sourceRect.m_top = 0;
	m_sourceRect.m_left = 0;
	m_sourceRect.m_right = m_rendererObject->m_unk0x34;
	m_sourceRect.m_bottom = m_rendererObject->m_unk0x38;

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00467d70
LegoS32 CopperCrest0x40::Helper0x44::FUN_00467d70()
{
	FUN_00467c80();
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00467d80
LegoS32 CopperCrest0x40::Helper0x44::FUN_00467d80(undefined4)
{
	if (m_golExport && m_unk0x40 && m_unk0x41) {
		MouseInputDevice* mouse = m_inputManager->GetMouse();

		m_unk0x30 += (LegoS32) mouse->GetAxisValue(1);
		m_unk0x34 += (LegoS32) mouse->GetAxisValue(2);

		if (m_unk0x30 < m_bounds.m_left) {
			m_unk0x30 = m_bounds.m_left;
		}
		else if (m_unk0x30 > m_bounds.m_right) {
			m_unk0x30 = m_bounds.m_right;
		}

		if (m_unk0x34 < m_bounds.m_top) {
			m_unk0x34 = m_bounds.m_top;
		}
		else if (m_unk0x34 > m_bounds.m_bottom) {
			m_unk0x34 = m_bounds.m_bottom;
		}
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00467e00
LegoS32 CopperCrest0x40::Helper0x44::FUN_00467e00()
{
	if (m_golExport && m_unk0x40 && m_unk0x41) {
		Rect destRect;

		destRect.m_left = m_unk0x30;
		destRect.m_right = m_unk0x30 + m_sourceRect.m_right;
		destRect.m_top = m_unk0x34;
		destRect.m_bottom = m_unk0x34 + m_sourceRect.m_right;

		m_renderer->VTable0x7c(m_rendererObject, 0, &destRect, &m_sourceRect, 0);
		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00468ec0
CopperCrest0x40::CopperCrest0x40()
{
	VTable0x00();
}

// FUNCTION: LEGORACERS 0x00468f30
CopperCrest0x40::~CopperCrest0x40()
{
	VTable0x0c();
}

// FUNCTION: LEGORACERS 0x00468f80
LegoS32 CopperCrest0x40::VTable0x00()
{
	m_inputManager = NULL;
	m_inputBindingContainer = NULL;
	m_unk0x54 = NULL;
	m_unk0x58 = 0;
	m_unk0x5c = 0;

	return m_unk0x10.FUN_00467d70();
}

// FUNCTION: LEGORACERS 0x00468fa0
LegoS32 CopperCrest0x40::FUN_00468fa0(InitStruct* p_initStruct)
{
	m_unk0x58 = m_drawState->m_width;
	m_unk0x5c = m_drawState->m_height;

	if (!p_initStruct->m_inputManager->IsMouseAvailable() || !p_initStruct->m_rendererObject) {
		return TRUE;
	}

	Rect bounds;
	Helper0x44::InitStruct helperInit;

	bounds.m_left = 0;
	bounds.m_top = 0;
	bounds.m_right = m_unk0x58 - p_initStruct->m_rendererObject->m_unk0x34;
	LegoS32 bottom = m_unk0x5c;
	bottom -= p_initStruct->m_rendererObject->m_unk0x38;
	bounds.m_bottom = bottom;

	helperInit.m_rendererObject = p_initStruct->m_rendererObject;
	helperInit.m_golExport = p_initStruct->m_golExport;
	helperInit.m_renderer = p_initStruct->m_renderer;
	helperInit.m_inputManager = p_initStruct->m_inputManager;
	helperInit.m_bounds = &bounds;
	helperInit.m_unk0x14 = 0;
	helperInit.m_unk0x18 = 0;
	helperInit.m_unk0x1c = 0;
	helperInit.m_unk0x20 = 0;

	return m_unk0x10.FUN_00467cc0(&helperInit);
}

// FUNCTION: LEGORACERS 0x00469040
LegoS32 CopperCrest0x40::FUN_00469040(InitStruct* p_initStruct)
{
	m_inputManager = p_initStruct->m_inputManager;
	m_inputBindingContainer = p_initStruct->m_inputBindingContainer;
	m_drawState = p_initStruct->m_renderer->GetDrawState();

	return FUN_00468fa0(p_initStruct);
}

// FUNCTION: LEGORACERS 0x00469070
LegoS32 CopperCrest0x40::VTable0x0c()
{
	if (!m_drawState) {
		return TRUE;
	}

	if (m_unk0x10.FUN_00467d70()) {
		VTable0x00();

		return m_drawState == NULL;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x004690b0
void CopperCrest0x40::VTable0x14()
{
	ObscureIcon0x1a8* icon = m_unk0x54->GetUnk0xd8();

	if (!icon->VTable0x60()) {
		icon->VTable0x68();
	}
}

// FUNCTION: LEGORACERS 0x004690d0
void CopperCrest0x40::VTable0x18()
{
	ObscureIcon0x1a8* icon = m_unk0x54->GetUnk0xd8();

	if (!icon->VTable0x64()) {
		icon->VTable0x6c();
	}
}

// FUNCTION: LEGORACERS 0x004690f0
LegoS32 CopperCrest0x40::FUN_004690f0(OnyxCircularBuffer0x1c::Item* p_item)
{
	ObscureIcon0x1a8* icon = m_unk0x54->GetUnk0xd8();
	ObscureVantage0x58* active = icon->FUN_00472e60();
	undefined4 x = m_unk0x10.m_unk0x38 + m_unk0x10.m_unk0x30;
	undefined4 y = m_unk0x10.m_unk0x3c + m_unk0x10.m_unk0x34;

	if (p_item->m_unk0x0c) {
		if (m_unk0x54->VTable0x18(icon, p_item, x, y)) {
			return TRUE;
		}
		if (active) {
			Rect* rect = active->FUN_00472e90();

			if (active->VTable0x30(p_item, x - rect->m_left, y - rect->m_top)) {
				return TRUE;
			}
		}
	}
	else {
		if (m_unk0x54->VTable0x1c(icon, p_item, x, y)) {
			return TRUE;
		}
		if (active) {
			Rect* rect = active->FUN_00472e90();

			if (active->VTable0x34(p_item, x - rect->m_left, y - rect->m_top)) {
				return TRUE;
			}
		}
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x004691e0
void CopperCrest0x40::FUN_004691e0(MouseInputDevice* p_mouse)
{
	ObscureIcon0x1a8* icon = m_unk0x54->GetUnk0xd8();
	ObscureVantage0x58* active = icon->FUN_00472e60();
	UtopianPan0xa4* rendererObject = m_unk0x10.m_rendererObject;
	LegoS32 right = m_unk0x58 - (rendererObject->m_unk0x34 >> 2);
	LegoS32 bottom = m_unk0x5c - (rendererObject->m_unk0x38 >> 2);
	Rect* bounds = &m_unk0x10.m_bounds;

	bounds->m_left = 0;
	Helper0x44* helper = &m_unk0x10;
	bounds->m_top = 0;
	bounds->m_right = right;
	bounds->m_bottom = bottom;

	undefined4 x = helper->m_unk0x38 + helper->m_unk0x30;
	undefined4 y = helper->m_unk0x3c + helper->m_unk0x34;

	if (!m_unk0x54->VTable0x14(icon, helper, x, y)) {
		if (active) {
			if (active->VTable0x2c(helper, (LegoS32) p_mouse->GetAxisValue(1), (LegoS32) p_mouse->GetAxisValue(2))) {
				return;
			}
		}

		icon->VTable0x20(helper, x, y);
	}
}

// FUNCTION: LEGORACERS 0x004692b0
LegoS32 CopperCrest0x40::VTable0x04(ObscureIcon0x1a8*)
{
	undefined4 x = m_unk0x10.m_unk0x38 + m_unk0x10.m_unk0x30;
	undefined4 y = m_unk0x10.m_unk0x3c + m_unk0x10.m_unk0x34;
	OnyxCircularBuffer0x1c::Item* item;

	while (m_inputBindingContainer->GetSize()) {
		item = m_inputBindingContainer->FUN_0044b7f0();
		if (!FUN_004690f0(item)) {
			switch (item->m_keyCode) {
			case c_keyboardLeftShift:
			case c_keyboardRightShift:
				g_unk0x4c7648 = item->m_unk0x0c != FALSE;
				break;
			case c_keyboardLeftControl:
			case c_keyboardRightControl:
				g_unk0x4c764c = item->m_unk0x0c != FALSE;
				break;
			case c_keyboardTab:
				if (item->m_unk0x0c) {
					if (g_unk0x4c7648) {
						VTable0x18();
					}
					else {
						VTable0x14();
					}
				}
				break;
			case c_keyboardDown:
			case c_joystick1Button8:
			case c_joystick2Button2:
				if (item->m_unk0x0c) {
					VTable0x14();
				}
				break;
			case c_keyboardUp:
			case c_joystick1Button6:
			case c_joystick2Button3:
				if (item->m_unk0x0c) {
					VTable0x18();
				}
				break;
			case c_joystick1Button1:
				break;
			default:
				ObscureIcon0x1a8* icon = m_unk0x54->GetUnk0xd8();

				if (item->m_unk0x0c) {
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
LegoS32 CopperCrest0x40::VTable0x10(undefined4 p_elapsedMs)
{
	ObscureIcon0x1a8* icon = m_unk0x54->GetUnk0xd8();

	if (icon) {
		icon->VTable0x18(p_elapsedMs);
		if (!VTable0x04(icon)) {
			return FALSE;
		}
	}

	if (m_unk0x10.m_golExport) {
		MouseInputDevice* mouse = m_inputManager->GetMouse();

		if (mouse->GetAxisValue(1) != 0.0f || mouse->GetAxisValue(2) != 0.0f) {
			FUN_004691e0(mouse);
		}

		if (m_drawState->m_flags & GolDrawState::c_flagBit9) {
			m_unk0x10.FUN_00467d80(p_elapsedMs);
		}
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00469550
void CopperCrest0x40::FUN_00469550()
{
	Rect rect1;
	Rect rect2;

	rect2.m_left = 0;
	rect2.m_top = 0;
	rect1.m_left = 0;
	rect1.m_top = 0;
	rect2.m_right = rect1.m_right = m_drawState->m_width;
	rect2.m_bottom = rect1.m_bottom = m_drawState->m_height;

	if (m_unk0x54->VTable0x7c(&rect2, &rect1)) {
		m_unk0x10.FUN_00467e00();
	}
}
