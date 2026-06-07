#include "model/carpartset.h"

#include "golbinparser.h"
#include "golerror.h"
#include "goltxtparser.h"
#include "model/legocolortable.h"
#include "model/legopiecelibrary.h"

#include <string.h>

DECOMP_SIZE_ASSERT(CarPartSet, 0x14)
DECOMP_SIZE_ASSERT(CarPartSet::PartChoice, 0x04)
DECOMP_SIZE_ASSERT(CarPartSet::Entry, 0x18)

// FUNCTION: LEGORACERS 0x0049cae0
CarPartSet::Entry::Entry()
{
	m_name[0] = '\0';
	m_pieceType = 0;
	m_choiceCount = 0;
	m_choices = NULL;
}

// FUNCTION: LEGORACERS 0x0049caf0
CarPartSet::Entry::~Entry()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void CarPartSet::Entry::FUN_004513d0(CarBuildModel*)
{
}

// FUNCTION: LEGORACERS 0x0049cb00
void CarPartSet::Entry::Clear()
{
	if (m_choices != NULL) {
		delete[] m_choices;
		m_choices = NULL;
	}

	m_pieceType = 0;
	m_choiceCount = 0;
}

// FUNCTION: LEGORACERS 0x0049cb30
void CarPartSet::Entry::Load(
	const LegoChar* p_filename,
	LegoPieceLibrary* p_pieceLibrary,
	LegoColorTable* p_verdantTide,
	undefined4 p_binary
)
{
	Clear();

	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".leb");
	}
	else {
		parser = new LegoPieceLibrary::LebTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_filename);
	if (!parser->IsOpen()) {
		GOL_FATALERROR_MESSAGE("Unable to open LEGO Car Set file");
	}

	GolFileParser::ParserTokenType token;
	while ((token = parser->GetNextToken()) != GolFileParser::e_syntaxerror) {
		switch (token) {
		case GolFileParser::e_unknown0x2e:
			m_pieceType = parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x30: {
			m_choiceCount = LegoPieceLibrary::ReadBracketedCountAndLeftCurly(parser);
			m_choices = new PartChoice[m_choiceCount];
			if (m_choices == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}

			for (LegoS32 i = 0; i < m_choiceCount; i++) {
				LegoPieceLibrary::PieceRecord* piece = p_pieceLibrary->FindPieceRecordByName(parser->ReadString());
				if (piece != NULL) {
					m_choices[i].m_pieceType = piece->m_pieceType;
				}
				else {
					m_choices[i].m_pieceType = 0;
				}
				m_choices[i].m_colorRecordIndex =
					static_cast<LegoU8>(p_verdantTide->FindColorRecordIndexByName(parser->ReadString()));
			}
			parser->ReadRightCurly();
			break;
		}
		case GolFileParser::e_unknown0x31:
			::strncpy(m_name, parser->ReadString(), sizeof(m_name));
			break;
		default:
			parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
			break;
		}
	}

	delete parser;
}

// FUNCTION: LEGORACERS 0x0049cd20
void CarPartSet::Entry::FillChoiceIndices(LegoS32* p_dest, LegoS32 p_startIndex, LegoS32 p_count)
{
	LegoS32 startIndex = p_startIndex;
	if (startIndex < 0) {
		startIndex = 0;
	}
	if (startIndex >= m_choiceCount) {
		startIndex %= m_choiceCount;
	}

	LegoS32 index = startIndex;
	if (p_count) {
		while (TRUE) {
			*p_dest++ = index;
			if (!--p_count) {
				break;
			}

			if (++index == m_choiceCount) {
				index = 0;
			}
			if (index == startIndex) {
				if (p_count) {
					startIndex = -1;
					::memset(p_dest, -1, sizeof(LegoS32) * p_count);
				}
				break;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x0049cd70
LegoS32 CarPartSet::Entry::NormalizeChoiceIndex(LegoS32 p_index)
{
	if (p_index < 0) {
		return -1;
	}

	FillChoiceIndices(&p_index, p_index, 1);
	return p_index;
}

// FUNCTION: LEGORACERS 0x0049cda0
LegoS32* CarPartSet::Entry::GetChoice(LegoS32 p_index, LegoS32* p_pieceType, LegoS32* p_colorRecordIndex)
{
	*p_pieceType = m_choices[p_index].m_pieceType;
	*p_colorRecordIndex = m_choices[p_index].m_colorRecordIndex;
	return p_colorRecordIndex;
}

// FUNCTION: LEGORACERS 0x0049cdd0
LegoS32 CarPartSet::Entry::FindChoiceIndex(LegoS32 p_pieceType, LegoS32 p_colorRecordIndex)
{
	for (LegoS32 i = 0; i < m_choiceCount; i++) {
		if (m_choices[i].m_pieceType == p_pieceType && m_choices[i].m_colorRecordIndex == p_colorRecordIndex) {
			return i;
		}
	}

	return -1;
}

// FUNCTION: LEGORACERS 0x0049ce10
CarPartSet::CarPartSet()
{
	m_pieceLibrary = NULL;
	m_verdantTide = NULL;
	m_entryCount = 0;
	m_entries = NULL;
	m_selectedEntry = 0;
}

// FUNCTION: LEGORACERS 0x0049ce30
CarPartSet::~CarPartSet()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x0049ce40
void CarPartSet::Clear()
{
	if (m_entries != NULL) {
		delete[] m_entries;
		m_entries = NULL;
	}

	m_entryCount = 0;
	m_pieceLibrary = NULL;
	m_verdantTide = NULL;
	m_selectedEntry = 0;
}

// FUNCTION: LEGORACERS 0x0049ce80
void CarPartSet::Load(
	const LegoChar* p_filename,
	LegoPieceLibrary* p_pieceLibrary,
	LegoColorTable* p_verdantTide,
	undefined4 p_binary
)
{
	Clear();
	m_verdantTide = p_verdantTide;
	m_pieceLibrary = p_pieceLibrary;

	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".leb");
	}
	else {
		parser = new LegoPieceLibrary::LebTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_filename);
	if (!parser->IsOpen()) {
		GOL_FATALERROR_MESSAGE("Unable to open LEGO Car Set file");
	}

	if (parser->GetNextToken() != GolFileParser::e_unknown0x2f) {
		parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
	}
	m_entryCount = LegoPieceLibrary::ReadBracketedCountAndLeftCurly(parser);
	m_entries = new Entry[m_entryCount];
	if (m_entries == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoChar* entryFiles = new LegoChar[m_entryCount * 16];
	LegoS32 i;
	for (i = 0; i < m_entryCount; i++) {
		::strncpy(&entryFiles[i * 16], parser->ReadString(), 16);
		entryFiles[i * 16 + 15] = '\0';
	}

	if (parser->GetNextToken() != GolFileParser::e_rightCurly) {
		parser->HandleUnexpectedToken(GolFileParser::e_rightCurly);
	}
	delete parser;

	for (i = 0; i < m_entryCount; i++) {
		m_entries[i].SetIndex(i);
		m_entries[i].Load(&entryFiles[i * 16], m_pieceLibrary, m_verdantTide, p_binary);
	}

	delete[] entryFiles;
}

// FUNCTION: LEGORACERS 0x0049d0b0
CarPartSet::Entry* CarPartSet::FindEntry(LegoS32 p_index)
{
	for (LegoS32 i = 0; i < m_entryCount; i++) {
		if (m_entries[i].GetPieceType() == p_index) {
			m_selectedEntry = &m_entries[i];
			return &m_entries[i];
		}
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x0049d0f0
LegoS32 CarPartSet::FindEntryIndex(LegoS32 p_index)
{
	for (LegoS32 i = 0; i < m_entryCount; i++) {
		if (m_entries[i].GetPieceType() == p_index) {
			return i;
		}
	}

	return -1;
}
