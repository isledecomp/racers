#include "race/events/modeldistanceresource.h"

#include "decomp.h"
#include "golmodelentity.h"

DECOMP_SIZE_ASSERT(ModelDistanceResource::InitParams, 0x24)
DECOMP_SIZE_ASSERT(ModelDistanceResource, 0x34)

// FUNCTION: LEGORACERS 0x00463640
ModelDistanceResource::ModelDistanceResource()
{
	m_flags = 0;
	ClearFields();
}

// FUNCTION: LEGORACERS 0x00463690
ModelDistanceResource::~ModelDistanceResource()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004636e0
void ModelDistanceResource::ClearFields()
{
	m_modelDistances[0] = 0.0f;
	m_modelDistances[1] = 0.0f;
	m_modelDistances[2] = 0.0f;
	m_hideWhenActive = FALSE;
	m_modelEntity = NULL;
}

// FUNCTION: LEGORACERS 0x00463700
void ModelDistanceResource::Initialize(InitParams* p_params)
{
	if (m_state) {
		Destroy();
	}

	m_eventId = p_params->m_eventId;
	LegoS32* eventId = p_params->m_stateEventIds;
	LegoU32 i;
	for (i = 0; i < sizeOfArray(m_stateEventIds); i++) {
		m_stateEventIds[i] = *eventId++;
	}

	m_eventTable = p_params->m_eventTable;
	m_modelEntity = p_params->m_modelEntity;
	m_hideWhenActive = p_params->m_hideWhenActive;
	if (p_params->m_noEnd) {
		m_flags |= c_flagNoEnd;
	}
	if (p_params->m_triggerOnEnd) {
		m_flags |= c_flagTriggerOnEnd;
	}

	for (i = 0; i < sizeOfArray(m_modelDistances); i++) {
		m_modelDistances[i] = m_modelEntity->GetModelDistance(i);
		if (!m_hideWhenActive) {
			LegoFloat modelDistance = -1.0f;
			m_modelEntity->SetModelDistance(i, modelDistance);
		}
	}

	m_state = c_stateIdle;
}

// FUNCTION: LEGORACERS 0x004637a0
void ModelDistanceResource::Destroy()
{
	ClearFields();
	Reset();
}

// FUNCTION: LEGORACERS 0x004637c0
void ModelDistanceResource::OnStartAt(GolVec3*)
{
	for (LegoU32 i = 0; i < sizeOfArray(m_modelDistances); i++) {
		LegoFloat modelDistance;
		if (m_hideWhenActive) {
			modelDistance = -1.0f;
		}
		else {
			modelDistance = m_modelDistances[i];
		}
		m_modelEntity->SetModelDistance(i, modelDistance);
	}

	m_state = c_stateActive;
}

// FUNCTION: LEGORACERS 0x00463800
void ModelDistanceResource::OnEnd()
{
	for (LegoU32 i = 0; i < sizeOfArray(m_modelDistances); i++) {
		LegoFloat modelDistance;
		if (m_hideWhenActive) {
			modelDistance = m_modelDistances[i];
		}
		else {
			modelDistance = -1.0f;
		}
		m_modelEntity->SetModelDistance(i, modelDistance);
	}

	m_state = c_stateIdle;
}

// FUNCTION: LEGORACERS 0x00463840
LegoU32 ModelDistanceResource::GetKind()
{
	return 10;
}
