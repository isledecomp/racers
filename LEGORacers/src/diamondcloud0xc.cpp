#include "diamondcloud0xc.h"

DECOMP_SIZE_ASSERT(DiamondCloud0xc, 0xc)

// FUNCTION: LEGORACERS 0x0046e8f0
DiamondCloud0xc::DiamondCloud0xc()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046e900
DiamondCloud0xc::~DiamondCloud0xc()
{
	FUN_0046e950();
}

// FUNCTION: LEGORACERS 0x0046e910
void DiamondCloud0xc::Reset()
{
	m_unk0x00 = 0;
	m_unk0x04 = 0;
	m_unk0x08 = 0;
}

// FUNCTION: LEGORACERS 0x0046e950
LegoBool32 DiamondCloud0xc::FUN_0046e950()
{
	if (m_unk0x04) {
		Reset();
	}

	return m_unk0x04 == 0;
}
