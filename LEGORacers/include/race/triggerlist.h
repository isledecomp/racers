#ifndef TRIGGERLIST_H
#define TRIGGERLIST_H

#include "golmath.h"
#include "goltxtparser.h"
#include "types.h"
#include "util/legoeventqueue.h"

class GolFileParser;
class RaceEventTable;
class RaceSession;
class TriggerWorld;

// VTABLE: LEGORACERS 0x004b1d54
// SIZE 0x14
class TriggerList {
public:
	// VTABLE: LEGORACERS 0x004b1d64
	// SIZE 0x1fc
	class TrbTxtParser : public GolTxtParser {
	public:
		enum {
			e_triggers = 0x27,
			e_position = 0x29,
			e_radius = 0x2a,
			e_event = 0x2b,
			e_mirror = 0x2f,
		};
	};

	class EntryParams;

	// VTABLE: LEGORACERS 0x004b1d40
	// SIZE 0x3c
	class Entry : public LegoEventQueue::Callback {
	public:
		Entry();
		void OnEvent(LegoEventQueue::CallbackData* p_data) override; // vtable+0x00
		virtual ~Entry();                                            // vtable+0x04
		virtual void Destroy();                                      // vtable+0x08
		virtual void Update(LegoU32 p_elapsedMs);                    // vtable+0x0c
		virtual void Reset();                                        // vtable+0x10

	protected:
		friend class TriggerList;
		friend class RacerTriggerList;

		enum {
			c_touchedThisFrame = 1 << 0,
			c_eventsActive = 1 << 1,
			c_mirror = 1 << 2,
		};

		void Initialize(const EntryParams* p_params);
		void CallBaseInitialize(const EntryParams* p_params) { Entry::Initialize(p_params); }
		void CallBaseOnEvent(LegoEventQueue::CallbackData* p_data) { Entry::OnEvent(p_data); }
		void CallBaseDestroy() { Entry::Destroy(); }
		void CallBaseUpdate(LegoU32 p_elapsedMs) { Entry::Update(p_elapsedMs); }
		void CallBaseReset() { Entry::Reset(); }

		GolWorldEntity m_body;          // 0x04
		LegoEventQueue::Event* m_event; // 0x2c
		RaceEventTable* m_eventTable;   // 0x30
		LegoS32 m_eventId;              // 0x34
		LegoU32 m_flags;                // 0x38
	};

	// SIZE 0x1c
	class EntryParams {
	public:
		RaceEventTable* m_eventTable; // 0x00
		LegoS32 m_eventId;            // 0x04
		GolVec3 m_position;           // 0x08
		LegoFloat m_radius;           // 0x14
		LegoBool32 m_mirror;          // 0x18
	};

	TriggerList();
	virtual ~TriggerList();                      // vtable+0x00
	virtual void Destroy();                      // vtable+0x04
	virtual LegoU32 Update(LegoU32 p_elapsedMs); // vtable+0x08
	virtual LegoU32 Reset();                     // vtable+0x0c

	// SYNTHETIC: LEGORACERS 0x00464fc0
	// TriggerList::`scalar deleting destructor'

	// SYNTHETIC: LEGORACERS 0x00465180
	// TriggerList::Entry::`vector deleting destructor'

protected:
	friend class RaceSession;

	void Load(
		LegoEventQueue* p_eventQueue,
		RaceEventTable* p_eventTable,
		const LegoChar* p_name,
		LegoBool32 p_binary,
		LegoBool32 p_mirror
	);

	GolFileParser* CreateParser(const LegoChar* p_name, LegoBool32 p_binary);
	void DestroyParser(GolFileParser* p_parser);
	void ParseTrigger(GolFileParser* p_parser, EntryParams* p_params);
	LegoEventQueue::Event* RegisterTrigger(Entry* p_entry, LegoBool32 p_projectiles);

	LegoEventQueue* m_eventQueue; // 0x04
	RaceEventTable* m_eventTable; // 0x08
	LegoU32 m_count;              // 0x0c
	Entry* m_entries;             // 0x10
};

#endif // TRIGGERLIST_H
