#include "corundumpeak0x14.h"

#include "golstring.h"

DECOMP_SIZE_ASSERT(CorundumPeak0x14, 0x14)

// STUB: LEGORACERS 0x0044e220
CorundumPeak0x14::CorundumPeak0x14()
{
	// TODO
	STUB(0x44e220);
}

// STUB: LEGORACERS 0x0044e240
CorundumPeak0x14::~CorundumPeak0x14()
{
	// TODO
	STUB(0x44e240);
}

// FUNCTION: LEGORACERS 0x0044e500
LegoS32 CorundumPeak0x14::FUN_0044e500(GolString* p_string, LegoU16 p_index)
{
	if (!m_unk0x08) {
		return 0;
	}
	else if (p_index > m_unk0x10) {
		return 0;
	}

	return p_string->CopyFromBufSelection(&m_unk0x08[m_unk0x0c[p_index]], 0);
}

// STUB: LEGORACERS 0x004a12e0
CorundumPeak0x14* FUN_004a12e0(undefined4 p_count)
{
	// TODO
	STUB(0x4a12e0);
	return new CorundumPeak0x14[p_count];
}
