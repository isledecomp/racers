#include "decomp.h"
#include "golmath.h"
#include "race/racesession.h"

#include <float.h>
#include <math.h>

DECOMP_SIZE_ASSERT(RacePowerupManager::HomingProjectile, 0xf8)

extern const LegoFloat g_unk0x004afde0;

// GLOBAL: LEGORACERS 0x004b0170
extern const LegoFloat g_homingProjectileCollisionStartOffset = 5.0f;

// GLOBAL: LEGORACERS 0x004b0224
extern const LegoFloat g_homingProjectileTargetHeightOffset = 5.0f;

// GLOBAL: LEGORACERS 0x004b022c
extern const LegoFloat g_homingProjectileTargetSnapDistanceSquared = 3600.0f;

// GLOBAL: LEGORACERS 0x004b0230
extern const LegoFloat g_homingProjectileTargetDirectHitDistanceSquared = 9.0f;

// GLOBAL: LEGORACERS 0x004b0234
extern const LegoFloat g_homingProjectileGroundProbeStartOffset = 2.0f;

// GLOBAL: LEGORACERS 0x004b0238
const LegoFloat g_homingProjectileCollisionHitLift = 6.0f;

// GLOBAL: LEGORACERS 0x004b023c
extern const LegoFloat g_homingProjectileDescentRate = 6.0f;

// GLOBAL: LEGORACERS 0x004b0240
const LegoFloat g_homingProjectileOscillationGrowth = 6.0f;

// GLOBAL: LEGORACERS 0x004b0244
const LegoFloat g_homingProjectilePathDistanceLimitSquared = 90000.0f;

// GLOBAL: LEGORACERS 0x004b0268
extern const LegoFloat g_homingProjectileCollisionProbeDepth = 50.0f;

// FUNCTION: LEGORACERS 0x00423590
RacePowerupManager::HomingProjectile::HomingProjectile()
{
	m_velocity.m_x = 0.0f;
	m_velocity.m_y = 0.0f;
	m_velocity.m_z = 0.0f;
	m_direction.m_y = 0.0f;
	m_direction.m_z = 0.0f;
	m_position.m_x = 0.0f;
	m_position.m_y = 0.0f;
	m_position.m_z = 0.0f;
	m_spiralAmplitude = 0;
	m_maxSpiralAmplitude = 0;
	m_spiralAngle = 0;
	m_spiralRate = 0;
	m_hasWaypoint = 0;
	m_pathEntry = 0;
	m_retargetTimerMs = 0;
	m_direction.m_x = 1.0f;
}

// FUNCTION: LEGORACERS 0x00423610
PowerupProjectile* RacePowerupManager::HomingProjectile::Destroy(undefined4 p_flags)
{
	HomingProjectile* result = this;
	Destruct();
	if (p_flags & 1) {
		::operator delete(result);
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00423630
void RacePowerupManager::HomingProjectile::Destruct()
{
	PowerupProjectile::~PowerupProjectile();
}

// STUB: LEGORACERS 0x00423640
void RacePowerupManager::HomingProjectile::UpdateTargeting(
	LegoU32 p_elapsedMs,
	RaceState* p_raceState,
	LegoFloat p_unk0x0c,
	LegoFloat p_unk0x10,
	LegoFloat p_unk0x14
)
{
	m_retargetTimerMs += p_elapsedMs;

	RaceState::Racer* noTarget = NULL;
	RaceState::Racer* target = m_targetRacer;
	if (target == noTarget || m_retargetTimerMs > c_targetRefreshMs ||
		(target->m_unk0x3e8.m_flags0x6c0 & c_racerFlags0xaa8Bit7) ||
		(target->m_unk0xd04 & c_racerFlags0xd04InvalidTargetMask)) {
		m_retargetTimerMs = 0;
		target = p_raceState->FUN_0043c6e0(&m_position, &m_direction, p_unk0x0c, p_unk0x10, p_unk0x14);
		m_targetRacer = target;

		while (target != noTarget) {
			if (target != m_ownerRacer && !(target->m_unk0x3e8.m_flags0x6c0 & c_racerFlags0xaa8Bit7) &&
				!(target->m_unk0xd04 & c_racerFlags0xd04InvalidTargetMask)) {
				break;
			}

			target = p_raceState->FUN_0043c7f0(target, &m_position, &m_direction, p_unk0x0c, p_unk0x10, p_unk0x14);
			m_targetRacer = target;
		}
	}

	if (!m_hasWaypoint && m_pathEntry != NULL) {
		RaceSessionField0x27f4::Entry* pathField = m_pathEntry;
		GolVec3 point = pathField->m_unk0x10;
		for (;;) {
			GolVec3 delta = point - m_position;
			if (GOLVECTOR3_DOT(delta, m_direction) > 0.0f &&
				GOLVECTOR3_DOT(pathField->m_unk0x00, m_position) + pathField->m_unk0x0c >= g_unk0x004afde0) {
				break;
			}

			pathField = m_ownerRacer->m_unk0x010->FUN_0041e940(pathField->m_unk0x20.m_items[0]);
			m_pathEntry = pathField;
			if (pathField != NULL) {
				point = pathField->m_unk0x10;
				delta = point - m_position;
				if (GOLVECTOR3_DOT(delta, delta) > g_homingProjectilePathDistanceLimitSquared ||
					GOLVECTOR3_DOT(pathField->m_unk0x00, m_direction) > 0.0f) {
					m_pathEntry = NULL;
				}
			}

			if (m_pathEntry == NULL) {
				break;
			}
		}

		if (m_pathEntry != NULL) {
			GolVec3 hit = point;
			GolVec3 start = point;
			GolVec3 end = point;
			start.m_z += g_homingProjectileCollisionStartOffset;
			end.m_z -= g_homingProjectileCollisionProbeDepth;

			GolBoundingVolume::Field0x0c record;
			if (m_collisionWorld->FUN_0041f730(&start, &end, &record, &hit)) {
				m_hasWaypoint = 1;
				m_waypointPosition.m_x = hit.m_x;
				m_waypointPosition.m_y = hit.m_y;
				m_waypointPosition.m_z = hit.m_z + g_homingProjectileCollisionHitLift;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00423980
void RacePowerupManager::HomingProjectile::StartHoming()
{
	m_worldEntity->VTable0x04(&m_position);
	m_spiralAmplitude = 0.0f;
	m_hasWaypoint = 0;
	m_retargetTimerMs = 0;

	GolVec3 forward;
	GolVec3* direction = &m_direction;
	m_worldEntity->VTable0x48(direction, &forward);
	m_retargetTimerMs = 0;

	RaceState::Racer* racer = m_ownerRacer;
	if (racer != NULL) {
		RaceSessionField0x27f4::Entry* pathField = racer->m_unk0xcc4;
		m_pathEntry = pathField;
		if (pathField != NULL) {
			forward.m_x = pathField->m_unk0x00.m_x;
			forward.m_y = pathField->m_unk0x00.m_y;
			LegoFloat dot = direction->m_z;
			dot *= pathField->m_unk0x00.m_z;
			LegoFloat yDot = direction->m_y;
			yDot *= forward.m_y;
			dot += yDot;
			dot += forward.m_x * direction->m_x;
			if (dot > 0.0f) {
				m_pathEntry = NULL;
			}
		}
	}
	else {
		m_pathEntry = NULL;
	}
}

// STUB: LEGORACERS 0x00423a20
LegoS32 RacePowerupManager::HomingProjectile::Update(LegoU32 p_elapsedMs)
{
	LegoU32 state = m_state;
	if (state != c_stateFlying) {
		return state;
	}

	m_ageMs += p_elapsedMs;
	if (static_cast<LegoU32>(m_ageMs) >= m_lifetimeMs) {
		m_state = c_stateExpired;
		m_worldEntity->VTable0x04(&m_hitPosition);
		return c_stateExpired;
	}

	LegoFloat elapsedSeconds = static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs)) * 0.001f;
	LegoFloat targetDistanceSquared;
	GolVec3 nextPosition;
	GolVec3 previousPosition;
	GolVec3 start;
	GolVec3 end;
	GolBoundingVolume::Field0x0c record;

	RaceState::Racer* target = m_targetRacer;
	if (target != NULL) {
		target->m_unk0x018.m_unk0x044->VTable0x04(&m_targetPosition);
		m_targetPosition.m_z += g_homingProjectileTargetHeightOffset;
		m_direction.m_x = m_targetPosition.m_x - m_position.m_x;
		m_direction.m_y = m_targetPosition.m_y - m_position.m_y;
		m_direction.m_z = m_targetPosition.m_z - m_position.m_z;
		targetDistanceSquared = m_direction.m_z * m_direction.m_z;
		targetDistanceSquared += m_direction.m_y * m_direction.m_y;
		targetDistanceSquared += m_direction.m_x * m_direction.m_x;
	}
	else {
		targetDistanceSquared = FLT_MAX;
	}

	GolVec3* direction = &m_direction;
	if (targetDistanceSquared < g_homingProjectileTargetSnapDistanceSquared) {
		GolMath::NormalizeVector3(*direction, direction);

		LegoFloat speed = static_cast<LegoFloat>(
			sqrt(m_velocityZ * m_velocityZ + m_velocityY * m_velocityY + m_velocityX * m_velocityX)
		);
		m_velocity.m_x = speed * direction->m_x;
		m_velocity.m_y = speed * direction->m_y;
		m_velocity.m_z = speed * direction->m_z;

		if (targetDistanceSquared < g_homingProjectileTargetDirectHitDistanceSquared) {
			m_hitPosition = m_targetPosition;
			m_worldEntity->VTable0x08(m_hitPosition);
			m_state = c_stateExpired;
			return c_stateExpired;
		}

		nextPosition.m_x = m_position.m_x + m_velocity.m_x * elapsedSeconds;
		nextPosition.m_y = m_position.m_y + m_velocity.m_y * elapsedSeconds;
		nextPosition.m_z = m_position.m_z + m_velocity.m_z * elapsedSeconds;

		targetDistanceSquared = (m_targetPosition.m_z - nextPosition.m_z) * direction->m_z;
		targetDistanceSquared += (m_targetPosition.m_y - nextPosition.m_y) * direction->m_y;
		targetDistanceSquared += (m_targetPosition.m_x - nextPosition.m_x) * direction->m_x;
		if (targetDistanceSquared <= 0.0f) {
			m_hitPosition = m_targetPosition;
			m_worldEntity->VTable0x08(m_hitPosition);
			m_state = c_stateExpired;
			return c_stateExpired;
		}
	}
	else {
		if (m_hasWaypoint) {
			end.m_x = m_waypointPosition.m_x - m_position.m_x;
			end.m_y = m_waypointPosition.m_y - m_position.m_y;
			end.m_z = m_waypointPosition.m_z - m_position.m_z;
			if (GOLVECTOR3_DOT(end, m_direction) > 0.0f) {
				m_direction.m_x = end.m_x;
				m_direction.m_y = end.m_y;
				m_direction.m_z = end.m_z;
			}
			else {
				m_hasWaypoint = 0;
			}
		}

		GolMath::NormalizeVector3(*direction, direction);
		m_velocity.m_x = m_speed * direction->m_x;
		m_velocity.m_y = m_speed * direction->m_y;
		m_velocity.m_z = m_speed * direction->m_z;
		nextPosition.m_x = m_position.m_x + m_velocity.m_x * elapsedSeconds;
		nextPosition.m_y = m_position.m_y + m_velocity.m_y * elapsedSeconds;
		nextPosition.m_z = m_position.m_z + m_velocity.m_z * elapsedSeconds;

		start.m_x = nextPosition.m_x;
		start.m_y = nextPosition.m_y;
		start.m_z = nextPosition.m_z;
		end.m_x = nextPosition.m_x;
		end.m_y = nextPosition.m_y;
		end.m_z = nextPosition.m_z;
		start.m_z += g_homingProjectileGroundProbeStartOffset;
		end.m_z -= g_homingProjectileCollisionHitLift;

		if (m_collisionWorld->FUN_0041f730(&start, &end, &record, &m_hitPosition)) {
			nextPosition.m_z = m_hitPosition.m_z + g_homingProjectileCollisionHitLift;
			if (m_position.m_z > nextPosition.m_z) {
				LegoFloat descentLimit = m_position.m_z - g_homingProjectileDescentRate * elapsedSeconds;
				if (descentLimit > nextPosition.m_z) {
					nextPosition.m_z = descentLimit;
				}
			}
		}
	}

	m_position = nextPosition;
	ApplySpiral(elapsedSeconds, direction, &nextPosition);

	m_worldEntity->VTable0x04(&previousPosition);

	if (m_collisionWorld->FUN_0041f730(&previousPosition, &nextPosition, &record, &m_hitPosition)) {
		m_hitNormal.m_x = record.m_unk0x24.m_x;
		m_hitNormal.m_y = record.m_unk0x24.m_y;
		m_hitNormal.m_z = record.m_unk0x24.m_z;
		m_worldEntity->VTable0x08(m_hitPosition);
		m_state = c_stateHitWorld;
		return c_stateHitWorld;
	}

	m_worldEntity->VTable0x08(nextPosition);
	return c_stateFlying;
}

// FUNCTION: LEGORACERS 0x00423ea0
void RacePowerupManager::HomingProjectile::GetVelocity(GolVec3* p_velocity)
{
	p_velocity->m_x = m_velocity.m_x;
	p_velocity->m_y = m_velocity.m_y;
	p_velocity->m_z = m_velocity.m_z;
}

// FUNCTION: LEGORACERS 0x00423ed0
void RacePowerupManager::HomingProjectile::ApplySpiral(
	LegoFloat p_elapsedSeconds,
	GolVec3* p_direction,
	GolVec3* p_position
)
{
	m_spiralAmplitude += g_homingProjectileOscillationGrowth * p_elapsedSeconds;
	if (m_maxSpiralAmplitude <= m_spiralAmplitude) {
		m_spiralAmplitude = m_maxSpiralAmplitude;
	}

	LegoFloat cosine;
	LegoFloat angleDelta = m_spiralRate;
	angleDelta *= p_elapsedSeconds;
	p_elapsedSeconds = m_spiralAngle + angleDelta;
	m_spiralAngle = p_elapsedSeconds;
	GolMath::FUN_00449170(p_elapsedSeconds, &p_elapsedSeconds, &cosine);

	LegoFloat xSine = p_elapsedSeconds * p_direction->m_x;
	LegoFloat ySine = p_direction->m_y;
	ySine *= p_elapsedSeconds;
	LegoFloat oneMinusCosine = 1.0f - cosine;
	LegoFloat zY = p_direction->m_z * p_direction->m_y * oneMinusCosine;
	p_position->m_x += ((p_direction->m_z * p_direction->m_x * oneMinusCosine) - ySine) * m_spiralAmplitude;
	p_position->m_y += (zY + xSine) * m_spiralAmplitude;
	p_position->m_z += ((p_direction->m_z * p_direction->m_z * oneMinusCosine) + cosine) * m_spiralAmplitude;
}
