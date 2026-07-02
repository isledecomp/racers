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

extern const LegoFloat g_unk0x004b14dc;

extern const LegoFloat g_unk0x004b1508;

// GLOBAL: LEGORACERS 0x004b14e0
const LegoFloat g_unk0x004b14e0 = 30.0f;

// GLOBAL: LEGORACERS 0x004b14e4
const LegoFloat g_unk0x004b14e4 = 300.0f;

// GLOBAL: LEGORACERS 0x004b14e8
const LegoFloat g_unk0x004b14e8 = 4.0f;

// GLOBAL: LEGORACERS 0x004b14ec
const LegoFloat g_unk0x004b14ec = 180.0f;

// GLOBAL: LEGORACERS 0x004b14f0
const LegoFloat g_unk0x004b14f0 = -90.1760025f;

// GLOBAL: LEGORACERS 0x004b14f4
const LegoFloat g_unk0x004b14f4 = 320.0f;

// GLOBAL: LEGORACERS 0x004b150c
const LegoFloat g_unk0x004b150c = 5.0f;

// GLOBAL: LEGORACERS 0x004b1510
const LegoFloat g_unk0x004b1510 = 144.0f;

// GLOBAL: LEGORACERS 0x004b1514
const LegoFloat g_unk0x004b1514 = 0.6f;

// GLOBAL: LEGORACERS 0x004c1c50
ColorRGBA g_unk0x004c1c50 = {0x64, 0x3c, 0x0e, 0xff};

// GLOBAL: LEGORACERS 0x004c1c54
ColorRGBA g_unk0x004c1c54 = {0x8f, 0x5a, 0x1c, 0xff};

// GLOBAL: LEGORACERS 0x004c1c58
ColorRGBA g_unk0x004c1c58 = {0x14, 0x14, 0x00, 0xff};

// FUNCTION: LEGORACERS 0x00453bf0
RacePowerupManager::GrapplingHookAction::GrapplingHookAction()
{
	m_activeProjectile = 0;
	m_activeProjectile = &m_projectile;
	m_unk0x268 = 0;
	m_unk0x26c = 0;
	m_unk0x270 = NULL;
	m_unk0x28c = 0;
}

// FUNCTION: LEGORACERS 0x00453c70
RacePowerupManager::GrapplingHookAction::~GrapplingHookAction()
{
	FUN_00453d90();
}

// FUNCTION: LEGORACERS 0x00453cd0
void RacePowerupManager::GrapplingHookAction::Initialize(
	RacePowerupManager* p_unk0x04,
	RaceSessionField0x32b4* p_unk0x08,
	undefined4 p_unk0x0c
)
{
	if (m_state != 0) {
		FUN_00453d90();
	}

	m_owner0x01c = p_unk0x04;
	m_collisionWorld = p_unk0x08;
	m_unk0x268 = 0;
	m_unk0x26c = 0;
	m_unk0x28c = p_unk0x0c;

	TetherProjectile::SetupParams params;
	params.m_golExport = p_unk0x04->m_golExport;
	params.m_ropeThickness = g_unk0x004b1514;
	params.m_waveAmplitude = g_unk0x004b14e8;
	params.m_baseColor = g_unk0x004c1c50;
	params.m_attachHeight = 3.0f;
	params.m_secondaryColor = g_unk0x004c1c54;
	params.m_tertiaryColor = g_unk0x004c1c58;
	params.m_material = p_unk0x04->m_renderer->FindMaterialByName("tether");
	m_projectile.Initialize(&params);

	m_state = 1;
	m_unk0x270 = static_cast<GolBillboard*>(params.m_golExport->VTable0x30());
}

// FUNCTION: LEGORACERS 0x00453d90
void RacePowerupManager::GrapplingHookAction::FUN_00453d90()
{
	Deactivate();

	if (m_owner0x01c != NULL && m_unk0x270 != NULL) {
		m_owner0x01c->m_golExport->VTable0x64(m_unk0x270);
		m_unk0x270 = NULL;
		m_owner0x01c = NULL;
	}

	m_projectile.Deactivate();
	m_state = 0;
}

// FUNCTION: LEGORACERS 0x00453de0
LegoU32 RacePowerupManager::GrapplingHookAction::Activate(
	GolModelEntity* p_unk0x04,
	RaceState::Racer* p_racer,
	RaceState::Racer* p_unk0x0c,
	TargetPointList::Entry* p_unk0x10,
	MabMaterialAnimationItem0x18* p_unk0x14,
	LegoU32 p_unk0x18
)
{
	m_unk0x268 = p_unk0x04;
	m_ownerRacer = p_racer;
	m_targetRacer = p_unk0x0c;
	m_state = 2;
	m_targetPoint = p_unk0x10;
	m_stateTimerMs = p_unk0x18;

	m_unk0x274.FUN_004103c0(*p_unk0x14);
	m_unk0x274.FUN_00410470();
	m_unk0x274.FUN_00410480();
	m_unk0x274.FUN_10025da0(m_owner0x01c->GetBillboardMaterialTable(), m_unk0x28c, FALSE);
	m_unk0x274
		.FUN_004104c0(0, m_owner0x01c->GetMaterialAnimationItems(), m_owner0x01c->GetMaterialAnimationItemCount());

	return m_unk0x270->FUN_10029e90(
		m_owner0x01c->GetBillboardMaterialTable(),
		m_unk0x28c,
		g_unk0x004b1508,
		g_unk0x004b1508,
		g_unk0x004b14dc
	);
}

// FUNCTION: LEGORACERS 0x00453e90
void RacePowerupManager::GrapplingHookAction::Deactivate()
{
	m_projectile.CancelCollisionEvent();

	if (m_unk0x26c != NULL) {
		m_owner0x01c->m_cutsceneAnimation->FUN_00489f00(m_unk0x26c);
		m_unk0x26c = NULL;
	}

	m_unk0x274.Reset();

	if (m_unk0x270 != NULL) {
		m_unk0x270->VTable0x50();
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

	if (m_state == 6) {
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

	if (m_state == 2) {
		return;
	}

	projectileState = m_projectile.Update(p_elapsedMs);
	if (projectileState != PowerupProjectile::c_stateFlying) {
		if (projectileState == PowerupProjectile::c_stateHitRacer) {
			OnHitRacer(m_projectile.GetHitRacer());
		}
	}

	switch (m_state) {
	case 3: {
		if (projectileState == PowerupProjectile::c_stateHitWorld) {
			GolVec3& projectilePositionCopyBase = projectilePositionCopy;
			projectilePositionCopyBase = m_projectile.GetHitPosition();
			FUN_00454690(&projectilePositionCopy);
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
			m_unk0x268->VTable0x40(forward, up);
		}

		break;
	}
	case 4:
		if (projectileState == PowerupProjectile::c_stateHitWorld) {
			GolVec3& projectilePositionCopyBase = projectilePositionCopy;
			projectilePositionCopyBase = m_projectile.GetHitPosition();
			FUN_00454690(&projectilePositionCopy);
		}
		else {
			RaceState::Racer::Field0x018* racerField = &m_ownerRacer->m_unk0x018;
			racerField->m_unk0x044->VTable0x04(&position);

			RaceState::Racer* targetRacer = m_projectile.GetHitRacer();
			targetRacer->m_unk0x018.m_unk0x044->VTable0x04(&targetPosition);

			if (targetRacer->m_unk0xd04 & c_racerFlags0xd04Bit0) {
				FUN_00454690(&targetPosition);
				return;
			}

			direction.m_x = targetPosition.m_x - position.m_x;
			direction.m_y = targetPosition.m_y - position.m_y;
			direction.m_z = targetPosition.m_z - position.m_z;

			LegoFloat distanceSquared = direction.m_y * direction.m_y;
			distanceSquared += direction.m_z * direction.m_z;
			distanceSquared += direction.m_x * direction.m_x;
			if (distanceSquared < g_unk0x004b1510) {
				FUN_00454690(&targetPosition);
				break;
			}

			m_ownerRacer->m_unk0x018.m_unk0x044->GetOrientationRow0(&forward);

			LegoFloat dot = direction.m_z;
			dot *= forward.m_z;
			dot += direction.m_y * forward.m_y;
			dot += direction.m_x * forward.m_x;
			if (dot < 0.0f) {
				FUN_00454690(&targetPosition);
				break;
			}

			GolMath::NormalizeVector3(direction, &direction);
			direction.m_x *= g_unk0x004b14ec;
			direction.m_y *= g_unk0x004b14ec;
			direction.m_z *= g_unk0x004b14ec;
			m_ownerRacer->m_unk0x3e8.VTable0x48(&direction);

			direction.m_x = -direction.m_x;
			direction.m_y = -direction.m_y;
			direction.m_z = -direction.m_z;
			targetRacer->m_unk0x3e8.VTable0x40(&direction);
		}
		break;
	case 5:
		if (m_unk0x274.IsAssigned()) {
			m_unk0x274.FUN_004104c0(
				p_elapsedMs,
				m_owner0x01c->GetMaterialAnimationItems(),
				m_owner0x01c->GetMaterialAnimationItemCount()
			);
			m_unk0x270->VTable0x10(p_elapsedMs);
		}

		if (projectileState == 4) {
			m_state = 6;
			m_stateTimerMs = 0;
		}
		break;
	}

	if (m_unk0x26c != NULL) {
		CutsceneParticle* particle = m_unk0x26c->m_unk0x00;
		if (particle == NULL || particle->GetSpawnedCount() >= 3) {
			m_owner0x01c->m_cutsceneAnimation->FUN_00489f30(m_unk0x26c);
			m_unk0x26c = NULL;
			return;
		}

		m_ownerRacer->m_unk0x3e8.m_unk0x13c->VTable0x04(&position);
		position.m_z += 4.0f;

		velocity = m_ownerRacer->m_unk0x3e8.m_unk0x008;
		if (m_unk0x26c->m_unk0x00 != NULL) {
			m_ownerRacer->m_unk0x3e8.m_unk0x13c->VTable0x44(m_unk0x26c->m_unk0x00->GetUnk0x160());
		}
		if (m_unk0x26c->m_unk0x00 != NULL) {
			m_unk0x26c->m_unk0x00->FUN_00489660(&position);
		}
		if (m_unk0x26c->m_unk0x00 != NULL) {
			m_unk0x26c->m_unk0x00->FUN_00489690(&velocity);
		}
	}
}

// FUNCTION: LEGORACERS 0x004542d0
void RacePowerupManager::GrapplingHookAction::Draw(GolD3DRenderDevice* p_renderer)
{
	switch (m_state) {
	case 3:
		p_renderer->VTable0x94(m_unk0x268);
		m_projectile.Draw(p_renderer);
		break;
	case 4:
		p_renderer->VTable0x94(m_unk0x268);
		m_projectile.Draw(p_renderer);
		break;
	case 5:
		m_projectile.Draw(p_renderer);
		if (m_unk0x274.IsAssigned()) {
			p_renderer->VTable0xb4(*m_unk0x270);
		}
		break;
	}
}

// STUB: LEGORACERS 0x00454360
void RacePowerupManager::GrapplingHookAction::AdvanceState()
{
	SoundVector targetPosition;

	if (m_state != 2) {
		if (m_state > 2 && m_state <= 4) {
			m_unk0x268->VTable0x04(&targetPosition);
			FUN_00454690(&targetPosition);
		}
		else {
			m_state = 6;
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

	m_state = 3;
	m_stateTimerMs = durationMs;

	racerField->m_unk0x044->VTable0x04(&position);

	m_ownerRacer->m_unk0x018.m_unk0x044->GetOrientationRow0(&direction);

	projectileParams.m_worldEntity = m_unk0x268;
	projectileParams.m_collisionWorld = m_collisionWorld;
	projectileParams.m_gravity = g_unk0x004b14f0;
	projectileParams.m_eventQueue = m_owner0x01c->m_raceState->GetEventQueue();
	projectileParams.m_targetOffset.m_x = 0.0f;
	projectileParams.m_targetOffset.m_y = 0.0f;
	projectileParams.m_targetOffset.m_z = 0.0f;
	projectileParams.m_speed = g_unk0x004b14f4;
	projectileParams.m_lifetimeMs = durationMs;
	projectileParams.m_launchHeight = g_unk0x004b150c;

	if (m_targetRacer == NULL) {
		if (m_targetPoint != NULL) {
			targetPosition.m_x = m_targetPoint->m_unk0x00.m_x;
			targetPosition.m_y = m_targetPoint->m_unk0x00.m_y;
			targetPosition.m_z = m_targetPoint->m_unk0x00.m_z;
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

	m_unk0x26c = m_owner0x01c->m_cutsceneAnimation->FUN_00489d70("cannsmk", NULL, NULL, NULL);
	if (m_unk0x26c != NULL) {
		m_ownerRacer->m_unk0x3e8.m_unk0x13c->VTable0x04(&position);
		position.m_z += 4.0f;

		if (m_unk0x26c->m_unk0x00 != NULL) {
			m_ownerRacer->m_unk0x3e8.m_unk0x13c->VTable0x44(m_unk0x26c->m_unk0x00->GetUnk0x160());
		}
		if (m_unk0x26c->m_unk0x00 != NULL) {
			m_unk0x26c->m_unk0x00->FUN_00489660(&position);
		}
	}

	racerField->m_unk0x044->VTable0x04(&position);
	m_soundSource->PlaySpatialSoundById(0x15, &position, g_unk0x004b14e0, g_unk0x004b14e4, 1.0f, 1.0f);
}

// FUNCTION: LEGORACERS 0x004545d0
void RacePowerupManager::GrapplingHookAction::OnHitRacer(RaceState::Racer* p_racer)
{
	if (m_state == 3) {
		if (p_racer->GetUnk0xd04() & c_racerFlags0xd04Bit0) {
			p_racer->PlayReaction(TRUE);
			p_racer->AbsorbShieldHit();

			SoundVector position;
			m_unk0x268->VTable0x04(&position);
			FUN_00454690(&position);
		}
		else {
			if (m_ownerRacer != NULL) {
				m_ownerRacer->PlayReaction(TRUE);
			}

			p_racer->PlayReaction(FALSE);
			p_racer->DropWhiteBrick();

			SoundVector position;
			p_racer->m_unk0x018.m_unk0x044->VTable0x04(&position);
			m_soundSource->PlaySpatialSoundById(0x12, &position, g_unk0x004b14e0, g_unk0x004b14e4, 1.0f, 1.0f);

			m_state = 4;
			m_stateTimerMs = 4000;
		}
	}
}

// FUNCTION: LEGORACERS 0x00454690
void RacePowerupManager::GrapplingHookAction::FUN_00454690(SoundVector* p_position)
{
	RaceState::Racer* racer = m_projectile.GetHitRacer();
	if (racer != NULL) {
		racer->m_unk0x3e8.VTable0x44();
		m_ownerRacer->m_unk0x3e8.VTable0x4c();
		m_soundSource->PlaySpatialSoundById(0x14, p_position, g_unk0x004b14e0, g_unk0x004b14e4, 1.0f, 1.0f);
	}
	else {
		m_soundSource->PlaySpatialSoundById(0x16, p_position, g_unk0x004b14e0, g_unk0x004b14e4, 1.0f, 1.0f);
		m_soundSource->PlaySpatialSoundById(0x49, p_position, g_unk0x004b14e0, g_unk0x004b14e4, 1.0f, 1.0f);
	}

	m_state = 5;
	m_stateTimerMs = 500;
	m_unk0x274.FUN_00410470();
	m_unk0x274.FUN_00410480();
	m_unk0x274.FUN_10025da0(m_owner0x01c->GetBillboardMaterialTable(), m_unk0x28c, FALSE);
	m_unk0x274
		.FUN_004104c0(0, m_owner0x01c->GetMaterialAnimationItems(), m_owner0x01c->GetMaterialAnimationItemCount());
	m_unk0x270->VTable0x08(*p_position);
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
