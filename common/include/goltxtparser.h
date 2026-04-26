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
	// GolTxtParser::`scalar deleting destructor'

protected:
	undefined4 m_unk0x1f0; // 0x1f0
	LegoS32 m_unk0x1f4;    // 0x1f4
	undefined4 m_unk0x1f8; // 0x1f8
};

#endif // GOLTXTPARSER_H
