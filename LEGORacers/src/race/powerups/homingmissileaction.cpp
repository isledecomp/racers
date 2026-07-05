#include "race/powerups/homingmissileaction.h"

#include "audio/soundnode.h"
#include "audio/spatialsoundinstance.h"
#include "decomp.h"
#include "golmodelbase.h"
#include "golscenenode.h"
#include "goltransformbase.h"
#include "menu/runtime/cutsceneparticle.h"
#include "race/powerups/racepowerupmanager.h"
#include "race/racesoundsource.h"
#include "render/gold3drenderdevice.h"
#include "world/golworlddatabase.h"

#include <float.h>
#include <math.h>

// GLOBAL: LEGORACERS 0x004b1654
const LegoFloat g_missileTargetHeightOffset = 5.0f;

// GLOBAL: LEGORACERS 0x004b165c
extern const LegoFloat g_missileFireSoundMinDistance = 30.0f;

// GLOBAL: LEGORACERS 0x004b1660
extern const LegoFloat g_missileFireSoundMaxDistance = 300.0f;

// GLOBAL: LEGORACERS 0x004b1684
const LegoFloat g_missileTargetMinDistanceSquared = 100.0f;

// GLOBAL: LEGORACERS 0x004b1688
const LegoFloat g_missileTargetMaxDistanceSquared = 160000.0f;

extern const LegoFloat g_scarNormalThreshold;

// GLOBAL: LEGORACERS 0x004b1664
const LegoFloat g_missileExplodeSoundMinDistance = 200.0f;

// GLOBAL: LEGORACERS 0x004b1668
const LegoFloat g_missileExplodeSoundMaxDistance = 600.0f;

// GLOBAL: LEGORACERS 0x004b166c
const LegoFloat g_missileSpeed = 170.0f;

// GLOBAL: LEGORACERS 0x004b1670
const LegoFloat g_missileGravity = -32.1759987f;

// GLOBAL: LEGORACERS 0x004b1674
const LegoFloat g_missileAimAheadDistance = 500.0f;

// GLOBAL: LEGORACERS 0x004b1678
const LegoFloat g_missileLaunchHeight = 4.0f;

// GLOBAL: LEGORACERS 0x004b168c
const LegoFloat g_missileTargetConeCosine = 0.70709997f;

// GLOBAL: LEGORACERS 0x004c1c64
ColorRGBA g_missileTrailColor = {0xff, 0xff, 0xff, 0xc8};

// FUNCTION: LEGORACERS 0x00456430
HomingMissileAction::HomingMissileAction()
{
	m_activeProjectile = 0;
	m_activeProjectile = &m_projectile;
	m_trail = 0;
	m_projectile.m_unk0x0f4 = 0;
}

// FUNCTION: LEGORACERS 0x004564b0
HomingMissileAction::~HomingMissileAction()
{
	Shutdown();
}

// FUNCTION: LEGORACERS 0x00456510
void HomingMissileAction::Initialize(RacePowerupManager* p_manager, TriggerWorld* p_collisionWorld)
{
	if (m_state != c_stateUnloaded) {
		Shutdown();
	}

	m_owner = p_manager;
	m_collisionWorld = p_collisionWorld;
	m_state = c_stateReady;
}

// FUNCTION: LEGORACERS 0x00456540
void HomingMissileAction::Shutdown()
{
	Deactivate();
	m_state = c_stateUnloaded;
	m_trail = 0;
}

// FUNCTION: LEGORACERS 0x00456560
void HomingMissileAction::Activate(
	GolAnimatedEntity* p_missileTemplate,
	GolAnimatedEntity*,
	Racer* p_racer,
	LegoU32 p_missileIndex
)
{
	m_state = c_stateArmed;
	m_stateTimerMs = 3000;
	m_missileIndex = p_missileIndex;
	m_ownerRacer = p_racer;
	m_targetRacer = NULL;

	GolAnimatedEntity* projectile = &m_missileEntity;
	projectile->SetModel(
		p_missileTemplate->GetModel(0),
		p_missileTemplate->GetSceneNode(0),
		p_missileTemplate->GetModelPart(0),
		p_missileTemplate->GetModelDistance(0)
	);

	SoundVector position;
	CarVisuals* racerEntities = &m_ownerRacer->m_visuals;
	racerEntities->m_carEntity->GetPosition(&position);
	projectile->SetPosition(position);

	m_ownerRacer->m_physics.m_carEntity->CopyOrientationTo(&projectile->GetOrientation());
	projectile->SetFlags(projectile->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	projectile->PlayPart(p_missileIndex);
	projectile->SetFlags(projectile->GetFlags() & ~GolAnimatedEntity::c_flagLoopCurrentPart);

	m_soundSource->PlaySpatialSoundById(
		c_soundFire,
		&position,
		g_missileFireSoundMinDistance,
		g_missileFireSoundMaxDistance,
		1.0f,
		1.0f
	);
}

// FUNCTION: LEGORACERS 0x00456680
void HomingMissileAction::LaunchProjectile()
{
	GolVec3 position;
	{
		CarVisuals* racerField = &m_ownerRacer->m_visuals;
		racerField->m_carEntity->GetPosition(&position);
	}

	GolVec3 direction;
	m_ownerRacer->m_visuals.m_carEntity->GetOrientationRow0(&direction);

	RaceState* raceState = m_owner->m_raceState;
	LegoU32 i = 0;
	m_targetRacer = raceState->FindRacerInCone(
		&position,
		&direction,
		g_missileTargetMinDistanceSquared,
		g_missileTargetMaxDistanceSquared,
		g_missileTargetConeCosine
	);

	for (; i < m_missileIndex; i++) {
		if (m_targetRacer == NULL) {
			break;
		}

		m_targetRacer = raceState->FindNextRacerInCone(
			m_targetRacer,
			&position,
			&direction,
			g_missileTargetMinDistanceSquared,
			g_missileTargetMaxDistanceSquared,
			g_missileTargetConeCosine
		);
	}

	PowerupProjectile::Params projectileParams;
	projectileParams.m_worldEntity = &m_missileEntity;
	projectileParams.m_collisionWorld = m_collisionWorld;
	projectileParams.m_gravity = g_missileGravity;
	projectileParams.m_eventQueue = m_owner->m_raceState->GetEventQueue();
	projectileParams.m_targetOffset.m_x = 0.0f;
	projectileParams.m_targetOffset.m_y = 0.0f;
	projectileParams.m_targetOffset.m_z = 0.0f;
	projectileParams.m_speed = g_missileSpeed;
	projectileParams.m_lifetimeMs = c_flightTimeMs;
	projectileParams.m_launchHeight = g_missileLaunchHeight;

	if (m_targetRacer == NULL) {
		GolVec3 velocity;
		velocity.m_x = 0.0f;
		velocity.m_y = 0.0f;
		velocity.m_z = 0.0f;

		GolVec3 scaledDirection;
		scaledDirection.m_x = direction.m_x * g_missileAimAheadDistance;
		scaledDirection.m_y = direction.m_y * g_missileAimAheadDistance;
		scaledDirection.m_z = direction.m_z * g_missileAimAheadDistance;

		GolVec3 target;
		target.m_x = position.m_x + scaledDirection.m_x;
		target.m_y = position.m_y + scaledDirection.m_y;
		target.m_z = position.m_z + scaledDirection.m_z + g_missileTargetHeightOffset;

		if (m_missileIndex == 0) {
			target.m_x += direction.m_y * 150.0f;
			target.m_y += (-direction.m_x) * 150.0f;
		}
		else if (m_missileIndex == 2) {
			target.m_x += (-direction.m_y) * 150.0f;
			target.m_y += direction.m_x * 150.0f;
		}

		PowerupProjectile* projectile = &m_projectile;
		projectile->LaunchAtPoint(&projectileParams, m_ownerRacer, &target, &velocity, FALSE);
	}
	else {
		PowerupProjectile* projectile = &m_projectile;
		projectile->LaunchAtRacer(&projectileParams, m_ownerRacer, m_targetRacer, FALSE, FALSE);
	}

	m_projectile.m_maxSpiralAmplitude = 4.0f;
	m_projectile.m_spiralRate = 10.0f;
	m_projectile.StartHoming();
}

// FUNCTION: LEGORACERS 0x004568a0
void HomingMissileAction::Deactivate()
{
	m_projectile.Deactivate();
	m_missileEntity.ResetModelState();
	m_state = c_stateReady;
	m_stateTimerMs = 0;

	if (m_owner != NULL && m_trail != NULL) {
		m_owner->m_trailManager->ReleaseTrail(m_trail);
		m_trail = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004568f0
void HomingMissileAction::Update(LegoU32 p_elapsedMs)
{
	GolVec3 direction;
	GolVec3 up;

	if (m_state == c_stateArmed) {
		m_missileEntity.Update(p_elapsedMs);
		if (m_missileEntity.IsPartAnimationDone()) {
			AdvanceState();
		}
		else {
			GolVec3 position;
			CarVisuals* racerField = &m_ownerRacer->m_visuals;
			racerField->m_carEntity->GetPosition(&position);
			m_missileEntity.SetPosition(position);
			m_missileEntity.CopyOrientationFrom(*m_ownerRacer->m_physics.m_carEntity);
			return;
		}
	}

	if (m_state == c_stateFlying) {
		m_missileEntity.Update(p_elapsedMs);
		m_projectile.UpdateTargeting(
			p_elapsedMs,
			m_owner->m_raceState,
			g_missileTargetMinDistanceSquared,
			g_missileTargetMaxDistanceSquared,
			g_missileTargetConeCosine
		);

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
			}
			else {
				m_soundSource->PlaySpatialSoundById(
					c_soundExplode,
					&position,
					g_missileExplodeSoundMinDistance,
					g_missileExplodeSoundMaxDistance,
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

				m_owner->FUN_0045b4d0(&position, upwardHit, m_ownerRacer);
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

			return;
		}

		m_missileEntity.GetAxes(&direction, &up);
		direction = m_projectile.m_direction;
		m_missileEntity.SetDirectionUp(direction, up);

		GolVec3 position;
		m_missileEntity.GetPosition(&position);

		if (m_trail != NULL) {
			GolVec3 velocity;
			m_projectile.GetVelocity(&velocity);

			GolVec2 perpendicular;
			perpendicular.m_x = velocity.m_y;
			perpendicular.m_y = -velocity.m_x;
			if (perpendicular.m_y != 0.0f || perpendicular.m_x != 0.0f) {
				GolMath::NormalizeVector2(perpendicular, &perpendicular);
				perpendicular.m_x *= 1.0f;
				perpendicular.m_y *= 1.0f;

				GolVec3 positions[4];
				positions[0].m_x = position.m_x - perpendicular.m_x * 0.5f;
				positions[0].m_y = position.m_y - perpendicular.m_y * 0.5f;
				positions[0].m_z = position.m_z + 1.0f * 0.5f;
				positions[1].m_x = positions[0].m_x;
				positions[1].m_y = positions[0].m_y;
				positions[1].m_z = positions[0].m_z - 1.0f;
				positions[2].m_x = positions[0].m_x + perpendicular.m_x;
				positions[2].m_y = positions[0].m_y + perpendicular.m_y;
				positions[2].m_z = positions[1].m_z;
				positions[3].m_x = positions[2].m_x;
				positions[3].m_y = positions[2].m_y;
				positions[3].m_z = positions[1].m_z + 1.0f;

				m_trail->AddSampleWithCenter(p_elapsedMs, positions, position);
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00456ce0
void HomingMissileAction::Draw(GolD3DRenderDevice* p_renderer)
{
	if (m_state == c_stateArmed) {
		p_renderer->DrawModelEntity(&m_missileEntity);
	}
	else if (m_state == c_stateFlying) {
		GolSceneNode* node = m_missileEntity.GetSceneNode(0);
		GolTransformBase* transform = node->GetTransform(c_transformNodeIndex1);

		GolVec3 position;
		position.m_x = 0.0f;
		position.m_y = 0.0f;
		position.m_z = 0.0f;
		transform->SetPosition(&position);

		GolVec3 direction;
		direction.m_x = 1.0f;
		direction.m_y = 0.0f;
		direction.m_z = 0.0f;

		GolVec3 up;
		up.m_x = 0.0f;
		up.m_y = 0.0f;
		up.m_z = 1.0f;
		transform->SetRightDirection(&direction, &up);

		p_renderer->DrawModelEntity(&m_missileEntity);
	}
}

// FUNCTION: LEGORACERS 0x00456db0
void HomingMissileAction::AdvanceState()
{
	switch (m_state) {
	case c_stateArmed: {
		m_state = c_stateFlying;
		m_stateTimerMs = c_flightTimeMs;
		m_missileEntity.ApplyPartAnimation(0);

		GolAnimatedEntity* animatedEntity = &m_missileEntity;
		GolSceneNode* node = animatedEntity->GetSceneNode(0);
		GolTransformBase* transform = node->GetTransform(c_transformNodeIndex1);

		GolVec3 position;
		transform->GetPosition(&position);

		GolVec3 up;
		transform->GetUp(&up);

		GolVec3 right;
		transform->GetRight(&right);

		LegoFloat scale = animatedEntity->GetModel(0)->GetScale() * animatedEntity->GetScale();
		position.m_x *= scale;
		position.m_y *= scale;
		position.m_z *= scale;

		GolVec3 worldPosition;
		animatedEntity->LocalToWorld(position, &worldPosition);

		GolVec3 worldBasis[2];
		animatedEntity->RotateToWorld(up, &worldBasis[1]);
		animatedEntity->RotateToWorld(right, &worldBasis[0]);

		animatedEntity->SetPosition(worldPosition);
		animatedEntity->SetDirectionUp(worldBasis[1], worldBasis[0]);
		animatedEntity->ComputeBoundsFromModel(0);

		LegoU32 flags = animatedEntity->GetFlags();
		flags &= ~GolAnimatedEntity::c_flagPartAnimation;
		animatedEntity->SetFlags(flags);

		LaunchProjectile();

		RaceTrailManager::Trail::Params params;
		params.m_sampleCount = 4;
		params.m_pointCount = 4;
		RacePowerupManager* owner = m_owner;
		params.m_durationMs = 0x190;
		params.m_unk0x0c = 1;
		params.m_unk0x10 = 0;
		params.m_endScale = 0.1f;
		params.m_endAlpha = 0.0f;

		RaceTrailManager* trailManager = owner->m_trailManager;
		m_trail = trailManager->AcquireTrail(&params);
		if (m_trail != NULL) {
			m_trail->SetColor(&g_missileTrailColor);
			GolMaterial* material = m_owner->m_renderer->FindMaterialByName("mslstrk");
			if (material != NULL) {
				m_trail->SetMaterial(m_owner->m_renderer, material);
			}
		}
		break;
	}
	case c_stateFlying:
		m_state = c_stateDone;
		m_stateTimerMs = 0;
		m_projectile.CancelCollisionEvent();
		if (m_trail != NULL) {
			m_owner->m_trailManager->ReleaseTrail(m_trail);
			m_trail = NULL;
		}
		break;
	case c_state0x04:
		m_state = c_stateDone;
		m_stateTimerMs = 0;
		break;
	}
}

// FUNCTION: LEGORACERS 0x00456fa0
void HomingMissileAction::OnHitRacer(Racer* p_racer)
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
			p_racer->m_physics.StartSpin(2.0f, 0.007f, 0);

			if (m_ownerRacer != NULL) {
				m_ownerRacer->PlayReaction(TRUE);
			}

			p_racer->PlayReaction(FALSE);
			p_racer->DropWhiteBrick();
			p_racer->m_visuals.m_reactionFlags |= CarVisuals::c_reactionHit;

			SoundVector position;
			p_racer->m_visuals.m_carEntity->GetPosition(&position);
			m_soundSource->PlaySpatialSoundById(
				c_soundExplode,
				&position,
				g_missileExplodeSoundMinDistance,
				g_missileExplodeSoundMaxDistance,
				1.0f,
				1.0f
			);
		}
	}
}
