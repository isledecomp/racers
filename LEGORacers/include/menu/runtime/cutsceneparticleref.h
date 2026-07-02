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

	CutsceneParticle* m_particle;
	LegoU8 m_flags;
};

#endif // CUTSCENEPARTICLEREF_H
