#include "race/events/partanimationresource.h"

#include "decomp.h"
#include "golanimatedentity.h"

DECOMP_SIZE_ASSERT(PartAnimationResource::InitParams, 0x3c)
DECOMP_SIZE_ASSERT(PartAnimationResource, 0x34)

// FUNCTION: LEGORACERS 0x004632c0
PartAnimationResource::PartAnimationResource()
{
	m_animatedEntity = NULL;
	m_flags0x1c = 0;
}

// FUNCTION: LEGORACERS 0x004632e0
PartAnimationResource::~PartAnimationResource()
{
	FUN_004633e0();
}

// FUNCTION: LEGORACERS 0x00463330
void PartAnimationResource::FUN_00463330(InitParams* p_params)
{
	if (m_state0x18) {
		FUN_004633e0();
	}

	m_eventId = p_params->m_eventId;
	LegoS32* eventId = p_params->m_stateEventIds;
	for (LegoU32 i = 0; i < sizeOfArray(m_stateEventIds); i++) {
		m_stateEventIds[i] = *eventId++;
	}

	m_eventTable = p_params->m_eventTable;
	m_animatedEntity = p_params->m_animatedEntity;
	m_unk0x24 = p_params->m_unk0x18;
	m_unk0x28 = p_params->m_unk0x1c;
	m_unk0x2c = p_params->m_unk0x20;
	m_unk0x30 = p_params->m_unk0x24;

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

	if (p_params->m_unk0x38) {
		m_flags0x1c |= c_flags0x1cBit4;
	}

	m_animatedEntity->SetFlags(m_animatedEntity->GetFlags() | c_entityFlag0x200000);
	m_state0x18 = c_state0x18One;
}

// FUNCTION: LEGORACERS 0x004633e0
void PartAnimationResource::FUN_004633e0()
{
	m_animatedEntity = NULL;
	Reset();
}

// STUB: LEGORACERS 0x004633f0
void PartAnimationResource::Update(LegoU32 p_elapsedMs)
{
	RaceEventResource::Update(p_elapsedMs);

	GolAnimatedEntity* entity = m_animatedEntity;
	LegoU32 state = m_state0x18;
	LegoS32 currentPart = entity->GetCurrentPartIndex();

	if (state == 2) {
		if (currentPart == m_unk0x2c) {
			LegoU32 flags = entity->GetFlags();
			if (!(flags & c_entityFlags0x120000) || static_cast<LegoU32>(entity->GetQueuedPartIndex()) == 0xffff) {
				LegoU32 loop = m_flags0x1c & c_flags0x1cBit0;
				entity->SetQueuedPartIndex(static_cast<LegoU16>(m_unk0x24));
				flags = entity->GetFlags();
				flags &= ~c_entityFlags0x4e0000;
				flags |= GolAnimatedEntity::c_flagRestartQueuedPart;
				if (loop) {
					flags |= GolAnimatedEntity::c_flagLoopQueuedPart;
				}
				entity->SetFlags(flags);
			}
		}
	}
	else if (state == 4) {
		if (currentPart == m_unk0x30) {
			LegoU32 flags = entity->GetFlags();
			if (!(flags & c_entityFlags0x120000) || static_cast<LegoU32>(entity->GetQueuedPartIndex()) == 0xffff) {
				entity->SetQueuedPartIndex(static_cast<LegoU16>(m_unk0x28));
				flags = entity->GetFlags();
				flags &= ~c_entityFlags0x0e0000;
				flags |= GolAnimatedEntity::c_flagRestartQueuedPart | GolAnimatedEntity::c_flagLoopQueuedPart;
				entity->SetFlags(flags);
			}
		}
	}
	else if (state == 3) {
		if (!(m_flags0x1c & c_flags0x1cBit0) && currentPart == m_unk0x24) {
			LegoU32 flags = entity->GetFlags();
			if (!(flags & c_entityFlags0x120000) || static_cast<LegoU32>(entity->GetQueuedPartIndex()) == 0xffff) {
				LegoS32 queuedPart = m_unk0x30;
				if (queuedPart == -1) {
					entity->SetQueuedPartIndex(static_cast<LegoU16>(m_unk0x28));
					flags = entity->GetFlags();
					flags &= ~c_entityFlags0x0e0000;
					flags |= GolAnimatedEntity::c_flagRestartQueuedPart | GolAnimatedEntity::c_flagLoopQueuedPart;
					entity->SetFlags(flags);
				}
				else {
					entity->SetQueuedPartIndex(static_cast<LegoU16>(queuedPart));
					flags = entity->GetFlags();
					flags &= ~c_entityFlags0x4e0000;
					flags |= GolAnimatedEntity::c_flagRestartQueuedPart;
					entity->SetFlags(flags);
				}
			}
		}
	}

	if (currentPart == m_unk0x2c) {
		if (m_state0x18 != 2) {
			NotifyStateChange(m_state0x18, 0);
			m_state0x18 = 2;
		}
	}
	else if (currentPart == m_unk0x24) {
		if (m_state0x18 != 3) {
			NotifyStateChange(m_state0x18, 1);
			m_state0x18 = 3;
		}
	}
	else if (currentPart == m_unk0x30) {
		if (m_state0x18 != 4) {
			NotifyStateChange(m_state0x18, 2);
			m_state0x18 = 4;
		}
	}
	else if (currentPart == m_unk0x28 && m_state0x18 != c_state0x18One) {
		NotifyStateChange(m_state0x18, 3);
		m_state0x18 = c_state0x18One;
	}
}

// FUNCTION: LEGORACERS 0x00463570
void PartAnimationResource::OnStartAt(GolVec3*)
{
	LegoS32 queuedPart = m_unk0x2c;
	GolAnimatedEntity* entity = m_animatedEntity;
	if (queuedPart != -1) {
		entity->SetQueuedPartIndex(static_cast<LegoU16>(queuedPart));
		LegoU32 flags = entity->GetFlags();
		flags &= ~c_entityFlags0x4e0000;
		flags |= GolAnimatedEntity::c_flagRestartQueuedPart;
		entity->SetFlags(flags);
	}
	else {
		queuedPart = m_unk0x24;
		entity->SetQueuedPartIndex(static_cast<LegoU16>(queuedPart));
		LegoU32 flags = entity->GetFlags();
		flags &= ~c_entityFlags0x0e0000;
		flags |= GolAnimatedEntity::c_flagRestartQueuedPart | GolAnimatedEntity::c_flagLoopQueuedPart;
		entity->SetFlags(flags);
	}
}

// FUNCTION: LEGORACERS 0x004635c0
void PartAnimationResource::OnEnd()
{
	LegoU32 state = m_state0x18;
	LegoU32 nextState = state;
	LegoU32 resetState = c_state0x18One;
	if (state != resetState) {
		nextState = resetState;
		GolAnimatedEntity* entity = m_animatedEntity;
		LegoS32 targetPart = m_unk0x28;
		LegoS32 currentPart = entity->GetCurrentPartIndex();
		if (currentPart != targetPart) {
			LegoS32 queuedPart = m_unk0x30;
			if (queuedPart != -1) {
				if (currentPart != queuedPart) {
					queuedPart = m_unk0x30;
					if (queuedPart != -1) {
						entity->SetQueuedPartIndex(static_cast<LegoU16>(queuedPart));
						LegoU32 flags = entity->GetFlags();
						flags &= ~c_entityFlags0x4e0000;
						flags |= GolAnimatedEntity::c_flagRestartQueuedPart;
						entity->SetFlags(flags);
						SetState0x18(nextState);
						return;
					}
				}
			}
			else {
				entity->SetQueuedPartIndex(static_cast<LegoU16>(targetPart));
				LegoU32 flags = entity->GetFlags();
				flags &= ~c_entityFlags0x0e0000;
				flags |= GolAnimatedEntity::c_flagRestartQueuedPart | GolAnimatedEntity::c_flagLoopQueuedPart;
				entity->SetFlags(flags);
			}
		}
	}

	SetState0x18(nextState);
}

#pragma code_seg(".text$animatedpartresource_vt18")
// FUNCTION: LEGORACERS 0x00452430 FOLDED
LegoU32 PartAnimationResource::GetKind()
{
	return 1;
}
#pragma code_seg()
