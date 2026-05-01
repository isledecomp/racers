#include "amberlens0x344.h"

#include "bronzefalcon0xc8770.h"

DECOMP_SIZE_ASSERT(AmberLens0x344, 0x344)

// FUNCTION: GOLDP 0x10001ea0
AmberLens0x344::AmberLens0x344()
{
	m_unk0x04 = &m_unk0x120;
	m_unk0x340 = NULL;
}

// FUNCTION: GOLDP 0x10001f00
AmberLens0x344::~AmberLens0x344()
{
	if (m_unk0x340) {
		m_unk0x340->VTable0x24();
	}
}

// STUB: GOLDP 0x10001f60
void AmberLens0x344::FUN_10001f60(undefined*)
{
	// TODO
	STUB(0x10001f60);
}

// STUB: GOLDP 0x10002060
void AmberLens0x344::VTable0x28()
{
	STUB(0x10002060);
}

// STUB: GOLDP 0x10002160
void AmberLens0x344::VTable0x00()
{
	STUB(0x10002160);
}

// STUB: GOLDP 0x10002370
void AmberLens0x344::VTable0x04()
{
	STUB(0x10002370);
}

// STUB: GOLDP 0x10002430
void AmberLens0x344::VTable0x14()
{
	STUB(0x10002430);
}

// STUB: GOLDP 0x100024d0
void AmberLens0x344::VTable0x18()
{
	STUB(0x100024d0);
}

// STUB: GOLDP 0x10002570
void AmberLens0x344::VTable0x1c()
{
	STUB(0x10002570);
}

// STUB: GOLDP 0x10002630
void AmberLens0x344::VTable0x10()
{
	STUB(0x10002630);
}

// STUB: GOLDP 0x10002660
void AmberLens0x344::VTable0x0c()
{
	STUB(0x10002660);
}

// STUB: GOLDP 0x10002770
void AmberLens0x344::VTable0x20(undefined4, undefined4)
{
	STUB(0x10002770);
}
