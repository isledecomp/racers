#include "model/gdbpartvertexpool.h"

#include "golerror.h"
#include "golfileparser.h"

#include <string.h>

DECOMP_SIZE_ASSERT(GdbPartVertexPool, 0x14)
DECOMP_SIZE_ASSERT(GdbPartVertexPool::Vertex, 0x0e)
DECOMP_SIZE_ASSERT(GdbPartVertexPool::Vertex::Tail, 0x04)
DECOMP_SIZE_ASSERT(GdbPartVertexPool::Vertex::Tail::Normal, 0x04)

// GLOBAL: LEGORACERS 0x004af4ac
static const LegoFloat g_gdbPartTexCoordDivisor = 4096.0f;

// GLOBAL: LEGORACERS 0x004af4b0
static const LegoFloat g_gdbPartNormalDivisor = 127.0f;

// GLOBAL: LEGORACERS 0x004c2854
static LegoFloat g_gdbPartNormalScale = 1.0f / g_gdbPartNormalDivisor;

// GLOBAL: LEGORACERS 0x004c2858
static LegoFloat g_gdbPartTexCoordScale = 1.0f / g_gdbPartTexCoordDivisor;

// FUNCTION: LEGORACERS 0x00407fe0
GdbPartVertexPool::GdbPartVertexPool()
{
	m_vertices = NULL;
	m_unk0x10 = 0;
}

// FUNCTION: LEGORACERS 0x00408020
GdbPartVertexPool::~GdbPartVertexPool()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00408070
void GdbPartVertexPool::Read(GolFileParser& p_parser, LegoU16 p_vertexType)
{
	if (m_count != 0) {
		Destroy();
	}

	m_vertexType = p_vertexType;
	m_count = static_cast<LegoU16>(p_parser.ReadBracketedCountAndLeftCurly());
	if (m_count == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}

	m_vertices = new Vertex[m_count];
	if (m_vertices == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	::memset(m_vertices, 0, sizeof(*m_vertices) * m_count);

	Vertex* vertex = m_vertices;
	Vertex* end = m_vertices + m_count;
	if (m_vertexType == c_vertexTypeColored) {
		while (vertex < end) {
			vertex->m_x = static_cast<LegoS16>(p_parser.ReadInteger());
			vertex->m_y = static_cast<LegoS16>(p_parser.ReadInteger());
			vertex->m_z = static_cast<LegoS16>(p_parser.ReadInteger());
			vertex->m_u = static_cast<LegoS16>(p_parser.ReadInteger());
			vertex->m_v = static_cast<LegoS16>(p_parser.ReadInteger());
			vertex->m_tail.m_normal.m_nx = static_cast<LegoS8>(p_parser.ReadInteger());
			vertex->m_tail.m_normal.m_ny = static_cast<LegoS8>(p_parser.ReadInteger());
			vertex->m_tail.m_normal.m_nz = static_cast<LegoS8>(p_parser.ReadInteger());
			vertex->m_tail.m_normal.m_argb = static_cast<LegoU8>(p_parser.ReadInteger());
			vertex++;
		}
	}
	else {
		while (vertex < end) {
			vertex->m_x = static_cast<LegoS16>(p_parser.ReadInteger());
			vertex->m_y = static_cast<LegoS16>(p_parser.ReadInteger());
			vertex->m_z = static_cast<LegoS16>(p_parser.ReadInteger());
			vertex->m_u = static_cast<LegoS16>(p_parser.ReadInteger());
			vertex->m_v = static_cast<LegoS16>(p_parser.ReadInteger());
			vertex->m_tail.m_normal.m_nx = static_cast<LegoS8>(p_parser.ReadInteger());
			vertex->m_tail.m_normal.m_ny = static_cast<LegoS8>(p_parser.ReadInteger());
			vertex->m_tail.m_normal.m_nz = static_cast<LegoS8>(p_parser.ReadInteger());
			vertex++;
		}
	}

	p_parser.ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00408200
void GdbPartVertexPool::Destroy()
{
	if (m_vertices != NULL) {
		delete[] m_vertices;
		m_vertices = NULL;
	}
	m_unk0x10 = 0;
}

// FUNCTION: LEGORACERS 0x00408230
void GdbPartVertexPool::GetPosition(LegoU32 p_index, GolVec3* p_dest) const
{
	const Vertex& vertex = m_vertices[p_index];
	p_dest->m_x = static_cast<LegoFloat>(vertex.m_x);
	p_dest->m_y = static_cast<LegoFloat>(vertex.m_y);
	p_dest->m_z = static_cast<LegoFloat>(vertex.m_z);
}

// FUNCTION: LEGORACERS 0x00408280
void GdbPartVertexPool::GetTextureCoordinate(LegoU32 p_index, GolVec2* p_dest) const
{
	const Vertex& vertex = m_vertices[p_index];
	p_dest->m_x = static_cast<LegoFloat>(vertex.m_u) * g_gdbPartTexCoordScale;
	p_dest->m_y = static_cast<LegoFloat>(vertex.m_v) * g_gdbPartTexCoordScale;
}

// FUNCTION: LEGORACERS 0x004082d0
void GdbPartVertexPool::GetNormal(LegoU32 p_index, GolVec3* p_dest) const
{
	const Vertex& vertex = m_vertices[p_index];
	p_dest->m_x = static_cast<LegoFloat>(vertex.m_tail.m_normal.m_nx) * g_gdbPartNormalScale;
	p_dest->m_y = static_cast<LegoFloat>(vertex.m_tail.m_normal.m_ny) * g_gdbPartNormalScale;
	p_dest->m_z = static_cast<LegoFloat>(vertex.m_tail.m_normal.m_nz) * g_gdbPartNormalScale;
}

// FUNCTION: LEGORACERS 0x00408330
void GdbPartVertexPool::GetColor(LegoU32 p_index, ColorRGBA* p_dest) const
{
	*p_dest = m_vertices[p_index].m_tail.m_color;
}

// FUNCTION: LEGORACERS 0x00408350
void GdbPartVertexPool::SetPosition(LegoU32 p_index, const GolVec3& p_src)
{
	Vertex* vertex = &m_vertices[p_index];
	vertex->m_x = static_cast<LegoS16>(p_src.m_x);
	vertex->m_y = static_cast<LegoS16>(p_src.m_y);
	vertex->m_z = static_cast<LegoS16>(p_src.m_z);
}

// FUNCTION: LEGORACERS 0x00408390
void GdbPartVertexPool::SetTextureCoordinate(LegoU32 p_index, const GolVec2& p_src)
{
	Vertex* vertex = &m_vertices[p_index];
	vertex->m_u = static_cast<LegoS16>(g_gdbPartTexCoordDivisor * p_src.m_x);
	vertex->m_v = static_cast<LegoS16>(p_src.m_y * g_gdbPartTexCoordDivisor);
}

// FUNCTION: LEGORACERS 0x004083e0
void GdbPartVertexPool::SetNormal(LegoU32 p_index, const GolVec3& p_src)
{
	Vertex* vertex = &m_vertices[p_index];
	vertex->m_tail.m_normal.m_nx = static_cast<LegoS8>(g_gdbPartNormalDivisor * p_src.m_x);
	vertex->m_tail.m_normal.m_ny = static_cast<LegoS8>(p_src.m_y * g_gdbPartNormalDivisor);
	vertex->m_tail.m_normal.m_nz = static_cast<LegoS8>(p_src.m_z * g_gdbPartNormalDivisor);
	vertex->m_tail.m_normal.m_argb = 0xff;
}

// FUNCTION: LEGORACERS 0x00408440
void GdbPartVertexPool::SetColor(LegoU32 p_index, const ColorRGBA& p_src)
{
	m_vertices[p_index].m_tail.m_color = p_src;
}
