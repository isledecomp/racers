#include "race/racerouterecord.h"

#include "golbinparser.h"
#include "golerror.h"

#include <stdlib.h>

DECOMP_SIZE_ASSERT(RaceRouteRecord, 0x48)
DECOMP_SIZE_ASSERT(RaceRouteRecord::RrbTxtParser, 0x1fc)

// FUNCTION: LEGORACERS 0x004a4e10
RaceRouteRecord::RaceRouteRecord()
{
	FUN_004a50c0();
}

// FUNCTION: LEGORACERS 0x004a4e20
RaceRouteRecord::~RaceRouteRecord()
{
	FUN_004a50a0();
}

// FUNCTION: LEGORACERS 0x004a4e30
void RaceRouteRecord::FUN_004a4e30(const LegoChar* p_fileName, LegoBool32 p_binary, LegoBool32 p_mirror)
{
	if (m_unk0x004) {
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
			m_unk0x014.m_x = parser->ReadFloat();
			m_unk0x014.m_y = parser->ReadFloat();
			m_unk0x014.m_z = parser->ReadFloat();
			m_unk0x014.m_w = parser->ReadFloat();
			if (p_mirror) {
				m_unk0x014.m_y = -m_unk0x014.m_y;
				m_unk0x014.m_w = -m_unk0x014.m_w;
			}
			break;
		case GolFileParser::e_unknown0x29:
			m_unk0x008.m_x = parser->ReadFloat();
			m_unk0x008.m_y = parser->ReadFloat();
			m_unk0x008.m_z = parser->ReadFloat();
			if (p_mirror) {
				m_unk0x008.m_y = -m_unk0x008.m_y;
			}
			break;
		case GolFileParser::e_unknown0x2a:
			m_unk0x024.m_x = parser->ReadFloat();
			m_unk0x024.m_y = parser->ReadFloat();
			m_unk0x024.m_z = parser->ReadFloat();
			if (p_mirror) {
				m_unk0x024.m_y = -m_unk0x024.m_y;
			}
			break;
		case GolFileParser::e_unknown0x2b:
			m_unk0x030.m_x = parser->ReadFloat();
			m_unk0x030.m_y = parser->ReadFloat();
			m_unk0x030.m_z = parser->ReadFloat();
			m_unk0x030.m_w = parser->ReadFloat();
			if (p_mirror) {
				m_unk0x030.m_y = -m_unk0x030.m_y;
				m_unk0x030.m_w = -m_unk0x030.m_w;
			}
			break;
		case GolFileParser::e_unknown0x2c:
			m_unk0x040 = parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x2d:
			m_unk0x044 = parser->ReadInteger();
			break;
		default:
			break;
		}

		token = parser->GetNextToken();
	}

	if (static_cast<LegoU32>(m_unk0x044) >= static_cast<LegoU32>(m_unk0x000)) {
		parser->HandleUnexpectedToken(GolFileParser::e_invalidValue);
	}

	parser->Dispose();
	delete parser;
}

// FUNCTION: LEGORACERS 0x004a50a0
void RaceRouteRecord::FUN_004a50a0()
{
	if (m_unk0x004) {
		delete[] m_unk0x004;
	}

	FUN_004a50c0();
}

// FUNCTION: LEGORACERS 0x004a50c0
void RaceRouteRecord::FUN_004a50c0()
{
	m_unk0x000 = 0;
	m_unk0x004 = NULL;
	m_unk0x008.m_x = 0;
	m_unk0x008.m_y = 0;
	m_unk0x008.m_z = 0;
	m_unk0x014.m_x = 0;
	m_unk0x014.m_y = 0;
	m_unk0x014.m_z = 0;
	m_unk0x014.m_w = 1.0f;
	m_unk0x024.m_x = 0;
	m_unk0x024.m_y = 0;
	m_unk0x024.m_z = 0;
	m_unk0x030.m_x = 0;
	m_unk0x030.m_y = 0;
	m_unk0x030.m_z = 0;
	m_unk0x030.m_w = 1.0f;
	m_unk0x040 = 0;
	m_unk0x044 = 0;
}

// FUNCTION: LEGORACERS 0x004a5100
void RaceRouteRecord::FUN_004a5100(GolFileParser* p_parser, LegoBool32 p_mirror)
{
	m_unk0x000 = p_parser->ReadBracketedCountAndLeftCurly();
	m_unk0x004 = new RaceState::Racer::Field0x00c::Entry::PathPoint[m_unk0x000];
	if (!m_unk0x004) {
		GolFatalError(c_golErrorOutOfMemory, NULL, 0);
	}

	for (LegoU32 i = 0; i < static_cast<LegoU32>(m_unk0x000); i++) {
		m_unk0x004[i].FUN_004a5e10(p_parser, p_mirror);
	}

	p_parser->ReadRightCurly();
}
