#ifndef TRIGGEREDANIMATIONHAZARD_H
#define TRIGGEREDANIMATIONHAZARD_H

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

// VTABLE: LEGORACERS 0x004b4654
// SIZE 0x30
class TriggeredAnimationHazard : public Hazard {
public:
	TriggeredAnimationHazard();
	~TriggeredAnimationHazard() override;
	void OnActivate(void* p_racer) override;                               // vtable+0x04
	void OnDeactivate(void* p_context) override;                           // vtable+0x08
	void Load(HazardContext* p_context, GolFileParser* p_parser) override; // vtable+0x10
	void Update(undefined4 p_elapsedMs) override;                          // vtable+0x14
	void Draw(GolD3DRenderDevice* p_renderer) override;                    // vtable+0x1c
	void ResetState() override;                                            // vtable+0x24

	void ClearFields();
	LegoS32 Reset();

	// SYNTHETIC: LEGORACERS 0x0048ed60
	// TriggeredAnimationHazard::`scalar deleting destructor'

private:
	enum {
		c_entityCount = 4,
		c_modelDistanceCount = 3,
	};

	GolAnimatedEntity* m_entities[c_entityCount]; // 0x10
	ColliderRecord* m_collider;                   // 0x20
	GolVec3 m_unk0x24;                            // 0x24
};

#endif // TRIGGEREDANIMATIONHAZARD_H
