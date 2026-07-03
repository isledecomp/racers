#include "race/events/materialanimationresource.h"

#include "decomp.h"
#include "mabmaterialanimation.h"
#include "mabmaterialtrack.h"

DECOMP_SIZE_ASSERT(MaterialAnimationResource::InitParams, 0x38)
DECOMP_SIZE_ASSERT(MaterialAnimationResource, 0x34)

// FUNCTION: LEGORACERS 0x0045c330 FOLDED
LegoU32 MaterialAnimationResource::GetKind()
{
	return 2;
}

// FUNCTION: LEGORACERS 0x004630a0
MaterialAnimationResource::MaterialAnimationResource()
{
	m_materialAnimation = NULL;
	m_activeTrack = NULL;
	m_idleTrack = NULL;
	m_materialTable = NULL;
	m_materialIndex = 0;
	m_flags0x1c = 0;
}

// FUNCTION: LEGORACERS 0x004630d0
MaterialAnimationResource::~MaterialAnimationResource()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00463120
void MaterialAnimationResource::Initialize(InitParams* p_params)
{
	if (m_state0x18) {
		Destroy();
	}

	m_eventId = p_params->m_eventId;
	LegoS32* eventId = p_params->m_stateEventIds;
	for (LegoU32 i = 0; i < sizeOfArray(m_stateEventIds); i++) {
		m_stateEventIds[i] = *eventId++;
	}

	m_eventTable = p_params->m_eventTable;
	m_materialAnimation = p_params->m_materialAnimation;
	if (p_params->m_unk0x28) {
		m_flags0x1c |= c_flags0x1cBit0;
	}
	if (p_params->m_unk0x2c) {
		m_flags0x1c |= c_flagNoEnd;
	}
	if (p_params->m_unk0x30) {
		m_flags0x1c |= c_flagTriggerOnEnd;
	}
	if (p_params->m_unk0x34) {
		m_flags0x1c |= c_flags0x1cBit3;
	}

	m_activeTrack = &m_materialAnimation->GetUnk0x0c()[p_params->m_activeTrackIndex];
	MabMaterialTrack* item = &m_materialAnimation->GetUnk0x0c()[p_params->m_idleTrackIndex];
	m_idleTrack = item;
	m_materialTable = item->GetUnk0x00();
	m_materialIndex = item->GetUnk0x04();
	if (p_params->m_unk0x18) {
		m_materialTable = p_params->m_unk0x18;
		m_materialIndex = p_params->m_unk0x1c;
	}

	m_state0x18 = c_stateIdle;
}

// FUNCTION: LEGORACERS 0x004631e0
void MaterialAnimationResource::Destroy()
{
	OnEnd();
	m_materialAnimation = NULL;
	Reset();
}

// FUNCTION: LEGORACERS 0x00463200
void MaterialAnimationResource::Update(LegoU32 p_elapsedMs)
{
	RaceEventResource::Update(p_elapsedMs);
	if (m_state0x18 == c_stateActive && !(m_flags0x1c & c_flags0x1cBit0) && !m_activeTrack->IsAssigned()) {
		OnEnd();
	}
}

// FUNCTION: LEGORACERS 0x00463230
void MaterialAnimationResource::OnStartAt(GolVec3*)
{
	m_idleTrack->FUN_00410470();
	m_activeTrack->FUN_10025da0(m_materialTable, m_materialIndex, m_flags0x1c & c_flags0x1cBit0);
	m_activeTrack->FUN_00410480();
	NotifyStateChange(m_state0x18, c_stateIdle);
	m_state0x18 = c_stateActive;
}

// FUNCTION: LEGORACERS 0x00463280
void MaterialAnimationResource::OnEnd()
{
	m_activeTrack->FUN_00410470();
	m_idleTrack->FUN_10025da0(m_materialTable, m_materialIndex, TRUE);
	m_idleTrack->FUN_00410480();
	NotifyStateChange(m_state0x18, c_stateActive);
	m_state0x18 = c_stateIdle;
}
