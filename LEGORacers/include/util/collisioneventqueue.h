#ifndef COLLISIONEVENTQUEUE_H
#define COLLISIONEVENTQUEUE_H

#include "util/proximityeventqueue.h"

// VTABLE: LEGORACERS 0x004b09e8
// SIZE 0x48
class CollisionEventQueue : public ProximityEventQueue {
public:
	CollisionEventQueue();
	LegoS32 AddEvent(Event* p_event) override;               // vtable+0x00
	void Destroy() override;                                 // vtable+0x0c
	void Update(LegoU32 p_elapsedMs) override;               // vtable+0x10
	GolWorldEntity* GetEventEntity(Event* p_event) override; // vtable+0x14

	// SIZE 0x24
	class CollisionCallbackData {
	public:
		undefined4 m_unk0x00;                  // 0x00
		GolVec3 m_contactPoint;                // 0x04
		GolVec3 m_normal;                      // 0x10
		LegoFloat m_penetrationDepth;          // 0x1c
		Descriptor::RigidBody* m_secondTarget; // 0x20
	};

protected:
	void PruneBodyList();
	void DispatchContact(Event* p_event, LegoEventQueue* p_queue, CallbackData* p_data);
	void TestBodyPairs();
	void SortBodyList();

	Event* m_bodyList;            // 0x2c
	CallbackData m_collisionData; // 0x30
};

#endif // COLLISIONEVENTQUEUE_H
