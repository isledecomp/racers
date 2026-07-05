#include "race/powerups/cannonballaction.h"

#include "audio/soundnode.h"
#include "audio/spatialsoundinstance.h"
#include "camera/golcamera.h"
#include "cmbmodelpart.h"
#include "decomp.h"
#include "golmodelbase.h"
#include "golscenenode.h"
#include "goltransformbase.h"
#include "material/materialtable.h"
#include "menu/runtime/cutsceneparticle.h"
#include "race/powerups/racepowerupmanager.h"
#include "race/racesoundsource.h"
#include "render/golcommondrawstate.h"
#include "render/gold3drenderdevice.h"
#include "world/golworlddatabase.h"

#include <float.h>
#include <math.h>

extern const LegoFloat g_unlimitedDrawDistance;

// GLOBAL: LEGORACERS 0x004b1370
const LegoFloat g_cannonballTargetHeightOffset = 5.0f;

// GLOBAL: LEGORACERS 0x004b1384
const LegoFloat g_powerupSoundMinDistance = 30.0f;

// GLOBAL: LEGORACERS 0x004b1388
const LegoFloat g_powerupSoundMaxDistance = 300.0f;

// GLOBAL: LEGORACERS 0x004b138c
const LegoFloat g_powerupHitSoundMinDistance = 200.0f;

// GLOBAL: LEGORACERS 0x004b1390
const LegoFloat g_powerupHitSoundMaxDistance = 600.0f;

// GLOBAL: LEGORACERS 0x004b1394
const LegoFloat g_cannonballGravity = -32.1759987f;

// GLOBAL: LEGORACERS 0x004b1398
const LegoFloat g_cannonballSpeed = 180.0f;

// GLOBAL: LEGORACERS 0x004b139c
const LegoFloat g_cannonballDefaultRange = 500.0f;

// GLOBAL: LEGORACERS 0x004b13a0
const LegoFloat g_cannonballBillboardSize = 5.0f;

// GLOBAL: LEGORACERS 0x004b13a4
const LegoFloat g_cannonballTrailSize = 3.0f;

// GLOBAL: LEGORACERS 0x004b13b0
const LegoFloat g_cannonballSmokeHeightOffset = 4.0f;

// GLOBAL: LEGORACERS 0x004b13b4
const LegoFloat g_cannonballLaunchHeight = 5.0f;

// GLOBAL: LEGORACERS 0x004b13e4
extern const LegoFloat g_scarNormalThreshold = 0.70709997f;

// GLOBAL: LEGORACERS 0x004c1c4c
ColorRGBA g_cannonballTrailColor = {0x32, 0x32, 0x32, 0xc8};

// FUNCTION: LEGORACERS 0x004518f0
CannonballAction::CannonballAction()
{
	m_activeProjectile = 0;
	m_activeProjectile = &m_projectile;
	m_billboard = NULL;
	m_smokeParticle = 0;
	m_emplacement = 0;
	m_trailParticle = 0;
}

// FUNCTION: LEGORACERS 0x00451970
CannonballAction::~CannonballAction()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004519d0
void CannonballAction::Initialize(RacePowerupManager* p_manager, TriggerWorld* p_collisionWorld)
{
	if (m_state != c_stateUnloaded) {
		Destroy();
	}

	m_owner = p_manager;
	m_collisionWorld = p_collisionWorld;
	m_billboard = static_cast<GolBillboard*>(p_manager->m_golExport->CreateBillboard());
	m_state = c_stateReady;
}

// FUNCTION: LEGORACERS 0x00451a10
void CannonballAction::Destroy()
{
	Deactivate();

	if (m_owner != NULL && m_billboard != NULL) {
		m_owner->m_golExport->DestroyBillboard(m_billboard);
		m_billboard = NULL;
		m_owner = NULL;
	}

	m_state = c_stateUnloaded;
}

// FUNCTION: LEGORACERS 0x00451a50
void CannonballAction::Activate(ActionSetup* p_setup)
{
	m_state = c_stateArmed;
	m_ownerRacer = p_setup->m_racer;
	m_targetRacer = p_setup->m_targetRacer;
	m_targetPoint = p_setup->m_targetPoint;
	m_stateTimerMs = p_setup->m_initialTimerMs;

	ActionTarget* target = p_setup->m_aimTarget;
	if (target) {
		m_materialName = target->m_materialName;
	}

	GolD3DRenderDevice* renderDevice = m_owner->m_renderer;
	const LegoChar* materialName = m_materialName;
	GolMaterial* material;
	if (materialName && materialName[0]) {
		material = renderDevice->FindMaterialByName(materialName);
	}
	else {
		material = renderDevice->FindMaterialByName("cannon");
	}

	m_billboard->Configure(material, g_cannonballBillboardSize, g_cannonballBillboardSize, g_unlimitedDrawDistance);
}

// FUNCTION: LEGORACERS 0x00451ad0
void CannonballAction::Deactivate()
{
	m_projectile.Deactivate();

	if (m_smokeParticle != NULL) {
		m_owner->m_cutsceneAnimation->ReleaseRef(m_smokeParticle);
		m_smokeParticle = NULL;
	}

	if (m_billboard != NULL) {
		m_billboard->SetPrimaryModel();
	}

	m_ownerRacer = NULL;
	m_targetRacer = 0;
	m_targetPoint = 0;
	m_emplacement = 0;
	m_state = c_stateReady;

	if (m_owner != NULL && m_trail != NULL) {
		m_owner->m_trailManager->ReleaseTrail(m_trail);
		m_trail = NULL;
	}
}

// FUNCTION: LEGORACERS 0x00451b50
void CannonballAction::Update(LegoU32 p_elapsedMs)
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

	if (m_state == c_stateFlying) {
		LegoS32 projectileState = m_projectile.Update(p_elapsedMs);
		if (projectileState != PowerupProjectile::c_stateFlying) {
			SoundVector position;
			GolVec3& positionBase = position;
			positionBase = m_projectile.GetHitPosition();
			LegoBool32 skipBurst = FALSE;

			if (projectileState == PowerupProjectile::c_stateHitRacer) {
				Racer* target = m_projectile.GetHitRacer();
				if ((target->m_flags & Racer::c_flagShielded) && target->m_shieldLevel >= 2) {
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

				m_owner->SpawnExplosion(&position, upwardHit, m_ownerRacer);
				if (projectileState == PowerupProjectile::c_stateHitRacer &&
					!(m_projectile.GetHitRacer()->m_flags & Racer::c_flagShielded)) {
					m_projectile.GetVelocity(&direction);
					direction.m_x = -direction.m_x;
					direction.m_y = -direction.m_y;
					direction.m_z = 0.0f;
					GolMath::NormalizeVector3(direction, &direction);
					m_owner->SpawnBrickDebris(&position, &direction, m_projectile.GetHitRacer());
				}

				AdvanceState();
			}
		}
	}

	if (m_smokeParticle != NULL) {
		CutsceneParticle* particle = m_smokeParticle->m_particle;
		if (particle != NULL && particle->GetSpawnedCount() < 3) {
			if (m_ownerRacer != NULL) {
				m_ownerRacer->m_physics.m_carEntity->GetPosition(&particlePosition);
				particlePosition.m_z += g_cannonballSmokeHeightOffset;

				particleVelocity = m_ownerRacer->m_physics.m_velocity;
				if (m_smokeParticle->m_particle != NULL) {
					m_ownerRacer->m_physics.m_carEntity->CopyOrientation(m_smokeParticle->m_particle->GetBasis());
				}

				if (m_smokeParticle->m_particle != NULL) {
					m_smokeParticle->m_particle->SetPosition(&particlePosition);
				}
				if (m_smokeParticle->m_particle != NULL) {
					m_smokeParticle->m_particle->SetVelocity(&particleVelocity);
				}
			}
		}
		else {
			m_owner->m_cutsceneAnimation->FinishRef(m_smokeParticle);
			m_smokeParticle = NULL;
		}
	}

	if (m_state == c_stateFlying) {
		GolVec3 position;
		m_projectile.GetWorldEntity()->GetBoundsCenter(&position);

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

				m_trail->AddSampleWithCenter(p_elapsedMs, positions, position);
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00451f30
void CannonballAction::Draw(GolD3DRenderDevice* p_renderer)
{
	if (m_state == c_stateFlying) {
		p_renderer->DrawBillboard(*m_billboard);
	}
}

// FUNCTION: LEGORACERS 0x00451f50
void CannonballAction::AdvanceState()
{
	switch (m_state) {
	case 2:
		break;
	case 3:
		m_state = c_stateDone;
		m_stateTimerMs = 0;
		m_projectile.CancelCollisionEvent();
		if (m_trail != NULL) {
			m_owner->m_trailManager->ReleaseTrail(m_trail);
			m_trail = NULL;
		}

		return;
	default:
		m_state = c_stateDone;
		m_stateTimerMs = 0;
		return;
	}

	m_state = c_stateFlying;
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
		CarVisuals* racerField = &m_ownerRacer->m_visuals;
		racerField->m_carEntity->GetPosition(&position);
		m_ownerRacer->m_visuals.m_carEntity->GetOrientationRow0(&direction);
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
	projectileParams.m_eventQueue = m_owner->m_raceState->GetEventQueue();
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
		target = m_emplacement->m_targetPosition;
		projectileParams.m_lifetimeMs = m_emplacement->m_lifetimeMs;
		m_billboard->SetPosition(m_emplacement->m_position);
		projectileParams.m_gravity = g_cannonballGravity * 3.0f;
		projectileParams.m_launchHeight = 0.0f;
		projectileParams.m_lifetimeMs = 5000;
		m_projectile.LaunchAtPosition(&projectileParams, &target);
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

	m_smokeParticle = m_owner->m_cutsceneAnimation->SpawnParticle("cannsmk", NULL, NULL, NULL);
	if (m_smokeParticle != NULL) {
		if (m_emplacement == NULL) {
			m_ownerRacer->m_physics.m_carEntity->GetAxes(&right, &forward);
			m_ownerRacer->m_physics.m_carEntity->GetPosition(&position);
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
			m_smokeParticle->m_particle->SetOrientation(&right, &forward);
		}
		if (m_smokeParticle->m_particle != NULL) {
			m_smokeParticle->m_particle->SetPosition(&position);
		}
	}

	trailParams.m_durationMs = 300;
	trailParams.m_sampleCount = 4;
	trailParams.m_pointCount = 4;
	trailParams.m_unk0x0c = 1;
	trailParams.m_unk0x10 = 0;
	trailParams.m_endScale = 0.1f;
	trailParams.m_endAlpha = 0.0f;
	m_trail = m_owner->m_trailManager->AcquireTrail(&trailParams);
	if (m_trail != NULL) {
		m_trail->SetColor(&g_cannonballTrailColor);

		GolMaterial* material = m_owner->m_renderer->FindMaterialByName("canstrk");
		if (material != NULL) {
			m_trail->SetMaterial(m_owner->m_renderer, material);
		}
	}

	if (m_emplacement != NULL) {
		GolVec3& positionBase = position;
		positionBase = m_emplacement->m_position;
	}
	else {
		CarVisuals* racerField = &m_ownerRacer->m_visuals;
		racerField->m_carEntity->GetPosition(&position);
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
void CannonballAction::OnHitRacer(Racer* p_racer)
{
	if (m_state == c_stateFlying) {
		if (p_racer->GetFlags() & Racer::c_flagShielded) {
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
			p_racer->m_visuals.SetReactionFlags(CarVisuals::c_reactionHit);
			p_racer->m_visuals.GetCarEntity()->GetPosition(&position);
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
