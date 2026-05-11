#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include "compat.h"
#include "decomp.h"
#include "types.h"

#include <stddef.h> /// wchar_t

class InputManager;

// VTABLE: LEGORACERS 0x004b0e9c
// SIZE 0x9c
class InputDevice {
public:
	class Callback {
	public:
		virtual void OnKeyDown(InputDevice* p_device, undefined4 p_keyCode, undefined4 p_arg3) = 0; // vtable+0x00
		virtual void OnKeyUp(InputDevice* p_device, undefined4 p_keyCode, undefined4 p_arg3) = 0;   // vtable+0x04
		virtual void OnKeyRepeat(InputDevice* p_device, undefined4 p_keyCode,
								 undefined4 p_arg3) = 0; // vtable+0x08
	};

	// VTABLE: LEGORACERS 0x004b0f18
	// SIZE 0x24
	class DirectionalTrigger {
	public:
		enum {
			c_directionCount = 4,
			c_virtualDirectionSource = 0x50,
			c_directionChangeDelayMs = 50
		};

		DirectionalTrigger();
		virtual LegoBool32 OnKeyDown(InputDevice* p_device, undefined4 p_keyCode, undefined4 p_time);   // vtable+0x00
		virtual LegoBool32 OnKeyUp(InputDevice* p_device, undefined4 p_keyCode, undefined4 p_time);     // vtable+0x04
		virtual LegoBool32 OnKeyRepeat(InputDevice* p_device, undefined4 p_keyCode, undefined4 p_time); // vtable+0x08
		virtual ~DirectionalTrigger();                                                                  // vtable+0x0c

		LegoBool32 Configure(
			LegoU32 p_sourceId,
			LegoU32 p_directionEvent1,
			LegoU32 p_directionEvent2,
			LegoU32 p_directionEvent3,
			LegoU32 p_directionEvent4
		);
		LegoBool32 Destroy();
		LegoBool32 DispatchDelayedStateChange(LegoU32 p_time, InputDevice* p_device);
		LegoBool32 DispatchRepeatEvent(LegoU32 p_time, InputDevice* p_device);

		// SYNTHETIC: LEGORACERS 0x0044c120
		// InputDevice::DirectionalTrigger::`scalar deleting destructor'

	private:
		void Reset();
		LegoS32 WrapDirectionIndex(LegoS32 p_index);
		LegoS32 GetPressedDirection(InputDevice* p_device);
		LegoS32 GetDirectionForEvent(InputDevice* p_device, LegoU32 p_event);
		LegoU32 MakeDirectionEvent(LegoS32 p_direction) const
		{
			return ((m_sourceId | c_virtualDirectionSource) << 24) | p_direction;
		}

		LegoBool32 m_active;          // 0x04
		LegoU32 m_directionEvents[4]; // 0x08
		LegoS32 m_currentDirection;   // 0x18
		LegoU32 m_sourceId;           // 0x1c
		LegoU32 m_nextDispatchTimeMs; // 0x20
	};

	enum {
		c_sourceKeyboard = 0x10000000,
		c_sourceMouse = 0x20000000,
		c_sourceJoystick1 = 0x30000000,
		c_sourceJoystick2 = 0x40000000,
		c_sourceMask = 0xf0000000,
		c_keyCodeMask = 0x0000ffff,
		c_pressed = 0x80,
	};

	InputDevice();
	virtual void Initialize();                                                            // vtable+0x00
	virtual void SetButtonState(undefined4 p_event, LegoU8 p_state, LegoBool32 p_notify); // vtable+0x04
	virtual void SetAxisValue(undefined4, LegoFloat) = 0;                                 // vtable+0x08
	virtual ~InputDevice();                                                               // vtable+0x0c
	virtual LegoBool32 Destroy();                                                         // vtable+0x10
	virtual undefined4 Poll(LegoS32 p_elapsedMs);                                         // vtable+0x14
	virtual undefined4 IsAcquired();                                                      // vtable+0x18
	virtual LegoS32 GetButtonCount();                                                     // vtable+0x1c
	virtual LegoS32 GetAxisCount();                                                       // vtable+0x20
	virtual const wchar_t* GetControlName(undefined4);                                    // vtable+0x24
	virtual void SetDeadZonePercent(LegoU32) = 0;                                         // vtable+0x28
	virtual LegoFloat GetAxisValueByIndex(undefined4) = 0;                                // vtable+0x2c
	virtual LegoFloat GetAxisValue(undefined4) = 0;                                       // vtable+0x30
	virtual undefined4 GetButtonState(undefined4) = 0;                                    // vtable+0x34
	virtual undefined4 SetBackgroundMode() = 0;                                           // vtable+0x38
	virtual undefined4 SetForegroundMode() = 0;                                           // vtable+0x3c
	virtual undefined4 SetExclusiveMode() = 0;                                            // vtable+0x40
	virtual undefined4 SetNonExclusiveMode() = 0;                                         // vtable+0x44
	virtual undefined4 IsBackgroundMode() = 0;                                            // vtable+0x48
	virtual undefined4 IsExclusiveMode() = 0;                                             // vtable+0x4c
	virtual undefined4 Acquire();                                                         // vtable+0x50
	virtual undefined4 Unacquire();                                                       // vtable+0x54
	virtual LegoBool32 CreateForceFeedbackEffect() = 0;                                   // vtable+0x58
	virtual LegoS32 StartForceFeedbackEffect() = 0;                                       // vtable+0x5c
	virtual LegoBool32 StopForceFeedbackEffect() = 0;                                     // vtable+0x60

	void ReleasePressedButtons();
	void SetRepeatDelays(LegoS32 p_repeatDelayMs, LegoS32 p_initialRepeatDelayMs);
	void SetDeviceName(const LegoChar* p_deviceName);
	void SetEventMappings(undefined2* p_buttonMapping, undefined2* p_axisMapping);
	undefined2* GetCustomButtonMapping();
	undefined2* GetCustomAxisMapping();
	void DispatchAxisButtonStateChanges(LegoFloat p_newValue, LegoFloat p_oldValue, LegoU32 p_positiveEvent);
	void DispatchRepeatEvents(LegoS32 p_elapsedMs);
	void ResetAxisValues();
	LegoS32 AddDirectionalTrigger(DirectionalTrigger* p_trigger);
	LegoBool32 RemoveDirectionalTrigger(DirectionalTrigger* p_trigger);
	LegoS16 StoreString(const LegoChar*);

	static LegoU32 GetKeySource(LegoU32 p_event) { return p_event & c_sourceMask; }

	static LegoU32 MakeEvent(LegoU32 p_source, LegoU32 p_value) { return p_source | p_value; }

	LegoBool32 IsCreated() const { return m_created; }
	void SetForceFeedbackAvailable(undefined4 p_forceFeedbackAvailable)
	{
		m_forceFeedbackAvailable = p_forceFeedbackAvailable;
	}
	void SetCallback(Callback* p_callback) { m_callback = p_callback; }
	void SetRepeatEnabled(LegoBool32 p_enabled) { m_repeatEnabled = p_enabled; }

	// SYNTHETIC: LEGORACERS 0x0044b920
	// InputDevice::`scalar deleting destructor'

	friend class DirectionalTrigger;

protected:
	DirectionalTrigger* m_directionalTriggers[4]; // 0x04
	InputManager* m_inputManager;                 // 0x14
	LegoBool32 m_created;                         // 0x18
	LegoBool32 m_acquired;                        // 0x1c
	LegoBool32 m_repeatEnabled;                   // 0x20
	LegoBool32 m_axisButtonEventsEnabled;         // 0x24
	undefined4 m_forceFeedbackAvailable;          // 0x28
	undefined2* m_buttonMapping;                  // 0x2c
	undefined2* m_axisMapping;                    // 0x30
	LegoS32 m_currentTimeMs;                      // 0x34
	LegoU32 m_axisMask;                           // 0x38
	LegoS32 m_initialRepeatDelayMs;               // 0x3c
	LegoS32 m_repeatDelayMs;                      // 0x40
	LegoS32 m_repeatTimerMs;                      // 0x44
	LegoS32 m_buttonCount;                        // 0x48
	LegoS32 m_axisCount;                          // 0x4c
	LegoS32 m_directionalTriggerCount;            // 0x50
	undefined4 m_deviceSubType;                   // 0x54
	undefined4 m_deviceType;                      // 0x58
	undefined4 m_stringBufferLength;              // 0x5c
	LegoChar m_deviceName[32];                    // 0x60
	undefined m_unk0x80[0x90 - 0x80];             // 0x80
	undefined4 m_deviceId;                        // 0x90
	wchar_t* m_stringBuffer;                      // 0x94
	Callback* m_callback;                         // 0x98
};

#endif // INPUTDEVICE_H
