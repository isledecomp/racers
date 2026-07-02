#include "menu/runtime/cutsceneplayer.h"

#include "audio/soundgroup.h"
#include "audio/soundinstance.h"
#include "audio/soundmanager.h"
#include "audio/spatialsoundinstance.h"
#include "audio/streamingsoundinstance.h"
#include "camera/golcamera.h"
#include "core/gol.h"
#include "font/golfont.h"
#include "font/golfonttable.h"
#include "golanimatedentity.h"
#include "golbinparser.h"
#include "golconstants.h"
#include "golerror.h"
#include "golfileparser.h"
#include "golmodelbase.h"
#include "golname.h"
#include "golscenenode.h"
#include "golstream.h"
#include "goltxtparser.h"
#include "golworldentity.h"
#include "image/utopianpan0xa4.h"
#include "mabmaterialanimation0x14.h"
#include "mabmaterialanimationitem0x18.h"
#include "material/awakekite0x20.h"
#include "menu/menuanimationlist.h"
#include "menu/runtime/cutscenedefinition.h"
#include "menu/runtime/cutsceneparticle.h"
#include "render/gold3drenderdevice.h"
#include "render/golrenderdevice.h"
#include "render/rectangle.h"

#include <string.h>

DECOMP_SIZE_ASSERT(CutscenePlayer, 0x228)
DECOMP_SIZE_ASSERT(CutscenePlayer::CebTxtParser, 0x1fc)
DECOMP_SIZE_ASSERT(CutsceneAnimation::EmbTxtParser, 0x1fc)
DECOMP_SIZE_ASSERT(CutsceneEventSink, 0x04)
DECOMP_SIZE_ASSERT(CutsceneEvent, 0x14)
DECOMP_SIZE_ASSERT(CutsceneCameraTargetView, 0x2c)
DECOMP_SIZE_ASSERT(CutsceneCameraEventView, 0x24)
DECOMP_SIZE_ASSERT(CutsceneModelEventView, 0x28)
DECOMP_SIZE_ASSERT(CutsceneTransformEventView, 0x44)
DECOMP_SIZE_ASSERT(CutsceneEventLink, 0x0c)
DECOMP_SIZE_ASSERT(CutsceneSoundEvent, 0x30)
DECOMP_SIZE_ASSERT(CutsceneColorEvent, 0x48)
DECOMP_SIZE_ASSERT(CutsceneAnimationEvent, 0x50)
DECOMP_SIZE_ASSERT(CutsceneStreamingSoundEvent, 0x50)
DECOMP_SIZE_ASSERT(CutsceneMenuAnimationEvent, 0x2c)
DECOMP_SIZE_ASSERT(CutsceneVisual, 0x58)
DECOMP_SIZE_ASSERT(CutsceneImageVisual, 0x64)
DECOMP_SIZE_ASSERT(CutsceneTextVisual, 0x70)
DECOMP_SIZE_ASSERT(CutsceneAnimation::Entry, 0x08)
DECOMP_SIZE_ASSERT(CutsceneAnimation::Emitter, 0x44)
DECOMP_SIZE_ASSERT(CutsceneAnimation, 0x33c)

// GLOBAL: LEGORACERS 0x004b4ab0
const LegoFloat g_crimsonPebbleEvent0x30DefaultVolume = 1.0f;

// GLOBAL: LEGORACERS 0x004b4ab4
const LegoFloat g_crimsonPebbleEvent0x30DefaultPan = 0.0f;

// GLOBAL: LEGORACERS 0x004b4ab8
const LegoFloat g_crimsonPebbleEvent0x30DefaultFrequencyScale = 1.0f;

// FUNCTION: LEGORACERS 0x00489970
CutsceneAnimation::Entry::Entry()
{
	m_particle = 0;
	m_flags = 0;
}

// FUNCTION: LEGORACERS 0x00489980
CutsceneAnimation::Entry::~Entry()
{
	m_particle = 0;
	m_flags = 0;
}

// FUNCTION: LEGORACERS 0x00489990
CutsceneAnimation::CutsceneAnimation()
{
	m_particles = NULL;
	m_emitters = NULL;
	m_emitterCount = 0;
	m_numParticles = 0;
}

// FUNCTION: LEGORACERS 0x00489a00
CutsceneAnimation::~CutsceneAnimation()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x00489a70
void CutsceneAnimation::Clear()
{
	if (m_nameEntries != NULL) {
		GolNameTable::Clear();
	}

	if (m_emitters != NULL) {
		delete[] m_emitters;
		m_emitters = NULL;
	}

	if (m_particles != NULL) {
		delete[] m_particles;
		m_particles = NULL;
	}

	m_emitterCount = 0;
	m_numParticles = 0;
}

// FUNCTION: LEGORACERS 0x00489af0
void CutsceneAnimation::Load(
	LegoU32 p_numParticles,
	GolExport* p_golExport,
	GolD3DRenderDevice* p_renderer,
	MabMaterialAnimation0x14* p_materialAnimation,
	const LegoChar* p_fileName,
	LegoBool32 p_binary
)
{
	LegoU32 i;
	GolFileParser* parser;

	if (m_emitters) {
		Clear();
	}

	m_numParticles = p_numParticles;
	m_particles = new CutsceneParticle[p_numParticles];
	if (!m_particles) {
		GolFatalError(c_golErrorOutOfMemory, NULL, 0);
	}

	if (p_binary) {
		parser = new GolBinParser();
		if (!parser) {
			GolFatalError(c_golErrorOutOfMemory, NULL, 0);
		}
		parser->SetSuffix(".emb");
	}
	else {
		parser = new EmbTxtParser();
		if (!parser) {
			GolFatalError(c_golErrorOutOfMemory, NULL, 0);
		}
	}

	parser->OpenFileForRead(p_fileName);
	parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);

	m_emitterCount = parser->ReadBracketedCountAndLeftCurly();

	if (m_emitterCount) {
		m_emitters = new Emitter[m_emitterCount];

		if (!m_emitters) {
			GolFatalError(c_golErrorOutOfMemory, NULL, 0);
		}

		GolNameTable::Allocate(m_emitterCount);

		for (i = 0; i < m_emitterCount; i++) {
			m_emitters[i].Parse(p_materialAnimation, p_renderer, parser, this);
		}

		parser->ReadRightCurly();
	}

	parser->Dispose();
	delete parser;

	for (i = 0; i < m_numParticles; i++) {
		m_particles[i].FUN_00489520(p_golExport, p_renderer);
	}
}

// FUNCTION: LEGORACERS 0x00489d50
LegoBool32 CutsceneAnimation::HasEmitter(const LegoChar* p_param)
{
	return GetName(p_param) != NULL;
}

// STUB: LEGORACERS 0x00489d70
CutsceneParticleRef* CutsceneAnimation::SpawnParticle(
	const LegoChar* p_param1,
	GolVec3* p_param2,
	GolVec3* p_param3,
	GolVec3* p_param4
)
{
	Emitter* runtime = static_cast<Emitter*>(GetName(p_param1));

	LegoU32 refIndex = 0;
	while (refIndex < sizeOfArray(m_refs) && (m_refs[refIndex].m_flags & CutsceneParticleRef::c_flagInUse)) {
		refIndex++;
	}

	if (refIndex == sizeOfArray(m_refs)) {
		return NULL;
	}

	LegoU8 lowestPriority = 0xff;
	CutsceneParticle* particle = NULL;
	LegoU32 particleIndex;

	for (particleIndex = 0; particleIndex < m_numParticles; particleIndex++) {
		CutsceneParticle* currentParticle = &m_particles[particleIndex];
		if (!currentParticle->IsActive()) {
			currentParticle->ActivateRuntime(runtime);
			if (p_param3 != NULL && p_param4 != NULL) {
				currentParticle->FUN_00489540(p_param3, p_param4);
			}
			if (p_param2 != NULL) {
				currentParticle->FUN_00489660(p_param2);
			}

			if (runtime->IsOneShot()) {
				CutsceneParticleRef* ref = &m_refs[refIndex];
				ref->m_flags |= CutsceneParticleRef::c_flagInUse;
				ref->m_particle = currentParticle;
				currentParticle->SetRef(ref);
				return ref;
			}

			return NULL;
		}

		Emitter* activeRuntime = currentParticle->GetRuntime();
		if (activeRuntime != NULL) {
			if (activeRuntime->GetPriority() <= lowestPriority) {
				lowestPriority = activeRuntime->GetPriority();
				particle = currentParticle;
			}
		}
		else {
			lowestPriority = 0;
			particle = currentParticle;
		}
	}

	if (runtime->GetPriority() <= lowestPriority) {
		return NULL;
	}

	CutsceneParticleRef* oldRef = particle->GetRef();
	if (oldRef != NULL) {
		oldRef->m_particle = NULL;
	}

	particle->FUN_004897a0();

	particle->ActivateRuntime(runtime);
	if (p_param3 != NULL && p_param4 != NULL) {
		particle->FUN_00489540(p_param3, p_param4);
	}
	if (p_param2 != NULL) {
		particle->FUN_00489660(p_param2);
	}

	if (runtime->IsOneShot()) {
		CutsceneParticleRef* ref = &m_refs[refIndex];
		ref->m_flags |= CutsceneParticleRef::c_flagInUse;
		ref->m_particle = particle;
		particle->SetRef(ref);
		return ref;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00489f00
void CutsceneAnimation::ReleaseRef(CutsceneParticleRef* p_param)
{
	if (p_param->m_particle) {
		p_param->m_particle->FUN_004897a0();
	}

	p_param->m_particle = NULL;
	p_param->m_flags &= ~CutsceneParticleRef::c_flagInUse;
}

// FUNCTION: LEGORACERS 0x00489f30
void CutsceneAnimation::FinishRef(CutsceneParticleRef* p_param)
{
	if (p_param->m_particle) {
		p_param->m_particle->FUN_004897c0();
	}

	p_param->m_particle = NULL;
	p_param->m_flags &= ~CutsceneParticleRef::c_flagInUse;
}

// FUNCTION: LEGORACERS 0x00489f60
LegoU32 CutsceneAnimation::StopAllParticles()
{
	LegoU32 result = m_numParticles;

	for (LegoU32 i = 0; i < result; i++) {
		if (m_particles[i].IsActive()) {
			m_particles[i].FUN_004897a0();
		}

		result = m_numParticles;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00489fa0
void CutsceneAnimation::Update(LegoU32 p_elapsedMs)
{
	for (LegoU32 i = 0; i < m_numParticles; i++) {
		if (m_particles[i].IsActive()) {
			m_particles[i].FUN_004897e0(p_elapsedMs);
		}
	}
}

// FUNCTION: LEGORACERS 0x00489ff0
void CutsceneAnimation::Draw(GolD3DRenderDevice* p_renderer)
{
	for (LegoU32 i = 0; i < m_numParticles; i++) {
		if (m_particles[i].IsActive()) {
			m_particles[i].FUN_004513d0(p_renderer);
		}
	}
}

// FUNCTION: LEGORACERS 0x0048a040
void CutsceneAnimation::DrawTransparent(GolD3DRenderDevice* p_renderer)
{
	for (LegoU32 i = 0; i < m_numParticles; i++) {
		if (m_particles[i].IsActive()) {
			m_particles[i].FUN_00489960(p_renderer);
		}
	}
}

// FUNCTION: LEGORACERS 0x0048a090
CutsceneAnimation::Emitter::Emitter()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048a0a0
CutsceneAnimation::Emitter::~Emitter()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x0048a0b0
void CutsceneAnimation::Emitter::Clear()
{
	if (m_unk0x00) {
		delete[] m_unk0x00;
		m_unk0x00 = NULL;
	}

	Reset();
}

// FUNCTION: LEGORACERS 0x0048a0e0
void CutsceneAnimation::Emitter::Reset()
{
	m_unk0x00 = NULL;
	m_unk0x04 = 0;
	m_unk0x38 = 0;
	m_materialAnimation = NULL;
	m_unk0x40 = NULL;
	m_unk0x14 = 0;
	m_unk0x18 = 0;
	m_unk0x1c = 1.0f;
	m_unk0x20 = 1.0f;
	m_unk0x24 = 0.0f;
	m_unk0x28 = 0.0f;
	m_unk0x08 = 0.0f;
	m_unk0x0c = 0.0f;
	m_unk0x10 = 0.0f;
	m_unk0x2c = 0.0f;
	m_unk0x30 = 0;
	m_unk0x19 = 0;
	m_unk0x34 = -1;
}

// FUNCTION: LEGORACERS 0x0048a130
void CutsceneAnimation::Emitter::Parse(
	MabMaterialAnimation0x14* p_materialAnimation,
	GolD3DRenderDevice* p_renderer,
	GolFileParser* p_parser,
	CutsceneAnimation* p_param4
)
{
	if (m_unk0x00) {
		Clear();
	}

	LegoU32 i;

	m_unk0x38 = 0;
	m_unk0x40 = 0;
	m_materialAnimation = p_materialAnimation;

	p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);

	LegoChar name[8];
	strncpy(name, p_parser->ReadStringWithMaxLength(8), 8);

	p_param4->AddName(name, this);
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();

	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case GolFileParser::e_unknown0x28:
			m_unk0x14 = static_cast<LegoS32>(g_floatConst1000 / p_parser->ReadFloat());
			break;
		case GolFileParser::e_unknown0x29:
			m_unk0x18 = static_cast<LegoS32>(p_parser->ReadFloat() * g_floatConst256);
			break;
		case GolFileParser::e_unknown0x35:
			m_unk0x19 = static_cast<LegoU8>(p_parser->ReadInteger());
			break;
		case GolFileParser::e_unknown0x2c:
			m_unk0x1c = p_parser->ReadFloat();
			break;
		case GolFileParser::e_unknown0x2d:
			m_unk0x20 = p_parser->ReadFloat();
			break;
		case GolFileParser::e_unknown0x31:
			m_unk0x24 = p_parser->ReadFloat();
			break;
		case GolFileParser::e_unknown0x32:
			m_unk0x28 = p_parser->ReadFloat();
			break;
		case GolFileParser::e_unknown0x33:
			m_unk0x2c = p_parser->ReadFloat();
			break;
		case GolFileParser::e_unknown0x2f:
			m_unk0x30 = p_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x30:
			m_unk0x34 = p_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x2a:
			m_unk0x08 = p_parser->ReadFloat();
			m_unk0x0c = p_parser->ReadFloat();
			m_unk0x10 = p_parser->ReadFloat();
			break;
		case GolFileParser::e_unknown0x2e:
			i = p_parser->ReadInteger();
			m_unk0x38 = &p_materialAnimation->GetUnk0x0c()[i];
			break;
		case GolFileParser::e_unknown0x34: {
			LegoChar materialName[8];
			strncpy(materialName, p_parser->ReadStringWithMaxLength(8), 8);
			m_unk0x40 = p_renderer->FindMaterialByName(materialName);
			break;
		}
		case GolFileParser::e_unknown0x2b:
			p_parser->ReadLeftBracket();
			m_unk0x04 = p_parser->ReadInteger();
			p_parser->ReadRightBracket();

			m_unk0x00 = new GolVec3[m_unk0x04];

			if (!m_unk0x00) {
				GolFatalError(c_golErrorOutOfMemory, NULL, 0);
			}
			p_parser->ReadLeftCurly();

			for (i = 0; i < m_unk0x04; i++) {
				m_unk0x00[i].m_x = p_parser->ReadFloat();
				m_unk0x00[i].m_y = p_parser->ReadFloat();
				m_unk0x00[i].m_z = p_parser->ReadFloat();
			}

			p_parser->ReadRightCurly();
			break;
		default:
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
		}
		token = p_parser->GetNextToken();
	}
}

// FUNCTION: LEGORACERS 0x0048a3b0
void CutsceneAnimation::Emitter::GetVectorAt(GolVec3* p_vec, int p_index)
{
	p_vec->m_x = m_unk0x00[p_index].m_x;
	p_vec->m_y = m_unk0x00[p_index].m_y;
	p_vec->m_z = m_unk0x00[p_index].m_z;
}

// FUNCTION: LEGORACERS 0x0048a3e0
void CutsceneAnimation::Emitter::GetOrigin(GolVec3* p_vec) const
{
	p_vec->m_x = m_unk0x08;
	p_vec->m_y = m_unk0x0c;
	p_vec->m_z = m_unk0x10;
}

// FUNCTION: LEGORACERS 0x0049fd70
CutsceneEvent::CutsceneEvent()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0049fdb0
CutsceneEvent::~CutsceneEvent()
{
	// empty
}

// FUNCTION: LEGORACERS 0x0049fdc0
void CutsceneEvent::Reset()
{
	m_parsedEntity = 0;
	m_entity = 0;
	m_animatedEntity = 0;
	m_disabled = 0;
}

// FUNCTION: LEGORACERS 0x0049fdd0
void CutsceneEvent::StartAt(const GolVec3*, const GolVec3*, const GolVec3*)
{
	if (m_disabled == 0) {
		Start();
	}
}

// FUNCTION: LEGORACERS 0x0049fde0
void CutsceneEvent::StartOnBsp(GolWorldEntity*)
{
	if (m_disabled == 0) {
		Start();
	}
}

// FUNCTION: LEGORACERS 0x0049fdf0
void CutsceneEvent::StartOnModel(GolWorldEntity* p_arg)
{
	if (m_disabled == 0) {
		StartOnBsp(p_arg);
	}
}

// FUNCTION: LEGORACERS 0x0049fe10
void CutsceneEvent::StartOnJointed(GolWorldEntity* p_arg)
{
	if (m_disabled == 0) {
		StartOnModel(p_arg);
	}
}

// FUNCTION: LEGORACERS 0x0049fe30
void CutsceneEvent::GetJointPosition(undefined4 p_param1, GolVec3* p_param2)
{
	m_animatedEntity->VTable0x5c(0);
	GolSceneNode* falconNode = m_animatedEntity->VTable0x58(0);

	GolVec3 vec1;
	GolVec3 vec2;
	vec1.m_x = 0.0f;
	vec1.m_y = 0.0f;
	vec1.m_z = 0.0f;

	falconNode->FUN_00413230(p_param1, &vec1, &vec2);

	LegoFloat scale = m_animatedEntity->GetModel(0)->GetScale() * m_animatedEntity->GetUnk0x58();
	vec2.m_x *= scale;
	vec2.m_y *= scale;
	vec2.m_z *= scale;
	m_animatedEntity->VTable0x2c(vec2, p_param2);
}

// FUNCTION: LEGORACERS 0x0049fec0
void CutsceneEvent::GetJointAxes(undefined4 p_param1, GolVec3* p_param2, GolVec3* p_param3)
{
	m_animatedEntity->VTable0x5c(0);
	GolSceneNode* falconNode = m_animatedEntity->VTable0x58(0);

	GolVec3 vec1;
	GolVec3 vec2;
	vec1.m_x = 1.0f;
	vec1.m_y = 0.0f;
	vec1.m_z = 0.0f;

	falconNode->FUN_004132a0(p_param1, &vec1, &vec2);
	m_animatedEntity->VTable0x34(vec2, p_param2);

	vec1.m_x = 0.0f;
	vec1.m_y = 0.0f;
	vec1.m_z = 1.0f;
	falconNode->FUN_004132a0(p_param1, &vec1, &vec2);
	m_animatedEntity->VTable0x34(vec2, p_param3);
}

// FUNCTION: LEGORACERS 0x0049ff70
void CutsceneEvent::ParseCommonToken(
	GolFileParser* p_parser,
	CutscenePlayer* p_owner,
	GolFileParser::ParserTokenType p_token
)
{
	GolName name;
	LegoChar text[64];
	::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));

	switch (p_token) {
	case GolFileParser::e_unknown0x5d:
		m_parsedEntity = p_owner->FindJointedEntity(name);
		m_entity = m_parsedEntity;
		m_animatedEntity = static_cast<GolAnimatedEntity*>(m_parsedEntity);
		if (m_parsedEntity) {
			return;
		}
		::strncpy(text, name, sizeof(GolName));
		text[sizeof(GolName)] = '\0';
		::strcat(text, ": unable to find jointed model");
		GOL_FATALERROR_MESSAGE(text);
		break;
	case GolFileParser::e_unknown0x5e:
		m_parsedEntity = p_owner->FindModelEntity(name);
		m_entity = m_parsedEntity;
		if (m_parsedEntity) {
			return;
		}
		::strncpy(text, name, sizeof(GolName));
		text[sizeof(GolName)] = '\0';
		::strcat(text, ": unable to find model");
		GOL_FATALERROR_MESSAGE(text);
		break;
	case GolFileParser::e_unknown0x5f:
		m_parsedEntity = p_owner->FindBspEntity(name);
		m_entity = m_parsedEntity;
		if (m_parsedEntity) {
			return;
		}
		::strncpy(text, name, sizeof(GolName));
		text[sizeof(GolName)] = '\0';
		::strcat(text, ": unable to find bsp model");
		GOL_FATALERROR_MESSAGE(text);
		break;
	default:
		p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
		break;
	}
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void CutsceneEvent::Start()
{
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void CutsceneEvent::Stop()
{
}

// FUNCTION: LEGORACERS 0x004a00b0 FOLDED
CutsceneEventLink::CutsceneEventLink()
{
	m_isStart = 0;
	m_event = NULL;
	m_next = NULL;
}

// FUNCTION: LEGORACERS 0x004a00c0
void CutsceneEventLink::Bind(undefined4 p_unk0x04, CutsceneEvent* p_event)
{
	m_isStart = p_unk0x04;
	m_event = p_event;
}

// FUNCTION: LEGORACERS 0x004a00d0
void CutsceneEventLink::Fire()
{
	if (m_isStart) {
		m_event->Start();
	}
	else {
		m_event->Stop();
	}
}

// FUNCTION: LEGORACERS 0x004a00f0
void CutsceneEventLink::Fire(CutsceneCameraEventView* p_payload)
{
	GolWorldEntity* value = p_payload->m_target->m_entity;
	if (value) {
		if (m_isStart) {
			m_event->StartOnJointed(value);
		}
		else {
			m_event->Stop();
		}
	}
	else {
		Fire();
	}
}

// FUNCTION: LEGORACERS 0x004a0120
void CutsceneEventLink::Fire(CutsceneModelEventView* p_payload)
{
	if (p_payload->m_modelType == 2) {
		if (m_isStart) {
			m_event->StartOnJointed(p_payload->m_entity);
		}
		else {
			m_event->Stop();
		}
	}
	else if (p_payload->m_modelType == 3 || p_payload->m_modelType == 1) {
		if (m_isStart) {
			m_event->StartOnModel(p_payload->m_entity);
		}
		else {
			m_event->Stop();
		}
	}
	else {
		if (m_isStart) {
			m_event->StartOnBsp(p_payload->m_entity);
		}
		else {
			m_event->Stop();
		}
	}
}

// FUNCTION: LEGORACERS 0x004a0180
void CutsceneEventLink::Fire(CutsceneTransformEventView* p_payload)
{
	GolVec3 vector0 = p_payload->m_position;
	GolVec3 vector1 = p_payload->m_direction;
	GolVec3 vector2 = p_payload->m_up;

	if (m_isStart) {
		m_event->StartAt(&vector0, &vector1, &vector2);
	}
	else {
		m_event->Stop();
	}
}

// FUNCTION: LEGORACERS 0x004a0200
void CutsceneEventLink::Fire(void*)
{
	Fire();
}

// FUNCTION: LEGORACERS 0x004a0210
CutscenePlayer::CutscenePlayer()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a03b0
CutscenePlayer::~CutscenePlayer()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x004a0530
void CutscenePlayer::Reset()
{
	m_golExport = NULL;
	m_renderer = 0;
	m_soundManager = NULL;
	m_definition = 0;
	m_menuAnimations = NULL;
	m_animationCount = 0;
	m_animations = NULL;
	m_materialAnimations = NULL;
	m_animationNames = NULL;
	m_stringTableCount = 0;
	m_stringTables = NULL;
	m_stringTableNames = NULL;
	m_soundGroupCount = 0;
	m_soundGroups = NULL;
	m_soundGroupNames = NULL;
	m_fontTableCount = 0;
	m_fontTables = NULL;
	m_fontTableNames = NULL;
	m_imageListCount = 0;
	m_imageLists = NULL;
	m_imageListNames = NULL;
	m_moveEventCount = 0;
	m_moveEvents = NULL;
	m_soundEventCount = 0;
	m_soundEvents = NULL;
	m_streamEventCount = 0;
	m_streamEvents = NULL;
	m_animEventCount = 0;
	m_animEvents = NULL;
	m_menuAnimEventCount = 0;
	m_menuAnimEvents = NULL;
	m_textVisualCount = 0;
	m_textVisuals = NULL;
	m_imageVisualCount = 0;
	m_imageVisuals = NULL;
	m_eventStartedCount = 0;
	m_eventStartedLinks = NULL;
	m_eventEndedCount = 0;
	m_eventEndedLinks = NULL;
	m_cameraStartedCount = 0;
	m_cameraStartedLinks = NULL;
	m_cameraEndedCount = 0;
	m_cameraEndedLinks = NULL;
	m_modelStartedCount = 0;
	m_modelStartedLinks = NULL;
	m_modelEndedCount = 0;
	m_modelEndedLinks = NULL;
	m_transformStartedCount = 0;
	m_transformStartedLinks = NULL;
	m_transformEndedCount = 0;
	m_transformEndedLinks = NULL;
	m_ambientStartedCount = 0;
	m_ambientStartedLinks = NULL;
	m_ambientEndedCount = 0;
	m_ambientEndedLinks = NULL;
	m_directionalStartedCount = 0;
	m_directionalStartedLinks = NULL;
	m_directionalEndedCount = 0;
	m_directionalEndedLinks = NULL;
	m_stringTable = NULL;
}

// FUNCTION: LEGORACERS 0x004a0680
LegoBool32 CutscenePlayer::HasFileWithSuffix(const LegoChar* p_fileName, const LegoChar* p_suffix)
{
	LegoU32 length = ::strlen(p_fileName) + ::strlen(p_suffix) + 1;
	LegoChar* path = new LegoChar[length];
	if (path == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	::strcpy(path, p_fileName);
	::strcat(path, p_suffix);

	LegoS32 result = GolStream::FindFile(path);
	delete[] path;

	return result == GolStream::e_ioSuccess;
}

// FUNCTION: LEGORACERS 0x004a0730
void CutscenePlayer::Load(
	GolExport* p_golExport,
	GolD3DRenderDevice* p_renderer,
	SoundManager* p_soundManager,
	CutsceneDefinition* p_unk0x10,
	const LegoChar* p_fileName,
	undefined4 p_binary
)
{
	GolFileParser* parser;

	if (m_golExport) {
		Clear();
	}

	if (p_binary) {
		if (!HasFileWithSuffix(p_fileName, ".ceb")) {
			return;
		}
		parser = new GolBinParser();
		if (!parser) {
			GolFatalError(c_golErrorOutOfMemory, NULL, 0);
		}
		parser->SetSuffix(".ceb");
	}
	else {
		parser = new CebTxtParser();
		if (!parser) {
			GolFatalError(c_golErrorOutOfMemory, NULL, 0);
		}
		if (!HasFileWithSuffix(p_fileName, parser->GetSuffix())) {
			delete parser;
			return;
		}
	}

	m_golExport = p_golExport;
	m_renderer = p_renderer;
	m_definition = p_unk0x10;
	m_soundManager = p_soundManager;

	p_soundManager->AddActiveSoundNode(&m_listener);
	parser->OpenFileForRead(p_fileName);
	GolFileParser::ParserTokenType token = parser->GetNextToken();
	while (token != GolFileParser::e_syntaxerror) {
		switch (token) {
		case GolFileParser::e_unknown0x27:
			ParseAnimationNames(parser);
			break;
		case GolFileParser::e_unknown0x28:
			ParseStringTableNames(parser);
			break;
		case GolFileParser::e_unknown0x5c:
			ParseSoundGroupNames(parser);
			break;
		case GolFileParser::e_unknown0x29:
			ParseFontTableNames(parser);
			break;
		case GolFileParser::e_unknown0x2a:
			ParseImageListNames(parser);
			break;
		case GolFileParser::e_unknown0x2b:
			ParseMoveEvents(parser);
			break;
		case GolFileParser::e_unknown0x2f:
			ParseSoundEvents(parser);
			break;
		case GolFileParser::e_unknown0x36:
			ParseStreamEvents(parser);
			break;
		case GolFileParser::e_unknown0x3c:
			ParseAnimationEvents(parser);
			break;
		case GolFileParser::e_unknown0x60:
			ParseMenuAnimationEvents(parser);
			break;
		case GolFileParser::e_unknown0x3f:
			ParseTextVisuals(parser);
			break;
		case GolFileParser::e_unknown0x4d:
			ParseImageVisuals(parser);
			break;
		case GolFileParser::e_unknown0x50:
			ParseTriggerChannel(parser, 0x50, m_eventStartedCount, m_eventStartedLinks, m_eventStartedNames);
			break;
		case GolFileParser::e_unknown0x51:
			ParseTriggerChannel(parser, 0x51, m_eventEndedCount, m_eventEndedLinks, m_eventEndedNames);
			break;
		case GolFileParser::e_unknown0x52:
			ParseTriggerChannel(parser, 0x52, m_cameraStartedCount, m_cameraStartedLinks, m_cameraStartedNames);
			break;
		case GolFileParser::e_unknown0x53:
			ParseTriggerChannel(parser, 0x53, m_cameraEndedCount, m_cameraEndedLinks, m_cameraEndedNames);
			break;
		case GolFileParser::e_unknown0x54:
			ParseTriggerChannel(parser, 0x54, m_modelStartedCount, m_modelStartedLinks, m_modelStartedNames);
			break;
		case GolFileParser::e_unknown0x55:
			ParseTriggerChannel(parser, 0x55, m_modelEndedCount, m_modelEndedLinks, m_modelEndedNames);
			break;
		case GolFileParser::e_unknown0x56:
			ParseTriggerChannel(
				parser,
				0x56,
				m_transformStartedCount,
				m_transformStartedLinks,
				m_transformStartedNames
			);
			break;
		case GolFileParser::e_unknown0x57:
			ParseTriggerChannel(parser, 0x57, m_transformEndedCount, m_transformEndedLinks, m_transformEndedNames);
			break;
		case GolFileParser::e_unknown0x58:
			ParseTriggerChannel(parser, 0x58, m_ambientStartedCount, m_ambientStartedLinks, m_ambientStartedNames);
			break;
		case GolFileParser::e_unknown0x59:
			ParseTriggerChannel(parser, 0x59, m_ambientEndedCount, m_ambientEndedLinks, m_ambientEndedNames);
			break;
		case GolFileParser::e_unknown0x5a:
			ParseTriggerChannel(
				parser,
				0x5a,
				m_directionalStartedCount,
				m_directionalStartedLinks,
				m_directionalStartedNames
			);
			break;
		case GolFileParser::e_unknown0x5b:
			ParseTriggerChannel(
				parser,
				0x5b,
				m_directionalEndedCount,
				m_directionalEndedLinks,
				m_directionalEndedNames
			);
			break;
		default:
			parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}
		token = parser->GetNextToken();
	}

	parser->Dispose();
	delete parser;

	LoadAnimations(p_binary);
	LoadStringTables();
	LoadSoundGroups();
	LoadFontTables(p_binary);
	LoadImageLists(p_binary);
	RefreshTextVisuals();
	LoadImageVisuals();
}

// FUNCTION: LEGORACERS 0x004a0bf0
void CutscenePlayer::Clear()
{
	LegoU32 i;

	if (m_soundManager) {
		m_soundManager->RemoveActiveSoundNode(&m_listener);
	}

	if (m_soundGroups) {
		for (i = 0; i < m_soundGroupCount; i++) {
			if (m_soundGroups[i]) {
				m_soundManager->DestroySoundGroup(m_soundGroups[i]);
			}
		}
		delete[] m_soundGroups;
	}

	if (m_soundGroupNames) {
		delete m_soundGroupNames;
	}

	if (m_fontTables) {
		for (i = 0; i < m_fontTableCount; i++) {
			if (m_fontTables[i]) {
				m_golExport->DestroyFontTable(m_fontTables[i]);
			}
		}
		delete[] m_fontTables;
	}

	if (m_fontTableNames) {
		delete m_fontTableNames;
	}

	if (m_imageLists) {
		for (i = 0; i < m_imageListCount; i++) {
			if (m_imageLists[i]) {
				m_golExport->VTable0x68(m_imageLists[i]);
			}
		}
		delete m_imageLists;
	}
	if (m_imageListNames) {
		delete m_imageListNames;
	}
	if (m_animations) {
		delete[] m_animations;
	}
	if (m_animationNames) {
		delete m_animationNames;
	}
	if (m_materialAnimations) {
		delete[] m_materialAnimations;
	}
	if (m_stringTables) {
		delete[] m_stringTables;
	}
	if (m_stringTableNames) {
		delete m_stringTableNames;
	}
	if (m_moveEvents) {
		delete[] m_moveEvents;
	}
	if (m_soundEvents) {
		delete[] m_soundEvents;
	}
	if (m_streamEvents) {
		delete[] m_streamEvents;
	}
	if (m_animEvents) {
		delete[] m_animEvents;
	}
	if (m_menuAnimations) {
		delete m_menuAnimations;
	}
	if (m_menuAnimEvents) {
		delete[] m_menuAnimEvents;
	}
	if (m_textVisuals) {
		delete[] m_textVisuals;
	}
	if (m_imageVisuals) {
		delete[] m_imageVisuals;
	}
	if (m_eventStartedLinks) {
		delete m_eventStartedLinks;
	}
	if (m_eventEndedLinks) {
		delete m_eventEndedLinks;
	}
	if (m_cameraStartedLinks) {
		delete m_cameraStartedLinks;
	}
	if (m_cameraEndedLinks) {
		delete m_cameraEndedLinks;
	}
	if (m_modelStartedLinks) {
		delete m_modelStartedLinks;
	}
	if (m_modelEndedLinks) {
		delete m_modelEndedLinks;
	}
	if (m_transformStartedLinks) {
		delete m_transformStartedLinks;
	}
	if (m_transformEndedLinks) {
		delete m_transformEndedLinks;
	}
	if (m_ambientStartedLinks) {
		delete m_ambientStartedLinks;
	}
	if (m_ambientEndedLinks) {
		delete m_ambientEndedLinks;
	}
	if (m_directionalStartedLinks) {
		delete m_directionalStartedLinks;
	}
	if (m_directionalEndedLinks) {
		delete m_directionalEndedLinks;
	}
	m_moveEventNames.Clear();
	m_soundEventNames.Clear();
	m_streamEventNames.Clear();
	m_animEventNames.Clear();
	m_menuAnimEventNames.Clear();
	m_textVisualNames.Clear();
	m_imageVisualNames.Clear();
	m_eventStartedNames.Clear();
	m_eventEndedNames.Clear();
	m_cameraStartedNames.Clear();
	m_cameraEndedNames.Clear();
	m_modelStartedNames.Clear();
	m_modelEndedNames.Clear();
	m_transformStartedNames.Clear();
	m_transformEndedNames.Clear();
	m_ambientStartedNames.Clear();
	m_ambientEndedNames.Clear();
	m_directionalStartedNames.Clear();
	m_directionalEndedNames.Clear();

	Reset();
}

// FUNCTION: LEGORACERS 0x004a0ff0
void CutscenePlayer::ParseAnimationNames(GolFileParser* p_parser)
{
	if (m_animations != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_animationCount = p_parser->ReadInteger();
	if (m_animationCount == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_animations = new CutsceneAnimation[m_animationCount];
	m_materialAnimations = new MabMaterialAnimation0x14[m_animationCount];
	m_animationNames = new LegoChar[m_animationCount * 9];
	if (m_animations == NULL || m_materialAnimations == NULL || m_animationNames == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoU32 i = 0;

	if (i < m_animationCount) {
		LegoU32 offset = 0;

		do {
			::strncpy(&m_animationNames[offset], p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
			i++;
			m_animationNames[offset + sizeof(GolName)] = '\0';
			offset += 9;
		} while (i < m_animationCount);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a1240
void CutscenePlayer::LoadAnimations(undefined4 p_binary)
{
	if (m_animationNames != NULL) {
		for (LegoU32 i = 0; i < m_animationCount; i++) {
			m_materialAnimations[i].VTable0x04(m_renderer, &m_animationNames[i * 9], p_binary);
			m_animations[i]
				.Load(3, m_golExport, m_renderer, &m_materialAnimations[i], &m_animationNames[i * 9], p_binary);
		}

		delete[] m_animationNames;
		m_animationNames = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004a12e0
void CutscenePlayer::ParseStringTableNames(GolFileParser* p_parser)
{
	if (m_stringTables != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_stringTableCount = p_parser->ReadInteger();
	if (m_stringTableCount == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_stringTables = new GolStringTable[m_stringTableCount];
	m_stringTableNames = new LegoChar[m_stringTableCount * 13];
	if (m_stringTables == NULL || m_stringTableNames == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_stringTableCount; i++) {
		::strncpy(&m_stringTableNames[i * 13], p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		m_stringTableNames[i * 13 + sizeof(GolName)] = '\0';
		::strcat(&m_stringTableNames[i * 13], ".srf");

		m_stringTables[i].UseOwnedBuffers();
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a14e0
void CutscenePlayer::LoadStringTables()
{
	if (m_stringTableNames != NULL) {
		LegoU32 i = 0;

		if (i < m_stringTableCount) {
			LegoU32 fileNameOffset = 0;

			do {
				m_stringTables[i].UseOwnedBuffers();

				if (!m_stringTables[i].Load(&m_stringTableNames[fileNameOffset])) {
					LegoChar text[48];
					::strcpy(text, "Unable to open: ");
					::strcat(text, &m_stringTableNames[fileNameOffset]);
					GOL_FATALERROR_MESSAGE(text);
				}

				i++;
				fileNameOffset += 13;
			} while (i < m_stringTableCount);
		}

		delete[] m_stringTableNames;
		m_stringTableNames = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004a15e0
void CutscenePlayer::ParseSoundGroupNames(GolFileParser* p_parser)
{
	if (m_soundGroups != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_soundGroupCount = p_parser->ReadInteger();
	if (m_soundGroupCount == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_soundGroups = new SoundGroup*[m_soundGroupCount];
	if (m_soundGroups == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_soundGroupNames = new LegoChar[m_soundGroupCount * 9];
	if (m_soundGroupNames == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoU32 i = 0;

	if (i < m_soundGroupCount) {
		LegoU32 offset = 0;

		do {
			::strncpy(&m_soundGroupNames[offset], p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
			m_soundGroupNames[offset + sizeof(GolName)] = '\0';

			SoundGroup* soundGroup = m_soundManager->CreateSoundGroup();
			i++;
			offset += 9;
			m_soundGroups[i - 1] = soundGroup;
		} while (i < m_soundGroupCount);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a16f0
void CutscenePlayer::LoadSoundGroups()
{
	if (m_soundGroupNames != NULL) {
		for (LegoU32 i = 0; i < m_soundGroupCount; i++) {
			m_soundGroups[i]->Load(&m_soundGroupNames[i * 9]);
		}

		delete[] m_soundGroupNames;
		m_soundGroupNames = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004a1760
void CutscenePlayer::ParseFontTableNames(GolFileParser* p_parser)
{
	if (m_fontTables != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_fontTableCount = p_parser->ReadInteger();
	if (m_fontTableCount == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_fontTables = new GolFontTable*[m_fontTableCount];
	m_fontTableNames = new LegoChar[m_fontTableCount * 9];
	if (m_fontTables == NULL || m_fontTableNames == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoU32 i = 0;

	if (i < m_fontTableCount) {
		LegoU32 offset = 0;

		do {
			::strncpy(&m_fontTableNames[offset], p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
			i++;
			m_fontTableNames[offset + sizeof(GolName)] = '\0';
			offset += 9;
		} while (i < m_fontTableCount);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a1850
void CutscenePlayer::LoadFontTables(undefined4 p_binary)
{
	if (m_fontTableNames != NULL) {
		for (LegoU32 i = 0; i < m_fontTableCount; i++) {
			m_fontTables[i] = m_golExport->CreateFontTable();
			m_fontTables[i]->LoadFontDefinitions(m_renderer, &m_fontTableNames[i * 9], p_binary);
		}

		delete[] m_fontTableNames;
		m_fontTableNames = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004a18d0
void CutscenePlayer::ParseImageListNames(GolFileParser* p_parser)
{
	if (m_imageLists != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_imageListCount = p_parser->ReadInteger();
	if (m_imageListCount == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_imageLists = new AwakeKite0x20*[m_imageListCount];
	m_imageListNames = new LegoChar[m_imageListCount * 9];
	if (m_imageLists == NULL || m_imageListNames == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoU32 i = 0;

	if (i < m_imageListCount) {
		LegoU32 offset = 0;

		do {
			::strncpy(&m_imageListNames[offset], p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
			i++;
			m_imageListNames[offset + sizeof(GolName)] = '\0';
			offset += 9;
		} while (i < m_imageListCount);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a19c0
void CutscenePlayer::LoadImageLists(undefined4 p_binary)
{
	if (m_imageListNames != NULL) {
		for (LegoU32 i = 0; i < m_imageListCount; i++) {
			m_imageLists[i] = m_golExport->VTable0x34();
			m_imageLists[i]->LoadImageDefinitions(m_renderer, &m_imageListNames[i * 9], p_binary);
		}

		delete[] m_imageListNames;
		m_imageListNames = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004a1a40
void CutscenePlayer::ParseMoveEvents(GolFileParser* p_parser)
{
	if (m_moveEvents != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_moveEventCount = p_parser->ReadInteger();
	if (m_moveEventCount == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_moveEventNames.Allocate(m_moveEventCount);
	m_moveEvents = new CutsceneColorEvent[m_moveEventCount];
	if (m_moveEvents == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_moveEventCount; i++) {
		GolName name;

		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x2b);
		::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		m_moveEventNames.AddName(name, &m_moveEvents[i]);
		m_moveEvents[i].Parse(p_parser, this);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a1c00
void CutscenePlayer::ParseSoundEvents(GolFileParser* p_parser)
{
	if (m_soundEvents != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_soundEventCount = p_parser->ReadInteger();
	if (m_soundEventCount == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_soundEventNames.Allocate(m_soundEventCount);
	m_soundEvents = new CutsceneSoundEvent[m_soundEventCount];
	if (m_soundEvents == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_soundEventCount; i++) {
		GolName name;

		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x2f);
		::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		m_soundEventNames.AddName(name, &m_soundEvents[i]);
		m_soundEvents[i].Parse(p_parser, this);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a1dc0
void CutscenePlayer::ParseStreamEvents(GolFileParser* p_parser)
{
	if (m_streamEvents != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_streamEventCount = p_parser->ReadInteger();
	if (m_streamEventCount == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_streamEventNames.Allocate(m_streamEventCount);
	m_streamEvents = new CutsceneStreamingSoundEvent[m_streamEventCount];
	if (m_streamEvents == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_streamEventCount; i++) {
		GolName name;

		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x36);
		::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		m_streamEventNames.AddName(name, &m_streamEvents[i]);
		m_streamEvents[i].Parse(p_parser, this);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a1f80
void CutscenePlayer::ParseAnimationEvents(GolFileParser* p_parser)
{
	if (m_animEvents != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_animEventCount = p_parser->ReadInteger();
	if (m_animEventCount == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_animEventNames.Allocate(m_animEventCount);
	m_animEvents = new CutsceneAnimationEvent[m_animEventCount];
	if (m_animEvents == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_animEventCount; i++) {
		GolName name;

		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x3c);
		::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		m_animEventNames.AddName(name, &m_animEvents[i]);
		m_animEvents[i].Parse(p_parser, this);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a20f0
void CutscenePlayer::ParseMenuAnimationEvents(GolFileParser* p_parser)
{
	if (m_menuAnimEvents != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_menuAnimEventCount = p_parser->ReadInteger();
	if (m_menuAnimEventCount == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_menuAnimEventNames.Allocate(m_menuAnimEventCount);
	m_menuAnimEvents = new CutsceneMenuAnimationEvent[m_menuAnimEventCount];
	m_menuAnimations = new MenuAnimationList();
	if (m_menuAnimEvents == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	if (m_menuAnimations == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_menuAnimations->Allocate(2);

	for (LegoU32 i = 0; i < m_menuAnimEventCount; i++) {
		GolName name;

		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x60);
		::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		m_menuAnimEventNames.AddName(name, &m_menuAnimEvents[i]);
		m_menuAnimEvents[i].Parse(p_parser, this, m_menuAnimations, m_renderer);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a2310
void CutscenePlayer::ParseTextVisuals(GolFileParser* p_parser)
{
	if (m_textVisuals != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_textVisualCount = p_parser->ReadInteger();
	if (m_textVisualCount == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_textVisualNames.Allocate(m_textVisualCount);
	m_textVisuals = new CutsceneTextVisual[m_textVisualCount];
	if (m_textVisuals == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_textVisualCount; i++) {
		GolName name;

		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x3f);
		::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		m_textVisualNames.AddName(name, &m_textVisuals[i]);
		m_textVisuals[i].Parse(p_parser, this, m_renderer);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a24e0
void CutscenePlayer::RefreshTextVisuals()
{
	for (LegoU32 i = 0; i < m_textVisualCount; i++) {
		m_textVisuals[i].RefreshString(this, m_renderer);
	}
}

// FUNCTION: LEGORACERS 0x004a2520
void CutscenePlayer::ParseImageVisuals(GolFileParser* p_parser)
{
	if (m_imageVisuals != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_imageVisualCount = p_parser->ReadInteger();
	if (m_imageVisualCount == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_imageVisualNames.Allocate(m_imageVisualCount);
	m_imageVisuals = new CutsceneImageVisual[m_imageVisualCount];
	if (m_imageVisuals == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_imageVisualCount; i++) {
		GolName name;

		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x4d);
		::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		m_imageVisualNames.AddName(name, &m_imageVisuals[i]);
		m_imageVisuals[i].Parse(p_parser, this, m_renderer);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a26f0
void CutscenePlayer::LoadImageVisuals()
{
	for (LegoU32 i = 0; i < m_imageVisualCount; i++) {
		m_imageVisuals[i].ResolveImage(m_renderer);
	}
}

// FUNCTION: LEGORACERS 0x004a2730
void CutscenePlayer::ParseTriggerChannel(
	GolFileParser* p_parser,
	LegoU32 p_token,
	undefined4& p_unk0x08,
	CutsceneEventLink*& p_unk0x0c,
	GolNameTable& p_unk0x10
)
{
	CutsceneEvent* event = NULL;
	undefined4 mode = 0;

	if (p_unk0x0c != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	LegoU32 count = p_parser->ReadInteger();
	if (count == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	p_unk0x08 = count;
	p_unk0x10.Allocate(count);

	CutsceneEventLink* links = new CutsceneEventLink[count];
	if (links == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	p_unk0x0c = links;

	CutsceneEventLink* link = links;
	CutsceneEventLink* end = links + count;
	while (link < end) {
		GolName name;

		p_parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(p_token));
		::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));

		CutsceneEventLink* existing = static_cast<CutsceneEventLink*>(p_unk0x10.GetName(name));
		if (existing != NULL) {
			link->SetNext(existing->GetNext());
			existing->SetNext(link);
		}
		else {
			p_unk0x10.AddName(name, link);
		}

		p_parser->ReadLeftCurly();

		GolFileParser::ParserTokenType targetToken = p_parser->GetNextToken();
		GolFileParser::ParserTokenType modeToken = p_parser->GetNextToken();
		if (modeToken == GolFileParser::e_unknown0x4e) {
			mode = 1;
		}
		else if (modeToken == GolFileParser::e_unknown0x4f) {
			mode = 0;
		}
		else {
			p_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName targetName;
		::strncpy(targetName, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));

		switch (targetToken) {
		case GolFileParser::e_unknown0x2b:
			event = static_cast<CutsceneEvent*>(m_moveEventNames.GetName(targetName));
			break;
		case GolFileParser::e_unknown0x2f:
			event = static_cast<CutsceneEvent*>(m_soundEventNames.GetName(targetName));
			break;
		case GolFileParser::e_unknown0x36:
			event = static_cast<CutsceneEvent*>(m_streamEventNames.GetName(targetName));
			break;
		case GolFileParser::e_unknown0x3c:
			event = static_cast<CutsceneEvent*>(m_animEventNames.GetName(targetName));
			break;
		case GolFileParser::e_unknown0x60:
			event = static_cast<CutsceneEvent*>(m_menuAnimEventNames.GetName(targetName));
			break;
		case GolFileParser::e_unknown0x3f:
			event = static_cast<CutsceneEvent*>(m_textVisualNames.GetName(targetName));
			break;
		case GolFileParser::e_unknown0x4d:
			event = static_cast<CutsceneEvent*>(m_imageVisualNames.GetName(targetName));
			break;
		default:
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}

		if (event == NULL) {
			LegoChar text[64];
			::strncpy(text, targetName, sizeof(GolName));
			text[sizeof(GolName)] = '\0';
			::strcat(text, ": Unable to find effect");
			GOL_FATALERROR_MESSAGE(text);
		}

		link->Bind(mode, event);
		p_parser->ReadRightCurly();
		link++;
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a2ac0
void CutscenePlayer::OnEventStarted(void*, void* p_name, void*)
{
	if (m_eventStartedNames.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_eventStartedNames.GetName(static_cast<const LegoChar*>(p_name)));
		while (link != NULL) {
			link->Fire();
			link = link->GetNext();
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2b00
void CutscenePlayer::OnEventEnded(void*, void* p_name, void*)
{
	if (m_eventEndedNames.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_eventEndedNames.GetName(static_cast<const LegoChar*>(p_name)));
		while (link != NULL) {
			link->Fire();
			link = link->GetNext();
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2b40
void CutscenePlayer::OnCameraStarted(void*, void* p_name, void* p_payload)
{
	if (m_cameraStartedNames.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_cameraStartedNames.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			CutsceneCameraEventView* payload = static_cast<CutsceneCameraEventView*>(p_payload);

			while (link != NULL) {
				link->Fire(payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2b80
void CutscenePlayer::OnCameraEnded(void*, void* p_name, void* p_payload)
{
	if (m_cameraEndedNames.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_cameraEndedNames.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			CutsceneCameraEventView* payload = static_cast<CutsceneCameraEventView*>(p_payload);

			while (link != NULL) {
				link->Fire(payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2bc0
void CutscenePlayer::OnModelStarted(void*, void* p_name, void* p_payload)
{
	if (m_modelStartedNames.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_modelStartedNames.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			CutsceneModelEventView* payload = static_cast<CutsceneModelEventView*>(p_payload);

			while (link != NULL) {
				link->Fire(payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2c00
void CutscenePlayer::OnModelEnded(void*, void* p_name, void* p_payload)
{
	if (m_modelEndedNames.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_modelEndedNames.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			CutsceneModelEventView* payload = static_cast<CutsceneModelEventView*>(p_payload);

			while (link != NULL) {
				link->Fire(payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2c40
void CutscenePlayer::OnTransformStarted(void*, void* p_name, void* p_payload)
{
	if (m_transformStartedNames.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_transformStartedNames.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			CutsceneTransformEventView* payload = static_cast<CutsceneTransformEventView*>(p_payload);

			while (link != NULL) {
				link->Fire(payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2c80
void CutscenePlayer::OnTransformEnded(void*, void* p_name, void* p_payload)
{
	if (m_transformEndedNames.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_transformEndedNames.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			CutsceneTransformEventView* payload = static_cast<CutsceneTransformEventView*>(p_payload);

			while (link != NULL) {
				link->Fire(payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2cc0
void CutscenePlayer::OnAmbientLightStarted(void*, void* p_name, void* p_payload)
{
	if (m_ambientStartedNames.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_ambientStartedNames.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			while (link != NULL) {
				link->Fire(p_payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2d00
void CutscenePlayer::OnAmbientLightEnded(void*, void* p_name, void* p_payload)
{
	if (m_ambientEndedNames.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_ambientEndedNames.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			while (link != NULL) {
				link->Fire(p_payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2d40
void CutscenePlayer::OnDirectionalLightStarted(void*, void* p_name, void* p_payload)
{
	if (m_directionalStartedNames.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_directionalStartedNames.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			while (link != NULL) {
				link->Fire(p_payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2d80
void CutscenePlayer::OnDirectionalLightEnded(void*, void* p_name, void* p_payload)
{
	if (m_directionalEndedNames.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_directionalEndedNames.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			while (link != NULL) {
				link->Fire(p_payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2dc0
void CutscenePlayer::Update(LegoU32 p_elapsedMs)
{
	if (m_golExport != NULL) {
		LegoFloat elapsedSeconds = static_cast<LegoS32>(p_elapsedMs) * 0.001f;
		LegoU32 i;

		for (i = 0; i < m_moveEventCount; i++) {
			m_moveEvents[i].Update(elapsedSeconds);
		}

		for (i = 0; i < m_soundEventCount; i++) {
			m_soundEvents[i].Update();
		}

		for (i = 0; i < m_streamEventCount; i++) {
			m_streamEvents[i].Update();
		}

		for (i = 0; i < m_animationCount; i++) {
			CutsceneAnimation* entries = m_animations;
			entries[i].Update(p_elapsedMs);
		}

		for (i = 0; i < m_textVisualCount; i++) {
			m_textVisuals[i].Update(elapsedSeconds);
		}

		for (i = 0; i < m_imageVisualCount; i++) {
			m_imageVisuals[i].Update(elapsedSeconds);
		}

		for (i = 0; i < m_animEventCount; i++) {
			m_animEvents[i].Update(p_elapsedMs);
		}

		if (m_menuAnimations != NULL) {
			m_menuAnimations->Update(p_elapsedMs);
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2f30
void CutscenePlayer::Draw(GolD3DRenderDevice* p_renderer)
{
	if (m_golExport != NULL) {
		UpdateListener(p_renderer->GetUnk0x0c());

		for (LegoU32 i = 0; i < m_animationCount; i++) {
			m_animations[i].Draw(p_renderer);
		}
	}
}

// STUB: LEGORACERS 0x004a2f80
void CutscenePlayer::UpdateListener(GolCamera* p_lens)
{
	GolVec3 position;
	GolVec3 right;
	GolVec3 forward;

	p_lens->GetTransform()->GetPosition(&position);
	p_lens->GetTransform()->GetRight(&right);
	p_lens->GetTransform()->GetForward(&forward);

	SoundNode* node = &m_listener;

	node->m_position.m_x = position.m_x;
	node->m_position.m_y = position.m_y;
	node->m_position.m_z = position.m_z;
	node->m_unk0x44 = 1;

	forward.m_x = -forward.m_x;
	forward.m_y = -forward.m_y;
	forward.m_z = -forward.m_z;

	node->m_right.m_x = right.m_x;
	node->m_right.m_y = right.m_y;
	node->m_right.m_z = right.m_z;
	node->m_forward.m_x = forward.m_x;
	node->m_forward.m_y = forward.m_y;
	node->m_forward.m_z = forward.m_z;

	node->m_orientation.m_x = (node->m_forward.m_y * node->m_right.m_z) - (node->m_forward.m_z * node->m_right.m_y);
	node->m_orientation.m_y = (node->m_forward.m_z * node->m_right.m_x) - (node->m_right.m_z * node->m_forward.m_x);
	node->m_orientation.m_z = (node->m_right.m_y * node->m_forward.m_x) - (node->m_forward.m_y * node->m_right.m_x);

	GolVec3 orientation;
	orientation.m_x = node->m_orientation.m_x;
	orientation.m_y = node->m_orientation.m_y;
	orientation.m_z = node->m_orientation.m_z;
	GolMath::NormalizeVector3(orientation, &orientation);
	node->m_orientation.m_x = orientation.m_x;
	node->m_orientation.m_y = orientation.m_y;
	node->m_orientation.m_z = orientation.m_z;

	node->m_unk0x44 = 1;
}

// FUNCTION: LEGORACERS 0x004a3070
void CutscenePlayer::DrawTransparent(GolD3DRenderDevice* p_renderer)
{
	if (m_golExport != NULL) {
		for (LegoU32 i = 0; i < m_animationCount; i++) {
			m_animations[i].DrawTransparent(p_renderer);
		}
	}
}

// FUNCTION: LEGORACERS 0x004a30b0
void CutscenePlayer::DrawOverlay(GolD3DRenderDevice* p_renderer)
{
	if (m_golExport != NULL) {
		p_renderer->VTable0xe8(FALSE);

		LegoU32 i;
		for (i = 0; i < m_imageVisualCount; i++) {
			m_imageVisuals[i].Draw(p_renderer);
		}

		for (i = 0; i < m_textVisualCount; i++) {
			m_textVisuals[i].Draw(p_renderer);
		}

		if (m_menuAnimations != NULL) {
			m_menuAnimations->Draw(p_renderer);
		}

		p_renderer->VTable0xe4();
	}
}

// FUNCTION: LEGORACERS 0x004a3150
void CutscenePlayer::StopAll()
{
	LegoU32 i;

	for (i = 0; i < m_moveEventCount; i++) {
		m_moveEvents[i].Stop();
	}

	for (i = 0; i < m_soundEventCount; i++) {
		m_soundEvents[i].Stop();
	}

	for (i = 0; i < m_streamEventCount; i++) {
		m_streamEvents[i].Stop();
	}

	for (i = 0; i < m_textVisualCount; i++) {
		m_textVisuals[i].Stop();
	}

	for (i = 0; i < m_imageVisualCount; i++) {
		m_imageVisuals[i].Stop();
	}
}

// FUNCTION: LEGORACERS 0x004a3230
GolWorldEntity* CutscenePlayer::FindModelEntity(const LegoChar* p_name)
{
	return m_definition->FUN_00406e30(p_name);
}

// FUNCTION: LEGORACERS 0x004a3240
GolWorldEntity* CutscenePlayer::FindJointedEntity(const LegoChar* p_name)
{
	return m_definition->FUN_00406e80(p_name);
}

// FUNCTION: LEGORACERS 0x004a3250
GolWorldEntity* CutscenePlayer::FindBspEntity(const LegoChar* p_name)
{
	return m_definition->FUN_00406ed0(p_name);
}

// FUNCTION: LEGORACERS 0x004a3260
GolStringTable* CutscenePlayer::GetStringTableByIndex(LegoU32 p_index)
{
	if (p_index == 0 && m_stringTable != NULL) {
		return m_stringTable;
	}

	return &m_stringTables[p_index];
}

// FUNCTION: LEGORACERS 0x004a37e0
CutsceneImageVisual::CutsceneImageVisual()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a3830
CutsceneImageVisual::~CutsceneImageVisual()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x004a3880
void CutsceneImageVisual::Reset()
{
	m_image = NULL;
	m_imageName[0] = '\0';
	CutsceneVisual::Reset();
}

// FUNCTION: LEGORACERS 0x004a3890
void CutsceneImageVisual::Parse(GolFileParser* p_parser, CutscenePlayer* p_owner, GolRenderDevice* p_renderer)
{
	p_parser->ReadLeftCurly();
	m_flags = 3;

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	if (token != GolFileParser::e_rightCurly) {
		do {
			if (token != GolFileParser::e_unknown0x4d) {
				ParseVisualToken(p_parser, token, p_owner, p_renderer);
			}
			else {
				::strncpy(m_imageName, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
			}

			token = p_parser->GetNextToken();
		} while (token != GolFileParser::e_rightCurly);
	}

	if (m_imageName[0] == '\0') {
		p_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
	}
}

// FUNCTION: LEGORACERS 0x004a3910
void CutsceneImageVisual::ResolveImage(GolD3DRenderDevice* p_renderer)
{
	m_image = p_renderer->FindImageByName(m_imageName);
	if (m_image == NULL) {
		LegoChar text[64];
		::strncpy(text, m_imageName, sizeof(GolName));
		text[sizeof(GolName)] = '\0';
		::strcat(text, ": Unable to find image");
		GOL_FATALERROR_MESSAGE(text);
	}
}

// FUNCTION: LEGORACERS 0x004a3990
void CutsceneImageVisual::Clear()
{
	Reset();
	CutsceneEvent::Reset();
}

// FUNCTION: LEGORACERS 0x004a39b0
void CutsceneImageVisual::VTable0x1c(LegoS32* p_width, LegoS32* p_height)
{
	*p_width = m_image->GetWidth();
	*p_height = m_image->GetHeight();
}

// FUNCTION: LEGORACERS 0x004a39d0
void CutsceneImageVisual::VTable0x20(
	GolRenderDevice* p_renderer,
	LegoS32 p_x,
	LegoS32 p_y,
	undefined4 p_width,
	undefined4 p_height,
	LegoFloat,
	LegoFloat
)
{
	Rect destRect;
	destRect.m_left = p_x;
	destRect.m_right = p_x + p_width;
	destRect.m_top = p_y;
	destRect.m_bottom = p_y + p_height;

	if (m_flags & 0x100) {
		m_image->m_unk0x4a.m_u32 = m_colorPacked;
	}

	p_renderer->VTable0x78(m_image, 0, &destRect, NULL);

	if (m_flags & 0x100) {
		union {
			ColorRGBA m_color;
			LegoU32 m_colorPacked;
		} color;

		color.m_color.m_red = 0xff;
		color.m_color.m_grn = 0xff;
		color.m_color.m_blu = 0xff;
		color.m_color.m_alp = 0xff;
		m_image->m_unk0x4a.m_u32 = color.m_colorPacked;
	}
}

// FUNCTION: LEGORACERS 0x004a3a50
CutsceneAnimationEvent::CutsceneAnimationEvent()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a3aa0
void CutsceneAnimationEvent::Reset()
{
	m_animation = NULL;
	m_particleRef = NULL;
	m_emitterName[0] = '\0';
	m_position.m_x = 0.0f;
	m_position.m_y = 0.0f;
	m_position.m_z = 0.0f;
	m_direction.m_x = 0.0f;
	m_direction.m_y = 0.0f;
	m_direction.m_z = 0.0f;
	m_up.m_x = 0.0f;
	m_up.m_y = 0.0f;
	m_up.m_z = 0.0f;
	m_flags = 0;
}

// FUNCTION: LEGORACERS 0x004a3ad0
void CutsceneAnimationEvent::Parse(GolFileParser* p_parser, CutscenePlayer* p_owner)
{
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case GolFileParser::e_unknown0x3d: {
			LegoU32 index = p_parser->ReadInteger();
			if (index >= p_owner->GetAnimationCount()) {
				p_parser->HandleUnexpectedToken(GolFileParser::e_invalidValue);
			}

			m_animation = p_owner->GetAnimationByIndex(index);
			::strncpy(m_emitterName, p_parser->ReadString(), sizeof(GolName));
			break;
		}
		case GolFileParser::e_unknown0x39:
			m_position.m_x = p_parser->ReadFloat();
			m_position.m_y = p_parser->ReadFloat();
			m_position.m_z = p_parser->ReadFloat();
			m_flags |= 1;
			break;
		case GolFileParser::e_unknown0x3e:
			m_direction.m_x = p_parser->ReadFloat();
			m_direction.m_y = p_parser->ReadFloat();
			m_direction.m_z = p_parser->ReadFloat();
			m_up.m_x = p_parser->ReadFloat();
			m_up.m_y = p_parser->ReadFloat();
			m_up.m_z = p_parser->ReadFloat();
			m_flags |= 2;
			break;
		case GolFileParser::e_unknown0x3a:
			m_flags |= 4;
			break;
		case GolFileParser::e_unknown0x3b:
			m_jointIndex = p_parser->ReadInteger();
			m_flags |= 8;
			break;
		default:
			ParseCommonToken(p_parser, p_owner, token);
			break;
		}

		token = p_parser->GetNextToken();
	}
}

// FUNCTION: LEGORACERS 0x004a3c20
void CutsceneAnimationEvent::Start()
{
	if (m_particleRef == NULL) {
		GolVec3 v1, v2, v3;
		v1.m_x = 0.0f;
		v1.m_y = 0.0f;
		v1.m_z = 0.0f;
		v2.m_x = 1.0f;
		v2.m_y = 0.0f;
		v2.m_z = 0.0f;
		v3.m_x = 0.0f;
		v3.m_y = 0.0f;
		v3.m_z = 1.0f;

		StartAt(&v1, &v2, &v3);
	}
}

// FUNCTION: LEGORACERS 0x004a3c90
void CutsceneAnimationEvent::StartAt(const GolVec3* p_a, const GolVec3* p_b, const GolVec3* p_c)
{
	if (m_particleRef == NULL) {
		if ((m_flags & 8) && m_animatedEntity) {
			GetJointPosition(m_jointIndex, &m_position);
			GetJointAxes(m_jointIndex, &m_direction, &m_up);
			Spawn();
			return;
		}

		if (!(m_flags & 1)) {
			if (m_parsedEntity != NULL) {
				m_parsedEntity->VTable0x04(&m_position);
			}
			else {
				m_position = *p_a;
			}
		}

		if (!(m_flags & 2)) {
			if (m_parsedEntity != NULL) {
				m_parsedEntity->VTable0x48(&m_direction, &m_up);
			}
			else {
				m_direction = *p_b;
				m_up = *p_c;
			}
		}

		Spawn();
	}
}

// FUNCTION: LEGORACERS 0x004a3d70
void CutsceneAnimationEvent::StartOnBsp(GolWorldEntity* p_arg)
{
	if (m_particleRef == NULL) {
		if (m_parsedEntity == NULL) {
			m_parsedEntity = p_arg;
		}

		Start();
	}
}

// FUNCTION: LEGORACERS 0x004a3d90
void CutsceneAnimationEvent::StartOnJointed(GolWorldEntity* p_arg)
{
	if (m_particleRef == NULL) {
		if (m_animatedEntity == NULL) {
			m_animatedEntity = static_cast<GolAnimatedEntity*>(p_arg);
		}

		Start();
	}
}

// FUNCTION: LEGORACERS 0x004a3db0
void CutsceneAnimationEvent::Spawn()
{
	m_particleRef = m_animation->SpawnParticle(m_emitterName, &m_position, &m_direction, &m_up);
}

// FUNCTION: LEGORACERS 0x004a3dd0
void CutsceneAnimationEvent::Stop()
{
	if (m_particleRef) {
		m_animation->ReleaseRef(m_particleRef);
		m_particleRef = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004a3df0
void CutsceneAnimationEvent::Update(LegoU32)
{
	GolVec3 v0, v1, v2;

	if (m_particleRef && (m_flags & 8) && m_animatedEntity) {
		CutsceneEvent::GetJointPosition(m_jointIndex, &v0);
		GetJointAxes(m_jointIndex, &v1, &v2);
		if (m_particleRef->m_particle) {
			m_particleRef->m_particle->FUN_00489660(&v0);
		}
		if (m_particleRef->m_particle) {
			m_particleRef->m_particle->FUN_00489540(&v1, &v2);
		}
	}
}

// FUNCTION: LEGORACERS 0x004a3e70
CutsceneSoundEvent::CutsceneSoundEvent()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a3ec0
void CutsceneSoundEvent::Reset()
{
	m_soundGroup = NULL;
	m_instance = NULL;
	m_volume = g_crimsonPebbleEvent0x30DefaultVolume;
	m_priority = 0;
	m_frequencyScale = g_crimsonPebbleEvent0x30DefaultFrequencyScale;
	m_pan = g_crimsonPebbleEvent0x30DefaultPan;
	m_looping = 0;
	m_soundIndex = 0;
}

// FUNCTION: LEGORACERS 0x004a3ef0
void CutsceneSoundEvent::Parse(GolFileParser* p_parser, CutscenePlayer* p_owner)
{
	if (m_soundGroup != NULL) {
		Clear();
	}

	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		if (!ParseToken(p_parser, p_owner, token)) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
		}

		token = p_parser->GetNextToken();
	}

	if (m_soundGroup == NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
	}
}

// FUNCTION: LEGORACERS 0x004a3f60
LegoBool32 CutsceneSoundEvent::ParseToken(
	GolFileParser* p_parser,
	CutscenePlayer* p_owner,
	GolFileParser::ParserTokenType p_token
)
{
	switch (p_token) {
	case GolFileParser::e_unknown0x30: {
		LegoU32 index = p_parser->ReadInteger();
		if (index >= p_owner->GetSoundGroupCount()) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_invalidValue);
		}

		m_soundGroup = p_owner->GetSoundGroupByIndex(index);
		m_soundIndex = static_cast<LegoU16>(p_parser->ReadInteger());
		return TRUE;
	}
	case GolFileParser::e_unknown0x31:
		m_priority = p_parser->ReadInteger();
		return TRUE;
	case GolFileParser::e_unknown0x32:
		m_volume = p_parser->ReadFloat();
		return TRUE;
	case GolFileParser::e_unknown0x33:
		m_frequencyScale = p_parser->ReadFloat();
		return TRUE;
	case GolFileParser::e_unknown0x34:
		m_pan = p_parser->ReadFloat();
		return TRUE;
	case GolFileParser::e_unknown0x35:
		m_looping = 1;
		return TRUE;
	default:
		return FALSE;
	}
}

// FUNCTION: LEGORACERS 0x004a4050
void CutsceneSoundEvent::Clear()
{
	Reset();
	CutsceneEvent::Reset();
}

// FUNCTION: LEGORACERS 0x004a4070
void CutsceneSoundEvent::Start()
{
	if (m_instance == NULL) {
		m_instance = m_soundGroup->CreateSoundInstance(m_soundIndex);
		m_instance->Play(m_looping);
		m_instance->SetVolume(m_volume);
		m_instance->SetPan(m_pan);
		m_instance->SetFrequencyScale(m_frequencyScale);
		m_instance->SetPriority(m_priority);
	}
}

// FUNCTION: LEGORACERS 0x004a40d0
void CutsceneSoundEvent::Stop()
{
	if (m_instance != NULL) {
		m_soundGroup->DestroySoundInstance(m_instance);
		m_instance = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004a40f0
void CutsceneSoundEvent::Update()
{
	if (m_instance != NULL) {
		if (!m_instance->IsPlaying()) {
			Stop();
		}
	}
}

// FUNCTION: LEGORACERS 0x004a4110
CutsceneStreamingSoundEvent::CutsceneStreamingSoundEvent()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a4160
void CutsceneStreamingSoundEvent::Reset()
{
	m_streamInstance = NULL;
	m_minDistance = 100.0f;
	m_maxDistance = 500.0f;
	m_position.m_x = 0.0f;
	m_position.m_y = 0.0f;
	m_position.m_z = 0.0f;
	m_flags = 0;
	m_jointIndex = 0;
	CutsceneSoundEvent::Reset();
	CutsceneEvent::Reset();
}

// FUNCTION: LEGORACERS 0x004a41a0
void CutsceneStreamingSoundEvent::Parse(GolFileParser* p_parser, CutscenePlayer* p_owner)
{
	if (m_soundGroup != NULL) {
		Clear();
	}

	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case GolFileParser::e_unknown0x37:
			m_minDistance = p_parser->ReadFloat();
			break;
		case GolFileParser::e_unknown0x38:
			m_maxDistance = p_parser->ReadFloat();
			break;
		case GolFileParser::e_unknown0x39:
			m_position.m_x = p_parser->ReadFloat();
			m_position.m_y = p_parser->ReadFloat();
			m_position.m_z = p_parser->ReadFloat();
			m_flags |= 1;
			break;
		case GolFileParser::e_unknown0x3a:
			m_flags = (m_flags & ~4) | 2;
			break;
		case GolFileParser::e_unknown0x3b:
			m_jointIndex = p_parser->ReadInteger();
			m_flags = (m_flags & ~2) | 4;
			break;
		default:
			if (!ParseToken(p_parser, p_owner, token)) {
				ParseCommonToken(p_parser, p_owner, token);
			}
			break;
		}

		token = p_parser->GetNextToken();
	}

	if (m_soundGroup == NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
	}
}

// FUNCTION: LEGORACERS 0x004a42a0
void CutsceneStreamingSoundEvent::Clear()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a42b0
void CutsceneStreamingSoundEvent::Start()
{
	if (m_streamInstance == NULL) {
		GolVec3 velocity;
		GolVec3 position;
		velocity.m_x = 0.0f;
		velocity.m_y = 0.0f;
		velocity.m_z = 0.0f;

		if ((m_flags & c_flagTrackJoint) && m_animatedEntity != NULL) {
			GetJointPosition(m_jointIndex, &position);
			m_animatedEntity->GetVelocity(&velocity);
		}
		else if (m_flags & c_flagHasPosition) {
			position = m_position;
		}
		else if (m_parsedEntity != NULL) {
			m_parsedEntity->VTable0x04(&position);
			m_parsedEntity->GetVelocity(&velocity);
		}
		else {
			position.m_x = 0.0f;
			position.m_y = 0.0f;
			position.m_z = 0.0f;
		}

		CreateInstance(&position);
		m_streamInstance->SetVelocity(velocity);
	}
}

// STUB: LEGORACERS 0x004a43a0
void CutsceneStreamingSoundEvent::CreateInstance(const GolVec3* p_position)
{
	if (m_streamInstance == NULL) {
		m_streamInstance = m_soundGroup->CreateStreamingSoundInstance(m_soundIndex);
		m_streamInstance->Play(m_looping);
		m_streamInstance->SetVolume(m_volume);
		m_streamInstance->SetFrequencyScale(m_frequencyScale);
		LegoFloat maxDistance = m_maxDistance;
		LegoFloat minDistance = m_minDistance;
		m_streamInstance->SetDistanceRange(minDistance, maxDistance);

		m_flags &= ~c_flagWasPlaying;
		if (m_flags & c_flagHasPosition) {
			m_streamInstance->SetPosition(&m_position);
			return;
		}

		m_streamInstance->SetPosition(p_position);
	}
}

// FUNCTION: LEGORACERS 0x004a4450
void CutsceneStreamingSoundEvent::StartAt(const GolVec3* p_a, const GolVec3*, const GolVec3*)
{
	if (m_streamInstance == NULL) {
		if (m_parsedEntity == NULL && !(m_flags & 1)) {
			CreateInstance(p_a);
		}
		else {
			Start();
		}
	}
}

// FUNCTION: LEGORACERS 0x004a4480
void CutsceneStreamingSoundEvent::StartOnBsp(GolWorldEntity* p_arg)
{
	if (m_streamInstance == NULL) {
		if (m_parsedEntity == NULL) {
			m_parsedEntity = p_arg;
		}

		Start();
	}
}

// FUNCTION: LEGORACERS 0x004a44a0
void CutsceneStreamingSoundEvent::StartOnJointed(GolWorldEntity* p_arg)
{
	if (m_streamInstance == NULL) {
		if (m_animatedEntity == NULL) {
			m_animatedEntity = static_cast<GolAnimatedEntity*>(p_arg);
			m_parsedEntity = p_arg;
		}

		Start();
	}
}

// FUNCTION: LEGORACERS 0x004a44c0
void CutsceneStreamingSoundEvent::Stop()
{
	if (m_streamInstance) {
		m_flags &= ~c_flagWasPlaying;
		m_soundGroup->DestroyStreamingSoundInstance(m_streamInstance);
		m_streamInstance = NULL;
	}
}

// STUB: LEGORACERS 0x004a44f0
void CutsceneStreamingSoundEvent::Update()
{
	if (m_streamInstance) {
		if (!m_streamInstance->IsPlaying()) {
			if (m_flags & c_flagWasPlaying) {
				Stop();
				return;
			}
		}
		else {
			m_flags |= c_flagWasPlaying;
		}

		GolVec3 position;
		GolVec3 velocity;
		GolWorldEntity* entity;

		if (m_flags & c_flagTrackJoint) {
			GetJointPosition(m_jointIndex, &position);
			m_streamInstance->SetPosition(&position);
			entity = m_animatedEntity;
		}
		else if (m_flags & c_flagTrackEntity) {
			m_parsedEntity->VTable0x04(&position);
			m_streamInstance->SetPosition(&position);
			entity = m_parsedEntity;
		}
		else {
			return;
		}

		entity->GetVelocity(&velocity);
		m_streamInstance->SetVelocity(velocity);
	}
}

// FUNCTION: LEGORACERS 0x004a4970
CutsceneMenuAnimationEvent::CutsceneMenuAnimationEvent()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a49c0
void CutsceneMenuAnimationEvent::Reset()
{
	m_animationList = NULL;
	m_material = NULL;
	m_activeEntry = NULL;
	m_durationMs = 0;
	m_mode = 0;
	m_red = 0;
	m_grn = 0;
	m_blu = 0;
	m_alpha = 0;
}

// FUNCTION: LEGORACERS 0x004a49e0
void CutsceneMenuAnimationEvent::Parse(
	GolFileParser* p_parser,
	CutscenePlayer* p_owner,
	MenuAnimationList* p_animationList,
	GolD3DRenderDevice* p_renderer
)
{
	GolName materialName;

	materialName[0] = '\0';
	m_animationList = p_animationList;
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case GolFileParser::e_unknown0x61:
			m_durationMs = p_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x62: {
			GolFileParser::ParserTokenType mode = p_parser->GetNextToken();
			switch (mode) {
			case GolFileParser::e_unknown0x63:
				m_mode |= 1;
				break;
			case GolFileParser::e_unknown0x64:
				m_mode |= 2;
				break;
			default:
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
			break;
		}
		case GolFileParser::e_unknown0x65:
			::strncpy(materialName, p_parser->ReadString(), sizeof(GolName));
			break;
		case GolFileParser::e_unknown0x66:
			m_red = static_cast<LegoU8>(p_parser->ReadInteger());
			m_grn = static_cast<LegoU8>(p_parser->ReadInteger());
			m_blu = static_cast<LegoU8>(p_parser->ReadInteger());
			break;
		default:
			ParseCommonToken(p_parser, p_owner, token);
			break;
		}

		token = p_parser->GetNextToken();
	}

	if (materialName[0] != '\0') {
		m_material = p_renderer->FindMaterialByName(materialName);
	}
}

// FUNCTION: LEGORACERS 0x004a4af0
void CutsceneMenuAnimationEvent::Start()
{
	if (m_mode & 1) {
		m_activeEntry = m_animationList->Activate(m_durationMs, TRUE, m_material, NULL);
	}
	else if (m_mode & 2) {
		m_activeEntry = m_animationList->Activate(m_durationMs, FALSE, m_material, NULL);
	}

	if (m_activeEntry != NULL) {
		m_activeEntry->SetColor(m_colorPacked);
	}
}

// FUNCTION: LEGORACERS 0x004a4b40
void CutsceneMenuAnimationEvent::Stop()
{
	if (m_activeEntry != NULL) {
		m_animationList->Deactivate(m_activeEntry);
		m_activeEntry = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004a4b60
CutsceneColorEvent::CutsceneColorEvent()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a4bb0
void CutsceneColorEvent::Reset()
{
	m_entity = NULL;
	m_active = FALSE;
	m_shiftRed = 0;
	m_shiftGrn = 0;
	m_shiftBlu = 0;
	m_offsetStartRed = 0;
	m_offsetStartGrn = 0;
	m_offsetStartBlu = 0;
	m_offsetRed = 0.0f;
	m_offsetGrn = 0.0f;
	m_offsetBlu = 0.0f;
	m_offsetRateRed = 0.0f;
	m_offsetRateGrn = 0.0f;
	m_offsetRateBlu = 0.0f;
}

// FUNCTION: LEGORACERS 0x004a4be0
void CutsceneColorEvent::Parse(GolFileParser* p_parser, CutscenePlayer* p_owner)
{
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case GolFileParser::e_unknown0x2c:
			m_shiftRed = p_parser->ReadInteger();
			m_shiftGrn = p_parser->ReadInteger();
			m_shiftBlu = p_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x2d:
			m_offsetStartRed = p_parser->ReadInteger();
			m_offsetStartGrn = p_parser->ReadInteger();
			m_offsetStartBlu = p_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x2e:
			m_offsetRateRed = p_parser->ReadFloat();
			m_offsetRateGrn = p_parser->ReadFloat();
			m_offsetRateBlu = p_parser->ReadFloat();
			break;
		default:
			ParseCommonToken(p_parser, p_owner, token);
			break;
		}

		token = p_parser->GetNextToken();
	}
}

// FUNCTION: LEGORACERS 0x004a4ca0
void CutsceneColorEvent::Start()
{
	if (!m_active && m_entity != NULL) {
		m_active = TRUE;
		m_offsetRed = static_cast<LegoFloat>(m_offsetStartRed);
		m_offsetGrn = static_cast<LegoFloat>(m_offsetStartGrn);
		m_offsetBlu = static_cast<LegoFloat>(m_offsetStartBlu);
		ApplyColorTransform();
	}
}

// FUNCTION: LEGORACERS 0x004a4cd0
void CutsceneColorEvent::StartOnModel(GolWorldEntity* p_arg)
{
	if (!m_active) {
		if (m_entity == NULL) {
			m_entity = p_arg;
		}

		Start();
	}
}

// FUNCTION: LEGORACERS 0x004a4cf0
void CutsceneColorEvent::Stop()
{
	if (m_active) {
		m_active = FALSE;
		if (m_entity != NULL) {
			m_entity->VTable0x28();
		}
	}
}

// FUNCTION: LEGORACERS 0x004a4d10
void CutsceneColorEvent::Update(LegoFloat p_elapsedSeconds)
{
	if (m_active) {
		if (m_entity != 0) {
			LegoFloat deltaX = m_offsetRateRed * p_elapsedSeconds;
			LegoFloat deltaY = m_offsetRateGrn * p_elapsedSeconds;
			LegoFloat deltaZ = m_offsetRateBlu * p_elapsedSeconds;

			if (static_cast<LegoS32>(deltaX) || static_cast<LegoS32>(deltaY) || static_cast<LegoS32>(deltaZ)) {
				m_offsetRed += deltaX;
				m_offsetGrn += deltaY;
				m_offsetBlu += deltaZ;
				ApplyColorTransform();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a4da0
void CutsceneColorEvent::ApplyColorTransform()
{
	ColorTransform0x20 transform;
	transform.m_redShift = m_shiftRed;
	transform.m_grnShift = m_shiftGrn;
	transform.m_bluShift = m_shiftBlu;
	transform.m_alpShift = 0;
	transform.m_redOffset = static_cast<LegoS32>(m_offsetRed);
	transform.m_grnOffset = static_cast<LegoS32>(m_offsetGrn);
	transform.m_bluOffset = static_cast<LegoS32>(m_offsetBlu);
	transform.m_alpOffset = 0;

	m_entity->VTable0x24(&transform);
}
