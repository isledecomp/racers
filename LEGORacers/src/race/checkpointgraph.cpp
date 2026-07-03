#include "race/checkpointgraph.h"

#include "golbinparser.h"
#include "golerror.h"

DECOMP_SIZE_ASSERT(CheckpointGraph::Entry, 0x24)
DECOMP_SIZE_ASSERT(CheckpointGraph, 0x08)

extern LegoFloat g_minSoundPan;

// FUNCTION: LEGORACERS 0x0041e5e0
CheckpointGraph::Entry::Entry()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0041e5f0
CheckpointGraph::Entry::~Entry()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0041e600
void CheckpointGraph::Entry::Reset()
{
	m_next.m_all = 0xffffffff;
	m_planeNormal.m_x = 0;
	m_planeNormal.m_y = 0;
	m_planeNormal.m_z = 0;
	m_planeDistance = 0;
	m_position.m_x = 0;
	m_position.m_y = 0;
	m_position.m_z = 0;
	m_lapFraction = -1.0f;
}

// FUNCTION: LEGORACERS 0x0041e630
void CheckpointGraph::Entry::Destroy()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0041e640
void CheckpointGraph::Entry::Load(GolFileParser* p_parser, LegoBool32 p_mirror)
{
	p_parser->ReadLeftCurly();

	LegoU32 i;
	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case CpbTxtParser::e_plane:
			m_planeNormal.m_x = p_parser->ReadFloat();
			if (p_mirror) {
				m_planeNormal.m_y = -p_parser->ReadFloat();
			}
			else {
				m_planeNormal.m_y = p_parser->ReadFloat();
			}
			m_planeNormal.m_z = p_parser->ReadFloat();
			m_planeDistance = p_parser->ReadFloat();
			break;
		case CpbTxtParser::e_nextIndices:
			for (i = 0; i < sizeOfArray(m_next.m_items); i++) {
				m_next.m_items[i] = static_cast<LegoU8>(p_parser->ReadInteger());
			}
			break;
		case CpbTxtParser::e_position:
			m_position.m_x = p_parser->ReadFloat();
			if (p_mirror) {
				m_position.m_y = -p_parser->ReadFloat();
			}
			else {
				m_position.m_y = p_parser->ReadFloat();
			}
			m_position.m_z = p_parser->ReadFloat();
			break;
		default:
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}

		token = p_parser->GetNextToken();
	}
}

// FUNCTION: LEGORACERS 0x0041e720
CheckpointGraph::~CheckpointGraph()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0041e730
void CheckpointGraph::Reset()
{
	if (m_entries) {
		delete[] m_entries;
		m_entries = NULL;
	}

	m_count = 0;
}

// FUNCTION: LEGORACERS 0x0041e770
void CheckpointGraph::Load(const LegoChar* p_name, LegoBool32 p_binary, LegoBool32 p_mirror)
{
	if (m_entries) {
		Reset();
	}

	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".cpb");
	}
	else {
		parser = new CpbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_name);
	parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(CpbTxtParser::e_checkpoint));
	m_count = parser->ReadBracketedCountAndLeftCurly();
	if (m_count) {
		if (m_count > 0xfe) {
			GOL_FATALERROR_MESSAGE("Too many CheckPoints");
		}

		m_entries = new Entry[m_count];
	}

	for (LegoU32 i = 0; i < m_count; i++) {
		parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(CpbTxtParser::e_checkpoint));
		m_entries[i].Load(parser, p_mirror);
	}

	parser->ReadRightCurly();
	parser->Dispose();
	if (parser != NULL) {
		delete parser;
	}

	ComputeLapFractions();
}

// FUNCTION: LEGORACERS 0x0041e940 FOLDED
CheckpointGraph::Entry* CheckpointGraph::GetCheckpoint(LegoU32 p_index)
{
	return &m_entries[p_index];
}

// STUB: LEGORACERS 0x0041e950
void CheckpointGraph::ComputeLapFractions()
{
	LegoS32 pathCount = static_cast<LegoS32>(CountLapCheckpoints());
	Entry* entry = m_entries;
	LegoFloat step = 1.0f / pathCount;
	LegoFloat progress = 0.0f;

	do {
		entry->m_lapFraction = progress;
		progress += step;
		entry = &m_entries[entry->m_next.m_items[0]];
	} while (entry != m_entries && progress < 1.0f);

	LegoU32 entryIndex = 0;
	do {
		entry = &m_entries[entryIndex];
		for (LegoU32 i = 1; i < sizeOfArray(entry->m_next.m_items); i++) {
			LegoU8 next = entry->m_next.m_items[i];
			if (next != 0xff) {
				LegoU32 distance;
				LegoU32 targetIndex = FindNextFractionedCheckpoint(next, &distance);
				Entry* target = &m_entries[targetIndex];
				LegoFloat step = (target->m_lapFraction - entry->m_lapFraction) / (distance + 1);
				Entry* cursor = &m_entries[entry->m_next.m_items[i]];
				LegoFloat progress = entry->m_lapFraction + step;

				do {
					cursor->m_lapFraction = progress;
					progress += step;
					cursor = &m_entries[cursor->m_next.m_items[0]];
				} while (cursor != target);
			}
		}

		entryIndex = entry->m_next.m_items[0];
	} while (entryIndex != 0);
}

// FUNCTION: LEGORACERS 0x0041ea60
LegoU32 CheckpointGraph::CountLapCheckpoints()
{
	LegoU32 result = 0;
	Entry* first = m_entries;
	Entry* entry = first;

	do {
		result++;
		entry = &m_entries[entry->m_next.m_items[0]];
	} while (entry != first && result < m_count);

	return result;
}

// FUNCTION: LEGORACERS 0x0041ea90
LegoU32 CheckpointGraph::FindNextFractionedCheckpoint(LegoU32 p_startIndex, LegoU32* p_stepCount)
{
	*p_stepCount = 0;

	Entry* entry = &m_entries[p_startIndex];
	while (entry->m_lapFraction == g_minSoundPan) {
		if (*p_stepCount >= m_count) {
			break;
		}

		LegoU32 count = *p_stepCount + 1;
		p_startIndex = entry->m_next.m_items[0];
		*p_stepCount = count;
		entry = &m_entries[p_startIndex];
	}

	return p_startIndex;
}

// FUNCTION: LEGORACERS 0x0045c3b0 FOLDED
CheckpointGraph::CheckpointGraph()
{
	m_entries = NULL;
	m_count = 0;
}
