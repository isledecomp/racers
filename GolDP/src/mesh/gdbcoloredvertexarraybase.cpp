#include "mesh/gdbcoloredvertexarraybase.h"

#include "decomp.h"

DECOMP_SIZE_ASSERT(GdbColoredVertexArrayBase, 0x1c)

#include "golerror.h"
#include "golmath.h"

// FUNCTION: GOLDP 0x10016f20
GdbColoredVertexArrayBase::GdbColoredVertexArrayBase()
{
	m_textureCoordinates = NULL;
	m_colors = NULL;
	m_hasTransformedColors = FALSE;
	m_transformedColors = NULL;
}

// FUNCTION: GOLDP 0x10016f60 FOLDED
GdbColoredVertexArrayBase::~GdbColoredVertexArrayBase()
{
	Destroy();
}

// FUNCTION: GOLDP 0x10016ff0
void GdbColoredVertexArrayBase::Destroy()
{
	if (m_textureCoordinates != NULL) {
		delete[] m_textureCoordinates;
		m_textureCoordinates = NULL;
	}
	if (m_colors != NULL) {
		delete[] m_colors;
		m_colors = NULL;
	}
	if (m_transformedColors != NULL) {
		delete[] m_transformedColors;
		m_transformedColors = NULL;
	}
	GdbVertexArray::Destroy();
}

// FUNCTION: GOLDP 0x10017050
void GdbColoredVertexArrayBase::ApplyColorTransform(const ColorTransform& p_details)
{
	LegoU32* ptrIn;
	LegoU32* ptrOut;
	LegoU32* ptrInEnd;

	if (m_transformedColors == NULL) {
		m_transformedColors = new LegoU32[m_count];
		if (m_transformedColors == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	ptrOut = m_transformedColors;
	ptrIn = m_colors;
	ptrInEnd = ptrIn + m_count;

	for (; ptrIn < ptrInEnd; ptrIn++, ptrOut++) {
		LegoU32 original = *ptrIn;
		LegoS32 r = (original >> 16) & 0xff;
		LegoS32 g = (original >> 8) & 0xff;
		LegoS32 b = (original >> 0) & 0xff;
		LegoS32 a = (original >> 24) & 0xff;
		r = (r >> p_details.m_redShift) + p_details.m_redOffset;
		if (r > 0xff) {
			r = 0xff;
		}
		g = (g >> p_details.m_grnShift) + p_details.m_grnOffset;
		if (g > 0xff) {
			g = 0xff;
		}
		b = (b >> p_details.m_bluShift) + p_details.m_bluOffset;
		if (b > 0xff) {
			b = 0xff;
		}
		a = (a >> p_details.m_alpShift) + p_details.m_alpOffset;
		if (a > 0xff) {
			a = 0xff;
		}
		*ptrOut = (a << 24) | (r << 16) | (g << 8) | (b << 0);
	}

	m_hasTransformedColors = TRUE;
}

// FUNCTION: GOLDP 0x10017180
void GdbColoredVertexArrayBase::ClearColorTransform()
{
	m_hasTransformedColors = FALSE;
}
