#include "menu/style/menuresourcetable.h"

#include "golname.h"
#include "menu/style/menubindingtoken.h"

#include <string.h>

DECOMP_SIZE_ASSERT(MenuResourceTable, 0x20)

// FUNCTION: LEGORACERS 0x0046aff0
void* MenuResourceTable::ResolveEntryByName(const LegoChar* p_name)
{
	GolName name;

	::strncpy(name, p_name, sizeof(name));
	return GetName(name);
}

// FUNCTION: LEGORACERS 0x0046b020
MenuResourceTable::MenuResourceTable()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046b090
MenuResourceTable::~MenuResourceTable()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x0046b0e0
void MenuResourceTable::Reset()
{
	m_parser = NULL;
	m_renderer = NULL;
	m_entryCapacity = 0;
	m_entryCount = 0;
	m_loaded = FALSE;
}

// FUNCTION: LEGORACERS 0x0046b100
LegoBool32 MenuResourceTable::BeginLoad()
{
	m_loaded = TRUE;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0046b110
void MenuResourceTable::Clear()
{
	if (m_nameEntries) {
		GolNameTable::Clear();
		Reset();
	}
}

// FUNCTION: LEGORACERS 0x0046b130
LegoS32 MenuResourceTable::ReadHeader()
{
	if (m_parser->GetNextToken() != c_resourceHeader) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
	}

	m_entryCapacity = m_parser->ReadInteger();
	GolNameTable::Allocate(m_entryCapacity);
	return m_entryCapacity;
}

// FUNCTION: LEGORACERS 0x0046b170
LegoS32 MenuResourceTable::ReadSectionCount()
{
	if (m_parser->GetNextToken() != GolFileParser::e_leftBracket) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftBracket);
	}

	LegoS32 count = m_parser->ReadInteger();
	m_entryCount += count;
	if (m_parser->GetNextToken() != GolFileParser::e_rightBracket) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_rightBracket);
	}

	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	return count;
}

// FUNCTION: LEGORACERS 0x0046b1d0
void MenuResourceTable::ReadRect(LegoS32* p_ints)
{
	p_ints[0] = m_parser->ReadInteger();
	p_ints[1] = m_parser->ReadInteger();
	p_ints[2] = m_parser->ReadInteger();
	p_ints[3] = m_parser->ReadInteger();
}

// FUNCTION: LEGORACERS 0x0046b210
void MenuResourceTable::ReadVisualState(LegoS8* p_ints)
{
	p_ints[3] = m_parser->ReadInteger();
	p_ints[0] = m_parser->ReadInteger();
	p_ints[1] = m_parser->ReadInteger();
	p_ints[2] = m_parser->ReadInteger();
}

// FUNCTION: LEGORACERS 0x0046b250
void MenuResourceTable::ParseSections()
{
	GolFileParser::ParserTokenType token;

	while ((token = m_parser->GetNextToken()) != 0) {
		ParseSection(token);
		token = m_parser->GetNextToken();
		if (token != GolFileParser::e_rightCurly) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_rightCurly);
		}
	}
}
