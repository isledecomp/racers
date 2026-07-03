#ifndef CURSEACTION_H
#define CURSEACTION_H

#include "golmodelentity.h"
#include "race/powerups/hazardactionbase.h"
#include "race/raceresourcemanager.h"

class CutsceneAnimation;
class MabMaterialTrack;
class SpatialSoundInstance;

struct CutsceneParticleRef;
struct SoundVector;

// VTABLE: LEGORACERS 0x004b13fc
// SIZE 0x68
class CurseAction : public HazardActionBase {
public:
	enum {
		c_stateUnloaded = 0,
		c_stateReady = 1,
		c_stateArmed = 2,
		c_stateActive = 3,
		c_stateFade = 4,
		c_stateExpiring = 5,
		c_stateDone = 6,
		c_fadeDurationMs = 0x03e8,
		c_curseDurationMs = 0x2710,
		c_activeDurationMs = 0x3a98,
		c_soundLoop = 0x09,
		c_flagCursed = 1 << 11,
	};

	CurseAction();
	~CurseAction() override; // vtable+0x04

	// SYNTHETIC: LEGORACERS 0x004584b0
	// CurseAction::`vector deleting destructor'
	void Update(LegoU32 p_elapsedMs) override;                     // vtable+0x08
	void Draw(GolD3DRenderDevice* p_renderer) override;            // vtable+0x0c
	void DrawTransparent(GolD3DRenderDevice* p_renderer) override; // vtable+0x10
	void AdvanceState() override;                                  // vtable+0x14
	void Deactivate() override;                                    // vtable+0x1c
	void OnHitRacer(Racer* p_racer) override;                      // vtable+0x20
	void Initialize(RaceState* p_raceState, TriggerWorld* p_curseModel, RacePowerupManager* p_manager);
	void Reset();
	void Destroy();
	void Activate(
		Racer* p_racer,
		GolAnimatedEntity* p_curseModel,
		GolAnimatedEntity* p_auraModel,
		GolAnimatedEntity* p_innerAuraModel,
		ActionTarget* p_target
	);

private:
	RacePowerupManager* m_manager;        // 0x2c
	GolAnimatedEntity* m_curseEntity;     // 0x30
	GolAnimatedEntity* m_auraEntity;      // 0x34
	GolAnimatedEntity* m_innerAuraEntity; // 0x38
	GolWorldEntity m_worldEntity;         // 0x3c
	SpatialSoundInstance* m_sound;        // 0x64
};

#endif // CURSEACTION_H
