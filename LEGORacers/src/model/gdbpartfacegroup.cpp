#include "model/gdbpartfacegroup.h"

#include "golerror.h"
#include "golfileparser.h"

#include <string.h>

DECOMP_SIZE_ASSERT(GdbPartFaceGroup, 0x14)

// FUNCTION: LEGORACERS 0x00407e70
GdbPartFaceGroup::GdbPartFaceGroup()
{
	m_indices = NULL;
	m_materialName[0] = '\0';
	m_triangleCount = 0;
	m_unk0x10 = 0;
}

// FUNCTION: LEGORACERS 0x00407e80
GdbPartFaceGroup::~GdbPartFaceGroup()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x00407e90
void GdbPartFaceGroup::Read(GolFileParser& p_parser)
{
	p_parser.AssertNextTokenIs(GolFileParser::e_unknown0x2b);
	p_parser.ReadLeftCurly();
	GolFileParser::ParserTokenType token = p_parser.GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case GolFileParser::e_unknown0x27:
			p_parser.ReadStringWithMaxLength(sizeof(m_materialName));
			::strncpy(m_materialName, p_parser.GetLastString(), sizeof(m_materialName));
			break;
		case GolFileParser::e_unknown0x2a: {
			m_triangleCount = static_cast<LegoU16>(p_parser.ReadBracketedCountAndLeftCurly());
			LegoU32 indexCount = m_triangleCount * 3;
			m_indices = new LegoU16[indexCount];
			if (m_indices == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}
			for (LegoU32 i = 0; i < indexCount; i++) {
				m_indices[i] = static_cast<LegoU16>(p_parser.ReadInteger());
			}
			p_parser.ReadRightCurly();
			break;
		}
		default:
			p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}

		token = p_parser.GetNextToken();
	}
}

// FUNCTION: LEGORACERS 0x00407f60
void GdbPartFaceGroup::Clear()
{
	if (m_indices != NULL) {
		delete[] m_indices;
		m_indices = NULL;
	}
	m_triangleCount = 0;
	m_unk0x10 = 0;
}
