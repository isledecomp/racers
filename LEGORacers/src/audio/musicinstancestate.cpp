#include "audio/musicinstancestate.h"

#include "audio/musicgroup.h"
#include "audio/soundmanager.h"

DECOMP_SIZE_ASSERT(MusicInstanceState, 0x18)

// GLOBAL: LEGORACERS 0x004afb9c
LegoFloat g_minMusicVolume = 0.0f;

// GLOBAL: LEGORACERS 0x004afba0
LegoFloat g_defaultMusicVolume = 1.0f;

// FUNCTION: LEGORACERS 0x0041a570
MusicInstanceState::MusicInstanceState()
{
	m_musicGroup = NULL;
	m_playing = FALSE;
	m_paused = FALSE;
	m_wasPaused = FALSE;
	m_playFlag = FALSE;
	m_volume = g_defaultMusicVolume;
}

// FUNCTION: LEGORACERS 0x0041a5c0
MusicInstanceState::~MusicInstanceState()
{
	if (m_musicGroup) {
		Remove();
	}
}

// FUNCTION: LEGORACERS 0x0041a5f0
void MusicInstanceState::SetVolume(LegoFloat p_volume)
{
	if (p_volume < g_minMusicVolume) {
		m_volume = g_minMusicVolume;
	}
	else {
		if (!(p_volume <= g_defaultMusicVolume)) {
			m_volume = g_defaultMusicVolume;
		}
		else {
			m_volume = p_volume;
		}
	}

	m_volume = m_musicGroup->GetSoundManager()->GetMusicVolumeScale() * m_volume;
}
