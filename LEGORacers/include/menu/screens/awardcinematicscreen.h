#ifndef AWARDCINEMATICSCREEN_H
#define AWARDCINEMATICSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "golanimatedentity.h"
#include "golnametable.h"
#include "golworldentitygroup0x38.h"
#include "menu/screens/menuscenescreen.h"
#include "race/data/racedefinitionlist.h"
#include "save/savegame.h"

class ChassisModelTable;
class GolWorldEntity;
class CarBuildModel;

// VTABLE: LEGORACERS 0x004b2c5c
// SIZE 0x7b0
class AwardCinematicScreen : public MenuSceneScreen {
public:
	// VTABLE: LEGORACERS 0x004b2f00
	// SIZE 0x50
	class SceneEntityGroup : public GolWorldEntityGroup0x38 {
	public:
		// SIZE 0x18
		struct CreateParams {
			ChassisModelTable* m_chassisModels; // 0x00
			CarBuildModel* m_unk0x04;           // 0x04
			GolWorldEntity* m_unk0x08;          // 0x08
			GolAnimatedEntity* m_unk0x0c;       // 0x0c
			GolName m_chassisName;              // 0x10
		};

		SceneEntityGroup();
		~SceneEntityGroup() override;

		void VTable0x08(const GolVec3& p_center) override;                         // vtable+0x08
		void VTable0x40(const GolVec3& p_direction, const GolVec3& p_up) override; // vtable+0x40
		LegoBool32 FUN_00479510(CreateParams* p_createParams);
		LegoBool32 FUN_00479590();

		// SYNTHETIC: LEGORACERS 0x00479460
		// AwardCinematicScreen::SceneEntityGroup::`scalar deleting destructor'

	private:
		void FUN_004794d0(GolAnimatedEntity* p_entity);

		ChassisModelTable* m_chassisModels; // 0x38
		CarBuildModel* m_unk0x3c;           // 0x3c
		GolWorldEntity* m_unk0x40;          // 0x40
		GolAnimatedEntity* m_unk0x44;       // 0x44
		GolName m_chassisName;              // 0x48
	};

	AwardCinematicScreen();

	void VTable0x4c() override;                                                // vtable+0x4c
	~AwardCinematicScreen() override;                                          // vtable+0x68
	LegoBool32 Destroy() override;                                             // vtable+0x74
	LegoBool32 VTable0x78(undefined4) override;                                // vtable+0x78
	void VTable0x84() override;                                                // vtable+0x84
	LegoBool32 VTable0x8c(MenuGameContext*, MenuScreenCreateParams*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00475cb0
	// AwardCinematicScreen::`scalar deleting destructor'

protected:
	LegoBool32 FUN_004767b0();
	LegoBool32 FUN_00476890(SaveRecordList* p_records, RaceDefinitionList::RaceDefinition* p_raceDefinition);
	LegoBool32 FUN_004768f0(GameState* p_gameState, RaceDefinitionList::RaceDefinition* p_raceDefinition);
	LegoBool32 FUN_00476990(GameState* p_gameState, RaceDefinitionList::RaceDefinition* p_raceDefinition);

	SceneEntityGroup m_unk0x658;  // 0x658
	GolAnimatedEntity m_unk0x6a8; // 0x6a8
	GolModelBase* m_unk0x79c;     // 0x79c
	LegoS32 m_unk0x7a0;           // 0x7a0
	undefined4 m_unk0x7a4;        // 0x7a4
	undefined4 m_unk0x7a8;        // 0x7a8
	undefined4 m_unk0x7ac;        // 0x7ac
};

#endif // AWARDCINEMATICSCREEN_H
