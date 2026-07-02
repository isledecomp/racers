#include "decomp.h"
#include "golbinparser.h"
#include "golboundedentity.h"
#include "golerror.h"
#include "race/racesession.h"
#include "world/golworlddatabase.h"

#include <string.h>

DECOMP_SIZE_ASSERT(RaceSession::RacerTriggerList, 0x18)
DECOMP_SIZE_ASSERT(RaceSession::RacerTriggerList::Entry, 0x58)
DECOMP_SIZE_ASSERT(RaceSession::RacerTriggerList::EntryParams, 0x3c)
DECOMP_SIZE_ASSERT(RaceSession::TriggerList, 0x14)
DECOMP_SIZE_ASSERT(RaceSession::TriggerList::Entry, 0x3c)
DECOMP_SIZE_ASSERT(RaceSession::TriggerList::EntryParams, 0x1c)
DECOMP_SIZE_ASSERT(RaceSession::TriggerList::TrbTxtParser, 0x1fc)

// FUNCTION: LEGORACERS 0x00463ae0
RaceSession::RacerTriggerList::Entry::Entry()
{
	m_insideMask = 0;
	m_previousInsideMask = 0;
	m_raceState = NULL;
	m_powerupManager = 0;
	m_collisionWorlds = 0;
	m_collisionWorldIndex = 0;
	m_lapNumber = 0;
}

// FUNCTION: LEGORACERS 0x00463b10
RaceSession::RacerTriggerList::Entry::~Entry()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00463b60
void RaceSession::RacerTriggerList::Entry::Initialize(const EntryParams* p_params)
{
	CallBaseInitialize(p_params);
	m_raceState = p_params->m_raceState;
	m_powerupManager = p_params->m_powerupManager;
	m_collisionWorlds = p_params->m_collisionWorlds;
	m_collisionWorldIndex = p_params->m_collisionWorldIndex;
	m_lapNumber = p_params->m_lapNumber;

	if (p_params->m_triggerOnProjectiles) {
		m_flags0x38 |= c_triggerOnProjectiles;
	}

	if (p_params->m_hasCollisionWorld) {
		m_flags0x38 |= c_activatesCollisionWorld;
	}

	if (p_params->m_hasLapNumber) {
		m_flags0x38 |= c_lapGated;
	}
}

// FUNCTION: LEGORACERS 0x00463bd0
void RaceSession::RacerTriggerList::Entry::Destroy()
{
	CallBaseDestroy();
	m_insideMask = 0;
	m_previousInsideMask = 0;
	m_eventTable = 0;
	m_raceState = NULL;
	m_powerupManager = 0;
	m_collisionWorldIndex = 0;
	m_lapNumber = 0;
}

// FUNCTION: LEGORACERS 0x00463c00
void RaceSession::RacerTriggerList::Entry::Update(LegoU32 p_elapsedMs)
{
	CallBaseUpdate(p_elapsedMs);
	if (m_eventId != -1 && m_previousInsideMask) {
		LegoU32 bit = 1;
		LegoU32 racerIndex;
		for (racerIndex = 0; racerIndex < 6; racerIndex++) {
			if ((bit & m_previousInsideMask) && !(bit & m_insideMask)) {
				m_eventTable->EndEventsForRacer(m_eventId, m_raceState->GetRacer(racerIndex));
			}

			bit <<= 1;
		}
	}

	m_previousInsideMask = m_insideMask;
	m_insideMask = 0;
}

// FUNCTION: LEGORACERS 0x00463c70
void RaceSession::RacerTriggerList::Entry::VTable0x00(LegoEventQueue::CallbackData* p_data)
{
	RaceState::Racer* racer = NULL;
	if (p_data->m_type == 2) {
		if (!m_powerupManager->IsProjectileEntity(static_cast<GolWorldEntity*>(p_data->m_data))) {
			return;
		}
	}
	else if (p_data->m_type == 4) {
		racer = static_cast<RaceState::Racer*>(p_data->m_data);
		if ((m_flags0x38 & c_lapGated) && racer->m_lapsCompleted != m_lapNumber) {
			return;
		}

		if (m_flags0x38 & c_activatesCollisionWorld) {
			m_collisionWorlds->ActivateWorld(racer, m_collisionWorldIndex);
		}
	}

	CallBaseVTable0x00(p_data);
	if (racer) {
		LegoU32 bit = 1 << racer->m_materialIndex;
		LegoU32 previousFlags = m_previousInsideMask;
		m_insideMask |= bit;
		if (!(previousFlags & bit) && m_eventId != -1) {
			m_eventTable->StartEventsForRacer(m_eventId, racer);
		}
	}
}

// FUNCTION: LEGORACERS 0x00463d10
void RaceSession::RacerTriggerList::Entry::Reset()
{
	CallBaseReset();
	m_insideMask = 0;
	m_previousInsideMask = 0;
}

// FUNCTION: LEGORACERS 0x00463d30
RaceSession::RacerTriggerList::RacerTriggerList()
{
	m_racerEntries = NULL;
}

// FUNCTION: LEGORACERS 0x00463d70
RaceSession::RacerTriggerList::~RacerTriggerList()
{
	Destroy();
}

// STUB: LEGORACERS 0x00463dc0
void RaceSession::RacerTriggerList::Load(
	RaceState* p_raceState,
	RaceEventTable* p_eventTable,
	RacePowerupManager* p_powerupManager,
	GolWorldDatabase* p_worldDatabase,
	RacerCollisionWorlds* p_collisionWorlds,
	const LegoChar* p_name,
	LegoBool32 p_binary,
	LegoBool32 p_mirror
)
{
	if (m_eventQueue) {
		Destroy();
	}

	m_eventQueue = p_raceState->GetEventQueue();
	m_eventTable = p_eventTable;

	GolFileParser* parser = CreateParser(p_name, p_binary);
	if (parser) {
		m_racerEntries = new Entry[m_count];
		if (m_racerEntries == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		for (LegoU32 i = 0; i < m_count; i++) {
			parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
			parser->ReadLeftCurly();

			EntryParams params;
			params.m_eventTable = m_eventTable;
			params.m_position.m_x = 0.0f;
			params.m_position.m_y = 0.0f;
			params.m_position.m_z = 0.0f;
			params.m_radius = 0.0f;
			params.m_eventId = 0;
			params.m_mirror = FALSE;
			params.m_raceState = p_raceState;
			params.m_powerupManager = p_powerupManager;
			params.m_collisionWorlds = p_collisionWorlds;
			params.m_lapNumber = 0;
			params.m_triggerOnProjectiles = FALSE;
			params.m_hasCollisionWorld = FALSE;
			params.m_hasLapNumber = FALSE;
			params.m_collisionWorldIndex = 0;

			GolFileParser::ParserTokenType token = parser->GetNextToken();
			while (token != GolFileParser::e_rightCurly) {
				switch (token) {
				case GolFileParser::e_unknown0x2c:
					params.m_triggerOnProjectiles = TRUE;
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

					params.m_collisionWorldIndex = index;
					params.m_hasCollisionWorld = TRUE;
					break;
				}
				case GolFileParser::e_unknown0x2e:
					params.m_lapNumber = parser->ReadInteger();
					params.m_hasLapNumber = TRUE;
					break;
				default:
					ParseTrigger(parser, &params);
					break;
				}

				token = parser->GetNextToken();
			}

			if (p_mirror) {
				params.m_position.m_y = -params.m_position.m_y;
			}

			m_racerEntries[i].Initialize(&params);
			RegisterTrigger(&m_racerEntries[i], params.m_triggerOnProjectiles);
		}

		DestroyParser(parser);
	}
}

// FUNCTION: LEGORACERS 0x004640a0
void RaceSession::RacerTriggerList::Destroy()
{
	if (m_racerEntries) {
		delete[] m_racerEntries;
		m_racerEntries = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004640c0
LegoU32 RaceSession::RacerTriggerList::Update(LegoU32 p_elapsedMs)
{
	LegoU32 i;
	LegoU32 result = m_count;

	for (i = 0; i < result; i++) {
		m_racerEntries[i].Update(p_elapsedMs);
		result = m_count;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00464100
LegoU32 RaceSession::RacerTriggerList::Reset()
{
	LegoU32 i;
	LegoU32 result = m_count;

	for (i = 0; i < result; i++) {
		m_racerEntries[i].Reset();
		result = m_count;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00464e40
RaceSession::TriggerList::Entry::Entry()
{
	m_eventTable = NULL;
	m_event = NULL;
	m_eventId = 0;
	m_flags0x38 = 0;
}

// FUNCTION: LEGORACERS 0x00464e70
RaceSession::TriggerList::Entry::~Entry()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00464e80
void RaceSession::TriggerList::Entry::Initialize(const EntryParams* p_params)
{
	m_eventTable = p_params->m_eventTable;
	m_body.SetCenter(p_params->m_position);
	m_body.FUN_10026fa0(p_params->m_radius);
	m_eventId = p_params->m_eventId;

	if (p_params->m_mirror) {
		m_flags0x38 |= c_mirror;
	}
}

// FUNCTION: LEGORACERS 0x00464ed0
void RaceSession::TriggerList::Entry::Destroy()
{
	m_eventTable = NULL;

	if (m_event) {
		m_event->m_active = 0;
		m_event = NULL;
	}

	m_eventId = 0;
	m_flags0x38 = 0;
}

// FUNCTION: LEGORACERS 0x00464ef0
void RaceSession::TriggerList::Entry::Update(LegoU32)
{
	LegoU32 flags = m_flags0x38;
	if ((flags & c_eventsActive) && !(flags & c_touchedThisFrame)) {
		m_flags0x38 = flags & ~c_eventsActive;

		GolVec3 position;
		GolWorldEntity* entity = &m_body;
		entity->VTable0x04(&position);

		if (m_eventId != -1) {
			m_eventTable->EndEventsAt(m_eventId, &position);
		}
	}

	m_flags0x38 &= ~c_touchedThisFrame;
}

// FUNCTION: LEGORACERS 0x00464f40
void RaceSession::TriggerList::Entry::VTable0x00(LegoEventQueue::CallbackData*)
{
	LegoU32 flags = m_flags0x38;
	if (!(flags & c_eventsActive)) {
		m_flags0x38 = flags | c_eventsActive;

		GolVec3 position;
		GolWorldEntity* entity = &m_body;
		entity->VTable0x04(&position);

		if (m_eventId != -1) {
			m_eventTable->StartEventsAt(m_eventId, &position);
		}
	}

	m_flags0x38 |= c_touchedThisFrame;
}

// FUNCTION: LEGORACERS 0x00464f90
void RaceSession::TriggerList::Entry::Reset()
{
	m_flags0x38 &= ~(c_touchedThisFrame | c_eventsActive);
}

// FUNCTION: LEGORACERS 0x00464fa0
RaceSession::TriggerList::TriggerList()
{
	m_entries = NULL;
	m_eventQueue = NULL;
	m_eventTable = 0;
	m_count = 0;
}

// FUNCTION: LEGORACERS 0x00464fe0
RaceSession::TriggerList::~TriggerList()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00464ff0
void RaceSession::TriggerList::Load(
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
			parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
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
void RaceSession::TriggerList::Destroy()
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
GolFileParser* RaceSession::TriggerList::CreateParser(const LegoChar* p_name, LegoBool32 p_binary)
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
void RaceSession::TriggerList::DestroyParser(GolFileParser* p_parser)
{
	p_parser->Dispose();
	delete p_parser;
}

// FUNCTION: LEGORACERS 0x00465350
void RaceSession::TriggerList::ParseTrigger(GolFileParser* p_parser, EntryParams* p_params)
{
	switch (p_parser->GetCurrentToken()) {
	case GolFileParser::e_unknown0x29:
		p_params->m_position.m_x = p_parser->ReadFloat();
		p_params->m_position.m_y = p_parser->ReadFloat();
		p_params->m_position.m_z = p_parser->ReadFloat();
		break;
	case GolFileParser::e_unknown0x2a:
		p_params->m_radius = p_parser->ReadFloat();
		break;
	case GolFileParser::e_unknown0x2b:
		p_params->m_eventId = p_parser->ReadInteger();
		break;
	case GolFileParser::e_unknown0x2f:
		p_params->m_mirror = TRUE;
		break;
	default:
		p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
		break;
	}
}

// FUNCTION: LEGORACERS 0x004653f0
LegoEventQueue::Event* RaceSession::TriggerList::RegisterTrigger(Entry* p_entry, LegoBool32 p_projectiles)
{
	LegoEventQueue::Descriptor descriptor;
	descriptor.m_flags = 1;
	if (p_entry->m_flags0x38 & Entry::c_mirror) {
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
LegoU32 RaceSession::TriggerList::Update(LegoU32 p_elapsedMs)
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
LegoU32 RaceSession::TriggerList::Reset()
{
	LegoU32 i;
	LegoU32 result = m_count;

	for (i = 0; i < result; i++) {
		m_entries[i].Reset();
		result = m_count;
	}

	return result;
}
