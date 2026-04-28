#include "bronzedunebag0xc.h"

#include "decomp.h"

// FUNCTION: GOLDP 0x1002a090
BronzeDuneBag0xc::BronzeDuneBag0xc()
{
	m_unk0x4 = NULL;
	m_unk0x8 = 0;
}

// FUNCTION: GOLDP 0x1002a0f0
BronzeDuneBag0xc::~BronzeDuneBag0xc()
{
	m_unk0x8 = 0;
	if (m_unk0x4 != NULL) {
		delete[] m_unk0x4;
		m_unk0x4 = NULL;
	}
}

// STUB: GOLDP 0x1002a120
void BronzeDuneBag0xc::FUN_1002a120(undefined4)
{
	// TODO
	STUB(0x1002a120);
}

// STUB: GOLDP 0x1002a1b0
void BronzeDuneBag0xc::FUN_1002a1b0()
{
	// TODO
	STUB(0x1002a1b0);
}

// STUB: GOLDP 0x1002a1e0
void BronzeDuneBag0xc::VTable0x00(undefined4*, undefined4, undefined4)
{
	// TODO
	STUB(0x1002a1e0);
}

// STUB: GOLDP 0x1002a230
void BronzeDuneBag0xc::VTable0x08(undefined4*, undefined4, undefined4)
{
	// TODO
	STUB(0x1002a230);
}

// STUB: GOLDP 0x1002a290
void BronzeDuneBag0xc::VTable0x0c(undefined4*, undefined4)
{
	// TODO
	STUB(0x1002a290);
}

// STUB: GOLDP 0x1002a2d0
void BronzeDuneBag0xc::VTable0x04(undefined4*)
{
	// TODO
	STUB(0x1002a2d0);
}

// STUB: GOLDP 0x1002a300
void BronzeDuneBag0xc::VTable0x10(undefined4*)
{
	// TODO
	STUB(0x1002a300);
}

// STUB: GOLDP 0x100016f0 FOLDED
undefined4 BronzeDuneBag0xc::VTable0x14()
{
	MATCHING(0x100016f0);
	return 0;
}

// STUB: GOLDP 0x1002a350 FOLDED
undefined4 BronzeDuneBag0xc::VTable0x18()
{
	return m_unk0x8;
}

// STUB: GOLDP 0x1002a350 FOLDED
undefined4 BronzeDuneBag0xc::VTable0x1c()
{
	return m_unk0x8;
}
