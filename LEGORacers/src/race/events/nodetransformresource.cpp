#include "race/events/nodetransformresource.h"

#include "decomp.h"
#include "golboundedentity.h"
#include "golmodelbase.h"
#include "golmodelentity.h"
#include "golscenenode.h"
#include "goltransformbase.h"

DECOMP_SIZE_ASSERT(NodeTransformResource::InitParams, 0x24)
DECOMP_SIZE_ASSERT(NodeTransformResource, 0x2c)

// FUNCTION: LEGORACERS 0x00463850
NodeTransformResource::NodeTransformResource()
{
	FUN_004638f0();
	m_flags0x1c = 0;
}

// FUNCTION: LEGORACERS 0x004638a0
NodeTransformResource::~NodeTransformResource()
{
	FUN_00463970();
}

// FUNCTION: LEGORACERS 0x004638f0
void NodeTransformResource::FUN_004638f0()
{
	m_unk0x20 = NULL;
	m_unk0x24 = NULL;
	m_unk0x28 = 0;
}

// FUNCTION: LEGORACERS 0x00463900
void NodeTransformResource::FUN_00463900(InitParams* p_params)
{
	if (m_state0x18) {
		FUN_00463970();
	}

	m_eventId = p_params->m_unk0x00;
	LegoS32* eventId = p_params->m_stateEventIds;
	for (LegoU32 i = 0; i < sizeOfArray(m_stateEventIds); i++) {
		m_stateEventIds[i] = *eventId++;
	}

	m_eventTable = p_params->m_eventTable;
	m_unk0x20 = p_params->m_unk0x14;
	m_unk0x24 = p_params->m_unk0x18;
	m_unk0x28 = p_params->m_unk0x1c;
	if (p_params->m_unk0x20) {
		m_flags0x1c |= c_flags0x1cBit2;
	}

	m_state0x18 = c_state0x18One;
}

// FUNCTION: LEGORACERS 0x00463970
void NodeTransformResource::FUN_00463970()
{
	OnEnd();
	FUN_004638f0();
	Reset();
}

// FUNCTION: LEGORACERS 0x00463990
void NodeTransformResource::OnStartAt(GolVec3*)
{
	NotifyStateChange(1, 1);
	m_state0x18 = c_state0x18Three;
}

// FUNCTION: LEGORACERS 0x004639b0
void NodeTransformResource::OnEnd()
{
	NotifyStateChange(m_state0x18, 3);
	m_state0x18 = c_state0x18One;
}

// FUNCTION: LEGORACERS 0x004639d0
void NodeTransformResource::Update(LegoU32 p_elapsedMs)
{
	if (m_state0x18 != c_state0x18One) {
		RaceEventResource::Update(p_elapsedMs);

		if (m_unk0x20) {
			m_unk0x24->VTable0x5c(0);
			GolSceneNode* node = m_unk0x24->VTable0x58(0);
			GolTransformBase* transform = node->VTable0x18(m_unk0x28);

			GolVec3 position;
			GolVec3 up;
			GolVec3 right;
			transform->GetPosition(&position);
			transform->GetUp(&up);
			transform->GetRight(&right);

			LegoFloat scale = m_unk0x24->GetModel(0)->GetScale() * m_unk0x24->GetUnk0x58();
			position.m_x *= scale;
			position.m_y *= scale;
			position.m_z *= scale;

			GolVec3 transformedPosition;
			GolVec3 transformedUp;
			GolVec3 transformedRight;
			m_unk0x24->VTable0x2c(position, &transformedPosition);
			m_unk0x24->VTable0x34(up, &transformedUp);
			m_unk0x24->VTable0x34(right, &transformedRight);
			m_unk0x20->VTable0x08(transformedPosition);
			m_unk0x20->VTable0x40(transformedUp, transformedRight);
		}
	}
}

// FUNCTION: LEGORACERS 0x00463ad0
LegoU32 NodeTransformResource::GetKind()
{
	return 9;
}
