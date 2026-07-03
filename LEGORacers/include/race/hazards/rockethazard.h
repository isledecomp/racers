#ifndef ROCKETHAZARD_H
#define ROCKETHAZARD_H

#include "race/hazards/hazard.h"
#include "golmath.h"
#include "race/hazards/colliderrecord.h"
#include "golmodelentity.h"
#include "race/hazards/hazardcontext.h"

class CutsceneAnimation;
class GolAnimatedEntity;
class GolCollidableEntity;
class MabMaterialAnimationItem0x18;
class SpatialSoundInstance;

struct CutsceneParticleRef;
struct SoundVector;

// VTABLE: LEGORACERS 0x004b456c
// SIZE 0x5c
class RocketHazard : public Hazard {
public:
	RocketHazard();
	~RocketHazard() override;
	void VTable0x00(LegoEventQueue::CallbackData* p_data) override;  // vtable+0x00
	void OnActivate(void* p_unk0x04) override;                       // vtable+0x04
	void OnDeactivate(void* p_unk0x04) override;                     // vtable+0x08
	void Load(HazardContext* p_context, GolFileParser* p_parser) override; // vtable+0x10
	void Update(undefined4 p_elapsedMs) override;                    // vtable+0x14

	LegoS32 ClearFields();
	LegoS32 Reset();
	void ShowOnModel();
	void ShowOffModel();

	// SYNTHETIC: LEGORACERS 0x0048e300
	// RocketHazard::`scalar deleting destructor'

private:
	enum {
		c_field0x0e0Flags0xd04Bit0 = 1 << 0,
		c_modelDistanceCount = 3,
		c_eventId = 0x23,
	};

	GolWorldEntity m_trigger;                // 0x10
	LegoEventQueue* m_eventQueue;            // 0x38
	LegoEventQueue::Event* m_collisionEvent; // 0x3c
	GolModelEntity* m_offModel;              // 0x40
	GolModelEntity* m_onModel;               // 0x44
	ColliderRecord* m_collider;              // 0x48
	LegoFloat m_unk0x4c[3];                  // 0x4c
	LegoU32 m_unk0x58;                       // 0x58
};


#endif // ROCKETHAZARD_H
