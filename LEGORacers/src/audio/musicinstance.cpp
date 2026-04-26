#include "audio/musicinstance.h"

DECOMP_SIZE_ASSERT(MusicInstance, 0x10)

// FUNCTION: LEGORACERS 0x004113b0 FOLDED
undefined4 MusicInstance::VTable0x04(undefined4)
{
	return 0;
}

// FUNCTION: LEGORACERS 0x0041bfa0
MusicInstance::MusicInstance()
{
	m_musicGroup = NULL;
}

// FUNCTION: LEGORACERS 0x0041bfe0
MusicInstance::~MusicInstance()
{
	if (m_musicGroup) {
		Remove();
	}
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void MusicInstance::Stop()
{
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void MusicInstance::VTable0x0c()
{
}
