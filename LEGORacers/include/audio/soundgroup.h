#ifndef SOUNDGROUP_H
#define SOUNDGROUP_H

#include "decomp.h"
#include "gollist.h"
#include "types.h"

class SoundManager;

// SIZE 0x10
class SoundGroup : public GolListLink {
public:
	SoundGroup() {}

	virtual void Load(const LegoChar* p_name) = 0; // vtable+0x00
	virtual void Unload() = 0;                     // vtable+0x04

	void SetSoundManager(SoundManager* p_soundManager) { m_soundManager = p_soundManager; }

protected:
	SoundManager* m_soundManager; // 0x0c
};

#endif // SOUNDGROUP_H
