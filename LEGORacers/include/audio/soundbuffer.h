#ifndef SOUNDBUFFER_H
#define SOUNDBUFFER_H

#include "compat.h"
#include "decomp.h"
#include "gollist.h"
#include "types.h"

#include <dsound.h>

class DirectSoundManager;
class SoundBuffer;
class SoundInstance;
class SoundData;
class StreamingSoundInstance;
struct SoundBufferListTraits;

// VTABLE: LEGORACERS 0x004afc64
// SIZE 0x48
class SoundBuffer {
public:
	enum {
		c_playbackStateQueued = 0,
		c_playbackStateActive = 1,
		c_playbackStateIdle = 2,
		c_defaultPriority = 4096,
		c_streamingPriority = 0,
		c_playFlagNone = 0,
		c_playFlagDirectSoundLooping = DSBPLAY_LOOPING,
		c_playFlagLooping = (1 << 1),
		c_playFlagsLooping = c_playFlagDirectSoundLooping | c_playFlagLooping,
		c_defaultSampleRate = 22050,
		c_defaultChannelCount = 1,
		c_defaultBitsPerSample = 16,
	};

	SoundBuffer();
	SoundBuffer(LegoBool32 p_streaming);
	virtual ~SoundBuffer();                  // vtable+0x00
	virtual void ReleaseDirectSoundBuffer(); // vtable+0x04

	// SYNTHETIC: LEGORACERS 0x0041b6b0
	// SoundBuffer::`scalar deleting destructor'

	void ResetRuntimeState();
	void StopOrRelease();
	void StopDirectSoundBuffer();
	void ReleaseBufferPlayback();
	void ApplyDirectSoundSettings();
	LegoBool32 Play(LegoBool32 p_loop);
	LegoBool32 LoadSoundData(SoundData* p_data);
	LegoBool32 CreateDirectSoundBuffer(LegoU32 p_bufferSize);
	void StartDirectSoundBuffer();
	LegoBool32 IsPlaying();
	void SetPriority(LegoS32 p_priority);
	void ResetSoundSettings();
	void SetVolume(LegoFloat p_volume);
	void SetPan(LegoFloat p_pan);
	void SetFrequencyScale(LegoFloat p_frequencyScale);

	GolListLink& GetLink() { return m_link; }
	LegoU8 GetPlaybackState() { return m_playbackState; }
	LegoBool ShouldStopWhenPaused() { return m_stopWhenPaused; }
	LegoFloat GetVolume() { return m_volume; }
	void ClearSoundInstance() { m_soundInstance = NULL; }
	void SetPlaybackState(LegoU8 p_playbackState) { m_playbackState = p_playbackState; }
	template <class TList>
	void MoveToList(TList& p_list, LegoU8 p_playbackState)
	{
		m_link.Remove();
		m_playbackState = p_playbackState;
		p_list.Append(*this);
	}

private:
	friend class DirectSoundGroup;
	friend class DirectSoundManager;
	friend struct SoundBufferListTraits;

	GolListLink m_link;                 // 0x04
	LegoS32 m_priority;                 // 0x0c
	DirectSoundManager* m_soundManager; // 0x10
	LegoU8 m_playbackState;             // 0x14
	LegoBool m_streaming;               // 0x15
	LegoBool m_stopWhenPaused;          // 0x16
	LegoU8 m_playFlags;                 // 0x17
	union {
		SoundInstance* m_soundInstance;                   // 0x18
		StreamingSoundInstance* m_streamingSoundInstance; // 0x18
	};
	LegoFloat m_volume;                      // 0x1c
	LegoFloat m_pan;                         // 0x20
	LegoFloat m_frequencyScale;              // 0x24
	LegoS32 m_directSoundVolume;             // 0x28
	LegoS32 m_directSoundPan;                // 0x2c
	LegoS32 m_directSoundFrequency;          // 0x30
	LegoFloat m_sampleRate;                  // 0x34
	SoundData* m_soundData;                  // 0x38
	LPDIRECTSOUNDBUFFER m_directSoundBuffer; // 0x3c
	LegoU8 m_channelCount;                   // 0x40
	LegoU8 m_bitsPerSample;                  // 0x41
	undefined m_unk0x42[0x44 - 0x42];        // 0x42
	LegoU32 m_directSoundBufferSize;         // 0x44
};

struct SoundBufferListTraits {
	static GolListLink* GetLink(SoundBuffer& p_sound) { return &p_sound.m_link; }
	static SoundBuffer& GetItem(GolListLink& p_link) { return *CONTAINING_RECORD(&p_link, SoundBuffer, m_link); }
};

typedef GolList<SoundBuffer, SoundBufferListTraits> SoundBufferList;

#endif // SOUNDBUFFER_H
