#include "golbinparser.h"

#include "decomp.h"

DECOMP_SIZE_ASSERT(GolBinParser, 0x650)

#include "golconstants.h"
#include "golerror.h"

#include <stdio.h>

// GLOBAL: GOLDP 0x10065b58
// GLOBAL: LEGORACERS 0x004c7070
const LegoFloat g_dequantize4096 = 1.0f / g_floatConst4096.m_value;

// GLOBAL: GOLDP 0x10065b60
// GLOBAL: LEGORACERS 0x004c7078
const LegoFloat g_dequantize32 = 1.0f / g_floatConst32.m_value;

// GLOBAL: GOLDP 0x10065b64
// GLOBAL: LEGORACERS 0x004c707c
const LegoFloat g_dequantize127 = 1.0f / g_floatConst127;

// GLOBAL: GOLDP 0x1005f030
// GLOBAL: LEGORACERS 0x004c182c
const LegoChar* g_fileFormatStr = "file %s\n";

// GLOBAL: GOLDP 0x100577f8
// GLOBAL: LEGORACERS 0x004b0df8
const GolFileParser::ParserTokenType g_binParserBracketSequence[] =
	{GolFileParser::e_leftBracket, GolFileParser::e_int, GolFileParser::e_rightBracket, GolFileParser::e_rightBracket};

// FUNCTION: GOLDP 0x1002fff0
// FUNCTION: LEGORACERS 0x0044a7e0
GolBinParser::GolBinParser()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0044a830
void GolBinParser::Reset()
{
	m_fileOffset = 0;
	m_unk0x1f4 = 0;
	m_expansionRepeatCount = 0;
	m_expansionToken = 0;
	m_expandingBracketSequence = FALSE;
	m_expandingTokenSequence = FALSE;
	m_tokenSequenceIndex = 0;
	m_expansionTokenIndex = 0;
	memset(m_tokenSequences, 0, sizeof(m_tokenSequences));
	memset(m_tokenSequenceLengths, 0, sizeof(m_tokenSequenceLengths));
}

// FUNCTION: GOLDP 0x10030070
// FUNCTION: LEGORACERS 0x0044a890
void GolBinParser::OpenFileForRead(const LegoChar* p_fileName)
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
		if (len < 64) {
			m_filePath = m_inlinePathBuffer;
		}
		else {
			m_filePath = new LegoChar[len + 1];
		}
		if (!m_filePath) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		strcpy(m_filePath, p_fileName);
		strcat(m_filePath, suffix);
	}
	else if (*m_suffix) {
		const LegoChar* suffix = GetSuffix();
		len += strlen(suffix);
		if (len < 64) {
			m_filePath = m_inlinePathBuffer;
		}
		else {
			m_filePath = new LegoChar[len + 1];
		}
		if (!m_filePath) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		strcpy(m_filePath, p_fileName);
		strcpy(&m_filePath[dotpos], suffix);
	}
	else {
		if (len < 64) {
			m_filePath = m_inlinePathBuffer;
		}
		else {
			m_filePath = new LegoChar[len + 1];
		}
		if (!m_filePath) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		strcpy(m_filePath, p_fileName);
	}

	LegoS32 code = GolStream::BufferedOpen(m_filePath, c_modeRead, 0x1000);
	if (code != e_ioSuccess) {
		HandleIoError(code);
	}

	m_fileOffset = 0;
	m_unk0x1f4 = 0;
	m_currentToken = e_syntaxerror;
	m_replayToken = 0;
}

// FUNCTION: GOLDP 0x10030280
// FUNCTION: LEGORACERS 0x0044aaa0
LegoS32 GolBinParser::Dispose()
{
	LegoS32 result = GolFileParser::Dispose();
	Reset();
	return result;
}

// FUNCTION: GOLDP 0x100302e0
// FUNCTION: LEGORACERS 0x0044aac0
const LegoChar* GolBinParser::GetSuffix()
{
	return *m_suffix ? m_suffix : ".bin";
}

// FUNCTION: GOLDP 0x10030300
// FUNCTION: LEGORACERS 0x0044aae0
GolFileParser::ParserTokenType GolBinParser::GetNextToken()
{
	LegoU32 i;
	ParserTokenType token;
	LegoS32 code;
	LegoS32 lenRead;

	if (m_replayToken) {
		m_replayToken = 0;
		return (GolFileParser::ParserTokenType) m_currentToken;
	}

	while (1) {
		LegoU32 t;
		if (m_expansionRepeatCount) {
			t = GetExpandedToken();
		}
		else {
			if (!ReadBytes(1)) {
				return e_syntaxerror;
			}
			t = ((LegoU8) m_readBuffer[0]);
		}

		switch (t) {
		case 0x14:
			if (!ReadBytes(2)) {
				return e_syntaxerror;
			}

			m_expansionRepeatCount = ((LegoU8) m_readBuffer[0]) + ((LegoU8) m_readBuffer[1] << 8);

			if (!ReadBytes(1)) {
				return e_syntaxerror;
			}

			m_expansionToken = (LegoU8) m_readBuffer[0];
			if (m_expansionToken == 0x13) {
				if (!ReadBytes(2)) {
					return e_syntaxerror;
				}

				m_expansionToken = ((LegoU8) m_readBuffer[0]) + ((LegoU8) m_readBuffer[1] << 8);
			}

			m_expandingTokenSequence = FALSE;

			if (m_expansionToken >= 0x17 && m_expansionToken <= 0x26) {
				m_tokenSequenceIndex = m_expansionToken - 0x17;
				// TODO: ???
				if (&m_tokenSequences[m_tokenSequenceIndex][0] == 0) {
					HandleUnexpectedToken(e_syntaxerror);
				}

				m_expansionTokenIndex = 0;
				m_expandingTokenSequence = TRUE;
			}
			else if (m_expansionToken == 0x15) {
				m_expandingBracketSequence = TRUE;
				m_expansionTokenIndex = 0;
			}

			break;

		case 0x15:
			m_expansionRepeatCount = 1;
			m_expandingBracketSequence = TRUE;
			m_expansionTokenIndex = 0;
			m_expandingTokenSequence = FALSE;
			break;

		case 0x16:
			ReadTokenSequenceDefinition();
			if (m_currentToken == e_syntaxerror) {
				return e_syntaxerror;
			}

			break;

		default:
			if (t >= 0x17 && t <= 0x26) {
				m_tokenSequenceIndex = t - 0x17;
				// TODO: ???
				if (&m_tokenSequences[m_tokenSequenceIndex][0] == 0) {
					HandleUnexpectedToken(e_syntaxerror);
				}

				m_expansionTokenIndex = 0;
				m_expandingTokenSequence = TRUE;
				m_expansionRepeatCount = 1;
				break;
			}

			m_currentToken = (GolFileParser::ParserTokenType) t;
			return (GolFileParser::ParserTokenType) m_currentToken;

		case 2:
			code = BufferedRead(m_fileOffset, m_readBuffer, 63, &lenRead);
			if (code != e_ioSuccess) {
				if (code == e_ioEndOfFile) {
					if (lenRead == 0) {
						m_currentToken = e_syntaxerror;
						return e_syntaxerror;
					}
				}
				else {
					HandleIoError(code);
				}
			}

			for (i = 0; i < lenRead; i++) {
				if (m_readBuffer[i] == '\0') {
					break;
				}

				m_lastString[i] = m_readBuffer[i];
			}

			m_lastString[i++] = '\0';
			m_fileOffset += i;

			m_currentToken = (GolFileParser::ParserTokenType) t;
			return (GolFileParser::ParserTokenType) m_currentToken;

		case 3: {
			if (!ReadBytes(4)) {
				return e_syntaxerror;
			}

			LegoU32 floatBits = (((LegoU32) m_readBuffer[3] << 8) + (LegoU32) m_readBuffer[2]);
			floatBits = (floatBits << 8) + (LegoU32) m_readBuffer[1];
			floatBits = (floatBits << 8) + (LegoU32) m_readBuffer[0];
			m_lastFloat = *(LegoFloat*) &floatBits;

			m_currentToken = (GolFileParser::ParserTokenType) t;
			return (GolFileParser::ParserTokenType) m_currentToken;
		}

		case 4: {
			if (!ReadBytes(4)) {
				return e_syntaxerror;
			}

			LegoU32 intBits = (((LegoU32) m_readBuffer[3] << 8) + (LegoU32) m_readBuffer[2]);
			intBits = (intBits << 8) + (LegoU32) m_readBuffer[1];
			intBits = (intBits << 8) + (LegoU32) m_readBuffer[0];
			m_lastInt = intBits;

			m_currentToken = (GolFileParser::ParserTokenType) t;
			return (GolFileParser::ParserTokenType) m_currentToken;
		}

		case 0xb:
			if (!ReadBytes(1)) {
				return e_syntaxerror;
			}

#ifdef BUILDING_GOL
			m_lastInt = (LegoU8) (m_readBuffer[0]);
			m_currentToken = e_int;
#else
			m_currentToken = e_int;
			m_lastInt = (LegoU8) (m_readBuffer[0]);
#endif
			return (GolFileParser::ParserTokenType) m_currentToken;

		case 0xc:
			if (!ReadBytes(1)) {
				return e_syntaxerror;
			}

			m_lastInt = (LegoU8) (m_readBuffer[0]);
			m_currentToken = e_int;
			return (GolFileParser::ParserTokenType) m_currentToken;

		case 0xd:
			if (!ReadBytes(2)) {
				return e_syntaxerror;
			}

			m_lastInt = (LegoS16) (m_readBuffer[0] + (m_readBuffer[1] << 8));
			m_currentToken = e_int;
			return (GolFileParser::ParserTokenType) m_currentToken;

		case 0xe:
			if (!ReadBytes(2)) {
				return e_syntaxerror;
			}

#ifdef BUILDING_GOL
			m_lastInt = (LegoU16) (m_readBuffer[0] + (m_readBuffer[1] << 8));
			m_currentToken = e_int;
#else
			m_currentToken = e_int;
			m_lastInt = (LegoU16) (m_readBuffer[0] + (m_readBuffer[1] << 8));
#endif
			return (GolFileParser::ParserTokenType) m_currentToken;

		case 0xf:
			if (!ReadBytes(2)) {
				return e_syntaxerror;
			}

			m_lastFloat = g_dequantize4096 * (LegoS16) (m_readBuffer[0] + ((m_readBuffer[1] << 8)));
			m_currentToken = e_float;
			return (GolFileParser::ParserTokenType) m_currentToken;

		case 0x10:
			if (!ReadBytes(2)) {
				return e_syntaxerror;
			}

			m_lastFloat = g_dequantize32 * (LegoS16) (m_readBuffer[0] + ((m_readBuffer[1] << 8)));
			m_currentToken = e_float;
			return (GolFileParser::ParserTokenType) m_currentToken;

		case 0x11:
			if (!ReadBytes(2)) {
				return e_syntaxerror;
			}

			m_lastFloat = (LegoS16) (m_readBuffer[0] + ((m_readBuffer[1] << 8)));
			m_currentToken = e_float;
			return (GolFileParser::ParserTokenType) m_currentToken;

		case 0x12:
			if (!ReadBytes(1)) {
				return e_syntaxerror;
			}

			m_lastFloat = g_dequantize127 * (LegoU8) (m_readBuffer[0]);
			m_currentToken = e_float;
			return (GolFileParser::ParserTokenType) m_currentToken;

		case 0x13: {
			if (!ReadBytes(2)) {
				return e_syntaxerror;
			}

			token = (ParserTokenType) ((LegoU8) m_readBuffer[1]);
			token = (ParserTokenType) ((LegoU32) token << 8);
			token = (ParserTokenType) (token + (LegoU8) m_readBuffer[0]);
			m_currentToken = token;
			return token;
		}
		}
	}
}

// FUNCTION: GOLDP 0x10030c30
// FUNCTION: LEGORACERS 0x0044b020
void GolBinParser::ReadTokenSequenceDefinition()
{
	if (!ReadBytes(2)) {
		return;
	}

	LegoU32 sequenceIndex = (LegoU8) m_readBuffer[0] - 0x17;
	LegoU32 count = (LegoU8) m_readBuffer[1];
	m_tokenSequenceLengths[sequenceIndex] = count;

	for (LegoU32 i = 0; i < count; i++) {
		if (!ReadBytes(1)) {
			return;
		}

		LegoU32 token = (LegoU8) m_readBuffer[0];
		if (token == 0x13) {
			if (!ReadBytes(2)) {
				return;
			}

			token = ((LegoU8) m_readBuffer[1] << 8) + (LegoU8) m_readBuffer[0];
		}

		m_tokenSequences[sequenceIndex][i] = token;
	}
}

// FUNCTION: LEGORACERS 0x0044b0b0
undefined4 GolBinParser::ReadBytes(LegoS32 p_size)
{
	LegoS32 lenRead;
	LegoS32 code = BufferedRead(m_fileOffset, m_readBuffer, p_size, &lenRead);
	if (code != e_ioSuccess) {
		if (code == e_ioEndOfFile) {
			if (lenRead == 0) {
				m_currentToken = e_syntaxerror;
				return 0;
			}
		}
		else {
			HandleIoError(code);
		}
	}

	if (lenRead != p_size) {
		HandleUnexpectedToken(e_syntaxerror);
	}

	m_fileOffset += p_size;
	return 1;
}

// FUNCTION: GOLDP 0x10030da0
// FUNCTION: LEGORACERS 0x0044b130
GolFileParser::ParserTokenType GolBinParser::GetExpandedToken()
{
	ParserTokenType token;

	if (m_expandingTokenSequence) {
		LegoU32 sequenceIndex = m_tokenSequenceIndex;

		token = (ParserTokenType) m_tokenSequences[sequenceIndex][m_expansionTokenIndex++];

		if (m_expansionTokenIndex < m_tokenSequenceLengths[sequenceIndex]) {
			return token;
		}

		m_expansionTokenIndex = 0;
	}
	else if (m_expandingBracketSequence) {
		LegoU32 tokenIndex = m_expansionTokenIndex;

		token = g_binParserBracketSequence[tokenIndex];
		tokenIndex++;
		m_expansionTokenIndex = tokenIndex;

		if (tokenIndex < sizeOfArray(g_binParserBracketSequence)) {
			return token;
		}

		m_expansionTokenIndex = 0;
	}
	else {
		token = (ParserTokenType) m_expansionToken;
	}

	m_expansionRepeatCount--;

	if (m_expansionRepeatCount == 0) {
		m_expandingTokenSequence = FALSE;
		m_expandingBracketSequence = FALSE;
	}

	return token;
}

// FUNCTION: GOLDP 0x1002fa40 FOLDED
// FUNCTION: LEGORACERS 0x0044b1d0 FOLDED
undefined4 GolBinParser::VTable0x48(undefined4, undefined4)
{
	return 1;
}

// FUNCTION: GOLDP 0x10030e40
// FUNCTION: LEGORACERS 0x0044b1e0
void GolBinParser::HandleUnexpectedToken(ParserTokenType p_code)
{
	if (m_filePath == NULL) {
		GOL_FATALERROR_MESSAGE(ParserErrorCodeToString(p_code));
		return;
	}

	LegoS32 totalLen = strlen(ParserErrorCodeToString(p_code)) + strlen(m_filePath) + strlen(g_fileFormatStr);
	m_readBuffer[0] = '\0';

	if (totalLen < (LegoS32) sizeOfArray(m_readBuffer) - 1) {
		sprintf((LegoChar*) m_readBuffer, g_fileFormatStr, m_filePath);
	}

	strcat((LegoChar*) m_readBuffer, ParserErrorCodeToString(p_code));
	GOL_FATALERROR_MESSAGE((LegoChar*) m_readBuffer);
}

// FUNCTION: GOLDP 0x10030f10
// FUNCTION: LEGORACERS 0x0044b2b0
void GolBinParser::OpenFileForWrite(LegoChar* p_fileName)
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
		if (len < 64) {
			m_filePath = m_inlinePathBuffer;
		}
		else {
			m_filePath = new LegoChar[len + 1];
		}
		if (!m_filePath) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		strcpy(m_filePath, p_fileName);
		strcat(m_filePath, suffix);
	}
	else {
		if (len < 64) {
			m_filePath = m_inlinePathBuffer;
		}
		else {
			m_filePath = new LegoChar[len + 1];
		}
		if (!m_filePath) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		strcpy(m_filePath, p_fileName);
	}

	LegoS32 code = GolStream::BufferedOpen(m_filePath, c_modeWrite | c_modeCreate, 0x1000);
	if (code != e_ioSuccess) {
		HandleIoError(code);
	}

	m_fileOffset = 0;
	m_unk0x1f4 = 0;
}

// FUNCTION: GOLDP 0x10031070
// FUNCTION: LEGORACERS 0x0044b410
void GolBinParser::WriteToken(ParserTokenType p_token)
{
	if ((LegoU32) p_token > 0xff) {
		LegoU8 tokenHigh = (LegoU16) p_token >> 8;

		m_readBuffer[0] = 0x13;
		m_readBuffer[1] = (LegoU8) p_token;
		m_readBuffer[2] = tokenHigh;

		LegoS32 code = BufferedWrite(m_fileOffset, m_readBuffer, 3);
		if (code != e_ioSuccess) {
			HandleIoError(code);
		}

		m_fileOffset += 3;
	}
	else {
		m_readBuffer[0] = (LegoU8) p_token;

		LegoS32 code = BufferedWrite(m_fileOffset, m_readBuffer, 1);
		if (code != e_ioSuccess) {
			HandleIoError(code);
		}

		m_fileOffset++;
	}
}

// FUNCTION: GOLDP 0x10031100
// FUNCTION: LEGORACERS 0x0044b4a0
void GolBinParser::WriteByte(undefined4 p_param)
{
	*m_readBuffer = p_param;

	LegoS32 code = BufferedWrite(m_fileOffset, m_readBuffer, 1);
	if (code != e_ioSuccess) {
		HandleIoError(code);
	}

	m_fileOffset++;
}

// FUNCTION: GOLDP 0x10031140
// FUNCTION: LEGORACERS 0x0044b4e0
void GolBinParser::WriteFloat(LegoFloat p_param)
{
	*m_readBuffer = 3;

	LegoS32 code = BufferedWrite(m_fileOffset, m_readBuffer, 1);
	if (code != e_ioSuccess) {
		HandleIoError(code);
	}

	m_fileOffset++;

	LegoU32 buf;
	memcpy(&buf, &p_param, sizeof(buf));
	m_readBuffer[0] = (LegoU8) buf;
	m_readBuffer[1] = (LegoU8) (buf >> 8);
	m_readBuffer[2] = (LegoU8) (buf >> 16);
	m_readBuffer[3] = (LegoU8) (buf >> 24);

	code = BufferedWrite(m_fileOffset, m_readBuffer, sizeof(p_param));
	if (code != e_ioSuccess) {
		HandleIoError(code);
	}

	m_fileOffset += 4;
}

// FUNCTION: GOLDP 0x1002fd50 FOLDED
// FUNCTION: LEGORACERS 0x0044b570 FOLDED
void GolBinParser::WriteFloat2(LegoFloat p_param)
{
	WriteFloat(p_param);
}

// FUNCTION: GOLDP 0x100311d0
// FUNCTION: LEGORACERS 0x0044b580
void GolBinParser::WriteInt4(undefined4 p_param)
{
	*m_readBuffer = 4;

	LegoS32 code = BufferedWrite(m_fileOffset, m_readBuffer, 1);
	if (code != e_ioSuccess) {
		HandleIoError(code);
	}

	m_fileOffset++;

	m_readBuffer[0] = (LegoU8) p_param;
	m_readBuffer[1] = (LegoU8) (p_param >> 8);
	m_readBuffer[2] = (LegoU8) (p_param >> 16);
	m_readBuffer[3] = (LegoU8) (p_param >> 24);

	code = BufferedWrite(m_fileOffset, m_readBuffer, sizeof(p_param));
	if (code != e_ioSuccess) {
		HandleIoError(code);
	}

	m_fileOffset += 4;
}

// FUNCTION: GOLDP 0x10031260
// FUNCTION: LEGORACERS 0x0044b610
void GolBinParser::WriteString(LegoChar* p_str)
{
	*m_readBuffer = 2;

	LegoS32 code = BufferedWrite(m_fileOffset, m_readBuffer, 1);
	if (code != e_ioSuccess) {
		HandleIoError(code);
	}

	m_fileOffset++;

	LegoS32 len = strlen(p_str);
	if (len >= 63) {
		len = 63;
	}

	memcpy(m_readBuffer, p_str, len);

	code = BufferedWrite(m_fileOffset, m_readBuffer, len);
	if (code != e_ioSuccess) {
		HandleIoError(code);
	}

	m_fileOffset += len;

	*m_readBuffer = 2;
	code = BufferedWrite(m_fileOffset, m_readBuffer, 1);
	if (code != e_ioSuccess) {
		HandleIoError(code);
	}

	m_fileOffset++;
}

// FUNCTION: GOLDP 0x10029920 FOLDED
// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void GolBinParser::FlushLine()
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void GolBinParser::WriteSpace()
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void GolBinParser::WriteTab()
{
	// empty
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void GolBinParser::WriteTabs(undefined4)
{
	// empty
}
