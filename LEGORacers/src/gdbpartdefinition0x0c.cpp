#include "gdbpartdefinition0x0c.h"

#include "golfileparser.h"

DECOMP_SIZE_ASSERT(GdbPartDefinition0x0c, 0x0c)

// FUNCTION: LEGORACERS 0x00407440
GdbPartDefinition0x0c::GdbPartDefinition0x0c()
{
	m_groupCount = 0;
	m_scale = 1.0f;
	m_groups = NULL;
}

// FUNCTION: LEGORACERS 0x00407460
GdbPartDefinition0x0c::~GdbPartDefinition0x0c()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x00407470
void GdbPartDefinition0x0c::Read(GolFileParser& p_parser)
{
	if (m_groups != NULL) {
		Clear();
	}

	p_parser.ReadLeftCurly();
	GolFileParser::ParserTokenType token = p_parser.GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case GolFileParser::e_unknown0x2b: {
			m_groupCount = p_parser.ReadBracketedCountAndLeftCurly();
			m_groups = new GdbPartFaceGroup0x14[m_groupCount];
			for (LegoU32 i = 0; i < m_groupCount; i++) {
				m_groups[i].Read(p_parser);
			}
			p_parser.ReadRightCurly();
			break;
		}
		case GolFileParser::e_unknown0x2d:
			m_scale = p_parser.ReadFloat();
			break;
		default:
			p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}

		token = p_parser.GetNextToken();
	}
}

// FUNCTION: LEGORACERS 0x00407580
void GdbPartDefinition0x0c::Clear()
{
	if (m_groups != NULL) {
		delete[] m_groups;
		m_groups = NULL;
	}
	m_groupCount = 0;
}
