#ifndef MENUSCREENINTERFACE_H
#define MENUSCREENINTERFACE_H

#include "decomp.h"
#include "input/inputeventqueue.h"
#include "silverdune0x30.h"
#include "types.h"

class MenuIcon;
class MenuWidget;

union MenuEventResult {
	MenuWidget* m_widget;
	LegoBool32 m_result;

	MenuEventResult() {}
	MenuEventResult(MenuWidget* p_widget) : m_widget(p_widget) {}
	MenuEventResult(int p_result) : m_result(p_result) {}
	MenuEventResult(LegoBool32 p_result) : m_result(p_result) {}

	operator LegoBool32() const { return m_result; }
};

// VTABLE: LEGORACERS 0x004b2388
class MenuScreenInterface {
public:
	virtual void VTable0x00(MenuWidget*) = 0;                                      // vtable+0x00
	virtual void VTable0x04(MenuWidget*) = 0;                                      // vtable+0x04
	virtual void VTable0x08(MenuWidget*) = 0;                                      // vtable+0x08
	virtual void VTable0x0c(MenuWidget*) = 0;                                      // vtable+0x0c
	virtual void VTable0x10(MenuWidget*) = 0;                                      // vtable+0x10
	virtual undefined4 VTable0x14(MenuWidget*, void*, undefined4, undefined4) = 0; // vtable+0x14
	virtual LegoBool32 VTable0x18(MenuWidget*, InputEventQueue::Event*, undefined4,
								  undefined4) = 0; // vtable+0x18
	virtual LegoBool32 VTable0x1c(MenuWidget*, InputEventQueue::Event*, undefined4,
								  undefined4) = 0;                                 // vtable+0x1c
	virtual void VTable0x20(MenuWidget*) = 0;                                      // vtable+0x20
	virtual void VTable0x24(MenuWidget*) = 0;                                      // vtable+0x24
	virtual undefined4 VTable0x28(MenuWidget*, void*, undefined4, undefined4) = 0; // vtable+0x28
	virtual void VTable0x2c(MenuIcon*) = 0;                                        // vtable+0x2c
	virtual void VTable0x30(MenuIcon*) = 0;                                        // vtable+0x30
	virtual void VTable0x34(MenuIcon*) = 0;                                        // vtable+0x34
	virtual void VTable0x38(MenuWidget*) = 0;                                      // vtable+0x38
	virtual void VTable0x3c(MenuIcon*) = 0;                                        // vtable+0x3c
	virtual void VTable0x40(MenuIcon*) = 0;                                        // vtable+0x40
	virtual void VTable0x44(MenuWidget*) = 0;                                      // vtable+0x44
	virtual void VTable0x48(MenuWidget*) = 0;                                      // vtable+0x48
};

#endif // MENUSCREENINTERFACE_H
