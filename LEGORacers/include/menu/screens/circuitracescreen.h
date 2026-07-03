#ifndef CIRCUITRACESCREEN_H
#define CIRCUITRACESCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/menuanimationlist.h"
#include "menu/screens/singleraceselectbase.h"
#include "menu/widgets/menuimage.h"
#include "menu/widgets/menutextbutton.h"
#include "menu/widgets/menutextlabel.h"

// VTABLE: LEGORACERS 0x004b30c8
// SIZE 0x2228
class CircuitRaceScreen : public SingleRaceSelectBase {
public:
	CircuitRaceScreen();

	void OnIconUnfocused(MenuWidget*) override;                                // vtable+0x38
	void OnWidgetValueChanged(MenuWidget*) override;                           // vtable+0x44
	void CreateWidgets() override;                                             // vtable+0x4c
	void Reset() override;                                                     // vtable+0x54
	~CircuitRaceScreen() override;                                             // vtable+0x68
	LegoBool32 Update(undefined4) override;                                    // vtable+0x78
	void Navigate() override;                                                  // vtable+0x84
	LegoBool32 Initialize(MenuGameContext*, MenuScreenCreateParams*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00479e50
	//  CircuitRaceScreen::`scalar deleting destructor'

protected:
	void UpdateRacePreview();

	MenuImage m_photoImage;                 // 0x1908
	MenuTextLabel m_infoLabel;              // 0x1964
	MenuTextLabel m_circuitCaptionLabel;    // 0x19dc
	MenuTextLabel m_circuitNameLabel;       // 0x1a54
	MenuTextLabel m_raceNameLabel;          // 0x1acc
	MenuTextLabel m_trackCaptionLabel;      // 0x1b44
	MenuTextLabel m_circuitDescLabel;       // 0x1bbc
	MenuTextButton m_backButton;            // 0x1c34
	MenuTextButton m_startButton;           // 0x1f24
	MenuAnimationList::Entry* m_transition; // 0x2214
	LegoU32 m_previewTimerMs;               // 0x2218
	LegoU32 m_circuitIndex;                 // 0x221c
	LegoU32 m_previewRaceIndex;             // 0x2220
	LegoBool32 m_previewChanged;            // 0x2224
};

#endif // CIRCUITRACESCREEN_H
