#include "audio/staticnullsoundinstance.h"

#include "types.h"

DECOMP_SIZE_ASSERT(StaticNullSoundInstance, 0x8)

// GLOBAL: LEGORACERS 0x004c6bb8
StaticNullSoundInstance g_staticNullSoundInstance;

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void StaticNullSoundInstance::Play(LegoBool32)
{
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void StaticNullSoundInstance::Stop()
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void StaticNullSoundInstance::SetVolume(LegoFloat)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void StaticNullSoundInstance::SetPan(LegoFloat)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void StaticNullSoundInstance::SetFrequencyScale(LegoFloat)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void StaticNullSoundInstance::SetPriority(LegoS32)
{
}
