#ifndef OPTIONSSCREENBASE_H
#define OPTIONSSCREENBASE_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/menugamescreen.h"
#include "menu/widgets/menucarousel.h"
#include "menu/widgets/menuimage.h"
#include "menu/widgets/menuselector.h"
#include "menu/widgets/menutextbutton.h"
#include "menu/widgets/menutextlabel.h"
#include "menu/widgets/optionsrow.h"

class GameState;

// VTABLE: LEGORACERS 0x004b3920
// SIZE 0x51ac
class OptionsScreenBase : public MenuGameScreen {
public:
	OptionsScreenBase();

	void VTable0x38(MenuWidget*) override;                                     // vtable+0x38
	void VTable0x44(MenuWidget*) override;                                     // vtable+0x44
	void VTable0x4c() override;                                                // vtable+0x4c
	void Reset() override;                                                     // vtable+0x54
	~OptionsScreenBase() override;                                             // vtable+0x68
	LegoBool32 VTable0x78(undefined4) override;                                // vtable+0x78
	void VTable0x84() override;                                                // vtable+0x84
	LegoBool32 VTable0x8c(MenuGameContext*, MenuScreenCreateParams*) override; // vtable+0x8c
	virtual void VTable0x98();                                                 // vtable+0x98
	virtual void VTable0x9c();                                                 // vtable+0x9c
	virtual void VTable0xa0();                                                 // vtable+0xa0
	virtual void VTable0xa4();                                                 // vtable+0xa4

	// SYNTHETIC: LEGORACERS 0x00482bc0
	// OptionsScreenBase::`scalar deleting destructor'

protected:
	void FUN_00482e00();
	void FUN_00482e40();
	void FUN_00482ef0();
	void FUN_00483030();
	void FUN_004836a0();
	void FUN_00483730();
	void FUN_00483770();
	void FUN_00483800();

	LegoU8 m_unk0x368;                   // 0x0368
	LegoU8 m_unk0x369;                   // 0x0369
	undefined m_unk0x36a[0x36c - 0x36a]; // 0x036a
	undefined4 m_unk0x36c;               // 0x036c
	GameState* m_unk0x370;               // 0x0370
	MenuImage m_unk0x374;                // 0x0374
	MenuTextLabel m_unk0x3d0;            // 0x03d0
	MenuTextButton m_unk0x448;           // 0x0448
	MenuTextButton m_unk0x738;           // 0x0738
	MenuTextButton m_unk0xa28;           // 0x0a28
	MenuTextButton m_unk0xd18;           // 0x0d18
	MenuTextButton m_unk0x1008;          // 0x1008
	MenuTextButton m_unk0x12f8;          // 0x12f8
	MenuTextButton m_unk0x15e8;          // 0x15e8
	MenuTextButton m_unk0x18d8;          // 0x18d8
	MenuSelector m_unk0x1bc8;            // 0x1bc8
	MenuSelector m_unk0x25bc;            // 0x25bc
	MenuCarouselNavigator m_unk0x2fb0;   // 0x2fb0
	MenuCarouselNavigator m_unk0x3044;   // 0x3044
	MenuTextLabel m_unk0x30d8[6];        // 0x30d8
	MenuTextLabel m_unk0x33a8[5];        // 0x33a8
	MenuTextLabel m_unk0x3600[2];        // 0x3600
	MenuSelector m_unk0x36f0;            // 0x36f0
	MenuCarouselNavigator m_unk0x40e4;   // 0x40e4
	OptionsRow m_unk0x4178;              // 0x4178
	OptionsRow m_unk0x4864;              // 0x4864
	MenuTextLabel m_unk0x4f50;           // 0x4f50
	MenuTextLabel m_unk0x4fc8;           // 0x4fc8
	MenuTextLabel m_unk0x5040[3];        // 0x5040
	LegoS32 m_unk0x51a8;                 // 0x51a8
};

#endif // OPTIONSSCREENBASE_H
