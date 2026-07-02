#ifndef RACERCONTEXT_H
#define RACERCONTEXT_H

#include "types.h"

class CheckpointGraph;
class CutsceneAnimation;
class GolBoundedEntity;
class GolCollidableEntity;
class GolD3DRenderDevice;
class GolExport;
class RaceDecalManager;
class RaceEventTable;
class RacePowerupManager;
class RaceRouteRecord;
class RacerSoundSource;

// Shared per-race context handed to every racer subsystem.
// SIZE 0x40
class RacerContext {
public:
	GolD3DRenderDevice* m_renderer;               // 0x00
	GolExport* m_golExport;                       // 0x04
	GolCollidableEntity* m_trackCollidable;       // 0x08
	GolBoundedEntity* m_trackWorld;               // 0x0c
	GolBoundedEntity* m_triggerWorld;             // 0x10
	RacerSoundSource* m_soundSource;              // 0x14
	RacePowerupManager* m_powerupManager;         // 0x18
	CutsceneAnimation* m_particleAnimation;       // 0x1c
	CutsceneAnimation* m_sharedParticleAnimation; // 0x20
	RaceDecalManager* m_decalManager;             // 0x24
	RaceEventTable* m_eventTable;                 // 0x28
	void* m_surfaceTable;                         // 0x2c
	LegoBool32 m_shadowsEnabled;                  // 0x30
	RaceRouteRecord* m_routeRecord;               // 0x34
	CheckpointGraph* m_checkpointGraph;           // 0x38
	LegoU32 m_cheatFlags;                         // 0x3c
};

#endif // RACERCONTEXT_H
