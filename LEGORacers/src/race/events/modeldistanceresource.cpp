#include "race/events/modeldistanceresource.h"

#include "decomp.h"
#include "golmodelentity.h"

DECOMP_SIZE_ASSERT(ModelDistanceResource::InitParams, 0x24)
DECOMP_SIZE_ASSERT(ModelDistanceResource, 0x34)

// FUNCTION: LEGORACERS 0x00463640
ModelDistanceResource::ModelDistanceResource()
{
	m_flags0x1c = 0;
	FUN_004636e0();
}

// FUNCTION: LEGORACERS 0x00463690
ModelDistanceResource::~ModelDistanceResource()
{
	FUN_004637a0();
}

// FUNCTION: LEGORACERS 0x004636e0
void ModelDistanceResource::FUN_004636e0()
{
	m_modelDistances[0] = 0.0f;
	m_modelDistances[1] = 0.0f;
	m_modelDistances[2] = 0.0f;
	m_unk0x30 = FALSE;
	m_modelEntity = NULL;
}

// FUNCTION: LEGORACERS 0x00463700
void ModelDistanceResource::FUN_00463700(InitParams* p_params)
{
	if (m_state0x18) {
		FUN_004637a0();
	}

	m_eventId = p_params->m_eventId;
	LegoS32* eventId = p_params->m_stateEventIds;
	LegoU32 i;
	for (i = 0; i < sizeOfArray(m_stateEventIds); i++) {
		m_stateEventIds[i] = *eventId++;
	}

	m_eventTable = p_params->m_eventTable;
	m_modelEntity = p_params->m_modelEntity;
	m_unk0x30 = p_params->m_unk0x20;
	if (p_params->m_unk0x18) {
		m_flags0x1c |= c_flagNoEnd;
	}
	if (p_params->m_unk0x1c) {
		m_flags0x1c |= c_flagTriggerOnEnd;
	}

	for (i = 0; i < sizeOfArray(m_modelDistances); i++) {
		m_modelDistances[i] = m_modelEntity->GetModelDistance(i);
		if (!m_unk0x30) {
			LegoFloat modelDistance = -1.0f;
			m_modelEntity->SetModelDistance(i, modelDistance);
		}
	}

	m_state0x18 = c_stateIdle;
}

// FUNCTION: LEGORACERS 0x004637a0
void ModelDistanceResource::FUN_004637a0()
{
	FUN_004636e0();
	Reset();
}

// FUNCTION: LEGORACERS 0x004637c0
void ModelDistanceResource::OnStartAt(GolVec3*)
{
	for (LegoU32 i = 0; i < sizeOfArray(m_modelDistances); i++) {
		LegoFloat modelDistance;
		if (m_unk0x30) {
			modelDistance = -1.0f;
		}
		else {
			modelDistance = m_modelDistances[i];
		}
		m_modelEntity->SetModelDistance(i, modelDistance);
	}

	m_state0x18 = c_stateActive;
}

// FUNCTION: LEGORACERS 0x00463800
void ModelDistanceResource::OnEnd()
{
	for (LegoU32 i = 0; i < sizeOfArray(m_modelDistances); i++) {
		LegoFloat modelDistance;
		if (m_unk0x30) {
			modelDistance = m_modelDistances[i];
		}
		else {
			modelDistance = -1.0f;
		}
		m_modelEntity->SetModelDistance(i, modelDistance);
	}

	m_state0x18 = c_stateIdle;
}

// FUNCTION: LEGORACERS 0x00463840
LegoU32 ModelDistanceResource::GetKind()
{
	return 10;
}
