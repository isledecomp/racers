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
	m_flags = 0;
}

// FUNCTION: LEGORACERS 0x004630d0
MaterialAnimationResource::~MaterialAnimationResource()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00463120
void MaterialAnimationResource::Initialize(InitParams* p_params)
{
	if (m_state) {
		Destroy();
	}

	m_eventId = p_params->m_eventId;
	LegoS32* eventId = p_params->m_stateEventIds;
	for (LegoU32 i = 0; i < sizeOfArray(m_stateEventIds); i++) {
		m_stateEventIds[i] = *eventId++;
	}

	m_eventTable = p_params->m_eventTable;
	m_materialAnimation = p_params->m_materialAnimation;
	if (p_params->m_looping) {
		m_flags |= c_flagLooping;
	}
	if (p_params->m_noEnd) {
		m_flags |= c_flagNoEnd;
	}
	if (p_params->m_triggerOnEnd) {
		m_flags |= c_flagTriggerOnEnd;
	}
	if (p_params->m_atEventPosition) {
		m_flags |= c_flagAtEventPosition;
	}

	m_activeTrack = &m_materialAnimation->GetTracks()[p_params->m_activeTrackIndex];
	MabMaterialTrack* item = &m_materialAnimation->GetTracks()[p_params->m_idleTrackIndex];
	m_idleTrack = item;
	m_materialTable = item->GetMaterialTable();
	m_materialIndex = item->GetMaterialIndex();
	if (p_params->m_materialTable) {
		m_materialTable = p_params->m_materialTable;
		m_materialIndex = p_params->m_materialIndex;
	}

	m_state = c_stateIdle;
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
	if (m_state == c_stateActive && !(m_flags & c_flagLooping) && !m_activeTrack->IsAssigned()) {
		OnEnd();
	}
}

// FUNCTION: LEGORACERS 0x00463230
void MaterialAnimationResource::OnStartAt(GolVec3*)
{
	m_idleTrack->Unassign();
	m_activeTrack->Assign(m_materialTable, m_materialIndex, m_flags & c_flagLooping);
	m_activeTrack->Rewind();
	NotifyStateChange(m_state, c_stateIdle);
	m_state = c_stateActive;
}

// FUNCTION: LEGORACERS 0x00463280
void MaterialAnimationResource::OnEnd()
{
	m_activeTrack->Unassign();
	m_idleTrack->Assign(m_materialTable, m_materialIndex, TRUE);
	m_idleTrack->Rewind();
	NotifyStateChange(m_state, c_stateActive);
	m_state = c_stateIdle;
}
