#include "cmbmodelpartdata0x28.h"

#include "golfileparser.h"

#include <float.h>

DECOMP_SIZE_ASSERT(CmbModelPartData0x28, 0x28)

// FUNCTION: GOLDP 0x10018640
// FUNCTION: LEGORACERS 0x00401000
CmbModelPartData0x28::CmbModelPartData0x28()
{
	m_unk0x24 = 0;
	m_unk0x26 = 0;
	m_unk0x20 = 0;
	m_unk0x00 = 0.0f;
	m_unk0x04.m_x = 0.0f;
	m_unk0x04.m_y = 0.0f;
	m_unk0x04.m_z = 0.0f;
	m_unk0x10.m_x = 0.0f;
	m_unk0x10.m_y = 0.0f;
	m_unk0x10.m_z = 0.0f;
	m_unk0x10.m_u = FLT_MAX / 2.0f;
}

// FUNCTION: GOLDP 0x10018670
// FUNCTION: LEGORACERS 0x00401030
void CmbModelPartData0x28::FUN_10018670(GolFileParser& p_parser)
{
	p_parser.ReadLeftCurly();
	GolFileParser::ParserTokenType token;

	while ((token = p_parser.GetNextToken()) != GolFileParser::e_rightCurly) {
		switch (token) {
		case GolFileParser::e_unknown0x2b:
			m_unk0x20 = p_parser.ReadInteger();
			break;
		case GolFileParser::e_unknown0x2d:
			if (p_parser.GetNextToken() != GolFileParser::e_int) {
				p_parser.HandleUnexpectedToken(GolFileParser::e_int);
			}
			m_unk0x24 = p_parser.GetUnk0x38();
			break;
		case GolFileParser::e_unknown0x2e:
			if (p_parser.GetNextToken() != GolFileParser::e_int) {
				p_parser.HandleUnexpectedToken(GolFileParser::e_int);
			}
			m_unk0x26 = p_parser.GetUnk0x38();
			break;
		case GolFileParser::e_unknown0x2f:
			m_unk0x00 = static_cast<LegoFloat>(p_parser.ReadInteger()) / 1000.0f;
			break;
		case GolFileParser::e_unknown0x30:
			m_unk0x04.m_x = p_parser.ReadFloat();
			m_unk0x04.m_y = p_parser.ReadFloat();
			m_unk0x04.m_z = p_parser.ReadFloat();
			break;
		case GolFileParser::e_unknown0x31:
			m_unk0x10.m_x = p_parser.ReadFloat();
			m_unk0x10.m_y = p_parser.ReadFloat();
			m_unk0x10.m_z = p_parser.ReadFloat();
			m_unk0x10.m_u = p_parser.ReadFloat();
			break;
		default:
			p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}
	}
}
