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
	m_unk0x24 = NULL;
	m_unk0x28 = NULL;
	m_unk0x2c = NULL;
	m_unk0x30 = 0;
	m_flags0x1c = 0;
}

// FUNCTION: LEGORACERS 0x004630d0
MaterialAnimationResource::~MaterialAnimationResource()
{
	FUN_004631e0();
}

// FUNCTION: LEGORACERS 0x00463120
void MaterialAnimationResource::FUN_00463120(InitParams* p_params)
{
	if (m_state0x18) {
		FUN_004631e0();
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
		m_flags0x1c |= c_flags0x1cBit1;
	}
	if (p_params->m_unk0x30) {
		m_flags0x1c |= c_flags0x1cBit2;
	}
	if (p_params->m_unk0x34) {
		m_flags0x1c |= c_flags0x1cBit3;
	}

	m_unk0x24 = &m_materialAnimation->GetUnk0x0c()[p_params->m_unk0x20];
	MabMaterialTrack* item = &m_materialAnimation->GetUnk0x0c()[p_params->m_unk0x24];
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
void MaterialAnimationResource::FUN_004631e0()
{
	OnEnd();
	m_materialAnimation = NULL;
	Reset();
}

// FUNCTION: LEGORACERS 0x00463200
void MaterialAnimationResource::Update(LegoU32 p_elapsedMs)
{
	RaceEventResource::Update(p_elapsedMs);
	if (m_state0x18 == c_state0x18Three && !(m_flags0x1c & c_flags0x1cBit0) && !m_unk0x24->IsAssigned()) {
		OnEnd();
	}
}

// FUNCTION: LEGORACERS 0x00463230
void MaterialAnimationResource::OnStartAt(GolVec3*)
{
	m_unk0x28->FUN_00410470();
	m_unk0x24->FUN_10025da0(m_unk0x2c, m_unk0x30, m_flags0x1c & c_flags0x1cBit0);
	m_unk0x24->FUN_00410480();
	NotifyStateChange(m_state0x18, c_state0x18One);
	m_state0x18 = c_state0x18Three;
}

// FUNCTION: LEGORACERS 0x00463280
void MaterialAnimationResource::OnEnd()
{
	m_unk0x24->FUN_00410470();
	m_unk0x28->FUN_10025da0(m_unk0x2c, m_unk0x30, TRUE);
	m_unk0x28->FUN_00410480();
	NotifyStateChange(m_state0x18, c_state0x18Three);
	m_state0x18 = c_state0x18One;
}
