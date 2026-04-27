#include "audio/directsoundmanager.h"

#include "audio/directmusicgroup.h"
#include "audio/directsoundgroup.h"
#include "audio/nullsoundgroup.h"
#include "audio/soundbuffer.h"
#include "audio/soundnode.h"
#include "audio/streamingsoundinstance.h"
#include "types.h"

DECOMP_SIZE_ASSERT(DirectSoundManager, 0x98)

// FUNCTION: LEGORACERS 0x004185d0
DirectSoundManager::DirectSoundManager()
{
	m_cooperativeLevel = DSSCL_PRIORITY;
	m_nChannels = c_defaultChannelCount;
	m_cooperativeWindow = NULL;
	m_currentCooperativeWindow = NULL;
	m_directSound = NULL;
	m_deviceGuid = NULL;
	m_directSoundBuffer = NULL;
	m_nSamplesPerSec = c_defaultSampleRate;
	m_bitsPerSample = c_defaultBitsPerSample;
	m_paused = FALSE;
	m_availableSoundCount = 0;
	m_maxActiveSoundCount = 0;
}

// FUNCTION: LEGORACERS 0x004186a0
DirectSoundManager::~DirectSoundManager()
{
	Shutdown();
}

// FUNCTION: LEGORACERS 0x004186f0
LegoBool32 DirectSoundManager::Initialize(LegoS32 p_maxActiveSoundCount)
{
	Shutdown();

	if (!m_cooperativeWindow) {
		HWND hwnd = GetForegroundWindow();
		DWORD hwndProcessId;
		GetWindowThreadProcessId(hwnd, &hwndProcessId);

		if (hwndProcessId == GetCurrentProcessId()) {
			SetCooperativeWindow(hwnd);
		}

		if (!m_cooperativeWindow) {
			return FALSE;
		}
	}

	WAVEFORMATEX waveformat;
	waveformat.nChannels = m_nChannels;
	waveformat.wBitsPerSample = m_bitsPerSample;
	waveformat.nSamplesPerSec = m_nSamplesPerSec;
	waveformat.nBlockAlign = (waveformat.wBitsPerSample + 7) / 8 * waveformat.nChannels;
	waveformat.wFormatTag = WAVE_FORMAT_PCM;
	waveformat.nAvgBytesPerSec = m_nSamplesPerSec * waveformat.nBlockAlign;
	waveformat.cbSize = 0;

	if (DirectSoundCreate(m_deviceGuid, &m_directSound, NULL)) {
		m_directSound = NULL;
		return FALSE;
	}

	if (m_directSound->SetCooperativeLevel(m_cooperativeWindow, m_cooperativeLevel)) {
		Shutdown();
		return FALSE;
	}

	HWND activeWindow = GetActiveWindow();
	if (m_cooperativeWindow != activeWindow) {
		SetCooperativeWindow(activeWindow);
	}

	DSBUFFERDESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;

	if (m_directSound->CreateSoundBuffer(&bufferDesc, &m_directSoundBuffer, NULL)) {
		Shutdown();
		return FALSE;
	}

	if (m_cooperativeLevel >= DSSCL_PRIORITY) {
		if (m_directSoundBuffer->SetFormat(&waveformat)) {
			Shutdown();
			return FALSE;
		}
	}

	DSBCAPS caps;
	caps.dwSize = sizeof(DSBCAPS);

	m_directSoundBuffer->GetCaps(&caps);
	m_directSoundBuffer->Play(0, 0, DSBPLAY_LOOPING);

	m_paused = FALSE;
	m_availableSoundCount = p_maxActiveSoundCount;
	m_maxActiveSoundCount = p_maxActiveSoundCount;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x004188b0
void DirectSoundManager::Shutdown()
{
	while (TRUE) {
		GolListLink* link = m_musicGroups.LastLink();

		if (!m_musicGroups.IsValidLastLink(link)) {
			break;
		}

		DestroyMusicGroup(&m_musicGroups.GetItem(*link));
	}

	while (TRUE) {
		GolListLink* link = m_soundGroups.LastLink();

		if (!m_soundGroups.IsValidLastLink(link)) {
			break;
		}

		DestroySoundGroup(&m_soundGroups.GetItem(*link));
	}

	while (m_activeSoundNodes) {
		DestroySoundNode(m_activeSoundNodes);
	}

	while (m_soundNodes) {
		DestroySoundNode(m_soundNodes);
	}

	if (m_directSoundBuffer) {
		m_directSoundBuffer->Release();
		m_directSoundBuffer = NULL;
	}

	if (m_directSound) {
		m_directSound->Release();
		m_directSound = NULL;
	}

	m_availableSoundCount = 0;
	m_maxActiveSoundCount = 0;
}

// FUNCTION: LEGORACERS 0x00418940
void DirectSoundManager::Update(undefined4)
{
	SoundBufferList spatialSounds;

	ReleaseStoppedSounds();

	GolListLink* link;
	m_activeSpatialSounds.Swap(spatialSounds);

	link = spatialSounds.FirstLink();
	while (link && spatialSounds.IsValidLink(link)) {
		SoundBuffer& sound = spatialSounds.GetItem(*link);
		link = spatialSounds.NextLink(link);

		sound.GetLink().Remove();
		sound.m_streamingSoundInstance->UpdateSpatial(m_activeSoundNodes);
		InsertByPriority(m_activeSpatialSounds, sound);
	}

	m_queuedSpatialSounds.Swap(spatialSounds);

	link = spatialSounds.FirstLink();
	while (link && spatialSounds.IsValidLink(link)) {
		SoundBuffer& sound = spatialSounds.GetItem(*link);
		link = spatialSounds.NextLink(link);

		sound.GetLink().Remove();
		sound.m_streamingSoundInstance->UpdateSpatial(m_activeSoundNodes);
		InsertByPriority(m_queuedSpatialSounds, sound);
	}

	link = m_activeSpatialSounds.FirstLink();
	while (link && m_activeSpatialSounds.IsValidLink(link)) {
		SoundBuffer& sound = m_activeSpatialSounds.GetItem(*link);
		link = m_activeSpatialSounds.NextLink(link);

		if (sound.m_priority) {
			break;
		}

		if (sound.m_stopWhenPaused) {
			sound.StopOrRelease();
		}
		else {
			m_availableSoundCount++;
			sound.StopDirectSoundBuffer();
			sound.GetLink().Remove();
			sound.SetPlaybackState(SoundBuffer::c_playbackStateQueued);
			m_queuedSpatialSounds.Prepend(sound);
		}
	}

	if (!m_paused) {
		while (TRUE) {
			SoundBuffer* queuedSound = NULL;
			link = m_queuedSounds.FirstLink();
			if (m_queuedSounds.IsValidLink(link)) {
				queuedSound = &m_queuedSounds.GetItem(*link);
			}

			link = m_queuedSpatialSounds.FirstLink();
			if (m_queuedSpatialSounds.IsValidLink(link)) {
				SoundBuffer& queuedSpatialSound = m_queuedSpatialSounds.GetItem(*link);

				if (!queuedSound || queuedSpatialSound.m_priority > queuedSound->m_priority) {
					if (!queuedSpatialSound.m_priority || !MakeSoundAvailable(queuedSpatialSound.m_priority)) {
						break;
					}

					m_availableSoundCount--;
					queuedSpatialSound.GetLink().Remove();
					InsertByPriority(m_activeSpatialSounds, queuedSpatialSound);
					queuedSpatialSound.SetPlaybackState(SoundBuffer::c_playbackStateActive);
					queuedSpatialSound.StartDirectSoundBuffer();
					continue;
				}
			}
			else if (!queuedSound) {
				break;
			}

			if (!queuedSound || !MakeSoundAvailable(queuedSound->m_priority)) {
				break;
			}

			m_availableSoundCount--;
			queuedSound->GetLink().Remove();
			InsertByPriority(m_activeSounds, *queuedSound);
			queuedSound->SetPlaybackState(SoundBuffer::c_playbackStateActive);
			queuedSound->StartDirectSoundBuffer();
		}
	}

	DestroyPendingStoppedSounds();
}

// FUNCTION: LEGORACERS 0x00418cc0
void DirectSoundManager::Pause()
{
	DirectSoundManager* manager = this;

	if (manager->m_directSound) {
		GolListLink* link;
		LegoBool32& paused = manager->m_paused;

		paused = TRUE;
		link = manager->m_activeSpatialSounds.FirstLink();
		if (manager->m_activeSpatialSounds.IsValidLink(link)) {
			do {
				SoundBuffer& sound = manager->m_activeSpatialSounds.GetItem(*link);
				link = manager->m_activeSpatialSounds.NextLink(link);

				if (sound.ShouldStopWhenPaused()) {
					sound.StopOrRelease();
				}
				else {
					LegoS32 availableSoundCount = manager->m_availableSoundCount;
					availableSoundCount++;
					manager->m_availableSoundCount = availableSoundCount;
					sound.StopDirectSoundBuffer();

					sound.GetLink().Remove();
					sound.SetPlaybackState(SoundBuffer::c_playbackStateQueued);
					manager->m_queuedSpatialSounds.Prepend(sound);
				}
			} while (link);
		}

		manager->Update(0);
	}
}

// FUNCTION: LEGORACERS 0x00418d60
void DirectSoundManager::Resume()
{
	if (m_directSound) {
		m_paused = FALSE;
		Update(0);
	}
}

// FUNCTION: LEGORACERS 0x00418d80
MusicGroup* DirectSoundManager::CreateMusicGroup()
{
	DirectMusicGroup* node = new DirectMusicGroup();

	if (node) {
		node->SetSoundManager(this);
		m_musicGroups.Append(node);
	}

	return node;
}

// FUNCTION: LEGORACERS 0x00418e00
SoundGroup* DirectSoundManager::CreateSoundGroup()
{
	DirectSoundGroup* node = new DirectSoundGroup();

	if (node) {
		node->SetSoundManager(this);
		m_soundGroups.Append(node);
	}

	return node;
}

// FUNCTION: LEGORACERS 0x00418e80
void DirectSoundManager::DestroySoundGroup(SoundGroup* p_node)
{
	p_node->Remove();
	delete static_cast<DirectSoundGroup*>(p_node);
}

// FUNCTION: LEGORACERS 0x00418eb0
SoundNode* DirectSoundManager::CreateSoundNode()
{
	SoundNode* node = new SoundNode();

	if (node) {
		AddNode(node);
	}

	return node;
}

// FUNCTION: LEGORACERS 0x00418f20 FOLDED
void DirectSoundManager::DestroySoundNode(SoundNode* p_node)
{
	RemoveActiveSoundNode(p_node);
	RemoveNode(p_node);
	delete p_node;
}

// FUNCTION: LEGORACERS 0x00418f50
void DirectSoundManager::SetCooperativeWindow(HWND p_hwnd)
{
	if (m_directSound) {
		if (m_currentCooperativeWindow != p_hwnd) {
			if (p_hwnd) {
				DWORD hwndProcessId;
				GetWindowThreadProcessId(p_hwnd, &hwndProcessId);

				if (hwndProcessId == GetCurrentProcessId()) {
					m_currentCooperativeWindow = p_hwnd;
					m_directSound->SetCooperativeLevel(p_hwnd, m_cooperativeLevel);
				}
			}
			else {
				m_currentCooperativeWindow = NULL;
			}
		}
	}
	else {
		m_currentCooperativeWindow = p_hwnd;
		m_cooperativeWindow = p_hwnd;
	}
}

// FUNCTION: LEGORACERS 0x00418fc0
void DirectSoundManager::DestroyPendingStoppedSounds()
{
	GolListLink* link = m_idleSounds.LastLink();
	if (m_idleSounds.IsValidLastLink(link)) {
		do {
			SoundBuffer& sound = m_idleSounds.GetItem(*link);
			link = m_idleSounds.PrevLink(link);

			if (sound.m_stopWhenPaused) {
				DestroySoundBuffer(&sound);
			}
		} while (link);
	}

	link = m_queuedSpatialSounds.LastLink();
	if (m_queuedSpatialSounds.IsValidLastLink(link)) {
		do {
			SoundBuffer& sound = m_queuedSpatialSounds.GetItem(*link);
			link = m_queuedSpatialSounds.PrevLink(link);

			if (sound.m_stopWhenPaused) {
				DestroySoundBuffer(&sound);
			}
		} while (link);
	}
}

// FUNCTION: LEGORACERS 0x00419030
void DirectSoundManager::ReleaseStoppedSounds()
{
	GolListLink* link = m_activeSounds.LastLink();
	if (m_activeSounds.IsValidLastLink(link)) {
		do {
			SoundBuffer& sound = m_activeSounds.GetItem(*link);
			link = m_activeSounds.PrevLink(link);

			if (!sound.IsPlaying()) {
				sound.StopOrRelease();
			}
		} while (link);
	}

	link = m_activeSpatialSounds.LastLink();
	if (m_activeSpatialSounds.IsValidLastLink(link)) {
		do {
			SoundBuffer& sound = m_activeSpatialSounds.GetItem(*link);
			link = m_activeSpatialSounds.PrevLink(link);

			if (!sound.IsPlaying()) {
				sound.StopOrRelease();
			}
		} while (link);
	}
}

// FUNCTION: LEGORACERS 0x004190a0
LegoS32 DirectSoundManager::GetAvailableSoundCount()
{
	if (!m_availableSoundCount) {
		ReleaseStoppedSounds();
	}

	return m_availableSoundCount;
}

// FUNCTION: LEGORACERS 0x004190c0
LegoBool32 DirectSoundManager::CanPlaySound(LegoS32 p_priority)
{
	return MakeSoundAvailable(p_priority + SoundBuffer::c_defaultPriority);
}

// FUNCTION: LEGORACERS 0x004190e0
LegoBool32 DirectSoundManager::MakeSoundAvailable(LegoS32 p_priority)
{
	if (!m_maxActiveSoundCount) {
		return FALSE;
	}

	if (GetAvailableSoundCount()) {
		return TRUE;
	}

	GolListLink* activeSpatialLink = m_activeSpatialSounds.FirstLink();
	activeSpatialLink = activeSpatialLink->m_next ? activeSpatialLink : NULL;

	GolListLink* activeSoundLink = m_activeSounds.FirstLink();
	activeSoundLink = activeSoundLink->m_next ? activeSoundLink : NULL;

	if (activeSoundLink && (!activeSpatialLink || m_activeSounds.GetItem(*activeSoundLink).m_priority <
													  m_activeSpatialSounds.GetItem(*activeSpatialLink).m_priority)) {
		SoundBuffer& activeSound = m_activeSounds.GetItem(*activeSoundLink);

		if (p_priority > activeSound.m_priority) {
			if (activeSound.m_stopWhenPaused) {
				activeSound.StopOrRelease();
				return m_availableSoundCount != 0;
			}

			m_availableSoundCount++;
			activeSound.StopDirectSoundBuffer();
			activeSound.GetLink().Remove();
			activeSound.SetPlaybackState(SoundBuffer::c_playbackStateQueued);
			InsertByPriority(m_queuedSounds, activeSound);
		}
	}
	else if (activeSpatialLink) {
		SoundBuffer& activeSpatialSound = m_activeSpatialSounds.GetItem(*activeSpatialLink);

		if (p_priority > activeSpatialSound.m_priority) {
			if (activeSpatialSound.m_stopWhenPaused) {
				activeSpatialSound.StopOrRelease();
				return m_availableSoundCount != 0;
			}

			m_availableSoundCount++;
			activeSpatialSound.StopDirectSoundBuffer();
			activeSpatialSound.GetLink().Remove();
			activeSpatialSound.SetPlaybackState(SoundBuffer::c_playbackStateQueued);
			InsertByPriority(m_queuedSpatialSounds, activeSpatialSound);
		}
	}

	return m_availableSoundCount != 0;
}

// FUNCTION: LEGORACERS 0x004192b0
SoundBuffer* DirectSoundManager::CreateSoundBuffer()
{
	SoundBuffer* sound = new SoundBuffer();

	if (sound) {
		sound->m_soundManager = this;
		m_idleSounds.Append(*sound);
	}

	return sound;
}

// FUNCTION: LEGORACERS 0x00419330
SoundBuffer* DirectSoundManager::CreateSoundBuffer(SoundData* p_data)
{
	SoundBuffer* sound = CreateSoundBuffer();

	if (!sound || sound->LoadSoundData(p_data)) {
		return sound;
	}

	DestroySoundBuffer(sound);
	return NULL;
}

// FUNCTION: LEGORACERS 0x00419370
SoundBuffer* DirectSoundManager::CreateStreamingSoundBuffer()
{
	SoundBuffer* sound = new SoundBuffer(TRUE);

	if (sound) {
		sound->m_soundManager = this;
		m_idleSounds.Append(*sound);
	}

	return sound;
}

// FUNCTION: LEGORACERS 0x004193f0
SoundBuffer* DirectSoundManager::CreateStreamingSoundBuffer(SoundData* p_data)
{
	SoundBuffer* sound = CreateStreamingSoundBuffer();

	if (!sound || sound->LoadSoundData(p_data)) {
		return sound;
	}

	DestroySoundBuffer(sound);
	return NULL;
}

// FUNCTION: LEGORACERS 0x00419430
void DirectSoundManager::DestroySoundBuffer(SoundBuffer* p_sound)
{
	p_sound->ReleaseDirectSoundBuffer();
	p_sound->m_soundManager = NULL;
	p_sound->GetLink().Remove();
	delete p_sound;
}

// FUNCTION: LEGORACERS 0x00419470
void DirectSoundManager::MoveSoundToIdle(SoundBuffer& p_sound)
{
	if (p_sound.GetPlaybackState() == SoundBuffer::c_playbackStateActive) {
		m_availableSoundCount++;
	}

	SoundBufferList* idleSounds = &m_idleSounds;
	p_sound.MoveToList(*idleSounds, SoundBuffer::c_playbackStateIdle);
}

// FUNCTION: LEGORACERS 0x004194b0
LegoBool32 DirectSoundManager::QueueSound(SoundBuffer& p_sound)
{
	if (p_sound.m_playbackState == SoundBuffer::c_playbackStateActive) {
		return TRUE;
	}

	if (!p_sound.m_streaming) {
		if (MakeSoundAvailable(p_sound.m_priority)) {
			p_sound.GetLink().Remove();
			p_sound.SetPlaybackState(SoundBuffer::c_playbackStateActive);
			InsertByPriority(m_activeSounds, p_sound);
			m_availableSoundCount--;
		}
		else {
			p_sound.GetLink().Remove();
			p_sound.SetPlaybackState(SoundBuffer::c_playbackStateQueued);
			InsertByPriority(m_queuedSounds, p_sound);
		}

		return p_sound.m_playbackState == SoundBuffer::c_playbackStateActive;
	}

	if (p_sound.m_playbackState == SoundBuffer::c_playbackStateIdle) {
		p_sound.GetLink().Remove();
		p_sound.SetPlaybackState(SoundBuffer::c_playbackStateQueued);
		InsertByPriority(m_queuedSpatialSounds, p_sound);
	}

	return p_sound.m_playbackState == SoundBuffer::c_playbackStateActive;
}

// FUNCTION: LEGORACERS 0x0041be50 FOLDED
void DirectSoundManager::DestroyMusicGroup(MusicGroup* p_node)
{
	p_node->Remove();
	delete p_node;
}
