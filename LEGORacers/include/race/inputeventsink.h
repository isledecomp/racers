#ifndef INPUTEVENTSINK_H
#define INPUTEVENTSINK_H

#include "input/inputdevice.h"
#include "types.h"

// SIZE 0x04
class InputEventSink : public InputDevice::Callback {
public:
	InputDevice::Callback::ResultValue OnKeyDown(
		InputDevice* p_source,
		undefined4 p_input,
		undefined4 p_time
	) override = 0;
	InputDevice::Callback::ResultValue OnKeyUp(InputDevice* p_source, undefined4 p_input, undefined4 p_time) override =
		0;
	InputDevice::Callback::ResultValue OnKeyRepeat(
		InputDevice* p_source,
		undefined4 p_input,
		undefined4 p_time
	) override;
};

#endif // INPUTEVENTSINK_H
