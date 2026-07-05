#ifndef MENUSTATICWIDGET_H
#define MENUSTATICWIDGET_H

#include "compat.h"
#include "decomp.h"
#include "input/inputeventqueue.h"
#include "menu/widgets/menuwidget.h"

// VTABLE: LEGORACERS 0x004b263c
// SIZE 0x58
class MenuStaticWidget : public MenuWidget {
public:
	MenuStaticWidget();
	~MenuStaticWidget() override;                                                    // vtable+0x04
	MenuWidget* OnCursorEvent(void*, undefined4, undefined4) override;               // vtable+0x2c
	MenuWidget* OnKeyDown(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x30
	MenuWidget* OnKeyUp(InputEventQueue::Event*, undefined4, undefined4) override;   // vtable+0x34

	// SYNTHETIC: LEGORACERS 0x0046ea30
	// MenuStaticWidget::`scalar deleting destructor'
};

#endif // MENUSTATICWIDGET_H
