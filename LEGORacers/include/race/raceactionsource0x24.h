#ifndef RACEACTIONSOURCE0X24_H
#define RACEACTIONSOURCE0X24_H

#include "audio/soundnode.h"

// SIZE 0x24
class RaceActionSource0x24 : public SoundVector {
public:
	SoundVector m_velocity; // 0x0c
	SoundVector m_right;    // 0x18
};

#endif // RACEACTIONSOURCE0X24_H
