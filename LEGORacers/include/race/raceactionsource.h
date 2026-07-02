#ifndef RACEACTIONSOURCE_H
#define RACEACTIONSOURCE_H

#include "audio/soundnode.h"

// Kinematic sample of a racer (position base, velocity, facing) used as the
// source/aim basis for powerup actions and spatial sounds.
// SIZE 0x24
class RaceActionSource : public SoundVector {
public:
	SoundVector m_velocity; // 0x0c
	SoundVector m_forward;  // 0x18
};

#endif // RACEACTIONSOURCE_H
