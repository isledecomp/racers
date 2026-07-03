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
	m_helpStrings.ReleaseOwnedBuffers();
	Destroy();
}

// FUNCTION: LEGORACERS 0x004738a0
void CarBuildScreen::Reset()
{
	m_doubleClickMs = 0;
	m_dragDelayMs = 0;
	CarModelScreenBase::Reset();
}

// FUNCTION: LEGORACERS 0x004738c0
void CarBuildScreen::CreateWidgets()
{
	CarModelScreenBase::CreateWidgets();
	CreateHotspotButton(&m_movePad, 0xb5, 0xb5);
	CreateButton(&m_rotateButton, 0xb2, 0xb0);
	CreateButton(&m_placeButton, 0xb1, 0xb0);
	CreateButton(&m_undoButton, 0xb3, 0xb0);
	CreateHotspotButton(&m_viewPad, 0xb4, 0xb4);

	MenuButton* glyph0 = &m_pieceViewRegion;
	CreateButton(glyph0, 0xb8, 0xb0);

	MenuButton* glyph1 = &m_carViewRegion;
	CreateButton(glyph1, 0xb7, 0xb0);

	glyph0->ClearFlags(MenuIcon::c_flagSelected);
	glyph1->ClearFlags(MenuIcon::c_flagSelected);
	CreateButton(&m_doneButton, 0x3f, 0xb0);
}

// FUNCTION: LEGORACERS 0x004739a0
LegoBool32 CarBuildScreen::Initialize(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	if (!CarModelScreenBase::Initialize(p_context, p_createParams)) {
		return FALSE;
	}

	p_context->m_saveSystem.GetGameState().SetLanguageResourcePath();
	m_helpStrings.UseOwnedBuffers();
	m_helpStrings.Load("carbuild.srf");

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}

	m_categorySelector.Select(4);
	return m_initialized;
}

// FUNCTION: LEGORACERS 0x00473a20 FOLDED
LegoBool32 CarBuildScreen::PointInRect(Rect* p_rect, LegoS32 p_x, LegoS32 p_y)
{
	return p_x >= p_rect->m_left && p_x <= p_rect->m_right && p_y >= p_rect->m_top && p_y <= p_rect->m_bottom;
}

// FUNCTION: LEGORACERS 0x00473a50
LegoBool32 CarBuildScreen::HandleSceneClick(InputEventQueue::Event* p_event, undefined4 p_cursorX, undefined4 p_cursorY)
{
	if (p_event->m_isRepeat) {
		return FALSE;
	}

	LegoS32 x = static_cast<LegoS32>(p_cursorX);
	LegoS32 y = static_cast<LegoS32>(p_cursorY);

	if (!PointInRect(m_sceneView.GetGlobalRect(), x, y)) {
		return FALSE;
	}

	if (PointInRect(m_pieceViewRegion.GetRect(), x, y)) {
		if (m_doubleClickMs) {
			if (m_mode == c_modeBrowse) {
				if (m_partPlacement.CommitPiece()) {
					m_nextMode = c_modeBusy;
					m_carouselAction = 4;
				}

				m_doubleClickMs = 0;
				return TRUE;
			}
		}

		m_nextMode = c_modePieceView;
		m_doubleClickMs = c_carBuildClickDelay;
		m_rootIcon.SetFocus();

		if (m_partPlacement.GetFocusedPane() != 1) {
			m_partPlacement.FocusPiece();
		}

		return TRUE;
	}

	if (PointInRect(m_carViewRegion.GetRect(), x, y)) {
		m_nextMode = c_modeCarView;
		m_rootIcon.SetFocus();

		if (m_partPlacement.GetFocusedPane() != 2) {
			m_partPlacement.FocusCar();
		}

		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00473b80
void CarBuildScreen::HandleCursorDrag(LegoS32 p_deltaX, LegoS32 p_deltaY)
{
	if (m_dragDelayMs) {
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
	MovePieceByDrag(
		g_carBuildDragHorizontalOffsets[m_partPlacement.GetViewSlot() * 8 + index],
		g_carBuildDragVerticalOffsets[m_partPlacement.GetViewSlot() * 8 + index],
		index & 1,
		0
	);
	m_dragDelayMs = c_carBuildDragDelay;
}

// FUNCTION: LEGORACERS 0x00473c40
void CarBuildScreen::EnterBrowseMode()
{
	if (m_movePad.GetStateFlags() & 4) {
		m_movePad.Unfocus(0);
	}

	if (m_viewPad.GetStateFlags() & 4) {
		m_viewPad.Unfocus(0);
	}

	m_cursor->SetCursorEnabled(TRUE);
}

// FUNCTION: LEGORACERS 0x00473c90
void CarBuildScreen::EnterPieceViewMode()
{
	m_categorySelector.Disable(0);
	m_pieceSelector.Disable(0);
	m_viewPad.Disable(0);
	m_placeButton.Disable(0);
	m_rotateButton.Disable(0);
	m_undoButton.Disable(0);
	m_doneButton.Disable(0);
	m_movePad.Select(5);
}

// FUNCTION: LEGORACERS 0x00473d20
void CarBuildScreen::ExitPieceViewMode()
{
	if (m_movePad.GetStateFlags() & 4) {
		m_movePad.Unfocus(5);
	}

	m_categorySelector.Enable(0);
	m_pieceSelector.Enable(0);
	m_viewPad.Enable(0);
	m_placeButton.Enable(0);
	m_rotateButton.Enable(0);
	m_undoButton.Enable(0);
	m_doneButton.Enable(0);
	m_cursor->SetCursorEnabled(TRUE);
}

// FUNCTION: LEGORACERS 0x00473dc0
void CarBuildScreen::EnterCarViewMode()
{
	m_categorySelector.Disable(0);
	m_pieceSelector.Disable(0);
	m_movePad.Disable(0);
	m_placeButton.Disable(0);
	m_rotateButton.Disable(0);
	m_undoButton.Disable(0);
	m_viewPad.Select(5);
	m_cursor->SetCursorEnabled(FALSE);
}

// FUNCTION: LEGORACERS 0x00473e50
void CarBuildScreen::ExitCarViewMode()
{
	if (m_viewPad.GetStateFlags() & 4) {
		m_viewPad.Unfocus(5);
	}

	m_categorySelector.Enable(0);
	m_pieceSelector.Enable(0);
	m_movePad.Enable(0);
	m_placeButton.Enable(0);
	m_rotateButton.Enable(0);
	m_undoButton.Enable(0);
	m_cursor->SetCursorEnabled(TRUE);
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void CarBuildScreen::ExitBrowseMode()
{
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void CarBuildScreen::EnterBusyMode()
{
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void CarBuildScreen::ExitBusyMode()
{
}

// FUNCTION: LEGORACERS 0x00473ee0
LegoBool32 CarBuildScreen::HandleBuildKey(MenuWidget*, InputEventQueue::Event* p_event, undefined4, undefined4)
{
	LegoU32 keyCode = p_event->m_keyCode;
	LegoU32 sound = 0;
	if ((keyCode & InputDevice::c_sourceMask) != InputDevice::c_sourceKeyboard) {
		return FALSE;
	}

	LegoS32 categoryIndex = m_partPlacement.GetViewSlot();
	undefined4 nextMode = 1;
	LegoBool32 result = TRUE;
	LegoBool32 moved;
	SoundVector position;

	switch (keyCode) {
	case c_carBuildKeyboardLeft:
		MovePieceByDrag(
			g_carBuildDragHorizontalOffsets[categoryIndex * 8 + 6],
			g_carBuildDragVerticalOffsets[categoryIndex * 8 + 6],
			0x10,
			FALSE
		);
		break;
	case c_carBuildKeyboardRight:
		MovePieceByDrag(
			g_carBuildDragHorizontalOffsets[categoryIndex * 8 + 2],
			g_carBuildDragVerticalOffsets[categoryIndex * 8 + 2],
			0x10,
			FALSE
		);
		break;
	case c_carBuildKeyboardDown:
		MovePieceByDrag(
			g_carBuildDragHorizontalOffsets[categoryIndex * 8 + 4],
			g_carBuildDragVerticalOffsets[categoryIndex * 8 + 4],
			0x10,
			FALSE
		);
		break;
	case c_carBuildKeyboardUp:
		MovePieceByDrag(
			g_carBuildDragHorizontalOffsets[categoryIndex * 8],
			g_carBuildDragVerticalOffsets[categoryIndex * 8],
			0x10,
			FALSE
		);
		break;
	case c_carBuildKeyboardEnd:
		MovePieceByDrag(
			g_carBuildDragHorizontalOffsets[categoryIndex * 8 + 5],
			g_carBuildDragVerticalOffsets[categoryIndex * 8 + 5],
			0x10,
			TRUE
		);
		break;
	case c_carBuildKeyboardPageDownNum:
		MovePieceByDrag(
			g_carBuildDragHorizontalOffsets[categoryIndex * 8 + 3],
			g_carBuildDragVerticalOffsets[categoryIndex * 8 + 3],
			0x10,
			TRUE
		);
		break;
	case c_carBuildKeyboardNumpad7:
		MovePieceByDrag(
			g_carBuildDragHorizontalOffsets[categoryIndex * 8 + 7],
			g_carBuildDragVerticalOffsets[categoryIndex * 8 + 7],
			0x10,
			TRUE
		);
		break;
	case c_carBuildKeyboardPageUpNum:
		MovePieceByDrag(
			g_carBuildDragHorizontalOffsets[categoryIndex * 8 + 1],
			g_carBuildDragVerticalOffsets[categoryIndex * 8 + 1],
			0x10,
			TRUE
		);
		break;
	case c_carBuildKeyboardNumpad5:
		m_partPlacement.RotatePiece();
		sound = 0x16;
		break;
	case c_carBuildKeyboardA:
		moved = m_partPlacement.RotateViewStep(-1, TRUE);
		goto playMovementSound;
	case c_carBuildKeyboardD:
		moved = m_partPlacement.RotateViewStep(1, TRUE);
		goto playMovementSound;
	case c_carBuildKeyboardS:
		moved = m_partPlacement.PitchViewStep(1, TRUE);
		goto playMovementSound;
	case c_carBuildKeyboardX:
		moved = m_partPlacement.PitchViewStep(-1, TRUE);

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
		m_soundGroupBinding->PlaySpatialSound(spatialSound & 0xffff, &position, 100.0f, 200.0f, volume, 1.0f);
		m_nextMode = nextMode;
		return result;
	}
	case c_carBuildKeyboardPlus:
		if (m_partPlacement.CommitPiece()) {
			nextMode = 6;
			m_carouselAction = 4;
		}
		break;
	case c_carBuildKeyboardMinus:
		if (UndoPiece()) {
			nextMode = 5;
		}
		break;
	case c_carBuildKeyboardInsert:
		if (!(m_categorySelector.GetStateFlags() & MenuIcon::c_flagFocused)) {
			m_categorySelector.GetPrevButton().Focus(1);
			m_categorySelector.OnPreviousPressed(0);
		}
		break;
	case c_carBuildKeyboardPageUp:
		if (!(m_categorySelector.GetStateFlags() & MenuIcon::c_flagFocused)) {
			m_categorySelector.GetNextButton().Focus(1);
			m_categorySelector.OnNextPressed(0);
		}
		break;
	case c_carBuildKeyboardDelete:
		if (!(m_pieceSelector.GetStateFlags() & MenuIcon::c_flagFocused)) {
			m_pieceSelector.GetPrevButton().Focus(1);
			m_pieceSelector.OnPreviousPressed(0);
		}
		break;
	case c_carBuildKeyboardPageDown:
		if (!(m_pieceSelector.GetStateFlags() & MenuIcon::c_flagFocused)) {
			m_pieceSelector.GetNextButton().Focus(1);
			m_pieceSelector.OnNextPressed(0);
		}
		break;
	default:
		nextMode = m_mode;
		result = FALSE;
		break;
	}

	m_soundGroupBinding->PlaySoundByIndex(sound & 0xffff);
	m_nextMode = nextMode;
	return result;
}

// FUNCTION: LEGORACERS 0x00474330
LegoBool32 CarBuildScreen::HandleViewModeKey(MenuWidget*, InputEventQueue::Event* p_event, undefined4, undefined4)
{
	LegoU32 keyCode = p_event->m_keyCode;
	if ((keyCode & InputDevice::c_sourceMask) != InputDevice::c_sourceKeyboard) {
		return FALSE;
	}

	LegoBool32 result = TRUE;
	switch (keyCode) {
	case c_carBuildKeyboardInsert:
		m_categorySelector.GetPrevButton().Unfocus(1);
		break;
	case c_carBuildKeyboardPageUp:
		m_categorySelector.GetNextButton().Unfocus(1);
		break;
	case c_carBuildKeyboardDelete:
		m_pieceSelector.GetPrevButton().Unfocus(1);
		break;
	case c_carBuildKeyboardPageDown:
		m_pieceSelector.GetNextButton().Unfocus(1);
		break;
	default:
		result = FALSE;
		break;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x004743f0
LegoBool32 CarBuildScreen::HandleMouseButton(
	InputEventQueue::Event* p_event,
	undefined4 p_cursorX,
	undefined4 p_cursorY
)
{
	switch (p_event->m_keyCode) {
	default:
		return FALSE;
	case c_carBuildMouseButton1: {
		MenuInputDispatcher::Cursor* cursor = m_cursor;
		LegoS32 x = cursor->m_cursorX + cursor->m_originX;
		LegoS32 y = cursor->m_cursorY + cursor->m_originY;

		if (PointInRect(m_pieceViewRegion.GetRect(), x, y)) {
			m_partPlacement.RotatePiece();
			m_soundGroupBinding->PlaySoundByIndex(0x16);
			return TRUE;
		}
		break;
	}
	case c_carBuildMouseButton0:
		return HandleSceneClick(p_event, p_cursorX, p_cursorY);
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00474470
LegoBool32 CarBuildScreen::RouteWidgetKeyUp(
	MenuWidget* p_source,
	InputEventQueue::Event* p_event,
	undefined4 p_cursorX,
	undefined4 p_cursorY
)
{
	if (p_source == GetRootIcon()) {
		return HandleMouseButton(p_event, p_cursorX, p_cursorY);
	}

	if (p_source == &m_partCarousel) {
		OnWidgetValueChanged(&m_pieceSelector);
		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x004744c0
LegoBool32 CarBuildScreen::HandleKeyDown(
	MenuWidget* p_source,
	InputEventQueue::Event* p_event,
	undefined4 p_cursorX,
	undefined4 p_cursorY
)
{
	if (m_mode != c_modeBusy) {
		if (!m_navPending) {
			CarBuildScreenBase::HandleKeyDown(p_source, p_event, p_cursorX, p_cursorY);
			if (p_source != GetRootIcon() || !HandleBuildKey(p_source, p_event, p_cursorX, p_cursorY)) {
				switch (m_mode) {
				case c_modeBrowse:
					return RouteWidgetKeyUp(p_source, p_event, p_cursorX, p_cursorY);
				case c_modeCarView:
					return FALSE;
				case c_modePieceView:
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
LegoBool32 CarBuildScreen::HandleKeyUp(
	MenuWidget* p_source,
	InputEventQueue::Event* p_event,
	undefined4 p_cursorX,
	undefined4 p_cursorY
)
{
	if (m_mode == c_modeBusy) {
		return TRUE;
	}

	CarBuildScreenBase::HandleKeyUp(p_source, p_event, p_cursorX, p_cursorY);
	if (p_source == GetRootIcon() && HandleViewModeKey(p_source, p_event, p_cursorX, p_cursorY)) {
		return TRUE;
	}

	if ((p_event->m_keyCode & InputDevice::c_sourceMask) == InputDevice::c_sourceMouse) {
		m_nextMode = c_modeBrowse;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x004745e0
void CarBuildScreen::OnWidgetFocused(MenuWidget* p_source)
{
	if (p_source == GetRootIcon()) {
		switch (m_nextMode) {
		case 2:
			m_soundGroupBinding->PlaySoundByIndex(5);
			break;
		case 3:
			m_soundGroupBinding->PlaySoundByIndex(17);
			break;
		default:
			return;
		}

		m_cursor->SetCursorEnabled(FALSE);
	}

	if (p_source == &m_movePad) {
		m_cursor->SetCursorEnabled(FALSE);
	}
}

// FUNCTION: LEGORACERS 0x00474640
void CarBuildScreen::OnWidgetUnfocused(MenuWidget* p_source)
{
	if (p_source == GetRootIcon()) {
		switch (m_mode) {
		case c_modeCarView:
			m_partPlacement.SnapViewRotation();
			m_partPlacement.SnapViewPitch();
			m_soundGroupBinding->PlaySoundByIndex(5);
			break;
		case c_modePieceView:
			m_soundGroupBinding->PlaySoundByIndex(17);
			break;
		default:
			return;
		}

		m_cursor->SetCursorEnabled(TRUE);
	}

	if (p_source == &m_movePad) {
		m_cursor->SetCursorEnabled(TRUE);
	}
}

// FUNCTION: LEGORACERS 0x004746c0
undefined4 CarBuildScreen::OnWidgetKeyDown(MenuWidget* p_source, void*, undefined4 p_cursorX, undefined4 p_cursorY)
{
	if (p_source == GetRootIcon()) {
		switch (m_mode) {
		case c_modeCarView:
			HandleViewDrag(p_cursorX, p_cursorY);
			break;
		case c_modePieceView:
			HandleCursorDrag(p_cursorX, p_cursorY);
			return 1;
		}
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x00474710
void CarBuildScreen::OnIconFocused(MenuIcon* p_icon)
{
	m_clickedWidget = NULL;
	if (p_icon == &m_movePad) {
		m_nextMode = c_modePieceView;
	}
	else if (p_icon == &m_viewPad) {
		m_nextMode = c_modeCarView;
	}
}

// FUNCTION: LEGORACERS 0x00474750
void CarBuildScreen::OnIconUnfocused(MenuWidget* p_source)
{
	if (m_mode != c_modeBusy) {
		m_clickedWidget = p_source;
		m_nextMode = c_modeBrowse;

		if (p_source == &m_placeButton) {
			if (m_partPlacement.CommitPiece()) {
				m_nextMode = c_modeBusy;
				m_carouselAction = 4;
			}
			return;
		}
		else if (p_source == &m_rotateButton) {
			m_partPlacement.RotatePiece();
			m_soundGroupBinding->PlaySoundByIndex(0x16);
			return;
		}
		else if (p_source == &m_undoButton) {
			if (UndoPiece()) {
				m_nextMode = c_modeResetView;
			}
			return;
		}
		else if (p_source == &m_doneButton) {
			m_nextMenuId = 0x11;
			m_navPending = 1;
			return;
		}
	}

	CarModelScreenBase::OnIconUnfocused(p_source);
}

// FUNCTION: LEGORACERS 0x00474820
void CarBuildScreen::OnWidgetValueChanged(MenuWidget* p_source)
{
	LegoU32 sound = 0;

	if (p_source == &m_movePad) {
		LegoU32 index = m_movePad.GetHotspotIndex();
		LegoS32 categoryIndex = m_partPlacement.GetViewSlot();
		LegoU32 regionId = index;
		index--;

		if (regionId) {
			MovePieceByDrag(
				g_carBuildDragHorizontalOffsets[index + (categoryIndex * 8)],
				g_carBuildDragVerticalOffsets[index + (categoryIndex * 8)],
				0x10,
				index & 1
			);
		}

		m_dragDelayMs = c_carBuildDragDelay;
	}
	else if (p_source == &m_viewPad) {
		switch (m_viewPad.GetHotspotIndex()) {
		case 1:
			if (m_partPlacement.PitchViewStep(1, TRUE)) {
				sound = 6;
			}
			break;
		case 3:
			if (m_partPlacement.RotateViewStep(1, TRUE)) {
				sound = 6;
			}
			break;
		case 5:
			if (m_partPlacement.PitchViewStep(-1, TRUE)) {
				sound = 6;
			}
			break;
		case 7:
			if (m_partPlacement.RotateViewStep(-1, TRUE)) {
				sound = 6;
			}
			break;
		case 9:
			m_partPlacement.BeginViewReset(TRUE);
			break;
		}

		m_soundGroupBinding->PlaySoundByIndex(sound & 0xffff);
	}
	else {
		CarModelScreenBase::OnWidgetValueChanged(p_source);
	}
}

// FUNCTION: LEGORACERS 0x00474940
void CarBuildScreen::UpdateHoverRegions()
{
	MenuInputDispatcher::Cursor* cursor = m_cursor;
	if (!cursor || !cursor->m_isCursorVisible) {
		return;
	}

	Rect rect;
	m_sceneView.GetEntityScreenRect(m_partPlacement.GetCarGroup(), &rect);
	m_carViewRegion.SetRect(&rect);
	m_sceneView.GetEntityScreenRect(m_partPlacement.GetPieceEntity(), &rect);
	m_pieceViewRegion.SetRect(&rect);

	LegoS32 x = cursor->m_cursorX + cursor->m_originX;
	LegoS32 y = cursor->m_cursorY + cursor->m_originY;

	if (PointInRect(m_sceneView.GetGlobalRect(), x, y)) {
		if (PointInRect(m_pieceViewRegion.GetRect(), x, y)) {
			if (m_partPlacement.GetFocusedPane() != 1) {
				m_hoverIcon = NULL;
				m_carViewRegion.Deselect(6);
				m_pieceViewRegion.Select(6);
				m_partPlacement.FocusPiece();
			}
			return;
		}

		if (PointInRect(m_carViewRegion.GetRect(), x, y)) {
			if (m_partPlacement.GetFocusedPane() != 2) {
				m_hoverIcon = NULL;
				m_pieceViewRegion.Deselect(6);
				m_carViewRegion.Select(6);
				m_partPlacement.FocusCar();
			}
			return;
		}
	}

	if ((m_pieceViewRegion.GetStateFlags() & MenuIcon::c_flagSelected) ||
		(m_carViewRegion.GetStateFlags() & MenuIcon::c_flagSelected)) {
		m_pieceViewRegion.Deselect(7);
		m_carViewRegion.Deselect(7);
		m_hoverIcon = NULL;
		CarModelScreenBase::Update(0);
		m_hoverIcon = m_rootIcon.FindSelectedLeaf();
		m_selectedIcon = m_hoverIcon;
	}

	m_partPlacement.ClearFocusPane();
}

// FUNCTION: LEGORACERS 0x00474b10
LegoBool32 CarBuildScreen::Update(undefined4 p_elapsed)
{
	UpdateHoverRegions();

	if (p_elapsed >= m_doubleClickMs) {
		m_doubleClickMs = 0;
	}
	else {
		m_doubleClickMs -= p_elapsed;
	}

	if (p_elapsed >= m_dragDelayMs) {
		m_dragDelayMs = 0;
	}
	else {
		m_dragDelayMs -= p_elapsed;
	}

	return CarModelScreenBase::Update(p_elapsed);
}

// FUNCTION: LEGORACERS 0x00474b70
GolString* CarBuildScreen::GetHelpString(undefined4 p_index)
{
	if (!p_index) {
		return NULL;
	}

	m_helpStrings.CopyStringByIndex(&m_tooltipText, g_carBuildTextIds[p_index]);
	return &m_tooltipText;
}

// FUNCTION: LEGORACERS 0x00474ba0
GolFont* CarBuildScreen::GetHelpFont(undefined4 p_helpStringId)
{
	if (!p_helpStringId) {
		return NULL;
	}

	LegoChar fontName[sizeof(g_carBuildHelpFontName)];
	::memcpy(fontName, g_carBuildHelpFontName, sizeof(fontName));
	return m_renderer->FindFontByName(fontName);
}

// FUNCTION: LEGORACERS 0x00474be0
void CarBuildScreen::GetTooltipLayout(LegoS32*, LegoS32*, LegoS32* p_wrapWidth, LegoS32*)
{
	*p_wrapWidth = 0;
}

// FUNCTION: LEGORACERS 0x004774e0
void CarBuildScreen::HandleViewDrag(LegoS32 p_deltaX, LegoS32 p_deltaY)
{
	if (m_mode == c_modeBusy) {
		return;
	}

	if (p_deltaX) {
		m_partPlacement.RotateViewAnalog(-(static_cast<LegoFloat>(p_deltaX) * g_carBuildPreviewMouseScale));
	}

	if (p_deltaY) {
		m_partPlacement.PitchViewAnalog(static_cast<LegoFloat>(p_deltaY) * g_carBuildPreviewMouseScale);
	}
}

// FUNCTION: LEGORACERS 0x00477540
LegoBool32 CarBuildScreen::UndoPiece()
{
	if (m_mode != c_modeBusy) {
		LegoS32 carSetPartId;
		LegoS32 pieceType;
		LegoS32 colorRecordIndex;
		m_partPlacement.UndoLastPiece(&carSetPartId, &pieceType, &colorRecordIndex);

		if (carSetPartId) {
			CarPartCarousel* partCarousel = &m_partCarousel;
			partCarousel->SelectPartByType(carSetPartId);
			partCarousel->SelectChoice(pieceType, colorRecordIndex);

			m_categoryCarousel.SelectChild(&m_categoryIcons[m_context->m_partSet.GetSelectedEntry()->GetIndex()]);
			m_partPlacement.SelectPieceChoice(partCarousel->GetChoiceIndex(partCarousel->GetSelectedIndex()));
			m_nextMode = c_modeResetView;
			return TRUE;
		}
	}

	return FALSE;
}
