#ifndef GOLTXTPARSER_H
#define GOLTXTPARSER_H

#include "compat.h"
#include "decomp.h"
#include "golfileparser.h"

// VTABLE: GOLDP 0x10056f4c
// VTABLE: LEGORACERS 0x004b27e4
// SIZE 0x1fc
class GolTxtParser : public GolFileParser {
public:
	GolTxtParser() {}

	const LegoChar* GetSuffix() override;                   // vtable+0x3c
	void HandleUnexpectedToken(ParserTokenType) override;   // vtable+0x40
	ParserTokenType GetNextToken() override;                // vtable+0x44
	undefined4 VTable0x48(undefined4, undefined4) override; // vtable+0x48
	void OpenFileForWrite(LegoChar* p_fileName) override;   // vtable+0x4c
	void WriteToken(ParserTokenType) override;              // vtable+0x50
	void VTable0x54(undefined4) override;                   // vtable+0x54
	void WriteFloat(LegoFloat) override;                    // vtable+0x58
	void VTable0x5c(LegoFloat) override;                    // vtable+0x5c
	void WriteInt4(undefined4) override;                    // vtable+0x60
	void WriteString(LegoChar*) override;                   // vtable+0x64
	void FlushLine() override;                              // vtable+0x68
	void WriteSpace() override;                             // vtable+0x6c
	void WriteTab() override;                               // vtable+0x70
	void WriteTabs(undefined4) override;                    // vtable+0x74

	// SYNTHETIC: GOLDP 0x10030050 FOLDED
	// SYNTHETIC: LEGORACERS 0x0041e920 FOLDED
	// GolTxtParser::`scalar deleting destructor'

	// SYNTHETIC: GOLDP 0x1001b000 FOLDED
	// SYNTHETIC: LEGORACERS 0x00498840 FOLDED
	// GolTxtParser::~GolTxtParser

protected:
	LegoS32 m_lineCount;    // 0x1f0
	LegoS32 m_bufferLength; // 0x1f4
	undefined4 m_unk0x1f8;  // 0x1f8
};

// VTABLE: LEGORACERS 0x004b49d4
// SIZE 0x1fc
class GolTxtParser2 : public GolTxtParser {
	// It is not clear at this point why this class exists multiple times. The VTable is identical.
};

// VTABLE: LEGORACERS 0x004b4048
// SIZE 0x1fc
class GolTxtParser3 : public GolTxtParser {
	// It is not clear at this point why this class exists multiple times. The VTable is identical.
};

#endif // GOLTXTPARSER_H
