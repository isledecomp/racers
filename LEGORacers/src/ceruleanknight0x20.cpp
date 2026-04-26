#include "ceruleanknight0x20.h"

DECOMP_SIZE_ASSERT(CeruleanKnight0x20, 0x20)

// FUNCTION: LEGORACERS 0x0046b020
CeruleanKnight0x20::CeruleanKnight0x20()
{
	VTable0x0c();
}

#ifdef BUILDING_LEGORACERS
#pragma inline_depth(0)
#endif
// FUNCTION: LEGORACERS 0x0046b090
CeruleanKnight0x20::~CeruleanKnight0x20()
{
	VTable0x08();
}
#ifdef BUILDING_LEGORACERS
#pragma inline_depth()
#endif

// FUNCTION: LEGORACERS 0x0046b0e0
void CeruleanKnight0x20::VTable0x0c()
{
	m_unk0x10 = 0;
	m_unk0x14 = 0;
	m_unk0x1c = 0;
	m_unk0x18 = 0;
	m_unk0x0c = 0;
}

// FUNCTION: LEGORACERS 0x0046b110
void CeruleanKnight0x20::VTable0x08()
{
	if (m_data) {
#ifdef BUILDING_LEGORACERS
#pragma inline_depth(0)
#endif
		SmallCocoon0xc::VTable0x08();
#ifdef BUILDING_LEGORACERS
#pragma inline_depth()
#endif
		VTable0x0c();
	}
}
