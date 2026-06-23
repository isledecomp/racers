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
DECOMP_SIZE_ASSERT(BluebellFog0x4, 0x04)
DECOMP_SIZE_ASSERT(CutsceneEvent, 0x14)
DECOMP_SIZE_ASSERT(CutsceneEventValueSource, 0x2c)
DECOMP_SIZE_ASSERT(CutsceneEventValuePayload, 0x24)
DECOMP_SIZE_ASSERT(CutsceneEventSelectorPayload, 0x28)
DECOMP_SIZE_ASSERT(CutsceneEventVectorPayload, 0x44)
DECOMP_SIZE_ASSERT(CutsceneEventLink, 0x0c)
DECOMP_SIZE_ASSERT(CutsceneSoundEvent, 0x30)
DECOMP_SIZE_ASSERT(CutsceneMoveEvent, 0x48)
DECOMP_SIZE_ASSERT(CutsceneAnimationEvent, 0x50)
DECOMP_SIZE_ASSERT(CutsceneStreamingSoundEvent, 0x50)
DECOMP_SIZE_ASSERT(CutsceneMenuAnimationEvent, 0x2c)
DECOMP_SIZE_ASSERT(CutsceneVisual, 0x58)
DECOMP_SIZE_ASSERT(CutsceneImageVisual, 0x64)
DECOMP_SIZE_ASSERT(CutsceneTextVisual, 0x70)
DECOMP_SIZE_ASSERT(CutsceneAnimation::Entry, 0x08)
DECOMP_SIZE_ASSERT(CutsceneAnimation::Runtime, 0x44)
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
	m_unk0x00 = 0;
	m_unk0x04 = 0;
}

// FUNCTION: LEGORACERS 0x00489980
CutsceneAnimation::Entry::~Entry()
{
	m_unk0x00 = 0;
	m_unk0x04 = 0;
}

// FUNCTION: LEGORACERS 0x00489990
CutsceneAnimation::CutsceneAnimation()
{
	m_particles = NULL;
	m_unk0x010 = NULL;
	m_unk0x334 = 0;
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

	if (m_unk0x010 != NULL) {
		delete[] m_unk0x010;
		m_unk0x010 = NULL;
	}

	if (m_particles != NULL) {
		delete[] m_particles;
		m_particles = NULL;
	}

	m_unk0x334 = 0;
	m_numParticles = 0;
}

// FUNCTION: LEGORACERS 0x00489af0
void CutsceneAnimation::FUN_00489af0(
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

	if (m_unk0x010) {
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

	m_unk0x334 = parser->ReadBracketedCountAndLeftCurly();

	if (m_unk0x334) {
		m_unk0x010 = new Runtime[m_unk0x334];

		if (!m_unk0x010) {
			GolFatalError(c_golErrorOutOfMemory, NULL, 0);
		}

		GolNameTable::Allocate(m_unk0x334);

		for (i = 0; i < m_unk0x334; i++) {
			m_unk0x010[i].Parse(p_materialAnimation, p_renderer, parser, this);
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
LegoBool32 CutsceneAnimation::FUN_00489d50(const LegoChar* p_param)
{
	return GetName(p_param) != NULL;
}

// STUB: LEGORACERS 0x00489d70
CutsceneParticleRef* CutsceneAnimation::FUN_00489d70(
	const LegoChar* p_param1,
	GolVec3* p_param2,
	GolVec3* p_param3,
	GolVec3* p_param4
)
{
	Runtime* runtime = static_cast<Runtime*>(GetName(p_param1));

	LegoU32 refIndex = 0;
	while (refIndex < sizeOfArray(m_unk0x014) && (m_unk0x014[refIndex].m_unk0x04 & CutsceneParticleRef::c_flagBit0)) {
		refIndex++;
	}

	if (refIndex == sizeOfArray(m_unk0x014)) {
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
				CutsceneParticleRef* ref = &m_unk0x014[refIndex];
				ref->m_unk0x04 |= CutsceneParticleRef::c_flagBit0;
				ref->m_unk0x00 = currentParticle;
				currentParticle->SetRef(ref);
				return ref;
			}

			return NULL;
		}

		Runtime* activeRuntime = currentParticle->GetRuntime();
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
		oldRef->m_unk0x00 = NULL;
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
		CutsceneParticleRef* ref = &m_unk0x014[refIndex];
		ref->m_unk0x04 |= CutsceneParticleRef::c_flagBit0;
		ref->m_unk0x00 = particle;
		particle->SetRef(ref);
		return ref;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00489f00
void CutsceneAnimation::FUN_00489f00(CutsceneParticleRef* p_param)
{
	if (p_param->m_unk0x00) {
		p_param->m_unk0x00->FUN_004897a0();
	}

	p_param->m_unk0x00 = NULL;
	p_param->m_unk0x04 &= ~CutsceneParticleRef::c_flagBit0;
}

// FUNCTION: LEGORACERS 0x00489f30
void CutsceneAnimation::FUN_00489f30(CutsceneParticleRef* p_param)
{
	if (p_param->m_unk0x00) {
		p_param->m_unk0x00->FUN_004897c0();
	}

	p_param->m_unk0x00 = NULL;
	p_param->m_unk0x04 &= ~CutsceneParticleRef::c_flagBit0;
}

// FUNCTION: LEGORACERS 0x00489f60
LegoU32 CutsceneAnimation::FUN_00489f60()
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
void CutsceneAnimation::FUN_00489fa0(LegoU32 p_elapsedMs)
{
	for (LegoU32 i = 0; i < m_numParticles; i++) {
		if (m_particles[i].IsActive()) {
			m_particles[i].FUN_004897e0(p_elapsedMs);
		}
	}
}

// FUNCTION: LEGORACERS 0x00489ff0
void CutsceneAnimation::FUN_00489ff0(GolD3DRenderDevice* p_renderer)
{
	for (LegoU32 i = 0; i < m_numParticles; i++) {
		if (m_particles[i].IsActive()) {
			m_particles[i].FUN_004513d0(p_renderer);
		}
	}
}

// FUNCTION: LEGORACERS 0x0048a040
void CutsceneAnimation::FUN_0048a040(GolD3DRenderDevice* p_renderer)
{
	for (LegoU32 i = 0; i < m_numParticles; i++) {
		if (m_particles[i].IsActive()) {
			m_particles[i].FUN_00489960(p_renderer);
		}
	}
}

// FUNCTION: LEGORACERS 0x0048a090
CutsceneAnimation::Runtime::Runtime()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048a0a0
CutsceneAnimation::Runtime::~Runtime()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x0048a0b0
void CutsceneAnimation::Runtime::Clear()
{
	if (m_unk0x00) {
		delete[] m_unk0x00;
		m_unk0x00 = NULL;
	}

	Reset();
}

// FUNCTION: LEGORACERS 0x0048a0e0
void CutsceneAnimation::Runtime::Reset()
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
void CutsceneAnimation::Runtime::Parse(
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
void CutsceneAnimation::Runtime::GetVectorAt(GolVec3* p_vec, int p_index)
{
	p_vec->m_x = m_unk0x00[p_index].m_x;
	p_vec->m_y = m_unk0x00[p_index].m_y;
	p_vec->m_z = m_unk0x00[p_index].m_z;
}

// FUNCTION: LEGORACERS 0x0048a3e0
void CutsceneAnimation::Runtime::GetOrigin(GolVec3* p_vec) const
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
	m_unk0x04 = 0;
	m_unk0x08 = 0;
	m_unk0x0c = 0;
	m_unk0x10 = 0;
}

// FUNCTION: LEGORACERS 0x0049fdd0
void CutsceneEvent::VTable0x10(const GolVec3*, const GolVec3*, const GolVec3*)
{
	if (m_unk0x10 == 0) {
		VTable0x14();
	}
}

// FUNCTION: LEGORACERS 0x0049fde0
void CutsceneEvent::VTable0x0c(GolWorldEntity*)
{
	if (m_unk0x10 == 0) {
		VTable0x14();
	}
}

// FUNCTION: LEGORACERS 0x0049fdf0
void CutsceneEvent::VTable0x08(GolWorldEntity* p_arg)
{
	if (m_unk0x10 == 0) {
		VTable0x0c(p_arg);
	}
}

// FUNCTION: LEGORACERS 0x0049fe10
void CutsceneEvent::VTable0x04(GolWorldEntity* p_arg)
{
	if (m_unk0x10 == 0) {
		VTable0x08(p_arg);
	}
}

// FUNCTION: LEGORACERS 0x0049fe30
void CutsceneEvent::FUN_0049fe30(undefined4 p_param1, GolVec3* p_param2)
{
	m_unk0x0c->VTable0x5c(0);
	GolSceneNode* falconNode = m_unk0x0c->VTable0x58(0);

	GolVec3 vec1;
	GolVec3 vec2;
	vec1.m_x = 0.0f;
	vec1.m_y = 0.0f;
	vec1.m_z = 0.0f;

	falconNode->FUN_00413230(p_param1, &vec1, &vec2);

	LegoFloat scale = m_unk0x0c->GetModel(0)->GetScale() * m_unk0x0c->GetUnk0x58();
	vec2.m_x *= scale;
	vec2.m_y *= scale;
	vec2.m_z *= scale;
	m_unk0x0c->VTable0x2c(vec2, p_param2);
}

// FUNCTION: LEGORACERS 0x0049fec0
void CutsceneEvent::FUN_0049fec0(undefined4 p_param1, GolVec3* p_param2, GolVec3* p_param3)
{
	m_unk0x0c->VTable0x5c(0);
	GolSceneNode* falconNode = m_unk0x0c->VTable0x58(0);

	GolVec3 vec1;
	GolVec3 vec2;
	vec1.m_x = 1.0f;
	vec1.m_y = 0.0f;
	vec1.m_z = 0.0f;

	falconNode->FUN_004132a0(p_param1, &vec1, &vec2);
	m_unk0x0c->VTable0x34(vec2, p_param2);

	vec1.m_x = 0.0f;
	vec1.m_y = 0.0f;
	vec1.m_z = 1.0f;
	falconNode->FUN_004132a0(p_param1, &vec1, &vec2);
	m_unk0x0c->VTable0x34(vec2, p_param3);
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
		m_unk0x04 = p_owner->FUN_004a3240(name);
		m_unk0x08 = m_unk0x04;
		m_unk0x0c = static_cast<GolAnimatedEntity*>(m_unk0x04);
		if (m_unk0x04) {
			return;
		}
		::strncpy(text, name, sizeof(GolName));
		text[sizeof(GolName)] = '\0';
		::strcat(text, ": unable to find jointed model");
		GOL_FATALERROR_MESSAGE(text);
		break;
	case GolFileParser::e_unknown0x5e:
		m_unk0x04 = p_owner->FUN_004a3230(name);
		m_unk0x08 = m_unk0x04;
		if (m_unk0x04) {
			return;
		}
		::strncpy(text, name, sizeof(GolName));
		text[sizeof(GolName)] = '\0';
		::strcat(text, ": unable to find model");
		GOL_FATALERROR_MESSAGE(text);
		break;
	case GolFileParser::e_unknown0x5f:
		m_unk0x04 = p_owner->FUN_004a3250(name);
		m_unk0x08 = m_unk0x04;
		if (m_unk0x04) {
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
void CutsceneEvent::VTable0x14()
{
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void CutsceneEvent::VTable0x18()
{
}

// FUNCTION: LEGORACERS 0x004a00b0 FOLDED
CutsceneEventLink::CutsceneEventLink()
{
	m_unk0x00 = 0;
	m_event = NULL;
	m_next = NULL;
}

// FUNCTION: LEGORACERS 0x004a00c0
void CutsceneEventLink::FUN_004a00c0(undefined4 p_unk0x04, CutsceneEvent* p_event)
{
	m_unk0x00 = p_unk0x04;
	m_event = p_event;
}

// FUNCTION: LEGORACERS 0x004a00d0
void CutsceneEventLink::FUN_004a00d0()
{
	if (m_unk0x00) {
		m_event->VTable0x14();
	}
	else {
		m_event->VTable0x18();
	}
}

// FUNCTION: LEGORACERS 0x004a00f0
void CutsceneEventLink::FUN_004a00f0(CutsceneEventValuePayload* p_payload)
{
	GolWorldEntity* value = p_payload->m_unk0x20->m_unk0x28;
	if (value) {
		if (m_unk0x00) {
			m_event->VTable0x04(value);
		}
		else {
			m_event->VTable0x18();
		}
	}
	else {
		FUN_004a00d0();
	}
}

// FUNCTION: LEGORACERS 0x004a0120
void CutsceneEventLink::FUN_004a0120(CutsceneEventSelectorPayload* p_payload)
{
	if (p_payload->m_unk0x20 == 2) {
		if (m_unk0x00) {
			m_event->VTable0x04(p_payload->m_unk0x24);
		}
		else {
			m_event->VTable0x18();
		}
	}
	else if (p_payload->m_unk0x20 == 3 || p_payload->m_unk0x20 == 1) {
		if (m_unk0x00) {
			m_event->VTable0x08(p_payload->m_unk0x24);
		}
		else {
			m_event->VTable0x18();
		}
	}
	else {
		if (m_unk0x00) {
			m_event->VTable0x0c(p_payload->m_unk0x24);
		}
		else {
			m_event->VTable0x18();
		}
	}
}

// FUNCTION: LEGORACERS 0x004a0180
void CutsceneEventLink::FUN_004a0180(CutsceneEventVectorPayload* p_payload)
{
	GolVec3 vector0 = p_payload->m_unk0x20;
	GolVec3 vector1 = p_payload->m_unk0x2c;
	GolVec3 vector2 = p_payload->m_unk0x38;

	if (m_unk0x00) {
		m_event->VTable0x10(&vector0, &vector1, &vector2);
	}
	else {
		m_event->VTable0x18();
	}
}

// FUNCTION: LEGORACERS 0x004a0200
void CutsceneEventLink::FUN_004a0200(void*)
{
	FUN_004a00d0();
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
	m_unk0x04 = NULL;
	m_unk0x08 = 0;
	m_soundManager = NULL;
	m_unk0x10 = 0;
	m_unk0x64 = NULL;
	m_unk0x68 = 0;
	m_unk0x6c = NULL;
	m_unk0x70 = NULL;
	m_unk0x74 = NULL;
	m_unk0x78 = 0;
	m_unk0x7c = NULL;
	m_unk0x80 = NULL;
	m_unk0x84 = 0;
	m_unk0x88 = NULL;
	m_unk0x8c = NULL;
	m_unk0x90 = 0;
	m_unk0x94 = NULL;
	m_unk0x98 = NULL;
	m_unk0x9c = 0;
	m_unk0xa0 = NULL;
	m_unk0xa4 = NULL;
	m_unk0xb4 = 0;
	m_unk0xb8 = NULL;
	m_unk0xc8 = 0;
	m_unk0xcc = NULL;
	m_unk0xdc = 0;
	m_unk0xe0 = NULL;
	m_unk0xf0 = 0;
	m_unk0xf4 = NULL;
	m_unk0x104 = 0;
	m_unk0x108 = NULL;
	m_unk0x118 = 0;
	m_unk0x11c = NULL;
	m_unk0x12c = 0;
	m_unk0x130 = NULL;
	m_unk0x134 = 0;
	m_unk0x138 = NULL;
	m_unk0x148 = 0;
	m_unk0x14c = NULL;
	m_unk0x15c = 0;
	m_unk0x160 = NULL;
	m_unk0x170 = 0;
	m_unk0x174 = NULL;
	m_unk0x184 = 0;
	m_unk0x188 = NULL;
	m_unk0x198 = 0;
	m_unk0x19c = NULL;
	m_unk0x1ac = 0;
	m_unk0x1b0 = NULL;
	m_unk0x1c0 = 0;
	m_unk0x1c4 = NULL;
	m_unk0x1d4 = 0;
	m_unk0x1d8 = NULL;
	m_unk0x1e8 = 0;
	m_unk0x1ec = NULL;
	m_unk0x1fc = 0;
	m_unk0x200 = NULL;
	m_unk0x210 = 0;
	m_unk0x214 = NULL;
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
void CutscenePlayer::FUN_004a0730(
	GolExport* p_golExport,
	GolD3DRenderDevice* p_renderer,
	SoundManager* p_soundManager,
	CutsceneDefinition* p_unk0x10,
	const LegoChar* p_fileName,
	undefined4 p_binary
)
{
	GolFileParser* parser;

	if (m_unk0x04) {
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

	m_unk0x04 = p_golExport;
	m_unk0x08 = p_renderer;
	m_unk0x10 = p_unk0x10;
	m_soundManager = p_soundManager;

	p_soundManager->AddActiveSoundNode(&m_unk0x14);
	parser->OpenFileForRead(p_fileName);
	GolFileParser::ParserTokenType token = parser->GetNextToken();
	while (token != GolFileParser::e_syntaxerror) {
		switch (token) {
		case GolFileParser::e_unknown0x27:
			FUN_004a0ff0(parser);
			break;
		case GolFileParser::e_unknown0x28:
			FUN_004a12e0(parser);
			break;
		case GolFileParser::e_unknown0x5c:
			FUN_004a15e0(parser);
			break;
		case GolFileParser::e_unknown0x29:
			FUN_004a1760(parser);
			break;
		case GolFileParser::e_unknown0x2a:
			FUN_004a18d0(parser);
			break;
		case GolFileParser::e_unknown0x2b:
			FUN_004a1a40(parser);
			break;
		case GolFileParser::e_unknown0x2f:
			FUN_004a1c00(parser);
			break;
		case GolFileParser::e_unknown0x36:
			FUN_004a1dc0(parser);
			break;
		case GolFileParser::e_unknown0x3c:
			FUN_004a1f80(parser);
			break;
		case GolFileParser::e_unknown0x60:
			FUN_004a20f0(parser);
			break;
		case GolFileParser::e_unknown0x3f:
			LoadTextEntries(parser);
			break;
		case GolFileParser::e_unknown0x4d:
			FUN_004a2520(parser);
			break;
		case GolFileParser::e_unknown0x50:
			FUN_004a2730(parser, 0x50, m_unk0x134, m_unk0x138, m_unk0x13c);
			break;
		case GolFileParser::e_unknown0x51:
			FUN_004a2730(parser, 0x51, m_unk0x148, m_unk0x14c, m_unk0x150);
			break;
		case GolFileParser::e_unknown0x52:
			FUN_004a2730(parser, 0x52, m_unk0x15c, m_unk0x160, m_unk0x164);
			break;
		case GolFileParser::e_unknown0x53:
			FUN_004a2730(parser, 0x53, m_unk0x170, m_unk0x174, m_unk0x178);
			break;
		case GolFileParser::e_unknown0x54:
			FUN_004a2730(parser, 0x54, m_unk0x184, m_unk0x188, m_unk0x18c);
			break;
		case GolFileParser::e_unknown0x55:
			FUN_004a2730(parser, 0x55, m_unk0x198, m_unk0x19c, m_unk0x1a0);
			break;
		case GolFileParser::e_unknown0x56:
			FUN_004a2730(parser, 0x56, m_unk0x1ac, m_unk0x1b0, m_unk0x1b4);
			break;
		case GolFileParser::e_unknown0x57:
			FUN_004a2730(parser, 0x57, m_unk0x1c0, m_unk0x1c4, m_unk0x1c8);
			break;
		case GolFileParser::e_unknown0x58:
			FUN_004a2730(parser, 0x58, m_unk0x1d4, m_unk0x1d8, m_unk0x1dc);
			break;
		case GolFileParser::e_unknown0x59:
			FUN_004a2730(parser, 0x59, m_unk0x1e8, m_unk0x1ec, m_unk0x1f0);
			break;
		case GolFileParser::e_unknown0x5a:
			FUN_004a2730(parser, 0x5a, m_unk0x1fc, m_unk0x200, m_unk0x204);
			break;
		case GolFileParser::e_unknown0x5b:
			FUN_004a2730(parser, 0x5b, m_unk0x210, m_unk0x214, m_unk0x218);
			break;
		default:
			parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}
		token = parser->GetNextToken();
	}

	parser->Dispose();
	delete parser;

	FUN_004a1240(p_binary);
	FUN_004a14e0();
	FUN_004a16f0();
	FUN_004a1850(p_binary);
	FUN_004a19c0(p_binary);
	FUN_004a24e0();
	FUN_004a26f0();
}

// FUNCTION: LEGORACERS 0x004a0bf0
void CutscenePlayer::Clear()
{
	LegoU32 i;

	if (m_soundManager) {
		m_soundManager->RemoveActiveSoundNode(&m_unk0x14);
	}

	if (m_unk0x88) {
		for (i = 0; i < m_unk0x84; i++) {
			if (m_unk0x88[i]) {
				m_soundManager->DestroySoundGroup(m_unk0x88[i]);
			}
		}
		delete[] m_unk0x88;
	}

	if (m_unk0x8c) {
		delete m_unk0x8c;
	}

	if (m_unk0x94) {
		for (i = 0; i < m_unk0x90; i++) {
			if (m_unk0x94[i]) {
				m_unk0x04->DestroyFontTable(m_unk0x94[i]);
			}
		}
		delete[] m_unk0x94;
	}

	if (m_unk0x98) {
		delete m_unk0x98;
	}

	if (m_unk0xa0) {
		for (i = 0; i < m_unk0x9c; i++) {
			if (m_unk0xa0[i]) {
				m_unk0x04->VTable0x68(m_unk0xa0[i]);
			}
		}
		delete m_unk0xa0;
	}
	if (m_unk0xa4) {
		delete m_unk0xa4;
	}
	if (m_unk0x6c) {
		delete[] m_unk0x6c;
	}
	if (m_unk0x74) {
		delete m_unk0x74;
	}
	if (m_unk0x70) {
		delete[] m_unk0x70;
	}
	if (m_unk0x7c) {
		delete[] m_unk0x7c;
	}
	if (m_unk0x80) {
		delete m_unk0x80;
	}
	if (m_unk0xb8) {
		delete[] m_unk0xb8;
	}
	if (m_unk0xcc) {
		delete[] m_unk0xcc;
	}
	if (m_unk0xe0) {
		delete[] m_unk0xe0;
	}
	if (m_unk0xf4) {
		delete[] m_unk0xf4;
	}
	if (m_unk0x64) {
		delete m_unk0x64;
	}
	if (m_unk0x108) {
		delete[] m_unk0x108;
	}
	if (m_unk0x11c) {
		delete[] m_unk0x11c;
	}
	if (m_unk0x130) {
		delete[] m_unk0x130;
	}
	if (m_unk0x138) {
		delete m_unk0x138;
	}
	if (m_unk0x14c) {
		delete m_unk0x14c;
	}
	if (m_unk0x160) {
		delete m_unk0x160;
	}
	if (m_unk0x174) {
		delete m_unk0x174;
	}
	if (m_unk0x188) {
		delete m_unk0x188;
	}
	if (m_unk0x19c) {
		delete m_unk0x19c;
	}
	if (m_unk0x1b0) {
		delete m_unk0x1b0;
	}
	if (m_unk0x1c4) {
		delete m_unk0x1c4;
	}
	if (m_unk0x1d8) {
		delete m_unk0x1d8;
	}
	if (m_unk0x1ec) {
		delete m_unk0x1ec;
	}
	if (m_unk0x200) {
		delete m_unk0x200;
	}
	if (m_unk0x214) {
		delete m_unk0x214;
	}
	m_unk0xa8.Clear();
	m_unk0xbc.Clear();
	m_unk0xd0.Clear();
	m_unk0xe4.Clear();
	m_unk0xf8.Clear();
	m_unk0x10c.Clear();
	m_unk0x120.Clear();
	m_unk0x13c.Clear();
	m_unk0x150.Clear();
	m_unk0x164.Clear();
	m_unk0x178.Clear();
	m_unk0x18c.Clear();
	m_unk0x1a0.Clear();
	m_unk0x1b4.Clear();
	m_unk0x1c8.Clear();
	m_unk0x1dc.Clear();
	m_unk0x1f0.Clear();
	m_unk0x204.Clear();
	m_unk0x218.Clear();

	Reset();
}

// FUNCTION: LEGORACERS 0x004a0ff0
void CutscenePlayer::FUN_004a0ff0(GolFileParser* p_parser)
{
	if (m_unk0x6c != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_unk0x68 = p_parser->ReadInteger();
	if (m_unk0x68 == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_unk0x6c = new CutsceneAnimation[m_unk0x68];
	m_unk0x70 = new MabMaterialAnimation0x14[m_unk0x68];
	m_unk0x74 = new LegoChar[m_unk0x68 * 9];
	if (m_unk0x6c == NULL || m_unk0x70 == NULL || m_unk0x74 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoU32 i = 0;

	if (i < m_unk0x68) {
		LegoU32 offset = 0;

		do {
			::strncpy(&m_unk0x74[offset], p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
			i++;
			m_unk0x74[offset + sizeof(GolName)] = '\0';
			offset += 9;
		} while (i < m_unk0x68);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a1240
void CutscenePlayer::FUN_004a1240(undefined4 p_binary)
{
	if (m_unk0x74 != NULL) {
		for (LegoU32 i = 0; i < m_unk0x68; i++) {
			m_unk0x70[i].VTable0x04(m_unk0x08, &m_unk0x74[i * 9], p_binary);
			m_unk0x6c[i].FUN_00489af0(3, m_unk0x04, m_unk0x08, &m_unk0x70[i], &m_unk0x74[i * 9], p_binary);
		}

		delete[] m_unk0x74;
		m_unk0x74 = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004a12e0
void CutscenePlayer::FUN_004a12e0(GolFileParser* p_parser)
{
	if (m_unk0x7c != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_unk0x78 = p_parser->ReadInteger();
	if (m_unk0x78 == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_unk0x7c = new GolStringTable[m_unk0x78];
	m_unk0x80 = new LegoChar[m_unk0x78 * 13];
	if (m_unk0x7c == NULL || m_unk0x80 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_unk0x78; i++) {
		::strncpy(&m_unk0x80[i * 13], p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		m_unk0x80[i * 13 + sizeof(GolName)] = '\0';
		::strcat(&m_unk0x80[i * 13], ".srf");

		m_unk0x7c[i].UseOwnedBuffers();
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a14e0
void CutscenePlayer::FUN_004a14e0()
{
	if (m_unk0x80 != NULL) {
		LegoU32 i = 0;

		if (i < m_unk0x78) {
			LegoU32 fileNameOffset = 0;

			do {
				m_unk0x7c[i].UseOwnedBuffers();

				if (!m_unk0x7c[i].Load(&m_unk0x80[fileNameOffset])) {
					LegoChar text[48];
					::strcpy(text, "Unable to open: ");
					::strcat(text, &m_unk0x80[fileNameOffset]);
					GOL_FATALERROR_MESSAGE(text);
				}

				i++;
				fileNameOffset += 13;
			} while (i < m_unk0x78);
		}

		delete[] m_unk0x80;
		m_unk0x80 = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004a15e0
void CutscenePlayer::FUN_004a15e0(GolFileParser* p_parser)
{
	if (m_unk0x88 != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_unk0x84 = p_parser->ReadInteger();
	if (m_unk0x84 == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_unk0x88 = new SoundGroup*[m_unk0x84];
	if (m_unk0x88 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x8c = new LegoChar[m_unk0x84 * 9];
	if (m_unk0x8c == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoU32 i = 0;

	if (i < m_unk0x84) {
		LegoU32 offset = 0;

		do {
			::strncpy(&m_unk0x8c[offset], p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
			m_unk0x8c[offset + sizeof(GolName)] = '\0';

			SoundGroup* soundGroup = m_soundManager->CreateSoundGroup();
			i++;
			offset += 9;
			m_unk0x88[i - 1] = soundGroup;
		} while (i < m_unk0x84);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a16f0
void CutscenePlayer::FUN_004a16f0()
{
	if (m_unk0x8c != NULL) {
		for (LegoU32 i = 0; i < m_unk0x84; i++) {
			m_unk0x88[i]->Load(&m_unk0x8c[i * 9]);
		}

		delete[] m_unk0x8c;
		m_unk0x8c = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004a1760
void CutscenePlayer::FUN_004a1760(GolFileParser* p_parser)
{
	if (m_unk0x94 != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_unk0x90 = p_parser->ReadInteger();
	if (m_unk0x90 == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_unk0x94 = new GolFontTable*[m_unk0x90];
	m_unk0x98 = new LegoChar[m_unk0x90 * 9];
	if (m_unk0x94 == NULL || m_unk0x98 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoU32 i = 0;

	if (i < m_unk0x90) {
		LegoU32 offset = 0;

		do {
			::strncpy(&m_unk0x98[offset], p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
			i++;
			m_unk0x98[offset + sizeof(GolName)] = '\0';
			offset += 9;
		} while (i < m_unk0x90);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a1850
void CutscenePlayer::FUN_004a1850(undefined4 p_binary)
{
	if (m_unk0x98 != NULL) {
		for (LegoU32 i = 0; i < m_unk0x90; i++) {
			m_unk0x94[i] = m_unk0x04->CreateFontTable();
			m_unk0x94[i]->LoadFontDefinitions(m_unk0x08, &m_unk0x98[i * 9], p_binary);
		}

		delete[] m_unk0x98;
		m_unk0x98 = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004a18d0
void CutscenePlayer::FUN_004a18d0(GolFileParser* p_parser)
{
	if (m_unk0xa0 != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_unk0x9c = p_parser->ReadInteger();
	if (m_unk0x9c == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_unk0xa0 = new AwakeKite0x20*[m_unk0x9c];
	m_unk0xa4 = new LegoChar[m_unk0x9c * 9];
	if (m_unk0xa0 == NULL || m_unk0xa4 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoU32 i = 0;

	if (i < m_unk0x9c) {
		LegoU32 offset = 0;

		do {
			::strncpy(&m_unk0xa4[offset], p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
			i++;
			m_unk0xa4[offset + sizeof(GolName)] = '\0';
			offset += 9;
		} while (i < m_unk0x9c);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a19c0
void CutscenePlayer::FUN_004a19c0(undefined4 p_binary)
{
	if (m_unk0xa4 != NULL) {
		for (LegoU32 i = 0; i < m_unk0x9c; i++) {
			m_unk0xa0[i] = m_unk0x04->VTable0x34();
			m_unk0xa0[i]->LoadImageDefinitions(m_unk0x08, &m_unk0xa4[i * 9], p_binary);
		}

		delete[] m_unk0xa4;
		m_unk0xa4 = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004a1a40
void CutscenePlayer::FUN_004a1a40(GolFileParser* p_parser)
{
	if (m_unk0xb8 != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_unk0xb4 = p_parser->ReadInteger();
	if (m_unk0xb4 == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_unk0xa8.Allocate(m_unk0xb4);
	m_unk0xb8 = new CutsceneMoveEvent[m_unk0xb4];
	if (m_unk0xb8 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_unk0xb4; i++) {
		GolName name;

		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x2b);
		::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		m_unk0xa8.AddName(name, &m_unk0xb8[i]);
		m_unk0xb8[i].Parse(p_parser, this);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a1c00
void CutscenePlayer::FUN_004a1c00(GolFileParser* p_parser)
{
	if (m_unk0xcc != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_unk0xc8 = p_parser->ReadInteger();
	if (m_unk0xc8 == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_unk0xbc.Allocate(m_unk0xc8);
	m_unk0xcc = new CutsceneSoundEvent[m_unk0xc8];
	if (m_unk0xcc == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_unk0xc8; i++) {
		GolName name;

		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x2f);
		::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		m_unk0xbc.AddName(name, &m_unk0xcc[i]);
		m_unk0xcc[i].Parse(p_parser, this);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a1dc0
void CutscenePlayer::FUN_004a1dc0(GolFileParser* p_parser)
{
	if (m_unk0xe0 != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_unk0xdc = p_parser->ReadInteger();
	if (m_unk0xdc == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_unk0xd0.Allocate(m_unk0xdc);
	m_unk0xe0 = new CutsceneStreamingSoundEvent[m_unk0xdc];
	if (m_unk0xe0 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_unk0xdc; i++) {
		GolName name;

		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x36);
		::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		m_unk0xd0.AddName(name, &m_unk0xe0[i]);
		m_unk0xe0[i].Parse(p_parser, this);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a1f80
void CutscenePlayer::FUN_004a1f80(GolFileParser* p_parser)
{
	if (m_unk0xf4 != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_unk0xf0 = p_parser->ReadInteger();
	if (m_unk0xf0 == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_unk0xe4.Allocate(m_unk0xf0);
	m_unk0xf4 = new CutsceneAnimationEvent[m_unk0xf0];
	if (m_unk0xf4 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_unk0xf0; i++) {
		GolName name;

		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x3c);
		::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		m_unk0xe4.AddName(name, &m_unk0xf4[i]);
		m_unk0xf4[i].Parse(p_parser, this);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a20f0
void CutscenePlayer::FUN_004a20f0(GolFileParser* p_parser)
{
	if (m_unk0x108 != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_unk0x104 = p_parser->ReadInteger();
	if (m_unk0x104 == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_unk0xf8.Allocate(m_unk0x104);
	m_unk0x108 = new CutsceneMenuAnimationEvent[m_unk0x104];
	m_unk0x64 = new MenuAnimationList();
	if (m_unk0x108 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	if (m_unk0x64 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x64->Allocate(2);

	for (LegoU32 i = 0; i < m_unk0x104; i++) {
		GolName name;

		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x60);
		::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		m_unk0xf8.AddName(name, &m_unk0x108[i]);
		m_unk0x108[i].Parse(p_parser, this, m_unk0x64, m_unk0x08);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a2310
void CutscenePlayer::LoadTextEntries(GolFileParser* p_parser)
{
	if (m_unk0x11c != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_unk0x118 = p_parser->ReadInteger();
	if (m_unk0x118 == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_unk0x10c.Allocate(m_unk0x118);
	m_unk0x11c = new CutsceneTextVisual[m_unk0x118];
	if (m_unk0x11c == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_unk0x118; i++) {
		GolName name;

		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x3f);
		::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		m_unk0x10c.AddName(name, &m_unk0x11c[i]);
		m_unk0x11c[i].Parse(p_parser, this, m_unk0x08);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a24e0
void CutscenePlayer::FUN_004a24e0()
{
	for (LegoU32 i = 0; i < m_unk0x118; i++) {
		m_unk0x11c[i].RefreshString(this, m_unk0x08);
	}
}

// FUNCTION: LEGORACERS 0x004a2520
void CutscenePlayer::FUN_004a2520(GolFileParser* p_parser)
{
	if (m_unk0x130 != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_unk0x12c = p_parser->ReadInteger();
	if (m_unk0x12c == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_unk0x120.Allocate(m_unk0x12c);
	m_unk0x130 = new CutsceneImageVisual[m_unk0x12c];
	if (m_unk0x130 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_unk0x12c; i++) {
		GolName name;

		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x4d);
		::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		m_unk0x120.AddName(name, &m_unk0x130[i]);
		m_unk0x130[i].Parse(p_parser, this, m_unk0x08);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a26f0
void CutscenePlayer::FUN_004a26f0()
{
	for (LegoU32 i = 0; i < m_unk0x12c; i++) {
		m_unk0x130[i].FUN_004a3910(m_unk0x08);
	}
}

// FUNCTION: LEGORACERS 0x004a2730
void CutscenePlayer::FUN_004a2730(
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
			event = static_cast<CutsceneEvent*>(m_unk0xa8.GetName(targetName));
			break;
		case GolFileParser::e_unknown0x2f:
			event = static_cast<CutsceneEvent*>(m_unk0xbc.GetName(targetName));
			break;
		case GolFileParser::e_unknown0x36:
			event = static_cast<CutsceneEvent*>(m_unk0xd0.GetName(targetName));
			break;
		case GolFileParser::e_unknown0x3c:
			event = static_cast<CutsceneEvent*>(m_unk0xe4.GetName(targetName));
			break;
		case GolFileParser::e_unknown0x60:
			event = static_cast<CutsceneEvent*>(m_unk0xf8.GetName(targetName));
			break;
		case GolFileParser::e_unknown0x3f:
			event = static_cast<CutsceneEvent*>(m_unk0x10c.GetName(targetName));
			break;
		case GolFileParser::e_unknown0x4d:
			event = static_cast<CutsceneEvent*>(m_unk0x120.GetName(targetName));
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

		link->FUN_004a00c0(mode, event);
		p_parser->ReadRightCurly();
		link++;
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a2ac0
void CutscenePlayer::VTable0x00(void*, void* p_name, void*)
{
	if (m_unk0x13c.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_unk0x13c.GetName(static_cast<const LegoChar*>(p_name)));
		while (link != NULL) {
			link->FUN_004a00d0();
			link = link->GetNext();
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2b00
void CutscenePlayer::VTable0x04(void*, void* p_name, void*)
{
	if (m_unk0x150.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_unk0x150.GetName(static_cast<const LegoChar*>(p_name)));
		while (link != NULL) {
			link->FUN_004a00d0();
			link = link->GetNext();
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2b40
void CutscenePlayer::VTable0x08(void*, void* p_name, void* p_payload)
{
	if (m_unk0x164.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_unk0x164.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			CutsceneEventValuePayload* payload = static_cast<CutsceneEventValuePayload*>(p_payload);

			while (link != NULL) {
				link->FUN_004a00f0(payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2b80
void CutscenePlayer::VTable0x0c(void*, void* p_name, void* p_payload)
{
	if (m_unk0x178.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_unk0x178.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			CutsceneEventValuePayload* payload = static_cast<CutsceneEventValuePayload*>(p_payload);

			while (link != NULL) {
				link->FUN_004a00f0(payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2bc0
void CutscenePlayer::VTable0x10(void*, void* p_name, void* p_payload)
{
	if (m_unk0x18c.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_unk0x18c.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			CutsceneEventSelectorPayload* payload = static_cast<CutsceneEventSelectorPayload*>(p_payload);

			while (link != NULL) {
				link->FUN_004a0120(payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2c00
void CutscenePlayer::VTable0x14(void*, void* p_name, void* p_payload)
{
	if (m_unk0x1a0.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_unk0x1a0.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			CutsceneEventSelectorPayload* payload = static_cast<CutsceneEventSelectorPayload*>(p_payload);

			while (link != NULL) {
				link->FUN_004a0120(payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2c40
void CutscenePlayer::VTable0x18(void*, void* p_name, void* p_payload)
{
	if (m_unk0x1b4.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_unk0x1b4.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			CutsceneEventVectorPayload* payload = static_cast<CutsceneEventVectorPayload*>(p_payload);

			while (link != NULL) {
				link->FUN_004a0180(payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2c80
void CutscenePlayer::VTable0x1c(void*, void* p_name, void* p_payload)
{
	if (m_unk0x1c8.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_unk0x1c8.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			CutsceneEventVectorPayload* payload = static_cast<CutsceneEventVectorPayload*>(p_payload);

			while (link != NULL) {
				link->FUN_004a0180(payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2cc0
void CutscenePlayer::VTable0x20(void*, void* p_name, void* p_payload)
{
	if (m_unk0x1dc.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_unk0x1dc.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			while (link != NULL) {
				link->FUN_004a0200(p_payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2d00
void CutscenePlayer::VTable0x24(void*, void* p_name, void* p_payload)
{
	if (m_unk0x1f0.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_unk0x1f0.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			while (link != NULL) {
				link->FUN_004a0200(p_payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2d40
void CutscenePlayer::VTable0x28(void*, void* p_name, void* p_payload)
{
	if (m_unk0x204.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_unk0x204.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			while (link != NULL) {
				link->FUN_004a0200(p_payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2d80
void CutscenePlayer::VTable0x2c(void*, void* p_name, void* p_payload)
{
	if (m_unk0x218.GetNameEntries() != NULL) {
		CutsceneEventLink* link =
			static_cast<CutsceneEventLink*>(m_unk0x218.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			while (link != NULL) {
				link->FUN_004a0200(p_payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2dc0
void CutscenePlayer::FUN_004a2dc0(LegoU32 p_elapsedMs)
{
	if (m_unk0x04 != NULL) {
		LegoFloat elapsedSeconds = static_cast<LegoS32>(p_elapsedMs) * 0.001f;
		LegoU32 i;

		for (i = 0; i < m_unk0xb4; i++) {
			m_unk0xb8[i].FUN_004a4d10(elapsedSeconds);
		}

		for (i = 0; i < m_unk0xc8; i++) {
			m_unk0xcc[i].FUN_004a40f0();
		}

		for (i = 0; i < m_unk0xdc; i++) {
			m_unk0xe0[i].FUN_004a44f0();
		}

		for (i = 0; i < m_unk0x68; i++) {
			CutsceneAnimation* entries = m_unk0x6c;
			entries[i].FUN_00489fa0(p_elapsedMs);
		}

		for (i = 0; i < m_unk0x118; i++) {
			m_unk0x11c[i].FUN_004a3550(elapsedSeconds);
		}

		for (i = 0; i < m_unk0x12c; i++) {
			m_unk0x130[i].FUN_004a3550(elapsedSeconds);
		}

		for (i = 0; i < m_unk0xf0; i++) {
			m_unk0xf4[i].FUN_004a3df0(p_elapsedMs);
		}

		if (m_unk0x64 != NULL) {
			m_unk0x64->Update(p_elapsedMs);
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2f30
void CutscenePlayer::FUN_004a2f30(GolD3DRenderDevice* p_renderer)
{
	if (m_unk0x04 != NULL) {
		FUN_004a2f80(p_renderer->GetUnk0x0c());

		for (LegoU32 i = 0; i < m_unk0x68; i++) {
			m_unk0x6c[i].FUN_00489ff0(p_renderer);
		}
	}
}

// STUB: LEGORACERS 0x004a2f80
void CutscenePlayer::FUN_004a2f80(GolCamera* p_lens)
{
	GolVec3 position;
	GolVec3 right;
	GolVec3 forward;

	p_lens->GetTransform()->GetPosition(&position);
	p_lens->GetTransform()->GetRight(&right);
	p_lens->GetTransform()->GetForward(&forward);

	SoundNode* node = &m_unk0x14;

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
void CutscenePlayer::FUN_004a3070(GolD3DRenderDevice* p_renderer)
{
	if (m_unk0x04 != NULL) {
		for (LegoU32 i = 0; i < m_unk0x68; i++) {
			m_unk0x6c[i].FUN_0048a040(p_renderer);
		}
	}
}

// FUNCTION: LEGORACERS 0x004a30b0
void CutscenePlayer::FUN_004a30b0(GolD3DRenderDevice* p_renderer)
{
	if (m_unk0x04 != NULL) {
		p_renderer->VTable0xe8(FALSE);

		LegoU32 i;
		for (i = 0; i < m_unk0x12c; i++) {
			m_unk0x130[i].FUN_004a35a0(p_renderer);
		}

		for (i = 0; i < m_unk0x118; i++) {
			m_unk0x11c[i].FUN_004a35a0(p_renderer);
		}

		if (m_unk0x64 != NULL) {
			m_unk0x64->Draw(p_renderer);
		}

		p_renderer->VTable0xe4();
	}
}

// FUNCTION: LEGORACERS 0x004a3150
void CutscenePlayer::FUN_004a3150()
{
	LegoU32 i;

	for (i = 0; i < m_unk0xb4; i++) {
		m_unk0xb8[i].VTable0x18();
	}

	for (i = 0; i < m_unk0xc8; i++) {
		m_unk0xcc[i].VTable0x18();
	}

	for (i = 0; i < m_unk0xdc; i++) {
		m_unk0xe0[i].VTable0x18();
	}

	for (i = 0; i < m_unk0x118; i++) {
		m_unk0x11c[i].VTable0x18();
	}

	for (i = 0; i < m_unk0x12c; i++) {
		m_unk0x130[i].VTable0x18();
	}
}

// FUNCTION: LEGORACERS 0x004a3230
GolWorldEntity* CutscenePlayer::FUN_004a3230(const LegoChar* p_name)
{
	return m_unk0x10->FUN_00406e30(p_name);
}

// FUNCTION: LEGORACERS 0x004a3240
GolWorldEntity* CutscenePlayer::FUN_004a3240(const LegoChar* p_name)
{
	return m_unk0x10->FUN_00406e80(p_name);
}

// FUNCTION: LEGORACERS 0x004a3250
GolWorldEntity* CutscenePlayer::FUN_004a3250(const LegoChar* p_name)
{
	return m_unk0x10->FUN_00406ed0(p_name);
}

// FUNCTION: LEGORACERS 0x004a3260
GolStringTable* CutscenePlayer::GetStringTableByIndex(LegoU32 p_index)
{
	if (p_index == 0 && m_stringTable != NULL) {
		return m_stringTable;
	}

	return &m_unk0x7c[p_index];
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
	m_unk0x58 = NULL;
	m_unk0x5c[0] = '\0';
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
				::strncpy(m_unk0x5c, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
			}

			token = p_parser->GetNextToken();
		} while (token != GolFileParser::e_rightCurly);
	}

	if (m_unk0x5c[0] == '\0') {
		p_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
	}
}

// FUNCTION: LEGORACERS 0x004a3910
void CutsceneImageVisual::FUN_004a3910(GolD3DRenderDevice* p_renderer)
{
	m_unk0x58 = p_renderer->FindImageByName(m_unk0x5c);
	if (m_unk0x58 == NULL) {
		LegoChar text[64];
		::strncpy(text, m_unk0x5c, sizeof(GolName));
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
	*p_width = m_unk0x58->GetWidth();
	*p_height = m_unk0x58->GetHeight();
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
		m_unk0x58->m_unk0x4a.m_u32 = m_colorPacked;
	}

	p_renderer->VTable0x78(m_unk0x58, 0, &destRect, NULL);

	if (m_flags & 0x100) {
		union {
			ColorRGBA m_color;
			LegoU32 m_colorPacked;
		} color;

		color.m_color.m_red = 0xff;
		color.m_color.m_grn = 0xff;
		color.m_color.m_blu = 0xff;
		color.m_color.m_alp = 0xff;
		m_unk0x58->m_unk0x4a.m_u32 = color.m_colorPacked;
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
	m_unk0x14 = NULL;
	m_unk0x18 = NULL;
	m_unk0x1c[0] = '\0';
	m_unk0x24.m_x = 0.0f;
	m_unk0x24.m_y = 0.0f;
	m_unk0x24.m_z = 0.0f;
	m_unk0x30.m_x = 0.0f;
	m_unk0x30.m_y = 0.0f;
	m_unk0x30.m_z = 0.0f;
	m_unk0x3c.m_x = 0.0f;
	m_unk0x3c.m_y = 0.0f;
	m_unk0x3c.m_z = 0.0f;
	m_unk0x48 = 0;
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

			m_unk0x14 = p_owner->GetAnimationByIndex(index);
			::strncpy(m_unk0x1c, p_parser->ReadString(), sizeof(GolName));
			break;
		}
		case GolFileParser::e_unknown0x39:
			m_unk0x24.m_x = p_parser->ReadFloat();
			m_unk0x24.m_y = p_parser->ReadFloat();
			m_unk0x24.m_z = p_parser->ReadFloat();
			m_unk0x48 |= 1;
			break;
		case GolFileParser::e_unknown0x3e:
			m_unk0x30.m_x = p_parser->ReadFloat();
			m_unk0x30.m_y = p_parser->ReadFloat();
			m_unk0x30.m_z = p_parser->ReadFloat();
			m_unk0x3c.m_x = p_parser->ReadFloat();
			m_unk0x3c.m_y = p_parser->ReadFloat();
			m_unk0x3c.m_z = p_parser->ReadFloat();
			m_unk0x48 |= 2;
			break;
		case GolFileParser::e_unknown0x3a:
			m_unk0x48 |= 4;
			break;
		case GolFileParser::e_unknown0x3b:
			m_unk0x4c = p_parser->ReadInteger();
			m_unk0x48 |= 8;
			break;
		default:
			ParseCommonToken(p_parser, p_owner, token);
			break;
		}

		token = p_parser->GetNextToken();
	}
}

// FUNCTION: LEGORACERS 0x004a3c20
void CutsceneAnimationEvent::VTable0x14()
{
	if (m_unk0x18 == NULL) {
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

		VTable0x10(&v1, &v2, &v3);
	}
}

// FUNCTION: LEGORACERS 0x004a3c90
void CutsceneAnimationEvent::VTable0x10(const GolVec3* p_a, const GolVec3* p_b, const GolVec3* p_c)
{
	if (m_unk0x18 == NULL) {
		if ((m_unk0x48 & 8) && m_unk0x0c) {
			FUN_0049fe30(m_unk0x4c, &m_unk0x24);
			FUN_0049fec0(m_unk0x4c, &m_unk0x30, &m_unk0x3c);
			FUN_004a3db0();
			return;
		}

		if (!(m_unk0x48 & 1)) {
			if (m_unk0x04 != NULL) {
				m_unk0x04->VTable0x04(&m_unk0x24);
			}
			else {
				m_unk0x24 = *p_a;
			}
		}

		if (!(m_unk0x48 & 2)) {
			if (m_unk0x04 != NULL) {
				m_unk0x04->VTable0x48(&m_unk0x30, &m_unk0x3c);
			}
			else {
				m_unk0x30 = *p_b;
				m_unk0x3c = *p_c;
			}
		}

		FUN_004a3db0();
	}
}

// FUNCTION: LEGORACERS 0x004a3d70
void CutsceneAnimationEvent::VTable0x0c(GolWorldEntity* p_arg)
{
	if (m_unk0x18 == NULL) {
		if (m_unk0x04 == NULL) {
			m_unk0x04 = p_arg;
		}

		VTable0x14();
	}
}

// FUNCTION: LEGORACERS 0x004a3d90
void CutsceneAnimationEvent::VTable0x04(GolWorldEntity* p_arg)
{
	if (m_unk0x18 == NULL) {
		if (m_unk0x0c == NULL) {
			m_unk0x0c = static_cast<GolAnimatedEntity*>(p_arg);
		}

		VTable0x14();
	}
}

// FUNCTION: LEGORACERS 0x004a3db0
void CutsceneAnimationEvent::FUN_004a3db0()
{
	m_unk0x18 = m_unk0x14->FUN_00489d70(m_unk0x1c, &m_unk0x24, &m_unk0x30, &m_unk0x3c);
}

// FUNCTION: LEGORACERS 0x004a3dd0
void CutsceneAnimationEvent::VTable0x18()
{
	if (m_unk0x18) {
		m_unk0x14->FUN_00489f00(m_unk0x18);
		m_unk0x18 = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004a3df0
void CutsceneAnimationEvent::FUN_004a3df0(LegoU32)
{
	GolVec3 v0, v1, v2;

	if (m_unk0x18 && (m_unk0x48 & 8) && m_unk0x0c) {
		CutsceneEvent::FUN_0049fe30(m_unk0x4c, &v0);
		FUN_0049fec0(m_unk0x4c, &v1, &v2);
		if (m_unk0x18->m_unk0x00) {
			m_unk0x18->m_unk0x00->FUN_00489660(&v0);
		}
		if (m_unk0x18->m_unk0x00) {
			m_unk0x18->m_unk0x00->FUN_00489540(&v1, &v2);
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
	m_unk0x14 = NULL;
	m_unk0x18 = NULL;
	m_unk0x1c = g_crimsonPebbleEvent0x30DefaultVolume;
	m_unk0x20 = 0;
	m_unk0x24 = g_crimsonPebbleEvent0x30DefaultFrequencyScale;
	m_unk0x28 = g_crimsonPebbleEvent0x30DefaultPan;
	m_unk0x2c = 0;
	m_unk0x2e = 0;
}

// FUNCTION: LEGORACERS 0x004a3ef0
void CutsceneSoundEvent::Parse(GolFileParser* p_parser, CutscenePlayer* p_owner)
{
	if (m_unk0x14 != NULL) {
		FUN_004a4050();
	}

	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		if (!ParseToken(p_parser, p_owner, token)) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
		}

		token = p_parser->GetNextToken();
	}

	if (m_unk0x14 == NULL) {
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

		m_unk0x14 = p_owner->GetSoundGroupByIndex(index);
		m_unk0x2e = static_cast<LegoU16>(p_parser->ReadInteger());
		return TRUE;
	}
	case GolFileParser::e_unknown0x31:
		m_unk0x20 = p_parser->ReadInteger();
		return TRUE;
	case GolFileParser::e_unknown0x32:
		m_unk0x1c = p_parser->ReadFloat();
		return TRUE;
	case GolFileParser::e_unknown0x33:
		m_unk0x24 = p_parser->ReadFloat();
		return TRUE;
	case GolFileParser::e_unknown0x34:
		m_unk0x28 = p_parser->ReadFloat();
		return TRUE;
	case GolFileParser::e_unknown0x35:
		m_unk0x2c = 1;
		return TRUE;
	default:
		return FALSE;
	}
}

// FUNCTION: LEGORACERS 0x004a4050
void CutsceneSoundEvent::FUN_004a4050()
{
	Reset();
	CutsceneEvent::Reset();
}

// FUNCTION: LEGORACERS 0x004a4070
void CutsceneSoundEvent::VTable0x14()
{
	if (m_unk0x18 == NULL) {
		m_unk0x18 = m_unk0x14->CreateSoundInstance(m_unk0x2e);
		m_unk0x18->Play(m_unk0x2c);
		m_unk0x18->SetVolume(m_unk0x1c);
		m_unk0x18->SetPan(m_unk0x28);
		m_unk0x18->SetFrequencyScale(m_unk0x24);
		m_unk0x18->SetPriority(m_unk0x20);
	}
}

// FUNCTION: LEGORACERS 0x004a40d0
void CutsceneSoundEvent::VTable0x18()
{
	if (m_unk0x18 != NULL) {
		m_unk0x14->DestroySoundInstance(m_unk0x18);
		m_unk0x18 = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004a40f0
void CutsceneSoundEvent::FUN_004a40f0()
{
	if (m_unk0x18 != NULL) {
		if (!m_unk0x18->IsPlaying()) {
			VTable0x18();
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
	m_unk0x30 = NULL;
	m_unk0x34 = 100.0f;
	m_unk0x38 = 500.0f;
	m_unk0x3c.m_x = 0.0f;
	m_unk0x3c.m_y = 0.0f;
	m_unk0x3c.m_z = 0.0f;
	m_unk0x48 = 0;
	m_unk0x4c = 0;
	CutsceneSoundEvent::Reset();
	CutsceneEvent::Reset();
}

// FUNCTION: LEGORACERS 0x004a41a0
void CutsceneStreamingSoundEvent::Parse(GolFileParser* p_parser, CutscenePlayer* p_owner)
{
	if (m_unk0x14 != NULL) {
		FUN_004a42a0();
	}

	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case GolFileParser::e_unknown0x37:
			m_unk0x34 = p_parser->ReadFloat();
			break;
		case GolFileParser::e_unknown0x38:
			m_unk0x38 = p_parser->ReadFloat();
			break;
		case GolFileParser::e_unknown0x39:
			m_unk0x3c.m_x = p_parser->ReadFloat();
			m_unk0x3c.m_y = p_parser->ReadFloat();
			m_unk0x3c.m_z = p_parser->ReadFloat();
			m_unk0x48 |= 1;
			break;
		case GolFileParser::e_unknown0x3a:
			m_unk0x48 = (m_unk0x48 & ~4) | 2;
			break;
		case GolFileParser::e_unknown0x3b:
			m_unk0x4c = p_parser->ReadInteger();
			m_unk0x48 = (m_unk0x48 & ~2) | 4;
			break;
		default:
			if (!ParseToken(p_parser, p_owner, token)) {
				ParseCommonToken(p_parser, p_owner, token);
			}
			break;
		}

		token = p_parser->GetNextToken();
	}

	if (m_unk0x14 == NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
	}
}

// FUNCTION: LEGORACERS 0x004a42a0
void CutsceneStreamingSoundEvent::FUN_004a42a0()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a42b0
void CutsceneStreamingSoundEvent::VTable0x14()
{
	if (m_unk0x30 == NULL) {
		GolVec3 velocity;
		GolVec3 position;
		velocity.m_x = 0.0f;
		velocity.m_y = 0.0f;
		velocity.m_z = 0.0f;

		if ((m_unk0x48 & c_flagBit2) && m_unk0x0c != NULL) {
			FUN_0049fe30(m_unk0x4c, &position);
			m_unk0x0c->GetVelocity(&velocity);
		}
		else if (m_unk0x48 & c_flagBit0) {
			position = m_unk0x3c;
		}
		else if (m_unk0x04 != NULL) {
			m_unk0x04->VTable0x04(&position);
			m_unk0x04->GetVelocity(&velocity);
		}
		else {
			position.m_x = 0.0f;
			position.m_y = 0.0f;
			position.m_z = 0.0f;
		}

		FUN_004a43a0(&position);
		m_unk0x30->SetVelocity(velocity);
	}
}

// STUB: LEGORACERS 0x004a43a0
void CutsceneStreamingSoundEvent::FUN_004a43a0(const GolVec3* p_position)
{
	if (m_unk0x30 == NULL) {
		m_unk0x30 = m_unk0x14->CreateStreamingSoundInstance(m_unk0x2e);
		m_unk0x30->Play(m_unk0x2c);
		m_unk0x30->SetVolume(m_unk0x1c);
		m_unk0x30->SetFrequencyScale(m_unk0x24);
		LegoFloat maxDistance = m_unk0x38;
		LegoFloat minDistance = m_unk0x34;
		m_unk0x30->SetDistanceRange(minDistance, maxDistance);

		m_unk0x48 &= ~c_flagBit3;
		if (m_unk0x48 & c_flagBit0) {
			m_unk0x30->SetPosition(&m_unk0x3c);
			return;
		}

		m_unk0x30->SetPosition(p_position);
	}
}

// FUNCTION: LEGORACERS 0x004a4450
void CutsceneStreamingSoundEvent::VTable0x10(const GolVec3* p_a, const GolVec3*, const GolVec3*)
{
	if (m_unk0x30 == NULL) {
		if (m_unk0x04 == NULL && !(m_unk0x48 & 1)) {
			FUN_004a43a0(p_a);
		}
		else {
			VTable0x14();
		}
	}
}

// FUNCTION: LEGORACERS 0x004a4480
void CutsceneStreamingSoundEvent::VTable0x0c(GolWorldEntity* p_arg)
{
	if (m_unk0x30 == NULL) {
		if (m_unk0x04 == NULL) {
			m_unk0x04 = p_arg;
		}

		VTable0x14();
	}
}

// FUNCTION: LEGORACERS 0x004a44a0
void CutsceneStreamingSoundEvent::VTable0x04(GolWorldEntity* p_arg)
{
	if (m_unk0x30 == NULL) {
		if (m_unk0x0c == NULL) {
			m_unk0x0c = static_cast<GolAnimatedEntity*>(p_arg);
			m_unk0x04 = p_arg;
		}

		VTable0x14();
	}
}

// FUNCTION: LEGORACERS 0x004a44c0
void CutsceneStreamingSoundEvent::VTable0x18()
{
	if (m_unk0x30) {
		m_unk0x48 &= ~c_flagBit3;
		m_unk0x14->DestroyStreamingSoundInstance(m_unk0x30);
		m_unk0x30 = NULL;
	}
}

// STUB: LEGORACERS 0x004a44f0
void CutsceneStreamingSoundEvent::FUN_004a44f0()
{
	if (m_unk0x30) {
		if (!m_unk0x30->IsPlaying()) {
			if (m_unk0x48 & c_flagBit3) {
				VTable0x18();
				return;
			}
		}
		else {
			m_unk0x48 |= c_flagBit3;
		}

		GolVec3 position;
		GolVec3 velocity;
		GolWorldEntity* entity;

		if (m_unk0x48 & c_flagBit2) {
			FUN_0049fe30(m_unk0x4c, &position);
			m_unk0x30->SetPosition(&position);
			entity = m_unk0x0c;
		}
		else if (m_unk0x48 & c_flagBit1) {
			m_unk0x04->VTable0x04(&position);
			m_unk0x30->SetPosition(&position);
			entity = m_unk0x04;
		}
		else {
			return;
		}

		entity->GetVelocity(&velocity);
		m_unk0x30->SetVelocity(velocity);
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
	m_unk0x14 = NULL;
	m_unk0x18 = NULL;
	m_unk0x1c = NULL;
	m_unk0x24 = 0;
	m_unk0x28 = 0;
	m_unk0x20 = 0;
	m_unk0x21 = 0;
	m_unk0x22 = 0;
	m_unk0x23 = 0;
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
	m_unk0x14 = p_animationList;
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case GolFileParser::e_unknown0x61:
			m_unk0x24 = p_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x62: {
			GolFileParser::ParserTokenType mode = p_parser->GetNextToken();
			switch (mode) {
			case GolFileParser::e_unknown0x63:
				m_unk0x28 |= 1;
				break;
			case GolFileParser::e_unknown0x64:
				m_unk0x28 |= 2;
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
			m_unk0x20 = static_cast<LegoU8>(p_parser->ReadInteger());
			m_unk0x21 = static_cast<LegoU8>(p_parser->ReadInteger());
			m_unk0x22 = static_cast<LegoU8>(p_parser->ReadInteger());
			break;
		default:
			ParseCommonToken(p_parser, p_owner, token);
			break;
		}

		token = p_parser->GetNextToken();
	}

	if (materialName[0] != '\0') {
		m_unk0x18 = p_renderer->FindMaterialByName(materialName);
	}
}

// FUNCTION: LEGORACERS 0x004a4af0
void CutsceneMenuAnimationEvent::VTable0x14()
{
	if (m_unk0x28 & 1) {
		m_unk0x1c = m_unk0x14->Activate(m_unk0x24, TRUE, m_unk0x18, NULL);
	}
	else if (m_unk0x28 & 2) {
		m_unk0x1c = m_unk0x14->Activate(m_unk0x24, FALSE, m_unk0x18, NULL);
	}

	if (m_unk0x1c != NULL) {
		m_unk0x1c->SetColor(m_colorPacked);
	}
}

// FUNCTION: LEGORACERS 0x004a4b40
void CutsceneMenuAnimationEvent::VTable0x18()
{
	if (m_unk0x1c != NULL) {
		m_unk0x14->Deactivate(m_unk0x1c);
		m_unk0x1c = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004a4b60
CutsceneMoveEvent::CutsceneMoveEvent()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a4bb0
void CutsceneMoveEvent::Reset()
{
	m_unk0x08 = NULL;
	m_active = FALSE;
	m_baseX = 0;
	m_baseY = 0;
	m_baseZ = 0;
	m_offsetStartX = 0;
	m_offsetStartY = 0;
	m_offsetStartZ = 0;
	m_offsetX = 0.0f;
	m_offsetY = 0.0f;
	m_offsetZ = 0.0f;
	m_offsetDeltaX = 0.0f;
	m_offsetDeltaY = 0.0f;
	m_offsetDeltaZ = 0.0f;
}

// FUNCTION: LEGORACERS 0x004a4be0
void CutsceneMoveEvent::Parse(GolFileParser* p_parser, CutscenePlayer* p_owner)
{
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case GolFileParser::e_unknown0x2c:
			m_baseX = p_parser->ReadInteger();
			m_baseY = p_parser->ReadInteger();
			m_baseZ = p_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x2d:
			m_offsetStartX = p_parser->ReadInteger();
			m_offsetStartY = p_parser->ReadInteger();
			m_offsetStartZ = p_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x2e:
			m_offsetDeltaX = p_parser->ReadFloat();
			m_offsetDeltaY = p_parser->ReadFloat();
			m_offsetDeltaZ = p_parser->ReadFloat();
			break;
		default:
			ParseCommonToken(p_parser, p_owner, token);
			break;
		}

		token = p_parser->GetNextToken();
	}
}

// FUNCTION: LEGORACERS 0x004a4ca0
void CutsceneMoveEvent::VTable0x14()
{
	if (!m_active && m_unk0x08 != NULL) {
		m_active = TRUE;
		m_offsetX = static_cast<LegoFloat>(m_offsetStartX);
		m_offsetY = static_cast<LegoFloat>(m_offsetStartY);
		m_offsetZ = static_cast<LegoFloat>(m_offsetStartZ);
		FUN_004a4da0();
	}
}

// FUNCTION: LEGORACERS 0x004a4cd0
void CutsceneMoveEvent::VTable0x08(GolWorldEntity* p_arg)
{
	if (!m_active) {
		if (m_unk0x08 == NULL) {
			m_unk0x08 = p_arg;
		}

		VTable0x14();
	}
}

// FUNCTION: LEGORACERS 0x004a4cf0
void CutsceneMoveEvent::VTable0x18()
{
	if (m_active) {
		m_active = FALSE;
		if (m_unk0x08 != NULL) {
			m_unk0x08->VTable0x28();
		}
	}
}

// FUNCTION: LEGORACERS 0x004a4d10
void CutsceneMoveEvent::FUN_004a4d10(LegoFloat p_elapsedSeconds)
{
	if (m_active) {
		if (m_unk0x08 != 0) {
			LegoFloat deltaX = m_offsetDeltaX * p_elapsedSeconds;
			LegoFloat deltaY = m_offsetDeltaY * p_elapsedSeconds;
			LegoFloat deltaZ = m_offsetDeltaZ * p_elapsedSeconds;

			if (static_cast<LegoS32>(deltaX) || static_cast<LegoS32>(deltaY) || static_cast<LegoS32>(deltaZ)) {
				m_offsetX += deltaX;
				m_offsetY += deltaY;
				m_offsetZ += deltaZ;
				FUN_004a4da0();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a4da0
void CutsceneMoveEvent::FUN_004a4da0()
{
	ColorTransform0x20 transform;
	transform.m_redShift = m_baseX;
	transform.m_grnShift = m_baseY;
	transform.m_bluShift = m_baseZ;
	transform.m_alpShift = 0;
	transform.m_redOffset = static_cast<LegoS32>(m_offsetX);
	transform.m_grnOffset = static_cast<LegoS32>(m_offsetY);
	transform.m_bluOffset = static_cast<LegoS32>(m_offsetZ);
	transform.m_alpOffset = 0;

	m_unk0x08->VTable0x24(&transform);
}
