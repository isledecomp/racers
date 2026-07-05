#ifndef PLAYERCONTROLS_H
#define PLAYERCONTROLS_H

#include "golmath.h"
#include "inputeventsink.h"
#include "types.h"

class DirectInputDevice;
class GolFileParser;
class InputDevice;
class Racer;
class RaceSession;

// SIZE 0x74
class PlayerControls {
public:
	enum {
		c_inputSlotCount = 9,
		c_inputFlagSteerPositive = 1 << 0,
		c_inputFlagSteerNegative = 1 << 1,
		c_inputFlagThrottle = 1 << 2,
		c_inputFlagBrake = 1 << 3,
		c_inputFlagDrift = 1 << 7,
		c_inputFlagSteerMask = c_inputFlagSteerPositive | c_inputFlagSteerNegative,
		c_statePreStart = 1 << 0,
		c_stateAiControl = 1 << 1,
		c_stateFlagThrottle = 1 << 3,
		c_stateControlMask = c_statePreStart | c_stateAiControl,
	};

	// SIZE 0x70
	// VTABLE: LEGORACERS 0x004b075c
	class InputState : public InputEventSink {
	public:
		InputState();
		InputDevice::Callback::ResultValue OnKeyDown(
			InputDevice* p_source,
			undefined4 p_input,
			undefined4 p_time
		) override;
		InputDevice::Callback::ResultValue OnKeyUp(
			InputDevice* p_source,
			undefined4 p_input,
			undefined4 p_time
		) override;
		virtual ~InputState();

		// SYNTHETIC: LEGORACERS 0x00430870
		// PlayerControls::InputState::`scalar deleting destructor'

		void ReleaseAllInputs();

	private:
		friend class RaceSession;
		friend class PlayerControls;
		friend class RaceInputRouter;

		void Destroy();
		PlayerControls* Initialize(PlayerControls* p_parent, InputDevice::Callback* p_fallback);
		LegoU32 SetBinding(DirectInputDevice* p_source, undefined4 p_input, LegoU32 p_index);
		undefined4 GetBinding(DirectInputDevice** p_source, LegoU32 p_index);
		void AcquireDevices();
		void UnacquireDevices();

		PlayerControls* m_controls;                     // 0x004
		undefined4 m_inputs[c_inputSlotCount];          // 0x008
		DirectInputDevice* m_devices[c_inputSlotCount]; // 0x02c
		InputDevice::Callback* m_fallback;              // 0x050
		LegoBool32 m_enabled;                           // 0x054
		LegoU32 m_inputFlags;                           // 0x058
		LegoU32 m_stateFlags;                           // 0x05c
		LegoU32 m_boostWindowMs;                        // 0x060
		LegoU32 m_throttleHoldMs;                       // 0x064
		LegoFloat m_steering;                           // 0x068
		LegoBool32 m_analogThrottle;                    // 0x06c
	};

	PlayerControls();
	~PlayerControls();

private:
	friend class RaceSession;
	friend class InputState;

	void Destroy();
	void Initialize(Racer* p_racer, InputDevice::Callback* p_fallback);
	void Reset();
	void UpdateSteering(LegoU32 p_elapsedMs);
	void UpdateThrottle();
	void Update(LegoU32 p_elapsedMs);
	void OnSteerLeft(LegoBool32 p_enabled);
	void OnSteerRight(LegoBool32 p_enabled);
	void OnThrottle(LegoBool32 p_enabled);
	void OnBrake(LegoBool32 p_enabled);
	void OnUsePowerup(LegoBool32 p_enabled);
	void OnCycleCamera(LegoBool32 p_enabled);
	void OnCycleHud(LegoBool32 p_enabled);
	void OnDrift(LegoBool32 p_enabled);
	void OnLookBack(LegoBool32 p_enabled);
	void TryStartBoost();
	void EnterAiControl();
	void TrackThrottleHold();
	LegoS32 DetectAnalogDevice();

	Racer* m_racer;     // 0x000
	InputState m_input; // 0x004
};

#endif // PLAYERCONTROLS_H
