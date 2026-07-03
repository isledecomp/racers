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
	ClearFields();
	m_flags = 0;
}

// FUNCTION: LEGORACERS 0x004638a0
NodeTransformResource::~NodeTransformResource()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004638f0
void NodeTransformResource::ClearFields()
{
	m_boundedEntity = NULL;
	m_modelEntity = NULL;
	m_nodeIndex = 0;
}

// FUNCTION: LEGORACERS 0x00463900
void NodeTransformResource::Initialize(InitParams* p_params)
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
	m_boundedEntity = p_params->m_boundedEntity;
	m_modelEntity = p_params->m_modelEntity;
	m_nodeIndex = p_params->m_nodeIndex;
	if (p_params->m_triggerOnEnd) {
		m_flags |= c_flagTriggerOnEnd;
	}

	m_state = c_stateIdle;
}

// FUNCTION: LEGORACERS 0x00463970
void NodeTransformResource::Destroy()
{
	OnEnd();
	ClearFields();
	Reset();
}

// FUNCTION: LEGORACERS 0x00463990
void NodeTransformResource::OnStartAt(GolVec3*)
{
	NotifyStateChange(1, 1);
	m_state = c_stateActive;
}

// FUNCTION: LEGORACERS 0x004639b0
void NodeTransformResource::OnEnd()
{
	NotifyStateChange(m_state, 3);
	m_state = c_stateIdle;
}

// FUNCTION: LEGORACERS 0x004639d0
void NodeTransformResource::Update(LegoU32 p_elapsedMs)
{
	if (m_state != c_stateIdle) {
		RaceEventResource::Update(p_elapsedMs);

		if (m_boundedEntity) {
			m_modelEntity->ApplyPartAnimation(0);
			GolSceneNode* node = m_modelEntity->GetSceneNode(0);
			GolTransformBase* transform = node->GetTransform(m_nodeIndex);

			GolVec3 position;
			GolVec3 up;
			GolVec3 right;
			transform->GetPosition(&position);
			transform->GetUp(&up);
			transform->GetRight(&right);

			LegoFloat scale = m_modelEntity->GetModel(0)->GetScale() * m_modelEntity->GetScale();
			position.m_x *= scale;
			position.m_y *= scale;
			position.m_z *= scale;

			GolVec3 transformedPosition;
			GolVec3 transformedUp;
			GolVec3 transformedRight;
			m_modelEntity->LocalToWorld(position, &transformedPosition);
			m_modelEntity->RotateToWorld(up, &transformedUp);
			m_modelEntity->RotateToWorld(right, &transformedRight);
			m_boundedEntity->SetPosition(transformedPosition);
			m_boundedEntity->SetDirectionUp(transformedUp, transformedRight);
		}
	}
}

// FUNCTION: LEGORACERS 0x00463ad0
LegoU32 NodeTransformResource::GetKind()
{
	return 9;
}
