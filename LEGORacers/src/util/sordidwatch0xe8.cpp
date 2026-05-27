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

// STUB: LEGORACERS 0x00412970
void SordidWatch0xe8::FUN_00412970()
{
	STUB(0x00412970);
}
