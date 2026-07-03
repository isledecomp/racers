#ifndef CURSEDROPHAZARD_H
#define CURSEDROPHAZARD_H

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

// VTABLE: LEGORACERS 0x004b423c
// SIZE 0x18
class CurseDropHazard : public Hazard {
public:
	CurseDropHazard();
	~CurseDropHazard() override;
	void OnActivate(void* p_racer) override;                               // vtable+0x04
	void OnDeactivate(void* p_context) override;                           // vtable+0x08
	void Load(HazardContext* p_context, GolFileParser* p_parser) override; // vtable+0x10
	void Update(undefined4 p_elapsedMs) override;                          // vtable+0x14

	LegoS32 Reset();

	// SYNTHETIC: LEGORACERS 0x0048b310
	// CurseDropHazard::`scalar deleting destructor'

private:
	enum {
		c_randomTableMask = 0x3ff,
		c_positionCount = 3,
	};

	RacePowerupManager* m_powerupManager; // 0x10
	LegoU32 m_mirror;                     // 0x14
};

#endif // CURSEDROPHAZARD_H
