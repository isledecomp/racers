#include "race/raceeventtable.h"

#include "audio/spatialsoundinstance.h"
#include "decomp.h"
#include "golbinparser.h"
#include "golboundedentity.h"
#include "golcollidableentity.h"
#include "golerror.h"
#include "golmodelbase.h"
#include "golscenenode.h"
#include "goltransformbase.h"
#include "menu/runtime/cutsceneparticle.h"
#include "race/events/colortransformresource.h"
#include "race/events/externalforceresource.h"
#include "race/events/lapzoneresource.h"
#include "race/events/looktargetresource.h"
#include "race/events/materialanimationresource.h"
#include "race/events/modeldistanceresource.h"
#include "race/events/nodetransformresource.h"
#include "race/events/partanimationresource.h"
#include "race/events/particleresource.h"
#include "race/events/raceeventresource.h"
#include "race/events/skystateresource.h"
#include "race/events/soundresource.h"
#include "race/events/timerresource.h"
#include "race/hazardmanager.h"
#include "race/racesession.h"
#include "race/targetpointlist.h"
#include "world/golworlddatabase.h"

DECOMP_SIZE_ASSERT(RaceEventTable, 0x90)
DECOMP_SIZE_ASSERT(RaceEventTable::EvbTxtParser, 0x1fc)
DECOMP_SIZE_ASSERT(RaceEventTable::Params, 0x34)
DECOMP_SIZE_ASSERT(RaceEventTable::EventLink, 0x08)
DECOMP_SIZE_ASSERT(RaceActionSource, 0x24)

DECOMP_SIZE_ASSERT(RaceEventTable, 0x90)

// STUB: LEGORACERS 0x0045c660
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

// FUNCTION: LEGORACERS 0x0045ee50
void RaceEventResource::OnEventStart(GolVec3* p_position)
{
	if (!(m_flags & 4) && (m_state == 1 || m_state == 4)) {
		OnStartAt(p_position);
	}
}

// FUNCTION: LEGORACERS 0x0045ee70
void RaceEventResource::OnEventEnd(GolVec3* p_position)
{
	if (m_flags & 4) {
		if (m_state == 1 || m_state == 4) {
			OnStartAt(p_position);

			if (!(m_flags & 2)) {
				OnEnd();
			}

			return;
		}
	}

	if (m_state != 1 && !(m_flags & 2)) {
		OnEnd();
	}
}

// FUNCTION: LEGORACERS 0x0045eec0
void RaceEventResource::ForceEventStart(Racer* p_racer)
{
	if (!(m_flags & 4) && (m_state == 1 || m_state == 4)) {
		OnStartForRacer(p_racer);
	}
}

// FUNCTION: LEGORACERS 0x0045ef40
RaceEventTable::RaceEventTable()
{
	m_sounds = NULL;
	m_partAnimations = NULL;
	m_materialAnimations = NULL;
	m_particles = NULL;
	m_eventLinks = NULL;
	m_skyStates = NULL;
	m_timers = NULL;
	m_nodeTransforms = NULL;
	m_colorTransforms = NULL;
	m_lapZones = NULL;
	m_modelDistances = NULL;
	m_lookTargets = NULL;
	m_externalForces = NULL;
	m_trackDatabase = 0;
	m_sharedDatabase = 0;
	m_triggerDatabase = 0;
	m_materialAnimationDatabase = 0;
	m_soundSource = 0;
	m_hazardManager = 0;
	m_skyState = 0;
	m_targetPoints = 0;
}

// FUNCTION: LEGORACERS 0x0045ef90
RaceEventTable::~RaceEventTable()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0045efa0
void RaceEventTable::Load(Params* p_params)
{
	if (m_trackDatabase) {
		Destroy();
	}

	m_trackDatabase = p_params->m_trackDatabase;
	m_sharedDatabase = p_params->m_sharedDatabase;
	m_triggerDatabase = p_params->m_triggerDatabase;
	m_materialAnimationDatabase = p_params->m_materialAnimationDatabase;
	m_soundSource = p_params->m_soundSource;
	m_hazardManager = p_params->m_hazardManager;
	m_particleAnimation = p_params->m_particleAnimation;
	m_sharedParticleAnimation = p_params->m_sharedParticleAnimation;
	m_skyState = p_params->m_skyState;
	m_targetPoints = p_params->m_targetPoints;

	GolFileParser* parser;
	if (p_params->m_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		parser->SetSuffix(".evb");
	}
	else {
		parser = new EvbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_params->m_name);
	for (GolFileParser::ParserTokenType token = parser->GetNextToken(); token; token = parser->GetNextToken()) {
		switch (token) {
		case EvbTxtParser::e_sounds:
			ParseSounds(parser, p_params->m_mirror);
			break;
		case EvbTxtParser::e_partAnimations:
			ParsePartAnimations(parser);
			break;
		case EvbTxtParser::e_materialAnimations:
			ParseMaterialAnimations(parser);
			break;
		case EvbTxtParser::e_particles:
			ParseParticles(parser, p_params->m_mirror);
			break;
		case EvbTxtParser::e_eventLinks:
			ParseEventLinks(parser);
			break;
		case EvbTxtParser::e_skyStates:
			ParseSkyStates(parser);
			break;
		case EvbTxtParser::e_timers:
			ParseTimers(parser);
			break;
		case EvbTxtParser::e_nodeTransforms:
			ParseNodeTransforms(parser);
			break;
		case EvbTxtParser::e_colorTransforms:
			ParseColorTransforms(parser);
			break;
		case EvbTxtParser::e_lapZones:
			ParseLapZones(parser);
			break;
		case EvbTxtParser::e_modelDistances:
			ParseModelDistances(parser);
			break;
		case EvbTxtParser::e_lookTargets:
			ParseLookTargets(parser, p_params->m_mirror);
			break;
		case EvbTxtParser::e_externalForces:
			ParseExternalForces(parser, p_params->m_mirror);
			break;
		default:
			parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}
	}

	parser->Dispose();
	delete parser;
}

// FUNCTION: LEGORACERS 0x0045f220
void RaceEventTable::ParseSounds(GolFileParser* p_parser, LegoBool32 p_mirror)
{
	RaceEventTable* field = this;

	if (p_parser->GetNextToken() != GolFileParser::e_leftBracket) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_leftBracket);
	}

	field->m_soundCount = p_parser->ReadInteger();
	if (p_parser->GetNextToken() != GolFileParser::e_rightBracket) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_rightBracket);
	}

	if (p_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	field->m_sounds = new SoundResource[field->m_soundCount];
	if (field->m_sounds == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < field->m_soundCount; i++) {
		if (p_parser->GetNextToken() != EvbTxtParser::e_event) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
		}

		SoundResource::InitParams params;
		params.m_eventId = p_parser->ReadInteger();

		GolFileParser::ParserTokenType token = p_parser->GetNextToken();
		params.m_triggerOnEnd = FALSE;
		if (token == EvbTxtParser::e_triggerOnEnd) {
			params.m_triggerOnEnd = TRUE;
			if (p_parser->GetNextToken() != GolFileParser::e_leftCurly) {
				p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
			}
		}
		else if (token != GolFileParser::e_leftCurly) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		params.m_maxDistance = 300.0f;
		params.m_minDistance = 30.0f;
		params.m_soundId = 0;
		params.m_looping = FALSE;
		params.m_noEnd = FALSE;
		params.m_positional = FALSE;
		params.m_unk0x1c = 0;
		params.m_volume = 1.0f;
		params.m_frequencyScale = 1.0f;
		params.m_soundSource = field->m_soundSource;
		params.m_probability = 1.0f;
		params.m_entity = NULL;
		params.m_nodeIndex = 0;

		for (token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly; token = p_parser->GetNextToken()) {
			switch (token) {
			case SoundResource::e_position:
				params.m_position.m_x = p_parser->ReadFloat();
				params.m_position.m_y = p_parser->ReadFloat();
				params.m_position.m_z = p_parser->ReadFloat();
				if (p_mirror) {
					params.m_position.m_y = -params.m_position.m_y;
				}
				break;
			case SoundResource::e_soundId:
				params.m_soundId = p_parser->ReadInteger();
				break;
			case SoundResource::e_unknown0x2e:
				params.m_unk0x1c = p_parser->ReadInteger();
				break;
			case SoundResource::e_volume:
				params.m_volume = p_parser->ReadFloat();
				break;
			case SoundResource::e_frequencyScale:
				params.m_frequencyScale = p_parser->ReadFloat();
				break;
			case SoundResource::e_minDistance:
				params.m_minDistance = p_parser->ReadFloat();
				break;
			case SoundResource::e_maxDistance:
				params.m_maxDistance = p_parser->ReadFloat();
				break;
			case EvbTxtParser::e_looping:
				params.m_looping = TRUE;
				break;
			case EvbTxtParser::e_noEnd:
				params.m_noEnd = TRUE;
				break;
			case EvbTxtParser::e_atEventPosition:
				params.m_positional = TRUE;
				break;
			case SoundResource::e_probability:
				params.m_probability = p_parser->ReadFloat();
				break;
			case EvbTxtParser::e_entityName: {
				GolName name;
				::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));
				params.m_entity = field->m_trackDatabase->FindAnimatedEntity(name);
				if (params.m_entity == NULL) {
					params.m_entity = field->m_sharedDatabase->FindAnimatedEntity(name);
				}
				break;
			}
			case EvbTxtParser::e_node:
				params.m_nodeIndex = p_parser->ReadInteger();
				break;
			default:
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}

		field->m_sounds[i].Initialize(&params);
	}

	if (p_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_rightCurly);
	}
}

// FUNCTION: LEGORACERS 0x0045f660
void RaceEventTable::ParsePartAnimations(GolFileParser* p_parser)
{
	RaceEventTable* field = this;

	if (p_parser->GetNextToken() != GolFileParser::e_leftBracket) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_leftBracket);
	}

	field->m_partAnimationCount = p_parser->ReadInteger();
	if (p_parser->GetNextToken() != GolFileParser::e_rightBracket) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_rightBracket);
	}

	if (p_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	field->m_partAnimations = new PartAnimationResource[field->m_partAnimationCount];
	if (field->m_partAnimations == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < field->m_partAnimationCount; i++) {
		if (p_parser->GetNextToken() != EvbTxtParser::e_event) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
		}

		PartAnimationResource::InitParams params;
		params.m_eventId = p_parser->ReadInteger();
		GolFileParser::ParserTokenType token = p_parser->GetNextToken();
		LegoS32 eventIndex = 1;
		params.m_triggerOnEnd = 0;
		if (token == EvbTxtParser::e_triggerOnEnd) {
			eventIndex = 1;
			params.m_triggerOnEnd = 1;
			if (p_parser->GetNextToken() != GolFileParser::e_leftCurly) {
				p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
			}
		}
		else if (token != GolFileParser::e_leftCurly) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		params.m_eventTable = field;
		params.m_stateEventIds[0] = -1;
		params.m_animatedEntity = NULL;
		params.m_stateEventIds[1] = -1;
		params.m_activePart = 0;
		params.m_stateEventIds[2] = -1;
		params.m_idlePart = 0;
		params.m_startPart = -1;
		params.m_endPart = -1;
		params.m_noEnd = FALSE;
		params.m_looping = FALSE;
		params.m_atEventPosition = FALSE;
		params.m_useSharedDatabase = FALSE;

		for (token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly; token = p_parser->GetNextToken()) {
			switch (token) {
			case EvbTxtParser::e_entityName: {
				const LegoChar* name = p_parser->ReadStringWithMaxLength(sizeof(GolName));
				LegoChar destination[sizeof(GolName)];
				::strncpy(destination, name, sizeof(destination));

				if (params.m_useSharedDatabase) {
					GolWorldDatabase* worldDatabase = field->m_sharedDatabase;
					if (worldDatabase->GetAnimatedEntityEntries()) {
						params.m_animatedEntity = worldDatabase->GetAnimatedEntityByName(destination);
					}
					else {
						params.m_animatedEntity = NULL;
					}
				}
				else {
					GolWorldDatabase* worldDatabase = field->m_trackDatabase;
					if (worldDatabase->GetAnimatedEntityEntries()) {
						params.m_animatedEntity = worldDatabase->GetAnimatedEntityByName(destination);
					}
					else {
						params.m_animatedEntity = NULL;
					}
				}
				break;
			}
			case EvbTxtParser::e_sharedDatabase:
				params.m_useSharedDatabase = TRUE;
				break;
			case EvbTxtParser::e_active:
				params.m_activePart = p_parser->ReadInteger();
				break;
			case EvbTxtParser::e_idle:
				params.m_idlePart = p_parser->ReadInteger();
				break;
			case EvbTxtParser::e_start:
				params.m_startPart = p_parser->ReadInteger();
				break;
			case EvbTxtParser::e_end:
				params.m_endPart = p_parser->ReadInteger();
				break;
			case EvbTxtParser::e_looping:
				params.m_looping = TRUE;
				break;
			case EvbTxtParser::e_noEnd:
				params.m_noEnd = TRUE;
				break;
			case EvbTxtParser::e_atEventPosition:
				params.m_atEventPosition = TRUE;
				break;
			case EvbTxtParser::e_event: {
				LegoS32 eventToken = p_parser->GetNextToken() - EvbTxtParser::e_active;
				if (eventToken) {
					eventToken -= 2;
					if (eventToken) {
						eventToken--;
						if (eventToken) {
							eventIndex = 3;
							p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
						}
						else {
							eventIndex = 2;
						}
					}
					else {
						eventIndex = 0;
					}
				}
				params.m_stateEventIds[eventIndex] = p_parser->ReadInteger();
				eventIndex = 1;
				break;
			}
			default:
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}

		field->m_partAnimations[i].Initialize(&params);
	}

	if (p_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_rightCurly);
	}
}

// FUNCTION: LEGORACERS 0x0045fa30
void RaceEventTable::ParseMaterialAnimations(GolFileParser* p_parser)
{
	RaceEventTable* field = this;

	if (p_parser->GetNextToken() != GolFileParser::e_leftBracket) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_leftBracket);
	}

	field->m_materialAnimationCount = p_parser->ReadInteger();
	if (p_parser->GetNextToken() != GolFileParser::e_rightBracket) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_rightBracket);
	}

	if (p_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	field->m_materialAnimations = new MaterialAnimationResource[field->m_materialAnimationCount];
	if (field->m_materialAnimations == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < field->m_materialAnimationCount; i++) {
		if (p_parser->GetNextToken() != EvbTxtParser::e_event) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
		}

		MaterialAnimationResource::InitParams params;
		params.m_eventId = p_parser->ReadInteger();
		GolFileParser::ParserTokenType token = p_parser->GetNextToken();
		params.m_triggerOnEnd = FALSE;
		if (token == EvbTxtParser::e_triggerOnEnd) {
			params.m_triggerOnEnd = TRUE;
			if (p_parser->GetNextToken() != GolFileParser::e_leftCurly) {
				p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
			}
		}
		else if (token != GolFileParser::e_leftCurly) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		params.m_stateEventIds[0] = -1;
		params.m_stateEventIds[1] = -1;
		params.m_stateEventIds[2] = -1;
		params.m_eventTable = field;
		params.m_materialAnimation = NULL;
		params.m_materialTable = NULL;
		params.m_materialIndex = 0;
		params.m_activeTrackIndex = 0;
		params.m_idleTrackIndex = 0;
		params.m_looping = FALSE;
		params.m_noEnd = FALSE;
		params.m_atEventPosition = FALSE;

		for (token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly; token = p_parser->GetNextToken()) {
			switch (token) {
			case EvbTxtParser::e_materialAnimation:
				params.m_materialAnimation =
					field->m_materialAnimationDatabase->GetMaterialAnimation(p_parser->ReadInteger());
				break;
			case EvbTxtParser::e_active:
				params.m_activeTrackIndex = p_parser->ReadInteger();
				break;
			case EvbTxtParser::e_idle:
				params.m_idleTrackIndex = p_parser->ReadInteger();
				break;
			case EvbTxtParser::e_looping:
				params.m_looping = TRUE;
				break;
			case EvbTxtParser::e_noEnd:
				params.m_noEnd = TRUE;
				break;
			case EvbTxtParser::e_atEventPosition:
				params.m_atEventPosition = TRUE;
				break;
			case EvbTxtParser::e_event: {
				LegoS32 eventIndex = p_parser->GetNextToken() - EvbTxtParser::e_active;
				if (eventIndex) {
					eventIndex -= 2;
					if (eventIndex) {
						if (--eventIndex) {
							eventIndex = 3;
							p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
						}
						else {
							eventIndex = 2;
						}
					}
					else {
						eventIndex = 0;
					}
				}
				else {
					eventIndex = 1;
				}
				params.m_stateEventIds[eventIndex] = p_parser->ReadInteger();
				break;
			}
			case EvbTxtParser::e_entityName: {
				const LegoChar* name = p_parser->ReadStringWithMaxLength(sizeof(GolName));
				LegoChar destination[sizeof(GolName)];
				::strncpy(destination, name, sizeof(destination));

				GolModelEntity* entity = field->m_trackDatabase->FindModelEntity(destination);
				if (!entity) {
					entity = field->m_trackDatabase->FindAnimatedEntity(destination);
					if (!entity) {
						entity = field->m_trackDatabase->FindCollidableEntity(destination);
						if (!entity) {
							entity = field->m_sharedDatabase->FindModelEntity(destination);
							if (!entity) {
								entity = field->m_sharedDatabase->FindAnimatedEntity(destination);
								if (!entity) {
									if (field->m_sharedDatabase->GetCollidableEntityEntries() == NULL) {
										entity = NULL;
									}
									else {
										entity = field->m_sharedDatabase->GetCollidableEntityByName(destination);
									}
								}
							}
						}
					}
				}

				MaterialTable* materialTable;
				if (entity->GetMaterialTable(0)) {
					materialTable = entity->GetMaterialTable(0);
				}
				else {
					materialTable = entity->GetModel(0)->GetMaterialTable();
				}
				params.m_materialTable = materialTable;
				params.m_materialIndex = p_parser->ReadInteger();
				break;
			}
			default:
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}

		field->m_materialAnimations[i].Initialize(&params);
	}

	if (p_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_rightCurly);
	}
}

// FUNCTION: LEGORACERS 0x0045feb0
void RaceEventTable::ParseParticles(GolFileParser* p_parser, LegoBool32 p_mirror)
{
	RaceEventTable* field = this;

	field->m_particleCount = p_parser->ReadBracketedCountAndLeftCurly();
	field->m_particles = new ParticleResource[field->m_particleCount];
	if (field->m_particles == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < field->m_particleCount; i++) {
		p_parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(EvbTxtParser::e_event));

		ParticleResource::InitParams params;
		params.m_eventId = p_parser->ReadInteger();

		GolFileParser::ParserTokenType token = p_parser->GetNextToken();
		LegoS32 eventIndex;
		params.m_triggerOnEnd = FALSE;
		if (token == EvbTxtParser::e_triggerOnEnd) {
			eventIndex = 1;
			params.m_triggerOnEnd = eventIndex;
			p_parser->ReadLeftCurly();
		}
		else {
			if (token != GolFileParser::e_leftCurly) {
				p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
			}
			eventIndex = 1;
		}

		params.m_particleAnimation = field->m_particleAnimation;
		params.m_sharedParticleAnimation = field->m_sharedParticleAnimation;
		params.m_stateEventIds[0] = -1;
		params.m_stateEventIds[1] = -1;
		params.m_eventTable = field;
		params.m_stateEventIds[2] = -1;
		params.m_particleName[0] = '\0';
		params.m_noEnd = FALSE;
		params.m_atEventPosition = FALSE;
		params.m_position.m_x = 0.0f;
		params.m_position.m_y = 0.0f;
		params.m_position.m_z = 0.0f;
		params.m_direction.m_x = 1.0f;
		params.m_direction.m_y = 0.0f;
		params.m_direction.m_z = 0.0f;
		params.m_up.m_x = 0.0f;
		params.m_up.m_y = 0.0f;
		params.m_up.m_z = 1.0f;
		params.m_trackedEntity = NULL;
		params.m_nodeIndex = 0;
		LegoBool32 useSharedDatabase = FALSE;

		for (token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly; token = p_parser->GetNextToken()) {
			switch (token) {
			case EvbTxtParser::e_particle:
				::strncpy(
					params.m_particleName,
					p_parser->ReadStringWithMaxLength(sizeof(params.m_particleName)),
					sizeof(params.m_particleName)
				);
				break;
			case EvbTxtParser::e_noEnd:
				params.m_noEnd = eventIndex;
				break;
			case EvbTxtParser::e_position:
				params.m_position.m_x = p_parser->ReadFloat();
				params.m_position.m_y = p_parser->ReadFloat();
				params.m_position.m_z = p_parser->ReadFloat();
				if (p_mirror) {
					params.m_position.m_y = -params.m_position.m_y;
				}
				break;
			case EvbTxtParser::e_direction:
				params.m_direction.m_x = p_parser->ReadFloat();
				params.m_direction.m_y = p_parser->ReadFloat();
				params.m_direction.m_z = p_parser->ReadFloat();
				params.m_up.m_x = p_parser->ReadFloat();
				params.m_up.m_y = p_parser->ReadFloat();
				params.m_up.m_z = p_parser->ReadFloat();
				if (p_mirror) {
					params.m_direction.m_y = -params.m_direction.m_y;
					params.m_up.m_y = -params.m_up.m_y;
				}
				break;
			case EvbTxtParser::e_atEventPosition:
				params.m_atEventPosition = eventIndex;
				break;
			case EvbTxtParser::e_sharedDatabase:
				useSharedDatabase = eventIndex;
				break;
			case EvbTxtParser::e_entityName: {
				const LegoChar* name = p_parser->ReadStringWithMaxLength(sizeof(GolName));
				LegoChar destination[sizeof(GolName)];
				::strncpy(destination, name, sizeof(destination));

				if (useSharedDatabase) {
					GolWorldDatabase* worldDatabase = field->m_sharedDatabase;
					if (worldDatabase->GetAnimatedEntityEntries() == NULL) {
						GolModelEntity* entity = NULL;
						params.m_trackedEntity = entity;
					}
					else {
						params.m_trackedEntity = worldDatabase->GetAnimatedEntityByName(destination);
					}
				}
				else {
					GolWorldDatabase* worldDatabase = field->m_trackDatabase;
					if (worldDatabase->GetAnimatedEntityEntries() == NULL) {
						GolModelEntity* entity = NULL;
						params.m_trackedEntity = entity;
					}
					else {
						params.m_trackedEntity = worldDatabase->GetAnimatedEntityByName(destination);
					}
				}
				break;
			}
			case EvbTxtParser::e_node:
				params.m_nodeIndex = p_parser->ReadInteger();
				break;
			case EvbTxtParser::e_event: {
				LegoS32 eventToken = p_parser->GetNextToken() - EvbTxtParser::e_active;
				if (eventToken) {
					eventToken -= 2;
					if (eventToken) {
						if (--eventToken) {
							eventIndex = 3;
							p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
						}
						else {
							eventIndex = 2;
						}
					}
					else {
						eventIndex = 0;
					}
				}
				params.m_stateEventIds[eventIndex] = p_parser->ReadInteger();
				eventIndex = 1;
				break;
			}
			default:
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}

		field->m_particles[i].Initialize(&params);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00460320
void RaceEventTable::ParseEventLinks(GolFileParser* p_parser)
{
	if (p_parser->GetNextToken() != GolFileParser::e_leftBracket) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_leftBracket);
	}

	m_eventLinkCount = p_parser->ReadInteger();
	if (p_parser->GetNextToken() != GolFileParser::e_rightBracket) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_rightBracket);
	}

	if (p_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	m_eventLinks = new EventLink[m_eventLinkCount];
	if (m_eventLinks == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_eventLinkCount; i++) {
		if (p_parser->GetNextToken() != EvbTxtParser::e_event) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
		}

		m_eventLinks[i].m_eventId = p_parser->ReadInteger();
		if (p_parser->GetNextToken() != GolFileParser::e_leftCurly) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		if (p_parser->GetNextToken() != EvbTxtParser::e_eventLinks) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
		}

		m_eventLinks[i].m_forcedEventId = p_parser->ReadInteger();
		if (p_parser->GetNextToken() != GolFileParser::e_rightCurly) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_rightCurly);
		}
	}

	if (p_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_rightCurly);
	}
}

// FUNCTION: LEGORACERS 0x00460430
void RaceEventTable::ParseSkyStates(GolFileParser* p_parser)
{
	RaceEventTable* field = this;

	field->m_skyStateCount = p_parser->ReadBracketedCountAndLeftCurly();
	field->m_skyStates = new SkyStateResource[field->m_skyStateCount];
	if (field->m_skyStates == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < field->m_skyStateCount; i++) {
		p_parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(EvbTxtParser::e_event));

		SkyStateResource::InitParams params;
		params.m_eventId = p_parser->ReadInteger();

		GolFileParser::ParserTokenType token = p_parser->GetNextToken();
		params.m_triggerOnEnd = FALSE;
		if (token == EvbTxtParser::e_triggerOnEnd) {
			params.m_triggerOnEnd = TRUE;
			p_parser->ReadLeftCurly();
		}
		else if (token != GolFileParser::e_leftCurly) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		params.m_skyState = field->m_skyState;
		params.m_stateEventIds[0] = -1;
		params.m_stateEventIds[1] = -1;
		params.m_eventTable = field;
		params.m_stateEventIds[2] = -1;
		params.m_skyName[0] = '\0';
		params.m_durationMs = 0;
		params.m_skyFlags = 0;

		for (token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly; token = p_parser->GetNextToken()) {
			switch (token) {
			case SkyStateResource::e_skyName:
				::strncpy(
					params.m_skyName,
					p_parser->ReadStringWithMaxLength(sizeof(params.m_skyName)),
					sizeof(params.m_skyName)
				);
				break;
			case EvbTxtParser::e_duration:
				params.m_durationMs = p_parser->ReadInteger();
				break;
			case SkyStateResource::e_hideDome:
				params.m_skyFlags |= SkyStateResource::c_hideDome;
				break;
			case SkyStateResource::e_showDome:
				params.m_skyFlags |= SkyStateResource::c_showDome;
				break;
			case SkyStateResource::e_hideSkyWorld:
				params.m_skyFlags |= SkyStateResource::c_hideSkyWorld;
				break;
			case SkyStateResource::e_showSkyWorld:
				params.m_skyFlags |= SkyStateResource::c_showSkyWorld;
				break;
			case EvbTxtParser::e_event: {
				LegoS32 eventIndex = p_parser->GetNextToken() - EvbTxtParser::e_active;
				if (eventIndex) {
					eventIndex -= 2;
					if (eventIndex) {
						if (--eventIndex) {
							eventIndex = 3;
							p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
						}
						else {
							eventIndex = 2;
						}
					}
					else {
						eventIndex = 0;
					}
				}
				else {
					eventIndex = 1;
				}

				params.m_stateEventIds[eventIndex] = p_parser->ReadInteger();
				break;
			}
			default:
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}

		field->m_skyStates[i].Initialize(&params);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00460720
void RaceEventTable::ParseColorTransforms(GolFileParser* p_parser)
{
	RaceEventTable* field = this;

	field->m_colorTransformCount = p_parser->ReadBracketedCountAndLeftCurly();
	field->m_colorTransforms = new ColorTransformResource[field->m_colorTransformCount];
	if (field->m_colorTransforms == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < field->m_colorTransformCount; i++) {
		p_parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(EvbTxtParser::e_event));

		ColorTransformResource::InitParams params;
		params.m_eventId = p_parser->ReadInteger();

		GolFileParser::ParserTokenType token = p_parser->GetNextToken();
		params.m_flags = 0;
		if (token == EvbTxtParser::e_triggerOnEnd) {
			params.m_flags = 5;
			p_parser->ReadLeftCurly();
		}
		else if (token != GolFileParser::e_leftCurly) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		params.m_stateEventIds[0] = -1;
		params.m_eventTable = field;
		params.m_stateEventIds[1] = -1;
		params.m_worldEntity = NULL;
		params.m_stateEventIds[2] = -1;

		for (token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly; token = p_parser->GetNextToken()) {
			switch (token) {
			case EvbTxtParser::e_entityName: {
				GolName name;
				::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));

				if (field->m_trackDatabase->GetModelEntityEntries()) {
					params.m_worldEntity = field->m_trackDatabase->GetModelEntityByName(name);
				}
				else {
					params.m_worldEntity = NULL;
				}

				if (params.m_worldEntity) {
					break;
				}

				if (field->m_trackDatabase->GetAnimatedEntityEntries()) {
					params.m_worldEntity = field->m_trackDatabase->GetAnimatedEntityByName(name);
				}
				else {
					params.m_worldEntity = NULL;
				}

				if (params.m_worldEntity) {
					break;
				}

				if (field->m_trackDatabase->GetCollidableEntityEntries()) {
					params.m_worldEntity = field->m_trackDatabase->GetCollidableEntityByName(name);
				}
				else {
					params.m_worldEntity = NULL;
				}
				break;
			}
			case ColorTransformResource::e_shifts:
				params.m_colorTransform.m_redShift = p_parser->ReadInteger();
				params.m_colorTransform.m_grnShift = p_parser->ReadInteger();
				params.m_colorTransform.m_bluShift = p_parser->ReadInteger();
				params.m_colorTransform.m_alpShift = p_parser->ReadInteger();
				break;
			case ColorTransformResource::e_offsets:
				params.m_colorTransform.m_redOffset = p_parser->ReadInteger();
				params.m_colorTransform.m_grnOffset = p_parser->ReadInteger();
				params.m_colorTransform.m_bluOffset = p_parser->ReadInteger();
				params.m_colorTransform.m_alpOffset = p_parser->ReadInteger();
				break;
			case ColorTransformResource::e_clearTransform:
				params.m_flags |= ColorTransformResource::c_clearTransform;
				break;
			case EvbTxtParser::e_noEnd:
				params.m_flags |= 4;
				break;
			case EvbTxtParser::e_event: {
				LegoS32 eventIndex;
				switch (p_parser->GetNextToken()) {
				default:
					eventIndex = 3;
					p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
					break;
				case 55:
					eventIndex = 2;
					break;
				case 54:
					eventIndex = 0;
					break;
				case 52:
					eventIndex = 1;
					break;
				}

				params.m_stateEventIds[eventIndex] = p_parser->ReadInteger();
				break;
			}
			default:
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}

		field->m_colorTransforms[i].Initialize(&params);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00460ad0
void RaceEventTable::ParseTimers(GolFileParser* p_parser)
{
	RaceEventTable* field = this;

	field->m_timerCount = p_parser->ReadBracketedCountAndLeftCurly();
	field->m_timers = new TimerResource[field->m_timerCount];
	if (field->m_timers == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < field->m_timerCount; i++) {
		p_parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(EvbTxtParser::e_event));

		TimerResource::InitParams params;
		params.m_eventId = p_parser->ReadInteger();

		GolFileParser::ParserTokenType token = p_parser->GetNextToken();
		params.m_triggerOnEnd = FALSE;
		if (token == EvbTxtParser::e_triggerOnEnd) {
			params.m_triggerOnEnd = TRUE;
			p_parser->ReadLeftCurly();
		}
		else if (token != GolFileParser::e_leftCurly) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		params.m_stateEventIds[0] = -1;
		params.m_eventTable = field;
		params.m_stateEventIds[1] = -1;
		params.m_holdEventId = -1;
		params.m_stateEventIds[2] = -1;
		params.m_durationMs = 0;

		for (token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly; token = p_parser->GetNextToken()) {
			switch (token) {
			case TimerResource::e_durationMs:
				params.m_durationMs = p_parser->ReadInteger();
				break;
			case TimerResource::e_holdEventId:
				params.m_holdEventId = p_parser->ReadInteger();
				break;
			case EvbTxtParser::e_event: {
				LegoS32 eventIndex = p_parser->GetNextToken() - EvbTxtParser::e_active;
				if (eventIndex) {
					eventIndex -= 2;
					if (eventIndex) {
						if (--eventIndex) {
							eventIndex = 3;
							p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
						}
						else {
							eventIndex = 2;
						}
					}
					else {
						eventIndex = 0;
					}
				}
				else {
					eventIndex = 1;
				}

				params.m_stateEventIds[eventIndex] = p_parser->ReadInteger();
				break;
			}
			default:
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}

		field->m_timers[i].Initialize(&params);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00460d10
void RaceEventTable::ParseNodeTransforms(GolFileParser* p_parser)
{
	RaceEventTable* field = this;

	field->m_nodeTransformCount = p_parser->ReadBracketedCountAndLeftCurly();
	field->m_nodeTransforms = new NodeTransformResource[field->m_nodeTransformCount];
	if (field->m_nodeTransforms == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < field->m_nodeTransformCount; i++) {
		p_parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(EvbTxtParser::e_event));

		NodeTransformResource::InitParams params;
		params.m_eventId = p_parser->ReadInteger();

		GolFileParser::ParserTokenType token = p_parser->GetNextToken();
		params.m_triggerOnEnd = FALSE;
		if (token == EvbTxtParser::e_triggerOnEnd) {
			params.m_triggerOnEnd = TRUE;
			p_parser->ReadLeftCurly();
		}
		else if (token != GolFileParser::e_leftCurly) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		params.m_stateEventIds[0] = -1;
		params.m_stateEventIds[1] = -1;
		params.m_stateEventIds[2] = -1;
		params.m_eventTable = field;
		params.m_boundedEntity = NULL;
		params.m_modelEntity = NULL;
		params.m_nodeIndex = 0;

		GolName name;
		for (token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly; token = p_parser->GetNextToken()) {
			switch (token) {
			case NodeTransformResource::e_triggerEntity:
				::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));

				params.m_boundedEntity = field->m_triggerDatabase->FindBoundedEntity(name);
				break;
			case EvbTxtParser::e_entityName:
				::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));

				params.m_modelEntity = field->m_trackDatabase->FindAnimatedEntity(name);
				if (params.m_modelEntity == NULL) {
					params.m_modelEntity = field->m_sharedDatabase->FindAnimatedEntity(name);
				}
				break;
			case EvbTxtParser::e_node:
				params.m_nodeIndex = p_parser->ReadInteger();
				break;
			case EvbTxtParser::e_event: {
				LegoS32 eventIndex;
				switch (p_parser->GetNextToken()) {
				case EvbTxtParser::e_active:
					eventIndex = 1;
					break;
				case EvbTxtParser::e_start:
					eventIndex = 0;
					break;
				case EvbTxtParser::e_end:
					eventIndex = 2;
					break;
				default:
					p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
					eventIndex = 3;
					break;
				}

				params.m_stateEventIds[eventIndex] = p_parser->ReadInteger();
				break;
			}
			default:
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}

		field->m_nodeTransforms[i].Initialize(&params);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00461070
void RaceEventTable::ParseModelDistances(GolFileParser* p_parser)
{
	RaceEventTable* field = this;

	field->m_modelDistanceCount = p_parser->ReadBracketedCountAndLeftCurly();
	field->m_modelDistances = new ModelDistanceResource[field->m_modelDistanceCount];
	if (field->m_modelDistances == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < field->m_modelDistanceCount; i++) {
		p_parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(EvbTxtParser::e_event));

		ModelDistanceResource::InitParams params;
		params.m_eventId = p_parser->ReadInteger();

		GolFileParser::ParserTokenType token = p_parser->GetNextToken();
		params.m_triggerOnEnd = FALSE;
		if (token == EvbTxtParser::e_triggerOnEnd) {
			params.m_triggerOnEnd = TRUE;
			p_parser->ReadLeftCurly();
		}
		else if (token != GolFileParser::e_leftCurly) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		params.m_stateEventIds[0] = -1;
		params.m_stateEventIds[1] = -1;
		params.m_stateEventIds[2] = -1;
		params.m_eventTable = field;
		params.m_modelEntity = NULL;
		params.m_noEnd = FALSE;
		params.m_hideWhenActive = FALSE;
		LegoBool32 useSharedDatabase = FALSE;
		LegoS32 eventIndex = 1;

		for (token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly; token = p_parser->GetNextToken()) {
			switch (token) {
			case EvbTxtParser::e_entityName: {
				GolName name;
				::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));

				if (!useSharedDatabase) {
					params.m_modelEntity = field->m_trackDatabase->FindModelEntity(name);
					if (params.m_modelEntity == NULL) {
						params.m_modelEntity = field->m_trackDatabase->FindAnimatedEntity(name);
					}
					if (params.m_modelEntity == NULL) {
						params.m_modelEntity = field->m_trackDatabase->FindCollidableEntity(name);
					}
				}
				else {
					params.m_modelEntity = field->m_sharedDatabase->FindModelEntity(name);
					if (params.m_modelEntity == NULL) {
						params.m_modelEntity = field->m_sharedDatabase->FindAnimatedEntity(name);
					}
					if (params.m_modelEntity == NULL) {
						params.m_modelEntity = field->m_sharedDatabase->FindCollidableEntity(name);
					}
				}
				break;
			}
			case EvbTxtParser::e_noEnd:
				params.m_noEnd = eventIndex;
				break;
			case EvbTxtParser::e_sharedDatabase:
				useSharedDatabase = eventIndex;
				break;
			case ModelDistanceResource::e_hideWhenActive:
				params.m_hideWhenActive = eventIndex;
				break;
			case EvbTxtParser::e_event: {
				LegoS32 tokenIndex = p_parser->GetNextToken() - EvbTxtParser::e_active;
				if (tokenIndex) {
					tokenIndex -= 2;
					if (tokenIndex) {
						if (--tokenIndex == 0) {
							eventIndex = 2;
						}
						else {
							eventIndex = 3;
							p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
						}
					}
					else {
						eventIndex = 0;
					}
				}

				params.m_stateEventIds[eventIndex] = p_parser->ReadInteger();
				eventIndex = 1;
				break;
			}
			default:
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}

		field->m_modelDistances[i].Initialize(&params);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00461430
void RaceEventTable::ParseLookTargets(GolFileParser* p_parser, LegoBool32 p_mirror)
{
	RaceEventTable* field = this;

	field->m_lookTargetCount = p_parser->ReadBracketedCountAndLeftCurly();
	field->m_lookTargets = new LookTargetResource[field->m_lookTargetCount];
	if (field->m_lookTargets == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	if (field->m_lookTargetCount) {
		LookTargetResource* resource = field->m_lookTargets;
		for (LegoU32 i = 0; i < field->m_lookTargetCount; i++, resource++) {
			p_parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(EvbTxtParser::e_event));

			LookTargetResource::InitParams params;
			params.m_eventId = p_parser->ReadInteger();

			p_parser->ReadLeftCurly();
			params.m_stateEventIds[0] = -1;
			params.m_stateEventIds[1] = -1;
			params.m_stateEventIds[2] = -1;
			params.m_eventTable = field;
			params.m_lookPosition.m_x = 0.0f;
			params.m_lookPosition.m_y = 0.0f;
			params.m_lookPosition.m_z = 0.0f;

			for (GolFileParser::ParserTokenType token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly;
				 token = p_parser->GetNextToken()) {
				switch (token) {
				case LookTargetResource::e_position:
					params.m_lookPosition.m_x = p_parser->ReadFloat();
					params.m_lookPosition.m_y = p_parser->ReadFloat();
					params.m_lookPosition.m_z = p_parser->ReadFloat();
					if (p_mirror) {
						params.m_lookPosition.m_y = -params.m_lookPosition.m_y;
					}
					break;
				case EvbTxtParser::e_event: {
					LegoS32 eventIndex = p_parser->GetNextToken() - EvbTxtParser::e_active;
					if (eventIndex) {
						eventIndex -= 2;
						if (eventIndex) {
							if (--eventIndex) {
								eventIndex = 3;
								p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
							}
							else {
								eventIndex = 2;
							}
						}
						else {
							eventIndex = 0;
						}
					}
					else {
						eventIndex = 1;
					}

					params.m_stateEventIds[eventIndex] = p_parser->ReadInteger();
					break;
				}
				default:
					p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
					break;
				}
			}

			resource->Initialize(&params);
		}
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00461670
void RaceEventTable::ParseExternalForces(GolFileParser* p_parser, LegoBool32 p_mirror)
{
	RaceEventTable* field = this;

	field->m_externalForceCount = p_parser->ReadBracketedCountAndLeftCurly();
	field->m_externalForces = new ExternalForceResource[field->m_externalForceCount];
	if (field->m_externalForces == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < field->m_externalForceCount; i++) {
		p_parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(EvbTxtParser::e_event));

		ExternalForceResource::InitParams params;
		params.m_eventId = p_parser->ReadInteger();

		GolFileParser::ParserTokenType token = p_parser->GetNextToken();
		params.m_triggerOnEnd = FALSE;
		if (token == EvbTxtParser::e_triggerOnEnd) {
			params.m_triggerOnEnd = TRUE;
			p_parser->ReadLeftCurly();
		}
		else if (token != GolFileParser::e_leftCurly) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		params.m_stateEventIds[0] = -1;
		params.m_stateEventIds[1] = -1;
		params.m_stateEventIds[2] = -1;
		params.m_eventTable = field;
		params.m_force.m_x = 0.0f;
		params.m_force.m_y = 0.0f;
		params.m_force.m_z = 0.0f;
		params.m_channel = 0;
		params.m_armEventId = -1;
		params.m_noEnd = FALSE;

		for (token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly; token = p_parser->GetNextToken()) {
			switch (token) {
			case ExternalForceResource::e_force:
				params.m_force.m_x = p_parser->ReadFloat();
				params.m_force.m_y = p_parser->ReadFloat();
				params.m_force.m_z = p_parser->ReadFloat();
				if (p_mirror) {
					params.m_force.m_y = -params.m_force.m_y;
				}
				break;
			case ExternalForceResource::e_channel:
				params.m_channel = p_parser->ReadInteger();
				break;
			case ExternalForceResource::e_armEventId:
				params.m_armEventId = p_parser->ReadInteger();
				break;
			case EvbTxtParser::e_event: {
				LegoS32 eventIndex = p_parser->GetNextToken() - EvbTxtParser::e_active;
				if (eventIndex) {
					eventIndex -= 2;
					if (eventIndex) {
						if (--eventIndex) {
							eventIndex = 3;
							p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
						}
						else {
							eventIndex = 2;
						}
					}
					else {
						eventIndex = 0;
					}
				}
				else {
					eventIndex = 1;
				}

				params.m_stateEventIds[eventIndex] = p_parser->ReadInteger();
				break;
			}
			default:
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}

		field->m_externalForces[i].Initialize(&params);
	}

	p_parser->ReadRightCurly();
}

// STUB: LEGORACERS 0x00461990
void RaceEventTable::ParseLapZones(GolFileParser* p_parser)
{
	RaceEventTable* field = this;

	field->m_lapZoneCount = p_parser->ReadBracketedCountAndLeftCurly();
	field->m_lapZones = new LapZoneResource[field->m_lapZoneCount];
	if (field->m_lapZones == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < field->m_lapZoneCount; i++) {
		p_parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(EvbTxtParser::e_event));

		LapZoneResource::InitParams params;
		params.m_eventId = p_parser->ReadInteger();

		p_parser->ReadLeftCurly();
		params.m_stateEventIds[0] = -1;
		params.m_stateEventIds[1] = -1;
		params.m_eventTable = field;
		params.m_stateEventIds[2] = -1;
		params.m_zone = 1;

		for (GolFileParser::ParserTokenType token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly;
			 token = p_parser->GetNextToken()) {
			switch (token) {
			case EvbTxtParser::e_start:
				params.m_zone = 0;
				break;
			case EvbTxtParser::e_end:
				params.m_zone = 2;
				break;
			case EvbTxtParser::e_event: {
				LegoS32 eventIndex = p_parser->GetNextToken() - EvbTxtParser::e_active;
				if (eventIndex) {
					eventIndex -= 2;
					if (eventIndex) {
						if (--eventIndex) {
							eventIndex = 3;
							p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
						}
						else {
							eventIndex = 2;
						}
					}
					else {
						eventIndex = 0;
					}
				}
				else {
					eventIndex = 1;
				}

				params.m_stateEventIds[eventIndex] = p_parser->ReadInteger();
				break;
			}
			default:
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}

		field->m_lapZones[i].Initialize(&params);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00461ba0
void RaceEventTable::Destroy()
{
	if (m_sounds) {
		delete[] m_sounds;
		m_sounds = NULL;
	}

	if (m_partAnimations) {
		delete[] m_partAnimations;
		m_partAnimations = NULL;
	}

	if (m_materialAnimations) {
		delete[] m_materialAnimations;
		m_materialAnimations = NULL;
	}

	if (m_particles) {
		delete[] m_particles;
		m_particles = NULL;
	}

	if (m_eventLinks) {
		delete[] m_eventLinks;
		m_eventLinks = NULL;
	}

	if (m_skyStates) {
		delete[] m_skyStates;
		m_skyStates = NULL;
	}

	if (m_timers) {
		delete[] m_timers;
		m_timers = NULL;
	}

	if (m_nodeTransforms) {
		delete[] m_nodeTransforms;
		m_nodeTransforms = NULL;
	}

	if (m_colorTransforms) {
		delete[] m_colorTransforms;
		m_colorTransforms = NULL;
	}

	if (m_lapZones) {
		delete[] m_lapZones;
		m_lapZones = NULL;
	}

	if (m_modelDistances) {
		delete[] m_modelDistances;
		m_modelDistances = NULL;
	}

	if (m_lookTargets) {
		delete[] m_lookTargets;
		m_lookTargets = NULL;
	}

	if (m_externalForces) {
		delete[] m_externalForces;
		m_externalForces = NULL;
	}

	m_trackDatabase = 0;
	m_sharedDatabase = 0;
	m_triggerDatabase = 0;
	m_materialAnimationDatabase = 0;
	m_soundSource = 0;
	m_hazardManager = 0;
	m_skyState = 0;
	m_targetPoints = 0;
}

// FUNCTION: LEGORACERS 0x00461cc0
void RaceEventTable::Update(LegoU32 p_elapsedMs)
{
	LegoU32 i;

	if (m_sounds) {
		for (i = 0; i < m_soundCount; i++) {
			m_sounds[i].Update(p_elapsedMs);
		}
	}

	if (m_partAnimations) {
		for (i = 0; i < m_partAnimationCount; i++) {
			m_partAnimations[i].Update(p_elapsedMs);
		}
	}

	if (m_materialAnimations) {
		for (i = 0; i < m_materialAnimationCount; i++) {
			m_materialAnimations[i].Update(p_elapsedMs);
		}
	}

	if (m_particles) {
		for (i = 0; i < m_particleCount; i++) {
			m_particles[i].Update(p_elapsedMs);
		}
	}

	if (m_skyStates) {
		for (i = 0; i < m_skyStateCount; i++) {
			m_skyStates[i].Update(p_elapsedMs);
		}
	}

	if (m_timers) {
		for (i = 0; i < m_timerCount; i++) {
			m_timers[i].Update(p_elapsedMs);
		}
	}

	if (m_nodeTransforms) {
		for (i = 0; i < m_nodeTransformCount; i++) {
			m_nodeTransforms[i].Update(p_elapsedMs);
		}
	}

	if (m_colorTransforms) {
		for (i = 0; i < m_colorTransformCount; i++) {
			m_colorTransforms[i].Update(p_elapsedMs);
		}
	}

	if (m_lapZones) {
		for (i = 0; i < m_lapZoneCount; i++) {
			m_lapZones[i].Update(p_elapsedMs);
		}
	}

	if (m_modelDistances) {
		for (i = 0; i < m_modelDistanceCount; i++) {
			m_modelDistances[i].Update(p_elapsedMs);
		}
	}

	if (m_lookTargets) {
		for (i = 0; i < m_lookTargetCount; i++) {
			m_lookTargets[i].Update(p_elapsedMs);
		}
	}

	if (m_externalForces) {
		LegoU32 count = m_externalForceCount;

		for (i = 0; i < count; i++) {
			m_externalForces[i].Update(p_elapsedMs);
			count = m_externalForceCount;
		}
	}
}

// FUNCTION: LEGORACERS 0x00461ef0
LegoU32 RaceEventTable::StartEventsAt(undefined4 p_eventId, GolVec3* p_position)
{
	if (m_sounds) {
		for (LegoU32 i = 0; i < m_soundCount; i++) {
			if (m_sounds[i].m_eventId == p_eventId) {
				m_sounds[i].OnEventStart(p_position);
			}
		}
	}

	if (m_partAnimations) {
		for (LegoU32 i = 0; i < m_partAnimationCount; i++) {
			if (m_partAnimations[i].m_eventId == p_eventId) {
				m_partAnimations[i].OnEventStart(p_position);
			}
		}
	}

	if (m_materialAnimations) {
		for (LegoU32 i = 0; i < m_materialAnimationCount; i++) {
			if (m_materialAnimations[i].m_eventId == p_eventId) {
				m_materialAnimations[i].OnEventStart(p_position);
			}
		}
	}

	if (m_particles) {
		for (LegoU32 i = 0; i < m_particleCount; i++) {
			if (m_particles[i].m_eventId == p_eventId) {
				m_particles[i].OnEventStart(p_position);
			}
		}
	}

	if (m_skyStates) {
		for (LegoU32 i = 0; i < m_skyStateCount; i++) {
			if (m_skyStates[i].m_eventId == p_eventId) {
				m_skyStates[i].OnEventStart(p_position);
			}
		}
	}

	if (m_timers) {
		for (LegoU32 i = 0; i < m_timerCount; i++) {
			if (m_timers[i].m_eventId == p_eventId) {
				m_timers[i].OnEventStart(p_position);
			}

			if (m_timers[i].m_holdEventId == p_eventId) {
				m_timers[i].m_timerFlags |= 1;
			}
		}
	}

	if (m_nodeTransforms) {
		for (LegoU32 i = 0; i < m_nodeTransformCount; i++) {
			if (m_nodeTransforms[i].m_eventId == p_eventId) {
				m_nodeTransforms[i].OnEventStart(p_position);
			}
		}
	}

	if (m_modelDistances) {
		for (LegoU32 i = 0; i < m_modelDistanceCount; i++) {
			if (m_modelDistances[i].m_eventId == p_eventId) {
				m_modelDistances[i].OnEventStart(p_position);
			}
		}
	}

	if (m_eventLinks) {
		for (LegoU32 i = 0; i < m_eventLinkCount; i++) {
			if (m_eventLinks[i].m_eventId == p_eventId) {
				ForceEvents(m_eventLinks[i].m_forcedEventId);
			}
		}
	}

	if (m_externalForces) {
		for (LegoU32 i = 0; i < m_externalForceCount; i++) {
			if (m_externalForces[i].m_armEventId == p_eventId) {
				m_externalForces[i].m_forceFlags |= 1;
			}
		}
	}

	m_hazardManager->NotifyEventStart(p_eventId, p_position);
	return m_targetPoints->DisableTargetPoints(p_eventId);
}

// FUNCTION: LEGORACERS 0x00462140
void RaceEventTable::EndEventsAt(undefined4 p_eventId, GolVec3* p_position)
{
	if (m_sounds) {
		for (LegoU32 i = 0; i < m_soundCount; i++) {
			if (m_sounds[i].m_eventId == p_eventId) {
				m_sounds[i].OnEventEnd(p_position);
			}
		}
	}

	if (m_partAnimations) {
		for (LegoU32 i = 0; i < m_partAnimationCount; i++) {
			if (m_partAnimations[i].m_eventId == p_eventId) {
				m_partAnimations[i].OnEventEnd(p_position);
			}
		}
	}

	if (m_materialAnimations) {
		for (LegoU32 i = 0; i < m_materialAnimationCount; i++) {
			if (m_materialAnimations[i].m_eventId == p_eventId) {
				m_materialAnimations[i].OnEventEnd(p_position);
			}
		}
	}

	if (m_particles) {
		for (LegoU32 i = 0; i < m_particleCount; i++) {
			if (m_particles[i].m_eventId == p_eventId) {
				m_particles[i].OnEventEnd(p_position);
			}
		}
	}

	if (m_skyStates) {
		for (LegoU32 i = 0; i < m_skyStateCount; i++) {
			if (m_skyStates[i].m_eventId == p_eventId) {
				m_skyStates[i].OnEventEnd(p_position);
			}
		}
	}

	if (m_timers) {
		for (LegoU32 i = 0; i < m_timerCount; i++) {
			if (m_timers[i].m_eventId == p_eventId) {
				m_timers[i].OnEventEnd(p_position);
			}

			if (m_timers[i].m_holdEventId == p_eventId) {
				m_timers[i].m_timerFlags &= ~1;
			}
		}
	}

	if (m_nodeTransforms) {
		for (LegoU32 i = 0; i < m_nodeTransformCount; i++) {
			if (m_nodeTransforms[i].m_eventId == p_eventId) {
				m_nodeTransforms[i].OnEventEnd(p_position);
			}
		}
	}

	if (m_modelDistances) {
		for (LegoU32 i = 0; i < m_modelDistanceCount; i++) {
			if (m_modelDistances[i].m_eventId == p_eventId) {
				m_modelDistances[i].OnEventEnd(p_position);
			}
		}
	}

	if (m_externalForces) {
		for (LegoU32 i = 0; i < m_externalForceCount; i++) {
			if (m_externalForces[i].m_armEventId == p_eventId) {
				m_externalForces[i].m_forceFlags &= ~1;
			}
		}
	}

	m_hazardManager->NotifyEventEnd(p_eventId, p_position);
}

// FUNCTION: LEGORACERS 0x00462350
void RaceEventTable::ForceEvents(undefined4 p_eventId)
{
	if (m_sounds) {
		for (LegoU32 i = 0; i < m_soundCount; i++) {
			if (m_sounds[i].m_eventId == p_eventId) {
				m_sounds[i].m_state = 5;
			}
		}
	}

	if (m_partAnimations) {
		for (LegoU32 i = 0; i < m_partAnimationCount; i++) {
			if (m_partAnimations[i].m_eventId == p_eventId) {
				m_partAnimations[i].m_state = 5;
			}
		}
	}

	if (m_materialAnimations) {
		for (LegoU32 i = 0; i < m_materialAnimationCount; i++) {
			if (m_materialAnimations[i].m_eventId == p_eventId) {
				m_materialAnimations[i].m_state = 5;
			}
		}
	}

	if (m_particles) {
		for (LegoU32 i = 0; i < m_particleCount; i++) {
			if (m_particles[i].m_eventId == p_eventId) {
				m_particles[i].m_state = 5;
			}
		}
	}

	if (m_skyStates) {
		for (LegoU32 i = 0; i < m_skyStateCount; i++) {
			if (m_skyStates[i].m_eventId == p_eventId) {
				m_skyStates[i].m_state = 5;
			}
		}
	}

	if (m_timers) {
		for (LegoU32 i = 0; i < m_timerCount; i++) {
			if (m_timers[i].m_eventId == p_eventId) {
				m_timers[i].m_state = 5;
			}
		}
	}

	if (m_nodeTransforms) {
		for (LegoU32 i = 0; i < m_nodeTransformCount; i++) {
			if (m_nodeTransforms[i].m_eventId == p_eventId) {
				m_nodeTransforms[i].m_state = 5;
			}
		}
	}

	if (m_colorTransforms) {
		for (LegoU32 i = 0; i < m_colorTransformCount; i++) {
			if (m_colorTransforms[i].m_eventId == p_eventId) {
				m_colorTransforms[i].m_state = 5;
			}
		}
	}

	if (m_lapZones) {
		for (LegoU32 i = 0; i < m_lapZoneCount; i++) {
			if (m_lapZones[i].m_eventId == p_eventId) {
				m_lapZones[i].m_state = 5;
			}
		}
	}

	if (m_modelDistances) {
		for (LegoU32 i = 0; i < m_modelDistanceCount; i++) {
			if (m_modelDistances[i].m_eventId == p_eventId) {
				m_modelDistances[i].m_state = 5;
			}
		}
	}

	if (m_lookTargets) {
		for (LegoU32 i = 0; i < m_lookTargetCount; i++) {
			if (m_lookTargets[i].m_eventId == p_eventId) {
				m_lookTargets[i].m_state = 5;
			}
		}
	}

	if (m_externalForces) {
		for (LegoU32 i = 0; i < m_externalForceCount; i++) {
			if (m_externalForces[i].m_eventId == p_eventId) {
				m_externalForces[i].m_state = 5;
			}
		}
	}

	m_hazardManager->ForceDeactivate(p_eventId);
}

// FUNCTION: LEGORACERS 0x00462580
void RaceEventTable::FireEventsAt(undefined4 p_startId, undefined4 p_endId, GolVec3* p_position)
{
	if (m_sounds) {
		for (LegoU32 i = 0; i < m_soundCount; i++) {
			if (m_sounds[i].m_eventId == p_startId) {
				m_sounds[i].OnEventStart(p_position);
			}

			if (m_sounds[i].m_eventId == p_endId) {
				m_sounds[i].OnEventEnd(p_position);
			}
		}
	}

	if (m_partAnimations) {
		for (LegoU32 i = 0; i < m_partAnimationCount; i++) {
			if (m_partAnimations[i].m_eventId == p_startId) {
				m_partAnimations[i].OnEventStart(p_position);
			}

			if (m_partAnimations[i].m_eventId == p_endId) {
				m_partAnimations[i].OnEventEnd(p_position);
			}
		}
	}

	if (m_materialAnimations) {
		for (LegoU32 i = 0; i < m_materialAnimationCount; i++) {
			if (m_materialAnimations[i].m_eventId == p_startId) {
				m_materialAnimations[i].OnEventStart(p_position);
			}

			if (m_materialAnimations[i].m_eventId == p_endId) {
				m_materialAnimations[i].OnEventEnd(p_position);
			}
		}
	}

	if (m_particles) {
		for (LegoU32 i = 0; i < m_particleCount; i++) {
			if (m_particles[i].m_eventId == p_startId) {
				m_particles[i].OnEventStart(p_position);
			}

			if (m_particles[i].m_eventId == p_endId) {
				m_particles[i].OnEventEnd(p_position);
			}
		}
	}

	if (m_skyStates) {
		for (LegoU32 i = 0; i < m_skyStateCount; i++) {
			if (m_skyStates[i].m_eventId == p_startId) {
				m_skyStates[i].OnEventStart(p_position);
			}

			if (m_skyStates[i].m_eventId == p_endId) {
				m_skyStates[i].OnEventEnd(p_position);
			}
		}
	}

	if (m_timers) {
		for (LegoU32 i = 0; i < m_timerCount; i++) {
			if (m_timers[i].m_eventId == p_startId) {
				m_timers[i].OnEventStart(p_position);
			}

			if (m_timers[i].m_holdEventId == p_startId) {
				m_timers[i].m_timerFlags |= 1;
			}

			if (m_timers[i].m_eventId == p_endId) {
				m_timers[i].OnEventEnd(p_position);
			}

			if (m_timers[i].m_holdEventId == p_endId) {
				m_timers[i].m_timerFlags &= ~1;
			}
		}
	}

	if (m_nodeTransforms) {
		for (LegoU32 i = 0; i < m_nodeTransformCount; i++) {
			if (m_nodeTransforms[i].m_eventId == p_startId) {
				m_nodeTransforms[i].OnEventStart(p_position);
			}

			if (m_nodeTransforms[i].m_eventId == p_endId) {
				m_nodeTransforms[i].OnEventEnd(p_position);
			}
		}
	}

	if (m_modelDistances) {
		for (LegoU32 i = 0; i < m_modelDistanceCount; i++) {
			if (m_modelDistances[i].m_eventId == p_startId) {
				m_modelDistances[i].OnEventStart(p_position);
			}

			if (m_modelDistances[i].m_eventId == p_endId) {
				m_modelDistances[i].OnEventEnd(p_position);
			}
		}
	}

	if (m_eventLinks) {
		for (LegoU32 i = 0; i < m_eventLinkCount; i++) {
			if (m_eventLinks[i].m_eventId == p_startId) {
				ForceEvents(m_eventLinks[i].m_forcedEventId);
			}
		}
	}

	if (m_externalForces) {
		for (LegoU32 i = 0; i < m_externalForceCount; i++) {
			if (m_externalForces[i].m_armEventId == p_startId) {
				m_externalForces[i].m_forceFlags |= 1;
			}

			if (m_externalForces[i].m_armEventId == p_endId) {
				m_externalForces[i].m_forceFlags &= ~1;
			}
		}
	}

	m_hazardManager->NotifyEventPair(p_startId, p_endId, p_position);
}

// FUNCTION: LEGORACERS 0x004628c0
void RaceEventTable::StartEventsForRacer(undefined4 p_eventId, Racer* p_racer)
{
	if (m_colorTransforms) {
		for (LegoU32 i = 0; i < m_colorTransformCount; i++) {
			if (m_colorTransforms[i].m_eventId == p_eventId) {
				m_colorTransforms[i].ForceEventStart(p_racer);
			}
		}
	}

	if (m_lapZones) {
		for (LegoU32 i = 0; i < m_lapZoneCount; i++) {
			if (m_lapZones[i].m_eventId == p_eventId) {
				m_lapZones[i].ForceEventStart(p_racer);
			}
		}
	}

	if (m_lookTargets) {
		for (LegoU32 i = 0; i < m_lookTargetCount; i++) {
			if (m_lookTargets[i].m_eventId == p_eventId) {
				m_lookTargets[i].ForceEventStart(p_racer);
			}
		}
	}

	if (m_externalForces) {
		for (LegoU32 i = 0; i < m_externalForceCount; i++) {
			if (m_externalForces[i].m_eventId == p_eventId) {
				m_externalForces[i].ForceEventStart(p_racer);
			}
		}
	}

	if (p_racer) {
		m_hazardManager->DispatchEventStart(p_eventId, p_racer);
	}
}

// FUNCTION: LEGORACERS 0x004629d0
void RaceEventTable::EndEventsForRacer(undefined4 p_eventId, Racer* p_racer)
{
	if (m_colorTransforms) {
		for (LegoU32 i = 0; i < m_colorTransformCount; i++) {
			if (m_colorTransforms[i].m_eventId == p_eventId) {
				m_colorTransforms[i].ForceEventEnd(p_racer);
			}
		}
	}

	if (m_lapZones) {
		for (LegoU32 i = 0; i < m_lapZoneCount; i++) {
			if (m_lapZones[i].m_eventId == p_eventId) {
				m_lapZones[i].ForceEventEnd(p_racer);
			}
		}
	}

	if (m_lookTargets) {
		for (LegoU32 i = 0; i < m_lookTargetCount; i++) {
			if (m_lookTargets[i].m_eventId == p_eventId) {
				m_lookTargets[i].ForceEventEnd(p_racer);
			}
		}
	}

	if (m_externalForces) {
		for (LegoU32 i = 0; i < m_externalForceCount; i++) {
			if (m_externalForces[i].m_eventId == p_eventId) {
				m_externalForces[i].ForceEventEnd(p_racer);
			}
		}
	}

	if (p_racer) {
		m_hazardManager->DispatchEventEnd(p_eventId, p_racer);
	}
}

// FUNCTION: LEGORACERS 0x00462ae0
void RaceEventTable::FireEventsForRacer(undefined4 p_startId, undefined4 p_endId, Racer* p_racer)
{
	if (m_colorTransforms) {
		for (LegoU32 i = 0; i < m_colorTransformCount; i++) {
			if (m_colorTransforms[i].m_eventId == p_startId) {
				m_colorTransforms[i].ForceEventStart(p_racer);
			}

			if (m_colorTransforms[i].m_eventId == p_endId) {
				m_colorTransforms[i].ForceEventEnd(p_racer);
			}
		}
	}

	if (m_lapZones) {
		for (LegoU32 i = 0; i < m_lapZoneCount; i++) {
			if (m_lapZones[i].m_eventId == p_startId) {
				m_lapZones[i].ForceEventStart(p_racer);
			}

			if (m_lapZones[i].m_eventId == p_endId) {
				m_lapZones[i].ForceEventEnd(p_racer);
			}
		}
	}

	if (m_lookTargets) {
		for (LegoU32 i = 0; i < m_lookTargetCount; i++) {
			if (m_lookTargets[i].m_eventId == p_startId) {
				m_lookTargets[i].ForceEventStart(p_racer);
			}

			if (m_lookTargets[i].m_eventId == p_endId) {
				m_lookTargets[i].ForceEventEnd(p_racer);
			}
		}
	}

	if (m_externalForces) {
		for (LegoU32 i = 0; i < m_externalForceCount; i++) {
			if (m_externalForces[i].m_eventId == p_startId) {
				m_externalForces[i].ForceEventStart(p_racer);
			}

			if (m_externalForces[i].m_eventId == p_endId) {
				m_externalForces[i].ForceEventEnd(p_racer);
			}
		}
	}

	if (p_racer) {
		m_hazardManager->DispatchEventPair(p_startId, p_endId, p_racer);
	}
}
// FUNCTION: LEGORACERS 0x00462c60
void RaceEventTable::ForceAllEvents()
{
	LegoU32 i;

	if (m_sounds) {
		for (i = 0; i < m_soundCount; i++) {
			m_sounds[i].SetState(RaceEventResource::c_stateEndPending);
		}
	}

	if (m_partAnimations) {
		for (i = 0; i < m_partAnimationCount; i++) {
			m_partAnimations[i].SetState(RaceEventResource::c_stateEndPending);
		}
	}

	if (m_materialAnimations) {
		for (i = 0; i < m_materialAnimationCount; i++) {
			m_materialAnimations[i].SetState(RaceEventResource::c_stateEndPending);
		}
	}

	if (m_particles) {
		for (i = 0; i < m_particleCount; i++) {
			m_particles[i].SetState(RaceEventResource::c_stateEndPending);
		}
	}

	if (m_skyStates) {
		for (i = 0; i < m_skyStateCount; i++) {
			m_skyStates[i].SetState(RaceEventResource::c_stateEndPending);
		}
	}

	if (m_timers) {
		for (i = 0; i < m_timerCount; i++) {
			m_timers[i].SetState(RaceEventResource::c_stateEndPending);
		}
	}

	if (m_nodeTransforms) {
		for (i = 0; i < m_nodeTransformCount; i++) {
			m_nodeTransforms[i].SetState(RaceEventResource::c_stateEndPending);
		}
	}

	if (m_modelDistances) {
		for (i = 0; i < m_modelDistanceCount; i++) {
			m_modelDistances[i].SetState(RaceEventResource::c_stateEndPending);
		}
	}

	Update(0);
}

// FUNCTION: LEGORACERS 0x00462da0
void RaceEventTable::EndAllForRacer(Racer* p_racer)
{
	LegoU32 i;

	if (m_colorTransforms) {
		for (i = 0; i < m_colorTransformCount; i++) {
			RaceEventResource* resource = &m_colorTransforms[i];
			resource->ForceEventEnd(p_racer);
		}
	}

	if (m_lapZones) {
		for (i = 0; i < m_lapZoneCount; i++) {
			RaceEventResource* resource = &m_lapZones[i];
			resource->ForceEventEnd(p_racer);
		}
	}

	if (m_lookTargets) {
		for (i = 0; i < m_lookTargetCount; i++) {
			RaceEventResource* resource = &m_lookTargets[i];
			resource->ForceEventEnd(p_racer);
		}
	}

	if (m_externalForces) {
		LegoU32 count = m_externalForceCount;

		for (i = 0; i < count; i++) {
			RaceEventResource* resource = &m_externalForces[i];
			resource->ForceEventEnd(p_racer);
			count = m_externalForceCount;
		}
	}
}
