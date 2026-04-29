#include "golbinparser.h"

#include "golerror.h"

#include <stdio.h>

// GLOBAL: GOLDP 0x10065b58
// GLOBAL: LEGORACERS 0x004c7070
const LegoFloat g_token0x0fconstant = 1.0f / 4096.0f;

// GLOBAL: GOLDP 0x10065b60
// GLOBAL: LEGORACERS 0x004c7078
const LegoFloat g_token0x10constant = 1.0f / 32.0f;

// GLOBAL: GOLDP 0x10065b64
// GLOBAL: LEGORACERS 0x004c707c
const LegoFloat g_token0x12constant = 1.0f / 127.0f;

// GLOBAL: GOLDP 0x1005f030
// GLOBAL: LEGORACERS 0x004c182c
const LegoChar* g_fileFormatStr = "file %s\n";

// GLOBAL: GOLDP 0x100577f8
// GLOBAL: LEGORACERS 0x004b0df8
const GolFileParser::ParserTokenType g_binParserBracketSequence[] =
	{GolFileParser::e_leftBracket, GolFileParser::e_int, GolFileParser::e_rightBracket, GolFileParser::e_rightBracket};

// STUB: GOLDP 0x1002fff0
// STUB: LEGORACERS 0x0044a7e0
GolBinParser::GolBinParser()
{
	FUN_0044a830();
}

// FUNCTION: LEGORACERS 0x0044a830
void GolBinParser::FUN_0044a830()
{
	m_unk0x1f0 = 0;
	m_unk0x1f4 = 0;
	m_unk0x1f8 = 0;
	m_unk0x1fc = 0;
	m_unk0x200 = 0;
	m_unk0x204 = 0;
	m_unk0x208 = 0;
	m_unk0x20c = 0;
	memset(m_unk0x210, 0, sizeof(m_unk0x210));
	memset(m_unk0x610, 0, sizeof(m_unk0x610));
}

// STUB: GOLDP 0x10030070
// STUB: LEGORACERS 0x0044a890
void GolBinParser::VTable0x38(const LegoChar*)
{
	// TODO
	STUB(0x0044a890);
}

// FUNCTION: GOLDP 0x10030280
// FUNCTION: LEGORACERS 0x0044aaa0
LegoS32 GolBinParser::Dispose()
{
	LegoS32 result = GolFileParser::Dispose();
	FUN_0044a830();
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

	if (m_unk0x30) {
		m_unk0x30 = 0;
		return (GolFileParser::ParserTokenType) m_unk0x34;
	}

	while (1) {
		LegoU32 t;
		if (m_unk0x1f8) {
			t = FUN_0044b130();
		}
		else {
			if (!FUN_0044b0b0(1)) {
				return e_syntaxerror;
			}
			t = ((LegoU8) m_unk0xa4[0]);
		}

		switch (t) {
		case 0x14:
			if (!FUN_0044b0b0(2)) {
				return e_syntaxerror;
			}

			m_unk0x1f8 = ((LegoU8) m_unk0xa4[0]) + ((LegoU8) m_unk0xa4[1] << 8);

			if (!FUN_0044b0b0(1)) {
				return e_syntaxerror;
			}

			m_unk0x1fc = (LegoU8) m_unk0xa4[0];
			if (m_unk0x1fc == 0x13) {
				if (!FUN_0044b0b0(2)) {
					return e_syntaxerror;
				}

				m_unk0x1fc = ((LegoU8) m_unk0xa4[0]) + ((LegoU8) m_unk0xa4[1] << 8);
			}

			m_unk0x204 = 0;

			if (m_unk0x1fc >= 0x17 && m_unk0x1fc <= 0x26) {
				m_unk0x208 = m_unk0x1fc - 0x17;
				// TODO: ???
				if (&m_unk0x210[m_unk0x208][0] == 0) {
					HandleUnexpectedToken(e_syntaxerror);
				}

				m_unk0x20c = 0;
				m_unk0x204 = 1;
			}
			else if (m_unk0x1fc == 0x15) {
				m_unk0x200 = 1;
				m_unk0x20c = 0;
			}

			break;

		case 0x15:
			m_unk0x1f8 = 1;
			m_unk0x200 = 1;
			m_unk0x20c = 0;
			m_unk0x204 = 0;
			break;

		case 0x16:
			FUN_0044b020();
			if (m_unk0x34 == e_syntaxerror) {
				return e_syntaxerror;
			}

			break;

		default:
			if (t >= 0x17 && t <= 0x26) {
				m_unk0x208 = t - 0x17;
				// TODO: ???
				if (&m_unk0x210[m_unk0x208][0] == 0) {
					HandleUnexpectedToken(e_syntaxerror);
				}

				m_unk0x20c = 0;
				m_unk0x204 = 1;
				m_unk0x1f8 = 1;
				break;
			}

			m_unk0x34 = (GolFileParser::ParserTokenType) t;
			return (GolFileParser::ParserTokenType) m_unk0x34;

		case 2:
			lenRead;
			code = BufferedRead(m_unk0x1f0, m_unk0xa4, 63, &lenRead);
			if (code != e_ioSuccess) {
				if (code == e_ioEndOfFile) {
					if (lenRead == 0) {
						m_unk0x34 = e_syntaxerror;
						return e_syntaxerror;
					}
				}
				else {
					FUN_10032580(code);
				}
			}

			for (i = 0; i < lenRead; i++) {
				if (m_unk0xa4[i] == '\0') {
					break;
				}

				m_unk0x44[i] = m_unk0xa4[i];
			}

			m_unk0x44[i++] = '\0';
			m_unk0x1f0 += i;

			m_unk0x34 = (GolFileParser::ParserTokenType) t;
			return (GolFileParser::ParserTokenType) m_unk0x34;

		case 3: {
			if (!FUN_0044b0b0(4)) {
				return e_syntaxerror;
			}

			LegoU32 floatBits = (((LegoU32) m_unk0xa4[3] << 8) + (LegoU32) m_unk0xa4[2]);
			floatBits = (floatBits << 8) + (LegoU32) m_unk0xa4[1];
			floatBits = (floatBits << 8) + (LegoU32) m_unk0xa4[0];
			m_unk0x40 = *(LegoFloat*) &floatBits;

			m_unk0x34 = (GolFileParser::ParserTokenType) t;
			return (GolFileParser::ParserTokenType) m_unk0x34;
		}

		case 4: {
			if (!FUN_0044b0b0(4)) {
				return e_syntaxerror;
			}

			LegoU32 intBits = (((LegoU32) m_unk0xa4[3] << 8) + (LegoU32) m_unk0xa4[2]);
			intBits = (intBits << 8) + (LegoU32) m_unk0xa4[1];
			intBits = (intBits << 8) + (LegoU32) m_unk0xa4[0];
			m_unk0x38 = intBits;

			m_unk0x34 = (GolFileParser::ParserTokenType) t;
			return (GolFileParser::ParserTokenType) m_unk0x34;
		}

		case 0xb:
			if (!FUN_0044b0b0(1)) {
				return e_syntaxerror;
			}

#ifdef BUILDING_GOL
			m_unk0x38 = (LegoU8) (m_unk0xa4[0]);
			m_unk0x34 = e_int;
#else
			m_unk0x34 = e_int;
			m_unk0x38 = (LegoU8) (m_unk0xa4[0]);
#endif
			return (GolFileParser::ParserTokenType) m_unk0x34;

		case 0xc:
			if (!FUN_0044b0b0(1)) {
				return e_syntaxerror;
			}

			m_unk0x38 = (LegoU8) (m_unk0xa4[0]);
			m_unk0x34 = e_int;
			return (GolFileParser::ParserTokenType) m_unk0x34;

		case 0xd:
			if (!FUN_0044b0b0(2)) {
				return e_syntaxerror;
			}

			m_unk0x38 = (LegoS16) (m_unk0xa4[0] + (m_unk0xa4[1] << 8));
			m_unk0x34 = e_int;
			return (GolFileParser::ParserTokenType) m_unk0x34;

		case 0xe:
			if (!FUN_0044b0b0(2)) {
				return e_syntaxerror;
			}

#ifdef BUILDING_GOL
			m_unk0x38 = (LegoU16) (m_unk0xa4[0] + (m_unk0xa4[1] << 8));
			m_unk0x34 = e_int;
#else
			m_unk0x34 = e_int;
			m_unk0x38 = (LegoU16) (m_unk0xa4[0] + (m_unk0xa4[1] << 8));
#endif
			return (GolFileParser::ParserTokenType) m_unk0x34;

		case 0xf:
			if (!FUN_0044b0b0(2)) {
				return e_syntaxerror;
			}

			m_unk0x40 = g_token0x0fconstant * (LegoS16) (m_unk0xa4[0] + ((m_unk0xa4[1] << 8)));
			m_unk0x34 = e_float;
			return (GolFileParser::ParserTokenType) m_unk0x34;

		case 0x10:
			if (!FUN_0044b0b0(2)) {
				return e_syntaxerror;
			}

			m_unk0x40 = g_token0x10constant * (LegoS16) (m_unk0xa4[0] + ((m_unk0xa4[1] << 8)));
			m_unk0x34 = e_float;
			return (GolFileParser::ParserTokenType) m_unk0x34;

		case 0x11:
			if (!FUN_0044b0b0(2)) {
				return e_syntaxerror;
			}

			m_unk0x40 = (LegoS16) (m_unk0xa4[0] + ((m_unk0xa4[1] << 8)));
			m_unk0x34 = e_float;
			return (GolFileParser::ParserTokenType) m_unk0x34;

		case 0x12:
			if (!FUN_0044b0b0(1)) {
				return e_syntaxerror;
			}

			m_unk0x40 = g_token0x12constant * (LegoU8) (m_unk0xa4[0]);
			m_unk0x34 = e_float;
			return (GolFileParser::ParserTokenType) m_unk0x34;

		case 0x13: {
			if (!FUN_0044b0b0(2)) {
				return e_syntaxerror;
			}

			token = (ParserTokenType) ((LegoU8) m_unk0xa4[1]);
			token = (ParserTokenType) ((LegoU32) token << 8);
			token = (ParserTokenType) (token + (LegoU8) m_unk0xa4[0]);
			m_unk0x34 = token;
			return token;
		}
		}
	}
}

// FUNCTION: GOLDP 0x10030c30
// FUNCTION: LEGORACERS 0x0044b020
void GolBinParser::FUN_0044b020()
{
	if (!FUN_0044b0b0(2)) {
		return;
	}

	LegoU32 sequenceIndex = (LegoU8) m_unk0xa4[0] - 0x17;
	LegoU32 count = (LegoU8) m_unk0xa4[1];
	m_unk0x610[sequenceIndex] = count;

	for (LegoU32 i = 0; i < count; i++) {
		if (!FUN_0044b0b0(1)) {
			return;
		}

		LegoU32 token = (LegoU8) m_unk0xa4[0];
		if (token == 0x13) {
			if (!FUN_0044b0b0(2)) {
				return;
			}

			token = ((LegoU8) m_unk0xa4[1] << 8) + (LegoU8) m_unk0xa4[0];
		}

		m_unk0x210[sequenceIndex][i] = token;
	}
}

// FUNCTION: LEGORACERS 0x0044b0b0
undefined4 GolBinParser::FUN_0044b0b0(LegoS32 p_size)
{
	LegoS32 lenRead;
	LegoS32 code = BufferedRead(m_unk0x1f0, m_unk0xa4, p_size, &lenRead);
	if (code != e_ioSuccess) {
		if (code == e_ioEndOfFile) {
			if (lenRead == 0) {
				m_unk0x34 = e_syntaxerror;
				return 0;
			}
		}
		else {
			FUN_10032580(code);
		}
	}

	if (lenRead != p_size) {
		HandleUnexpectedToken(e_syntaxerror);
	}

	m_unk0x1f0 += p_size;
	return 1;
}

// STUB: GOLDP 0x10030da0
// STUB: LEGORACERS 0x0044b130
GolFileParser::ParserTokenType GolBinParser::FUN_0044b130()
{
	ParserTokenType token;

	if (m_unk0x204) {
		LegoU32 sequenceIndex = m_unk0x208;
		LegoU32 tokenIndex = m_unk0x20c;

		token = (ParserTokenType) m_unk0x210[sequenceIndex][tokenIndex++];
		m_unk0x20c = tokenIndex;

		if (tokenIndex < m_unk0x610[sequenceIndex]) {
			return token;
		}

		m_unk0x20c = 0;
	}
	else if (m_unk0x200) {
		LegoU32 tokenIndex = m_unk0x20c;

		token = g_binParserBracketSequence[tokenIndex];
		tokenIndex++;
		m_unk0x20c = tokenIndex;

		if (tokenIndex < sizeOfArray(g_binParserBracketSequence)) {
			return token;
		}

		m_unk0x20c = 0;
	}
	else {
		token = (ParserTokenType) m_unk0x1fc;
	}

	m_unk0x1f8--;

	if (m_unk0x1f8 == 0) {
		m_unk0x204 = 0;
		m_unk0x200 = 0;
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
	m_unk0xa4[0] = '\0';

	if (totalLen < (LegoS32) sizeOfArray(m_unk0xa4) - 1) {
		sprintf((LegoChar*) m_unk0xa4, g_fileFormatStr, m_filePath);
	}

	strcat((LegoChar*) m_unk0xa4, ParserErrorCodeToString(p_code));
	GOL_FATALERROR_MESSAGE((LegoChar*) m_unk0xa4);
}

// FUNCTION: GOLDP 0x10030f10
// FUNCTION: LEGORACERS 0x0044b2b0
void GolBinParser::OpenFile(LegoChar* p_fileName)
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
			m_filePath = m_unk0x1a8;
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
			m_filePath = m_unk0x1a8;
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
		FUN_10032580(code);
	}

	m_unk0x1f0 = 0;
	m_unk0x1f4 = 0;
}

// STUB: GOLDP 0x10031070
// STUB: LEGORACERS 0x0044b410
void GolBinParser::VTable0x50(undefined4)
{
	// TODO
	STUB(0x0044b410);
}

// FUNCTION: GOLDP 0x10031100
// FUNCTION: LEGORACERS 0x0044b4a0
void GolBinParser::VTable0x54(undefined4 p_param)
{
	*m_unk0xa4 = p_param;
	LegoS32 code = BufferedWrite(m_unk0x1f0, m_unk0xa4, 1);
	if (code != e_ioSuccess) {
		FUN_10032580(code);
	}

	m_unk0x1f0++;
}

// FUNCTION: GOLDP 0x10031140
// FUNCTION: LEGORACERS 0x0044b4e0
void GolBinParser::WriteFloat(LegoFloat p_param)
{
	*m_unk0xa4 = 3;
	LegoS32 code = BufferedWrite(m_unk0x1f0, m_unk0xa4, 1);
	if (code != e_ioSuccess) {
		FUN_10032580(code);
	}

	m_unk0x1f0++;

	LegoU32 buf;
	memcpy(&buf, &p_param, sizeof(buf));
	m_unk0xa4[0] = (LegoU8) buf;
	m_unk0xa4[1] = (LegoU8) (buf >> 8);
	m_unk0xa4[2] = (LegoU8) (buf >> 16);
	m_unk0xa4[3] = (LegoU8) (buf >> 24);

	code = BufferedWrite(m_unk0x1f0, m_unk0xa4, sizeof(p_param));
	if (code != e_ioSuccess) {
		FUN_10032580(code);
	}

	m_unk0x1f0 += 4;
}

// FUNCTION: GOLDP 0x1002fd50 FOLDED
// FUNCTION: LEGORACERS 0x0044b570 FOLDED
void GolBinParser::VTable0x5c(LegoFloat p_param)
{
	WriteFloat(p_param);
}

// FUNCTION: GOLDP 0x100311d0
// FUNCTION: LEGORACERS 0x0044b580
void GolBinParser::WriteInt4(undefined4 p_param)
{
	*m_unk0xa4 = 4;
	LegoS32 code = BufferedWrite(m_unk0x1f0, m_unk0xa4, 1);
	if (code != e_ioSuccess) {
		FUN_10032580(code);
	}

	m_unk0x1f0++;

	m_unk0xa4[0] = (LegoU8) p_param;
	m_unk0xa4[1] = (LegoU8) (p_param >> 8);
	m_unk0xa4[2] = (LegoU8) (p_param >> 16);
	m_unk0xa4[3] = (LegoU8) (p_param >> 24);

	code = BufferedWrite(m_unk0x1f0, m_unk0xa4, sizeof(p_param));
	if (code != e_ioSuccess) {
		FUN_10032580(code);
	}

	m_unk0x1f0 += 4;
}

// FUNCTION: GOLDP 0x10031260
// FUNCTION: LEGORACERS 0x0044b610
void GolBinParser::WriteString(LegoChar* p_str)
{
	*m_unk0xa4 = 2;
	LegoS32 code = BufferedWrite(m_unk0x1f0, m_unk0xa4, 1);
	if (code != e_ioSuccess) {
		FUN_10032580(code);
	}

	m_unk0x1f0++;

	LegoS32 len = strlen(p_str);
	if (len >= 63) {
		len = 63;
	}

	memcpy(m_unk0xa4, p_str, len);

	code = BufferedWrite(m_unk0x1f0, m_unk0xa4, len);
	if (code != e_ioSuccess) {
		FUN_10032580(code);
	}

	m_unk0x1f0 += len;

	*m_unk0xa4 = 2;
	code = BufferedWrite(m_unk0x1f0, m_unk0xa4, 1);
	if (code != e_ioSuccess) {
		FUN_10032580(code);
	}

	m_unk0x1f0++;
}

// FUNCTION: GOLDP 0x10029920 FOLDED
// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void GolBinParser::VTable0x68()
{
}

// FUNCTION: GOLDP 0x10029920 FOLDED
// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void GolBinParser::VTable0x6c()
{
}

// FUNCTION: GOLDP 0x10029920 FOLDED
// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void GolBinParser::VTable0x70()
{
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void GolBinParser::VTable0x74(undefined4)
{
}
