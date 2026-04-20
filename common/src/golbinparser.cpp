#include "golbinparser.h"

#include "golerror.h"

#include <stdio.h>

// GLOBAL: GOLDP 0x1005f030
// GLOBAL: LEGORACERS 0x004c182c
const LegoChar* g_fileFormatStr = "file %s\n";

// STUB: LEGORACERS 0x0044a7e0
GolBinParser::GolBinParser()
{
	FUN_0044a830();
}

// STUB: GOLDP 0x10030070
// STUB: LEGORACERS 0x0044a890
void GolBinParser::VTable0x38(undefined4)
{
	// TODO
	STUB(0x0044a890);
}

// FUNCTION: GOLDP 0x10030280
// FUNCTION: LEGORACERS 0x0044aaa0
LegoS32 GolBinParser::Dispose()
{
	LegoS32 result = GolFileParser::Dispose();
#ifdef BUILDING_LEGORACERS
#pragma inline_depth(0)
#endif
	FUN_0044a830();
#ifdef BUILDING_LEGORACERS
#pragma inline_depth()
#endif
	return result;
}

// FUNCTION: GOLDP 0x100302e0
// FUNCTION: LEGORACERS 0x0044aac0
const LegoChar* GolBinParser::GetSuffix()
{
	return *m_suffix ? m_suffix : ".bin";
}

// STUB: GOLDP 0x10030300
// STUB: LEGORACERS 0x0044aae0
undefined4 GolBinParser::VTable0x44()
{
	// TODO
	STUB(0x0044aae0);
	return 0;
}

// FUNCTION: GOLDP 0x1002fa40 FOLDED
// FUNCTION: LEGORACERS 0x0044b1d0 FOLDED
undefined4 GolBinParser::VTable0x48(undefined4, undefined4)
{
	return 1;
}

// FUNCTION: GOLDP 0x10030e40
// FUNCTION: LEGORACERS 0x0044b1e0
void GolBinParser::VTable0x40(undefined4 p_code)
{
	if (m_filePath == NULL) {
		GOL_FATALERROR_MESSAGE(ParserErrorCodeToString(p_code));
		return;
	}

	LegoS32 totalLen = strlen(ParserErrorCodeToString(p_code)) + strlen(m_filePath) + strlen(g_fileFormatStr);
	m_unk0xa4[0] = '\0';

	if (totalLen < (LegoS32) sizeOfArray(m_unk0xa4) - 1) {
		sprintf(m_unk0xa4, g_fileFormatStr, m_filePath);
	}

	strcat(m_unk0xa4, ParserErrorCodeToString(p_code));
	GOL_FATALERROR_MESSAGE(m_unk0xa4);
}

// STUB: GOLDP 0x10030f10
// STUB: LEGORACERS 0x0044b2b0
void GolBinParser::VTable0x4c()
{
	// TODO
	STUB(0x0044b2b0);
}

// STUB: GOLDP 0x10031070
// STUB: LEGORACERS 0x0044b410
void GolBinParser::VTable0x50(undefined4)
{
	// TODO
	STUB(0x0044b410);
}

// FUNCTION: GOLDP 0x10031100
// FUNCTION: LEGORACERS 0x0044b4a0
void GolBinParser::VTable0x54(undefined4 p_param)
{
	*m_unk0xa4 = p_param;
	LegoS32 code = BufferedWrite(m_unk0x1f0, m_unk0xa4, 1);
	if (code != e_ioSuccess) {
		FUN_10032580(code);
	}

	m_unk0x1f0++;
}

// FUNCTION: GOLDP 0x10031140
// FUNCTION: LEGORACERS 0x0044b4e0
void GolBinParser::WriteFloat(LegoFloat p_param)
{
	*m_unk0xa4 = 3;
	LegoS32 code = BufferedWrite(m_unk0x1f0, m_unk0xa4, 1);
	if (code != e_ioSuccess) {
		FUN_10032580(code);
	}

	m_unk0x1f0++;

	LegoU32 buf;
	memcpy(&buf, &p_param, sizeof(buf));
	m_unk0xa4[0] = (LegoU8) buf;
	m_unk0xa4[1] = (LegoU8) (buf >> 8);
	m_unk0xa4[2] = (LegoU8) (buf >> 16);
	m_unk0xa4[3] = (LegoU8) (buf >> 24);

	code = BufferedWrite(m_unk0x1f0, m_unk0xa4, sizeof(p_param));
	if (code != e_ioSuccess) {
		FUN_10032580(code);
	}

	m_unk0x1f0 += 4;
}

// STUB: GOLDP 0x1002fd50 FOLDED
// STUB: LEGORACERS 0x0044b570 FOLDED
void GolBinParser::VTable0x5c()
{
	// TODO
	STUB(0x0044b570);
}

// FUNCTION: GOLDP 0x100311d0
// FUNCTION: LEGORACERS 0x0044b580
void GolBinParser::WriteInt4(undefined4 p_param)
{
	*m_unk0xa4 = 4;
	LegoS32 code = BufferedWrite(m_unk0x1f0, m_unk0xa4, 1);
	if (code != e_ioSuccess) {
		FUN_10032580(code);
	}

	m_unk0x1f0++;

	m_unk0xa4[0] = (LegoU8) p_param;
	m_unk0xa4[1] = (LegoU8) (p_param >> 8);
	m_unk0xa4[2] = (LegoU8) (p_param >> 16);
	m_unk0xa4[3] = (LegoU8) (p_param >> 24);

	code = BufferedWrite(m_unk0x1f0, m_unk0xa4, sizeof(p_param));
	if (code != e_ioSuccess) {
		FUN_10032580(code);
	}

	m_unk0x1f0 += 4;
}

// FUNCTION: GOLDP 0x10031260
// FUNCTION: LEGORACERS 0x0044b610
void GolBinParser::WriteString(LegoChar* p_str)
{
	*m_unk0xa4 = 2;
	LegoS32 code = BufferedWrite(m_unk0x1f0, m_unk0xa4, 1);
	if (code != e_ioSuccess) {
		FUN_10032580(code);
	}

	m_unk0x1f0++;

	LegoS32 len = strlen(p_str);
	if (len >= 63) {
		len = 63;
	}

	memcpy(m_unk0xa4, p_str, len);

	code = BufferedWrite(m_unk0x1f0, m_unk0xa4, len);
	if (code != e_ioSuccess) {
		FUN_10032580(code);
	}

	m_unk0x1f0 += len;

	*m_unk0xa4 = 2;
	code = BufferedWrite(m_unk0x1f0, m_unk0xa4, 1);
	if (code != e_ioSuccess) {
		FUN_10032580(code);
	}

	m_unk0x1f0++;
}

// FUNCTION: GOLDP 0x10029920 FOLDED
// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void GolBinParser::VTable0x68()
{
}

// FUNCTION: GOLDP 0x10029920 FOLDED
// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void GolBinParser::VTable0x6c()
{
}

// FUNCTION: GOLDP 0x10029920 FOLDED
// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void GolBinParser::VTable0x70()
{
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void GolBinParser::VTable0x74(undefined4)
{
}
