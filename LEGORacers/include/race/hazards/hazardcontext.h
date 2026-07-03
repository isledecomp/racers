#ifndef HAZARDCONTEXT_H
#define HAZARDCONTEXT_H

#include "types.h"

class RaceTrailManager;
class CutsceneAnimation;
class GolCollidableEntity;
class GolD3DRenderDevice;
class GolExport;
class GolNameTable;
class GolWorldDatabase;
class LegoEventQueue;
class RaceEventTable;
class RacePowerupManager;
class RaceState;
class RacerSoundSource;
class TriggerWorld;

// SIZE 0x60
class HazardContext {
public:
	class PositionProvider {
	public:
		virtual void VTable0x00() = 0;       // vtable+0x00
		virtual void GetPosition(void*) = 0; // vtable+0x04
	};

	RaceEventTable* GetEventTable() const { return m_eventTable; }
	LegoEventQueue* GetEventQueue() const { return m_eventQueue; }
	RacerSoundSource* GetSoundSource() const { return m_soundSource; }
	GolWorldDatabase* GetTrackDatabase() const { return m_trackDatabase; }
	GolWorldDatabase* GetSharedDatabase() const { return m_sharedDatabase; }
	CutsceneAnimation* GetParticleAnimation() const { return m_particleAnimation; }
	GolCollidableEntity* GetTrackCollidable() const { return m_trackCollidable; }
	GolExport* GetGolExport() const { return m_golExport; }
	GolD3DRenderDevice* GetRenderer() const { return m_renderer; }
	GolNameTable* GetColliderTable() const { return m_colliderTable; }
	RaceState* GetRaceState() const { return m_raceState; }
	TriggerWorld* GetTriggerWorld() const { return m_triggerWorld; }
	RacePowerupManager* GetPowerupManager() const { return m_powerupManager; }
	RaceTrailManager* GetTrailManager() const { return m_trailManager; }
	LegoU32 GetMirror() const { return m_mirror; }
	PositionProvider* GetPositionProvider() const { return m_positionProvider; }

private:
	friend class HazardManager;
	friend class RaceSession;

	LegoEventQueue* m_eventQueue;           // 0x00
	void* m_context;                        // 0x04
	RacerSoundSource* m_soundSource;        // 0x08
	RaceEventTable* m_eventTable;           // 0x0c
	GolWorldDatabase* m_trackDatabase;      // 0x10
	GolWorldDatabase* m_sharedDatabase;     // 0x14
	GolWorldDatabase* m_triggerDatabase;    // 0x18
	CutsceneAnimation* m_particleAnimation; // 0x1c
	GolCollidableEntity* m_trackCollidable; // 0x20
	GolExport* m_golExport;                 // 0x24
	GolD3DRenderDevice* m_renderer;         // 0x28
	GolNameTable* m_colliderTable;          // 0x2c
	RaceState* m_raceState;                 // 0x30
	TriggerWorld* m_triggerWorld;           // 0x34
	RacePowerupManager* m_powerupManager;   // 0x38
	RaceTrailManager* m_trailManager;       // 0x3c
	LegoU32 m_mirror;                       // 0x40
	undefined m_unk0x44[0x5c - 0x44];       // 0x44
	PositionProvider* m_positionProvider;   // 0x5c
};

#endif // HAZARDCONTEXT_H
