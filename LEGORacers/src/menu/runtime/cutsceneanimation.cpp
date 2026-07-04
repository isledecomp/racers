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
#include "image/golimage.h"
#include "mabmaterialanimation.h"
#include "mabmaterialtrack.h"
#include "material/golimagedefinitionlist.h"
#include "menu/menuanimationlist.h"
#include "menu/runtime/cutscenedefinition.h"
#include "menu/runtime/cutsceneparticle.h"
#include "menu/runtime/cutsceneplayer.h"
#include "render/gold3drenderdevice.h"
#include "render/golrenderdevice.h"
#include "render/rectangle.h"

#include <string.h>

DECOMP_SIZE_ASSERT(CutsceneAnimation::EmbTxtParser, 0x1fc)
DECOMP_SIZE_ASSERT(CutsceneAnimation::Entry, 0x08)
DECOMP_SIZE_ASSERT(CutsceneAnimation::Emitter, 0x44)
DECOMP_SIZE_ASSERT(CutsceneAnimation, 0x33c)

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
	MabMaterialAnimation* p_materialAnimation,
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
	parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(EmbTxtParser::e_emitters));

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
		m_particles[i].Initialize(p_golExport, p_renderer);
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
			currentParticle->ActivateEmitter(runtime);
			if (p_param3 != NULL && p_param4 != NULL) {
				currentParticle->SetOrientation(p_param3, p_param4);
			}
			if (p_param2 != NULL) {
				currentParticle->SetPosition(p_param2);
			}

			if (runtime->IsPersistent()) {
				CutsceneParticleRef* ref = &m_refs[refIndex];
				ref->m_flags |= CutsceneParticleRef::c_flagInUse;
				ref->m_particle = currentParticle;
				currentParticle->SetRef(ref);
				return ref;
			}

			return NULL;
		}

		Emitter* activeRuntime = currentParticle->GetEmitter();
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

	particle->Deactivate();

	particle->ActivateEmitter(runtime);
	if (p_param3 != NULL && p_param4 != NULL) {
		particle->SetOrientation(p_param3, p_param4);
	}
	if (p_param2 != NULL) {
		particle->SetPosition(p_param2);
	}

	if (runtime->IsPersistent()) {
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
		p_param->m_particle->Deactivate();
	}

	p_param->m_particle = NULL;
	p_param->m_flags &= ~CutsceneParticleRef::c_flagInUse;
}

// FUNCTION: LEGORACERS 0x00489f30
void CutsceneAnimation::FinishRef(CutsceneParticleRef* p_param)
{
	if (p_param->m_particle) {
		p_param->m_particle->Finish();
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
			m_particles[i].Deactivate();
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
			m_particles[i].Update(p_elapsedMs);
		}
	}
}

// FUNCTION: LEGORACERS 0x00489ff0
void CutsceneAnimation::Draw(GolD3DRenderDevice* p_renderer)
{
	for (LegoU32 i = 0; i < m_numParticles; i++) {
		if (m_particles[i].IsActive()) {
			m_particles[i].Draw(p_renderer);
		}
	}
}

// FUNCTION: LEGORACERS 0x0048a040
void CutsceneAnimation::DrawTransparent(GolD3DRenderDevice* p_renderer)
{
	for (LegoU32 i = 0; i < m_numParticles; i++) {
		if (m_particles[i].IsActive()) {
			m_particles[i].DrawTransparent(p_renderer);
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
	if (m_points) {
		delete[] m_points;
		m_points = NULL;
	}

	Reset();
}

// FUNCTION: LEGORACERS 0x0048a0e0
void CutsceneAnimation::Emitter::Reset()
{
	m_points = NULL;
	m_pointCount = 0;
	m_materialAnimationItem = 0;
	m_materialAnimation = NULL;
	m_material = NULL;
	m_emitIntervalMs = 0;
	m_emitChance = 0;
	m_startSizeUp = 1.0f;
	m_startSizeForward = 1.0f;
	m_sizeGrowthUp = 0.0f;
	m_sizeGrowthForward = 0.0f;
	m_originX = 0.0f;
	m_originY = 0.0f;
	m_originZ = 0.0f;
	m_radius = 0.0f;
	m_particleLifeMs = 0;
	m_priority = 0;
	m_durationMs = -1;
}

// FUNCTION: LEGORACERS 0x0048a130
void CutsceneAnimation::Emitter::Parse(
	MabMaterialAnimation* p_materialAnimation,
	GolD3DRenderDevice* p_renderer,
	GolFileParser* p_parser,
	CutsceneAnimation* p_param4
)
{
	if (m_points) {
		Clear();
	}

	LegoU32 i;

	m_materialAnimationItem = 0;
	m_material = 0;
	m_materialAnimation = p_materialAnimation;

	p_parser->AssertNextTokenIs(
		static_cast<GolFileParser::ParserTokenType>(CutscenePlayer::CebTxtParser::e_animations)
	);

	LegoChar name[8];
	strncpy(name, p_parser->ReadStringWithMaxLength(8), 8);

	p_param4->AddName(name, this);
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token;

	while ((token = p_parser->GetNextToken()) != GolFileParser::e_rightCurly) {
		switch (token) {
		case CutsceneAnimation::EmbTxtParser::e_emitInterval:
			m_emitIntervalMs = static_cast<LegoS32>(g_floatConst1000 / p_parser->ReadFloat());
			break;
		case CutsceneAnimation::EmbTxtParser::e_emitChance:
			m_emitChance = static_cast<LegoS32>(p_parser->ReadFloat() * g_floatConst256);
			break;
		case CutsceneAnimation::EmbTxtParser::e_priority:
			m_priority = static_cast<LegoU8>(p_parser->ReadInteger());
			break;
		case CutsceneAnimation::EmbTxtParser::e_startSizeUp:
			m_startSizeUp = p_parser->ReadFloat();
			break;
		case CutsceneAnimation::EmbTxtParser::e_startSizeForward:
			m_startSizeForward = p_parser->ReadFloat();
			break;
		case CutsceneAnimation::EmbTxtParser::e_sizeGrowthUp:
			m_sizeGrowthUp = p_parser->ReadFloat();
			break;
		case CutsceneAnimation::EmbTxtParser::e_sizeGrowthForward:
			m_sizeGrowthForward = p_parser->ReadFloat();
			break;
		case CutsceneAnimation::EmbTxtParser::e_radius:
			m_radius = p_parser->ReadFloat();
			break;
		case CutsceneAnimation::EmbTxtParser::e_particleLifeMs:
			m_particleLifeMs = p_parser->ReadInteger();
			break;
		case CutsceneAnimation::EmbTxtParser::e_durationMs:
			m_durationMs = p_parser->ReadInteger();
			break;
		case CutsceneAnimation::EmbTxtParser::e_origin:
			m_originX = p_parser->ReadFloat();
			m_originY = p_parser->ReadFloat();
			m_originZ = p_parser->ReadFloat();
			break;
		case CutsceneAnimation::EmbTxtParser::e_materialAnimationItem:
			i = p_parser->ReadInteger();
			m_materialAnimationItem = &p_materialAnimation->GetTracks()[i];
			break;
		case CutsceneAnimation::EmbTxtParser::e_material: {
			LegoChar materialName[8];
			strncpy(materialName, p_parser->ReadStringWithMaxLength(8), 8);
			m_material = p_renderer->FindMaterialByName(materialName);
			break;
		}
		case CutsceneAnimation::EmbTxtParser::e_points:
			p_parser->ReadLeftBracket();
			m_pointCount = p_parser->ReadInteger();
			p_parser->ReadRightBracket();

			m_points = new GolVec3[m_pointCount];

			if (!m_points) {
				GolFatalError(c_golErrorOutOfMemory, NULL, 0);
			}
			p_parser->ReadLeftCurly();

			for (i = 0; i < m_pointCount; i++) {
				m_points[i].m_x = p_parser->ReadFloat();
				m_points[i].m_y = p_parser->ReadFloat();
				m_points[i].m_z = p_parser->ReadFloat();
			}

			p_parser->ReadRightCurly();
			break;
		default:
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
		}
	}
}

// FUNCTION: LEGORACERS 0x0048a3b0
void CutsceneAnimation::Emitter::GetVectorAt(GolVec3* p_vec, int p_index)
{
	p_vec->m_x = m_points[p_index].m_x;
	p_vec->m_y = m_points[p_index].m_y;
	p_vec->m_z = m_points[p_index].m_z;
}

// FUNCTION: LEGORACERS 0x0048a3e0
void CutsceneAnimation::Emitter::GetOrigin(GolVec3* p_vec) const
{
	p_vec->m_x = m_originX;
	p_vec->m_y = m_originY;
	p_vec->m_z = m_originZ;
}
