#ifndef SNOWFALLHAZARD_H
#define SNOWFALLHAZARD_H

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

// VTABLE: LEGORACERS 0x004b4624
// SIZE 0x20
class SnowfallHazard : public Hazard {
public:
	SnowfallHazard();
	~SnowfallHazard() override;
	void OnActivate(void* p_racer) override;                               // vtable+0x04
	void OnDeactivate(void* p_context) override;                           // vtable+0x08
	void Load(HazardContext* p_context, GolFileParser* p_parser) override; // vtable+0x10
	void Update(undefined4 p_elapsedMs) override;                          // vtable+0x14
	void UpdatePerRacer(GolCamera* p_camera, Racer* p_racer) override;     // vtable+0x18
	void ResetState() override;                                            // vtable+0x24

	LegoS32 ClearFields();
	LegoS32 Reset();

	// SYNTHETIC: LEGORACERS 0x0048e9d0
	// SnowfallHazard::`scalar deleting destructor'

private:
	enum {
		c_snowResetMs = 1000,
		c_randomTableMask = 0x3ff,
	};

	CutsceneAnimation* m_particleAnimation; // 0x10
	CutsceneParticleRef* m_snowParticle;    // 0x14
	LegoU32 m_resetMs;                      // 0x18
	LegoU32 m_snowEnabled;                  // 0x1c
};

#endif // SNOWFALLHAZARD_H
