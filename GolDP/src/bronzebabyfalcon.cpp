#include "bronzebabyfalcon.h"

DECOMP_SIZE_ASSERT(BronzeBabyFalcon, 0x140) // based on constructor; not 100 % sure
DECOMP_SIZE_ASSERT(BronzeBabyFalcon::JasperRipple0x4, 0x4)

// FUNCTION: GOLDP 0x10028840
BronzeBabyFalcon::BronzeBabyFalcon()
{
	LegoS32 i;

	m_unk0x10 = 0;
	m_unk0x14 = 0;
	m_unk0x18 = 0;
	m_unk0x1c = 0;
	m_unk0x20 = 0;
	m_unk0x24 = 0;
	m_unk0x28 = 0;
	m_unk0x30 = 0;
	m_unk0x34 = 0;
	m_unk0x38 = 0;
	m_unk0x3c = 0;
	m_unk0x40 = 0;
	m_unk0x44 = 0;
	m_nextDrawStateRenderer = NULL;
	m_unk0x0c = 0;
	m_unk0x04 = 0;
	m_unk0x0a = 0;

	for (i = 0; i < sizeOfArray(m_unk0x4c); i++) {
		m_unk0x4c[i] = 0;
	}

	m_unk0x11c = 0;
	m_unk0x120 = 0;

	for (i = 0; i < sizeOfArray(m_unk0x124); i++) {
		m_unk0x124[i] = 0;
	}

	m_unk0x124[0] = 0;
}

// STUB: GOLDP 0x100288f0
BronzeBabyFalcon::~BronzeBabyFalcon()
{
	STUB(0x100288b0);
}

// STUB: GOLDP 0x10028980
void BronzeBabyFalcon::VTable0x04()
{
	STUB(0x10028980);
}

// STUB: GOLDP 0x10028a10
void BronzeBabyFalcon::VTable0x00()
{
	STUB(0x10028a10);
}

// STUB: GOLDP 0x10028c50
void BronzeBabyFalcon::VTable0x0c(undefined4, undefined4, undefined4)
{
	STUB(0x10028c50);
}

// STUB: GOLDP 0x10029500
void BronzeBabyFalcon::VTable0xa4()
{
	STUB(0x10029500);
}

// STUB: GOLDP 0x10029680
void BronzeBabyFalcon::VTable0xa0()
{
	STUB(0x10029680);
}

// STUB: GOLDP 0x10029840
void BronzeBabyFalcon::VTable0xa8()
{
	STUB(0x10029840);
}

// STUB: GOLDP 0x10029850
void BronzeBabyFalcon::VTable0xb8()
{
	STUB(0x10029850);
}

// STUB: GOLDP 0x10029870
void BronzeBabyFalcon::VTable0xbc()
{
	STUB(0x10029870);
}

// STUB: GOLDP 0x10029880
void BronzeBabyFalcon::VTable0xc0()
{
	STUB(0x10029880);
}

// STUB: GOLDP 0x100298a0
void BronzeBabyFalcon::VTable0xc4()
{
	STUB(0x100298a0);
}

// STUB: GOLDP 0x100298b0
void BronzeBabyFalcon::VTable0x28()
{
	STUB(0x100298b0);
}

// STUB: GOLDP 0x100298d0
void BronzeBabyFalcon::VTable0x2c(undefined4)
{
	STUB(0x100298d0);
}

// STUB: GOLDP 0x100298f0
void BronzeBabyFalcon::VTable0x30(undefined4)
{
	STUB(0x100298f0);
}

// STUB: GOLDP 0x10029930
void BronzeBabyFalcon::VTable0x44()
{
	STUB(0x10029930);
}

// STUB: GOLDP 0x10029940
void BronzeBabyFalcon::VTable0x48()
{
	STUB(0x10029940);
}

// STUB: GOLDP 0x10029960
void BronzeBabyFalcon::VTable0x58()
{
	STUB(0x10029960);
}

// STUB: GOLDP 0x10029970
void BronzeBabyFalcon::VTable0x24()
{
	MATCHING(0x10029970);
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void BronzeBabyFalcon::VTable0x38()
{
	// empty
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
void BronzeBabyFalcon::VTable0x34(LegoS32, const LegoFloat*)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
void BronzeBabyFalcon::VTable0xec(undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void BronzeBabyFalcon::VTable0xf4()
{
	// empty
}

// FUNCTION: GOLDP 0x100016f0 FOLDED
LegoBool32 BronzeBabyFalcon::VTable0x110() const
{
	MATCHING(0x100016f0);
	return FALSE;
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
void BronzeBabyFalcon::VTable0xac(undefined4, undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
void BronzeBabyFalcon::VTable0xb0(undefined4, undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x100294f0 FOLDED
void BronzeBabyFalcon::VTable0x8c(undefined4, undefined4, undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x100294f0 FOLDED
void BronzeBabyFalcon::VTable0x88(undefined4, undefined4, undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x100294f0 FOLDED
void BronzeBabyFalcon::VTable0x9c(undefined4, undefined4, undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x100294f0 FOLDED
void BronzeBabyFalcon::VTable0x98(undefined4, undefined4, undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void BronzeBabyFalcon::VTable0x60()
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void BronzeBabyFalcon::VTable0xc8()
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void BronzeBabyFalcon::VTable0xcc()
{
	// empty
}

// STUB: GOLDP 0x10029920 FOLDED
void BronzeBabyFalcon::VTable0x40()
{
	// empty
}

// FUNCTION: GOLDP 0x10029950 FOLDED
undefined4 BronzeBabyFalcon::VTable0x4c(undefined4, undefined4)
{
	return 0;
}

// STUB: GOLDP 0x1002c020 FOLDED
void BronzeBabyFalcon::VTable0x3c(undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
void BronzeBabyFalcon::VTable0x50(undefined4)
{
	// empty
}
