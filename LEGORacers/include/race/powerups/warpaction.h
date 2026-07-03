#ifndef WARPACTION_H
#define WARPACTION_H

#include "golmodelentity.h"
#include "race/powerups/powerupaction.h"

class CutsceneAnimation;
class MabMaterialTrack;
class SpatialSoundInstance;

struct CutsceneParticleRef;
struct SoundVector;

// VTABLE: LEGORACERS 0x004b1a88
// SIZE 0xe4
class WarpAction : public PowerupAction {
public:
	// SIZE 0x08
	struct SetupParams {
		RacePowerupManager* m_manager; // 0x00
		LegoFloat m_cameraFov;         // 0x04
	};

	WarpAction();
	~WarpAction() override; // vtable+0x04

	// SYNTHETIC: LEGORACERS 0x00458750
	// WarpAction::`vector deleting destructor'
	void Update(LegoU32 p_elapsedMs) override;                     // vtable+0x08
	void Draw(GolD3DRenderDevice* p_renderer) override;            // vtable+0x0c
	void DrawTransparent(GolD3DRenderDevice* p_renderer) override; // vtable+0x10
	void AdvanceState() override;                                  // vtable+0x14
	LegoS32 GetBrickColor() override;                              // vtable+0x18
	void Deactivate() override;                                    // vtable+0x1c
	void Reset();
	void Initialize(const SetupParams* p_params);
	void Destroy();
	LegoU32 Activate(Racer* p_racer, GolModelEntity* p_portalModel, ActionTarget* p_target);
	void TeleportEntity(GolWorldEntity* p_entity);

private:
	friend class RacePowerupManager;

	enum {
		c_stateUnloaded = 0,
		c_stateInitialized = 1,
		c_stateStarting = 2,
		c_stateActive = 3,
		c_stateDone = 6,
		c_menuAnimationDurationMs = 200,
		c_menuAnimationColorBlue = 100,
		c_transitionDurationMs = 1500,
		c_soundStart = 0x27,
		c_soundFinish = 0x29,
		c_soundSpatial = 0x41,
		c_flagGhost = 1 << 4,
	};

	GolModelEntity m_modelEntity;  // 0x018
	Racer* m_racer;                // 0x0a8
	RacePowerupManager* m_manager; // 0x0ac
	LegoFloat m_cameraFov;         // 0x0b0
	SoundVector m_startPosition;   // 0x0b4
	GolVec3 m_targetPosition;      // 0x0c0
	GolVec3 m_targetDirection;     // 0x0cc
	LegoBool32 m_hasTarget;        // 0x0d8
	LegoBool32 m_followingPath;    // 0x0dc
	LegoBool32 m_isDemoRacer;      // 0x0e0
};

#endif // WARPACTION_H
