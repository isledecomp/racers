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

	void OnIconUnfocused(MenuWidget*) override;                                // vtable+0x38
	void OnIconSelected(MenuIcon*) override;                                   // vtable+0x3c
	void OnWidgetValueChanged(MenuWidget*) override;                           // vtable+0x44
	void CreateWidgets() override;                                             // vtable+0x4c
	void Reset() override;                                                     // vtable+0x54
	~RaceModeSetupScreen() override;                                           // vtable+0x68
	LegoBool32 Update(undefined4) override;                                    // vtable+0x78
	void Navigate() override;                                                  // vtable+0x84
	LegoBool32 Initialize(MenuGameContext*, MenuScreenCreateParams*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00487990
	// RaceModeSetupScreen::`scalar deleting destructor'

protected:
	LegoU32 FormatTime(LegoChar* p_buffer, LegoU32 p_time);
	void UpdateRacePreview();
	void UpdateBestTimePanel();

	MenuImage m_photoImage;                               // 0x1908
	MenuTextLabel m_infoLabel;                            // 0x1964
	MenuTextButton m_startButton;                         // 0x19dc
	MenuTextButton m_backButton;                          // 0x1ccc
	LegoU32 m_savedRacerCount;                            // 0x1fbc
	MenuCarouselNavigator m_raceCarousel;                 // 0x1fc0
	MenuSelector m_raceSelector;                          // 0x2054
	MenuTextLabel m_raceLabels[4];                        // 0x2a48
	MenuTextLabel m_timeLabel;                            // 0x2c28
	MenuTextLabel m_holderNameLabel;                      // 0x2ca0
	MenuTextLabel m_recordTypeLabel;                      // 0x2d18
	MenuTextLabel m_unlockedLabel;                        // 0x2d90
	LegoU32 m_recordToggleMs;                             // 0x2e08
	LegoU32 m_selectedRaceIndex;                          // 0x2e0c
	LegoBool32 m_showLapTime;                             // 0x2e10
	undefined2 m_holderNameBuffer[(0x2e32 - 0x2e14) / 2]; // 0x2e14
	undefined2 m_timeBuffer[(0x2e46 - 0x2e32) / 2];       // 0x2e32
	GolString m_holderNameString;                         // 0x2e48
	GolString m_timeString;                               // 0x2e54
};

#endif // RACEMODESETUPSCREEN_H
