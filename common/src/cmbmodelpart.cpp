#include "cmbmodelpart.h"

#include "cmbmodelpartdata.h"
#include "golbinparser.h"
#include "golerror.h"
#include "golname.h"

DECOMP_SIZE_ASSERT(CmbModelPart, 0x34)
DECOMP_SIZE_ASSERT(CmbModelPart::AdbTxtParser, 0x1fc)
DECOMP_SIZE_ASSERT(CmbModelPartTrack, 0x14)

// FUNCTION: GOLDP 0x100187e0
// FUNCTION: LEGORACERS 0x004011a0
CmbModelPart::CmbModelPart()
{
	m_tracks = NULL;
	m_trackCount = 0;
	m_partData = NULL;
	m_partCount = 0;
}

// FUNCTION: GOLDP 0x10018840
// FUNCTION: LEGORACERS 0x00401200
CmbModelPart::~CmbModelPart()
{
	Clear();
}

// FUNCTION: GOLDP 0x100188e0
// FUNCTION: LEGORACERS 0x00401260
void CmbModelPart::Load(const LegoChar* p_name, LegoBool32 p_binary)
{
	if (m_partData) {
		Clear();
	}

	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".adb");
	}
	else {
		parser = new AdbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_name);

	GolFileParser::ParserTokenType token;
	while ((token = parser->GetNextToken()) != GolFileParser::e_syntaxerror) {
		switch (token) {
		case CmbModelPart::e_data:
			m_data.Parse(*parser);
			break;
		case CmbModelPart::e_tracks:
			ParseTracks(*parser);
			break;
		case CmbModelPart::e_parts:
			ParseParts(*parser);
			break;
		default:
			parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}
	}

	parser->Dispose();
	if (parser != NULL) {
		delete parser;
	}
}

// FUNCTION: GOLDP 0x10018a30
// FUNCTION: LEGORACERS 0x004013b0
void CmbModelPart::Clear()
{
	m_data.Clear();

	if (m_tracks != NULL) {
		delete[] m_tracks;
		m_tracks = NULL;
	}

	if (m_partData != NULL) {
		delete[] m_partData;
		m_partData = NULL;
	}

	GolNameTable::Clear();
	m_trackCount = 0;
	m_partCount = 0;
}

// FUNCTION: GOLDP 0x10018a80
// FUNCTION: LEGORACERS 0x00401400
void CmbModelPart::ParseTracks(GolFileParser& p_parser)
{
	m_trackCount = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_trackCount == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}

	m_tracks = new CmbModelPartTrack[m_trackCount];
	if (m_tracks == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoU32 i;
	for (i = 0; i < m_trackCount; i++) {
		m_tracks[i].m_rotationFrameIndex = p_parser.ReadInteger();
		m_tracks[i].m_rotationKeyIndex = p_parser.ReadInteger();
		m_tracks[i].m_rotationKeyCount = p_parser.ReadInteger();
		m_tracks[i].m_positionFrameIndex = p_parser.ReadInteger();
		m_tracks[i].m_positionKeyIndex = p_parser.ReadInteger();
		m_tracks[i].m_positionKeyCount = p_parser.ReadInteger();
	}

	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x10018b40
// FUNCTION: LEGORACERS 0x004014c0
void CmbModelPart::ParseParts(GolFileParser& p_parser)
{
	m_partCount = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_partCount == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}

	m_partData = new CmbModelPartData[m_partCount];
	if (m_partData == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	GolNameTable::Allocate(m_partCount);

	LegoU32 i;
	for (i = 0; i < m_partCount; i++) {
		if (p_parser.GetNextToken() != CmbModelPart::e_parts) {
			p_parser.HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, p_parser.ReadString(), sizeOfArray(name));
		AddName(name, &m_partData[i]);
		m_partData[i].Parse(p_parser);
	}

	p_parser.ReadRightCurly();
}

// STUB: LEGORACERS 0x004015e0
void CmbModelPart::MirrorY()
{
	for (LegoU32 i = 0; i < m_partCount; i++) {
		GolVec4 bounds = m_partData[i].m_bounds;
		bounds.m_y = -bounds.m_y;
		m_partData[i].m_bounds = bounds;

		GolVec3 position = m_partData[i].m_velocity;
		position.m_y = -position.m_y;
		m_partData[i].m_velocity = position;
	}

	m_data.MirrorY();
}
