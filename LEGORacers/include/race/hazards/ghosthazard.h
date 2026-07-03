#ifndef GHOSTHAZARD_H
#define GHOSTHAZARD_H

#include "race/hazards/hazard.h"
#include "golmath.h"
#include "race/raceresourcemanager.h"
#include "golmodelentity.h"
#include "race/hazards/hazardcontext.h"

class CutsceneAnimation;
class GolAnimatedEntity;
class GolCollidableEntity;
class MabMaterialAnimationItem0x18;
class SpatialSoundInstance;

struct CutsceneParticleRef;
struct SoundVector;

// VTABLE: LEGORACERS 0x004b43dc
// SIZE 0x220
class GhostHazard : public Hazard {
public:
	GhostHazard();
	~GhostHazard() override;
	void VTable0x00(LegoEventQueue::CallbackData* p_data) override;  // vtable+0x00
	void OnActivate(void* p_unk0x04) override;                       // vtable+0x04
	void OnDeactivate(void* p_unk0x04) override;                     // vtable+0x08
	void Load(HazardContext* p_context, GolFileParser* p_parser) override; // vtable+0x10
	void Update(undefined4 p_elapsedMs) override;                    // vtable+0x14
	void Draw(GolD3DRenderDevice* p_renderer) override;              // vtable+0x1c

	LegoS32 Reset();

	// SYNTHETIC: LEGORACERS 0x0048c8c0
	// GhostHazard::`scalar deleting destructor'

private:
	enum {
		c_randomTableMask = 0x3ff,
		c_soundId0xbc5 = 0xbc5,
		c_soundId0xbc7 = 0xbc7,
		c_racerFlags0xd04Bit0 = 1 << 0,
		c_racerSearchIntervalMs = 4000,
		c_soundFrequencyUpdateMs = 500,
		c_randomFrequencyVariantCount = 100,
		c_trailFrameOffsetStep = 100,
		c_trailFrameOffsetEnd = 400,
	};

	void ClearFields();

	GolWorldEntity m_trigger;                // 0x10
	GolAnimatedEntity* m_ghostEntity;        // 0x38
	GolModelEntity* m_trailModel;            // 0x3c
	LegoEventQueue* m_eventQueue;            // 0x40
	LegoEventQueue::Event* m_collisionEvent; // 0x44
	CutsceneAnimation* m_particleAnimation;  // 0x48
	CutsceneParticleRef* m_trailParticle;    // 0x4c
	union {
		SpatialSoundInstance* m_loopSound;                  // 0x50
		RaceResourceManager::Resource* m_loopSoundResource; // 0x50
	};
	RacerSoundSource* m_soundSource; // 0x54
	RaceState* m_raceState;          // 0x58
	undefined4 m_unk0x5c;            // 0x5c
	LegoS32 m_animationFrameCount;   // 0x60
	LegoU32 m_soundJitterMs;         // 0x64
	LegoFloat m_frequencyJitter;     // 0x68
	LegoU32 m_racerSearchMs;         // 0x6c
	GolModelEntity m_trailModels[3]; // 0x70
};


#endif // GHOSTHAZARD_H
