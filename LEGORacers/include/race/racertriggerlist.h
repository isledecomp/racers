#ifndef RACERTRIGGERLIST_H
#define RACERTRIGGERLIST_H

#include "race/triggerlist.h"

class GolWorldDatabase;
class RacerCollisionWorlds;
class RacePowerupManager;
class Racer;
class RaceState;

// VTABLE: LEGORACERS 0x004b1c74
// SIZE 0x18
class RacerTriggerList : public TriggerList {
public:
	enum {
		e_triggers = 0x27,
		e_projectiles = 0x2c,
		e_entity = 0x2d,
		e_lap = 0x2e,
	};

	class EntryParams;

	// VTABLE: LEGORACERS 0x004b1c5c
	// SIZE 0x58
	class Entry : public TriggerList::Entry {
	public:
		Entry();
		void OnEvent(LegoEventQueue::CallbackData* p_data) override; // vtable+0x00
		~Entry() override;                                           // vtable+0x04
		void Destroy() override;                                     // vtable+0x08
		void Update(LegoU32 p_elapsedMs) override;                   // vtable+0x0c
		void Reset() override;                                       // vtable+0x10

		void Initialize(const EntryParams* p_params);

		// SYNTHETIC: LEGORACERS 0x00464040
		// RacerTriggerList::Entry::`vector deleting destructor'

	private:
		enum {
			c_triggerOnProjectiles = 1 << 12,
			c_activatesCollisionWorld = 1 << 13,
			c_lapGated = 1 << 14
		};

		LegoU32 m_insideMask;                    // 0x3c
		LegoU32 m_previousInsideMask;            // 0x40
		RaceState* m_raceState;                  // 0x44
		RacePowerupManager* m_powerupManager;    // 0x48
		RacerCollisionWorlds* m_collisionWorlds; // 0x4c
		LegoU32 m_collisionWorldIndex;           // 0x50
		LegoU32 m_lapNumber;                     // 0x54
	};

	// SIZE 0x3c
	class EntryParams : public TriggerList::EntryParams {
	public:
		RaceState* m_raceState;                  // 0x1c
		RacePowerupManager* m_powerupManager;    // 0x20
		RacerCollisionWorlds* m_collisionWorlds; // 0x24
		LegoU32 m_lapNumber;                     // 0x28
		LegoBool32 m_triggerOnProjectiles;       // 0x2c
		LegoBool32 m_hasCollisionWorld;          // 0x30
		LegoBool32 m_hasLapNumber;               // 0x34
		LegoU32 m_collisionWorldIndex;           // 0x38
	};

	RacerTriggerList();
	~RacerTriggerList() override;                 // vtable+0x00
	void Destroy() override;                      // vtable+0x04
	LegoU32 Update(LegoU32 p_elapsedMs) override; // vtable+0x08
	LegoU32 Reset() override;                     // vtable+0x0c

	// SYNTHETIC: LEGORACERS 0x00463d50
	// RacerTriggerList::`scalar deleting destructor'

private:
	friend class RaceSession;

	void Load(
		RaceState* p_raceState,
		RaceEventTable* p_eventTable,
		RacePowerupManager* p_powerupManager,
		GolWorldDatabase* p_worldDatabase,
		RacerCollisionWorlds* p_collisionWorlds,
		const LegoChar* p_name,
		LegoBool32 p_binary,
		LegoBool32 p_mirror
	);

	Entry* m_racerEntries; // 0x14
};

#endif // RACERTRIGGERLIST_H
