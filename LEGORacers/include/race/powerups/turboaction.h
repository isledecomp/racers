#ifndef TURBOACTION_H
#define TURBOACTION_H

#include "golmodelentity.h"
#include "race/powerups/powerupaction.h"

class CutsceneAnimation;
class GolAnimatedEntity;
class MabMaterialTrack;
class SpatialSoundInstance;

struct CutsceneParticleRef;
struct SoundVector;

// VTABLE: LEGORACERS 0x004b1a30
// SIZE 0x34
class TurboAction : public PowerupAction {
public:
	enum {
		c_stateUnloaded = 0,
		c_stateReady = 1,
		c_stateIgnite = 2,
		c_stateBoosting = 3,
		c_stateFade = 4,
		c_stateDone = 6,
		c_speedModDurationL0Ms = 0x007d,
		c_speedModDurationMs = 0x00fa,
		c_igniteFlashMs = 0x0032,
		c_fadeBaseMs = 0x015e,
		c_smokeWindowMs = 0x0320,
		c_boostDurationL0Ms = 0x03e8,
		c_boostDurationL1Ms = 0x05dc,
		c_earlyEndWindowMs = 0x1194,
		c_boostDurationL2Ms = 0x1388,
		c_soundBoostBase = 0x24,
		c_soundEnd = 0x28,
		c_soundWhoosh = 0x41,
		c_soundEndL2 = 0x4b,
		c_flagHalted = 1 << 3,
	};

	TurboAction();
	~TurboAction() override; // vtable+0x04

	// SYNTHETIC: LEGORACERS 0x004586f0
	// TurboAction::`vector deleting destructor'

	void Update(LegoU32 p_elapsedMs) override;                     // vtable+0x08
	void Draw(GolD3DRenderDevice* p_renderer) override;            // vtable+0x0c
	void DrawTransparent(GolD3DRenderDevice* p_renderer) override; // vtable+0x10
	void AdvanceState() override;                                  // vtable+0x14
	LegoS32 GetBrickColor() override;                              // vtable+0x18
	void Deactivate() override;                                    // vtable+0x1c
	void Initialize(RacePowerupManager* p_manager, CutsceneAnimation* p_particleAnimation);
	void Destroy();
	void Reset();
	void Activate(Racer* p_racer, LegoU32 p_level);
	void StartBoost();
	void AnchorToRacer();

private:
	friend class RacePowerupManager;

	Racer* m_racer;                         // 0x18
	RacePowerupManager* m_manager;          // 0x1c
	GolAnimatedEntity* m_turboEntity;       // 0x20
	GolAnimatedEntity* m_flameEntity;       // 0x24
	GolAnimatedEntity* m_flame2Entity;      // 0x28
	CutsceneAnimation* m_particleAnimation; // 0x2c
	CutsceneParticleRef* m_smokeParticle;   // 0x30
};

#endif // TURBOACTION_H
