#include "cmbmodelpartdata0x18.h"

#include "golerror.h"
#include "golfileparser.h"

DECOMP_SIZE_ASSERT(CmbModelPartData0x18, 0x18)

// FUNCTION: GOLDP 0x100241b0
// FUNCTION: LEGORACERS 0x0040e490
CmbModelPartData0x18::CmbModelPartData0x18()
{
	m_vertexCount = 0;
	m_vertices = NULL;
	m_frameCount = 0;
	m_frames = NULL;
	m_keyCount = 0;
	m_keys = NULL;
}

// FUNCTION: LEGORACERS 0x0040e4b0
CmbModelPartData0x18::~CmbModelPartData0x18()
{
	Clear();
}

// FUNCTION: GOLDP 0x100241d0
// FUNCTION: LEGORACERS 0x0040e4c0
void CmbModelPartData0x18::FUN_100241d0(GolFileParser& p_parser)
{
	p_parser.ReadLeftCurly();
	LegoU32 i;
	LegoU32 count;
	GolFileParser::ParserTokenType token;
	while ((token = p_parser.GetNextToken()) != GolFileParser::e_rightCurly) {
		switch (token) {
		case GolFileParser::e_unknown0x28:
			count = p_parser.ReadBracketedCountAndLeftCurly();
			if (count == 0) {
				p_parser.HandleUnexpectedToken(GolFileParser::e_int);
			}
			m_vertices = new GolVec3[count];
			if (m_vertices == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}
			m_vertexCount = count;
			for (i = 0; i < count; i++) {
				m_vertices[i].m_x = p_parser.ReadFloat();
				m_vertices[i].m_y = p_parser.ReadFloat();
				m_vertices[i].m_z = p_parser.ReadFloat();
			}
			p_parser.ReadRightCurly();
			break;
		case GolFileParser::e_unknown0x29:
			count = p_parser.ReadBracketedCountAndLeftCurly();
			if (count == 0) {
				p_parser.HandleUnexpectedToken(GolFileParser::e_int);
			}
			m_frames = new GolVec4[count];
			if (m_frames == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}
			m_frameCount = count;
			for (i = 0; i < count; i++) {
				m_frames[i].m_x = p_parser.ReadFloat();
				m_frames[i].m_y = p_parser.ReadFloat();
				m_frames[i].m_z = p_parser.ReadFloat();
				m_frames[i].m_u = p_parser.ReadFloat();
			}
			p_parser.ReadRightCurly();
			break;
		case GolFileParser::e_unknown0x2a:
			count = p_parser.ReadBracketedCountAndLeftCurly();
			if (count == 0) {
				p_parser.HandleUnexpectedToken(GolFileParser::e_int);
			}
			m_keys = new LegoU16[count];
			if (m_keys == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}
			m_keyCount = count;
			for (i = 0; i < count; i++) {
				m_keys[i] = p_parser.ReadInteger();
			}
			p_parser.ReadRightCurly();
			break;
		default:
			p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
		}
	}
}

// FUNCTION: GOLDP 0x10024710
// FUNCTION: LEGORACERS 0x0040e9d0
void CmbModelPartData0x18::Clear()
{
	if (m_vertices != NULL) {
		delete[] m_vertices;
		m_vertices = NULL;
	}

	if (m_frames != NULL) {
		delete[] m_frames;
		m_frames = NULL;
	}

	if (m_keys != NULL) {
		delete[] m_keys;
		m_keys = NULL;
	}

	m_vertexCount = 0;
	m_frameCount = 0;
	m_keyCount = 0;
}
