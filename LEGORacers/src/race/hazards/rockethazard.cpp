#include "race/hazards/rockethazard.h"

#include "decomp.h"
#include "golfileparser.h"
#include "golmath.h"
#include "golmodelentity.h"
#include "golnametable.h"
#include "race/hazards/hazardcontext.h"
#include "race/raceeventtable.h"
#include "race/racer/racer.h"
#include "types.h"
#include "world/golworlddatabase.h"

DECOMP_SIZE_ASSERT(RocketHazard, 0x5c)

// GLOBAL: LEGORACERS 0x004b4548
extern const LegoFloat g_rocketInactiveModelDistance = -1.0f;

// GLOBAL: LEGORACERS 0x004b4568
extern const LegoFloat g_rocketTriggerRadius = 350.0f;

// FUNCTION: LEGORACERS 0x0048e2a0
RocketHazard::RocketHazard()
{
	ClearFields();
}

// FUNCTION: LEGORACERS 0x0048e320
RocketHazard::~RocketHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048e370
LegoS32 RocketHazard::ClearFields()
{
	m_savedModelDistances[0] = 0.0f;
	m_savedModelDistances[1] = 0.0f;
	m_savedModelDistances[2] = 0.0f;
	m_offModel = NULL;
	m_onModel = NULL;
	m_collider = NULL;
	m_eventQueue = NULL;
	m_collisionEvent = NULL;
	m_idle = 1;

	return 0;
}

// FUNCTION: LEGORACERS 0x0048e3a0
void RocketHazard::Load(HazardContext* p_context, GolFileParser*)
{
	if (m_state) {
		Reset();
	}

	m_triggerId = 1;
	m_eventTable = p_context->GetEventTable();
	m_eventQueue = p_context->GetEventQueue();

	GolNameTable* nameTable = p_context->GetColliderTable();
	m_collider =
		nameTable->GetNameEntries() == NULL ? NULL : static_cast<ColliderRecord*>(nameTable->GetName("mmrocc"));

	GolWorldDatabase* worldDatabase = p_context->GetTrackDatabase();
	GolModelEntity* modelEntity;
	if (!worldDatabase->GetModelEntityEntries()) {
		modelEntity = NULL;
	}
	else {
		modelEntity = worldDatabase->GetModelEntityByName("mmrocof");
	}
	m_offModel = modelEntity;

	worldDatabase = p_context->GetTrackDatabase();
	if (!worldDatabase->GetModelEntityEntries()) {
		modelEntity = NULL;
	}
	else {
		modelEntity = worldDatabase->GetModelEntityByName("mmrocon");
	}
	m_onModel = modelEntity;

	for (LegoS32 i = 0; i < c_modelDistanceCount; i++) {
		m_savedModelDistances[i] = m_offModel->GetModelDistance(i);
	}

	ShowOffModel();

	GolVec3 position;
	m_offModel->GetPosition(&position);
	m_trigger.SetBoundsCenter(position);
	m_trigger.SetBoundsRadius(g_rocketTriggerRadius);
	m_idle = 1;
	m_state = c_stateLoaded;
}

// FUNCTION: LEGORACERS 0x0048e490
LegoS32 RocketHazard::Reset()
{
	OnDeactivate(NULL);
	ClearFields();
	return Hazard::Reset();
}

// FUNCTION: LEGORACERS 0x0048e4b0
void RocketHazard::OnActivate(void*)
{
	LegoEventQueue::Descriptor descriptor;
	descriptor.m_maxFireCount = 0;
	descriptor.m_hitThreshold = 0;
	descriptor.m_type = LegoEventQueue::Descriptor::c_typeRacerTrigger;
	descriptor.m_flags = 1;
	descriptor.m_worldEntity = &m_trigger;

	m_collisionEvent = m_eventQueue->AllocateEvent(this, &descriptor);
	m_state = c_stateActive;
}

// FUNCTION: LEGORACERS 0x0048e500
void RocketHazard::OnDeactivate(void*)
{
	ShowOffModel();
	if (m_collisionEvent) {
		m_collisionEvent->m_active = 0;
		m_collisionEvent = NULL;
	}
	m_state = c_stateLoaded;
}

// FUNCTION: LEGORACERS 0x0048e530
void RocketHazard::Update(undefined4 p_elapsedMs)
{
	if (m_state != c_stateLoaded) {
		Hazard::Update(p_elapsedMs);

		LegoU32 state = m_idle;
		if (state == 0) {
			if (m_onModel->GetModelDistance(0) == g_rocketInactiveModelDistance) {
				ShowOnModel();
				m_idle = 1;
				return;
			}
		}
		else if (state == 1 && m_offModel->GetModelDistance(0) == g_rocketInactiveModelDistance) {
			ShowOffModel();
		}
		m_idle = 1;
	}
}

// FUNCTION: LEGORACERS 0x0048e5a0
void RocketHazard::ShowOnModel()
{
	for (LegoS32 i = 0; i < c_modelDistanceCount; i++) {
		if (m_onModel) {
			m_onModel->SetModelDistance(i, m_savedModelDistances[i]);
		}

		if (m_offModel) {
			m_offModel->SetModelDistance(i, g_rocketInactiveModelDistance);
		}
	}

	if (m_eventTable) {
		m_eventTable->StartEventsAt(c_eventId, NULL);
	}

	if (m_collider) {
		m_collider->m_flags |= ColliderRecord::c_flagBit16;
		m_collider->m_flags |= ColliderRecord::c_flagBit17;
	}
}

// FUNCTION: LEGORACERS 0x0048e600
void RocketHazard::ShowOffModel()
{
	for (LegoS32 i = 0; i < c_modelDistanceCount; i++) {
		if (m_onModel) {
			m_onModel->SetModelDistance(i, g_rocketInactiveModelDistance);
		}

		if (m_offModel) {
			m_offModel->SetModelDistance(i, m_savedModelDistances[i]);
		}
	}

	if (m_eventTable) {
		m_eventTable->EndEventsAt(c_eventId, NULL);
	}

	if (m_collider) {
		m_collider->m_flags &= ~ColliderRecord::c_flagBit16;
		m_collider->m_flags &= ~ColliderRecord::c_flagBit17;
	}
}

// FUNCTION: LEGORACERS 0x0048e660
void RocketHazard::OnEvent(LegoEventQueue::CallbackData* p_data)
{
	if (p_data->m_racerView1->GetFlags() & Racer::c_flagShielded) {
		m_idle = 0;
	}
}
