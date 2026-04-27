#ifndef MUSICGROUPSTATE_H
#define MUSICGROUPSTATE_H

#include "decomp.h"
#include "gollist.h"
#include "types.h"

class MusicInstance;
class SoundManager;

// VTABLE: LEGORACERS 0x004afa9c
// SIZE 0x08
class MusicGroupState {
public:
	MusicGroupState();
	virtual ~MusicGroupState();                                      // vtable+0x00
	virtual void Load(const LegoChar* p_name) = 0;                   // vtable+0x04
	virtual void Unload() = 0;                                       // vtable+0x08
	virtual LegoBool32 IsLoaded() = 0;                               // vtable+0x0c
	virtual MusicInstance* CreateMusicInstance(LegoU32 p_index) = 0; // vtable+0x10
	virtual void DestroyMusicInstance(MusicInstance*) = 0;           // vtable+0x14
	virtual SoundManager* GetSoundManager() = 0;                     // vtable+0x18

	// SYNTHETIC: LEGORACERS 0x00417bc0
	// MusicGroupState::`scalar deleting destructor'

protected:
	LegoU32 m_musicCount; // 0x04
};

#endif // MUSICGROUPSTATE_H
