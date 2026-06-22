#include "race/racesessionfield0x27f4.h"

#include "golbinparser.h"
#include "golerror.h"

DECOMP_SIZE_ASSERT(RaceSessionField0x27f4::Entry, 0x24)
DECOMP_SIZE_ASSERT(RaceSessionField0x27f4, 0x08)

extern LegoFloat g_minSoundPan;

// FUNCTION: LEGORACERS 0x0041e5e0
RaceSessionField0x27f4::Entry::Entry()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0041e5f0
RaceSessionField0x27f4::Entry::~Entry()
{
	FUN_0041e630();
}

// FUNCTION: LEGORACERS 0x0041e600
void RaceSessionField0x27f4::Entry::Reset()
{
	m_unk0x20.m_all = 0xffffffff;
	m_unk0x00.m_x = 0;
	m_unk0x00.m_y = 0;
	m_unk0x00.m_z = 0;
	m_unk0x0c = 0;
	m_unk0x10.m_x = 0;
	m_unk0x10.m_y = 0;
	m_unk0x10.m_z = 0;
	m_unk0x1c = -1.0f;
}

// FUNCTION: LEGORACERS 0x0041e630
void RaceSessionField0x27f4::Entry::FUN_0041e630()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0041e640
void RaceSessionField0x27f4::Entry::FUN_0041e640(GolFileParser* p_parser, LegoBool32 p_mirror)
{
	p_parser->ReadLeftCurly();

	LegoU32 i;
	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case GolFileParser::e_unknown0x28:
			m_unk0x00.m_x = p_parser->ReadFloat();
			if (p_mirror) {
				m_unk0x00.m_y = -p_parser->ReadFloat();
			}
			else {
				m_unk0x00.m_y = p_parser->ReadFloat();
			}
			m_unk0x00.m_z = p_parser->ReadFloat();
			m_unk0x0c = p_parser->ReadFloat();
			break;
		case GolFileParser::e_unknown0x29:
			for (i = 0; i < sizeOfArray(m_unk0x20.m_items); i++) {
				m_unk0x20.m_items[i] = static_cast<LegoU8>(p_parser->ReadInteger());
			}
			break;
		case GolFileParser::e_unknown0x2a:
			m_unk0x10.m_x = p_parser->ReadFloat();
			if (p_mirror) {
				m_unk0x10.m_y = -p_parser->ReadFloat();
			}
			else {
				m_unk0x10.m_y = p_parser->ReadFloat();
			}
			m_unk0x10.m_z = p_parser->ReadFloat();
			break;
		default:
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}

		token = p_parser->GetNextToken();
	}
}

// FUNCTION: LEGORACERS 0x0041e720
RaceSessionField0x27f4::~RaceSessionField0x27f4()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0041e730
void RaceSessionField0x27f4::Reset()
{
	if (m_entries) {
		delete[] m_entries;
		m_entries = NULL;
	}

	m_count = 0;
}

// FUNCTION: LEGORACERS 0x0041e770
void RaceSessionField0x27f4::FUN_0041e770(const LegoChar* p_name, LegoBool32 p_binary, LegoBool32 p_mirror)
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
	parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
	m_count = parser->ReadBracketedCountAndLeftCurly();
	if (m_count) {
		if (m_count > 0xfe) {
			GOL_FATALERROR_MESSAGE("Too many CheckPoints");
		}

		m_entries = new Entry[m_count];
	}

	for (LegoU32 i = 0; i < m_count; i++) {
		parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
		m_entries[i].FUN_0041e640(parser, p_mirror);
	}

	parser->ReadRightCurly();
	parser->Dispose();
	if (parser != NULL) {
		delete parser;
	}

	FUN_0041e950();
}

// FUNCTION: LEGORACERS 0x0041e940 FOLDED
RaceSessionField0x27f4::Entry* RaceSessionField0x27f4::FUN_0041e940(LegoU32 p_unk0x04)
{
	return &m_entries[p_unk0x04];
}

// STUB: LEGORACERS 0x0041e950
void RaceSessionField0x27f4::FUN_0041e950()
{
	LegoS32 pathCount = static_cast<LegoS32>(FUN_0041ea60());
	Entry* entry = m_entries;
	LegoFloat step = 1.0f / pathCount;
	LegoFloat progress = 0.0f;

	do {
		entry->m_unk0x1c = progress;
		progress += step;
		entry = &m_entries[entry->m_unk0x20.m_items[0]];
	} while (entry != m_entries && progress < 1.0f);

	LegoU32 entryIndex = 0;
	do {
		entry = &m_entries[entryIndex];
		for (LegoU32 i = 1; i < sizeOfArray(entry->m_unk0x20.m_items); i++) {
			LegoU8 next = entry->m_unk0x20.m_items[i];
			if (next != 0xff) {
				LegoU32 distance;
				LegoU32 targetIndex = FUN_0041ea90(next, &distance);
				Entry* target = &m_entries[targetIndex];
				LegoFloat step = (target->m_unk0x1c - entry->m_unk0x1c) / (distance + 1);
				Entry* cursor = &m_entries[entry->m_unk0x20.m_items[i]];
				LegoFloat progress = entry->m_unk0x1c + step;

				do {
					cursor->m_unk0x1c = progress;
					progress += step;
					cursor = &m_entries[cursor->m_unk0x20.m_items[0]];
				} while (cursor != target);
			}
		}

		entryIndex = entry->m_unk0x20.m_items[0];
	} while (entryIndex != 0);
}

// FUNCTION: LEGORACERS 0x0041ea60
LegoU32 RaceSessionField0x27f4::FUN_0041ea60()
{
	LegoU32 result = 0;
	Entry* first = m_entries;
	Entry* entry = first;

	do {
		result++;
		entry = &m_entries[entry->m_unk0x20.m_items[0]];
	} while (entry != first && result < m_count);

	return result;
}

// FUNCTION: LEGORACERS 0x0041ea90
LegoU32 RaceSessionField0x27f4::FUN_0041ea90(LegoU32 p_unk0x04, LegoU32* p_unk0x08)
{
	*p_unk0x08 = 0;

	Entry* entry = &m_entries[p_unk0x04];
	while (entry->m_unk0x1c == g_minSoundPan) {
		if (*p_unk0x08 >= m_count) {
			break;
		}

		LegoU32 count = *p_unk0x08 + 1;
		p_unk0x04 = entry->m_unk0x20.m_items[0];
		*p_unk0x08 = count;
		entry = &m_entries[p_unk0x04];
	}

	return p_unk0x04;
}

// FUNCTION: LEGORACERS 0x0045c3b0 FOLDED
RaceSessionField0x27f4::RaceSessionField0x27f4()
{
	m_entries = NULL;
	m_count = 0;
}
