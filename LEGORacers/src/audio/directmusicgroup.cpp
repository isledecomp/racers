#include "audio/directmusicgroup.h"

#include "audio/audiohelpers.h"
#include "audio/directmusicinstance.h"
#include "audio/musicinstance.h"
#include "golfile.h"
#include "golstream.h"

#include <stdlib.h>
#include <string.h>

DECOMP_SIZE_ASSERT(DirectMusicGroup, 0x128)

// GLOBAL: LEGORACERS 0x004be7e4
LegoChar g_musicPcmExtension[] = ".pcm";

// GLOBAL: LEGORACERS 0x004be7ec
LegoChar g_musicTunExtension[] = ".tun";

// FUNCTION: LEGORACERS 0x0041a650
DirectMusicGroup::DirectMusicGroup()
{
	m_basePath[0] = '\0';
	m_soundManager = NULL;
	m_musicNames = NULL;
}

// FUNCTION: LEGORACERS 0x0041a6b0
DirectMusicGroup::~DirectMusicGroup()
{
	Unload();
}

// FUNCTION: LEGORACERS 0x0041a700
void DirectMusicGroup::Load(const LegoChar* p_name)
{
	LegoBool32 failed = FALSE;
	GolFile file;
	LegoChar countString[c_musicCountLength];

	Unload();

	if (!file.BufferedOpen(p_name, GolStream::c_modeRead | GolStream::c_modeTextAppend, c_fileBufferSize)) {
		if (file.ReadLine(m_basePath, c_musicPathLength)) {
			failed = TRUE;
		}

		if (file.ReadLine(countString, sizeof(countString))) {
			failed = TRUE;
		}

		m_musicCount = atoi(countString);
		if (m_musicCount > 0) {
			m_musicNames = new LegoChar[c_musicPathLength * m_musicCount];

			for (LegoU32 i = 0; i < m_musicCount; i++) {
				LegoU32 offset = c_musicPathLength * i;
				m_musicNames[offset] = '\0';

				if (file.ReadLine(&m_musicNames[offset], c_musicPathLength)) {
					failed = TRUE;
				}

				LowercaseString(&m_musicNames[offset]);
			}
		}
		else {
			m_musicCount = 0;
			failed = TRUE;
		}

		file.Dispose();

		if (failed) {
			Unload();
		}
	}
}

// FUNCTION: LEGORACERS 0x0041a850
void DirectMusicGroup::Unload()
{
	if (m_musicNames) {
		delete[] m_musicNames;
		m_musicNames = NULL;
	}

	while (TRUE) {
		GolListLink* link = m_musicInstances.LastLink();

		if (!m_musicInstances.IsValidLastLink(link)) {
			break;
		}

		DestroyMusicInstance(&m_musicInstances.GetItem(*link));
	}

	m_musicCount = 0;
	m_basePath[0] = '\0';
}

// FUNCTION: LEGORACERS 0x0041a890
LegoBool32 DirectMusicGroup::IsLoaded()
{
	return m_musicCount != 0;
}

// FUNCTION: LEGORACERS 0x0041a8a0
MusicInstance* DirectMusicGroup::CreateMusicInstance(LegoU32 p_index)
{
	if (p_index >= m_musicCount) {
		return NULL;
	}

	LegoChar source[c_musicPathLength];
	LegoChar* musicNames = m_musicNames;
	LegoU32 offset = c_musicPathLength * p_index;
	JoinAudioPath(source, c_musicPathLength, m_basePath, &musicNames[offset]);

	if (strstr(&m_musicNames[offset], g_musicTunExtension) || strstr(&m_musicNames[offset], g_musicPcmExtension)) {
		DirectMusicInstance* instance = new DirectMusicInstance();

		if (instance) {
			instance->SetMusicGroup(this);

			if (instance->Initialize()) {
				instance->SetPath(source);
				m_musicInstances.Append(instance);
			}
			else {
				instance->SetMusicGroup(NULL);
				delete instance;
				instance = NULL;
			}
		}

		return instance;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x0041a9d0 FOLDED
void DirectMusicGroup::DestroyMusicInstance(MusicInstance* p_node)
{
	delete p_node;
}

// FUNCTION: LEGORACERS 0x0041a9f0 FOLDED
SoundManager* DirectMusicGroup::GetSoundManager()
{
	return m_soundManager;
}
