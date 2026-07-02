#include "race/racer/racerouterecord.h"

#include "golbinparser.h"
#include "golerror.h"

#include <stdlib.h>

DECOMP_SIZE_ASSERT(RaceRouteRecord, 0x48)
DECOMP_SIZE_ASSERT(RaceRouteRecord::RrbTxtParser, 0x1fc)

// FUNCTION: LEGORACERS 0x004a4e10
RaceRouteRecord::RaceRouteRecord()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a4e20
RaceRouteRecord::~RaceRouteRecord()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004a4e30
void RaceRouteRecord::Load(const LegoChar* p_fileName, LegoBool32 p_binary, LegoBool32 p_mirror)
{
	if (m_pathPoints) {
		Destroy();
	}

	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (!parser) {
			GolFatalError(c_golErrorOutOfMemory, NULL, 0);
		}
		parser->SetSuffix(".rrb");
	}
	else {
		parser = new RrbTxtParser;
		if (!parser) {
			GolFatalError(c_golErrorOutOfMemory, NULL, 0);
		}
	}

	parser->OpenFileForRead(p_fileName);

	GolFileParser::ParserTokenType token = parser->GetNextToken();
	while (token != GolFileParser::e_syntaxerror) {
		switch (token) {
		case RrbTxtParser::e_pathPoints:
			ParsePathPoints(parser, p_mirror);
			break;
		case RrbTxtParser::e_startRotation:
			m_startRotation.m_x = parser->ReadFloat();
			m_startRotation.m_y = parser->ReadFloat();
			m_startRotation.m_z = parser->ReadFloat();
			m_startRotation.m_w = parser->ReadFloat();
			if (p_mirror) {
				m_startRotation.m_y = -m_startRotation.m_y;
				m_startRotation.m_w = -m_startRotation.m_w;
			}
			break;
		case RrbTxtParser::e_startPosition:
			m_startPosition.m_x = parser->ReadFloat();
			m_startPosition.m_y = parser->ReadFloat();
			m_startPosition.m_z = parser->ReadFloat();
			if (p_mirror) {
				m_startPosition.m_y = -m_startPosition.m_y;
			}
			break;
		case RrbTxtParser::e_loopPosition:
			m_loopPosition.m_x = parser->ReadFloat();
			m_loopPosition.m_y = parser->ReadFloat();
			m_loopPosition.m_z = parser->ReadFloat();
			if (p_mirror) {
				m_loopPosition.m_y = -m_loopPosition.m_y;
			}
			break;
		case RrbTxtParser::e_loopRotation:
			m_loopRotation.m_x = parser->ReadFloat();
			m_loopRotation.m_y = parser->ReadFloat();
			m_loopRotation.m_z = parser->ReadFloat();
			m_loopRotation.m_w = parser->ReadFloat();
			if (p_mirror) {
				m_loopRotation.m_y = -m_loopRotation.m_y;
				m_loopRotation.m_w = -m_loopRotation.m_w;
			}
			break;
		case RrbTxtParser::e_loopTime:
			m_loopTime = parser->ReadInteger();
			break;
		case RrbTxtParser::e_loopPointIndex:
			m_loopPointIndex = parser->ReadInteger();
			break;
		default:
			break;
		}

		token = parser->GetNextToken();
	}

	if (static_cast<LegoU32>(m_loopPointIndex) >= static_cast<LegoU32>(m_pathPointCount)) {
		parser->HandleUnexpectedToken(GolFileParser::e_invalidValue);
	}

	parser->Dispose();
	delete parser;
}

// FUNCTION: LEGORACERS 0x004a50a0
void RaceRouteRecord::Destroy()
{
	if (m_pathPoints) {
		delete[] m_pathPoints;
	}

	Reset();
}

// FUNCTION: LEGORACERS 0x004a50c0
void RaceRouteRecord::Reset()
{
	m_pathPointCount = 0;
	m_pathPoints = NULL;
	m_startPosition.m_x = 0;
	m_startPosition.m_y = 0;
	m_startPosition.m_z = 0;
	m_startRotation.m_x = 0;
	m_startRotation.m_y = 0;
	m_startRotation.m_z = 0;
	m_startRotation.m_w = 1.0f;
	m_loopPosition.m_x = 0;
	m_loopPosition.m_y = 0;
	m_loopPosition.m_z = 0;
	m_loopRotation.m_x = 0;
	m_loopRotation.m_y = 0;
	m_loopRotation.m_z = 0;
	m_loopRotation.m_w = 1.0f;
	m_loopTime = 0;
	m_loopPointIndex = 0;
}

// FUNCTION: LEGORACERS 0x004a5100
void RaceRouteRecord::ParsePathPoints(GolFileParser* p_parser, LegoBool32 p_mirror)
{
	m_pathPointCount = p_parser->ReadBracketedCountAndLeftCurly();
	m_pathPoints = new RaceRouteRecord::PathPoint[m_pathPointCount];
	if (!m_pathPoints) {
		GolFatalError(c_golErrorOutOfMemory, NULL, 0);
	}

	for (LegoU32 i = 0; i < static_cast<LegoU32>(m_pathPointCount); i++) {
		m_pathPoints[i].Load(p_parser, p_mirror);
	}

	p_parser->ReadRightCurly();
}
