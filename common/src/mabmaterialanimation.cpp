#include "mabmaterialanimation.h"

#include "golbinparser.h"
#include "golerror.h"
#include "golfileparser.h"
#include "golname.h"
#include "mabmaterialframe.h"
#include "mabmaterialtrack.h"

DECOMP_SIZE_ASSERT(MabMaterialAnimation, 0x14)
DECOMP_SIZE_ASSERT(MabMaterialAnimation::MabTxtParser, 0x1fc)

// FUNCTION: GOLDP 0x10025890
// FUNCTION: LEGORACERS 0x0040fea0
MabMaterialAnimation::MabMaterialAnimation()
{
	m_frames = NULL;
	m_frameCount = 0;
	m_tracks = NULL;
	m_trackCount = 0;
}

// FUNCTION: GOLDP 0x100258b0
// FUNCTION: LEGORACERS 0x0040fec0
MabMaterialAnimation::~MabMaterialAnimation()
{
	Destroy();
}

// FUNCTION: GOLDP 0x100258f0
// FUNCTION: LEGORACERS 0x0040fed0
void MabMaterialAnimation::Load(GolRenderDevice* p_renderer, const LegoChar* p_fileName, LegoBool32 p_binary)
{
	if (m_tracks != NULL) {
		Destroy();
	}

	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".mab");
	}
	else {
		parser = new MabTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_fileName);
	ParseFrames(p_renderer, *parser);
	ParseTracks(*parser);
	parser->Dispose();
	if (parser != NULL) {
		delete parser;
	}
}

// FUNCTION: GOLDP 0x10025a00
// FUNCTION: LEGORACERS 0x0040ffe0
void MabMaterialAnimation::Destroy()
{
	if (m_frames != NULL) {
		delete[] m_frames;
		m_frames = NULL;
	}
	if (m_tracks != NULL) {
		delete[] m_tracks;
		m_tracks = NULL;
	}
	m_frameCount = 0;
	m_trackCount = 0;
}

// FUNCTION: GOLDP 0x10025a40
// FUNCTION: LEGORACERS 0x00410020
void MabMaterialAnimation::ParseFrames(GolRenderDevice* p_renderer, GolFileParser& p_parser)
{
	LegoU32 i;

	if (p_parser.GetNextToken() != MabTxtParser::e_frames) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
	}

	m_frameCount = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_frameCount == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
	}

	m_frames = new MabMaterialFrame[m_frameCount];
	if (m_frames == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (i = 0; i < m_frameCount; i++) {
		GolName name;
		::strncpy(name, p_parser.ReadStringWithMaxLength(sizeOfArray(name)), sizeof(name));
		m_frames[i].Initialize(p_renderer, name, p_parser.ReadInteger());
	}

	if (p_parser.GetNextToken() != GolFileParser::e_rightCurly) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_rightCurly);
	}
}

// FUNCTION: GOLDP 0x10025b60
// FUNCTION: LEGORACERS 0x00410140
void MabMaterialAnimation::ParseTracks(GolFileParser& p_parser)
{
	LegoU32 i;

	if (p_parser.GetNextToken() != MabTxtParser::e_track) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
	}

	m_trackCount = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_trackCount == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
	}

	m_tracks = new MabMaterialTrack[m_trackCount];
	if (m_tracks == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (i = 0; i < m_trackCount; i++) {
		undefined4 param2 = 1;
		undefined4 param1 = 0;
		undefined4 param3 = 1;
		undefined4 param4 = 30;

		if (p_parser.GetNextToken() != MabTxtParser::e_track) {
			p_parser.HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		if (p_parser.GetNextToken() != GolFileParser::e_leftCurly) {
			p_parser.HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		GolFileParser::ParserTokenType token;
		while ((token = p_parser.GetNextToken()) != GolFileParser::e_rightCurly) {
			switch (token) {
			case MabTxtParser::e_frameRange:
				param1 = p_parser.ReadInteger();
				param2 = p_parser.ReadInteger();
				break;
			case MabTxtParser::e_duration:
				param3 = p_parser.ReadInteger();
				break;
			case MabTxtParser::e_frameRate:
				param4 = p_parser.ReadInteger();
				break;
			default:
				p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}

		m_tracks[i].Configure(param1, param2, param3, param4);
	}

	if (p_parser.GetNextToken() != GolFileParser::e_rightCurly) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_rightCurly);
	}
}

// FUNCTION: LEGORACERS 0x00410300
void MabMaterialAnimation::Update(LegoS32 p_elapsedMs)
{
	for (LegoU32 i = 0; i < m_trackCount; i++) {
		if (m_tracks[i].IsAssigned()) {
			m_tracks[i].Update(p_elapsedMs, m_frames, m_frameCount);
		}
	}
}
