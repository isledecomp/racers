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
	m_firstSoundIndex = 0;
}

// FUNCTION: LEGORACERS 0x0046e920
LegoBool32 SoundGroupBinding::SetSoundGroup(
	SoundManager* p_soundManager,
	SoundGroup* p_soundGroup,
	undefined4 p_firstSoundIndex
)
{
	ResetSoundGroup();
	m_soundManager = p_soundManager;
	m_soundGroup = p_soundGroup;
	m_firstSoundIndex = p_firstSoundIndex;
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

// FUNCTION: LEGORACERS 0x0046e970
void SoundGroupBinding::PlaySoundByIndex(LegoU32 p_index)
{
	if (m_soundGroup && p_index) {
		m_soundGroup->PlaySoundByIndex(m_firstSoundIndex + p_index - 1);
	}
}

// FUNCTION: LEGORACERS 0x0046e9a0
void SoundGroupBinding::PlaySpatialSound(
	LegoU32 p_index,
	SoundVector* p_position,
	LegoFloat p_minDistance,
	LegoFloat p_maxDistance,
	LegoFloat p_volume,
	LegoFloat p_frequencyScale
)
{
	if (m_soundGroup && p_index) {
		m_soundGroup->PlaySpatialSound(
			m_firstSoundIndex + p_index - 1,
			p_position,
			p_minDistance,
			p_maxDistance,
			p_volume,
			p_frequencyScale
		);
	}
}
