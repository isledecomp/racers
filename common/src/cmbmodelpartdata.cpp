#include "cmbmodelpartdata.h"

#include "golfileparser.h"

#include <float.h>

DECOMP_SIZE_ASSERT(CmbModelPartData, 0x28)

// FUNCTION: GOLDP 0x10018640
// FUNCTION: LEGORACERS 0x00401000
CmbModelPartData::CmbModelPartData()
{
	m_frameCount = 0;
	m_loopFrameCount = 0;
	m_trackIndex = 0;
	m_msPerFrame = 0.0f;
	m_velocity.m_x = 0.0f;
	m_velocity.m_y = 0.0f;
	m_velocity.m_z = 0.0f;
	m_bounds.m_x = 0.0f;
	m_bounds.m_y = 0.0f;
	m_bounds.m_z = 0.0f;
	m_bounds.m_u = FLT_MAX / 2.0f;
}

// FUNCTION: GOLDP 0x10018670
// FUNCTION: LEGORACERS 0x00401030
void CmbModelPartData::Parse(GolFileParser& p_parser)
{
	p_parser.ReadLeftCurly();
	GolFileParser::ParserTokenType token;

	while ((token = p_parser.GetNextToken()) != GolFileParser::e_rightCurly) {
		switch (token) {
		case CmbModelPartData::e_track:
			m_trackIndex = p_parser.ReadInteger();
			break;
		case CmbModelPartData::e_frames:
			if (p_parser.GetNextToken() != GolFileParser::e_int) {
				p_parser.HandleUnexpectedToken(GolFileParser::e_int);
			}
			m_frameCount = p_parser.GetLastInt();
			break;
		case CmbModelPartData::e_loopFrames:
			if (p_parser.GetNextToken() != GolFileParser::e_int) {
				p_parser.HandleUnexpectedToken(GolFileParser::e_int);
			}
			m_loopFrameCount = p_parser.GetLastInt();
			break;
		case CmbModelPartData::e_frameDuration:
			m_msPerFrame = static_cast<LegoFloat>(p_parser.ReadInteger()) / 1000.0f;
			break;
		case CmbModelPartData::e_velocity:
			m_velocity.m_x = p_parser.ReadFloat();
			m_velocity.m_y = p_parser.ReadFloat();
			m_velocity.m_z = p_parser.ReadFloat();
			break;
		case CmbModelPartData::e_bounds:
			m_bounds.m_x = p_parser.ReadFloat();
			m_bounds.m_y = p_parser.ReadFloat();
			m_bounds.m_z = p_parser.ReadFloat();
			m_bounds.m_u = p_parser.ReadFloat();
			break;
		default:
			p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}
	}
}

// FUNCTION: GOLDP 0x10018790
// FUNCTION: LEGORACERS 0x00401150
LegoFloat CmbModelPartData::WrapTime(LegoFloat p_time) const
{
	LegoFloat frameCount = static_cast<LegoFloat>(m_loopFrameCount);
	if (p_time >= frameCount) {
		LegoFloat wrapCount = static_cast<LegoFloat>(static_cast<LegoS32>(p_time / frameCount));

		return p_time - frameCount * wrapCount;
	}

	return p_time;
}
