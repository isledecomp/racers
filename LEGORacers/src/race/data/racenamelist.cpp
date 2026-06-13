#include "race/data/racenamelist.h"

#include "golbinparser.h"
#include "golerror.h"
#include "golname.h"

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
	m_positionInCircuit = 0;
	m_mirror = FALSE;
	m_stringTable = NULL;
	m_displayStringIndex = 0;
	::memset(m_name, 0, sizeof(m_name));
	::memset(m_folderName, 0, sizeof(m_folderName));
	::memset(m_themeName, 0, sizeof(m_themeName));
	::memset(m_mascotName, 0, sizeof(m_mascotName));
}

// FUNCTION: LEGORACERS 0x004364f0
void RaceNameEntry::Load(
	GolFileParser& p_parser,
	CircuitDefinitionList* p_raceList,
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
	GolName circuitName;
	while ((token = p_parser.GetNextToken()) != GolFileParser::e_rightCurly) {
		switch (token) {
		case c_tokenPositionInCircuit:
			m_positionInCircuit = p_parser.ReadInteger();
			break;
		case c_tokenFolderName:
			::strncpy(m_folderName, p_parser.ReadStringWithMaxLength(sizeof(m_folderName)), sizeof(m_folderName));
			break;
		case c_tokenCircuit:
			::strncpy(circuitName, p_parser.ReadStringWithMaxLength(sizeof(circuitName)), sizeof(circuitName));
			m_circuit = static_cast<CircuitDefinitionList::CircuitDefinition*>(p_raceList->GetName(circuitName));
			if (!m_circuit) {
				GOL_FATALERROR_MESSAGE("Unable to find circuit");
			}
			break;
		case c_tokenDisplayStringIndex:
			m_displayStringIndex = static_cast<LegoU16>(p_parser.ReadInteger());
			break;
		case c_tokenThemeName:
			::strncpy(m_themeName, p_parser.ReadStringWithMaxLength(sizeof(m_themeName)), sizeof(m_themeName));
			break;
		case c_tokenMascotName:
			::strncpy(m_mascotName, p_parser.ReadStringWithMaxLength(sizeof(m_mascotName)), sizeof(m_mascotName));
			break;
		case c_tokenMirror:
			m_mirror = TRUE;
			break;
		default:
			p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}
	}

	if (m_circuit) {
		m_circuit->SetRaceNameEntry(m_positionInCircuit, this);
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
	CircuitDefinitionList* p_raceList,
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

		GolName name;
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
