#include "gdbvertexarraymistery0x1c.h"

#include "color.h"
#include "golmath.h"

// FUNCTION: GOLDP 0x100156d0
GdbVertexArrayMistery0x1c::GdbVertexArrayMistery0x1c()
{
	m_unk0x06 = 1;
}

// STUB: GOLDP 0x10006150 FOLDED
void GdbVertexArrayMistery0x1c::VTable0x04(LegoU16 p_count)
{
	// TODO
	STUB(0x10006150);
}

// STUB: GOLDP 0x100156f0
void GdbVertexArrayMistery0x1c::VTable0x08(GolFileParser& p_parser)
{
	// TODO
	STUB(0x100156f0);
}

// FUNCTION: GOLDP 0x10006210 FOLDED
void GdbVertexArrayMistery0x1c::VTable0x18(LegoU32 p_index, GolVec2* p_dest)
{
	p_dest->m_x = m_unk0x0c[p_index].m_x;
	p_dest->m_y = m_unk0x0c[p_index].m_y;
}

// FUNCTION: GOLDP 0x10015890
void GdbVertexArrayMistery0x1c::VTable0x20(LegoU32 p_index, ColorRGBA* p_dest)
{
	p_dest->m_red = 0xff;
	p_dest->m_grn = 0xff;
	p_dest->m_blu = 0xff;
	p_dest->m_alp = 0xff;
}

// FUNCTION: GOLDP 0x100158f0 FOLDED
void GdbVertexArrayMistery0x1c::VTable0x28(LegoU32 p_index, const GolVec2& p_arg2)
{
	m_unk0x0c[p_index].m_x = p_arg2.m_x;
	m_unk0x0c[p_index].m_y = p_arg2.m_y;
}
