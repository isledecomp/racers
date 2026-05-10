#include "racenamelist.h"

#include "golbinparser.h"
#include "golerror.h"

#include <memory.h>
#include <string.h>

DECOMP_SIZE_ASSERT(RaceNameList, 0x14)
DECOMP_SIZE_ASSERT(RaceNameEntry, 0x38)
DECOMP_SIZE_ASSERT(RaceNameList::RcbTxtParser, 0x1fc)

// FUNCTION: LEGORACERS 0x00436490
RaceNameEntry::RaceNameEntry()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x004364a0
RaceNameEntry::~RaceNameEntry()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004364b0
void RaceNameEntry::Clear()
{
	m_loaded = FALSE;
	m_circuit = NULL;
	m_raceDefinitionIndex = 0;
	m_unk0x2c = FALSE;
	m_stringTable = NULL;
	m_unk0x34 = 0;
	::memset(m_name, 0, sizeof(m_name));
	::memset(m_unk0x0c, 0, sizeof(m_unk0x0c));
	::memset(m_unk0x14, 0, sizeof(m_unk0x14));
	::memset(m_unk0x1c, 0, sizeof(m_unk0x1c));
}

// FUNCTION: LEGORACERS 0x004364f0
void RaceNameEntry::Load(
	GolFileParser& p_parser,
	RaceDefinitionList* p_raceList,
	const LegoChar* p_name,
	GolStringTable* p_stringTable
)
{
	if (m_loaded) {
		Reset();
	}

	m_stringTable = p_stringTable;
	::strncpy(m_name, p_name, sizeof(m_name));
	m_loaded = TRUE;

	GolFileParser::ParserTokenType token;
	LegoChar circuitName[8];
	while ((token = p_parser.GetNextToken()) != GolFileParser::e_rightCurly) {
		switch (token) {
		case c_tokenRaceDefinitionIndex:
			m_raceDefinitionIndex = p_parser.ReadInteger();
			break;
		case c_tokenUnk0x0cName:
			::strncpy(m_unk0x0c, p_parser.ReadStringWithMaxLength(sizeof(m_unk0x0c)), sizeof(m_unk0x0c));
			break;
		case c_tokenCircuit:
			::strncpy(circuitName, p_parser.ReadStringWithMaxLength(sizeof(circuitName)), sizeof(circuitName));
			m_circuit = static_cast<RaceDefinitionList::RaceDefinition*>(p_raceList->GetName(circuitName));
			if (!m_circuit) {
				GOL_FATALERROR_MESSAGE("Unable to find circuit");
			}
			break;
		case c_tokenUnk0x34:
			m_unk0x34 = static_cast<LegoU16>(p_parser.ReadInteger());
			break;
		case c_tokenUnk0x14Name:
			::strncpy(m_unk0x14, p_parser.ReadStringWithMaxLength(sizeof(m_unk0x14)), sizeof(m_unk0x14));
			break;
		case c_tokenUnk0x1cName:
			::strncpy(m_unk0x1c, p_parser.ReadStringWithMaxLength(sizeof(m_unk0x1c)), sizeof(m_unk0x1c));
			break;
		case c_tokenFlag0x2c:
			m_unk0x2c = TRUE;
			break;
		default:
			p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}
	}

	if (m_circuit) {
		m_circuit->SetRaceNameEntry(m_raceDefinitionIndex, this);
	}
}

// FUNCTION: LEGORACERS 0x00436650
void RaceNameEntry::Reset()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x00436660
RaceNameList::RaceNameList()
{
	m_entries = NULL;
	m_entryCount = 0;
}

// FUNCTION: LEGORACERS 0x004366a0
RaceNameList::~RaceNameList()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x004366f0
void RaceNameList::Load(
	GolStringTable* p_stringTable,
	RaceDefinitionList* p_raceList,
	const LegoChar* p_fileName,
	undefined4 p_binary
)
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

		parser->SetSuffix(".rcb");
	}
	else {
		parser = new RcbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_fileName);
	parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(c_tokenRaceName));

	m_entryCount = parser->ReadBracketedCountAndLeftCurly();
	m_entries = new RaceNameEntry[m_entryCount];

	if (m_entries == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	GolNameTable::Allocate(m_entryCount);

	for (LegoU32 i = 0; i < m_entryCount; i++) {
		parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(c_tokenRaceName));

		LegoChar name[8];
		::strncpy(name, parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));
		parser->ReadLeftCurly();
		AddName(name, &m_entries[i]);
		m_entries[i].Load(*parser, p_raceList, name, p_stringTable);
	}

	parser->ReadRightCurly();
	parser->Dispose();

	if (parser != NULL) {
		delete parser;
	}
}

// FUNCTION: LEGORACERS 0x004368f0
void RaceNameList::Clear()
{
	if (m_entries) {
		delete[] m_entries;
		m_entries = NULL;
	}

	m_entryCount = 0;
}

// FUNCTION: LEGORACERS 0x00436930
LegoU32 RaceNameList::GetEntryIndexByName(LegoChar* p_name)
{
	RaceNameEntry* entry = static_cast<RaceNameEntry*>(GetName(p_name));
	return entry - m_entries;
}
