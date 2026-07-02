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

// GLOBAL: LEGORACERS 0x004b14dc
extern const LegoFloat g_hookBillboardDrawDistance = FLT_MAX;

// GLOBAL: LEGORACERS 0x004b1508
extern const LegoFloat g_hookBillboardSize = 15.0f;

// GLOBAL: LEGORACERS 0x004b14e0
const LegoFloat g_hookSoundMinDistance = 30.0f;

// GLOBAL: LEGORACERS 0x004b14e4
const LegoFloat g_hookSoundMaxDistance = 300.0f;

// GLOBAL: LEGORACERS 0x004b14e8
const LegoFloat g_hookRopeWaveAmplitude = 4.0f;

// GLOBAL: LEGORACERS 0x004b14ec
const LegoFloat g_hookPullForce = 180.0f;

// GLOBAL: LEGORACERS 0x004b14f0
const LegoFloat g_hookGravity = -90.1760025f;

// GLOBAL: LEGORACERS 0x004b14f4
const LegoFloat g_hookSpeed = 320.0f;

// GLOBAL: LEGORACERS 0x004b150c
const LegoFloat g_hookLaunchHeight = 5.0f;

// GLOBAL: LEGORACERS 0x004b1510
const LegoFloat g_hookReleaseDistanceSquared = 144.0f;

// GLOBAL: LEGORACERS 0x004b1514
const LegoFloat g_hookRopeThickness = 0.6f;

// GLOBAL: LEGORACERS 0x004c1c50
ColorRGBA g_hookRopeBaseColor = {0x64, 0x3c, 0x0e, 0xff};

// GLOBAL: LEGORACERS 0x004c1c54
ColorRGBA g_hookRopeSecondaryColor = {0x8f, 0x5a, 0x1c, 0xff};

// GLOBAL: LEGORACERS 0x004c1c58
ColorRGBA g_hookRopeTertiaryColor = {0x14, 0x14, 0x00, 0xff};

// FUNCTION: LEGORACERS 0x00453bf0
RacePowerupManager::GrapplingHookAction::GrapplingHookAction()
{
	m_activeProjectile = 0;
	m_activeProjectile = &m_projectile;
	m_hookEntity = 0;
	m_smokeParticleRef = 0;
	m_billboard = NULL;
	m_billboardMaterialIndex = 0;
}

// FUNCTION: LEGORACERS 0x00453c70
RacePowerupManager::GrapplingHookAction::~GrapplingHookAction()
{
	Shutdown();
}

// FUNCTION: LEGORACERS 0x00453cd0
void RacePowerupManager::GrapplingHookAction::Initialize(
	RacePowerupManager* p_manager,
	RaceSessionField0x32b4* p_collisionWorld,
	undefined4 p_billboardMaterialIndex
)
{
	if (m_state != 0) {
		Shutdown();
	}

	m_owner0x01c = p_manager;
	m_collisionWorld = p_collisionWorld;
	m_hookEntity = 0;
	m_smokeParticleRef = 0;
	m_billboardMaterialIndex = p_billboardMaterialIndex;

	TetherProjectile::SetupParams params;
	params.m_golExport = p_manager->m_golExport;
	params.m_ropeThickness = g_hookRopeThickness;
	params.m_waveAmplitude = g_hookRopeWaveAmplitude;
	params.m_baseColor = g_hookRopeBaseColor;
	params.m_attachHeight = 3.0f;
	params.m_secondaryColor = g_hookRopeSecondaryColor;
	params.m_tertiaryColor = g_hookRopeTertiaryColor;
	params.m_material = p_manager->m_renderer->FindMaterialByName("tether");
	m_projectile.Initialize(&params);

	m_state = 1;
	m_billboard = static_cast<GolBillboard*>(params.m_golExport->VTable0x30());
}

// FUNCTION: LEGORACERS 0x00453d90
void RacePowerupManager::GrapplingHookAction::Shutdown()
{
	Deactivate();

	if (m_owner0x01c != NULL && m_billboard != NULL) {
		m_owner0x01c->m_golExport->VTable0x64(m_billboard);
		m_billboard = NULL;
		m_owner0x01c = NULL;
	}

	m_projectile.Deactivate();
	m_state = 0;
}

// FUNCTION: LEGORACERS 0x00453de0
LegoU32 RacePowerupManager::GrapplingHookAction::Activate(
	GolModelEntity* p_hookEntity,
	RaceState::Racer* p_racer,
	RaceState::Racer* p_targetRacer,
	TargetPointList::Entry* p_targetPoint,
	MabMaterialAnimationItem0x18* p_billboardAnimation,
	LegoU32 p_delayMs
)
{
	m_hookEntity = p_hookEntity;
	m_ownerRacer = p_racer;
	m_targetRacer = p_targetRacer;
	m_state = c_stateArmed;
	m_targetPoint = p_targetPoint;
	m_stateTimerMs = p_delayMs;

	m_billboardAnimation.FUN_004103c0(*p_billboardAnimation);
	m_billboardAnimation.FUN_00410470();
	m_billboardAnimation.FUN_00410480();
	m_billboardAnimation.FUN_10025da0(m_owner0x01c->GetBillboardMaterialTable(), m_billboardMaterialIndex, FALSE);
	m_billboardAnimation
		.FUN_004104c0(0, m_owner0x01c->GetMaterialAnimationItems(), m_owner0x01c->GetMaterialAnimationItemCount());

	return m_billboard->FUN_10029e90(
		m_owner0x01c->GetBillboardMaterialTable(),
		m_billboardMaterialIndex,
		g_hookBillboardSize,
		g_hookBillboardSize,
		g_hookBillboardDrawDistance
	);
}

// FUNCTION: LEGORACERS 0x00453e90
void RacePowerupManager::GrapplingHookAction::Deactivate()
{
	m_projectile.CancelCollisionEvent();

	if (m_smokeParticleRef != NULL) {
		m_owner0x01c->m_cutsceneAnimation->FUN_00489f00(m_smokeParticleRef);
		m_smokeParticleRef = NULL;
	}

	m_billboardAnimation.Reset();

	if (m_billboard != NULL) {
		m_billboard->VTable0x50();
	}

	m_ownerRacer = NULL;
	m_targetRacer = 0;
	m_targetPoint = 0;
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x00453ef0
void RacePowerupManager::GrapplingHookAction::Update(LegoU32 p_elapsedMs)
{
	GolVec3 direction;
	SoundVector targetPosition;
	SoundVector position;
	GolVec3 forward;
	SoundVector projectilePositionCopy;
	GolVec3 up;
	GolVec3 velocity;

	if (m_state == c_stateDone) {
		return;
	}

	LegoS32 projectileState = 0;
	if (p_elapsedMs >= m_stateTimerMs) {
		p_elapsedMs -= m_stateTimerMs;
		m_stateTimerMs = projectileState;
		AdvanceState();
	}
	else {
		m_stateTimerMs -= p_elapsedMs;
	}

	if (m_state == c_stateArmed) {
		return;
	}

	projectileState = m_projectile.Update(p_elapsedMs);
	if (projectileState != PowerupProjectile::c_stateFlying) {
		if (projectileState == PowerupProjectile::c_stateHitRacer) {
			OnHitRacer(m_projectile.GetHitRacer());
		}
	}

	switch (m_state) {
	case c_stateFlying: {
		if (projectileState == PowerupProjectile::c_stateHitWorld) {
			GolVec3& projectilePositionCopyBase = projectilePositionCopy;
			projectilePositionCopyBase = m_projectile.GetHitPosition();
			ReleaseHook(&projectilePositionCopy);
		}
		else {
			m_ownerRacer->m_unk0x3e8.m_unk0x13c->VTable0x04(&position);

			up.m_x = 0.0f;
			up.m_y = 0.0f;
			up.m_z = 1.0f;

			const GolVec3* target = &m_projectile.GetTargetPosition();
			GolVec3& targetPositionBase = targetPosition;
			targetPositionBase = *target;
			forward.m_x = targetPosition.m_x - position.m_x;
			forward.m_y = targetPosition.m_y - position.m_y;
			forward.m_z = targetPosition.m_z - position.m_z;
			m_hookEntity->VTable0x40(forward, up);
		}

		break;
	}
	case c_statePulling:
		if (projectileState == PowerupProjectile::c_stateHitWorld) {
			GolVec3& projectilePositionCopyBase = projectilePositionCopy;
			projectilePositionCopyBase = m_projectile.GetHitPosition();
			ReleaseHook(&projectilePositionCopy);
		}
		else {
			RaceState::Racer::Field0x018* racerField = &m_ownerRacer->m_unk0x018;
			racerField->m_unk0x044->VTable0x04(&position);

			RaceState::Racer* targetRacer = m_projectile.GetHitRacer();
			targetRacer->m_unk0x018.m_unk0x044->VTable0x04(&targetPosition);

			if (targetRacer->m_unk0xd04 & c_racerFlags0xd04Bit0) {
				ReleaseHook(&targetPosition);
				return;
			}

			direction.m_x = targetPosition.m_x - position.m_x;
			direction.m_y = targetPosition.m_y - position.m_y;
			direction.m_z = targetPosition.m_z - position.m_z;

			LegoFloat distanceSquared = direction.m_y * direction.m_y;
			distanceSquared += direction.m_z * direction.m_z;
			distanceSquared += direction.m_x * direction.m_x;
			if (distanceSquared < g_hookReleaseDistanceSquared) {
				ReleaseHook(&targetPosition);
				break;
			}

			m_ownerRacer->m_unk0x018.m_unk0x044->GetOrientationRow0(&forward);

			LegoFloat dot = direction.m_z;
			dot *= forward.m_z;
			dot += direction.m_y * forward.m_y;
			dot += direction.m_x * forward.m_x;
			if (dot < 0.0f) {
				ReleaseHook(&targetPosition);
				break;
			}

			GolMath::NormalizeVector3(direction, &direction);
			direction.m_x *= g_hookPullForce;
			direction.m_y *= g_hookPullForce;
			direction.m_z *= g_hookPullForce;
			m_ownerRacer->m_unk0x3e8.VTable0x48(&direction);

			direction.m_x = -direction.m_x;
			direction.m_y = -direction.m_y;
			direction.m_z = -direction.m_z;
			targetRacer->m_unk0x3e8.VTable0x40(&direction);
		}
		break;
	case c_stateRetracting:
		if (m_billboardAnimation.IsAssigned()) {
			m_billboardAnimation.FUN_004104c0(
				p_elapsedMs,
				m_owner0x01c->GetMaterialAnimationItems(),
				m_owner0x01c->GetMaterialAnimationItemCount()
			);
			m_billboard->VTable0x10(p_elapsedMs);
		}

		if (projectileState == PowerupProjectile::c_stateExpired) {
			m_state = c_stateDone;
			m_stateTimerMs = 0;
		}
		break;
	}

	if (m_smokeParticleRef != NULL) {
		CutsceneParticle* particle = m_smokeParticleRef->m_particle;
		if (particle == NULL || particle->GetSpawnedCount() >= 3) {
			m_owner0x01c->m_cutsceneAnimation->FUN_00489f30(m_smokeParticleRef);
			m_smokeParticleRef = NULL;
			return;
		}

		m_ownerRacer->m_unk0x3e8.m_unk0x13c->VTable0x04(&position);
		position.m_z += 4.0f;

		velocity = m_ownerRacer->m_unk0x3e8.m_unk0x008;
		if (m_smokeParticleRef->m_particle != NULL) {
			m_ownerRacer->m_unk0x3e8.m_unk0x13c->VTable0x44(m_smokeParticleRef->m_particle->GetUnk0x160());
		}
		if (m_smokeParticleRef->m_particle != NULL) {
			m_smokeParticleRef->m_particle->FUN_00489660(&position);
		}
		if (m_smokeParticleRef->m_particle != NULL) {
			m_smokeParticleRef->m_particle->FUN_00489690(&velocity);
		}
	}
}

// FUNCTION: LEGORACERS 0x004542d0
void RacePowerupManager::GrapplingHookAction::Draw(GolD3DRenderDevice* p_renderer)
{
	switch (m_state) {
	case c_stateFlying:
		p_renderer->VTable0x94(m_hookEntity);
		m_projectile.Draw(p_renderer);
		break;
	case c_statePulling:
		p_renderer->VTable0x94(m_hookEntity);
		m_projectile.Draw(p_renderer);
		break;
	case c_stateRetracting:
		m_projectile.Draw(p_renderer);
		if (m_billboardAnimation.IsAssigned()) {
			p_renderer->VTable0xb4(*m_billboard);
		}
		break;
	}
}

// STUB: LEGORACERS 0x00454360
void RacePowerupManager::GrapplingHookAction::AdvanceState()
{
	SoundVector targetPosition;

	if (m_state != c_stateArmed) {
		if (m_state > c_stateArmed && m_state <= c_statePulling) {
			m_hookEntity->VTable0x04(&targetPosition);
			ReleaseHook(&targetPosition);
		}
		else {
			m_state = c_stateDone;
			m_stateTimerMs = 0;
		}

		return;
	}

	SoundVector position;
	GolVec3 direction;
	GolVec3 scaledDirection;
	GolVec3 targetVelocity;
	PowerupProjectile::Params projectileParams;
	RaceState::Racer::Field0x018* racerField = &m_ownerRacer->m_unk0x018;
	LegoU32 durationMs = 3000;

	m_state = c_stateFlying;
	m_stateTimerMs = durationMs;

	racerField->m_unk0x044->VTable0x04(&position);

	m_ownerRacer->m_unk0x018.m_unk0x044->GetOrientationRow0(&direction);

	projectileParams.m_worldEntity = m_hookEntity;
	projectileParams.m_collisionWorld = m_collisionWorld;
	projectileParams.m_gravity = g_hookGravity;
	projectileParams.m_eventQueue = m_owner0x01c->m_raceState->GetEventQueue();
	projectileParams.m_targetOffset.m_x = 0.0f;
	projectileParams.m_targetOffset.m_y = 0.0f;
	projectileParams.m_targetOffset.m_z = 0.0f;
	projectileParams.m_speed = g_hookSpeed;
	projectileParams.m_lifetimeMs = durationMs;
	projectileParams.m_launchHeight = g_hookLaunchHeight;

	if (m_targetRacer == NULL) {
		if (m_targetPoint != NULL) {
			targetPosition.m_x = m_targetPoint->m_position.m_x;
			targetPosition.m_y = m_targetPoint->m_position.m_y;
			targetPosition.m_z = m_targetPoint->m_position.m_z;
		}
		else {
			scaledDirection.m_x = direction.m_x * 500.0f;
			scaledDirection.m_y = direction.m_y * 500.0f;
			scaledDirection.m_z = direction.m_z * 500.0f;
			GolCameraBase::FUN_00404550(&position, &scaledDirection, &targetPosition);
			targetPosition.m_z = 5.0f + targetPosition.m_z;
		}

		targetVelocity.m_x = 0.0f;
		targetVelocity.m_y = 0.0f;
		targetVelocity.m_z = 0.0f;
		m_projectile
			.PowerupProjectile::LaunchAtPoint(&projectileParams, m_ownerRacer, &targetPosition, &targetVelocity, TRUE);
	}
	else {
		m_projectile.PowerupProjectile::LaunchAtRacer(&projectileParams, m_ownerRacer, m_targetRacer, TRUE, FALSE);
	}

	m_projectile.ResetRope();

	m_smokeParticleRef = m_owner0x01c->m_cutsceneAnimation->FUN_00489d70("cannsmk", NULL, NULL, NULL);
	if (m_smokeParticleRef != NULL) {
		m_ownerRacer->m_unk0x3e8.m_unk0x13c->VTable0x04(&position);
		position.m_z += 4.0f;

		if (m_smokeParticleRef->m_particle != NULL) {
			m_ownerRacer->m_unk0x3e8.m_unk0x13c->VTable0x44(m_smokeParticleRef->m_particle->GetUnk0x160());
		}
		if (m_smokeParticleRef->m_particle != NULL) {
			m_smokeParticleRef->m_particle->FUN_00489660(&position);
		}
	}

	racerField->m_unk0x044->VTable0x04(&position);
	m_soundSource
		->PlaySpatialSoundById(c_soundFire, &position, g_hookSoundMinDistance, g_hookSoundMaxDistance, 1.0f, 1.0f);
}

// FUNCTION: LEGORACERS 0x004545d0
void RacePowerupManager::GrapplingHookAction::OnHitRacer(RaceState::Racer* p_racer)
{
	if (m_state == c_stateFlying) {
		if (p_racer->GetUnk0xd04() & c_racerFlags0xd04Bit0) {
			p_racer->PlayReaction(TRUE);
			p_racer->AbsorbShieldHit();

			SoundVector position;
			m_hookEntity->VTable0x04(&position);
			ReleaseHook(&position);
		}
		else {
			if (m_ownerRacer != NULL) {
				m_ownerRacer->PlayReaction(TRUE);
			}

			p_racer->PlayReaction(FALSE);
			p_racer->DropWhiteBrick();

			SoundVector position;
			p_racer->m_unk0x018.m_unk0x044->VTable0x04(&position);
			m_soundSource->PlaySpatialSoundById(
				c_soundHitRacer,
				&position,
				g_hookSoundMinDistance,
				g_hookSoundMaxDistance,
				1.0f,
				1.0f
			);

			m_state = c_statePulling;
			m_stateTimerMs = 4000;
		}
	}
}

// FUNCTION: LEGORACERS 0x00454690
void RacePowerupManager::GrapplingHookAction::ReleaseHook(SoundVector* p_position)
{
	RaceState::Racer* racer = m_projectile.GetHitRacer();
	if (racer != NULL) {
		racer->m_unk0x3e8.VTable0x44();
		m_ownerRacer->m_unk0x3e8.VTable0x4c();
		m_soundSource->PlaySpatialSoundById(
			c_soundRelease,
			p_position,
			g_hookSoundMinDistance,
			g_hookSoundMaxDistance,
			1.0f,
			1.0f
		);
	}
	else {
		m_soundSource
			->PlaySpatialSoundById(c_soundMiss, p_position, g_hookSoundMinDistance, g_hookSoundMaxDistance, 1.0f, 1.0f);
		m_soundSource->PlaySpatialSoundById(
			c_soundRetract,
			p_position,
			g_hookSoundMinDistance,
			g_hookSoundMaxDistance,
			1.0f,
			1.0f
		);
	}

	m_state = c_stateRetracting;
	m_stateTimerMs = 500;
	m_billboardAnimation.FUN_00410470();
	m_billboardAnimation.FUN_00410480();
	m_billboardAnimation.FUN_10025da0(m_owner0x01c->GetBillboardMaterialTable(), m_billboardMaterialIndex, FALSE);
	m_billboardAnimation
		.FUN_004104c0(0, m_owner0x01c->GetMaterialAnimationItems(), m_owner0x01c->GetMaterialAnimationItemCount());
	m_billboard->VTable0x08(*p_position);
	m_projectile.Release(p_position);
	m_projectile.CancelCollisionEvent();
}

// FUNCTION: LEGORACERS 0x00458570
RacePowerupManager::PowerupAction* RacePowerupManager::GrapplingHookAction::Destroy(undefined4 p_flags)
{
	GrapplingHookAction* result = this;
	if (p_flags & 2) {
		if (p_flags & 1) {
			delete[] this;
		}

		return result;
	}

	this->~GrapplingHookAction();
	if (p_flags & 1) {
		::operator delete(result);
	}

	return result;
}
