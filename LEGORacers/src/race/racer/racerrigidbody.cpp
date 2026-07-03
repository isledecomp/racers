#include "audio/spatialsoundinstance.h"
#include "audio/streamingsoundinstance.h"
#include "golcamerabase.h"
#include "golconstants.h"
#include "golmath.h"
#include "race/raceeventtable.h"
#include "race/raceforcefeedback.h"
#include "race/racer/racerouterecord.h"
#include "race/racer/racersoundsource.h"
#include "race/racestate.h"
#include "race/triggerworld.h"

#include <float.h>
#include <math.h>
#include <string.h>

// GLOBAL: LEGORACERS 0x004b0b90
extern const LegoFloat g_boxInertiaFactor = 0.083333336f;

// FUNCTION: LEGORACERS 0x00440950
RacerRigidBody::RacerRigidBody()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00440970 FOLDED
void RacerRigidBody::Reset()
{
	m_body = NULL;
	m_centerOfMassLocal.m_x = 0.0f;
	m_centerOfMassLocal.m_y = 0.0f;
	m_centerOfMassLocal.m_z = 0.0f;
	m_centerOfMassWorld.m_x = 0.0f;
	m_centerOfMassWorld.m_y = 0.0f;
	m_centerOfMassWorld.m_z = 0.0f;

	m_angularVelocity.m_x = 0.0f;
	m_angularVelocity.m_y = 0.0f;
	m_angularVelocity.m_z = 0.0f;
	m_angularMomentum.m_x = 0.0f;
	m_angularMomentum.m_y = 0.0f;
	m_angularMomentum.m_z = 0.0f;
	m_force.m_x = 0.0f;
	m_force.m_y = 0.0f;
	m_force.m_z = 0.0f;
	m_torque.m_x = 0.0f;
	m_torque.m_y = 0.0f;
	m_torque.m_z = 0.0f;

	m_mass = 1.0f;
	m_inverseMass = 1.0f;
}

// FUNCTION: LEGORACERS 0x004409f0 FOLDED
void RacerRigidBody::Initialize(GolOrientedEntity* p_body, LegoFloat p_mass)
{
	if (m_body != NULL) {
		Reset();
	}

	LegoFloat inverseMass = p_mass;
	inverseMass = 1.0f / inverseMass;
	m_body = p_body;
	m_mass = p_mass;
	m_velocity.m_x = 0.0f;
	m_velocity.m_y = 0.0f;
	m_velocity.m_z = 0.0f;
	m_inverseMass = inverseMass;
	ComputeInertiaTensor();
	UpdateWorldInverseInertia();
}

// FUNCTION: LEGORACERS 0x00440a50 FOLDED
void RacerRigidBody::Destroy()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00440a60 FOLDED
void RacerRigidBody::UpdateWorldInverseInertia()
{
	m_body->TransformMatrixToLocal(m_inverseInertiaTensor, &m_worldInverseInertia);
}

// FUNCTION: LEGORACERS 0x00440a80 FOLDED
void RacerRigidBody::UpdateAngularVelocity()
{
	LegoFloat value = m_worldInverseInertia.m_m[2][0] * m_angularMomentum.m_z;
	value += m_worldInverseInertia.m_m[1][0] * m_angularMomentum.m_y;
	m_angularVelocity.m_x = value + m_worldInverseInertia.m_m[0][0] * m_angularMomentum.m_x;

	value = m_worldInverseInertia.m_m[2][1] * m_angularMomentum.m_z;
	value += m_worldInverseInertia.m_m[1][1] * m_angularMomentum.m_y;
	m_angularVelocity.m_y = value + m_worldInverseInertia.m_m[0][1] * m_angularMomentum.m_x;

	value = m_worldInverseInertia.m_m[2][2] * m_angularMomentum.m_z;
	value += m_worldInverseInertia.m_m[1][2] * m_angularMomentum.m_y;
	m_angularVelocity.m_z = value + m_worldInverseInertia.m_m[0][2] * m_angularMomentum.m_x;
}

// FUNCTION: LEGORACERS 0x00440b10
void RacerCarBody::AddForce(GolVec3* p_force)
{
	m_force.m_x += p_force->m_x;
	m_force.m_y += p_force->m_y;
	m_force.m_z += p_force->m_z;
}

// FUNCTION: LEGORACERS 0x00440b50
void RacerCarBody::AddForceAtPoint(GolVec3* p_force, GolVec3* p_point)
{
	GolVec3 offset;
	offset.m_x = p_point->m_x - m_centerOfMassWorld.m_x;
	offset.m_y = p_point->m_y - m_centerOfMassWorld.m_y;
	offset.m_z = p_point->m_z - m_centerOfMassWorld.m_z;

	GolVec3 torque;
	LegoFloat value = offset.m_y;
	value *= p_force->m_z;
	LegoFloat crossValue = p_force->m_y;
	crossValue *= offset.m_z;
	torque.m_x = value - crossValue;

	value = offset.m_z;
	value *= p_force->m_x;
	crossValue = p_force->m_z;
	crossValue *= offset.m_x;
	torque.m_y = value - crossValue;

	value = p_force->m_y;
	value *= offset.m_x;
	crossValue = offset.m_y;
	crossValue *= p_force->m_x;
	torque.m_z = value - crossValue;

	m_torque.m_x += torque.m_x;
	m_torque.m_y += torque.m_y;
	m_torque.m_z += torque.m_z;
}

// FUNCTION: LEGORACERS 0x00440bd0
void RacerCarBody::AddAngularImpulse(GolVec3* p_impulse)
{
	GolVec3 local;
	m_body->RotateToLocal(*p_impulse, &local);

	GolVec3 transformed;
	transformed.m_x = m_inertiaTensor.m_m[0][0];
	transformed.m_x *= local.m_x;
	transformed.m_y = m_inertiaTensor.m_m[0][1];
	transformed.m_y *= local.m_x;
	transformed.m_z = m_inertiaTensor.m_m[0][2];
	transformed.m_z *= local.m_x;

	LegoFloat value = m_inertiaTensor.m_m[1][0];
	value *= local.m_y;
	transformed.m_x += value;
	value = m_inertiaTensor.m_m[1][1];
	value *= local.m_y;
	transformed.m_y += value;
	value = m_inertiaTensor.m_m[1][2];
	value *= local.m_y;
	transformed.m_z += value;

	value = m_inertiaTensor.m_m[2][0];
	value *= local.m_z;
	transformed.m_x += value;
	value = m_inertiaTensor.m_m[2][1];
	value *= local.m_z;
	transformed.m_y += value;
	value = m_inertiaTensor.m_m[2][2];
	value *= local.m_z;
	transformed.m_z += value;

	GolVec3 world;
	m_body->RotateToWorld(transformed, &world);
	m_angularMomentum.m_x += world.m_x;
	m_angularMomentum.m_y += world.m_y;
	m_angularMomentum.m_z += world.m_z;
}

// FUNCTION: LEGORACERS 0x00440cb0
void RacerCarBody::CancelAngularMomentum(GolVec3* p_direction, GolVec3* p_point)
{
	GolVec3 offset;
	offset.m_x = p_point->m_x - m_centerOfMassWorld.m_x;
	offset.m_y = p_point->m_y - m_centerOfMassWorld.m_y;
	offset.m_z = p_point->m_z - m_centerOfMassWorld.m_z;

	GolVec3 axis;
	LegoFloat value = offset.m_y;
	value *= p_direction->m_z;
	LegoFloat crossValue = p_direction->m_y;
	crossValue *= offset.m_z;
	axis.m_x = value - crossValue;

	value = offset.m_z;
	value *= p_direction->m_x;
	crossValue = p_direction->m_z;
	crossValue *= offset.m_x;
	axis.m_y = value - crossValue;

	value = p_direction->m_y;
	value *= offset.m_x;
	crossValue = offset.m_y;
	crossValue *= p_direction->m_x;
	axis.m_z = value - crossValue;
	GolMath::NormalizeVector3(axis, &axis);

	LegoFloat dot = axis.m_z;
	dot *= m_angularMomentum.m_z;
	value = m_angularMomentum.m_y;
	value *= axis.m_y;
	dot += value;
	value = axis.m_x;
	value *= m_angularMomentum.m_x;
	dot += value;

	if (dot >= 0.0f) {
		GolVec3 scaled;
		scaled.m_x = axis.m_x * dot;
		scaled.m_y = axis.m_y * dot;
		scaled.m_z = axis.m_z * dot;
		m_angularMomentum.m_x -= scaled.m_x;
		m_angularMomentum.m_y -= scaled.m_y;
		m_angularMomentum.m_z -= scaled.m_z;
	}
}

// FUNCTION: LEGORACERS 0x00440da0
void RacerCarBody::CancelAngularMomentumAlong(GolVec3* p_axis)
{
	LegoFloat dot = m_angularMomentum.m_z * p_axis->m_z;
	dot += m_angularMomentum.m_y * p_axis->m_y;
	dot += m_angularMomentum.m_x * p_axis->m_x;
	GolVec3 scaled;
	scaled.m_x = dot * p_axis->m_x;
	scaled.m_y = p_axis->m_y;
	scaled.m_y *= dot;
	scaled.m_z = dot * p_axis->m_z;
	m_angularMomentum.m_x -= scaled.m_x;
	m_angularMomentum.m_y -= scaled.m_y;
	m_angularMomentum.m_z -= scaled.m_z;
}

// FUNCTION: LEGORACERS 0x00440e10 FOLDED
void RacerRigidBody::Update(LegoS32 p_elapsedMs)
{
	UpdateAngularVelocity();

	LegoFloat elapsed = static_cast<LegoFloat>(p_elapsedMs);
	{
		GolVec3 linearDelta;
		linearDelta.m_x = m_force.m_x;
		linearDelta.m_x *= elapsed;
		linearDelta.m_x *= m_inverseMass;
		linearDelta.m_y = m_force.m_y;
		linearDelta.m_y *= elapsed;
		linearDelta.m_y *= m_inverseMass;
		linearDelta.m_z = m_force.m_z;
		linearDelta.m_z *= elapsed;
		linearDelta.m_z *= m_inverseMass;

		LegoFloat halfElapsed = elapsed * 0.5f;

		GolVec3 position;
		m_body->GetPosition(&position);
		LegoFloat velocityTerm = m_velocity.m_x;
		velocityTerm *= elapsed;
		LegoFloat accelerationTerm = halfElapsed;
		accelerationTerm *= linearDelta.m_x;
		position.m_x += velocityTerm + accelerationTerm;

		velocityTerm = m_velocity.m_y;
		velocityTerm *= elapsed;
		accelerationTerm = halfElapsed;
		accelerationTerm *= linearDelta.m_y;
		position.m_y += velocityTerm + accelerationTerm;

		velocityTerm = m_velocity.m_z;
		velocityTerm *= elapsed;
		accelerationTerm = halfElapsed;
		accelerationTerm *= linearDelta.m_z;
		position.m_z += velocityTerm + accelerationTerm;
		m_body->SetPosition(position);

		if (linearDelta.m_x == 0.0f && linearDelta.m_y == 0.0f && linearDelta.m_z == 0.0f) {
			const LegoFloat velocityThreshold = 9.9999997e-05f;

			if (m_velocity.m_x < velocityThreshold && -velocityThreshold < m_velocity.m_x) {
				m_velocity.m_x = 0.0f;
			}
			if (m_velocity.m_y < velocityThreshold && -velocityThreshold < m_velocity.m_y) {
				m_velocity.m_y = 0.0f;
			}
			if (m_velocity.m_z < velocityThreshold && -velocityThreshold < m_velocity.m_z) {
				m_velocity.m_z = 0.0f;
			}
		}

		m_velocity.m_x += linearDelta.m_x;
		m_velocity.m_y += linearDelta.m_y;
		m_velocity.m_z += linearDelta.m_z;
	}

	LegoFloat angularStepZ;
	LegoFloat angularStepY;
	LegoFloat angularStepX;
	angularStepX = m_angularVelocity.m_x;
	angularStepX *= elapsed;
	angularStepY = m_angularVelocity.m_y;
	angularStepY *= elapsed;
	angularStepZ = m_angularVelocity.m_z;
	angularStepZ *= elapsed;

	GolVec3 right;
	GolVec3 forward;
	m_body->GetAxes(&right, &forward);

	GolVec3 newRight;
	LegoFloat value = right.m_y;
	value *= angularStepZ;
	newRight.m_x = right.m_x - value;
	value = right.m_z;
	value *= angularStepY;
	newRight.m_x += value;

	value = right.m_x;
	value *= angularStepZ;
	newRight.m_y = right.m_y + value;
	value = right.m_z;
	value *= angularStepX;
	newRight.m_y -= value;

	value = right.m_x;
	value *= angularStepY;
	newRight.m_z = right.m_z - value;
	value = right.m_y;
	value *= angularStepX;
	newRight.m_z += value;

	GolVec3 newForward;
	value = forward.m_y;
	value *= angularStepZ;
	newForward.m_x = forward.m_x - value;
	value = forward.m_z;
	value *= angularStepY;
	newForward.m_x += value;

	value = forward.m_x;
	value *= angularStepZ;
	newForward.m_y = forward.m_y + value;
	value = forward.m_z;
	value *= angularStepX;
	newForward.m_y -= value;

	value = forward.m_x;
	value *= angularStepY;
	newForward.m_z = forward.m_z - value;
	value = forward.m_y;
	value *= angularStepX;
	newForward.m_z += value;
	GolOrientedEntity* entity = m_body;
	entity->SetDirectionUp(newRight, newForward);

	LegoFloat angularDeltaY = m_torque.m_y;
	angularDeltaY *= elapsed;
	LegoFloat angularDeltaZ = m_torque.m_z;
	angularDeltaZ *= elapsed;
	LegoFloat velocityTerm = elapsed;
	velocityTerm *= m_torque.m_x;
	m_angularMomentum.m_x += velocityTerm;
	m_angularMomentum.m_y += angularDeltaY;
	m_angularMomentum.m_z += angularDeltaZ;

	if (m_torque.m_x == 0.0f && m_torque.m_y == 0.0f && m_torque.m_z == 0.0f) {
		LegoFloat angularStepLengthSq =
			angularStepX * angularStepX + angularStepY * angularStepY + angularStepZ * angularStepZ;
		if (angularStepLengthSq < 0.00060000003f) {
			m_angularVelocity.m_x = 0.0f;
			m_angularVelocity.m_y = 0.0f;
			m_angularVelocity.m_z = 0.0f;
			m_angularMomentum.m_x = 0.0f;
			m_angularMomentum.m_y = 0.0f;
			m_angularMomentum.m_z = 0.0f;
		}
	}

	m_force.m_x = 0.0f;
	m_force.m_y = 0.0f;
	m_force.m_z = 0.0f;
	m_torque.m_x = 0.0f;
	m_torque.m_y = 0.0f;
	m_torque.m_z = 0.0f;
}

// FUNCTION: LEGORACERS 0x00441190
void RacerCarBody::SetCenterOfMass(GolVec3* p_centerOfMass)
{
	::memcpy(&m_centerOfMassLocal, p_centerOfMass, sizeof(m_centerOfMassLocal));
	m_body->LocalToWorld(m_centerOfMassLocal, &m_centerOfMassWorld);
}

// FUNCTION: LEGORACERS 0x004411c0 FOLDED
GolOrientedEntity* RacerRigidBody::GetEntity()
{
	return m_body;
}

// FUNCTION: LEGORACERS 0x004411d0
RacerBoxBody::RacerBoxBody()
{
	m_sizeX = 0.0f;
	m_sizeY = 0.0f;
	m_sizeZ = 0.0f;
	m_speedRampScale = 0.0f;
	m_racer = NULL;
}

// FUNCTION: LEGORACERS 0x00441210
void RacerBoxBody::Initialize(
	GolOrientedEntity* p_body,
	LegoFloat p_mass,
	LegoFloat p_sizeX,
	LegoFloat p_sizeY,
	LegoFloat p_sizeZ
)
{
	m_sizeX = p_sizeX;
	m_sizeY = p_sizeY;
	m_sizeZ = p_sizeZ;
	m_speedRampScale = 1.0f;
	m_racer = NULL;
	RacerRigidBody::Initialize(p_body, p_mass);
}

// FUNCTION: LEGORACERS 0x00441260 FOLDED
void RacerBoxBody::ComputeInertiaTensor()
{
	LegoFloat xSquared = m_sizeX * m_sizeX;
	LegoFloat ySquared = m_sizeY * m_sizeY;
	LegoFloat zSquared = m_sizeZ * m_sizeZ;
	LegoFloat scaledMass = m_mass / m_sizeX;

	m_inertiaTensor.m_m[0][1] = 0.0f;
	m_inertiaTensor.m_m[0][2] = 0.0f;
	m_inertiaTensor.m_m[1][0] = 0.0f;
	m_inertiaTensor.m_m[1][2] = 0.0f;
	m_inertiaTensor.m_m[2][0] = 0.0f;
	m_inertiaTensor.m_m[2][1] = 0.0f;
	m_inverseInertiaTensor.m_m[0][1] = 0.0f;
	m_inverseInertiaTensor.m_m[0][2] = 0.0f;
	m_inverseInertiaTensor.m_m[1][0] = 0.0f;
	m_inverseInertiaTensor.m_m[1][2] = 0.0f;
	m_inverseInertiaTensor.m_m[2][0] = 0.0f;
	m_inverseInertiaTensor.m_m[2][1] = 0.0f;

	LegoFloat xInertia = scaledMass * (zSquared + ySquared) * g_boxInertiaFactor;
	m_inertiaTensor.m_m[0][0] = xInertia;
	LegoFloat yInertia = (m_mass / m_sizeY) * (zSquared + xSquared) * g_boxInertiaFactor;
	m_inertiaTensor.m_m[1][1] = yInertia;
	LegoFloat zInertia = (m_mass / m_sizeZ) * (ySquared + xSquared) * g_boxInertiaFactor;
	m_inertiaTensor.m_m[2][2] = zInertia;
	m_inverseInertiaTensor.m_m[0][0] = 1.0f / xInertia;
	m_inverseInertiaTensor.m_m[1][1] = 1.0f / yInertia;
	m_inverseInertiaTensor.m_m[2][2] = 1.0f / zInertia;
}
