#include "race/events/colortransformresource.h"

#include "decomp.h"
#include "race/racesession.h"

DECOMP_SIZE_ASSERT(ColorTransformResource, 0x48)
DECOMP_SIZE_ASSERT(ColorTransformResource::InitParams, 0x3c)

// FUNCTION: LEGORACERS 0x004654c0
ColorTransformResource::ColorTransformResource()
{
	FUN_00465560();
}

// FUNCTION: LEGORACERS 0x00465510
ColorTransformResource::~ColorTransformResource()
{
	FUN_004655e0();
}

// FUNCTION: LEGORACERS 0x00465560
void ColorTransformResource::FUN_00465560()
{
	m_eventTable = NULL;
	m_flags0x20 = 0;
	m_state0x18 = 0;
	m_eventId = 0;
}

// FUNCTION: LEGORACERS 0x00465570
void ColorTransformResource::FUN_00465570(InitParams* p_params)
{
	if (m_state0x18) {
		FUN_004655e0();
	}

	m_eventId = p_params->m_unk0x00;
	LegoS32* eventId = p_params->m_stateEventIds;
	for (LegoU32 i = 0; i < sizeOfArray(m_stateEventIds); i++) {
		m_stateEventIds[i] = *eventId++;
	}

	m_eventTable = p_params->m_eventTable;
	LegoU32 flags = p_params->m_flags0x14;
	m_flags0x20 = flags;
	m_colorTransform = p_params->m_unk0x18;
	m_unk0x44 = p_params->m_unk0x38;
	if (flags & 1) {
		m_flags0x1c |= c_flags0x1cBit2;
	}
	if (flags & 4) {
		m_flags0x1c |= c_flags0x1cBit1;
	}

	m_state0x18 = c_state0x18Four;
}

// FUNCTION: LEGORACERS 0x004655e0
void ColorTransformResource::FUN_004655e0()
{
	OnEndForRacer(NULL);
	FUN_00465560();
	Reset();
}

// FUNCTION: LEGORACERS 0x00465600
void ColorTransformResource::OnStartForRacer(Racer* p_racer)
{
	LegoU8 flags = static_cast<LegoU8>(m_flags0x20);
	GolWorldEntity* entity = m_unk0x44;
	if (flags & c_flags0x20Bit1) {
		if (entity) {
			entity->VTable0x28();
		}
		else if (p_racer) {
			p_racer->m_visuals.ClearColorTransform();
		}

		NotifyStateChange(c_state0x18One, c_state0x18One);
		return;
	}

	if (entity) {
		entity->VTable0x24(&m_colorTransform);
	}
	else if (p_racer) {
		p_racer->m_visuals.SetColorTransform(&m_colorTransform);
	}

	NotifyStateChange(c_state0x18One, c_state0x18One);
}

// FUNCTION: LEGORACERS 0x00465690
void ColorTransformResource::OnEndForRacer(Racer* p_racer)
{
	if (!(static_cast<LegoU8>(m_flags0x20) & c_flags0x20Bit1)) {
		GolWorldEntity* entity = m_unk0x44;
		if (entity) {
			entity->VTable0x28();
		}
		else if (p_racer) {
			p_racer->m_visuals.ClearColorTransform();
		}
	}

	NotifyStateChange(m_state0x18, c_state0x18Three);
	m_state0x18 = c_state0x18Four;
}

// FUNCTION: LEGORACERS 0x004656d0
LegoU32 ColorTransformResource::GetKind()
{
	return 7;
}
