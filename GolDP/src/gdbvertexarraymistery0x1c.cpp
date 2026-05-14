#include "gdbvertexarraymistery0x1c.h"

#include "color.h"
#include "golerror.h"
#include "golfileparser.h"
#include "golmath.h"

DECOMP_SIZE_ASSERT(GdbVertexArrayMistery0x1c, 0x1c)

// FUNCTION: GOLDP 0x100156d0
GdbVertexArrayMistery0x1c::GdbVertexArrayMistery0x1c()
{
	m_unk0x06 = 1;
}

// FUNCTION: GOLDP 0x10006150 FOLDED
void GdbVertexArrayMistery0x1c::VTable0x04(LegoU16 p_count)
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
	m_unk0x10 = new LegoU32[m_count];
	if (m_unk0x10 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (i = 0; i < m_count; i++) {
		m_unk0x0c[i].m_x = 0.0f;
		m_unk0x0c[i].m_y = 0.0f;
		m_unk0x10[i] = ARGBU32(0xff, 0xff, 0xff, 0xff);
	}
}

// FUNCTION: GOLDP 0x100156f0
void GdbVertexArrayMistery0x1c::VTable0x08(GolFileParser& p_parser)
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

	::memset(m_unk0x08, 0, sizeof(GolVec3) * m_count);
	::memset(m_unk0x0c, 0, sizeof(GolVec2) * m_count);

	for (i = 0; i < m_count; i++) {
		m_unk0x08[i].m_x = p_parser.ReadFloat();
		m_unk0x08[i].m_y = p_parser.ReadFloat();
		m_unk0x08[i].m_z = p_parser.ReadFloat();
		m_unk0x0c[i].m_x = p_parser.ReadFloat();
		m_unk0x0c[i].m_y = p_parser.ReadFloat();
		m_unk0x10[i] = ARGBU32(0xff, 0xff, 0xff, 0xff);
	}

	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x10006210 FOLDED
void GdbVertexArrayMistery0x1c::VTable0x18(LegoU32 p_index, GolVec2* p_dest) const
{
	p_dest->m_x = m_unk0x0c[p_index].m_x;
	p_dest->m_y = m_unk0x0c[p_index].m_y;
}

// FUNCTION: GOLDP 0x10015890
void GdbVertexArrayMistery0x1c::VTable0x20(LegoU32 p_index, ColorRGBA* p_dest) const
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
