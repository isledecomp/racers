#ifndef RACEROSTER_H
#define RACEROSTER_H

#include "golmath.h"
#include "util/legoeventqueue.h"

class Racer;
class GolWorldDatabase;

// Race roster and event hub: the racer array plus the shared per-race
// services wired through the event queue callback interface.
// VTABLE: LEGORACERS 0x004b0aa8
// SIZE 0x194
class RaceRoster : public LegoEventQueue::CollisionQueue {
public:
	RaceRoster();
	LegoS32 AddEvent(LegoEventQueue::Event* p_event) override;               // vtable+0x00
	void Destroy() override;                                                 // vtable+0x0c
	void Update(LegoU32 p_elapsedMs) override;                               // vtable+0x10
	GolWorldEntity* GetEventEntity(LegoEventQueue::Event* p_event) override; // vtable+0x14

private:
	friend class RaceState;

	// SIZE 0x28
	class Field0x064 {
	public:
		undefined m_unk0x00[0x24 - 0x00]; // 0x00
		undefined4 m_unk0x24;             // 0x24
	};

	void PruneBodyEvents();
	void TestRacerCollisions();
	void SortBodyEvents();

	LegoEventQueue::Event* m_bodyEvents; // 0x048
	RaceState* m_raceState;              // 0x04c
	Racer* m_racers;                     // 0x050
	LegoU32 m_racerCount;                // 0x054
	union {
		undefined4 m_unk0x058;         // 0x058
		CheckpointGraph* m_field0x010; // 0x058
	};
	union {
		RaceResourceManager* m_unk0x05c; // 0x05c
		RacerSoundSource* m_soundSource; // 0x05c
	};
	RacePowerupManager* m_powerupManager;    // 0x060
	LegoEventQueue::Event* m_racerEvents[6]; // 0x064
	union {
		RaceResourceManager::Resource* m_proximitySoundResource; // 0x07c
		SpatialSoundInstance* m_proximitySound;                  // 0x07c
	};
	union {
		GolExport* m_unk0x080[3]; // 0x080
		Racer* m_racer080;        // 0x080
		struct {
			undefined4* m_unk0x0800;            // 0x080
			GolExport* m_golExport;             // 0x084
			TimeRaceManager* m_timeRaceManager; // 0x088
		};
	};
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
