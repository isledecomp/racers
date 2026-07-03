#ifndef OPTIONSSCREEN_H
#define OPTIONSSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/menudialog.h"
#include "menu/screens/optionsscreenbase.h"
#include "menu/widgets/menucarousel.h"
#include "menu/widgets/menucarouselnavigator.h"
#include "menu/widgets/menuselector.h"
#include "menu/widgets/menutextbutton.h"
#include "menu/widgets/menutextlabel.h"

// VTABLE: LEGORACERS 0x004b2b04
// SIZE 0x6750
class OptionsScreen : public OptionsScreenBase {
public:
	OptionsScreen();

	void OnIconUnfocused(MenuWidget*) override;                                // vtable+0x38
	void Reset() override;                                                     // vtable+0x54
	~OptionsScreen() override;                                                 // vtable+0x68
	LegoBool32 Initialize(MenuGameContext*, MenuScreenCreateParams*) override; // vtable+0x8c
	void CreateVideoWidgets() override;                                        // vtable+0x98
	void ShowMainButtons() override;                                           // vtable+0x9c
	void HideMainButtons() override;                                           // vtable+0xa0
	void ApplyPageChange() override;                                           // vtable+0xa4

	// SYNTHETIC: LEGORACERS 0x004755f0
	// OptionsScreen::`scalar deleting destructor'

	// SIZE 0x64
	struct DriverNameBuffer {
		undefined2 m_data[0x32]; // 0x00
	};

protected:
	void ShowVideoWidgets();
	void HideVideoWidgets();
	void ApplyVideoDriver();

	MenuTextButton m_videoButton;            // 0x51ac
	MenuTextButton m_videoNoticePopup;       // 0x549c
	MenuCarouselNavigator m_driverCarousel;  // 0x578c
	MenuSelector m_driverSelector;           // 0x5820
	MenuDialog::TextLine m_driverLabels[5];  // 0x6214
	DriverNameBuffer m_driverNameBuffers[5]; // 0x646c
	MenuTextLabel m_videoLabels[2];          // 0x6660
};

#endif // OPTIONSSCREEN_H
