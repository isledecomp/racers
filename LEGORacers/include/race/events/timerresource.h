#ifndef TIMERRESOURCE_H
#define TIMERRESOURCE_H

#include "compat.h"
#include "decomp.h"
#include "race/events/raceeventresource.h"
#include "types.h"

class RaceEventTable;

// VTABLE: LEGORACERS 0x004b1af0
// SIZE 0x30
class TimerResource : public RaceEventResource {
public:
	// .evb timer field tokens
	enum {
		e_durationMs = 0x49,
		e_holdEventId = 0x4c,
	};

	// SIZE 0x20
	struct InitParams {
		LegoU32 m_eventId;            // 0x00
		LegoS32 m_stateEventIds[3];   // 0x04
		RaceEventTable* m_eventTable; // 0x10
		LegoS32 m_holdEventId;        // 0x14
		LegoU32 m_durationMs;         // 0x18
		LegoBool32 m_triggerOnEnd;    // 0x1c
	};

	TimerResource();
	~TimerResource() override;
	void OnStartAt(GolVec3* p_position) override;
	void OnEnd() override;
	void Update(LegoU32 p_elapsedMs) override;
	LegoU32 GetKind() override; // vtable+0x18

	void FUN_004513d0(undefined4);
	void ClearFields();
	void Initialize(InitParams* p_params);
	void Destroy();

	// SYNTHETIC: LEGORACERS 0x00460cb0
	// TimerResource::`vector deleting destructor'

public:
	LegoS32 m_holdEventId;            // 0x20
	LegoU32 m_durationMs;             // 0x24
	LegoU32 m_remainingMs;            // 0x28
	LegoU8 m_timerFlags;              // 0x2c
	undefined m_unk0x2d[0x30 - 0x2d]; // 0x2d
};

#endif // TIMERRESOURCE_H
