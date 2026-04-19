#include "golbinparser.h"

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

// STUB: GOLDP 0x10030e40
// STUB: LEGORACERS 0x0044b1e0
void GolBinParser::VTable0x40(undefined4)
{
	// TODO
	STUB(0x0044b1e0);
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
void GolBinParser::VTable0x50()
{
	// TODO
	STUB(0x0044b410);
}

// STUB: GOLDP 0x10031100
// STUB: LEGORACERS 0x0044b4a0
void GolBinParser::VTable0x54()
{
	// TODO
	STUB(0x0044b4a0);
}

// STUB: GOLDP 0x10031140
// STUB: LEGORACERS 0x0044b4e0
void GolBinParser::VTable0x58()
{
	// TODO
	STUB(0x0044b4e0);
}

// STUB: GOLDP 0x1002fd50 FOLDED
// STUB: LEGORACERS 0x0044b570 FOLDED
void GolBinParser::VTable0x5c()
{
	// TODO
	STUB(0x0044b570);
}

// STUB: GOLDP 0x100311d0
// STUB: LEGORACERS 0x0044b580
void GolBinParser::VTable0x60()
{
	// TODO
	STUB(0x0044b580);
}

// STUB: GOLDP 0x10031260
// STUB: LEGORACERS 0x0044b610
void GolBinParser::VTable0x64()
{
	// TODO
	STUB(0x0044b610);
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void GolBinParser::VTable0x68()
{
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void GolBinParser::VTable0x6c()
{
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void GolBinParser::VTable0x70()
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void GolBinParser::VTable0x74(undefined4)
{
}
