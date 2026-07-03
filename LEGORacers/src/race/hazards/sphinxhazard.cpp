#include "race/hazards/sphinxhazard.h"

#include "decomp.h"
#include "golanimatedentity.h"
#include "golfileparser.h"
#include "golmath.h"
#include "golnametable.h"
#include "mabmaterialanimation0x14.h"
#include "mabmaterialanimationitem0x18.h"
#include "race/hazards/hazardcontext.h"
#include "race/raceeventtable.h"
#include "types.h"
#include "world/golworlddatabase.h"

#include <string.h>

DECOMP_SIZE_ASSERT(SphinxHazard, 0x24)

// GLOBAL: LEGORACERS 0x004b4338
extern const LegoFloat g_sphinxInactiveModelDistance = -1.0f;

// FUNCTION: LEGORACERS 0x0048c020
SphinxHazard::SphinxHazard()
{
	m_particleAnimation = 0;
	m_sharedDatabase = NULL;
	m_blowupItem = NULL;
	m_entity = NULL;
	m_collider = NULL;
}

// FUNCTION: LEGORACERS 0x0048c070
SphinxHazard::~SphinxHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048c0c0
void SphinxHazard::Load(HazardContext* p_context, GolFileParser*)
{
	if (m_state) {
		Reset();
	}

	m_triggerId = 0x0c;
	m_eventTable = p_context->GetEventTable();
	m_particleAnimation = p_context->GetParticleAnimation();
	m_sharedDatabase = p_context->GetSharedDatabase();

	GolNameTable* nameTable = p_context->GetColliderTable();
	m_collider =
		nameTable->GetNameEntries() == NULL ? NULL : static_cast<ColliderRecord*>(nameTable->GetName("sphinx"));
	m_entity = m_sharedDatabase->FindAnimatedEntity("blowup");
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0048c150
LegoS32 SphinxHazard::Reset()
{
	OnDeactivate(NULL);
	m_particleAnimation = 0;
	m_sharedDatabase = NULL;
	m_blowupItem = NULL;
	m_entity = NULL;
	m_collider = NULL;
	return Hazard::Reset();
}

// FUNCTION: LEGORACERS 0x0048c180
void SphinxHazard::OnActivate(void*)
{
	MabMaterialAnimation0x14* animation = NULL;
	if (m_entity->GetModelDistance(0) == g_sphinxInactiveModelDistance) {
		return;
	}

	int(__cdecl * compare)(const LegoChar*, const LegoChar*, size_t) = ::strncmp;
	LegoU32 i = 0;
	while (i < m_sharedDatabase->GetUnk0x74()) {
		GolName name;
		::strncpy(name, m_sharedDatabase->GetUnk0x78()[i], sizeof(name));
		if (compare(name, "blowup", sizeof(name)) == 0) {
			animation = m_sharedDatabase->VTable0x4c(i);
		}
		i++;
		if (animation != NULL) {
			break;
		}
	}

	if (animation != NULL) {
		MabMaterialAnimationItem0x18* items = animation->GetUnk0x0c();
		MabMaterialAnimationItem0x18* item1 = &items[1];
		MabMaterialAnimationItem0x18* item2 = &items[2];
		MabMaterialAnimationItem0x18* item3 = &items[3];
		items[0].FUN_00410470();
		item1->FUN_00410470();
		item2->FUN_10025da0(items[0].GetUnk0x00(), items[0].GetUnk0x04(), FALSE);
		item2->FUN_00410480();
		item3->FUN_10025da0(item1->GetUnk0x00(), item1->GetUnk0x04(), FALSE);
		item3->FUN_00410480();
		m_blowupItem = item2;

		GolVec3 position;
		m_entity->VTable0x04(&position);
		m_eventTable->StartEventsAt(0x10, &position);
	}

	m_collider->m_flags |= ColliderRecord::c_flagBit16;
	m_collider->m_flags |= ColliderRecord::c_flagBit17;
	m_state = 2;
}

// FUNCTION: LEGORACERS 0x0048c2a0
void SphinxHazard::OnDeactivate(void*)
{
	if (m_blowupItem != NULL && m_blowupItem->IsAssigned()) {
		return;
	}

	for (LegoS32 i = 0; i < c_modelDistanceCount; i++) {
		m_entity->SetModelDistance(i, g_sphinxInactiveModelDistance);
	}

	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0048c2e0
void SphinxHazard::Update(undefined4 p_elapsedMs)
{
	if (m_state == 1) {
		return;
	}

	Hazard::Update(p_elapsedMs);
	if (m_blowupItem != NULL) {
		if (m_blowupItem->IsAssigned()) {
			return;
		}

		GolVec3 position;
		m_entity->VTable0x04(&position);
		m_eventTable->EndEventsAt(0x10, &position);
		OnDeactivate(NULL);
		return;
	}
	OnDeactivate(NULL);
}

// FUNCTION: LEGORACERS 0x0048c340
void SphinxHazard::ResetState()
{
	MabMaterialAnimation0x14* animation = NULL;
	if (m_state == 1 && m_entity->GetModelDistance(0) != g_sphinxInactiveModelDistance) {
		return;
	}

	int(__cdecl * compare)(const LegoChar*, const LegoChar*, size_t) = ::strncmp;
	m_collider->m_flags &= ~ColliderRecord::c_flagBit16;
	m_collider->m_flags &= ~ColliderRecord::c_flagBit17;
	m_entity->SetModelDistance(0, 640000.0f);

	LegoU32 i = 0;
	while (TRUE) {
		if (i >= m_sharedDatabase->GetUnk0x74()) {
			break;
		}

		GolName name;
		::strncpy(name, m_sharedDatabase->GetUnk0x78()[i], sizeof(name));
		if (compare(name, "blowup", sizeof(name)) == 0) {
			animation = m_sharedDatabase->VTable0x4c(i);
		}
		i++;
		if (animation != NULL) {
			break;
		}
	}

	if (animation != NULL) {
		MabMaterialAnimationItem0x18* items = animation->GetUnk0x0c();
		MabMaterialAnimationItem0x18* item2 = &items[2];
		MabMaterialAnimationItem0x18* item1 = &items[1];
		MabMaterialAnimationItem0x18* item3 = &items[3];
		item2->FUN_00410470();
		item3->FUN_00410470();
		items[0].FUN_10025da0(items[0].GetUnk0x00(), items[0].GetUnk0x04(), TRUE);
		items[0].FUN_00410480();
		item1->FUN_10025da0(item1->GetUnk0x00(), item1->GetUnk0x04(), TRUE);
		item1->FUN_00410480();
	}

	m_state = 1;
}
