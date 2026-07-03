#include "race/raceforcefeedback.h"

#include "decomp.h"
#include "input/directinputdevice.h"

DECOMP_SIZE_ASSERT(RaceForceFeedback, 0x28)

static const LegoFloat g_engineEffectPeriodSeconds = 0.2f;
static const LegoFloat g_microsecondsPerSecond = 1000000.0f;

// FUNCTION: LEGORACERS 0x00421da0
RaceForceFeedback::RaceForceFeedback()
{
	m_device = NULL;
	m_totalMs = 0;
	m_phaseMs = 0;
	m_onMs = 0;
	m_offMs = 0;
	m_surfaceIntensity = 0;
	m_state = 0;
	m_surfaceMode = 0;
	m_engineEffectActive = 0;
	m_engineEffect = NULL;
}

// FUNCTION: LEGORACERS 0x00421dd0
RaceForceFeedback::~RaceForceFeedback()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00421de0
void RaceForceFeedback::Destroy()
{
	LPDIRECTINPUTEFFECT effect = m_engineEffect;
	m_device = NULL;

	if (effect) {
		effect->Stop();
		m_engineEffect = NULL;
	}
}

// FUNCTION: LEGORACERS 0x00421e00
void RaceForceFeedback::Initialize(DirectInputDevice* p_device)
{
	if (m_device) {
		Destroy();
	}

	m_device = p_device;
	if (p_device->CreateForceFeedbackEffect()) {
		m_device = NULL;
	}

	CreateEngineEffect();
}

// FUNCTION: LEGORACERS 0x00421e30
void RaceForceFeedback::Update(LegoU32 p_elapsedMs, LegoFloat p_forwardSpeed)
{
	UpdateEngineEffect(p_forwardSpeed);
	if (m_device && m_state) {
		if (m_surfaceMode) {
			UpdateSurfacePulse(p_forwardSpeed);
		}

		if (p_elapsedMs >= m_totalMs) {
			m_totalMs = 0;
			Stop();
			return;
		}

		m_totalMs -= p_elapsedMs;

		if (p_elapsedMs > m_phaseMs) {
			m_phaseMs = 0;
		}
		else {
			m_phaseMs -= p_elapsedMs;
		}

		if (!m_phaseMs) {
			if (m_state == 2 && m_onMs) {
				m_device->StartForceFeedbackEffect();
				m_state = 1;
				m_phaseMs = m_onMs;
			}
			else {
				m_device->StopForceFeedbackEffect();
				m_state = 2;
				m_phaseMs = m_offMs;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00421ef0
void RaceForceFeedback::Stop()
{
	if (m_device && m_state) {
		m_device->StopForceFeedbackEffect();

		LegoFloat value = m_surfaceIntensity;
		m_totalMs = 0;
		m_phaseMs = 0;
		m_onMs = 0;
		m_offMs = 0;
		m_state = 0;

		if (value != 0.0f) {
			StartSurfaceRumble();
		}
	}
}

// FUNCTION: LEGORACERS 0x00421f30
void RaceForceFeedback::StartPulses()
{
	m_state = 2;
	m_surfaceMode = 0;
}

// FUNCTION: LEGORACERS 0x00421f40
LegoS32 RaceForceFeedback::StartSurfaceRumble()
{
	LegoFloat value = m_surfaceIntensity * 20.0f;
	m_surfaceMode = 1;
	m_totalMs = 0xffffffff;
	LegoS32 result = static_cast<LegoS32>(value);
	m_onMs = result;
	m_offMs = 50;
	m_phaseMs = 0;
	m_state = 2;
	return result;
}

// FUNCTION: LEGORACERS 0x00421f80
LegoS32 RaceForceFeedback::UpdateSurfacePulse(LegoFloat p_forwardSpeed)
{
	if (p_forwardSpeed < 0.0f) {
		p_forwardSpeed = -p_forwardSpeed;
	}

	if (p_forwardSpeed > 0.2f) {
		p_forwardSpeed = 0.2f;
	}

	LegoFloat value = (p_forwardSpeed / 0.2f) * (p_forwardSpeed / 0.2f);
	if (value < 0.02f) {
		value = 0.0f;
	}

	value *= 20.0f;
	LegoS32 result = static_cast<LegoS32>(value * m_surfaceIntensity);
	m_onMs = result;
	return result;
}

// FUNCTION: LEGORACERS 0x00421fe0
void RaceForceFeedback::SetSurfaceIntensity(LegoFloat p_intensity)
{
	m_surfaceIntensity = p_intensity;

	if (p_intensity == 0.0f) {
		if (m_surfaceMode) {
			m_surfaceMode = 0;
			Stop();
			return;
		}
	}

	if (!m_state) {
		m_surfaceMode = 1;
		StartSurfaceRumble();
	}
}

// FUNCTION: LEGORACERS 0x00422030
void RaceForceFeedback::PlayTurboRumble(LegoU32 p_level)
{
	LegoU32 zero = 0;

	if (m_device) {
		switch (p_level) {
		case 0:
			m_totalMs = 1000;
			m_onMs = 500;
			m_offMs = zero;
			break;
		case 1:
			m_totalMs = 1500;
			m_onMs = 750;
			m_offMs = zero;
			break;
		case 2:
			m_totalMs = 5000;
			m_onMs = 500;
			m_offMs = 100;
			break;
		case 3:
			m_totalMs = 1000;
			m_offMs = zero;
			m_onMs = 1000;
			break;
		}

		StartPulses();
	}
}

// FUNCTION: LEGORACERS 0x004220c0
void RaceForceFeedback::PlayReactionRumble()
{
	if (m_device) {
		m_offMs = 0;
		m_totalMs = 500;
		m_onMs = 500;
		StartPulses();
	}
}

// FUNCTION: LEGORACERS 0x004220e0
void RaceForceFeedback::PlayLightRumble()
{
	if (m_device) {
		m_offMs = 0;
		m_totalMs = 150;
		m_onMs = 150;
		StartPulses();
	}
}

// FUNCTION: LEGORACERS 0x00422100
void RaceForceFeedback::PlayScrapeRumble()
{
	if (m_device && !m_state) {
		m_offMs = 0;
		m_totalMs = 100;
		m_onMs = 100;
		StartPulses();
	}
}

// FUNCTION: LEGORACERS 0x00422130
void RaceForceFeedback::StartEngineEffect()
{
	m_engineEffectActive = 1;

	LPDIRECTINPUTEFFECT effect = m_engineEffect;
	if (effect) {
		effect->Start(1, 0);
	}
}

// FUNCTION: LEGORACERS 0x00422150
void RaceForceFeedback::StopEngineEffect()
{
	m_engineEffectActive = 0;

	LPDIRECTINPUTEFFECT effect = m_engineEffect;
	if (effect) {
		effect->Stop();
	}
}

// FUNCTION: LEGORACERS 0x00422170
void RaceForceFeedback::Pause()
{
	if (m_device) {
		m_device->StopForceFeedbackEffect();

		LPDIRECTINPUTEFFECT effect = m_engineEffect;
		if (effect) {
			if (m_engineEffectActive) {
				effect->Stop();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004221a0
void RaceForceFeedback::Resume()
{
	if (m_device) {
		if (m_state == 1) {
			m_device->StartForceFeedbackEffect();
		}

		LPDIRECTINPUTEFFECT effect = m_engineEffect;
		if (effect) {
			if (m_engineEffectActive) {
				effect->Start(1, 0);
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004221d0
void RaceForceFeedback::CreateEngineEffect()
{
	DWORD axes[2];
	LONG direction[2];
	DIPERIODIC periodicParams;
	DIEFFECT effectParams;
	RaceForceFeedback* self = this;
	DirectInputDevice* device = self->m_device;
	LegoS32 zero = 0;

	if (device) {
		if (device->IsForceFeedbackAvailable()) {
			LegoFloat period = g_engineEffectPeriodSeconds;
			period *= g_microsecondsPerSecond;

			axes[0] = zero;
			axes[1] = DIJOFS_Y;

			direction[0] = zero;
			direction[1] = zero;

			periodicParams.dwMagnitude = 2000;
			periodicParams.lOffset = zero;
			periodicParams.dwPhase = zero;
			periodicParams.dwPeriod = static_cast<LegoS32>(period);

			effectParams.dwDuration = INFINITE;
			effectParams.dwTriggerButton = DIEB_NOTRIGGER;

			DWORD* axesPtr = axes;
			LONG* directionPtr = direction;
			DIPERIODIC* periodicParamsPtr = &periodicParams;

			effectParams.dwSize = sizeof(effectParams);
			effectParams.dwFlags = DIEFF_POLAR | DIEFF_OBJECTOFFSETS;
			effectParams.dwSamplePeriod = zero;
			effectParams.dwGain = 10000;
			effectParams.dwTriggerRepeatInterval = zero;
			effectParams.cAxes = sizeOfArray(axes);
			effectParams.rgdwAxes = axesPtr;
			effectParams.rglDirection = directionPtr;
			effectParams.lpEnvelope = NULL;
			effectParams.cbTypeSpecificParams = sizeof(periodicParams);
			effectParams.lpvTypeSpecificParams = periodicParamsPtr;

			HRESULT result = device->GetDevice()->CreateEffect(GUID_Sine, &effectParams, &self->m_engineEffect, NULL);
			if (FAILED(result)) {
				self->m_engineEffect = NULL;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004222b0
undefined4 RaceForceFeedback::UpdateEngineEffect(LegoFloat p_forwardSpeed)
{
	undefined4 result = (undefined4) m_device;
	if (!m_device) {
		return result;
	}

	LPDIRECTINPUTEFFECT effect = m_engineEffect;
	if (!effect) {
		return result;
	}

	if (!m_engineEffectActive) {
		return result;
	}

	if (p_forwardSpeed < 0.0f) {
		p_forwardSpeed = -p_forwardSpeed;
	}

	if (p_forwardSpeed > 0.2f) {
		p_forwardSpeed = 0.2f;
	}

	DIPERIODIC periodicParams;
	periodicParams.dwMagnitude = 2000;
	periodicParams.lOffset = 0;
	periodicParams.dwPhase = 0;
	periodicParams.dwPeriod = static_cast<LegoS32>((0.2f - p_forwardSpeed) * 1000000.0f);

	DIEFFECT effectParams;
	effectParams.dwSize = sizeof(effectParams);
	effectParams.cbTypeSpecificParams = sizeof(periodicParams);
	effectParams.lpvTypeSpecificParams = &periodicParams;
	result = effect->SetParameters(&effectParams, DIEP_TYPESPECIFICPARAMS);
	return result;
}
