#include "audio/directmusicstream.h"

#include "audio/directmusicgroup.h"
#include "audio/directsoundconversions.h"
#include "audio/directsoundmanager.h"

#include <mmsystem.h>

DECOMP_SIZE_ASSERT(DirectMusicStream, 0x44)

// GLOBAL: LEGORACERS 0x004c47f0
static GolList<DirectMusicStream, DirectMusicStreamListTraits> g_directMusicStreams;

// GLOBAL: LEGORACERS 0x004c47fc
static UINT g_directMusicTimerId;

// GLOBAL: LEGORACERS 0x004c4800
static HANDLE g_directMusicMutex;

// Modern Windows SDKs use DWORD_PTR for multimedia timer callback payloads.
#ifdef COMPAT_MODE
typedef DWORD_PTR DirectMusicTimerCallbackData;
#else
typedef DWORD DirectMusicTimerCallbackData;
#endif

// FUNCTION: LEGORACERS 0x0041a110
static void CALLBACK DirectMusicTimerCallback(
	UINT,
	UINT,
	DirectMusicTimerCallbackData,
	DirectMusicTimerCallbackData,
	DirectMusicTimerCallbackData
)
{
	if (!WaitForSingleObject(g_directMusicMutex, 0)) {
		GolListLink* link = g_directMusicStreams.LastLink();
		if (g_directMusicStreams.IsValidLastLink(link)) {
			do {
				DirectMusicStream& stream = g_directMusicStreams.GetItem(*link);

				HANDLE mutex = stream.GetMutex();
				if (mutex && !WaitForSingleObject(mutex, 0)) {
					stream.Service();
					ReleaseMutex(stream.GetMutex());
				}

				link = link->m_prev;
			} while (g_directMusicStreams.IsValidLastLink(link));
		}

		ReleaseMutex(g_directMusicMutex);
	}
}

// FUNCTION: LEGORACERS 0x0041a180
DirectMusicStream::DirectMusicStream()
{
	m_channelCount = c_defaultChannelCount;
	m_sampleRate = c_defaultSampleRate;
	m_averageBytesPerSecond = c_defaultAverageBytesPerSecond;
	m_bufferSeconds = c_defaultBufferSeconds;
	m_mutex = NULL;
	m_directSoundBuffer = NULL;

	if (!g_directMusicMutex) {
		g_directMusicMutex = CreateMutex(NULL, FALSE, NULL);
	}

	WaitForSingleObject(g_directMusicMutex, INFINITE);
	g_directMusicStreams.Append(*this);
	ReleaseMutex(g_directMusicMutex);
}

// FUNCTION: LEGORACERS 0x0041a230
DirectMusicStream::~DirectMusicStream()
{
	if (g_directMusicMutex) {
		WaitForSingleObject(g_directMusicMutex, INFINITE);
		m_updateLink.Remove();

		if (g_directMusicStreams.IsEmpty()) {
			if (g_directMusicTimerId) {
				timeKillEvent(g_directMusicTimerId);
				g_directMusicTimerId = 0;
			}

			ReleaseMutex(g_directMusicMutex);
			CloseHandle(g_directMusicMutex);
			g_directMusicMutex = NULL;
		}
		else {
			ReleaseMutex(g_directMusicMutex);
		}
	}
	else {
		m_updateLink.Remove();
	}

	ReleaseResources();
}

// FUNCTION: LEGORACERS 0x0041a310
void DirectMusicStream::ReleaseResources()
{
	if (g_directMusicMutex) {
		WaitForSingleObject(g_directMusicMutex, INFINITE);
	}

	if (m_directSoundBuffer) {
		m_directSoundBuffer->Release();
		m_directSoundBuffer = NULL;
	}

	if (m_mutex) {
		CloseHandle(m_mutex);
		m_mutex = NULL;
	}

	if (g_directMusicMutex) {
		ReleaseMutex(g_directMusicMutex);
	}
}

// FUNCTION: LEGORACERS 0x0041a360
LegoBool32 DirectMusicStream::Initialize()
{
	LPDIRECTSOUND directSound = GetDirectSound();
	if (!directSound) {
		return FALSE;
	}

	WaitForSingleObject(g_directMusicMutex, INFINITE);

	if (!g_directMusicTimerId) {
		g_directMusicTimerId = timeSetEvent(
			c_streamTimerDelay,
			c_streamTimerDelay,
			DirectMusicTimerCallback,
			(DirectMusicTimerCallbackData) this,
			TIME_PERIODIC
		);

		if (!g_directMusicTimerId) {
			ReleaseMutex(g_directMusicMutex);
			return FALSE;
		}
	}

	if (m_directSoundBuffer) {
		DirectMusicStream::ReleaseResources();
	}

	WAVEFORMATEX waveFormat;
	waveFormat.nChannels = (WORD) m_channelCount;
	waveFormat.nSamplesPerSec = m_sampleRate;
	waveFormat.wBitsPerSample = c_defaultBitsPerSample;
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.cbSize = 0;
	waveFormat.nBlockAlign = c_defaultBytesPerSample * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = m_sampleRate * waveFormat.nBlockAlign;

	m_bufferSize =
		(waveFormat.nAvgBytesPerSec * m_bufferSeconds + c_streamBufferAlignment - 1) & ~(c_streamBufferAlignment - 1);
	m_serviceBlocks = c_streamTimerDelay * waveFormat.nAvgBytesPerSec / c_serviceByteScale + c_serviceBlockPadding;

	DSBUFFERDESC bufferDesc;
	bufferDesc.dwSize = sizeof(bufferDesc);
	bufferDesc.dwFlags = c_directSoundBufferFlags;
	bufferDesc.dwBufferBytes = m_bufferSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;

	m_mutex = CreateMutex(NULL, TRUE, NULL);
	if (m_mutex) {
		if (directSound->CreateSoundBuffer(&bufferDesc, &m_directSoundBuffer, NULL)) {
			m_directSoundBuffer = NULL;
		}

		ReleaseMutex(m_mutex);
	}

	ReleaseMutex(g_directMusicMutex);

	if (m_directSoundBuffer) {
		SetVolume(m_volume);
		return TRUE;
	}

	DirectMusicStream::ReleaseResources();
	return FALSE;
}

// FUNCTION: LEGORACERS 0x0041a4f0
void DirectMusicStream::Service()
{
	if (m_directSoundBuffer) {
		if (m_playing) {
			FillBuffer(m_serviceBlocks);
		}
	}
}

// FUNCTION: LEGORACERS 0x0041a510
LPDIRECTSOUND DirectMusicStream::GetDirectSound()
{
	return static_cast<DirectSoundManager*>(static_cast<DirectMusicGroup*>(m_musicGroup)->GetSoundManagerDirect())
		->GetDirectSound();
}

// FUNCTION: LEGORACERS 0x0041a520
void DirectMusicStream::SetVolume(LegoFloat p_volume)
{
	MusicInstanceState::SetVolume(p_volume);

	if (m_directSoundBuffer) {
		WaitForSingleObject(m_mutex, INFINITE);
		m_directSoundBuffer->SetVolume(ConvertVolumeToDirectSound(m_volume));
		ReleaseMutex(m_mutex);
	}
}
