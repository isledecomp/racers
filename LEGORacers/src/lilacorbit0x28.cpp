#include "lilacorbit0x28.h"

DECOMP_SIZE_ASSERT(LilacOrbit0x28, 0x28)
DECOMP_SIZE_ASSERT(LilacOrbit0x28::TransformPayload0x20, 0x20)

// FUNCTION: LEGORACERS 0x00411a40
LilacOrbit0x28::LilacOrbit0x28()
{
	m_unk0x04 = 0;
	m_unk0x08 = 0;
	m_unk0x0c = 0;
	m_unk0x1c = 0;
	m_unk0x20 = 0;
	m_unk0x24 = 0;
	m_unk0x10 = 0;
	m_unk0x14 = 0;
	m_unk0x18 = 0;
}

// STUB: LEGORACERS 0x00411a70
void LilacOrbit0x28::VTable0x10(undefined4)
{
	STUB(0x00411a70);
}

// STUB: LEGORACERS 0x00411ae0
void LilacOrbit0x28::VTable0x0c(undefined4)
{
	STUB(0x00411ae0);
}

// STUB: LEGORACERS 0x00411b50
void LilacOrbit0x28::VTable0x14(undefined4, undefined4)
{
	STUB(0x00411b50);
}

// STUB: LEGORACERS 0x00411b90
void LilacOrbit0x28::VTable0x18(undefined4)
{
	STUB(0x00411b90);
}

// FUNCTION: LEGORACERS 0x00411c30
void LilacOrbit0x28::VTable0x04(LegoFloat* p_unk0x04)
{
	p_unk0x04[0] = m_unk0x04;
	p_unk0x04[1] = m_unk0x08;
	p_unk0x04[2] = m_unk0x0c;
}

// STUB: LEGORACERS 0x00411c50
void LilacOrbit0x28::VTable0x08(LegoFloat*)
{
	STUB(0x00411c50);
}

// FUNCTION: LEGORACERS 0x00411c90
void LilacOrbit0x28::VTable0x00()
{
	m_unk0x10 = 0;
	m_unk0x0c = 0;
	m_unk0x08 = 0;
	m_unk0x04 = 0;
}

// FUNCTION: LEGORACERS 0x00411cf0
void LilacOrbit0x28::VTable0x2c(LegoFloat* p_unk0x04, LegoFloat* p_unk0x08)
{
	p_unk0x08[0] = m_unk0x04 + p_unk0x04[0];
	p_unk0x08[1] = m_unk0x08 + p_unk0x04[1];
	p_unk0x08[2] = m_unk0x0c + p_unk0x04[2];
}

// FUNCTION: LEGORACERS 0x00411d20
void LilacOrbit0x28::VTable0x30(LegoFloat* p_unk0x04, LegoFloat* p_unk0x08)
{
	p_unk0x08[0] = p_unk0x04[0] - m_unk0x04;
	p_unk0x08[1] = p_unk0x04[1] - m_unk0x08;
	p_unk0x08[2] = p_unk0x04[2] - m_unk0x0c;
}

// FUNCTION: LEGORACERS 0x00411d50 FOLDED
void LilacOrbit0x28::VTable0x34(LegoFloat* p_unk0x04, LegoFloat* p_unk0x08)
{
	p_unk0x08[0] = p_unk0x04[0];
	p_unk0x08[1] = p_unk0x04[1];
	p_unk0x08[2] = p_unk0x04[2];
}

// FUNCTION: LEGORACERS 0x00411d50 FOLDED
void LilacOrbit0x28::VTable0x38(LegoFloat* p_unk0x04, LegoFloat* p_unk0x08)
{
	p_unk0x08[0] = p_unk0x04[0];
	p_unk0x08[1] = p_unk0x04[1];
	p_unk0x08[2] = p_unk0x04[2];
}

// FUNCTION: LEGORACERS 0x00411d70
void LilacOrbit0x28::VTable0x48(LegoFloat* p_unk0x04, LegoFloat* p_unk0x08)
{
	p_unk0x04[0] = 1.0f;
	p_unk0x04[1] = 0;
	p_unk0x04[2] = 0;
	p_unk0x08[0] = 0;
	p_unk0x08[1] = 0;
	p_unk0x08[2] = 1.0f;
}

// FUNCTION: LEGORACERS 0x00411da0
void LilacOrbit0x28::VTable0x44(LegoFloat* p_unk0x04)
{
	p_unk0x04[0] = 1.0f;
	p_unk0x04[1] = 0;
	p_unk0x04[2] = 0;
	p_unk0x04[3] = 0;
	p_unk0x04[4] = 1.0f;
	p_unk0x04[5] = 0;
	p_unk0x04[6] = 0;
	p_unk0x04[7] = 0;
	p_unk0x04[8] = 1.0f;
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void LilacOrbit0x28::VTable0x28()
{
}

// FUNCTION: LEGORACERS 0x0044e7e0 FOLDED
LegoBool32 LilacOrbit0x28::VTable0x20()
{
	return FALSE;
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void LilacOrbit0x28::VTable0x1c(WhiteFalcon0x140*)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void LilacOrbit0x28::VTable0x24(TransformPayload0x20*)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void LilacOrbit0x28::VTable0x3c(LegoFloat*)
{
}

// FUNCTION: LEGORACERS 0x0046c9f0 FOLDED
void LilacOrbit0x28::VTable0x40(LegoFloat*, LegoFloat*)
{
}
