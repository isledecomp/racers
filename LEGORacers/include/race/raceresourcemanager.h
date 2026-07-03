#ifndef RACERESOURCEMANAGER_H
#define RACERESOURCEMANAGER_H

#include "decomp.h"
#include "types.h"

class SoundManager;
class SpatialSoundInstance;

// SIZE 0x04
class RaceResourceManager {
public:
	void ReleaseSound(SpatialSoundInstance* p_sound);

protected:
	SoundManager* m_soundManager; // 0x00
};

#endif // RACERESOURCEMANAGER_H
