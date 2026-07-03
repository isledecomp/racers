#ifndef MENUSCREENINTERFACE_H
#define MENUSCREENINTERFACE_H

#include "decomp.h"
#include "golsurface.h"
#include "input/inputeventqueue.h"
#include "types.h"

class MenuIcon;
class MenuWidget;

union MenuEventResult {
	MenuWidget* m_widget; // 0x00
	LegoBool32 m_result;  // 0x00

	MenuEventResult() {}
	MenuEventResult(MenuWidget* p_widget) : m_widget(p_widget) {}
	MenuEventResult(int p_result) : m_result(p_result) {}
	MenuEventResult(LegoBool32 p_result) : m_result(p_result) {}

	operator LegoBool32() const { return m_result; }
};

// VTABLE: LEGORACERS 0x004b2388
class MenuScreenInterface {
public:
	virtual void OnWidgetCreated(MenuWidget*) = 0;                                    // vtable+0x00
	virtual void OnWidgetDestroyed(MenuWidget*) = 0;                                  // vtable+0x04
	virtual void OnWidgetMoved(MenuWidget*) = 0;                                      // vtable+0x08
	virtual void OnWidgetResized(MenuWidget*) = 0;                                    // vtable+0x0c
	virtual void OnCarouselSettled(MenuWidget*) = 0;                                  // vtable+0x10
	virtual undefined4 OnWidgetKeyUp(MenuWidget*, void*, undefined4, undefined4) = 0; // vtable+0x14
	virtual LegoBool32 HandleKeyDown(MenuWidget*, InputEventQueue::Event*, undefined4,
									 undefined4) = 0; // vtable+0x18
	virtual LegoBool32 HandleKeyUp(MenuWidget*, InputEventQueue::Event*, undefined4,
								   undefined4) = 0;                                     // vtable+0x1c
	virtual void OnWidgetFocused(MenuWidget*) = 0;                                      // vtable+0x20
	virtual void OnWidgetUnfocused(MenuWidget*) = 0;                                    // vtable+0x24
	virtual undefined4 OnWidgetKeyDown(MenuWidget*, void*, undefined4, undefined4) = 0; // vtable+0x28
	virtual void OnIconEnabled(MenuIcon*) = 0;                                          // vtable+0x2c
	virtual void OnIconDisabled(MenuIcon*) = 0;                                         // vtable+0x30
	virtual void OnIconFocused(MenuIcon*) = 0;                                          // vtable+0x34
	virtual void OnIconUnfocused(MenuWidget*) = 0;                                      // vtable+0x38
	virtual void OnIconSelected(MenuIcon*) = 0;                                         // vtable+0x3c
	virtual void OnIconDeselected(MenuIcon*) = 0;                                       // vtable+0x40
	virtual void OnWidgetValueChanged(MenuWidget*) = 0;                                 // vtable+0x44
	virtual void OnSelectorSettled(MenuWidget*) = 0;                                    // vtable+0x48
};

#endif // MENUSCREENINTERFACE_H
