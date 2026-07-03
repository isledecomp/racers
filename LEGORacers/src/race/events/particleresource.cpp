#include "race/events/particleresource.h"

#include "decomp.h"
#include "golmodelbase.h"
#include "golmodelentity.h"
#include "golscenenode.h"
#include "goltransformbase.h"
#include "menu/runtime/cutsceneanimation.h"
#include "menu/runtime/cutsceneparticle.h"

#include <string.h>

DECOMP_SIZE_ASSERT(ParticleResource::InitParams, 0x5c)
DECOMP_SIZE_ASSERT(ParticleResource, 0x64)

// FUNCTION: LEGORACERS 0x0044f580 FOLDED
LegoU32 ParticleResource::GetKind()
{
	return 3;
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void ParticleResource::FUN_004513d0(undefined4)
{
}

// FUNCTION: LEGORACERS 0x0045e920
ParticleResource::ParticleResource()
{
	ClearFields();
	m_flags = 0;
}

// FUNCTION: LEGORACERS 0x0045e970
ParticleResource::~ParticleResource()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0045e9c0
void ParticleResource::ClearFields()
{
	m_particleAnimation = NULL;
	m_sharedParticleAnimation = NULL;
	m_particle = NULL;
	m_trackedEntity = NULL;
	m_particleName[0] = '\0';
	m_position.m_x = 0.0f;
	m_position.m_y = 0.0f;
	m_position.m_z = 0.0f;
	m_direction.m_x = 0.0f;
	m_direction.m_y = 0.0f;
	m_direction.m_z = 0.0f;
	m_direction.m_x = 1.0f;
	m_up.m_x = 0.0f;
	m_up.m_y = 0.0f;
	m_up.m_z = 0.0f;
	m_up.m_z = 1.0f;
	m_partAnimations = 0;
	m_nodeIndex = 0;
}

// FUNCTION: LEGORACERS 0x0045ea00
void ParticleResource::Initialize(InitParams* p_params)
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
	m_particleAnimation = p_params->m_particleAnimation;
	m_sharedParticleAnimation = p_params->m_sharedParticleAnimation;
	m_trackedEntity = p_params->m_trackedEntity;
	m_nodeIndex = p_params->m_nodeIndex;
	::strncpy(m_particleName, p_params->m_particleName, sizeof(m_particleName));
	m_position.m_x = p_params->m_position.m_x;
	m_position.m_y = p_params->m_position.m_y;
	m_position.m_z = p_params->m_position.m_z;
	m_direction.m_x = p_params->m_direction.m_x;
	m_direction.m_y = p_params->m_direction.m_y;
	m_direction.m_z = p_params->m_direction.m_z;
	m_up.m_x = p_params->m_up.m_x;
	m_up.m_y = p_params->m_up.m_y;
	m_up.m_z = p_params->m_up.m_z;

	if (p_params->m_noEnd) {
		m_flags |= c_flagNoEnd;
	}

	if (p_params->m_triggerOnEnd) {
		m_flags |= c_flagTriggerOnEnd;
	}

	if (p_params->m_atEventPosition) {
		m_flags |= c_flagAtEventPosition;
	}

	m_state = c_stateIdle;
	m_flags &= ~c_flagBit5;
}

// FUNCTION: LEGORACERS 0x0045ead0
void ParticleResource::Destroy()
{
	OnEnd();
	ClearFields();
	Reset();
}

// FUNCTION: LEGORACERS 0x0045eaf0
void ParticleResource::OnStartAt(GolVec3* p_position)
{
	if (p_position && (m_flags & c_flagAtEventPosition)) {
		m_position = *p_position;
	}

	if (m_particleAnimation->HasEmitter(m_particleName)) {
		m_partAnimations = 1;
		m_particle = m_particleAnimation->SpawnParticle(m_particleName, &m_position, &m_direction, &m_up);
	}
	else if (m_sharedParticleAnimation->HasEmitter(m_particleName)) {
		m_partAnimations = 0;
		m_particle = m_sharedParticleAnimation->SpawnParticle(m_particleName, &m_position, &m_direction, &m_up);
	}

	if (m_particle) {
		m_flags |= c_flagBit5;
	}

	NotifyStateChange(m_state, 1);
	m_state = c_stateActive;
}

// FUNCTION: LEGORACERS 0x0045eb90
void ParticleResource::OnEnd()
{
	if (m_particle) {
		if (m_partAnimations) {
			m_particleAnimation->FinishRef(m_particle);
		}
		else {
			m_sharedParticleAnimation->FinishRef(m_particle);
		}

		m_particle = NULL;
	}

	NotifyStateChange(m_state, 3);
	m_state = c_stateIdle;
	m_flags &= ~c_flagBit5;
}

// FUNCTION: LEGORACERS 0x0045ebe0
void ParticleResource::Update(LegoU32 p_elapsedMs)
{
	RaceEventResource::Update(p_elapsedMs);
	if (m_state == c_stateIdle) {
		return;
	}

	if (!(m_flags & c_flagBit5)) {
		if (m_particleAnimation->HasEmitter(m_particleName)) {
			m_partAnimations = 1;
			m_particle = m_particleAnimation->SpawnParticle(m_particleName, &m_position, &m_direction, &m_up);
		}
		else if (m_sharedParticleAnimation->HasEmitter(m_particleName)) {
			m_partAnimations = 0;
			m_particle = m_sharedParticleAnimation->SpawnParticle(m_particleName, &m_position, &m_direction, &m_up);
		}

		if (m_particle) {
			m_flags |= c_flagBit5;
		}
	}

	if (m_trackedEntity && m_particle) {
		m_trackedEntity->ApplyPartAnimation(0);
		GolSceneNode* node = m_trackedEntity->GetSceneNode(0);
		GolTransformBase* transform = node->GetTransform(m_nodeIndex);
		GolVec3 position;
		position.m_x = 0.0f;
		position.m_y = 0.0f;
		position.m_z = 0.0f;
		GolVec3 transformedPosition;

		do {
			transformedPosition = position;
			transform->TransformPoint(&transformedPosition, &position);
			transform = transform->m_parent;
		} while (transform);

		LegoFloat scale = m_trackedEntity->GetModel(0)->GetScale() * m_trackedEntity->GetScale();
		position.m_x *= scale;
		position.m_y *= scale;
		position.m_z *= scale;

		m_trackedEntity->LocalToWorld(position, &transformedPosition);
		if (m_particle->m_particle) {
			m_particle->m_particle->SetPosition(&transformedPosition);
		}
	}
}
