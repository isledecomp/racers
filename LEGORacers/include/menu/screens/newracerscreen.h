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

	void OnIconUnfocused(MenuWidget*) override;                                // vtable+0x38
	void CreateWidgets() override;                                             // vtable+0x4c
	~NewRacerScreen() override;                                                // vtable+0x68
	LegoBool32 Destroy() override;                                             // vtable+0x74
	void Navigate() override;                                                  // vtable+0x84
	LegoBool32 Initialize(MenuGameContext*, MenuScreenCreateParams*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00482070
	// NewRacerScreen::`scalar deleting destructor'

protected:
	MenuImage m_photoImage;       // 0x368
	MenuImage m_statusPanelImage; // 0x3c4
	MenuImage m_statusIconImage;  // 0x420
	MenuTextButton m_okButton;    // 0x47c
	LegoU32 m_saveSlot;           // 0x76c
};

#endif // NEWRACERSCREEN_H
