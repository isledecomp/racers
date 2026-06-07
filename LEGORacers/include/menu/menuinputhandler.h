#ifndef MENUINPUTHANDLER_H
#define MENUINPUTHANDLER_H

#include "decomp.h"
#include "input/inputdevice.h"
#include "input/inputeventqueue.h"

class InputManager;
class MouseInputDevice;

// SIZE 0x248
class MenuInputHandler {
public:
	MenuInputHandler();
	~MenuInputHandler();

	void Initialize(InputManager* p_inputManager);
	void Shutdown();

	InputEventQueue* GetUnk0x208() { return &m_unk0x208; }
	InputManager* GetInputManager() const { return m_inputManager; }
	LegoBool32 HasInputManager() const { return m_inputManager != NULL; }
	LegoBool32 HasKeyboard() const;

private:
	void FUN_0041fac0();

	InputManager* m_inputManager;               // 0x000
	undefined2 m_unk0x004[256];                 // 0x004
	MouseInputDevice* m_mouse;                  // 0x204
	InputEventQueue m_unk0x208;                 // 0x208
	InputDevice::DirectionalTrigger m_unk0x224; // 0x224
};

#endif // MENUINPUTHANDLER_H
