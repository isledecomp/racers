#include "opalhaven0xf4.h"

DECOMP_SIZE_ASSERT(OpalHaven0xf4, 0xf4)

// FUNCTION: LEGORACERS 0x0040d530
OpalHaven0xf4::OpalHaven0xf4()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0040d5f0
void OpalHaven0xf4::Reset()
{
	for (LegoS32 i = 0; i < sizeOfArray(m_unk0x90); i++) {
		m_unk0x90[i] = 0;
		m_unk0xa8[i] = 0;
		m_unk0x9c[i] = 0xffffffff;
	}

	m_unk0xbc = 0;
	m_unk0x10 = -1.0f;
	m_unk0xb4 = 0;
	m_unk0xb8 = 0;
	m_unk0xd8 = 0;
	m_unk0xd0 = 0;
	m_unk0xd4 = 0;
	m_unk0xec = 0;
	m_unk0xf0 = 0;
}
