#include "golbinparser.h"
#include "golerror.h"
#include "race/racesession.h"

DECOMP_SIZE_ASSERT(RaceSession::Field0x2804::Entry, 0x14)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2804, 0x08)

// FUNCTION: LEGORACERS 0x0045c340
RaceSession::Field0x2804::Entry::Entry()
{
	m_unk0x00.m_x = 0.0f;
	m_unk0x00.m_y = 0.0f;
	m_unk0x00.m_z = 0.0f;
	m_unk0x0c = -1;
	m_flags0x10 = 0;
}

// FUNCTION: LEGORACERS 0x0045c360
RaceSession::Field0x2804::Entry::~Entry()
{
	m_unk0x0c = -1;
	m_unk0x00.m_x = 0.0f;
	m_unk0x00.m_y = 0.0f;
	m_unk0x00.m_z = 0.0f;
	m_flags0x10 = 0;
}

// FUNCTION: LEGORACERS 0x0045c380
void RaceSession::Field0x2804::Entry::FUN_0045c380(GolVec3* p_unk0x04, LegoS32 p_unk0x08)
{
	m_unk0x00.m_x = p_unk0x04->m_x;
	m_unk0x00.m_y = p_unk0x04->m_y;
	m_unk0x00.m_z = p_unk0x04->m_z;
	m_unk0x0c = p_unk0x08;
	m_flags0x10 |= 3;
}

// FUNCTION: LEGORACERS 0x0045c3b0 FOLDED
RaceSession::Field0x2804::Field0x2804()
{
	m_entries = NULL;
	m_count = 0;
}

// FUNCTION: LEGORACERS 0x0045c3c0
RaceSession::Field0x2804::~Field0x2804()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0045c3d0
void RaceSession::Field0x2804::FUN_0045c3d0(const LegoChar* p_name, LegoBool32 p_binary, LegoBool32 p_mirror)
{
	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".tgb");
	}
	else {
		parser = new TgbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_name);
	parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
	m_count = parser->ReadBracketedCountAndLeftCurly();

	if (!m_count) {
		parser->Dispose();
		if (parser != NULL) {
			delete parser;
		}

		return;
	}

	m_entries = new Entry[m_count];
	if (m_entries == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_count; i++) {
		parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
		parser->ReadLeftCurly();

		GolVec3 position;
		position.m_x = 0.0f;
		position.m_y = 0.0f;
		position.m_z = 0.0f;
		LegoS32 index = -1;

		GolFileParser::ParserTokenType token = parser->GetNextToken();
		while (token != GolFileParser::e_rightCurly) {
			switch (token) {
			case GolFileParser::e_unknown0x28:
				position.m_x = parser->ReadFloat();
				position.m_y = parser->ReadFloat();
				position.m_z = parser->ReadFloat();
				if (p_mirror) {
					position.m_y = -position.m_y;
				}
				break;
			case GolFileParser::e_unknown0x29:
				index = parser->ReadInteger();
				break;
			default:
				parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}

			token = parser->GetNextToken();
		}

		m_entries[i].FUN_0045c380(&position, index);
	}

	parser->ReadRightCurly();
	parser->Dispose();
	if (parser != NULL) {
		delete parser;
	}
}

// FUNCTION: LEGORACERS 0x0045c620
void RaceSession::Field0x2804::Reset()
{
	if (m_entries) {
		delete[] m_entries;
		m_entries = NULL;
	}

	m_count = 0;
}
