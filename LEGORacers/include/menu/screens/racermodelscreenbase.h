#ifndef RACERMODELSCREENBASE_H
#define RACERMODELSCREENBASE_H

#include "cmbmodelpart.h"
#include "compat.h"
#include "decomp.h"
#include "golanimatedentity.h"
#include "golmodelentity.h"
#include "menu/screens/awardcinematicscreen.h"
#include "menu/screens/menugamescreen.h"
#include "menu/screens/racermodelslot.h"
#include "menu/screens/saverecordcursor.h"
#include "menu/widgets/menuframedsceneview.h"
#include "menu/widgets/menutextlabel.h"

class GolModelBase;
class GolSceneNode;

// VTABLE: LEGORACERS 0x004b3c78
// SIZE 0x270c
class RacerModelScreenBase : public MenuGameScreen {
public:
	RacerModelScreenBase();

	void CreateWidgets() override;                                                         // vtable+0x4c
	void Reset() override;                                                                 // vtable+0x54
	~RacerModelScreenBase() override;                                                      // vtable+0x68
	LegoBool32 Destroy() override;                                                         // vtable+0x74
	LegoBool32 Update(undefined4) override;                                                // vtable+0x78
	void SetupLighting() override;                                                         // vtable+0x80
	LegoBool32 CanNavigate() override;                                                     // vtable+0x88
	virtual void CreateModelSlots();                                                       // vtable+0x98
	virtual LegoS32 PickRandomAnimation();                                                 // vtable+0x9c
	virtual LegoBool32 Initialize(MenuGameContext*, MenuScreenCreateParams*, undefined4*); // vtable+0xa0

	// SYNTHETIC: LEGORACERS 0x004859e0
	// RacerModelScreenBase::`scalar deleting destructor'

protected:
	void CreateCarModels();
	void OpenRecordCursors(MenuGameContext* p_context, LegoU32 p_mask);
	void CreateDriverModels();
	void CommitRecordSelections();
	void RefreshSlotModel(LegoS32 p_index);
	void SwapSlotModel(LegoS32 p_index);
	void UpdateSourceLabel(LegoS32 p_index);
	void SelectNextRecord(LegoS32 p_index);
	void SelectPreviousRecord(LegoS32 p_index);
	void AlignDriverSlots();
	void AlignCarSlots();
	void DetachSlotWidgets(LegoS32 p_index);
	void PlayRandomAnimation(LegoS32 p_index);
	void PlayRandomNamedAnimation(LegoS32 p_index);

	CmbModelPart m_modelParts;                             // 0x0368
	AwardCinematicScreen::SceneEntityGroup m_carGroups[4]; // 0x039c
	GolSceneNode* m_bodySceneNodes[4];                     // 0x04dc
	GolModelBase* m_driverModels[4];                       // 0x04ec
	GolModelEntity m_carModelEntities[4];                  // 0x04fc
	GolModelBase* m_carModels[4];                          // 0x073c
	GolVec3 m_carDirAxis;                                  // 0x074c
	GolVec3 m_carUpAxis;                                   // 0x0758
	undefined4 m_unk0x764;                                 // 0x0764
	undefined4 m_unk0x768;                                 // 0x0768
	LegoBool32 m_slotSettled[2];                           // 0x076c
	LegoBool32 m_slotDirty[2];                             // 0x0774
	LegoS32 m_slotCount;                                   // 0x077c
	LegoS32 m_slotModelToggle[2];                          // 0x0780
	undefined m_carData[0x98c - 0x788];                    // 0x0788
	MenuFramedSceneView m_sceneViews[4];                   // 0x098c
	MenuTextLabel m_sourceLabels[2];                       // 0x1cec
	RacerModelSlot m_carSlots[4];                          // 0x1ddc
	RacerModelSlot m_driverSlots[4];                       // 0x205c
	SaveRecordCursor m_recordCursors[2];                   // 0x22dc
	GolAnimatedEntity m_driverEntities[4];                 // 0x232c
	LegoS32 m_modelSlotCount;                              // 0x26fc
	LegoS32 m_modelsPerSlot;                               // 0x2700
	undefined4 m_recordCounts[2];                          // 0x2704
};

#endif // RACERMODELSCREENBASE_H
