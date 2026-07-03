#include "race/hazards/oscillatorhazard.h"

#include "decomp.h"
#include "golanimatedentity.h"
#include "golfileparser.h"
#include "golmath.h"
#include "golmodelentity.h"
#include "golname.h"
#include "race/hazards/hazardcontext.h"
#include "types.h"
#include "world/golworlddatabase.h"

#include <string.h>

DECOMP_SIZE_ASSERT(OscillatorHazard, 0x20)

extern LegoFloat g_cosineTable[1024];

static const LegoFloat g_oscillatorCycleMs = 10000.0f;

static const LegoFloat g_oscillatorInvCycleMs = 0.0001f;

static const LegoFloat g_oscillatorTau = 6.2831855f;

static const LegoFloat g_oscillatorCosineIndexScale = -162.974655f;

// FUNCTION: LEGORACERS 0x0048b080
OscillatorHazard::OscillatorHazard()
{
	m_entity = NULL;
	m_amplitude0 = 0.0f;
	m_amplitude1 = 0.0f;
	m_phaseMs = 0.0f;
}

// FUNCTION: LEGORACERS 0x0048b0c0
OscillatorHazard::~OscillatorHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048b110
void OscillatorHazard::Load(HazardContext* p_context, GolFileParser* p_parser)
{
	if (m_state) {
		Reset();
	}

	m_triggerId = -1;
	m_eventTable = p_context->GetEventTable();

	GolName name;
	::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));

	m_entity = p_context->GetTrackDatabase()->FindModelEntity(name);
	if (!m_entity) {
		m_entity = p_context->GetTrackDatabase()->FindAnimatedEntity(name);
	}

	if (!m_entity) {
		m_entity = p_context->GetSharedDatabase()->FindModelEntity(name);
	}

	if (!m_entity) {
		m_entity = p_context->GetSharedDatabase()->FindAnimatedEntity(name);
	}

	m_amplitude0 = p_parser->ReadFloat();
	m_amplitude1 = p_parser->ReadFloat();
	m_state = c_stateLoaded;
}

// FUNCTION: LEGORACERS 0x0048b220
void OscillatorHazard::OnActivate(void*)
{
	m_state = c_stateActive;
	m_phaseMs = 0.0f;
}

// FUNCTION: LEGORACERS 0x0048b240
void OscillatorHazard::Update(undefined4 p_elapsedMs)
{
	Hazard::Update(p_elapsedMs);

	m_phaseMs += static_cast<LegoFloat>(static_cast<LegoU32>(p_elapsedMs));
	if (m_phaseMs >= g_oscillatorCycleMs) {
		m_phaseMs -= g_oscillatorCycleMs;
	}

	LegoFloat scaledTime = m_phaseMs;
	scaledTime *= g_oscillatorInvCycleMs;
	scaledTime *= g_oscillatorTau;
	scaledTime *= g_oscillatorCosineIndexScale;

	LegoS32 index = -256 - static_cast<LegoS32>(scaledTime);
	index &= 0x3ff;
	LegoFloat scale = g_cosineTable[index];

	LegoFloat amount = m_amplitude0;
	amount *= scale;
	m_entity->SetTextureScrollSpeedU(amount);

	amount = m_amplitude1;
	amount *= scale;
	m_entity->SetTextureScrollSpeedV(amount);
}

// FUNCTION: LEGORACERS 0x0048d470 FOLDED
void OscillatorHazard::OnDeactivate(void*)
{
	m_state = c_stateLoaded;
}

// FUNCTION: LEGORACERS 0x0048b9b0 FOLDED
LegoS32 OscillatorHazard::Reset()
{
	OnDeactivate(NULL);
	m_entity = NULL;
	m_amplitude0 = 0.0f;
	m_amplitude1 = 0.0f;
	m_phaseMs = 0.0f;
	return Hazard::Reset();
}
