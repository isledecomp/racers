#include "race/events/partanimationresource.h"

#include "decomp.h"
#include "golanimatedentity.h"

DECOMP_SIZE_ASSERT(PartAnimationResource::InitParams, 0x3c)
DECOMP_SIZE_ASSERT(PartAnimationResource, 0x34)

// FUNCTION: LEGORACERS 0x004632c0
PartAnimationResource::PartAnimationResource()
{
	m_animatedEntity = NULL;
	m_flags = 0;
}

// FUNCTION: LEGORACERS 0x004632e0
PartAnimationResource::~PartAnimationResource()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00463330
void PartAnimationResource::Initialize(InitParams* p_params)
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
	m_animatedEntity = p_params->m_animatedEntity;
	m_activePart = p_params->m_activePart;
	m_idlePart = p_params->m_idlePart;
	m_startPart = p_params->m_startPart;
	m_endPart = p_params->m_endPart;

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

	if (p_params->m_useSharedDatabase) {
		m_flags |= c_flagUseSharedDatabase;
	}

	m_animatedEntity->SetFlags(m_animatedEntity->GetFlags() | c_entityFlag0x200000);
	m_state = c_stateIdle;
}

// FUNCTION: LEGORACERS 0x004633e0
void PartAnimationResource::Destroy()
{
	m_animatedEntity = NULL;
	Reset();
}

// STUB: LEGORACERS 0x004633f0
void PartAnimationResource::Update(LegoU32 p_elapsedMs)
{
	RaceEventResource::Update(p_elapsedMs);

	GolAnimatedEntity* entity = m_animatedEntity;
	LegoU32 state = m_state;
	LegoS32 currentPart = entity->GetCurrentPartIndex();

	if (state == 2) {
		if (currentPart == m_startPart) {
			LegoU32 flags = entity->GetFlags();
			if (!(flags & c_entityFlags0x120000) || static_cast<LegoU32>(entity->GetQueuedPartIndex()) == 0xffff) {
				LegoU32 loop = m_flags & c_flagLooping;
				entity->SetQueuedPartIndex(static_cast<LegoU16>(m_activePart));
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
		if (currentPart == m_endPart) {
			LegoU32 flags = entity->GetFlags();
			if (!(flags & c_entityFlags0x120000) || static_cast<LegoU32>(entity->GetQueuedPartIndex()) == 0xffff) {
				entity->SetQueuedPartIndex(static_cast<LegoU16>(m_idlePart));
				flags = entity->GetFlags();
				flags &= ~c_entityFlags0x0e0000;
				flags |= GolAnimatedEntity::c_flagRestartQueuedPart | GolAnimatedEntity::c_flagLoopQueuedPart;
				entity->SetFlags(flags);
			}
		}
	}
	else if (state == 3) {
		if (!(m_flags & c_flagLooping) && currentPart == m_activePart) {
			LegoU32 flags = entity->GetFlags();
			if (!(flags & c_entityFlags0x120000) || static_cast<LegoU32>(entity->GetQueuedPartIndex()) == 0xffff) {
				LegoS32 queuedPart = m_endPart;
				if (queuedPart == -1) {
					entity->SetQueuedPartIndex(static_cast<LegoU16>(m_idlePart));
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

	if (currentPart == m_startPart) {
		if (m_state != 2) {
			NotifyStateChange(m_state, 0);
			m_state = 2;
		}
	}
	else if (currentPart == m_activePart) {
		if (m_state != 3) {
			NotifyStateChange(m_state, 1);
			m_state = 3;
		}
	}
	else if (currentPart == m_endPart) {
		if (m_state != 4) {
			NotifyStateChange(m_state, 2);
			m_state = 4;
		}
	}
	else if (currentPart == m_idlePart && m_state != c_stateIdle) {
		NotifyStateChange(m_state, 3);
		m_state = c_stateIdle;
	}
}

// FUNCTION: LEGORACERS 0x00463570
void PartAnimationResource::OnStartAt(GolVec3*)
{
	LegoS32 queuedPart = m_startPart;
	GolAnimatedEntity* entity = m_animatedEntity;
	if (queuedPart != -1) {
		entity->SetQueuedPartIndex(static_cast<LegoU16>(queuedPart));
		LegoU32 flags = entity->GetFlags();
		flags &= ~c_entityFlags0x4e0000;
		flags |= GolAnimatedEntity::c_flagRestartQueuedPart;
		entity->SetFlags(flags);
	}
	else {
		queuedPart = m_activePart;
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
	LegoU32 state = m_state;
	LegoU32 nextState = state;
	LegoU32 resetState = c_stateIdle;
	if (state != resetState) {
		nextState = resetState;
		GolAnimatedEntity* entity = m_animatedEntity;
		LegoS32 targetPart = m_idlePart;
		LegoS32 currentPart = entity->GetCurrentPartIndex();
		if (currentPart != targetPart) {
			LegoS32 queuedPart = m_endPart;
			if (queuedPart != -1) {
				if (currentPart != queuedPart) {
					queuedPart = m_endPart;
					if (queuedPart != -1) {
						entity->SetQueuedPartIndex(static_cast<LegoU16>(queuedPart));
						LegoU32 flags = entity->GetFlags();
						flags &= ~c_entityFlags0x4e0000;
						flags |= GolAnimatedEntity::c_flagRestartQueuedPart;
						entity->SetFlags(flags);
						SetState(nextState);
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

	SetState(nextState);
}

#pragma code_seg(".text$animatedpartresource_vt18")
// FUNCTION: LEGORACERS 0x00452430 FOLDED
LegoU32 PartAnimationResource::GetKind()
{
	return 1;
}
#pragma code_seg()
