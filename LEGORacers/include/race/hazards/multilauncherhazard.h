#ifndef MULTILAUNCHERHAZARD_H
#define MULTILAUNCHERHAZARD_H

#include "golmath.h"
#include "golmodelentity.h"
#include "race/hazards/hazardcontext.h"
#include "race/hazards/launcherhazard.h"

class CutsceneAnimation;
class GolAnimatedEntity;
class GolCollidableEntity;
class MabMaterialTrack;
class SpatialSoundInstance;

struct CutsceneParticleRef;
struct SoundVector;

// VTABLE: LEGORACERS 0x004b4684
// SIZE 0x140
class MultiLauncherHazard : public LauncherHazard {
public:
	MultiLauncherHazard();
	~MultiLauncherHazard() override;
	void OnActivate(void* p_racer) override;                               // vtable+0x04
	void OnDeactivate(void* p_context) override;                           // vtable+0x08
	void Load(HazardContext* p_context, GolFileParser* p_parser) override; // vtable+0x10
	void Update(undefined4 p_elapsedMs) override;                          // vtable+0x14

	void Reset();

	// SYNTHETIC: LEGORACERS 0x0048f240
	// MultiLauncherHazard::`scalar deleting destructor'

private:
	enum {
		c_randomTableMask = 0x3ff,
	};

	GolVec3* m_launchPositions;    // 0x124
	LegoS32* m_launchEventIds;     // 0x128
	GolVec3* m_targetPositions;    // 0x12c
	LegoS32* m_targetEventIds;     // 0x130
	LegoU32 m_launchPositionCount; // 0x134
	LegoU32 m_targetPositionCount; // 0x138
	LegoU32 m_targetIndex;         // 0x13c
};

#endif // MULTILAUNCHERHAZARD_H
