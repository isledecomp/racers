#ifndef NEWRACERSCREEN_H
#define NEWRACERSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/menugamescreen.h"
#include "menu/widgets/menuimage.h"
#include "menu/widgets/menutextbutton.h"

// VTABLE: LEGORACERS 0x004b3818
// SIZE 0x770
class NewRacerScreen : public MenuGameScreen {
public:
	NewRacerScreen();

	void VTable0x38(MenuWidget*) override;                                     // vtable+0x38
	void VTable0x4c() override;                                                // vtable+0x4c
	~NewRacerScreen() override;                                                // vtable+0x68
	LegoBool32 Destroy() override;                                             // vtable+0x74
	void VTable0x84() override;                                                // vtable+0x84
	LegoBool32 VTable0x8c(MenuGameContext*, MenuScreenCreateParams*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00482070
	// NewRacerScreen::`scalar deleting destructor'

protected:
	MenuImage m_unk0x368;      // 0x368
	MenuImage m_unk0x3c4;      // 0x3c4
	MenuImage m_unk0x420;      // 0x420
	MenuTextButton m_unk0x47c; // 0x47c
	LegoU32 m_unk0x76c;        // 0x76c
};

#endif // NEWRACERSCREEN_H
