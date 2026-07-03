#ifndef GRABBERHAZARD_H
#define GRABBERHAZARD_H

#include "golmath.h"
#include "golmodelentity.h"
#include "race/hazards/hazard.h"
#include "race/hazards/hazardcontext.h"

class CutsceneAnimation;
class GolAnimatedEntity;
class GolCollidableEntity;
class MabMaterialTrack;
class SpatialSoundInstance;

struct CutsceneParticleRef;
struct SoundVector;

// VTABLE: LEGORACERS 0x004b4518
// SIZE 0x60
class GrabberHazard : public Hazard {
public:
	GrabberHazard();
	~GrabberHazard() override;
	void OnEvent(LegoEventQueue::CallbackData* p_data) override;           // vtable+0x00
	void OnActivate(void* p_racer) override;                               // vtable+0x04
	void OnDeactivate(void* p_context) override;                           // vtable+0x08
	void Load(HazardContext* p_context, GolFileParser* p_parser) override; // vtable+0x10
	void Update(undefined4 p_elapsedMs) override;                          // vtable+0x14

	LegoS32 ClearFields();
	LegoS32 Reset();

	// SYNTHETIC: LEGORACERS 0x0048dd80
	// GrabberHazard::`scalar deleting destructor'

private:
	enum {
		c_racerFlags0xd04Bit0 = 1 << 0,
		c_racerFlags0xd04Bit29 = 0x20000000,
		c_stateOne = 1,
		c_stateTwo = 2,
		c_timerMs = 1000,
		c_restoreTimerMs = 500,
	};

	void GetGrabPosition(GolVec3* p_position);
	void ReleaseRacer();

	GolWorldEntity m_trigger;                // 0x10
	GolAnimatedEntity* m_entity;             // 0x38
	LegoEventQueue* m_eventQueue;            // 0x3c
	LegoEventQueue::Event* m_collisionEvent; // 0x40
	Racer* m_racer;                          // 0x44
	LegoFloat m_unk0x48;                     // 0x48
	LegoFloat m_unk0x4c;                     // 0x4c
	LegoFloat m_unk0x50;                     // 0x50
	LegoU32 m_stateMs;                       // 0x54
	LegoU32 m_grabState;                     // 0x58
	LegoU32 m_unk0x5c;                       // 0x5c
};

#endif // GRABBERHAZARD_H
