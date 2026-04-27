#include "audio/soundmanager.h"

#include "audio/soundnode.h"

DECOMP_SIZE_ASSERT(SoundManager, 0x18)

// GLOBAL: LEGORACERS 0x004afa3c
LegoFloat g_defaultSoundManagerVolumeScale = 1.0f;

// FUNCTION: LEGORACERS 0x00417a30
SoundManager::SoundManager()
{
	m_unk0x04 = 0;
	m_activeSoundNodes = NULL;
	m_soundNodes = NULL;
	m_volumeScale = g_defaultSoundManagerVolumeScale;
	m_musicVolumeScale = g_defaultSoundManagerVolumeScale;
}

// FUNCTION: LEGORACERS 0x00417a80
SoundManager::~SoundManager()
{
	Shutdown();
}

// FUNCTION: LEGORACERS 0x00417a90
void SoundManager::Shutdown()
{
	m_unk0x04 = 0;
	m_activeSoundNodes = NULL;
	m_volumeScale = g_defaultSoundManagerVolumeScale;
	m_musicVolumeScale = g_defaultSoundManagerVolumeScale;
}

// FUNCTION: LEGORACERS 0x00417ab0
SoundNode* SoundManager::AddNode(SoundNode* p_node)
{
	SoundNode* result = m_soundNodes;

	if (result) {
		while (TRUE) {
			if (result == p_node) {
				return result;
			}

			result = result->m_nextSoundNode;

			if (!result) {
				break;
			}
		}
	}

	p_node->m_nextSoundNode = m_soundNodes;
	m_soundNodes = p_node;
	return result;
}

// FUNCTION: LEGORACERS 0x00417ae0
SoundNode* SoundManager::RemoveNode(SoundNode* p_node)
{
	SoundNode* prev = m_soundNodes;

	if (prev) {
		if (prev == p_node) {
			m_soundNodes = p_node->m_nextSoundNode;
			p_node->m_nextSoundNode = NULL;
			return p_node;
		}

		SoundNode* current = prev->m_nextSoundNode;

		if (current) {
			while (TRUE) {
				if (current == p_node) {
					break;
				}

				prev = current;
				current = current->m_nextSoundNode;

				if (!current) {
					return NULL;
				}
			}

			prev->m_nextSoundNode = current->m_nextSoundNode;
			p_node->m_nextSoundNode = NULL;
			return p_node;
		}
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00417b30
SoundNode* SoundManager::AddActiveSoundNode(SoundNode* p_node)
{
	SoundNode* result = m_activeSoundNodes;

	if (result) {
		while (TRUE) {
			if (result == p_node) {
				return result;
			}

			result = result->m_nextActiveSoundNode;

			if (!result) {
				break;
			}
		}
	}

	p_node->m_nextActiveSoundNode = m_activeSoundNodes;
	m_activeSoundNodes = p_node;
	return result;
}

// FUNCTION: LEGORACERS 0x00417b60
SoundNode* SoundManager::RemoveActiveSoundNode(SoundNode* p_node)
{
	SoundNode* result = m_activeSoundNodes;

	if (result) {
		if (result == p_node) {
			result = p_node->m_nextActiveSoundNode;
			m_activeSoundNodes = result;
			p_node->m_nextActiveSoundNode = NULL;
		}
		else {
			SoundNode* prev = m_activeSoundNodes;
			result = result->m_nextActiveSoundNode;

			if (result) {
				while (TRUE) {
					if (result == p_node) {
						break;
					}

					prev = result;
					result = result->m_nextActiveSoundNode;

					if (!result) {
						return result;
					}
				}

				result = result->m_nextActiveSoundNode;
				prev->m_nextActiveSoundNode = result;
				p_node->m_nextActiveSoundNode = NULL;
			}
		}
	}

	return result;
}
