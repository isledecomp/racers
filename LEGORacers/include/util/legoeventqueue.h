#ifndef LEGOEVENTQUEUE_H
#define LEGOEVENTQUEUE_H

#include "compat.h"
#include "decomp.h"
#include "golorientedentity.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004b0710
// SIZE 0x28
class LegoEventQueue {
public:
	class Event;

	// SIZE 0x18
	class Descriptor {
	public:
		enum {
			c_typeTimer = 1,
			c_typeProximity = 2,
			c_typeCollision = 3,
			c_typeRacerTrigger = 4,
		};

		// Layout mirror of the racer physics chain (RacerRigidBody 0x04-0xd0,
		// RacerBoxBody 0xd0-0xe4); racer bodies are the only implementers.
		// SIZE 0xe4
		class RigidBody {
		public:
			virtual void ComputeInertiaTensor() = 0; // vtable+0x00
			virtual void Update(LegoS32) = 0;        // vtable+0x04
			virtual GolWorldEntity* GetEntity() = 0; // vtable+0x08
			LegoBool32 CalculateBoxContact(
				RigidBody* p_other,
				LegoFloat* p_penetration,
				GolVec3* p_normal,
				GolVec3* p_contactPoint
			);

			class RacerView {
			public:
				LegoU32 GetFlags() const { return m_flags; }

				undefined m_unk0x00[0x1c - 0x00];  // 0x00
				GolWorldEntity m_entityGroup;      // 0x1c
				undefined m_unk0x44[0xd04 - 0x44]; // 0x44
				LegoU32 m_flags;                   // 0xd04
				LegoU32 m_controlMode;             // 0xd08
			};

			GolOrientedEntity* m_body;         // 0x004
			GolVec3 m_velocity;                // 0x008
			GolVec3 m_centerOfMassLocal;       // 0x014
			GolVec3 m_centerOfMassWorld;       // 0x020
			GolMatrix3 m_inertiaTensor;        // 0x02c
			GolMatrix3 m_inverseInertiaTensor; // 0x050
			GolMatrix3 m_worldInverseInertia;  // 0x074
			GolVec3 m_angularVelocity;         // 0x098
			GolVec3 m_angularMomentum;         // 0x0a4
			GolVec3 m_force;                   // 0x0b0
			GolVec3 m_torque;                  // 0x0bc
			LegoFloat m_mass;                  // 0x0c8
			LegoFloat m_inverseMass;           // 0x0cc
			LegoFloat m_boxSizeX;              // 0x0d0
			LegoFloat m_boxSizeY;              // 0x0d4
			LegoFloat m_boxSizeZ;              // 0x0d8
			LegoFloat m_boxScale;              // 0x0dc
			union {
				RacerView* m_ownerData; // 0x0e0
				void* m_owner;          // 0x0e0
			};

		private:
			LegoBool32 TestBoxOverlap(
				RigidBody* p_other,
				LegoFloat* p_penetration,
				GolVec3* p_normal,
				LegoFloat* p_distance0,
				LegoFloat* p_distance1
			);
		};

		undefined4 m_type;         // 0x00
		undefined4 m_flags;        // 0x04
		LegoU32 m_maxFireCount;    // 0x08
		undefined4 m_hitThreshold; // 0x0c
		union {
			LegoU32 m_intervalMs;          // 0x10
			void* m_data;                  // 0x10
			GolWorldEntity* m_worldEntity; // 0x10
			RigidBody* m_target;           // 0x10
		};
		union {
			LegoU32 m_elapsedMs; // 0x14
			Event* m_previous;   // 0x14
		};
	};

	// SIZE 0x18
	class CallbackData {
	public:
		undefined4 m_type;   // 0x00
		undefined4 m_flags;  // 0x04
		LegoU32 m_fireCount; // 0x08
		LegoU32 m_hitCount;  // 0x0c
		union {
			LegoU32 m_intervalMs;             // 0x10
			GolWorldEntity* m_worldEntity0;   // 0x10
			Descriptor::RigidBody* m_target0; // 0x10
		};
		union {
			LegoU32 m_elapsedMs;                            // 0x14
			void* m_data;                                   // 0x14
			GolWorldEntity* m_worldEntity1;                 // 0x14
			Descriptor::RigidBody* m_target1;               // 0x14
			Descriptor::RigidBody::RacerView* m_racerView1; // 0x14
		};
	};

	// VTABLE: LEGORACERS 0x004b016c
	// SIZE 0x04
	class Callback {
	public:
		virtual void OnEvent(CallbackData* p_data) = 0; // vtable+0x00
	};

	// SIZE 0x2c
	class Event {
	public:
		Event();
		void Initialize(Callback* p_callback, const Descriptor* p_descriptor);
		void Fire(LegoEventQueue*, CallbackData* p_data);

		Callback* m_callback;    // 0x00
		Descriptor m_descriptor; // 0x04
		LegoU32 m_fireCount;     // 0x1c
		LegoU32 m_hitCount;      // 0x20
		LegoBool32 m_active;     // 0x24
		Event* m_next;           // 0x28
	};

	LegoEventQueue();
	virtual LegoS32 AddEvent(Event* p_event); // vtable+0x00
	virtual ~LegoEventQueue();                // vtable+0x04
	// SYNTHETIC: LEGORACERS 0x0042fa10
	// LegoEventQueue::`scalar deleting destructor'
	virtual void Initialize(LegoU32 p_count); // vtable+0x08
	virtual void Destroy();                   // vtable+0x0c
	virtual void Update(LegoU32 p_elapsedMs); // vtable+0x10

	Event* AllocateEvent(Callback* p_callback, const Descriptor* p_descriptor);
	void PruneActiveList();
	Event* FreeEvent(Event* p_event);

protected:
	Event* m_events;             // 0x04
	Event* m_freeList;           // 0x08
	Event* m_activeList;         // 0x0c
	CallbackData m_callbackData; // 0x10
};

#endif // LEGOEVENTQUEUE_H
