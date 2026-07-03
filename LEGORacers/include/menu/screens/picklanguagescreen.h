#ifndef PICKLANGUAGESCREEN_H
#define PICKLANGUAGESCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/menugamescreen.h"
#include "menu/widgets/menucarousel.h"
#include "menu/widgets/menucarouselnavigator.h"
#include "menu/widgets/menuimage.h"
#include "menu/widgets/menuselector.h"
#include "menu/widgets/menutextbutton.h"
#include "menu/widgets/menutextlabel.h"

// VTABLE: LEGORACERS 0x004b3a38
// SIZE 0x15ec
class PickLanguageScreen : public MenuGameScreen {
public:
	PickLanguageScreen();

	void OnIconUnfocused(MenuWidget*) override;                                // vtable+0x38
	void OnWidgetValueChanged(MenuWidget*) override;                           // vtable+0x44
	void CreateWidgets() override;                                             // vtable+0x4c
	~PickLanguageScreen() override;                                            // vtable+0x68
	void Navigate() override;                                                  // vtable+0x84
	LegoBool32 Initialize(MenuGameContext*, MenuScreenCreateParams*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00484430
	// PickLanguageScreen::`scalar deleting destructor'

protected:
	MenuImage m_photoImage;                   // 0x0368
	MenuTextLabel m_infoLabel;                // 0x03c4
	MenuSelector m_languageSelector;          // 0x043c
	MenuCarouselNavigator m_languageCarousel; // 0x0e30
	MenuTextLabel m_languageLabels[9];        // 0x0ec4
	MenuTextButton m_backButton;              // 0x12fc
};

#endif // PICKLANGUAGESCREEN_H
