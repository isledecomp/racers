#ifndef CONTROLCONFIGSCREEN_H
#define CONTROLCONFIGSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "golstring.h"
#include "menu/screens/menugamescreen.h"
#include "menu/widgets/menucarousel.h"
#include "menu/widgets/menuimage.h"
#include "menu/widgets/menuselector.h"
#include "menu/widgets/menutextbutton.h"
#include "menu/widgets/menutextlabel.h"

class InputDevice;

// VTABLE: LEGORACERS 0x004b3160
// SIZE 0x3360
class ControlConfigScreen : public MenuGameScreen {
public:
	ControlConfigScreen();

	LegoBool32 VTable0x18(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x18
	LegoBool32 VTable0x1c(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x1c
	void VTable0x34(MenuIcon*) override;                                                          // vtable+0x34
	void VTable0x38(MenuWidget*) override;                                                        // vtable+0x38
	void VTable0x44(MenuWidget*) override;                                                        // vtable+0x44
	void VTable0x4c() override;                                                                   // vtable+0x4c
	void Reset() override;                                                                        // vtable+0x54
	~ControlConfigScreen() override;                                                              // vtable+0x68
	LegoBool32 VTable0x78(undefined4) override;                                                   // vtable+0x78
	void VTable0x84() override;                                                                   // vtable+0x84
	LegoBool32 VTable0x8c(MenuGameContext*, MenuScreenCreateParams*) override;                    // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x0047a690
	// ControlConfigScreen::`scalar deleting destructor'

protected:
	void FUN_0047a930();
	void FUN_0047adb0();

	InputDevice* m_unk0x368[5];          // 0x0368
	LegoS32 m_unk0x37c[5];               // 0x037c
	MenuIcon* m_unk0x390;                // 0x0390
	undefined2* m_unk0x394;              // 0x0394
	undefined2* m_unk0x398;              // 0x0398
	LegoU32 m_unk0x39c;                  // 0x039c
	LegoS32 m_unk0x3a0;                  // 0x03a0
	LegoU32 m_unk0x3a4;                  // 0x03a4
	MenuImage m_unk0x3a8;                // 0x03a8
	MenuTextLabel m_unk0x404;            // 0x0404
	MenuTextButton m_unk0x47c;           // 0x047c
	undefined2 m_ellipsisText[9];        // 0x076c
	undefined m_unk0x77e[0x780 - 0x77e]; // 0x077e
	MenuCarouselNavigator m_unk0x780;    // 0x0780
	MenuSelector m_unk0x814;             // 0x0814
	MenuImage m_unk0x1208[5];            // 0x1208
	MenuTextLabel m_unk0x13d4;           // 0x13d4
	MenuTextButton m_unk0x144c[9];       // 0x144c
	MenuTextLabel m_unk0x2ebc[9];        // 0x2ebc
	GolString m_unk0x32f4[9];            // 0x32f4
};

#endif // CONTROLCONFIGSCREEN_H
