#ifndef RACERCOLLISIONWORLDS_H
#define RACERCOLLISIONWORLDS_H

#include "types.h"

class GolBoundedEntity;
class GolWorldDatabase;
class RaceSession;
class RaceState;
class Racer;

// VTABLE: LEGORACERS 0x004b1acc
// SIZE 0x3c
class RacerCollisionWorlds {
public:
	RacerCollisionWorlds();
	virtual ~RacerCollisionWorlds(); // vtable+0x00
	void Update(LegoU32 p_elapsedMs);
	void ActivateWorld(Racer* p_racer, LegoU32 p_worldIndex);
	LegoU32 Reset();

	// SYNTHETIC: LEGORACERS 0x0045e380
	// RacerCollisionWorlds::`scalar deleting destructor'

private:
	friend class RaceSession;

	void Initialize(GolWorldDatabase* p_worldDatabase, RaceState* p_raceState);
	void Destroy();

	enum {
		c_racerCount = 6,
		c_maxElapsedChunk = 0xff,
		c_activationTtl = 150,
	};

	Racer* m_racers[c_racerCount];     // 0x04
	GolWorldDatabase* m_worldDatabase; // 0x1c
	LegoU8* m_ttl[c_racerCount];       // 0x20
	LegoU32 m_worldCount;              // 0x38
};

#endif // RACERCOLLISIONWORLDS_H
