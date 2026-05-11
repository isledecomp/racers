#include "gdbvertexarraytypeone0x1c.h"

#include "color.h"
#include "golerror.h"
#include "golfileparser.h"
#include "golmath.h"

// FUNCTION: GOLDP 0x10005f90
GdbVertexArrayTypeOne0x1c::GdbVertexArrayTypeOne0x1c()
{
	m_unk0x06 = 1;
}

// FUNCTION: GOLDP 0x10005fc0
void GdbVertexArrayTypeOne0x1c::VTable0x08(GolFileParser& p_parser)
{
	LegoU32 i;
	if (m_unk0x04 != 0) {
		VTable0x0c();
	}
	p_parser.ReadLeftBracket();
	m_unk0x04 = p_parser.ReadInteger();
	if (m_unk0x04 == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	p_parser.ReadRightBracket();
	p_parser.ReadLeftCurly();
	m_unk0x08 = new GolVec3[m_unk0x04];
	if (m_unk0x08 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	m_unk0x0c = new GolVec2[m_unk0x04];
	if (m_unk0x0c == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	m_unk0x10 = new LegoU32[m_unk0x04];
	if (m_unk0x10 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	for (i = 0; i < m_unk0x04; i++) {
		m_unk0x08[i].m_x = p_parser.ReadFloat();
		m_unk0x08[i].m_y = p_parser.ReadFloat();
		m_unk0x08[i].m_z = p_parser.ReadFloat();
		m_unk0x0c[i].m_x = p_parser.ReadFloat();
		m_unk0x0c[i].m_y = p_parser.ReadFloat();
		LegoU32 red = p_parser.ReadInteger() & 0xff;
		LegoU32 grn = p_parser.ReadInteger() & 0xff;
		LegoU32 blu = p_parser.ReadInteger() & 0xff;
		LegoU32 alp = p_parser.ReadInteger() & 0xff;
		m_unk0x10[i] = (alp << 24) | (red << 16) | (grn << 8) | (blu << 0);
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x10006150 FOLDED
void GdbVertexArrayTypeOne0x1c::VTable0x04(LegoU16 p_count)
{
	LegoU32 i;
	if (m_unk0x04 != 0) {
		VTable0x0c();
	}
	m_unk0x04 = p_count;
	m_unk0x08 = new GolVec3[m_unk0x04];
	if (m_unk0x08 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	m_unk0x0c = new GolVec2[m_unk0x04];
	if (m_unk0x0c == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	m_unk0x10 = new LegoU32[m_unk0x04];
	if (m_unk0x10 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	for (i = 0; i < m_unk0x04; i++) {
		m_unk0x0c[i].m_x = 0.0f;
		m_unk0x0c[i].m_y = 0.0f;
		m_unk0x10[i] = ARGBU32(0xff, 0xff, 0xff, 0xff);
	}
}

// FUNCTION: GOLDP 0x10006210 FOLDED
void GdbVertexArrayTypeOne0x1c::VTable0x18(LegoU32 p_index, GolVec2* p_dest)
{
	p_dest->m_x = m_unk0x0c[p_index].m_x;
	p_dest->m_y = m_unk0x0c[p_index].m_y;
}

// FUNCTION: GOLDP 0x10016ea0 FOLDED
void GdbVertexArrayTypeOne0x1c::VTable0x20(LegoU32 p_index, ColorRGBA* p_dest)
{
	p_dest->m_red = m_unk0x10[p_index] >> 16;
	p_dest->m_grn = m_unk0x10[p_index] >> 8;
	p_dest->m_blu = m_unk0x10[p_index] >> 0;
	p_dest->m_alp = m_unk0x10[p_index] >> 24;
}

// FUNCTION: GOLDP 0x100158f0 FOLDED
void GdbVertexArrayTypeOne0x1c::VTable0x28(LegoU32 p_index, const GolVec2& p_arg2)
{
	m_unk0x0c[p_index].m_x = p_arg2.m_x;
	m_unk0x0c[p_index].m_y = p_arg2.m_y;
}

// FUNCTION: GOLDP 0x10006250 FOLDED
void GdbVertexArrayTypeOne0x1c::VTable0x30(LegoU32 p_index, const ColorRGBA& p_arg2)
{
	m_unk0x10[p_index] = ARGBU32(p_arg2.m_alp, p_arg2.m_red, p_arg2.m_grn, p_arg2.m_blu);
}
