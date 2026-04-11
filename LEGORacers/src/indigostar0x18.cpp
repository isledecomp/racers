#include "indigostar0x18.h"

#include "silvernode0x50.h"

DECOMP_SIZE_ASSERT(IndigoStar0x18, 0x18)

// GLOBAL: LEGORACERS 0x4afa3c
LegoFloat g_unk0x4afa3c = 1.0f;

// FUNCTION: LEGORACERS 0x417a30
IndigoStar0x18::IndigoStar0x18()
{
	m_unk0x04 = 0;
	m_unk0x0c = NULL;
	m_unk0x08 = NULL;
	m_unk0x10 = g_unk0x4afa3c;
	m_unk0x14 = g_unk0x4afa3c;
}

// FUNCTION: LEGORACERS 0x417a80
IndigoStar0x18::~IndigoStar0x18()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x417a90
void IndigoStar0x18::VTable0x08()
{
	m_unk0x04 = 0;
	m_unk0x0c = NULL;
	m_unk0x10 = g_unk0x4afa3c;
	m_unk0x14 = g_unk0x4afa3c;
}

// FUNCTION: LEGORACERS 0x417ab0
SilverNode0x50* IndigoStar0x18::FUN_00417ab0(SilverNode0x50* p_node)
{
	SilverNode0x50* result = m_unk0x08;

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

// FUNCTION: LEGORACERS 0x417ae0
SilverNode0x50* IndigoStar0x18::FUN_00417ae0(SilverNode0x50* p_node)
{
	SilverNode0x50* prev = m_unk0x08;

	if (prev) {
		if (prev == p_node) {
			m_unk0x08 = p_node->m_unk0x48;
			p_node->m_unk0x48 = NULL;
			return p_node;
		}

		SilverNode0x50* current = prev->m_unk0x48;

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

// FUNCTION: LEGORACERS 0x417b30
SilverNode0x50* IndigoStar0x18::VTable0x2c(SilverNode0x50* p_node)
{
	SilverNode0x50* result = m_unk0x0c;

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

// FUNCTION: LEGORACERS 0x417b60
SilverNode0x50* IndigoStar0x18::VTable0x30(SilverNode0x50* p_node)
{
	SilverNode0x50* result = m_unk0x0c;

	if (result) {
		if (result == p_node) {
			result = p_node->m_unk0x4c;
			m_unk0x0c = result;
			p_node->m_unk0x4c = NULL;
		}
		else {
			SilverNode0x50* prev = m_unk0x0c;
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
