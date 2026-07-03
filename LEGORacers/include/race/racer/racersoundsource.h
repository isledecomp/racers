#ifndef RACERSOUNDSOURCE_H
#define RACERSOUNDSOURCE_H

#include "race/raceresourcemanager.h"
#include "types.h"

class SoundGroup;
class SpatialSoundInstance;

struct SoundVector;

// SIZE 0x14
class RacerSoundSource : public RaceResourceManager {
public:
	void PlaySoundById(LegoU32 p_soundId);
	void PlaySpatialSoundById(
		LegoU32 p_soundId,
		SoundVector* p_position,
		LegoFloat p_minDistance,
		LegoFloat p_maxDistance,
		LegoFloat p_volume,
		LegoFloat p_frequencyScale
	);
	SpatialSoundInstance* AcquireSoundById(LegoU32 p_soundId);

private:
	LegoU32 ResolveSoundId(LegoU32 p_soundId, SoundGroup** p_soundGroup);

protected:
	SoundGroup* m_groups[4]; // 0x04
};

#endif // RACERSOUNDSOURCE_H
