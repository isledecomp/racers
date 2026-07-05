#include "audio/nullstreamingsoundinstance.h"

#include "audio/directsoundgroup.h"
#include "types.h"

#include <stddef.h>

DECOMP_SIZE_ASSERT(NullStreamingSoundInstance, 0x44)

// GLOBAL: LEGORACERS 0x004c6bc0
SpatialSoundInstance g_nullStreamingSoundInstance;

// FUNCTION: LEGORACERS 0x0041c180
NullStreamingSoundInstance::NullStreamingSoundInstance()
{
	m_soundGroup = NULL;
}

// FUNCTION: LEGORACERS 0x0041c1d0
NullStreamingSoundInstance::~NullStreamingSoundInstance()
{
	if (m_soundGroup) {
		Remove();
	}
}

// FUNCTION: LEGORACERS 0x0041ae00 FOLDED
DirectSoundGroup* NullStreamingSoundInstance::GetSoundGroup()
{
	return (DirectSoundGroup*) m_soundGroup;
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void NullStreamingSoundInstance::Stop()
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void NullStreamingSoundInstance::Play(LegoBool32)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void NullStreamingSoundInstance::SetPriority(undefined4)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void NullStreamingSoundInstance::UpdateSpatial(SoundNode*)
{
}
