#ifndef DIRECTMUSICINSTANCE_H
#define DIRECTMUSICINSTANCE_H

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

// VTABLE: LEGORACERS 0x004afb34
// SIZE 0x417c
class DirectMusicInstance : public DirectMusicStream {
public:
	enum {
		c_pathLength = 260,
		c_streamScratchSize = 0x4000,
		c_adpcmMagic = 0x20504c41,
		c_adpcmFormat = 0x43504441,
		c_adpcmHeaderSize = 0x10,
		c_readChunkSize = 0x4000,
		c_prefillBlockSize = 2048,
		c_invalidFileHandle = -1,
		c_lostBuffer = DSERR_BUFFERLOST
	};

	// SIZE 0x10
	struct AdpcmHeader {
		LegoU32 m_magic;               // 0x00
		LegoU32 m_dataOffset;          // 0x04
		LegoU32 m_format;              // 0x08
		LegoU8 m_padding[0x0f - 0x0c]; // 0x0c
		LegoU8 m_channelCount;         // 0x0f
	};

	DirectMusicInstance();
	~DirectMusicInstance() override;               // vtable+0x00
	LegoBool32 Play(LegoBool32 p_loop) override;   // vtable+0x04
	void Stop() override;                          // vtable+0x08
	void Pause() override;                         // vtable+0x0c
	void Resume() override;                        // vtable+0x10
	LegoBool32 IsPlaying() override;               // vtable+0x14
	void VTable0x1c(undefined4 p_arg) override;    // vtable+0x1c
	void VTable0x20(undefined4 p_arg) override;    // vtable+0x20
	void ReleaseResources() override;              // vtable+0x24
	LegoS32 FillBuffer(LegoS32 p_blocks) override; // vtable+0x2c
	void Service() override;                       // vtable+0x30

	LegoBool32 SetPath(const LegoChar* p_path);

	// SYNTHETIC: LEGORACERS 0x00419720
	// DirectMusicInstance::`scalar deleting destructor'

private:
	void StopBuffer();
	void CloseFile();
	LegoBool32 OpenFileAndPlay(LegoBool p_play);
	void PauseDirectSoundBuffer();
	void ResumeDirectSoundBuffer();

	HANDLE m_file;                 // 0x44
	LegoS32 m_fileSize;            // 0x48
	LegoChar m_path[c_pathLength]; // 0x4c
	LegoBool32 m_restartRequested; // 0x150
	LegoU32 m_sourceChannelCount;  // 0x154
	LegoU32 m_dataStart;           // 0x158
	LegoS32 m_loopCount;           // 0x15c
	LegoS32 m_remainingBytes;      // 0x160
	LegoS32 m_writeCursor;         // 0x164
	LegoS32 m_silenceBytes;        // 0x168
	LegoS32 m_leftState[2];        // 0x16c
	LegoS32 m_rightState[2];       // 0x174
	union {
		AdpcmHeader m_adpcmHeader;                  // 0x17c
		LegoU8 m_streamBuffer[c_streamScratchSize]; // 0x17c
	};
};

struct DirectMusicStreamListTraits {
	static GolListLink* GetLink(DirectMusicStream& p_instance) { return &p_instance.m_updateLink; }
	static DirectMusicStream& GetItem(GolListLink& p_link)
	{
		return *CONTAINING_RECORD(&p_link, DirectMusicStream, m_updateLink);
	}
};

#endif // DIRECTMUSICINSTANCE_H
