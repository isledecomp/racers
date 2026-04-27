#ifndef DIRECTMUSICSTREAM_H
#define DIRECTMUSICSTREAM_H

#include "audio/musicinstancestate.h"
#include "compat.h"
#include "decomp.h"
#include "gollist.h"
#include "types.h"

#include <dsound.h>
#include <windows.h>

// VTABLE: LEGORACERS 0x004afb68
// SIZE 0x44
class DirectMusicStream : public MusicInstanceState {
public:
	enum {
		c_defaultChannelCount = 2,
		c_defaultSampleRate = 22050,
		c_defaultAverageBytesPerSecond = 88200,
		c_defaultBufferSeconds = 2,
		c_defaultBitsPerSample = 16,
		c_defaultBytesPerSample = 2,
		c_streamBufferAlignment = 0x1000,
		c_streamTimerDelay = 100,
		c_serviceByteScale = 0x14d000,
		c_serviceBlockPadding = 2,
		c_directSoundBufferFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_CTRLVOLUME
	};

	DirectMusicStream();
	~DirectMusicStream() override;                    // vtable+0x00
	void SetVolume(LegoFloat p_volume) override;      // vtable+0x18
	virtual void ReleaseResources();                  // vtable+0x24
	virtual LegoBool32 Initialize();                  // vtable+0x28
	virtual LegoS32 FillBuffer(LegoS32 p_blocks) = 0; // vtable+0x2c
	virtual void Service();                           // vtable+0x30

	// SYNTHETIC: LEGORACERS 0x0041a210
	// DirectMusicStream::`scalar deleting destructor'

	HANDLE GetMutex() { return m_mutex; }

protected:
	friend struct DirectMusicStreamListTraits;

	LPDIRECTSOUND GetDirectSound();

	GolListLink m_updateLink;                // 0x18
	LPDIRECTSOUNDBUFFER m_directSoundBuffer; // 0x20
	LegoS32 m_bufferSize;                    // 0x24
	LegoS32 m_channelCount;                  // 0x28
	LegoS32 m_averageBytesPerSecond;         // 0x2c
	LegoS32 m_sampleRate;                    // 0x30
	LegoS32 m_bufferSeconds;                 // 0x34
	LegoS32 m_serviceBlocks;                 // 0x38
	HANDLE m_mutex;                          // 0x3c
	LegoBool32 m_streamError;                // 0x40
};

struct DirectMusicStreamListTraits {
	static GolListLink* GetLink(DirectMusicStream& p_instance) { return &p_instance.m_updateLink; }
	static DirectMusicStream& GetItem(GolListLink& p_link)
	{
		return *CONTAINING_RECORD(&p_link, DirectMusicStream, m_updateLink);
	}
};

#endif // DIRECTMUSICSTREAM_H
