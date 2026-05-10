#include "lavendervault0x764.h"

#include "golbinparser.h"
#include "golerror.h"

#include <string.h>

DECOMP_SIZE_ASSERT(LavenderVault0x764, 0x764)
DECOMP_SIZE_ASSERT(PcbTxtParser, 0x1fc)

// FUNCTION: LEGORACERS 0x00498700
LavenderVault0x764::LavenderVault0x764()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00498710
LavenderVault0x764::~LavenderVault0x764()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00498720
void LavenderVault0x764::Reset()
{
	m_loaded = FALSE;
	m_countLegs = 0;
	m_countTorsos = 0;
	m_countFaces = 0;
	m_countHats = 0;
}

// FUNCTION: LEGORACERS 0x00498740
LegoBool32 LavenderVault0x764::Load(const LegoChar* p_path, LegoBool32 p_binary)
{
	GolFileParser* parser;
	Destroy();

	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".pcb");
	}
	else {
		parser = new PcbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_path);
	ReadFile(*parser);
	if (parser != NULL) {
		delete parser;
	}

	m_loaded = TRUE;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00498850
LegoBool32 LavenderVault0x764::Destroy()
{
	if (m_loaded) {
		Reset();
	}

	return !m_loaded;
}

// FUNCTION: LEGORACERS 0x00498870
LegoS32 LavenderVault0x764::ReadBracketedCount(GolFileParser& p_parser) const
{
	p_parser.ReadLeftBracket();
	LegoS32 number = p_parser.ReadInteger();
	p_parser.ReadRightBracket();
	return number;
}

// FUNCTION: LEGORACERS 0x004988a0
void LavenderVault0x764::FUN_004988a0(GolFileParser& p_parser)
{
	const LegoChar* str;

	ReadBracketedCount(p_parser);
	p_parser.ReadLeftCurly();
	str = p_parser.ReadStringWithMaxLength(13);
	::memcpy(m_unk0x6da, str, 13);
	str = p_parser.ReadStringWithMaxLength(13);
	::memcpy(m_unk0x6e7, str, 13);
	str = p_parser.ReadStringWithMaxLength(13);
	::memcpy(m_unk0x6f4, str, 13);
	p_parser.ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00498930
void LavenderVault0x764::FUN_00498930(GolFileParser& p_parser)
{
	const LegoChar* str;

	ReadBracketedCount(p_parser);
	p_parser.ReadLeftCurly();
	str = p_parser.ReadStringWithMaxLength(sizeof(m_unk0x701) - 1);
	::memcpy(m_unk0x701, str, sizeof(m_unk0x701) - 1);
	str = p_parser.ReadStringWithMaxLength(sizeof(m_unk0x721) - 1);
	::memcpy(m_unk0x721, str, sizeof(m_unk0x721) - 1);
	p_parser.ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00498990
void LavenderVault0x764::ReadHats(GolFileParser& p_parser)
{
	const LegoChar* str;

	m_countHats = ReadBracketedCount(p_parser);
	if (m_countHats > static_cast<LegoS32>(sizeOfArray(m_hatNames))) {
		GOL_FATALERROR_MESSAGE("Too many hats!");
	}

	p_parser.ReadLeftCurly();

	for (LegoS32 i = 0; i < m_countHats; i++) {
		str = p_parser.ReadStringWithMaxLength(8);
		::memcpy(m_hatNames[i], str, sizeof(m_hatNames[i]));
		m_unk0x158[i] = p_parser.ReadInteger();
	}

	p_parser.ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00498a10
void LavenderVault0x764::ReadFaces(GolFileParser& p_parser)
{
	const LegoChar* str;

	m_countFaces = ReadBracketedCount(p_parser);
	if (m_countFaces > static_cast<LegoS32>(sizeOfArray(m_faceNames))) {
		GOL_FATALERROR_MESSAGE("Too many faces!");
	}

	p_parser.ReadLeftCurly();
	str = p_parser.ReadStringWithMaxLength(sizeof(m_unk0x180));
	::memcpy(m_unk0x180, str, sizeof(m_unk0x180));

	for (LegoS32 i = 0; i < m_countFaces; i++) {
		str = p_parser.ReadString();
		::strcpy(m_faceNames[i], str);
		m_unk0x224[i] = p_parser.ReadInteger();
	}

	p_parser.ReadRightCurly();
	::strcpy(m_faceExpressions[0], "dflt");
	::strcpy(m_faceExpressions[1], "angry");
	::strcpy(m_faceExpressions[2], "blink");
	::strcpy(m_faceExpressions[3], "happy");
	::strcpy(m_faceExpressions[4], "sad");
	::strcpy(m_faceExpressions[5], "suprz");
}

// FUNCTION: LEGORACERS 0x00498bc0
void LavenderVault0x764::ReadTorsos(GolFileParser& p_parser)
{
	const LegoChar* str;

	m_countTorsos = ReadBracketedCount(p_parser);
	if (m_countTorsos > static_cast<LegoS32>(sizeOfArray(m_torsoNames))) {
		GOL_FATALERROR_MESSAGE("Too many torsos");
	}

	p_parser.ReadLeftCurly();
	str = p_parser.ReadStringWithMaxLength(sizeof(m_unk0x242[0]));
	::memcpy(&m_unk0x242[0], str, sizeof(m_unk0x242[0]));
	str = p_parser.ReadStringWithMaxLength(sizeof(m_unk0x242[1]));
	::memcpy(&m_unk0x242[1], str, sizeof(m_unk0x242[1]));

	for (LegoS32 i = 0; i < m_countTorsos; i++) {
		str = p_parser.ReadStringWithMaxLength(sizeof(m_torsoNames[i]));
		::memcpy(m_torsoNames[i], str, sizeof(m_torsoNames[i]));
		m_unk0x344[i] = p_parser.ReadInteger();
		m_unk0x3bc[i] = p_parser.ReadInteger();
	}

	p_parser.ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00498c90
void LavenderVault0x764::ReadLegs(GolFileParser& p_parser)
{
	const LegoChar* str;

	m_countLegs = ReadBracketedCount(p_parser);
	if (m_countLegs > static_cast<LegoS32>(sizeOfArray(m_legNames))) {
		GOL_FATALERROR_MESSAGE("Too many legs!");
	}

	p_parser.ReadLeftCurly();
	str = p_parser.ReadStringWithMaxLength(sizeof(m_unk0x3da[0]));
	::strncpy(m_unk0x3da[0], str, sizeof(m_unk0x3da[0]));
	str = p_parser.ReadStringWithMaxLength(sizeof(m_unk0x3da[1]));
	::strncpy(m_unk0x3da[1], str, sizeof(m_unk0x3da[1]));

	for (LegoS32 i = 0; i < m_countLegs; i++) {
		str = p_parser.ReadStringWithMaxLength(sizeof(m_legNames[i]));
		::strncpy(m_legNames[i], str, sizeof(m_legNames[i]));
		m_unk0x4dc[i] = p_parser.ReadInteger();
		m_unk0x554[i] = p_parser.ReadInteger();
	}

	p_parser.ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00498d70
void LavenderVault0x764::ReadHeadHats(GolFileParser& p_parser)
{
	const LegoChar* str;

	LegoS32 count = ReadBracketedCount(p_parser);
	if (count > static_cast<LegoS32>(sizeOfArray(m_headHatNames))) {
		GOL_FATALERROR_MESSAGE("Too many head hats!");
	}

	p_parser.ReadLeftCurly();

	for (LegoS32 i = 0; i < count; i++) {
		str = p_parser.ReadStringWithMaxLength(sizeof(m_headHatNames[i]));
		::strncpy(m_headHatNames[i], str, sizeof(m_headHatNames[i]));
	}

	p_parser.ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00498de0
void LavenderVault0x764::FUN_00498de0(GolFileParser& p_parser)
{
	const LegoChar* str;

	m_unk0x014 = ReadBracketedCount(p_parser);
	p_parser.ReadLeftCurly();

	for (LegoS32 i = 0; i < m_unk0x014; i++) {
		str = p_parser.ReadStringWithMaxLength(sizeof(m_unk0x6b2[i]));
		::strncpy(m_unk0x6b2[i], str, sizeof(m_unk0x6b2[i]));
	}

	p_parser.ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00498e40
void LavenderVault0x764::FUN_00498e40(GolFileParser& p_parser)
{
	const LegoChar* str;

	LegoS32 count = ReadBracketedCount(p_parser);
	p_parser.ReadLeftCurly();

	for (LegoS32 i = 0; i < count; i++) {
		str = p_parser.ReadStringWithMaxLength(sizeof(m_unk0x741[i]));
		::strncpy(m_unk0x741[i], str, sizeof(m_unk0x741[i]));
	}

	p_parser.ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00498e90
void LavenderVault0x764::ReadFile(GolFileParser& p_parser)
{
	GolFileParser::ParserTokenType token;

	while ((token = p_parser.GetNextToken()) != 0) {
		switch (token) {
		case GolFileParser::e_unknown0x27:
			FUN_004988a0(p_parser);
			break;
		case GolFileParser::e_unknown0x28:
			FUN_00498930(p_parser);
			break;
		case GolFileParser::e_unknown0x29:
			ReadHats(p_parser);
			break;
		case GolFileParser::e_unknown0x2a:
			ReadFaces(p_parser);
			break;
		case GolFileParser::e_unknown0x2b:
			ReadTorsos(p_parser);
			break;
		case GolFileParser::e_unknown0x2c:
			ReadLegs(p_parser);
			break;
		case GolFileParser::e_unknown0x2d:
			ReadHeadHats(p_parser);
			break;
		case GolFileParser::e_unknown0x2e:
			FUN_00498de0(p_parser);
			break;
		case GolFileParser::e_unknown0x2f:
			FUN_00498e40(p_parser);
			break;
		default:
			p_parser.HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x00498f50
void LavenderVault0x764::CopyHatName(LegoS32 p_index, LegoChar* p_buffer) const
{
	::strncpy(p_buffer, m_hatNames[p_index], sizeof(m_hatNames[p_index]));
}

// FUNCTION: LEGORACERS 0x00498f70
void LavenderVault0x764::FUN_00498f70(LegoS32 p_index, LegoChar* p_buffer1, LegoChar* p_buffer2) const
{
	::strncpy(p_buffer1, m_unk0x180, sizeof(m_unk0x180));
	::strcpy(p_buffer2, m_faceNames[p_index]);
	::strncat(p_buffer2, m_faceExpressions[0], sizeOfArray(m_faceExpressions) - 1);
}

// FUNCTION: LEGORACERS 0x00498fd0
void LavenderVault0x764::FUN_00498fd0(LegoS32 p_index, LegoChar* p_buffer1, LegoChar* p_buffer2) const
{
	::strncpy(p_buffer1, m_unk0x242[m_unk0x344[p_index]], sizeof(m_unk0x242[m_unk0x344[p_index]]));
	::strncpy(p_buffer2, m_torsoNames[p_index], sizeof(m_torsoNames[p_index]));
}

// FUNCTION: LEGORACERS 0x00499020
void LavenderVault0x764::FUN_00499020(LegoS32 p_index, LegoChar* p_buffer1, LegoChar* p_buffer2) const
{
	::strncpy(p_buffer1, m_unk0x3da[m_unk0x4dc[p_index]], sizeof(m_unk0x3da[m_unk0x4dc[p_index]]));
	::strncpy(p_buffer2, m_legNames[p_index], sizeof(m_legNames[p_index]));
}

// FUNCTION: LEGORACERS 0x00499070
void LavenderVault0x764::FUN_00499070(LegoS32 p_index, LegoChar* p_buffer) const
{
	::strncpy(p_buffer, m_unk0x6b2[p_index], sizeof(m_unk0x6b2[p_index]));
}

// FUNCTION: LEGORACERS 0x00499090
void LavenderVault0x764::CopyHeadHatName(LegoS32 p_index, LegoChar* p_buffer) const
{
	::strncpy(p_buffer, m_headHatNames[p_index], sizeof(m_headHatNames[p_index]));
}

// FUNCTION: LEGORACERS 0x004990b0
void LavenderVault0x764::BuildFaceExpressionName(
	LegoS32 p_faceIndex,
	LegoS32 p_expressionIndex,
	LegoChar* p_buffer
) const
{
	::strcpy(p_buffer, m_faceNames[p_faceIndex]);
	::strncpy(
		&p_buffer[3],
		m_faceExpressions[p_expressionIndex],
		sizeOfArray(m_faceExpressions[p_expressionIndex]) - 1
	);
}
