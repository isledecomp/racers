#include "audio/soundbuffer.h"

#include "audio/audiohelpers.h"
#include "audio/directsoundconversions.h"
#include "audio/directsoundgroup.h"
#include "audio/directsoundmanager.h"
#include "audio/sounddata.h"
#include "audio/soundinstance.h"
#include "audio/streamingsoundinstance.h"

DECOMP_SIZE_ASSERT(SoundBuffer, 0x48)

// GLOBAL: LEGORACERS 0x004afc58
LegoFloat g_defaultSoundVolume = 1.0f;

// GLOBAL: LEGORACERS 0x004afc5c
const LegoFloat g_defaultSoundPan = 0.0f;

// GLOBAL: LEGORACERS 0x004afc60
LegoFloat g_defaultSoundFrequencyScale = 1.0f;

// FUNCTION: LEGORACERS 0x0041b5d0
LegoChar LowercaseString(LegoChar* p_string)
{
	LegoChar* cursor = p_string;
	LegoChar result = *cursor;

	while (result) {
		if (result >= 'A' && result <= 'Z') {
			*cursor = result + ('a' - 'A');
		}

		cursor++;
		result = *cursor;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0041b5f0
LegoChar* JoinAudioPath(LegoChar* p_destination, LegoU32 p_size, const LegoChar* p_basePath, const LegoChar* p_name)
{
	LegoChar* destination = p_destination;
	p_size--;

	while (*p_basePath) {
		if (!p_size) {
			break;
		}

		*destination++ = *p_basePath++;
		p_size--;
	}

	while (*p_name) {
		if (!p_size) {
			break;
		}

		*destination++ = *p_name++;
		p_size--;
	}

	*destination = '\0';
	return destination;
}

// FUNCTION: LEGORACERS 0x0041b640
void SoundBuffer::ResetRuntimeState()
{
	m_soundManager = NULL;
	m_soundInstance = NULL;
	m_playbackState = c_playbackStateIdle;
	m_soundData = NULL;
	m_directSoundBuffer = NULL;
	m_directSoundBufferSize = 0;
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
		m_playFlags = c_playFlagsLooping;
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
		if (m_soundInstance) {
			m_soundInstance->SetSoundBuffer(NULL);
			DirectSoundGroup* soundGroup = m_soundInstance->GetSoundGroupDirect();
			if (soundGroup) {
				soundGroup->DestroySoundInstance(m_soundInstance);
			}
			else {
				delete m_soundInstance;
			}
		}
	}
	else {
		if (m_streamingSoundInstance) {
			m_streamingSoundInstance->SetSoundBuffer(NULL);
			DirectSoundGroup* soundGroup = m_streamingSoundInstance->GetSoundGroupDirect();
			if (soundGroup) {
				soundGroup->DestroyStreamingSoundInstance(m_streamingSoundInstance);
			}
			else {
				delete m_streamingSoundInstance;
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
	m_soundData = NULL;

	if (m_directSoundBuffer) {
		m_directSoundBuffer->Release();
		m_directSoundBuffer = NULL;
	}
}

// FUNCTION: LEGORACERS 0x0041b7e0
LegoBool32 SoundBuffer::CreateDirectSoundBuffer(LegoU32 p_bufferSize)
{
	ReleaseDirectSoundBuffer();
	m_directSoundBufferSize = p_bufferSize;

	if (!p_bufferSize) {
		return FALSE;
	}

	WAVEFORMATEX waveFormat;
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nChannels = m_channelCount;
	waveFormat.nSamplesPerSec = (LegoU32) m_sampleRate;
	waveFormat.wBitsPerSample = m_bitsPerSample;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample + 7) / 8 * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	DSBUFFERDESC bufferDesc;
	bufferDesc.dwSize = sizeof(bufferDesc);
	bufferDesc.dwFlags = DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = p_bufferSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;

	if (m_soundManager->GetDirectSound()->CreateSoundBuffer(&bufferDesc, &m_directSoundBuffer, NULL)) {
		m_directSoundBufferSize = 0;
		return FALSE;
	}

	ApplyDirectSoundSettings();
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0041b8d0
LegoBool32 SoundBuffer::LoadSoundData(SoundData* p_data)
{
	if (!p_data) {
		ReleaseDirectSoundBuffer();
		return FALSE;
	}

	if (!p_data->GetData()) {
		ReleaseDirectSoundBuffer();
		return FALSE;
	}

	if (m_directSoundBuffer) {
		if (m_soundData == p_data && m_channelCount == p_data->GetChannelCount() &&
			m_bitsPerSample == p_data->GetBitsPerSample() &&
			m_directSoundBufferSize == (p_data->GetDecodedSize() << p_data->GetShift())) {
			return TRUE;
		}
	}

	m_channelCount = p_data->GetChannelCount();
	m_bitsPerSample = p_data->GetBitsPerSample();
	LegoS32 sampleRate = p_data->GetSampleRate() << p_data->GetShift();
	m_sampleRate = (LegoFloat) sampleRate;

	if (!CreateDirectSoundBuffer(p_data->GetDecodedSize() << p_data->GetShift())) {
		return FALSE;
	}

	LPVOID audioPtr1;
	LPVOID audioPtr2;
	DWORD audioBytes1;
	DWORD audioBytes2;

	if (!m_directSoundBuffer->Lock(0, 0, &audioPtr1, &audioBytes1, &audioPtr2, &audioBytes2, DSBLOCK_ENTIREBUFFER)) {
		p_data->Decode((LegoS16*) audioPtr1);
		m_directSoundBuffer->Unlock(audioPtr1, audioBytes1, audioPtr2, audioBytes2);
		m_soundData = p_data;
		return TRUE;
	}

	ReleaseDirectSoundBuffer();
	return FALSE;
}

// FUNCTION: LEGORACERS 0x0041b9e0
LegoBool32 SoundBuffer::IsPlaying()
{
	DWORD status;

	if (m_directSoundBuffer) {
		m_directSoundBuffer->GetStatus(&status);

		if ((LegoU8) status & DSBSTATUS_PLAYING) {
			return TRUE;
		}
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x0041ba10
void SoundBuffer::SetPriority(LegoS32 p_priority)
{
	if (!m_streaming) {
		if (m_playbackState == c_playbackStateIdle) {
			m_priority = c_defaultPriority + p_priority;
		}
	}
	else {
		m_priority = p_priority;
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

// FUNCTION: LEGORACERS 0x0041bad0
void SoundBuffer::ApplyDirectSoundSettings()
{
	if (m_directSoundBuffer) {
		m_directSoundBuffer->SetVolume(m_directSoundVolume);
		m_directSoundBuffer->SetPan(m_directSoundPan);
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

// FUNCTION: LEGORACERS 0x0041bb30
LegoBool32 SoundBuffer::Play(LegoBool32 p_loop)
{
	LegoBool32 result = FALSE;

	if (IsPlaying()) {
		result = TRUE;
	}
	else if (!m_streaming) {
		ReleaseBufferPlayback();
		ApplyDirectSoundSettings();

		if (p_loop) {
			m_playFlags = c_playFlagsLooping;
		}
		else {
			m_playFlags = c_playFlagNone;
		}

		if (m_soundManager->QueueSound(*this)) {
			if (m_playFlags & c_playFlagLooping) {
				m_directSoundBuffer->Play(0, 0, c_playFlagDirectSoundLooping);
			}
			else {
				m_directSoundBuffer->Play(0, 0, 0);
			}

			result = TRUE;
		}
		else if (m_stopWhenPaused) {
			m_soundManager->MoveSoundToIdle(*this);
		}
	}
	else if (m_playbackState == c_playbackStateIdle) {
		ReleaseBufferPlayback();

		if (p_loop) {
			m_playFlags = c_playFlagsLooping;
			m_soundManager->QueueSound(*this);
		}
		else {
			m_playFlags = c_playFlagNone;
			m_soundManager->QueueSound(*this);
		}
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0041bc10
void SoundBuffer::StopOrRelease()
{
	if (m_playbackState != c_playbackStateIdle) {
		if (m_directSoundBuffer) {
			m_directSoundBuffer->Stop();
		}

		m_soundManager->MoveSoundToIdle(*this);
	}
}

// FUNCTION: LEGORACERS 0x0041bc40
void SoundBuffer::StopDirectSoundBuffer()
{
	if (m_directSoundBuffer) {
		m_directSoundBuffer->Stop();
	}
}

// FUNCTION: LEGORACERS 0x0041bc50
void SoundBuffer::ReleaseBufferPlayback()
{
	if (m_directSoundBuffer) {
		m_directSoundBuffer->SetCurrentPosition(0);
	}
}

// FUNCTION: LEGORACERS 0x0041bc60
void SoundBuffer::StartDirectSoundBuffer()
{
	if (m_directSoundBuffer) {
		ApplyDirectSoundSettings();

		if (m_playFlags & c_playFlagLooping) {
			m_directSoundBuffer->Play(0, 0, c_playFlagDirectSoundLooping);
			return;
		}

		m_directSoundBuffer->Play(0, 0, 0);
	}
}
