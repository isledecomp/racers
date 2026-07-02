#ifndef RACEINPUTROUTER_H
#define RACEINPUTROUTER_H

#include "race/inputeventsink.h"
#include "race/playercontrols.h"

class RaceSession;

// SIZE 0x1c
// VTABLE: LEGORACERS 0x004b0300
class RaceInputRouter : public InputEventSink {
public:
	RaceInputRouter();
	InputDevice::Callback::ResultValue OnKeyDown(InputDevice* p_source, undefined4 p_input, undefined4 p_time) override;
	InputDevice::Callback::ResultValue OnKeyUp(InputDevice* p_source, undefined4 p_input, undefined4 p_time) override;
	virtual ~RaceInputRouter();

	// SYNTHETIC: LEGORACERS 0x00427930
	// RaceInputRouter::`scalar deleting destructor'

	void Initialize(DirectInputDevice* p_source, InputDevice::Callback* p_fallback);
	void AddSink(PlayerControls::InputState* p_sink);
	void AcquireDevice();
	void UnacquireDevice();
	void ReleaseAllInputs();

private:
	friend class RaceSession;

	void Reset();

	DirectInputDevice* m_device;            // 0x04
	PlayerControls::InputState* m_sinks[2]; // 0x08
	LegoU32 m_sinkCount;                    // 0x10
	InputDevice::Callback* m_fallback;      // 0x14
	LegoBool32 m_enabled;                   // 0x18
};

#endif // RACEINPUTROUTER_H
