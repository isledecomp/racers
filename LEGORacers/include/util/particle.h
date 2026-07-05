#ifndef PARTICLE_H
#define PARTICLE_H

#include "golworldentity.h"
#include "types.h"

class GolMaterial;
struct GolVec3;

// VTABLE: LEGORACERS 0x004af8c0
class Particle : public GolWorldEntity {
public:
	Particle();

	void Integrate(LegoFloat p_deltaT, GolVec3* p_acceleration);

	LegoU32 m_ageMs;         // 0x28
	LegoU32 m_lifetimeMs;    // 0x2c
	GolMaterial* m_material; // 0x30
	Particle* m_next;        // 0x34
};

#endif // PARTICLE_H
