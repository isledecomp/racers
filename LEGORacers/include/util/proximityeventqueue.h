#ifndef PROXIMITYEVENTQUEUE_H
#define PROXIMITYEVENTQUEUE_H

#include "compat.h"
#include "util/legoeventqueue.h"

// VTABLE: LEGORACERS 0x004b0724
// SIZE 0x2c
class ProximityEventQueue : public LegoEventQueue {
public:
	ProximityEventQueue();
	LegoS32 AddEvent(Event* p_event) override; // vtable+0x00

	// SYNTHETIC: LEGORACERS 0x0042fca0
	// ProximityEventQueue::`scalar deleting destructor'

	// FUNCTION: LEGORACERS 0x0042fcc0
	// ProximityEventQueue::~ProximityEventQueue

	void Destroy() override;                                // vtable+0x0c
	void Update(LegoU32 p_elapsedMs) override;              // vtable+0x10
	virtual GolWorldEntity* GetEventEntity(Event* p_event); // vtable+0x14

protected:
	void TestPairs();
	void SortList();
	void PruneSortedList();

	Event* m_sortedList; // 0x28
};

#endif // PROXIMITYEVENTQUEUE_H
