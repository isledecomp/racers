#ifndef SPHINXHAZARD_H
#define SPHINXHAZARD_H

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

// VTABLE: LEGORACERS 0x004b433c
// SIZE 0x24
class SphinxHazard : public Hazard {
public:
	SphinxHazard();
	~SphinxHazard() override;
	void OnActivate(void* p_racer) override;                               // vtable+0x04
	void OnDeactivate(void* p_context) override;                           // vtable+0x08
	void Load(HazardContext* p_context, GolFileParser* p_parser) override; // vtable+0x10
	void Update(undefined4 p_elapsedMs) override;                          // vtable+0x14
	void ResetState() override;                                            // vtable+0x24

	LegoS32 Reset();

	// SYNTHETIC: LEGORACERS 0x0048c050
	// SphinxHazard::`scalar deleting destructor'

private:
	enum {
		c_modelDistanceCount = 3,
	};

	CutsceneAnimation* m_particleAnimation; // 0x10
	GolWorldDatabase* m_sharedDatabase;     // 0x14
	MabMaterialTrack* m_blowupItem;         // 0x18
	GolAnimatedEntity* m_entity;            // 0x1c
	ColliderRecord* m_collider;             // 0x20
};

#endif // SPHINXHAZARD_H
