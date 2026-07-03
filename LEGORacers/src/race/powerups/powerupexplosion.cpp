#include "decomp.h"
#include "race/racesession.h"
#include "render/golcommondrawstate.h"
#include "render/gold3drenderdevice.h"

DECOMP_SIZE_ASSERT(PowerupExplosion, 0x270)

// GLOBAL: LEGORACERS 0x004b0150
LegoFloat g_explosionImpulseScale = 80.0f;

// GLOBAL: LEGORACERS 0x004b0154
LegoFloat g_explosionLaunchImpulse = 200.0f;

// GLOBAL: LEGORACERS 0x004b015c
LegoFloat g_explosionScarAlpha = 180.0f;

extern const LegoFloat g_violetShoalTwo;
extern const LegoFloat g_unk0x004b0544;
extern const LegoFloat g_homingProjectileCollisionStartOffset;

// FUNCTION: LEGORACERS 0x004210b0
PowerupExplosion::PowerupExplosion()
{
	m_materialTable.Reset();
	m_state = c_stateUninitialized;
	m_golExport = NULL;
	m_billboard = NULL;
	m_collidable = NULL;
	m_flashMaterial = NULL;
	m_scarMaterial = NULL;
	m_eventQueue = NULL;
	m_ownerRacer = 0;
	m_collisionEvent = NULL;
	m_manager = NULL;
	m_particleAnimation = 0;
	m_flashDurationMs = 0;
	m_scarDurationMs = 0;
	m_alpha = 0.0f;
	m_modelAlpha = 0.0f;
	m_remainingMs = 0;
	m_alphaRate = 100.0f;
	m_modelScale = 1.0f;
	m_flashWidth = 1.0f;
	m_flashHeight = 1.0f;
	m_blastRadius = 1.0f;
	m_next = NULL;
	m_leavesScar = 0;
	m_blastMode = 0;
	m_growth = g_unk0x004b0544;
	m_growthRate = 0.0f;
	m_initialGrowthRate = 0.0f;
	m_growthAcceleration = 0.0f;
}

// FUNCTION: LEGORACERS 0x004211e0
PowerupExplosion::~PowerupExplosion()
{
	Destroy();
	m_materialTable.Destroy();
}

// FUNCTION: LEGORACERS 0x00421250
void PowerupExplosion::Initialize(const Params* p_params)
{
	if (m_state != c_stateUninitialized) {
		Destroy();
	}

	m_golExport = p_params->m_golExport;
	m_collidable = p_params->m_collidable;
	m_flashMaterial = p_params->m_flashMaterial;
	m_scarMaterial = p_params->m_scarMaterial;
	m_eventQueue = p_params->m_eventQueue;
	m_manager = p_params->m_manager;
	m_particleAnimation = p_params->m_particleAnimation;
	m_billboardMaterialIndex = p_params->m_billboardMaterialIndex;
	m_flashDurationMs = p_params->m_flashDurationMs;
	m_scarDurationMs = p_params->m_scarDurationMs;
	m_modelScale = p_params->m_modelScale;
	m_flashWidth = p_params->m_flashWidth;
	m_flashHeight = p_params->m_flashHeight;
	m_blastRadius = p_params->m_blastRadius;
	m_blastMode = p_params->m_blastMode;

	LegoFloat rate = 1.0f / (static_cast<LegoFloat>(static_cast<LegoS32>(m_flashDurationMs)) * 0.001f);
	m_initialGrowthRate = rate + rate;
	LegoFloat rateDelta = (1.0f - 0.050000001f) - m_initialGrowthRate;
	m_growthAcceleration = (rateDelta + rateDelta) * (rate * rate);

	LegoFloat endRate =
		g_explosionScarAlpha / (static_cast<LegoFloat>(static_cast<LegoS32>(m_scarDurationMs)) * 0.001f);
	m_remainingMs = 0;
	m_alphaRate = -endRate;

	if (p_params->m_billboardMaterial != NULL || p_params->m_billboardAnimation != NULL) {
		m_billboard = static_cast<GolBillboard*>(m_golExport->CreateBillboard());
	}

	if (p_params->m_billboardAnimation != NULL) {
		m_billboardAnimation.ConfigureFrom(*p_params->m_billboardAnimation);
		m_billboardAnimation.Assign(m_manager->GetBillboardMaterialTable(), m_billboardMaterialIndex, FALSE);
		m_billboardAnimation
			.Update(0, m_manager->GetMaterialAnimationItems(), m_manager->GetMaterialAnimationItemCount());
		m_billboard->ConfigureFromMaterialTable(
			m_manager->GetBillboardMaterialTable(),
			m_billboardMaterialIndex,
			0.1f,
			0.2f,
			250000.0f
		);
	}
	else if (m_billboard != NULL) {
		m_billboard->Configure(p_params->m_billboardMaterial, 0.1f, 0.2f, 250000.0f);
	}

	if (p_params->m_model != NULL) {
		m_modelEntity.SetPrimaryModel(p_params->m_model->GetModel(0), 250000.0f);
		m_modelEntity.SetTextureScrollU(p_params->m_model->GetTextureScrollU());
		m_modelEntity.SetTextureScrollV(p_params->m_model->GetTextureScrollV());
		m_modelEntity.SetTextureScrollSpeedU(p_params->m_model->GetTextureScrollSpeedU());
		m_modelEntity.SetTextureScrollSpeedV(p_params->m_model->GetTextureScrollSpeedV());
	}

	GolD3DRenderDevice* renderer = m_golExport->GetDrawState()->m_currentRenderer;
	m_materialTable.Initialize(renderer, 1);
	m_scarDecal.Initialize(m_golExport, renderer, 10);
	m_scarDecal.GetEntity().SetPrimaryMaterialTable(&m_materialTable);
	m_state = c_stateIdle;
}

// FUNCTION: LEGORACERS 0x004214b0
void PowerupExplosion::Destroy()
{
	Deactivate();
	m_scarDecal.Destroy();
	m_materialTable.Clear();
	m_modelEntity.ResetModelState();

	if (m_golExport != NULL && m_billboard != NULL) {
		m_billboard->SetPrimaryModel();
		m_golExport->DestroyBillboard(m_billboard);
		m_billboard = NULL;
	}

	m_billboardAnimation.Reset();
	m_state = c_stateUninitialized;
}

// STUB: LEGORACERS 0x00421520
void PowerupExplosion::Spawn(const GolVec3* p_position, undefined4 p_leavesScar, Racer* p_racer)
{
	LegoFloat negativeLimit = -2048.0f;
	if (p_position->m_x > 2048.0f || p_position->m_x < negativeLimit || p_position->m_y > 2048.0f ||
		p_position->m_y < negativeLimit || p_position->m_z > 2048.0f || p_position->m_z < negativeLimit) {
		m_state = c_stateIdle;
		return;
	}

	m_state = c_stateExploding;
	m_remainingMs = m_flashDurationMs;
	m_leavesScar = p_leavesScar;
	m_ownerRacer = p_racer;
	m_alpha = 255.0f;
	m_modelAlpha = 0.0f;
	m_growth = 0.050000001f;
	m_growthRate = m_initialGrowthRate;

	m_worldEntity.SetPosition(*p_position);
	m_worldEntity.SetBoundsRadius(0.1f);

	if (m_billboard != NULL) {
		m_billboard->SetWidth(0.1f);
		m_billboard->SetHeight(0.2f);
		m_billboard->SetPosition(*p_position);
	}

	if (m_modelEntity.HasModel()) {
		m_modelEntity.SetScaleThenInvalidateRadius(0.050000001f);
		m_modelEntity.SetPosition(*p_position);
	}

	GolVec3 position;
	position.m_x = p_position->m_x;
	position.m_y = p_position->m_y;
	position.m_z = p_position->m_z + g_homingProjectileCollisionStartOffset;
	m_scarDecal.m_center = position;

	GolVec3 forward;
	forward.m_x = 0.0f;
	forward.m_y = 0.0f;
	forward.m_z = -1.0f;

	GolVec3 up;
	up.m_x = 1.0f;
	up.m_y = 0.0f;
	up.m_z = 0.0f;
	m_scarDecal.SetOrientation(&forward, &up);

	if (m_collisionEvent != NULL) {
		m_collisionEvent->m_active = 0;
	}

	if (m_eventQueue != NULL) {
		LegoEventQueue::Callback* callback = this;
		LegoEventQueue::Descriptor descriptor;
		descriptor.m_type = 4;
		descriptor.m_flags = 1;
		descriptor.m_maxFireCount = 0;
		descriptor.m_hitThreshold = 0;
		descriptor.m_data = &m_worldEntity;
		m_collisionEvent = m_eventQueue->AllocateEvent(callback, &descriptor);
	}
	else {
		m_collisionEvent = NULL;
	}

	if (m_billboardAnimation.IsConfigured()) {
		m_billboardAnimation.Unassign();
		m_billboardAnimation.Rewind();
		m_billboardAnimation.Assign(m_manager->GetBillboardMaterialTable(), m_billboardMaterialIndex, FALSE);
	}

	if (m_particleAnimation != NULL) {
		GolVec3 particlePosition;
		particlePosition.m_x = position.m_x;
		particlePosition.m_y = position.m_y;
		particlePosition.m_z = position.m_z - g_homingProjectileCollisionStartOffset;
		m_particleAnimation->SpawnParticle("explode", &particlePosition, NULL, NULL);
	}
}

// FUNCTION: LEGORACERS 0x004217b0
void PowerupExplosion::Deactivate()
{
	if (m_collisionEvent != NULL) {
		m_collisionEvent->m_active = 0;
		m_collisionEvent = NULL;
	}

	m_state = c_stateIdle;
}

// FUNCTION: LEGORACERS 0x004217d0
void PowerupExplosion::Update(LegoU32 p_elapsedMs)
{
	if (m_state == c_stateExploding) {
		UpdateFlash(p_elapsedMs);
	}

	if (m_state == c_stateScarFading) {
		LegoFloat elapsedSeconds = static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs)) * 0.001f;
		m_alpha += elapsedSeconds * m_alphaRate;
		if (m_alpha < 0.0f) {
			m_alpha = 0.0f;
		}

		LegoU32 duration = m_remainingMs;
		if (p_elapsedMs >= duration) {
			m_remainingMs = 0;
			Deactivate();
		}
		else {
			m_remainingMs = duration - p_elapsedMs;
		}
	}
}

// FUNCTION: LEGORACERS 0x00421850
void PowerupExplosion::UpdateFlash(LegoU32 p_elapsedMs)
{
	LegoS32 zero = 0;
	if (m_state != zero && m_state != c_stateIdle) {
		LegoU32 duration = m_remainingMs;
		if (p_elapsedMs >= duration) {
			if (m_scarMaterial != NULL && m_leavesScar != zero) {
				if (m_collisionEvent != NULL) {
					m_collisionEvent->m_active = 0;
					m_collisionEvent = NULL;
				}

				LegoU32 finishDuration = m_scarDurationMs;
				m_state = c_stateScarFading;
				LegoFloat width = m_flashWidth;
				LegoFloat width2 = m_flashWidth;
				m_remainingMs = finishDuration;
				m_alpha = g_explosionScarAlpha;
				m_scarDecal.m_width = width;
				m_scarDecal.m_length = width2;
				m_scarDecal.m_depth = 15.0f;
				m_scarDecal.Project(m_collidable);
			}
			else {
				Deactivate();
			}

			return;
		}

		m_remainingMs = duration - p_elapsedMs;

		LegoFloat elapsedSeconds = static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs)) * 0.001f;
		LegoFloat acceleration = m_growthAcceleration;
		m_growthRate = acceleration * elapsedSeconds + m_growthRate;
		m_growth = elapsedSeconds * m_growthRate + m_growth;

		LegoFloat radius = (m_blastRadius - 0.1f) * m_growth + 0.1f;
		m_worldEntity.SetBoundsRadius(radius);

		LegoFloat width = (m_flashWidth - 0.1f) * m_growth + 0.1f;
		if (m_scarMaterial != NULL && m_leavesScar != zero) {
			m_materialTable.SetEntry(0, m_scarMaterial);
			m_scarDecal.m_width = width;
			m_scarDecal.m_length = width;
			m_scarDecal.m_depth = 15.0f;
			m_scarDecal.Project(m_collidable);
		}

		if (m_billboard != NULL) {
			m_billboard->SetWidth(width);
			m_billboard->SetHeight((m_flashHeight - 0.2f) * m_growth + 0.2f);
		}

		LegoFloat value = (m_modelScale - 0.050000001f) * m_growth + 0.050000001f;
		if (value > 1.0f) {
			value = 1.0f;
		}

		if (m_modelEntity.HasModel()) {
			m_modelEntity.SetScaleThenInvalidateRadius(value);
		}

		m_alpha = (g_violetShoalTwo - (m_growth + m_growth)) * 255.0f;
		if (m_alpha < 0.0f) {
			m_alpha = 0.0f;
		}
		else if (m_alpha > 255.0f) {
			m_alpha = 255.0f;
		}

		m_modelAlpha = (1.0f - m_growth) * 255.0f;
		if (m_modelAlpha < 0.0f) {
			m_modelAlpha = 0.0f;
		}

		if (m_billboardAnimation.IsConfigured()) {
			m_billboardAnimation.Update(
				p_elapsedMs,
				m_manager->GetMaterialAnimationItems(),
				m_manager->GetMaterialAnimationItemCount()
			);
		}
	}
}

// FUNCTION: LEGORACERS 0x00421ae0
void PowerupExplosion::DrawTransparent(GolD3DRenderDevice* p_renderer)
{
	if (m_state == c_stateUninitialized || m_state == c_stateIdle) {
		return;
	}

	if (m_state == c_stateExploding) {
		if (m_scarMaterial != 0 && m_leavesScar != 0) {
			p_renderer->SetAlphaOverride(static_cast<LegoS32>(g_explosionScarAlpha), 2);
			m_scarDecal.Draw(p_renderer);
		}

		p_renderer->SetAlphaOverride(static_cast<LegoS32>(m_alpha), 1);

		if (m_billboard != NULL) {
			p_renderer->DrawBillboard(*m_billboard);
		}

		if (m_modelEntity.HasModel()) {
			p_renderer->SetAlphaOverride(static_cast<LegoS32>(m_modelAlpha), 1);
			m_modelEntity.Draw(*p_renderer);
		}

		p_renderer->ClearAlphaOverride();
		return;
	}

	if (m_state == c_stateScarFading && m_scarMaterial != 0 && m_leavesScar != 0) {
		p_renderer->SetAlphaOverride(static_cast<LegoS32>(m_alpha), 2);
		m_scarDecal.Draw(p_renderer);
		p_renderer->ClearAlphaOverride();
	}
}

// STUB: LEGORACERS 0x00421c00
void PowerupExplosion::OnEvent(LegoEventQueue::CallbackData* p_data)
{
	LegoU32 mode = m_blastMode;
	if (!mode) {
		return;
	}

	Racer* racer = static_cast<Racer*>(p_data->m_data);
	if (racer == m_ownerRacer) {
		return;
	}

	LegoU8 racerFlags = static_cast<LegoU8>(racer->m_flags);
	RacerPhysics* physics = &racer->m_physics;
	if (racerFlags & Racer::c_flagShielded) {
		return;
	}

	mode--;
	if (mode) {
		if (--mode) {
			return;
		}

		if ((racer->m_physics.m_flags & RacerPhysics::c_flagSpinOut) && racer->m_controlMode != Racer::c_controlAi) {
			return;
		}

		GolVec3 direction = physics->m_facingDirection;
		racer->StartSpinOut();

		GolVec3 impulse;
		impulse.m_x = 0.0f;
		impulse.m_y = 0.0f;
		impulse.m_z = 0.0f;
		physics->m_velocity = impulse;

		LegoFloat amount;
		LegoS32 duration = static_cast<LegoS32>(m_flashDurationMs);
		if (duration) {
			LegoFloat remaining = static_cast<LegoFloat>(static_cast<LegoS32>(m_remainingMs));
			LegoFloat durationFloat = static_cast<LegoFloat>(duration);
			amount = remaining / durationFloat;
			amount += amount;

			if (amount > 1.0f) {
				amount = 1.0f;
			}
			else if (amount < 0.0f) {
				amount = 0.0f;
			}
		}
		else {
			amount = 1.0f;
		}

		LegoFloat scale = amount * g_explosionImpulseScale;
		impulse.m_x = direction.m_x * scale;
		impulse.m_y = direction.m_y * scale;
		impulse.m_z = direction.m_z * scale;
		impulse.m_z += amount * g_explosionLaunchImpulse;

		physics->ApplyImpulse(&impulse, &impulse);
		return;
	}

	if (!(physics->m_flags & RacerPhysics::c_flagSpinning)) {
		physics->StartSpin(2.0f, 0.007f, 0);
	}
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void PowerupExplosion::Draw(GolD3DRenderDevice*)
{
}
