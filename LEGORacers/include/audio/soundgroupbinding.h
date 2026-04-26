#ifndef SOUNDGROUPBINDING_H
#define SOUNDGROUPBINDING_H

#include "decomp.h"
#include "types.h"

class SoundGroup;
class SoundManager;

// SIZE 0xc
class SoundGroupBinding {
public:
	SoundGroupBinding();
	~SoundGroupBinding();

	LegoBool32 SetSoundGroup(SoundManager* p_soundManager, SoundGroup* p_soundGroup, undefined4 p_unk0x0c);
	LegoBool32 ResetSoundGroup();

private:
	void Reset();

	SoundManager* m_soundManager; // 0x00
	SoundGroup* m_soundGroup;     // 0x04
	undefined4 m_unk0x08;         // 0x08
};

#endif // SOUNDGROUPBINDING_H
