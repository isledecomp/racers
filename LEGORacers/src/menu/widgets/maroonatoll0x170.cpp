#include "menu/widgets/maroonatoll0x170.h"

#include <string.h>

DECOMP_SIZE_ASSERT(MaroonAtoll0x170, 0x170)

// FUNCTION: LEGORACERS 0x00483970
MaroonAtoll0x170::MaroonAtoll0x170()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004839e0
MaroonAtoll0x170::~MaroonAtoll0x170()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x00483a30
void MaroonAtoll0x170::Reset()
{
	m_unk0xcc = 0;
	m_unk0xc0 = 0;
	memset(&m_unk0xd0, 0, sizeof(m_unk0xd0));
	VioletShoal0xc0::Reset();
}

// STUB: LEGORACERS 0x00483af0
LegoBool32 MaroonAtoll0x170::VTable0x08()
{
	STUB(0x00483af0);
	return FALSE;
}

// STUB: LEGORACERS 0x00483f70
void MaroonAtoll0x170::VTable0x60(LegoS32)
{
	STUB(0x00483f70);
}

// STUB: LEGORACERS 0x00484100
void MaroonAtoll0x170::VTable0x50(undefined4)
{
	STUB(0x00484100);
}

// STUB: LEGORACERS 0x004841b0
LegoS32 MaroonAtoll0x170::VTable0x54()
{
	STUB(0x004841b0);
	return 0;
}

// STUB: LEGORACERS 0x00484290
LegoS32 MaroonAtoll0x170::VTable0x58()
{
	STUB(0x00484290);
	return 0;
}
