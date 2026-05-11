#include "cmbmodelpart0x34.h"

#include "cmbmodelpartdata0x28.h"
#include "golbinparser.h"
#include "golerror.h"

DECOMP_SIZE_ASSERT(CmbModelPart0x34, 0x34)

// FUNCTION: GOLDP 0x100187e0
// FUNCTION: LEGORACERS 0x004011a0
CmbModelPart0x34::CmbModelPart0x34()
{
	m_unk0x24 = NULL;
	m_unk0x28 = 0;
	m_unk0x2c = NULL;
	m_unk0x30 = 0;
}

// FUNCTION: GOLDP 0x10018840
// FUNCTION: LEGORACERS 0x00401200
CmbModelPart0x34::~CmbModelPart0x34()
{
	Clear();
}

// FUNCTION: GOLDP 0x100188e0
// FUNCTION: LEGORACERS 0x00401260
void CmbModelPart0x34::VTable0x14(const LegoChar* p_name, LegoBool32 p_binary)
{
	if (m_unk0x2c) {
		Clear();
	}
	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".adb");
	}
	else {
		parser = new AdbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}
	parser->OpenFileForRead(p_name);
	GolFileParser::ParserTokenType token;
	while ((token = parser->GetNextToken()) != GolFileParser::e_syntaxerror) {
		switch (token) {
		case GolFileParser::e_unknown0x27:
			m_data.FUN_100241d0(*parser);
			break;
		case GolFileParser::e_unknown0x2b:
			VTable0x0c(*parser);
			break;
		case GolFileParser::e_unknown0x2c:
			VTable0x10(*parser);
			break;
		default:
			parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}
	}
	parser->Dispose();
	if (parser != NULL) {
		delete parser;
	}
}

// FUNCTION: GOLDP 0x10018a30
// FUNCTION: LEGORACERS 0x004013b0
void CmbModelPart0x34::Clear()
{
	m_data.Clear();

	if (m_unk0x24 != NULL) {
		delete[] m_unk0x24;
		m_unk0x24 = NULL;
	}

	if (m_unk0x2c != NULL) {
		delete[] m_unk0x2c;
		m_unk0x2c = NULL;
	}

	GolNameTable::Clear();
	m_unk0x28 = 0;
	m_unk0x30 = 0;
}

// FUNCTION: GOLDP 0x10018a80
// FUNCTION: LEGORACERS 0x00401400
void CmbModelPart0x34::VTable0x0c(GolFileParser& p_parser)
{
	m_unk0x28 = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_unk0x28 == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_unk0x24 = new Data0x14[m_unk0x28];
	if (m_unk0x24 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	LegoU32 i;
	for (i = 0; i < m_unk0x28; i++) {
		m_unk0x24[i].m_unk0x00 = p_parser.ReadInteger();
		m_unk0x24[i].m_unk0x04 = p_parser.ReadInteger();
		m_unk0x24[i].m_unk0x10 = p_parser.ReadInteger();
		m_unk0x24[i].m_unk0x08 = p_parser.ReadInteger();
		m_unk0x24[i].m_unk0x0c = p_parser.ReadInteger();
		m_unk0x24[i].m_unk0x12 = p_parser.ReadInteger();
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x10018b40
// FUNCTION: LEGORACERS 0x004014c0
void CmbModelPart0x34::VTable0x10(GolFileParser& p_parser)
{
	m_unk0x30 = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_unk0x30 == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_unk0x2c = new CmbModelPartData0x28[m_unk0x30];
	if (m_unk0x2c == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	GolNameTable::Allocate(m_unk0x30);
	LegoU32 i;
	for (i = 0; i < m_unk0x30; i++) {
		if (p_parser.GetNextToken() != GolFileParser::e_unknown0x2c) {
			p_parser.HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}
		LegoChar name[8];
		::strncpy(name, p_parser.ReadString(), sizeOfArray(name));
		AddName(name, &m_unk0x2c[i]);
		m_unk0x2c[i].FUN_10018670(p_parser);
	}
	p_parser.ReadRightCurly();
}
