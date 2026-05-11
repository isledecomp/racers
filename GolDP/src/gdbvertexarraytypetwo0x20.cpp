#include "gdbvertexarraytypetwo0x20.h"

#include "color.h"
#include "golmath.h"

// FUNCTION: GOLDP 0x10016b80
GdbVertexArrayTypeTwo0x20::GdbVertexArrayTypeTwo0x20()
{
	m_unk0x1c = 0;
	m_unk0x06 = 2;
}

// STUB: GOLDP 0x10016ba0
void GdbVertexArrayTypeTwo0x20::VTable0x08(GolFileParser& p_parser)
{
	// TODO
	STUB(0x10016ba0);
}

// STUB: GOLDP 0x10016d30
void GdbVertexArrayTypeTwo0x20::VTable0x04(LegoU16 p_count)
{
	// TODO
	STUB(0x10016d30);
}

// FUNCTION: GOLDP 0x10016e40
void GdbVertexArrayTypeTwo0x20::VTable0x0c()
{
	if (m_unk0x1c != NULL) {
		delete[] m_unk0x1c;
		m_unk0x1c = NULL;
	}
	GdbCommonVertexArray0x1c::VTable0x0c();
}

// FUNCTION: GOLDP 0x10006210 FOLDED
void GdbVertexArrayTypeTwo0x20::VTable0x18(LegoU32 p_index, GolVec2* p_dest)
{
	p_dest->m_x = m_unk0x0c[p_index].m_x;
	p_dest->m_y = m_unk0x0c[p_index].m_y;
}

// FUNCTION: GOLDP 0x10016e70 FOLDED
void GdbVertexArrayTypeTwo0x20::VTable0x1c(LegoU32 p_index, GolVec3* p_dest)
{
	p_dest->m_x = m_unk0x1c[p_index].m_x;
	p_dest->m_y = m_unk0x1c[p_index].m_y;
	p_dest->m_z = m_unk0x1c[p_index].m_z;
}

// FUNCTION: GOLDP 0x10016ea0 FOLDED
void GdbVertexArrayTypeTwo0x20::VTable0x20(LegoU32 p_index, ColorRGBA* p_dest)
{
	p_dest->m_red = m_unk0x10[p_index] >> 16;
	p_dest->m_grn = m_unk0x10[p_index] >> 8;
	p_dest->m_blu = m_unk0x10[p_index] >> 0;
	p_dest->m_alp = m_unk0x10[p_index] >> 24;
}

// FUNCTION: GOLDP 0x10016ee0
void GdbVertexArrayTypeTwo0x20::VTable0x2c(LegoU32 p_index, const GolVec3& p_arg2)
{
	m_unk0x1c[p_index].m_x = p_arg2.m_x;
	m_unk0x1c[p_index].m_y = p_arg2.m_y;
	m_unk0x1c[p_index].m_z = p_arg2.m_z;
}

// FUNCTION: GOLDP 0x100158f0 FOLDED
void GdbVertexArrayTypeTwo0x20::VTable0x28(LegoU32 p_index, const GolVec2& p_arg2)
{
	m_unk0x0c[p_index].m_x = p_arg2.m_x;
	m_unk0x0c[p_index].m_y = p_arg2.m_y;
}

// FUNCTION: GOLDP 0x10006250 FOLDED
void GdbVertexArrayTypeTwo0x20::VTable0x30(LegoU32 p_index, const ColorRGBA& p_arg2)
{
	m_unk0x10[p_index] = ARGBU32(p_arg2.m_alp, p_arg2.m_red, p_arg2.m_grn, p_arg2.m_blu);
}
