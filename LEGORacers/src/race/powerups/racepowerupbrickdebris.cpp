#include "decomp.h"
#include "golmateriallibrary.h"
#include "race/powerups/powerupaction.h"
#include "race/powerups/racepowerupmanager.h"
#include "render/gold3drenderdevice.h"
#include "world/golworlddatabase.h"

DECOMP_SIZE_ASSERT(PowerupAction, 0x18)
DECOMP_SIZE_ASSERT(RacePowerupManager::BrickDebris, 0x80)
DECOMP_SIZE_ASSERT(RacePowerupManager::BrickDebris::Entry, 0x14)

extern LegoU16 g_randomTable[1024];
extern LegoU32 g_randomTableIndex;

// FUNCTION: LEGORACERS 0x00451350
PowerupAction::PowerupAction()
{
	m_state = 0;
	m_stateTimerMs = 0;
	m_next = NULL;
	m_soundSource = NULL;
	m_level = 0;
}

// FUNCTION: LEGORACERS 0x00451390
PowerupAction::~PowerupAction()
{
}

// FUNCTION: LEGORACERS 0x004513a0 FOLDED
void PowerupAction::Update(LegoU32 p_elapsedMs)
{
	if (p_elapsedMs >= m_stateTimerMs) {
		m_stateTimerMs = 0;
		AdvanceState();
	}
	else {
		m_stateTimerMs -= p_elapsedMs;
	}
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void PowerupAction::OnEvent(LegoEventQueue::CallbackData*)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void PowerupAction::Draw(GolD3DRenderDevice*)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void PowerupAction::DrawTransparent(GolD3DRenderDevice*)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void PowerupAction::AdvanceState()
{
}

// FUNCTION: LEGORACERS 0x004513e0 FOLDED
void PowerupAction::Deactivate()
{
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x004513f0
RacePowerupManager::BrickDebris::Entry::Entry()
{
	m_entity = 0;
	m_state = 0;
}

// FUNCTION: LEGORACERS 0x00451410
RacePowerupManager::BrickDebris::Entry::~Entry()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00451460
void RacePowerupManager::BrickDebris::Entry::Reset()
{
	m_materialTable.Clear();
	m_entity = 0;
	m_state = 0;
}

// FUNCTION: LEGORACERS 0x00451480
void RacePowerupManager::BrickDebris::Entry::Initialize(GolD3DRenderDevice* p_renderer)
{
	if (m_state) {
		Reset();
	}

	m_materialTable.Initialize(p_renderer, 1);
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x004514b0
void RacePowerupManager::BrickDebris::Entry::Spawn(
	GolAnimatedEntity* p_sourceEntity,
	GolAnimatedEntity* p_entity,
	const GolVec3* p_position,
	const GolVec3* p_direction,
	LegoU32 p_partIndex,
	void* p_billboardPosition
)
{
	m_entity = p_entity;
	m_entity->SetModel(
		p_sourceEntity->GetModel(0),
		p_sourceEntity->GetSceneNode(0),
		p_sourceEntity->GetModelPart(0),
		p_sourceEntity->GetModelDistance(0)
	);

	LegoU32 i;
	for (i = 1; i < 3; i++) {
		if (p_sourceEntity->GetModel(i)) {
			m_entity->AddModel(
				p_sourceEntity->GetModel(i),
				p_sourceEntity->GetSceneNode(i),
				p_sourceEntity->GetModelPart(i),
				p_sourceEntity->GetModelDistance(i)
			);
		}
	}

	p_partIndex %= p_sourceEntity->GetModelPart(0)->GetPartCount();
	m_entity->PlayPart(p_partIndex);

	LegoU32 flags = m_entity->GetFlags();
	flags |= GolAnimatedEntity::c_flagPartAnimation;
	m_entity->SetFlags(flags);

	flags = m_entity->GetFlags();
	flags &= ~GolAnimatedEntity::c_flagLoopCurrentPart;
	m_entity->SetFlags(flags);

	if (p_billboardPosition) {
		m_materialTable.SetEntry(0, p_billboardPosition);
		m_entity->SetPrimaryMaterialTable(&m_materialTable);
	}

	GolVec3 up;
	up.m_x = 0.0f;
	up.m_y = 0.0f;
	up.m_z = 1.0f;
	m_entity->SetPosition(*p_position);
	m_entity->SetDirectionUp(*p_direction, up);
	m_state = c_statePlaying;
}

// FUNCTION: LEGORACERS 0x004515d0
void RacePowerupManager::BrickDebris::Entry::Update(LegoU32 p_elapsedMs)
{
	if (m_state == c_statePlaying) {
		m_entity->Update(p_elapsedMs);
		if (m_entity->IsPartAnimationDone()) {
			m_entity->ResetModelState();
			m_state = c_stateFinished;
		}
	}
}

// FUNCTION: LEGORACERS 0x00451610
void RacePowerupManager::BrickDebris::Entry::Draw(GolD3DRenderDevice* p_renderer)
{
	if (m_state == c_statePlaying) {
		p_renderer->DrawModelEntity(m_entity);
	}
}

// FUNCTION: LEGORACERS 0x00451630
void RacePowerupManager::BrickDebris::Entry::Release()
{
	m_entity = NULL;
	m_state = c_stateFree;
}

// FUNCTION: LEGORACERS 0x00451640
RacePowerupManager::BrickDebris::BrickDebris()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004516a0
RacePowerupManager::BrickDebris::~BrickDebris()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00451700
LegoS32 RacePowerupManager::BrickDebris::Destroy()
{
	LegoS32 i;

	for (i = 0; i < sizeOfArray(m_entries); i++) {
		m_entries[i].Reset();
	}

	return Reset();
}

// FUNCTION: LEGORACERS 0x00451730
LegoS32 RacePowerupManager::BrickDebris::Reset()
{
	m_brickModels[0] = NULL;
	m_brickModels[1] = NULL;
	m_brickModels[2] = NULL;
	m_brickModels[3] = NULL;
	m_manager = 0;
	m_nextModelIndex = 0;
	m_nextPartIndex = 0;

	return 0;
}

// FUNCTION: LEGORACERS 0x00451750
void RacePowerupManager::BrickDebris::Initialize(RacePowerupManager* p_manager, GolD3DRenderDevice* p_renderer)
{
	if (m_manager) {
		Destroy();
	}

	m_manager = p_manager;

	const LegoChar* name = "brick1\0\0brick2\0\0brick3\0\0brick4\0";
	const LegoChar* endName = name + (sizeof(GolName) * 4);
	GolAnimatedEntity** entity = m_brickModels;
	GolWorldDatabase* worldDatabase = p_manager->m_worldDatabase;

	while (name < endName) {
		GolAnimatedEntity* model;
		if (worldDatabase->GetAnimatedEntityEntries() == NULL) {
			model = NULL;
		}
		else {
			model = worldDatabase->GetAnimatedEntityByName(name);
		}
		*entity = model;

		name += sizeof(GolName);
		entity++;
	}

	Entry* entry = m_entries;
	LegoS32 i;
	for (i = 5; i != 0; i--) {
		entry->Initialize(p_renderer);
		entry++;
	}
}

// FUNCTION: LEGORACERS 0x004517c0
void RacePowerupManager::BrickDebris::Spawn(const GolVec3* p_position, const GolVec3* p_direction, Racer* p_racer)
{
	GolMaterial* material;
	material = NULL;
	LegoS32 entryIndex;

	entryIndex = 0;
	while (TRUE) {
		if (m_entries[entryIndex].m_state != Entry::c_statePlaying) {
			break;
		}

		entryIndex++;
		if (entryIndex >= sizeOfArray(m_entries)) {
			break;
		}
	}

	if (entryIndex != sizeOfArray(m_entries)) {
		GolAnimatedEntity* entity = m_manager->AllocateEffectEntity();
		if (entity) {
			LegoU32 sourceIndex = m_nextModelIndex;
			m_nextModelIndex = sourceIndex + 1;
			if (m_nextModelIndex == 4) {
				m_nextModelIndex = 0;
			}

			if (p_racer) {
				material = m_manager->m_raceState->GetMaterialLibrary()->GetItem(p_racer->m_materialIndex);
			}

			m_entries[entryIndex]
				.Spawn(m_brickModels[sourceIndex], entity, p_position, p_direction, m_nextPartIndex, material);
			m_nextPartIndex++;
		}
	}
}

// FUNCTION: LEGORACERS 0x00451860
void RacePowerupManager::BrickDebris::Update(LegoU32 p_elapsedMs)
{
	Entry* entry = m_entries;
	LegoS32 i;

	for (i = 5; i != 0; i--) {
		entry->Update(p_elapsedMs);
		if (entry->GetState() == 3) {
			m_manager->ReleaseEffectEntity(entry->GetEntity());
			entry->Release();
		}

		entry++;
	}
}

// FUNCTION: LEGORACERS 0x004518a0
void RacePowerupManager::BrickDebris::Draw(GolD3DRenderDevice* p_renderer)
{
	Entry* entry = m_entries;
	LegoS32 i;

	for (i = 5; i != 0; i--) {
		entry->Draw(p_renderer);
		entry++;
	}
}

// FUNCTION: LEGORACERS 0x004518d0
void RacePowerupManager::BrickDebris::ReleaseAll()
{
	Entry* entry = m_entries;
	LegoS32 i;

	for (i = 5; i != 0; i--) {
		entry->Release();
		entry++;
	}
}
