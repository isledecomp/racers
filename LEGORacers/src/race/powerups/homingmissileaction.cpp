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

const LegoFloat g_unk0x004b1688 = 160000.0f;

const LegoFloat g_unk0x004b1684 = 100.0f;

extern const LegoFloat g_unk0x004b165c;

extern const LegoFloat g_unk0x004b1660;

extern const LegoFloat g_scarNormalThreshold;

// GLOBAL: LEGORACERS 0x004b1664
const LegoFloat g_unk0x004b1664 = 200.0f;

// GLOBAL: LEGORACERS 0x004b1668
const LegoFloat g_unk0x004b1668 = 600.0f;

// GLOBAL: LEGORACERS 0x004b166c
const LegoFloat g_unk0x004b166c = 170.0f;

// GLOBAL: LEGORACERS 0x004b1670
const LegoFloat g_unk0x004b1670 = -32.1759987f;

// GLOBAL: LEGORACERS 0x004b1674
const LegoFloat g_unk0x004b1674 = 500.0f;

// GLOBAL: LEGORACERS 0x004b1678
const LegoFloat g_unk0x004b1678 = 4.0f;

// GLOBAL: LEGORACERS 0x004b168c
const LegoFloat g_unk0x004b168c = 0.70709997f;

// GLOBAL: LEGORACERS 0x004c1c64
ColorRGBA g_unk0x004c1c64 = {0xff, 0xff, 0xff, 0xc8};

// FUNCTION: LEGORACERS 0x00456430
RacePowerupManager::HomingMissileAction::HomingMissileAction()
{
	m_activeProjectile = 0;
	m_activeProjectile = &m_projectile;
	m_unk0x21c = 0;
	m_projectile.m_unk0x0f4 = 0;
}

// FUNCTION: LEGORACERS 0x004564b0
RacePowerupManager::HomingMissileAction::~HomingMissileAction()
{
	FUN_00456540();
}

// FUNCTION: LEGORACERS 0x00456510
void RacePowerupManager::HomingMissileAction::Initialize(GolExport** p_unk0x04, RaceSessionField0x32b4* p_unk0x08)
{
	if (m_state != 0) {
		FUN_00456540();
	}

	m_golExportPtr = p_unk0x04;
	m_collisionWorld = p_unk0x08;
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x00456540
void RacePowerupManager::HomingMissileAction::FUN_00456540()
{
	Deactivate();
	m_state = 0;
	m_unk0x21c = 0;
}

// FUNCTION: LEGORACERS 0x00456560
void RacePowerupManager::HomingMissileAction::Activate(
	GolAnimatedEntity* p_unk0x04,
	GolAnimatedEntity*,
	RaceState::Racer* p_racer,
	LegoU32 p_unk0x10
)
{
	m_state = 2;
	m_stateTimerMs = 3000;
	m_unk0x220 = p_unk0x10;
	m_ownerRacer = p_racer;
	m_targetRacer = NULL;

	GolAnimatedEntity* projectile = &m_unk0x128;
	projectile->FUN_0040d550(
		p_unk0x04->GetModel(0),
		p_unk0x04->VTable0x58(0),
		p_unk0x04->GetModelPart(0),
		p_unk0x04->GetModelDistance(0)
	);

	SoundVector position;
	RaceState::Racer::Field0x018* racerEntities = &m_ownerRacer->m_unk0x018;
	racerEntities->m_unk0x044->VTable0x04(&position);
	projectile->VTable0x08(position);

	m_ownerRacer->m_unk0x3e8.m_unk0x13c->CopyOrientationTo(&projectile->GetOrientation());
	projectile->SetFlags(projectile->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	projectile->FUN_0040dad0(p_unk0x10);
	projectile->SetFlags(projectile->GetFlags() & ~GolAnimatedEntity::c_flagLoopCurrentPart);

	m_soundSource->PlaySpatialSoundById(c_sound0x33, &position, g_unk0x004b165c, g_unk0x004b1660, 1.0f, 1.0f);
}

// FUNCTION: LEGORACERS 0x00456680
void RacePowerupManager::HomingMissileAction::FUN_00456680()
{
	GolVec3 position;
	{
		RaceState::Racer::Field0x018* racerField = &m_ownerRacer->m_unk0x018;
		racerField->m_unk0x044->VTable0x04(&position);
	}

	GolVec3 direction;
	m_ownerRacer->m_unk0x018.m_unk0x044->GetOrientationRow0(&direction);

	RaceState* raceState = m_owner0x01c->m_raceState;
	LegoU32 i = 0;
	m_targetRacer = raceState->FUN_0043c6e0(&position, &direction, g_unk0x004b1684, g_unk0x004b1688, g_unk0x004b168c);

	for (; i < m_unk0x220; i++) {
		if (m_targetRacer == NULL) {
			break;
		}

		m_targetRacer =
			raceState
				->FUN_0043c7f0(m_targetRacer, &position, &direction, g_unk0x004b1684, g_unk0x004b1688, g_unk0x004b168c);
	}

	PowerupProjectile::Params projectileParams;
	projectileParams.m_worldEntity = &m_unk0x128;
	projectileParams.m_collisionWorld = m_collisionWorld;
	projectileParams.m_gravity = g_unk0x004b1670;
	projectileParams.m_eventQueue = m_owner0x01c->m_raceState->GetEventQueue();
	projectileParams.m_targetOffset.m_x = 0.0f;
	projectileParams.m_targetOffset.m_y = 0.0f;
	projectileParams.m_targetOffset.m_z = 0.0f;
	projectileParams.m_speed = g_unk0x004b166c;
	projectileParams.m_lifetimeMs = c_timer0x157c;
	projectileParams.m_launchHeight = g_unk0x004b1678;

	if (m_targetRacer == NULL) {
		GolVec3 velocity;
		velocity.m_x = 0.0f;
		velocity.m_y = 0.0f;
		velocity.m_z = 0.0f;

		GolVec3 scaledDirection;
		scaledDirection.m_x = direction.m_x * g_unk0x004b1674;
		scaledDirection.m_y = direction.m_y * g_unk0x004b1674;
		scaledDirection.m_z = direction.m_z * g_unk0x004b1674;

		GolVec3 target;
		target.m_x = position.m_x + scaledDirection.m_x;
		target.m_y = position.m_y + scaledDirection.m_y;
		target.m_z = position.m_z + scaledDirection.m_z + g_unk0x004b1678;

		if (m_unk0x220 == 0) {
			target.m_x += direction.m_y * 150.0f;
			target.m_y += (-direction.m_x) * 150.0f;
		}
		else if (m_unk0x220 == 2) {
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
void RacePowerupManager::HomingMissileAction::Deactivate()
{
	m_projectile.Deactivate();
	m_unk0x128.VTable0x54();
	m_state = 1;
	m_stateTimerMs = 0;

	if (m_owner0x01c != NULL && m_unk0x21c != NULL) {
		m_owner0x01c->m_trailManager->FUN_00493a10(m_unk0x21c);
		m_unk0x21c = NULL;
	}
}

// STUB: LEGORACERS 0x004568f0
void RacePowerupManager::HomingMissileAction::Update(LegoU32 p_elapsedMs)
{
	GolVec3 direction;
	GolVec3 up;

	if (m_state == c_state0x02) {
		m_unk0x128.VTable0x10(p_elapsedMs);
		if (m_unk0x128.FUN_0040e360()) {
			AdvanceState();
		}
		else {
			GolVec3 position;
			RaceState::Racer::Field0x018* racerField = &m_ownerRacer->m_unk0x018;
			racerField->m_unk0x044->VTable0x04(&position);
			m_unk0x128.VTable0x08(position);
			m_unk0x128.CopyOrientationFrom(*m_ownerRacer->m_unk0x3e8.m_unk0x13c);
			return;
		}
	}

	if (m_state == c_state0x03) {
		m_unk0x128.VTable0x10(p_elapsedMs);
		m_projectile
			.UpdateTargeting(p_elapsedMs, m_owner0x01c->m_raceState, g_unk0x004b1684, g_unk0x004b1688, g_unk0x004b168c);

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
			}
			else {
				m_soundSource
					->PlaySpatialSoundById(c_sound0x32, &position, g_unk0x004b1664, g_unk0x004b1668, 1.0f, 1.0f);
			}

			if (!skipBurst) {
				GolVec3 hitNormal = m_projectile.GetHitNormal();
				LegoBool32 upwardHit = FALSE;
				if (projectileState == PowerupProjectile::c_stateHitWorld && hitNormal.m_z > g_scarNormalThreshold) {
					upwardHit = TRUE;
				}

				m_owner0x01c->FUN_0045b4d0(&position, upwardHit, m_ownerRacer);
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

			return;
		}

		m_unk0x128.VTable0x48(&direction, &up);
		direction = m_projectile.m_direction;
		m_unk0x128.VTable0x40(direction, up);

		GolVec3 position;
		m_unk0x128.VTable0x04(&position);

		if (m_unk0x21c != NULL) {
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

				m_unk0x21c->FUN_00492ee0(p_elapsedMs, positions, position);
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00456ce0
void RacePowerupManager::HomingMissileAction::Draw(GolD3DRenderDevice* p_renderer)
{
	if (m_state == c_state0x02) {
		p_renderer->VTable0x94(&m_unk0x128);
	}
	else if (m_state == c_state0x03) {
		GolSceneNode* node = m_unk0x128.VTable0x58(0);
		GolTransformBase* transform = node->VTable0x18(c_transformNodeIndex1);

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
		transform->VTable0x28(&direction, &up);

		p_renderer->VTable0x94(&m_unk0x128);
	}
}

// FUNCTION: LEGORACERS 0x00456db0
void RacePowerupManager::HomingMissileAction::AdvanceState()
{
	switch (m_state) {
	case c_state0x02: {
		m_state = c_state0x03;
		m_stateTimerMs = c_timer0x157c;
		m_unk0x128.VTable0x5c(0);

		GolAnimatedEntity* animatedEntity = &m_unk0x128;
		GolSceneNode* node = animatedEntity->VTable0x58(0);
		GolTransformBase* transform = node->VTable0x18(c_transformNodeIndex1);

		GolVec3 position;
		transform->GetPosition(&position);

		GolVec3 up;
		transform->GetUp(&up);

		GolVec3 right;
		transform->GetRight(&right);

		LegoFloat scale = animatedEntity->GetModel(0)->GetScale() * animatedEntity->GetUnk0x58();
		position.m_x *= scale;
		position.m_y *= scale;
		position.m_z *= scale;

		GolVec3 worldPosition;
		animatedEntity->VTable0x2c(position, &worldPosition);

		GolVec3 worldBasis[2];
		animatedEntity->VTable0x34(up, &worldBasis[1]);
		animatedEntity->VTable0x34(right, &worldBasis[0]);

		animatedEntity->VTable0x08(worldPosition);
		animatedEntity->VTable0x40(worldBasis[1], worldBasis[0]);
		animatedEntity->VTable0x4c(0);

		LegoU32 flags = animatedEntity->GetFlags();
		flags &= ~GolAnimatedEntity::c_flagPartAnimation;
		animatedEntity->SetFlags(flags);

		FUN_00456680();

		RaceTrailManager::Trail::Params params;
		params.m_unk0x04 = 4;
		params.m_unk0x08 = 4;
		RacePowerupManager* owner = m_owner0x01c;
		params.m_unk0x00 = 0x190;
		params.m_unk0x0c = 1;
		params.m_unk0x10 = 0;
		params.m_unk0x14 = 0.1f;
		params.m_unk0x18 = 0.0f;

		RaceTrailManager* trailManager = owner->m_trailManager;
		m_unk0x21c = trailManager->FUN_004939b0(&params);
		if (m_unk0x21c != NULL) {
			m_unk0x21c->FUN_00492ab0(&g_unk0x004c1c64);
			DuskwindBananaRelic0x24* material = m_owner0x01c->m_renderer->FindMaterialByName("mslstrk");
			if (material != NULL) {
				m_unk0x21c->FUN_00492a90(m_owner0x01c->m_renderer, material);
			}
		}
		break;
	}
	case c_state0x03:
		m_state = c_state0x06;
		m_stateTimerMs = 0;
		m_projectile.CancelCollisionEvent();
		if (m_unk0x21c != NULL) {
			m_owner0x01c->m_trailManager->FUN_00493a10(m_unk0x21c);
			m_unk0x21c = NULL;
		}
		break;
	case c_state0x04:
		m_state = c_state0x06;
		m_stateTimerMs = 0;
		break;
	}
}

// FUNCTION: LEGORACERS 0x00456fa0
void RacePowerupManager::HomingMissileAction::OnHitRacer(RaceState::Racer* p_racer)
{
	if (m_state == c_state0x03) {
		if (p_racer->GetUnk0xd04() & c_racerFlags0xd04Bit0) {
			p_racer->PlayReaction(TRUE);
			p_racer->AbsorbShieldHit();
			if (p_racer->m_shieldLevel >= 2) {
				m_projectile.Deflect(p_racer);
				m_ownerRacer = p_racer;
			}
		}
		else {
			p_racer->m_unk0x3e8.VTable0x24(2.0f, 0.007f, 0);

			if (m_ownerRacer != NULL) {
				m_ownerRacer->PlayReaction(TRUE);
			}

			p_racer->PlayReaction(FALSE);
			p_racer->DropWhiteBrick();
			p_racer->m_unk0x018.m_unk0x384 |= c_racerField0x018Flags0x384Bit1;

			SoundVector position;
			p_racer->m_unk0x018.m_unk0x044->VTable0x04(&position);
			m_soundSource->PlaySpatialSoundById(c_sound0x32, &position, g_unk0x004b1664, g_unk0x004b1668, 1.0f, 1.0f);
		}
	}
}

// FUNCTION: LEGORACERS 0x00458630
RacePowerupManager::PowerupAction* RacePowerupManager::HomingMissileAction::Destroy(undefined4 p_flags)
{
	HomingMissileAction* result = this;
	if (p_flags & 2) {
		if (p_flags & 1) {
			delete[] this;
		}

		return result;
	}

	this->~HomingMissileAction();
	if (p_flags & 1) {
		::operator delete(result);
	}

	return result;
}
