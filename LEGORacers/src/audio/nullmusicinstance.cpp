#include "audio/nullmusicinstance.h"

DECOMP_SIZE_ASSERT(NullMusicInstance, 0x10)

// FUNCTION: LEGORACERS 0x004113b0 FOLDED
LegoBool32 NullMusicInstance::Play(LegoBool32)
{
	return FALSE;
}

// FUNCTION: LEGORACERS 0x0041bfa0
NullMusicInstance::NullMusicInstance()
{
	m_musicGroup = NULL;
}

// FUNCTION: LEGORACERS 0x0041bfe0
NullMusicInstance::~NullMusicInstance()
{
	if (m_musicGroup) {
		Remove();
	}
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void NullMusicInstance::Stop()
{
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void NullMusicInstance::Pause()
{
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void NullMusicInstance::Resume()
{
}

// FUNCTION: LEGORACERS 0x0044e7e0 FOLDED
LegoBool32 NullMusicInstance::IsPlaying()
{
	return FALSE;
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void NullMusicInstance::SetVolume(LegoFloat)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void NullMusicInstance::VTable0x1c(undefined4)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void NullMusicInstance::VTable0x20(undefined4)
{
}
