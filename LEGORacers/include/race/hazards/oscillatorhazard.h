#ifndef OSCILLATORHAZARD_H
#define OSCILLATORHAZARD_H

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

// VTABLE: LEGORACERS 0x004b41c4
// SIZE 0x20
class OscillatorHazard : public Hazard {
public:
	OscillatorHazard();
	~OscillatorHazard() override;
	void OnActivate(void* p_racer) override;                               // vtable+0x04
	void OnDeactivate(void* p_context) override;                           // vtable+0x08
	void Load(HazardContext* p_context, GolFileParser* p_parser) override; // vtable+0x10
	void Update(undefined4 p_elapsedMs) override;                          // vtable+0x14

	LegoS32 Reset();

	// SYNTHETIC: LEGORACERS 0x0048b0a0
	// OscillatorHazard::`scalar deleting destructor'

private:
	GolModelEntity* m_entity; // 0x10
	LegoFloat m_amplitude0;   // 0x14
	LegoFloat m_amplitude1;   // 0x18
	LegoFloat m_phaseMs;      // 0x1c
};

#endif // OSCILLATORHAZARD_H
