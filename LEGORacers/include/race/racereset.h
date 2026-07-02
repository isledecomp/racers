#ifndef RACERESET_H
#define RACERESET_H

#include "app/legoracers.h"
#include "types.h"

class CutsceneAnimation;
class HazardManager;
class RacePowerupManager;
class RaceSession;
class RaceState;
class RacerTriggerList;
class TimeRaceManager;
class TriggerList;

// SIZE 0x2c
class RaceReset {
public:
	// SIZE 0x2c
	class Params {
	public:
		LegoRacers::Context* m_context;               // 0x00
		RaceState* m_raceState;                       // 0x04
		RacePowerupManager* m_powerupManager;         // 0x08
		HazardManager* m_hazardManager;               // 0x0c
		CutsceneAnimation* m_particleAnimation;       // 0x10
		CutsceneAnimation* m_sharedParticleAnimation; // 0x14
		TimeRaceManager* m_timeRaceManager;           // 0x18
		RacerTriggerList* m_racerTriggers;            // 0x1c
		TriggerList* m_triggers;                      // 0x20
		RacerCollisionWorlds* m_collisionWorlds;      // 0x24
		RaceEventTable* m_eventTable;                 // 0x28
	};

	RaceReset();
	~RaceReset();

private:
	friend class RaceSession;

	void Reset();
	void Initialize(const Params* p_source);
	void FinishRace();
	void ResetRacers();

	LegoRacers::Context* m_context;               // 0x00
	RaceState* m_raceState;                       // 0x04
	RacePowerupManager* m_powerupManager;         // 0x08
	HazardManager* m_hazardManager;               // 0x0c
	CutsceneAnimation* m_particleAnimation;       // 0x10
	CutsceneAnimation* m_sharedParticleAnimation; // 0x14
	TimeRaceManager* m_timeRaceManager;           // 0x18
	RacerTriggerList* m_racerTriggers;            // 0x1c
	TriggerList* m_triggers;                      // 0x20
	RacerCollisionWorlds* m_collisionWorlds;      // 0x24
	RaceEventTable* m_eventTable;                 // 0x28
};

#endif // RACERESET_H
