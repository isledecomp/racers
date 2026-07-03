#ifndef EDITCARSCREEN_H
#define EDITCARSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "golanimatedentity.h"
#include "golname.h"
#include "menu/screens/awardcinematicscreen.h"
#include "menu/screens/menugamescreen.h"
#include "menu/screens/racermodelslot.h"
#include "menu/screens/saverecordcursor.h"
#include "menu/widgets/menucarousel.h"
#include "menu/widgets/menucarouselnavigator.h"
#include "menu/widgets/menuframedsceneview.h"
#include "menu/widgets/menuimage.h"
#include "menu/widgets/menuselector.h"
#include "menu/widgets/menutextbutton.h"
#include "menu/widgets/menutextlabel.h"

class CmbModelPart;
class GolModelBase;
class GolSceneNode;
class ActiveRecordBuffer;

// VTABLE: LEGORACERS 0x004b3294
// SIZE 0x36c4
class EditCarScreen : public MenuGameScreen {
public:
	EditCarScreen();

	void OnIconUnfocused(MenuWidget*) override;                                // vtable+0x38
	void OnWidgetValueChanged(MenuWidget*) override;                           // vtable+0x44
	void CreateWidgets() override;                                             // vtable+0x4c
	void Reset() override;                                                     // vtable+0x54
	~EditCarScreen() override;                                                 // vtable+0x68
	LegoBool32 Destroy() override;                                             // vtable+0x74
	void SetupLighting() override;                                             // vtable+0x80
	void Navigate() override;                                                  // vtable+0x84
	LegoBool32 Initialize(MenuGameContext*, MenuScreenCreateParams*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x0047bde0
	// EditCarScreen::`scalar deleting destructor'

protected:
	void CreateCarScene();
	void CreateCategoryCarousel();
	void PopulateCategoryCarousel();
	void LoadBuilderImages(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams);
	void LoadCarData();
	void SaveCarData();
	void CreateDriverModel();
	void CreateCarGroup();
	void UpdateButtonStates();
	void LoadQuickBuildCar();
	LegoBool32 HasUnsavedChanges();
	void SetPlayerOneRecord();

	MenuImage m_photoImage;                            // 0x0368
	MenuTextLabel m_infoLabel;                         // 0x03c4
	MenuFramedSceneView m_sceneView;                   // 0x043c
	MenuTextButton m_buildButton;                      // 0x0914
	MenuTextButton m_quickBuildButton;                 // 0x0c04
	MenuTextButton m_newCarButton;                     // 0x0ef4
	MenuTextButton m_doneButton;                       // 0x11e4
	MenuTextButton m_backButton;                       // 0x14d4
	MenuTextButton m_discardYesButton;                 // 0x17c4
	MenuTextButton m_confirmNoButton;                  // 0x1ab4
	MenuTextButton m_quickBuildYesButton;              // 0x1da4
	MenuTextButton m_newCarYesButton;                  // 0x2094
	MenuCarouselNavigator m_categoryCarousel;          // 0x2384
	MenuSelector m_categorySelector;                   // 0x2418
	MenuImage m_categoryIcons[12];                     // 0x2e0c
	LegoU8 m_carBuildSaveBuffer[0x202];                // 0x325c
	AwardCinematicScreen::SceneEntityGroup m_carGroup; // 0x3460
	GolAnimatedEntity m_driverEntity;                  // 0x34b0
	GolModelBase* m_driverModel;                       // 0x35a4
	GolSceneNode* m_bodySceneNode;                     // 0x35a8
	CmbModelPart* m_bodyModelPart;                     // 0x35ac
	RacerModelSlot m_modelSlot;                        // 0x35b0
	SaveRecordCursor m_recordCursor;                   // 0x3650
	ActiveRecordBuffer* m_activeRecord;                // 0x3678
	GolName m_chassisName;                             // 0x367c
	LegoU32 m_partCategoryUnlockFlags;                 // 0x3684
	LegoU32 m_partCategoryAvailable[12];               // 0x3688
	undefined m_unk0x36b8[0x36c0 - 0x36b8];            // 0x36b8
	LegoBool32 m_savePending;                          // 0x36c0
};

#endif // EDITCARSCREEN_H
