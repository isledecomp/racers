#include "audio/directmusicinstance.h"

#include "audio/audiohelpers.h"
#include "audio/directmusicgroup.h"
#include "audio/directsoundconversions.h"
#include "audio/directsoundmanager.h"

#include <mmsystem.h>
#include <string.h>

DECOMP_SIZE_ASSERT(DirectMusicStream, 0x44)
DECOMP_SIZE_ASSERT(DirectMusicInstance, 0x417c)
DECOMP_SIZE_ASSERT(DirectMusicInstance::AdpcmHeader, 0x10)

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

// FUNCTION: LEGORACERS 0x00419700
DirectMusicInstance::DirectMusicInstance()
{
	m_file = (HANDLE) c_invalidFileHandle;
	m_streamError = FALSE;
}

// FUNCTION: LEGORACERS 0x00419740
DirectMusicInstance::~DirectMusicInstance()
{
	ReleaseResources();
}

// FUNCTION: LEGORACERS 0x00419790
void DirectMusicInstance::ReleaseResources()
{
	CloseFile();
}

// FUNCTION: LEGORACERS 0x004197a0
LegoS32 DirectMusicInstance::FillBuffer(LegoS32 p_blocks)
{
	DWORD playCursor;
	DWORD writeCursor;
	LegoS32 bytesAvailable = 0;

	if (!m_directSoundBuffer || m_file == (HANDLE) c_invalidFileHandle ||
		m_directSoundBuffer->GetCurrentPosition(&playCursor, &writeCursor)) {
		return bytesAvailable;
	}

	LegoS32 writeBytes = playCursor - m_writeCursor;
	if (writeBytes > 0) {
		if (writeBytes > 4) {
			writeBytes -= 4;
		}
	}
	else {
		writeBytes = writeBytes + m_bufferSize - 4;
	}

	if (!m_remainingBytes && !m_loopCount) {
		LegoS32 alignment = m_bufferSize >> 2;
		alignment = alignment & ~3;
		LegoS32 silenceBytes = m_silenceBytes + alignment - m_bufferSize;

		if (silenceBytes > 0) {
			if (writeBytes > silenceBytes) {
				writeBytes = silenceBytes;
			}

			LPVOID audioPtr1;
			LPVOID audioPtr2;
			DWORD audioBytes1;
			DWORD audioBytes2;

			if (!m_directSoundBuffer
					 ->Lock(m_writeCursor, writeBytes, &audioPtr1, &audioBytes1, &audioPtr2, &audioBytes2, 0)) {
				if (audioBytes1 & 3) {
					m_silenceBytes = 0;
				}
				else {
					memset(audioPtr1, 0, 4 * (audioBytes1 >> 2));
					if (audioPtr2) {
						memset(audioPtr2, 0, 4 * (audioBytes2 >> 2));
					}
				}

				m_directSoundBuffer->Unlock(audioPtr1, audioBytes1, audioPtr2, audioBytes2);
			}
		}

		m_writeCursor += writeBytes;
		if (m_writeCursor >= m_bufferSize) {
			m_writeCursor -= m_bufferSize;
		}

		m_silenceBytes -= writeBytes;
		return 0;
	}

	writeBytes &= ~(c_streamBufferAlignment - 1);
	if (!writeBytes) {
		return 0;
	}

	LegoS32 maxWriteBytes = p_blocks << 12;
	if (writeBytes > maxWriteBytes) {
		writeBytes = maxWriteBytes;
	}

	bytesAvailable = writeBytes;
	if (m_channelCount == 2) {
		if (m_sourceChannelCount == 2) {
			while (writeBytes) {
				LegoS32 readBytes = writeBytes >> 2;
				if (readBytes > c_readChunkSize) {
					readBytes = c_readChunkSize;
				}
				if (readBytes > m_remainingBytes) {
					readBytes = m_remainingBytes;
				}

				DWORD numberOfBytesRead;
				if (!ReadFile(m_file, m_streamBuffer, readBytes, &numberOfBytesRead, NULL)) {
					m_streamError = TRUE;
					break;
				}

				LPVOID audioPtr1;
				LPVOID audioPtr2;
				DWORD audioBytes1;
				DWORD audioBytes2;
				HRESULT result =
					m_directSoundBuffer
						->Lock(m_writeCursor, 4 * readBytes, &audioPtr1, &audioBytes1, &audioPtr2, &audioBytes2, 0);

				if (result) {
					if (result == c_lostBuffer) {
						m_directSoundBuffer->Restore();
						writeBytes = 0;
					}
				}
				else {
					DecodeStereoPcmToStereo(
						m_streamBuffer,
						(LegoS16*) audioPtr1,
						audioBytes1 >> 2,
						m_leftState,
						m_rightState
					);

					LPVOID unlockPtr2 = audioPtr2;
					if (audioPtr2) {
						DecodeStereoPcmToStereo(
							m_streamBuffer + (audioBytes1 >> 2),
							(LegoS16*) audioPtr2,
							audioBytes2 >> 2,
							m_leftState,
							m_rightState
						);
						m_writeCursor = audioBytes2;
					}
					else {
						m_writeCursor += audioBytes1;
						if (m_writeCursor >= m_bufferSize) {
							m_writeCursor -= m_bufferSize;
						}
					}

					m_directSoundBuffer->Unlock(audioPtr1, audioBytes1, unlockPtr2, audioBytes2);
				}

				m_remainingBytes -= readBytes;
				if (!m_remainingBytes) {
					break;
				}

				writeBytes -= 4 * readBytes;
			}
		}
		else {
			while (writeBytes) {
				LegoS32 readBytes = writeBytes >> 3;
				if (readBytes > c_readChunkSize) {
					readBytes = c_readChunkSize;
				}
				if (readBytes > m_remainingBytes) {
					readBytes = m_remainingBytes;
				}

				DWORD numberOfBytesRead;
				if (!ReadFile(m_file, m_streamBuffer, readBytes, &numberOfBytesRead, NULL)) {
					m_streamError = TRUE;
					break;
				}

				LPVOID audioPtr1;
				LPVOID audioPtr2;
				DWORD audioBytes1;
				DWORD audioBytes2;
				HRESULT result =
					m_directSoundBuffer
						->Lock(m_writeCursor, 8 * readBytes, &audioPtr1, &audioBytes1, &audioPtr2, &audioBytes2, 0);

				if (result) {
					if (result == c_lostBuffer) {
						m_directSoundBuffer->Restore();
						writeBytes = 0;
					}
				}
				else {
					DecodeMonoPcmToStereo(m_streamBuffer, (LegoS16*) audioPtr1, audioBytes1 >> 3, m_leftState);

					LPVOID unlockPtr2 = audioPtr2;
					if (audioPtr2) {
						DecodeMonoPcmToStereo(
							m_streamBuffer + (audioBytes1 >> 3),
							(LegoS16*) audioPtr2,
							audioBytes2 >> 3,
							m_leftState
						);
						m_writeCursor = audioBytes2;
					}
					else {
						m_writeCursor += audioBytes1;
						if (m_writeCursor >= m_bufferSize) {
							m_writeCursor -= m_bufferSize;
						}
					}

					m_directSoundBuffer->Unlock(audioPtr1, audioBytes1, unlockPtr2, audioBytes2);
				}

				m_remainingBytes -= readBytes;
				if (!m_remainingBytes) {
					break;
				}

				writeBytes -= 8 * readBytes;
			}
		}
	}

	if (!m_remainingBytes) {
		if (!m_loopCount) {
			m_silenceBytes = m_bufferSize;
			return bytesAvailable;
		}

		if (m_loopCount > 0) {
			m_loopCount--;
		}

		SetFilePointer(m_file, m_dataStart, NULL, FILE_BEGIN);
		m_leftState[0] = 0;
		m_leftState[1] = 0;
		m_rightState[0] = 0;
		m_rightState[1] = 0;
		m_remainingBytes = m_fileSize - m_dataStart;
	}

	return bytesAvailable;
}

// FUNCTION: LEGORACERS 0x00419c50
void DirectMusicInstance::Service()
{
	if (m_directSoundBuffer) {
		if (m_restartRequested) {
			m_restartRequested = FALSE;
		}

		if (m_playing) {
			FillBuffer(m_serviceBlocks);
			if (!m_remainingBytes && !m_loopCount && (LegoS32) m_silenceBytes <= 0) {
				CloseFile();
				m_streamError = FALSE;
			}
		}

		if (m_streamError) {
			CloseFile();
			m_streamError = FALSE;
			m_restartRequested = TRUE;
		}
	}
}

// FUNCTION: LEGORACERS 0x00419cd0
void DirectMusicInstance::StopBuffer()
{
	if (m_directSoundBuffer) {
		WaitForSingleObject(m_mutex, INFINITE);
		m_directSoundBuffer->Stop();
		m_paused = FALSE;
		m_playing = FALSE;
		m_wasPaused = m_playFlag;
		ReleaseMutex(m_mutex);
	}
}

// FUNCTION: LEGORACERS 0x00419d10
void DirectMusicInstance::CloseFile()
{
	if (m_directSoundBuffer) {
		WaitForSingleObject(m_mutex, INFINITE);
		StopBuffer();

		if (m_file != (HANDLE) c_invalidFileHandle) {
			CloseHandle(m_file);
			m_file = (HANDLE) c_invalidFileHandle;
		}

		m_directSoundBuffer->SetCurrentPosition(0);
		ReleaseMutex(m_mutex);
	}
}

// FUNCTION: LEGORACERS 0x00419d60
LegoBool32 DirectMusicInstance::OpenFileAndPlay(LegoBool p_play)
{
	CloseFile();

	m_leftState[1] = 0;
	m_leftState[0] = 0;
	m_rightState[1] = 0;
	m_rightState[0] = 0;

	m_file = CreateFile(
		m_path,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
		NULL
	);

	if (m_file != (HANDLE) c_invalidFileHandle) {
		m_streamError = FALSE;
		m_dataStart = 0;
		m_sourceChannelCount = 1;
		m_fileSize = GetFileSize(m_file, NULL);

		if (m_fileSize >= c_adpcmHeaderSize) {
			ReadFile(m_file, &m_adpcmHeader, c_adpcmHeaderSize, (DWORD*) &m_remainingBytes, NULL);

			if (m_adpcmHeader.m_magic == c_adpcmMagic && m_adpcmHeader.m_format == c_adpcmFormat) {
				LegoU32 dataStart = m_adpcmHeader.m_dataOffset;
				m_sourceChannelCount = m_adpcmHeader.m_channelCount;
				m_dataStart = dataStart + 8;
			}

			SetFilePointer(m_file, m_dataStart, NULL, FILE_BEGIN);
		}

		m_remainingBytes = m_fileSize - m_dataStart;
		m_silenceBytes = m_bufferSize;
		m_writeCursor = 0;
		FillBuffer(m_silenceBytes / c_prefillBlockSize);

		if (m_streamError) {
			CloseFile();
			m_streamError = FALSE;
		}
		else {
			m_directSoundBuffer->SetCurrentPosition(0);
			m_playing = p_play;
			if (p_play) {
				if (!m_wasPaused) {
					m_directSoundBuffer->Play(0, 0, DSBPLAY_LOOPING);
				}
			}

			return TRUE;
		}
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00419eb0
void DirectMusicInstance::PauseDirectSoundBuffer()
{
	if (m_directSoundBuffer) {
		WaitForSingleObject(m_mutex, INFINITE);
		m_directSoundBuffer->Stop();
		ReleaseMutex(m_mutex);
	}
}

// FUNCTION: LEGORACERS 0x00419ee0
void DirectMusicInstance::ResumeDirectSoundBuffer()
{
	if (m_directSoundBuffer) {
		WaitForSingleObject(m_mutex, INFINITE);
		m_directSoundBuffer->Play(0, 0, DSBPLAY_LOOPING);
		ReleaseMutex(m_mutex);
	}
}

// FUNCTION: LEGORACERS 0x00419f20
LegoBool32 DirectMusicInstance::Play(LegoBool32 p_loop)
{
	if (!m_directSoundBuffer) {
		return FALSE;
	}

	WaitForSingleObject(m_mutex, INFINITE);
	if (p_loop) {
		m_loopCount = -1;
	}
	else {
		m_loopCount = 0;
	}

	if (m_playing) {
		if (m_paused) {
			Resume();
		}
	}
	else {
		OpenFileAndPlay(TRUE);
	}

	LegoBool32 result = m_playing;
	ReleaseMutex(m_mutex);
	return result;
}

// FUNCTION: LEGORACERS 0x00419fa0
void DirectMusicInstance::Stop()
{
	if (m_directSoundBuffer) {
		WaitForSingleObject(m_mutex, INFINITE);
		if (m_playing) {
			StopBuffer();
		}
		ReleaseMutex(m_mutex);
	}
}

// FUNCTION: LEGORACERS 0x00419fd0
void DirectMusicInstance::Pause()
{
	if (m_directSoundBuffer) {
		WaitForSingleObject(m_mutex, INFINITE);
		LegoBool wasPaused = m_wasPaused;
		m_paused = TRUE;
		if (!wasPaused) {
			m_wasPaused = TRUE;
			if (m_playing) {
				PauseDirectSoundBuffer();
			}
		}
		ReleaseMutex(m_mutex);
	}
}

// FUNCTION: LEGORACERS 0x0041a010
void DirectMusicInstance::Resume()
{
	if (m_directSoundBuffer) {
		WaitForSingleObject(m_mutex, INFINITE);
		LegoBool wasPaused = m_playFlag;
		m_paused = FALSE;
		m_wasPaused = wasPaused;
		if (!wasPaused) {
			if (m_playing) {
				ResumeDirectSoundBuffer();
			}
		}
		ReleaseMutex(m_mutex);
	}
}

// FUNCTION: LEGORACERS 0x0041a050
LegoBool32 DirectMusicInstance::IsPlaying()
{
	if (m_wasPaused) {
		return FALSE;
	}

	return m_playing;
}

// FUNCTION: LEGORACERS 0x0041a060
LegoBool32 DirectMusicInstance::SetPath(const LegoChar* p_path)
{
	if (!m_directSoundBuffer) {
		return FALSE;
	}

	WaitForSingleObject(m_mutex, INFINITE);
	m_streamError = FALSE;
	m_restartRequested = FALSE;
	strncpy(m_path, p_path, c_pathLength);
	m_path[c_pathLength - 1] = '\0';
	DWORD attributes = GetFileAttributes(m_path);
	ReleaseMutex(m_mutex);
	attributes = ~attributes;
	return ((attributes & 0xff) >> 4) & 1;
}

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

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void DirectMusicInstance::VTable0x1c(undefined4)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void DirectMusicInstance::VTable0x20(undefined4)
{
}
