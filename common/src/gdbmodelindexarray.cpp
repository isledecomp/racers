#include "gdbmodelindexarray.h"

#include "golerror.h"
#include "golfileparser.h"

DECOMP_SIZE_ASSERT(GdbModelIndexArray, 0xc)
DECOMP_SIZE_ASSERT(GdbModelIndexArray::Indices, 0x4)

// FUNCTION: GOLDP 0x1002b310
GdbModelIndexArray::GdbModelIndexArray()
{
	m_indices = NULL;
}

// FUNCTION: GOLDP 0x1002b350
GdbModelIndexArray::~GdbModelIndexArray()
{
	Destroy();
}

// FUNCTION: GOLDP 0x1002b3c0
void GdbModelIndexArray::Parse(GolFileParser& p_parser)
{
	LegoU32 i;

	if (m_count != 0) {
		Destroy();
	}

	m_count = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_count == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}

	m_indices = new Indices[m_count];
	if (m_indices == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	::memset(m_indices, 0, sizeof(*m_indices) * m_count);

	for (i = 0; i < m_count; i++) {
		m_indices[i].m_a = p_parser.ReadInteger();
		m_indices[i].m_b = p_parser.ReadInteger();
		m_indices[i].m_c = p_parser.ReadInteger();
		m_indices[i].m_x = 0;
	}

	if (p_parser.GetNextToken() != GolFileParser::e_rightCurly) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_rightCurly);
	}
}

// FUNCTION: GOLDP 0x1002bfb0 FOLDED
// FUNCTION: LEGORACERS 0x00415f40 FOLDED
void GdbModelIndexArray::Destroy()
{
	if (m_indices != NULL) {
		delete[] m_indices;
		m_indices = NULL;
	}
}

// FUNCTION: GOLDP 0x1002b490
void GdbModelIndexArray::Allocate(LegoU32 p_count)
{
	if (m_count != 0) {
		Destroy();
	}

	m_count = p_count;
	m_indices = new Indices[m_count];
	if (m_indices == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
}
