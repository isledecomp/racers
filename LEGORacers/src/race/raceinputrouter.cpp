#include "race/raceinputrouter.h"

#include "decomp.h"
#include "input/directinputdevice.h"

#include <string.h>

DECOMP_SIZE_ASSERT(RaceInputRouter, 0x1c)

// FUNCTION: LEGORACERS 0x00427900
RaceInputRouter::RaceInputRouter()
{
	m_device = NULL;
	for (LegoU32 i = 0; i < sizeOfArray(m_sinks); i++) {
		m_sinks[i] = NULL;
	}
	m_sinkCount = 0;
	m_fallback = NULL;
	m_enabled = TRUE;
}

// FUNCTION: LEGORACERS 0x00427950
RaceInputRouter::~RaceInputRouter()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00427960
void RaceInputRouter::Reset()
{
	m_device = NULL;
	for (LegoU32 i = 0; i < sizeOfArray(m_sinks); i++) {
		m_sinks[i] = NULL;
	}
	m_sinkCount = 0;
	m_fallback = NULL;
	m_enabled = TRUE;
}

// FUNCTION: LEGORACERS 0x00427980
void RaceInputRouter::Initialize(DirectInputDevice* p_source, InputDevice::Callback* p_fallback)
{
	m_device = p_source;
	m_fallback = p_fallback;
	m_enabled = TRUE;
}

// FUNCTION: LEGORACERS 0x004279a0
void RaceInputRouter::AddSink(PlayerControls::InputState* p_sink)
{
	m_sinks[m_sinkCount] = p_sink;
	m_sinkCount++;
}

// FUNCTION: LEGORACERS 0x004279c0
void RaceInputRouter::AcquireDevice()
{
	m_device->SetCallback(this);
	if (!m_device->IsAcquired()) {
		m_device->Acquire();
	}
}

// FUNCTION: LEGORACERS 0x004279f0
void RaceInputRouter::UnacquireDevice()
{
	m_device->Unacquire();
}

// FUNCTION: LEGORACERS 0x00427a00
InputDevice::Callback::ResultValue RaceInputRouter::OnKeyDown(
	InputDevice* p_source,
	undefined4 p_input,
	undefined4 p_time
)
{
	LegoU32 i;
	LegoBool32 matched = FALSE;

	if (m_enabled) {
		i = 0;
		if (i < m_sinkCount) {
			do {
				for (LegoU32 j = 0; j < PlayerControls::c_inputSlotCount; j++) {
					DirectInputDevice* source;
					if (m_sinks[i]->GetBinding(&source, j) != p_input || source != m_device) {
						continue;
					}

					matched = TRUE;
					break;
				}

				if (matched) {
					break;
				}

				i++;
			} while (i < m_sinkCount);
		}
	}

	if (!matched && m_fallback) {
		return m_fallback->OnKeyDown(p_source, p_input, p_time);
	}

	if (matched) {
		return m_sinks[i]->OnKeyDown(p_source, p_input, p_time);
	}

	InputDevice::Callback::Result result;
	result.m_result = FALSE;
	return result.m_value;
}

// FUNCTION: LEGORACERS 0x00427aa0
InputDevice::Callback::ResultValue RaceInputRouter::OnKeyUp(
	InputDevice* p_source,
	undefined4 p_input,
	undefined4 p_time
)
{
	LegoU32 i;
	LegoBool32 matched = FALSE;

	if (m_enabled) {
		i = 0;
		if (i < m_sinkCount) {
			do {
				for (LegoU32 j = 0; j < PlayerControls::c_inputSlotCount; j++) {
					DirectInputDevice* source;
					if (m_sinks[i]->GetBinding(&source, j) != p_input || source != m_device) {
						continue;
					}

					matched = TRUE;
					break;
				}

				if (matched) {
					break;
				}

				i++;
			} while (i < m_sinkCount);
		}
	}

	if (!matched && m_fallback) {
		return m_fallback->OnKeyUp(p_source, p_input, p_time);
	}

	if (matched) {
		return m_sinks[i]->OnKeyUp(p_source, p_input, p_time);
	}

	InputDevice::Callback::Result result;
	result.m_result = FALSE;
	return result.m_value;
}

// FUNCTION: LEGORACERS 0x00427b40
void RaceInputRouter::ReleaseAllInputs()
{
	LegoU32 i = 0;
	if (m_sinkCount > 0) {
		PlayerControls::InputState** current = m_sinks;

		do {
			(*current)->ReleaseAllInputs();
			i++;
			current++;
		} while (i < m_sinkCount);
	}
}
