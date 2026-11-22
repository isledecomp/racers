#include "cmbmodelparttrackdata.h"

#include "golerror.h"
#include "golfileparser.h"

DECOMP_SIZE_ASSERT(CmbModelPartTrackData, 0x18)

// FUNCTION: GOLDP 0x100241b0
// FUNCTION: LEGORACERS 0x0040e490
CmbModelPartTrackData::CmbModelPartTrackData()
{
	m_vertexCount = 0;
	m_vertices = NULL;
	m_frameCount = 0;
	m_frames = NULL;
	m_keyCount = 0;
	m_keys = NULL;
}

// FUNCTION: GOLDP 0x10024710 FOLDED
// FUNCTION: LEGORACERS 0x0040e4b0
CmbModelPartTrackData::~CmbModelPartTrackData()
{
	Clear();
}

// FUNCTION: GOLDP 0x100241d0
// FUNCTION: LEGORACERS 0x0040e4c0
void CmbModelPartTrackData::Parse(GolFileParser& p_parser)
{
	p_parser.ReadLeftCurly();
	LegoU32 i;
	LegoU32 count;
	GolFileParser::ParserTokenType token;
	while ((token = p_parser.GetNextToken()) != GolFileParser::e_rightCurly) {
		switch (token) {
		case CmbModelPartTrackData::e_vertices:
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
		case CmbModelPartTrackData::e_frames:
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
		case CmbModelPartTrackData::e_keys:
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

// FUNCTION: GOLDP 0x10024380
// FUNCTION: LEGORACERS 0x0040e670
LegoBool32 CmbModelPartTrackData::InterpolatePosition(
	GolVec3* p_dest,
	const CmbModelPartTrack& p_track,
	LegoFloat p_time,
	LegoS32 p_frameCount
) const
{
	LegoU16 keyCount = p_track.m_positionKeyCount;
	if (keyCount == 0) {
		return FALSE;
	}

	if (keyCount == 1) {
		*p_dest = m_vertices[p_track.m_positionFrameIndex];
		return TRUE;
	}

	LegoU32 i;
	for (i = 0; i < keyCount; i++) {
		if (m_keys[p_track.m_positionKeyIndex + i] > p_time) {
			break;
		}
	}

	const GolVec3* from;
	const GolVec3* to;
	LegoFloat elapsed;
	LegoS32 duration;
	if (i == 0) {
		LegoS32 firstKey = m_keys[p_track.m_positionKeyIndex];
		LegoS32 lastKey = m_keys[p_track.m_positionKeyIndex + keyCount - 1];
		duration = firstKey - lastKey + p_frameCount;
		elapsed = static_cast<LegoFloat>(duration - firstKey);
		elapsed += p_time;
		from = &m_vertices[p_track.m_positionFrameIndex + keyCount - 1];
		to = &m_vertices[p_track.m_positionFrameIndex];
	}
	else if (i == keyCount) {
		LegoU32 lastIndex = p_track.m_positionKeyIndex + keyCount - 1;
		duration = m_keys[p_track.m_positionKeyIndex] - m_keys[lastIndex] + p_frameCount;
		elapsed = p_time - static_cast<LegoFloat>(m_keys[lastIndex]);
		from = &m_vertices[p_track.m_positionFrameIndex + keyCount - 1];
		to = &m_vertices[p_track.m_positionFrameIndex];
	}
	else {
		LegoU32 keyIndex = p_track.m_positionKeyIndex + i;
		LegoS32 key = m_keys[keyIndex];
		LegoS32 previousKey = m_keys[keyIndex - 1];
		duration = key - previousKey;
		elapsed = p_time - (static_cast<LegoFloat>(previousKey));
		to = &m_vertices[p_track.m_positionFrameIndex + i];
		from = to - 1;
	}
	p_frameCount = duration;

	LegoFloat amount;
	if (p_frameCount == 0) {
		amount = 0.0f;
	}
	else {
		LegoFloat divisor = static_cast<LegoFloat>(p_frameCount);
		amount = elapsed / divisor;
	}
	p_dest->m_x = to->m_x - from->m_x;
	p_dest->m_y = to->m_y - from->m_y;
	p_dest->m_z = to->m_z - from->m_z;
	GolVec3 scaled;
	scaled.m_x = p_dest->m_x * amount;
	scaled.m_y = p_dest->m_y;
	scaled.m_y *= amount;
	scaled.m_z = p_dest->m_z * amount;
	p_dest->m_x = scaled.m_x + from->m_x;
	p_dest->m_y = scaled.m_y + from->m_y;
	p_dest->m_z = scaled.m_z + from->m_z;
	return TRUE;
}

// FUNCTION: GOLDP 0x10024540
// FUNCTION: LEGORACERS 0x0040e830
LegoBool32 CmbModelPartTrackData::InterpolateRotation(
	GolQuat* p_dest,
	const CmbModelPartTrack& p_track,
	LegoFloat p_time,
	LegoS32 p_frameCount
) const
{
	LegoU16 keyCount = p_track.m_rotationKeyCount;
	if (keyCount == 0) {
		return FALSE;
	}

	if (keyCount == 1) {
		GetRotationFrame(p_track.m_rotationFrameIndex, p_dest);
		return TRUE;
	}

	LegoU32 i;
	for (i = 0; i < keyCount; i++) {
		if (m_keys[p_track.m_rotationKeyIndex + i] > p_time) {
			break;
		}
	}

	GolQuat from;
	GolQuat to;
	LegoFloat elapsed;
	LegoS32 duration;
	if (i == 0) {
		LegoS32 firstKey = m_keys[p_track.m_rotationKeyIndex];
		LegoS32 lastKey = m_keys[p_track.m_rotationKeyIndex + keyCount - 1];
		duration = firstKey - lastKey + p_frameCount;
		elapsed = static_cast<LegoFloat>(duration - firstKey);
		elapsed += p_time;
		GetRotationFrame(p_track.m_rotationFrameIndex + keyCount - 1, &from);
		GetRotationFrame(p_track.m_rotationFrameIndex, &to);
	}
	else if (i == keyCount) {
		LegoU32 lastIndex = p_track.m_rotationKeyIndex + keyCount - 1;
		duration = m_keys[p_track.m_rotationKeyIndex] - m_keys[lastIndex] + p_frameCount;
		elapsed = p_time - static_cast<LegoFloat>(m_keys[lastIndex]);
		GetRotationFrame(p_track.m_rotationFrameIndex + keyCount - 1, &from);
		GetRotationFrame(p_track.m_rotationFrameIndex, &to);
	}
	else {
		LegoU32 keyIndex = p_track.m_rotationKeyIndex + i;
		LegoS32 key = m_keys[keyIndex];
		LegoS32 previousKey = m_keys[keyIndex - 1];
		duration = key - previousKey;
		elapsed = p_time - static_cast<LegoFloat>(previousKey);
		GetRotationFrame(p_track.m_rotationFrameIndex + i - 1, &from);
		GetRotationFrame(p_track.m_rotationFrameIndex + i, &to);
	}
	p_frameCount = duration;

	LegoFloat amount;
	if (p_frameCount == 0) {
		amount = 0.0f;
	}
	else {
		LegoFloat divisor = static_cast<LegoFloat>(p_frameCount);
		amount = elapsed / divisor;
	}
	GolMath::LerpQuat(from, to, amount, p_dest);
	return TRUE;
}

// FUNCTION: GOLDP 0x10024710 FOLDED
// FUNCTION: LEGORACERS 0x0040e9d0
void CmbModelPartTrackData::Clear()
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

// FUNCTION: LEGORACERS 0x0040ea20
void CmbModelPartTrackData::MirrorY()
{
	LegoU32 i;

	for (i = 0; i < m_vertexCount; i++) {
		m_vertices[i].m_y = -m_vertices[i].m_y;
	}

	for (i = 0; i < m_frameCount; i++) {
		m_frames[i].m_y = -m_frames[i].m_y;
		m_frames[i].m_u = -m_frames[i].m_u;
	}
}

// FUNCTION: LEGORACERS 0x0040ea80
void CmbModelPartTrackData::GetRotationFrame(LegoU32 p_index, GolQuat* p_dest) const
{
	p_dest->m_x = m_frames[p_index].m_x;
	p_dest->m_y = m_frames[p_index].m_y;
	p_dest->m_z = m_frames[p_index].m_z;
	p_dest->m_w = m_frames[p_index].m_u;
}
