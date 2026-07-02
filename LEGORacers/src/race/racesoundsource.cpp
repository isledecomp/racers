#include "audio/soundgroup.h"
#include "audio/soundmanager.h"
#include "race/racesession.h"

DECOMP_SIZE_ASSERT(RaceSession::RaceSoundSource, 0x14)

// FUNCTION: LEGORACERS 0x00443a50
RaceSession::RaceSoundSource::RaceSoundSource()
{
	m_groups[0] = NULL;
	m_groups[1] = NULL;
	m_groups[2] = NULL;
	m_groups[3] = NULL;
	m_soundManager = NULL;
}

// FUNCTION: LEGORACERS 0x00443a70
RaceSession::RaceSoundSource::~RaceSoundSource()
{
	DestroyGroups();
}

// FUNCTION: LEGORACERS 0x00443a80
void RaceSession::RaceSoundSource::DestroyGroups()
{
	SoundGroup** current = m_groups;
	LegoS32 remaining = sizeOfArray(m_groups);

	do {
		if (*current) {
			(*current)->Unload();
			m_soundManager->DestroySoundGroup(*current);
			*current = NULL;
		}
		current++;
	} while (--remaining);

	m_soundManager = NULL;
}

// FUNCTION: LEGORACERS 0x00443ac0
void RaceSession::RaceSoundSource::Initialize(SoundManager* p_soundManager)
{
	if (m_soundManager) {
		DestroyGroups();
	}

	m_soundManager = p_soundManager;
	for (LegoS32 i = 0; i < sizeOfArray(m_groups); i++) {
		m_groups[i] = m_soundManager->CreateSoundGroup();
	}
}

// FUNCTION: LEGORACERS 0x00443b00
void RaceSession::RaceSoundSource::LoadSfxBank(const LegoChar* p_name)
{
	m_groups[0]->Load(p_name);
}

// FUNCTION: LEGORACERS 0x00443b10
void RaceSession::RaceSoundSource::LoadVoiceBanks(const LegoChar* p_name1, const LegoChar* p_name2)
{
	m_groups[1]->Load(p_name1);

	if (p_name2[0]) {
		m_groups[2]->Load(p_name2);
	}
}

// FUNCTION: LEGORACERS 0x00443b40
void RaceSession::RaceSoundSource::LoadAmbientBank(const LegoChar* p_name)
{
	m_groups[3]->Load(p_name);
}
