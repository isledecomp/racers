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

	LegoBool32 SetSoundGroup(SoundManager* p_soundManager, SoundGroup* p_soundGroup, undefined4 p_unk0x0c);
	LegoBool32 ResetSoundGroup();
	void FUN_0046e970(LegoU32 p_index);
	void FUN_0046e9a0(
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
	undefined4 m_unk0x08;         // 0x08
};

#endif // SOUNDGROUPBINDING_H
