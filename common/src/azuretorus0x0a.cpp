#include "azuretorus0x0a.h"

#include "types.h"

#include <ctype.h>
#include <memory.h>

// FUNCTION: LEGORACERS 0x00449dc0
LegoS32 AzureTorus0x0a::AzureStrlen(undefined2* p_string)
{
	LegoS32 len = 0;

	while (*p_string++) {
		len++;
	}

	return len;
}

// FUNCTION: GOLDP 0x1002f950
// FUNCTION: LEGORACERS 0x00449e10
AzureTorus0x0a::AzureTorus0x0a()
{
	Reset();
}

// FUNCTION: GOLDP 0x1002f970
// FUNCTION: LEGORACERS 0x00449e30
AzureTorus0x0a::~AzureTorus0x0a()
{
	Reset();
}

// FUNCTION: GOLDP 0x1002f990
// FUNCTION: LEGORACERS 0x00449e50
undefined2* AzureTorus0x0a::FromCursor(undefined4 p_index)
{
	return &m_chars[m_cursorStart + p_index];
}

// FUNCTION: GOLDP 0x1002f9b0
// FUNCTION: LEGORACERS 0x00449e70
undefined4 AzureTorus0x0a::FUN_00449e70(undefined2* p_buf, LegoS32 p_count)
{
	m_cursorEnd = 0;
	m_cursorStart = 0;
	m_maxLen = 0;
	m_chars = p_buf;
	ResetCursors();

	if (p_count == 0) {
		m_maxLen = SelectionLength() + 1;
		return 1;
	}

	if (p_count < SelectionLength()) {
		m_maxLen = p_count;
		return 1;
	}

	Reset();
	return 0;
}

// FUNCTION: LEGORACERS 0x00449ed0
undefined4 AzureTorus0x0a::FUN_00449ed0(AzureTorus0x0a* p_torus)
{
	Reset();
	m_chars = p_torus->m_chars;
	m_maxLen = p_torus->m_maxLen;
	ResetCursors();
	return 1;
}

// FUNCTION: LEGORACERS 0x00449f00
void AzureTorus0x0a::ResetCursors()
{
	m_cursorEnd = 0;
	m_cursorStart = 0;

	while (m_chars[m_cursorEnd]) {
		m_cursorEnd++;
	}
}

// FUNCTION: LEGORACERS 0x00449f30
void AzureTorus0x0a::FirstLine()
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
void AzureTorus0x0a::NextLine()
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
undefined4 AzureTorus0x0a::TorusStrcmp(AzureTorus0x0a* p_torus)
{
	LegoS32 len = SelectionLength();
	if (len != p_torus->SelectionLength()) {
		return 0;
	}

	while (--len >= 0) {
		if (m_chars[len] != *p_torus->FromCursor(len)) {
			return 0;
		}
	}

	return 1;
}

// FUNCTION: LEGORACERS 0x0044a020
undefined4 AzureTorus0x0a::TorusStrcpy(AzureTorus0x0a* p_torus)
{
	LegoS32 len = AzureStrlen(p_torus->m_chars);
	if (len >= m_maxLen) {
		return 0;
	}

	memcpy(m_chars, p_torus->m_chars, 2 * len);
	m_cursorStart = p_torus->m_cursorStart;
	m_cursorEnd = p_torus->m_cursorEnd;

	return 1;
}

// FUNCTION: LEGORACERS 0x0044a080
undefined4 AzureTorus0x0a::AzureStrcpy(undefined2* p_string)
{
	LegoS32 len = AzureStrlen(p_string);
	if (len >= m_maxLen) {
		return 0;
	}

	memcpy(m_chars, p_string, 2 * len);
	m_chars[len] = 0;
	m_cursorEnd = len;

	return 1;
}

// FUNCTION: LEGORACERS 0x0044a0d0
void AzureTorus0x0a::ToUpperCase()
{
	LegoS32 i = SelectionLength();
	while (--i >= 0) {
		undefined2 c = m_chars[i];
		if ((c >= 0x80 && c <= 0xe0) || islower(c)) {
			m_chars[i] = c + ('A' - 'a');
		}
	}
}

// FUNCTION: LEGORACERS 0x0044a130
void AzureTorus0x0a::CopyToString(LegoChar* p_string)
{
	LegoS32 i = SelectionLength();
	p_string[i] = '\0';

	while (--i >= 0) {
		p_string[i] = m_chars[i];
	}
}

// FUNCTION: LEGORACERS 0x0044a160
void AzureTorus0x0a::CopyToBuf8(LegoChar* p_buf)
{
	LegoS32 i = SelectionLength();
	memset(p_buf, 0, 8);
	i = i > 8 ? 8 : i;

	while (--i >= 0) {
		p_buf[i] = m_chars[i];
	}
}

// FUNCTION: LEGORACERS 0x0044a1a0
LegoS32 AzureTorus0x0a::CountLines()
{
	LegoS32 i = AzureStrlen(m_chars);
	LegoS32 count = 1;
	while (--i >= 0) {
		if (m_chars[i] == '\n') {
			count++;
		}
	}

	return count;
}
