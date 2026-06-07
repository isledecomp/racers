#ifndef MAINMENUSCREEN_H
#define MAINMENUSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/mainmenumodelslot.h"
#include "menu/screens/menugamescreen.h"
#include "menu/widgets/menuimage.h"
#include "menu/widgets/menusceneview.h"
#include "menu/widgets/menutextbutton.h"
#include "menu/widgets/menutextlabel.h"

// VTABLE: LEGORACERS 0x004b36d8
// SIZE 0x2450
class MainMenuScreen : public MenuGameScreen {
public:
	MainMenuScreen();

	LegoBool32 VTable0x18(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x18
	LegoBool32 VTable0x1c(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x1c
	void VTable0x38(MenuWidget*) override;                                                        // vtable+0x38
	void VTable0x4c() override;                                                                   // vtable+0x4c
	void Reset() override;                                                                        // vtable+0x54
	~MainMenuScreen() override;                                                                   // vtable+0x68
	LegoBool32 Destroy() override;                                                                // vtable+0x74
	LegoBool32 VTable0x78(undefined4) override;                                                   // vtable+0x78
	void VTable0x84() override;                                                                   // vtable+0x84
	LegoBool32 VTable0x8c(MenuGameContext*, MenuScreenCreateParams*) override;                    // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00480cb0
	//  MainMenuScreen::`scalar deleting destructor'

protected:
	void FUN_00480e40();

	MenuImage m_unk0x368;                   // 0x0368
	MenuImage m_unk0x3c4;                   // 0x03c4
	MenuTextLabel m_unk0x420;               // 0x0420
	MenuTextButton m_unk0x498;              // 0x0498
	MenuTextButton m_unk0x788;              // 0x0788
	MenuTextButton m_unk0xa78;              // 0x0a78
	MenuTextButton m_unk0xd68;              // 0x0d68
	MenuTextButton m_unk0x1058;             // 0x1058
	MenuTextButton m_unk0x1348;             // 0x1348
	MenuTextButton m_unk0x1638;             // 0x1638
	MenuTextButton m_unk0x1928;             // 0x1928
	MenuTextButton m_unk0x1c18;             // 0x1c18
	MenuTextButton m_unk0x1f08;             // 0x1f08
	MenuSceneView m_unk0x21f8;              // 0x21f8
	undefined m_unk0x22d4[0x22dc - 0x22d4]; // 0x22d4
	MainMenuModelSlot m_unk0x22dc;          // 0x22dc
	GolAnimatedEntity* m_unk0x2438;         // 0x2438
	undefined4 m_unk0x243c;                 // 0x243c
	undefined4 m_unk0x2440;                 // 0x2440
	LegoU32 m_unk0x2444;                    // 0x2444
	LegoU32 m_unk0x2448;                    // 0x2448
	LegoU8 m_unk0x244c;                     // 0x244c
	undefined m_unk0x244d[0x2450 - 0x244d]; // 0x244d
};

#endif // MAINMENUSCREEN_H
