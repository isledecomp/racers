#ifndef HAMMERHAZARD_H
#define HAMMERHAZARD_H

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

// VTABLE: LEGORACERS 0x004b4434
// SIZE 0x18
class HammerHazard : public Hazard {
public:
	HammerHazard();
	~HammerHazard() override;
	void OnActivate(void* p_racer) override;                               // vtable+0x04
	void OnDeactivate(void* p_context) override;                           // vtable+0x08
	void Load(HazardContext* p_context, GolFileParser* p_parser) override; // vtable+0x10
	void Update(undefined4 p_elapsedMs) override;                          // vtable+0x14

	LegoS32 Reset();

	// SYNTHETIC: LEGORACERS 0x0048d010
	// HammerHazard::`scalar deleting destructor'

private:
	GolAnimatedEntity* m_entity; // 0x10
	LegoU32 m_unk0x14;           // 0x14
};

#endif // HAMMERHAZARD_H
