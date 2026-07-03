#ifndef MAINMENUSCREEN_H
#define MAINMENUSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/mainmenumodelslot.h"
#include "menu/screens/menugamescreen.h"
#include "menu/widgets/menuimage.h"
#include "menu/widgets/menusceneview.h"
#include "menu/widgets/menutextbutton.h"
#include "menu/widgets/menutextlabel.h"

// VTABLE: LEGORACERS 0x004b36d8
// SIZE 0x2450
class MainMenuScreen : public MenuGameScreen {
public:
	MainMenuScreen();

	LegoBool32 HandleKeyDown(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x18
	LegoBool32 HandleKeyUp(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4) override;   // vtable+0x1c
	void OnIconUnfocused(MenuWidget*) override;                                                      // vtable+0x38
	void CreateWidgets() override;                                                                   // vtable+0x4c
	void Reset() override;                                                                           // vtable+0x54
	~MainMenuScreen() override;                                                                      // vtable+0x68
	LegoBool32 Destroy() override;                                                                   // vtable+0x74
	LegoBool32 Update(undefined4) override;                                                          // vtable+0x78
	void Navigate() override;                                                                        // vtable+0x84
	LegoBool32 Initialize(MenuGameContext*, MenuScreenCreateParams*) override;                       // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00480cb0
	//  MainMenuScreen::`scalar deleting destructor'

protected:
	void CreateDriverScene();

	MenuImage m_photoImage;                 // 0x0368
	MenuImage m_logoImage;                  // 0x03c4
	MenuTextLabel m_unk0x420;               // 0x0420
	MenuTextButton m_singleRaceButton;      // 0x0498
	MenuTextButton m_circuitRaceButton;     // 0x0788
	MenuTextButton m_versusRaceButton;      // 0x0a78
	MenuTextButton m_timeRaceButton;        // 0x0d68
	MenuTextButton m_garageButton;          // 0x1058
	MenuTextButton m_optionsButton;         // 0x1348
	MenuTextButton m_exitButton;            // 0x1638
	MenuTextButton m_confirmYesButton;      // 0x1928
	MenuTextButton m_confirmNoButton;       // 0x1c18
	MenuTextButton m_noticePopup;           // 0x1f08
	MenuSceneView m_sceneView;              // 0x21f8
	undefined m_unk0x22d4[0x22dc - 0x22d4]; // 0x22d4
	MainMenuModelSlot m_modelSlot;          // 0x22dc
	GolAnimatedEntity* m_driverEntity;      // 0x2438
	LegoBool32 m_animSoundPlayed;           // 0x243c
	undefined4 m_unk0x2440;                 // 0x2440
	LegoU32 m_idleTimeoutMs;                // 0x2444
	LegoU32 m_idleAnimTimerMs;              // 0x2448
	LegoU8 m_cheatKeyMask;                  // 0x244c
	undefined m_unk0x244d[0x2450 - 0x244d]; // 0x244d
};

#endif // MAINMENUSCREEN_H
