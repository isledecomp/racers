#include "opalhaven0xf4.h"

DECOMP_SIZE_ASSERT(OpalHaven0xf4, 0xf4)

// FUNCTION: LEGORACERS 0x0040d530
OpalHaven0xf4::OpalHaven0xf4()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0040d550
void OpalHaven0xf4::FUN_0040d550(
	IGdbModel0x40* p_model,
	WhiteFalconNode0x18* p_node,
	CmbModelPart0x34* p_modelParts,
	LegoFloat p_unk0x10
)
{
	SilverHollow0xb8::VTable0x50(p_model, p_unk0x10);
	m_nodes[0] = p_node;
	m_modelParts[0] = p_modelParts;
}

// FUNCTION: LEGORACERS 0x0040d5d0
void OpalHaven0xf4::VTable0x54()
{
	SilverHollow0xb8::VTable0x54();
	Reset();
}

// FUNCTION: LEGORACERS 0x0040d5f0
void OpalHaven0xf4::Reset()
{
	for (LegoS32 i = 0; i < sizeOfArray(m_nodes); i++) {
		m_nodes[i] = NULL;
		m_modelParts[i] = NULL;
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

// FUNCTION: LEGORACERS 0x0040d650
void OpalHaven0xf4::FUN_0040d650()
{
	for (LegoS32 i = 0; i < sizeOfArray(m_unk0x9c); i++) {
		m_unk0x9c[i] = -1;
	}
}

// STUB: LEGORACERS 0x0040d670
void OpalHaven0xf4::VTable0x5c(LegoU32)
{
	STUB(0x0040d670);
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

// FUNCTION: LEGORACERS 0x0040e480
WhiteFalconNode0x18* OpalHaven0xf4::VTable0x58(LegoU32 p_arg1)
{
	return m_nodes[p_arg1];
}
