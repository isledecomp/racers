#include "race/hazards/smokeventhazard.h"

#include "decomp.h"
#include "golanimatedentity.h"
#include "golfileparser.h"
#include "golmath.h"
#include "golmodelbase.h"
#include "golscenenode.h"
#include "goltransformbase.h"
#include "menu/runtime/cutsceneparticle.h"
#include "race/hazards/hazardcontext.h"
#include "types.h"
#include "world/golworlddatabase.h"

DECOMP_SIZE_ASSERT(SmokeVentHazard, 0x20)

extern LegoU16 g_randomTable[1024];
extern LegoU32 g_randomTableIndex;

// GLOBAL: LEGORACERS 0x004b45b0
extern const GolVec3 g_smokeVentSmokeOffsets[4] = {
	{-24.45f, 26.74f, -19.56f},
	{-35.72f, 9.41f, -18.41f},
	{-6.9f, -9.13f, -15.49f},
	{4.37f, 8.54f, -16.65f},
};

// FUNCTION: LEGORACERS 0x0048e680
SmokeVentHazard::SmokeVentHazard()
{
	m_entity = NULL;
	m_particleAnimation = NULL;
	m_smokeParticle = NULL;
	m_mirror = 0;
}

// FUNCTION: LEGORACERS 0x0048e6c0
SmokeVentHazard::~SmokeVentHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048e710
void SmokeVentHazard::Load(HazardContext* p_context, GolFileParser*)
{
	if (m_state) {
		Reset();
	}

	m_triggerId = 10;
	m_eventTable = p_context->GetEventTable();
	m_particleAnimation = p_context->GetParticleAnimation();
	m_mirror = p_context->GetMirror();
	m_entity = p_context->GetTrackDatabase()->FindAnimatedEntity("dp_def");
	m_state = c_stateLoaded;
}

// FUNCTION: LEGORACERS 0x0048e780
LegoS32 SmokeVentHazard::Reset()
{
	OnDeactivate(NULL);
	m_entity = NULL;
	m_particleAnimation = NULL;
	m_mirror = 0;
	return Hazard::Reset();
}

// FUNCTION: LEGORACERS 0x0048e7b0
void SmokeVentHazard::OnActivate(void*)
{
	m_state = c_stateActive;
}

// FUNCTION: LEGORACERS 0x0048e7c0
void SmokeVentHazard::OnDeactivate(void*)
{
	if (m_smokeParticle) {
		m_particleAnimation->FinishRef(m_smokeParticle);
		m_smokeParticle = NULL;
	}

	m_state = c_stateLoaded;
}

// FUNCTION: LEGORACERS 0x0048e7f0
void SmokeVentHazard::Update(undefined4 p_elapsedMs)
{
	if (m_state == c_stateLoaded) {
		return;
	}

	LegoFloat scale = m_entity->GetModel(0)->GetScale() * m_entity->GetScale();
	LegoFloat inverseScale = 1.0f / scale;
	Hazard::Update(p_elapsedMs);

	GolSceneNode* node = m_entity->GetSceneNode(0);
	GolTransformBase* transform = node->GetTransform(0);

	GolVec3 vector;
	transform->GetPosition(&vector);
	vector.m_x *= scale;
	vector.m_y *= scale;
	vector.m_z *= scale;

	GolVec3 position;
	m_entity->LocalToWorld(vector, &position);

	if (m_smokeParticle || (m_smokeParticle = m_particleAnimation->SpawnParticle("smoke", NULL, NULL, NULL)) != NULL) {
		g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
		LegoU32 offsetIndex = g_randomTable[g_randomTableIndex] & 3;
		vector.m_x = g_smokeVentSmokeOffsets[offsetIndex].m_x;
		vector.m_x *= inverseScale;
		vector.m_y = g_smokeVentSmokeOffsets[offsetIndex].m_y;
		vector.m_y *= inverseScale;
		vector.m_z = g_smokeVentSmokeOffsets[offsetIndex].m_z;

		LegoU32 flipOffset = m_mirror;
		vector.m_z *= inverseScale;
		if (flipOffset) {
			vector.m_y = -vector.m_y;
		}

		transform->TransformPoint(&vector, &position);
		vector.m_x = position.m_x * scale;
		vector.m_y = position.m_y * scale;
		vector.m_z = position.m_z * scale;

		m_entity->LocalToWorld(vector, &position);

		CutsceneParticleRef* particleRef = m_smokeParticle;
		GolAnimatedEntity* entity = m_entity;
		CutsceneParticle* particle = particleRef->m_particle;
		if (particle) {
			entity->CopyOrientation(particle->GetBasis());
		}

		particleRef = m_smokeParticle;
		if (particleRef->m_particle) {
			particleRef->m_particle->SetPosition(&position);
		}
	}
}
