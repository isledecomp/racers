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

// FUNCTION: GOLDP 0x10024710 FOLDED
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

// STUB: GOLDP 0x10024380
// STUB: LEGORACERS 0x0040e670
LegoBool32 CmbModelPartData0x18::InterpolatePosition(
	GolVec3* p_dest,
	const CmbModelPartTrack0x14& p_track,
	LegoFloat p_time,
	LegoU16 p_frameCount
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

	const LegoU16* keys = &m_keys[p_track.m_positionKeyIndex];
	LegoU32 keyIndex = 0;
	for (; keyIndex < keyCount; keyIndex++) {
		if (keys[keyIndex] > p_time) {
			break;
		}
	}

	const GolVec3* from;
	const GolVec3* to;
	LegoS32 duration;
	LegoFloat elapsed;
	if (keyIndex == 0) {
		LegoU16 firstKey = keys[0];
		LegoU16 lastKey = keys[keyCount - 1];
		duration = p_frameCount + firstKey - lastKey;
		elapsed = static_cast<LegoFloat>(duration - firstKey) + p_time;
		from = &m_vertices[p_track.m_positionFrameIndex + keyCount - 1];
		to = &m_vertices[p_track.m_positionFrameIndex];
	}
	else if (keyIndex == keyCount) {
		LegoU16 firstKey = keys[0];
		LegoU16 lastKey = keys[keyCount - 1];
		duration = p_frameCount + firstKey - lastKey;
		elapsed = p_time - static_cast<LegoFloat>(lastKey);
		from = &m_vertices[p_track.m_positionFrameIndex + keyCount - 1];
		to = &m_vertices[p_track.m_positionFrameIndex];
	}
	else {
		LegoU16 previousKey = keys[keyIndex - 1];
		duration = keys[keyIndex] - previousKey;
		elapsed = p_time - static_cast<LegoFloat>(previousKey);
		from = &m_vertices[p_track.m_positionFrameIndex + keyIndex - 1];
		to = &m_vertices[p_track.m_positionFrameIndex + keyIndex];
	}

	LegoFloat amount = duration == 0 ? 0.0f : elapsed / static_cast<LegoFloat>(duration);
	p_dest->m_x = to->m_x - from->m_x;
	p_dest->m_y = to->m_y - from->m_y;
	p_dest->m_z = to->m_z - from->m_z;
	p_dest->m_x = from->m_x + p_dest->m_x * amount;
	p_dest->m_y = from->m_y + p_dest->m_y * amount;
	p_dest->m_z = from->m_z + p_dest->m_z * amount;
	return TRUE;
}

// STUB: GOLDP 0x10024540
// STUB: LEGORACERS 0x0040e830
LegoBool32 CmbModelPartData0x18::InterpolateRotation(
	GolQuat* p_dest,
	const CmbModelPartTrack0x14& p_track,
	LegoFloat p_time,
	LegoS32 p_frameCount
) const
{
	LegoU16 keyCount = p_track.m_rotationKeyCount;
	if (keyCount == 0) {
		return FALSE;
	}

	if (keyCount == 1) {
		FUN_0040ea80(p_track.m_rotationFrameIndex, p_dest);
		return TRUE;
	}

	LegoU32 keyIndex = 0;
	const LegoU16* allKeys = m_keys;
	const LegoU16* keys = &allKeys[p_track.m_rotationKeyIndex];
	const LegoU16* cursor = keys;
	for (; keyIndex < keyCount; keyIndex++) {
		if (*cursor > p_time) {
			break;
		}
		cursor++;
	}

	GolQuat from;
	GolQuat to;
	LegoS32 duration;
	LegoFloat elapsed;
	if (keyIndex == 0) {
		LegoU32 keyBase = p_track.m_rotationKeyIndex;
		LegoS32 firstKey = allKeys[keyBase];
		LegoS32 lastKey = allKeys[keyBase + keyCount - 1];
		duration = p_frameCount + firstKey - lastKey;
		elapsed = static_cast<LegoFloat>(duration - firstKey) + p_time;
		FUN_0040ea80(p_track.m_rotationFrameIndex + keyCount - 1, &from);
		FUN_0040ea80(p_track.m_rotationFrameIndex, &to);
	}
	else if (keyIndex == keyCount) {
		LegoU32 keyBase = p_track.m_rotationKeyIndex;
		LegoS32 firstKey = keys[0];
		LegoS32 lastKey = allKeys[keyBase + keyCount - 1];
		duration = p_frameCount + firstKey - lastKey;
		elapsed = p_time - static_cast<LegoFloat>(lastKey);
		FUN_0040ea80(p_track.m_rotationFrameIndex + keyCount - 1, &from);
		FUN_0040ea80(p_track.m_rotationFrameIndex, &to);
	}
	else {
		LegoU32 keyBase = p_track.m_rotationKeyIndex + keyIndex;
		LegoS32 previousKey = allKeys[keyBase - 1];
		duration = allKeys[keyBase] - previousKey;
		elapsed = p_time - static_cast<LegoFloat>(previousKey);
		FUN_0040ea80(p_track.m_rotationFrameIndex + keyIndex - 1, &from);
		FUN_0040ea80(p_track.m_rotationFrameIndex + keyIndex, &to);
	}

	LegoFloat amount = duration == 0 ? 0.0f : elapsed / static_cast<LegoFloat>(duration);
	GolMath::FUN_1002f890(from, to, amount, p_dest);
	return TRUE;
}

// FUNCTION: GOLDP 0x10024710 FOLDED
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

// FUNCTION: LEGORACERS 0x0040ea20
void CmbModelPartData0x18::FUN_0040ea20()
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
void CmbModelPartData0x18::FUN_0040ea80(LegoU32 p_index, GolQuat* p_dest) const
{
	p_dest->m_x = m_frames[p_index].m_x;
	p_dest->m_y = m_frames[p_index].m_y;
	p_dest->m_z = m_frames[p_index].m_z;
	p_dest->m_w = m_frames[p_index].m_u;
}
