#include "race/hazards/snowfallhazard.h"

#include "camera/golcamera.h"
#include "decomp.h"
#include "golfileparser.h"
#include "golmath.h"
#include "menu/runtime/cutsceneparticle.h"
#include "race/hazards/hazardcontext.h"
#include "race/racer/racer.h"
#include "types.h"

DECOMP_SIZE_ASSERT(SnowfallHazard, 0x20)

extern LegoU16 g_randomTable[1024];
extern LegoU32 g_randomTableIndex;

// GLOBAL: LEGORACERS 0x004b461c
extern const LegoFloat g_snowfallCameraForwardScale = 100.0f;

// GLOBAL: LEGORACERS 0x004b4620
extern const LegoFloat g_snowfallCameraVerticalOffset = -40.0f;

// FUNCTION: LEGORACERS 0x0048e980
SnowfallHazard::SnowfallHazard()
{
	ClearFields();
}

// FUNCTION: LEGORACERS 0x0048e9f0
SnowfallHazard::~SnowfallHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048ea40
LegoS32 SnowfallHazard::ClearFields()
{
	m_particleAnimation = NULL;
	m_snowParticle = NULL;
	m_resetMs = 0;
	m_snowEnabled = 0;
	return 0;
}

// FUNCTION: LEGORACERS 0x0048ea50
void SnowfallHazard::Load(HazardContext* p_context, GolFileParser*)
{
	if (m_state) {
		Reset();
	}

	m_triggerId = -1;
	m_particleAnimation = p_context->GetParticleAnimation();
	m_state = c_stateLoaded;
	OnActivate(NULL);
}

// FUNCTION: LEGORACERS 0x0048ea90
LegoS32 SnowfallHazard::Reset()
{
	OnDeactivate(NULL);
	ClearFields();
	return Hazard::Reset();
}

// FUNCTION: LEGORACERS 0x0048eab0
void SnowfallHazard::OnActivate(void*)
{
	m_snowEnabled = 1;
	m_state = c_stateActive;
}

// FUNCTION: LEGORACERS 0x0048ead0
void SnowfallHazard::OnDeactivate(void*)
{
	if (m_snowParticle) {
		m_particleAnimation->FinishRef(m_snowParticle);
		m_snowParticle = NULL;
	}

	m_state = c_stateLoaded;
}

// FUNCTION: LEGORACERS 0x0048eb00
void SnowfallHazard::Update(undefined4 p_elapsedMs)
{
	if (m_state == c_stateLoaded) {
		return;
	}

	LegoU32 elapsedMs = p_elapsedMs;
	Hazard::Update(p_elapsedMs);
	m_resetMs += elapsedMs;
	if (m_resetMs > c_snowResetMs && m_snowParticle) {
		m_particleAnimation->FinishRef(m_snowParticle);
		m_snowParticle = NULL;
	}

	if (m_snowEnabled && !m_snowParticle) {
		m_snowParticle = m_particleAnimation->SpawnParticle("snow", NULL, NULL, NULL);
		if (m_snowParticle) {
			m_resetMs = 0;
		}
	}
}

// FUNCTION: LEGORACERS 0x0048eb70
void SnowfallHazard::UpdatePerRacer(GolCamera* p_camera, Racer* p_racer)
{
	if (p_racer->m_visuals.m_hasColorTransform) {
		m_snowEnabled = 0;
		if (m_snowParticle) {
			m_particleAnimation->FinishRef(m_snowParticle);
			m_snowParticle = NULL;
		}
	}
	else {
		m_snowEnabled = 1;
	}

	if (m_snowParticle) {
		GolVec3 position;
		GolVec3 direction;
		GolVec3 up;
		p_camera->GetTransform()->VTable0x1c(&direction, &up);

		p_camera->GetTransform()->GetPosition(&position);
		position.m_x = g_snowfallCameraForwardScale * direction.m_x + position.m_x;
		position.m_y = g_snowfallCameraForwardScale * direction.m_y + position.m_y;
		LegoFloat scaledZ = g_snowfallCameraForwardScale * direction.m_z;

		direction.m_z = 0.0f;
		scaledZ += position.m_z;
		position.m_z = scaledZ + g_snowfallCameraVerticalOffset * up.m_z;
		GolMath::NormalizeVector3(direction, &direction);

		up.m_x = 0.0f;
		g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
		up.m_y = 0.0f;
		LegoU16 randomValue = g_randomTable[g_randomTableIndex];
		up.m_z = 1.0f;

		LegoFloat lateral = direction.m_y;
		lateral -= up.m_x;
		LegoU32 remainder = static_cast<LegoU32>(randomValue) % 200;
		LegoS32 offsetInt = static_cast<LegoS32>(remainder - 100);
		LegoFloat offset = static_cast<LegoFloat>(offsetInt);
		CutsceneParticleRef* ref = m_snowParticle;
		position.m_x = lateral * offset + position.m_x;
		position.m_y = (up.m_y - direction.m_x) * offset + position.m_y;

		if (ref->m_particle) {
			ref->m_particle->SetOrientation(&direction, &up);
		}

		ref = m_snowParticle;
		if (ref->m_particle) {
			ref->m_particle->SetPosition(&position);
		}
	}
}

// FUNCTION: LEGORACERS 0x0048ece0
void SnowfallHazard::ResetState()
{
	if (m_snowParticle) {
		m_particleAnimation->FinishRef(m_snowParticle);
		m_snowParticle = NULL;
	}

	m_state = c_stateLoaded;
	OnActivate(NULL);
}
