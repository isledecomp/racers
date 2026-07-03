#ifndef CUTSCENEPARTICLEREF_H
#define CUTSCENEPARTICLEREF_H

#include "types.h"

class CutsceneParticle;

struct CutsceneParticleRef {
public:
	enum {
		c_flagInUse = 1 << 0
	};

	// size unknown, confirmed to be at least 5

	CutsceneParticle* m_particle; // 0x00
	LegoU8 m_flags;               // 0x04
};

#endif // CUTSCENEPARTICLEREF_H
