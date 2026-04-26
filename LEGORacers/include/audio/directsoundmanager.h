#ifndef DIRECTSOUNDMANAGER_H
#define DIRECTSOUNDMANAGER_H

#include "audio/directmusicgroup.h"
#include "audio/musicgroup.h"
#include "audio/soundbuffer.h"
#include "audio/soundgroup.h"
#include "audio/soundmanager.h"
#include "audio/soundnode.h"
#include "compat.h"
#include "decomp.h"
#include "gollist.h"

#include <dsound.h>
#include <objbase.h>

// VTABLE: LEGORACERS 0x004afaf0
// SIZE 0x98
class DirectSoundManager : public SoundManager {
public:
	enum {
		c_defaultActiveSoundCount = 0x20,
		c_defaultChannelCount = 2,
		c_defaultSampleRate = 22050,
		c_defaultBitsPerSample = 16,
	};

	DirectSoundManager();
	~DirectSoundManager() override;                                // vtable+0x00
	LegoBool32 Initialize(LegoS32 p_maxActiveSoundCount) override; // vtable+0x04
	void Shutdown() override;                                      // vtable+0x08
	void Pause() override;                                         // vtable+0x0c
	void Resume() override;                                        // vtable+0x10
	MusicGroup* CreateMusicGroup() override;                       // vtable+0x14
	void DestroyMusicGroup(MusicGroup*) override;                  // vtable+0x18
	SoundGroup* CreateSoundGroup() override;                       // vtable+0x1c
	void DestroySoundGroup(SoundGroup*) override;                  // vtable+0x20
	SoundNode* CreateSoundNode() override;                         // vtable+0x24
	void DestroySoundNode(SoundNode*) override;                    // vtable+0x28
	void Update(undefined4) override;                              // vtable+0x34

	void SetCooperativeWindow(HWND p_hwnd);
	void MoveSoundToIdle(SoundBuffer& p_sound);

	// SYNTHETIC: LEGORACERS 0x00418680
	// DirectSoundManager::`scalar deleting destructor'

private:
	LegoBool32 m_paused;                     // 0x18
	HWND m_currentCooperativeWindow;         // 0x1c
	HWND m_cooperativeWindow;                // 0x20
	LPDIRECTSOUND m_directSound;             // 0x24
	LegoS32 m_cooperativeLevel;              // 0x28
	LPGUID m_deviceGuid;                     // 0x2c
	LPDIRECTSOUNDBUFFER m_directSoundBuffer; // 0x30
	LegoU8 m_nChannels;                      // 0x34
	LegoU8 m_bitsPerSample;                  // 0x35
	undefined m_unk0x36[0x38 - 0x36];        // 0x36
	LegoU32 m_nSamplesPerSec;                // 0x38
	GolList<MusicGroup> m_musicGroups;       // 0x3c
	GolList<SoundGroup> m_soundGroups;       // 0x48
	LegoS32 m_maxActiveSoundCount;           // 0x54
	LegoS32 m_availableSoundCount;           // 0x58
	SoundBufferList m_idleSounds;            // 0x5c
	SoundBufferList m_unk0x68;               // 0x68
	SoundBufferList m_activeSounds;          // 0x74
	SoundBufferList m_unk0x80;               // 0x80
	SoundBufferList m_pausedSounds;          // 0x8c
};

#endif // DIRECTSOUNDMANAGER_H
