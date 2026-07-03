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
	enum {
		c_state0x18One = 1,
		c_state0x18Three = 3,
		c_state0x18Four = 4,
		c_state0x18Five = 5,
		c_flags0x1cBit1 = 1 << 1,
		c_flags0x1cBit2 = 1 << 2,
		c_flags0x1cBit3 = 1 << 3,
		c_flags0x1cBit5 = 1 << 5
	};

	RaceEventResource();
	virtual void OnStartForRacer(Racer* p_racer); // vtable+0x00
	virtual void OnStartAt(GolVec3* p_position);  // vtable+0x04
	virtual void OnEndForRacer(Racer* p_racer);   // vtable+0x08
	virtual void OnEnd();                         // vtable+0x0c
	virtual ~RaceEventResource();                          // vtable+0x10
	virtual void Update(LegoU32 p_elapsedMs);     // vtable+0x14

	void ForceEventStart(Racer* p_racer);
	void ForceEventEnd(Racer* p_racer);
	void Reset();
	void NotifyStateChange(LegoU32 p_unk0x04, LegoU32 p_unk0x08);
	void OnEventStart(GolVec3* p_position);
	void OnEventEnd(GolVec3* p_position);
	void SetState0x18(LegoU32 p_state) { m_state0x18 = p_state; }

	// SYNTHETIC: LEGORACERS 0x0045ed70
	// RaceEventResource::`scalar deleting destructor'

public:
	RaceEventTable* m_eventTable;     // 0x04
	LegoS32 m_stateEventIds[3];       // 0x08
	undefined4 m_eventId;             // 0x14
	LegoU32 m_state0x18;              // 0x18
	LegoU8 m_flags0x1c;               // 0x1c
	undefined m_unk0x1d[0x20 - 0x1d]; // 0x1d
};

#endif // RACEEVENTRESOURCE_H
