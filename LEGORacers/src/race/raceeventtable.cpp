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
#include "race/racesession.h"
#include "world/golworlddatabase.h"

DECOMP_SIZE_ASSERT(RaceEventTable, 0x90)
DECOMP_SIZE_ASSERT(RaceEventTable::EvbTxtParser, 0x1fc)
DECOMP_SIZE_ASSERT(RaceEventTable::Params, 0x34)
DECOMP_SIZE_ASSERT(RaceEventTable::EventLink, 0x08)
DECOMP_SIZE_ASSERT(RaceEventTable::Resource, 0x20)
DECOMP_SIZE_ASSERT(RaceEventTable::LapZoneResource::InitParams, 0x18)
DECOMP_SIZE_ASSERT(RaceEventTable::LapZoneResource, 0x24)
DECOMP_SIZE_ASSERT(RaceEventTable::LookTargetResource::InitParams, 0x20)
DECOMP_SIZE_ASSERT(RaceEventTable::LookTargetResource, 0x2c)
DECOMP_SIZE_ASSERT(RaceEventTable::TimerResource::InitParams, 0x20)
DECOMP_SIZE_ASSERT(RaceEventTable::TimerResource, 0x30)
DECOMP_SIZE_ASSERT(RaceEventTable::MaterialAnimationResource::InitParams, 0x38)
DECOMP_SIZE_ASSERT(RaceEventTable::MaterialAnimationResource, 0x34)
DECOMP_SIZE_ASSERT(RaceEventTable::PartAnimationResource::InitParams, 0x3c)
DECOMP_SIZE_ASSERT(RaceEventTable::PartAnimationResource, 0x34)
DECOMP_SIZE_ASSERT(RaceEventTable::ModelDistanceResource::InitParams, 0x24)
DECOMP_SIZE_ASSERT(RaceEventTable::ModelDistanceResource, 0x34)
DECOMP_SIZE_ASSERT(RaceEventTable::NodeTransformResource::InitParams, 0x24)
DECOMP_SIZE_ASSERT(RaceEventTable::NodeTransformResource, 0x2c)
DECOMP_SIZE_ASSERT(RaceEventTable::SkyStateResource::InitParams, 0x2c)
DECOMP_SIZE_ASSERT(RaceEventTable::SkyStateResource, 0x34)
DECOMP_SIZE_ASSERT(RaceEventTable::ExternalForceResource::InitParams, 0x30)
DECOMP_SIZE_ASSERT(RaceEventTable::ExternalForceResource, 0x38)
DECOMP_SIZE_ASSERT(RaceEventTable::ColorTransformResource, 0x48)
DECOMP_SIZE_ASSERT(RaceEventTable::SoundResource::InitParams, 0x4c)
DECOMP_SIZE_ASSERT(RaceEventTable::SoundResource, 0x5c)
DECOMP_SIZE_ASSERT(RaceEventTable::ParticleResource::InitParams, 0x5c)
DECOMP_SIZE_ASSERT(RaceEventTable::ParticleResource, 0x64)

extern LegoU16 g_randomTable[1024];
extern LegoU32 g_randomTableIndex;

// FUNCTION: LEGORACERS 0x0045c330 FOLDED
LegoU32 RaceEventTable::MaterialAnimationResource::GetKind()
{
	return 2;
}

// FUNCTION: LEGORACERS 0x0045e150
RaceEventTable::SkyStateResource::SkyStateResource()
{
	ClearFields();
	m_flags0x1c = 0;
}

// FUNCTION: LEGORACERS 0x0045e1a0
RaceEventTable::SkyStateResource::~SkyStateResource()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0045e1f0
void RaceEventTable::SkyStateResource::ClearFields()
{
	m_skyState = NULL;
	m_unk0x24[0] = '\0';
	m_unk0x2c = 0;
	m_flags0x30 = 0;
}

// FUNCTION: LEGORACERS 0x0045e200
void RaceEventTable::SkyStateResource::Initialize(InitParams* p_params)
{
	if (m_state0x18) {
		Destroy();
	}

	m_eventId = p_params->m_unk0x00;
	LegoS32* eventId = p_params->m_stateEventIds;
	LegoU32 i;
	for (i = 0; i < sizeOfArray(m_stateEventIds); i++) {
		m_stateEventIds[i] = *eventId++;
	}

	m_eventTable = p_params->m_eventTable;
	m_skyState = p_params->m_unk0x14;
	m_unk0x2c = p_params->m_unk0x20;
	m_flags0x30 = p_params->m_flags0x28;
	::strncpy(m_unk0x24, p_params->m_unk0x18, sizeof(m_unk0x24));
	if (p_params->m_unk0x24) {
		m_flags0x1c |= c_flags0x1cBit2;
	}

	m_state0x18 = c_state0x18One;
	m_flags0x1c &= ~c_flags0x1cBit5;
}

// FUNCTION: LEGORACERS 0x0045e280
void RaceEventTable::SkyStateResource::Destroy()
{
	OnEnd();
	ClearFields();
	Reset();
}

// FUNCTION: LEGORACERS 0x0045e2a0
void RaceEventTable::SkyStateResource::OnStartAt(GolVec3*)
{
	if (m_unk0x24[0]) {
		m_skyState->StartTransition(m_unk0x24, m_unk0x2c);
	}

	if (m_flags0x30 & c_flags0x30Bit0) {
		m_skyState->m_hideFlags &= ~RaceSkyState::c_hideDome;
	}

	if (m_flags0x30 & c_flags0x30Bit1) {
		m_skyState->m_hideFlags |= RaceSkyState::c_hideDome;
	}

	if (m_flags0x30 & c_flags0x30Bit2) {
		m_skyState->m_hideFlags &= ~RaceSkyState::c_hideSkyWorld;
	}

	if (m_flags0x30 & c_flags0x30Bit3) {
		m_skyState->m_hideFlags |= RaceSkyState::c_hideSkyWorld;
	}

	NotifyStateChange(m_state0x18, 1);
	m_state0x18 = c_state0x18Five;
}

// FUNCTION: LEGORACERS 0x0045e320
void RaceEventTable::SkyStateResource::OnEnd()
{
	NotifyStateChange(m_state0x18, 3);
	m_state0x18 = c_state0x18One;
	m_flags0x1c &= ~c_flags0x1cBit5;
}

// FUNCTION: LEGORACERS 0x0045e340
LegoU32 RaceEventTable::SkyStateResource::GetKind()
{
	return 5;
}

// FUNCTION: LEGORACERS 0x0045e5e0
RaceEventTable::LookTargetResource::LookTargetResource()
{
	m_lookPosition.m_x = 0.0f;
	m_lookPosition.m_y = 0.0f;
	m_lookPosition.m_z = 0.0f;
}

// FUNCTION: LEGORACERS 0x0045e600
RaceEventTable::LookTargetResource::~LookTargetResource()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0045e650
void RaceEventTable::LookTargetResource::Initialize(InitParams* p_params)
{
	if (m_state0x18) {
		Destroy();
	}

	m_eventId = p_params->m_unk0x00;
	LegoS32* eventId = p_params->m_stateEventIds;
	LegoU32 i;
	for (i = 0; i < sizeOfArray(m_stateEventIds); i++) {
		m_stateEventIds[i] = *eventId++;
	}

	m_eventTable = p_params->m_eventTable;
	m_lookPosition.m_x = p_params->m_unk0x14.m_x;
	m_lookPosition.m_y = p_params->m_unk0x14.m_y;
	m_lookPosition.m_z = p_params->m_unk0x14.m_z;
	m_state0x18 = c_state0x18Four;
}

// FUNCTION: LEGORACERS 0x0045e6b0
void RaceEventTable::LookTargetResource::Destroy()
{
	m_lookPosition.m_x = 0.0f;
	m_lookPosition.m_y = 0.0f;
	m_lookPosition.m_z = 0.0f;
	Reset();
}

// FUNCTION: LEGORACERS 0x0045e6c0
void RaceEventTable::LookTargetResource::OnStartForRacer(RaceState::Racer* p_racer)
{
	NotifyStateChange(1, 1);
	if (p_racer) {
		p_racer->SetLookTarget(&m_lookPosition);
	}
}

// FUNCTION: LEGORACERS 0x0045e6f0
void RaceEventTable::LookTargetResource::OnEndForRacer(RaceState::Racer* p_racer)
{
	NotifyStateChange(m_state0x18, 3);
	if (p_racer) {
		p_racer->ClearLookTarget();
	}

	m_state0x18 = c_state0x18Four;
}

// FUNCTION: LEGORACERS 0x0045e720
LegoU32 RaceEventTable::LookTargetResource::GetKind()
{
	return 11;
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RaceEventTable::LookTargetResource::FUN_004513d0(undefined4)
{
}

// FUNCTION: LEGORACERS 0x0045e730
RaceEventTable::TimerResource::TimerResource()
{
	ClearFields();
	m_flags0x1c = 0;
}

// FUNCTION: LEGORACERS 0x0045e780
RaceEventTable::TimerResource::~TimerResource()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0045e7d0
void RaceEventTable::TimerResource::ClearFields()
{
	m_holdEventId = -1;
	m_durationMs = 0;
	m_remainingMs = 0;
	m_flags0x2c = 0;
}

// FUNCTION: LEGORACERS 0x0045e7f0
void RaceEventTable::TimerResource::Initialize(InitParams* p_params)
{
	if (m_state0x18) {
		Destroy();
	}

	m_eventId = p_params->m_unk0x00;
	LegoS32* eventId = p_params->m_stateEventIds;
	LegoU32 i;
	for (i = 0; i < sizeOfArray(m_stateEventIds); i++) {
		m_stateEventIds[i] = *eventId++;
	}

	m_eventTable = p_params->m_eventTable;
	m_holdEventId = p_params->m_unk0x14;
	m_durationMs = p_params->m_unk0x18;
	m_remainingMs = 0;
	if (p_params->m_unk0x1c) {
		m_flags0x1c |= c_flags0x1cBit2;
	}

	m_state0x18 = c_state0x18Four;
}

// FUNCTION: LEGORACERS 0x0045e860
void RaceEventTable::TimerResource::Destroy()
{
	OnEnd();
	ClearFields();
	Reset();
}

// FUNCTION: LEGORACERS 0x0045e880
void RaceEventTable::TimerResource::OnStartAt(GolVec3*)
{
	m_remainingMs = m_durationMs;
	NotifyStateChange(1, 1);
	m_state0x18 = c_state0x18Three;
}

// FUNCTION: LEGORACERS 0x0045e8a0
void RaceEventTable::TimerResource::OnEnd()
{
	if (m_remainingMs <= 0 && !(m_flags0x2c & 1)) {
		NotifyStateChange(m_state0x18, 3);
		m_state0x18 = c_state0x18Four;
	}
}

// FUNCTION: LEGORACERS 0x0045e8d0
void RaceEventTable::TimerResource::Update(LegoU32 p_elapsedMs)
{
	Resource::Update(p_elapsedMs);
	if (m_state0x18 != c_state0x18Four) {
		if (p_elapsedMs > m_remainingMs) {
			m_remainingMs = 0;
		}
		else {
			m_remainingMs -= p_elapsedMs;
		}

		if (!m_remainingMs) {
			OnEnd();
		}
	}
}

// FUNCTION: LEGORACERS 0x0045e910
LegoU32 RaceEventTable::TimerResource::GetKind()
{
	return 6;
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RaceEventTable::TimerResource::FUN_004513d0(undefined4)
{
}

// FUNCTION: LEGORACERS 0x0044f580 FOLDED
LegoU32 RaceEventTable::ParticleResource::GetKind()
{
	return 3;
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RaceEventTable::ParticleResource::FUN_004513d0(undefined4)
{
}

// FUNCTION: LEGORACERS 0x0045e920
RaceEventTable::ParticleResource::ParticleResource()
{
	ClearFields();
	m_flags0x1c = 0;
}

// FUNCTION: LEGORACERS 0x0045e970
RaceEventTable::ParticleResource::~ParticleResource()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0045e9c0
void RaceEventTable::ParticleResource::ClearFields()
{
	m_particleAnimation = NULL;
	m_sharedParticleAnimation = NULL;
	m_particle = NULL;
	m_trackedEntity = NULL;
	m_particleName[0] = '\0';
	m_unk0x3c.m_x = 0.0f;
	m_unk0x3c.m_y = 0.0f;
	m_unk0x3c.m_z = 0.0f;
	m_unk0x48.m_x = 0.0f;
	m_unk0x48.m_y = 0.0f;
	m_unk0x48.m_z = 0.0f;
	m_unk0x48.m_x = 1.0f;
	m_unk0x54.m_x = 0.0f;
	m_unk0x54.m_y = 0.0f;
	m_unk0x54.m_z = 0.0f;
	m_unk0x54.m_z = 1.0f;
	m_partAnimations = 0;
	m_nodeIndex = 0;
}

// FUNCTION: LEGORACERS 0x0045ea00
void RaceEventTable::ParticleResource::Initialize(InitParams* p_params)
{
	if (m_state0x18) {
		Destroy();
	}

	m_eventId = p_params->m_unk0x00;
	LegoS32* eventId = p_params->m_stateEventIds;
	for (LegoU32 i = 0; i < sizeOfArray(m_stateEventIds); i++) {
		m_stateEventIds[i] = *eventId++;
	}

	m_eventTable = p_params->m_eventTable;
	m_particleAnimation = p_params->m_unk0x14;
	m_sharedParticleAnimation = p_params->m_particleAnimation;
	m_trackedEntity = p_params->m_unk0x1c;
	m_nodeIndex = p_params->m_unk0x20;
	::strncpy(m_particleName, p_params->m_unk0x24, sizeof(m_particleName));
	m_unk0x3c.m_x = p_params->m_unk0x2c.m_x;
	m_unk0x3c.m_y = p_params->m_unk0x2c.m_y;
	m_unk0x3c.m_z = p_params->m_unk0x2c.m_z;
	m_unk0x48.m_x = p_params->m_unk0x38.m_x;
	m_unk0x48.m_y = p_params->m_unk0x38.m_y;
	m_unk0x48.m_z = p_params->m_unk0x38.m_z;
	m_unk0x54.m_x = p_params->m_unk0x44.m_x;
	m_unk0x54.m_y = p_params->m_unk0x44.m_y;
	m_unk0x54.m_z = p_params->m_unk0x44.m_z;

	if (p_params->m_unk0x50) {
		m_flags0x1c |= c_flags0x1cBit1;
	}

	if (p_params->m_unk0x54) {
		m_flags0x1c |= c_flags0x1cBit2;
	}

	if (p_params->m_unk0x58) {
		m_flags0x1c |= c_flags0x1cBit3;
	}

	m_state0x18 = c_state0x18One;
	m_flags0x1c &= ~c_flags0x1cBit5;
}

// FUNCTION: LEGORACERS 0x0045ead0
void RaceEventTable::ParticleResource::Destroy()
{
	OnEnd();
	ClearFields();
	Reset();
}

// FUNCTION: LEGORACERS 0x0045eaf0
void RaceEventTable::ParticleResource::OnStartAt(GolVec3* p_unk0x04)
{
	if (p_unk0x04 && (m_flags0x1c & c_flags0x1cBit3)) {
		m_unk0x3c = *p_unk0x04;
	}

	if (m_particleAnimation->HasEmitter(m_particleName)) {
		m_partAnimations = 1;
		m_particle = m_particleAnimation->SpawnParticle(m_particleName, &m_unk0x3c, &m_unk0x48, &m_unk0x54);
	}
	else if (m_sharedParticleAnimation->HasEmitter(m_particleName)) {
		m_partAnimations = 0;
		m_particle = m_sharedParticleAnimation->SpawnParticle(m_particleName, &m_unk0x3c, &m_unk0x48, &m_unk0x54);
	}

	if (m_particle) {
		m_flags0x1c |= c_flags0x1cBit5;
	}

	NotifyStateChange(m_state0x18, 1);
	m_state0x18 = c_state0x18Three;
}

// FUNCTION: LEGORACERS 0x0045eb90
void RaceEventTable::ParticleResource::OnEnd()
{
	if (m_particle) {
		if (m_partAnimations) {
			m_particleAnimation->FinishRef(m_particle);
		}
		else {
			m_sharedParticleAnimation->FinishRef(m_particle);
		}

		m_particle = NULL;
	}

	NotifyStateChange(m_state0x18, 3);
	m_state0x18 = c_state0x18One;
	m_flags0x1c &= ~c_flags0x1cBit5;
}

// FUNCTION: LEGORACERS 0x0045ebe0
void RaceEventTable::ParticleResource::Update(LegoU32 p_elapsedMs)
{
	Resource::Update(p_elapsedMs);
	if (m_state0x18 == c_state0x18One) {
		return;
	}

	if (!(m_flags0x1c & c_flags0x1cBit5)) {
		if (m_particleAnimation->HasEmitter(m_particleName)) {
			m_partAnimations = 1;
			m_particle = m_particleAnimation->SpawnParticle(m_particleName, &m_unk0x3c, &m_unk0x48, &m_unk0x54);
		}
		else if (m_sharedParticleAnimation->HasEmitter(m_particleName)) {
			m_partAnimations = 0;
			m_particle = m_sharedParticleAnimation->SpawnParticle(m_particleName, &m_unk0x3c, &m_unk0x48, &m_unk0x54);
		}

		if (m_particle) {
			m_flags0x1c |= c_flags0x1cBit5;
		}
	}

	if (m_trackedEntity && m_particle) {
		m_trackedEntity->VTable0x5c(0);
		GolSceneNode* node = m_trackedEntity->VTable0x58(0);
		GolTransformBase* transform = node->VTable0x18(m_nodeIndex);
		GolVec3 position;
		position.m_x = 0.0f;
		position.m_y = 0.0f;
		position.m_z = 0.0f;
		GolVec3 transformedPosition;

		do {
			transformedPosition = position;
			transform->VTable0x04(&transformedPosition, &position);
			transform = transform->m_unk0x04;
		} while (transform);

		LegoFloat scale = m_trackedEntity->GetModel(0)->GetScale() * m_trackedEntity->GetUnk0x58();
		position.m_x *= scale;
		position.m_y *= scale;
		position.m_z *= scale;

		m_trackedEntity->VTable0x2c(position, &transformedPosition);
		if (m_particle->m_particle) {
			m_particle->m_particle->SetPosition(&transformedPosition);
		}
	}
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RaceEventTable::Resource::OnStartForRacer(RaceState::Racer*)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RaceEventTable::Resource::OnStartAt(GolVec3*)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RaceEventTable::Resource::OnEndForRacer(RaceState::Racer*)
{
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void RaceEventTable::Resource::OnEnd()
{
}

// FUNCTION: LEGORACERS 0x0045ed40
RaceEventTable::Resource::Resource()
{
	m_eventTable = NULL;
	m_stateEventIds[0] = -1;
	m_stateEventIds[1] = -1;
	m_stateEventIds[2] = -1;
	m_state0x18 = 0;
	m_eventId = 0;
	m_flags0x1c = 0;
}

// FUNCTION: LEGORACERS 0x0045ed90
RaceEventTable::Resource::~Resource()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0045eda0
void RaceEventTable::Resource::Reset()
{
	m_eventTable = NULL;
	m_stateEventIds[0] = -1;
	m_stateEventIds[1] = -1;
	m_stateEventIds[2] = -1;
	m_state0x18 = 0;
	m_eventId = 0;
}

// FUNCTION: LEGORACERS 0x0045edc0
void RaceEventTable::Resource::Update(LegoU32)
{
	if (m_state0x18 == c_state0x18Five) {
		OnEnd();
	}
}

// FUNCTION: LEGORACERS 0x0045edd0
void RaceEventTable::Resource::NotifyStateChange(LegoU32 p_unk0x04, LegoU32 p_unk0x08)
{
	LegoS32 current = -1;
	LegoS32 next = -1;

	switch (p_unk0x04) {
	case 2:
		p_unk0x04 = 0;
		break;
	case 3:
		p_unk0x04 = 1;
		break;
	case 4:
		p_unk0x04 = 2;
		break;
	default:
		p_unk0x04 = 3;
		break;
	}

	if (p_unk0x04 != 3) {
		current = m_stateEventIds[p_unk0x04];
	}

	if (p_unk0x08 != 3) {
		next = m_stateEventIds[p_unk0x08];
	}

	if (current != -1) {
		if (next != -1) {
			m_eventTable->FireEventsAt(next, current, NULL);
		}
		else {
			m_eventTable->EndEventsAt(current, NULL);
		}
	}
	else if (next != -1) {
		m_eventTable->StartEventsAt(next, NULL);
	}
}

// FUNCTION: LEGORACERS 0x0045eee0 FOLDED
void RaceEventTable::Resource::ForceEventEnd(RaceState::Racer* p_racer)
{
	LegoU8 flags = m_flags0x1c;
	if (flags & c_flags0x1cBit2) {
		LegoU32 state = m_state0x18;
		if (state == c_state0x18One || state == c_state0x18Four) {
			OnStartForRacer(p_racer);
			if (m_flags0x1c & c_flags0x1cBit1) {
				return;
			}

			OnEndForRacer(p_racer);
			return;
		}
	}

	if (m_state0x18 != c_state0x18One && !(flags & c_flags0x1cBit1)) {
		OnEndForRacer(p_racer);
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
		case GolFileParser::e_unknown0x2a:
			ParseSounds(parser, p_params->m_mirror);
			break;
		case GolFileParser::e_unknown0x28:
			ParsePartAnimations(parser);
			break;
		case GolFileParser::e_unknown0x29:
			ParseMaterialAnimations(parser);
			break;
		case GolFileParser::e_unknown0x3d:
			ParseParticles(parser, p_params->m_mirror);
			break;
		case GolFileParser::e_unknown0x39:
			ParseEventLinks(parser);
			break;
		case GolFileParser::e_unknown0x42:
			ParseSkyStates(parser);
			break;
		case GolFileParser::e_unknown0x4b:
			ParseTimers(parser);
			break;
		case GolFileParser::e_unknown0x52:
			ParseNodeTransforms(parser);
			break;
		case GolFileParser::e_unknown0x4d:
			ParseColorTransforms(parser);
			break;
		case GolFileParser::e_unknown0x51:
			ParseLapZones(parser);
			break;
		case GolFileParser::e_unknown0x53:
			ParseModelDistances(parser);
			break;
		case GolFileParser::e_unknown0x55:
			ParseLookTargets(parser, p_params->m_mirror);
			break;
		case GolFileParser::e_unknown0x59:
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
		if (p_parser->GetNextToken() != GolFileParser::e_unknown0x27) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
		}

		SoundResource::InitParams params;
		params.m_eventId = p_parser->ReadInteger();

		GolFileParser::ParserTokenType token = p_parser->GetNextToken();
		params.m_unk0x3c = FALSE;
		if (token == GolFileParser::e_unknown0x3c) {
			params.m_unk0x3c = TRUE;
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
		params.m_unk0x34 = FALSE;
		params.m_unk0x38 = FALSE;
		params.m_positional = FALSE;
		params.m_unk0x1c = 0;
		params.m_volume = 1.0f;
		params.m_frequencyScale = 1.0f;
		params.m_soundSource = field->m_soundSource;
		params.m_probability = 1.0f;
		params.m_entity = NULL;
		params.m_unk0x48 = 0;

		for (token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly; token = p_parser->GetNextToken()) {
			switch (token) {
			case GolFileParser::e_unknown0x3b:
				params.m_position.m_x = p_parser->ReadFloat();
				params.m_position.m_y = p_parser->ReadFloat();
				params.m_position.m_z = p_parser->ReadFloat();
				if (p_mirror) {
					params.m_position.m_y = -params.m_position.m_y;
				}
				break;
			case GolFileParser::e_unknown0x2c:
				params.m_soundId = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x2e:
				params.m_unk0x1c = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x2f:
				params.m_volume = p_parser->ReadFloat();
				break;
			case GolFileParser::e_unknown0x30:
				params.m_frequencyScale = p_parser->ReadFloat();
				break;
			case GolFileParser::e_unknown0x31:
				params.m_minDistance = p_parser->ReadFloat();
				break;
			case GolFileParser::e_unknown0x32:
				params.m_maxDistance = p_parser->ReadFloat();
				break;
			case GolFileParser::e_unknown0x2d:
				params.m_unk0x34 = TRUE;
				break;
			case GolFileParser::e_unknown0x3a:
				params.m_unk0x38 = TRUE;
				break;
			case GolFileParser::e_unknown0x3f:
				params.m_positional = TRUE;
				break;
			case GolFileParser::e_unknown0x40:
				params.m_probability = p_parser->ReadFloat();
				break;
			case GolFileParser::e_unknown0x33: {
				GolName name;
				::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));
				params.m_entity = field->m_trackDatabase->FindAnimatedEntity(name);
				if (params.m_entity == NULL) {
					params.m_entity = field->m_sharedDatabase->FindAnimatedEntity(name);
				}
				break;
			}
			case GolFileParser::e_unknown0x54:
				params.m_unk0x48 = p_parser->ReadInteger();
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
		if (p_parser->GetNextToken() != GolFileParser::e_unknown0x27) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
		}

		PartAnimationResource::InitParams params;
		params.m_unk0x00 = p_parser->ReadInteger();
		GolFileParser::ParserTokenType token = p_parser->GetNextToken();
		LegoS32 eventIndex = 1;
		params.m_unk0x30 = 0;
		if (token == GolFileParser::e_unknown0x3c) {
			eventIndex = 1;
			params.m_unk0x30 = 1;
			if (p_parser->GetNextToken() != GolFileParser::e_leftCurly) {
				p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
			}
		}
		else if (token != GolFileParser::e_leftCurly) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		params.m_eventTable = field;
		params.m_stateEventIds[0] = -1;
		params.m_unk0x14 = NULL;
		params.m_stateEventIds[1] = -1;
		params.m_unk0x18 = 0;
		params.m_stateEventIds[2] = -1;
		params.m_unk0x1c = 0;
		params.m_unk0x20 = -1;
		params.m_unk0x24 = -1;
		params.m_unk0x2c = FALSE;
		params.m_unk0x28 = FALSE;
		params.m_unk0x34 = FALSE;
		params.m_unk0x38 = FALSE;

		for (token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly; token = p_parser->GetNextToken()) {
			switch (token) {
			case GolFileParser::e_unknown0x33: {
				const LegoChar* name = p_parser->ReadStringWithMaxLength(sizeof(GolName));
				LegoChar destination[sizeof(GolName)];
				::strncpy(destination, name, sizeof(destination));

				if (params.m_unk0x38) {
					GolWorldDatabase* worldDatabase = field->m_sharedDatabase;
					if (worldDatabase->GetAnimatedEntityEntries()) {
						params.m_unk0x14 = worldDatabase->GetAnimatedEntityByName(destination);
					}
					else {
						params.m_unk0x14 = NULL;
					}
				}
				else {
					GolWorldDatabase* worldDatabase = field->m_trackDatabase;
					if (worldDatabase->GetAnimatedEntityEntries()) {
						params.m_unk0x14 = worldDatabase->GetAnimatedEntityByName(destination);
					}
					else {
						params.m_unk0x14 = NULL;
					}
				}
				break;
			}
			case GolFileParser::e_unknown0x41:
				params.m_unk0x38 = TRUE;
				break;
			case GolFileParser::e_unknown0x34:
				params.m_unk0x18 = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x35:
				params.m_unk0x1c = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x36:
				params.m_unk0x20 = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x37:
				params.m_unk0x24 = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x2d:
				params.m_unk0x28 = TRUE;
				break;
			case GolFileParser::e_unknown0x3a:
				params.m_unk0x2c = TRUE;
				break;
			case GolFileParser::e_unknown0x3f:
				params.m_unk0x34 = TRUE;
				break;
			case GolFileParser::e_unknown0x27: {
				LegoS32 eventToken = p_parser->GetNextToken() - GolFileParser::e_unknown0x34;
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

		field->m_partAnimations[i].FUN_00463330(&params);
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
		if (p_parser->GetNextToken() != GolFileParser::e_unknown0x27) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
		}

		MaterialAnimationResource::InitParams params;
		params.m_unk0x00 = p_parser->ReadInteger();
		GolFileParser::ParserTokenType token = p_parser->GetNextToken();
		params.m_unk0x30 = FALSE;
		if (token == GolFileParser::e_unknown0x3c) {
			params.m_unk0x30 = TRUE;
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
		params.m_unk0x14 = NULL;
		params.m_unk0x18 = NULL;
		params.m_unk0x1c = 0;
		params.m_unk0x20 = 0;
		params.m_unk0x24 = 0;
		params.m_unk0x28 = FALSE;
		params.m_unk0x2c = FALSE;
		params.m_unk0x34 = FALSE;

		for (token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly; token = p_parser->GetNextToken()) {
			switch (token) {
			case GolFileParser::e_unknown0x38:
				params.m_unk0x14 = field->m_materialAnimationDatabase->VTable0x4c(p_parser->ReadInteger());
				break;
			case GolFileParser::e_unknown0x34:
				params.m_unk0x20 = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x35:
				params.m_unk0x24 = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x2d:
				params.m_unk0x28 = TRUE;
				break;
			case GolFileParser::e_unknown0x3a:
				params.m_unk0x2c = TRUE;
				break;
			case GolFileParser::e_unknown0x3f:
				params.m_unk0x34 = TRUE;
				break;
			case GolFileParser::e_unknown0x27: {
				LegoS32 eventIndex = p_parser->GetNextToken() - GolFileParser::e_unknown0x34;
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
			case GolFileParser::e_unknown0x33: {
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
									if (field->m_sharedDatabase->GetUnk0xccNameEntries() == NULL) {
										entity = NULL;
									}
									else {
										entity = field->m_sharedDatabase->GetUnk0xccName(destination);
									}
								}
							}
						}
					}
				}

				MaterialTable0x0c* materialTable;
				if (entity->GetMaterialTable(0)) {
					materialTable = entity->GetMaterialTable(0);
				}
				else {
					materialTable = entity->GetModel(0)->GetMaterialTable();
				}
				params.m_unk0x18 = materialTable;
				params.m_unk0x1c = p_parser->ReadInteger();
				break;
			}
			default:
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}

		field->m_materialAnimations[i].FUN_00463120(&params);
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
		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);

		ParticleResource::InitParams params;
		params.m_unk0x00 = p_parser->ReadInteger();

		GolFileParser::ParserTokenType token = p_parser->GetNextToken();
		LegoS32 eventIndex;
		params.m_unk0x54 = FALSE;
		if (token == GolFileParser::e_unknown0x3c) {
			eventIndex = 1;
			params.m_unk0x54 = eventIndex;
			p_parser->ReadLeftCurly();
		}
		else {
			if (token != GolFileParser::e_leftCurly) {
				p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
			}
			eventIndex = 1;
		}

		params.m_unk0x14 = field->m_particleAnimation;
		params.m_particleAnimation = field->m_sharedParticleAnimation;
		params.m_stateEventIds[0] = -1;
		params.m_stateEventIds[1] = -1;
		params.m_eventTable = field;
		params.m_stateEventIds[2] = -1;
		params.m_unk0x24[0] = '\0';
		params.m_unk0x50 = FALSE;
		params.m_unk0x58 = FALSE;
		params.m_unk0x2c.m_x = 0.0f;
		params.m_unk0x2c.m_y = 0.0f;
		params.m_unk0x2c.m_z = 0.0f;
		params.m_unk0x38.m_x = 1.0f;
		params.m_unk0x38.m_y = 0.0f;
		params.m_unk0x38.m_z = 0.0f;
		params.m_unk0x44.m_x = 0.0f;
		params.m_unk0x44.m_y = 0.0f;
		params.m_unk0x44.m_z = 1.0f;
		params.m_unk0x1c = NULL;
		params.m_unk0x20 = 0;
		LegoBool32 token0x3f = FALSE;

		for (token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly; token = p_parser->GetNextToken()) {
			switch (token) {
			case GolFileParser::e_unknown0x3d:
				::strncpy(
					params.m_unk0x24,
					p_parser->ReadStringWithMaxLength(sizeof(params.m_unk0x24)),
					sizeof(params.m_unk0x24)
				);
				break;
			case GolFileParser::e_unknown0x3a:
				params.m_unk0x50 = eventIndex;
				break;
			case GolFileParser::e_unknown0x3b:
				params.m_unk0x2c.m_x = p_parser->ReadFloat();
				params.m_unk0x2c.m_y = p_parser->ReadFloat();
				params.m_unk0x2c.m_z = p_parser->ReadFloat();
				if (p_mirror) {
					params.m_unk0x2c.m_y = -params.m_unk0x2c.m_y;
				}
				break;
			case GolFileParser::e_unknown0x3e:
				params.m_unk0x38.m_x = p_parser->ReadFloat();
				params.m_unk0x38.m_y = p_parser->ReadFloat();
				params.m_unk0x38.m_z = p_parser->ReadFloat();
				params.m_unk0x44.m_x = p_parser->ReadFloat();
				params.m_unk0x44.m_y = p_parser->ReadFloat();
				params.m_unk0x44.m_z = p_parser->ReadFloat();
				if (p_mirror) {
					params.m_unk0x38.m_y = -params.m_unk0x38.m_y;
					params.m_unk0x44.m_y = -params.m_unk0x44.m_y;
				}
				break;
			case GolFileParser::e_unknown0x3f:
				params.m_unk0x58 = eventIndex;
				break;
			case GolFileParser::e_unknown0x41:
				token0x3f = eventIndex;
				break;
			case GolFileParser::e_unknown0x33: {
				const LegoChar* name = p_parser->ReadStringWithMaxLength(sizeof(GolName));
				LegoChar destination[sizeof(GolName)];
				::strncpy(destination, name, sizeof(destination));

				if (token0x3f) {
					GolWorldDatabase* worldDatabase = field->m_sharedDatabase;
					if (worldDatabase->GetAnimatedEntityEntries() == NULL) {
						GolModelEntity* entity = NULL;
						params.m_unk0x1c = entity;
					}
					else {
						params.m_unk0x1c = worldDatabase->GetAnimatedEntityByName(destination);
					}
				}
				else {
					GolWorldDatabase* worldDatabase = field->m_trackDatabase;
					if (worldDatabase->GetAnimatedEntityEntries() == NULL) {
						GolModelEntity* entity = NULL;
						params.m_unk0x1c = entity;
					}
					else {
						params.m_unk0x1c = worldDatabase->GetAnimatedEntityByName(destination);
					}
				}
				break;
			}
			case GolFileParser::e_unknown0x54:
				params.m_unk0x20 = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x27: {
				LegoS32 eventToken = p_parser->GetNextToken() - GolFileParser::e_unknown0x34;
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
		if (p_parser->GetNextToken() != GolFileParser::e_unknown0x27) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
		}

		m_eventLinks[i].m_eventId = p_parser->ReadInteger();
		if (p_parser->GetNextToken() != GolFileParser::e_leftCurly) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		if (p_parser->GetNextToken() != GolFileParser::e_unknown0x39) {
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
		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);

		SkyStateResource::InitParams params;
		params.m_unk0x00 = p_parser->ReadInteger();

		GolFileParser::ParserTokenType token = p_parser->GetNextToken();
		params.m_unk0x24 = FALSE;
		if (token == GolFileParser::e_unknown0x3c) {
			params.m_unk0x24 = TRUE;
			p_parser->ReadLeftCurly();
		}
		else if (token != GolFileParser::e_leftCurly) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		params.m_unk0x14 = field->m_skyState;
		params.m_stateEventIds[0] = -1;
		params.m_stateEventIds[1] = -1;
		params.m_eventTable = field;
		params.m_stateEventIds[2] = -1;
		params.m_unk0x18[0] = '\0';
		params.m_unk0x20 = 0;
		params.m_flags0x28 = 0;

		for (token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly; token = p_parser->GetNextToken()) {
			switch (token) {
			case GolFileParser::e_unknown0x43:
				::strncpy(
					params.m_unk0x18,
					p_parser->ReadStringWithMaxLength(sizeof(params.m_unk0x18)),
					sizeof(params.m_unk0x18)
				);
				break;
			case GolFileParser::e_unknown0x44:
				params.m_unk0x20 = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x45:
				params.m_flags0x28 |= 2;
				break;
			case GolFileParser::e_unknown0x46:
				params.m_flags0x28 |= 1;
				break;
			case GolFileParser::e_unknown0x47:
				params.m_flags0x28 |= 8;
				break;
			case GolFileParser::e_unknown0x48:
				params.m_flags0x28 |= 4;
				break;
			case GolFileParser::e_unknown0x27: {
				LegoS32 eventIndex = p_parser->GetNextToken() - GolFileParser::e_unknown0x34;
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
		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);

		ColorTransformResource::InitParams params;
		params.m_unk0x00 = p_parser->ReadInteger();

		GolFileParser::ParserTokenType token = p_parser->GetNextToken();
		params.m_flags0x14 = 0;
		if (token == GolFileParser::e_unknown0x3c) {
			params.m_flags0x14 = 5;
			p_parser->ReadLeftCurly();
		}
		else if (token != GolFileParser::e_leftCurly) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		params.m_stateEventIds[0] = -1;
		params.m_eventTable = field;
		params.m_stateEventIds[1] = -1;
		params.m_unk0x38 = NULL;
		params.m_stateEventIds[2] = -1;

		for (token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly; token = p_parser->GetNextToken()) {
			switch (token) {
			case GolFileParser::e_unknown0x33: {
				GolName name;
				::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));

				if (field->m_trackDatabase->GetUnk0xb4NameEntries()) {
					params.m_unk0x38 = field->m_trackDatabase->GetUnk0xb4Name(name);
				}
				else {
					params.m_unk0x38 = NULL;
				}

				if (params.m_unk0x38) {
					break;
				}

				if (field->m_trackDatabase->GetAnimatedEntityEntries()) {
					params.m_unk0x38 = field->m_trackDatabase->GetAnimatedEntityByName(name);
				}
				else {
					params.m_unk0x38 = NULL;
				}

				if (params.m_unk0x38) {
					break;
				}

				if (field->m_trackDatabase->GetUnk0xccNameEntries()) {
					params.m_unk0x38 = field->m_trackDatabase->GetUnk0xccName(name);
				}
				else {
					params.m_unk0x38 = NULL;
				}
				break;
			}
			case GolFileParser::e_unknown0x4e:
				params.m_unk0x18.m_redShift = p_parser->ReadInteger();
				params.m_unk0x18.m_grnShift = p_parser->ReadInteger();
				params.m_unk0x18.m_bluShift = p_parser->ReadInteger();
				params.m_unk0x18.m_alpShift = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x4f:
				params.m_unk0x18.m_redOffset = p_parser->ReadInteger();
				params.m_unk0x18.m_grnOffset = p_parser->ReadInteger();
				params.m_unk0x18.m_bluOffset = p_parser->ReadInteger();
				params.m_unk0x18.m_alpOffset = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x50:
				params.m_flags0x14 |= 2;
				break;
			case GolFileParser::e_unknown0x3a:
				params.m_flags0x14 |= 4;
				break;
			case GolFileParser::e_unknown0x27: {
				LegoS32 eventIndex = p_parser->GetNextToken() - GolFileParser::e_unknown0x34;
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

		field->m_colorTransforms[i].FUN_00465570(&params);
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
		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);

		TimerResource::InitParams params;
		params.m_unk0x00 = p_parser->ReadInteger();

		GolFileParser::ParserTokenType token = p_parser->GetNextToken();
		params.m_unk0x1c = FALSE;
		if (token == GolFileParser::e_unknown0x3c) {
			params.m_unk0x1c = TRUE;
			p_parser->ReadLeftCurly();
		}
		else if (token != GolFileParser::e_leftCurly) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		params.m_stateEventIds[0] = -1;
		params.m_eventTable = field;
		params.m_stateEventIds[1] = -1;
		params.m_unk0x14 = -1;
		params.m_stateEventIds[2] = -1;
		params.m_unk0x18 = 0;

		for (token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly; token = p_parser->GetNextToken()) {
			switch (token) {
			case GolFileParser::e_unknown0x49:
				params.m_unk0x18 = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x4c:
				params.m_unk0x14 = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x27: {
				LegoS32 eventIndex = p_parser->GetNextToken() - GolFileParser::e_unknown0x34;
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
		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);

		NodeTransformResource::InitParams params;
		params.m_unk0x00 = p_parser->ReadInteger();

		GolFileParser::ParserTokenType token = p_parser->GetNextToken();
		params.m_unk0x20 = FALSE;
		if (token == GolFileParser::e_unknown0x3c) {
			params.m_unk0x20 = TRUE;
			p_parser->ReadLeftCurly();
		}
		else if (token != GolFileParser::e_leftCurly) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		params.m_stateEventIds[0] = -1;
		params.m_stateEventIds[1] = -1;
		params.m_stateEventIds[2] = -1;
		params.m_eventTable = field;
		params.m_unk0x14 = NULL;
		params.m_unk0x18 = NULL;
		params.m_unk0x1c = 0;

		GolName name;
		for (token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly; token = p_parser->GetNextToken()) {
			switch (token) {
			case GolFileParser::e_unknown0x4a:
				::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));

				params.m_unk0x14 = field->m_triggerDatabase->FindBoundedEntity(name);
				break;
			case GolFileParser::e_unknown0x33:
				::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));

				params.m_unk0x18 = field->m_trackDatabase->FindAnimatedEntity(name);
				if (params.m_unk0x18 == NULL) {
					params.m_unk0x18 = field->m_sharedDatabase->FindAnimatedEntity(name);
				}
				break;
			case GolFileParser::e_unknown0x54:
				params.m_unk0x1c = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x27: {
				LegoS32 eventIndex;
				switch (p_parser->GetNextToken()) {
				case GolFileParser::e_unknown0x34:
					eventIndex = 1;
					break;
				case GolFileParser::e_unknown0x36:
					eventIndex = 0;
					break;
				case GolFileParser::e_unknown0x37:
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

		field->m_nodeTransforms[i].FUN_00463900(&params);
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
		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);

		ModelDistanceResource::InitParams params;
		params.m_unk0x00 = p_parser->ReadInteger();

		GolFileParser::ParserTokenType token = p_parser->GetNextToken();
		params.m_unk0x1c = FALSE;
		if (token == GolFileParser::e_unknown0x3c) {
			params.m_unk0x1c = TRUE;
			p_parser->ReadLeftCurly();
		}
		else if (token != GolFileParser::e_leftCurly) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		params.m_stateEventIds[0] = -1;
		params.m_stateEventIds[1] = -1;
		params.m_stateEventIds[2] = -1;
		params.m_eventTable = field;
		params.m_unk0x14 = NULL;
		params.m_unk0x18 = FALSE;
		params.m_unk0x20 = FALSE;
		LegoBool32 useAlternateDatabase = FALSE;
		LegoS32 eventIndex = 1;

		for (token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly; token = p_parser->GetNextToken()) {
			switch (token) {
			case GolFileParser::e_unknown0x33: {
				GolName name;
				::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));

				if (!useAlternateDatabase) {
					params.m_unk0x14 = field->m_trackDatabase->FindModelEntity(name);
					if (params.m_unk0x14 == NULL) {
						params.m_unk0x14 = field->m_trackDatabase->FindAnimatedEntity(name);
					}
					if (params.m_unk0x14 == NULL) {
						params.m_unk0x14 = field->m_trackDatabase->FindCollidableEntity(name);
					}
				}
				else {
					params.m_unk0x14 = field->m_sharedDatabase->FindModelEntity(name);
					if (params.m_unk0x14 == NULL) {
						params.m_unk0x14 = field->m_sharedDatabase->FindAnimatedEntity(name);
					}
					if (params.m_unk0x14 == NULL) {
						params.m_unk0x14 = field->m_sharedDatabase->FindCollidableEntity(name);
					}
				}
				break;
			}
			case GolFileParser::e_unknown0x3a:
				params.m_unk0x18 = eventIndex;
				break;
			case GolFileParser::e_unknown0x41:
				useAlternateDatabase = eventIndex;
				break;
			case GolFileParser::e_unknown0x46:
				params.m_unk0x20 = eventIndex;
				break;
			case GolFileParser::e_unknown0x27: {
				LegoS32 tokenIndex = p_parser->GetNextToken() - GolFileParser::e_unknown0x34;
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

		field->m_modelDistances[i].FUN_00463700(&params);
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
			p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);

			LookTargetResource::InitParams params;
			params.m_unk0x00 = p_parser->ReadInteger();

			p_parser->ReadLeftCurly();
			params.m_stateEventIds[0] = -1;
			params.m_stateEventIds[1] = -1;
			params.m_stateEventIds[2] = -1;
			params.m_eventTable = field;
			params.m_unk0x14.m_x = 0.0f;
			params.m_unk0x14.m_y = 0.0f;
			params.m_unk0x14.m_z = 0.0f;

			for (GolFileParser::ParserTokenType token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly;
				 token = p_parser->GetNextToken()) {
				switch (token) {
				case GolFileParser::e_unknown0x3b:
					params.m_unk0x14.m_x = p_parser->ReadFloat();
					params.m_unk0x14.m_y = p_parser->ReadFloat();
					params.m_unk0x14.m_z = p_parser->ReadFloat();
					if (p_mirror) {
						params.m_unk0x14.m_y = -params.m_unk0x14.m_y;
					}
					break;
				case GolFileParser::e_unknown0x27: {
					LegoS32 eventIndex = p_parser->GetNextToken() - GolFileParser::e_unknown0x34;
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
		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);

		ExternalForceResource::InitParams params;
		params.m_unk0x00 = p_parser->ReadInteger();

		GolFileParser::ParserTokenType token = p_parser->GetNextToken();
		params.m_unk0x2c = FALSE;
		if (token == GolFileParser::e_unknown0x3c) {
			params.m_unk0x2c = TRUE;
			p_parser->ReadLeftCurly();
		}
		else if (token != GolFileParser::e_leftCurly) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		params.m_stateEventIds[0] = -1;
		params.m_stateEventIds[1] = -1;
		params.m_stateEventIds[2] = -1;
		params.m_eventTable = field;
		params.m_unk0x14.m_x = 0.0f;
		params.m_unk0x14.m_y = 0.0f;
		params.m_unk0x14.m_z = 0.0f;
		params.m_unk0x20 = 0;
		params.m_unk0x24 = -1;
		params.m_unk0x28 = FALSE;

		for (token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly; token = p_parser->GetNextToken()) {
			switch (token) {
			case GolFileParser::e_unknown0x3e:
				params.m_unk0x14.m_x = p_parser->ReadFloat();
				params.m_unk0x14.m_y = p_parser->ReadFloat();
				params.m_unk0x14.m_z = p_parser->ReadFloat();
				if (p_mirror) {
					params.m_unk0x14.m_y = -params.m_unk0x14.m_y;
				}
				break;
			case GolFileParser::e_unknown0x4c:
				params.m_unk0x20 = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x5a:
				params.m_unk0x24 = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x27: {
				LegoS32 eventIndex = p_parser->GetNextToken() - GolFileParser::e_unknown0x34;
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
		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);

		LapZoneResource::InitParams params;
		params.m_unk0x00 = p_parser->ReadInteger();

		p_parser->ReadLeftCurly();
		params.m_stateEventIds[0] = -1;
		params.m_stateEventIds[1] = -1;
		params.m_eventTable = field;
		params.m_stateEventIds[2] = -1;
		params.m_unk0x14 = 1;

		for (GolFileParser::ParserTokenType token = p_parser->GetNextToken(); token != GolFileParser::e_rightCurly;
			 token = p_parser->GetNextToken()) {
			switch (token) {
			case GolFileParser::e_unknown0x36:
				params.m_unk0x14 = 0;
				break;
			case GolFileParser::e_unknown0x37:
				params.m_unk0x14 = 2;
				break;
			case GolFileParser::e_unknown0x27: {
				LegoS32 eventIndex = p_parser->GetNextToken() - GolFileParser::e_unknown0x34;
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

// FUNCTION: LEGORACERS 0x00462c60
void RaceEventTable::ForceAllEvents()
{
	LegoU32 i;

	if (m_sounds) {
		for (i = 0; i < m_soundCount; i++) {
			m_sounds[i].SetState0x18(Resource::c_state0x18Five);
		}
	}

	if (m_partAnimations) {
		for (i = 0; i < m_partAnimationCount; i++) {
			m_partAnimations[i].SetState0x18(Resource::c_state0x18Five);
		}
	}

	if (m_materialAnimations) {
		for (i = 0; i < m_materialAnimationCount; i++) {
			m_materialAnimations[i].SetState0x18(Resource::c_state0x18Five);
		}
	}

	if (m_particles) {
		for (i = 0; i < m_particleCount; i++) {
			m_particles[i].SetState0x18(Resource::c_state0x18Five);
		}
	}

	if (m_skyStates) {
		for (i = 0; i < m_skyStateCount; i++) {
			m_skyStates[i].SetState0x18(Resource::c_state0x18Five);
		}
	}

	if (m_timers) {
		for (i = 0; i < m_timerCount; i++) {
			m_timers[i].SetState0x18(Resource::c_state0x18Five);
		}
	}

	if (m_nodeTransforms) {
		for (i = 0; i < m_nodeTransformCount; i++) {
			m_nodeTransforms[i].SetState0x18(Resource::c_state0x18Five);
		}
	}

	if (m_modelDistances) {
		for (i = 0; i < m_modelDistanceCount; i++) {
			m_modelDistances[i].SetState0x18(Resource::c_state0x18Five);
		}
	}

	Update(0);
}

// FUNCTION: LEGORACERS 0x00462da0
void RaceEventTable::EndAllForRacer(RaceState::Racer* p_racer)
{
	LegoU32 i;

	if (m_colorTransforms) {
		for (i = 0; i < m_colorTransformCount; i++) {
			Resource* resource = &m_colorTransforms[i];
			resource->ForceEventEnd(p_racer);
		}
	}

	if (m_lapZones) {
		for (i = 0; i < m_lapZoneCount; i++) {
			Resource* resource = &m_lapZones[i];
			resource->ForceEventEnd(p_racer);
		}
	}

	if (m_lookTargets) {
		for (i = 0; i < m_lookTargetCount; i++) {
			Resource* resource = &m_lookTargets[i];
			resource->ForceEventEnd(p_racer);
		}
	}

	if (m_externalForces) {
		LegoU32 count = m_externalForceCount;

		for (i = 0; i < count; i++) {
			Resource* resource = &m_externalForces[i];
			resource->ForceEventEnd(p_racer);
			count = m_externalForceCount;
		}
	}
}

// FUNCTION: LEGORACERS 0x00462e70
RaceEventTable::ExternalForceResource::ExternalForceResource()
{
	ClearFields();
}

// FUNCTION: LEGORACERS 0x00462ec0
RaceEventTable::ExternalForceResource::~ExternalForceResource()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00462f10
void RaceEventTable::ExternalForceResource::ClearFields()
{
	m_armEventId = -1;
	m_eventTable = NULL;
	m_state0x18 = 0;
	m_eventId = 0;
	m_force.m_x = 0.0f;
	m_force.m_y = 0.0f;
	m_force.m_z = 0.0f;
	m_channel = 0;
	m_flags0x34 = 0;
}

// FUNCTION: LEGORACERS 0x00462f40
void RaceEventTable::ExternalForceResource::Initialize(InitParams* p_params)
{
	if (m_state0x18) {
		Destroy();
	}

	m_eventId = p_params->m_unk0x00;
	LegoS32* eventId = p_params->m_stateEventIds;
	for (LegoU32 i = 0; i < sizeOfArray(m_stateEventIds); i++) {
		m_stateEventIds[i] = *eventId++;
	}

	m_eventTable = p_params->m_eventTable;
	m_force = p_params->m_unk0x14;
	m_channel = p_params->m_unk0x20;
	m_armEventId = p_params->m_unk0x24;
	if (p_params->m_unk0x28) {
		m_flags0x1c |= c_flags0x1cBit1;
	}
	if (p_params->m_unk0x2c) {
		m_flags0x1c |= c_flags0x1cBit2;
	}

	m_state0x18 = c_state0x18One;
}

// FUNCTION: LEGORACERS 0x00462fc0
void RaceEventTable::ExternalForceResource::Destroy()
{
	ClearFields();
	Reset();
}

// FUNCTION: LEGORACERS 0x00462fe0
void RaceEventTable::ExternalForceResource::OnStartForRacer(RaceState::Racer* p_racer)
{
	if (m_flags0x34 & c_flags0x34Bit0) {
		if (p_racer) {
			switch (m_channel) {
			case 0:
				p_racer->m_physics.StartExternalForce0(&m_force);
				break;
			case 1:
				p_racer->m_physics.StartExternalForce1(&m_force);
				break;
			}
		}

		NotifyStateChange(1, 1);
		m_state0x18 = c_state0x18Three;
	}
}

// FUNCTION: LEGORACERS 0x00463040
void RaceEventTable::ExternalForceResource::OnEndForRacer(RaceState::Racer* p_racer)
{
	if (p_racer) {
		switch (m_channel) {
		case 0:
			p_racer->m_physics.EndExternalForce0();
			break;
		case 1:
			p_racer->m_physics.EndExternalForce1();
			break;
		}
	}

	NotifyStateChange(m_state0x18, 3);
	m_state0x18 = c_state0x18One;
}

// FUNCTION: LEGORACERS 0x00463090
LegoU32 RaceEventTable::ExternalForceResource::GetKind()
{
	return 12;
}

// FUNCTION: LEGORACERS 0x004630a0
RaceEventTable::MaterialAnimationResource::MaterialAnimationResource()
{
	m_unk0x20 = NULL;
	m_unk0x24 = NULL;
	m_unk0x28 = NULL;
	m_unk0x2c = NULL;
	m_unk0x30 = 0;
	m_flags0x1c = 0;
}

// FUNCTION: LEGORACERS 0x004630d0
RaceEventTable::MaterialAnimationResource::~MaterialAnimationResource()
{
	FUN_004631e0();
}

// FUNCTION: LEGORACERS 0x00463120
void RaceEventTable::MaterialAnimationResource::FUN_00463120(InitParams* p_params)
{
	if (m_state0x18) {
		FUN_004631e0();
	}

	m_eventId = p_params->m_unk0x00;
	LegoS32* eventId = p_params->m_stateEventIds;
	for (LegoU32 i = 0; i < sizeOfArray(m_stateEventIds); i++) {
		m_stateEventIds[i] = *eventId++;
	}

	m_eventTable = p_params->m_eventTable;
	m_unk0x20 = p_params->m_unk0x14;
	if (p_params->m_unk0x28) {
		m_flags0x1c |= c_flags0x1cBit0;
	}
	if (p_params->m_unk0x2c) {
		m_flags0x1c |= c_flags0x1cBit1;
	}
	if (p_params->m_unk0x30) {
		m_flags0x1c |= c_flags0x1cBit2;
	}
	if (p_params->m_unk0x34) {
		m_flags0x1c |= c_flags0x1cBit3;
	}

	m_unk0x24 = &m_unk0x20->GetUnk0x0c()[p_params->m_unk0x20];
	MabMaterialAnimationItem0x18* item = &m_unk0x20->GetUnk0x0c()[p_params->m_unk0x24];
	m_unk0x28 = item;
	m_unk0x2c = item->GetUnk0x00();
	m_unk0x30 = item->GetUnk0x04();
	if (p_params->m_unk0x18) {
		m_unk0x2c = p_params->m_unk0x18;
		m_unk0x30 = p_params->m_unk0x1c;
	}

	m_state0x18 = c_state0x18One;
}

// FUNCTION: LEGORACERS 0x004631e0
void RaceEventTable::MaterialAnimationResource::FUN_004631e0()
{
	OnEnd();
	m_unk0x20 = NULL;
	Reset();
}

// FUNCTION: LEGORACERS 0x00463200
void RaceEventTable::MaterialAnimationResource::Update(LegoU32 p_elapsedMs)
{
	Resource::Update(p_elapsedMs);
	if (m_state0x18 == c_state0x18Three && !(m_flags0x1c & c_flags0x1cBit0) && !m_unk0x24->IsAssigned()) {
		OnEnd();
	}
}

// FUNCTION: LEGORACERS 0x00463230
void RaceEventTable::MaterialAnimationResource::OnStartAt(GolVec3*)
{
	m_unk0x28->FUN_00410470();
	m_unk0x24->FUN_10025da0(m_unk0x2c, m_unk0x30, m_flags0x1c & c_flags0x1cBit0);
	m_unk0x24->FUN_00410480();
	NotifyStateChange(m_state0x18, c_state0x18One);
	m_state0x18 = c_state0x18Three;
}

// FUNCTION: LEGORACERS 0x00463280
void RaceEventTable::MaterialAnimationResource::OnEnd()
{
	m_unk0x24->FUN_00410470();
	m_unk0x28->FUN_10025da0(m_unk0x2c, m_unk0x30, TRUE);
	m_unk0x28->FUN_00410480();
	NotifyStateChange(m_state0x18, c_state0x18Three);
	m_state0x18 = c_state0x18One;
}

// FUNCTION: LEGORACERS 0x004632c0
RaceEventTable::PartAnimationResource::PartAnimationResource()
{
	m_unk0x20 = NULL;
	m_flags0x1c = 0;
}

// FUNCTION: LEGORACERS 0x004632e0
RaceEventTable::PartAnimationResource::~PartAnimationResource()
{
	FUN_004633e0();
}

// FUNCTION: LEGORACERS 0x00463330
void RaceEventTable::PartAnimationResource::FUN_00463330(InitParams* p_params)
{
	if (m_state0x18) {
		FUN_004633e0();
	}

	m_eventId = p_params->m_unk0x00;
	LegoS32* eventId = p_params->m_stateEventIds;
	for (LegoU32 i = 0; i < sizeOfArray(m_stateEventIds); i++) {
		m_stateEventIds[i] = *eventId++;
	}

	m_eventTable = p_params->m_eventTable;
	m_unk0x20 = p_params->m_unk0x14;
	m_unk0x24 = p_params->m_unk0x18;
	m_unk0x28 = p_params->m_unk0x1c;
	m_unk0x2c = p_params->m_unk0x20;
	m_unk0x30 = p_params->m_unk0x24;

	if (p_params->m_unk0x28) {
		m_flags0x1c |= c_flags0x1cBit0;
	}

	if (p_params->m_unk0x2c) {
		m_flags0x1c |= c_flags0x1cBit1;
	}

	if (p_params->m_unk0x30) {
		m_flags0x1c |= c_flags0x1cBit2;
	}

	if (p_params->m_unk0x34) {
		m_flags0x1c |= c_flags0x1cBit3;
	}

	if (p_params->m_unk0x38) {
		m_flags0x1c |= c_flags0x1cBit4;
	}

	m_unk0x20->SetFlags(m_unk0x20->GetFlags() | c_entityFlag0x200000);
	m_state0x18 = c_state0x18One;
}

// FUNCTION: LEGORACERS 0x004633e0
void RaceEventTable::PartAnimationResource::FUN_004633e0()
{
	m_unk0x20 = NULL;
	Reset();
}

// STUB: LEGORACERS 0x004633f0
void RaceEventTable::PartAnimationResource::Update(LegoU32 p_elapsedMs)
{
	Resource::Update(p_elapsedMs);

	GolAnimatedEntity* entity = m_unk0x20;
	LegoU32 state = m_state0x18;
	LegoS32 currentPart = entity->GetCurrentPartIndex();

	if (state == 2) {
		if (currentPart == m_unk0x2c) {
			LegoU32 flags = entity->GetFlags();
			if (!(flags & c_entityFlags0x120000) || static_cast<LegoU32>(entity->GetQueuedPartIndex()) == 0xffff) {
				LegoU32 loop = m_flags0x1c & c_flags0x1cBit0;
				entity->SetQueuedPartIndex(static_cast<LegoU16>(m_unk0x24));
				flags = entity->GetFlags();
				flags &= ~c_entityFlags0x4e0000;
				flags |= GolAnimatedEntity::c_flagRestartQueuedPart;
				if (loop) {
					flags |= GolAnimatedEntity::c_flagLoopQueuedPart;
				}
				entity->SetFlags(flags);
			}
		}
	}
	else if (state == 4) {
		if (currentPart == m_unk0x30) {
			LegoU32 flags = entity->GetFlags();
			if (!(flags & c_entityFlags0x120000) || static_cast<LegoU32>(entity->GetQueuedPartIndex()) == 0xffff) {
				entity->SetQueuedPartIndex(static_cast<LegoU16>(m_unk0x28));
				flags = entity->GetFlags();
				flags &= ~c_entityFlags0x0e0000;
				flags |= GolAnimatedEntity::c_flagRestartQueuedPart | GolAnimatedEntity::c_flagLoopQueuedPart;
				entity->SetFlags(flags);
			}
		}
	}
	else if (state == 3) {
		if (!(m_flags0x1c & c_flags0x1cBit0) && currentPart == m_unk0x24) {
			LegoU32 flags = entity->GetFlags();
			if (!(flags & c_entityFlags0x120000) || static_cast<LegoU32>(entity->GetQueuedPartIndex()) == 0xffff) {
				LegoS32 queuedPart = m_unk0x30;
				if (queuedPart == -1) {
					entity->SetQueuedPartIndex(static_cast<LegoU16>(m_unk0x28));
					flags = entity->GetFlags();
					flags &= ~c_entityFlags0x0e0000;
					flags |= GolAnimatedEntity::c_flagRestartQueuedPart | GolAnimatedEntity::c_flagLoopQueuedPart;
					entity->SetFlags(flags);
				}
				else {
					entity->SetQueuedPartIndex(static_cast<LegoU16>(queuedPart));
					flags = entity->GetFlags();
					flags &= ~c_entityFlags0x4e0000;
					flags |= GolAnimatedEntity::c_flagRestartQueuedPart;
					entity->SetFlags(flags);
				}
			}
		}
	}

	if (currentPart == m_unk0x2c) {
		if (m_state0x18 != 2) {
			NotifyStateChange(m_state0x18, 0);
			m_state0x18 = 2;
		}
	}
	else if (currentPart == m_unk0x24) {
		if (m_state0x18 != 3) {
			NotifyStateChange(m_state0x18, 1);
			m_state0x18 = 3;
		}
	}
	else if (currentPart == m_unk0x30) {
		if (m_state0x18 != 4) {
			NotifyStateChange(m_state0x18, 2);
			m_state0x18 = 4;
		}
	}
	else if (currentPart == m_unk0x28 && m_state0x18 != c_state0x18One) {
		NotifyStateChange(m_state0x18, 3);
		m_state0x18 = c_state0x18One;
	}
}

// FUNCTION: LEGORACERS 0x00463570
void RaceEventTable::PartAnimationResource::OnStartAt(GolVec3*)
{
	LegoS32 queuedPart = m_unk0x2c;
	GolAnimatedEntity* entity = m_unk0x20;
	if (queuedPart != -1) {
		entity->SetQueuedPartIndex(static_cast<LegoU16>(queuedPart));
		LegoU32 flags = entity->GetFlags();
		flags &= ~c_entityFlags0x4e0000;
		flags |= GolAnimatedEntity::c_flagRestartQueuedPart;
		entity->SetFlags(flags);
	}
	else {
		queuedPart = m_unk0x24;
		entity->SetQueuedPartIndex(static_cast<LegoU16>(queuedPart));
		LegoU32 flags = entity->GetFlags();
		flags &= ~c_entityFlags0x0e0000;
		flags |= GolAnimatedEntity::c_flagRestartQueuedPart | GolAnimatedEntity::c_flagLoopQueuedPart;
		entity->SetFlags(flags);
	}
}

// FUNCTION: LEGORACERS 0x004635c0
void RaceEventTable::PartAnimationResource::OnEnd()
{
	LegoU32 state = m_state0x18;
	LegoU32 nextState = state;
	LegoU32 resetState = c_state0x18One;
	if (state != resetState) {
		nextState = resetState;
		GolAnimatedEntity* entity = m_unk0x20;
		LegoS32 targetPart = m_unk0x28;
		LegoS32 currentPart = entity->GetCurrentPartIndex();
		if (currentPart != targetPart) {
			LegoS32 queuedPart = m_unk0x30;
			if (queuedPart != -1) {
				if (currentPart != queuedPart) {
					queuedPart = m_unk0x30;
					if (queuedPart != -1) {
						entity->SetQueuedPartIndex(static_cast<LegoU16>(queuedPart));
						LegoU32 flags = entity->GetFlags();
						flags &= ~c_entityFlags0x4e0000;
						flags |= GolAnimatedEntity::c_flagRestartQueuedPart;
						entity->SetFlags(flags);
						SetState0x18(nextState);
						return;
					}
				}
			}
			else {
				entity->SetQueuedPartIndex(static_cast<LegoU16>(targetPart));
				LegoU32 flags = entity->GetFlags();
				flags &= ~c_entityFlags0x0e0000;
				flags |= GolAnimatedEntity::c_flagRestartQueuedPart | GolAnimatedEntity::c_flagLoopQueuedPart;
				entity->SetFlags(flags);
			}
		}
	}

	SetState0x18(nextState);
}

// FUNCTION: LEGORACERS 0x00463640
RaceEventTable::ModelDistanceResource::ModelDistanceResource()
{
	m_flags0x1c = 0;
	FUN_004636e0();
}

// FUNCTION: LEGORACERS 0x00463690
RaceEventTable::ModelDistanceResource::~ModelDistanceResource()
{
	FUN_004637a0();
}

// FUNCTION: LEGORACERS 0x004636e0
void RaceEventTable::ModelDistanceResource::FUN_004636e0()
{
	m_modelDistances[0] = 0.0f;
	m_modelDistances[1] = 0.0f;
	m_modelDistances[2] = 0.0f;
	m_unk0x30 = FALSE;
	m_unk0x20 = NULL;
}

// FUNCTION: LEGORACERS 0x00463700
void RaceEventTable::ModelDistanceResource::FUN_00463700(InitParams* p_params)
{
	if (m_state0x18) {
		FUN_004637a0();
	}

	m_eventId = p_params->m_unk0x00;
	LegoS32* eventId = p_params->m_stateEventIds;
	LegoU32 i;
	for (i = 0; i < sizeOfArray(m_stateEventIds); i++) {
		m_stateEventIds[i] = *eventId++;
	}

	m_eventTable = p_params->m_eventTable;
	m_unk0x20 = p_params->m_unk0x14;
	m_unk0x30 = p_params->m_unk0x20;
	if (p_params->m_unk0x18) {
		m_flags0x1c |= c_flags0x1cBit1;
	}
	if (p_params->m_unk0x1c) {
		m_flags0x1c |= c_flags0x1cBit2;
	}

	for (i = 0; i < sizeOfArray(m_modelDistances); i++) {
		m_modelDistances[i] = m_unk0x20->GetModelDistance(i);
		if (!m_unk0x30) {
			LegoFloat modelDistance = -1.0f;
			m_unk0x20->SetModelDistance(i, modelDistance);
		}
	}

	m_state0x18 = c_state0x18One;
}

// FUNCTION: LEGORACERS 0x004637a0
void RaceEventTable::ModelDistanceResource::FUN_004637a0()
{
	FUN_004636e0();
	Reset();
}

// FUNCTION: LEGORACERS 0x004637c0
void RaceEventTable::ModelDistanceResource::OnStartAt(GolVec3*)
{
	for (LegoU32 i = 0; i < sizeOfArray(m_modelDistances); i++) {
		LegoFloat modelDistance;
		if (m_unk0x30) {
			modelDistance = -1.0f;
		}
		else {
			modelDistance = m_modelDistances[i];
		}
		m_unk0x20->SetModelDistance(i, modelDistance);
	}

	m_state0x18 = c_state0x18Three;
}

// FUNCTION: LEGORACERS 0x00463800
void RaceEventTable::ModelDistanceResource::OnEnd()
{
	for (LegoU32 i = 0; i < sizeOfArray(m_modelDistances); i++) {
		LegoFloat modelDistance;
		if (m_unk0x30) {
			modelDistance = m_modelDistances[i];
		}
		else {
			modelDistance = -1.0f;
		}
		m_unk0x20->SetModelDistance(i, modelDistance);
	}

	m_state0x18 = c_state0x18One;
}

// FUNCTION: LEGORACERS 0x00463840
LegoU32 RaceEventTable::ModelDistanceResource::GetKind()
{
	return 10;
}

// FUNCTION: LEGORACERS 0x00463850
RaceEventTable::NodeTransformResource::NodeTransformResource()
{
	FUN_004638f0();
	m_flags0x1c = 0;
}

// FUNCTION: LEGORACERS 0x004638a0
RaceEventTable::NodeTransformResource::~NodeTransformResource()
{
	FUN_00463970();
}

// FUNCTION: LEGORACERS 0x004638f0
void RaceEventTable::NodeTransformResource::FUN_004638f0()
{
	m_unk0x20 = NULL;
	m_unk0x24 = NULL;
	m_unk0x28 = 0;
}

// FUNCTION: LEGORACERS 0x00463900
void RaceEventTable::NodeTransformResource::FUN_00463900(InitParams* p_params)
{
	if (m_state0x18) {
		FUN_00463970();
	}

	m_eventId = p_params->m_unk0x00;
	LegoS32* eventId = p_params->m_stateEventIds;
	for (LegoU32 i = 0; i < sizeOfArray(m_stateEventIds); i++) {
		m_stateEventIds[i] = *eventId++;
	}

	m_eventTable = p_params->m_eventTable;
	m_unk0x20 = p_params->m_unk0x14;
	m_unk0x24 = p_params->m_unk0x18;
	m_unk0x28 = p_params->m_unk0x1c;
	if (p_params->m_unk0x20) {
		m_flags0x1c |= c_flags0x1cBit2;
	}

	m_state0x18 = c_state0x18One;
}

// FUNCTION: LEGORACERS 0x00463970
void RaceEventTable::NodeTransformResource::FUN_00463970()
{
	OnEnd();
	FUN_004638f0();
	Reset();
}

// FUNCTION: LEGORACERS 0x00463990
void RaceEventTable::NodeTransformResource::OnStartAt(GolVec3*)
{
	NotifyStateChange(1, 1);
	m_state0x18 = c_state0x18Three;
}

// FUNCTION: LEGORACERS 0x004639b0
void RaceEventTable::NodeTransformResource::OnEnd()
{
	NotifyStateChange(m_state0x18, 3);
	m_state0x18 = c_state0x18One;
}

// FUNCTION: LEGORACERS 0x004639d0
void RaceEventTable::NodeTransformResource::Update(LegoU32 p_elapsedMs)
{
	if (m_state0x18 != c_state0x18One) {
		Resource::Update(p_elapsedMs);

		if (m_unk0x20) {
			m_unk0x24->VTable0x5c(0);
			GolSceneNode* node = m_unk0x24->VTable0x58(0);
			GolTransformBase* transform = node->VTable0x18(m_unk0x28);

			GolVec3 position;
			GolVec3 up;
			GolVec3 right;
			transform->GetPosition(&position);
			transform->GetUp(&up);
			transform->GetRight(&right);

			LegoFloat scale = m_unk0x24->GetModel(0)->GetScale() * m_unk0x24->GetUnk0x58();
			position.m_x *= scale;
			position.m_y *= scale;
			position.m_z *= scale;

			GolVec3 transformedPosition;
			GolVec3 transformedUp;
			GolVec3 transformedRight;
			m_unk0x24->VTable0x2c(position, &transformedPosition);
			m_unk0x24->VTable0x34(up, &transformedUp);
			m_unk0x24->VTable0x34(right, &transformedRight);
			m_unk0x20->VTable0x08(transformedPosition);
			m_unk0x20->VTable0x40(transformedUp, transformedRight);
		}
	}
}

// FUNCTION: LEGORACERS 0x00463ad0
LegoU32 RaceEventTable::NodeTransformResource::GetKind()
{
	return 9;
}

// FUNCTION: LEGORACERS 0x00464130
RaceEventTable::SoundResource::SoundResource()
{
	m_sound = NULL;
	m_soundSource = NULL;
	m_flags0x1c = 0;
	m_unk0x28 = NULL;
	m_unk0x2c = 0;
	m_probability = 0xff;
}

// FUNCTION: LEGORACERS 0x00464160
RaceEventTable::SoundResource::~SoundResource()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004641b0
void RaceEventTable::SoundResource::Initialize(InitParams* p_params)
{
	if (m_state0x18) {
		Destroy();
	}

	m_eventId = p_params->m_eventId;
	m_soundSource = p_params->m_soundSource;
	m_soundId = p_params->m_soundId;
	m_unk0x40 = p_params->m_unk0x1c;
	m_volume = p_params->m_volume;
	m_frequencyScale = p_params->m_frequencyScale;
	m_minDistance = p_params->m_minDistance;
	m_maxDistance = p_params->m_maxDistance;
	m_position.m_x = p_params->m_position.m_x;
	m_position.m_y = p_params->m_position.m_y;
	m_position.m_z = p_params->m_position.m_z;
	m_unk0x28 = p_params->m_entity;
	m_unk0x2c = p_params->m_unk0x48;
	m_probability = static_cast<LegoU8>(p_params->m_probability * 255.0f);

	g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
	m_unk0x58 = static_cast<LegoU32>(g_randomTable[g_randomTableIndex]) % c_randomDelayRangeMs + c_randomDelayBaseMs;

	if (p_params->m_unk0x34) {
		m_flags0x1c |= c_flags0x1cBit0;
	}
	if (p_params->m_unk0x38) {
		m_flags0x1c |= c_flags0x1cBit1;
	}
	if (p_params->m_unk0x3c) {
		m_flags0x1c |= c_flags0x1cBit2;
	}
	if (p_params->m_positional) {
		m_flags0x1c |= c_flags0x1cBit3;
	}

	m_state0x18 = c_state0x18One;
}

// FUNCTION: LEGORACERS 0x00464290
void RaceEventTable::SoundResource::Destroy()
{
	if (m_sound) {
		m_soundSource->ReleaseSound(m_res0x20);
		m_sound = NULL;
	}

	m_soundSource = NULL;
	m_unk0x28 = NULL;
	m_unk0x2c = 0;
	m_flags0x1c = 0;
	Reset();
}

// FUNCTION: LEGORACERS 0x004642c0
void RaceEventTable::SoundResource::OnStartAt(GolVec3* p_unk0x04)
{
	if (p_unk0x04 && (m_flags0x1c & c_flags0x1cBit3)) {
		m_position.m_x = p_unk0x04->m_x;
		m_position.m_y = p_unk0x04->m_y;
		m_position.m_z = p_unk0x04->m_z;
	}

	if (m_probability < c_probabilityMax) {
		m_state0x18 = c_state0x18Three;
		return;
	}

	if (m_unk0x28) {
		StopSound();
	}

	if (!(m_flags0x1c & c_flags0x1cBit0)) {
		m_soundSource
			->PlaySpatialSoundById(m_soundId, &m_position, m_minDistance, m_maxDistance, m_volume, m_frequencyScale);
		return;
	}

	m_sound = m_soundSource->AcquireSoundById(m_soundId);
	if (m_sound) {
		m_sound->Play(TRUE);
		m_sound->SetDistanceRangeWithMinSquared(m_minDistance * m_minDistance, m_maxDistance);
		m_sound->SetVolume(m_volume);
		m_sound->SetFrequencyScale(m_frequencyScale);
		m_sound->SetPosition(&m_position);

		GolVec3 velocity;
		velocity.m_x = 0.0f;
		velocity.m_y = 0.0f;
		velocity.m_z = 0.0f;
		m_sound->SetVelocity(velocity);
		m_state0x18 = c_state0x18Three;
	}
}

// FUNCTION: LEGORACERS 0x004643b0
void RaceEventTable::SoundResource::OnEnd()
{
	if (m_sound) {
		m_soundSource->ReleaseSound(m_res0x20);
		m_sound = NULL;
	}

	m_state0x18 = c_state0x18One;
}

// FUNCTION: LEGORACERS 0x004643e0
void RaceEventTable::SoundResource::Update(LegoU32 p_elapsedMs)
{
	Resource::Update(p_elapsedMs);
	if (m_state0x18 == c_state0x18One) {
		return;
	}

	if (m_unk0x58 > p_elapsedMs) {
		m_unk0x58 -= p_elapsedMs;
	}
	else {
		m_unk0x58 = 0;
	}

	if (m_unk0x28) {
		StopSound();
	}

	if (m_probability >= c_probabilityMax || m_unk0x58) {
		return;
	}

	g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
	m_unk0x58 = static_cast<LegoU32>(g_randomTable[g_randomTableIndex]) % c_randomDelayRangeMs + c_randomDelayBaseMs;

	g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
	if (static_cast<LegoS32>(g_randomTable[g_randomTableIndex]) % c_probabilityMax >= m_probability) {
		return;
	}

	m_soundSource
		->PlaySpatialSoundById(m_soundId, &m_position, m_minDistance, m_maxDistance, m_volume, m_frequencyScale);
}

// FUNCTION: LEGORACERS 0x004644b0
void RaceEventTable::SoundResource::StopSound()
{
	GolSceneNode* node = m_unk0x28->VTable0x58(0);
	GolTransformBase* transform = node->VTable0x18(m_unk0x2c);

	GolVec3 position;
	position.m_x = 0.0f;
	position.m_y = 0.0f;
	position.m_z = 0.0f;
	GolVec3 transformedPosition;

	do {
		transformedPosition = position;
		transform->VTable0x04(&transformedPosition, &position);
		transform = transform->m_unk0x04;
	} while (transform);

	LegoFloat scale = m_unk0x28->GetModel(0)->GetScale() * m_unk0x28->GetUnk0x58();
	position.m_x = position.m_x * scale;
	position.m_y = position.m_y * scale;
	position.m_z = position.m_z * scale;

	m_unk0x28->VTable0x2c(position, &m_position);
	if (m_sound) {
		m_sound->SetPosition(&m_position);
	}
}

// FUNCTION: LEGORACERS 0x0044f2e0 FOLDED
#pragma code_seg(".text$kbd_vt20")
LegoU32 RaceEventTable::SoundResource::GetKind()
{
	return 0;
}
#pragma code_seg()

// TODO: Prevent unwanted ICF with NullMusicGroup::IsLoaded while this folded return helper is still isolated.
// FUNCTION: LEGORACERS 0x00452430 FOLDED
#pragma code_seg(".text$animatedpartresource_vt18")
LegoU32 RaceEventTable::PartAnimationResource::GetKind()
{
	return 1;
}
#pragma code_seg()
