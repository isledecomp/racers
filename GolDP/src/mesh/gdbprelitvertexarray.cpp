#include "mesh/gdbprelitvertexarray.h"

#include "golmath.h"

DECOMP_SIZE_ASSERT(GdbPrelitVertexArray, 0x20)

// FUNCTION: GOLDP 0x10016ad0
GdbPrelitVertexArray::GdbPrelitVertexArray()
{
	m_vertexType = c_vertexTypeColored;
}

// FUNCTION: GOLDP 0x10016b10
void GdbPrelitVertexArray::Parse(GolFileParser& p_parser)
{
	GdbNormalVertexArray::Parse(p_parser);
	m_vertexType = c_vertexTypePrelit;
}

// FUNCTION: GOLDP 0x10016b30
void GdbPrelitVertexArray::Allocate(LegoU16 p_count)
{
	GdbNormalVertexArray::Allocate(p_count);
	m_vertexType = c_vertexTypePrelit;
}

// FUNCTION: GOLDP 0x10016b50
void GdbPrelitVertexArray::DiscardNormals()
{
	if (m_normals != NULL) {
		delete[] m_normals;
		m_normals = NULL;
	}

	m_vertexType = c_vertexTypeColored;
}
