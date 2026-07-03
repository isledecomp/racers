#ifndef OPTIONSSCREENBASE_H
#define OPTIONSSCREENBASE_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/menugamescreen.h"
#include "menu/widgets/menucarousel.h"
#include "menu/widgets/menucarouselnavigator.h"
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

	void OnIconUnfocused(MenuWidget*) override;                                // vtable+0x38
	void OnWidgetValueChanged(MenuWidget*) override;                           // vtable+0x44
	void CreateWidgets() override;                                             // vtable+0x4c
	void Reset() override;                                                     // vtable+0x54
	~OptionsScreenBase() override;                                             // vtable+0x68
	LegoBool32 Update(undefined4) override;                                    // vtable+0x78
	void Navigate() override;                                                  // vtable+0x84
	LegoBool32 Initialize(MenuGameContext*, MenuScreenCreateParams*) override; // vtable+0x8c
	virtual void CreateVideoWidgets();                                         // vtable+0x98
	virtual void ShowMainButtons();                                            // vtable+0x9c
	virtual void HideMainButtons();                                            // vtable+0xa0
	virtual void ApplyPageChange();                                            // vtable+0xa4

	// SYNTHETIC: LEGORACERS 0x00482bc0
	// OptionsScreenBase::`scalar deleting destructor'

protected:
	void CreateHeaderWidgets();
	void CreateMainButtons();
	void CreateGameOptionWidgets();
	void CreateAudioOptionWidgets();
	void ShowGameOptionWidgets();
	void HideGameOptionWidgets();
	void ShowAudioOptionWidgets();
	void HideAudioOptionWidgets();

	LegoU8 m_page;                              // 0x0368
	LegoU8 m_nextPage;                          // 0x0369
	undefined m_unk0x36a[0x36c - 0x36a];        // 0x036a
	undefined4 m_unk0x36c;                      // 0x036c
	GameState* m_gameState;                     // 0x0370
	MenuImage m_photoImage;                     // 0x0374
	MenuTextLabel m_infoLabel;                  // 0x03d0
	MenuTextButton m_gameOptionsButton;         // 0x0448
	MenuTextButton m_audioButton;               // 0x0738
	MenuTextButton m_controls1Button;           // 0x0a28
	MenuTextButton m_controls2Button;           // 0x0d18
	MenuTextButton m_creditsButton;             // 0x1008
	MenuTextButton m_languageButton;            // 0x12f8
	MenuTextButton m_audioNoticePopup;          // 0x15e8
	MenuTextButton m_backButton;                // 0x18d8
	MenuSelector m_racerCountSelector;          // 0x1bc8
	MenuSelector m_lapCountSelector;            // 0x25bc
	MenuCarouselNavigator m_racerCountCarousel; // 0x2fb0
	MenuCarouselNavigator m_lapCountCarousel;   // 0x3044
	MenuTextLabel m_racerCountLabels[6];        // 0x30d8
	MenuTextLabel m_lapCountLabels[5];          // 0x33a8
	MenuTextLabel m_gameOptionLabels[2];        // 0x3600
	MenuSelector m_stereoSelector;              // 0x36f0
	MenuCarouselNavigator m_stereoCarousel;     // 0x40e4
	OptionsRow m_musicVolumeSlider;             // 0x4178
	OptionsRow m_soundVolumeSlider;             // 0x4864
	MenuTextLabel m_stereoLabel;                // 0x4f50
	MenuTextLabel m_monoLabel;                  // 0x4fc8
	MenuTextLabel m_audioLabels[3];             // 0x5040
	LegoS32 m_driverCount;                      // 0x51a8
};

#endif // OPTIONSSCREENBASE_H
