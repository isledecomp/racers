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

class SoundData;

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
	SoundBuffer* CreateSoundBuffer();
	SoundBuffer* CreateSoundBuffer(SoundData* p_data);
	SoundBuffer* CreateStreamingSoundBuffer();
	SoundBuffer* CreateStreamingSoundBuffer(SoundData* p_data);
	void DestroySoundBuffer(SoundBuffer* p_sound);
	LegoBool32 CanPlaySound(LegoS32 p_priority);
	LegoBool32 QueueSound(SoundBuffer& p_sound);
	LPDIRECTSOUND GetDirectSound() { return m_directSound; }

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
	SoundBufferList m_activeSounds;          // 0x68
	SoundBufferList m_activeSpatialSounds;   // 0x74
	SoundBufferList m_queuedSounds;          // 0x80
	SoundBufferList m_queuedSpatialSounds;   // 0x8c

	void DestroyPendingStoppedSounds();
	void ReleaseStoppedSounds();
	LegoS32 GetAvailableSoundCount();
	LegoBool32 MakeSoundAvailable(LegoS32 p_priority);
	void InsertByPriority(SoundBufferList& p_list, SoundBuffer& p_sound)
	{
		GolListLink* link = p_list.FirstLink();
		while (link && p_list.IsValidLink(link)) {
			SoundBuffer& currentSound = p_list.GetItem(*link);

			if (p_sound.m_priority <= currentSound.m_priority) {
				p_sound.GetLink().InsertBefore(link);
				return;
			}

			link = link->NextValid();
		}

		p_list.Append(p_sound);
	}
};

#endif // DIRECTSOUNDMANAGER_H
