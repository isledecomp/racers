#include "decomp.h"
#include "golbinparser.h"
#include "golboundedentity.h"
#include "golerror.h"
#include "race/racesession.h"
#include "world/golworlddatabase.h"

#include <string.h>

DECOMP_SIZE_ASSERT(RacerTriggerList, 0x18)
DECOMP_SIZE_ASSERT(RacerTriggerList::Entry, 0x58)
DECOMP_SIZE_ASSERT(RacerTriggerList::EntryParams, 0x3c)

// FUNCTION: LEGORACERS 0x00463ae0
RacerTriggerList::Entry::Entry()
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
RacerTriggerList::Entry::~Entry()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00463b60
void RacerTriggerList::Entry::Initialize(const EntryParams* p_params)
{
	CallBaseInitialize(p_params);
	m_raceState = p_params->m_raceState;
	m_powerupManager = p_params->m_powerupManager;
	m_collisionWorlds = p_params->m_collisionWorlds;
	m_collisionWorldIndex = p_params->m_collisionWorldIndex;
	m_lapNumber = p_params->m_lapNumber;

	if (p_params->m_triggerOnProjectiles) {
		m_flags |= c_triggerOnProjectiles;
	}

	if (p_params->m_hasCollisionWorld) {
		m_flags |= c_activatesCollisionWorld;
	}

	if (p_params->m_hasLapNumber) {
		m_flags |= c_lapGated;
	}
}

// FUNCTION: LEGORACERS 0x00463bd0
void RacerTriggerList::Entry::Destroy()
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
void RacerTriggerList::Entry::Update(LegoU32 p_elapsedMs)
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
void RacerTriggerList::Entry::OnEvent(LegoEventQueue::CallbackData* p_data)
{
	Racer* racer = NULL;
	if (p_data->m_type == LegoEventQueue::Descriptor::c_typeProximity) {
		if (!m_powerupManager->IsProjectileEntity(static_cast<GolWorldEntity*>(p_data->m_data))) {
			return;
		}
	}
	else if (p_data->m_type == LegoEventQueue::Descriptor::c_typeRacerTrigger) {
		racer = static_cast<Racer*>(p_data->m_data);
		if ((m_flags & c_lapGated) && racer->m_lapsCompleted != m_lapNumber) {
			return;
		}

		if (m_flags & c_activatesCollisionWorld) {
			m_collisionWorlds->ActivateWorld(racer, m_collisionWorldIndex);
		}
	}

	CallBaseOnEvent(p_data);
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
void RacerTriggerList::Entry::Reset()
{
	CallBaseReset();
	m_insideMask = 0;
	m_previousInsideMask = 0;
}

// FUNCTION: LEGORACERS 0x00463d30
RacerTriggerList::RacerTriggerList()
{
	m_racerEntries = NULL;
}

// FUNCTION: LEGORACERS 0x00463d70
RacerTriggerList::~RacerTriggerList()
{
	Destroy();
}

// STUB: LEGORACERS 0x00463dc0
void RacerTriggerList::Load(
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
			parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(RacerTriggerList::e_triggers));
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
				case RacerTriggerList::e_projectiles:
					params.m_triggerOnProjectiles = TRUE;
					break;
				case RacerTriggerList::e_entity: {
					LegoChar name[8];
					strncpy(name, parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));

					GolBoundedEntity* entry = p_worldDatabase->FindBoundedEntity(name);

					LegoU32 index = p_worldDatabase->GetBoundedEntityCount();
					if (index > 0) {
						GolBoundedEntity* item = p_worldDatabase->GetBoundedEntities();
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
				case RacerTriggerList::e_lap:
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
void RacerTriggerList::Destroy()
{
	if (m_racerEntries) {
		delete[] m_racerEntries;
		m_racerEntries = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004640c0
LegoU32 RacerTriggerList::Update(LegoU32 p_elapsedMs)
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
LegoU32 RacerTriggerList::Reset()
{
	LegoU32 i;
	LegoU32 result = m_count;

	for (i = 0; i < result; i++) {
		m_racerEntries[i].Reset();
		result = m_count;
	}

	return result;
}
