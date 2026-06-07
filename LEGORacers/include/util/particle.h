#ifndef PARTICLE_H
#define PARTICLE_H

#include "decomp.h"
#include "golmodelentity.h"
#include "types.h"

class DuskwindBananaRelic0x24;

// VTABLE: LEGORACERS 0x004af8c0
class Particle : public GolWorldEntity {
public:
	Particle();

	void FUN_00414600(LegoFloat p_deltaT, GolVec3* p_acceleration);

	LegoU32 m_unk0x28;                  // 0x28
	LegoU32 m_unk0x2c;                  // 0x2c
	DuskwindBananaRelic0x24* m_unk0x30; // 0x30
	Particle* m_next;                   // 0x34
};

#endif // PARTICLE_H
