#include "goltxtparser.h"

#include "golerror.h"

#include <stdio.h>

// FUNCTION: GOLDP 0x1002fa20
// FUNCTION: LEGORACERS 0x0044a1d0
const LegoChar* GolTxtParser::GetSuffix()
{
	return ".txt";
}

// STUB: LEGORACERS 0x0044a1f0
void GolTxtParser::VTable0x4c()
{
	// TODO
	STUB(0x0044a1f0);
}

// FUNCTION: GOLDP 0x1002fba0
// FUNCTION: LEGORACERS 0x0044a340
void GolTxtParser::VTable0x50(undefined4 p_token)
{
	if (m_unk0x1f4 + sizeof(m_unk0x84) >= sizeof(m_unk0xa4) - 1) {
		VTable0x68();
	}

	switch (p_token) {
	case 5:
		m_unk0xa4[m_unk0x1f4++] = '{';
		break;
	case 6:
		m_unk0xa4[m_unk0x1f4++] = '}';
		break;
	case 7:
		m_unk0xa4[m_unk0x1f4++] = '[';
		break;
	case 8:
		m_unk0xa4[m_unk0x1f4++] = ']';
		break;
	case 9:
		m_unk0xa4[m_unk0x1f4++] = ',';
		break;
	case 10:
		m_unk0xa4[m_unk0x1f4++] = ';';
		break;
	default:
		VTable0x54(p_token);
		break;
	}
}

// FUNCTION: GOLDP 0x1002fcb0
// FUNCTION: LEGORACERS 0x0044a450
void GolTxtParser::VTable0x54(undefined4 p_param)
{
	if (p_param) {
		GOL_FATALERROR_MESSAGE("Cannot write invalid token");
	}
}

// FUNCTION: GOLDP 0x1002fcd0
// FUNCTION: LEGORACERS 0x0044a470
void GolTxtParser::WriteFloat(LegoFloat p_param)
{
	// TODO: style fix?
	if (m_unk0x1f4 + sizeof(m_unk0x84) >= sizeof(m_unk0xa4) - 1) {
		VTable0x68();
	}

	sprintf(m_unk0x84, "%f", p_param);
	LegoS32 len = strlen(m_unk0x84);
	memcpy(&m_unk0xa4[m_unk0x1f4], m_unk0x84, len);
	m_unk0x1f4 += len;
}

// FUNCTION: GOLDP 0x1002fd60
// FUNCTION: LEGORACERS 0x0044a4f0
void GolTxtParser::WriteInt4(undefined4 p_param)
{
	// TODO: style fix?
	if (m_unk0x1f4 + sizeof(m_unk0x84) >= sizeof(m_unk0xa4) - 1) {
		VTable0x68();
	}

	sprintf(m_unk0x84, "%d", p_param);
	LegoS32 len = strlen(m_unk0x84);
	memcpy(&m_unk0xa4[m_unk0x1f4], m_unk0x84, len);
	m_unk0x1f4 += len;
}

// FUNCTION: GOLDP 0x1002fdd0
// FUNCTION: LEGORACERS 0x0044a570
void GolTxtParser::WriteString(LegoChar* p_str)
{
	LegoS32 len = strlen(p_str);
	// TODO: style fix?
	if (len + 4 >= sizeof(m_unk0xa4) - 1) {
		VTable0x68();
	}

	m_unk0xa4[m_unk0x1f4++] = '"';
	memcpy(&m_unk0xa4[m_unk0x1f4], p_str, len);
	m_unk0x1f4 += len;
	m_unk0xa4[m_unk0x1f4++] = '"';
}

// FUNCTION: GOLDP 0x1002fe60
// FUNCTION: LEGORACERS 0x0044a600
void GolTxtParser::VTable0x68()
{
	LegoS32 code = WriteLine(m_unk0xa4, m_unk0x1f4);
	if (code != e_ioSuccess) {
		FUN_10032580(code);
	}

	m_unk0x1f0++;
	m_unk0x1f4 = 0;
}

// FUNCTION: GOLDP 0x1002fea0
// FUNCTION: LEGORACERS 0x0044a640
void GolTxtParser::VTable0x6c()
{
	if (m_unk0x1f4 + 2 >= sizeof(m_unk0xa4) - 1) {
		VTable0x68();
	}

	m_unk0xa4[m_unk0x1f4] = ' ';
	m_unk0x1f4++;
}

// FUNCTION: GOLDP 0x1002fee0
// FUNCTION: LEGORACERS 0x0044a680
void GolTxtParser::VTable0x70()
{
	if (m_unk0x1f4 + 2 >= sizeof(m_unk0xa4) - 1) {
		VTable0x68();
	}

	m_unk0xa4[m_unk0x1f4] = '\t';
	m_unk0x1f4++;
}

// FUNCTION: GOLDP 0x1002ff20
// FUNCTION: LEGORACERS 0x0044a6c0
void GolTxtParser::VTable0x74(undefined4 p_param)
{
	// TODO: style fix?
	if (p_param + m_unk0x1f4 + 1 >= sizeof(m_unk0xa4) - 1) {
		VTable0x68();
	}

	while (p_param > 0) {
		m_unk0xa4[m_unk0x1f4] = '\t';
		m_unk0x1f4++;
		p_param--;
	}
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void GolTxtParser::VTable0x40(undefined4)
{
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
// FUNCTION: LEGORACERS 0x0044a1e0 FOLDED
undefined4 GolTxtParser::VTable0x44()
{
	return 1;
}

// FUNCTION: GOLDP 0x1002fa40 FOLDED
// FUNCTION: LEGORACERS 0x0044b1d0 FOLDED
undefined4 GolTxtParser::VTable0x48(undefined4, undefined4)
{
	return 1;
}

// STUB: GOLDP 0x1002fd50 FOLDED
// STUB: LEGORACERS 0x0044b570 FOLDED
void GolTxtParser::VTable0x5c()
{
	// TODO
	STUB(0x0044b570);
}
