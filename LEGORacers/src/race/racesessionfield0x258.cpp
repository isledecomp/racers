#include "decomp.h"
#include "input/directinputdevice.h"
#include "race/racesession.h"

#include <string.h>

DECOMP_SIZE_ASSERT(RaceSession::Field0x258, 0x74)
DECOMP_SIZE_ASSERT(RaceSession::Field0x258::Field0x04, 0x70)

extern const LegoChar* g_sideWinderForceFeedName;
extern LegoFloat g_minSoundPan;

// GLOBAL: LEGORACERS 0x004b0740
extern const LegoFloat g_unk0x004b0740 = 2.5f;

// GLOBAL: LEGORACERS 0x004b0744
extern const LegoFloat g_unk0x004b0744 = 1.25f;

// GLOBAL: LEGORACERS 0x004b0748
extern const LegoFloat g_unk0x004b0748 = 8.25f;

// GLOBAL: LEGORACERS 0x004b074c
extern const LegoFloat g_unk0x004b074c = 5.0f;

// GLOBAL: LEGORACERS 0x004b0750
extern const LegoFloat g_unk0x004b0750 = 16.0f;

// GLOBAL: LEGORACERS 0x004b0754
extern const LegoFloat g_unk0x004b0754 = 1.0f;

// FUNCTION: LEGORACERS 0x00430020
RaceSession::Field0x258::Field0x258()
{
	m_unk0x000 = NULL;
	m_unk0x004.m_unk0x058 = 0;
	m_unk0x004.m_unk0x068 = 0;
	m_unk0x004.m_unk0x05c = 0;
	m_unk0x004.m_unk0x060 = 0;
	m_unk0x004.m_unk0x064 = 0;
	m_unk0x004.m_unk0x06c = 0;
}

// FUNCTION: LEGORACERS 0x00430050
RaceSession::Field0x258::~Field0x258()
{
	FUN_004300a0();
}

// FUNCTION: LEGORACERS 0x004300a0
void RaceSession::Field0x258::FUN_004300a0()
{
	m_unk0x004.FUN_004308a0();

	m_unk0x000 = NULL;
	m_unk0x004.m_unk0x058 = 0;
	m_unk0x004.m_unk0x068 = 0;
	m_unk0x004.m_unk0x05c = 0;
	m_unk0x004.m_unk0x060 = 0;
	m_unk0x004.m_unk0x064 = 0;
	m_unk0x004.m_unk0x06c = 0;
}

// FUNCTION: LEGORACERS 0x004300d0
void RaceSession::Field0x258::FUN_004300d0(RaceState::Racer* p_racer, InputDevice::Callback* p_fallback)
{
	m_unk0x000 = p_racer;
	m_unk0x004.FUN_004308d0(this, p_fallback);
	FUN_00430100();
}

// FUNCTION: LEGORACERS 0x00430100
void RaceSession::Field0x258::FUN_00430100()
{
	m_unk0x004.m_unk0x060 = 0;
	m_unk0x004.m_unk0x064 = 0;
	m_unk0x004.m_unk0x05c = (m_unk0x004.m_unk0x05c & ~2) | 1;
}

// STUB: LEGORACERS 0x00430120
void RaceSession::Field0x258::FUN_00430120(LegoU32 p_elapsedMs)
{
	LegoFloat elapsedSeconds = static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs)) * 0.001f;
	LegoU32 inputFlags = m_unk0x004.m_unk0x058;
	LegoU32 hasSteerInput = (inputFlags & c_inputFlagSteerMask) ? TRUE : FALSE;
	LegoFloat limitNegative;
	LegoFloat limitPositive;
	LegoFloat turnRate;
	LegoFloat delta;

	limitPositive = g_unk0x004b0754;
	limitNegative = -g_unk0x004b0754;

	if (m_unk0x000->m_unk0xd04 & c_racerFlags0xd04Bit7) {
		if (m_unk0x000->m_unk0xc70.m_unk0x030 == 1) {
			turnRate = g_unk0x004b0750;
		}
		else {
			turnRate = g_unk0x004b074c;
		}
	}
	else if (hasSteerInput) {
		turnRate = g_unk0x004b0744;
	}
	else {
		turnRate = g_unk0x004b0740;
	}

	if (hasSteerInput) {
		if ((inputFlags & c_inputFlagSteerPositive) && !(inputFlags & c_inputFlagSteerNegative)) {
			if (m_unk0x004.m_unk0x068 < 0.0f) {
				delta = g_unk0x004b0748;
			}
			else {
				delta = turnRate;
			}
		}
		else if (!(inputFlags & c_inputFlagSteerPositive) && (inputFlags & c_inputFlagSteerNegative)) {
			if (m_unk0x004.m_unk0x068 > 0.0f) {
				delta = -g_unk0x004b0748;
			}
			else {
				delta = -turnRate;
			}
		}
		else if (m_unk0x004.m_unk0x068 > 0.0f) {
			delta = -g_unk0x004b0748;
			limitNegative = 0.0f;
		}
		else if (m_unk0x004.m_unk0x068 < 0.0f) {
			delta = g_unk0x004b0748;
			limitPositive = 0.0f;
		}
		else {
			delta = 0.0f;
			limitNegative = 0.0f;
		}
	}
	else {
		DirectInputDevice* source;
		m_unk0x004.FUN_00430910(&source, 0);

		LegoFloat analogValue = -source->GetAxisValue(1);
		if (analogValue > 1.0f) {
			analogValue = 1.0f;
		}
		else if (analogValue < g_minSoundPan) {
			analogValue = g_minSoundPan;
		}

		if (analogValue > 0.0f) {
			limitPositive = analogValue;
			if (m_unk0x004.m_unk0x068 < 0.0f) {
				delta = g_unk0x004b0748;
			}
			else {
				delta = 1.0f - analogValue;
				delta *= 0.5f;
				delta += 0.5f;
				delta *= turnRate;
			}
		}
		else if (analogValue < 0.0f) {
			limitNegative = analogValue;
			if (m_unk0x004.m_unk0x068 > 0.0f) {
				delta = -g_unk0x004b0748;
			}
			else {
				delta = analogValue + 1.0f;
				delta *= 0.5f;
				delta += 0.5f;
				delta *= -turnRate;
			}
		}
		else {
			delta = 0.0f;
		}
	}

	if (delta == 0.0f) {
		if (m_unk0x004.m_unk0x068 > 0.0f) {
			delta = -g_unk0x004b0748;
			limitNegative = 0.0f;
		}
		else if (m_unk0x004.m_unk0x068 < 0.0f) {
			delta = g_unk0x004b0748;
			limitPositive = 0.0f;
		}
		else {
			limitNegative = 0.0f;
			limitPositive = 0.0f;
		}
	}

	m_unk0x004.m_unk0x068 += delta * elapsedSeconds;

	if (m_unk0x004.m_unk0x068 > limitPositive) {
		m_unk0x004.m_unk0x068 = limitPositive;
	}
	else if (m_unk0x004.m_unk0x068 < limitNegative) {
		m_unk0x004.m_unk0x068 = limitNegative;
	}

	if (!(m_unk0x004.m_unk0x05c & c_stateControlMask)) {
		m_unk0x000->m_unk0xc70.FUN_0041fe60(m_unk0x004.m_unk0x068);
	}
}

// FUNCTION: LEGORACERS 0x00430390
void RaceSession::Field0x258::FUN_00430390()
{
	LegoFloat driveValue;
	LegoFloat throttleValue = 0.0f;
	LegoFloat reverseValue = 0.0f;
	DirectInputDevice* source;

	m_unk0x004.FUN_00430910(&source, 2);
	if (m_unk0x004.m_unk0x06c) {
		LegoFloat analogValue = -source->GetAxisValue(2);
		if (analogValue < 0.0f) {
			reverseValue = analogValue;
		}
		else {
			throttleValue = analogValue;
		}
	}

	if (m_unk0x004.m_unk0x058 & c_inputFlagThrottle) {
		throttleValue = 1.0f;
	}

	if (m_unk0x004.m_unk0x058 & c_inputFlagBrake) {
		reverseValue = -1.0f;
	}

	driveValue = throttleValue + reverseValue;
	if (driveValue > 0.0f) {
		FUN_00430790();
	}
	else if (driveValue < 0.0f) {
		m_unk0x004.m_unk0x064 = 0;
	}

	if (throttleValue > 0.0f) {
		m_unk0x004.m_unk0x05c |= c_stateFlagThrottle;
	}
	else {
		m_unk0x004.m_unk0x05c &= ~c_stateFlagThrottle;
	}

	if (throttleValue > 0.0f && (m_unk0x004.m_unk0x058 & c_inputFlagDrift)) {
		if (!(m_unk0x004.m_unk0x05c & c_stateControlMask)) {
			driveValue = 1.0f;

			if (m_unk0x004.m_unk0x068 == 0.0f) {
				m_unk0x000->FUN_00439870();
			}
			else if (!(m_unk0x000->m_unk0xd04 & c_racerFlags0xd04Bit7)) {
				if (reverseValue < 0.0f) {
					m_unk0x000->FUN_004397c0(TRUE);
				}
				else {
					m_unk0x000->FUN_004397c0(FALSE);
				}
			}
		}
	}
	else if (m_unk0x000->m_unk0xd04 & c_racerFlags0xd04Bit7) {
		m_unk0x000->FUN_00439870();
	}

	if (!(m_unk0x000->m_unk0xd04 & c_racerFlags0xd04Bit7) && reverseValue < 0.0f && throttleValue > 0.0f) {
		driveValue = 0.5f;
	}

	if (!(m_unk0x004.m_unk0x05c & c_stateControlMask)) {
		m_unk0x000->m_unk0xc70.FUN_00420130(driveValue);
	}
}

// FUNCTION: LEGORACERS 0x00430530
void RaceSession::Field0x258::FUN_00430530(LegoU32 p_elapsedMs)
{
	LegoU32 duration = m_unk0x004.m_unk0x060;
	if (duration < p_elapsedMs) {
		m_unk0x004.m_unk0x060 = 0;
	}
	else {
		m_unk0x004.m_unk0x060 = duration - p_elapsedMs;
	}

	m_unk0x004.m_unk0x064 += p_elapsedMs;
	FUN_00430120(p_elapsedMs);
	FUN_00430390();
}

// FUNCTION: LEGORACERS 0x00430570
void RaceSession::Field0x258::FUN_00430570(LegoBool32 p_enabled)
{
	if (p_enabled) {
		m_unk0x004.m_unk0x058 |= 1;
	}
	else {
		m_unk0x004.m_unk0x058 &= ~1;
	}
}

// FUNCTION: LEGORACERS 0x00430590
void RaceSession::Field0x258::FUN_00430590(LegoBool32 p_enabled)
{
	if (p_enabled) {
		m_unk0x004.m_unk0x058 |= 2;
	}
	else {
		m_unk0x004.m_unk0x058 &= ~2;
	}
}

// FUNCTION: LEGORACERS 0x004305b0
void RaceSession::Field0x258::FUN_004305b0(LegoBool32 p_enabled)
{
	if (p_enabled) {
		m_unk0x004.m_unk0x058 |= 4;
		FUN_00430790();
	}
	else {
		m_unk0x004.m_unk0x058 &= ~4;
		m_unk0x004.m_unk0x064 = 0;
	}
}

// FUNCTION: LEGORACERS 0x004305e0
void RaceSession::Field0x258::FUN_004305e0(LegoBool32 p_enabled)
{
	if (p_enabled) {
		RaceState::Racer* racer = m_unk0x000;
		if (racer->m_unk0x3e8.m_flags0x6c0 & 2) {
			racer->m_unk0x3e8.VTable0x28();
		}

		m_unk0x004.m_unk0x058 |= 8;
	}
	else {
		m_unk0x004.m_unk0x058 &= ~8;
	}
}

// FUNCTION: LEGORACERS 0x00430620
void RaceSession::Field0x258::FUN_00430620(LegoBool32 p_enabled)
{
	if (!(m_unk0x004.m_unk0x05c & 3)) {
		if (p_enabled) {
			m_unk0x004.m_unk0x058 |= 0x10;
			m_unk0x000->FUN_00439100();
		}
		else {
			m_unk0x004.m_unk0x058 &= ~0x10;
		}
	}
}

// FUNCTION: LEGORACERS 0x00430650
void RaceSession::Field0x258::FUN_00430650(LegoBool32 p_enabled)
{
	if (p_enabled) {
		m_unk0x000->FUN_0043a390();
		m_unk0x004.m_unk0x058 |= 0x20;
	}
	else {
		m_unk0x004.m_unk0x058 &= ~0x20;
	}
}

// FUNCTION: LEGORACERS 0x00430680
void RaceSession::Field0x258::FUN_00430680(LegoBool32 p_enabled)
{
	if (p_enabled) {
		m_unk0x000->FUN_0043a0c0();
		m_unk0x004.m_unk0x058 |= 0x40;
	}
	else {
		m_unk0x004.m_unk0x058 &= ~0x40;
	}
}

// FUNCTION: LEGORACERS 0x004306b0
void RaceSession::Field0x258::FUN_004306b0(LegoBool32 p_enabled)
{
	if (p_enabled) {
		m_unk0x004.m_unk0x058 |= 0x80;
	}
	else {
		m_unk0x004.m_unk0x058 &= ~0x80;
	}
}

// FUNCTION: LEGORACERS 0x004306d0
void RaceSession::Field0x258::FUN_004306d0(LegoBool32 p_enabled)
{
	if (p_enabled) {
		m_unk0x000->FUN_0043a3f0();
		m_unk0x004.m_unk0x058 |= 0x100;
	}
	else {
		m_unk0x000->FUN_0043a400();
		m_unk0x004.m_unk0x058 &= ~0x100;
	}
}

// FUNCTION: LEGORACERS 0x00430710
void RaceSession::Field0x258::FUN_00430710()
{
	LegoU32 flags = m_unk0x004.m_unk0x05c;
	flags &= ~1;
	m_unk0x004.m_unk0x05c = flags;

	if (m_unk0x004.m_unk0x060 > 0) {
		LegoU32 duration = m_unk0x004.m_unk0x060;
		RaceState::Racer* racer = m_unk0x000;
		if (duration >= 60) {
			racer->m_unk0x008->FUN_0045b1e0(racer, TRUE);
		}
		else {
			racer->m_unk0x008->FUN_0045b1e0(racer, FALSE);
		}
		m_unk0x004.m_unk0x060 = 0;
	}
	else if (!(flags & 8)) {
		m_unk0x004.m_unk0x060 = 100;
	}
}

// FUNCTION: LEGORACERS 0x00430760
void RaceSession::Field0x258::FUN_00430760()
{
	m_unk0x004.m_unk0x05c |= 2;
	m_unk0x000->FUN_0043a0e0();

	RaceState::Racer* racer = m_unk0x000;
	if (racer->m_unk0xd04 & 0x80) {
		racer->FUN_00439870();
	}
}

// STUB: LEGORACERS 0x00430790
void RaceSession::Field0x258::FUN_00430790()
{
	if (m_unk0x004.m_unk0x05c & 1) {
		if (m_unk0x004.m_unk0x064 > 2000) {
			m_unk0x004.m_unk0x060 = 100;
			m_unk0x004.m_unk0x064 = 0;
		}
	}
	else {
		LegoU32 duration = m_unk0x004.m_unk0x060;
		LegoU32 flags = m_unk0x004.m_unk0x05c;
		if (!(0 < duration) || (flags & 3)) {
			return;
		}

		RaceState::Racer* racer = m_unk0x000;
		if (duration >= 60) {
			racer->m_unk0x008->FUN_0045b1e0(racer, TRUE);
		}
		else {
			racer->m_unk0x008->FUN_0045b1e0(racer, FALSE);
		}

		m_unk0x000->m_unk0x018.FUN_0043df90();
		m_unk0x004.m_unk0x060 = 0;
	}
}

// FUNCTION: LEGORACERS 0x004307f0
LegoS32 RaceSession::Field0x258::FUN_004307f0()
{
	LegoS32 result = ::strcmp(m_unk0x004.m_unk0x02c[4]->GetDeviceName(), g_sideWinderForceFeedName);
	if (!result) {
		m_unk0x004.m_unk0x06c = TRUE;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00430840
RaceSession::Field0x258::Field0x04::Field0x04()
{
	m_unk0x004 = NULL;
	m_unk0x050 = NULL;

	for (LegoS32 i = 0; i < c_inputSlotCount; i++) {
		m_unk0x008[i] = 0;
		m_unk0x02c[i] = NULL;
	}

	m_unk0x054 = 1;
}

// FUNCTION: LEGORACERS 0x00430890
RaceSession::Field0x258::Field0x04::~Field0x04()
{
	FUN_004308a0();
}

// FUNCTION: LEGORACERS 0x004308a0
void RaceSession::Field0x258::Field0x04::FUN_004308a0()
{
	FUN_00430980();

	for (LegoS32 i = 0; i < c_inputSlotCount; i++) {
		m_unk0x008[i] = 0;
		m_unk0x02c[i] = NULL;
	}

	m_unk0x004 = NULL;
	m_unk0x050 = NULL;
	m_unk0x054 = 1;
}

// FUNCTION: LEGORACERS 0x004308d0
RaceSession::Field0x258* RaceSession::Field0x258::Field0x04::FUN_004308d0(
	Field0x258* p_parent,
	InputDevice::Callback* p_fallback
)
{
	m_unk0x004 = p_parent;
	m_unk0x050 = p_fallback;
	m_unk0x054 = TRUE;

	return p_parent;
}

// FUNCTION: LEGORACERS 0x004308f0
LegoU32 RaceSession::Field0x258::Field0x04::FUN_004308f0(
	DirectInputDevice* p_source,
	undefined4 p_input,
	LegoU32 p_index
)
{
	m_unk0x02c[p_index] = p_source;
	m_unk0x008[p_index] = p_input;

	return p_index;
}

// FUNCTION: LEGORACERS 0x00430910
undefined4 RaceSession::Field0x258::Field0x04::FUN_00430910(DirectInputDevice** p_source, LegoU32 p_index)
{
	*p_source = m_unk0x02c[p_index];
	return m_unk0x008[p_index];
}

// FUNCTION: LEGORACERS 0x00430930
void RaceSession::Field0x258::Field0x04::FUN_00430930()
{
	undefined4* input = m_unk0x008;
	DirectInputDevice** current = m_unk0x02c;
	LegoS32 remaining = c_inputSlotCount;

	do {
		DirectInputDevice* source = *current;
		if (source && (*input & InputDevice::c_sourceCharacter) != InputDevice::c_sourceKeyboard) {
			source->SetCallback(this);
			if (!(*current)->IsAcquired()) {
				(*current)->Acquire();
			}
		}

		input++;
		current++;
	} while (--remaining);
}

// FUNCTION: LEGORACERS 0x00430980
void RaceSession::Field0x258::Field0x04::FUN_00430980()
{
	DirectInputDevice** current = m_unk0x02c;
	LegoS32 remaining = c_inputSlotCount;
	do {
		DirectInputDevice* source = *current;
		if (source && source->GetCallback() == this) {
			source->SetCallback(NULL);
			(*current)->Unacquire();
		}
		current++;
	} while (--remaining);
}

// FUNCTION: LEGORACERS 0x004309c0
InputDevice::Callback::ResultValue RaceSession::Field0x258::Field0x04::OnKeyDown(
	InputDevice* p_source,
	undefined4 p_input,
	undefined4 p_time
)
{
	if (m_unk0x054) {
		for (LegoU32 i = 0; i < c_inputSlotCount; i++) {
			if (p_input == m_unk0x008[i] && p_source == m_unk0x02c[i]) {
				switch (i) {
				case 0:
					m_unk0x004->FUN_00430570(TRUE);
					return TRUE;
				case 1:
					m_unk0x004->FUN_00430590(TRUE);
					return TRUE;
				case 2:
					m_unk0x004->FUN_004305b0(TRUE);
					return TRUE;
				case 3:
					m_unk0x004->FUN_004305e0(TRUE);
					return TRUE;
				case 4:
					m_unk0x004->FUN_00430620(TRUE);
					return TRUE;
				case 5:
					m_unk0x004->FUN_00430650(TRUE);
					return TRUE;
				case 6:
					m_unk0x004->FUN_00430680(TRUE);
					return TRUE;
				case 7:
					m_unk0x004->FUN_004306b0(TRUE);
					return TRUE;
				case 8:
					m_unk0x004->FUN_004306d0(TRUE);
					return TRUE;
				}
			}
		}
	}

	if (m_unk0x050) {
		return m_unk0x050->OnKeyDown(p_source, p_input, p_time);
	}

	InputDevice::Callback::Result result;
	result.m_result = FALSE;
	return result.m_value;
}

// FUNCTION: LEGORACERS 0x00430af0
InputDevice::Callback::ResultValue RaceSession::Field0x258::Field0x04::OnKeyUp(
	InputDevice* p_source,
	undefined4 p_input,
	undefined4 p_time
)
{
	if (m_unk0x054) {
		for (LegoU32 i = 0; i < c_inputSlotCount; i++) {
			if (p_input == m_unk0x008[i] && p_source == m_unk0x02c[i]) {
				switch (i) {
				case 0:
					m_unk0x004->FUN_00430570(FALSE);
					return TRUE;
				case 1:
					m_unk0x004->FUN_00430590(FALSE);
					return TRUE;
				case 2:
					m_unk0x004->FUN_004305b0(FALSE);
					return TRUE;
				case 3:
					m_unk0x004->FUN_004305e0(FALSE);
					return TRUE;
				case 4:
					m_unk0x004->FUN_00430620(FALSE);
					return TRUE;
				case 5:
					m_unk0x004->FUN_00430650(FALSE);
					return TRUE;
				case 6:
					m_unk0x004->FUN_00430680(FALSE);
					return TRUE;
				case 7:
					m_unk0x004->FUN_004306b0(FALSE);
					return TRUE;
				case 8:
					m_unk0x004->FUN_004306d0(FALSE);
					return TRUE;
				}
			}
		}
	}

	if (m_unk0x050) {
		return m_unk0x050->OnKeyUp(p_source, p_input, p_time);
	}

	InputDevice::Callback::Result result;
	result.m_result = FALSE;
	return result.m_value;
}

// FUNCTION: LEGORACERS 0x00430c20
void RaceSession::Field0x258::Field0x04::FUN_00430c20()
{
	m_unk0x004->FUN_00430570(FALSE);
	m_unk0x004->FUN_00430590(FALSE);
	m_unk0x004->FUN_004305b0(FALSE);
	m_unk0x004->FUN_004305e0(FALSE);
	m_unk0x004->FUN_00430620(FALSE);
	m_unk0x004->FUN_00430650(FALSE);
	m_unk0x004->FUN_00430680(FALSE);
	m_unk0x004->FUN_004306b0(FALSE);
	m_unk0x004->FUN_004306d0(FALSE);
}

// FUNCTION: LEGORACERS 0x00430c80
InputDevice::Callback::ResultValue RaceSession::InputEventSink::OnKeyRepeat(
	InputDevice* p_source,
	undefined4 p_input,
	undefined4 p_time
)
{
	return OnKeyDown(p_source, p_input, p_time);
}
