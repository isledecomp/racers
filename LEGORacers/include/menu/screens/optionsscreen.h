#ifndef OPTIONSSCREEN_H
#define OPTIONSSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/menudialog.h"
#include "menu/screens/optionsscreenbase.h"
#include "menu/widgets/menucarousel.h"
#include "menu/widgets/menuselector.h"
#include "menu/widgets/menutextbutton.h"
#include "menu/widgets/menutextlabel.h"

// VTABLE: LEGORACERS 0x004b2b04
// SIZE 0x6750
class OptionsScreen : public OptionsScreenBase {
public:
	OptionsScreen();

	void VTable0x38(MenuWidget*) override;                                     // vtable+0x38
	void Reset() override;                                                     // vtable+0x54
	~OptionsScreen() override;                                                 // vtable+0x68
	LegoBool32 VTable0x8c(MenuGameContext*, MenuScreenCreateParams*) override; // vtable+0x8c
	void VTable0x98() override;                                                // vtable+0x98
	void VTable0x9c() override;                                                // vtable+0x9c
	void VTable0xa0() override;                                                // vtable+0xa0
	void VTable0xa4() override;                                                // vtable+0xa4

	// SYNTHETIC: LEGORACERS 0x004755f0
	// OptionsScreen::`scalar deleting destructor'

	// SIZE 0x64
	struct DriverNameBuffer {
		undefined2 m_data[0x32]; // 0x00
	};

protected:
	void FUN_00475a30();
	void FUN_00475aa0();
	void FUN_00475b10();

	MenuTextButton m_unk0x51ac;              // 0x51ac
	MenuTextButton m_unk0x549c;              // 0x549c
	MenuCarouselNavigator m_unk0x578c;       // 0x578c
	MenuSelector m_unk0x5820;                // 0x5820
	MenuDialog::TextLine m_unk0x6214[5];     // 0x6214
	DriverNameBuffer m_driverNameBuffers[5]; // 0x646c
	MenuTextLabel m_unk0x6660[2];            // 0x6660
};

#endif // OPTIONSSCREEN_H
