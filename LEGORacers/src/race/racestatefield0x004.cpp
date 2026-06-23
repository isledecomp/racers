#include "audio/soundgroup.h"
#include "audio/soundnode.h"
#include "audio/spatialsoundinstance.h"
#include "audio/streamingsoundinstance.h"
#include "race/racestate.h"

DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x004, 0x14)

extern SpatialSoundInstance g_nullStreamingSoundInstance;

// FUNCTION: LEGORACERS 0x00443b50
void RaceState::Racer::Field0x004::FUN_00443b50(LegoU32 p_unk0x04)
{
	if (m_soundManager) {
		SoundGroup* soundGroup = NULL;
		LegoU32 index = FUN_00443c30(p_unk0x04, &soundGroup);
		soundGroup->PlaySoundByIndex(index);
	}
}

// FUNCTION: LEGORACERS 0x00443b80
void RaceState::Racer::Field0x004::FUN_00443b80(
	LegoU32 p_unk0x04,
	SoundVector* p_unk0x08,
	LegoFloat p_unk0x0c,
	LegoFloat p_unk0x10,
	LegoFloat p_unk0x14,
	LegoFloat p_unk0x18
)
{
	if (m_soundManager) {
		SoundGroup* soundGroup = NULL;
		LegoU32 index = FUN_00443c30(p_unk0x04, &soundGroup);
		soundGroup->PlaySpatialSound(index, p_unk0x08, p_unk0x0c, p_unk0x10, p_unk0x14, p_unk0x18);
	}
}

// FUNCTION: LEGORACERS 0x00443bd0
SpatialSoundInstance* RaceState::Racer::Field0x004::FUN_00443bd0(LegoU32 p_unk0x04)
{
	if (!m_soundManager) {
		return &g_nullStreamingSoundInstance;
	}

	SoundGroup* soundGroup = NULL;
	LegoU32 index = FUN_00443c30(p_unk0x04, &soundGroup);
	return soundGroup->CreateStreamingSoundInstance(index);
}

// FUNCTION: LEGORACERS 0x00443c30
LegoU32 RaceState::Racer::Field0x004::FUN_00443c30(LegoU32 p_unk0x04, SoundGroup** p_soundGroup)
{
	if (p_unk0x04 < 1000) {
		*p_soundGroup = m_groups[0];
		return p_unk0x04;
	}

	if (p_unk0x04 < 1100) {
		*p_soundGroup = m_groups[1];
		return p_unk0x04 - 1000;
	}

	if (p_unk0x04 < 3000) {
		*p_soundGroup = m_groups[2];
		return p_unk0x04 - 1100;
	}

	*p_soundGroup = m_groups[3];
	return p_unk0x04 - 3000;
}
