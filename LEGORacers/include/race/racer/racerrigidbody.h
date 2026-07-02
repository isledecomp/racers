#ifndef RACERRIGIDBODY_H
#define RACERRIGIDBODY_H

#include "decomp.h"
#include "golmath.h"
#include "types.h"

class GolOrientedEntity;

// Rigid-body integrator core: force/torque accumulators, inertia
// tensors, and the per-step position/orientation integration.
// VTABLE: LEGORACERS 0x004b0b78
// SIZE 0xd0
class RacerRigidBody {
public:
	RacerRigidBody();
	virtual void ComputeInertiaTensor() = 0;  // vtable+0x00
	virtual void Update(LegoS32 p_elapsedMs); // vtable+0x04
	virtual GolOrientedEntity* GetEntity();   // vtable+0x08

	void Reset();
	void Initialize(GolOrientedEntity* p_body, LegoFloat p_mass);
	void Destroy();
	void UpdateWorldInverseInertia();
	void UpdateAngularVelocity();

	GolOrientedEntity* m_body;         // 0x004
	GolVec3 m_velocity;                // 0x008
	GolVec3 m_centerOfMassLocal;       // 0x014
	GolVec3 m_centerOfMassWorld;       // 0x020
	GolMatrix3 m_inertiaTensor;        // 0x02c
	GolMatrix3 m_inverseInertiaTensor; // 0x050
	GolMatrix3 m_worldInverseInertia;  // 0x074
	GolVec3 m_angularVelocity;         // 0x098
	GolVec3 m_angularMomentum;         // 0x0a4
	GolVec3 m_force;                   // 0x0b0
	GolVec3 m_torque;                  // 0x0bc
	LegoFloat m_mass;                  // 0x0c8
	LegoFloat m_inverseMass;           // 0x0cc
};

#endif // RACERRIGIDBODY_H
