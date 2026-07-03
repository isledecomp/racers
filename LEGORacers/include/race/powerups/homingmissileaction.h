#ifndef HOMINGMISSILEACTION_H
#define HOMINGMISSILEACTION_H

#include "golmodelentity.h"
#include "race/powerups/homingprojectile.h"
#include "race/powerups/weaponactionbase.h"
#include "race/racetrailmanager.h"

class CutsceneAnimation;
class MabMaterialTrack;
class SpatialSoundInstance;

struct CutsceneParticleRef;
struct SoundVector;

// VTABLE: LEGORACERS 0x004b1690
// SIZE 0x224
class HomingMissileAction : public WeaponActionBase {
public:
	enum {
		c_stateUnloaded = 0,
		c_stateReady = 1,
		c_stateArmed = 2,
		c_stateFlying = 3,
		c_state0x04 = 4,
		c_stateDone = 6,
		c_transformNodeIndex1 = 1,
		c_flightTimeMs = 0x157c,
		c_soundExplode = 0x32,
		c_soundFire = 0x33,
	};

	HomingMissileAction();
	~HomingMissileAction() override; // vtable+0x04

	// SYNTHETIC: LEGORACERS 0x00458630
	// HomingMissileAction::`vector deleting destructor'
	void Update(LegoU32 p_elapsedMs) override;          // vtable+0x08
	void Draw(GolD3DRenderDevice* p_renderer) override; // vtable+0x0c
	void AdvanceState() override;                       // vtable+0x14
	void Deactivate() override;                         // vtable+0x1c
	void OnHitRacer(Racer* p_racer) override;           // vtable+0x20
	void Initialize(RacePowerupManager* p_manager, TriggerWorld* p_collisionWorld);
	void Shutdown();
	void Activate(GolAnimatedEntity* p_missileTemplate, GolAnimatedEntity*, Racer* p_racer, LegoU32 p_missileIndex);
	void LaunchProjectile();

private:
	HomingProjectile m_projectile;     // 0x030
	GolAnimatedEntity m_missileEntity; // 0x128
	RaceTrailManager::Trail* m_trail;  // 0x21c
	LegoU32 m_missileIndex;            // 0x220
};

#endif // HOMINGMISSILEACTION_H
