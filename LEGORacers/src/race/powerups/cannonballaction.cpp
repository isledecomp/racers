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

const LegoFloat g_powerupHitSoundMaxDistance = 600.0f;

const LegoFloat g_powerupHitSoundMinDistance = 200.0f;

extern const LegoFloat g_unlimitedDrawDistance;

// GLOBAL: LEGORACERS 0x004b1370
const LegoFloat g_cannonballTargetHeightOffset = 5.0f;

// GLOBAL: LEGORACERS 0x004b1384
const LegoFloat g_powerupSoundMinDistance = 30.0f;

// GLOBAL: LEGORACERS 0x004b1388
const LegoFloat g_powerupSoundMaxDistance = 300.0f;

// GLOBAL: LEGORACERS 0x004b1394
const LegoFloat g_cannonballGravity = -32.1759987f;

// GLOBAL: LEGORACERS 0x004b1398
const LegoFloat g_cannonballSpeed = 180.0f;

// GLOBAL: LEGORACERS 0x004b139c
const LegoFloat g_cannonballDefaultRange = 500.0f;

// GLOBAL: LEGORACERS 0x004b13a4
const LegoFloat g_cannonballTrailSize = 3.0f;

// GLOBAL: LEGORACERS 0x004b13b0
const LegoFloat g_cannonballSmokeHeightOffset = 4.0f;

// GLOBAL: LEGORACERS 0x004b13b4
const LegoFloat g_cannonballLaunchHeight = 5.0f;

// GLOBAL: LEGORACERS 0x004b13e4
extern const LegoFloat g_scarNormalThreshold = 0.70709997f;

// GLOBAL: LEGORACERS 0x004b13e8
extern const LegoFloat g_emplacementGravityScale = 3.0f;

// GLOBAL: LEGORACERS 0x004c1c4c
ColorRGBA g_cannonballTrailColor = {0x32, 0x32, 0x32, 0xc8};

// FUNCTION: LEGORACERS 0x004518f0
RacePowerupManager::CannonballAction::CannonballAction()
{
	m_activeProjectile = 0;
	m_activeProjectile = &m_projectile;
	m_billboard = NULL;
	m_smokeParticle = 0;
	m_emplacement = 0;
	m_trailParticle = 0;
}

// FUNCTION: LEGORACERS 0x00451970
RacePowerupManager::CannonballAction::~CannonballAction()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004519d0
void RacePowerupManager::CannonballAction::Initialize(
	GolExport** p_golExportPtr,
	RaceSessionField0x32b4* p_collisionWorld
)
{
	if (m_state != 0) {
		Destroy();
	}

	m_golExportPtr = p_golExportPtr;
	m_collisionWorld = p_collisionWorld;
	m_billboard = static_cast<GolBillboard*>((*p_golExportPtr)->VTable0x30());
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x00451a10
void RacePowerupManager::CannonballAction::Destroy()
{
	Deactivate();

	if (m_golExportPtr != NULL && m_billboard != NULL) {
		(*m_golExportPtr)->VTable0x64(m_billboard);
		m_billboard = NULL;
		m_golExportPtr = NULL;
	}

	m_state = 0;
}

// FUNCTION: LEGORACERS 0x00451a50
LegoU32 RacePowerupManager::CannonballAction::Activate(ActionSetup* p_setup)
{
	m_state = 2;
	m_ownerRacer = p_setup->m_racer;
	m_targetRacer = p_setup->m_targetRacer;
	m_targetPoint = p_setup->m_targetPoint;
	m_stateTimerMs = p_setup->m_initialTimerMs;

	ActionTarget* target = p_setup->m_aimTarget;
	if (target) {
		m_materialName = target->m_materialName;
	}

	GolD3DRenderDevice* renderDevice = m_owner0x01c->m_renderer;
	const LegoChar* materialName = m_materialName;
	DuskwindBananaRelic0x24* material;
	if (materialName && materialName[0]) {
		material = renderDevice->FindMaterialByName(materialName);
	}
	else {
		material = renderDevice->FindMaterialByName("cannon");
	}

	return m_billboard->VTable0x4c(material, 5.0f, 5.0f, g_unlimitedDrawDistance);
}

// FUNCTION: LEGORACERS 0x00451ad0
void RacePowerupManager::CannonballAction::Deactivate()
{
	m_projectile.Deactivate();

	if (m_smokeParticle != NULL) {
		m_owner0x01c->m_cutsceneAnimation->FUN_00489f00(m_smokeParticle);
		m_smokeParticle = NULL;
	}

	if (m_billboard != NULL) {
		m_billboard->VTable0x50();
	}

	m_ownerRacer = NULL;
	m_targetRacer = 0;
	m_targetPoint = 0;
	m_emplacement = 0;
	m_state = 1;

	if (m_owner0x01c != NULL && m_trail != NULL) {
		m_owner0x01c->m_trailManager->FUN_00493a10(m_trail);
		m_trail = NULL;
	}
}

// STUB: LEGORACERS 0x00451b50
void RacePowerupManager::CannonballAction::Update(LegoU32 p_elapsedMs)
{
	GolVec2 perpendicular;
	GolVec3 direction;
	GolVec3 particlePosition;
	GolVec3 particleVelocity;
	GolVec3 trailVelocity;
	GolVec3 positions[4];

	if (p_elapsedMs >= m_stateTimerMs) {
		p_elapsedMs -= m_stateTimerMs;
		m_stateTimerMs = 0;
		AdvanceState();
	}
	else {
		m_stateTimerMs -= p_elapsedMs;
	}

	if (m_state == 3) {
		LegoS32 projectileState = m_projectile.Update(p_elapsedMs);
		if (projectileState != PowerupProjectile::c_stateFlying) {
			SoundVector position;
			GolVec3& positionBase = position;
			positionBase = m_projectile.GetHitPosition();
			LegoBool32 skipBurst = FALSE;

			if (projectileState == PowerupProjectile::c_stateHitRacer) {
				RaceState::Racer* target = m_projectile.GetHitRacer();
				if ((target->m_unk0xd04 & c_racerFlags0xd04Bit0) && target->m_shieldLevel >= 2) {
					skipBurst = TRUE;
				}

				OnHitRacer(target);
				m_stateTimerMs = 3000;
			}
			else {
				m_soundSource->PlaySpatialSoundById(
					c_soundHit,
					&position,
					g_powerupHitSoundMinDistance,
					g_powerupHitSoundMaxDistance,
					1.0f,
					1.0f
				);
			}

			if (!skipBurst) {
				GolVec3 hitNormal = m_projectile.GetHitNormal();
				LegoBool32 upwardHit = FALSE;
				if (projectileState == PowerupProjectile::c_stateHitWorld && hitNormal.m_z > g_scarNormalThreshold) {
					upwardHit = TRUE;
				}

				m_owner0x01c->SpawnExplosion(&position, upwardHit, m_ownerRacer);
				if (projectileState == PowerupProjectile::c_stateHitRacer &&
					!(m_projectile.GetHitRacer()->m_unk0xd04 & c_racerFlags0xd04Bit0)) {
					m_projectile.GetVelocity(&direction);
					direction.m_x = -direction.m_x;
					direction.m_y = -direction.m_y;
					direction.m_z = 0.0f;
					GolMath::NormalizeVector3(direction, &direction);
					m_owner0x01c->SpawnBrickDebris(&position, &direction, m_projectile.GetHitRacer());
				}

				AdvanceState();
			}
		}
	}

	if (m_smokeParticle != NULL) {
		CutsceneParticle* particle = m_smokeParticle->m_particle;
		if (particle != NULL && particle->GetSpawnedCount() < 3) {
			if (m_ownerRacer != NULL) {
				m_ownerRacer->m_unk0x3e8.m_unk0x13c->VTable0x04(&particlePosition);
				particlePosition.m_z += g_cannonballSmokeHeightOffset;

				particleVelocity = m_ownerRacer->m_unk0x3e8.m_unk0x008;
				if (m_smokeParticle->m_particle != NULL) {
					m_ownerRacer->m_unk0x3e8.m_unk0x13c->VTable0x44(m_smokeParticle->m_particle->GetUnk0x160());
				}

				if (m_smokeParticle->m_particle != NULL) {
					m_smokeParticle->m_particle->FUN_00489660(&particlePosition);
				}
				if (m_smokeParticle->m_particle != NULL) {
					m_smokeParticle->m_particle->FUN_00489690(&particleVelocity);
				}
			}
		}
		else {
			m_owner0x01c->m_cutsceneAnimation->FUN_00489f30(m_smokeParticle);
			m_smokeParticle = NULL;
		}
	}

	if (m_state == 3) {
		GolVec3 position;
		m_projectile.GetWorldEntity()->FUN_100286d0(&position);

		if (m_trail != NULL) {
			m_projectile.GetVelocity(&trailVelocity);

			perpendicular.m_x = trailVelocity.m_y;
			perpendicular.m_y = -trailVelocity.m_x;
			if (perpendicular.m_y != 0.0f || perpendicular.m_x != 0.0f) {
				GolMath::NormalizeVector2(perpendicular, &perpendicular);
				perpendicular.m_x *= g_cannonballTrailSize;
				perpendicular.m_y *= g_cannonballTrailSize;

				positions[0].m_x = position.m_x - perpendicular.m_x * 0.5f;
				positions[0].m_y = position.m_y - perpendicular.m_y * 0.5f;
				positions[0].m_z = position.m_z + g_cannonballTrailSize * 0.5f;
				positions[1].m_x = positions[0].m_x;
				positions[1].m_y = positions[0].m_y;
				positions[1].m_z = positions[0].m_z - g_cannonballTrailSize;
				positions[2].m_x = positions[0].m_x + perpendicular.m_x;
				positions[2].m_y = positions[0].m_y + perpendicular.m_y;
				positions[2].m_z = positions[1].m_z;
				positions[3].m_x = positions[2].m_x;
				positions[3].m_y = positions[2].m_y;
				positions[3].m_z = positions[1].m_z + g_cannonballTrailSize;

				m_trail->FUN_00492ee0(p_elapsedMs, positions, position);
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00451f30
void RacePowerupManager::CannonballAction::Draw(GolD3DRenderDevice* p_renderer)
{
	if (m_state == 3) {
		p_renderer->VTable0xb4(*m_billboard);
	}
}

// STUB: LEGORACERS 0x00451f50
void RacePowerupManager::CannonballAction::AdvanceState()
{
	switch (m_state) {
	case 2:
		break;
	case 3:
		m_state = 6;
		m_stateTimerMs = 0;
		m_projectile.CancelCollisionEvent();
		if (m_trail != NULL) {
			m_owner0x01c->m_trailManager->FUN_00493a10(m_trail);
			m_trail = NULL;
		}

		return;
	default:
		m_state = 6;
		m_stateTimerMs = 0;
		return;
	}

	m_state = 3;
	LegoU32 durationMs = 3000;
	SoundVector position;
	GolVec3 direction;
	GolVec3 target;
	GolVec3 velocity;
	GolVec3 right;
	GolVec3 forward;
	PowerupProjectile::Params projectileParams;
	RaceTrailManager::Trail::Params trailParams;

	m_stateTimerMs = durationMs;

	if (m_emplacement == NULL) {
		RaceState::Racer::Field0x018* racerField = &m_ownerRacer->m_unk0x018;
		racerField->m_carEntity->VTable0x04(&position);
		m_ownerRacer->m_unk0x018.m_carEntity->GetOrientationRow0(&direction);
	}
	else {
		GolVec3& positionBase = position;
		positionBase = m_emplacement->m_position;
		direction.m_x = 0.0f;
		direction.m_y = 0.0f;
		direction.m_z = 0.0f;
	}

	projectileParams.m_worldEntity = m_billboard;
	projectileParams.m_collisionWorld = m_collisionWorld;
	projectileParams.m_gravity = g_cannonballGravity;
	projectileParams.m_eventQueue = m_owner0x01c->m_raceState->GetEventQueue();
	projectileParams.m_targetOffset.m_x = 0.0f;
	projectileParams.m_targetOffset.m_y = 0.0f;
	projectileParams.m_targetOffset.m_z = 0.0f;
	projectileParams.m_speed = g_cannonballSpeed;
	projectileParams.m_lifetimeMs = durationMs;
	projectileParams.m_launchHeight = g_cannonballLaunchHeight;

	if (m_targetRacer != NULL) {
		m_projectile.LaunchAtRacer(&projectileParams, m_ownerRacer, m_targetRacer, TRUE, FALSE);
	}
	else if (m_emplacement != NULL) {
		projectileParams.m_lifetimeMs = m_emplacement->m_lifetimeMs;
		m_billboard->VTable0x08(m_emplacement->m_position);
		projectileParams.m_gravity = g_cannonballGravity * g_emplacementGravityScale;
		m_projectile.LaunchAtPosition(&projectileParams, &m_emplacement->m_targetPosition);
	}
	else {
		if (m_targetPoint != NULL) {
			target = m_targetPoint->m_position;
		}
		else {
			target.m_x = position.m_x + direction.m_x * g_cannonballDefaultRange;
			target.m_y = position.m_y + direction.m_y * g_cannonballDefaultRange;
			target.m_z = position.m_z + direction.m_z * g_cannonballDefaultRange + g_cannonballTargetHeightOffset;
		}

		velocity.m_x = 0.0f;
		velocity.m_y = 0.0f;
		velocity.m_z = 0.0f;
		m_projectile.LaunchAtPoint(&projectileParams, m_ownerRacer, &target, &velocity, TRUE);
	}

	m_smokeParticle = m_owner0x01c->m_cutsceneAnimation->FUN_00489d70("cannsmk", NULL, NULL, NULL);
	if (m_smokeParticle != NULL) {
		if (m_emplacement == NULL) {
			m_ownerRacer->m_unk0x3e8.m_unk0x13c->VTable0x48(&right, &forward);
			m_ownerRacer->m_unk0x3e8.m_unk0x13c->VTable0x04(&position);
		}
		else {
			GolVec3& positionBase = position;
			positionBase = m_emplacement->m_position;
			right.m_x = 1.0f;
			right.m_y = 0.0f;
			right.m_z = 0.0f;
			forward.m_x = 0.0f;
			forward.m_y = 0.0f;
			forward.m_z = 1.0f;
		}

		position.m_z += g_cannonballSmokeHeightOffset;
		if (m_smokeParticle->m_particle != NULL) {
			m_smokeParticle->m_particle->FUN_00489540(&right, &forward);
		}
		if (m_smokeParticle->m_particle != NULL) {
			m_smokeParticle->m_particle->FUN_00489660(&position);
		}
	}

	trailParams.m_unk0x00 = 300;
	trailParams.m_unk0x04 = 4;
	trailParams.m_unk0x08 = 4;
	trailParams.m_unk0x0c = 1;
	trailParams.m_unk0x10 = 0;
	trailParams.m_unk0x14 = 0.1f;
	trailParams.m_unk0x18 = 0.0f;
	m_trail = m_owner0x01c->m_trailManager->FUN_004939b0(&trailParams);
	if (m_trail != NULL) {
		m_trail->FUN_00492ab0(&g_cannonballTrailColor);

		DuskwindBananaRelic0x24* material = m_owner0x01c->m_renderer->FindMaterialByName("canstrk");
		if (material != NULL) {
			m_trail->FUN_00492a90(m_owner0x01c->m_renderer, material);
		}
	}

	if (m_emplacement != NULL) {
		GolVec3& positionBase = position;
		positionBase = m_emplacement->m_position;
	}
	else {
		RaceState::Racer::Field0x018* racerField = &m_ownerRacer->m_unk0x018;
		racerField->m_carEntity->VTable0x04(&position);
	}

	m_soundSource->PlaySpatialSoundById(
		c_soundFire,
		&position,
		g_powerupSoundMinDistance,
		g_powerupSoundMaxDistance,
		1.0f,
		1.0f
	);
}

// FUNCTION: LEGORACERS 0x00452370
void RacePowerupManager::CannonballAction::OnHitRacer(RaceState::Racer* p_racer)
{
	if (m_state == 3) {
		if (p_racer->GetUnk0xd04() & c_racerFlags0xd04Bit0) {
			p_racer->PlayReaction(TRUE);
			p_racer->AbsorbShieldHit();
			if (p_racer->m_shieldLevel >= 2) {
				m_projectile.Deflect(p_racer);
				m_ownerRacer = p_racer;
			}
		}
		else {
			if (m_ownerRacer != NULL) {
				m_ownerRacer->PlayReaction(TRUE);
			}

			p_racer->PlayReaction(FALSE);
			p_racer->DropWhiteBrick();
			SoundVector position;
			p_racer->m_unk0x018.SetReactionFlags(c_racerField0x018Flags0x384Bit1);
			p_racer->m_unk0x018.GetCarEntity()->VTable0x04(&position);
			m_soundSource->PlaySpatialSoundById(
				c_soundHit,
				&position,
				g_powerupHitSoundMinDistance,
				g_powerupHitSoundMaxDistance,
				1.0f,
				1.0f
			);
		}
	}
}

// FUNCTION: LEGORACERS 0x00458510
RacePowerupManager::PowerupAction* RacePowerupManager::CannonballAction::Destroy(undefined4 p_flags)
{
	CannonballAction* result = this;
	if (p_flags & 2) {
		if (p_flags & 1) {
			delete[] this;
		}

		return result;
	}

	this->~CannonballAction();
	if (p_flags & 1) {
		::operator delete(result);
	}

	return result;
}
