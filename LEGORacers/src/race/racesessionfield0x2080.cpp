#include "decomp.h"
#include "golbinparser.h"
#include "golboundedentity.h"
#include "golerror.h"
#include "race/racesession.h"
#include "world/golworlddatabase.h"

#include <string.h>

DECOMP_SIZE_ASSERT(RaceSession::Field0x2080, 0x18)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2080::Entry, 0x58)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2080::EntryParams, 0x3c)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2128, 0x14)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2128::Entry, 0x3c)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2128::EntryParams, 0x1c)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2128::TrbTxtParser, 0x1fc)

// FUNCTION: LEGORACERS 0x00463ae0
RaceSession::Field0x2080::Entry::Entry()
{
	m_unk0x3c = 0;
	m_unk0x40 = 0;
	m_raceState = NULL;
	m_unk0x48 = 0;
	m_unk0x4c = 0;
	m_unk0x50 = 0;
	m_unk0x54 = 0;
}

// FUNCTION: LEGORACERS 0x00463b10
RaceSession::Field0x2080::Entry::~Entry()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x00463b60
void RaceSession::Field0x2080::Entry::FUN_00463b60(const EntryParams* p_params)
{
	FUN_00464e80(p_params);
	m_raceState = p_params->m_raceState;
	m_unk0x48 = p_params->m_unk0x20;
	m_unk0x4c = p_params->m_unk0x24;
	m_unk0x50 = p_params->m_unk0x38;
	m_unk0x54 = p_params->m_unk0x28;

	if (p_params->m_unk0x2c) {
		m_flags0x38 |= c_flags0x38Bit0x1000;
	}

	if (p_params->m_unk0x30) {
		m_flags0x38 |= c_flags0x38Bit0x2000;
	}

	if (p_params->m_unk0x34) {
		m_flags0x38 |= c_flags0x38Bit0x4000;
	}
}

// FUNCTION: LEGORACERS 0x00463bd0
void RaceSession::Field0x2080::Entry::VTable0x08()
{
	CallBaseVTable0x08();
	m_unk0x3c = 0;
	m_unk0x40 = 0;
	m_unk0x30 = 0;
	m_raceState = NULL;
	m_unk0x48 = 0;
	m_unk0x50 = 0;
	m_unk0x54 = 0;
}

// FUNCTION: LEGORACERS 0x00463c00
void RaceSession::Field0x2080::Entry::VTable0x0c(LegoU32 p_elapsedMs)
{
	CallBaseVTable0x0c(p_elapsedMs);
	if (m_unk0x34 != -1 && m_unk0x40) {
		LegoU32 bit = 1;
		LegoU32 racerIndex;
		for (racerIndex = 0; racerIndex < 6; racerIndex++) {
			if ((bit & m_unk0x40) && !(bit & m_unk0x3c)) {
				m_unk0x30->FUN_004629d0(m_unk0x34, m_raceState->GetRacer(racerIndex));
			}

			bit <<= 1;
		}
	}

	m_unk0x40 = m_unk0x3c;
	m_unk0x3c = 0;
}

// FUNCTION: LEGORACERS 0x00463c70
void RaceSession::Field0x2080::Entry::VTable0x00(LegoEventQueue::CallbackData* p_data)
{
	RaceState::Racer* racer = NULL;
	if (p_data->m_unk0x00 == 2) {
		if (!m_unk0x48->FUN_0045b9a0(static_cast<RaceState::Racer*>(p_data->m_data))) {
			return;
		}
	}
	else if (p_data->m_unk0x00 == 4) {
		racer = static_cast<RaceState::Racer*>(p_data->m_data);
		if ((m_flags0x38 & c_flags0x38Bit0x4000) && racer->m_lapsCompleted != m_unk0x54) {
			return;
		}

		if (m_flags0x38 & c_flags0x38Bit0x2000) {
			m_unk0x4c->FUN_0045e520(racer, m_unk0x50);
		}
	}

	CallBaseVTable0x00(p_data);
	if (racer) {
		LegoU32 bit = 1 << racer->m_unk0xe04;
		LegoU32 previousFlags = m_unk0x40;
		m_unk0x3c |= bit;
		if (!(previousFlags & bit) && m_unk0x34 != -1) {
			m_unk0x30->FUN_004628c0(m_unk0x34, racer);
		}
	}
}

// FUNCTION: LEGORACERS 0x00463d10
void RaceSession::Field0x2080::Entry::VTable0x10()
{
	CallBaseVTable0x10();
	m_unk0x3c = 0;
	m_unk0x40 = 0;
}

// FUNCTION: LEGORACERS 0x00463d30
RaceSession::Field0x2080::Field0x2080()
{
	m_unk0x14 = NULL;
}

// FUNCTION: LEGORACERS 0x00463d70
RaceSession::Field0x2080::~Field0x2080()
{
	Destroy();
}

// STUB: LEGORACERS 0x00463dc0
void RaceSession::Field0x2080::FUN_00463dc0(
	RaceState* p_raceState,
	RaceEventTable0x90* p_eventTable,
	RacePowerupManager* p_field0x6dc,
	GolWorldDatabase* p_worldDatabase,
	Field0x32c4* p_field0x32c4,
	const LegoChar* p_name,
	LegoBool32 p_binary,
	LegoBool32 p_mirror
)
{
	if (m_eventQueue) {
		Destroy();
	}

	m_eventQueue = p_raceState->GetEventQueue();
	m_unk0x08 = p_eventTable;

	GolFileParser* parser = FUN_00465210(p_name, p_binary);
	if (parser) {
		m_unk0x14 = new Entry[m_count];
		if (m_unk0x14 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		for (LegoU32 i = 0; i < m_count; i++) {
			parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
			parser->ReadLeftCurly();

			EntryParams params;
			params.m_unk0x00 = m_unk0x08;
			params.m_unk0x08.m_x = 0.0f;
			params.m_unk0x08.m_y = 0.0f;
			params.m_unk0x08.m_z = 0.0f;
			params.m_unk0x14 = 0.0f;
			params.m_unk0x04 = 0;
			params.m_unk0x18 = FALSE;
			params.m_raceState = p_raceState;
			params.m_unk0x20 = p_field0x6dc;
			params.m_unk0x24 = p_field0x32c4;
			params.m_unk0x28 = 0;
			params.m_unk0x2c = FALSE;
			params.m_unk0x30 = FALSE;
			params.m_unk0x34 = FALSE;
			params.m_unk0x38 = 0;

			GolFileParser::ParserTokenType token = parser->GetNextToken();
			while (token != GolFileParser::e_rightCurly) {
				switch (token) {
				case GolFileParser::e_unknown0x2c:
					params.m_unk0x2c = TRUE;
					break;
				case GolFileParser::e_unknown0x2d: {
					LegoChar name[8];
					strncpy(name, parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));

					GolBoundedEntity* entry = p_worldDatabase->FindUnk0xd8(name);

					LegoU32 index = p_worldDatabase->GetUnk0x64();
					if (index > 0) {
						GolBoundedEntity* item = p_worldDatabase->GetUnk0xa8();
						for (LegoU32 j = 0; j < index; j++) {
							if (item == entry) {
								index = j;
							}

							item++;
						}
					}

					params.m_unk0x38 = index;
					params.m_unk0x30 = TRUE;
					break;
				}
				case GolFileParser::e_unknown0x2e:
					params.m_unk0x28 = parser->ReadInteger();
					params.m_unk0x34 = TRUE;
					break;
				default:
					FUN_00465350(parser, &params);
					break;
				}

				token = parser->GetNextToken();
			}

			if (p_mirror) {
				params.m_unk0x08.m_y = -params.m_unk0x08.m_y;
			}

			m_unk0x14[i].FUN_00463b60(&params);
			FUN_004653f0(&m_unk0x14[i], params.m_unk0x2c);
		}

		FUN_00465330(parser);
	}
}

// FUNCTION: LEGORACERS 0x004640a0
void RaceSession::Field0x2080::Destroy()
{
	if (m_unk0x14) {
		delete[] m_unk0x14;
		m_unk0x14 = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004640c0
LegoU32 RaceSession::Field0x2080::VTable0x08(undefined4 p_unk0x04)
{
	LegoU32 i;
	LegoU32 result = m_count;

	for (i = 0; i < result; i++) {
		m_unk0x14[i].VTable0x0c(p_unk0x04);
		result = m_count;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00464100
LegoU32 RaceSession::Field0x2080::VTable0x0c()
{
	LegoU32 i;
	LegoU32 result = m_count;

	for (i = 0; i < result; i++) {
		m_unk0x14[i].VTable0x10();
		result = m_count;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00464e40
RaceSession::Field0x2128::Entry::Entry()
{
	m_unk0x30 = NULL;
	m_unk0x2c = NULL;
	m_unk0x34 = 0;
	m_flags0x38 = 0;
}

// FUNCTION: LEGORACERS 0x00464e70
RaceSession::Field0x2128::Entry::~Entry()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x00464e80
void RaceSession::Field0x2128::Entry::FUN_00464e80(const EntryParams* p_params)
{
	m_unk0x30 = p_params->m_unk0x00;
	m_unk0x04.SetCenter(p_params->m_unk0x08);
	m_unk0x04.FUN_10026fa0(p_params->m_unk0x14);
	m_unk0x34 = p_params->m_unk0x04;

	if (p_params->m_unk0x18) {
		m_flags0x38 |= c_flags0x38Bit2;
	}
}

// FUNCTION: LEGORACERS 0x00464ed0
void RaceSession::Field0x2128::Entry::VTable0x08()
{
	m_unk0x30 = NULL;

	if (m_unk0x2c) {
		m_unk0x2c->m_active = 0;
		m_unk0x2c = NULL;
	}

	m_unk0x34 = 0;
	m_flags0x38 = 0;
}

// FUNCTION: LEGORACERS 0x00464ef0
void RaceSession::Field0x2128::Entry::VTable0x0c(LegoU32)
{
	LegoU32 flags = m_flags0x38;
	if ((flags & c_flags0x38Bit1) && !(flags & c_flags0x38Bit0)) {
		m_flags0x38 = flags & ~c_flags0x38Bit1;

		GolVec3 position;
		GolWorldEntity* entity = &m_unk0x04;
		entity->VTable0x04(&position);

		if (m_unk0x34 != -1) {
			m_unk0x30->FUN_00462140(m_unk0x34, &position);
		}
	}

	m_flags0x38 &= ~c_flags0x38Bit0;
}

// FUNCTION: LEGORACERS 0x00464f40
void RaceSession::Field0x2128::Entry::VTable0x00(LegoEventQueue::CallbackData*)
{
	LegoU32 flags = m_flags0x38;
	if (!(flags & c_flags0x38Bit1)) {
		m_flags0x38 = flags | c_flags0x38Bit1;

		GolVec3 position;
		GolWorldEntity* entity = &m_unk0x04;
		entity->VTable0x04(&position);

		if (m_unk0x34 != -1) {
			m_unk0x30->FUN_00461ef0(m_unk0x34, &position);
		}
	}

	m_flags0x38 |= c_flags0x38Bit0;
}

// FUNCTION: LEGORACERS 0x00464f90
void RaceSession::Field0x2128::Entry::VTable0x10()
{
	m_flags0x38 &= ~(c_flags0x38Bit0 | c_flags0x38Bit1);
}

// FUNCTION: LEGORACERS 0x00464fa0
RaceSession::Field0x2128::Field0x2128()
{
	m_entries = NULL;
	m_eventQueue = NULL;
	m_unk0x08 = 0;
	m_count = 0;
}

// FUNCTION: LEGORACERS 0x00464fe0
RaceSession::Field0x2128::~Field0x2128()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00464ff0
void RaceSession::Field0x2128::FUN_00464ff0(
	LegoEventQueue* p_eventQueue,
	RaceEventTable0x90* p_unk0x08,
	const LegoChar* p_name,
	LegoBool32 p_binary,
	LegoBool32 p_mirror
)
{
	if (m_eventQueue) {
		Destroy();
	}

	m_eventQueue = p_eventQueue;
	m_unk0x08 = p_unk0x08;

	GolFileParser* parser = FUN_00465210(p_name, p_binary);
	if (parser) {
		m_entries = new Entry[m_count];
		if (m_entries == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		for (LegoU32 i = 0; i < m_count; i++) {
			parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
			parser->ReadLeftCurly();

			EntryParams params;
			params.m_unk0x00 = m_unk0x08;
			params.m_unk0x08.m_x = 0.0f;
			params.m_unk0x08.m_y = 0.0f;
			params.m_unk0x08.m_z = 0.0f;
			params.m_unk0x14 = 0.0f;
			params.m_unk0x04 = 0;
			params.m_unk0x18 = FALSE;

			GolFileParser::ParserTokenType token = parser->GetNextToken();
			while (token != GolFileParser::e_rightCurly) {
				FUN_00465350(parser, &params);
				token = parser->GetNextToken();
			}

			if (p_mirror) {
				params.m_unk0x08.m_y = -params.m_unk0x08.m_y;
			}

			m_entries[i].FUN_00464e80(&params);
			FUN_004653f0(&m_entries[i], FALSE);
		}

		FUN_00465330(parser);
	}
}

// FUNCTION: LEGORACERS 0x004651e0
void RaceSession::Field0x2128::Destroy()
{
	if (m_entries) {
		delete[] m_entries;
		m_entries = NULL;
	}

	m_eventQueue = NULL;
	m_unk0x08 = 0;
	m_count = 0;
}

// FUNCTION: LEGORACERS 0x00465210
GolFileParser* RaceSession::Field0x2128::FUN_00465210(const LegoChar* p_name, LegoBool32 p_binary)
{
	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		parser->SetSuffix(".trb");
	}
	else {
		parser = new TrbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_name);
	parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
	m_count = parser->ReadBracketedCountAndLeftCurly();
	if (!m_count) {
		parser->Dispose();
		delete parser;
		return NULL;
	}

	return parser;
}

// FUNCTION: LEGORACERS 0x00465330
void RaceSession::Field0x2128::FUN_00465330(GolFileParser* p_parser)
{
	p_parser->Dispose();
	delete p_parser;
}

// FUNCTION: LEGORACERS 0x00465350
void RaceSession::Field0x2128::FUN_00465350(GolFileParser* p_parser, EntryParams* p_params)
{
	switch (p_parser->GetCurrentToken()) {
	case GolFileParser::e_unknown0x29:
		p_params->m_unk0x08.m_x = p_parser->ReadFloat();
		p_params->m_unk0x08.m_y = p_parser->ReadFloat();
		p_params->m_unk0x08.m_z = p_parser->ReadFloat();
		break;
	case GolFileParser::e_unknown0x2a:
		p_params->m_unk0x14 = p_parser->ReadFloat();
		break;
	case GolFileParser::e_unknown0x2b:
		p_params->m_unk0x04 = p_parser->ReadInteger();
		break;
	case GolFileParser::e_unknown0x2f:
		p_params->m_unk0x18 = TRUE;
		break;
	default:
		p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
		break;
	}
}

// FUNCTION: LEGORACERS 0x004653f0
LegoEventQueue::Event* RaceSession::Field0x2128::FUN_004653f0(Entry* p_entry, LegoBool32 p_unk0x0c)
{
	LegoEventQueue::Descriptor descriptor;
	descriptor.m_unk0x04 = 1;
	if (p_entry->m_flags0x38 & Entry::c_flags0x38Bit2) {
		descriptor.m_unk0x04 = 9;
	}

	LegoEventQueue* eventQueue = m_eventQueue;
	descriptor.m_unk0x08 = 0;
	descriptor.m_unk0x0c = 0;
	p_unk0x0c = p_unk0x0c ? 2 : 4;
	descriptor.m_unk0x00 = p_unk0x0c;
	descriptor.m_worldEntity = &p_entry->m_unk0x04;

	LegoEventQueue::Descriptor* descriptorPtr = &descriptor;
	LegoEventQueue::Event* result = eventQueue->FUN_0042fb50(p_entry, descriptorPtr);
	p_entry->m_unk0x2c = result;
	return result;
}

// FUNCTION: LEGORACERS 0x00465450
LegoU32 RaceSession::Field0x2128::VTable0x08(undefined4 p_unk0x04)
{
	LegoU32 i;
	LegoU32 result = m_count;

	for (i = 0; i < result; i++) {
		m_entries[i].VTable0x0c(p_unk0x04);
		result = m_count;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00465490
LegoU32 RaceSession::Field0x2128::VTable0x0c()
{
	LegoU32 i;
	LegoU32 result = m_count;

	for (i = 0; i < result; i++) {
		m_entries[i].VTable0x10();
		result = m_count;
	}

	return result;
}
