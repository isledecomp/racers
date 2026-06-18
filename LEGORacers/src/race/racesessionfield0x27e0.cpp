#include "golbinparser.h"
#include "golerror.h"
#include "race/racesession.h"

#include <stdlib.h>
#include <string.h>

DECOMP_SIZE_ASSERT(RaceSession::Field0x27e0, 0x14)
DECOMP_SIZE_ASSERT(RaceSession::Field0x27e0::Entry, 0x5c)
DECOMP_SIZE_ASSERT(RaceSession::Field0x27e0::TmbTxtParser, 0x1fc)

// FUNCTION: LEGORACERS 0x00443c90
RaceSession::Field0x27e0::Entry::Entry()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00443ca0
void RaceSession::Field0x27e0::Entry::Reset()
{
	m_name[0] = '\0';
	m_flags = 0;
	m_unk0x0c = 0;
	m_unk0x10 = 0;
	m_unk0x14 = 0;
	m_unk0x18 = 0;
	m_unk0x1c.m_x = 0.0f;
	m_unk0x1c.m_y = 0.0f;
	m_unk0x1c.m_z = 0.0f;
	m_unk0x28.m_x = 0.0f;
	m_unk0x28.m_y = 0.0f;
	m_unk0x28.m_z = 0.0f;
	m_unk0x34 = 0;
	m_unk0x38 = 0;
	m_unk0x3c = 0;
	m_unk0x40[0] = '\0';
	m_unk0x48 = 0.0f;
	m_unk0x4c = 0.0f;
	m_unk0x50 = 0.0f;
	m_unk0x54 = 0.0f;
	m_unk0x58 = 0.0f;
}

// FUNCTION: LEGORACERS 0x00443cf0
void RaceSession::Field0x27e0::Entry::FUN_00443cf0(GolFileParser* p_parser, LegoBool32 p_mirror)
{
	if (m_flags & c_flagLoaded) {
		FUN_00443f90();
	}

	p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
	::memcpy(m_name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	if (token != GolFileParser::e_rightCurly) {
		do {
			switch (token) {
			case GolFileParser::e_unknown0x28:
				m_unk0x0c = p_parser->ReadInteger();
				m_flags |= c_flagUnk0x0c;
				break;
			case GolFileParser::e_unknown0x29:
				m_unk0x10 = p_parser->ReadInteger();
				m_flags |= c_flagUnk0x10;
				break;
			case GolFileParser::e_unknown0x2a:
				m_unk0x14 = p_parser->ReadInteger();
				m_flags |= c_flagUnk0x14;
				break;
			case GolFileParser::e_unknown0x2b:
				m_unk0x18 = p_parser->ReadInteger();
				m_flags |= c_flagUnk0x18;
				break;
			case GolFileParser::e_unknown0x2c:
				m_unk0x1c.m_x = p_parser->ReadFloat();
				m_unk0x1c.m_y = p_parser->ReadFloat();
				m_unk0x1c.m_z = p_parser->ReadFloat();
				m_flags |= c_flagUnk0x1c;
				if (p_mirror) {
					m_unk0x1c.m_y = -m_unk0x1c.m_y;
				}
				break;
			case GolFileParser::e_unknown0x2d:
				m_unk0x28.m_x = p_parser->ReadFloat();
				m_unk0x28.m_y = p_parser->ReadFloat();
				m_unk0x28.m_z = p_parser->ReadFloat();
				m_flags |= c_flagUnk0x28;
				if (p_mirror) {
					m_unk0x28.m_y = -m_unk0x28.m_y;
				}
				break;
			case GolFileParser::e_unknown0x2e:
				m_unk0x34 = p_parser->ReadInteger();
				m_flags |= c_flagUnk0x34;
				break;
			case GolFileParser::e_unknown0x2f:
				m_unk0x38 = p_parser->ReadInteger();
				m_flags |= c_flagUnk0x38;
				break;
			case GolFileParser::e_unknown0x30:
				m_unk0x3c = p_parser->ReadInteger();
				m_flags |= c_flagUnk0x3c;
				break;
			case GolFileParser::e_unknown0x31:
				::memcpy(m_unk0x40, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
				m_flags |= c_flagUnk0x40;
				break;
			case GolFileParser::e_unknown0x32:
				m_unk0x48 = p_parser->ReadFloat();
				m_flags |= c_flagUnk0x48;
				break;
			case GolFileParser::e_unknown0x33:
				m_unk0x4c = p_parser->ReadFloat();
				m_flags |= c_flagUnk0x4c;
				break;
			case GolFileParser::e_unknown0x34:
				m_unk0x50 = p_parser->ReadFloat();
				m_flags |= c_flagUnk0x50;
				break;
			case GolFileParser::e_unknown0x35:
				m_unk0x54 = p_parser->ReadFloat();
				m_flags |= c_flagUnk0x54;
				break;
			case GolFileParser::e_unknown0x36:
				m_unk0x58 = p_parser->ReadFloat();
				m_flags |= c_flagUnk0x58;
				break;
			case GolFileParser::e_unknown0x37:
				m_flags |= c_flagBit16;
				break;
			case GolFileParser::e_unknown0x38:
				m_flags |= c_flagBit17;
				break;
			case GolFileParser::e_unknown0x39:
				m_flags |= c_flagBit18;
				break;
			default:
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}

			token = p_parser->GetNextToken();
		} while (token != GolFileParser::e_rightCurly);
	}

	m_flags |= c_flagLoaded;
}

// FUNCTION: LEGORACERS 0x00443f90
void RaceSession::Field0x27e0::Entry::FUN_00443f90()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00443fa0
RaceSession::Field0x27e0::Field0x27e0()
{
	m_count = 0;
	m_entries = NULL;
}

// FUNCTION: LEGORACERS 0x00443fe0
RaceSession::Field0x27e0::~Field0x27e0()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x00444030
void RaceSession::Field0x27e0::FUN_00444030(const LegoChar* p_name, LegoBool32 p_binary, LegoBool32 p_mirror)
{
	if (m_entries) {
		Clear();
	}

	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".tmb");
	}
	else {
		parser = new TmbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_name);
	parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
	m_count = parser->ReadBracketedCountAndLeftCurly();
	GolNameTable::Allocate(m_count);

	m_entries = new Entry[m_count];
	if (m_entries == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_count; i++) {
		m_entries[i].FUN_00443cf0(parser, p_mirror);

		GolName name;
		::memcpy(name, m_entries[i].GetName(), sizeof(GolName));
		AddName(name, &m_entries[i]);
	}

	parser->ReadRightCurly();
	parser->Dispose();
	if (parser != NULL) {
		delete parser;
	}
}

// FUNCTION: LEGORACERS 0x00444210
void RaceSession::Field0x27e0::Clear()
{
	if (m_entries) {
		delete[] m_entries;
		m_entries = NULL;
	}

	if (m_nameEntries) {
		GolNameTable::Clear();
	}

	m_count = 0;
}
