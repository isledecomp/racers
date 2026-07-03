#ifndef ROLLINGROCKHAZARD_H
#define ROLLINGROCKHAZARD_H

#include "golanimatedentity.h"
#include "golmath.h"
#include "golmodelentity.h"
#include "race/hazards/hazard.h"
#include "race/hazards/hazardcontext.h"
#include "race/racer/racerboxbody.h"

class CutsceneAnimation;
class GolAnimatedEntity;
class GolCollidableEntity;
class MabMaterialTrack;
class SpatialSoundInstance;

struct CutsceneParticleRef;
struct SoundVector;

// VTABLE: LEGORACERS 0x004b42f0
// SIZE 0x204
class RollingRockHazard : public Hazard {
public:
	RollingRockHazard();
	~RollingRockHazard() override;
	void OnActivate(void* p_racer) override;                               // vtable+0x04
	void OnDeactivate(void* p_context) override;                           // vtable+0x08
	void Load(HazardContext* p_context, GolFileParser* p_parser) override; // vtable+0x10
	void Update(undefined4 p_elapsedMs) override;                          // vtable+0x14

	// SYNTHETIC: LEGORACERS 0x0048bb80
	// RollingRockHazard::`scalar deleting destructor'

private:
	void Reset();

	RacerBoxBody m_body;                     // 0x10
	GolAnimatedEntity m_bodyEntity;          // 0x0f4
	GolAnimatedEntity* m_entity;             // 0x1e8
	LegoEventQueue* m_eventQueue;            // 0x1ec
	LegoEventQueue::Event* m_collisionEvent; // 0x1f0
	LegoFloat m_sizeX;                       // 0x1f4
	LegoFloat m_sizeY;                       // 0x1f8
	LegoFloat m_sizeZ;                       // 0x1fc
	LegoU32 m_isRock;                        // 0x200
};

#endif // ROLLINGROCKHAZARD_H
