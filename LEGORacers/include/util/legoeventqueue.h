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
	class Field0x2c;
	class Field0x30;

	// SIZE 0x18
	class Descriptor {
	public:
		// SIZE 0xe4
		class Field0x10 {
		public:
			virtual void VTable0x00() = 0;            // vtable+0x00
			virtual void VTable0x04() = 0;            // vtable+0x04
			virtual GolWorldEntity* VTable0x08() = 0; // vtable+0x08
			LegoBool32 FUN_00441330(Field0x10* p_other, LegoFloat* p_unk0x08, GolVec3* p_unk0x0c, GolVec3* p_unk0x10);

			class Field0x0e0 {
			public:
				undefined m_unk0x00[0x1c - 0x00];  // 0x00
				GolWorldEntity m_unk0x1c;          // 0x1c
				undefined m_unk0x44[0xd08 - 0x44]; // 0x44
				LegoU32 m_unk0xd08;                // 0xd08
			};

			GolOrientedEntity* m_unk0x004;       // 0x004
			undefined m_unk0x008[0x020 - 0x008]; // 0x008
			GolVec3 m_unk0x020;                  // 0x020
			undefined m_unk0x02c[0x0d0 - 0x02c]; // 0x02c
			LegoFloat m_unk0x0d0;                // 0x0d0
			LegoFloat m_unk0x0d4;                // 0x0d4
			LegoFloat m_unk0x0d8;                // 0x0d8
			LegoFloat m_unk0x0dc;                // 0x0dc
			union {
				Field0x0e0* m_unk0x0e0; // 0x0e0
				void* m_owner;          // 0x0e0
			};

		private:
			LegoBool32 FUN_00441790(
				Field0x10* p_other,
				LegoFloat* p_unk0x08,
				GolVec3* p_unk0x0c,
				LegoFloat* p_unk0x10,
				LegoFloat* p_unk0x14
			);
		};

		undefined4 m_unk0x00; // 0x00
		undefined4 m_unk0x04; // 0x04
		undefined4 m_unk0x08; // 0x08
		undefined4 m_unk0x0c; // 0x0c
		union {
			LegoU32 m_unk0x10;             // 0x10
			undefined* m_data;             // 0x10
			GolWorldEntity* m_worldEntity; // 0x10
			Field0x10* m_target;           // 0x10
		};
		union {
			undefined4 m_unk0x14; // 0x14
			Event* m_previous;    // 0x14
		};
	};

	// SIZE 0x18
	class CallbackData {
	public:
		undefined4 m_unk0x00; // 0x00
		undefined4 m_unk0x04; // 0x04
		undefined4 m_unk0x08; // 0x08
		undefined4 m_unk0x0c; // 0x0c
		union {
			undefined4 m_unk0x10;             // 0x10
			GolWorldEntity* m_worldEntity0;   // 0x10
			Descriptor::Field0x10* m_target0; // 0x10
		};
		union {
			undefined4 m_unk0x14;                            // 0x14
			void* m_data;                                    // 0x14
			GolWorldEntity* m_worldEntity1;                  // 0x14
			Descriptor::Field0x10* m_target1;                // 0x14
			Descriptor::Field0x10::Field0x0e0* m_field0x0e0; // 0x14
		};
	};

	class Callback {
	public:
		virtual void VTable0x00(CallbackData* p_data) = 0; // vtable+0x00
	};

	// SIZE 0x2c
	class Event {
	public:
		Event();
		void FUN_004408b0(Callback* p_callback, const Descriptor* p_descriptor);
		void FUN_004408e0(LegoEventQueue*, CallbackData* p_data);

		Callback* m_callback;    // 0x00
		Descriptor m_descriptor; // 0x04
		undefined4 m_unk0x1c;    // 0x1c
		undefined4 m_unk0x20;    // 0x20
		undefined4 m_active;     // 0x24
		Event* m_next;           // 0x28
	};

	LegoEventQueue();
	virtual LegoS32 VTable0x00(Event* p_event); // vtable+0x00
	virtual ~LegoEventQueue();                  // vtable+0x04
	// SYNTHETIC: LEGORACERS 0x0042fa10
	// LegoEventQueue::`scalar deleting destructor'
	virtual void VTable0x08(LegoU32 p_count);     // vtable+0x08
	virtual void Destroy();                       // vtable+0x0c
	virtual void VTable0x10(LegoU32 p_elapsedMs); // vtable+0x10

	Event* FUN_0042fb50(Callback* p_callback, const Descriptor* p_descriptor);
	void FUN_0042fbc0();
	Event* FUN_0042fc70(Event* p_event);

protected:
	Event* m_events;             // 0x04
	Event* m_freeList;           // 0x08
	Event* m_activeList;         // 0x0c
	CallbackData m_callbackData; // 0x10
};

// VTABLE: LEGORACERS 0x004b0724
// SIZE 0x2c
class LegoEventQueue::Field0x2c : public LegoEventQueue {
public:
	Field0x2c();
	LegoS32 VTable0x00(Event* p_event) override; // vtable+0x00
	// SYNTHETIC: LEGORACERS 0x0042fca0
	// LegoEventQueue::Field0x2c::`scalar deleting destructor'
	void Destroy() override;                            // vtable+0x0c
	void VTable0x10(LegoU32 p_elapsedMs) override;      // vtable+0x10
	virtual GolWorldEntity* VTable0x14(Event* p_event); // vtable+0x14

protected:
	void FUN_0042fd10();
	void FUN_0042fe10();
	void FUN_0042ffc0();

	Event* m_unk0x28; // 0x28
};

// VTABLE: LEGORACERS 0x004b09e8
// SIZE 0x48
class LegoEventQueue::Field0x30 : public Field0x2c {
public:
	Field0x30();
	LegoS32 VTable0x00(Event* p_event) override;         // vtable+0x00
	void Destroy() override;                             // vtable+0x0c
	void VTable0x10(LegoU32 p_elapsedMs) override;       // vtable+0x10
	GolWorldEntity* VTable0x14(Event* p_event) override; // vtable+0x14

	// SIZE 0x24
	class CollisionCallbackData {
	public:
		undefined4 m_unk0x00;             // 0x00
		GolVec3 m_unk0x04;                // 0x04
		GolVec3 m_unk0x10;                // 0x10
		LegoFloat m_unk0x1c;              // 0x1c
		Descriptor::Field0x10* m_unk0x20; // 0x20
	};

protected:
	void FUN_0043aa90();
	void FUN_0043ab10(Event* p_event, LegoEventQueue* p_queue, CallbackData* p_data);
	void FUN_0043ab90();
	void FUN_0043aca0();

	Event* m_unk0x2c;       // 0x2c
	CallbackData m_unk0x30; // 0x30
};

#endif // LEGOEVENTQUEUE_H
