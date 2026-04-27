#include "audio/nullstreamingsoundinstance.h"

#include "audio/directsoundgroup.h"
#include "types.h"

DECOMP_SIZE_ASSERT(NullStreamingSoundInstance, 0x44)

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

// FUNCTION: LEGORACERS 0x0044e7e0 FOLDED
LegoBool32 NullStreamingSoundInstance::IsPlaying()
{
	return FALSE;
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
void NullStreamingSoundInstance::VTable0x14(undefined4)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void NullStreamingSoundInstance::UpdateSpatial(SoundNode*)
{
}
