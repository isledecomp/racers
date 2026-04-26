#include "audio/nullsoundmanager.h"

#include "types.h"

DECOMP_SIZE_ASSERT(GolListLink, 0x08)
DECOMP_SIZE_ASSERT(NullSoundManager, 0x30)

// FUNCTION: LEGORACERS 0x00418f20 FOLDED
void NullSoundManager::DestroySoundNode(SoundNode* p_node)
{
	RemoveActiveSoundNode(p_node);
	RemoveNode(p_node);
	delete p_node;
}

// FUNCTION: LEGORACERS 0x0041bca0
NullSoundManager::NullSoundManager()
{
}

// FUNCTION: LEGORACERS 0x0041bd00
NullSoundManager::~NullSoundManager()
{
	Shutdown();
}

// FUNCTION: LEGORACERS 0x0041bd50
LegoBool32 NullSoundManager::Initialize(LegoS32)
{
	Shutdown();
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0041bd60
void NullSoundManager::Shutdown()
{
	while (TRUE) {
		GolListLink* link = m_musicGroups.LastLink();

		if (!m_musicGroups.IsValidLastLink(link)) {
			break;
		}

		DestroyMusicGroup(&m_musicGroups.GetItem(*link));
	}

	while (TRUE) {
		GolListLink* link = m_soundGroups.LastLink();

		if (!m_soundGroups.IsValidLastLink(link)) {
			break;
		}

		DestroySoundGroup(&m_soundGroups.GetItem(*link));
	}

	while (m_activeSoundNodes) {
		DestroySoundNode(m_activeSoundNodes);
	}

	while (m_soundNodes) {
		DestroySoundNode(m_soundNodes);
	}
}

// FUNCTION: LEGORACERS 0x0041bdd0
MusicGroup* NullSoundManager::CreateMusicGroup()
{
	NullMusicGroup* node = new NullMusicGroup();

	if (node) {
		node->SetSoundManager(this);
		m_musicGroups.Append(node);
	}

	return node;
}

// FUNCTION: LEGORACERS 0x0041be50 FOLDED
void NullSoundManager::DestroyMusicGroup(MusicGroup* p_node)
{
	p_node->Remove();
	delete p_node;
}

// FUNCTION: LEGORACERS 0x0041be80
SoundGroup* NullSoundManager::CreateSoundGroup()
{
	NullSoundGroup* node = new NullSoundGroup();

	if (node) {
		node->SetSoundManager(this);
		m_soundGroups.Append(node);
	}

	return node;
}

// FUNCTION: LEGORACERS 0x0041bf00
void NullSoundManager::DestroySoundGroup(SoundGroup* p_node)
{
	p_node->Remove();
	delete static_cast<NullSoundGroup*>(p_node);
}

// FUNCTION: LEGORACERS 0x0041bf30
SoundNode* NullSoundManager::CreateSoundNode()
{
	SoundNode* node = new SoundNode();

	if (node) {
		AddNode(node);
	}

	return node;
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void NullSoundManager::Pause()
{
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void NullSoundManager::Resume()
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void NullSoundManager::Update(undefined4)
{
}
