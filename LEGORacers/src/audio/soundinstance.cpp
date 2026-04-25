#include "audio/soundinstance.h"

#include "audio/frostpetal0x34.h"
#include "audio/soundbuffer.h"

DECOMP_SIZE_ASSERT(SoundInstance, 0x14)

// FUNCTION: LEGORACERS 0x0041b4b0
SoundInstance::SoundInstance()
{
	m_owner = NULL;
	m_soundBuffer = NULL;
}

// FUNCTION: LEGORACERS 0x0041b4f0
SoundInstance::~SoundInstance()
{
	SoundBuffer* soundBuffer = m_soundBuffer;

	if (soundBuffer) {
		soundBuffer->ClearSoundInstance();
		soundBuffer = m_soundBuffer;

		if (soundBuffer) {
			delete soundBuffer;
		}
	}

	if (m_owner) {
		Remove();
	}
}

// STUB: LEGORACERS 0x0041b530
void SoundInstance::VTable0x00(undefined4)
{
	STUB(0x41b530);
}

// STUB: LEGORACERS 0x0041b540
void SoundInstance::VTable0x04()
{
	STUB(0x41b540);
}

// STUB: LEGORACERS 0x0041b550
LegoBool32 SoundInstance::VTable0x08()
{
	STUB(0x41b550);
	return FALSE;
}

// STUB: LEGORACERS 0x0041b560
void SoundInstance::VTable0x0c(LegoFloat)
{
	STUB(0x41b560);
}

// STUB: LEGORACERS 0x0041b590
void SoundInstance::VTable0x10(LegoFloat)
{
	STUB(0x41b590);
}

// STUB: LEGORACERS 0x0041b5a0
void SoundInstance::VTable0x14(LegoFloat)
{
	STUB(0x41b5a0);
}

// STUB: LEGORACERS 0x0041b5b0
void SoundInstance::VTable0x18(LegoS32)
{
	STUB(0x41b5b0);
}

// STUB: LEGORACERS 0x0041b5c0
undefined4 SoundInstance::VTable0x1c()
{
	STUB(0x41b5c0);
	return 0;
}
