#include "audio/soundgroup.h"
#include "audio/soundmanager.h"
#include "race/racesession.h"

DECOMP_SIZE_ASSERT(RaceSession::Field0x3300, 0x14)

// FUNCTION: LEGORACERS 0x00443a50
RaceSession::Field0x3300::Field0x3300()
{
	m_groups[0] = NULL;
	m_groups[1] = NULL;
	m_groups[2] = NULL;
	m_groups[3] = NULL;
	m_soundManager = NULL;
}

// FUNCTION: LEGORACERS 0x00443a70
RaceSession::Field0x3300::~Field0x3300()
{
	FUN_00443a80();
}

// FUNCTION: LEGORACERS 0x00443a80
void RaceSession::Field0x3300::FUN_00443a80()
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
void RaceSession::Field0x3300::FUN_00443ac0(SoundManager* p_soundManager)
{
	if (m_soundManager) {
		FUN_00443a80();
	}

	m_soundManager = p_soundManager;
	for (LegoS32 i = 0; i < sizeOfArray(m_groups); i++) {
		m_groups[i] = m_soundManager->CreateSoundGroup();
	}
}
