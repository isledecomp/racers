#include "gdbvertexarray.h"

#include "golerror.h"
#include "golfileparser.h"
#include "golmath.h"
#include "surface/color.h"

DECOMP_SIZE_ASSERT(ColorTransform, 0x20)
DECOMP_SIZE_ASSERT(GdbVertexArray, 0xc)

// FUNCTION: GOLDP 0x10006230
void GdbVertexArray::GetNormal(LegoU32 p_index, GolVec3* p_arg2) const
{
	p_arg2->m_x = 0.0f;
	p_arg2->m_y = 0.0f;
	p_arg2->m_z = 0.0f;
}

// FUNCTION: GOLDP 0x10015860
void GdbVertexArray::GetPosition(LegoU32 p_index, GolVec3* p_arg2) const
{
	p_arg2->m_x = m_positions[p_index].m_x;
	p_arg2->m_y = m_positions[p_index].m_y;
	p_arg2->m_z = m_positions[p_index].m_z;
}

// FUNCTION: GOLDP 0x100158b0
void GdbVertexArray::SetPosition(LegoU32 p_index, const GolVec3& p_arg2)
{
	m_positions[p_index].m_x = p_arg2.m_x;
	m_positions[p_index].m_y = p_arg2.m_y;
	m_positions[p_index].m_z = p_arg2.m_z;
}

// FUNCTION: GOLDP 0x10029920 FOLDED
// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void GdbVertexArray::ClearColorTransform()
{
	// empty
}

// FUNCTION: GOLDP 0x1002be00
// FUNCTION: LEGORACERS 0x00415dd0
GdbVertexArray::GdbVertexArray()
{
	m_count = 0;
	m_vertexType = c_vertexTypePosition;
	m_positions = NULL;
}

// FUNCTION: GOLDP 0x1002be60
// FUNCTION: LEGORACERS 0x00415e10
GdbVertexArray::~GdbVertexArray()
{
	Destroy();
}

// FUNCTION: GOLDP 0x1002be90
// FUNCTION: LEGORACERS 0x00415e20
void GdbVertexArray::Parse(GolFileParser& p_parser)
{
	if (m_count != 0) {
		Destroy();
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
void GdbVertexArray::Allocate(LegoU16 p_count)
{
	if (m_count != 0) {
		Destroy();
	}

	m_count = p_count;
	m_positions = new GolVec3[p_count];
	if (m_positions == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
}

// FUNCTION: GOLDP 0x1002bfb0 FOLDED
// FUNCTION: LEGORACERS 0x00415f40 FOLDED
void GdbVertexArray::Destroy()
{
	if (m_positions != NULL) {
		delete[] m_positions;
		m_positions = NULL;
	}
}

// FUNCTION: GOLDP 0x10029920 FOLDED
// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void GdbVertexArray::DiscardNormals()
{
	// empty
}

// FUNCTION: GOLDP 0x1002bfd0
// FUNCTION: LEGORACERS 0x00415f90
void GdbVertexArray::GetTextureCoordinate(undefined4, GolVec2* p_dest) const
{
	p_dest->m_x = 0.0f;
	p_dest->m_y = 0.0f;
}

// FUNCTION: GOLDP 0x1002bff0
// FUNCTION: LEGORACERS 0x00415fd0
void GdbVertexArray::GetColor(LegoU32 p_index, ColorRGBA* p_dest) const
{
	p_dest->m_red = 0;
	p_dest->m_grn = 0;
	p_dest->m_blu = 0;
	p_dest->m_alp = 0;
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
// FUNCTION: LEGORACERS 0x0046c9f0 FOLDED
void GdbVertexArray::SetTextureCoordinate(LegoU32 p_index, const GolVec2&)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
// FUNCTION: LEGORACERS 0x0046c9f0 FOLDED
void GdbVertexArray::SetNormal(LegoU32 p_index, const GolVec3&)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
// FUNCTION: LEGORACERS 0x0046c9f0 FOLDED
void GdbVertexArray::SetColor(LegoU32 p_index, const ColorRGBA&)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void GdbVertexArray::ApplyColorTransform(const ColorTransform& p_details)
{
	// empty
}
