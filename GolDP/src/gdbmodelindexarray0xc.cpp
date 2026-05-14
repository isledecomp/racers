#include "gdbmodelindexarray0xc.h"

#include "golerror.h"
#include "golfileparser.h"

DECOMP_SIZE_ASSERT(GdbModelIndexArray0xc, 0xc)
DECOMP_SIZE_ASSERT(GdbModelIndexArray0xc::Indices, 0x4)

// FUNCTION: GOLDP 0x1002b310
GdbModelIndexArray0xc::GdbModelIndexArray0xc()
{
	m_unk0x08 = NULL;
}

// FUNCTION: GOLDP 0x1002b350
GdbModelIndexArray0xc::~GdbModelIndexArray0xc()
{
	VTable0x08();
}

// FUNCTION: GOLDP 0x1002b3c0
void GdbModelIndexArray0xc::VTable0x04(GolFileParser& p_parser)
{
	LegoU32 i;

	if (m_unk0x04 != 0) {
		VTable0x08();
	}

	m_unk0x04 = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_unk0x04 == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}

	m_unk0x08 = new Indices[m_unk0x04];
	if (m_unk0x08 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	::memset(m_unk0x08, 0, sizeof(*m_unk0x08) * m_unk0x04);

	for (i = 0; i < m_unk0x04; i++) {
		m_unk0x08[i].m_a = p_parser.ReadInteger();
		m_unk0x08[i].m_b = p_parser.ReadInteger();
		m_unk0x08[i].m_c = p_parser.ReadInteger();
		m_unk0x08[i].m_x = 0;
	}

	if (p_parser.GetNextToken() != GolFileParser::e_rightCurly) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_rightCurly);
	}
}

// FUNCTION: GOLDP 0x1002bfb0 FOLDED
void GdbModelIndexArray0xc::VTable0x08()
{
	if (m_unk0x08 != NULL) {
		delete[] m_unk0x08;
		m_unk0x08 = NULL;
	}
}

// FUNCTION: GOLDP 0x1002b490
void GdbModelIndexArray0xc::VTable0x0c(LegoU32 p_count)
{
	if (m_unk0x04 != 0) {
		VTable0x08();
	}

	m_unk0x04 = p_count;
	m_unk0x08 = new Indices[m_unk0x04];
	if (m_unk0x08 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
}
