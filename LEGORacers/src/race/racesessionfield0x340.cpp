#include "decomp.h"
#include "input/directinputdevice.h"
#include "race/raceforcefeedback.h"

DECOMP_SIZE_ASSERT(RaceForceFeedback, 0x28)

// FUNCTION: LEGORACERS 0x00421da0
RaceForceFeedback::RaceForceFeedback()
{
	m_device = NULL;
	m_unk0x04 = 0;
	m_unk0x08 = 0;
	m_unk0x0c = 0;
	m_unk0x10 = 0;
	m_unk0x14 = 0;
	m_unk0x18 = 0;
	m_unk0x1c = 0;
	m_unk0x20 = 0;
	m_effect = NULL;
}

// FUNCTION: LEGORACERS 0x00421dd0
RaceForceFeedback::~RaceForceFeedback()
{
	FUN_00421de0();
}

// FUNCTION: LEGORACERS 0x00421de0
void RaceForceFeedback::FUN_00421de0()
{
	LPDIRECTINPUTEFFECT effect = m_effect;
	m_device = NULL;

	if (effect) {
		effect->Stop();
		m_effect = NULL;
	}
}

// FUNCTION: LEGORACERS 0x00421e00
void RaceForceFeedback::FUN_00421e00(DirectInputDevice* p_device)
{
	if (m_device) {
		FUN_00421de0();
	}

	m_device = p_device;
	if (p_device->CreateForceFeedbackEffect()) {
		m_device = NULL;
	}

	FUN_004221d0();
}

// FUNCTION: LEGORACERS 0x00421e30
void RaceForceFeedback::FUN_00421e30(LegoU32 p_elapsedMs, LegoFloat p_unk0x08)
{
	FUN_004222b0(p_unk0x08);
	if (m_device && m_unk0x18) {
		if (m_unk0x1c) {
			FUN_00421f80(p_unk0x08);
		}

		if (p_elapsedMs >= m_unk0x04) {
			m_unk0x04 = 0;
			FUN_00421ef0();
			return;
		}

		m_unk0x04 -= p_elapsedMs;

		if (p_elapsedMs > m_unk0x08) {
			m_unk0x08 = 0;
		}
		else {
			m_unk0x08 -= p_elapsedMs;
		}

		if (!m_unk0x08) {
			if (m_unk0x18 == 2 && m_unk0x0c) {
				m_device->StartForceFeedbackEffect();
				m_unk0x18 = 1;
				m_unk0x08 = m_unk0x0c;
			}
			else {
				m_device->StopForceFeedbackEffect();
				m_unk0x18 = 2;
				m_unk0x08 = m_unk0x10;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00421ef0
void RaceForceFeedback::FUN_00421ef0()
{
	if (m_device && m_unk0x18) {
		m_device->StopForceFeedbackEffect();

		LegoFloat value = m_unk0x14;
		m_unk0x04 = 0;
		m_unk0x08 = 0;
		m_unk0x0c = 0;
		m_unk0x10 = 0;
		m_unk0x18 = 0;

		if (value != 0.0f) {
			FUN_00421f40();
		}
	}
}

// FUNCTION: LEGORACERS 0x00421f40
LegoS32 RaceForceFeedback::FUN_00421f40()
{
	LegoFloat value = m_unk0x14 * 20.0f;
	m_unk0x1c = 1;
	m_unk0x04 = 0xffffffff;
	LegoS32 result = static_cast<LegoS32>(value);
	m_unk0x0c = result;
	m_unk0x10 = 50;
	m_unk0x08 = 0;
	m_unk0x18 = 2;
	return result;
}

// FUNCTION: LEGORACERS 0x00421f80
LegoS32 RaceForceFeedback::FUN_00421f80(LegoFloat p_unk0x04)
{
	if (p_unk0x04 < 0.0f) {
		p_unk0x04 = -p_unk0x04;
	}

	if (p_unk0x04 > 0.2f) {
		p_unk0x04 = 0.2f;
	}

	LegoFloat value = (p_unk0x04 / 0.2f) * (p_unk0x04 / 0.2f);
	if (value < 0.02f) {
		value = 0.0f;
	}

	value *= 20.0f;
	LegoS32 result = static_cast<LegoS32>(value * m_unk0x14);
	m_unk0x0c = result;
	return result;
}

// STUB: LEGORACERS 0x00422100
void RaceForceFeedback::FUN_00422100()
{
	if (m_device && !m_unk0x18) {
		m_unk0x10 = 0;
		m_unk0x04 = 100;
		m_unk0x0c = 100;
		m_unk0x18 = 2;
		m_unk0x1c = 0;
	}
}

// FUNCTION: LEGORACERS 0x00422130
void RaceForceFeedback::FUN_00422130()
{
	m_unk0x20 = 1;

	LPDIRECTINPUTEFFECT effect = m_effect;
	if (effect) {
		effect->Start(1, 0);
	}
}

// FUNCTION: LEGORACERS 0x00422150
void RaceForceFeedback::FUN_00422150()
{
	m_unk0x20 = 0;

	LPDIRECTINPUTEFFECT effect = m_effect;
	if (effect) {
		effect->Stop();
	}
}

// FUNCTION: LEGORACERS 0x00422170
void RaceForceFeedback::FUN_00422170()
{
	if (m_device) {
		m_device->StopForceFeedbackEffect();

		LPDIRECTINPUTEFFECT effect = m_effect;
		if (effect) {
			if (m_unk0x20) {
				effect->Stop();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004221a0
void RaceForceFeedback::FUN_004221a0()
{
	if (m_device) {
		if (m_unk0x18 == 1) {
			m_device->StartForceFeedbackEffect();
		}

		LPDIRECTINPUTEFFECT effect = m_effect;
		if (effect) {
			if (m_unk0x20) {
				effect->Start(1, 0);
			}
		}
	}
}

// STUB: LEGORACERS 0x004221d0
void RaceForceFeedback::FUN_004221d0()
{
	RaceForceFeedback* self = this;
	DirectInputDevice* device = self->m_device;
	LegoS32 zero = 0;

	if (device) {
		if (device->IsForceFeedbackAvailable()) {
			LegoFloat period = 1000000.0f * 0.2f;

			DWORD axes[2];
			axes[0] = zero;
			axes[1] = DIJOFS_Y;

			LONG direction[2];
			direction[0] = zero;
			direction[1] = zero;

			DIPERIODIC periodicParams;
			periodicParams.dwMagnitude = 2000;
			periodicParams.lOffset = zero;
			periodicParams.dwPhase = zero;
			periodicParams.dwPeriod = static_cast<LegoS32>(period);

			DIEFFECT effectParams = {
				sizeof(effectParams),
				DIEFF_POLAR | DIEFF_OBJECTOFFSETS,
				INFINITE,
				static_cast<DWORD>(zero),
				10000,
				DIEB_NOTRIGGER,
				static_cast<DWORD>(zero),
				sizeOfArray(axes),
				axes,
				direction,
				NULL,
				sizeof(periodicParams),
				&periodicParams,
			};

			HRESULT result = device->GetDevice()->CreateEffect(GUID_Sine, &effectParams, &self->m_effect, NULL);
			if (FAILED(result)) {
				self->m_effect = NULL;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004222b0
undefined4 RaceForceFeedback::FUN_004222b0(LegoFloat p_unk0x04)
{
	undefined4 result = (undefined4) m_device;
	if (!m_device) {
		return result;
	}

	LPDIRECTINPUTEFFECT effect = m_effect;
	if (!effect) {
		return result;
	}

	if (!m_unk0x20) {
		return result;
	}

	if (p_unk0x04 < 0.0f) {
		p_unk0x04 = -p_unk0x04;
	}

	if (p_unk0x04 > 0.2f) {
		p_unk0x04 = 0.2f;
	}

	DIPERIODIC periodicParams;
	periodicParams.dwMagnitude = 2000;
	periodicParams.lOffset = 0;
	periodicParams.dwPhase = 0;
	periodicParams.dwPeriod = static_cast<LegoS32>((0.2f - p_unk0x04) * 1000000.0f);

	DIEFFECT effectParams;
	effectParams.dwSize = sizeof(effectParams);
	effectParams.cbTypeSpecificParams = sizeof(periodicParams);
	effectParams.lpvTypeSpecificParams = &periodicParams;
	result = effect->SetParameters(&effectParams, DIEP_TYPESPECIFICPARAMS);
	return result;
}
