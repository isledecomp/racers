#ifndef RACERBOXBODY_H
#define RACERBOXBODY_H

#include "race/racer/racerrigidbody.h"

// Box-shaped rigid body: inertia tensor from box dimensions.
// VTABLE: LEGORACERS 0x004b0b84
// SIZE 0xe4
class RacerBoxBody : public RacerRigidBody {
public:
	RacerBoxBody();
	void ComputeInertiaTensor() override; // vtable+0x00
	void Initialize(
		GolOrientedEntity* p_body,
		LegoFloat p_mass,
		LegoFloat p_sizeX,
		LegoFloat p_sizeY,
		LegoFloat p_sizeZ
	);

	LegoFloat m_sizeX;          // 0x0d0
	LegoFloat m_sizeY;          // 0x0d4
	LegoFloat m_sizeZ;          // 0x0d8
	LegoFloat m_speedRampScale; // 0x0dc
	Racer* m_racer;             // 0x0e0
};

#endif // RACERBOXBODY_H
