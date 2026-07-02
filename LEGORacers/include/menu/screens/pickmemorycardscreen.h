#ifndef PICKMEMORYCARDSCREEN_H
#define PICKMEMORYCARDSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/menugamescreen.h"
#include "menu/widgets/menuimage.h"
#include "menu/widgets/menutextbutton.h"
#include "menu/widgets/menutextlabel.h"

// VTABLE: LEGORACERS 0x004b3ad0
// SIZE 0x2548
class PickMemoryCardScreen : public MenuGameScreen {
public:
	PickMemoryCardScreen();

	void OnIconUnfocused(MenuWidget*) override;                                // vtable+0x38
	void CreateWidgets() override;                                             // vtable+0x4c
	~PickMemoryCardScreen() override;                                          // vtable+0x68
	LegoBool32 Destroy() override;                                             // vtable+0x74
	LegoBool32 Update(undefined4) override;                                    // vtable+0x78
	void Navigate() override;                                                  // vtable+0x84
	LegoBool32 Initialize(MenuGameContext*, MenuScreenCreateParams*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00484800
	// PickMemoryCardScreen::`scalar deleting destructor'

protected:
	MenuImage m_photoImage;            // 0x0368
	MenuImage m_unk0x3c4;              // 0x03c4
	MenuImage m_unk0x420;              // 0x0420
	MenuTextLabel m_unk0x47c;          // 0x047c
	MenuTextButton m_slot0Button;      // 0x04f4
	MenuTextButton m_slot1Button;      // 0x07e4
	MenuTextButton m_slot2Button;      // 0x0ad4
	MenuTextButton m_slot3Button;      // 0x0dc4
	MenuTextButton m_noCardButton;     // 0x10b4
	MenuTextButton m_backButton;       // 0x13a4
	MenuTextButton m_unk0x1694;        // 0x1694
	MenuTextButton m_unk0x1984;        // 0x1984
	MenuTextButton m_confirmYesButton; // 0x1c74
	MenuTextButton m_confirmNoButton;  // 0x1f64
	MenuTextButton m_unk0x2254;        // 0x2254
	undefined4 m_unk0x2544;            // 0x2544
};

#endif // PICKMEMORYCARDSCREEN_H
