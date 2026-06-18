#include "golbinparser.h"
#include "golerror.h"
#include "race/racesession.h"

#include <stdlib.h>

DECOMP_SIZE_ASSERT(RaceSession::Field0x3104, 0x48)
DECOMP_SIZE_ASSERT(RaceSession::Field0x3104::RrbTxtParser, 0x1fc)

// FUNCTION: LEGORACERS 0x004a4e10
RaceSession::Field0x3104::Field0x3104()
{
	FUN_004a50c0();
}

// FUNCTION: LEGORACERS 0x004a4e20
RaceSession::Field0x3104::~Field0x3104()
{
	FUN_004a50a0();
}

// FUNCTION: LEGORACERS 0x004a4e30
void RaceSession::Field0x3104::FUN_004a4e30(const LegoChar* p_fileName, LegoBool32 p_binary, LegoBool32 p_mirror)
{
	if (m_unk0x04) {
		FUN_004a50a0();
	}

	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (!parser) {
			GolFatalError(c_golErrorOutOfMemory, NULL, 0);
		}
		parser->SetSuffix(".rrb");
	}
	else {
		parser = new RrbTxtParser;
		if (!parser) {
			GolFatalError(c_golErrorOutOfMemory, NULL, 0);
		}
	}

	parser->OpenFileForRead(p_fileName);

	GolFileParser::ParserTokenType token = parser->GetNextToken();
	while (token != GolFileParser::e_syntaxerror) {
		switch (token) {
		case GolFileParser::e_unknown0x27:
			FUN_004a5100(parser, p_mirror);
			break;
		case GolFileParser::e_unknown0x28:
			m_unk0x14 = parser->ReadFloat();
			m_unk0x18 = parser->ReadFloat();
			m_unk0x1c = parser->ReadFloat();
			m_unk0x20 = parser->ReadFloat();
			if (p_mirror) {
				m_unk0x18 = -m_unk0x18;
				m_unk0x20 = -m_unk0x20;
			}
			break;
		case GolFileParser::e_unknown0x29:
			m_unk0x08 = parser->ReadFloat();
			m_unk0x0c = parser->ReadFloat();
			m_unk0x10 = parser->ReadFloat();
			if (p_mirror) {
				m_unk0x0c = -m_unk0x0c;
			}
			break;
		case GolFileParser::e_unknown0x2a:
			m_unk0x24 = parser->ReadFloat();
			m_unk0x28 = parser->ReadFloat();
			m_unk0x2c = parser->ReadFloat();
			if (p_mirror) {
				m_unk0x28 = -m_unk0x28;
			}
			break;
		case GolFileParser::e_unknown0x2b:
			m_unk0x30 = parser->ReadFloat();
			m_unk0x34 = parser->ReadFloat();
			m_unk0x38 = parser->ReadFloat();
			m_unk0x3c = parser->ReadFloat();
			if (p_mirror) {
				m_unk0x34 = -m_unk0x34;
				m_unk0x3c = -m_unk0x3c;
			}
			break;
		case GolFileParser::e_unknown0x2c:
			m_unk0x40 = parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x2d:
			m_unk0x44 = parser->ReadInteger();
			break;
		default:
			break;
		}

		token = parser->GetNextToken();
	}

	if (static_cast<LegoU32>(m_unk0x44) >= static_cast<LegoU32>(m_unk0x00)) {
		parser->HandleUnexpectedToken(GolFileParser::e_invalidValue);
	}

	parser->Dispose();
	delete parser;
}

// FUNCTION: LEGORACERS 0x004a50a0
void RaceSession::Field0x3104::FUN_004a50a0()
{
	if (m_unk0x04) {
		delete[] m_unk0x04;
	}

	FUN_004a50c0();
}

// FUNCTION: LEGORACERS 0x004a50c0
void RaceSession::Field0x3104::FUN_004a50c0()
{
	m_unk0x00 = 0;
	m_unk0x04 = NULL;
	m_unk0x08 = 0;
	m_unk0x0c = 0;
	m_unk0x10 = 0;
	m_unk0x14 = 0;
	m_unk0x18 = 0;
	m_unk0x1c = 0;
	m_unk0x20 = 1.0f;
	m_unk0x24 = 0;
	m_unk0x28 = 0;
	m_unk0x2c = 0;
	m_unk0x30 = 0;
	m_unk0x34 = 0;
	m_unk0x38 = 0;
	m_unk0x3c = 1.0f;
	m_unk0x40 = 0;
	m_unk0x44 = 0;
}

// FUNCTION: LEGORACERS 0x004a5100
void RaceSession::Field0x3104::FUN_004a5100(GolFileParser* p_parser, LegoBool32 p_mirror)
{
	m_unk0x00 = p_parser->ReadBracketedCountAndLeftCurly();
	m_unk0x04 = new RaceState::Racer::Field0x00c::Entry::PathPoint[m_unk0x00];
	if (!m_unk0x04) {
		GolFatalError(c_golErrorOutOfMemory, NULL, 0);
	}

	for (LegoU32 i = 0; i < static_cast<LegoU32>(m_unk0x00); i++) {
		m_unk0x04[i].FUN_004a5e10(p_parser, p_mirror);
	}

	p_parser->ReadRightCurly();
}
