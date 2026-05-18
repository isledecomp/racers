#include "turquoiseglow0x80.h"

DECOMP_SIZE_ASSERT(TurquoiseGlow0x80, 0x80)
DECOMP_SIZE_ASSERT(TurquoiseGlowColor, 0x05)
DECOMP_SIZE_ASSERT(TurquoiseGlow0x80::LoadParams, 0x14)
DECOMP_SIZE_ASSERT(TurquoiseGlow0x80::Entry0x30, 0x30)

// STUB: LEGORACERS 0x00420680
TurquoiseGlow0x80::TurquoiseGlow0x80()
{
	// TODO
	STUB(0x420680);
}

// STUB: LEGORACERS 0x00420710
TurquoiseGlow0x80::~TurquoiseGlow0x80()
{
	// TODO
	STUB(0x420710);
}

// STUB: LEGORACERS 0x004207b0
void TurquoiseGlow0x80::Clear()
{
	// TODO
	STUB(0x004207b0);
}

// STUB: LEGORACERS 0x004208f0
void TurquoiseGlow0x80::Load(LoadParams*)
{
	STUB(0x004208f0);
}

// FUNCTION: LEGORACERS 0x00421050
void TurquoiseGlow0x80::FUN_00421050(LegoU32 p_index, TurquoiseGlowColor* p_color)
{
	Entry0x30& entry = m_entries[p_index];

	p_color->m_unk0x00 = entry.m_color.m_unk0x00;
	p_color->m_unk0x01 = entry.m_color.m_unk0x01;
	p_color->m_unk0x02 = entry.m_color.m_unk0x02;
	p_color->m_unk0x03 = entry.m_color.m_unk0x03;
	p_color->m_unk0x04 = entry.m_color.m_unk0x04;
}
