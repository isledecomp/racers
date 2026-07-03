#include "race/events/skystateresource.h"

#include "decomp.h"
#include "race/racesky.h"

#include <string.h>

DECOMP_SIZE_ASSERT(SkyStateResource::InitParams, 0x2c)
DECOMP_SIZE_ASSERT(SkyStateResource, 0x34)

// FUNCTION: LEGORACERS 0x0045e150
SkyStateResource::SkyStateResource()
{
	ClearFields();
	m_flags = 0;
}

// FUNCTION: LEGORACERS 0x0045e1a0
SkyStateResource::~SkyStateResource()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0045e1f0
void SkyStateResource::ClearFields()
{
	m_skyState = NULL;
	m_skyName[0] = '\0';
	m_durationMs = 0;
	m_skyFlags = 0;
}

// FUNCTION: LEGORACERS 0x0045e200
void SkyStateResource::Initialize(InitParams* p_params)
{
	if (m_state) {
		Destroy();
	}

	m_eventId = p_params->m_eventId;
	LegoS32* eventId = p_params->m_stateEventIds;
	LegoU32 i;
	for (i = 0; i < sizeOfArray(m_stateEventIds); i++) {
		m_stateEventIds[i] = *eventId++;
	}

	m_eventTable = p_params->m_eventTable;
	m_skyState = p_params->m_skyState;
	m_durationMs = p_params->m_durationMs;
	m_skyFlags = p_params->m_skyFlags;
	::strncpy(m_skyName, p_params->m_skyName, sizeof(m_skyName));
	if (p_params->m_triggerOnEnd) {
		m_flags |= c_flagTriggerOnEnd;
	}

	m_state = c_stateIdle;
	m_flags &= ~c_flagBit5;
}

// FUNCTION: LEGORACERS 0x0045e280
void SkyStateResource::Destroy()
{
	OnEnd();
	ClearFields();
	Reset();
}

// FUNCTION: LEGORACERS 0x0045e2a0
void SkyStateResource::OnStartAt(GolVec3*)
{
	if (m_skyName[0]) {
		m_skyState->StartTransition(m_skyName, m_durationMs);
	}

	if (m_skyFlags & c_showDome) {
		m_skyState->m_hideFlags &= ~RaceSkyState::c_hideDome;
	}

	if (m_skyFlags & c_hideDome) {
		m_skyState->m_hideFlags |= RaceSkyState::c_hideDome;
	}

	if (m_skyFlags & c_showSkyWorld) {
		m_skyState->m_hideFlags &= ~RaceSkyState::c_hideSkyWorld;
	}

	if (m_skyFlags & c_hideSkyWorld) {
		m_skyState->m_hideFlags |= RaceSkyState::c_hideSkyWorld;
	}

	NotifyStateChange(m_state, 1);
	m_state = c_stateEndPending;
}

// FUNCTION: LEGORACERS 0x0045e320
void SkyStateResource::OnEnd()
{
	NotifyStateChange(m_state, 3);
	m_state = c_stateIdle;
	m_flags &= ~c_flagBit5;
}

// FUNCTION: LEGORACERS 0x0045e340
LegoU32 SkyStateResource::GetKind()
{
	return 5;
}
