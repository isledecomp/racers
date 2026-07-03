#ifndef EDITDRIVERSCREEN_H
#define EDITDRIVERSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/mainmenumodelslot.h"
#include "menu/screens/menugamescreen.h"
#include "menu/widgets/menuframedsceneview.h"
#include "menu/widgets/menuimage.h"
#include "menu/widgets/menuracercarousel.h"
#include "menu/widgets/menuselector.h"
#include "menu/widgets/menutextbutton.h"
#include "menu/widgets/menutextlabel.h"
#include "racer/drivercosmetics.h"
#include "racer/driverheadbuilder.h"

// VTABLE: LEGORACERS 0x004b332c
// SIZE 0x4774
class EditDriverScreen : public MenuGameScreen {
public:
	EditDriverScreen();

	LegoBool32 HandleKeyDown(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x18
	void OnIconUnfocused(MenuWidget*) override;                                                      // vtable+0x38
	void OnWidgetValueChanged(MenuWidget*) override;                                                 // vtable+0x44
	void CreateWidgets() override;                                                                   // vtable+0x4c
	void Reset() override;                                                                           // vtable+0x54
	~EditDriverScreen() override;                                                                    // vtable+0x68
	LegoBool32 Destroy() override;                                                                   // vtable+0x74
	LegoBool32 Update(undefined4) override;                                                          // vtable+0x78
	void Navigate() override;                                                                        // vtable+0x84
	LegoBool32 CanNavigate() override;                                                               // vtable+0x88
	LegoBool32 Initialize(MenuGameContext*, MenuScreenCreateParams*) override;                       // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x0047cf70
	// EditDriverScreen::`scalar deleting destructor'

protected:
	void LoadHeadBuilder(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams);
	LegoBool32 CreateRacerCarousel(
		MenuRacerCarousel* p_widget,
		undefined2 p_createParamId,
		undefined2 p_styleId,
		LegoU32 p_category
	);
	void CreateDriverScene();
	LegoBool32 HasUnsavedChanges();
	LegoS32 PickNextAnimation();
	void PlayNextAnimation();
	void PlayExitAnimation();
	void LoadCosmetics();
	void SaveCosmetics();
	void RemoveSelectedRecord();

	MenuImage m_photoImage;                   // 0x0368
	MenuImage m_unk0x3c4;                     // 0x03c4
	MenuRacerCarousel m_cosmeticCarousels[4]; // 0x0420
	MenuSelector m_cosmeticSelectors[4];      // 0x09e0
	MenuFramedSceneView m_sceneView;          // 0x31b0
	MenuTextLabel m_infoLabel;                // 0x3688
	MenuTextButton m_randomButton;            // 0x3700
	MenuTextButton m_backButton;              // 0x39f0
	MenuTextButton m_doneButton;              // 0x3ce0
	MenuTextButton m_confirmYesButton;        // 0x3fd0
	MenuTextButton m_confirmNoButton;         // 0x42c0
	DriverHeadBuilder m_headBuilder;          // 0x45b0
	MainMenuModelSlot m_modelSlot;            // 0x4600
	DriverCosmetics m_driverCosmetics;        // 0x475c
	undefined m_unk0x4761[0x4764 - 0x4761];   // 0x4761
	LegoU32 m_cosmeticsDirty;                 // 0x4764
	LegoU16 m_pendingAnimTextId;              // 0x4768
	undefined m_unk0x476a[0x476c - 0x476a];   // 0x476a
	LegoU32 m_nextViewportIndex;              // 0x476c
	LegoU32 m_savePending;                    // 0x4770
};

#endif // EDITDRIVERSCREEN_H
