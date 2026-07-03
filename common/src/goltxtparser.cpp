#include "goltxtparser.h"

#include "decomp.h"

DECOMP_SIZE_ASSERT(GolTxtParser, 0x1fc)

#include "golerror.h"

#include <stdio.h>

// FUNCTION: GOLDP 0x1002fa20
// FUNCTION: LEGORACERS 0x0044a1d0
const LegoChar* GolTxtParser::GetSuffix()
{
	return ".txt";
}

// FUNCTION: GOLDP 0x1002fa50
// FUNCTION: LEGORACERS 0x0044a1f0
void GolTxtParser::OpenFileForWrite(LegoChar* p_fileName)
{
	if (m_flags & c_flagOpen) {
		Dispose();
	}

	LegoS32 dotpos = -1;
	LegoS32 len = 0;

	while (p_fileName[len] != '\0') {
		if (p_fileName[len] == '.') {
			dotpos = len;
		}
		len++;
	}

	if (dotpos < 0) {
		const LegoChar* suffix = GetSuffix();
		len += strlen(suffix);
		m_filePath = new LegoChar[len + 1];
		if (!m_filePath) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		strcpy(m_filePath, p_fileName);
		strcat(m_filePath, suffix);
	}
	else {
		m_filePath = new LegoChar[len + 1];
		if (!m_filePath) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		strcpy(m_filePath, p_fileName);
	}

	LegoS32 code = GolStream::BufferedOpen(m_filePath, c_modeTextAppend | c_modeWrite | c_modeCreate, 0x1000);
	if (code != e_ioSuccess) {
		HandleIoError(code);
	}

	m_lineCount = 0;
	m_bufferLength = 0;
	m_unk0x1f8 = 0;
}

// FUNCTION: GOLDP 0x1002fba0
// FUNCTION: LEGORACERS 0x0044a340
void GolTxtParser::WriteToken(ParserTokenType p_token)
{
	if (m_bufferLength + (LegoS32) sizeof(m_formatBuffer) >= (LegoS32) sizeof(m_readBuffer) - 1) {
		FlushLine();
	}

	switch (p_token) {
	case 5:
		m_readBuffer[m_bufferLength++] = '{';
		break;
	case 6:
		m_readBuffer[m_bufferLength++] = '}';
		break;
	case 7:
		m_readBuffer[m_bufferLength++] = '[';
		break;
	case 8:
		m_readBuffer[m_bufferLength++] = ']';
		break;
	case 9:
		m_readBuffer[m_bufferLength++] = ',';
		break;
	case 10:
		m_readBuffer[m_bufferLength++] = ';';
		break;
	default:
		WriteByte(p_token);
		break;
	}
}

// FUNCTION: GOLDP 0x1002fcb0
// FUNCTION: LEGORACERS 0x0044a450
void GolTxtParser::WriteByte(undefined4 p_param)
{
	if (p_param) {
		GOL_FATALERROR_MESSAGE("Cannot write invalid token");
	}
}

// FUNCTION: GOLDP 0x1002fcd0
// FUNCTION: LEGORACERS 0x0044a470
void GolTxtParser::WriteFloat(LegoFloat p_param)
{
	if (m_bufferLength + (LegoS32) sizeof(m_formatBuffer) >= (LegoS32) sizeof(m_readBuffer) - 1) {
		FlushLine();
	}

	sprintf(m_formatBuffer, "%f", p_param);

	LegoS32 len = strlen(m_formatBuffer);
	memcpy(&m_readBuffer[m_bufferLength], m_formatBuffer, len);
	m_bufferLength += len;
}

// FUNCTION: GOLDP 0x1002fd60
// FUNCTION: LEGORACERS 0x0044a4f0
void GolTxtParser::WriteInt4(undefined4 p_param)
{
	if (m_bufferLength + (LegoS32) sizeof(m_formatBuffer) >= (LegoS32) sizeof(m_readBuffer) - 1) {
		FlushLine();
	}

	sprintf(m_formatBuffer, "%d", p_param);

	LegoS32 len = strlen(m_formatBuffer);
	memcpy(&m_readBuffer[m_bufferLength], m_formatBuffer, len);
	m_bufferLength += len;
}

// FUNCTION: GOLDP 0x1002fdd0
// FUNCTION: LEGORACERS 0x0044a570
void GolTxtParser::WriteString(LegoChar* p_str)
{
	LegoS32 len = strlen(p_str);

	if (len + 4 >= (LegoS32) sizeof(m_readBuffer) - 1) {
		FlushLine();
	}

	m_readBuffer[m_bufferLength++] = '"';
	memcpy(&m_readBuffer[m_bufferLength], p_str, len);
	m_bufferLength += len;
	m_readBuffer[m_bufferLength++] = '"';
}

// FUNCTION: GOLDP 0x1002fe60
// FUNCTION: LEGORACERS 0x0044a600
void GolTxtParser::FlushLine()
{
	LegoS32 code = WriteLine(m_readBuffer, m_bufferLength);
	if (code != e_ioSuccess) {
		HandleIoError(code);
	}

	m_lineCount++;
	m_bufferLength = 0;
}

// FUNCTION: GOLDP 0x1002fea0
// FUNCTION: LEGORACERS 0x0044a640
void GolTxtParser::WriteSpace()
{
	if (m_bufferLength + 2 >= (LegoS32) sizeof(m_readBuffer) - 1) {
		FlushLine();
	}

	m_readBuffer[m_bufferLength] = ' ';
	m_bufferLength++;
}

// FUNCTION: GOLDP 0x1002fee0
// FUNCTION: LEGORACERS 0x0044a680
void GolTxtParser::WriteTab()
{
	if (m_bufferLength + 2 >= (LegoS32) sizeof(m_readBuffer) - 1) {
		FlushLine();
	}

	m_readBuffer[m_bufferLength] = '\t';
	m_bufferLength++;
}

// FUNCTION: GOLDP 0x1002ff20
// FUNCTION: LEGORACERS 0x0044a6c0
void GolTxtParser::WriteTabs(undefined4 p_param)
{
	if (p_param + m_bufferLength + 1 >= (LegoS32) sizeof(m_readBuffer) - 1) {
		FlushLine();
	}

	while (p_param > 0) {
		m_readBuffer[m_bufferLength] = '\t';
		m_bufferLength++;
		p_param--;
	}
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void GolTxtParser::HandleUnexpectedToken(ParserTokenType)
{
	// empty
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
// FUNCTION: LEGORACERS 0x0044a1e0 FOLDED
GolFileParser::ParserTokenType GolTxtParser::GetNextToken()
{
	return e_numericTooLong;
}

// FUNCTION: GOLDP 0x1002fa40 FOLDED
// FUNCTION: LEGORACERS 0x0044b1d0 FOLDED
undefined4 GolTxtParser::VTable0x48(undefined4, undefined4)
{
	return 1;
}

// FUNCTION: GOLDP 0x1002fd50 FOLDED
// FUNCTION: LEGORACERS 0x0044b570 FOLDED
void GolTxtParser::WriteFloat2(LegoFloat p_param)
{
	WriteFloat(p_param);
}
