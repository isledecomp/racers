#ifndef ONYXCIRCULARBUFFER_0x1C
#define ONYXCIRCULARBUFFER_0x1C

#include "decomp.h"
#include "input/inputdevice.h"
#include "types.h"

// SIZE 0x1c
// VTABLE: LEGORACERS 0x004b0e84
class OnyxCircularBuffer0x1c : public InputDevice::Callback {
public:
	// SIZE 0x10
	struct Item {
		InputDevice* m_device;           // 0x00
		undefined4 m_keyCode;            // 0x04
		undefined4 m_unk0x08;            // 0x08
		LegoBool m_isPressed;            // 0x0c
		LegoBool m_isRepeat;             // 0x0d
		undefined m_unk0x0e[0x10 - 0xe]; // 0x0e
	};

	OnyxCircularBuffer0x1c();

	void OnKeyDown(InputDevice* p_device, undefined4 p_keyCode, undefined4 p_arg3) override;   // vtable+0x00
	void OnKeyUp(InputDevice* p_device, undefined4 p_keyCode, undefined4 p_arg3) override;     // vtable+0x04
	void OnKeyRepeat(InputDevice* p_device, undefined4 p_keyCode, undefined4 p_arg3) override; // vtable+0x08
	virtual ~OnyxCircularBuffer0x1c();                                                         // vtable+0x0c
	virtual LegoBool32 Allocate(LegoS32 p_capacity);                                           // vtable+0x10
	virtual LegoBool32 Reset();                                                                // vtable+0x14

	void Initialize();
	Item* Dequeue();
	Item* Enqueue(InputDevice* p_device, undefined4 p_keyCode, undefined4 p_arg3);
	void ClearQueue();
	LegoS32 GetSize() const { return m_size; }

	// SYNTHETIC: LEGORACERS 0x0044b710
	// OnyxCircularBuffer0x1c::`scalar deleting destructor'

private:
	LegoBool m_allocated;             // 0x04
	undefined m_unk0x05[0x08 - 0x05]; // 0x05
	Item* m_items;                    // 0x08
	LegoS32 m_readPos;                // 0x0c
	LegoS32 m_writePos;               // 0x10
	LegoS32 m_capacity;               // 0x14
	LegoS32 m_size;                   // 0x18
};

#endif // ONYXCIRCULARBUFFER_0x1C
