#include "audio/nullmusicgroup.h"

#include "audio/nullmusicinstance.h"
#include "types.h"

DECOMP_SIZE_ASSERT(MusicGroup, 0x10)
DECOMP_SIZE_ASSERT(NullMusicGroup, 0x20)

// FUNCTION: LEGORACERS 0x0041a9d0 FOLDED
void NullMusicGroup::DestroyMusicInstance(MusicInstance* p_node)
{
	delete p_node;
}

// FUNCTION: LEGORACERS 0x0041a9f0 FOLDED
SoundManager* NullMusicGroup::GetSoundManager()
{
	return m_soundManager;
}

// FUNCTION: LEGORACERS 0x0041c010
NullMusicGroup::NullMusicGroup()
{
	m_soundManager = NULL;
}

// FUNCTION: LEGORACERS 0x0041c070
NullMusicGroup::~NullMusicGroup()
{
	Unload();
}

// FUNCTION: LEGORACERS 0x0041c0c0
void NullMusicGroup::Load(const LegoChar*)
{
	Unload();
}

// FUNCTION: LEGORACERS 0x0041c0d0
void NullMusicGroup::Unload()
{
	GolListLink* link = m_musicInstances.LastLink();
	while (m_musicInstances.IsValidLastLink(link)) {
		DestroyMusicInstance(&m_musicInstances.GetItem(*link));
		link = m_musicInstances.LastLink();
	}

	m_musicCount = 0;
}

// FUNCTION: LEGORACERS 0x0041c100
MusicInstance* NullMusicGroup::CreateMusicInstance(LegoU32)
{
	NullMusicInstance* node = new NullMusicInstance();

	if (node) {
		node->SetMusicGroup(this);
		m_musicInstances.Append(*node);
	}

	return node;
}

// FUNCTION: LEGORACERS 0x0044a1e0 FOLDED
LegoBool32 NullMusicGroup::IsLoaded()
{
	return TRUE;
}
