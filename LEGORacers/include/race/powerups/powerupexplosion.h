#ifndef POWERUPEXPLOSION_H
#define POWERUPEXPLOSION_H

#include "golmath.h"
#include "golmodelentity.h"
#include "util/legoeventqueue.h"

class GolBoundedEntity;
class GolCollidableEntity;
class GolD3DRenderDevice;
class GolExport;
class RacePowerupManager;
class Racer;
class RacerSoundSource;
class RaceState;
class TriggerWorld;
class CutsceneAnimation;

struct CutsceneParticleRef;

// VTABLE: LEGORACERS 0x004b0164
// SIZE 0x270
class PowerupExplosion : public LegoEventQueue::Callback {
public:
	enum {
		c_stateUninitialized = 0,
		c_stateIdle = 1,
		c_stateExploding = 2,
		c_stateScarFading = 3,

		c_blastNone = 0,
		c_blastShake = 1,
		c_blastLaunch = 2,
	};

	// SIZE 0x48
	struct Params {
		GolExport* m_golExport;                 // 0x00
		GolCollidableEntity* m_collidable;      // 0x04
		GolModelEntity* m_model;                // 0x08
		GolMaterial* m_billboardMaterial;       // 0x0c
		GolMaterial* m_flashMaterial;           // 0x10
		GolMaterial* m_scarMaterial;            // 0x14
		LegoEventQueue* m_eventQueue;           // 0x18
		RacePowerupManager* m_manager;          // 0x1c
		MabMaterialTrack* m_billboardAnimation; // 0x20
		LegoU32 m_billboardMaterialIndex;       // 0x24
		CutsceneAnimation* m_particleAnimation; // 0x28
		LegoU32 m_flashDurationMs;              // 0x2c
		LegoU32 m_scarDurationMs;               // 0x30
		LegoFloat m_modelScale;                 // 0x34
		LegoFloat m_flashWidth;                 // 0x38
		LegoFloat m_flashHeight;                // 0x3c
		LegoFloat m_blastRadius;                // 0x40
		LegoU32 m_blastMode;                    // 0x44
	};

	PowerupExplosion();
	void OnEvent(LegoEventQueue::CallbackData* p_data) override; // vtable+0x00
	virtual ~PowerupExplosion();                                 // vtable+0x04

	// SYNTHETIC: LEGORACERS 0x004587b0
	// PowerupExplosion::`vector deleting destructor'

	PowerupExplosion* GetNext() { return m_next; }
	LegoS32 GetState() const { return m_state; }
	LegoU32 GetRemainingMs() const { return m_remainingMs; }
	void SetNext(PowerupExplosion* p_next) { m_next = p_next; }
	void Initialize(const Params* p_params);
	void Destroy();
	void Spawn(const GolVec3* p_position, undefined4 p_leavesScar, Racer* p_racer);
	void Deactivate();
	void Update(LegoU32 p_elapsedMs);
	void UpdateFlash(LegoU32 p_elapsedMs);
	void DrawTransparent(GolD3DRenderDevice* p_renderer);
	void Draw(GolD3DRenderDevice* p_renderer);

private:
	LegoS32 m_state;                            // 0x004
	GolWorldEntity m_worldEntity;               // 0x008
	GolExport* m_golExport;                     // 0x030
	GolModelEntity m_modelEntity;               // 0x034
	GolBillboard* m_billboard;                  // 0x0c4
	MabMaterialTrack m_billboardAnimation;      // 0x0c8
	LegoU32 m_billboardMaterialIndex;           // 0x0e0
	RaceDecalManager::Trail::Decal m_scarDecal; // 0x0e4
	GolCollidableEntity* m_collidable;          // 0x200
	MaterialTable m_materialTable;              // 0x204
	GolMaterial* m_flashMaterial;               // 0x210
	GolMaterial* m_scarMaterial;                // 0x214
	LegoEventQueue* m_eventQueue;               // 0x218
	Racer* m_ownerRacer;                        // 0x21c
	LegoEventQueue::Event* m_collisionEvent;    // 0x220
	RacePowerupManager* m_manager;              // 0x224
	CutsceneAnimation* m_particleAnimation;     // 0x228
	LegoU32 m_blastMode;                        // 0x22c
	LegoU32 m_flashDurationMs;                  // 0x230
	LegoU32 m_scarDurationMs;                   // 0x234
	LegoU32 m_remainingMs;                      // 0x238
	LegoFloat m_alpha;                          // 0x23c
	LegoFloat m_modelAlpha;                     // 0x240
	LegoFloat m_alphaRate;                      // 0x244
	LegoFloat m_growth;                         // 0x248
	LegoFloat m_growthRate;                     // 0x24c
	LegoFloat m_initialGrowthRate;              // 0x250
	LegoFloat m_growthAcceleration;             // 0x254
	LegoFloat m_modelScale;                     // 0x258
	LegoFloat m_flashWidth;                     // 0x25c
	LegoFloat m_flashHeight;                    // 0x260
	LegoFloat m_blastRadius;                    // 0x264
	LegoS32 m_leavesScar;                       // 0x268
	PowerupExplosion* m_next;                   // 0x26c
};

#endif // POWERUPEXPLOSION_H
