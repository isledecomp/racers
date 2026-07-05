#ifndef SHIELDACTION_H
#define SHIELDACTION_H

#include "golmodelentity.h"
#include "race/powerups/powerupaction.h"

class CutsceneAnimation;
class GolAnimatedEntity;
class MabMaterialTrack;
class SpatialSoundInstance;

struct CutsceneParticleRef;
struct SoundVector;

// VTABLE: LEGORACERS 0x004b1938
// SIZE 0x2c
class ShieldAction : public PowerupAction {
public:
	enum {
		c_stateUnloaded = 0,
		c_stateReady = 1,
		c_stateActive = 3,
		c_stateFade = 4,
		c_stateDone = 6,
		c_fadeDurationMs = 0x03e8,
		c_durationLevel0Ms = 0x0fa0,
		c_durationLevel1Ms = 0x1770,
		c_durationLevel2Ms = 0x1f40,
		c_durationLevel3Ms = 0x2710,
		c_soundLevel1 = 0x35,
		c_soundExpire = 0x3b,
		c_soundLevel0 = 0x4c,
		c_soundLevel2 = 0x4d,
		c_soundLevel3 = 0x4e,
		c_flagCursed = 1 << 11,
	};

	ShieldAction();
	~ShieldAction() override; // vtable+0x04

	// SYNTHETIC: LEGORACERS 0x00458690 FOLDED
	// ShieldAction::`vector deleting destructor'

	void Update(LegoU32 p_elapsedMs) override;                     // vtable+0x08
	void DrawTransparent(GolD3DRenderDevice* p_renderer) override; // vtable+0x10
	void AdvanceState() override;                                  // vtable+0x14
	LegoS32 GetBrickColor() override;                              // vtable+0x18
	void Deactivate() override;                                    // vtable+0x1c
	void Initialize(RacePowerupManager* p_manager);
	void Destroy();
	void Activate(
		Racer* p_racer,
		LegoU32 p_level,
		GolAnimatedEntity* p_shieldTemplate,
		GolAnimatedEntity* p_innerShieldTemplate
	);

private:
	friend class RacePowerupManager;

	GolAnimatedEntity* m_shieldEntity;      // 0x18
	GolAnimatedEntity* m_innerShieldEntity; // 0x1c
	Racer* m_racer;                         // 0x20
	RacePowerupManager* m_manager;          // 0x24
	SpatialSoundInstance* m_sound;          // 0x28
};

#endif // SHIELDACTION_H
