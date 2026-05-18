#include "opalhaven0xf4.h"

DECOMP_SIZE_ASSERT(OpalHaven0xf4, 0xf4)

// FUNCTION: LEGORACERS 0x0040d530
OpalHaven0xf4::OpalHaven0xf4()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0040d5f0
void OpalHaven0xf4::Reset()
{
	for (LegoS32 i = 0; i < sizeOfArray(m_unk0x90); i++) {
		m_unk0x90[i] = 0;
		m_unk0xa8[i] = 0;
		m_unk0x9c[i] = 0xffffffff;
	}

	m_unk0xbc = 0;
	m_unk0x10 = -1.0f;
	m_unk0xb4 = 0;
	m_unk0xb8 = 0;
	m_unk0xd8 = 0;
	m_unk0xd0 = 0;
	m_unk0xd4 = 0;
	m_unk0xec = 0;
	m_unk0xf0 = 0;
}

// STUB: LEGORACERS 0x0040dad0
void OpalHaven0xf4::FUN_0040dad0(undefined2)
{
	STUB(0x0040dad0);
}

// STUB: LEGORACERS 0x0040db80
void OpalHaven0xf4::FUN_0040db80(undefined4, undefined4, LegoFloat, undefined4, undefined4, undefined4)
{
	STUB(0x0040db80);
}

// STUB: LEGORACERS 0x0040dd60
void OpalHaven0xf4::VTable0x10(undefined4)
{
	STUB(0x0040dd60);
}

// STUB: LEGORACERS 0x0040e0b0
void OpalHaven0xf4::VTable0x4c(undefined4)
{
	STUB(0x0040e0b0);
}

// STUB: LEGORACERS 0x0040e270
void OpalHaven0xf4::VTable0x14(undefined4, undefined4)
{
	STUB(0x0040e270);
}

// STUB: LEGORACERS 0x0040e360
LegoBool32 OpalHaven0xf4::FUN_0040e360()
{
	STUB(0x0040e360);
	return FALSE;
}
