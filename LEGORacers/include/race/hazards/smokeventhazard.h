#ifndef SMOKEVENTHAZARD_H
#define SMOKEVENTHAZARD_H

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

// VTABLE: LEGORACERS 0x004b45e0
// SIZE 0x20
class SmokeVentHazard : public Hazard {
public:
	SmokeVentHazard();
	~SmokeVentHazard() override;
	void OnActivate(void* p_racer) override;                               // vtable+0x04
	void OnDeactivate(void* p_context) override;                           // vtable+0x08
	void Load(HazardContext* p_context, GolFileParser* p_parser) override; // vtable+0x10
	void Update(undefined4 p_elapsedMs) override;                          // vtable+0x14

	LegoS32 Reset();

	// SYNTHETIC: LEGORACERS 0x0048e6a0
	// SmokeVentHazard::`scalar deleting destructor'

private:
	enum {
		c_randomTableMask = 0x3ff,
	};

	GolAnimatedEntity* m_entity;            // 0x10
	CutsceneAnimation* m_particleAnimation; // 0x14
	CutsceneParticleRef* m_smokeParticle;   // 0x18
	LegoU32 m_mirror;                       // 0x1c
};

#endif // SMOKEVENTHAZARD_H
