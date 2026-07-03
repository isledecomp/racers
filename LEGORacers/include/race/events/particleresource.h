#ifndef PARTICLERESOURCE_H
#define PARTICLERESOURCE_H

#include "golname.h"
#include "race/events/raceeventresource.h"

class CutsceneAnimation;
struct CutsceneParticleRef;
class GolModelEntity;

// VTABLE: LEGORACERS 0x004b1b0c
// SIZE 0x64
class ParticleResource : public RaceEventResource {
public:
	// SIZE 0x5c
	struct InitParams {
		LegoU32 m_eventId;                            // 0x00
		LegoS32 m_stateEventIds[3];                   // 0x04
		RaceEventTable* m_eventTable;                 // 0x10
		CutsceneAnimation* m_particleAnimation;       // 0x14
		CutsceneAnimation* m_sharedParticleAnimation; // 0x18
		GolModelEntity* m_trackedEntity;              // 0x1c
		LegoU32 m_nodeIndex;                          // 0x20
		GolName m_particleName;                       // 0x24
		GolVec3 m_position;                           // 0x2c
		GolVec3 m_direction;                          // 0x38
		GolVec3 m_up;                                 // 0x44
		undefined4 m_noEnd;                           // 0x50
		undefined4 m_triggerOnEnd;                    // 0x54
		undefined4 m_atEventPosition;                 // 0x58
	};

	ParticleResource();
	~ParticleResource() override;
	void OnStartAt(GolVec3* p_position) override;
	void OnEnd() override;
	void Update(LegoU32 p_elapsedMs) override;
	virtual LegoU32 GetKind(); // vtable+0x18

	void FUN_004513d0(undefined4);
	void ClearFields();
	void Initialize(InitParams* p_params);
	void Destroy();

	// SYNTHETIC: LEGORACERS 0x004602c0
	// ParticleResource::`vector deleting destructor'

private:
	CutsceneAnimation* m_particleAnimation;       // 0x20
	CutsceneAnimation* m_sharedParticleAnimation; // 0x24
	GolName m_particleName;                       // 0x28
	CutsceneParticleRef* m_particle;              // 0x30
	GolModelEntity* m_trackedEntity;              // 0x34
	LegoU32 m_nodeIndex;                          // 0x38
	GolVec3 m_position;                           // 0x3c
	GolVec3 m_direction;                          // 0x48
	GolVec3 m_up;                                 // 0x54
	LegoU32 m_partAnimations;                     // 0x60
};

#endif // PARTICLERESOURCE_H
