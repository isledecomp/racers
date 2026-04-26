#include "audio/directmusicgroup.h"

#include "audio/musicinstance.h"

DECOMP_SIZE_ASSERT(DirectMusicGroup, 0x128)

// TODO: Clean body, but MSVC sinks the derived vtable store past these assignments.
// FUNCTION: LEGORACERS 0x0041a650
DirectMusicGroup::DirectMusicGroup()
{
	m_unk0x20 = 0;
	m_soundManager = NULL;
	m_unk0x124 = 0;
}

// FUNCTION: LEGORACERS 0x0041a6b0
DirectMusicGroup::~DirectMusicGroup()
{
	Unload();
}

// STUB: LEGORACERS 0x0041a700
GolListLink* DirectMusicGroup::Load(const LegoChar*)
{
	STUB(0x41a700);
	return NULL;
}

// STUB: LEGORACERS 0x0041a850
GolListLink* DirectMusicGroup::Unload()
{
	STUB(0x41a850);
	return NULL;
}

// FUNCTION: LEGORACERS 0x0041a890
LegoBool32 DirectMusicGroup::IsLoaded()
{
	return m_unk0x04 != 0;
}

// STUB: LEGORACERS 0x0041a8a0
MusicInstance* DirectMusicGroup::CreateMusicInstance(undefined4)
{
	STUB(0x41a8a0);
	return NULL;
}

// FUNCTION: LEGORACERS 0x0041a9d0 FOLDED
void DirectMusicGroup::DestroyMusicInstance(MusicInstance* p_node)
{
	delete p_node;
}

// FUNCTION: LEGORACERS 0x0041a9f0 FOLDED
SoundManager* DirectMusicGroup::GetSoundManager()
{
	return m_soundManager;
}
