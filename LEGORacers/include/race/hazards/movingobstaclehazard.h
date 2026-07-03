#ifndef MOVINGOBSTACLEHAZARD_H
#define MOVINGOBSTACLEHAZARD_H

#include "golmath.h"
#include "golmodelentity.h"
#include "material/materialtable.h"
#include "race/hazards/hazard.h"
#include "race/hazards/hazardcontext.h"
#include "race/racedecalmanager.h"
#include "race/raceresourcemanager.h"

class CutsceneAnimation;
class GolAnimatedEntity;
class GolCollidableEntity;
class MabMaterialTrack;
class SpatialSoundInstance;

struct CutsceneParticleRef;
struct SoundVector;

// VTABLE: LEGORACERS 0x004b4734
// SIZE 0x17c
class MovingObstacleHazard : public Hazard {
public:
	MovingObstacleHazard();
	~MovingObstacleHazard() override;
	void OnEvent(LegoEventQueue::CallbackData* p_data) override;           // vtable+0x00
	void OnActivate(void* p_racer) override;                               // vtable+0x04
	void OnDeactivate(void* p_context) override;                           // vtable+0x08
	void Load(HazardContext* p_context, GolFileParser* p_parser) override; // vtable+0x10
	void Update(undefined4 p_elapsedMs) override;                          // vtable+0x14
	void UpdatePerRacer(GolCamera* p_camera, Racer* p_racer) override;     // vtable+0x18
	void Draw(GolD3DRenderDevice* p_renderer) override;                    // vtable+0x1c

	LegoS32 Reset();

	// SYNTHETIC: LEGORACERS 0x0048fec0
	// MovingObstacleHazard::`scalar deleting destructor'

private:
	enum {
		c_flagShadowVisible = 1 << 0,
		c_flagImpactPending = 1 << 1,
		c_soundId = 0xbbb,
		c_impactEventId = 0x14,
		c_nearImpactEventId = 0x15,
	};

	GolWorldEntity m_trigger;                     // 0x10
	GolAnimatedEntity* m_entity;                  // 0x38
	LegoEventQueue::Event* m_collisionEvent;      // 0x3c
	LegoEventQueue* m_eventQueue;                 // 0x40
	RaceDecalManager::Trail::Decal m_shadowDecal; // 0x44
	MaterialTable m_shadowMaterialTable;          // 0x160
	GolCollidableEntity* m_trackCollidable;       // 0x16c
	SpatialSoundInstance* m_loopSound;            // 0x170
	RacerSoundSource* m_soundSource;              // 0x174
	LegoU8 m_flags;                               // 0x178
	undefined m_unk0x179[0x17c - 0x179];          // 0x179
};

#endif // MOVINGOBSTACLEHAZARD_H
