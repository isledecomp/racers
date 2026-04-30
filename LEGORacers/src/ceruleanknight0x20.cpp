#include "ceruleanknight0x20.h"

DECOMP_SIZE_ASSERT(CeruleanKnight0x20, 0x20)

// FUNCTION: LEGORACERS 0x0046b020
CeruleanKnight0x20::CeruleanKnight0x20()
{
	VTable0x0c();
}

// FUNCTION: LEGORACERS 0x0046b090
CeruleanKnight0x20::~CeruleanKnight0x20()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x0046b0e0
void CeruleanKnight0x20::VTable0x0c()
{
	m_unk0x10 = 0;
	m_unk0x14 = 0;
	m_unk0x1c = 0;
	m_unk0x18 = 0;
	m_unk0x0c = 0;
}

// FUNCTION: LEGORACERS 0x0046b110
void CeruleanKnight0x20::Clear()
{
	if (m_nameEntries) {
		GolNameTable::Clear();
		VTable0x0c();
	}
}

// FUNCTION: LEGORACERS 0x0046b130
LegoS32 CeruleanKnight0x20::FUN_0046b130()
{
	if (m_unk0x10->GetNextToken() != GolFileParser::e_unknown0x27) {
		m_unk0x10->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
	}

	m_unk0x1c = m_unk0x10->ReadInteger();
	GolNameTable::Allocate(m_unk0x1c);
	return m_unk0x1c;
}

// FUNCTION: LEGORACERS 0x0046b170
LegoS32 CeruleanKnight0x20::FUN_0046b170()
{
	if (m_unk0x10->GetNextToken() != GolFileParser::e_leftBracket) {
		m_unk0x10->HandleUnexpectedToken(GolFileParser::e_leftBracket);
	}

	LegoS32 count = m_unk0x10->ReadInteger();
	m_unk0x18 += count;
	if (m_unk0x10->GetNextToken() != GolFileParser::e_rightBracket) {
		m_unk0x10->HandleUnexpectedToken(GolFileParser::e_rightBracket);
	}

	if (m_unk0x10->GetNextToken() != GolFileParser::e_leftCurly) {
		m_unk0x10->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	return count;
}

// FUNCTION: LEGORACERS 0x0046b1d0
void CeruleanKnight0x20::FUN_0046b1d0(LegoS32* p_ints)
{
	p_ints[0] = m_unk0x10->ReadInteger();
	p_ints[1] = m_unk0x10->ReadInteger();
	p_ints[2] = m_unk0x10->ReadInteger();
	p_ints[3] = m_unk0x10->ReadInteger();
}

// FUNCTION: LEGORACERS 0x0046b210
void CeruleanKnight0x20::FUN_0046b210(LegoS8* p_ints)
{
	p_ints[3] = m_unk0x10->ReadInteger();
	p_ints[0] = m_unk0x10->ReadInteger();
	p_ints[1] = m_unk0x10->ReadInteger();
	p_ints[2] = m_unk0x10->ReadInteger();
}

// FUNCTION: LEGORACERS 0x0046b250
void CeruleanKnight0x20::FUN_0046b250()
{
	GolFileParser::ParserTokenType token;

	while ((token = m_unk0x10->GetNextToken()) != 0) {
		VTable0x14(token);
		token = m_unk0x10->GetNextToken();
		if (token != GolFileParser::e_rightCurly) {
			m_unk0x10->HandleUnexpectedToken(GolFileParser::e_rightCurly);
		}
	}
}
