#include "mesh/gdbcoloredvertexarray.h"

#include "golerror.h"
#include "golfileparser.h"
#include "golmath.h"
#include "surface/color.h"

DECOMP_SIZE_ASSERT(GdbColoredVertexArray, 0x1c)

// FUNCTION: GOLDP 0x10005f90
GdbColoredVertexArray::GdbColoredVertexArray()
{
	m_vertexType = c_vertexTypeColored;
}

// FUNCTION: GOLDP 0x10005fc0
void GdbColoredVertexArray::Parse(GolFileParser& p_parser)
{
	LegoU32 i;

	if (m_count != 0) {
		Destroy();
	}

	p_parser.ReadLeftBracket();
	m_count = p_parser.ReadInteger();
	if (m_count == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	p_parser.ReadRightBracket();
	p_parser.ReadLeftCurly();

	m_positions = new GolVec3[m_count];
	if (m_positions == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	m_textureCoordinates = new GolVec2[m_count];
	if (m_textureCoordinates == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	m_colors = new LegoU32[m_count];
	if (m_colors == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (i = 0; i < m_count; i++) {
		m_positions[i].m_x = p_parser.ReadFloat();
		m_positions[i].m_y = p_parser.ReadFloat();
		m_positions[i].m_z = p_parser.ReadFloat();
		m_textureCoordinates[i].m_x = p_parser.ReadFloat();
		m_textureCoordinates[i].m_y = p_parser.ReadFloat();
		LegoU32 red = p_parser.ReadInteger() & 0xff;
		LegoU32 grn = p_parser.ReadInteger() & 0xff;
		LegoU32 blu = p_parser.ReadInteger() & 0xff;
		LegoU32 alp = p_parser.ReadInteger() & 0xff;
		m_colors[i] = (alp << 24) | (red << 16) | (grn << 8) | (blu << 0);
	}

	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x10006150 FOLDED
void GdbColoredVertexArray::Allocate(LegoU16 p_count)
{
	LegoU32 i;

	if (m_count != 0) {
		Destroy();
	}

	m_count = p_count;

	m_positions = new GolVec3[m_count];
	if (m_positions == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	m_textureCoordinates = new GolVec2[m_count];
	if (m_textureCoordinates == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	m_colors = new LegoU32[m_count];
	if (m_colors == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (i = 0; i < m_count; i++) {
		m_textureCoordinates[i].m_x = 0.0f;
		m_textureCoordinates[i].m_y = 0.0f;
		m_colors[i] = ARGBU32(0xff, 0xff, 0xff, 0xff);
	}
}

// FUNCTION: GOLDP 0x10006210 FOLDED
void GdbColoredVertexArray::GetTextureCoordinate(LegoU32 p_index, GolVec2* p_dest) const
{
	p_dest->m_x = m_textureCoordinates[p_index].m_x;
	p_dest->m_y = m_textureCoordinates[p_index].m_y;
}

// FUNCTION: GOLDP 0x10016ea0 FOLDED
void GdbColoredVertexArray::GetColor(LegoU32 p_index, ColorRGBA* p_dest) const
{
	p_dest->m_red = m_colors[p_index] >> 16;
	p_dest->m_grn = m_colors[p_index] >> 8;
	p_dest->m_blu = m_colors[p_index] >> 0;
	p_dest->m_alp = m_colors[p_index] >> 24;
}

// FUNCTION: GOLDP 0x100158f0 FOLDED
void GdbColoredVertexArray::SetTextureCoordinate(LegoU32 p_index, const GolVec2& p_arg2)
{
	m_textureCoordinates[p_index].m_x = p_arg2.m_x;
	m_textureCoordinates[p_index].m_y = p_arg2.m_y;
}

// FUNCTION: GOLDP 0x10006250 FOLDED
void GdbColoredVertexArray::SetColor(LegoU32 p_index, const ColorRGBA& p_arg2)
{
	m_colors[p_index] = ARGBU32(p_arg2.m_alp, p_arg2.m_red, p_arg2.m_grn, p_arg2.m_blu);
}
