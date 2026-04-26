#include "audio/nullsoundgroup.h"

#include "types.h"

DECOMP_SIZE_ASSERT(SoundGroup, 0x10)
DECOMP_SIZE_ASSERT(NullSoundGroup, 0x28)

// FUNCTION: LEGORACERS 0x0041c200
NullSoundGroup::NullSoundGroup()
{
	m_soundManager = NULL;
}

// FUNCTION: LEGORACERS 0x0041c240
NullSoundGroup::~NullSoundGroup()
{
	Unload();
}

// FUNCTION: LEGORACERS 0x0041c250
void NullSoundGroup::Load(const LegoChar*)
{
	Unload();
}

// STUB: LEGORACERS 0x0041c260
void NullSoundGroup::Unload()
{
	// TODO
	STUB(0x41c260);
}
