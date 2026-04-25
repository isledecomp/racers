#include "audio/nullsoundmanager.h"

#include "types.h"

DECOMP_SIZE_ASSERT(GolListLink, 0x08)
DECOMP_SIZE_ASSERT(NullSoundManager, 0x30)

// FUNCTION: LEGORACERS 0x00418f20 FOLDED
void NullSoundManager::VTable0x28(SoundNode* p_node)
{
	VTable0x30(p_node);
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
		GolListLink* link = m_unk0x18.LastLink();

		if (!m_unk0x18.IsValidLastLink(link)) {
			break;
		}

		VTable0x18(&m_unk0x18.GetItem(*link));
	}

	while (TRUE) {
		GolListLink* link = m_unk0x24.LastLink();

		if (!m_unk0x24.IsValidLastLink(link)) {
			break;
		}

		VTable0x20(&m_unk0x24.GetItem(*link));
	}

	while (m_unk0x0c) {
		VTable0x28(m_unk0x0c);
	}

	while (m_unk0x08) {
		VTable0x28(m_unk0x08);
	}
}

// FUNCTION: LEGORACERS 0x0041bdd0
CrimsonRay0x20* NullSoundManager::VTable0x14()
{
	CrimsonRay0x20* node = new CrimsonRay0x20();

	if (node) {
		node->SetUnk0x10(this);
		m_unk0x18.Append(node);
	}

	return node;
}

// FUNCTION: LEGORACERS 0x0041be50 FOLDED
void NullSoundManager::VTable0x18(CrimsonRay0x20* p_node)
{
	p_node->Remove();
	delete p_node;
}

// FUNCTION: LEGORACERS 0x0041be80
EmberDust0x28* NullSoundManager::VTable0x1c()
{
	EmberDust0x28* node = new EmberDust0x28();

	if (node) {
		node->SetUnk0x0c(this);
		m_unk0x24.Append(node);
	}

	return node;
}

// FUNCTION: LEGORACERS 0x0041bf00
void NullSoundManager::VTable0x20(EmberDust0x28* p_node)
{
	p_node->Remove();
	delete p_node;
}

// FUNCTION: LEGORACERS 0x0041bf30
SoundNode* NullSoundManager::VTable0x24()
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
void NullSoundManager::VTable0x34(undefined4)
{
}
