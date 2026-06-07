#ifndef OBSCUREANTHEM0X58
#define OBSCUREANTHEM0X58

#include "compat.h"
#include "decomp.h"
#include "menu/widgets/menuwidget.h"

// VTABLE: LEGORACERS 0x004b263c
// SIZE 0x58
class MenuStaticWidget : public MenuWidget {
public:
	MenuStaticWidget();
	~MenuStaticWidget() override;                                                     // vtable+0x04
	MenuWidget* VTable0x2c(void*, undefined4, undefined4) override;                   // vtable+0x2c
	MenuWidget* VTable0x30(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x30
	MenuWidget* VTable0x34(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x34

	// SYNTHETIC: LEGORACERS 0x0046ea30
	// MenuStaticWidget::`scalar deleting destructor'
};

#endif // OBSCUREANTHEM0X58
