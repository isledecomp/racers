#ifndef CANNONBALLRAINHAZARD_H
#define CANNONBALLRAINHAZARD_H

#include "golmath.h"
#include "golmodelentity.h"
#include "golname.h"
#include "race/hazards/hazard.h"
#include "race/hazards/hazardcontext.h"

class CutsceneAnimation;
class GolAnimatedEntity;
class GolCollidableEntity;
class MabMaterialTrack;
class SpatialSoundInstance;

struct CutsceneParticleRef;
struct SoundVector;

// VTABLE: LEGORACERS 0x004b4370
// SIZE 0x44
class CannonballRainHazard : public Hazard {
public:
	CannonballRainHazard();
	~CannonballRainHazard() override;
	void OnActivate(void* p_racer) override;                               // vtable+0x04
	void OnDeactivate(void* p_context) override;                           // vtable+0x08
	void Load(HazardContext* p_context, GolFileParser* p_parser) override; // vtable+0x10
	void Update(undefined4 p_elapsedMs) override;                          // vtable+0x14

	LegoS32 Reset();

	// SYNTHETIC: LEGORACERS 0x0048c490
	// CannonballRainHazard::`scalar deleting destructor'

private:
	void ClearFields();

	enum {
		c_randomTableMask = 0x3ff,
	};

	GolName m_materialName;               // 0x10
	GolVec3 m_dropPosition;               // 0x18
	GolVec3 m_emitterPosition;            // 0x24
	LegoFloat m_unk0x30;                  // 0x30
	RacePowerupManager* m_powerupManager; // 0x34
	GolAnimatedEntity* m_emitterEntity;   // 0x38
	LegoU32 m_timerMs;                    // 0x3c
	LegoU32 m_intervalMs;                 // 0x40
};

#endif // CANNONBALLRAINHAZARD_H
