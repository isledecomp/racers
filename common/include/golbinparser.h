#ifndef GOLBINPARSER_H
#define GOLBINPARSER_H

#include "compat.h"
#include "decomp.h"
#include "golfileparser.h"

#include <memory.h>

// VTABLE: GOLDP 0x1005780c
// VTABLE: LEGORACERS 0x004b0e0c
// SIZE 0x650
class GolBinParser : public GolFileParser {
public:
	GolBinParser();

	LegoS32 Dispose() override;                             // vtable+0x20
	void VTable0x38(const LegoChar*) override;              // vtable+0x38
	const LegoChar* GetSuffix() override;                   // vtable+0x3c
	void HandleUnexpectedToken(ParserTokenType) override;   // vtable+0x40
	ParserTokenType GetNextToken() override;                // vtable+0x44
	undefined4 VTable0x48(undefined4, undefined4) override; // vtable+0x48
	void OpenFile(LegoChar* p_fileName) override;           // vtable+0x4c
	void VTable0x50(undefined4) override;                   // vtable+0x50
	void VTable0x54(undefined4) override;                   // vtable+0x54
	void WriteFloat(LegoFloat) override;                    // vtable+0x58
	void VTable0x5c(LegoFloat) override;                    // vtable+0x5c
	void WriteInt4(undefined4) override;                    // vtable+0x60
	void WriteString(LegoChar*) override;                   // vtable+0x64
	void VTable0x68() override;                             // vtable+0x68
	void VTable0x6c() override;                             // vtable+0x6c
	void VTable0x70() override;                             // vtable+0x70
	void VTable0x74(undefined4) override;                   // vtable+0x74

	// SYNTHETIC: GOLDP 0x10030050 FOLDED
	// SYNTHETIC: LEGORACERS 0x0041e920 FOLDED
	// GolBinParser::`scalar deleting destructor'

	// SYNTHETIC: GOLDP 0x1001b000 FOLDED
	// SYNTHETIC: LEGORACERS 0x00498840 FOLDED
	// GolBinParser::~GolBinParser

	void FUN_0044a830();
	void FUN_0044b020();
	undefined4 FUN_0044b0b0(LegoS32);
	GolFileParser::ParserTokenType FUN_0044b130();

protected:
	undefined4 m_unk0x1f0;      // 0x1f0
	undefined4 m_unk0x1f4;      // 0x1f4
	undefined4 m_unk0x1f8;      // 0x1f8
	undefined4 m_unk0x1fc;      // 0x1fc
	undefined4 m_unk0x200;      // 0x200
	undefined4 m_unk0x204;      // 0x204
	undefined4 m_unk0x208;      // 0x208
	undefined4 m_unk0x20c;      // 0x20c
	LegoU32 m_unk0x210[16][16]; // 0x210
	LegoU32 m_unk0x610[16];     // 0x610
};

#endif // GOLBINPARSER_H
