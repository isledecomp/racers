#include "race/hazards/rollingrockhazard.h"

#include "decomp.h"
#include "golanimatedentity.h"
#include "golfileparser.h"
#include "golmath.h"
#include "golmodelbase.h"
#include "golscenenode.h"
#include "goltransformbase.h"
#include "race/hazards/hazardcontext.h"
#include "types.h"
#include "world/golworlddatabase.h"

#include <float.h>
#include <string.h>

DECOMP_SIZE_ASSERT(RollingRockHazard, 0x204)

// GLOBAL: LEGORACERS 0x004b42e8
extern const LegoFloat g_rollingRockModelDistance = FLT_MAX;

// GLOBAL: LEGORACERS 0x004b42ec
extern const LegoFloat g_rollingRockMass = 20000.0f;

// FUNCTION: LEGORACERS 0x0048bb00
RollingRockHazard::RollingRockHazard()
	: m_entity(NULL), m_eventQueue(NULL), m_collisionEvent(NULL), m_sizeX(0.0f), m_sizeY(0.0f), m_sizeZ(0.0f),
	  m_isRock(0)
{
}

// FUNCTION: LEGORACERS 0x0048bba0
RollingRockHazard::~RollingRockHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048bbf0
void RollingRockHazard::Load(HazardContext* p_context, GolFileParser* p_parser)
{
	if (m_state) {
		Reset();
	}

	m_eventTable = p_context->GetEventTable();
	m_eventQueue = p_context->GetEventQueue();

	p_parser->ReadLeftCurly();

	GolName name;
	::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));
	m_entity = p_context->GetTrackDatabase()->FindAnimatedEntity(name);

	LegoU32 state = 1;
	if (!::strncmp(name, "rk", 2)) {
		m_isRock = state;
	}

	m_triggerId = p_parser->ReadInteger();
	LegoFloat activeValue = p_parser->ReadFloat();
	m_sizeX = p_parser->ReadFloat();
	m_sizeY = p_parser->ReadFloat();
	m_sizeZ = p_parser->ReadFloat();
	p_parser->ReadRightCurly();

	GolAnimatedEntity* entity = m_entity;
	entity->ResetPartIndices();
	entity->SetActiveValue(activeValue);
	m_bodyEntity.SetNode(m_entity->GetSceneNode(0), m_entity->GetModelPart(), g_rollingRockModelDistance);

	LegoFloat radius = m_sizeX * 0.5f;
	LegoFloat halfDimension = m_sizeY * 0.5f;
	if (halfDimension > radius) {
		radius = halfDimension;
	}

	halfDimension = m_sizeZ * 0.5f;
	if (halfDimension > radius) {
		radius = halfDimension;
	}

	m_bodyEntity.SetBoundsRadius(radius);
	m_body.Initialize(&m_bodyEntity, g_rollingRockMass, m_sizeX, m_sizeY, m_sizeZ);
	m_state = state;
}

// FUNCTION: LEGORACERS 0x0048bda0
void RollingRockHazard::Reset()
{
	OnDeactivate(NULL);
	m_isRock = 0;
	m_sizeX = 0.0f;
	m_sizeY = 0.0f;
	m_sizeZ = 0.0f;
	m_entity = NULL;
	m_eventQueue = NULL;
	m_collisionEvent = NULL;
	m_bodyEntity.ResetModelState();
	m_body.Destroy();
	Hazard::Reset();
}

// FUNCTION: LEGORACERS 0x0048be00
void RollingRockHazard::OnActivate(void*)
{
	LegoEventQueue::Descriptor descriptor;
	descriptor.m_type = LegoEventQueue::Descriptor::c_typeCollision;
	descriptor.m_flags = 1;
	descriptor.m_hitThreshold = 0;
	descriptor.m_data = &m_body;

	m_collisionEvent = m_eventQueue->AllocateEvent(this, &descriptor);
	m_state = c_stateActive;
}

// FUNCTION: LEGORACERS 0x0048be50
void RollingRockHazard::OnDeactivate(void*)
{
	if (m_collisionEvent != NULL) {
		m_collisionEvent->m_active = 0;
		m_collisionEvent = NULL;
	}

	m_state = c_stateLoaded;
}

// STUB: LEGORACERS 0x0048be70
void RollingRockHazard::Update(undefined4 p_elapsedMs)
{
	if (m_state != c_stateLoaded) {
		Hazard::Update(p_elapsedMs);

		GolSceneNode* node = m_entity->GetSceneNode(0);
		GolTransformBase* transform = node->GetTransform(1);

		GolVec3 localPosition;
		localPosition.m_x = 0.0f;
		localPosition.m_y = 0.0f;
		localPosition.m_z = 0.0f;

		GolVec3 right;
		GolVec3 forward;
		transform->VTable0x20(&right, &forward);

		GolVec3 origin = localPosition;
		transform->TransformPoint(&origin, &localPosition);

		if (m_isRock) {
			do {
				GolVec3 transformedRight = right;
				GolVec3 transformedForward = forward;
				transform->TransformVector(&transformedRight, &right);
				transform->TransformVector(&transformedForward, &forward);
				transform = transform->m_parent;
			} while (transform != NULL);
		}

		LegoFloat scale = m_entity->GetModel(0)->GetScale() * m_entity->GetScale();
		localPosition.m_x *= scale;
		localPosition.m_y *= scale;
		localPosition.m_z *= scale;
		GolVec3 worldPosition;
		m_entity->LocalToWorld(localPosition, &worldPosition);
		m_body.m_centerOfMassWorld = worldPosition;

		if (m_isRock) {
			GolVec3 worldRight;
			GolVec3 worldForward;
			m_entity->RotateToWorld(right, &worldRight);
			m_entity->RotateToWorld(forward, &worldForward);
			m_bodyEntity.SetDirectionUp(worldRight, worldForward);
		}

		m_bodyEntity.SetBoundsCenter(worldPosition);
	}
}
