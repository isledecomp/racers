#include "golfileparser.h"

DECOMP_SIZE_ASSERT(GolFileParser, 0x1f0)

#include "golerror.h"

#include <stdio.h>

// GLOBAL: GOLDP 0x1005f25c
// GLOBAL: LEGORACERS 0x004c1a60
const char* g_ioErrorOccurredFormatStr = "I/O error occurred\nfile %s\n";

// GLOBAL: GOLDP 0x1005f260
// GLOBAL: LEGORACERS 0x004c1a64
const LegoChar* const g_parserErrorStrings[] = {
	"Syntax error",
	"Numeric too long",
	"Expected string",
	"Expected float",
	"Expected int",
	"Expected left curly",
	"Expected right curly",
	"Expected left bracket",
	"Expected right bracket",
	"Expected comma",
	"Expected semicolon",
	"Expected EOF",
	"Expected string or bracket",
	"Invalid keyword",
	"Invalid string",
	"Invalid value",
	"Duplicate name",
	"Unsupported",
	"Unexpected keyword",
	"Expected keyword"
};

// FUNCTION: GOLDP 0x10032440
// FUNCTION: LEGORACERS 0x0044e580
GolFileParser::GolFileParser()
{
	m_unk0x30 = 0;
	m_unk0x34 = e_syntaxerror;
	m_unk0x44[0] = '\0';
	m_unk0x84[0] = '\0';
	m_filePath = NULL;
	::memset(m_suffix, 0, sizeOfArray(m_suffix));
}

// FUNCTION: GOLDP 0x100324a0
// FUNCTION: LEGORACERS 0x0044e5e0
GolFileParser::~GolFileParser()
{
	if (m_filePath != NULL && m_filePath != m_unk0x1a8) {
		delete[] m_filePath;
	}
}

// FUNCTION: GOLDP 0x10032510
// FUNCTION: LEGORACERS 0x0044e650
LegoS32 GolFileParser::Dispose()
{
	LegoS32 result = GolStream::Dispose();

	if (m_filePath != NULL && m_filePath != m_unk0x1a8) {
		delete[] m_filePath;
		m_filePath = NULL;
	}

	return result;
}

// FUNCTION: GOLDP 0x10032550
// FUNCTION: LEGORACERS 0x0044e690
const LegoChar* GolFileParser::ParserErrorCodeToString(LegoS32 p_code)
{
	if (p_code >= (LegoS32) sizeOfArray(g_parserErrorStrings)) {
		GOL_FATALERROR_MESSAGE("Unknown error.");
	}

	return g_parserErrorStrings[p_code];
}

// FUNCTION: GOLDP 0x10032580
// FUNCTION: LEGORACERS 0x0044e6c0
void GolFileParser::FUN_10032580(LegoS32 p_code)
{
	if (m_filePath == NULL) {
		GOL_FATALERROR_MESSAGE(ErrorCodeToString(p_code));
		return;
	}

	LegoS32 totalLen =
		::strlen(ErrorCodeToString(p_code)) + ::strlen(m_filePath) + ::strlen(g_ioErrorOccurredFormatStr);
	m_unk0xa4[0] = '\0';

	if (totalLen < (LegoS32) sizeOfArray(m_unk0xa4) - 1) {
		::sprintf((LegoChar*) m_unk0xa4, g_ioErrorOccurredFormatStr, m_filePath);
	}

	::strcat((LegoChar*) m_unk0xa4, ErrorCodeToString(p_code));
	GOL_FATALERROR_MESSAGE((LegoChar*) m_unk0xa4);
}

// FUNCTION: GOLDP 0x10032650
// FUNCTION: LEGORACERS 0x0044e790 FOLDED
const LegoChar* GolFileParser::GetSuffix()
{
	if (m_suffix[0] == '\0') {
		return ".txt";
	}

	return m_suffix;
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void GolFileParser::OpenFileForRead(const LegoChar*)
{
	// empty
}

// STUB: GOLDP 0x100016f0 FOLDED
// STUB: LEGORACERS 0x0044e7e0 FOLDED
GolFileParser::ParserTokenType GolFileParser::GetNextToken()
{
	// TODO
#ifdef BUILDING_GOL
	MATCHING(0x100016f0);
#endif
	return e_syntaxerror;
}

// FUNCTION: GOLDP 0x10029950 FOLDED
// FUNCTION: LEGORACERS 0x0044e7f0 FOLDED
undefined4 GolFileParser::VTable0x48(undefined4, undefined4)
{
	return 0;
}

// FUNCTION: GOLDP 0x10032670
// FUNCTION: LEGORACERS 0x0044e7b0
void GolFileParser::SetSuffix(const LegoChar* p_suffix)
{
	::strncpy(m_suffix, p_suffix, sizeOfArray(m_suffix));
	m_suffix[sizeOfArray(m_suffix) - 1] = '\0';
}

// FUNCTION: GOLDP 0x100326a0
// FUNCTION: LEGORACERS 0x0044e800
LegoS32 GolFileParser::ReadInteger()
{
	if (GetNextToken() != e_int) {
		HandleUnexpectedToken(e_int);
	}

	return m_unk0x38;
}

// FUNCTION: GOLDP 0x100326c0
// FUNCTION: LEGORACERS 0x0044e820
LegoFloat GolFileParser::ReadFloat()
{
	if (GetNextToken() != e_float) {
		HandleUnexpectedToken(e_float);
	}

	return m_unk0x40;
}

// FUNCTION: GOLDP 0x100326e0
// FUNCTION: LEGORACERS 0x0044e840
LegoChar* GolFileParser::ReadString()
{
	if (GetNextToken() != e_string) {
		HandleUnexpectedToken(e_string);
	}

	return m_unk0x44;
}

// FUNCTION: GOLDP 0x10032700
// FUNCTION: LEGORACERS 0x0044e860
LegoChar* GolFileParser::ReadStringWithMaxLength(size_t p_len)
{
	if (GetNextToken() != e_string) {
		HandleUnexpectedToken(e_string);
	}

	if (::strlen(m_unk0x44) > p_len) {
		HandleUnexpectedToken(e_invalidString);
	}

	return m_unk0x44;
}

// FUNCTION: GOLDP 0x10032740
// FUNCTION: LEGORACERS 0x0044e8a0
void GolFileParser::AssertNextTokenIs(ParserTokenType p_expected)
{
	if (GetNextToken() != p_expected) {
		HandleUnexpectedToken(e_expectedKeyword);
	}
}

// FUNCTION: GOLDP 0x10032760
// FUNCTION: LEGORACERS 0x0044e8c0
void GolFileParser::ReadLeftBracket()
{
	if (GetNextToken() != e_leftBracket) {
		HandleUnexpectedToken(e_leftBracket);
	}
}

// FUNCTION: GOLDP 0x10032780
// FUNCTION: LEGORACERS 0x0044e8e0
void GolFileParser::ReadRightBracket()
{
	if (GetNextToken() != e_rightBracket) {
		HandleUnexpectedToken(e_rightBracket);
	}
}

// FUNCTION: GOLDP 0x100327a0
// FUNCTION: LEGORACERS 0x0044e900
void GolFileParser::ReadLeftCurly()
{
	if (GetNextToken() != e_leftCurly) {
		HandleUnexpectedToken(e_leftCurly);
	}
}

// FUNCTION: GOLDP 0x100327c0
// FUNCTION: LEGORACERS 0x0044e920
void GolFileParser::ReadRightCurly()
{
	if (GetNextToken() != e_rightCurly) {
		HandleUnexpectedToken(e_rightCurly);
	}
}

// FUNCTION: GOLDP 0x100327e0
// FUNCTION: LEGORACERS 0x0044e940
undefined4 GolFileParser::FUN_100327e0()
{
	if (GetNextToken() != e_leftBracket) {
		HandleUnexpectedToken(e_leftBracket);
	}

	if (GetNextToken() != e_int) {
		HandleUnexpectedToken(e_int);
	}

	if (GetNextToken() != e_rightBracket) {
		HandleUnexpectedToken(e_rightBracket);
	}

	if (GetNextToken() != e_leftCurly) {
		HandleUnexpectedToken(e_leftCurly);
	}

	return m_unk0x38;
}
