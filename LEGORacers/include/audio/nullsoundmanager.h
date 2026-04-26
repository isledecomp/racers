#ifndef NULLSOUNDMANAGER_H
#define NULLSOUNDMANAGER_H

#include "audio/musicgroup.h"
#include "audio/nullmusicgroup.h"
#include "audio/nullsoundgroup.h"
#include "audio/soundgroup.h"
#include "audio/soundmanager.h"
#include "audio/soundnode.h"
#include "compat.h"
#include "decomp.h"
#include "gollist.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004afc6c
// SIZE 0x30
class NullSoundManager : public SoundManager {
public:
	NullSoundManager();
	~NullSoundManager() override;                 // vtable+0x00
	LegoBool32 Initialize(LegoS32) override;      // vtable+0x04
	void Shutdown() override;                     // vtable+0x08
	void Pause() override;                        // vtable+0x0c
	void Resume() override;                       // vtable+0x10
	MusicGroup* CreateMusicGroup() override;      // vtable+0x14
	void DestroyMusicGroup(MusicGroup*) override; // vtable+0x18
	SoundGroup* CreateSoundGroup() override;      // vtable+0x1c
	void DestroySoundGroup(SoundGroup*) override; // vtable+0x20
	SoundNode* CreateSoundNode() override;        // vtable+0x24
	void DestroySoundNode(SoundNode*) override;   // vtable+0x28
	void Update(undefined4) override;             // vtable+0x34

	// SYNTHETIC: LEGORACERS 0x0041bce0
	// NullSoundManager::`scalar deleting destructor'

private:
	GolList<MusicGroup> m_musicGroups; // 0x18
	GolList<SoundGroup> m_soundGroups; // 0x24
};

#endif // NULLSOUNDMANAGER_H
