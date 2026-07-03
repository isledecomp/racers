#ifndef FALLINGPILLARHAZARD_H
#define FALLINGPILLARHAZARD_H

#include "golmath.h"
#include "golmodelentity.h"
#include "race/hazards/colliderrecord.h"
#include "race/hazards/hazard.h"
#include "race/hazards/hazardcontext.h"

class CutsceneAnimation;
class GolAnimatedEntity;
class GolCollidableEntity;
class MabMaterialTrack;
class SpatialSoundInstance;

struct CutsceneParticleRef;
struct SoundVector;

// VTABLE: LEGORACERS 0x004b42b8
// SIZE 0x20
class FallingPillarHazard : public Hazard {
public:
	FallingPillarHazard();
	~FallingPillarHazard() override;
	void OnActivate(void*) override;                              // vtable+0x04
	void OnDeactivate(void*) override;                            // vtable+0x08
	void Load(HazardContext* p_context, GolFileParser*) override; // vtable+0x10
	void Update(undefined4 p_elapsedMs) override;                 // vtable+0x14
	void ResetState() override;                                   // vtable+0x24

	LegoS32 Reset();

	// SYNTHETIC: LEGORACERS 0x0048b8b0
	// FallingPillarHazard::`scalar deleting destructor'

private:
	GolAnimatedEntity* m_entity;            // 0x10
	CutsceneAnimation* m_particleAnimation; // 0x14
	ColliderRecord* m_collider;             // 0x18
	LegoU32 m_fallen;                       // 0x1c
};

#endif // FALLINGPILLARHAZARD_H
