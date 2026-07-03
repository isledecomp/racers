#ifndef WARPPADHAZARD_H
#define WARPPADHAZARD_H

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

// VTABLE: LEGORACERS 0x004b4194
// SIZE 0x18
class WarpPadHazard : public Hazard {
public:
	WarpPadHazard();
	~WarpPadHazard() override;
	void OnActivate(void* p_racer) override;                      // vtable+0x04
	void OnDeactivate(void* p_context) override;                  // vtable+0x08
	void Load(HazardContext* p_context, GolFileParser*) override; // vtable+0x10
	void Update(undefined4 p_elapsedMs) override;                 // vtable+0x14
	LegoBool32 CanRetrigger() override;                           // vtable+0x20

	LegoS32 Reset();

	// SYNTHETIC: LEGORACERS 0x0048aea0
	// WarpPadHazard::`scalar deleting destructor'

private:
	enum {
		c_flagGhost = 1 << 4,
	};

	RacePowerupManager* m_powerupManager; // 0x10
	LegoU32 m_mirror;                     // 0x14
};

#endif // WARPPADHAZARD_H
