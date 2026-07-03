#ifndef SWEEPCANNONHAZARD_H
#define SWEEPCANNONHAZARD_H

#include "golmath.h"
#include "golmodelentity.h"
#include "race/hazards/hazard.h"
#include "race/hazards/hazardcontext.h"
#include "race/raceactionsource.h"

class CutsceneAnimation;
class GolAnimatedEntity;
class GolCollidableEntity;
class MabMaterialTrack;
class SpatialSoundInstance;

struct CutsceneParticleRef;
struct SoundVector;

// VTABLE: LEGORACERS 0x004b4274
// SIZE 0x58
class SweepCannonHazard : public Hazard {
public:
	SweepCannonHazard();
	~SweepCannonHazard() override;
	void OnActivate(void* p_racer) override;                               // vtable+0x04
	void OnDeactivate(void* p_context) override;                           // vtable+0x08
	void Load(HazardContext* p_context, GolFileParser* p_parser) override; // vtable+0x10
	void Update(undefined4 p_elapsedMs) override;                          // vtable+0x14

	void ClearFields();
	LegoS32 Reset();

	// SYNTHETIC: LEGORACERS 0x0048b4d0
	// SweepCannonHazard::`scalar deleting destructor'

private:
	enum {
		c_actionCooldownMs = 0x206c,
	};

	RaceActionSource m_source;            // 0x10
	RacePowerupManager* m_powerupManager; // 0x34
	GolAnimatedEntity* m_trackedEntity;   // 0x38
	LegoFloat m_sweepAngle;               // 0x3c
	LegoFloat m_verticalRange;            // 0x40
	LegoFloat m_verticalBase;             // 0x44
	LegoU32 m_sweepMs;                    // 0x48
	LegoU32 m_cooldownMs;                 // 0x4c
	LegoU32 m_periodMs;                   // 0x50
	LegoU32 m_mirror;                     // 0x54
};

#endif // SWEEPCANNONHAZARD_H
