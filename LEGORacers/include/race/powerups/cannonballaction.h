#ifndef CANNONBALLACTION_H
#define CANNONBALLACTION_H

#include "golmodelentity.h"
#include "golname.h"
#include "race/powerups/powerupprojectile.h"
#include "race/powerups/weaponactionbase.h"
#include "race/racetrailmanager.h"

class CutsceneAnimation;
class MabMaterialTrack;
class SpatialSoundInstance;

struct CutsceneParticleRef;
struct SoundVector;

// VTABLE: LEGORACERS 0x004b13b8
// SIZE 0xe8
class CannonballAction : public WeaponActionBase {
public:
	enum {
		c_stateUnloaded = 0,
		c_stateReady = 1,
		c_stateArmed = 2,
		c_stateFlying = 3,
		c_stateDone = 6,
	};

	enum {
		c_soundHit = 5,
		c_soundFire = 6,
	};

	CannonballAction();
	~CannonballAction() override; // vtable+0x04

	// SYNTHETIC: LEGORACERS 0x00458510
	// CannonballAction::`vector deleting destructor'
	void Update(LegoU32 p_elapsedMs) override;          // vtable+0x08
	void Draw(GolD3DRenderDevice* p_renderer) override; // vtable+0x0c
	void AdvanceState() override;                       // vtable+0x14
	void Deactivate() override;                         // vtable+0x1c
	void OnHitRacer(Racer* p_racer) override;           // vtable+0x20
	void Initialize(RacePowerupManager* p_manager, TriggerWorld* p_collisionWorld);
	void Destroy();
	LegoU32 Activate(ActionSetup* p_setup);

private:
	// SIZE 0x24
	class CannonEmplacement {
	public:
		undefined m_unk0x000[0x008 - 0x000]; // 0x000
		GolVec3 m_targetPosition;            // 0x008
		GolVec3 m_position;                  // 0x014
		LegoU32 m_lifetimeMs;                // 0x020
	};

	PowerupProjectile m_projectile;       // 0x030
	GolBillboard* m_billboard;            // 0x0d8
	CutsceneParticleRef* m_smokeParticle; // 0x0dc
	union {
		CannonEmplacement* m_emplacement; // 0x0e0
		const LegoChar* m_materialName;   // 0x0e0
	};
	union {
		CutsceneParticleRef* m_trailParticle; // 0x0e4
		RaceTrailManager::Trail* m_trail;     // 0x0e4
	};
};

#endif // CANNONBALLACTION_H
