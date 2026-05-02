#include "racedefinitionlist.h"

#include "golbinparser.h"
#include "golerror.h"

#include <string.h>

DECOMP_SIZE_ASSERT(RaceDefinitionList, 0x14)
DECOMP_SIZE_ASSERT(RaceDefinitionList::RaceDefinition, 0x64)
DECOMP_SIZE_ASSERT(RaceDefinitionList::CrbTxtParser, 0x1fc)

// FUNCTION: LEGORACERS 0x0041efc0
RaceDefinitionList::RaceDefinition::RaceDefinition()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x0041efd0
RaceDefinitionList::RaceDefinition::~RaceDefinition()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0041efe0
void RaceDefinitionList::RaceDefinition::Clear()
{
	m_loaded = FALSE;
	m_courseCount = 0;
	m_stringIndex = -1;
	m_stringTable = NULL;
	m_circuit = 0;
	::memset(m_name, 0, sizeof(m_name));
	::memset(m_menuName, 0, sizeof(m_menuName));
	::memset(m_courseNames, 0, sizeof(m_courseNames));
	::memset(m_raceNameEntries, 0, sizeof(m_raceNameEntries));
}

// FUNCTION: LEGORACERS 0x0041f030
void RaceDefinitionList::RaceDefinition::Load(
	GolFileParser& p_parser,
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
	LegoU32 i;
	while ((token = p_parser.GetNextToken()) != GolFileParser::e_rightCurly) {
		switch (token) {
		case c_tokenCourseList:
			m_courseCount = p_parser.FUN_100327e0();

			for (i = 0; i < m_courseCount; i++) {
				::strncpy(
					m_courseNames[i],
					p_parser.ReadStringWithMaxLength(sizeof(m_courseNames[i])),
					sizeof(m_courseNames[i])
				);
			}

			p_parser.ReadRightCurly();
			break;
		case c_tokenCircuit:
			m_circuit = static_cast<LegoU16>(p_parser.ReadInteger());
			break;
		case c_tokenStringIndex:
			m_stringIndex = p_parser.ReadInteger();
			break;
		case c_tokenMenuName:
			::strncpy(m_menuName, p_parser.ReadString(), sizeof(m_menuName));
			break;
		default:
			p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x0041f130
void RaceDefinitionList::RaceDefinition::Reset()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x0041f140
RaceDefinitionList::RaceDefinitionList()
{
	m_entries = NULL;
	m_entryCount = 0;
}

// FUNCTION: LEGORACERS 0x0041f180
RaceDefinitionList::~RaceDefinitionList()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x0041f1d0
void RaceDefinitionList::Load(GolStringTable* p_stringTable, const LegoChar* p_fileName, undefined4 p_binary)
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

		parser->SetSuffix(".crb");
	}
	else {
		parser = new CrbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_fileName);
	parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(c_tokenRaceDefinition));

	LegoU32 entryCount = parser->FUN_100327e0();
	m_entryCount = entryCount;
	m_entries = new RaceDefinition[entryCount];

	if (m_entries == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	GolNameTable::Allocate(m_entryCount);

	for (LegoU32 i = 0; i < m_entryCount; i++) {
		parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(c_tokenRaceDefinition));

		LegoChar name[8];
		::strncpy(name, parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));
		parser->ReadLeftCurly();
		AddName(name, &m_entries[i]);
		m_entries[i].Load(*parser, name, p_stringTable);
	}

	parser->ReadRightCurly();
	parser->Dispose();

	if (parser != NULL) {
		delete parser;
	}
}

// FUNCTION: LEGORACERS 0x0041f3c0
void RaceDefinitionList::Clear()
{
	if (m_entries) {
		delete[] m_entries;
		m_entries = NULL;
	}

	m_entryCount = 0;
}
