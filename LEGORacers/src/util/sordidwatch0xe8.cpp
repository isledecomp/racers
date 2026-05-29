#include "util/sordidwatch0xe8.h"

// TODO: Add when the size is known
// DECOMP_SIZE_ASSERT(SordidWatch0xe8, 0xTODO)

// FUNCTION: LEGORACERS 0x00412840
void SordidWatch0xe8::FUN_00412840()
{
	if (m_flags & 2) {
		FUN_00412970();
		m_unk0xd0 = 0;
		m_unk0xd4 = 0;
		m_unk0xd8 = 0;
		m_unk0xdc = 0;
		m_unk0xe0 = 0;
		m_unk0xe4 = 0;
		m_flags &= ~0x1e;
	}
}

// FUNCTION: LEGORACERS 0x00412970
void SordidWatch0xe8::FUN_00412970()
{
	m_unk0xb4 = 0;
	m_unk0xb0 = m_unk0xac;
	for (LegoU32 i = 0; i < m_unk0xa8 - 1; i++) {
		m_unk0xac[i].m_unk0x34 = &m_unk0xac[i + 1];
		m_unk0xac[i].m_unk0x30 = 0;
	}

	m_unk0xac[m_unk0xa8 - 1].m_unk0x34 = 0;
	m_unk0xac[m_unk0xa8 - 1].m_unk0x30 = 0;
}
