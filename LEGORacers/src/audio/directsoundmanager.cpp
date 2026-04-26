#include "audio/directsoundmanager.h"

#include "audio/directmusicgroup.h"
#include "audio/directsoundgroup.h"
#include "audio/nullsoundgroup.h"
#include "audio/soundbuffer.h"
#include "audio/soundnode.h"
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
		HWND pHVar4 = GetForegroundWindow();
		DWORD hwndProcessId;
		GetWindowThreadProcessId(pHVar4, &hwndProcessId);

		if (hwndProcessId == GetCurrentProcessId()) {
			SetCooperativeWindow(pHVar4);
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

// STUB: LEGORACERS 0x00418940
void DirectSoundManager::Update(undefined4)
{
	STUB(0x418940);
}

// FUNCTION: LEGORACERS 0x00418cc0
void DirectSoundManager::Pause()
{
	DirectSoundManager* manager = this;

	if (manager->m_directSound) {
		GolListLink* link;
		LegoBool32& paused = manager->m_paused;

		paused = TRUE;
		link = manager->m_activeSounds.FirstLink();
		if (manager->m_activeSounds.IsValidLink(link)) {
			do {
				SoundBuffer& sound = manager->m_activeSounds.GetItem(*link);
				link = manager->m_activeSounds.NextLink(link);

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
					manager->m_pausedSounds.Prepend(sound);
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

// FUNCTION: LEGORACERS 0x00419470
void DirectSoundManager::MoveSoundToIdle(SoundBuffer& p_sound)
{
	if (p_sound.GetPlaybackState() == SoundBuffer::c_playbackStateActive) {
		m_availableSoundCount++;
	}

	SoundBufferList* idleSounds = &m_idleSounds;
	p_sound.MoveToList(*idleSounds, SoundBuffer::c_playbackStateIdle);
}

// FUNCTION: LEGORACERS 0x0041be50 FOLDED
void DirectSoundManager::DestroyMusicGroup(MusicGroup* p_node)
{
	p_node->Remove();
	delete p_node;
}
