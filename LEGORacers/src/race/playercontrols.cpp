#include "decomp.h"
#include "input/directinputdevice.h"
#include "race/racesession.h"

#include <string.h>

DECOMP_SIZE_ASSERT(PlayerControls, 0x74)
DECOMP_SIZE_ASSERT(PlayerControls::InputState, 0x70)

extern const LegoChar* g_sideWinderForceFeedName;
extern LegoFloat g_minSoundPan;

// GLOBAL: LEGORACERS 0x004b0740
extern const LegoFloat g_idleTurnRate = 2.5f;

// GLOBAL: LEGORACERS 0x004b0744
extern const LegoFloat g_inputTurnRate = 1.25f;

// GLOBAL: LEGORACERS 0x004b0748
extern const LegoFloat g_steeringReturnRate = 8.25f;

// GLOBAL: LEGORACERS 0x004b074c
extern const LegoFloat g_driftTurnRate = 5.0f;

// GLOBAL: LEGORACERS 0x004b0750
extern const LegoFloat g_slideTurnRate = 16.0f;

// GLOBAL: LEGORACERS 0x004b0754
extern const LegoFloat g_steeringLimit = 1.0f;

// FUNCTION: LEGORACERS 0x00430020
PlayerControls::PlayerControls()
{
	m_racer = NULL;
	m_input.m_inputFlags = 0;
	m_input.m_steering = 0;
	m_input.m_stateFlags = 0;
	m_input.m_boostWindowMs = 0;
	m_input.m_throttleHoldMs = 0;
	m_input.m_analogThrottle = 0;
}

// FUNCTION: LEGORACERS 0x00430050
PlayerControls::~PlayerControls()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004300a0
void PlayerControls::Destroy()
{
	m_input.Destroy();

	m_racer = NULL;
	m_input.m_inputFlags = 0;
	m_input.m_steering = 0;
	m_input.m_stateFlags = 0;
	m_input.m_boostWindowMs = 0;
	m_input.m_throttleHoldMs = 0;
	m_input.m_analogThrottle = 0;
}

// FUNCTION: LEGORACERS 0x004300d0
void PlayerControls::Initialize(Racer* p_racer, InputDevice::Callback* p_fallback)
{
	m_racer = p_racer;
	m_input.Initialize(this, p_fallback);
	Reset();
}

// FUNCTION: LEGORACERS 0x00430100
void PlayerControls::Reset()
{
	m_input.m_boostWindowMs = 0;
	m_input.m_throttleHoldMs = 0;
	m_input.m_stateFlags = (m_input.m_stateFlags & ~2) | 1;
}

// STUB: LEGORACERS 0x00430120
void PlayerControls::UpdateSteering(LegoU32 p_elapsedMs)
{
	LegoFloat elapsedSeconds = static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs)) * 0.001f;
	LegoU32 inputFlags = m_input.m_inputFlags;
	LegoU32 hasSteerInput = (inputFlags & c_inputFlagSteerMask) ? TRUE : FALSE;
	LegoFloat limitNegative;
	LegoFloat limitPositive;
	LegoFloat turnRate;
	LegoFloat delta;

	limitPositive = g_steeringLimit;
	limitNegative = -g_steeringLimit;

	if (m_racer->m_flags & Racer::c_flagDrifting) {
		if (m_racer->m_driveController.m_slideLeft == 1) {
			turnRate = g_slideTurnRate;
		}
		else {
			turnRate = g_driftTurnRate;
		}
	}
	else if (hasSteerInput) {
		turnRate = g_inputTurnRate;
	}
	else {
		turnRate = g_idleTurnRate;
	}

	if (hasSteerInput) {
		if ((inputFlags & c_inputFlagSteerPositive) && !(inputFlags & c_inputFlagSteerNegative)) {
			if (m_input.m_steering < 0.0f) {
				delta = g_steeringReturnRate;
			}
			else {
				delta = turnRate;
			}
		}
		else if (!(inputFlags & c_inputFlagSteerPositive) && (inputFlags & c_inputFlagSteerNegative)) {
			if (m_input.m_steering > 0.0f) {
				delta = -g_steeringReturnRate;
			}
			else {
				delta = -turnRate;
			}
		}
		else if (m_input.m_steering > 0.0f) {
			delta = -g_steeringReturnRate;
			limitNegative = 0.0f;
		}
		else if (m_input.m_steering < 0.0f) {
			delta = g_steeringReturnRate;
			limitPositive = 0.0f;
		}
		else {
			delta = 0.0f;
			limitNegative = 0.0f;
		}
	}
	else {
		DirectInputDevice* source;
		m_input.GetBinding(&source, 0);

		LegoFloat analogValue = -source->GetAxisValue(1);
		if (analogValue > 1.0f) {
			analogValue = 1.0f;
		}
		else if (analogValue < g_minSoundPan) {
			analogValue = g_minSoundPan;
		}

		if (analogValue > 0.0f) {
			limitPositive = analogValue;
			if (m_input.m_steering < 0.0f) {
				delta = g_steeringReturnRate;
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
			if (m_input.m_steering > 0.0f) {
				delta = -g_steeringReturnRate;
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
		if (m_input.m_steering > 0.0f) {
			delta = -g_steeringReturnRate;
			limitNegative = 0.0f;
		}
		else if (m_input.m_steering < 0.0f) {
			delta = g_steeringReturnRate;
			limitPositive = 0.0f;
		}
		else {
			limitNegative = 0.0f;
			limitPositive = 0.0f;
		}
	}

	m_input.m_steering += delta * elapsedSeconds;

	if (m_input.m_steering > limitPositive) {
		m_input.m_steering = limitPositive;
	}
	else if (m_input.m_steering < limitNegative) {
		m_input.m_steering = limitNegative;
	}

	if (!(m_input.m_stateFlags & c_stateControlMask)) {
		m_racer->m_driveController.SetSteeringInput(m_input.m_steering);
	}
}

// FUNCTION: LEGORACERS 0x00430390
void PlayerControls::UpdateThrottle()
{
	LegoFloat driveValue;
	LegoFloat throttleValue = 0.0f;
	LegoFloat reverseValue = 0.0f;
	DirectInputDevice* source;

	m_input.GetBinding(&source, 2);
	if (m_input.m_analogThrottle) {
		LegoFloat analogValue = -source->GetAxisValue(2);
		if (analogValue < 0.0f) {
			reverseValue = analogValue;
		}
		else {
			throttleValue = analogValue;
		}
	}

	if (m_input.m_inputFlags & c_inputFlagThrottle) {
		throttleValue = 1.0f;
	}

	if (m_input.m_inputFlags & c_inputFlagBrake) {
		reverseValue = -1.0f;
	}

	driveValue = throttleValue + reverseValue;
	if (driveValue > 0.0f) {
		TrackThrottleHold();
	}
	else if (driveValue < 0.0f) {
		m_input.m_throttleHoldMs = 0;
	}

	if (throttleValue > 0.0f) {
		m_input.m_stateFlags |= c_stateFlagThrottle;
	}
	else {
		m_input.m_stateFlags &= ~c_stateFlagThrottle;
	}

	if (throttleValue > 0.0f && (m_input.m_inputFlags & c_inputFlagDrift)) {
		if (!(m_input.m_stateFlags & c_stateControlMask)) {
			driveValue = 1.0f;

			if (m_input.m_steering == 0.0f) {
				m_racer->EndDrift();
			}
			else if (!(m_racer->m_flags & Racer::c_flagDrifting)) {
				if (reverseValue < 0.0f) {
					m_racer->StartDrift(TRUE);
				}
				else {
					m_racer->StartDrift(FALSE);
				}
			}
		}
	}
	else if (m_racer->m_flags & Racer::c_flagDrifting) {
		m_racer->EndDrift();
	}

	if (!(m_racer->m_flags & Racer::c_flagDrifting) && reverseValue < 0.0f && throttleValue > 0.0f) {
		driveValue = 0.5f;
	}

	if (!(m_input.m_stateFlags & c_stateControlMask)) {
		m_racer->m_driveController.SetThrottleInput(driveValue);
	}
}

// FUNCTION: LEGORACERS 0x00430530
void PlayerControls::Update(LegoU32 p_elapsedMs)
{
	LegoU32 duration = m_input.m_boostWindowMs;
	if (duration < p_elapsedMs) {
		m_input.m_boostWindowMs = 0;
	}
	else {
		m_input.m_boostWindowMs = duration - p_elapsedMs;
	}

	m_input.m_throttleHoldMs += p_elapsedMs;
	UpdateSteering(p_elapsedMs);
	UpdateThrottle();
}

// FUNCTION: LEGORACERS 0x00430570
void PlayerControls::OnSteerLeft(LegoBool32 p_enabled)
{
	if (p_enabled) {
		m_input.m_inputFlags |= 1;
	}
	else {
		m_input.m_inputFlags &= ~1;
	}
}

// FUNCTION: LEGORACERS 0x00430590
void PlayerControls::OnSteerRight(LegoBool32 p_enabled)
{
	if (p_enabled) {
		m_input.m_inputFlags |= 2;
	}
	else {
		m_input.m_inputFlags &= ~2;
	}
}

// FUNCTION: LEGORACERS 0x004305b0
void PlayerControls::OnThrottle(LegoBool32 p_enabled)
{
	if (p_enabled) {
		m_input.m_inputFlags |= 4;
		TrackThrottleHold();
	}
	else {
		m_input.m_inputFlags &= ~4;
		m_input.m_throttleHoldMs = 0;
	}
}

// FUNCTION: LEGORACERS 0x004305e0
void PlayerControls::OnBrake(LegoBool32 p_enabled)
{
	if (p_enabled) {
		Racer* racer = m_racer;
		if (racer->m_physics.m_flags & 2) {
			racer->m_physics.FinishSpin();
		}

		m_input.m_inputFlags |= 8;
	}
	else {
		m_input.m_inputFlags &= ~8;
	}
}

// FUNCTION: LEGORACERS 0x00430620
void PlayerControls::OnUsePowerup(LegoBool32 p_enabled)
{
	if (!(m_input.m_stateFlags & 3)) {
		if (p_enabled) {
			m_input.m_inputFlags |= 0x10;
			m_racer->AiUsePowerup();
		}
		else {
			m_input.m_inputFlags &= ~0x10;
		}
	}
}

// FUNCTION: LEGORACERS 0x00430650
void PlayerControls::OnCycleCamera(LegoBool32 p_enabled)
{
	if (p_enabled) {
		m_racer->CycleCameraView();
		m_input.m_inputFlags |= 0x20;
	}
	else {
		m_input.m_inputFlags &= ~0x20;
	}
}

// FUNCTION: LEGORACERS 0x00430680
void PlayerControls::OnCycleHud(LegoBool32 p_enabled)
{
	if (p_enabled) {
		m_racer->CycleHudGadget();
		m_input.m_inputFlags |= 0x40;
	}
	else {
		m_input.m_inputFlags &= ~0x40;
	}
}

// FUNCTION: LEGORACERS 0x004306b0
void PlayerControls::OnDrift(LegoBool32 p_enabled)
{
	if (p_enabled) {
		m_input.m_inputFlags |= 0x80;
	}
	else {
		m_input.m_inputFlags &= ~0x80;
	}
}

// FUNCTION: LEGORACERS 0x004306d0
void PlayerControls::OnLookBack(LegoBool32 p_enabled)
{
	if (p_enabled) {
		m_racer->StartLookBack();
		m_input.m_inputFlags |= 0x100;
	}
	else {
		m_racer->EndLookBack();
		m_input.m_inputFlags &= ~0x100;
	}
}

// FUNCTION: LEGORACERS 0x00430710
void PlayerControls::TryStartBoost()
{
	LegoU32 flags = m_input.m_stateFlags;
	flags &= ~1;
	m_input.m_stateFlags = flags;

	if (m_input.m_boostWindowMs > 0) {
		LegoU32 duration = m_input.m_boostWindowMs;
		Racer* racer = m_racer;
		if (duration >= 60) {
			racer->m_powerupManager->UseGreenPowerup(racer, TRUE);
		}
		else {
			racer->m_powerupManager->UseGreenPowerup(racer, FALSE);
		}
		m_input.m_boostWindowMs = 0;
	}
	else if (!(flags & 8)) {
		m_input.m_boostWindowMs = 100;
	}
}

// FUNCTION: LEGORACERS 0x00430760
void PlayerControls::EnterAiControl()
{
	m_input.m_stateFlags |= 2;
	m_racer->SwitchToAiControl();

	Racer* racer = m_racer;
	if (racer->m_flags & 0x80) {
		racer->EndDrift();
	}
}

// FUNCTION: LEGORACERS 0x00430790
void PlayerControls::TrackThrottleHold()
{
	LegoU32 flags = m_input.m_stateFlags;
	if (flags & 1) {
		if (m_input.m_throttleHoldMs > 2000) {
			m_input.m_boostWindowMs = 100;
			m_input.m_throttleHoldMs = 0;
		}
	}
	else {
		LegoU32 duration = m_input.m_boostWindowMs;
		if (!(0 < duration) || (flags & 3)) {
			return;
		}

		if (duration >= 60) {
			m_racer->m_powerupManager->UseGreenPowerup(m_racer, TRUE);
		}
		else {
			m_racer->m_powerupManager->UseGreenPowerup(m_racer, FALSE);
		}

		m_racer->m_visuals.StartCarSmoke();
		m_input.m_boostWindowMs = 0;
	}
}

// FUNCTION: LEGORACERS 0x004307f0
LegoS32 PlayerControls::DetectAnalogDevice()
{
	LegoS32 result = ::strcmp(m_input.m_devices[4]->GetDeviceName(), g_sideWinderForceFeedName);
	if (!result) {
		m_input.m_analogThrottle = TRUE;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00430840
PlayerControls::InputState::InputState()
{
	m_controls = NULL;
	m_fallback = NULL;

	for (LegoS32 i = 0; i < c_inputSlotCount; i++) {
		m_inputs[i] = 0;
		m_devices[i] = NULL;
	}

	m_enabled = 1;
}

// FUNCTION: LEGORACERS 0x00430890
PlayerControls::InputState::~InputState()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004308a0
void PlayerControls::InputState::Destroy()
{
	UnacquireDevices();

	for (LegoS32 i = 0; i < c_inputSlotCount; i++) {
		m_inputs[i] = 0;
		m_devices[i] = NULL;
	}

	m_controls = NULL;
	m_fallback = NULL;
	m_enabled = 1;
}

// FUNCTION: LEGORACERS 0x004308d0
PlayerControls* PlayerControls::InputState::Initialize(PlayerControls* p_parent, InputDevice::Callback* p_fallback)
{
	m_controls = p_parent;
	m_fallback = p_fallback;
	m_enabled = TRUE;

	return p_parent;
}

// FUNCTION: LEGORACERS 0x004308f0
LegoU32 PlayerControls::InputState::SetBinding(DirectInputDevice* p_source, undefined4 p_input, LegoU32 p_index)
{
	m_devices[p_index] = p_source;
	m_inputs[p_index] = p_input;

	return p_index;
}

// FUNCTION: LEGORACERS 0x00430910
undefined4 PlayerControls::InputState::GetBinding(DirectInputDevice** p_source, LegoU32 p_index)
{
	*p_source = m_devices[p_index];
	return m_inputs[p_index];
}

// FUNCTION: LEGORACERS 0x00430930
void PlayerControls::InputState::AcquireDevices()
{
	undefined4* input = m_inputs;
	DirectInputDevice** current = m_devices;
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
void PlayerControls::InputState::UnacquireDevices()
{
	DirectInputDevice** current = m_devices;
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
InputDevice::Callback::ResultValue PlayerControls::InputState::OnKeyDown(
	InputDevice* p_source,
	undefined4 p_input,
	undefined4 p_time
)
{
	if (m_enabled) {
		for (LegoU32 i = 0; i < c_inputSlotCount; i++) {
			if (p_input == m_inputs[i] && p_source == m_devices[i]) {
				switch (i) {
				case 0:
					m_controls->OnSteerLeft(TRUE);
					return TRUE;
				case 1:
					m_controls->OnSteerRight(TRUE);
					return TRUE;
				case 2:
					m_controls->OnThrottle(TRUE);
					return TRUE;
				case 3:
					m_controls->OnBrake(TRUE);
					return TRUE;
				case 4:
					m_controls->OnUsePowerup(TRUE);
					return TRUE;
				case 5:
					m_controls->OnCycleCamera(TRUE);
					return TRUE;
				case 6:
					m_controls->OnCycleHud(TRUE);
					return TRUE;
				case 7:
					m_controls->OnDrift(TRUE);
					return TRUE;
				case 8:
					m_controls->OnLookBack(TRUE);
					return TRUE;
				}
			}
		}
	}

	if (m_fallback) {
		return m_fallback->OnKeyDown(p_source, p_input, p_time);
	}

	InputDevice::Callback::Result result;
	result.m_result = FALSE;
	return result.m_value;
}

// FUNCTION: LEGORACERS 0x00430af0
InputDevice::Callback::ResultValue PlayerControls::InputState::OnKeyUp(
	InputDevice* p_source,
	undefined4 p_input,
	undefined4 p_time
)
{
	if (m_enabled) {
		for (LegoU32 i = 0; i < c_inputSlotCount; i++) {
			if (p_input == m_inputs[i] && p_source == m_devices[i]) {
				switch (i) {
				case 0:
					m_controls->OnSteerLeft(FALSE);
					return TRUE;
				case 1:
					m_controls->OnSteerRight(FALSE);
					return TRUE;
				case 2:
					m_controls->OnThrottle(FALSE);
					return TRUE;
				case 3:
					m_controls->OnBrake(FALSE);
					return TRUE;
				case 4:
					m_controls->OnUsePowerup(FALSE);
					return TRUE;
				case 5:
					m_controls->OnCycleCamera(FALSE);
					return TRUE;
				case 6:
					m_controls->OnCycleHud(FALSE);
					return TRUE;
				case 7:
					m_controls->OnDrift(FALSE);
					return TRUE;
				case 8:
					m_controls->OnLookBack(FALSE);
					return TRUE;
				}
			}
		}
	}

	if (m_fallback) {
		return m_fallback->OnKeyUp(p_source, p_input, p_time);
	}

	InputDevice::Callback::Result result;
	result.m_result = FALSE;
	return result.m_value;
}

// FUNCTION: LEGORACERS 0x00430c20
void PlayerControls::InputState::ReleaseAllInputs()
{
	m_controls->OnSteerLeft(FALSE);
	m_controls->OnSteerRight(FALSE);
	m_controls->OnThrottle(FALSE);
	m_controls->OnBrake(FALSE);
	m_controls->OnUsePowerup(FALSE);
	m_controls->OnCycleCamera(FALSE);
	m_controls->OnCycleHud(FALSE);
	m_controls->OnDrift(FALSE);
	m_controls->OnLookBack(FALSE);
}

// FUNCTION: LEGORACERS 0x00430c80
InputDevice::Callback::ResultValue InputEventSink::OnKeyRepeat(
	InputDevice* p_source,
	undefined4 p_input,
	undefined4 p_time
)
{
	return OnKeyDown(p_source, p_input, p_time);
}
