#ifndef LAUNCHERHAZARD_H
#define LAUNCHERHAZARD_H

#include "golmath.h"
#include "golmodelentity.h"
#include "race/hazards/hazard.h"
#include "race/hazards/hazardcontext.h"
#include "race/powerups/powerupprojectile.h"
#include "race/racetrailmanager.h"

class CutsceneAnimation;
class GolAnimatedEntity;
class GolCollidableEntity;
class MabMaterialTrack;
class SpatialSoundInstance;

struct CutsceneParticleRef;
struct SoundVector;

// VTABLE: LEGORACERS 0x004b46c8
// SIZE 0x124
class LauncherHazard : public Hazard {
public:
	LauncherHazard();
	~LauncherHazard() override;
	void OnActivate(void* p_racer) override;                               // vtable+0x04
	void OnDeactivate(void* p_context) override;                           // vtable+0x08
	void Load(HazardContext* p_context, GolFileParser* p_parser) override; // vtable+0x10
	void Update(undefined4 p_elapsedMs) override;                          // vtable+0x14
	void Draw(GolD3DRenderDevice* p_renderer) override;                    // vtable+0x1c
	void OnEventStart(LegoS32 p_eventId, void* p_context) override;        // vtable+0x28

	void ClearFields();
	void Reset();

	// SYNTHETIC: LEGORACERS 0x0048f740
	// LauncherHazard::`scalar deleting destructor'

protected:
	GolWorldEntity m_trigger;             // 0x10
	PowerupProjectile m_projectile;       // 0x38
	GolVec3 m_launchPosition;             // 0xe0
	GolVec3 m_targetPosition;             // 0xec
	GolVec3 m_triggerPosition;            // 0xf8
	LegoFloat m_triggerRadiusSquared;     // 0x104
	LegoS32 m_triggerEventId;             // 0x108
	TriggerWorld* m_triggerWorld;         // 0x10c
	RacePowerupManager* m_powerupManager; // 0x110
	GolBillboard* m_billboard;            // 0x114
	GolExport* m_golExport;               // 0x118
	RaceTrailManager* m_trailManager;     // 0x11c
	RaceTrailManager::Trail* m_trail;     // 0x120
};

#endif // LAUNCHERHAZARD_H
