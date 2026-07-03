#ifndef GARAGESCREEN_H
#define GARAGESCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/racerpickscreenbase.h"
#include "menu/widgets/menuimage.h"
#include "menu/widgets/menutextbutton.h"

// VTABLE: LEGORACERS 0x004b33dc
// SIZE 0x6410
class GarageScreen : public RacerPickScreenBase {
public:
	GarageScreen();

	void OnIconUnfocused(MenuWidget*) override;                                // vtable+0x38
	void CreateWidgets() override;                                             // vtable+0x4c
	void Reset() override;                                                     // vtable+0x54
	~GarageScreen() override;                                                  // vtable+0x68
	LegoBool32 Update(undefined4) override;                                    // vtable+0x78
	void Navigate() override;                                                  // vtable+0x84
	LegoBool32 Initialize(MenuGameContext*, MenuScreenCreateParams*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x0047e3e0
	// GarageScreen::`scalar deleting destructor'

protected:
	void CreateMainButtons();
	void CreateEditButtons();
	void ShowMainButtons();
	void HideMainButtons();
	void ShowEditButtons();
	void HideEditButtons();
	void RefreshRecordAvailability(MenuGameContext* p_context);
	void DeleteSelectedRecord();
	void StartTestDrive();
	void ApplyPageChange();

	MenuImage m_photoImage;            // 0x3ff4
	MenuTextLabel m_infoLabel;         // 0x4050
	MenuTextButton m_newRacerButton;   // 0x40c8
	MenuTextButton m_editButton;       // 0x43b8
	MenuTextButton m_loadButton;       // 0x46a8
	MenuTextButton m_deleteButton;     // 0x4998
	MenuTextButton m_testDriveButton;  // 0x4c88
	MenuTextButton m_editCarButton;    // 0x4f78
	MenuTextButton m_editDriverButton; // 0x5268
	MenuTextButton m_licenseButton;    // 0x5558
	MenuTextButton m_backButton;       // 0x5848
	MenuTextButton m_confirmYesButton; // 0x5b38
	MenuTextButton m_confirmNoButton;  // 0x5e28
	MenuTextButton m_unk0x6118;        // 0x6118
	undefined4 m_page;                 // 0x6408
	undefined4 m_nextPage;             // 0x640c
};

#endif // GARAGESCREEN_H
