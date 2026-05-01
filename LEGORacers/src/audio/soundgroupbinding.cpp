#include "audio/soundgroupbinding.h"

#include "audio/soundgroup.h"

DECOMP_SIZE_ASSERT(SoundGroupBinding, 0xc)

// FUNCTION: LEGORACERS 0x0046e8f0
SoundGroupBinding::SoundGroupBinding()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046e900
SoundGroupBinding::~SoundGroupBinding()
{
	ResetSoundGroup();
}

// FUNCTION: LEGORACERS 0x0046e910
void SoundGroupBinding::Reset()
{
	m_soundManager = NULL;
	m_soundGroup = NULL;
	m_unk0x08 = 0;
}

// FUNCTION: LEGORACERS 0x0046e920
LegoBool32 SoundGroupBinding::SetSoundGroup(
	SoundManager* p_soundManager,
	SoundGroup* p_soundGroup,
	undefined4 p_unk0x0c
)
{
	ResetSoundGroup();
	m_soundManager = p_soundManager;
	m_soundGroup = p_soundGroup;
	m_unk0x08 = p_unk0x0c;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0046e950
LegoBool32 SoundGroupBinding::ResetSoundGroup()
{
	if (m_soundGroup) {
		Reset();
	}

	return m_soundGroup == NULL;
}
