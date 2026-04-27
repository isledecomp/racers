#include "audio/directsoundgroup.h"

#include "audio/audiohelpers.h"
#include "audio/directsoundmanager.h"
#include "audio/soundbuffer.h"
#include "audio/sounddata.h"
#include "audio/soundinstance.h"
#include "audio/soundnode.h"
#include "audio/streamingsoundinstance.h"
#include "golfile.h"
#include "golstream.h"

#include <stdlib.h>
#include <string.h>

DECOMP_SIZE_ASSERT(DirectSoundGroup, 0x34)

// GLOBAL: LEGORACERS 0x004be7f4
LegoChar* g_soundBankExtension = ".SBK";

// GLOBAL: LEGORACERS 0x004afc04
LegoFloat g_defaultSoundInstanceVolume = 1.0f;

// FUNCTION: LEGORACERS 0x0041ae10
DirectSoundGroup::DirectSoundGroup()
{
	m_soundManager = NULL;
	m_soundCount = 0;
	m_unk0x10 = 0;
	m_soundData = NULL;
}

// FUNCTION: LEGORACERS 0x0041ae50
DirectSoundGroup::~DirectSoundGroup()
{
	Unload();
}

// FUNCTION: LEGORACERS 0x0041ae60
void DirectSoundGroup::Load(const LegoChar* p_name)
{
	GolFile file;
	LegoChar soundBankPath[c_audioPathLength];
	LegoChar countString[c_soundCountLength];
	LegoChar soundBasePath[c_audioPathLength];
	LegoChar soundName[c_audioPathLength];
	LegoS32 index = 0;

	strncpy(soundBankPath, p_name, c_audioPathLength);

	LegoS32 soundBankPathLength = strlen(soundBankPath);
	if ((soundBankPathLength < c_soundBankExtensionLength ||
		 stricmp(&soundBankPath[soundBankPathLength - c_soundBankExtensionLength], g_soundBankExtension)) &&
		(soundBankPathLength + c_soundBankExtensionLength) <= c_audioPathLength) {
		strcat(soundBankPath, g_soundBankExtension);
	}

	Unload();

	if (!file.BufferedOpen(soundBankPath, GolStream::c_modeRead | GolStream::c_modeTextAppend, c_fileBufferSize)) {
		file.ReadLine(soundBasePath, c_audioPathLength);
		file.ReadLine(countString, sizeof(countString));
		LegoS32 soundCount = atoi(countString);
		m_soundCount = soundCount;

		if (soundCount > 0) {
			m_soundData = new SoundData[soundCount];
		}

		if (m_soundData) {
			LegoChar* soundPaths = new LegoChar[c_audioPathLength * m_soundCount];

			if (soundPaths) {
				LegoChar* currentPath = soundPaths;

				while (index < (LegoS32) m_soundCount) {
					if (file.ReadLine(soundName, c_audioPathLength)) {
						*currentPath = '\0';
					}
					else {
						LowercaseString(soundName);
						JoinAudioPath(currentPath, c_audioPathLength, soundBasePath, soundName);
					}

					index++;
					currentPath += c_audioPathLength;
				}

				file.Dispose();

				index = 0;
				currentPath = soundPaths;
				while (index < (LegoS32) m_soundCount) {
					m_soundData[index].Load(currentPath);
					index++;
					currentPath += c_audioPathLength;
				}

				operator delete(soundPaths);
			}
		}
		else {
			Unload();
		}

		file.Dispose();
	}
}

// FUNCTION: LEGORACERS 0x0041b0e0
void DirectSoundGroup::Unload()
{
	while (TRUE) {
		GolListLink* link = m_soundInstances.LastLink();

		if (!m_soundInstances.IsValidLastLink(link)) {
			break;
		}

		DestroySoundInstance(&m_soundInstances.GetItem(*link));
	}

	while (TRUE) {
		GolListLink* link = m_streamingSoundInstances.LastLink();

		if (!m_streamingSoundInstances.IsValidLastLink(link)) {
			break;
		}

		DestroyStreamingSoundInstance(&m_streamingSoundInstances.GetItem(*link));
	}

	if (m_soundData) {
		delete[] m_soundData;
		m_soundData = NULL;
	}

	m_unk0x10 = 0;
	m_soundCount = 0;
}

// FUNCTION: LEGORACERS 0x0041b150
LegoBool32 DirectSoundGroup::IsLoaded()
{
	if (m_soundCount && m_soundData) {
		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x0041b170
LegoU32 DirectSoundGroup::GetSoundCount()
{
	return m_soundCount;
}

// FUNCTION: LEGORACERS 0x0041b180
void DirectSoundGroup::PlaySoundByIndex(LegoU32 p_index)
{
	if (static_cast<DirectSoundManager*>(m_soundManager)->CanPlaySound(0)) {
		SoundInstance* sound = CreateSoundInstance(p_index);

		if (sound) {
			sound->GetSoundBuffer()->m_stopWhenPaused = TRUE;
			sound->Play(FALSE);
			sound->SetVolume(g_defaultSoundInstanceVolume);
		}
	}
}

// FUNCTION: LEGORACERS 0x0041b1d0
SoundInstance* DirectSoundGroup::CreateSoundInstance(LegoU32 p_index)
{
	if (p_index >= m_soundCount) {
		return NULL;
	}

	if (!m_soundData) {
		return NULL;
	}

	SoundData* soundData = &m_soundData[p_index];
	if (!soundData->GetData()) {
		return NULL;
	}

	SoundBuffer* soundBuffer = static_cast<DirectSoundManager*>(m_soundManager)->CreateSoundBuffer(soundData);
	if (!soundBuffer) {
		return NULL;
	}

	SoundInstance* sound = new SoundInstance();
	if (sound) {
		sound->SetSoundGroup(this);
		m_soundInstances.Append(static_cast<GolListLink*>(sound));
		sound->SetSoundBuffer(soundBuffer);
		soundBuffer->m_soundInstance = sound;
		sound->SetVolume(g_defaultSoundInstanceVolume);
		return sound;
	}
	else {
		static_cast<DirectSoundManager*>(m_soundManager)->DestroySoundBuffer(soundBuffer);
	}

	return sound;
}

// FUNCTION: LEGORACERS 0x0041b2d0 FOLDED
void DirectSoundGroup::DestroySoundInstance(SoundInstance* p_sound)
{
	p_sound->SetSoundGroup(NULL);
	p_sound->Remove();
	delete p_sound;
}

// FUNCTION: LEGORACERS 0x0041b300
void DirectSoundGroup::PlaySpatialSound(
	LegoU32 p_index,
	SoundNode* p_node,
	LegoFloat p_minDistance,
	LegoFloat p_maxDistance,
	LegoFloat p_volume,
	LegoFloat p_frequencyScale
)
{
	StreamingSoundInstance* sound = CreateStreamingSoundInstance(p_index);

	if (sound) {
		LegoFloat minDistSq = p_minDistance * p_minDistance;
		LegoFloat maxDistSq = p_maxDistance * p_maxDistance;
		sound->GetSoundBuffer()->m_stopWhenPaused = TRUE;
		sound->m_position = p_node->m_position;
		sound->m_minDistanceSquared = minDistSq;
		sound->m_maxDistanceSquared = maxDistSq;
		sound->SetVolume(p_volume);
		sound->m_frequencyScale = p_frequencyScale;
		sound->Play(FALSE);
	}
}

// FUNCTION: LEGORACERS 0x0041b370
StreamingSoundInstance* DirectSoundGroup::CreateStreamingSoundInstance(LegoU32 p_index)
{
	if (p_index >= m_soundCount) {
		return NULL;
	}

	if (!m_soundData) {
		return NULL;
	}

	SoundData* soundData = &m_soundData[p_index];
	if (!soundData->GetData()) {
		return NULL;
	}

	SoundBuffer* soundBuffer = static_cast<DirectSoundManager*>(m_soundManager)->CreateStreamingSoundBuffer(soundData);
	if (!soundBuffer) {
		return NULL;
	}

	StreamingSoundInstance* sound = new StreamingSoundInstance();
	if (sound) {
		sound->SetSoundGroup(this);
		m_streamingSoundInstances.Append(static_cast<GolListLink*>(sound));
		sound->SetSoundBuffer(soundBuffer);
		soundBuffer->m_streamingSoundInstance = sound;
		sound->SetVolume(g_defaultSoundInstanceVolume);
		return sound;
	}
	else {
		static_cast<DirectSoundManager*>(m_soundManager)->DestroySoundBuffer(soundBuffer);
	}

	return sound;
}

// FUNCTION: LEGORACERS 0x0041b470 FOLDED
void DirectSoundGroup::DestroyStreamingSoundInstance(StreamingSoundInstance* p_sound)
{
	p_sound->SetSoundGroup(NULL);
	p_sound->Remove();
	delete p_sound;
}

// FUNCTION: LEGORACERS 0x0041b4a0 FOLDED
SoundManager* DirectSoundGroup::GetSoundManager()
{
	return m_soundManager;
}
