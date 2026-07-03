#include "race/events/colortransformresource.h"

#include "decomp.h"
#include "race/racesession.h"

DECOMP_SIZE_ASSERT(ColorTransformResource, 0x48)
DECOMP_SIZE_ASSERT(ColorTransformResource::InitParams, 0x3c)

// FUNCTION: LEGORACERS 0x004654c0
ColorTransformResource::ColorTransformResource()
{
	ClearFields();
}

// FUNCTION: LEGORACERS 0x00465510
ColorTransformResource::~ColorTransformResource()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00465560
void ColorTransformResource::ClearFields()
{
	m_eventTable = NULL;
	m_transformFlags = 0;
	m_state = 0;
	m_eventId = 0;
}

// FUNCTION: LEGORACERS 0x00465570
void ColorTransformResource::Initialize(InitParams* p_params)
{
	if (m_state) {
		Destroy();
	}

	m_eventId = p_params->m_eventId;
	LegoS32* eventId = p_params->m_stateEventIds;
	for (LegoU32 i = 0; i < sizeOfArray(m_stateEventIds); i++) {
		m_stateEventIds[i] = *eventId++;
	}

	m_eventTable = p_params->m_eventTable;
	LegoU32 flags = p_params->m_flags;
	m_transformFlags = flags;
	m_colorTransform = p_params->m_colorTransform;
	m_worldEntity = p_params->m_worldEntity;
	if (flags & 1) {
		m_flags |= c_flagTriggerOnEnd;
	}
	if (flags & 4) {
		m_flags |= c_flagNoEnd;
	}

	m_state = c_stateEnded;
}

// FUNCTION: LEGORACERS 0x004655e0
void ColorTransformResource::Destroy()
{
	OnEndForRacer(NULL);
	ClearFields();
	Reset();
}

// FUNCTION: LEGORACERS 0x00465600
void ColorTransformResource::OnStartForRacer(Racer* p_racer)
{
	LegoU8 flags = static_cast<LegoU8>(m_transformFlags);
	GolWorldEntity* entity = m_worldEntity;
	if (flags & c_clearTransform) {
		if (entity) {
			entity->ClearColorTransform();
		}
		else if (p_racer) {
			p_racer->m_visuals.ClearColorTransform();
		}

		NotifyStateChange(c_stateIdle, c_stateIdle);
		return;
	}

	if (entity) {
		entity->ApplyColorTransform(&m_colorTransform);
	}
	else if (p_racer) {
		p_racer->m_visuals.SetColorTransform(&m_colorTransform);
	}

	NotifyStateChange(c_stateIdle, c_stateIdle);
}

// FUNCTION: LEGORACERS 0x00465690
void ColorTransformResource::OnEndForRacer(Racer* p_racer)
{
	if (!(static_cast<LegoU8>(m_transformFlags) & c_clearTransform)) {
		GolWorldEntity* entity = m_worldEntity;
		if (entity) {
			entity->ClearColorTransform();
		}
		else if (p_racer) {
			p_racer->m_visuals.ClearColorTransform();
		}
	}

	NotifyStateChange(m_state, c_stateActive);
	m_state = c_stateEnded;
}

// FUNCTION: LEGORACERS 0x004656d0
LegoU32 ColorTransformResource::GetKind()
{
	return 7;
}
