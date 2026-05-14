#include "gdbvertexarraytypetwo0x20.h"

#include "color.h"
#include "golerror.h"
#include "golfileparser.h"
#include "golmath.h"

DECOMP_SIZE_ASSERT(GdbVertexArrayTypeTwo0x20, 0x20)

// FUNCTION: GOLDP 0x10016b80
GdbVertexArrayTypeTwo0x20::GdbVertexArrayTypeTwo0x20()
{
	m_unk0x1c = 0;
	m_unk0x06 = 2;
}

// FUNCTION: GOLDP 0x10016ba0
void GdbVertexArrayTypeTwo0x20::VTable0x08(GolFileParser& p_parser)
{
	LegoU32 i;

	if (m_count != 0) {
		VTable0x0c();
	}

	p_parser.ReadLeftBracket();
	m_count = p_parser.ReadInteger();
	if (m_count == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	p_parser.ReadRightBracket();
	p_parser.ReadLeftCurly();

	m_unk0x08 = new GolVec3[m_count];
	if (m_unk0x08 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	m_unk0x0c = new GolVec2[m_count];
	if (m_unk0x0c == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	m_unk0x10 = new LegoU32[m_count];
	if (m_unk0x10 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	m_unk0x1c = new GolVec3[m_count];
	if (m_unk0x1c == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (i = 0; i < m_count; i++) {
		m_unk0x08[i].m_x = p_parser.ReadFloat();
		m_unk0x08[i].m_y = p_parser.ReadFloat();
		m_unk0x08[i].m_z = p_parser.ReadFloat();
		m_unk0x0c[i].m_x = p_parser.ReadFloat();
		m_unk0x0c[i].m_y = p_parser.ReadFloat();
		m_unk0x1c[i].m_x = p_parser.ReadFloat();
		m_unk0x1c[i].m_y = p_parser.ReadFloat();
		m_unk0x1c[i].m_z = p_parser.ReadFloat();
		m_unk0x10[i] = ARGBU32(0xff, 0xff, 0xff, 0xff);
	}

	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x10016d30
void GdbVertexArrayTypeTwo0x20::VTable0x04(LegoU16 p_count)
{
	LegoU32 i;

	if (m_count != 0) {
		VTable0x0c();
	}

	m_count = p_count;

	m_unk0x08 = new GolVec3[m_count];
	if (m_unk0x08 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	m_unk0x0c = new GolVec2[m_count];
	if (m_unk0x0c == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	m_unk0x1c = new GolVec3[m_count];
	if (m_unk0x1c == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	m_unk0x10 = new LegoU32[m_count];
	if (m_unk0x10 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (i = 0; i < m_count; i++) {
		m_unk0x1c[i].m_x = 0.0f;
		m_unk0x1c[i].m_y = 0.0f;
		m_unk0x1c[i].m_z = 1.0f;
		m_unk0x0c[i].m_x = 0.0f;
		m_unk0x0c[i].m_y = 0.0f;
		m_unk0x10[i] = ARGBU32(0xff, 0xff, 0xff, 0xff);
	}
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
void GdbVertexArrayTypeTwo0x20::VTable0x18(LegoU32 p_index, GolVec2* p_dest) const
{
	p_dest->m_x = m_unk0x0c[p_index].m_x;
	p_dest->m_y = m_unk0x0c[p_index].m_y;
}

// FUNCTION: GOLDP 0x10016e70 FOLDED
void GdbVertexArrayTypeTwo0x20::VTable0x1c(LegoU32 p_index, GolVec3* p_dest) const
{
	p_dest->m_x = m_unk0x1c[p_index].m_x;
	p_dest->m_y = m_unk0x1c[p_index].m_y;
	p_dest->m_z = m_unk0x1c[p_index].m_z;
}

// FUNCTION: GOLDP 0x10016ea0 FOLDED
void GdbVertexArrayTypeTwo0x20::VTable0x20(LegoU32 p_index, ColorRGBA* p_dest) const
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
