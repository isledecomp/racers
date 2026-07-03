#include "racer/driverpartcatalog.h"

#include "golbinparser.h"
#include "golerror.h"

#include <string.h>

DECOMP_SIZE_ASSERT(DriverPartCatalog, 0x764)
DECOMP_SIZE_ASSERT(DriverPartCatalog::PcbTxtParser, 0x1fc)

// FUNCTION: LEGORACERS 0x00498700
DriverPartCatalog::DriverPartCatalog()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00498710
DriverPartCatalog::~DriverPartCatalog()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00498720
void DriverPartCatalog::Reset()
{
	m_loaded = FALSE;
	m_legCount = 0;
	m_torsoCount = 0;
	m_faceCount = 0;
	m_hatCount = 0;
}

// FUNCTION: LEGORACERS 0x00498740
LegoBool32 DriverPartCatalog::Load(const LegoChar* p_path, LegoBool32 p_binary)
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
LegoBool32 DriverPartCatalog::Destroy()
{
	if (m_loaded) {
		Reset();
	}

	return !m_loaded;
}

// FUNCTION: LEGORACERS 0x00498870
LegoS32 DriverPartCatalog::ReadBracketedCount(GolFileParser& p_parser) const
{
	p_parser.ReadLeftBracket();
	LegoS32 number = p_parser.ReadInteger();
	p_parser.ReadRightBracket();
	return number;
}

// FUNCTION: LEGORACERS 0x004988a0
void DriverPartCatalog::ReadModelFileNames(GolFileParser& p_parser)
{
	const LegoChar* str;

	ReadBracketedCount(p_parser);
	p_parser.ReadLeftCurly();
	str = p_parser.ReadStringWithMaxLength(13);
	::memcpy(m_headModelFileName, str, 13);
	str = p_parser.ReadStringWithMaxLength(13);
	::memcpy(m_bodyModelFileNames[0], str, 13);
	str = p_parser.ReadStringWithMaxLength(13);
	::memcpy(m_bodyModelFileNames[1], str, 13);
	p_parser.ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00498930
void DriverPartCatalog::ReadModelDirectories(GolFileParser& p_parser)
{
	const LegoChar* str;

	ReadBracketedCount(p_parser);
	p_parser.ReadLeftCurly();
	str = p_parser.ReadStringWithMaxLength(sizeof(m_modelDirectories[0]) - 1);
	::memcpy(m_modelDirectories[0], str, sizeof(m_modelDirectories[0]) - 1);
	str = p_parser.ReadStringWithMaxLength(sizeof(m_modelDirectories[1]) - 1);
	::memcpy(m_modelDirectories[1], str, sizeof(m_modelDirectories[1]) - 1);
	p_parser.ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00498990
void DriverPartCatalog::ReadHats(GolFileParser& p_parser)
{
	const LegoChar* str;

	m_hatCount = ReadBracketedCount(p_parser);
	if (m_hatCount > static_cast<LegoS32>(sizeOfArray(m_hatNames))) {
		GOL_FATALERROR_MESSAGE("Too many hats!");
	}

	p_parser.ReadLeftCurly();

	for (LegoS32 i = 0; i < m_hatCount; i++) {
		str = p_parser.ReadStringWithMaxLength(sizeof(m_hatNames[i]));
		::memcpy(m_hatNames[i], str, sizeof(m_hatNames[i]));
		m_hatUnlockFlags[i] = p_parser.ReadInteger();
	}

	p_parser.ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00498a10
void DriverPartCatalog::ReadFaces(GolFileParser& p_parser)
{
	const LegoChar* str;

	m_faceCount = ReadBracketedCount(p_parser);
	if (m_faceCount > static_cast<LegoS32>(sizeOfArray(m_faceNames))) {
		GOL_FATALERROR_MESSAGE("Too many faces!");
	}

	p_parser.ReadLeftCurly();
	str = p_parser.ReadStringWithMaxLength(sizeof(m_faceDirectory));
	::memcpy(m_faceDirectory, str, sizeof(m_faceDirectory));

	for (LegoS32 i = 0; i < m_faceCount; i++) {
		str = p_parser.ReadString();
		::strcpy(m_faceNames[i], str);
		m_faceUnlockFlags[i] = p_parser.ReadInteger();
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
void DriverPartCatalog::ReadTorsos(GolFileParser& p_parser)
{
	const LegoChar* str;

	m_torsoCount = ReadBracketedCount(p_parser);
	if (m_torsoCount > static_cast<LegoS32>(sizeOfArray(m_torsoNames))) {
		GOL_FATALERROR_MESSAGE("Too many torsos");
	}

	p_parser.ReadLeftCurly();
	str = p_parser.ReadStringWithMaxLength(sizeof(m_torsoVariantDirs[0]));
	::memcpy(&m_torsoVariantDirs[0], str, sizeof(m_torsoVariantDirs[0]));
	str = p_parser.ReadStringWithMaxLength(sizeof(m_torsoVariantDirs[1]));
	::memcpy(&m_torsoVariantDirs[1], str, sizeof(m_torsoVariantDirs[1]));

	for (LegoS32 i = 0; i < m_torsoCount; i++) {
		str = p_parser.ReadStringWithMaxLength(sizeof(m_torsoNames[i]));
		::memcpy(m_torsoNames[i], str, sizeof(m_torsoNames[i]));
		m_torsoVariants[i] = p_parser.ReadInteger();
		m_torsoUnlockFlags[i] = p_parser.ReadInteger();
	}

	p_parser.ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00498c90
void DriverPartCatalog::ReadLegs(GolFileParser& p_parser)
{
	const LegoChar* str;

	m_legCount = ReadBracketedCount(p_parser);
	if (m_legCount > static_cast<LegoS32>(sizeOfArray(m_legNames))) {
		GOL_FATALERROR_MESSAGE("Too many legs!");
	}

	p_parser.ReadLeftCurly();
	str = p_parser.ReadStringWithMaxLength(sizeof(m_legVariantDirs[0]));
	::strncpy(m_legVariantDirs[0], str, sizeof(m_legVariantDirs[0]));
	str = p_parser.ReadStringWithMaxLength(sizeof(m_legVariantDirs[1]));
	::strncpy(m_legVariantDirs[1], str, sizeof(m_legVariantDirs[1]));

	for (LegoS32 i = 0; i < m_legCount; i++) {
		str = p_parser.ReadStringWithMaxLength(sizeof(m_legNames[i]));
		::strncpy(m_legNames[i], str, sizeof(m_legNames[i]));
		m_legVariants[i] = p_parser.ReadInteger();
		m_legUnlockFlags[i] = p_parser.ReadInteger();
	}

	p_parser.ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00498d70
void DriverPartCatalog::ReadHeadHats(GolFileParser& p_parser)
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
void DriverPartCatalog::ReadBodyModelNames(GolFileParser& p_parser)
{
	const LegoChar* str;

	m_bodyModelNameCount = ReadBracketedCount(p_parser);
	p_parser.ReadLeftCurly();

	for (LegoS32 i = 0; i < m_bodyModelNameCount; i++) {
		str = p_parser.ReadStringWithMaxLength(sizeof(m_bodyModelNames[i]));
		::strncpy(m_bodyModelNames[i], str, sizeof(m_bodyModelNames[i]));
	}

	p_parser.ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00498e40
void DriverPartCatalog::ReadPartSlotNames(GolFileParser& p_parser)
{
	const LegoChar* str;

	LegoS32 count = ReadBracketedCount(p_parser);
	p_parser.ReadLeftCurly();

	for (LegoS32 i = 0; i < count; i++) {
		str = p_parser.ReadStringWithMaxLength(sizeof(m_partSlotNames[i]));
		::strncpy(m_partSlotNames[i], str, sizeof(m_partSlotNames[i]));
	}

	p_parser.ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00498e90
void DriverPartCatalog::ReadFile(GolFileParser& p_parser)
{
	GolFileParser::ParserTokenType token;

	while ((token = p_parser.GetNextToken()) != 0) {
		switch (token) {
		case PcbTxtParser::e_modelFiles:
			ReadModelFileNames(p_parser);
			break;
		case PcbTxtParser::e_modelDirectories:
			ReadModelDirectories(p_parser);
			break;
		case PcbTxtParser::e_hats:
			ReadHats(p_parser);
			break;
		case PcbTxtParser::e_faces:
			ReadFaces(p_parser);
			break;
		case PcbTxtParser::e_torsos:
			ReadTorsos(p_parser);
			break;
		case PcbTxtParser::e_legs:
			ReadLegs(p_parser);
			break;
		case PcbTxtParser::e_headHats:
			ReadHeadHats(p_parser);
			break;
		case PcbTxtParser::e_bodyModels:
			ReadBodyModelNames(p_parser);
			break;
		case PcbTxtParser::e_partSlots:
			ReadPartSlotNames(p_parser);
			break;
		default:
			p_parser.HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x00498f50
void DriverPartCatalog::CopyHatName(LegoS32 p_index, LegoChar* p_buffer) const
{
	::strncpy(p_buffer, m_hatNames[p_index], sizeof(m_hatNames[p_index]));
}

// FUNCTION: LEGORACERS 0x00498f70
void DriverPartCatalog::CopyDefaultFaceName(LegoS32 p_index, LegoChar* p_directory, LegoChar* p_name) const
{
	::strncpy(p_directory, m_faceDirectory, sizeof(m_faceDirectory));
	::strcpy(p_name, m_faceNames[p_index]);
	::strncat(p_name, m_faceExpressions[0], sizeOfArray(m_faceExpressions) - 1);
}

// FUNCTION: LEGORACERS 0x00498fd0
void DriverPartCatalog::CopyTorsoName(LegoS32 p_index, LegoChar* p_directory, LegoChar* p_name) const
{
	::strncpy(
		p_directory,
		m_torsoVariantDirs[m_torsoVariants[p_index]],
		sizeof(m_torsoVariantDirs[m_torsoVariants[p_index]])
	);
	::strncpy(p_name, m_torsoNames[p_index], sizeof(m_torsoNames[p_index]));
}

// FUNCTION: LEGORACERS 0x00499020
void DriverPartCatalog::CopyLegName(LegoS32 p_index, LegoChar* p_directory, LegoChar* p_name) const
{
	::strncpy(p_directory, m_legVariantDirs[m_legVariants[p_index]], sizeof(m_legVariantDirs[m_legVariants[p_index]]));
	::strncpy(p_name, m_legNames[p_index], sizeof(m_legNames[p_index]));
}

// FUNCTION: LEGORACERS 0x00499070
void DriverPartCatalog::CopyBodyModelName(LegoS32 p_index, LegoChar* p_buffer) const
{
	::strncpy(p_buffer, m_bodyModelNames[p_index], sizeof(m_bodyModelNames[p_index]));
}

// FUNCTION: LEGORACERS 0x00499090
void DriverPartCatalog::CopyHeadHatName(LegoS32 p_index, LegoChar* p_buffer) const
{
	::strncpy(p_buffer, m_headHatNames[p_index], sizeof(m_headHatNames[p_index]));
}

// FUNCTION: LEGORACERS 0x004990b0
void DriverPartCatalog::BuildFaceExpressionName(
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
