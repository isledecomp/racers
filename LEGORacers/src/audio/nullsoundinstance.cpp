#include "audio/nullsoundinstance.h"

#include "types.h"

DECOMP_SIZE_ASSERT(NullSoundInstance, 0x10)

// FUNCTION: LEGORACERS 0x0041c3d0
NullSoundInstance::NullSoundInstance()
{
	m_soundGroup = NULL;
}

// FUNCTION: LEGORACERS 0x0041c410
NullSoundInstance::~NullSoundInstance()
{
	if (m_soundGroup) {
		Remove();
	}
}

// FUNCTION: LEGORACERS 0x0044e7e0 FOLDED
LegoBool32 NullSoundInstance::IsPlaying()
{
	return FALSE;
}

#pragma code_seg(".text$soundinstance_getsoundGroup")
// FUNCTION: LEGORACERS 0x0041b5c0 FOLDED
SoundGroup* NullSoundInstance::GetSoundGroup()
{
	return m_soundGroup;
}
#pragma code_seg()

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void NullSoundInstance::Stop()
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void NullSoundInstance::Play(LegoBool32)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void NullSoundInstance::SetVolume(LegoFloat)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void NullSoundInstance::SetPan(LegoFloat)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void NullSoundInstance::SetFrequencyScale(LegoFloat)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void NullSoundInstance::SetPriority(LegoS32)
{
}
