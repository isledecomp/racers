#include "audio/frostpetal0x34.h"

#include "audio/soundinstance.h"
#include "audio/streamingsoundinstance.h"

DECOMP_SIZE_ASSERT(FrostPetal0x34, 0x34)

// FUNCTION: LEGORACERS 0x0041ae10
FrostPetal0x34::FrostPetal0x34()
{
	m_unk0x0c = NULL;
	m_unk0x14 = 0;
	m_unk0x10 = 0;
	m_unk0x18 = 0;
}

// FUNCTION: LEGORACERS 0x0041ae50
FrostPetal0x34::~FrostPetal0x34()
{
	VTable0x04();
}

// STUB: LEGORACERS 0x0041ae60
void FrostPetal0x34::VTable0x00(LegoChar*)
{
	STUB(0x41ae60);
}

// STUB: LEGORACERS 0x0041b0e0
void FrostPetal0x34::VTable0x04()
{
	STUB(0x41b0e0);
}

// FUNCTION: LEGORACERS 0x0041b150
LegoBool32 FrostPetal0x34::VTable0x08()
{
	if (m_unk0x14 && m_unk0x18) {
		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x0041b170
undefined4 FrostPetal0x34::VTable0x0c()
{
	return m_unk0x14;
}

// STUB: LEGORACERS 0x0041b180
void FrostPetal0x34::VTable0x14(LegoFloat)
{
	STUB(0x41b180);
}

// STUB: LEGORACERS 0x0041b1d0
SoundInstance* FrostPetal0x34::VTable0x18(undefined4)
{
	STUB(0x41b1d0);
	return NULL;
}

// FUNCTION: LEGORACERS 0x0041b2d0
void FrostPetal0x34::DestroySoundInstance(SoundInstance* p_sound)
{
	p_sound->SetOwner(NULL);
	p_sound->Remove();
	delete p_sound;
}

// STUB: LEGORACERS 0x0041b300
void FrostPetal0x34::VTable0x10(undefined4, LegoFloat, LegoFloat, LegoFloat, LegoS32, LegoFloat)
{
	STUB(0x41b300);
}

// STUB: LEGORACERS 0x0041b370
StreamingSoundInstance* FrostPetal0x34::VTable0x20(undefined4)
{
	STUB(0x41b370);
	return NULL;
}

// FUNCTION: LEGORACERS 0x0041b470
void FrostPetal0x34::DestroyStreamingSoundInstance(StreamingSoundInstance* p_sound)
{
	p_sound->SetOwner(NULL);
	p_sound->Remove();
	delete p_sound;
}

// FUNCTION: LEGORACERS 0x0041b4a0
SoundManager* FrostPetal0x34::VTable0x28()
{
	return m_unk0x0c;
}
