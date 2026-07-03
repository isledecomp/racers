#ifndef OILSLICKACTION_H
#define OILSLICKACTION_H

#include "golmodelentity.h"
#include "race/powerups/hazardactionbase.h"

class CutsceneAnimation;
class MabMaterialTrack;
class SpatialSoundInstance;

struct CutsceneParticleRef;
struct SoundVector;

// VTABLE: LEGORACERS 0x004b16e0
// SIZE 0x190
class OilSlickAction : public HazardActionBase {
public:
	enum {
		c_stateUnloaded = 0,
		c_stateReady = 1,
		c_stateArmed = 2,
		c_stateActive = 3,
		c_stateExpiring = 5,
		c_stateDone = 6,
		c_flagHalted = 1 << 3,
		c_activeDurationMs = 0x2710,
		c_soundDrop = 0x2e,
		c_soundSlip = 0x2f,
		c_soundLoop = 0x30,
		c_randomTableMask = 0x3ff,
		c_randomPhaseRange = 0x274,
		c_randomBubbleOffsetRange = 7,
	};

	OilSlickAction();
	~OilSlickAction() override; // vtable+0x04

	// SYNTHETIC: LEGORACERS 0x004583f0
	// OilSlickAction::`vector deleting destructor'
	void Update(LegoU32 p_elapsedMs) override;          // vtable+0x08
	void Draw(GolD3DRenderDevice* p_renderer) override; // vtable+0x0c
	void AdvanceState() override;                       // vtable+0x14
	void Deactivate() override;                         // vtable+0x1c
	void OnHitRacer(Racer* p_racer) override;           // vtable+0x20
	void Initialize(
		RacePowerupManager* p_manager,
		RaceState* p_raceState,
		GolCollidableEntity* p_collidable,
		TriggerWorld* p_collisionWorld,
		CutsceneAnimation* p_particleAnimation,
		GolRenderDevice* p_renderer,
		GolExport* p_export
	);
	void Destroy();
	void Activate(Racer* p_racer);

private:
	RacePowerupManager* m_manager;                      // 0x02c
	GolWorldEntity m_worldEntity;                       // 0x030
	SpatialSoundInstance* m_sound;                      // 0x058
	CutsceneAnimation* m_particleAnimation;             // 0x05c
	CutsceneParticleRef* m_bubbleParticle;              // 0x060
	RaceDecalManager::Trail::Decal m_slickDecal;        // 0x064
	GolBillboard::ManagedMaterialTable m_materialTable; // 0x180
	GolCollidableEntity* m_collidable;                  // 0x18c
};

#endif // OILSLICKACTION_H
