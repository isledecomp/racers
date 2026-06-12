#include "menu/screens/carbuildscreen.h"

#include "audio/soundgroupbinding.h"
#include "audio/soundnode.h"
#include "golhashtable.h"
#include "golstream.h"
#include "input/inputdevice.h"
#include "menu/menugamecontext.h"

#include <string.h>

DECOMP_SIZE_ASSERT(CarBuildScreen, 0x3c34)

// GLOBAL: LEGORACERS 0x004af668
LegoFloat g_carBuildPreviewMouseScale = 0.01f;

// GLOBAL: LEGORACERS 0x004c1d12
const LegoU16 g_carBuildTextIds[] = {0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 0};

// GLOBAL: LEGORACERS 0x004c1d38
const LegoChar g_carBuildHelpFontName[8] = {'f', 'o', 'n', 't', '_', 'h', 'l', 'p'};

// GLOBAL: LEGORACERS 0x004c1d78
const LegoS32 g_carBuildDragHorizontalOffsets[] = {-1, -1, 0,  1,  1,  1,  0,  -1, -1, -1, -1, 0,  1,  1,  1,  0,
												   0,  -1, -1, -1, 0,  1,  1,  1,  1,  0,  -1, -1, -1, 0,  1,  1,
												   1,  1,  0,  -1, -1, -1, 0,  1,  1,  1,  1,  0,  -1, -1, -1, 0,
												   0,  1,  1,  1,  0,  -1, -1, -1, -1, 0,  1,  1,  1,  0,  -1, -1};

// GLOBAL: LEGORACERS 0x004c1e78
const LegoS32 g_carBuildDragVerticalOffsets[] = {0,  1,  1,  1,  0,  -1, -1, -1, -1, 0,  1,  1,  1,  0,  -1, -1,
												 -1, -1, 0,  1,  1,  1,  0,  -1, -1, -1, -1, 0,  1,  1,  1,  0,
												 0,  -1, -1, -1, 0,  1,  1,  1,  1,  0,  -1, -1, -1, 0,  1,  1,
												 1,  1,  0,  -1, -1, -1, 0,  1,  1,  1,  1,  0,  -1, -1, -1, 0};

// FUNCTION: LEGORACERS 0x004736b0
CarBuildScreen::CarBuildScreen()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004737b0
CarBuildScreen::~CarBuildScreen()
{
	m_unk0x3c20.ReleaseOwnedBuffers();
	Destroy();
}

// FUNCTION: LEGORACERS 0x004738a0
void CarBuildScreen::Reset()
{
	m_unk0x3c18 = 0;
	m_unk0x3c1c = 0;
	CarModelScreenBase::Reset();
}

// FUNCTION: LEGORACERS 0x004738c0
void CarBuildScreen::VTable0x4c()
{
	CarModelScreenBase::VTable0x4c();
	CreateHotspotButton(&m_unk0x2b20, 0xb5, 0xb5);
	CreateButton(&m_unk0x318c, 0xb2, 0xb0);
	CreateButton(&m_unk0x2f70, 0xb1, 0xb0);
	CreateButton(&m_unk0x33a8, 0xb3, 0xb0);
	CreateHotspotButton(&m_unk0x2d48, 0xb4, 0xb4);

	MenuButton* glyph0 = &m_unk0x35c4;
	CreateButton(glyph0, 0xb8, 0xb0);

	MenuButton* glyph1 = &m_unk0x37e0;
	CreateButton(glyph1, 0xb7, 0xb0);

	glyph0->ClearFlags(MenuIcon::c_flagBit1);
	glyph1->ClearFlags(MenuIcon::c_flagBit1);
	CreateButton(&m_unk0x39fc, 0x3f, 0xb0);
}

// FUNCTION: LEGORACERS 0x004739a0
LegoBool32 CarBuildScreen::VTable0x8c(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	if (!CarModelScreenBase::VTable0x8c(p_context, p_createParams)) {
		return FALSE;
	}

	p_context->m_unk0x258.GetUnk0x18c4().SetLanguageResourcePath();
	m_unk0x3c20.UseOwnedBuffers();
	m_unk0x3c20.Load("carbuild.srf");

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}

	m_unk0x4a4.VTable0x4c(4);
	return m_initialized;
}

// FUNCTION: LEGORACERS 0x00473a20 FOLDED
LegoBool32 CarBuildScreen::FUN_00473a20(Rect* p_rect, LegoS32 p_x, LegoS32 p_y)
{
	return p_x >= p_rect->m_left && p_x <= p_rect->m_right && p_y >= p_rect->m_top && p_y <= p_rect->m_bottom;
}

// FUNCTION: LEGORACERS 0x00473a50
LegoBool32 CarBuildScreen::FUN_00473a50(InputEventQueue::Event* p_event, undefined4 p_unk0x08, undefined4 p_unk0x0c)
{
	if (p_event->m_isRepeat) {
		return FALSE;
	}

	LegoS32 x = static_cast<LegoS32>(p_unk0x08);
	LegoS32 y = static_cast<LegoS32>(p_unk0x0c);

	if (!FUN_00473a20(m_unk0x1e30.GetGlobalRect(), x, y)) {
		return FALSE;
	}

	if (FUN_00473a20(m_unk0x35c4.GetRect(), x, y)) {
		if (m_unk0x3c18) {
			if (m_unk0x2ae0 == 1) {
				if (m_unk0x2308.FUN_00478730()) {
					m_unk0x2ae4 = 6;
					m_unk0x2adc = 4;
				}

				m_unk0x3c18 = 0;
				return TRUE;
			}
		}

		m_unk0x2ae4 = 3;
		m_unk0x3c18 = c_carBuildClickDelay;
		m_unk0xd8.SetFocus();

		if (m_unk0x2308.GetUnk0x294() != 1) {
			m_unk0x2308.FUN_00479310();
		}

		return TRUE;
	}

	if (FUN_00473a20(m_unk0x37e0.GetRect(), x, y)) {
		m_unk0x2ae4 = 2;
		m_unk0xd8.SetFocus();

		if (m_unk0x2308.GetUnk0x294() != 2) {
			m_unk0x2308.FUN_00479300();
		}

		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00473b80
void CarBuildScreen::FUN_00473b80(LegoS32 p_deltaX, LegoS32 p_deltaY)
{
	if (m_unk0x3c1c) {
		return;
	}

	LegoS32 keyCode = c_carBuildRegionSource;
	if (p_deltaX >= c_carBuildDragThreshold) {
		if (p_deltaY >= c_carBuildDragThreshold) {
			keyCode = c_carBuildRegionSource | 4;
		}
		else if (p_deltaY > -c_carBuildDragThreshold) {
			keyCode = c_carBuildRegionSource | 3;
		}
		else {
			keyCode = c_carBuildRegionSource | 2;
		}
	}
	else if (p_deltaX <= -c_carBuildDragThreshold) {
		if (p_deltaY >= c_carBuildDragThreshold) {
			keyCode = c_carBuildRegionSource | 6;
		}
		else if (p_deltaY <= -c_carBuildDragThreshold) {
			keyCode = c_carBuildRegionSource | 8;
		}
		else {
			keyCode = c_carBuildRegionSource | 7;
		}
	}
	else if (p_deltaY >= c_carBuildDragThreshold) {
		keyCode = c_carBuildRegionSource | 5;
	}
	else if (p_deltaY <= -c_carBuildDragThreshold) {
		keyCode = c_carBuildRegionSource | 1;
	}

	LegoS32 regionId = keyCode & InputDevice::c_keyCodeMask;
	if (!regionId) {
		return;
	}

	LegoS32 index = regionId - 1;
	FUN_004773e0(
		g_carBuildDragHorizontalOffsets[m_unk0x2308.GetUnk0x298() * 8 + index],
		g_carBuildDragVerticalOffsets[m_unk0x2308.GetUnk0x298() * 8 + index],
		index & 1,
		0
	);
	m_unk0x3c1c = c_carBuildDragDelay;
}

// FUNCTION: LEGORACERS 0x00473c40
void CarBuildScreen::VTable0xa4()
{
	if (m_unk0x2b20.GetStateFlags() & 4) {
		m_unk0x2b20.VTable0x58(0);
	}

	if (m_unk0x2d48.GetStateFlags() & 4) {
		m_unk0x2d48.VTable0x58(0);
	}

	m_cursorHelper->SetCursorEnabled(TRUE);
}

// FUNCTION: LEGORACERS 0x00473c90
void CarBuildScreen::VTable0xb4()
{
	m_unk0x4a4.VTable0x48(0);
	m_unk0xfec.VTable0x48(0);
	m_unk0x2d48.VTable0x48(0);
	m_unk0x2f70.VTable0x48(0);
	m_unk0x318c.VTable0x48(0);
	m_unk0x33a8.VTable0x48(0);
	m_unk0x39fc.VTable0x48(0);
	m_unk0x2b20.VTable0x4c(5);
}

// FUNCTION: LEGORACERS 0x00473d20
void CarBuildScreen::VTable0xb8()
{
	if (m_unk0x2b20.GetStateFlags() & 4) {
		m_unk0x2b20.VTable0x58(5);
	}

	m_unk0x4a4.VTable0x44(0);
	m_unk0xfec.VTable0x44(0);
	m_unk0x2d48.VTable0x44(0);
	m_unk0x2f70.VTable0x44(0);
	m_unk0x318c.VTable0x44(0);
	m_unk0x33a8.VTable0x44(0);
	m_unk0x39fc.VTable0x44(0);
	m_cursorHelper->SetCursorEnabled(TRUE);
}

// FUNCTION: LEGORACERS 0x00473dc0
void CarBuildScreen::VTable0xac()
{
	m_unk0x4a4.VTable0x48(0);
	m_unk0xfec.VTable0x48(0);
	m_unk0x2b20.VTable0x48(0);
	m_unk0x2f70.VTable0x48(0);
	m_unk0x318c.VTable0x48(0);
	m_unk0x33a8.VTable0x48(0);
	m_unk0x2d48.VTable0x4c(5);
	m_cursorHelper->SetCursorEnabled(FALSE);
}

// FUNCTION: LEGORACERS 0x00473e50
void CarBuildScreen::VTable0xb0()
{
	if (m_unk0x2d48.GetStateFlags() & 4) {
		m_unk0x2d48.VTable0x58(5);
	}

	m_unk0x4a4.VTable0x44(0);
	m_unk0xfec.VTable0x44(0);
	m_unk0x2b20.VTable0x44(0);
	m_unk0x2f70.VTable0x44(0);
	m_unk0x318c.VTable0x44(0);
	m_unk0x33a8.VTable0x44(0);
	m_cursorHelper->SetCursorEnabled(TRUE);
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void CarBuildScreen::VTable0xa8()
{
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void CarBuildScreen::VTable0xbc()
{
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void CarBuildScreen::VTable0xc0()
{
}

// FUNCTION: LEGORACERS 0x00473ee0
LegoBool32 CarBuildScreen::FUN_00473ee0(MenuWidget*, InputEventQueue::Event* p_event, undefined4, undefined4)
{
	LegoU32 keyCode = p_event->m_keyCode;
	LegoU32 sound = 0;
	if ((keyCode & InputDevice::c_sourceMask) != InputDevice::c_sourceKeyboard) {
		return FALSE;
	}

	LegoS32 categoryIndex = m_unk0x2308.GetUnk0x298();
	undefined4 nextMode = 1;
	LegoBool32 result = TRUE;
	LegoBool32 moved;
	SoundVector position;

	switch (keyCode) {
	case c_carBuildKeyboardLeft:
		FUN_004773e0(
			g_carBuildDragHorizontalOffsets[categoryIndex * 8 + 6],
			g_carBuildDragVerticalOffsets[categoryIndex * 8 + 6],
			0x10,
			FALSE
		);
		break;
	case c_carBuildKeyboardRight:
		FUN_004773e0(
			g_carBuildDragHorizontalOffsets[categoryIndex * 8 + 2],
			g_carBuildDragVerticalOffsets[categoryIndex * 8 + 2],
			0x10,
			FALSE
		);
		break;
	case c_carBuildKeyboardDown:
		FUN_004773e0(
			g_carBuildDragHorizontalOffsets[categoryIndex * 8 + 4],
			g_carBuildDragVerticalOffsets[categoryIndex * 8 + 4],
			0x10,
			FALSE
		);
		break;
	case c_carBuildKeyboardUp:
		FUN_004773e0(
			g_carBuildDragHorizontalOffsets[categoryIndex * 8],
			g_carBuildDragVerticalOffsets[categoryIndex * 8],
			0x10,
			FALSE
		);
		break;
	case c_carBuildKeyboardEnd:
		FUN_004773e0(
			g_carBuildDragHorizontalOffsets[categoryIndex * 8 + 5],
			g_carBuildDragVerticalOffsets[categoryIndex * 8 + 5],
			0x10,
			TRUE
		);
		break;
	case c_carBuildKeyboardPageDownNum:
		FUN_004773e0(
			g_carBuildDragHorizontalOffsets[categoryIndex * 8 + 3],
			g_carBuildDragVerticalOffsets[categoryIndex * 8 + 3],
			0x10,
			TRUE
		);
		break;
	case c_carBuildKeyboardNumpad7:
		FUN_004773e0(
			g_carBuildDragHorizontalOffsets[categoryIndex * 8 + 7],
			g_carBuildDragVerticalOffsets[categoryIndex * 8 + 7],
			0x10,
			TRUE
		);
		break;
	case c_carBuildKeyboardPageUpNum:
		FUN_004773e0(
			g_carBuildDragHorizontalOffsets[categoryIndex * 8 + 1],
			g_carBuildDragVerticalOffsets[categoryIndex * 8 + 1],
			0x10,
			TRUE
		);
		break;
	case c_carBuildKeyboardNumpad5:
		m_unk0x2308.FUN_00478560();
		sound = 0x16;
		break;
	case c_carBuildKeyboardA:
		moved = m_unk0x2308.FUN_00478080(-1, TRUE);
		goto playMovementSound;
	case c_carBuildKeyboardD:
		moved = m_unk0x2308.FUN_00478080(1, TRUE);
		goto playMovementSound;
	case c_carBuildKeyboardS:
		moved = m_unk0x2308.FUN_004782f0(1, TRUE);
		goto playMovementSound;
	case c_carBuildKeyboardX:
		moved = m_unk0x2308.FUN_004782f0(-1, TRUE);

	playMovementSound: {
		LegoU32 spatialSound;
		LegoFloat volume;
		if (moved) {
			spatialSound = 6;
			volume = 0.6f;
		}
		else {
			spatialSound = 8;
			volume = 0.7f;
		}

		position.m_x = 0.0f;
		position.m_y = 0.0f;
		position.m_z = 0.0f;
		m_soundGroupBinding->FUN_0046e9a0(spatialSound & 0xffff, &position, 100.0f, 200.0f, volume, 1.0f);
		m_unk0x2ae4 = nextMode;
		return result;
	}
	case c_carBuildKeyboardPlus:
		if (m_unk0x2308.FUN_00478730()) {
			nextMode = 6;
			m_unk0x2adc = 4;
		}
		break;
	case c_carBuildKeyboardMinus:
		if (FUN_00477540()) {
			nextMode = 5;
		}
		break;
	case c_carBuildKeyboardInsert:
		if (!(m_unk0x4a4.GetStateFlags() & MenuIcon::c_flagBit2)) {
			m_unk0x4a4.GetUnk0x1ac().VTable0x54(1);
			m_unk0x4a4.FUN_00467180(0);
		}
		break;
	case c_carBuildKeyboardPageUp:
		if (!(m_unk0x4a4.GetStateFlags() & MenuIcon::c_flagBit2)) {
			m_unk0x4a4.GetUnk0x3c8().VTable0x54(1);
			m_unk0x4a4.FUN_004671e0(0);
		}
		break;
	case c_carBuildKeyboardDelete:
		if (!(m_unk0xfec.GetStateFlags() & MenuIcon::c_flagBit2)) {
			m_unk0xfec.GetUnk0x1ac().VTable0x54(1);
			m_unk0xfec.FUN_00467180(0);
		}
		break;
	case c_carBuildKeyboardPageDown:
		if (!(m_unk0xfec.GetStateFlags() & MenuIcon::c_flagBit2)) {
			m_unk0xfec.GetUnk0x3c8().VTable0x54(1);
			m_unk0xfec.FUN_004671e0(0);
		}
		break;
	default:
		nextMode = m_unk0x2ae0;
		result = FALSE;
		break;
	}

	m_soundGroupBinding->FUN_0046e970(sound & 0xffff);
	m_unk0x2ae4 = nextMode;
	return result;
}

// FUNCTION: LEGORACERS 0x00474330
LegoBool32 CarBuildScreen::FUN_00474330(MenuWidget*, InputEventQueue::Event* p_event, undefined4, undefined4)
{
	LegoU32 keyCode = p_event->m_keyCode;
	if ((keyCode & InputDevice::c_sourceMask) != InputDevice::c_sourceKeyboard) {
		return FALSE;
	}

	LegoBool32 result = TRUE;
	switch (keyCode) {
	case c_carBuildKeyboardInsert:
		m_unk0x4a4.GetUnk0x1ac().VTable0x58(1);
		break;
	case c_carBuildKeyboardPageUp:
		m_unk0x4a4.GetUnk0x3c8().VTable0x58(1);
		break;
	case c_carBuildKeyboardDelete:
		m_unk0xfec.GetUnk0x1ac().VTable0x58(1);
		break;
	case c_carBuildKeyboardPageDown:
		m_unk0xfec.GetUnk0x3c8().VTable0x58(1);
		break;
	default:
		result = FALSE;
		break;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x004743f0
LegoBool32 CarBuildScreen::FUN_004743f0(InputEventQueue::Event* p_event, undefined4 p_unk0x08, undefined4 p_unk0x0c)
{
	switch (p_event->m_keyCode) {
	default:
		return FALSE;
	case c_carBuildMouseButton1: {
		CopperCrest0x40::Helper0x44* helper = m_cursorHelper;
		LegoS32 x = helper->m_cursorX + helper->m_originX;
		LegoS32 y = helper->m_cursorY + helper->m_originY;

		if (FUN_00473a20(m_unk0x35c4.GetRect(), x, y)) {
			m_unk0x2308.FUN_00478560();
			m_soundGroupBinding->FUN_0046e970(0x16);
			return TRUE;
		}
		break;
	}
	case c_carBuildMouseButton0:
		return FUN_00473a50(p_event, p_unk0x08, p_unk0x0c);
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00474470
LegoBool32 CarBuildScreen::FUN_00474470(
	MenuWidget* p_source,
	InputEventQueue::Event* p_event,
	undefined4 p_unk0x0c,
	undefined4 p_unk0x10
)
{
	if (p_source == GetUnk0xd8()) {
		return FUN_004743f0(p_event, p_unk0x0c, p_unk0x10);
	}

	if (p_source == &m_partCarousel) {
		VTable0x44(&m_unk0xfec);
		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x004744c0
LegoBool32 CarBuildScreen::VTable0x18(
	MenuWidget* p_source,
	InputEventQueue::Event* p_event,
	undefined4 p_unk0x0c,
	undefined4 p_unk0x10
)
{
	if (m_unk0x2ae0 != 6) {
		if (!m_unk0x364) {
			CarBuildScreenBase::VTable0x18(p_source, p_event, p_unk0x0c, p_unk0x10);
			if (p_source != GetUnk0xd8() || !FUN_00473ee0(p_source, p_event, p_unk0x0c, p_unk0x10)) {
				switch (m_unk0x2ae0) {
				case 1:
					return FUN_00474470(p_source, p_event, p_unk0x0c, p_unk0x10);
				case 2:
					return FALSE;
				case 3:
					return FALSE;
				default:
					return FALSE;
				}
			}
		}
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00474550
LegoBool32 CarBuildScreen::VTable0x1c(
	MenuWidget* p_source,
	InputEventQueue::Event* p_event,
	undefined4 p_unk0x0c,
	undefined4 p_unk0x10
)
{
	if (m_unk0x2ae0 == 6) {
		return TRUE;
	}

	CarBuildScreenBase::VTable0x1c(p_source, p_event, p_unk0x0c, p_unk0x10);
	if (p_source == GetUnk0xd8() && FUN_00474330(p_source, p_event, p_unk0x0c, p_unk0x10)) {
		return TRUE;
	}

	if ((p_event->m_keyCode & InputDevice::c_sourceMask) == InputDevice::c_sourceMouse) {
		m_unk0x2ae4 = 1;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x004745e0
void CarBuildScreen::VTable0x20(MenuWidget* p_source)
{
	if (p_source == GetUnk0xd8()) {
		switch (m_unk0x2ae4) {
		case 2:
			m_soundGroupBinding->FUN_0046e970(5);
			break;
		case 3:
			m_soundGroupBinding->FUN_0046e970(17);
			break;
		default:
			return;
		}

		m_cursorHelper->SetCursorEnabled(FALSE);
	}

	if (p_source == &m_unk0x2b20) {
		m_cursorHelper->SetCursorEnabled(FALSE);
	}
}

// FUNCTION: LEGORACERS 0x00474640
void CarBuildScreen::VTable0x24(MenuWidget* p_source)
{
	if (p_source == GetUnk0xd8()) {
		switch (m_unk0x2ae0) {
		case 2:
			m_unk0x2308.FUN_00478120();
			m_unk0x2308.FUN_004783d0();
			m_soundGroupBinding->FUN_0046e970(5);
			break;
		case 3:
			m_soundGroupBinding->FUN_0046e970(17);
			break;
		default:
			return;
		}

		m_cursorHelper->SetCursorEnabled(TRUE);
	}

	if (p_source == &m_unk0x2b20) {
		m_cursorHelper->SetCursorEnabled(TRUE);
	}
}

// FUNCTION: LEGORACERS 0x004746c0
undefined4 CarBuildScreen::VTable0x28(MenuWidget* p_source, void*, undefined4 p_unk0x0c, undefined4 p_unk0x10)
{
	if (p_source == GetUnk0xd8()) {
		switch (m_unk0x2ae0) {
		case 2:
			FUN_004774e0(p_unk0x0c, p_unk0x10);
			break;
		case 3:
			FUN_00473b80(p_unk0x0c, p_unk0x10);
			return 1;
		}
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x00474710
void CarBuildScreen::VTable0x34(MenuIcon* p_icon)
{
	m_unk0x35c = NULL;
	if (p_icon == &m_unk0x2b20) {
		m_unk0x2ae4 = 3;
	}
	else if (p_icon == &m_unk0x2d48) {
		m_unk0x2ae4 = 2;
	}
}

// FUNCTION: LEGORACERS 0x00474750
void CarBuildScreen::VTable0x38(MenuWidget* p_source)
{
	if (m_unk0x2ae0 != 6) {
		m_unk0x35c = p_source;
		m_unk0x2ae4 = 1;

		if (p_source == &m_unk0x2f70) {
			if (m_unk0x2308.FUN_00478730()) {
				m_unk0x2ae4 = 6;
				m_unk0x2adc = 4;
			}
			return;
		}
		else if (p_source == &m_unk0x318c) {
			m_unk0x2308.FUN_00478560();
			m_soundGroupBinding->FUN_0046e970(0x16);
			return;
		}
		else if (p_source == &m_unk0x33a8) {
			if (FUN_00477540()) {
				m_unk0x2ae4 = 5;
			}
			return;
		}
		else if (p_source == &m_unk0x39fc) {
			m_unk0x360 = 0x11;
			m_unk0x364 = 1;
			return;
		}
	}

	CarModelScreenBase::VTable0x38(p_source);
}

// FUNCTION: LEGORACERS 0x00474820
void CarBuildScreen::VTable0x44(MenuWidget* p_source)
{
	LegoU32 sound = 0;

	if (p_source == &m_unk0x2b20) {
		LegoU32 index = m_unk0x2b20.GetUnk0x224();
		LegoS32 categoryIndex = m_unk0x2308.GetUnk0x298();
		LegoU32 regionId = index;
		index--;
		LegoS32 tableIndex = index + (categoryIndex * 8);

		if (regionId) {
			LegoU32 direction = index & 1;
			LegoS32 verticalOffset = g_carBuildDragVerticalOffsets[tableIndex];
			LegoS32 horizontalOffset = g_carBuildDragHorizontalOffsets[tableIndex];

			FUN_004773e0(horizontalOffset, verticalOffset, 0x10, direction);
		}

		m_unk0x3c1c = c_carBuildDragDelay;
	}
	else if (p_source == &m_unk0x2d48) {
		switch (m_unk0x2d48.GetUnk0x224()) {
		case 1:
			if (m_unk0x2308.FUN_004782f0(1, TRUE)) {
				sound = 6;
			}
			break;
		case 3:
			if (m_unk0x2308.FUN_00478080(1, TRUE)) {
				sound = 6;
			}
			break;
		case 5:
			if (m_unk0x2308.FUN_004782f0(-1, TRUE)) {
				sound = 6;
			}
			break;
		case 7:
			if (m_unk0x2308.FUN_00478080(-1, TRUE)) {
				sound = 6;
			}
			break;
		case 9:
			m_unk0x2308.FUN_004784d0(TRUE);
			break;
		}

		m_soundGroupBinding->FUN_0046e970(sound & 0xffff);
	}
	else {
		CarModelScreenBase::VTable0x44(p_source);
	}
}

// FUNCTION: LEGORACERS 0x00474940
void CarBuildScreen::FUN_00474940()
{
	CopperCrest0x40::Helper0x44* helper = m_cursorHelper;
	if (!helper || !helper->m_isCursorVisible) {
		return;
	}

	Rect rect;
	m_unk0x1e30.FUN_00465b60(m_unk0x2308.GetUnk0x58(), &rect);
	m_unk0x37e0.VTable0x10(&rect);
	m_unk0x1e30.FUN_00465b60(m_unk0x2308.GetUnk0x1a4(), &rect);
	m_unk0x35c4.VTable0x10(&rect);

	LegoS32 x = helper->m_cursorX + helper->m_originX;
	LegoS32 y = helper->m_cursorY + helper->m_originY;

	if (FUN_00473a20(m_unk0x1e30.GetGlobalRect(), x, y)) {
		if (FUN_00473a20(m_unk0x35c4.GetRect(), x, y)) {
			if (m_unk0x2308.GetUnk0x294() != 1) {
				m_unk0x374 = NULL;
				m_unk0x37e0.VTable0x50(6);
				m_unk0x35c4.VTable0x4c(6);
				m_unk0x2308.FUN_00479310();
			}
			return;
		}

		if (FUN_00473a20(m_unk0x37e0.GetRect(), x, y)) {
			if (m_unk0x2308.GetUnk0x294() != 2) {
				m_unk0x374 = NULL;
				m_unk0x35c4.VTable0x50(6);
				m_unk0x37e0.VTable0x4c(6);
				m_unk0x2308.FUN_00479300();
			}
			return;
		}
	}

	if ((m_unk0x35c4.GetStateFlags() & MenuIcon::c_flagBit1) || (m_unk0x37e0.GetStateFlags() & MenuIcon::c_flagBit1)) {
		m_unk0x35c4.VTable0x50(7);
		m_unk0x37e0.VTable0x50(7);
		m_unk0x374 = NULL;
		CarModelScreenBase::VTable0x78(0);
		m_unk0x374 = m_unk0xd8.FUN_00471f90();
		m_unk0x358 = m_unk0x374;
	}

	m_unk0x2308.FUN_00479320();
}

// FUNCTION: LEGORACERS 0x00474b10
LegoBool32 CarBuildScreen::VTable0x78(undefined4 p_elapsed)
{
	FUN_00474940();

	if (p_elapsed >= m_unk0x3c18) {
		m_unk0x3c18 = 0;
	}
	else {
		m_unk0x3c18 -= p_elapsed;
	}

	if (p_elapsed >= m_unk0x3c1c) {
		m_unk0x3c1c = 0;
	}
	else {
		m_unk0x3c1c -= p_elapsed;
	}

	return CarModelScreenBase::VTable0x78(p_elapsed);
}

// FUNCTION: LEGORACERS 0x00474b70
GolString* CarBuildScreen::VTable0x98(undefined4 p_index)
{
	if (!p_index) {
		return NULL;
	}

	m_unk0x3c20.CopyStringByIndex(&m_unk0x3a8, g_carBuildTextIds[p_index]);
	return &m_unk0x3a8;
}

// FUNCTION: LEGORACERS 0x00474ba0
GolFont0xa0* CarBuildScreen::VTable0x9c(undefined4 p_unk0x04)
{
	if (!p_unk0x04) {
		return NULL;
	}

	LegoChar fontName[sizeof(g_carBuildHelpFontName)];
	::memcpy(fontName, g_carBuildHelpFontName, sizeof(fontName));
	return m_renderer->FindFontByName(fontName);
}

// FUNCTION: LEGORACERS 0x00474be0
void CarBuildScreen::VTable0xa0(LegoS32*, LegoS32*, LegoS32* p_unk0x0c, LegoS32*)
{
	*p_unk0x0c = 0;
}

// FUNCTION: LEGORACERS 0x004774e0
void CarBuildScreen::FUN_004774e0(LegoS32 p_deltaX, LegoS32 p_deltaY)
{
	if (m_unk0x2ae0 == 6) {
		return;
	}

	if (p_deltaX) {
		m_unk0x2308.FUN_00477fc0(-(static_cast<LegoFloat>(p_deltaX) * g_carBuildPreviewMouseScale));
	}

	if (p_deltaY) {
		m_unk0x2308.FUN_00478180(static_cast<LegoFloat>(p_deltaY) * g_carBuildPreviewMouseScale);
	}
}

// FUNCTION: LEGORACERS 0x00477540
LegoBool32 CarBuildScreen::FUN_00477540()
{
	if (m_unk0x2ae0 != 6) {
		LegoS32 carSetPartId;
		LegoS32 pieceType;
		LegoS32 colorRecordIndex;
		m_unk0x2308.FUN_004787e0(&carSetPartId, &pieceType, &colorRecordIndex);

		if (carSetPartId) {
			CarPartCarousel* partCarousel = &m_partCarousel;
			partCarousel->SelectPartByType(carSetPartId);
			partCarousel->SelectChoice(pieceType, colorRecordIndex);

			m_unk0x410.FUN_0046d920(&m_unk0x19e0[m_context->m_unk0x21a4.GetSelectedEntry()->GetIndex()]);
			m_unk0x2308.FUN_00477e40(partCarousel->GetChoiceIndex(partCarousel->GetUnk0x6c()));
			m_unk0x2ae4 = 5;
			return TRUE;
		}
	}

	return FALSE;
}
