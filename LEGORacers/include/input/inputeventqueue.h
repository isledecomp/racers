#ifndef INPUTEVENTQUEUE_H
#define INPUTEVENTQUEUE_H

#include "decomp.h"
#include "input/inputdevice.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004b0e84
// SIZE 0x1c
class InputEventQueue : public InputDevice::Callback {
public:
	// SIZE 0x10
	struct Event {
		InputDevice* m_device;           // 0x00
		LegoU32 m_keyCode;               // 0x04
		LegoU32 m_timeMs;                // 0x08
		LegoBool m_isPressed;            // 0x0c
		LegoBool m_isRepeat;             // 0x0d
		undefined m_unk0x0e[0x10 - 0xe]; // 0x0e
	};

	InputEventQueue();

	InputDevice::Callback::ResultValue OnKeyDown(
		InputDevice* p_device,
		undefined4 p_keyCode,
		undefined4 p_time
	) override; // vtable+0x00
	InputDevice::Callback::ResultValue OnKeyUp(
		InputDevice* p_device,
		undefined4 p_keyCode,
		undefined4 p_time
	) override; // vtable+0x04
	InputDevice::Callback::ResultValue OnKeyRepeat(
		InputDevice* p_device,
		undefined4 p_keyCode,
		undefined4 p_time
	) override;                                      // vtable+0x08
	virtual ~InputEventQueue();                      // vtable+0x0c
	virtual LegoBool32 Allocate(LegoS32 p_capacity); // vtable+0x10
	virtual LegoBool32 Reset();                      // vtable+0x14

	void Initialize();
	Event* Dequeue();
	Event* Enqueue(InputDevice* p_device, LegoU32 p_keyCode, LegoU32 p_time);
	void ClearQueue();
	LegoS32 GetSize() const { return m_size; }

	// SYNTHETIC: LEGORACERS 0x0044b710
	// InputEventQueue::`scalar deleting destructor'

private:
	LegoBool m_allocated;             // 0x04
	undefined m_unk0x05[0x08 - 0x05]; // 0x05
	Event* m_events;                  // 0x08
	LegoS32 m_readPos;                // 0x0c
	LegoS32 m_writePos;               // 0x10
	LegoS32 m_capacity;               // 0x14
	LegoS32 m_size;                   // 0x18
};

#endif // INPUTEVENTQUEUE_H
