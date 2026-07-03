#ifndef AWARDCINEMATICSCREEN_H
#define AWARDCINEMATICSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "golanimatedentity.h"
#include "golnametable.h"
#include "golworldentitygroup.h"
#include "menu/screens/menuscenescreen.h"
#include "race/data/circuitdefinitionlist.h"
#include "save/saverecordlist.h"

class ChassisModelTable;
class CarBuildModel;
class GameState;
class GolWorldEntity;

// VTABLE: LEGORACERS 0x004b2c5c
// SIZE 0x7b0
class AwardCinematicScreen : public MenuSceneScreen {
public:
	// VTABLE: LEGORACERS 0x004b2f00
	// SIZE 0x50
	class SceneEntityGroup : public GolWorldEntityGroup {
	public:
		// SIZE 0x18
		struct CreateParams {
			ChassisModelTable* m_chassisModels; // 0x00
			CarBuildModel* m_buildModel;        // 0x04
			GolWorldEntity* m_carEntity;        // 0x08
			GolAnimatedEntity* m_driverEntity;  // 0x0c
			GolName m_chassisName;              // 0x10
		};

		SceneEntityGroup();
		~SceneEntityGroup() override;

		void SetPosition(const GolVec3& p_center) override;                            // vtable+0x08
		void SetDirectionUp(const GolVec3& p_direction, const GolVec3& p_up) override; // vtable+0x40
		LegoBool32 Create(CreateParams* p_createParams);
		LegoBool32 Destroy();
		GolAnimatedEntity* GetPrimaryChassisEntity() const { return static_cast<GolAnimatedEntity*>(m_entities[1]); }

		// SYNTHETIC: LEGORACERS 0x00479460
		// AwardCinematicScreen::SceneEntityGroup::`scalar deleting destructor'

	private:
		void AddAnimatedEntity(GolAnimatedEntity* p_entity);

		ChassisModelTable* m_chassisModels; // 0x38
		CarBuildModel* m_buildModel;        // 0x3c
		GolWorldEntity* m_carEntity;        // 0x40
		GolAnimatedEntity* m_driverEntity;  // 0x44
		GolName m_chassisName;              // 0x48
	};

	AwardCinematicScreen();

	void CreateWidgets() override;                                             // vtable+0x4c
	~AwardCinematicScreen() override;                                          // vtable+0x68
	LegoBool32 Destroy() override;                                             // vtable+0x74
	LegoBool32 Update(undefined4) override;                                    // vtable+0x78
	void Navigate() override;                                                  // vtable+0x84
	LegoBool32 Initialize(MenuGameContext*, MenuScreenCreateParams*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00475cb0
	// AwardCinematicScreen::`scalar deleting destructor'

protected:
	LegoBool32 GrantAwards();
	LegoBool32 GrantTrophy(SaveRecordList* p_records, CircuitDefinitionList::CircuitDefinition* p_circuitDefinition);
	LegoBool32 UnlockNextCircuit(GameState* p_gameState, CircuitDefinitionList::CircuitDefinition* p_circuitDefinition);
	LegoBool32 UnlockPartSet(GameState* p_gameState, CircuitDefinitionList::CircuitDefinition* p_circuitDefinition);
	LegoBool32 CreateWinnerCar(undefined4);

	SceneEntityGroup m_carGroup;      // 0x658
	GolAnimatedEntity m_driverEntity; // 0x6a8
	GolModelBase* m_driverModel;      // 0x79c
	LegoS32 m_unlockedPartIndex;      // 0x7a0
	undefined4 m_trophyAwarded;       // 0x7a4
	undefined4 m_partsUnlocked;       // 0x7a8
	undefined4 m_circuitUnlocked;     // 0x7ac
};

#endif // AWARDCINEMATICSCREEN_H
