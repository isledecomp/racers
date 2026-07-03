#include "decomp.h"
#include "golbinparser.h"
#include "golboundedentity.h"
#include "golerror.h"
#include "race/racesession.h"
#include "world/golworlddatabase.h"

#include <string.h>

DECOMP_SIZE_ASSERT(TriggerList, 0x14)
DECOMP_SIZE_ASSERT(TriggerList::Entry, 0x3c)
DECOMP_SIZE_ASSERT(TriggerList::EntryParams, 0x1c)
DECOMP_SIZE_ASSERT(TriggerList::TrbTxtParser, 0x1fc)

// FUNCTION: LEGORACERS 0x00464e40
TriggerList::Entry::Entry()
{
	m_eventTable = NULL;
	m_event = NULL;
	m_eventId = 0;
	m_flags = 0;
}

// FUNCTION: LEGORACERS 0x00464e70
TriggerList::Entry::~Entry()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00464e80
void TriggerList::Entry::Initialize(const EntryParams* p_params)
{
	m_eventTable = p_params->m_eventTable;
	m_body.SetBoundsCenter(p_params->m_position);
	m_body.SetBoundsRadius(p_params->m_radius);
	m_eventId = p_params->m_eventId;

	if (p_params->m_mirror) {
		m_flags |= c_mirror;
	}
}

// FUNCTION: LEGORACERS 0x00464ed0
void TriggerList::Entry::Destroy()
{
	m_eventTable = NULL;

	if (m_event) {
		m_event->m_active = 0;
		m_event = NULL;
	}

	m_eventId = 0;
	m_flags = 0;
}

// FUNCTION: LEGORACERS 0x00464ef0
void TriggerList::Entry::Update(LegoU32)
{
	LegoU32 flags = m_flags;
	if ((flags & c_eventsActive) && !(flags & c_touchedThisFrame)) {
		m_flags = flags & ~c_eventsActive;

		GolVec3 position;
		GolWorldEntity* entity = &m_body;
		entity->GetPosition(&position);

		if (m_eventId != -1) {
			m_eventTable->EndEventsAt(m_eventId, &position);
		}
	}

	m_flags &= ~c_touchedThisFrame;
}

// FUNCTION: LEGORACERS 0x00464f40
void TriggerList::Entry::OnEvent(LegoEventQueue::CallbackData*)
{
	LegoU32 flags = m_flags;
	if (!(flags & c_eventsActive)) {
		m_flags = flags | c_eventsActive;

		GolVec3 position;
		GolWorldEntity* entity = &m_body;
		entity->GetPosition(&position);

		if (m_eventId != -1) {
			m_eventTable->StartEventsAt(m_eventId, &position);
		}
	}

	m_flags |= c_touchedThisFrame;
}

// FUNCTION: LEGORACERS 0x00464f90
void TriggerList::Entry::Reset()
{
	m_flags &= ~(c_touchedThisFrame | c_eventsActive);
}

// FUNCTION: LEGORACERS 0x00464fa0
TriggerList::TriggerList()
{
	m_entries = NULL;
	m_eventQueue = NULL;
	m_eventTable = 0;
	m_count = 0;
}

// FUNCTION: LEGORACERS 0x00464fe0
TriggerList::~TriggerList()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00464ff0
void TriggerList::Load(
	LegoEventQueue* p_eventQueue,
	RaceEventTable* p_eventTable,
	const LegoChar* p_name,
	LegoBool32 p_binary,
	LegoBool32 p_mirror
)
{
	if (m_eventQueue) {
		Destroy();
	}

	m_eventQueue = p_eventQueue;
	m_eventTable = p_eventTable;

	GolFileParser* parser = CreateParser(p_name, p_binary);
	if (parser) {
		m_entries = new Entry[m_count];
		if (m_entries == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		for (LegoU32 i = 0; i < m_count; i++) {
			parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(TrbTxtParser::e_triggers));
			parser->ReadLeftCurly();

			EntryParams params;
			params.m_eventTable = m_eventTable;
			params.m_position.m_x = 0.0f;
			params.m_position.m_y = 0.0f;
			params.m_position.m_z = 0.0f;
			params.m_radius = 0.0f;
			params.m_eventId = 0;
			params.m_mirror = FALSE;

			GolFileParser::ParserTokenType token = parser->GetNextToken();
			while (token != GolFileParser::e_rightCurly) {
				ParseTrigger(parser, &params);
				token = parser->GetNextToken();
			}

			if (p_mirror) {
				params.m_position.m_y = -params.m_position.m_y;
			}

			m_entries[i].Initialize(&params);
			RegisterTrigger(&m_entries[i], FALSE);
		}

		DestroyParser(parser);
	}
}

// FUNCTION: LEGORACERS 0x004651e0
void TriggerList::Destroy()
{
	if (m_entries) {
		delete[] m_entries;
		m_entries = NULL;
	}

	m_eventQueue = NULL;
	m_eventTable = 0;
	m_count = 0;
}

// FUNCTION: LEGORACERS 0x00465210
GolFileParser* TriggerList::CreateParser(const LegoChar* p_name, LegoBool32 p_binary)
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
	parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(TrbTxtParser::e_triggers));
	m_count = parser->ReadBracketedCountAndLeftCurly();
	if (!m_count) {
		parser->Dispose();
		delete parser;
		return NULL;
	}

	return parser;
}

// FUNCTION: LEGORACERS 0x00465330
void TriggerList::DestroyParser(GolFileParser* p_parser)
{
	p_parser->Dispose();
	delete p_parser;
}

// FUNCTION: LEGORACERS 0x00465350
void TriggerList::ParseTrigger(GolFileParser* p_parser, EntryParams* p_params)
{
	switch (p_parser->GetCurrentToken()) {
	case TrbTxtParser::e_position:
		p_params->m_position.m_x = p_parser->ReadFloat();
		p_params->m_position.m_y = p_parser->ReadFloat();
		p_params->m_position.m_z = p_parser->ReadFloat();
		break;
	case TrbTxtParser::e_radius:
		p_params->m_radius = p_parser->ReadFloat();
		break;
	case TrbTxtParser::e_event:
		p_params->m_eventId = p_parser->ReadInteger();
		break;
	case TrbTxtParser::e_mirror:
		p_params->m_mirror = TRUE;
		break;
	default:
		p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
		break;
	}
}

// FUNCTION: LEGORACERS 0x004653f0
LegoEventQueue::Event* TriggerList::RegisterTrigger(Entry* p_entry, LegoBool32 p_projectiles)
{
	LegoEventQueue::Descriptor descriptor;
	descriptor.m_flags = 1;
	if (p_entry->m_flags & Entry::c_mirror) {
		descriptor.m_flags = 9;
	}

	LegoEventQueue* eventQueue = m_eventQueue;
	descriptor.m_maxFireCount = 0;
	descriptor.m_hitThreshold = 0;
	p_projectiles = p_projectiles ? 2 : 4;
	descriptor.m_type = p_projectiles;
	descriptor.m_worldEntity = &p_entry->m_body;

	LegoEventQueue::Descriptor* descriptorPtr = &descriptor;
	LegoEventQueue::Event* result = eventQueue->AllocateEvent(p_entry, descriptorPtr);
	p_entry->m_event = result;
	return result;
}

// FUNCTION: LEGORACERS 0x00465450
LegoU32 TriggerList::Update(LegoU32 p_elapsedMs)
{
	LegoU32 i;
	LegoU32 result = m_count;

	for (i = 0; i < result; i++) {
		m_entries[i].Update(p_elapsedMs);
		result = m_count;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00465490
LegoU32 TriggerList::Reset()
{
	LegoU32 i;
	LegoU32 result = m_count;

	for (i = 0; i < result; i++) {
		m_entries[i].Reset();
		result = m_count;
	}

	return result;
}
