#ifndef RACETIMERLIST_H
#define RACETIMERLIST_H

#include "goltxtparser.h"
#include "types.h"
#include "util/legoeventqueue.h"

class GolFileParser;
class RaceEventTable;
class RaceSession;

// SIZE 0x0c
class RaceTimerList {
public:
	// VTABLE: LEGORACERS 0x004b1cc8
	// SIZE 0x1fc
	class TibTxtParser : public GolTxtParser {
	public:
		// .tib tokens
		enum {
			e_timer = 0x27,
			e_onPhase = 0x28,
			e_offPhase = 0x29,
			e_event = 0x2a,
			e_duration = 0x2b,
			e_initialDelay = 0x2d,
		};
	};

	// VTABLE: LEGORACERS 0x004b1cc0
	// SIZE 0x24
	class Resource : public LegoEventQueue::Callback {
	public:
		enum {
			c_active = 1 << 0,
			c_randomizeOnDuration = 1 << 1,
			c_randomizeOffDuration = 1 << 2,
			c_randomTableMask = 0x3ff,
		};

		Resource();
		void OnEvent(LegoEventQueue::CallbackData* p_data) override; // vtable+0x00
		virtual ~Resource();                                         // vtable+0x04

		void Initialize(
			LegoEventQueue* p_eventQueue,
			RaceEventTable* p_eventTable,
			LegoU32 p_onDurationMs,
			LegoU32 p_offDurationMs,
			LegoU32 p_delayMs,
			LegoS32 p_eventId,
			LegoU32 p_flags
		);
		void Reset();
		void Update(LegoU32 p_elapsedMs);
		LegoEventQueue::Event* Schedule(LegoU32 p_delayMs);

		// SYNTHETIC: LEGORACERS 0x00464d70
		// RaceTimerList::Resource::`vector deleting destructor'

	private:
		LegoEventQueue::Event* m_event; // 0x04
		RaceEventTable* m_eventTable;   // 0x08
		LegoEventQueue* m_eventQueue;   // 0x0c
		LegoU32 m_onDurationMs;         // 0x10
		LegoU32 m_offDurationMs;        // 0x14
		LegoU32 m_delayMs;              // 0x18
		LegoU32 m_flags;                // 0x1c
		LegoS32 m_eventId;              // 0x20
	};

	RaceTimerList();
	~RaceTimerList();
	LegoU32 Update(LegoU32 p_elapsedMs);

private:
	friend class RaceSession;

	void Destroy();
	void Load(LegoEventQueue* p_eventQueue, RaceEventTable* p_eventTable, const LegoChar* p_name, LegoBool32 p_binary);

	RaceEventTable* m_eventTable; // 0x00
	LegoU32 m_count;              // 0x04
	Resource* m_timers;           // 0x08
};

#endif // RACETIMERLIST_H
