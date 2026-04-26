#ifndef MUSICGROUPBASE_H
#define MUSICGROUPBASE_H

#include "decomp.h"
#include "gollist.h"
#include "types.h"

class MusicInstance;
class SoundManager;

// VTABLE: LEGORACERS 0x004afa9c
// SIZE 0x08
class MusicGroupBase {
public:
	MusicGroupBase();
	virtual ~MusicGroupBase();                                  // vtable+0x00
	virtual GolListLink* Load(const LegoChar* p_name) = 0;      // vtable+0x04
	virtual GolListLink* Unload() = 0;                          // vtable+0x08
	virtual LegoBool32 IsLoaded() = 0;                          // vtable+0x0c
	virtual MusicInstance* CreateMusicInstance(undefined4) = 0; // vtable+0x10
	virtual void DestroyMusicInstance(MusicInstance*) = 0;      // vtable+0x14
	virtual SoundManager* GetSoundManager() = 0;                // vtable+0x18

	// SYNTHETIC: LEGORACERS 0x00417bc0
	// MusicGroupBase::`scalar deleting destructor'

protected:
	undefined4 m_unk0x04; // 0x04
};

#endif // MUSICGROUPBASE_H
