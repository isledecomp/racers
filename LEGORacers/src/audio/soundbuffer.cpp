#include "audio/soundbuffer.h"

#include "audio/directsoundconversions.h"
#include "audio/directsoundmanager.h"
#include "audio/frostpetal0x34.h"
#include "audio/soundinstance.h"
#include "audio/streamingsoundinstance.h"

DECOMP_SIZE_ASSERT(SoundBuffer, 0x48)

// GLOBAL: LEGORACERS 0x004afc58
LegoFloat g_defaultSoundVolume = 1.0f;

// GLOBAL: LEGORACERS 0x004afc5c
const LegoFloat g_defaultSoundPan = 0.0f;

// GLOBAL: LEGORACERS 0x004afc60
LegoFloat g_defaultSoundFrequencyScale = 1.0f;

// FUNCTION: LEGORACERS 0x0041b640
void SoundBuffer::ResetRuntimeState()
{
	m_soundManager = NULL;
	m_soundInstance = NULL;
	m_playbackState = c_playbackStateIdle;
	m_unk0x38 = 0;
	m_directSoundBuffer = NULL;
	m_unk0x44 = 0;
	m_sampleRate = c_defaultSampleRate;
	ResetSoundSettings();
	m_channelCount = c_defaultChannelCount;
	m_bitsPerSample = c_defaultBitsPerSample;
	m_stopWhenPaused = FALSE;
}

// FUNCTION: LEGORACERS 0x0041b680
SoundBuffer::SoundBuffer()
{
	ResetRuntimeState();
	m_priority = c_defaultPriority;
	m_streaming = FALSE;
	m_playFlags = c_playFlagNone;
}

// FUNCTION: LEGORACERS 0x0041b6d0
SoundBuffer::SoundBuffer(LegoBool32 p_streaming)
{
	ResetRuntimeState();
	m_streaming = p_streaming;

	if (p_streaming == TRUE) {
		m_priority = c_streamingPriority;
		m_playFlags = c_playFlagStreaming;
	}
	else {
		m_priority = c_defaultPriority;
		m_playFlags = c_playFlagNone;
	}
}

// FUNCTION: LEGORACERS 0x0041b720
SoundBuffer::~SoundBuffer()
{
	ReleaseDirectSoundBuffer();

	if (!m_streaming) {
		SoundInstance* sound = m_soundInstance;

		if (sound) {
			sound->SetSoundBuffer(NULL);
			sound = m_soundInstance;
			FrostPetal0x34* owner = sound->GetOwner();
			if (owner) {
				owner->DestroySoundInstance(sound);
			}
			else {
				delete sound;
			}
		}
	}
	else {
		StreamingSoundInstance* sound = m_streamingSoundInstance;

		if (sound) {
			sound->SetSoundBuffer(NULL);
			sound = m_streamingSoundInstance;
			FrostPetal0x34* owner = sound->GetOwner();
			if (owner) {
				owner->DestroyStreamingSoundInstance(sound);
			}
			else {
				delete sound;
			}
		}
	}

	if (m_soundManager) {
		m_link.Remove();
	}
}

// FUNCTION: LEGORACERS 0x0041b7b0
void SoundBuffer::ReleaseDirectSoundBuffer()
{
	StopOrRelease();
	m_unk0x38 = 0;

	if (m_directSoundBuffer) {
		m_directSoundBuffer->Release();
		m_directSoundBuffer = NULL;
	}
}

// FUNCTION: LEGORACERS 0x0041ba40
void SoundBuffer::SetVolume(LegoFloat p_volume)
{
	m_volume = p_volume;
	LegoS32 directSoundVolume = ConvertVolumeToDirectSound(p_volume);
	m_directSoundVolume = directSoundVolume;

	if (m_directSoundBuffer) {
		m_directSoundBuffer->SetVolume(directSoundVolume);
	}
}

// FUNCTION: LEGORACERS 0x0041ba70
void SoundBuffer::SetPan(LegoFloat p_pan)
{
	m_pan = p_pan;
	LegoS32 directSoundPan = ConvertPanToDirectSound(p_pan);
	m_directSoundPan = directSoundPan;

	if (m_directSoundBuffer) {
		m_directSoundBuffer->SetPan(directSoundPan);
	}
}

// FUNCTION: LEGORACERS 0x0041baa0
void SoundBuffer::SetFrequencyScale(LegoFloat p_frequencyScale)
{
	m_frequencyScale = p_frequencyScale;
	LegoFloat directSoundFrequency = m_sampleRate;
	directSoundFrequency *= p_frequencyScale;
	m_directSoundFrequency = (LegoS32) directSoundFrequency;

	if (m_directSoundBuffer) {
		m_directSoundBuffer->SetFrequency(m_directSoundFrequency);
	}
}

// FUNCTION: LEGORACERS 0x0041bb00
void SoundBuffer::ResetSoundSettings()
{
	SetVolume(g_defaultSoundVolume);
	SetPan(g_defaultSoundPan);
	SetFrequencyScale(g_defaultSoundFrequencyScale);
}

// FUNCTION: LEGORACERS 0x0041bc10
void SoundBuffer::StopOrRelease()
{
	if (m_playbackState != c_playbackStateIdle) {
		LPDIRECTSOUNDBUFFER buffer = m_directSoundBuffer;

		if (buffer) {
			buffer->Stop();
		}

		m_soundManager->MoveSoundToIdle(*this);
	}
}

// FUNCTION: LEGORACERS 0x0041bc40
void SoundBuffer::StopDirectSoundBuffer()
{
	LPDIRECTSOUNDBUFFER buffer = m_directSoundBuffer;

	if (buffer) {
		buffer->Stop();
	}
}

// FUNCTION: LEGORACERS 0x0041bc50
void SoundBuffer::ReleaseBufferPlayback()
{
	LPDIRECTSOUNDBUFFER buffer = m_directSoundBuffer;

	if (buffer) {
		buffer->SetCurrentPosition(0);
	}
}
