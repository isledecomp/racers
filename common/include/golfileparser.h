#ifndef GOLFILEPARSER_H
#define GOLFILEPARSER_H

#include "golfile.h"

#include <string.h>

// SIZE 0x1f0
// VTABLE: GOLDP 0x100578bc
// VTABLE: LEGORACERS 0x004b0ffc
class GolFileParser : public GolFile {
public:
	enum ParserTokenType {
		e_syntaxerror = 0,
		e_numericTooLong = 1,
		e_string = 2,
		e_float = 3,
		e_int = 4,
		e_leftCurly = 5,
		e_rightCurly = 6,
		e_leftBracket = 7,
		e_rightBracket = 8,
		e_comma = 9,
		e_simicolon = 10,
		e_eof = 11,
		e_expectedStringOrBracket = 12,
		e_invalidKeyword = 13,
		e_invalidString = 14,
		e_invalidValue = 15,
		e_duplicateName = 16,
		e_unsuported = 17,
		e_unsuportedKeyword = 18,
		e_expectedKeyword = 19,
		//
		e_unknown0x27 = 0x27,
		e_unknown0x28 = 0x28,
		e_unknown0x29 = 0x29,
		e_unknown0x2a = 0x2a,
		e_unknown0x2b = 0x2b,
		e_unknown0x2c = 0x2c,
		e_unknown0x2d = 0x2d,
		e_unknown0x2e = 0x2e,
		e_unknown0x2f = 0x2f,
		e_unknown0x30 = 0x30,
		e_unknown0x31 = 0x31,
		e_unknown0x32 = 0x32,
		e_unknown0x33 = 0x33,
		e_unknown0x34 = 0x34,
		e_unknown0x35 = 0x35,
		e_unknown0x36 = 0x36,
		e_unknown0x37 = 0x37,
		e_unknown0x38 = 0x38,
		e_unknown0x39 = 0x39,
		e_unknown0x3a = 0x3a,
		e_unknown0x3b = 0x3b,
		e_unknown0x3c = 0x3c,
		e_unknown0x3d = 0x3d,
		e_unknown0x3e = 0x3e,
		e_unknown0x3f = 0x3f,
		e_unknown0x40 = 0x40,
		e_unknown0x41 = 0x41,
		e_unknown0x42 = 0x42,
		e_unknown0x43 = 0x43,
		e_unknown0x44 = 0x44,
		e_unknown0x45 = 0x45,
		e_unknown0x46 = 0x46,
		e_unknown0x47 = 0x47,
		e_unknown0x48 = 0x48,
		e_unknown0x49 = 0x49,
		e_unknown0x4a = 0x4a,
		e_unknown0x4b = 0x4b,
		e_unknown0x4c = 0x4c,
		e_unknown0x4d = 0x4d,
		e_unknown0x4e = 0x4e,
		e_unknown0x4f = 0x4f,
		e_unknown0x50 = 0x50,
		e_unknown0x51 = 0x51,
		e_unknown0x52 = 0x52,
		e_unknown0x53 = 0x53,
		e_unknown0x54 = 0x54,
		e_unknown0x55 = 0x55,
		e_unknown0x56 = 0x56,
		e_unknown0x57 = 0x57,
		e_unknown0x58 = 0x58,
		e_unknown0x59 = 0x59,
		e_unknown0x5a = 0x5a,
		e_unknown0x5b = 0x5b,
		e_unknown0x5c = 0x5c,
		e_unknown0x60 = 0x60,
		e_unknown0x66 = 0x66,
		e_unknown0x8b = 0x8b,
		e_unknown0x8c = 0x8c,
		e_unknown0x8d = 0x8d,
		e_unknown0x8e = 0x8e,
	};

	GolFileParser();
	~GolFileParser() override;

	LegoS32 Dispose() override;                              // vtable+0x20
	virtual void OpenFileForRead(const LegoChar*);           // vtable+0x38
	virtual const LegoChar* GetSuffix();                     // vtable+0x3c
	virtual void HandleUnexpectedToken(ParserTokenType) = 0; // vtable+0x40
	virtual ParserTokenType GetNextToken();                  // vtable+0x44
	virtual undefined4 VTable0x48(undefined4, undefined4);   // vtable+0x48
	virtual void OpenFileForWrite(LegoChar* p_fileName) = 0; // vtable+0x4c
	virtual void WriteToken(ParserTokenType) = 0;            // vtable+0x50
	virtual void VTable0x54(undefined4) = 0;                 // vtable+0x54
	virtual void WriteFloat(LegoFloat) = 0;                  // vtable+0x58
	virtual void VTable0x5c(LegoFloat) = 0;                  // vtable+0x5c
	virtual void WriteInt4(undefined4) = 0;                  // vtable+0x60
	virtual void WriteString(LegoChar*) = 0;                 // vtable+0x64
	virtual void FlushLine() = 0;                            // vtable+0x68
	virtual void WriteSpace() = 0;                           // vtable+0x6c
	virtual void WriteTab() = 0;                             // vtable+0x70
	virtual void WriteTabs(undefined4) = 0;                  // vtable+0x74

	void HandleIoError(LegoS32 p_code);
	void SetSuffix(const LegoChar* p_suffix);
	LegoS32 ReadInteger();
	LegoFloat ReadFloat();
	LegoChar* ReadString();
	LegoChar* ReadStringWithMaxLength(size_t p_len);
	void AssertNextTokenIs(ParserTokenType p_expected);
	void ReadLeftBracket();
	void ReadRightBracket();
	void ReadLeftCurly();
	void ReadRightCurly();
	LegoU32 ReadBracketedCountAndLeftCurly();

	const LegoChar* ParserErrorCodeToString(LegoS32 p_code);

	void SetUnk0x30(undefined4 p_arg) { m_unk0x30 = p_arg; }
	ParserTokenType GetCurrentToken() const { return m_currentToken; }
	LegoS32 GetLastInt() const { return m_lastInt; }
	LegoFloat GetLastFloat() const { return m_lastFloat; }
	const LegoChar* GetLastString() const { return m_lastString; }

	// SYNTHETIC: GOLDP 0x10032480
	// SYNTHETIC: LEGORACERS 0x0044e5c0
	// GolFileParser::`scalar deleting destructor'

protected:
	undefined4 m_unk0x30;                       // 0x30
	ParserTokenType m_currentToken;             // 0x34
	LegoS32 m_lastInt;                          // 0x38
	undefined m_unk0x3c[0x40 - 0x3c];           // 0x3c
	LegoFloat m_lastFloat;                      // 0x40
	LegoChar m_lastString[0x84 - 0x44];         // 0x44
	LegoChar m_formatBuffer[0xa4 - 0x84];       // 0x84
	LegoU8 m_readBuffer[256];                   // 0xa4
	LegoChar* m_filePath;                       // 0x1a4
	LegoChar m_inlinePathBuffer[0x1e8 - 0x1a8]; // 0x1a8
	LegoChar m_suffix[5];                       // 0x1e8
};

#endif // GOLFILEPARSER_H
