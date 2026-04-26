#ifndef DIRECTMUSICGROUP_H
#define DIRECTMUSICGROUP_H

#include "audio/musicgroup.h"
#include "compat.h"
#include "decomp.h"

class MusicInstance;
class SoundManager;

// VTABLE: LEGORACERS 0x004afbc8
// SIZE 0x128
class DirectMusicGroup : public MusicGroup {
public:
	DirectMusicGroup();
	~DirectMusicGroup() override;                            // vtable+0x00
	GolListLink* Load(const LegoChar* p_name) override;      // vtable+0x04
	GolListLink* Unload() override;                          // vtable+0x08
	LegoBool32 IsLoaded() override;                          // vtable+0x0c
	MusicInstance* CreateMusicInstance(undefined4) override; // vtable+0x10
	void DestroyMusicInstance(MusicInstance*) override;      // vtable+0x14
	SoundManager* GetSoundManager() override;                // vtable+0x18

	void SetSoundManager(SoundManager* p_soundManager) { m_soundManager = p_soundManager; }

	// SYNTHETIC: LEGORACERS 0x0041a690
	// DirectMusicGroup::`scalar deleting destructor'

private:
	SoundManager* m_soundManager;            // 0x10
	GolList<MusicInstance> m_musicInstances; // 0x14
	undefined m_unk0x20;                     // 0x20
	undefined m_unk0x21[0x124 - 0x21];       // 0x21
	undefined4 m_unk0x124;                   // 0x124
};

#endif // DIRECTMUSICGROUP_H
