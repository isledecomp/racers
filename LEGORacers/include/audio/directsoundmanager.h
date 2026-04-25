#ifndef DIRECTSOUNDMANAGER_H
#define DIRECTSOUNDMANAGER_H

#include "audio/soundbuffer.h"
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
	CrimsonRay0x20* VTable0x14() override;                         // vtable+0x14
	void VTable0x18(CrimsonRay0x20*) override;                     // vtable+0x18
	EmberDust0x28* VTable0x1c() override;                          // vtable+0x1c
	void VTable0x20(EmberDust0x28*) override;                      // vtable+0x20
	SoundNode* VTable0x24() override;                              // vtable+0x24
	void VTable0x28(SoundNode*) override;                          // vtable+0x28
	void VTable0x34(undefined4) override;                          // vtable+0x34

	void SetCooperativeWindow(HWND p_hwnd);
	void MoveSoundToIdle(SoundBuffer& p_sound);

	// SYNTHETIC: LEGORACERS 0x00418680
	// DirectSoundManager::`scalar deleting destructor'

private:
	LegoBool32 m_paused;                     // 0x18
	HWND m_unk0x1c;                          // 0x1c
	HWND m_unk0x20;                          // 0x20
	LPDIRECTSOUND m_directSound;             // 0x24
	LegoS32 m_cooperativeLevel;              // 0x28
	LPGUID m_unk0x2c;                        // 0x2c
	LPDIRECTSOUNDBUFFER m_directSoundBuffer; // 0x30
	LegoU8 m_nChannels;                      // 0x34
	LegoU8 m_bitsPerSample;                  // 0x35
	undefined m_unk0x36[0x38 - 0x36];        // 0x36
	LegoU32 m_nSamplesPerSec;                // 0x38
	GolList<CrimsonRay0x20> m_unk0x3c;       // 0x3c
	GolList<EmberDust0x28> m_unk0x48;        // 0x48
	LegoS32 m_maxActiveSoundCount;           // 0x54
	LegoS32 m_availableSoundCount;           // 0x58
	SoundBufferList m_unk0x5c;               // 0x5c
	SoundBufferList m_unk0x68;               // 0x68
	SoundBufferList m_activeSounds;          // 0x74
	SoundBufferList m_unk0x80;               // 0x80
	SoundBufferList m_pausedSounds;          // 0x8c
};

#endif // DIRECTSOUNDMANAGER_H
