#include "decomp.h"
#include "input/directinputdevice.h"
#include "race/racesession.h"

#include <string.h>

DECOMP_SIZE_ASSERT(RaceSession::Field0x23c, 0x1c)

// STUB: LEGORACERS 0x00427900
RaceSession::Field0x23c::Field0x23c()
{
	DirectInputDevice* source = NULL;
	Field0x258::Field0x04* sink = NULL;

	m_unk0x04 = source;
	m_unk0x08[0] = sink;
	m_unk0x08[1] = sink;
	m_unk0x10 = 0;
	m_unk0x14 = NULL;
	m_unk0x18 = TRUE;
}

// FUNCTION: LEGORACERS 0x00427950
RaceSession::Field0x23c::~Field0x23c()
{
	FUN_00427960();
}

// STUB: LEGORACERS 0x00427960
void RaceSession::Field0x23c::FUN_00427960()
{
	m_unk0x04 = NULL;
	memset(m_unk0x08, 0, sizeof(m_unk0x08));
	m_unk0x10 = 0;
	m_unk0x14 = NULL;
	m_unk0x18 = TRUE;
}

// FUNCTION: LEGORACERS 0x00427980
void RaceSession::Field0x23c::FUN_00427980(DirectInputDevice* p_source, InputDevice::Callback* p_fallback)
{
	m_unk0x04 = p_source;
	m_unk0x14 = p_fallback;
	m_unk0x18 = TRUE;
}

// FUNCTION: LEGORACERS 0x004279a0
void RaceSession::Field0x23c::FUN_004279a0(Field0x258::Field0x04* p_sink)
{
	m_unk0x08[m_unk0x10] = p_sink;
	m_unk0x10++;
}

// FUNCTION: LEGORACERS 0x004279c0
void RaceSession::Field0x23c::FUN_004279c0()
{
	m_unk0x04->SetCallback(this);
	if (!m_unk0x04->IsAcquired()) {
		m_unk0x04->Acquire();
	}
}

// FUNCTION: LEGORACERS 0x004279f0
void RaceSession::Field0x23c::FUN_004279f0()
{
	m_unk0x04->Unacquire();
}

// FUNCTION: LEGORACERS 0x00427a00
InputDevice::Callback::ResultValue RaceSession::Field0x23c::OnKeyDown(
	InputDevice* p_source,
	undefined4 p_input,
	undefined4 p_time
)
{
	LegoU32 i;
	LegoBool32 matched = FALSE;

	if (m_unk0x18) {
		i = 0;
		if (i < m_unk0x10) {
			do {
				for (LegoU32 j = 0; j < Field0x258::c_inputSlotCount; j++) {
					DirectInputDevice* source;
					if (m_unk0x08[i]->FUN_00430910(&source, j) != p_input || source != m_unk0x04) {
						continue;
					}

					matched = TRUE;
					break;
				}

				if (matched) {
					break;
				}

				i++;
			} while (i < m_unk0x10);
		}
	}

	if (!matched && m_unk0x14) {
		return m_unk0x14->OnKeyDown(p_source, p_input, p_time);
	}

	if (matched) {
		return m_unk0x08[i]->OnKeyDown(p_source, p_input, p_time);
	}

	InputDevice::Callback::Result result;
	result.m_result = FALSE;
	return result.m_value;
}

// FUNCTION: LEGORACERS 0x00427aa0
InputDevice::Callback::ResultValue RaceSession::Field0x23c::OnKeyUp(
	InputDevice* p_source,
	undefined4 p_input,
	undefined4 p_time
)
{
	LegoU32 i;
	LegoBool32 matched = FALSE;

	if (m_unk0x18) {
		i = 0;
		if (i < m_unk0x10) {
			do {
				for (LegoU32 j = 0; j < Field0x258::c_inputSlotCount; j++) {
					DirectInputDevice* source;
					if (m_unk0x08[i]->FUN_00430910(&source, j) != p_input || source != m_unk0x04) {
						continue;
					}

					matched = TRUE;
					break;
				}

				if (matched) {
					break;
				}

				i++;
			} while (i < m_unk0x10);
		}
	}

	if (!matched && m_unk0x14) {
		return m_unk0x14->OnKeyUp(p_source, p_input, p_time);
	}

	if (matched) {
		return m_unk0x08[i]->OnKeyUp(p_source, p_input, p_time);
	}

	InputDevice::Callback::Result result;
	result.m_result = FALSE;
	return result.m_value;
}

// FUNCTION: LEGORACERS 0x00427b40
void RaceSession::Field0x23c::FUN_00427b40()
{
	LegoU32 i = 0;
	if (m_unk0x10 > 0) {
		Field0x258::Field0x04** current = m_unk0x08;

		do {
			(*current)->FUN_00430c20();
			i++;
			current++;
		} while (i < m_unk0x10);
	}
}
