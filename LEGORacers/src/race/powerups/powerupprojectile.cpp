#include "race/powerups/powerupprojectile.h"

#include "decomp.h"
#include "golconstants.h"
#include "race/triggerworld.h"

#include <math.h>

DECOMP_SIZE_ASSERT(PowerupProjectile, 0xa8)

// FUNCTION: LEGORACERS 0x00430ca0
PowerupProjectile::PowerupProjectile()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00430cc0
PowerupProjectile* PowerupProjectile::Destroy(undefined4 p_flags)
{
	PowerupProjectile* result = this;
	this->~PowerupProjectile();
	if (p_flags & 1) {
		::operator delete(result);
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00430ce0
PowerupProjectile::~PowerupProjectile()
{
	Deactivate();
}

// FUNCTION: LEGORACERS 0x00430cf0
void PowerupProjectile::Reset()
{
	m_launchHeight = 5.0f;
	m_state = c_stateIdle;
	m_worldEntity = 0;
	m_collisionWorld = 0;
	m_startPosition.m_x = 0.0f;
	m_startPosition.m_y = 0.0f;
	m_startPosition.m_z = 0.0f;
	m_targetPosition.m_x = 0.0f;
	m_targetPosition.m_y = 0.0f;
	m_targetPosition.m_z = 0.0f;
	m_speed = 0;
	m_velocityX = 0;
	m_velocityY = 0;
	m_velocityZ = 0;
	m_gravity = 0;
	m_collisionEvent = NULL;
	m_ageMs = 0;
	m_flightTimeMs = 0;
	m_lifetimeMs = 0;
	m_hitRacer = 0;
	m_ownerRacer = 0;
}

// FUNCTION: LEGORACERS 0x00430d40
void PowerupProjectile::Initialize(Params* p_params)
{
	m_worldEntity = p_params->m_worldEntity;
	m_collisionWorld = p_params->m_collisionWorld;
	m_gravity = p_params->m_gravity;
	m_lifetimeMs = p_params->m_lifetimeMs;
	m_launchHeight = p_params->m_launchHeight;
	m_ageMs = 0;
	m_state = c_stateFlying;
	m_hitRacer = NULL;
}

// STUB: LEGORACERS 0x00430d80
void PowerupProjectile::LaunchAtRacer(
	Params* p_params,
	Racer* p_racer,
	Racer* p_targetRacer,
	LegoBool32 p_fromRacerPosition,
	LegoBool32 p_predictiveLead
)
{
	Params* params = p_params;
	Racer* targetRacer = p_targetRacer;
	Initialize(params);

	LegoFloat speed = params->m_speed;
	m_targetRacer = targetRacer;
	m_ownerRacer = p_racer;
	if (p_fromRacerPosition) {
		p_racer->m_visuals.m_carEntity->GetPosition(&m_startPosition);
		m_startPosition.m_z += m_launchHeight;
		m_worldEntity->SetPosition(m_startPosition);
	}
	else {
		m_worldEntity->GetPosition(&m_startPosition);
	}

	GolVec3* startPosition = &m_startPosition;
	GolVec3* target = &m_targetPosition;
	targetRacer->m_visuals.m_carEntity->GetPosition(target);
	target->m_z += 5.0f;

	GolVec3 scaledVelocity;
	GolVec3 targetVelocity = targetRacer->m_physics.m_velocity;
	GolVec3 racerDirection;
	GolVec3 delta;
	delta.m_x = target->m_x - startPosition->m_x;
	delta.m_y = m_targetPosition.m_y - m_startPosition.m_y;
	LegoFloat deltaY = delta.m_y;
	LegoFloat distance = static_cast<LegoFloat>(sqrt(deltaY * deltaY + delta.m_x * delta.m_x));
	LegoFloat inverseDistance;
	if (distance == 0.0f) {
		distance = 1.0f;
		inverseDistance = 1.0f;
	}
	else {
		inverseDistance = 1.0f / distance;
	}

	LegoFloat directionX = inverseDistance * delta.m_x;
	Racer* racer = p_racer;
	racerDirection = racer->m_physics.m_velocityDirection;
	LegoFloat directionY = inverseDistance * deltaY;
	LegoFloat dot = racerDirection.m_z * 0.0f + racerDirection.m_y * directionY + racerDirection.m_x * directionX;
	if (dot < 0.0f) {
		dot = -dot;
	}

	speed += dot * racer->m_physics.m_speed * g_floatConst1000;
	if (speed <= 0.001f) {
		speed = 0.001f;
	}

	speed = distance / speed;
	LegoFloat durationMs = speed * g_floatConst1000;
	m_flightTimeMs = static_cast<LegoS32>(durationMs);
	scaledVelocity.m_x = targetVelocity.m_x * durationMs;
	scaledVelocity.m_y = targetVelocity.m_y * durationMs;
	scaledVelocity.m_z = targetVelocity.m_z * durationMs;

	if (p_predictiveLead) {
		GolVec3 predictedTarget;
		predictedTarget.m_x = target->m_x + scaledVelocity.m_x;
		predictedTarget.m_y = target->m_y + scaledVelocity.m_y;
		predictedTarget.m_z = target->m_z + scaledVelocity.m_z;

		GolVec3 racerVector = p_racer->m_physics.m_facingDirection;
		GolVec3 predictedDelta;
		predictedDelta.m_x = predictedTarget.m_x - startPosition->m_x;
		predictedDelta.m_y = predictedTarget.m_y - startPosition->m_y;
		predictedDelta.m_z = predictedTarget.m_z - startPosition->m_z;
		LegoFloat predictedDot = racerVector.m_z * predictedDelta.m_z;
		predictedDot += racerVector.m_y * predictedDelta.m_y;
		predictedDot += racerVector.m_x * predictedDelta.m_x;
		if (predictedDot < 0.0f) {
			*target = predictedTarget;
		}
	}
	else {
		target->m_x += scaledVelocity.m_x;
		target->m_y += scaledVelocity.m_y;
		target->m_z += scaledVelocity.m_z;
	}

	target->m_x += params->m_targetOffset.m_x;
	target->m_y += params->m_targetOffset.m_y;
	target->m_z += params->m_targetOffset.m_z;
	ComputeTrajectory(speed);
	RegisterCollisionEvent(params->m_eventQueue);
}

// FUNCTION: LEGORACERS 0x00431050
void PowerupProjectile::LaunchAtPoint(
	Params* p_params,
	Racer* p_racer,
	GolVec3* p_targetPosition,
	GolVec3* p_targetVelocity,
	LegoBool32 p_fromRacerPosition
)
{
	Params* params = p_params;
	Initialize(params);

	LegoFloat speed = params->m_speed;
	m_targetPosition = *p_targetPosition;
	m_targetRacer = NULL;
	m_ownerRacer = p_racer;
	if (p_fromRacerPosition) {
		p_racer->m_visuals.m_carEntity->GetPosition(&m_startPosition);
		m_startPosition.m_z += m_launchHeight;
		m_worldEntity->SetPosition(m_startPosition);
	}
	else {
		m_worldEntity->GetPosition(&m_startPosition);
	}

	GolVec3* startPosition = &m_startPosition;
	GolVec3* target = &m_targetPosition;
	GolVec3 delta;
	delta.m_x = target->m_x - startPosition->m_x;
	delta.m_y = m_targetPosition.m_y - m_startPosition.m_y;
	LegoFloat deltaY = delta.m_y;
	LegoFloat distance = static_cast<LegoFloat>(sqrt(deltaY * deltaY + delta.m_x * delta.m_x));
	LegoFloat inverseDistance;
	if (distance == 0.0f) {
		distance = 1.0f;
		inverseDistance = 1.0f;
	}
	else {
		inverseDistance = 1.0f / distance;
	}

	LegoFloat directionX = inverseDistance * delta.m_x;
	Racer* racer = p_racer;
	GolVec3 racerDirection = racer->m_physics.m_velocityDirection;
	GolVec3* racerDirectionPtr = &racerDirection;
	LegoFloat directionY = inverseDistance * deltaY;
	LegoFloat dot = racerDirectionPtr->m_z * 0.0f;
	dot += racerDirectionPtr->m_y * directionY;
	dot += racerDirectionPtr->m_x * directionX;
	if (dot > 0.0f) {
		LegoFloat speedDelta = dot * racer->m_physics.m_speed;
		speedDelta *= g_floatConst1000;
		speed += speedDelta;
	}

	LegoFloat durationSeconds = distance / speed;
	LegoFloat scaledDuration = durationSeconds;
	scaledDuration *= g_floatConst1000;
	m_flightTimeMs = static_cast<LegoS32>(scaledDuration);
	GolVec3 scaledDelta;
	scaledDelta.m_x = p_targetVelocity->m_x * durationSeconds;
	scaledDelta.m_y = p_targetVelocity->m_y;
	scaledDelta.m_y *= durationSeconds;
	scaledDelta.m_z = p_targetVelocity->m_z;
	scaledDelta.m_z *= durationSeconds;
	target->m_x += scaledDelta.m_x;
	target->m_y += scaledDelta.m_y;
	target->m_z += scaledDelta.m_z;
	target->m_x += params->m_targetOffset.m_x;
	target->m_y += params->m_targetOffset.m_y;
	target->m_z += params->m_targetOffset.m_z;
	ComputeTrajectory(durationSeconds);
	RegisterCollisionEvent(params->m_eventQueue);
}

// FUNCTION: LEGORACERS 0x00431220
void PowerupProjectile::LaunchAtPosition(Params* p_params, GolVec3* p_position)
{
	Initialize(p_params);

	m_targetPosition.m_x = p_params->m_targetOffset.m_x + p_position->m_x;
	m_targetPosition.m_y = p_params->m_targetOffset.m_y + p_position->m_y;
	m_targetPosition.m_z = p_params->m_targetOffset.m_z + p_position->m_z;
	m_ownerRacer = NULL;
	m_targetRacer = NULL;
	m_worldEntity->GetPosition(&m_startPosition);

	GolVec3 delta;
	delta.m_x = m_targetPosition.m_x - m_startPosition.m_x;
	delta.m_y = m_targetPosition.m_y - m_startPosition.m_y;
	m_speed = p_params->m_speed;
	delta.m_z = m_targetPosition.m_z - m_startPosition.m_z;
	LegoFloat distance = static_cast<LegoFloat>(sqrt(delta.m_y * delta.m_y + delta.m_x * delta.m_x));
	LegoFloat durationSeconds = p_params->m_speed;
	durationSeconds = distance / durationSeconds;
	LegoFloat scaledDuration = durationSeconds;
	scaledDuration *= g_floatConst1000;
	m_flightTimeMs = static_cast<LegoS32>(scaledDuration);

	LegoFloat inverseDuration = 1.0f;
	inverseDuration /= durationSeconds;
	m_velocityX = inverseDuration * delta.m_x;
	m_velocityY = inverseDuration * delta.m_y;

	LegoFloat zVelocity = delta.m_z;
	zVelocity /= distance;
	zVelocity *= p_params->m_speed;
	m_velocityZ = zVelocity;
	LegoFloat acceleration = m_gravity;
	m_velocityZ = zVelocity - (acceleration * distance) / (p_params->m_speed + p_params->m_speed);
	RegisterCollisionEvent(p_params->m_eventQueue);
}

// STUB: LEGORACERS 0x00431310
void PowerupProjectile::Deflect(Racer* p_racer)
{
	GolVec3 velocity;
	velocity.m_x = 0.0f;
	velocity.m_y = 0.0f;
	velocity.m_z = 0.0f;

	m_ageMs = 0;
	m_state = c_stateFlying;
	m_targetRacer = m_ownerRacer;
	if (m_targetRacer) {
		m_targetRacer->m_visuals.m_carEntity->GetPosition(&m_targetPosition);
		m_targetPosition.m_z += 5.0f;
		velocity = m_targetRacer->m_physics.m_velocity;
	}
	else {
		m_targetPosition = m_startPosition;
	}

	m_ownerRacer = p_racer;
	m_worldEntity->GetPosition(&m_startPosition);
	m_hitRacer = NULL;

	GolVec3 delta;
	delta.m_x = m_targetPosition.m_x - m_startPosition.m_x;
	delta.m_y = m_targetPosition.m_y - m_startPosition.m_y;
	delta.m_z = m_targetPosition.m_z - m_startPosition.m_z;
	LegoFloat distance = static_cast<LegoFloat>(sqrt(delta.m_y * delta.m_y + delta.m_x * delta.m_x));
	if (distance == 0.0f) {
		distance = 1.0f;
	}

	LegoFloat durationSeconds = distance / m_speed;
	LegoFloat durationMs = durationSeconds * g_floatConst1000;
	m_flightTimeMs = static_cast<LegoS32>(durationMs);

	m_targetPosition.m_x += velocity.m_x * durationSeconds;
	m_targetPosition.m_y += velocity.m_y * durationSeconds;
	m_targetPosition.m_z += velocity.m_z * durationSeconds;
	ComputeTrajectory(durationSeconds);
}

// FUNCTION: LEGORACERS 0x00431450
void PowerupProjectile::ComputeTrajectory(LegoFloat p_durationSeconds)
{
	LegoFloat inverseDuration = 1.0f;
	inverseDuration /= p_durationSeconds;

	GolVec3 delta;
	delta.m_x = m_targetPosition.m_x - m_startPosition.m_x;
	delta.m_y = m_targetPosition.m_y - m_startPosition.m_y;
	delta.m_z = m_targetPosition.m_z - m_startPosition.m_z;

	LegoFloat distance = static_cast<LegoFloat>(sqrt(delta.m_y * delta.m_y + delta.m_x * delta.m_x));
	LegoFloat speed = distance * inverseDuration;
	m_speed = speed;
	m_velocityX = delta.m_x * inverseDuration;
	m_velocityY = delta.m_y * inverseDuration;

	LegoFloat zVelocity = delta.m_z / distance * speed;
	LegoFloat acceleration = m_gravity;
	m_velocityZ = zVelocity - (acceleration * distance) / (speed + speed);
}

// FUNCTION: LEGORACERS 0x004314d0
void PowerupProjectile::RegisterCollisionEvent(LegoEventQueue* p_eventQueue)
{
	if (m_collisionEvent != NULL) {
		m_collisionEvent->m_active = 0;
	}

	if (p_eventQueue != NULL) {
		LegoEventQueue::Callback* callback = this;
		LegoEventQueue::Descriptor descriptor;
		descriptor.m_maxFireCount = 0;
		descriptor.m_hitThreshold = 0;
		descriptor.m_type = 4;
		descriptor.m_flags = 1;
		descriptor.m_data = m_worldEntity;
		m_collisionEvent = p_eventQueue->AllocateEvent(callback, &descriptor);
	}
	else {
		m_collisionEvent = NULL;
	}
}

// FUNCTION: LEGORACERS 0x00431530
void PowerupProjectile::Deactivate()
{
	if (m_collisionEvent != NULL) {
		m_collisionEvent->m_active = 0;
		m_collisionEvent = NULL;
	}

	Reset();
}

// FUNCTION: LEGORACERS 0x00431550
LegoS32 PowerupProjectile::Update(LegoU32 p_elapsedMs)
{
	LegoU32 state = m_state;
	if (state != c_stateFlying) {
		return state;
	}

	m_ageMs += p_elapsedMs;
	p_elapsedMs = m_ageMs;
	if (p_elapsedMs >= m_lifetimeMs) {
		m_state = c_stateExpired;
		m_worldEntity->GetPosition(&m_hitPosition);
		return c_stateExpired;
	}

	LegoFloat elapsed = static_cast<LegoS32>(p_elapsedMs) * 0.001f;
	GolVec3 vectors[2];
	vectors[0].m_x =
		(vectors[1].m_y = m_velocityY * elapsed, vectors[1].m_z = m_velocityZ * elapsed, m_startPosition.m_x) +
		elapsed * m_velocityX;
	vectors[0].m_y = vectors[1].m_y + m_startPosition.m_y;
	vectors[0].m_z = (vectors[1].m_z + m_startPosition.m_z) + m_gravity * 0.5f * elapsed * elapsed;
	m_worldEntity->GetPosition(&vectors[1]);

	GolBoundingVolume::HitTriangle record;
	if (m_collisionWorld->IntersectSegmentAndFireEvents(&vectors[1], &vectors[0], &record, &m_hitPosition)) {
		m_hitNormal.m_x = record.m_normal.m_x;
		m_hitNormal.m_y = record.m_normal.m_y;
		m_hitNormal.m_z = record.m_normal.m_z;
		m_worldEntity->SetPosition(m_hitPosition);
		m_state = c_stateHitWorld;
		return c_stateHitWorld;
	}

	m_worldEntity->SetPosition(vectors[0]);
	return c_stateFlying;
}

// FUNCTION: LEGORACERS 0x00431660
void PowerupProjectile::OnEvent(LegoEventQueue::CallbackData* p_data)
{
	Racer* previousContext = m_ownerRacer;
	if (p_data->m_data != previousContext && m_state == c_stateFlying) {
		m_state = c_stateHitRacer;
		Racer* racer = static_cast<Racer*>(p_data->m_data);
		m_hitRacer = racer;
		racer->m_visuals.m_carEntity->GetPosition(&m_hitPosition);
	}
}

// FUNCTION: LEGORACERS 0x004316a0
void PowerupProjectile::GetVelocity(GolVec3* p_velocity)
{
	p_velocity->m_x = m_velocityX;
	p_velocity->m_y = m_velocityY;
	LegoFloat z = static_cast<LegoS32>(m_ageMs) * 0.001f;
	p_velocity->m_z = z * m_gravity + m_velocityZ;
}

// FUNCTION: LEGORACERS 0x004316d0
void PowerupProjectile::CancelCollisionEvent()
{
	if (m_collisionEvent != NULL) {
		m_collisionEvent->m_active = 0;
		m_collisionEvent = NULL;
	}
}
