#include "race/hazards/movingobstaclehazard.h"

#include "audio/spatialsoundinstance.h"
#include "audio/streamingsoundinstance.h"
#include "camera/golcamera.h"
#include "decomp.h"
#include "golfileparser.h"
#include "golmath.h"
#include "golmodelbase.h"
#include "golscenenode.h"
#include "goltransformbase.h"
#include "race/hazards/hazardcontext.h"
#include "race/raceeventtable.h"
#include "race/racer/racer.h"
#include "race/racer/racersoundsource.h"
#include "render/gold3drenderdevice.h"
#include "types.h"
#include "world/golworlddatabase.h"

DECOMP_SIZE_ASSERT(MovingObstacleHazard, 0x17c)

// FUNCTION: LEGORACERS 0x0048fe30
MovingObstacleHazard::MovingObstacleHazard()
{
	m_shadowMaterialTable.Reset();
	m_entity = NULL;
	m_collisionEvent = NULL;
	m_eventQueue = NULL;
	m_trackCollidable = NULL;
	m_loopSound = NULL;
	m_soundSource = NULL;
	m_flags = 0;
}

// FUNCTION: LEGORACERS 0x0048fee0
MovingObstacleHazard::~MovingObstacleHazard()
{
	Reset();
	m_shadowMaterialTable.Destroy();
}

// FUNCTION: LEGORACERS 0x0048ff50
void MovingObstacleHazard::Load(HazardContext* p_context, GolFileParser*)
{
	if (m_state) {
		Reset();
	}

	m_triggerId = 1;
	m_eventTable = p_context->GetEventTable();
	m_eventQueue = p_context->GetEventQueue();
	m_trackCollidable = p_context->GetTrackCollidable();
	m_soundSource = p_context->GetSoundSource();
	m_entity = p_context->GetTrackDatabase()->FindAnimatedEntity("crane");

	GolVec3 position;
	position.m_x = 0.0f;
	position.m_y = 0.0f;
	position.m_z = 0.0f;
	m_trigger.ClearVelocity();
	m_trigger.SetBoundsCenter(position);
	m_trigger.SetBoundsRadius(3.0f);

	m_shadowMaterialTable.Initialize(p_context->GetRenderer(), 1);
	m_shadowMaterialTable.AssignEntryByName(0, "crneshd");
	m_shadowDecal.Initialize(p_context->GetGolExport(), p_context->GetRenderer(), 0x20);
	m_state = c_stateLoaded;
}

// FUNCTION: LEGORACERS 0x00490040
LegoS32 MovingObstacleHazard::Reset()
{
	OnDeactivate(NULL);
	m_shadowDecal.Destroy();
	m_shadowMaterialTable.Clear();
	m_entity = NULL;
	return Hazard::Reset();
}

// FUNCTION: LEGORACERS 0x00490070
void MovingObstacleHazard::OnActivate(void*)
{
	LegoEventQueue::Descriptor descriptor;
	descriptor.m_type = LegoEventQueue::Descriptor::c_typeRacerTrigger;
	descriptor.m_flags = 1;
	descriptor.m_maxFireCount = 0;
	descriptor.m_hitThreshold = 0;
	descriptor.m_worldEntity = &m_trigger;

	m_collisionEvent = m_eventQueue->AllocateEvent(this, &descriptor);
	m_loopSound = m_soundSource->AcquireSoundById(c_soundId);
	if (m_loopSound != NULL) {
		GolVec3 position;
		m_entity->GetPosition(&position);
		m_loopSound->Play(TRUE);
		m_loopSound->SetPosition(position);
		m_loopSound->SetFrequencyScale(1.0f);
		LegoFloat maxDistance = 300.0f;
		m_loopSound->SetDistanceRangeWithMinSquared(10000.0f, maxDistance);
	}

	m_flags = c_flagImpactPending;
	m_state = c_stateActive;
}

// FUNCTION: LEGORACERS 0x00490140
void MovingObstacleHazard::OnDeactivate(void*)
{
	if (m_collisionEvent != NULL) {
		m_collisionEvent->m_active = 0;
		m_collisionEvent = NULL;
	}

	if (m_loopSound != NULL) {
		m_soundSource->ReleaseSound(m_loopSound);
		m_loopSound = NULL;
	}

	m_state = c_stateLoaded;
}

// FUNCTION: LEGORACERS 0x00490190
void MovingObstacleHazard::Update(undefined4 p_elapsedMs)
{
	if (m_state == c_stateLoaded) {
		return;
	}

	Hazard::Update(p_elapsedMs);

	GolSceneNode* node = m_entity->GetSceneNode(0);
	GolTransformBase* transform = node->GetTransform(3);

	GolVec3 offset;
	offset.m_x = 0.0f;
	offset.m_y = 0.0f;
	offset.m_z = 0.0f;
	GolVec3 position;
	do {
		position = offset;
		transform->TransformPoint(&position, &offset);
		transform = transform->m_parent;
	} while (transform != NULL);

	LegoFloat scale = m_entity->GetModel(0)->GetScale() * m_entity->GetScale();
	offset.m_x *= scale;
	offset.m_y *= scale;
	offset.m_z *= scale;

	m_entity->LocalToWorld(offset, &position);
	m_trigger.SetBoundsCenter(position);

	LegoFloat frame = m_entity->GetPartTimeMs();
	if ((m_flags & c_flagImpactPending) != 0) {
		if ((frame > 150.0f && frame < 180.0f) || (frame > 0.0f && frame < 30.0f)) {
			m_eventTable->FireEventsAt(c_impactEventId, c_impactEventId, &position);
			m_flags &= ~c_flagImpactPending;
		}
	}
	else if ((frame > 60.0f && frame < 120.0f) || (frame > 210.0f && frame < 270.0f)) {
		m_flags |= c_flagImpactPending;
	}

	m_flags &= ~c_flagShadowVisible;
}

// FUNCTION: LEGORACERS 0x00490330
void MovingObstacleHazard::UpdatePerRacer(GolCamera* p_camera, Racer*)
{
	if (m_state == c_stateLoaded || (m_flags & c_flagShadowVisible) != 0) {
		return;
	}

	GolVec3 position;
	m_trigger.GetBoundsCenter(&position);

	GolVec3 cameraPosition;
	p_camera->GetTransform()->GetPosition(&cameraPosition);

	LegoFloat dx = position.m_x - cameraPosition.m_x;
	LegoFloat dy = position.m_y - cameraPosition.m_y;
	LegoFloat dz = position.m_z - cameraPosition.m_z;
	LegoFloat distanceSquared = dx * dx + dy * dy + dz * dz;
	if (distanceSquared >= m_entity->GetModelDistance(0)) {
		return;
	}

	m_shadowDecal.m_width = 13.0f;
	m_shadowDecal.m_length = 13.0f;
	m_shadowDecal.m_depth = 15.0f;
	m_shadowDecal.m_center.m_x = position.m_x;
	m_shadowDecal.m_center.m_y = position.m_y;
	m_shadowDecal.m_center.m_z = position.m_z;
	m_shadowDecal.GetEntity().SetPrimaryMaterialTable(&m_shadowMaterialTable);

	GolVec3 up;
	GolVec3 forward;
	m_entity->GetAxes(&up, &forward);

	forward.m_x = 0.0f;
	forward.m_y = 0.0f;
	forward.m_z = -1.0f;
	m_shadowDecal.SetOrientation(&forward, &up);
	m_shadowDecal.Project(m_trackCollidable);

	m_flags |= c_flagShadowVisible;
}

// FUNCTION: LEGORACERS 0x00490460
void MovingObstacleHazard::Draw(GolD3DRenderDevice* p_renderer)
{
	if (m_state != c_stateLoaded && (m_flags & c_flagShadowVisible) != 0) {
		m_shadowDecal.Draw(p_renderer);
	}
}

// FUNCTION: LEGORACERS 0x00490490
void MovingObstacleHazard::OnEvent(LegoEventQueue::CallbackData* p_data)
{
	Racer* racer = static_cast<Racer*>(p_data->m_data);
	RacerPhysics* physics = &racer->m_physics;
	if (!(physics->m_flags & RacerPhysics::c_flagSpinning) && physics->m_forwardSpeed != 0.0f) {
		physics->StartSpin(1.0f, 0.01f, 0.0f);

		GolVec3 position;
		racer->m_visuals.m_carEntity->GetPosition(&position);
		m_eventTable->FireEventsAt(c_nearImpactEventId, c_nearImpactEventId, &position);
	}
}
