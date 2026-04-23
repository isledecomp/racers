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
	m_unk0x34 = 0;
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
		::sprintf(m_unk0xa4, g_ioErrorOccurredFormatStr, m_filePath);
	}

	::strcat(m_unk0xa4, ErrorCodeToString(p_code));
	GOL_FATALERROR_MESSAGE(m_unk0xa4);
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
void GolFileParser::VTable0x38(undefined4)
{
}

// STUB: GOLDP 0x100016f0 FOLDED
// STUB: LEGORACERS 0x0044e7e0 FOLDED
undefined4 GolFileParser::VTable0x44()
{
	// TODO
#ifdef BUILDING_GOL
	STUB(0x100016f0);
#endif
	return 0;
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
undefined4 GolFileParser::FUN_100326a0()
{
	if (VTable0x44() != e_expectedInt) {
		VTable0x40(e_expectedInt);
	}

	return m_unk0x38;
}

// FUNCTION: GOLDP 0x100326c0
// FUNCTION: LEGORACERS 0x0044e820
LegoFloat GolFileParser::FUN_100326c0()
{
	if (VTable0x44() != e_expectedFloat) {
		VTable0x40(e_expectedFloat);
	}

	return m_unk0x40;
}

// FUNCTION: GOLDP 0x100326e0
// FUNCTION: LEGORACERS 0x0044e840
LegoChar* GolFileParser::FUN_100326e0()
{
	if (VTable0x44() != e_expectedString) {
		VTable0x40(e_expectedString);
	}

	return m_unk0x44;
}

// FUNCTION: GOLDP 0x10032700
// FUNCTION: LEGORACERS 0x0044e860
LegoChar* GolFileParser::FUN_10032700(size_t p_len)
{
	if (VTable0x44() != e_expectedString) {
		VTable0x40(e_expectedString);
	}

	if (::strlen(m_unk0x44) > p_len) {
		VTable0x40(e_invalidString);
	}

	return m_unk0x44;
}

// FUNCTION: GOLDP 0x10032740
// FUNCTION: LEGORACERS 0x0044e8a0
void GolFileParser::FUN_10032740(undefined4 p_expected)
{
	if (VTable0x44() != p_expected) {
		VTable0x40(e_expectedKeyword);
	}
}

// FUNCTION: GOLDP 0x10032760
// FUNCTION: LEGORACERS 0x0044e8c0
void GolFileParser::FUN_10032760()
{
	if (VTable0x44() != e_expectedLeftBracket) {
		VTable0x40(e_expectedLeftBracket);
	}
}

// FUNCTION: GOLDP 0x10032780
// FUNCTION: LEGORACERS 0x0044e8e0
void GolFileParser::FUN_10032780()
{
	if (VTable0x44() != e_expectedRightBracket) {
		VTable0x40(e_expectedRightBracket);
	}
}

// FUNCTION: GOLDP 0x100327a0
// FUNCTION: LEGORACERS 0x0044e900
void GolFileParser::FUN_100327a0()
{
	if (VTable0x44() != e_expectedLeftCurly) {
		VTable0x40(e_expectedLeftCurly);
	}
}

// FUNCTION: GOLDP 0x100327c0
// FUNCTION: LEGORACERS 0x0044e920
void GolFileParser::FUN_100327c0()
{
	if (VTable0x44() != e_expectedRightCurly) {
		VTable0x40(e_expectedRightCurly);
	}
}

// FUNCTION: GOLDP 0x100327e0
// FUNCTION: LEGORACERS 0x0044e940
undefined4 GolFileParser::FUN_100327e0()
{
	if (VTable0x44() != e_expectedLeftBracket) {
		VTable0x40(e_expectedLeftBracket);
	}

	if (VTable0x44() != e_expectedInt) {
		VTable0x40(e_expectedInt);
	}

	if (VTable0x44() != e_expectedRightBracket) {
		VTable0x40(e_expectedRightBracket);
	}

	if (VTable0x44() != e_expectedLeftCurly) {
		VTable0x40(e_expectedLeftCurly);
	}

	return m_unk0x38;
}
