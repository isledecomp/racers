#include "audio/nullmusicgroup.h"

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
GolListLink* NullMusicGroup::Load(const LegoChar*)
{
	return Unload();
}

// FUNCTION: LEGORACERS 0x0041c0d0
GolListLink* NullMusicGroup::Unload()
{
	GolListLink* result;

	while (TRUE) {
		result = m_musicInstances.LastLink();

		if (!m_musicInstances.IsValidLastLink(result)) {
			break;
		}

		DestroyMusicInstance(&m_musicInstances.GetItem(*result));
	}

	m_unk0x04 = 0;
	return result;
}

// FUNCTION: LEGORACERS 0x0041c100
MusicInstance* NullMusicGroup::CreateMusicInstance(undefined4)
{
	MusicInstance* node = new MusicInstance();

	if (node) {
		node->SetMusicGroup(this);
		m_musicInstances.Append(node);
	}

	return node;
}

// FUNCTION: LEGORACERS 0x0044a1e0 FOLDED
LegoBool32 NullMusicGroup::IsLoaded()
{
	return 1;
}
