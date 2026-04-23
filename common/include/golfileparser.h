#ifndef GOLFILEPARSER_H
#define GOLFILEPARSER_H

#include "golfile.h"

#include <string.h>

// SIZE 0x1f0
// VTABLE: GOLDP 0x100578bc
// VTABLE: LEGORACERS 0x004b0ffc
class GolFileParser : public GolFile {
public:
	enum ParserErrorCode {
		e_syntaxerror = 0,
		e_numericTooLong = 1,
		e_expectedString = 2,
		e_expectedFloat = 3,
		e_expectedInt = 4,
		e_expectedLeftCurly = 5,
		e_expectedRightCurly = 6,
		e_expectedLeftBracket = 7,
		e_expectedRightBracket = 8,
		e_expectedComma = 9,
		e_expectedSimicolon = 10,
		e_expectedEOF = 11,
		e_expectedStringOrBracket = 12,
		e_invalidKeyword = 13,
		e_invalidString = 14,
		e_invalidValue = 15,
		e_duplicateName = 16,
		e_unsuported = 17,
		e_unsuportedKeyword = 18,
		e_expectedKeyword = 19
	};

	GolFileParser();
	~GolFileParser() override;

	LegoS32 Dispose() override;                            // vtable+0x20
	virtual void VTable0x38(undefined4);                   // vtable+0x38
	virtual const LegoChar* GetSuffix();                   // vtable+0x3c
	virtual void VTable0x40(undefined4) = 0;               // vtable+0x40
	virtual undefined4 VTable0x44();                       // vtable+0x44
	virtual undefined4 VTable0x48(undefined4, undefined4); // vtable+0x48
	virtual void OpenFile(LegoChar* p_fileName) = 0;       // vtable+0x4c
	virtual void VTable0x50(undefined4) = 0;               // vtable+0x50
	virtual void VTable0x54(undefined4) = 0;               // vtable+0x54
	virtual void WriteFloat(LegoFloat) = 0;                // vtable+0x58
	virtual void VTable0x5c(LegoFloat) = 0;                // vtable+0x5c
	virtual void WriteInt4(undefined4) = 0;                // vtable+0x60
	virtual void WriteString(LegoChar*) = 0;               // vtable+0x64
	virtual void VTable0x68() = 0;                         // vtable+0x68
	virtual void VTable0x6c() = 0;                         // vtable+0x6c
	virtual void VTable0x70() = 0;                         // vtable+0x70
	virtual void VTable0x74(undefined4) = 0;               // vtable+0x74

	void FUN_10032580(LegoS32 p_code);
	void SetSuffix(const LegoChar* p_suffix);
	undefined4 FUN_100326a0();
	LegoFloat FUN_100326c0();
	LegoChar* FUN_100326e0();
	LegoChar* FUN_10032700(size_t p_len);
	void FUN_10032740(undefined4 p_expected);
	void FUN_10032760();
	void FUN_10032780();
	void FUN_100327a0();
	void FUN_100327c0();
	undefined4 FUN_100327e0();

	const LegoChar* ParserErrorCodeToString(LegoS32 p_code);

	// SYNTHETIC: GOLDP 0x10032480
	// SYNTHETIC: LEGORACERS 0x0044e5c0
	// GolFileParser::`scalar deleting destructor'

protected:
	undefined4 m_unk0x30;               // 0x30
	undefined4 m_unk0x34;               // 0x34
	undefined4 m_unk0x38;               // 0x38
	undefined m_unk0x3c[0x40 - 0x3c];   // 0x3c
	LegoFloat m_unk0x40;                // 0x40
	LegoChar m_unk0x44[0x84 - 0x44];    // 0x44
	LegoChar m_unk0x84[0xa4 - 0x84];    // 0x84
	LegoChar m_unk0xa4[256];            // 0xa4
	LegoChar* m_filePath;               // 0x1a4
	LegoChar m_unk0x1a8[0x1e8 - 0x1a8]; // 0x1a8
	LegoChar m_suffix[5];               // 0x1a8
};

#endif // GOLFILEPARSER_H
