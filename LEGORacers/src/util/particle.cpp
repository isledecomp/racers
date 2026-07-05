#include "util/particle.h"

#include "decomp.h"
#include "golmath.h"

#include <stddef.h>

DECOMP_SIZE_ASSERT(Particle, 0x38)

// FUNCTION: LEGORACERS 0x004145e0
Particle::Particle()
{
	m_ageMs = 0;
	m_lifetimeMs = 0;
	m_material = NULL;
	m_next = NULL;
}

// FUNCTION: LEGORACERS 0x00414600
void Particle::Integrate(LegoFloat p_deltaT, GolVec3* p_acceleration)
{
	GolVec3 deltaVelocity;

	LegoFloat halfDeltaT = p_deltaT * 0.5f;
	deltaVelocity.m_x = p_deltaT * p_acceleration->m_x;
	deltaVelocity.m_y = p_acceleration->m_y;
	deltaVelocity.m_y *= p_deltaT;
	deltaVelocity.m_z = p_acceleration->m_z;
	deltaVelocity.m_z *= p_deltaT;

	LegoFloat deltaCenter = m_velocity.m_x;
	deltaCenter *= p_deltaT;
	deltaCenter += deltaVelocity.m_x * halfDeltaT;
	m_center.m_x += deltaCenter;

	deltaCenter = m_velocity.m_y;
	deltaCenter *= p_deltaT;
	deltaCenter += deltaVelocity.m_y * halfDeltaT;
	m_center.m_y += deltaCenter;

	deltaCenter = m_velocity.m_z;
	deltaCenter *= p_deltaT;
	deltaCenter += deltaVelocity.m_z * halfDeltaT;
	m_center.m_z += deltaCenter;

	m_velocity.m_x += deltaVelocity.m_x;
	m_velocity.m_y += deltaVelocity.m_y;
	m_velocity.m_z += deltaVelocity.m_z;
}
