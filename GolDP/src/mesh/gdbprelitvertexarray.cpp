#include "mesh/gdbprelitvertexarray.h"

#include "golmath.h"

DECOMP_SIZE_ASSERT(GdbPrelitVertexArray, 0x20)

// FUNCTION: GOLDP 0x10016ad0
GdbPrelitVertexArray::GdbPrelitVertexArray()
{
	m_vertexType = 1;
}

// FUNCTION: GOLDP 0x10016b10
void GdbPrelitVertexArray::VTable0x08(GolFileParser& p_parser)
{
	GdbNormalVertexArray::VTable0x08(p_parser);
	m_vertexType = 3;
}

// FUNCTION: GOLDP 0x10016b30
void GdbPrelitVertexArray::VTable0x04(LegoU16 p_count)
{
	GdbNormalVertexArray::VTable0x04(p_count);
	m_vertexType = 3;
}

// FUNCTION: GOLDP 0x10016b50
void GdbPrelitVertexArray::VTable0x10()
{
	if (m_unk0x1c != NULL) {
		delete[] m_unk0x1c;
		m_unk0x1c = NULL;
	}

	m_vertexType = 1;
}
