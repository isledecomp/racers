#include "race/powerups/curseaction.h"

#include "audio/spatialsoundinstance.h"
#include "camera/golcamera.h"
#include "cmbmodelpart.h"
#include "golmodelbase.h"
#include "menu/runtime/cutsceneparticle.h"
#include "race/powerups/racepowerupmanager.h"
#include "race/racesoundsource.h"
#include "render/gold3drenderdevice.h"

#include <float.h>
#include <math.h>

// GLOBAL: LEGORACERS 0x004b13f0
const LegoFloat g_curseSoundMinDistance = 30.0f;

// GLOBAL: LEGORACERS 0x004b13f4
const LegoFloat g_curseSoundMaxDistanceSquared = 300.0f;

// GLOBAL: LEGORACERS 0x004b13f8
const LegoFloat g_curseTriggerRadius = 10.0f;

// FUNCTION: LEGORACERS 0x00452440
CurseAction::CurseAction()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004524a0
CurseAction::~CurseAction()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004524f0
void CurseAction::Reset()
{
	m_manager = 0;
	m_curseEntity = 0;
	m_auraEntity = 0;
	m_innerAuraEntity = 0;
	m_raceState = NULL;
	m_collisionWorld = 0;
	m_sound = 0;
}

// FUNCTION: LEGORACERS 0x00452510
void CurseAction::Destroy()
{
	Deactivate();
	Reset();
}

// FUNCTION: LEGORACERS 0x00452530
void CurseAction::Initialize(RaceState* p_raceState, TriggerWorld* p_collisionWorld, RacePowerupManager* p_manager)
{
	m_raceState = p_raceState;
	m_collisionWorld = p_collisionWorld;
	m_manager = p_manager;
	m_state = c_stateReady;
}

// FUNCTION: LEGORACERS 0x00452550
void CurseAction::Activate(
	Racer* p_racer,
	GolAnimatedEntity* p_curseTemplate,
	GolAnimatedEntity* p_auraTemplate,
	GolAnimatedEntity* p_innerAuraTemplate,
	ActionTarget* p_target
)
{
	m_curseEntity = m_manager->AllocateEffectEntity();
	if (m_curseEntity == NULL) {
		m_state = c_stateDone;
		return;
	}

	m_auraEntity = m_manager->AllocateEffectEntity();
	if (m_auraEntity == NULL) {
		m_state = c_stateDone;
		return;
	}

	m_innerAuraEntity = m_manager->AllocateEffectEntity();
	if (m_innerAuraEntity == NULL) {
		m_state = c_stateDone;
		return;
	}

	m_ownerRacer = p_racer;

	m_curseEntity->SetModel(
		p_curseTemplate->GetModel(0),
		p_curseTemplate->GetSceneNode(0),
		p_curseTemplate->GetModelPart(0),
		p_curseTemplate->GetModelDistance(0)
	);

	LegoU32 i;
	for (i = 1; i < 3; i++) {
		GolModelBase* model = p_curseTemplate->GetModel(i);
		if (model != NULL) {
			LegoFloat modelDistance = p_curseTemplate->GetModelDistance(i);
			CmbModelPart* modelPart = p_curseTemplate->GetModelPart(i);
			m_curseEntity->AddModel(model, p_curseTemplate->GetSceneNode(i), modelPart, modelDistance);
		}
	}
	m_curseEntity->SetFlags(m_curseEntity->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_curseEntity->PlayPart(0);

	m_auraEntity->SetModel(
		p_auraTemplate->GetModel(0),
		p_auraTemplate->GetSceneNode(0),
		p_auraTemplate->GetModelPart(0),
		p_auraTemplate->GetModelDistance(0)
	);
	for (i = 1; i < 3; i++) {
		GolModelBase* model = p_auraTemplate->GetModel(i);
		if (model != NULL) {
			LegoFloat modelDistance = p_auraTemplate->GetModelDistance(i);
			CmbModelPart* modelPart = p_auraTemplate->GetModelPart(i);
			m_auraEntity->AddModel(model, p_auraTemplate->GetSceneNode(i), modelPart, modelDistance);
		}
	}
	m_auraEntity->SetFlags(m_auraEntity->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_auraEntity->PlayPart(0);
	m_auraEntity->SetTextureScrollU(p_auraTemplate->GetTextureScrollU());
	m_auraEntity->SetTextureScrollV(p_auraTemplate->GetTextureScrollV());
	m_auraEntity->SetTextureScrollSpeedU(p_auraTemplate->GetTextureScrollSpeedU());
	m_auraEntity->SetTextureScrollSpeedV(p_auraTemplate->GetTextureScrollSpeedV());

	m_innerAuraEntity->SetModel(
		p_innerAuraTemplate->GetModel(0),
		p_innerAuraTemplate->GetSceneNode(0),
		p_innerAuraTemplate->GetModelPart(0),
		p_innerAuraTemplate->GetModelDistance(0)
	);
	for (i = 1; i < 3; i++) {
		GolModelBase* model = p_innerAuraTemplate->GetModel(i);
		if (model != NULL) {
			LegoFloat modelDistance = p_innerAuraTemplate->GetModelDistance(i);
			CmbModelPart* modelPart = p_innerAuraTemplate->GetModelPart(i);
			m_innerAuraEntity->AddModel(model, p_innerAuraTemplate->GetSceneNode(i), modelPart, modelDistance);
		}
	}
	m_innerAuraEntity->SetFlags(m_innerAuraEntity->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_innerAuraEntity->PlayPart(0);
	m_innerAuraEntity->SetTextureScrollU(p_innerAuraTemplate->GetTextureScrollU());
	m_innerAuraEntity->SetTextureScrollV(p_innerAuraTemplate->GetTextureScrollV());
	m_innerAuraEntity->SetTextureScrollSpeedU(p_innerAuraTemplate->GetTextureScrollSpeedU());
	m_innerAuraEntity->SetTextureScrollSpeedV(p_innerAuraTemplate->GetTextureScrollSpeedV());

	if (m_ownerRacer == NULL) {
		GolVec3 position = p_target->m_position;
		GolVec3 direction = p_target->m_direction;

		GolWorldEntity* target = &m_worldEntity;
		target->SetPosition(position);
		m_worldEntity.SetBoundsRadius(g_curseTriggerRadius);
		m_auraEntity->SetPosition(position);
		m_innerAuraEntity->SetPosition(position);

		position.m_z += 13.0f;
		m_curseEntity->SetPosition(position);

		direction.m_x = -direction.m_x;
		direction.m_y = -direction.m_y;
		direction.m_z = -direction.m_z;

		GolVec3 up;
		up.m_x = 0.0f;
		up.m_y = 0.0f;
		up.m_z = 1.0f;

		GolVec3 forward;
		forward.m_x = -direction.m_y;
		forward.m_y = direction.m_x;
		forward.m_z = 0.0f;
		m_curseEntity->SetDirectionUp(forward, up);

		m_auraEntity->CopyOrientationFrom(*m_curseEntity);
		m_innerAuraEntity->CopyOrientationFrom(*m_curseEntity);
	}

	m_state = c_stateArmed;
	m_stateTimerMs = 0;
}

// FUNCTION: LEGORACERS 0x00452970
void CurseAction::Deactivate()
{
	if (m_innerAuraEntity != NULL) {
		m_innerAuraEntity->ResetModelState();
		m_manager->ReleaseEffectEntity(m_innerAuraEntity);
		m_innerAuraEntity = NULL;
	}

	if (m_auraEntity != NULL) {
		m_auraEntity->ResetModelState();
		m_manager->ReleaseEffectEntity(m_auraEntity);
		m_auraEntity = NULL;
	}

	if (m_curseEntity != NULL) {
		m_curseEntity->ResetModelState();
		m_manager->ReleaseEffectEntity(m_curseEntity);
		m_curseEntity = NULL;
	}

	if (m_sound != NULL) {
		m_soundSource->ReleaseSound(m_sound);
		m_sound = NULL;
	}

	if (m_collisionEvent != NULL) {
		m_collisionEvent->m_active = 0;
		m_collisionEvent = NULL;
	}

	m_ownerRacer = NULL;
	m_state = c_stateReady;
}

// FUNCTION: LEGORACERS 0x00452a00
void CurseAction::Update(LegoU32 p_elapsedMs)
{
	if (m_state == c_stateDone) {
		return;
	}

	PowerupAction::Update(p_elapsedMs);
	m_curseEntity->Update(p_elapsedMs);
	m_auraEntity->Update(p_elapsedMs);
	m_innerAuraEntity->Update(p_elapsedMs);
}

// FUNCTION: LEGORACERS 0x00452a40
void CurseAction::Draw(GolD3DRenderDevice* p_renderer)
{
	if (m_state == c_stateDone) {
		return;
	}

	if (m_state == c_stateFade) {
		m_curseEntity->SetScaleAndInvalidateRadius(static_cast<LegoS32>(m_stateTimerMs) * 0.001f);
	}

	p_renderer->DrawModelEntity(m_curseEntity);
}

// FUNCTION: LEGORACERS 0x00452a80
void CurseAction::DrawTransparent(GolD3DRenderDevice* p_renderer)
{
	if (m_state == c_stateDone) {
		return;
	}

	if (m_state == c_stateFade) {
		LegoFloat scale = static_cast<LegoS32>(m_stateTimerMs) * 0.001f;
		m_auraEntity->SetScaleAndInvalidateRadius(scale);
		m_innerAuraEntity->SetScaleThenInvalidateRadius(m_auraEntity->GetScale());
	}

	m_auraEntity->Draw(*p_renderer);
	m_innerAuraEntity->Draw(*p_renderer);
}

// FUNCTION: LEGORACERS 0x00452ae0
void CurseAction::AdvanceState()
{
	switch (m_state) {
	case c_stateArmed:
		break;
	case c_stateActive:
		m_state = c_stateFade;
		m_stateTimerMs = c_fadeDurationMs;
		return;
	case c_stateFade:
		m_state = c_stateDone;
		m_stateTimerMs = 0;
		return;
	default:
		return;
	}

	GolVec3 position;
	if (m_ownerRacer != NULL) {
		GolBoundingVolume::HitTriangle record;
		ComputeDropPosition(m_ownerRacer, &position, &record);

		GolVec3 direction;
		if (m_ownerRacer->m_checkpoint != NULL) {
			direction = m_ownerRacer->m_checkpoint->m_planeNormal;
		}
		else {
			direction.m_x = 1.0f;
			direction.m_y = 0.0f;
			direction.m_z = 0.0f;
		}

		m_worldEntity.SetPosition(position);
		m_worldEntity.SetBoundsRadius(g_curseTriggerRadius);
		m_auraEntity->SetPosition(position);
		m_innerAuraEntity->SetPosition(position);

		GolVec3 up = record.m_normal;
		position.m_x += up.m_x * 13.0f;
		position.m_y += up.m_y * 13.0f;
		position.m_z += up.m_z * 13.0f;
		m_curseEntity->SetPosition(position);

		GolVec3 cross;
		cross.m_x = up.m_y * direction.m_z - up.m_z * direction.m_y;
		cross.m_y = up.m_z * direction.m_x - direction.m_z * up.m_x;
		cross.m_z = direction.m_y * up.m_x - up.m_y * direction.m_x;
		m_curseEntity->SetDirectionUp(cross, up);

		m_auraEntity->CopyOrientationFrom(*m_curseEntity);
		m_innerAuraEntity->CopyOrientationFrom(*m_curseEntity);
	}
	else {
		m_worldEntity.GetPosition(&position);
		position.m_z += 13.0f;
	}

	m_sound = m_soundSource->AcquireSoundById(c_soundLoop);
	if (m_sound != NULL) {
		m_sound->Play(TRUE);
		m_sound->SetDistanceRangeWithMinSquared(
			g_curseSoundMinDistance * g_curseSoundMinDistance,
			g_curseSoundMaxDistanceSquared
		);
		m_sound->SetPosition(position);
	}

	m_state = c_stateActive;
	m_stateTimerMs = c_activeDurationMs;

	LegoEventQueue::Descriptor descriptor;
	descriptor.m_type = 4;
	descriptor.m_flags = 1;
	descriptor.m_maxFireCount = 0;
	descriptor.m_hitThreshold = 0;
	descriptor.m_worldEntity = &m_worldEntity;
	m_collisionEvent = m_raceState->GetEventQueue()->AllocateEvent(this, &descriptor);
}

// FUNCTION: LEGORACERS 0x00452da0
void CurseAction::OnHitRacer(Racer* p_racer)
{
	if (m_state != c_stateExpiring && !(p_racer->GetFlags() & c_flagCursed)) {
		p_racer->AttachCurse(m_curseEntity, c_curseDurationMs);
	}
}
