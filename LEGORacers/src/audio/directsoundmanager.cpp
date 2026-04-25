#include "audio/directsoundmanager.h"

#include "audio/crimsonray0x20.h"
#include "audio/emberdust0x28.h"
#include "audio/frostpetal0x34.h"
#include "audio/goldenoak0x128.h"
#include "audio/soundbuffer.h"
#include "audio/soundnode.h"
#include "types.h"

DECOMP_SIZE_ASSERT(DirectSoundManager, 0x98)

// FUNCTION: LEGORACERS 0x004185d0
DirectSoundManager::DirectSoundManager()
{
	m_cooperativeLevel = DSSCL_PRIORITY;
	m_nChannels = c_defaultChannelCount;
	m_unk0x20 = NULL;
	m_unk0x1c = NULL;
	m_directSound = NULL;
	m_unk0x2c = NULL;
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

	if (!m_unk0x20) {
		HWND pHVar4 = GetForegroundWindow();
		DWORD hwndProcessId;
		GetWindowThreadProcessId(pHVar4, &hwndProcessId);

		if (hwndProcessId == GetCurrentProcessId()) {
			SetCooperativeWindow(pHVar4);
		}

		if (!m_unk0x20) {
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

	if (DirectSoundCreate(m_unk0x2c, &m_directSound, NULL)) {
		m_directSound = NULL;
		return FALSE;
	}

	if (m_directSound->SetCooperativeLevel(m_unk0x20, m_cooperativeLevel)) {
		Shutdown();
		return FALSE;
	}

	HWND activeWindow = GetActiveWindow();
	if (m_unk0x20 != activeWindow) {
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
		GolListLink* link = m_unk0x3c.LastLink();

		if (!m_unk0x3c.IsValidLastLink(link)) {
			break;
		}

		VTable0x18(&m_unk0x3c.GetItem(*link));
	}

	while (TRUE) {
		GolListLink* link = m_unk0x48.LastLink();

		if (!m_unk0x48.IsValidLastLink(link)) {
			break;
		}

		VTable0x20(&m_unk0x48.GetItem(*link));
	}

	while (m_unk0x0c) {
		VTable0x28(m_unk0x0c);
	}

	while (m_unk0x08) {
		VTable0x28(m_unk0x08);
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
void DirectSoundManager::VTable0x34(undefined4)
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

		manager->VTable0x34(0);
	}
}

// FUNCTION: LEGORACERS 0x00418d60
void DirectSoundManager::Resume()
{
	if (m_directSound) {
		m_paused = FALSE;
		VTable0x34(0);
	}
}

// FUNCTION: LEGORACERS 0x00418d80
CrimsonRay0x20* DirectSoundManager::VTable0x14()
{
	GoldenOak0x128* node = new GoldenOak0x128();

	if (node) {
		node->SetUnk0x10(this);
		m_unk0x3c.Append(node);
	}

	// TODO: GoldenOak0x128 does not inherit from CrimsonRay0x20
	return (CrimsonRay0x20*) node;
}

// FUNCTION: LEGORACERS 0x00418e00
EmberDust0x28* DirectSoundManager::VTable0x1c()
{
	FrostPetal0x34* node = new FrostPetal0x34();

	if (node) {
		node->SetSoundManager(this);
		m_unk0x48.Append(node);
	}

	// TODO: FrostPetal0x34 does not inherit from EmberDust0x28
	return (EmberDust0x28*) node;
}

// FUNCTION: LEGORACERS 0x00418e80
void DirectSoundManager::VTable0x20(EmberDust0x28* p_node)
{
	p_node->Remove();
	delete (FrostPetal0x34*) p_node;
}

// FUNCTION: LEGORACERS 0x00418eb0
SoundNode* DirectSoundManager::VTable0x24()
{
	SoundNode* node = new SoundNode();

	if (node) {
		AddNode(node);
	}

	return node;
}

// FUNCTION: LEGORACERS 0x00418f20 FOLDED
void DirectSoundManager::VTable0x28(SoundNode* p_node)
{
	VTable0x30(p_node);
	RemoveNode(p_node);
	delete p_node;
}

// FUNCTION: LEGORACERS 0x00418f50
void DirectSoundManager::SetCooperativeWindow(HWND p_hwnd)
{
	if (m_directSound) {
		if (m_unk0x1c != p_hwnd) {
			if (p_hwnd) {
				DWORD hwndProcessId;
				GetWindowThreadProcessId(p_hwnd, &hwndProcessId);

				if (hwndProcessId == GetCurrentProcessId()) {
					m_unk0x1c = p_hwnd;
					m_directSound->SetCooperativeLevel(p_hwnd, m_cooperativeLevel);
				}
			}
			else {
				m_unk0x1c = NULL;
			}
		}
	}
	else {
		m_unk0x1c = p_hwnd;
		m_unk0x20 = p_hwnd;
	}
}

// FUNCTION: LEGORACERS 0x00419470
void DirectSoundManager::MoveSoundToIdle(SoundBuffer& p_sound)
{
	if (p_sound.GetPlaybackState() == SoundBuffer::c_playbackStateActive) {
		m_availableSoundCount++;
	}

	SoundBufferList* idleSounds = &m_unk0x5c;
	p_sound.MoveToList(*idleSounds, SoundBuffer::c_playbackStateIdle);
}

// FUNCTION: LEGORACERS 0x0041be50 FOLDED
void DirectSoundManager::VTable0x18(CrimsonRay0x20* p_node)
{
	p_node->Remove();
	delete p_node;
}
