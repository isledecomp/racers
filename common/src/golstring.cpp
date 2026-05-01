#include "golstring.h"

#include "types.h"

#include <ctype.h>
#include <memory.h>

// FUNCTION: LEGORACERS 0x00449dc0
LegoS32 GolString::GolStrlen(undefined2* p_string)
{
	LegoS32 len = 0;

	while (*p_string++) {
		len++;
	}

	return len;
}

// FUNCTION: GOLDP 0x1002f950
// FUNCTION: LEGORACERS 0x00449e10
GolString::GolString()
{
	Reset();
}

// FUNCTION: GOLDP 0x1002f970
// FUNCTION: LEGORACERS 0x00449e30
GolString::~GolString()
{
	Reset();
}

// FUNCTION: GOLDP 0x1002f990
// FUNCTION: LEGORACERS 0x00449e50
undefined2* GolString::FromCursor(undefined4 p_index)
{
	return &m_chars[m_cursorStart + p_index];
}

// FUNCTION: GOLDP 0x1002f9b0
// FUNCTION: LEGORACERS 0x00449e70
undefined4 GolString::CopyFromBufSelection(undefined2* p_buf, undefined2 p_count)
{
	m_cursorEnd = 0;
	m_cursorStart = 0;
	m_maxLen = 0;
	m_chars = p_buf;

	ResetCursors();

	if (!p_count) {
		p_count = SelectionLength() + 1;
	}
	else if (SelectionLength() >= p_count) {
		Reset();
		return 0;
	}

	m_maxLen = p_count;
	return 1;
}

// FUNCTION: LEGORACERS 0x00449ed0
undefined4 GolString::CopyFromGolString(GolString* p_string)
{
	Reset();
	m_chars = p_string->m_chars;
	m_maxLen = p_string->m_maxLen;

	ResetCursors();
	return 1;
}

// FUNCTION: LEGORACERS 0x00449f00
void GolString::ResetCursors()
{
	m_cursorEnd = 0;
	m_cursorStart = 0;

	while (m_chars[m_cursorEnd]) {
		m_cursorEnd++;
	}
}

// FUNCTION: LEGORACERS 0x00449f30
void GolString::FirstLine()
{
	m_cursorEnd = 0;
	m_cursorStart = 0;

	while (m_chars[m_cursorEnd]) {
		if (m_chars[m_cursorEnd] == '\n') {
			break;
		}

		m_cursorEnd++;
	}
}

// FUNCTION: LEGORACERS 0x00449f70
void GolString::NextLine()
{
	if (!m_chars[m_cursorEnd]) {
		return;
	}

	m_cursorEnd++;
	m_cursorStart = m_cursorEnd;

	while (m_chars[m_cursorEnd]) {
		if (m_chars[m_cursorEnd] == '\n') {
			break;
		}

		m_cursorEnd++;
	}
}

// FUNCTION: LEGORACERS 0x00449fc0
undefined4 GolString::GolStrcmp(GolString* p_string)
{
	LegoS32 len = SelectionLength();
	if (len != p_string->SelectionLength()) {
		return 0;
	}

	while (--len >= 0) {
		if (m_chars[len] != *p_string->FromCursor(len)) {
			return 0;
		}
	}

	return 1;
}

// FUNCTION: LEGORACERS 0x0044a020
undefined4 GolString::GolStrcpy(GolString* p_string)
{
	LegoS32 len = GolStrlen(p_string->m_chars);
	if (len >= m_maxLen) {
		return 0;
	}

	memcpy(m_chars, p_string->m_chars, len << 1);
	m_cursorStart = p_string->m_cursorStart;
	m_cursorEnd = p_string->m_cursorEnd;
	return 1;
}

// FUNCTION: LEGORACERS 0x0044a080
undefined4 GolString::GolStrcpy(undefined2* p_string)
{
	LegoS32 len = GolStrlen(p_string);
	if (len >= m_maxLen) {
		return 0;
	}

	memcpy(m_chars, p_string, len << 1);
	m_chars[len] = 0;
	m_cursorEnd = len;
	return 1;
}

// FUNCTION: LEGORACERS 0x0044a0d0
void GolString::ToUpperCase()
{
	LegoS32 i = SelectionLength();
	while (--i >= 0) {
		undefined2 c = m_chars[i] & 0xFF;
		if ((c >= 128u && c >= 224u) || islower(c)) {
			m_chars[i] = c + ('A' - 'a');
		}
	}
}

// FUNCTION: LEGORACERS 0x0044a130
void GolString::CopyToString(LegoChar* p_string)
{
	LegoS32 i = SelectionLength();
	p_string[i] = '\0';

	while (--i >= 0) {
		p_string[i] = m_chars[i];
	}
}

// FUNCTION: LEGORACERS 0x0044a160
void GolString::CopyToBuf8(LegoChar* p_buf)
{
	LegoS32 i = SelectionLength();
	memset(p_buf, 0, 8u);
	i = i > 8u ? 8u : i;

	while (--i >= 0) {
		p_buf[i] = m_chars[i];
	}
}

// FUNCTION: LEGORACERS 0x0044a1a0
LegoS32 GolString::CountLines()
{
	LegoS32 i = GolStrlen(m_chars);
	LegoS32 count = 1;
	while (--i >= 0) {
		if (m_chars[i] == '\n') {
			count++;
		}
	}

	return count;
}
