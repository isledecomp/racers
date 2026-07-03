#include "mesh/gdbuncoloredvertexarray.h"

#include "golerror.h"
#include "golfileparser.h"
#include "golmath.h"
#include "surface/color.h"

DECOMP_SIZE_ASSERT(GdbUncoloredVertexArray, 0x1c)

// FUNCTION: GOLDP 0x100156d0
GdbUncoloredVertexArray::GdbUncoloredVertexArray()
{
	m_vertexType = c_vertexTypeColored;
}

// FUNCTION: GOLDP 0x10006150 FOLDED
void GdbUncoloredVertexArray::Allocate(LegoU16 p_count)
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

// FUNCTION: GOLDP 0x100156f0
void GdbUncoloredVertexArray::Parse(GolFileParser& p_parser)
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

	::memset(m_positions, 0, sizeof(GolVec3) * m_count);
	::memset(m_textureCoordinates, 0, sizeof(GolVec2) * m_count);

	for (i = 0; i < m_count; i++) {
		m_positions[i].m_x = p_parser.ReadFloat();
		m_positions[i].m_y = p_parser.ReadFloat();
		m_positions[i].m_z = p_parser.ReadFloat();
		m_textureCoordinates[i].m_x = p_parser.ReadFloat();
		m_textureCoordinates[i].m_y = p_parser.ReadFloat();
		m_colors[i] = ARGBU32(0xff, 0xff, 0xff, 0xff);
	}

	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x10006210 FOLDED
void GdbUncoloredVertexArray::GetTextureCoordinate(LegoU32 p_index, GolVec2* p_dest) const
{
	p_dest->m_x = m_textureCoordinates[p_index].m_x;
	p_dest->m_y = m_textureCoordinates[p_index].m_y;
}

// FUNCTION: GOLDP 0x10015890
void GdbUncoloredVertexArray::GetColor(LegoU32 p_index, ColorRGBA* p_dest) const
{
	p_dest->m_red = 0xff;
	p_dest->m_grn = 0xff;
	p_dest->m_blu = 0xff;
	p_dest->m_alp = 0xff;
}

// FUNCTION: GOLDP 0x100158f0 FOLDED
void GdbUncoloredVertexArray::SetTextureCoordinate(LegoU32 p_index, const GolVec2& p_arg2)
{
	m_textureCoordinates[p_index].m_x = p_arg2.m_x;
	m_textureCoordinates[p_index].m_y = p_arg2.m_y;
}
