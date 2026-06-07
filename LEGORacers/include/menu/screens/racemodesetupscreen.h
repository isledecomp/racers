#ifndef RACEMODESETUPSCREEN_H
#define RACEMODESETUPSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "golstring.h"
#include "menu/screens/singleraceselectbase.h"
#include "menu/widgets/menucarousel.h"
#include "menu/widgets/menuimage.h"
#include "menu/widgets/menuselector.h"
#include "menu/widgets/menutextbutton.h"
#include "menu/widgets/menutextlabel.h"

// VTABLE: LEGORACERS 0x004b3dc8
// SIZE 0x2e60
class RaceModeSetupScreen : public SingleRaceSelectBase {
public:
	RaceModeSetupScreen();

	void VTable0x38(MenuWidget*) override;                                     // vtable+0x38
	void VTable0x3c(MenuIcon*) override;                                       // vtable+0x3c
	void VTable0x44(MenuWidget*) override;                                     // vtable+0x44
	void VTable0x4c() override;                                                // vtable+0x4c
	void Reset() override;                                                     // vtable+0x54
	~RaceModeSetupScreen() override;                                           // vtable+0x68
	LegoBool32 VTable0x78(undefined4) override;                                // vtable+0x78
	void VTable0x84() override;                                                // vtable+0x84
	LegoBool32 VTable0x8c(MenuGameContext*, MenuScreenCreateParams*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00487990
	// RaceModeSetupScreen::`scalar deleting destructor'

protected:
	LegoU32 FUN_004246d0(LegoChar* p_buffer, LegoU32 p_time);
	void FUN_00488010();
	void FUN_004881a0();

	MenuImage m_unk0x1908;                         // 0x1908
	MenuTextLabel m_unk0x1964;                     // 0x1964
	MenuTextButton m_unk0x19dc;                    // 0x19dc
	MenuTextButton m_unk0x1ccc;                    // 0x1ccc
	LegoU32 m_unk0x1fbc;                           // 0x1fbc
	MenuCarouselNavigator m_unk0x1fc0;             // 0x1fc0
	MenuSelector m_unk0x2054;                      // 0x2054
	MenuTextLabel m_unk0x2a48[4];                  // 0x2a48
	MenuTextLabel m_unk0x2c28;                     // 0x2c28
	MenuTextLabel m_unk0x2ca0;                     // 0x2ca0
	MenuTextLabel m_unk0x2d18;                     // 0x2d18
	MenuTextLabel m_unk0x2d90;                     // 0x2d90
	LegoU32 m_unk0x2e08;                           // 0x2e08
	LegoU32 m_unk0x2e0c;                           // 0x2e0c
	LegoBool32 m_unk0x2e10;                        // 0x2e10
	undefined2 m_unk0x2e14[(0x2e32 - 0x2e14) / 2]; // 0x2e14
	undefined2 m_unk0x2e32[(0x2e46 - 0x2e32) / 2]; // 0x2e32
	GolString m_unk0x2e48;                         // 0x2e48
	GolString m_unk0x2e54;                         // 0x2e54
};

#endif // RACEMODESETUPSCREEN_H
