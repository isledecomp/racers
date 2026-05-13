#include "gdbvertexarray0xc.h"

#include "color.h"
#include "golerror.h"
#include "golfileparser.h"
#include "golmath.h"

DECOMP_SIZE_ASSERT(GdbVertexArray0xc, 0xc)

// FUNCTION: GOLDP 0x10006230
void GdbVertexArray0xc::VTable0x1c(LegoU32 p_index, GolVec3* p_arg2) const
{
	p_arg2->m_x = 0.0f;
	p_arg2->m_y = 0.0f;
	p_arg2->m_z = 0.0f;
}

// FUNCTION: GOLDP 0x10015860
void GdbVertexArray0xc::VTable0x14(LegoU32 p_index, GolVec3* p_arg2) const
{
	p_arg2->m_x = m_unk0x08[p_index].m_x;
	p_arg2->m_y = m_unk0x08[p_index].m_y;
	p_arg2->m_z = m_unk0x08[p_index].m_z;
}

// FUNCTION: GOLDP 0x100158b0
void GdbVertexArray0xc::VTable0x24(LegoU32 p_index, const GolVec3& p_arg2)
{
	m_unk0x08[p_index].m_x = p_arg2.m_x;
	m_unk0x08[p_index].m_y = p_arg2.m_y;
	m_unk0x08[p_index].m_z = p_arg2.m_z;
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void GdbVertexArray0xc::VTable0x38()
{
	// empty
}

// FUNCTION: GOLDP 0x1002be00
GdbVertexArray0xc::GdbVertexArray0xc()
{
	m_unk0x04 = 0;
	m_unk0x06 = 5;
	m_unk0x08 = NULL;
}

// FUNCTION: GOLDP 0x1002be60
GdbVertexArray0xc::~GdbVertexArray0xc()
{
	VTable0x0c();
}

// FUNCTION: GOLDP 0x1002be90
void GdbVertexArray0xc::VTable0x08(GolFileParser& p_parser)
{
	if (m_unk0x04 != 0) {
		VTable0x0c();
	}
	m_unk0x04 = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_unk0x04 == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_unk0x08 = new GolVec3[m_unk0x04];
	if (m_unk0x08 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	::memset(m_unk0x08, 0, m_unk0x04 * sizeof(GolVec3));
	LegoU32 i;
	for (i = 0; i < m_unk0x04; i++) {
		m_unk0x08[i].m_x = p_parser.ReadFloat();
		m_unk0x08[i].m_y = p_parser.ReadFloat();
		m_unk0x08[i].m_z = p_parser.ReadFloat();
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002bf60
void GdbVertexArray0xc::VTable0x04(LegoU16 p_count)
{
	if (m_unk0x04 != 0) {
		VTable0x0c();
	}
	m_unk0x04 = p_count;
	m_unk0x08 = new GolVec3[p_count];
	if (m_unk0x08 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
}

// FUNCTION: GOLDP 0x1002bfb0 FOLDED
void GdbVertexArray0xc::VTable0x0c()
{
	if (m_unk0x08 != NULL) {
		delete[] m_unk0x08;
		m_unk0x08 = NULL;
	}
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void GdbVertexArray0xc::VTable0x10()
{
	// empty
}

// FUNCTION: GOLDP 0x1002bfd0
void GdbVertexArray0xc::VTable0x18(undefined4, GolVec2* p_dest) const
{
	p_dest->m_x = 0.0f;
	p_dest->m_y = 0.0f;
}

// FUNCTION: GOLDP 0x1002bff0
void GdbVertexArray0xc::VTable0x20(LegoU32 p_index, ColorRGBA* p_dest) const
{
	p_dest->m_red = 0;
	p_dest->m_grn = 0;
	p_dest->m_blu = 0;
	p_dest->m_alp = 0;
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
void GdbVertexArray0xc::VTable0x28(LegoU32 p_index, const GolVec2&)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
void GdbVertexArray0xc::VTable0x2c(LegoU32 p_index, const GolVec3&)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
void GdbVertexArray0xc::VTable0x30(LegoU32 p_index, const ColorRGBA&)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
void GdbVertexArray0xc::VTable0x34(const PixelFormatMod& p_details)
{
	// empty
}
