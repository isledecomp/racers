#ifndef GOLSTRING_H
#define GOLSTRING_H

#include "decomp.h"
#include "types.h"

// SIZE 0x0a
class GolString {
public:
	GolString();
	~GolString();

	static LegoS32 GolStrlen(undefined2* p_string);
	undefined2* FromCursor(undefined4 p_param);
	undefined4 CopyFromBufSelection(undefined2* p_buf, undefined2 p_count);
	undefined4 CopyFromGolString(GolString* p_string);

	// FUNCTION: LEGORACERS 0x00449f00
	void ResetCursors()
	{
		m_cursorEnd = 0;
		m_cursorStart = 0;

		while (m_chars[m_cursorEnd]) {
			m_cursorEnd++;
		}
	}

	void FirstLine();
	void NextLine();
	undefined4 GolStrcmp(GolString* p_string);
	undefined4 GolStrcpy(GolString* p_string);
	undefined4 GolStrcpy(undefined2* p_string);
	void ToUpperCase();
	void CopyToString(LegoChar* p_string);
	void CopyToBuf8(LegoChar* p_buf);
	LegoS32 CountLines();

	void Reset()
	{
		m_chars = NULL;
		m_cursorEnd = 0;
		m_cursorStart = 0;
		m_maxLen = 0;
	}

	undefined2 SelectionLength() const { return m_cursorEnd - m_cursorStart; }

protected:
	undefined2* m_chars;      // 0x00
	undefined2 m_maxLen;      // 0x04
	undefined2 m_cursorStart; // 0x06
	undefined2 m_cursorEnd;   // 0x08
};

#endif // GOLSTRING_H
