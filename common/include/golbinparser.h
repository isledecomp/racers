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

	LegoS32 Dispose() override;                                // vtable+0x20
	void OpenFileForRead(const LegoChar* p_fileName) override; // vtable+0x38
	const LegoChar* GetSuffix() override;                      // vtable+0x3c
	void HandleUnexpectedToken(ParserTokenType) override;      // vtable+0x40
	ParserTokenType GetNextToken() override;                   // vtable+0x44
	undefined4 VTable0x48(undefined4, undefined4) override;    // vtable+0x48
	void OpenFileForWrite(LegoChar* p_fileName) override;      // vtable+0x4c
	void WriteToken(ParserTokenType) override;                 // vtable+0x50
	void VTable0x54(undefined4) override;                      // vtable+0x54
	void WriteFloat(LegoFloat) override;                       // vtable+0x58
	void VTable0x5c(LegoFloat) override;                       // vtable+0x5c
	void WriteInt4(undefined4) override;                       // vtable+0x60
	void WriteString(LegoChar*) override;                      // vtable+0x64
	void VTable0x68() override;                                // vtable+0x68
	void VTable0x6c() override;                                // vtable+0x6c
	void VTable0x70() override;                                // vtable+0x70
	void VTable0x74(undefined4) override;                      // vtable+0x74

	// SYNTHETIC: GOLDP 0x10030050 FOLDED
	// SYNTHETIC: LEGORACERS 0x0041e920 FOLDED
	// GolBinParser::`scalar deleting destructor'

	// SYNTHETIC: GOLDP 0x1001b000 FOLDED
	// SYNTHETIC: LEGORACERS 0x00498840 FOLDED
	// GolBinParser::~GolBinParser

	void Reset();
	void ReadTokenSequenceDefinition();
	undefined4 ReadBytes(LegoS32 p_size);
	GolFileParser::ParserTokenType GetExpandedToken();

protected:
	LegoU32 m_fileOffset;                  // 0x1f0
	undefined4 m_unk0x1f4;                 // 0x1f4
	LegoU32 m_expansionRepeatCount;        // 0x1f8
	LegoU32 m_expansionToken;              // 0x1fc
	LegoBool32 m_expandingBracketSequence; // 0x200
	LegoBool32 m_expandingTokenSequence;   // 0x204
	LegoU32 m_tokenSequenceIndex;          // 0x208
	LegoU32 m_expansionTokenIndex;         // 0x20c
	LegoU32 m_tokenSequences[16][16];      // 0x210
	LegoU32 m_tokenSequenceLengths[16];    // 0x610
};

#endif // GOLBINPARSER_H
