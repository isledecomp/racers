#include "gdbvertexarray0xc.h"

#include "golerror.h"
#include "golfileparser.h"
#include "golmath.h"
#include "surface/color.h"

DECOMP_SIZE_ASSERT(ColorTransform0x20, 0x20)
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
	p_arg2->m_x = m_positions[p_index].m_x;
	p_arg2->m_y = m_positions[p_index].m_y;
	p_arg2->m_z = m_positions[p_index].m_z;
}

// FUNCTION: GOLDP 0x100158b0
void GdbVertexArray0xc::VTable0x24(LegoU32 p_index, const GolVec3& p_arg2)
{
	m_positions[p_index].m_x = p_arg2.m_x;
	m_positions[p_index].m_y = p_arg2.m_y;
	m_positions[p_index].m_z = p_arg2.m_z;
}

// FUNCTION: GOLDP 0x10029920 FOLDED
// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void GdbVertexArray0xc::VTable0x38()
{
	// empty
}

// FUNCTION: GOLDP 0x1002be00
// FUNCTION: LEGORACERS 0x00415dd0
GdbVertexArray0xc::GdbVertexArray0xc()
{
	m_count = 0;
	m_vertexType = 5;
	m_positions = NULL;
}

// FUNCTION: GOLDP 0x1002be60
// FUNCTION: LEGORACERS 0x00415e10
GdbVertexArray0xc::~GdbVertexArray0xc()
{
	VTable0x0c();
}

// FUNCTION: GOLDP 0x1002be90
// FUNCTION: LEGORACERS 0x00415e20
void GdbVertexArray0xc::VTable0x08(GolFileParser& p_parser)
{
	if (m_count != 0) {
		VTable0x0c();
	}

	m_count = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_count == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}

	m_positions = new GolVec3[m_count];
	if (m_positions == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	::memset(m_positions, 0, m_count * sizeof(GolVec3));

	LegoU32 i;
	for (i = 0; i < m_count; i++) {
		m_positions[i].m_x = p_parser.ReadFloat();
		m_positions[i].m_y = p_parser.ReadFloat();
		m_positions[i].m_z = p_parser.ReadFloat();
	}

	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002bf60
// FUNCTION: LEGORACERS 0x00415ef0
void GdbVertexArray0xc::VTable0x04(LegoU16 p_count)
{
	if (m_count != 0) {
		VTable0x0c();
	}

	m_count = p_count;
	m_positions = new GolVec3[p_count];
	if (m_positions == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
}

// FUNCTION: GOLDP 0x1002bfb0 FOLDED
// FUNCTION: LEGORACERS 0x00415f40 FOLDED
void GdbVertexArray0xc::VTable0x0c()
{
	if (m_positions != NULL) {
		delete[] m_positions;
		m_positions = NULL;
	}
}

// FUNCTION: GOLDP 0x10029920 FOLDED
// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void GdbVertexArray0xc::VTable0x10()
{
	// empty
}

// FUNCTION: GOLDP 0x1002bfd0
// FUNCTION: LEGORACERS 0x00415f90
void GdbVertexArray0xc::VTable0x18(undefined4, GolVec2* p_dest) const
{
	p_dest->m_x = 0.0f;
	p_dest->m_y = 0.0f;
}

// FUNCTION: GOLDP 0x1002bff0
// FUNCTION: LEGORACERS 0x00415fd0
void GdbVertexArray0xc::VTable0x20(LegoU32 p_index, ColorRGBA* p_dest) const
{
	p_dest->m_red = 0;
	p_dest->m_grn = 0;
	p_dest->m_blu = 0;
	p_dest->m_alp = 0;
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
// FUNCTION: LEGORACERS 0x0046c9f0 FOLDED
void GdbVertexArray0xc::VTable0x28(LegoU32 p_index, const GolVec2&)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
// FUNCTION: LEGORACERS 0x0046c9f0 FOLDED
void GdbVertexArray0xc::VTable0x2c(LegoU32 p_index, const GolVec3&)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
// FUNCTION: LEGORACERS 0x0046c9f0 FOLDED
void GdbVertexArray0xc::VTable0x30(LegoU32 p_index, const ColorRGBA&)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void GdbVertexArray0xc::VTable0x34(const ColorTransform0x20& p_details)
{
	// empty
}
