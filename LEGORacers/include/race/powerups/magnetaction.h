#ifndef MAGNETACTION_H
#define MAGNETACTION_H

#include "golworldentity.h"
#include "race/powerups/hazardactionbase.h"

class CutsceneAnimation;
class GolAnimatedEntity;
class MabMaterialTrack;
class SpatialSoundInstance;

struct CutsceneParticleRef;
struct SoundVector;

// VTABLE: LEGORACERS 0x004b15fc
// SIZE 0x84
class MagnetAction : public HazardActionBase {
public:
	enum {
		c_stateReady = 1,
		c_stateArmed = 2,
		c_stateHolding = 3,
		c_stateFade = 4,
		c_stateDone = 6,
	};

	enum {
		c_fadeDurationMs = 0x03e8,
		c_holdDurationMs = 0x0fa0,
		c_armedDurationMs = 0x4e20,
		c_soundDeploy = 0x21,
		c_soundLoop = 0x22,
		c_soundGrab = 0x23,
		c_soundRelease = 0x4a,
		c_flagVictimStopped = 1 << 0,
		c_flagVictimLifted = 1 << 1,
		c_flagHalted = 1 << 3,
	};

	MagnetAction();
	~MagnetAction() override; // vtable+0x04

	// SYNTHETIC: LEGORACERS 0x00458390
	// MagnetAction::`vector deleting destructor'

	void Update(LegoU32 p_elapsedMs) override;                     // vtable+0x08
	void Draw(GolD3DRenderDevice* p_renderer) override;            // vtable+0x0c
	void DrawTransparent(GolD3DRenderDevice* p_renderer) override; // vtable+0x10
	void AdvanceState() override;                                  // vtable+0x14
	void Deactivate() override;                                    // vtable+0x1c
	void OnHitRacer(Racer* p_racer) override;                      // vtable+0x20

	void Initialize(
		RacePowerupManager* p_manager,
		RaceState* p_raceState,
		TriggerWorld* p_collisionWorld,
		CutsceneAnimation*,
		GolExport*,
		GolD3DRenderDevice*,
		undefined4
	);
	void Destroy();
	void Reset();
	void Activate(
		Racer* p_racer,
		GolAnimatedEntity* p_magnetModel,
		GolAnimatedEntity* p_ringModel,
		GolAnimatedEntity* p_insideModel
	);
	void Deploy();

private:
	friend class RacePowerupManager;

	GolVec3 m_direction;               // 0x2c
	RacePowerupManager* m_manager;     // 0x38
	GolAnimatedEntity* m_magnetEntity; // 0x3c
	GolAnimatedEntity* m_ringEntity;   // 0x40
	GolAnimatedEntity* m_insideEntity; // 0x44
	GolWorldEntity m_worldEntity;      // 0x48
	SpatialSoundInstance* m_sound;     // 0x70
	undefined m_unk0x74[0x78 - 0x74];  // 0x74
	Racer* m_heldRacer;                // 0x78
	Racer* m_pulledRacer;              // 0x7c
	LegoU8 m_flags;                    // 0x80
	undefined m_unk0x81[0x84 - 0x81];  // 0x81
};

#endif // MAGNETACTION_H
