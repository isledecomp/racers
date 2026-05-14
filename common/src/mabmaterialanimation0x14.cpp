#include "mabmaterialanimation0x14.h"

#include "golbinparser.h"
#include "golerror.h"
#include "golfileparser.h"
#include "mabmaterialanimationitem0x18.h"
#include "mabmaterialanimationitem0x8.h"

DECOMP_SIZE_ASSERT(MabMaterialAnimation0x14, 0x14)

// FUNCTION: GOLDP 0x10025890
// FUNCTION: LEGORACERS 0x0040fea0
MabMaterialAnimation0x14::MabMaterialAnimation0x14()
{
	m_unk0x04 = NULL;
	m_unk0x08 = 0;
	m_unk0x0c = NULL;
	m_unk0x10 = 0;
}

// FUNCTION: GOLDP 0x100258b0
// FUNCTION: LEGORACERS 0x0040fec0
MabMaterialAnimation0x14::~MabMaterialAnimation0x14()
{
	VTable0x08();
}

// FUNCTION: GOLDP 0x100258f0
// FUNCTION: LEGORACERS 0x0040fed0
void MabMaterialAnimation0x14::VTable0x04(WhiteFalcon0x140* p_renderer, const LegoChar* p_fileName, LegoBool32 p_binary)
{
	if (m_unk0x0c != NULL) {
		VTable0x08();
	}

	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".mab");
	}
	else {
		parser = new MabTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_fileName);
	FUN_10025a40(p_renderer, *parser);
	FUN_10025b60(*parser);
	parser->Dispose();
	if (parser != NULL) {
		delete parser;
	}
}

// FUNCTION: GOLDP 0x10025a00
// FUNCTION: LEGORACERS 0x0040ffe0
void MabMaterialAnimation0x14::VTable0x08()
{
	if (m_unk0x04 != NULL) {
		delete[] m_unk0x04;
		m_unk0x04 = NULL;
	}
	if (m_unk0x0c != NULL) {
		delete[] m_unk0x0c;
		m_unk0x0c = NULL;
	}
	m_unk0x08 = 0;
	m_unk0x10 = 0;
}

// FUNCTION: GOLDP 0x10025a40
// FUNCTION: LEGORACERS 0x00410020
void MabMaterialAnimation0x14::FUN_10025a40(WhiteFalcon0x140* p_renderer, GolFileParser& p_parser)
{
	LegoU32 i;

	if (p_parser.GetNextToken() != GolFileParser::e_unknown0x27) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
	}

	m_unk0x08 = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_unk0x08 == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
	}

	m_unk0x04 = new MabMaterialAnimationItem0x8[m_unk0x08];
	if (m_unk0x04 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (i = 0; i < m_unk0x08; i++) {
		LegoChar name[8];
		::strncpy(name, p_parser.ReadStringWithMaxLength(sizeOfArray(name)), sizeof(name));
		m_unk0x04[i].FUN_10026110(p_renderer, name, p_parser.ReadInteger());
	}

	if (p_parser.GetNextToken() != GolFileParser::e_rightCurly) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_rightCurly);
	}
}

// FUNCTION: GOLDP 0x10025b60
// FUNCTION: LEGORACERS 0x00410140
void MabMaterialAnimation0x14::FUN_10025b60(GolFileParser& p_parser)
{
	LegoU32 i;

	if (p_parser.GetNextToken() != GolFileParser::e_unknown0x28) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
	}

	m_unk0x10 = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_unk0x10 == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
	}

	m_unk0x0c = new MabMaterialAnimationItem0x18[m_unk0x10];
	if (m_unk0x0c == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (i = 0; i < m_unk0x10; i++) {
		undefined4 param2 = 1;
		undefined4 param1 = 0;
		undefined4 param3 = 1;
		undefined4 param4 = 30;

		if (p_parser.GetNextToken() != GolFileParser::e_unknown0x28) {
			p_parser.HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		if (p_parser.GetNextToken() != GolFileParser::e_leftCurly) {
			p_parser.HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		GolFileParser::ParserTokenType token;
		while ((token = p_parser.GetNextToken()) != GolFileParser::e_rightCurly) {
			switch (token) {
			case GolFileParser::e_unknown0x27:
				param1 = p_parser.ReadInteger();
				param2 = p_parser.ReadInteger();
				break;
			case GolFileParser::e_unknown0x29:
				param3 = p_parser.ReadInteger();
				break;
			case GolFileParser::e_unknown0x2a:
				param4 = p_parser.ReadInteger();
				break;
			default:
				p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}

		m_unk0x0c[i].FUN_10025d40(param1, param2, param3, param4);
	}

	if (p_parser.GetNextToken() != GolFileParser::e_rightCurly) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_rightCurly);
	}
}
