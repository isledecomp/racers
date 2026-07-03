#ifndef LAVAGEYSERHAZARD_H
#define LAVAGEYSERHAZARD_H

#include "golmath.h"
#include "golmodelentity.h"
#include "race/hazards/hazard.h"
#include "race/hazards/hazardcontext.h"
#include "race/raceresourcemanager.h"

class CutsceneAnimation;
class GolAnimatedEntity;
class GolCollidableEntity;
class MabMaterialTrack;
class SpatialSoundInstance;

struct CutsceneParticleRef;
struct SoundVector;

// VTABLE: LEGORACERS 0x004b44e0
// SIZE 0x5c
class LavaGeyserHazard : public Hazard {
public:
	LavaGeyserHazard();
	~LavaGeyserHazard() override;
	void OnEvent(LegoEventQueue::CallbackData* p_data) override;           // vtable+0x00
	void OnActivate(void* p_racer) override;                               // vtable+0x04
	void OnDeactivate(void* p_context) override;                           // vtable+0x08
	void Load(HazardContext* p_context, GolFileParser* p_parser) override; // vtable+0x10
	void Update(undefined4 p_elapsedMs) override;                          // vtable+0x14

	LegoS32 ClearFields();
	LegoS32 Reset();

	// SYNTHETIC: LEGORACERS 0x0048d850
	// LavaGeyserHazard::`scalar deleting destructor'

private:
	enum {
		c_lavaPositionCount = 3,
		c_smokeCooldownMs = 800,
		c_eventCooldownMs = 400,
		c_eventId = 0x2b,
		c_soundId = 0xbba,
	};

	GolWorldEntity m_trigger;                // 0x10
	GolAnimatedEntity* m_entity;             // 0x38
	LegoEventQueue* m_eventQueue;            // 0x3c
	LegoEventQueue::Event* m_collisionEvent; // 0x40
	CutsceneAnimation* m_particleAnimation;  // 0x44
	SpatialSoundInstance* m_loopSound;       // 0x48
	RacerSoundSource* m_soundSource;         // 0x4c
	LegoU32 m_smokeMs;                       // 0x50
	LegoU32 m_eventMs;                       // 0x54
	LegoU32 m_unk0x58;                       // 0x58
};

#endif // LAVAGEYSERHAZARD_H
