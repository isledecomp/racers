#include "race/targetpointlist.h"

#include "golbinparser.h"
#include "golerror.h"
#include "race/tgbtargetpointlist.h"

#include <float.h>

DECOMP_SIZE_ASSERT(TargetPointList::Entry, 0x14)
DECOMP_SIZE_ASSERT(TgbTargetPointList, 0x08)

// FUNCTION: LEGORACERS 0x0045c340
TargetPointList::Entry::Entry()
{
	m_position.m_x = 0.0f;
	m_position.m_y = 0.0f;
	m_position.m_z = 0.0f;
	m_index = -1;
	m_flags = 0;
}

// FUNCTION: LEGORACERS 0x0045c360
TargetPointList::Entry::~Entry()
{
	m_index = -1;
	m_position.m_x = 0.0f;
	m_position.m_y = 0.0f;
	m_position.m_z = 0.0f;
	m_flags = 0;
}

// FUNCTION: LEGORACERS 0x0045c380
void TargetPointList::Entry::Set(GolVec3* p_position, LegoS32 p_index)
{
	m_position.m_x = p_position->m_x;
	m_position.m_y = p_position->m_y;
	m_position.m_z = p_position->m_z;
	m_index = p_index;
	m_flags |= 3;
}

// FUNCTION: LEGORACERS 0x0045c3b0 FOLDED
TgbTargetPointList::TgbTargetPointList()
{
	m_entries = NULL;
	m_count = 0;
}

// FUNCTION: LEGORACERS 0x0045c3c0
TgbTargetPointList::~TgbTargetPointList()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0045c3d0
void TgbTargetPointList::Load(const LegoChar* p_name, LegoBool32 p_binary, LegoBool32 p_mirror)
{
	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".tgb");
	}
	else {
		parser = new TgbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_name);
	parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(TgbTxtParser::e_target));
	m_count = parser->ReadBracketedCountAndLeftCurly();

	if (!m_count) {
		parser->Dispose();
		if (parser != NULL) {
			delete parser;
		}

		return;
	}

	m_entries = new TargetPointList::Entry[m_count];
	if (m_entries == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_count; i++) {
		parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(TgbTxtParser::e_target));
		parser->ReadLeftCurly();

		GolVec3 position;
		position.m_x = 0.0f;
		position.m_y = 0.0f;
		position.m_z = 0.0f;
		LegoS32 index = -1;

		GolFileParser::ParserTokenType token;
		while ((token = parser->GetNextToken()) != GolFileParser::e_rightCurly) {
			switch (token) {
			case TgbTxtParser::e_position:
				position.m_x = parser->ReadFloat();
				position.m_y = parser->ReadFloat();
				position.m_z = parser->ReadFloat();
				if (p_mirror) {
					position.m_y = -position.m_y;
				}
				break;
			case TgbTxtParser::e_index:
				index = parser->ReadInteger();
				break;
			default:
				parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}

		m_entries[i].Set(&position, index);
	}

	parser->ReadRightCurly();
	parser->Dispose();
	if (parser != NULL) {
		delete parser;
	}
}

// FUNCTION: LEGORACERS 0x0045c620
void TgbTargetPointList::Reset()
{
	if (m_entries) {
		delete[] m_entries;
		m_entries = NULL;
	}

	m_count = 0;
}

// FUNCTION: LEGORACERS 0x0045c660
LegoU32 TargetPointList::DisableTargetPoints(undefined4 p_index)
{
	LegoU32 i = 0;
	if (static_cast<LegoU32>(m_count) > 0) {
		Entry* entry = m_entries;
		while (i < static_cast<LegoU32>(m_count)) {
			if (entry->m_index == p_index) {
				if (entry->m_flags & TargetPointList::Entry::c_flagEnabled) {
					entry->m_flags &= ~TargetPointList::Entry::c_flagEnabled;
				}
			}

			i++;
			entry++;
		}
	}

	return m_count;
}

// FUNCTION: LEGORACERS 0x0045c6a0
TargetPointList::Entry* TargetPointList::FindTargetInCone(
	GolVec3* p_position,
	GolVec3* p_direction,
	LegoFloat p_minDistanceSquared,
	LegoFloat p_maxDistanceSquared,
	LegoFloat p_coneCosine
)
{
	LegoFloat nearestDistanceSquared = FLT_MAX;
	LegoS32 resultIndex = -1;

	for (LegoS32 i = 0; i < m_count; i++) {
		Entry& entry = m_entries[i];

		if (entry.m_flags & Entry::c_flagEnabled) {
			GolVec3 position = entry.m_position;
			LegoFloat deltaX = position.m_x - p_position->m_x;
			GolVec2 deltaYZ;
			deltaYZ.m_x = position.m_y - p_position->m_y;
			deltaYZ.m_y = position.m_z - p_position->m_z;
			LegoFloat distanceSquared = deltaYZ.m_y * deltaYZ.m_y + deltaYZ.m_x * deltaYZ.m_x + deltaX * deltaX;

			if (distanceSquared >= p_minDistanceSquared && distanceSquared <= p_maxDistanceSquared) {
				GolVec3 delta;
				delta.m_x = deltaX;
				delta.m_y = deltaYZ.m_x;
				delta.m_z = deltaYZ.m_y;
				GolMath::NormalizeVector3(delta, &delta);

				LegoFloat dotProduct = p_direction->m_z;
				dotProduct *= delta.m_z;
				LegoFloat dotProductY = p_direction->m_y;
				dotProduct += dotProductY * delta.m_y;
				dotProduct += delta.m_x * p_direction->m_x;
				if (dotProduct >= p_coneCosine && distanceSquared < nearestDistanceSquared) {
					resultIndex = i;
					nearestDistanceSquared = distanceSquared;
				}
			}
		}
	}

	if (resultIndex < 0) {
		return NULL;
	}

	return &m_entries[resultIndex];
}
