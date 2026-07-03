#ifndef RACEROSTER_H
#define RACEROSTER_H

#include "golmath.h"
#include "util/collisioneventqueue.h"
#include "util/legoeventqueue.h"

class Racer;
class GolWorldDatabase;

// Race roster and event hub: the racer array plus the shared per-race
// services wired through the event queue callback interface.
// VTABLE: LEGORACERS 0x004b0aa8
// SIZE 0x194
class RaceRoster : public CollisionEventQueue {
public:
	enum {
		c_soundProximity = 0x4f,
	};

	RaceRoster();
	LegoS32 AddEvent(LegoEventQueue::Event* p_event) override;               // vtable+0x00
	void Destroy() override;                                                 // vtable+0x0c
	void Update(LegoU32 p_elapsedMs) override;                               // vtable+0x10
	GolWorldEntity* GetEventEntity(LegoEventQueue::Event* p_event) override; // vtable+0x14

private:
	friend class RaceState;

	void PruneBodyEvents();
	void TestRacerCollisions();
	void SortBodyEvents();

	LegoEventQueue::Event* m_bodyEvents;       // 0x048
	RaceState* m_raceState;                    // 0x04c
	Racer* m_racers;                           // 0x050
	LegoU32 m_racerCount;                      // 0x054
	CheckpointGraph* m_checkpointGraph;        // 0x058
	RacerSoundSource* m_soundSource;           // 0x05c
	RacePowerupManager* m_powerupManager;      // 0x060
	LegoEventQueue::Event* m_racerEvents[6];   // 0x064
	SpatialSoundInstance* m_proximitySound;    // 0x07c
	Racer* m_currentRacer;                     // 0x080
	GolExport* m_golExport;                    // 0x084
	TimeRaceManager* m_timeRaceManager;        // 0x088
	GolModelEntity* m_customCarModels[2];      // 0x08c
	GolAnimatedEntity* m_customCarEntities[2]; // 0x094
	LegoU32 m_customCarCount;                  // 0x09c
	RaceRouteRecord* m_routeRecords;           // 0x0a0
	GolVec3 m_startPositions[6];               // 0x0a4
	GolVec3 m_startDirections[6];              // 0x0ec
	GolVec3 m_startUps[6];                     // 0x134
	LegoU32 m_placementSlots[6];               // 0x17c
};

#endif // RACEROSTER_H
