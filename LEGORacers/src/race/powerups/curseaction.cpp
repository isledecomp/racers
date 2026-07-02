#include "audio/soundnode.h"
#include "audio/spatialsoundinstance.h"
#include "camera/golcamera.h"
#include "cmbmodelpart0x34.h"
#include "decomp.h"
#include "golmodelbase.h"
#include "golscenenode.h"
#include "goltransformbase.h"
#include "material/materialtable0x0c.h"
#include "menu/runtime/cutsceneparticle.h"
#include "race/racesession.h"
#include "render/golcommondrawstate.h"
#include "render/gold3drenderdevice.h"
#include "world/golworlddatabase.h"

#include <float.h>
#include <math.h>

const LegoFloat g_curseTriggerRadius = 10.0f;

const LegoFloat g_curseSoundMaxDistanceSquared = 300.0f;

const LegoFloat g_curseSoundMinDistance = 30.0f;

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
	m_raceState0x018 = NULL;
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
	m_raceState0x018 = p_raceState;
	m_collisionWorld = p_collisionWorld;
	m_manager = p_manager;
	m_state = 1;
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
		m_state = 6;
		return;
	}

	m_auraEntity = m_manager->AllocateEffectEntity();
	if (m_auraEntity == NULL) {
		m_state = 6;
		return;
	}

	m_innerAuraEntity = m_manager->AllocateEffectEntity();
	if (m_innerAuraEntity == NULL) {
		m_state = 6;
		return;
	}

	m_ownerRacer = p_racer;

	m_curseEntity->SetModel(
		p_curseTemplate->GetModel(0),
		p_curseTemplate->VTable0x58(0),
		p_curseTemplate->GetModelPart(0),
		p_curseTemplate->GetModelDistance(0)
	);

	LegoU32 i;
	for (i = 1; i < 3; i++) {
		GolModelBase* model = p_curseTemplate->GetModel(i);
		if (model != NULL) {
			LegoFloat modelDistance = p_curseTemplate->GetModelDistance(i);
			CmbModelPart0x34* modelPart = p_curseTemplate->GetModelPart(i);
			m_curseEntity->AddModel(model, p_curseTemplate->VTable0x58(i), modelPart, modelDistance);
		}
	}
	m_curseEntity->SetFlags(m_curseEntity->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_curseEntity->PlayPart(0);

	m_auraEntity->SetModel(
		p_auraTemplate->GetModel(0),
		p_auraTemplate->VTable0x58(0),
		p_auraTemplate->GetModelPart(0),
		p_auraTemplate->GetModelDistance(0)
	);
	for (i = 1; i < 3; i++) {
		GolModelBase* model = p_auraTemplate->GetModel(i);
		if (model != NULL) {
			LegoFloat modelDistance = p_auraTemplate->GetModelDistance(i);
			CmbModelPart0x34* modelPart = p_auraTemplate->GetModelPart(i);
			m_auraEntity->AddModel(model, p_auraTemplate->VTable0x58(i), modelPart, modelDistance);
		}
	}
	m_auraEntity->SetFlags(m_auraEntity->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_auraEntity->PlayPart(0);
	m_auraEntity->FUN_00411680(p_auraTemplate->FUN_00411640());
	m_auraEntity->FUN_004116b0(p_auraTemplate->FUN_00411660());
	m_auraEntity->FUN_00411700(p_auraTemplate->FUN_004116e0());
	m_auraEntity->FUN_00411730(p_auraTemplate->FUN_004116f0());

	m_innerAuraEntity->SetModel(
		p_innerAuraTemplate->GetModel(0),
		p_innerAuraTemplate->VTable0x58(0),
		p_innerAuraTemplate->GetModelPart(0),
		p_innerAuraTemplate->GetModelDistance(0)
	);
	for (i = 1; i < 3; i++) {
		GolModelBase* model = p_innerAuraTemplate->GetModel(i);
		if (model != NULL) {
			LegoFloat modelDistance = p_innerAuraTemplate->GetModelDistance(i);
			CmbModelPart0x34* modelPart = p_innerAuraTemplate->GetModelPart(i);
			m_innerAuraEntity->AddModel(model, p_innerAuraTemplate->VTable0x58(i), modelPart, modelDistance);
		}
	}
	m_innerAuraEntity->SetFlags(m_innerAuraEntity->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_innerAuraEntity->PlayPart(0);
	m_innerAuraEntity->FUN_00411680(p_innerAuraTemplate->FUN_00411640());
	m_innerAuraEntity->FUN_004116b0(p_innerAuraTemplate->FUN_00411660());
	m_innerAuraEntity->FUN_00411700(p_innerAuraTemplate->FUN_004116e0());
	m_innerAuraEntity->FUN_00411730(p_innerAuraTemplate->FUN_004116f0());

	if (m_ownerRacer == NULL) {
		GolVec3 position = p_target->m_position;
		GolVec3 direction = p_target->m_direction;

		GolWorldEntity* target = &m_worldEntity;
		target->VTable0x08(position);
		m_worldEntity.FUN_10026fa0(10.0f);
		m_auraEntity->VTable0x08(position);
		m_innerAuraEntity->VTable0x08(position);

		position.m_z += 13.0f;
		m_curseEntity->VTable0x08(position);

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
		m_curseEntity->VTable0x40(forward, up);

		m_auraEntity->CopyOrientationFrom(*m_curseEntity);
		m_innerAuraEntity->CopyOrientationFrom(*m_curseEntity);
	}

	m_state = 2;
	m_stateTimerMs = 0;
}

// FUNCTION: LEGORACERS 0x00452970
void CurseAction::Deactivate()
{
	if (m_innerAuraEntity != NULL) {
		m_innerAuraEntity->VTable0x54();
		m_manager->ReleaseEffectEntity(m_innerAuraEntity);
		m_innerAuraEntity = NULL;
	}

	if (m_auraEntity != NULL) {
		m_auraEntity->VTable0x54();
		m_manager->ReleaseEffectEntity(m_auraEntity);
		m_auraEntity = NULL;
	}

	if (m_curseEntity != NULL) {
		m_curseEntity->VTable0x54();
		m_manager->ReleaseEffectEntity(m_curseEntity);
		m_curseEntity = NULL;
	}

	if (m_sound != NULL) {
		m_soundSource->ReleaseSound(m_soundResource);
		m_sound = NULL;
	}

	if (m_collisionEvent != NULL) {
		m_collisionEvent->m_active = 0;
		m_collisionEvent = NULL;
	}

	m_ownerRacer = NULL;
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x00452a00
void CurseAction::Update(LegoU32 p_elapsedMs)
{
	if (m_state == c_stateDone) {
		return;
	}

	PowerupActionBase::Update(p_elapsedMs);
	m_curseEntity->VTable0x10(p_elapsedMs);
	m_auraEntity->VTable0x10(p_elapsedMs);
	m_innerAuraEntity->VTable0x10(p_elapsedMs);
}

// FUNCTION: LEGORACERS 0x00452a40
void CurseAction::Draw(GolD3DRenderDevice* p_renderer)
{
	if (m_state == c_stateDone) {
		return;
	}

	if (m_state == c_stateFade) {
		m_curseEntity->SetUnk0x58AndInvalidateRadius(static_cast<LegoS32>(m_stateTimerMs) * 0.001f);
	}

	p_renderer->VTable0x94(m_curseEntity);
}

// FUNCTION: LEGORACERS 0x00452a80
void CurseAction::DrawTransparent(GolD3DRenderDevice* p_renderer)
{
	if (m_state == c_stateDone) {
		return;
	}

	if (m_state == c_stateFade) {
		LegoFloat scale = static_cast<LegoS32>(m_stateTimerMs) * 0.001f;
		m_auraEntity->SetUnk0x58AndInvalidateRadius(scale);
		m_innerAuraEntity->SetUnk0x58ThenInvalidateRadius(m_auraEntity->GetUnk0x58());
	}

	m_auraEntity->VTable0x1c(*p_renderer);
	m_innerAuraEntity->VTable0x1c(*p_renderer);
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
		GolBoundingVolume::Field0x0c record;
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

		m_worldEntity.VTable0x08(position);
		m_worldEntity.FUN_10026fa0(g_curseTriggerRadius);
		m_auraEntity->VTable0x08(position);
		m_innerAuraEntity->VTable0x08(position);

		GolVec3 up = record.m_normal;
		position.m_x += up.m_x * 13.0f;
		position.m_y += up.m_y * 13.0f;
		position.m_z += up.m_z * 13.0f;
		m_curseEntity->VTable0x08(position);

		GolVec3 cross;
		cross.m_x = up.m_y * direction.m_z - up.m_z * direction.m_y;
		cross.m_y = up.m_z * direction.m_x - direction.m_z * up.m_x;
		cross.m_z = direction.m_y * up.m_x - up.m_y * direction.m_x;
		m_curseEntity->VTable0x40(cross, up);

		m_auraEntity->CopyOrientationFrom(*m_curseEntity);
		m_innerAuraEntity->CopyOrientationFrom(*m_curseEntity);
	}
	else {
		m_worldEntity.VTable0x04(&position);
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
	m_collisionEvent = m_raceState0x018->GetEventQueue()->AllocateEvent(this, &descriptor);
}

// FUNCTION: LEGORACERS 0x00452da0
void CurseAction::OnHitRacer(Racer* p_racer)
{
	if (m_state != c_stateExpiring && !(p_racer->GetFlags() & c_flagCursed)) {
		p_racer->AttachCurse(m_curseEntity, c_curseDurationMs);
	}
}

// FUNCTION: LEGORACERS 0x004584b0
PowerupAction* CurseAction::Destroy(undefined4 p_flags)
{
	CurseAction* result = this;
	if (p_flags & 2) {
		if (p_flags & 1) {
			delete[] this;
		}

		return result;
	}

	this->~CurseAction();
	if (p_flags & 1) {
		::operator delete(result);
	}

	return result;
}
