#ifndef DYNAMITEACTION_H
#define DYNAMITEACTION_H

#include "golmodelentity.h"
#include "race/powerups/hazardactionbase.h"
#include "race/powerups/powerupprojectile.h"
#include "race/raceresourcemanager.h"

class CutsceneAnimation;
class MabMaterialTrack;
class SpatialSoundInstance;

struct CutsceneParticleRef;
struct SoundVector;

// VTABLE: LEGORACERS 0x004b1448
// SIZE 0x17c
class DynamiteAction : public HazardActionBase {
public:
	enum {
		c_stateUnloaded = 0,
		c_stateReady = 1,
		c_stateArmed = 2,
		c_stateThrown = 3,
		c_stateSecondBlast = 4,
		c_stateThirdBlast = 5,
		c_stateDone = 6,
		c_blastIntervalMs = 0x01f4,
		c_flightLifetimeMs = 0x0bb8,
		c_fuseDurationMs = 0x1388,
		c_soundExplode = 0x05,
		c_soundFuse = 0x11,
		c_randomTableMask = 0x3ff,
		c_randomOffsetRange = 13,
		c_randomOffsetCenter = 6,
	};

	DynamiteAction();
	~DynamiteAction() override; // vtable+0x04

	// SYNTHETIC: LEGORACERS 0x00458450
	// DynamiteAction::`vector deleting destructor'
	void Update(LegoU32 p_elapsedMs) override;          // vtable+0x08
	void Draw(GolD3DRenderDevice* p_renderer) override; // vtable+0x0c
	void AdvanceState() override;
	void OnHitRacer(Racer*) override; // vtable+0x20                        // vtable+0x14
	void Deactivate() override;       // vtable+0x1c
	void Initialize(
		RaceState* p_raceState,
		TriggerWorld* p_collisionWorld,
		RacePowerupManager* p_manager,
		CutsceneAnimation* p_cutsceneAnimation,
		GolModelEntity* p_model
	);
	void Destroy();
	LegoU32 Activate(Racer* p_racer, Racer* p_targetRacer);

private:
	GolModelEntity m_modelEntity;           // 0x02c
	PowerupProjectile m_projectile;         // 0x0bc
	RacePowerupManager* m_manager;          // 0x164
	CutsceneAnimation* m_cutsceneAnimation; // 0x168
	CutsceneParticleRef* m_sparkParticle;   // 0x16c
	SpatialSoundInstance* m_sound;          // 0x170
	Racer* m_targetRacer;                   // 0x174
	LegoFloat m_tumbleAngle;                // 0x178
};

#endif // DYNAMITEACTION_H
