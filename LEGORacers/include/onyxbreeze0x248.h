#ifndef ONYXBREEZE0X248_H
#define ONYXBREEZE0X248_H

#include "decomp.h"
#include "input/inputdevice.h"
#include "onyxcircularbuffer0x1c.h"

class InputManager;
class MouseInputDevice;

// SIZE 0x248
class OnyxBreeze0x248 {
public:
	OnyxBreeze0x248();
	~OnyxBreeze0x248();

	void Initialize(InputManager* p_inputManager);
	void Shutdown();

	OnyxCircularBuffer0x1c* GetUnk0x208() { return &m_unk0x208; }

private:
	LegoBool32 HasKeyboard() const;
	void FUN_0041fac0();

	InputManager* m_inputManager;               // 0x000
	undefined2 m_unk0x004[256];                 // 0x004
	MouseInputDevice* m_mouse;                  // 0x204
	OnyxCircularBuffer0x1c m_unk0x208;          // 0x208
	InputDevice::DirectionalTrigger m_unk0x224; // 0x224
};

#endif // ONYXBREEZE0X248_H
