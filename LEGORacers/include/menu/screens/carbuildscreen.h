#ifndef CARBUILDSCREEN_H
#define CARBUILDSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "golstringtable.h"
#include "menu/screens/carmodelscreenbase.h"
#include "menu/widgets/menubutton.h"
#include "menu/widgets/menuhotspotbutton.h"

// VTABLE: LEGORACERS 0x004b2a38
// SIZE 0x3c34
class CarBuildScreen : public CarModelScreenBase {
public:
	CarBuildScreen();

	LegoBool32 HandleKeyDown(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x18
	LegoBool32 HandleKeyUp(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4) override;   // vtable+0x1c
	void OnWidgetFocused(MenuWidget*) override;                                                      // vtable+0x20
	void OnWidgetUnfocused(MenuWidget*) override;                                                    // vtable+0x24
	undefined4 OnWidgetKeyDown(MenuWidget*, void*, undefined4, undefined4) override;                 // vtable+0x28
	void OnIconFocused(MenuIcon*) override;                                                          // vtable+0x34
	void OnIconUnfocused(MenuWidget*) override;                                                      // vtable+0x38
	void OnWidgetValueChanged(MenuWidget*) override;                                                 // vtable+0x44
	void CreateWidgets() override;                                                                   // vtable+0x4c
	void Reset() override;                                                                           // vtable+0x54
	~CarBuildScreen() override;                                                                      // vtable+0x68
	LegoBool32 Update(undefined4) override;                                                          // vtable+0x78
	LegoBool32 Initialize(MenuGameContext*, MenuScreenCreateParams*) override;                       // vtable+0x8c
	GolString* GetHelpString(undefined4) override;                                                   // vtable+0x98
	GolFont* GetHelpFont(undefined4) override;                                                       // vtable+0x9c
	void GetTooltipLayout(LegoS32*, LegoS32*, LegoS32*, LegoS32*) override;                          // vtable+0xa0
	void EnterBrowseMode() override;                                                                 // vtable+0xa4
	void ExitBrowseMode() override;                                                                  // vtable+0xa8
	void EnterCarViewMode() override;                                                                // vtable+0xac
	void ExitCarViewMode() override;                                                                 // vtable+0xb0
	void EnterPieceViewMode() override;                                                              // vtable+0xb4
	void ExitPieceViewMode() override;                                                               // vtable+0xb8
	void EnterBusyMode() override;                                                                   // vtable+0xbc
	void ExitBusyMode() override;                                                                    // vtable+0xc0

	// SYNTHETIC: LEGORACERS 0x00473790
	// CarBuildScreen::`scalar deleting destructor'

protected:
	enum {
		c_carBuildRegionSource = 0x50000000,
		c_carBuildDragThreshold = 5,
		c_carBuildDragDelay = 100,
		c_carBuildClickDelay = 500,
		c_carBuildKeyboardA = InputDevice::c_sourceKeyboard | 0x1e,
		c_carBuildKeyboardS = InputDevice::c_sourceKeyboard | 0x1f,
		c_carBuildKeyboardD = InputDevice::c_sourceKeyboard | 0x20,
		c_carBuildKeyboardX = InputDevice::c_sourceKeyboard | 0x2d,
		c_carBuildKeyboardNumpad7 = InputDevice::c_sourceKeyboard | 0x47,
		c_carBuildKeyboardUp = InputDevice::c_sourceKeyboard | 0x48,
		c_carBuildKeyboardPageUpNum = InputDevice::c_sourceKeyboard | 0x49,
		c_carBuildKeyboardMinus = InputDevice::c_sourceKeyboard | 0x4a,
		c_carBuildKeyboardLeft = InputDevice::c_sourceKeyboard | 0x4b,
		c_carBuildKeyboardNumpad5 = InputDevice::c_sourceKeyboard | 0x4c,
		c_carBuildKeyboardRight = InputDevice::c_sourceKeyboard | 0x4d,
		c_carBuildKeyboardPlus = InputDevice::c_sourceKeyboard | 0x4e,
		c_carBuildKeyboardEnd = InputDevice::c_sourceKeyboard | 0x4f,
		c_carBuildKeyboardDown = InputDevice::c_sourceKeyboard | 0x50,
		c_carBuildKeyboardPageDownNum = InputDevice::c_sourceKeyboard | 0x51,
		c_carBuildKeyboardPageUp = InputDevice::c_sourceKeyboard | 0xc9,
		c_carBuildKeyboardPageDown = InputDevice::c_sourceKeyboard | 0xd1,
		c_carBuildKeyboardInsert = InputDevice::c_sourceKeyboard | 0xd2,
		c_carBuildKeyboardDelete = InputDevice::c_sourceKeyboard | 0xd3,
		c_carBuildMouseButton0 = InputDevice::c_sourceMouse,
		c_carBuildMouseButton1 = InputDevice::c_sourceMouse | 1
	};

	LegoBool32 HandleSceneClick(InputEventQueue::Event* p_event, undefined4 p_cursorX, undefined4 p_cursorY);
	LegoBool32 PointInRect(Rect* p_rect, LegoS32 p_x, LegoS32 p_y);
	void HandleCursorDrag(LegoS32 p_deltaX, LegoS32 p_deltaY);
	LegoBool32 HandleBuildKey(
		MenuWidget* p_source,
		InputEventQueue::Event* p_event,
		undefined4 p_cursorX,
		undefined4 p_cursorY
	);
	LegoBool32 HandleViewModeKey(
		MenuWidget* p_source,
		InputEventQueue::Event* p_event,
		undefined4 p_cursorX,
		undefined4 p_cursorY
	);
	LegoBool32 HandleMouseButton(InputEventQueue::Event* p_event, undefined4 p_cursorX, undefined4 p_cursorY);
	LegoBool32 RouteWidgetKeyUp(
		MenuWidget* p_source,
		InputEventQueue::Event* p_event,
		undefined4 p_cursorX,
		undefined4 p_cursorY
	);
	void UpdateHoverRegions();
	void HandleViewDrag(LegoS32 p_deltaX, LegoS32 p_deltaY);
	LegoBool32 UndoPiece();

	MenuHotspotButton m_movePad;  // 0x2b20
	MenuHotspotButton m_viewPad;  // 0x2d48
	MenuButton m_placeButton;     // 0x2f70
	MenuButton m_rotateButton;    // 0x318c
	MenuButton m_undoButton;      // 0x33a8
	MenuButton m_pieceViewRegion; // 0x35c4
	MenuButton m_carViewRegion;   // 0x37e0
	MenuButton m_doneButton;      // 0x39fc
	LegoU32 m_doubleClickMs;      // 0x3c18
	LegoU32 m_dragDelayMs;        // 0x3c1c
	GolStringTable m_helpStrings; // 0x3c20
};

#endif // CARBUILDSCREEN_H
