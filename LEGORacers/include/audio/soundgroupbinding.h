#ifndef SOUNDGROUPBINDING_H
#define SOUNDGROUPBINDING_H

#include "decomp.h"
#include "types.h"

class SoundGroup;
class SoundManager;
struct SoundVector;

// SIZE 0xc
class SoundGroupBinding {
public:
	SoundGroupBinding();
	~SoundGroupBinding();

	LegoBool32 SetSoundGroup(SoundManager* p_soundManager, SoundGroup* p_soundGroup, undefined4 p_firstSoundIndex);
	LegoBool32 ResetSoundGroup();
	void PlaySoundByIndex(LegoU32 p_index);
	void PlaySpatialSound(
		LegoU32 p_index,
		SoundVector* p_position,
		LegoFloat p_minDistance,
		LegoFloat p_maxDistance,
		LegoFloat p_volume,
		LegoFloat p_frequencyScale
	);
	SoundManager* GetSoundManager() const { return m_soundManager; }

private:
	void Reset();

	SoundManager* m_soundManager; // 0x00
	SoundGroup* m_soundGroup;     // 0x04
	LegoU32 m_firstSoundIndex;    // 0x08
};

#endif // SOUNDGROUPBINDING_H
