#include "defiantoven0x70.h"

DECOMP_SIZE_ASSERT(DefiantOven0x70, 0x70)

// FUNCTION: LEGORACERS 0x004a3550
void DefiantOven0x70::FUN_004a3550(LegoFloat p_param1)
{
	if (((m_unk0x44 & c_flagBit6) != 0) && ((m_unk0x44 & c_flagBit7) == 0)) {
		m_unk0x1c[0] += p_param1 * m_unk0x34[0];
		m_unk0x1c[1] += p_param1 * m_unk0x34[1];
		m_unk0x2c[0] += p_param1 * m_unk0x3c[0];
		m_unk0x2c[1] += p_param1 * m_unk0x3c[1];
	}
}

// STUB: LEGORACERS 0x004a4790
void DefiantOven0x70::FUN_004a4790(CrimsonPebble0x228*, BronzeFalcon0xc8770*)
{
	STUB(0x004a4790);
}
