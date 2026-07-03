#ifndef GRAPPLINGHOOKACTION_H
#define GRAPPLINGHOOKACTION_H

#include "golmodelentity.h"
#include "race/powerups/tetherprojectile.h"
#include "race/powerups/weaponactionbase.h"
#include "race/targetpointlist.h"

class CutsceneAnimation;
class MabMaterialTrack;
class SpatialSoundInstance;

struct CutsceneParticleRef;
struct SoundVector;

// VTABLE: LEGORACERS 0x004b1518
// SIZE 0x290
class GrapplingHookAction : public WeaponActionBase {
public:
	enum {
		c_stateUnloaded = 0,
		c_stateReady = 1,
		c_stateArmed = 2,
		c_stateFlying = 3,
		c_statePulling = 4,
		c_stateRetracting = 5,
		c_stateDone = 6,
	};

	enum {
		c_soundHitRacer = 0x12,
		c_soundRelease = 0x14,
		c_soundFire = 0x15,
		c_soundMiss = 0x16,
		c_soundRetract = 0x49,
	};

	GrapplingHookAction();
	~GrapplingHookAction() override; // vtable+0x04

	// SYNTHETIC: LEGORACERS 0x00458570
	// GrapplingHookAction::`vector deleting destructor'
	void Update(LegoU32 p_elapsedMs) override;          // vtable+0x08
	void Draw(GolD3DRenderDevice* p_renderer) override; // vtable+0x0c
	void AdvanceState() override;                       // vtable+0x14
	void Deactivate() override;                         // vtable+0x1c
	void OnHitRacer(Racer* p_racer) override;           // vtable+0x20
	void Initialize(RacePowerupManager* p_manager, TriggerWorld* p_collisionWorld, undefined4 p_billboardMaterialIndex);
	void Shutdown();
	LegoU32 Activate(
		GolModelEntity* p_hookEntity,
		Racer* p_racer,
		Racer* p_targetRacer,
		TargetPointList::Entry* p_targetPoint,
		MabMaterialTrack* p_billboardAnimation,
		LegoU32 p_delayMs
	);
	void ReleaseHook(SoundVector* p_position);

private:
	TetherProjectile m_projectile;           // 0x030
	GolWorldEntity* m_hookEntity;            // 0x268
	CutsceneParticleRef* m_smokeParticleRef; // 0x26c
	GolBillboard* m_billboard;               // 0x270
	MabMaterialTrack m_billboardAnimation;   // 0x274
	LegoU32 m_billboardMaterialIndex;        // 0x28c
};

#endif // GRAPPLINGHOOKACTION_H
