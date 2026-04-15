#include "indigostar0x18.h"

#include "soundnode.h"

DECOMP_SIZE_ASSERT(IndigoStar0x18, 0x18)

// GLOBAL: LEGORACERS 0x004afa3c
LegoFloat g_unk0x4afa3c = 1.0f;

// FUNCTION: LEGORACERS 0x00417a30
IndigoStar0x18::IndigoStar0x18()
{
	m_unk0x04 = 0;
	m_unk0x0c = NULL;
	m_unk0x08 = NULL;
	m_unk0x10 = g_unk0x4afa3c;
	m_unk0x14 = g_unk0x4afa3c;
}

// FUNCTION: LEGORACERS 0x00417a80
IndigoStar0x18::~IndigoStar0x18()
{
	Shutdown();
}

// FUNCTION: LEGORACERS 0x00417a90
void IndigoStar0x18::Shutdown()
{
	m_unk0x04 = 0;
	m_unk0x0c = NULL;
	m_unk0x10 = g_unk0x4afa3c;
	m_unk0x14 = g_unk0x4afa3c;
}

// FUNCTION: LEGORACERS 0x00417ab0
SoundNode* IndigoStar0x18::AddNode(SoundNode* p_node)
{
	SoundNode* result = m_unk0x08;

	if (result) {
		while (TRUE) {
			if (result == p_node) {
				return result;
			}

			result = result->m_unk0x48;

			if (!result) {
				break;
			}
		}
	}

	p_node->m_unk0x48 = m_unk0x08;
	m_unk0x08 = p_node;
	return result;
}

// FUNCTION: LEGORACERS 0x00417ae0
SoundNode* IndigoStar0x18::RemoveNode(SoundNode* p_node)
{
	SoundNode* prev = m_unk0x08;

	if (prev) {
		if (prev == p_node) {
			m_unk0x08 = p_node->m_unk0x48;
			p_node->m_unk0x48 = NULL;
			return p_node;
		}

		SoundNode* current = prev->m_unk0x48;

		if (current) {
			while (TRUE) {
				if (current == p_node) {
					break;
				}

				prev = current;
				current = current->m_unk0x48;

				if (!current) {
					return NULL;
				}
			}

			prev->m_unk0x48 = current->m_unk0x48;
			p_node->m_unk0x48 = NULL;
			return p_node;
		}
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00417b30
SoundNode* IndigoStar0x18::VTable0x2c(SoundNode* p_node)
{
	SoundNode* result = m_unk0x0c;

	if (result) {
		while (TRUE) {
			if (result == p_node) {
				return result;
			}

			result = result->m_unk0x4c;

			if (!result) {
				break;
			}
		}
	}

	p_node->m_unk0x4c = m_unk0x0c;
	m_unk0x0c = p_node;
	return result;
}

// FUNCTION: LEGORACERS 0x00417b60
SoundNode* IndigoStar0x18::VTable0x30(SoundNode* p_node)
{
	SoundNode* result = m_unk0x0c;

	if (result) {
		if (result == p_node) {
			result = p_node->m_unk0x4c;
			m_unk0x0c = result;
			p_node->m_unk0x4c = NULL;
		}
		else {
			SoundNode* prev = m_unk0x0c;
			result = result->m_unk0x4c;

			if (result) {
				while (TRUE) {
					if (result == p_node) {
						break;
					}

					prev = result;
					result = result->m_unk0x4c;

					if (!result) {
						return result;
					}
				}

				result = result->m_unk0x4c;
				prev->m_unk0x4c = result;
				p_node->m_unk0x4c = NULL;
			}
		}
	}

	return result;
}
