#include "tealpulse0x24.h"

DECOMP_SIZE_ASSERT(TealPulse0x24, 0x24)

// FUNCTION: LEGORACERS 0x44c570
TealPulse0x24::TealPulse0x24()
{
	m_unk0x04 = 0;
	FUN_0044c5a0();
}

// FUNCTION: LEGORACERS 0x44c590
TealPulse0x24::~TealPulse0x24()
{
	VTable0x0c();
}

// FUNCTION: LEGORACERS 0x44c5a0
void TealPulse0x24::FUN_0044c5a0()
{
	m_unk0x20 = 0;
	m_unk0x08 = 0;
	m_unk0x0c = 0;
	m_unk0x10 = 0;
	m_unk0x14 = 0;
	m_unk0x1c = 0;
}

// STUB: LEGORACERS 0x44c5c0
void TealPulse0x24::VTable0x08(undefined4, undefined4)
{
	// TODO
	STUB(0x44c5c0);
}

// STUB: LEGORACERS 0x44c670
void TealPulse0x24::VTable0x0c()
{
	// TODO
	STUB(0x44c670);
}

// STUB: LEGORACERS 0x44c6e0
void TealPulse0x24::VTable0x00()
{
	// TODO
	STUB(0x44c6e0);
}

// STUB: LEGORACERS 0x44c880
undefined4* TealPulse0x24::VTable0x04(undefined4*, const LegoChar*)
{
	// TODO
	STUB(0x44c880);
	return NULL;
}
