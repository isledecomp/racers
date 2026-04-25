#include "audio/streamingsoundinstance.h"

#include "audio/frostpetal0x34.h"
#include "audio/soundbuffer.h"

DECOMP_SIZE_ASSERT(StreamingSoundInstance, 0x48)

// FUNCTION: LEGORACERS 0x0041acb0
StreamingSoundInstance::StreamingSoundInstance()
{
	m_owner = NULL;
}

// FUNCTION: LEGORACERS 0x0041ad00
StreamingSoundInstance::~StreamingSoundInstance()
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

// STUB: LEGORACERS 0x0041ad80
void StreamingSoundInstance::VTable0x04(undefined4)
{
	STUB(0x41ad80);
}

// STUB: LEGORACERS 0x0041ad90
void StreamingSoundInstance::VTable0x08()
{
	STUB(0x41ad90);
}

// STUB: LEGORACERS 0x0041ada0
undefined4 StreamingSoundInstance::VTable0x0c()
{
	STUB(0x41ada0);
	return 0;
}

// STUB: LEGORACERS 0x0041adb0
void StreamingSoundInstance::VTable0x18(undefined4)
{
	STUB(0x41adb0);
}

// STUB: LEGORACERS 0x0041ae00
undefined4 StreamingSoundInstance::VTable0x10()
{
	STUB(0x41ae00);
	return 0;
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void StreamingSoundInstance::VTable0x14(undefined4)
{
}
