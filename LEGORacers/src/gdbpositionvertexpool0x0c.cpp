#include "gdbpositionvertexpool0x0c.h"

#include "golerror.h"
#include "golfileparser.h"

#include <string.h>

DECOMP_SIZE_ASSERT(GdbPositionVertexPool0x0c, 0x0c)

// FUNCTION: LEGORACERS 0x00415dd0
GdbPositionVertexPool0x0c::GdbPositionVertexPool0x0c()
{
	m_count = 0;
	m_vertexType = 5;
	m_positions = NULL;
}

// FUNCTION: LEGORACERS 0x00415e10
GdbPositionVertexPool0x0c::~GdbPositionVertexPool0x0c()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x00415e20
void GdbPositionVertexPool0x0c::Read(GolFileParser& p_parser)
{
	if (m_count != 0) {
		Clear();
	}

	m_count = static_cast<LegoU16>(p_parser.ReadBracketedCountAndLeftCurly());
	if (m_count == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}

	m_positions = new GolVec3[m_count];
	if (m_positions == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	::memset(m_positions, 0, sizeof(*m_positions) * m_count);

	for (LegoU32 positionIndex = 0; positionIndex < m_count; positionIndex++) {
		m_positions[positionIndex].m_x = p_parser.ReadFloat();
		m_positions[positionIndex].m_y = p_parser.ReadFloat();
		m_positions[positionIndex].m_z = p_parser.ReadFloat();
	}

	p_parser.ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00415ef0
void GdbPositionVertexPool0x0c::Allocate(LegoU16 p_count)
{
	if (m_count != 0) {
		Clear();
	}

	m_count = p_count;
	m_positions = new GolVec3[m_count];
	if (m_positions == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
}

// FUNCTION: LEGORACERS 0x00415f40 FOLDED
void GdbPositionVertexPool0x0c::Clear()
{
	if (m_positions != NULL) {
		delete[] m_positions;
		m_positions = NULL;
	}
}

// FUNCTION: LEGORACERS 0x00415f60
void GdbPositionVertexPool0x0c::GetPosition(LegoU32 p_index, GolVec3* p_dest) const
{
	p_dest->m_x = m_positions[p_index].m_x;
	p_dest->m_y = m_positions[p_index].m_y;
	p_dest->m_z = m_positions[p_index].m_z;
}

// FUNCTION: LEGORACERS 0x00415f90
void GdbPositionVertexPool0x0c::GetTexCoord(LegoU32, GolVec2* p_dest) const
{
	p_dest->m_x = 0.0f;
	p_dest->m_y = 0.0f;
}

// FUNCTION: LEGORACERS 0x00415fb0
void GdbPositionVertexPool0x0c::GetNormal(LegoU32, GolVec3* p_dest) const
{
	p_dest->m_x = 0.0f;
	p_dest->m_y = 0.0f;
	p_dest->m_z = 0.0f;
}

// FUNCTION: LEGORACERS 0x00415fd0
void GdbPositionVertexPool0x0c::GetColor(LegoU32, ColorRGBA* p_dest) const
{
	p_dest->m_red = 0;
	p_dest->m_grn = 0;
	p_dest->m_blu = 0;
	p_dest->m_alp = 0;
}

// FUNCTION: LEGORACERS 0x00415ff0
void GdbPositionVertexPool0x0c::SetPosition(LegoU32 p_index, const GolVec3* p_src)
{
	m_positions[p_index].m_x = p_src->m_x;
	m_positions[p_index].m_y = p_src->m_y;
	m_positions[p_index].m_z = p_src->m_z;
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void GdbPositionVertexPool0x0c::VTable0x10()
{
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void GdbPositionVertexPool0x0c::VTable0x38()
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void GdbPositionVertexPool0x0c::VTable0x34(const LegoChar*)
{
}

// FUNCTION: LEGORACERS 0x0046c9f0 FOLDED
void GdbPositionVertexPool0x0c::SetTexCoord(LegoU32, const GolVec2*)
{
}

// FUNCTION: LEGORACERS 0x0046c9f0 FOLDED
void GdbPositionVertexPool0x0c::SetNormal(LegoU32, const GolVec3*)
{
}

// FUNCTION: LEGORACERS 0x0046c9f0 FOLDED
void GdbPositionVertexPool0x0c::SetColor(LegoU32, const ColorRGBA*)
{
}
