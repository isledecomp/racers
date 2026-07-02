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

const LegoFloat g_dynamiteThrowDistance = -90.0f;

const LegoFloat g_dynamiteSparkOffsetScale = -0.727681994f;

const LegoFloat g_dynamiteSoundMaxDistance = 600.0f;

const LegoFloat g_dynamiteSoundMinDistance = 200.0f;

const LegoFloat g_dynamiteFuseSoundMaxDistance = 300.0f;

const LegoFloat g_dynamiteFuseSoundMinDistance = 30.0f;

const LegoFloat g_dynamiteLaunchHeight = 5.0f;

extern LegoFloat g_cosineTable[1024];

extern const LegoFloat g_item0x40RadiansToTableIndex;

extern const LegoFloat g_negativeRadiansToTableIndex;

extern LegoU16 g_randomTable[1024];

extern LegoU32 g_randomTableIndex;

// FUNCTION: LEGORACERS 0x00452dd0
RacePowerupManager::DynamiteAction::DynamiteAction()
{
	m_manager = 0;
	m_cutsceneAnimation = 0;
	m_sparkParticle = 0;
	m_sound = 0;
	m_targetRacer = 0;
	m_tumbleAngle = 0;
}

// FUNCTION: LEGORACERS 0x00452e50
RacePowerupManager::DynamiteAction::~DynamiteAction()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00452eb0
void RacePowerupManager::DynamiteAction::Destroy()
{
	Deactivate();
	m_modelEntity.VTable0x54();
	m_manager = 0;
	m_cutsceneAnimation = 0;
	m_sparkParticle = 0;
	m_sound = 0;
}

// FUNCTION: LEGORACERS 0x00452ee0
void RacePowerupManager::DynamiteAction::Initialize(
	RaceState* p_raceState,
	RaceSessionField0x32b4* p_collisionWorld,
	RacePowerupManager* p_manager,
	CutsceneAnimation* p_cutsceneAnimation,
	GolModelEntity* p_model
)
{
	m_raceState0x018 = p_raceState;
	m_collisionWorld = p_collisionWorld;
	m_manager = p_manager;
	m_cutsceneAnimation = p_cutsceneAnimation;

	m_modelEntity.VTable0x50(p_model->GetModel(0), p_model->GetModelDistance(0));

	for (LegoU32 i = 1; i < 3; i++) {
		GolModelBase* model = p_model->GetModel(i);
		if (model != NULL) {
			m_modelEntity.FUN_10027c50(model, p_model->GetModelDistance(i));
		}
	}

	m_state = 1;
}

// FUNCTION: LEGORACERS 0x00452f60
LegoU32 RacePowerupManager::DynamiteAction::Activate(RaceState::Racer* p_racer, RaceState::Racer* p_targetRacer)
{
	m_ownerRacer = p_racer;
	LegoU32 result = 0;
	m_targetRacer = p_targetRacer;
	m_state = 2;
	m_stateTimerMs = result;
	m_tumbleAngle = 0.0f;
	return result;
}

// FUNCTION: LEGORACERS 0x00452f90
void RacePowerupManager::DynamiteAction::Deactivate()
{
	if (m_sound != NULL) {
		m_soundSource->ReleaseSound(m_soundResource);
		m_sound = NULL;
	}

	m_projectile.Deactivate();

	if (m_sparkParticle != NULL) {
		m_cutsceneAnimation->FUN_00489f30(m_sparkParticle);
		m_sparkParticle = NULL;
	}

	m_targetRacer = NULL;
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x00452ff0
void RacePowerupManager::DynamiteAction::Update(LegoU32 p_elapsedMs)
{
	if (m_state == c_stateDone) {
		return;
	}

	SoundVector position;
	m_modelEntity.VTable0x04(&position);

	if (m_projectile.GetState() != 0) {
		LegoS32 projectileState = m_projectile.Update(p_elapsedMs);
		if (projectileState != PowerupProjectile::c_stateFlying) {
			if (projectileState == PowerupProjectile::c_stateHitWorld) {
				const GolVec3* projectilePosition = &m_projectile.GetHitPosition();
				position.m_x = projectilePosition->m_x;
				position.m_y = projectilePosition->m_y;
				position.m_z = projectilePosition->m_z;
			}

			m_manager->SpawnSpikeExplosion(&position, TRUE, m_ownerRacer);
			m_state = c_stateSecondBlast;
			m_stateTimerMs = c_blastIntervalMs;
			m_soundSource->PlaySpatialSoundById(
				c_soundExplode,
				&position,
				g_dynamiteSoundMinDistance,
				g_dynamiteSoundMaxDistance,
				1.0f,
				1.0f
			);

			if (m_sound != NULL) {
				m_soundSource->ReleaseSound(m_soundResource);
				m_sound = NULL;
			}

			m_projectile.Deactivate();

			if (m_sparkParticle != NULL) {
				m_cutsceneAnimation->FUN_00489f30(m_sparkParticle);
				m_sparkParticle = NULL;
			}
		}
	}

	m_tumbleAngle += static_cast<LegoFloat>(p_elapsedMs) * 0.012f;

	LegoS32 tableIndex = (0xffffff00 - static_cast<LegoS32>(m_tumbleAngle * g_negativeRadiansToTableIndex)) & 0x3ff;
	GolVec3 up;
	up.m_x = g_cosineTable[tableIndex];
	up.m_y = 0.0f;

	tableIndex = static_cast<LegoS32>(m_tumbleAngle * g_item0x40RadiansToTableIndex) & 0x3ff;
	up.m_z = g_cosineTable[tableIndex];

	GolVec3 direction;
	direction.m_x = -up.m_z;
	direction.m_y = 0.0f;
	direction.m_z = up.m_x;
	m_modelEntity.VTable0x40(direction, up);

	if (m_sparkParticle != NULL) {
		position.m_x += up.m_x * g_dynamiteSparkOffsetScale;
		position.m_y += up.m_y * 0.155761003f;
		position.m_z += up.m_z * 5.17852306f;

		if (m_sparkParticle->m_particle != NULL) {
			m_sparkParticle->m_particle->FUN_00489660(&position);
		}
	}

	if (m_sound != NULL) {
		m_sound->SetPosition(&position);
	}

	PowerupActionBase::Update(p_elapsedMs);
}

// FUNCTION: LEGORACERS 0x00453210
void RacePowerupManager::DynamiteAction::Draw(GolD3DRenderDevice* p_renderer)
{
	if (m_state != c_stateDone && m_state != c_stateSecondBlast && m_state != c_stateThirdBlast) {
		p_renderer->VTable0x94(&m_modelEntity);
	}
}

// FUNCTION: LEGORACERS 0x00453240
void RacePowerupManager::DynamiteAction::AdvanceState()
{
	GolVec3 position;
	m_modelEntity.VTable0x04(&position);

	switch (m_state) {
	case c_stateArmed: {
		PowerupProjectile::Params projectileParams;
		projectileParams.m_worldEntity = &m_modelEntity;
		projectileParams.m_collisionWorld = m_collisionWorld;
		projectileParams.m_gravity = -32.1759987f;
		projectileParams.m_eventQueue = m_manager->GetRaceState()->GetEventQueue();
		projectileParams.m_targetOffset.m_x = 0.0f;
		projectileParams.m_targetOffset.m_y = 0.0f;
		projectileParams.m_targetOffset.m_z = 0.0f;
		projectileParams.m_speed = 40.0f;
		projectileParams.m_lifetimeMs = c_flightLifetimeMs;
		projectileParams.m_launchHeight = g_dynamiteLaunchHeight;

		RaceState::Racer::Field0x018* racerField = &m_ownerRacer->m_unk0x018;
		GolVec3 racerPosition;
		racerField->m_carEntity->VTable0x04(&racerPosition);

		GolVec3 forward;
		m_ownerRacer->m_unk0x018.m_carEntity->GetOrientationRow0(&forward);

		if (m_targetRacer != NULL) {
			m_projectile.LaunchAtRacer(&projectileParams, m_ownerRacer, m_targetRacer, TRUE, TRUE);
		}
		else {
			GolVec3 targetVelocity;
			targetVelocity.m_x = 0.0f;
			targetVelocity.m_y = 0.0f;
			targetVelocity.m_z = 0.0f;

			GolVec3 target;
			target.m_x = racerPosition.m_x + forward.m_x * g_dynamiteThrowDistance;
			target.m_y = racerPosition.m_y + forward.m_y * g_dynamiteThrowDistance;
			target.m_z = racerPosition.m_z + forward.m_z * g_dynamiteThrowDistance + 5.0f;

			m_projectile.LaunchAtPoint(&projectileParams, m_ownerRacer, &target, &targetVelocity, TRUE);
		}

		m_state = c_stateThrown;
		m_stateTimerMs = c_fuseDurationMs;
		m_sparkParticle = m_cutsceneAnimation->FUN_00489d70("dynsprk", NULL, NULL, NULL);
		if (m_sparkParticle != NULL) {
			position.m_x -= 0.727681994f;
			position.m_y += 0.155761003f;
			position.m_z += 5.17852306f;

			if (m_sparkParticle->m_particle != NULL) {
				m_sparkParticle->m_particle->FUN_00489660(&position);
			}
		}

		m_sound = m_soundSource->AcquireSoundById(c_soundFuse);
		if (m_sound != NULL) {
			m_sound->SetDistanceRange(g_dynamiteFuseSoundMinDistance, g_dynamiteFuseSoundMaxDistance);
			m_sound->SetPosition(position);
			m_sound->Play(TRUE);
		}
		break;
	}
	case c_stateThrown:
		m_manager->SpawnSpikeExplosion(&position, TRUE, m_ownerRacer);
		m_state = c_stateDone;
		m_stateTimerMs = 0;
		break;
	case c_stateSecondBlast:
		g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
		position.m_x +=
			static_cast<LegoS32>(g_randomTable[g_randomTableIndex]) % c_randomOffsetRange - c_randomOffsetCenter;

		g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
		position.m_y +=
			static_cast<LegoS32>(g_randomTable[g_randomTableIndex]) % c_randomOffsetRange - c_randomOffsetCenter;
		m_manager->SpawnSpikeExplosion(&position, TRUE, m_ownerRacer);
		m_state = c_stateThirdBlast;
		m_stateTimerMs = c_blastIntervalMs;
		break;
	case c_stateThirdBlast:
		g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
		position.m_x +=
			static_cast<LegoS32>(g_randomTable[g_randomTableIndex]) % c_randomOffsetRange - c_randomOffsetCenter;

		g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
		position.m_y +=
			static_cast<LegoS32>(g_randomTable[g_randomTableIndex]) % c_randomOffsetRange - c_randomOffsetCenter;
		m_manager->SpawnSpikeExplosion(&position, TRUE, m_ownerRacer);
		m_state = c_stateDone;
		m_stateTimerMs = 0;
		break;
	}
}

// FUNCTION: LEGORACERS 0x00458450
RacePowerupManager::PowerupAction* RacePowerupManager::DynamiteAction::Destroy(undefined4 p_flags)
{
	DynamiteAction* result = this;
	if (p_flags & 2) {
		if (p_flags & 1) {
			delete[] this;
		}

		return result;
	}

	this->~DynamiteAction();
	if (p_flags & 1) {
		::operator delete(result);
	}

	return result;
}
