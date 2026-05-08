#include "jadeorbit0x220.h"

DECOMP_SIZE_ASSERT(JadeOrbit0x220, 0x220)

// FUNCTION: GOLDP 0x10002890
JadeOrbit0x220::JadeOrbit0x220()
{
	m_unk0x50 = 1.0f;
	m_unk0x54 = 0.0f;
	m_unk0x58 = 0.0f;
	m_unk0x5c = 0.0f;
	m_unk0x60 = 0.0f;
	m_unk0x64 = 1.0f;
	m_unk0x68 = 0.0f;
	m_unk0x6c = 0.0f;
	m_unk0x70 = 0.0f;
	m_unk0x74 = 0.0f;
	m_unk0x78 = 1.0f;
	m_unk0x7c = 0.0f;
	m_unk0x80 = 0.0f;
	m_unk0x84 = 0.0f;
	m_unk0x88 = 0.0f;
	m_unk0x8c = 1.0f;
	m_unk0x94 = 0.0f;
	m_unk0x98 = 0.0f;
	m_unk0x9c = 0.0f;
	m_unk0xa0 = 0.0f;
	m_unk0xa8 = 0.0f;
	m_unk0xac = 0.0f;
	m_unk0xb0 = 0.0f;
	m_unk0xb4 = 0.0f;
	m_unk0xbc = 0.0f;
	m_unk0xc0 = 0.0f;
	m_unk0xc4 = 0.0f;
	m_unk0xc8 = 0.0f;
	m_unk0x14 = 0.0f;
	m_unk0x18 = 0.0f;
	m_unk0x1c = 0.0f;
	m_unk0x20 = 0.0f;
	m_unk0x28 = 0.0f;
	m_unk0x2c = 0.0f;
	m_unk0x30 = 0.0f;
	m_unk0x34 = 0.0f;
	m_unk0x3c = 0.0f;
	m_unk0x40 = 0.0f;
	m_unk0x44 = 0.0f;
	m_unk0x48 = 0.0f;
	m_unk0x90 = 1.0f;
	m_unk0xa4 = 1.0f;
	m_unk0xb8 = 1.0f;
	m_unk0xcc = 1.0f;
	m_unk0x10 = 1.0f;
	m_unk0x24 = 1.0f;
	m_unk0x38 = 1.0f;
	m_unk0x4c = 1.0f;
}

// FUNCTION: GOLDP 0x10002980
void JadeOrbit0x220::VTable0x18(FloatyVec0xc* p_right, FloatyVec0xc* p_forward, FloatyVec0xc* p_up)
{
	p_up->m_x = m_unk0x10;
	p_up->m_y = m_unk0x14;
	p_up->m_z = m_unk0x18;
	p_forward->m_x = m_unk0x20;
	p_forward->m_y = m_unk0x24;
	p_forward->m_z = m_unk0x28;
	p_right->m_x = m_unk0x30;
	p_right->m_y = m_unk0x34;
	p_right->m_z = m_unk0x38;
}

// FUNCTION: GOLDP 0x100029d0
void JadeOrbit0x220::VTable0x1c(FloatyVec0xc* p_right, FloatyVec0xc* p_forward)
{
	p_forward->m_x = m_unk0x20;
	p_forward->m_y = m_unk0x24;
	p_forward->m_z = m_unk0x28;
	p_right->m_x = m_unk0x30;
	p_right->m_y = m_unk0x34;
	p_right->m_z = m_unk0x38;
}

// FUNCTION: GOLDP 0x10002a00
void JadeOrbit0x220::VTable0x20(FloatyVec0xc* p_up, FloatyVec0xc* p_right)
{
	p_up->m_x = m_unk0x10;
	p_up->m_y = m_unk0x14;
	p_up->m_z = m_unk0x18;
	p_right->m_x = m_unk0x30;
	p_right->m_y = m_unk0x34;
	p_right->m_z = m_unk0x38;
}

// STUB: GOLDP 0x10002a30
void JadeOrbit0x220::VTable0x24(FloatyVec0xc*, FloatyVec0xc*)
{
	STUB(0x10002a30);
}

// STUB: GOLDP 0x10002b20
void JadeOrbit0x220::VTable0x28()
{
	STUB(0x10002b20);
}

// STUB: GOLDP 0x10002c10
void JadeOrbit0x220::VTable0x04()
{
	STUB(0x10002c10);
}

// STUB: GOLDP 0x10002c90
void JadeOrbit0x220::VTable0x0c()
{
	STUB(0x10002c90);
}

// STUB: GOLDP 0x10002d00
void JadeOrbit0x220::VTable0x08(undefined4, undefined4)
{
	STUB(0x10002d00);
}

// STUB: GOLDP 0x10002dc0
void JadeOrbit0x220::VTable0x10()
{
	STUB(0x10002dc0);
}

// STUB: GOLDP 0x10002e30
void JadeOrbit0x220::VTable0x2c()
{
	STUB(0x10002e30);
}

// FUNCTION: GOLDP 0x10002f50
void JadeOrbit0x220::VTable0x30(FloatyVec0xc* p_up)
{
	p_up->m_x = m_unk0x10;
	p_up->m_y = m_unk0x14;
	p_up->m_z = m_unk0x18;
}

// FUNCTION: GOLDP 0x10002f70
void JadeOrbit0x220::VTable0x34(FloatyVec0xc* p_forward)
{
	p_forward->m_x = m_unk0x20;
	p_forward->m_y = m_unk0x24;
	p_forward->m_z = m_unk0x28;
}

// FUNCTION: GOLDP 0x10002f90
void JadeOrbit0x220::VTable0x38(FloatyVec0xc* p_right)
{
	p_right->m_x = m_unk0x30;
	p_right->m_y = m_unk0x34;
	p_right->m_z = m_unk0x38;
}

// STUB: GOLDP 0x10002fb0
void JadeOrbit0x220::VTable0x3c()
{
	STUB(0x10002fb0);
}

// FUNCTION: GOLDP 0x10002fe0
void JadeOrbit0x220::VTable0x40(FloatyVec0xc* p_position)
{
	p_position->m_x = m_unk0x40;
	p_position->m_y = m_unk0x44;
	p_position->m_z = m_unk0x48;
}

// FUNCTION: GOLDP 0x10003000
void JadeOrbit0x220::VTable0x44(FloatyVec0xc* p_position)
{
	m_unk0x40 = p_position->m_x;
	m_unk0x44 = p_position->m_y;
	m_unk0x48 = p_position->m_z;
}

// STUB: GOLDP 0x10003020
void JadeOrbit0x220::VTable0x14()
{
	STUB(0x10003020);
}

// STUB: GOLDP 0x10003080
void JadeOrbit0x220::VTable0x48()
{
	STUB(0x10003080);
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void JadeOrbit0x220::VTable0x00()
{
	// empty
}
