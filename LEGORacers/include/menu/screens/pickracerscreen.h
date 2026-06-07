#ifndef PICKRACERSCREEN_H
#define PICKRACERSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/racerpickscreenbase.h"
#include "menu/widgets/menuimage.h"
#include "menu/widgets/menutextbutton.h"

// VTABLE: LEGORACERS 0x004b3b68
// SIZE 0x4c8c
class PickRacerScreen : public RacerPickScreenBase {
public:
	PickRacerScreen();

	void VTable0x38(MenuWidget*) override;                                     // vtable+0x38
	void VTable0x44(MenuWidget*) override;                                     // vtable+0x44
	void VTable0x4c() override;                                                // vtable+0x4c
	~PickRacerScreen() override;                                               // vtable+0x68
	void VTable0x84() override;                                                // vtable+0x84
	LegoBool32 VTable0x8c(MenuGameContext*, MenuScreenCreateParams*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00484cc0
	// PickRacerScreen::`scalar deleting destructor'

protected:
	MenuImage m_unk0x3ff4;      // 0x3ff4
	MenuTextLabel m_unk0x4050;  // 0x4050
	MenuTextButton m_unk0x40c8; // 0x40c8
	MenuTextButton m_unk0x43b8; // 0x43b8
	MenuTextButton m_unk0x46a8; // 0x46a8
	MenuTextButton m_unk0x4998; // 0x4998
	undefined4 m_unk0x4c88;     // 0x4c88
};

#endif // PICKRACERSCREEN_H
