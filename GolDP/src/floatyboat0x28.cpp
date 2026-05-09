#include "floatyboat0x28.h"

DECOMP_SIZE_ASSERT(FloatyBoat0x28, 0x28)

// STUB: GOLDP 0x100016f0 FOLDED
undefined4 FloatyBoat0x28::VTable0x20()
{
	// TODO
	MATCHING(0x100016f0);
	return 0;
}

// FUNCTION: GOLDP 0x100284c0
FloatyBoat0x28::FloatyBoat0x28()
{
	m_v0.m_x = 0.0f;
	m_v0.m_y = 0.0f;
	m_v0.m_z = 0.0f;
	m_v2.m_x = 0.0f;
	m_v2.m_y = 0.0f;
	m_v2.m_z = 0.0f;
	m_v1.m_x = 0.0f;
	m_v1.m_y = 0.0f;
	m_v1.m_z = 0.0f;
}

// FUNCTION: GOLDP 0x100284f0
void FloatyBoat0x28::VTable0x10(LegoS32 p_arg)
{
	// GolVec3 t;
	if (m_v1.m_x < 0.0f) {
		VTable0x00();
	}

	m_v0 += m_v2 * static_cast<LegoFloat>(p_arg);

	m_v1.m_y = m_v0.m_x - m_v1.m_x;
	m_v1.m_z = m_v0.m_x + m_v1.m_x;
}

// FUNCTION: GOLDP 0x10028560
void FloatyBoat0x28::VTable0x0c(LegoFloat p_v)
{
	// GolVec3 t;
	if (m_v1.m_x < 0.0f) {
		VTable0x00();
	}

	m_v0 += m_v2 * p_v;

	m_v1.m_y = m_v0.m_x - m_v1.m_x;
	m_v1.m_z = m_v0.m_x + m_v1.m_x;
}

// STUB: GOLDP 0x100285d0
void FloatyBoat0x28::VTable0x14(GolVec3* p_arg1, undefined4*)
{
	if (m_v1.m_x < 0.0f) {
		VTable0x00();
	}
	// TODO
	STUB(0x100285d0);
}

// STUB: GOLDP 0x10028610
LegoS32 FloatyBoat0x28::VTable0x18()
{
	if (m_v1.m_x < 0.0f) {
		VTable0x00();
	}
	// TODO
	STUB(0x10028610);
	return 0;
}

// FUNCTION: GOLDP 0x100286b0
void FloatyBoat0x28::VTable0x04(GolVec3* p_v) const
{
	p_v->m_x = m_v0.m_x;
	p_v->m_y = m_v0.m_y;
	p_v->m_z = m_v0.m_z;
}

// FUNCTION: GOLDP 0x100286d0
void FloatyBoat0x28::FUN_100286d0(GolVec3* p_v)
{
	if (m_v1.m_x < 0.0f) {
		VTable0x00();
	}
	p_v->m_x = m_v0.m_x;
	p_v->m_y = m_v0.m_y;
	p_v->m_z = m_v0.m_z;
}

// FUNCTION: GOLDP 0x10028700
void FloatyBoat0x28::VTable0x00()
{

	m_v1.m_x = 0.0f;
	m_v0.m_z = 0.0f;
	m_v0.m_y = 0.0f;
	m_v0.m_x = 0.0f;
}

// FUNCTION: GOLDP 0x10028710
LegoFloat FloatyBoat0x28::FUN_10028710()
{

	if (m_v1.m_x < 0.0f) {
		VTable0x00();
	}

	return m_v1.m_x;
}

// FUNCTION: GOLDP 0x10028730
void FloatyBoat0x28::VTable0x08(const GolVec3& p_v)
{
	m_v0.m_x = p_v.m_x;
	m_v0.m_y = p_v.m_y;
	m_v0.m_z = p_v.m_z;
	m_v1.m_y = m_v0.m_x - m_v1.m_x;
	m_v1.m_z = m_v1.m_x + m_v0.m_x;
}

// FUNCTION: GOLDP 0x10028760
void FloatyBoat0x28::VTable0x2c(const GolVec3& p_add, GolVec3* p_dest) const
{
	p_dest->m_x = m_v0.m_x + p_add.m_x;
	p_dest->m_y = m_v0.m_y + p_add.m_y;
	p_dest->m_z = m_v0.m_z + p_add.m_z;
}

// FUNCTION: GOLDP 0x10028790
void FloatyBoat0x28::VTable0x30(const GolVec3& p_add, GolVec3* p_dest) const
{
	p_dest->m_x = p_add.m_x - m_v0.m_x;
	p_dest->m_y = p_add.m_y - m_v0.m_y;
	p_dest->m_z = p_add.m_z - m_v0.m_z;
}

// FUNCTION: GOLDP 0x100287c0 FOLDED
void FloatyBoat0x28::VTable0x34(const GolVec3& p_src, GolVec3* p_dest)
{
	*p_dest = p_src;
}

// FUNCTION: GOLDP 0x100287c0 FOLDED
void FloatyBoat0x28::VTable0x38(const GolVec3& p_src, GolVec3* p_dest) const
{
	*p_dest = p_src;
}

// FUNCTION: GOLDP 0x100287e0
void FloatyBoat0x28::VTable0x48(GolVec3* p_v1, GolVec3* p_v2) const
{
	p_v1->m_x = 1.0f;
	p_v1->m_y = 0.0f;
	p_v1->m_z = 0.0f;
	p_v2->m_x = 0.0f;
	p_v2->m_y = 0.0f;
	p_v2->m_z = 1.0f;
}

// STUB: GOLDP 0x10028810
void FloatyBoat0x28::VTable0x44(undefined4*) const
{
	// TODO
	STUB(0x10028810);
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void FloatyBoat0x28::VTable0x28()
{
	// empty
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
void FloatyBoat0x28::VTable0x40(undefined4, undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
void FloatyBoat0x28::VTable0x1c(WhiteFalcon0x140*)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
void FloatyBoat0x28::VTable0x24(undefined4*)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
void FloatyBoat0x28::VTable0x3c(undefined4*)
{
	// empty
}
