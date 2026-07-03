#include "race/hazards/fallingpillarhazard.h"

#include "decomp.h"
#include "golanimatedentity.h"
#include "golfileparser.h"
#include "golmath.h"
#include "golnametable.h"
#include "race/hazards/hazardcontext.h"
#include "race/raceeventtable.h"
#include "types.h"
#include "world/golworlddatabase.h"

DECOMP_SIZE_ASSERT(FallingPillarHazard, 0x20)

// FUNCTION: LEGORACERS 0x0048b890
FallingPillarHazard::FallingPillarHazard()
{
	m_entity = NULL;
	m_particleAnimation = 0;
	m_collider = NULL;
	m_fallen = 0;
}

// FUNCTION: LEGORACERS 0x0048b8d0
FallingPillarHazard::~FallingPillarHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048b920
void FallingPillarHazard::Load(HazardContext* p_context, GolFileParser*)
{
	if (m_state) {
		Reset();
	}

	m_triggerId = 0x0a;
	m_eventTable = p_context->GetEventTable();
	m_particleAnimation = p_context->GetParticleAnimation();
	m_entity = p_context->GetTrackDatabase()->FindAnimatedEntity("piltop");

	GolNameTable* nameTable = p_context->GetColliderTable();
	m_collider =
		nameTable->GetNameEntries() == NULL ? NULL : static_cast<ColliderRecord*>(nameTable->GetName("pilcol"));

	m_entity->SetFlags(m_entity->GetFlags() & ~GolAnimatedEntity::c_flagPartAnimation);
	m_state = c_stateLoaded;
}

// FUNCTION: LEGORACERS 0x0048b9b0 FOLDED
LegoS32 FallingPillarHazard::Reset()
{
	OnDeactivate(NULL);
	m_entity = NULL;
	m_particleAnimation = 0;
	m_collider = NULL;
	m_fallen = 0;
	return Hazard::Reset();
}

// FUNCTION: LEGORACERS 0x0048b9e0
void FallingPillarHazard::OnActivate(void*)
{
	m_entity->SetFlags(m_entity->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_entity->PlayPart(0);
	m_entity->SetFlags(m_entity->GetFlags() & ~GolAnimatedEntity::c_flagLoopCurrentPart);
	m_fallen = 0;
	m_state = c_stateActive;
}

void FallingPillarHazard::OnDeactivate(void*)
{
}

// FUNCTION: LEGORACERS 0x0048ba20
void FallingPillarHazard::Update(undefined4 p_elapsedMs)
{
	if (m_state != c_stateLoaded) {
		Hazard::Update(p_elapsedMs);

		if (m_fallen == 0 && m_entity->GetPartTimeMs() > 50.0f) {
			m_collider->m_flags &= ~ColliderRecord::c_flagBit16;
			m_collider->m_flags &= ~ColliderRecord::c_flagBit17;
			m_eventTable->FireEventsAt(7, 7, NULL);
			m_fallen = 1;
		}
	}
}

// FUNCTION: LEGORACERS 0x0048ba90
void FallingPillarHazard::ResetState()
{
	m_state = c_stateLoaded;
	m_fallen = 0;
	m_collider->m_flags |= ColliderRecord::c_flagBit16;
	m_collider->m_flags |= ColliderRecord::c_flagBit17;
	m_entity->SetFlags(m_entity->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_entity->PlayPartScaled(0, 0);
	m_entity->ApplyPartAnimation(0);
	m_entity->SetFlags(m_entity->GetFlags() & ~GolAnimatedEntity::c_flagPartAnimation);
}
