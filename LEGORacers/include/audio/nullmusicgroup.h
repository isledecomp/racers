#ifndef NULLMUSICGROUP_H
#define NULLMUSICGROUP_H

#include "audio/musicgroup.h"
#include "audio/musicinstance.h"
#include "compat.h"
#include "decomp.h"

class SoundManager;

// VTABLE: LEGORACERS 0x004afcc8
// SIZE 0x20
class NullMusicGroup : public MusicGroup {
public:
	NullMusicGroup();
	~NullMusicGroup() override;                                   // vtable+0x00
	void Load(const LegoChar* p_name) override;                   // vtable+0x04
	void Unload() override;                                       // vtable+0x08
	LegoBool32 IsLoaded() override;                               // vtable+0x0c
	MusicInstance* CreateMusicInstance(LegoU32 p_index) override; // vtable+0x10
	void DestroyMusicInstance(MusicInstance*) override;           // vtable+0x14
	SoundManager* GetSoundManager() override;                     // vtable+0x18

	void SetSoundManager(SoundManager* p_soundManager) { m_soundManager = p_soundManager; }

	// SYNTHETIC: LEGORACERS 0x0041c050
	// NullMusicGroup::`scalar deleting destructor'

private:
	SoundManager* m_soundManager;            // 0x10
	GolList<MusicInstance> m_musicInstances; // 0x14
};

#endif // NULLMUSICGROUP_H
