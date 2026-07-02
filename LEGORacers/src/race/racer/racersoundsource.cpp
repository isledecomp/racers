#include "race/racer/racersoundsource.h"

#include "audio/soundgroup.h"
#include "audio/soundnode.h"
#include "audio/spatialsoundinstance.h"
#include "audio/streamingsoundinstance.h"
#include "race/racestate.h"

DECOMP_SIZE_ASSERT(RacerSoundSource, 0x14)

extern SpatialSoundInstance g_nullStreamingSoundInstance;

// FUNCTION: LEGORACERS 0x00443b50
void RacerSoundSource::PlaySoundById(LegoU32 p_soundId)
{
	if (m_soundManager) {
		SoundGroup* soundGroup = NULL;
		LegoU32 index = ResolveSoundId(p_soundId, &soundGroup);
		soundGroup->PlaySoundByIndex(index);
	}
}

// FUNCTION: LEGORACERS 0x00443b80
void RacerSoundSource::PlaySpatialSoundById(
	LegoU32 p_soundId,
	SoundVector* p_position,
	LegoFloat p_minDistance,
	LegoFloat p_maxDistance,
	LegoFloat p_volume,
	LegoFloat p_frequencyScale
)
{
	if (m_soundManager) {
		SoundGroup* soundGroup = NULL;
		LegoU32 index = ResolveSoundId(p_soundId, &soundGroup);
		soundGroup->PlaySpatialSound(index, p_position, p_minDistance, p_maxDistance, p_volume, p_frequencyScale);
	}
}

// FUNCTION: LEGORACERS 0x00443bd0
SpatialSoundInstance* RacerSoundSource::AcquireSoundById(LegoU32 p_soundId)
{
	if (!m_soundManager) {
		return &g_nullStreamingSoundInstance;
	}

	SoundGroup* soundGroup = NULL;
	LegoU32 index = ResolveSoundId(p_soundId, &soundGroup);
	return soundGroup->CreateStreamingSoundInstance(index);
}

// FUNCTION: LEGORACERS 0x00443c30
LegoU32 RacerSoundSource::ResolveSoundId(LegoU32 p_soundId, SoundGroup** p_soundGroup)
{
	if (p_soundId < 1000) {
		*p_soundGroup = m_groups[0];
		return p_soundId;
	}

	if (p_soundId < 1100) {
		*p_soundGroup = m_groups[1];
		return p_soundId - 1000;
	}

	if (p_soundId < 3000) {
		*p_soundGroup = m_groups[2];
		return p_soundId - 1100;
	}

	*p_soundGroup = m_groups[3];
	return p_soundId - 3000;
}
