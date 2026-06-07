#ifndef PICKLANGUAGESCREEN_H
#define PICKLANGUAGESCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/menugamescreen.h"
#include "menu/widgets/menucarousel.h"
#include "menu/widgets/menuimage.h"
#include "menu/widgets/menuselector.h"
#include "menu/widgets/menutextbutton.h"
#include "menu/widgets/menutextlabel.h"

// VTABLE: LEGORACERS 0x004b3a38
// SIZE 0x15ec
class PickLanguageScreen : public MenuGameScreen {
public:
	PickLanguageScreen();

	void VTable0x38(MenuWidget*) override;                                     // vtable+0x38
	void VTable0x44(MenuWidget*) override;                                     // vtable+0x44
	void VTable0x4c() override;                                                // vtable+0x4c
	~PickLanguageScreen() override;                                            // vtable+0x68
	void VTable0x84() override;                                                // vtable+0x84
	LegoBool32 VTable0x8c(MenuGameContext*, MenuScreenCreateParams*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00484430
	// PickLanguageScreen::`scalar deleting destructor'

protected:
	MenuImage m_unk0x368;             // 0x0368
	MenuTextLabel m_unk0x3c4;         // 0x03c4
	MenuSelector m_unk0x43c;          // 0x043c
	MenuCarouselNavigator m_unk0xe30; // 0x0e30
	MenuTextLabel m_unk0xec4[9];      // 0x0ec4
	MenuTextButton m_unk0x12fc;       // 0x12fc
};

#endif // PICKLANGUAGESCREEN_H
