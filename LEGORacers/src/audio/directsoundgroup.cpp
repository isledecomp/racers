#include "audio/directsoundgroup.h"

#include "audio/soundinstance.h"
#include "audio/streamingsoundinstance.h"

DECOMP_SIZE_ASSERT(DirectSoundGroup, 0x34)

// FUNCTION: LEGORACERS 0x0041ae10
DirectSoundGroup::DirectSoundGroup()
{
	m_soundManager = NULL;
	m_unk0x14 = 0;
	m_unk0x10 = 0;
	m_unk0x18 = 0;
}

// FUNCTION: LEGORACERS 0x0041ae50
DirectSoundGroup::~DirectSoundGroup()
{
	Unload();
}

// STUB: LEGORACERS 0x0041ae60
void DirectSoundGroup::Load(const LegoChar*)
{
	STUB(0x41ae60);
}

// STUB: LEGORACERS 0x0041b0e0
void DirectSoundGroup::Unload()
{
	STUB(0x41b0e0);
}

// FUNCTION: LEGORACERS 0x0041b150
LegoBool32 DirectSoundGroup::IsLoaded()
{
	if (m_unk0x14 && m_unk0x18) {
		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x0041b170
undefined4 DirectSoundGroup::VTable0x0c()
{
	return m_unk0x14;
}

// STUB: LEGORACERS 0x0041b180
void DirectSoundGroup::VTable0x14(LegoFloat)
{
	STUB(0x41b180);
}

// STUB: LEGORACERS 0x0041b1d0
SoundInstance* DirectSoundGroup::CreateSoundInstance(undefined4)
{
	STUB(0x41b1d0);
	return NULL;
}

// FUNCTION: LEGORACERS 0x0041b2d0
void DirectSoundGroup::DestroySoundInstance(SoundInstance* p_sound)
{
	p_sound->SetSoundGroup(NULL);
	p_sound->Remove();
	delete p_sound;
}

// STUB: LEGORACERS 0x0041b300
void DirectSoundGroup::VTable0x10(undefined4, LegoFloat, LegoFloat, LegoFloat, LegoS32, LegoFloat)
{
	STUB(0x41b300);
}

// STUB: LEGORACERS 0x0041b370
StreamingSoundInstance* DirectSoundGroup::CreateStreamingSoundInstance(undefined4)
{
	STUB(0x41b370);
	return NULL;
}

// FUNCTION: LEGORACERS 0x0041b470
void DirectSoundGroup::DestroyStreamingSoundInstance(StreamingSoundInstance* p_sound)
{
	p_sound->SetSoundGroup(NULL);
	p_sound->Remove();
	delete p_sound;
}

// FUNCTION: LEGORACERS 0x0041b4a0
SoundManager* DirectSoundGroup::GetSoundManager()
{
	return m_soundManager;
}
