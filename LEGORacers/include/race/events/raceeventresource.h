#ifndef RACEEVENTRESOURCE_H
#define RACEEVENTRESOURCE_H

#include "compat.h"
#include "decomp.h"
#include "golmath.h"
#include "types.h"

class RaceEventTable;
class Racer;

// VTABLE: LEGORACERS 0x004b1b28
// SIZE 0x20
class RaceEventResource {
public:
	// Lifecycle states: Idle (never started / fully reset), Starting
	// (intro phase), Active, Ended (outro phase / restartable), EndPending
	// (auto-OnEnd on next Update).
	enum {
		c_stateIdle = 1,
		c_stateStarting = 2,
		c_stateActive = 3,
		c_stateEnded = 4,
		c_stateEndPending = 5,
		c_flagNoEnd = 1 << 1,
		c_flagTriggerOnEnd = 1 << 2,
		c_flagAtEventPosition = 1 << 3,
		c_flagBit5 = 1 << 5
	};

	RaceEventResource();
	virtual void OnStartForRacer(Racer* p_racer); // vtable+0x00
	virtual void OnStartAt(GolVec3* p_position);  // vtable+0x04
	virtual void OnEndForRacer(Racer* p_racer);   // vtable+0x08
	virtual void OnEnd();                         // vtable+0x0c
	virtual ~RaceEventResource();                 // vtable+0x10
	virtual void Update(LegoU32 p_elapsedMs);     // vtable+0x14

	void ForceEventStart(Racer* p_racer);
	void ForceEventEnd(Racer* p_racer);
	void Reset();
	void NotifyStateChange(LegoU32 p_fromState, LegoU32 p_toState);
	void OnEventStart(GolVec3* p_position);
	void OnEventEnd(GolVec3* p_position);
	void SetState(LegoU32 p_state) { m_state = p_state; }

	// SYNTHETIC: LEGORACERS 0x0045ed70
	// RaceEventResource::`scalar deleting destructor'

public:
	RaceEventTable* m_eventTable;     // 0x04
	LegoS32 m_stateEventIds[3];       // 0x08
	LegoU32 m_eventId;                // 0x14
	LegoU32 m_state;                  // 0x18
	LegoU8 m_flags;                   // 0x1c
	undefined m_unk0x1d[0x20 - 0x1d]; // 0x1d
};

#endif // RACEEVENTRESOURCE_H
