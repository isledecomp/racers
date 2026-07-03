#include "app/cheatflags.h"
#include "audio/spatialsoundinstance.h"
#include "audio/streamingsoundinstance.h"
#include "cmbmodelpart.h"
#include "decomp.h"
#include "golbinparser.h"
#include "golmateriallibrary.h"
#include "golworldentity.h"
#include "race/racesession.h"
#include "render/gold3drenderdevice.h"
#include "world/golworlddatabase.h"

#include <float.h>
#include <golerror.h>

DECOMP_SIZE_ASSERT(RacePowerupManager, 0x19a4)
DECOMP_SIZE_ASSERT(PickupBrick, 0x54)
DECOMP_SIZE_ASSERT(ColorBrick, 0x68)
DECOMP_SIZE_ASSERT(WhiteBrick, 0x68)
DECOMP_SIZE_ASSERT(RacePowerupManager::PwbTxtParser, 0x1fc)
DECOMP_SIZE_ASSERT(RacePowerupManager::BrickDebris, 0x80)
DECOMP_SIZE_ASSERT(RacePowerupManager::BrickDebris::Entry, 0x14)
DECOMP_SIZE_ASSERT(TargetPointList::Entry, 0x14)
DECOMP_SIZE_ASSERT(MagnetAction, 0x84)
DECOMP_SIZE_ASSERT(OilSlickAction, 0x190)
DECOMP_SIZE_ASSERT(DynamiteAction, 0x17c)
DECOMP_SIZE_ASSERT(CurseAction, 0x68)
DECOMP_SIZE_ASSERT(PowerupAction, 0x18)
DECOMP_SIZE_ASSERT(HazardActionBase, 0x2c)
DECOMP_SIZE_ASSERT(WeaponActionBase, 0x30)
DECOMP_SIZE_ASSERT(CannonballAction, 0xe8)
DECOMP_SIZE_ASSERT(GrapplingHookAction, 0x290)
DECOMP_SIZE_ASSERT(LightningAction, 0x24c)
DECOMP_SIZE_ASSERT(HomingMissileAction, 0x224)
DECOMP_SIZE_ASSERT(ShieldAction, 0x2c)
DECOMP_SIZE_ASSERT(TurboAction, 0x34)
DECOMP_SIZE_ASSERT(WarpAction, 0xe4)

extern LegoU16 g_randomTable[1024];
extern LegoU32 g_randomTableIndex;
extern const LegoFloat g_unk0x004b02e0;
extern const LegoFloat g_aimMinDistanceSquared;
extern const LegoFloat g_aimMaxDistanceSquared;
extern const LegoFloat g_aimRacerConeCosine;
extern const LegoFloat g_aimPointConeCosine;
extern const LegoFloat g_dynamiteAimMinDistanceSquared;
extern const LegoFloat g_dynamiteAimMaxDistanceSquared;
extern const LegoFloat g_dynamiteAimConeCosine;
extern const LegoFloat g_hookAimMinDistanceSquared;
extern const LegoFloat g_hookAimFarMaxDistanceSquared;
extern const LegoFloat g_hookAimMaxDistanceSquared;
extern const LegoFloat g_hookAimFarConeCosine;
extern const LegoFloat g_hookAimWideConeCosine;

// GLOBAL: LEGORACERS 0x004b183c
extern const LegoFloat g_flightSoundMinDistance = 200.0f;

// GLOBAL: LEGORACERS 0x004b1870
extern const LegoFloat g_flightSoundMaxDistanceSquared = 500.0f;

// GLOBAL: LEGORACERS 0x004b1874
extern const LegoFloat g_brickSpinRate = 0.0040000002f;

// GLOBAL: LEGORACERS 0x004b1878
extern const LegoFloat g_brickSpinWrap = 6.2831855f;

// GLOBAL: LEGORACERS 0x004c7644
LegoFloat g_projectileSoundRangeSquared = g_flightSoundMaxDistanceSquared * g_flightSoundMaxDistanceSquared;

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

// FUNCTION: LEGORACERS 0x0044e7e0 FOLDED
LegoS32 PowerupAction::GetBrickColor()
{
	return 0;
}

void WeaponActionBase::AdvanceState()
{
}

// FUNCTION: LEGORACERS 0x0044f580 FOLDED
LegoS32 TurboAction::GetBrickColor()
{
	return RacePowerupManager::c_brickColorGreen;
}

// FUNCTION: LEGORACERS 0x0044f580 FOLDED
LegoS32 WarpAction::GetBrickColor()
{
	return RacePowerupManager::c_brickColorGreen;
}

// FUNCTION: LEGORACERS 0x004513e0 FOLDED
void PowerupAction::Deactivate()
{
	m_state = 1;
}

void WeaponActionBase::OnHitRacer(Racer*)
{
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

// FUNCTION: LEGORACERS 0x00457990
RacePowerupManager::RacePowerupManager()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00457a20
RacePowerupManager::~RacePowerupManager()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00457a90
void RacePowerupManager::Reset()
{
	m_golExport = 0;
	m_renderer = NULL;
	m_colorBricks = NULL;
	m_brickEvents = NULL;
	m_colorBrickCount = 0;
	m_whiteBricks = NULL;
	m_whiteBrickCount = 0;
	m_raceState = NULL;
	m_collisionWorld = 0;
	m_collidable = 0;
	m_soundSource = 0;
	m_cutsceneAnimation = NULL;
	m_cannonballFlightSound = 0;
	m_missileFlightSound = 0;
	m_grappleFlightSound = 0;
	m_grappleAttachedSound = 0;
	m_freeMagnetActions = 0;
	m_freeOilSlickActions = 0;
	m_freeDynamiteActions = 0;
	m_freeCurseActions = 0;
	m_freeCannonballActions = 0;
	m_freeGrapplingHookActions = 0;
	m_freeLightningActions = 0;
	m_freeHomingMissileActions = 0;
	m_freeShieldActions = 0;
	m_freeTurboActions = 0;
	m_freeWarpActions = 0;
	m_brickSpinAngle = 0;
	m_exclusiveDraw = 0;
	m_turbo3Database = 0;
	m_boundedEntity = 0;
	m_racerTriggers = 0;
	m_trackDatabase = 0;
	m_actionPoolCounts[0] = 0;
	m_actionPoolCounts[1] = 0;
	m_actionPoolCounts[2] = 0;
	m_actionPoolCounts[3] = 0;
	m_actionPoolCounts[4] = 0;
	m_actionPoolCounts[5] = 0;
	m_actionPoolCounts[6] = 0;
	m_actionPoolCounts[7] = 0;
	m_actionPoolCounts[8] = 0;
	m_actionPoolCounts[9] = 0;
	m_actionPoolCounts[10] = 0;
	m_explosionPoolCount = 0;
	m_spikeExplosionPoolCount = 0;
	m_activeExplosions = NULL;
	m_activeSpikeExplosions = NULL;
	m_freeExplosions = 0;
	m_freeSpikeExplosions = 0;
	m_aimTarget = 0;
	m_explosionPool = NULL;
	m_spikeExplosionPool = NULL;
	m_magnetActions = 0;
	m_oilSlickActions = 0;
	m_dynamiteActions = 0;
	m_curseActions = 0;
	m_cannonballActions = 0;
	m_grapplingHookActions = 0;
	m_lightningActions = 0;
	m_homingMissileActions = 0;
	m_shieldActions = 0;
	m_turboActions = 0;
	m_warpActions = 0;
	m_animationList = 0;
	m_targetPoints = 0;
	m_effectEntityUsedMask = 0;
	m_usedEffectEntityCount = 0;
	m_cameraFov = 0;
	m_brickModel = 0;
	m_brickBlendModel = 0;
	m_whiteBrickModel = 0;
	m_whiteBrickBlendModel = 0;

	GolMaterial** entry = m_brickMaterials;
	LegoS32 count;
	for (count = c_brickMaterialCount; count != 0; count--) {
		*entry = NULL;
		entry++;
	}
}

// FUNCTION: LEGORACERS 0x00457c20
void RacePowerupManager::Initialize(const Params* p_params)
{
	if (m_golExport) {
		Destroy();
	}

	m_golExport = p_params->m_golExport;
	m_renderer = p_params->m_renderer;
	m_raceState = p_params->m_raceState;
	m_collidable = p_params->m_collidable;
	m_boundedEntity = p_params->m_boundedEntity;
	m_collisionWorld = p_params->m_collisionWorld;
	m_soundSource = p_params->m_soundSource;
	m_cutsceneAnimation = p_params->m_cutsceneAnimation;
	m_trailManager = p_params->m_trailManager;
	m_trackDatabase = p_params->m_trackDatabase;
	m_racerTriggers = p_params->m_racerTriggers;
	m_animationList = p_params->m_animationList;
	m_targetPoints = p_params->m_targetPoints;
	m_cameraFov = p_params->m_cameraFov;
	m_cheatFlags = p_params->m_cheatFlags;
}

// FUNCTION: LEGORACERS 0x00457c90
void RacePowerupManager::LoadDatabases(
	const LegoChar* p_databaseName,
	const LegoChar* p_animationName,
	LegoBool32 p_binary
)
{
	m_worldDatabase = m_golExport->CreateWorldDatabase();
	m_worldDatabase->Load(m_renderer, p_databaseName, p_binary, 1.0f);
	m_materialAnimation.Load(m_renderer, p_animationName, p_binary);
	m_turbo3Database = m_golExport->CreateWorldDatabase();
	m_turbo3Database->Load(m_renderer, "turbo3", p_binary, 1.0f);
}

// FUNCTION: LEGORACERS 0x00457cf0
void RacePowerupManager::PreparePools(LegoBool32 p_mirror)
{
	SetActionPoolCounts(p_mirror);
	m_billboardMaterialTable.Initialize(m_renderer, m_actionPoolCounts[5] + m_actionPoolCounts[0]);
	m_brickDebris.Initialize(this, m_renderer);
}

// FUNCTION: LEGORACERS 0x00457d30
void RacePowerupManager::SetActionPoolCounts(LegoBool32 p_mirror)
{
	if (p_mirror) {
		m_actionPoolCounts[0] = 3;
		m_actionPoolCounts[1] = 4;
		m_actionPoolCounts[2] = 3;
		m_actionPoolCounts[3] = 2;
		m_actionPoolCounts[4] = 4;
		m_actionPoolCounts[5] = 3;
		m_actionPoolCounts[6] = 3;
		m_actionPoolCounts[7] = 9;
		m_actionPoolCounts[8] = 5;
		m_actionPoolCounts[9] = 6;
		m_actionPoolCounts[10] = 3;
	}
	else {
		m_actionPoolCounts[0] = 2;
		m_actionPoolCounts[1] = 3;
		m_actionPoolCounts[2] = 2;
		m_actionPoolCounts[3] = 2;
		m_actionPoolCounts[4] = 2;
		m_actionPoolCounts[5] = 2;
		m_actionPoolCounts[6] = 2;
		m_actionPoolCounts[7] = 6;
		m_actionPoolCounts[8] = 2;
		m_actionPoolCounts[9] = 2;
		m_actionPoolCounts[10] = 2;
	}

	m_explosionPoolCount = 6;
	m_spikeExplosionPoolCount = 2;

	m_magnetActions = new MagnetAction[m_actionPoolCounts[0]];
	if (!m_magnetActions) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_oilSlickActions = new OilSlickAction[m_actionPoolCounts[1]];
	if (!m_oilSlickActions) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_dynamiteActions = new DynamiteAction[m_actionPoolCounts[2]];
	if (!m_dynamiteActions) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_curseActions = new CurseAction[m_actionPoolCounts[3]];
	if (!m_curseActions) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_cannonballActions = new CannonballAction[m_actionPoolCounts[4]];
	if (!m_cannonballActions) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_grapplingHookActions = new GrapplingHookAction[m_actionPoolCounts[5]];
	if (!m_grapplingHookActions) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_lightningActions = new LightningAction[m_actionPoolCounts[6]];
	if (!m_lightningActions) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_homingMissileActions = new HomingMissileAction[m_actionPoolCounts[7]];
	if (!m_homingMissileActions) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_shieldActions = new ShieldAction[m_actionPoolCounts[8]];
	if (!m_shieldActions) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_turboActions = new TurboAction[m_actionPoolCounts[9]];
	if (!m_turboActions) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_warpActions = new WarpAction[m_actionPoolCounts[10]];
	if (!m_warpActions) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_explosionPool = new PowerupExplosion[m_explosionPoolCount];
	if (!m_explosionPool) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_spikeExplosionPool = new PowerupExplosion[m_spikeExplosionPoolCount];
	if (!m_spikeExplosionPool) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void RacePowerupManager::FUN_004164c0()
{
}

// FUNCTION: LEGORACERS 0x00458810
void RacePowerupManager::LoadPowerupFile(const LegoChar* p_name, LegoBool32 p_binary, LegoBool32 p_mirror)
{
	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".pwb");
	}
	else {
		parser = new PwbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_name);

	GolFileParser::ParserTokenType token = parser->GetNextToken();
	while (token != GolFileParser::e_syntaxerror) {
		if (token != PwbTxtParser::e_colorBricks) {
			if (token == PwbTxtParser::e_whiteBricks) {
				ParseWhiteBricks(parser, p_mirror);
			}
		}
		else {
			ParseColorBricks(parser, p_mirror);
		}

		token = parser->GetNextToken();
	}

	parser->Dispose();
	if (parser != NULL) {
		delete parser;
	}
}

// FUNCTION: LEGORACERS 0x00458940
void RacePowerupManager::CreatePools()
{
	m_brickEvents = new LegoEventQueue::Event*[m_colorBrickCount + m_whiteBrickCount];
	if (!m_brickEvents) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoU32 i;
	for (i = 0; i < m_colorBrickCount + m_whiteBrickCount; i++) {
		m_brickEvents[i] = NULL;
	}

	FUN_004164c0();
	CreateBrickEvents();
	CreateActionPools();
	CreateExplosionPools();

	m_cannonballFlightSound = m_soundSource->AcquireSoundById(7);
	if (m_cannonballFlightSound != NULL) {
		m_cannonballFlightSound->SetDistanceRangeWithMinSquared(
			g_flightSoundMinDistance * g_flightSoundMinDistance,
			g_flightSoundMaxDistanceSquared
		);
	}

	m_missileFlightSound = m_soundSource->AcquireSoundById(c_soundMissileFlight);
	if (m_missileFlightSound != NULL) {
		m_missileFlightSound->SetDistanceRangeWithMinSquared(
			g_flightSoundMinDistance * g_flightSoundMinDistance,
			g_flightSoundMaxDistanceSquared
		);
	}

	m_grappleFlightSound = m_soundSource->AcquireSoundById(c_soundGrappleFlight);
	if (m_grappleFlightSound != NULL) {
		m_grappleFlightSound->SetDistanceRangeWithMinSquared(
			g_flightSoundMinDistance * g_flightSoundMinDistance,
			g_flightSoundMaxDistanceSquared
		);
	}

	m_grappleAttachedSound = m_soundSource->AcquireSoundById(c_soundGrappleAttached);
	if (m_grappleAttachedSound != NULL) {
		m_grappleAttachedSound->SetDistanceRangeWithMinSquared(
			g_flightSoundMinDistance * g_flightSoundMinDistance,
			g_flightSoundMaxDistanceSquared
		);
	}
}

// FUNCTION: LEGORACERS 0x00458a80
void RacePowerupManager::ParseColorBricks(GolFileParser* p_parser, LegoBool32 p_mirror)
{
	m_colorBrickCount = p_parser->ReadBracketedCountAndLeftCurly();
	if (m_colorBrickCount == 0) {
		return;
	}

	m_colorBricks = new ColorBrick[m_colorBrickCount];
	if (m_colorBricks == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_brickModel = m_worldDatabase->FindAnimatedEntity("gen");
	m_brickBlendModel = m_worldDatabase->FindAnimatedEntity("genblen");
	m_brickMaterials[c_brickMaterialRed] = m_renderer->FindMaterialByName("pbrickP");
	m_brickMaterials[c_trailMaterialRed] = m_renderer->FindMaterialByName("ptrailP");
	m_brickMaterials[c_brickMaterialYellow] = m_renderer->FindMaterialByName("pbrickM");
	m_brickMaterials[c_trailMaterialYellow] = m_renderer->FindMaterialByName("ptrailM");
	m_brickMaterials[c_brickMaterialBlue] = m_renderer->FindMaterialByName("pbrickS");
	m_brickMaterials[c_trailMaterialBlue] = m_renderer->FindMaterialByName("ptrailS");
	m_brickMaterials[c_brickMaterialGreen] = m_renderer->FindMaterialByName("pbrickT");
	m_brickMaterials[c_trailMaterialGreen] = m_renderer->FindMaterialByName("ptrailT");

	LegoU32 i;
	for (i = 0; i < m_colorBrickCount; i++) {
		if (p_parser->GetNextToken() != PwbTxtParser::e_colorBricks) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}
		if (p_parser->GetNextToken() != GolFileParser::e_leftCurly) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		GolVec3 position;
		position.m_x = 0.0f;
		position.m_y = 0.0f;
		position.m_z = 0.0f;
		LegoU32 state = 3;
		LegoS32 duration = -1;

		GolFileParser::ParserTokenType token = p_parser->GetNextToken();
		while (token != GolFileParser::e_rightCurly) {
			switch (token) {
			case PwbTxtParser::e_position:
				position.m_x = p_parser->ReadFloat();
				position.m_y = p_parser->ReadFloat();
				position.m_z = p_parser->ReadFloat();
				break;
			case PwbTxtParser::e_colorRed:
				state = c_brickColorRed;
				break;
			case PwbTxtParser::e_colorYellow:
				state = c_brickColorYellow;
				break;
			case PwbTxtParser::e_colorBlue:
				state = c_brickColorBlue;
				break;
			case PwbTxtParser::e_colorGreen:
				state = c_brickColorGreen;
				break;
			case PwbTxtParser::e_respawnMs:
				duration = p_parser->ReadInteger();
				break;
			case PwbTxtParser::e_unknown0x30:
				p_parser->ReadStringWithMaxLength(sizeof(GolName));
				// Intentional fall-through: the original consumes the following integer too.
			case PwbTxtParser::e_unknown0x31:
				p_parser->ReadInteger();
				break;
			default:
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}

			token = p_parser->GetNextToken();
		}

		if (!(m_cheatFlags & (c_pgllrd | c_rpcrnly))) {
			if (m_cheatFlags & c_pgllyll) {
				state = 4;
			}
			else if (m_cheatFlags & c_pgllgrn) {
				state = i * sizeof(ColorBrick);
			}
		}
		else {
			state = 1;
		}

		if (p_mirror) {
			position.m_y = -position.m_y;
		}

		GolMaterial* material0 = GetBrickMaterial(&state);
		GolMaterial* material1 = GetTrailMaterial(&state);
		m_colorBricks[i].Initialize(this, m_soundSource, &position, m_brickModel, m_brickBlendModel);
		m_colorBricks[i].SetMaterials(material0, material1);
		m_colorBricks[i].SetColor(state);
		if (duration >= 0) {
			m_colorBricks[i].SetRespawnMs(duration);
		}
	}

	if (p_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_rightCurly);
	}
}

// FUNCTION: LEGORACERS 0x00458e80
void RacePowerupManager::ParseWhiteBricks(GolFileParser* p_parser, LegoBool32 p_mirror)
{
	m_whiteBrickCount = p_parser->ReadBracketedCountAndLeftCurly();
	if (m_whiteBrickCount == 0) {
		return;
	}

	m_whiteBricks = new WhiteBrick[m_whiteBrickCount];
	if (m_whiteBricks == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_whiteBrickModel = m_worldDatabase->FindAnimatedEntity("enh");
	m_whiteBrickBlendModel = m_worldDatabase->FindAnimatedEntity("enhblen");

	LegoU32 i;
	for (i = 0; i < m_whiteBrickCount; i++) {
		if (p_parser->GetNextToken() != PwbTxtParser::e_whiteBricks) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}
		if (p_parser->GetNextToken() != GolFileParser::e_leftCurly) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
		}

		GolVec3 position;
		position.m_x = 0.0f;
		position.m_y = 0.0f;
		position.m_z = 0.0f;

		GolFileParser::ParserTokenType token = p_parser->GetNextToken();
		while (token != GolFileParser::e_rightCurly) {
			switch (token) {
			case PwbTxtParser::e_position:
				position.m_x = p_parser->ReadFloat();
				position.m_y = p_parser->ReadFloat();
				position.m_z = p_parser->ReadFloat();
				break;
			case PwbTxtParser::e_unknown0x30:
				p_parser->ReadStringWithMaxLength(sizeof(GolName));
				// Intentional fall-through: the original consumes the following integer too.
			case PwbTxtParser::e_unknown0x31:
				p_parser->ReadInteger();
				break;
			default:
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}

			token = p_parser->GetNextToken();
		}

		if (p_mirror) {
			position.m_y = -position.m_y;
		}

		m_whiteBricks[i].Initialize(this, m_soundSource, &position, m_whiteBrickModel, m_whiteBrickBlendModel);
		m_whiteBricks[i].CaptureHomePosition();
	}

	if (p_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_rightCurly);
	}
}

// FUNCTION: LEGORACERS 0x004590f0
void RacePowerupManager::CreateActionPools()
{
	LegoU8 i = 0;

	if (m_actionPoolCounts[0] - 1 > 0) {
		do {
			m_magnetActions[i].SetNext(&m_magnetActions[i + 1]);
			m_magnetActions[i].Initialize(
				this,
				m_raceState,
				m_collisionWorld,
				m_cutsceneAnimation,
				m_golExport,
				m_renderer,
				m_actionPoolCounts[5] + i
			);
			m_magnetActions[i].SetSoundSource(m_soundSource);
			i++;
		} while (i < m_actionPoolCounts[0] - 1);
	}

	m_magnetActions[m_actionPoolCounts[0] - 1].SetNext(NULL);
	m_magnetActions[m_actionPoolCounts[0] - 1].Initialize(
		this,
		m_raceState,
		m_collisionWorld,
		m_cutsceneAnimation,
		m_golExport,
		m_renderer,
		m_actionPoolCounts[5] + m_actionPoolCounts[0] - 1
	);
	m_magnetActions[m_actionPoolCounts[0] - 1].SetSoundSource(m_soundSource);
	m_freeMagnetActions = m_magnetActions;

	i = 0;
	if (m_actionPoolCounts[1] - 1 > 0) {
		do {
			m_oilSlickActions[i].SetNext(&m_oilSlickActions[i + 1]);
			m_oilSlickActions[i].Initialize(
				this,
				m_raceState,
				m_collidable,
				m_collisionWorld,
				m_cutsceneAnimation,
				m_renderer,
				m_golExport
			);
			m_oilSlickActions[i].SetSoundSource(m_soundSource);
			i++;
		} while (i < m_actionPoolCounts[1] - 1);
	}

	m_oilSlickActions[m_actionPoolCounts[1] - 1].SetNext(NULL);
	m_oilSlickActions[m_actionPoolCounts[1] - 1]
		.Initialize(this, m_raceState, m_collidable, m_collisionWorld, m_cutsceneAnimation, m_renderer, m_golExport);
	m_oilSlickActions[m_actionPoolCounts[1] - 1].SetSoundSource(m_soundSource);
	m_freeOilSlickActions = m_oilSlickActions;

	i = 0;
	if (m_actionPoolCounts[2] - 1 > 0) {
		do {
			m_dynamiteActions[i].SetNext(&m_dynamiteActions[i + 1]);
			m_dynamiteActions[i].Initialize(
				m_raceState,
				m_collisionWorld,
				this,
				m_cutsceneAnimation,
				m_worldDatabase->FindModelEntity("barrel")
			);
			m_dynamiteActions[i].SetSoundSource(m_soundSource);
			i++;
		} while (i < m_actionPoolCounts[2] - 1);
	}

	m_dynamiteActions[m_actionPoolCounts[2] - 1].SetNext(NULL);
	m_dynamiteActions[m_actionPoolCounts[2] - 1].Initialize(
		m_raceState,
		m_collisionWorld,
		this,
		m_cutsceneAnimation,
		m_worldDatabase->FindModelEntity("barrel")
	);
	m_dynamiteActions[m_actionPoolCounts[2] - 1].SetSoundSource(m_soundSource);
	m_freeDynamiteActions = m_dynamiteActions;

	i = 0;
	if (m_actionPoolCounts[3] - 1 > 0) {
		do {
			m_curseActions[i].SetNext(&m_curseActions[i + 1]);
			m_curseActions[i].Initialize(m_raceState, m_collisionWorld, this);
			m_curseActions[i].SetSoundSource(m_soundSource);
			i++;
		} while (i < m_actionPoolCounts[3] - 1);
	}

	m_curseActions[m_actionPoolCounts[3] - 1].SetNext(NULL);
	m_curseActions[m_actionPoolCounts[3] - 1].Initialize(m_raceState, m_collisionWorld, this);
	m_curseActions[m_actionPoolCounts[3] - 1].SetSoundSource(m_soundSource);
	m_freeCurseActions = m_curseActions;

	i = 0;
	if (m_actionPoolCounts[4] - 1 > 0) {
		do {
			m_cannonballActions[i].SetNext(&m_cannonballActions[i + 1]);
			m_cannonballActions[i].Initialize(this, m_collisionWorld);
			m_cannonballActions[i].SetSoundSource(m_soundSource);
			i++;
		} while (i < m_actionPoolCounts[4] - 1);
	}

	m_cannonballActions[m_actionPoolCounts[4] - 1].SetNext(NULL);
	m_cannonballActions[m_actionPoolCounts[4] - 1].Initialize(this, m_collisionWorld);
	m_cannonballActions[m_actionPoolCounts[4] - 1].SetSoundSource(m_soundSource);
	m_freeCannonballActions = m_cannonballActions;

	i = 0;
	if (m_actionPoolCounts[5] - 1 > 0) {
		do {
			m_grapplingHookActions[i].SetNext(&m_grapplingHookActions[i + 1]);
			m_grapplingHookActions[i].Initialize(this, m_collisionWorld, i);
			m_grapplingHookActions[i].SetSoundSource(m_soundSource);
			i++;
		} while (i < m_actionPoolCounts[5] - 1);
	}

	m_grapplingHookActions[m_actionPoolCounts[5] - 1].SetNext(NULL);
	m_grapplingHookActions[m_actionPoolCounts[5] - 1].Initialize(this, m_collisionWorld, m_actionPoolCounts[5] - 1);
	m_grapplingHookActions[m_actionPoolCounts[5] - 1].SetSoundSource(m_soundSource);
	m_freeGrapplingHookActions = m_grapplingHookActions;

	i = 0;
	if (m_actionPoolCounts[6] - 1 > 0) {
		do {
			m_lightningActions[i].SetNext(&m_lightningActions[i + 1]);
			m_lightningActions[i].Initialize(m_golExport, this);
			m_lightningActions[i].SetSoundSource(m_soundSource);
			m_lightningActions[i].AcquireSound();
			i++;
		} while (i < m_actionPoolCounts[6] - 1);
	}

	m_lightningActions[m_actionPoolCounts[6] - 1].SetNext(NULL);
	m_lightningActions[m_actionPoolCounts[6] - 1].Initialize(m_golExport, this);
	m_lightningActions[m_actionPoolCounts[6] - 1].SetSoundSource(m_soundSource);
	m_lightningActions[m_actionPoolCounts[6] - 1].AcquireSound();
	m_freeLightningActions = m_lightningActions;

	i = 0;
	if (m_actionPoolCounts[7] - 1 > 0) {
		do {
			m_homingMissileActions[i].SetNext(&m_homingMissileActions[i + 1]);
			m_homingMissileActions[i].Initialize(this, m_collisionWorld);
			m_homingMissileActions[i].SetSoundSource(m_soundSource);
			i++;
		} while (i < m_actionPoolCounts[7] - 1);
	}

	m_homingMissileActions[m_actionPoolCounts[7] - 1].SetNext(NULL);
	m_homingMissileActions[m_actionPoolCounts[7] - 1].Initialize(this, m_collisionWorld);
	m_homingMissileActions[m_actionPoolCounts[7] - 1].SetSoundSource(m_soundSource);
	m_freeHomingMissileActions = m_homingMissileActions;

	i = 0;
	if (m_actionPoolCounts[8] - 1 > 0) {
		do {
			m_shieldActions[i].SetNext(&m_shieldActions[i + 1]);
			m_shieldActions[i].Initialize(this);
			m_shieldActions[i].SetSoundSource(m_soundSource);
			i++;
		} while (i < m_actionPoolCounts[8] - 1);
	}

	m_shieldActions[m_actionPoolCounts[8] - 1].SetNext(NULL);
	m_shieldActions[m_actionPoolCounts[8] - 1].Initialize(this);
	m_shieldActions[m_actionPoolCounts[8] - 1].SetSoundSource(m_soundSource);
	m_freeShieldActions = m_shieldActions;

	i = 0;
	if (m_actionPoolCounts[9] - 1 > 0) {
		do {
			m_turboActions[i].SetNext(&m_turboActions[i + 1]);
			m_turboActions[i].Initialize(this, m_cutsceneAnimation);
			m_turboActions[i].SetSoundSource(m_soundSource);
			i++;
		} while (i < m_actionPoolCounts[9] - 1);
	}

	m_turboActions[m_actionPoolCounts[9] - 1].SetNext(NULL);
	m_turboActions[m_actionPoolCounts[9] - 1].Initialize(this, m_cutsceneAnimation);
	m_turboActions[m_actionPoolCounts[9] - 1].SetSoundSource(m_soundSource);
	m_freeTurboActions = m_turboActions;

	WarpAction::SetupParams params;
	params.m_manager = this;
	params.m_cameraFov = m_cameraFov;

	i = 0;
	if (m_actionPoolCounts[10] - 1 > 0) {
		do {
			m_warpActions[i].SetNext(&m_warpActions[i + 1]);
			m_warpActions[i].Initialize(&params);
			m_warpActions[i].SetSoundSource(m_soundSource);
			i++;
		} while (i < m_actionPoolCounts[10] - 1);
	}

	m_warpActions[m_actionPoolCounts[10] - 1].SetNext(NULL);
	m_warpActions[m_actionPoolCounts[10] - 1].Initialize(&params);
	m_warpActions[m_actionPoolCounts[10] - 1].SetSoundSource(m_soundSource);
	m_freeWarpActions = m_warpActions;

	m_activeActions = NULL;
}

// FUNCTION: LEGORACERS 0x00459b80
void RacePowerupManager::CreateExplosionPools()
{
	PowerupExplosion::Params params;
	params.m_golExport = m_golExport;
	params.m_collidable = m_collidable;
	params.m_model = m_worldDatabase->FindModelEntity("Explsn");
	params.m_billboardMaterial = NULL;
	params.m_billboardAnimation = NULL;
	params.m_flashMaterial = m_renderer->FindMaterialByName("exflash");
	params.m_scarMaterial = m_renderer->FindMaterialByName("exscar");
	params.m_eventQueue = m_raceState->GetEventQueue();
	params.m_manager = this;
	params.m_particleAnimation = NULL;
	params.m_flashDurationMs = 1000;
	params.m_scarDurationMs = 5000;
	params.m_modelScale = 1.0f;
	params.m_flashWidth = 15.0f;
	params.m_flashHeight = 15.0f;
	params.m_blastRadius = 5.0f;
	params.m_blastMode = 2;

	LegoU8 index = 0;
	if (m_explosionPoolCount - 1 > 0) {
		do {
			m_explosionPool[index].SetNext(&m_explosionPool[index + 1]);
			params.m_billboardMaterialIndex = 0;
			m_explosionPool[index].Initialize(&params);
			index++;
		} while (index < m_explosionPoolCount - 1);
	}

	m_explosionPool[m_explosionPoolCount - 1].SetNext(NULL);
	params.m_billboardMaterialIndex = 0;
	m_explosionPool[m_explosionPoolCount - 1].Initialize(&params);
	m_freeExplosions = m_explosionPool;
	m_activeExplosions = NULL;

	params.m_particleAnimation = NULL;
	params.m_blastRadius = 10.0f;
	params.m_blastMode = 2;
	params.m_model = m_worldDatabase->FindModelEntity("spikexp");
	params.m_flashMaterial = NULL;
	params.m_flashWidth = 5.0f;
	params.m_flashHeight = 5.0f;

	index = 0;
	if (m_spikeExplosionPoolCount - 1 > 0) {
		do {
			m_spikeExplosionPool[index].SetNext(&m_spikeExplosionPool[index + 1]);
			params.m_billboardMaterialIndex = 0;
			m_spikeExplosionPool[index].Initialize(&params);
			index++;
		} while (index < m_spikeExplosionPoolCount - 1);
	}

	m_spikeExplosionPool[m_spikeExplosionPoolCount - 1].SetNext(NULL);
	params.m_billboardMaterialIndex = 0;
	m_spikeExplosionPool[m_spikeExplosionPoolCount - 1].Initialize(&params);
	m_activeSpikeExplosions = NULL;
	m_freeSpikeExplosions = m_spikeExplosionPool;
}

// FUNCTION: LEGORACERS 0x00459e20
void RacePowerupManager::Destroy()
{
	LegoU32 i;

	if (m_grappleAttachedSound != NULL) {
		m_soundSource->ReleaseSound(m_grappleAttachedSound);
		m_grappleAttachedSound = NULL;
	}

	if (m_grappleFlightSound != NULL) {
		m_soundSource->ReleaseSound(m_grappleFlightSound);
		m_grappleFlightSound = NULL;
	}

	if (m_missileFlightSound != NULL) {
		m_soundSource->ReleaseSound(m_missileFlightSound);
		m_missileFlightSound = NULL;
	}

	if (m_cannonballFlightSound != NULL) {
		m_soundSource->ReleaseSound(m_cannonballFlightSound);
		m_cannonballFlightSound = NULL;
	}

	m_billboardMaterialTable.Clear();

	if (m_spikeExplosionPool != NULL) {
		for (i = 0; i < m_spikeExplosionPoolCount; i++) {
			m_spikeExplosionPool[i].Destroy();
		}

		delete[] m_spikeExplosionPool;
		m_spikeExplosionPool = NULL;
	}

	if (m_explosionPool != NULL) {
		for (i = 0; i < m_explosionPoolCount; i++) {
			m_explosionPool[i].Destroy();
		}

		delete[] m_explosionPool;
		m_explosionPool = NULL;
	}

	if (m_warpActions != NULL) {
		for (i = 0; i < m_actionPoolCounts[10]; i++) {
			m_warpActions[i].Destroy();
		}

		delete[] m_warpActions;
		m_warpActions = NULL;
	}

	if (m_turboActions != NULL) {
		for (i = 0; i < m_actionPoolCounts[9]; i++) {
			m_turboActions[i].Destroy();
		}

		delete[] m_turboActions;
		m_turboActions = NULL;
	}

	if (m_shieldActions != NULL) {
		for (i = 0; i < m_actionPoolCounts[8]; i++) {
			m_shieldActions[i].Destroy();
		}

		delete[] m_shieldActions;
		m_shieldActions = NULL;
	}

	if (m_homingMissileActions != NULL) {
		for (i = 0; i < m_actionPoolCounts[7]; i++) {
			m_homingMissileActions[i].Shutdown();
		}

		delete[] m_homingMissileActions;
		m_homingMissileActions = NULL;
	}

	if (m_lightningActions != NULL) {
		for (i = 0; i < m_actionPoolCounts[6]; i++) {
			m_lightningActions[i].Destroy();
		}

		delete[] m_lightningActions;
		m_lightningActions = NULL;
	}

	if (m_grapplingHookActions != NULL) {
		for (i = 0; i < m_actionPoolCounts[5]; i++) {
			m_grapplingHookActions[i].Shutdown();
		}

		delete[] m_grapplingHookActions;
		m_grapplingHookActions = NULL;
	}

	if (m_cannonballActions != NULL) {
		for (i = 0; i < m_actionPoolCounts[4]; i++) {
			m_cannonballActions[i].Destroy();
		}

		delete[] m_cannonballActions;
		m_cannonballActions = NULL;
	}

	if (m_curseActions != NULL) {
		for (i = 0; i < m_actionPoolCounts[3]; i++) {
			m_curseActions[i].Destroy();
		}

		delete[] m_curseActions;
		m_curseActions = NULL;
	}

	if (m_dynamiteActions != NULL) {
		for (i = 0; i < m_actionPoolCounts[2]; i++) {
			m_dynamiteActions[i].Destroy();
		}

		delete[] m_dynamiteActions;
		m_dynamiteActions = NULL;
	}

	if (m_oilSlickActions != NULL) {
		for (i = 0; i < m_actionPoolCounts[1]; i++) {
			m_oilSlickActions[i].Destroy();
		}

		delete[] m_oilSlickActions;
		m_oilSlickActions = NULL;
	}

	if (m_magnetActions != NULL) {
		for (i = 0; i < m_actionPoolCounts[0]; i++) {
			m_magnetActions[i].Destroy();
		}

		delete[] m_magnetActions;
		m_magnetActions = NULL;
	}

	if (m_golExport != NULL && m_worldDatabase != 0) {
		m_golExport->DestroyWorldDatabase(m_worldDatabase);
		m_worldDatabase = 0;
	}

	m_materialAnimation.Destroy();
	m_trackDatabase = 0;

	if (m_golExport != NULL && m_turbo3Database != 0) {
		m_golExport->DestroyWorldDatabase(m_turbo3Database);
		m_turbo3Database = 0;
	}

	if (m_brickEvents != NULL) {
		for (i = 0; i < m_colorBrickCount + m_whiteBrickCount; i++) {
			if (m_brickEvents[i] != NULL) {
				m_brickEvents[i]->m_active = 0;
			}
		}

		delete[] m_brickEvents;
		m_brickEvents = NULL;
	}

	if (m_whiteBricks != NULL) {
		delete[] m_whiteBricks;
		m_whiteBricks = NULL;
	}

	if (m_colorBricks != NULL) {
		delete[] m_colorBricks;
		m_colorBricks = NULL;
	}

	for (LegoS32 j = 25; j != 0; j--) {
		m_effectEntities[25 - j].ResetModelState();
	}

	Reset();
}

// FUNCTION: LEGORACERS 0x0045a340
void RacePowerupManager::CreateBrickEvents()
{
	LegoEventQueue* eventQueue = m_raceState->GetEventQueue();
	LegoEventQueue::Descriptor descriptor;

	descriptor.m_type = 4;
	descriptor.m_flags = 1;
	descriptor.m_maxFireCount = 0;
	descriptor.m_hitThreshold = 0;

	LegoU32 i;
	for (i = 0; i < m_colorBrickCount; i++) {
		ColorBrick* entry = &m_colorBricks[i];
		descriptor.m_data = entry->GetWorldEntity();
		m_brickEvents[i] = eventQueue->AllocateEvent(entry, &descriptor);
	}

	WhiteBrick* whiteBricks = m_whiteBricks;
	for (i = 0; i < m_whiteBrickCount; i++) {
		WhiteBrick* entry = &whiteBricks[i];
		descriptor.m_data = entry->GetWorldEntity();
		m_brickEvents[m_colorBrickCount + i] = eventQueue->AllocateEvent(entry, &descriptor);
	}
}

// FUNCTION: LEGORACERS 0x0045a3f0
void RacePowerupManager::UpdateBricks(LegoU32 p_elapsedMs)
{
	if (m_brickModel != NULL) {
		m_brickModel->Update(p_elapsedMs);
	}
	if (m_brickBlendModel != NULL) {
		m_brickBlendModel->Update(p_elapsedMs);
	}
	if (m_whiteBrickModel != NULL) {
		m_whiteBrickModel->Update(p_elapsedMs);
	}
	if (m_whiteBrickBlendModel != NULL) {
		m_whiteBrickBlendModel->Update(p_elapsedMs);
	}

	if (m_colorBricks != NULL) {
		LegoU32 i;

		for (i = 0; i < m_colorBrickCount; i++) {
			m_colorBricks[i].Update(p_elapsedMs);
		}

		for (i = 0; i < m_whiteBrickCount; i++) {
			m_whiteBricks[i].Update(p_elapsedMs);
		}
	}
}

// FUNCTION: LEGORACERS 0x0045a490
void RacePowerupManager::Update(LegoU32 p_elapsedMs)
{
	UpdateBricks(p_elapsedMs);

	m_brickSpinAngle += static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs)) * g_brickSpinRate;
	if (m_brickSpinAngle > g_brickSpinWrap) {
		m_brickSpinAngle -= g_brickSpinWrap;
	}

	PowerupAction* action;
	for (action = m_activeActions; action != NULL; action = action->GetNext()) {
		action->Update(p_elapsedMs);
	}

	PowerupExplosion* explosion;
	for (explosion = m_activeExplosions; explosion != NULL; explosion = explosion->GetNext()) {
		explosion->Update(p_elapsedMs);
	}

	for (explosion = m_activeSpikeExplosions; explosion != NULL; explosion = explosion->GetNext()) {
		explosion->Update(p_elapsedMs);
	}

	m_brickDebris.Update(p_elapsedMs);

	action = m_activeActions;
	PowerupAction* previousAction = NULL;
	while (action != NULL) {
		PowerupAction* nextAction = action->GetNext();
		if (action->GetState() == 6) {
			if (previousAction == NULL) {
				m_activeActions = nextAction;
			}
			else {
				previousAction->SetNext(nextAction);
			}

			action->Deactivate();

			switch (action->GetBrickColor()) {
			case 1:
				switch (action->GetLevel()) {
				case 0:
					action->SetNext(m_freeCannonballActions);
					m_freeCannonballActions = action;
					break;
				case 1:
					action->SetNext(m_freeGrapplingHookActions);
					m_freeGrapplingHookActions = action;
					break;
				case 2:
					action->SetNext(m_freeLightningActions);
					m_freeLightningActions = action;
					break;
				case 3:
					action->SetNext(m_freeHomingMissileActions);
					m_freeHomingMissileActions = action;
					break;
				}
				break;
			case 4:
				switch (action->GetLevel()) {
				case 0:
					action->SetNext(m_freeOilSlickActions);
					m_freeOilSlickActions = action;
					break;
				case 1:
					action->SetNext(m_freeDynamiteActions);
					m_freeDynamiteActions = action;
					break;
				case 2:
					action->SetNext(m_freeMagnetActions);
					m_freeMagnetActions = action;
					break;
				case 3:
					action->SetNext(m_freeCurseActions);
					m_freeCurseActions = action;
					break;
				}
				break;
			case 2:
				action->SetNext(m_freeShieldActions);
				m_freeShieldActions = action;
				break;
			case 3:
				if (action->GetLevel() > 2) {
					if (action->GetLevel() == 3) {
						action->SetNext(m_freeWarpActions);
						m_freeWarpActions = action;
					}
				}
				else {
					action->SetNext(m_freeTurboActions);
					m_freeTurboActions = action;
				}
				break;
			}
		}
		else {
			previousAction = action;
		}

		action = nextAction;
	}

	explosion = m_activeExplosions;
	PowerupExplosion* previousExplosion = NULL;
	while (explosion != NULL) {
		PowerupExplosion* nextExplosion = explosion->GetNext();
		if (explosion->GetState() == PowerupExplosion::c_stateIdle) {
			if (previousExplosion == NULL) {
				m_activeExplosions = nextExplosion;
			}
			else {
				previousExplosion->SetNext(nextExplosion);
			}

			explosion->SetNext(m_freeExplosions);
			m_freeExplosions = explosion;
		}
		else {
			previousExplosion = explosion;
		}

		explosion = nextExplosion;
	}

	explosion = m_activeSpikeExplosions;
	previousExplosion = NULL;
	while (explosion != NULL) {
		PowerupExplosion* nextExplosion = explosion->GetNext();
		if (explosion->GetState() == PowerupExplosion::c_stateIdle) {
			if (previousExplosion == NULL) {
				m_activeSpikeExplosions = nextExplosion;
			}
			else {
				previousExplosion->SetNext(nextExplosion);
			}

			explosion->SetNext(m_freeSpikeExplosions);
			m_freeSpikeExplosions = explosion;
		}
		else {
			previousExplosion = explosion;
		}

		explosion = nextExplosion;
	}

	if (m_trackDatabase != NULL) {
		m_trackDatabase->Update(p_elapsedMs);
	}

	if (m_cannonballFlightSound != NULL) {
		UpdateProjectileSound(m_cannonballFlightSound, 0, 3);
	}
	if (m_missileFlightSound != NULL) {
		UpdateProjectileSound(m_missileFlightSound, 3, 3);
	}
	if (m_grappleFlightSound != NULL) {
		UpdateProjectileSound(m_grappleFlightSound, 1, 3);
	}
	if (m_grappleAttachedSound != NULL) {
		UpdateProjectileSound(m_grappleAttachedSound, 1, 4);
	}
}

// FUNCTION: LEGORACERS 0x0045a7b0
void RacePowerupManager::Draw(LegoBool32 p_warpOnly)
{
	if (!p_warpOnly) {
		LegoU32 i;

		for (i = 0; i < m_colorBrickCount; i++) {
			m_colorBricks[i].Draw(m_renderer);
		}

		for (i = 0; i < m_whiteBrickCount; i++) {
			m_whiteBricks[i].Draw(m_renderer);
		}
	}

	PowerupAction* action = m_activeActions;
	while (action != NULL) {
		if (!p_warpOnly || (action->GetBrickColor() == c_brickColorGreen && action->GetLevel() == 3)) {
			action->Draw(m_renderer);
		}

		action = action->GetNext();
	}

	if (!p_warpOnly) {
		PowerupExplosion* explosion = m_activeExplosions;
		while (explosion != NULL) {
			explosion->Draw(m_renderer);
			explosion = explosion->GetNext();
		}

		PowerupExplosion* spikeExplosion = m_activeSpikeExplosions;
		while (spikeExplosion != NULL) {
			spikeExplosion->Draw(m_renderer);
			spikeExplosion = spikeExplosion->GetNext();
		}
	}

	m_brickDebris.Draw(m_renderer);
}

// FUNCTION: LEGORACERS 0x0045a8a0
void RacePowerupManager::DrawTransparent()
{
	LegoU32 i;

	for (i = 0; i < m_colorBrickCount; i++) {
		m_colorBricks[i].DrawTransparent(m_renderer);
	}

	for (i = 0; i < m_whiteBrickCount; i++) {
		m_whiteBricks[i].DrawTransparent(m_renderer);
	}

	PowerupAction* action = m_activeActions;
	while (action != NULL) {
		action->DrawTransparent(m_renderer);
		action = action->GetNext();
	}

	PowerupExplosion* explosion = m_activeExplosions;
	while (explosion != NULL) {
		explosion->DrawTransparent(m_renderer);
		explosion = explosion->GetNext();
	}

	PowerupExplosion* spikeExplosion = m_activeSpikeExplosions;
	while (spikeExplosion != NULL) {
		spikeExplosion->DrawTransparent(m_renderer);
		spikeExplosion = spikeExplosion->GetNext();
	}
}

// FUNCTION: LEGORACERS 0x0045a950
void RacePowerupManager::UseRedPowerup(Racer* p_racer, LegoU32 p_level)
{
	switch (p_level) {
	case 0:
		FireCannonball(p_racer, 0);
		return;
	case 1:
		FireGrapplingHook(p_racer, 1);
		return;
	case 2:
		FireLightning(p_racer, 2);
		return;
	case 3:
		FireHomingMissiles(p_racer, 3);
		return;
	default:
		return;
	}
}

// FUNCTION: LEGORACERS 0x0045a9b0
void RacePowerupManager::UseYellowPowerup(Racer* p_racer, LegoU32 p_level)
{
	switch (p_level) {
	case 0:
		DropOilSlick(p_racer, 0);
		break;
	case 1:
		ThrowDynamite(p_racer, 1);
		break;
	case 2:
		if (25 - m_usedEffectEntityCount >= 3) {
			ActivateMagnet(p_racer, 2);
		}
		break;
	case 3:
		if (25 - m_usedEffectEntityCount >= 3) {
			CastCurse(p_racer, 3);
		}
		break;
	}
}

// FUNCTION: LEGORACERS 0x0045aa30
LegoU32 RacePowerupManager::FireCannonball(Racer* p_racer, LegoU32 p_level)
{
	ActionSetup setup;
	setup.m_racer = p_racer;
	setup.m_targetPoint = NULL;
	setup.m_targetRacer = NULL;

	if (!m_aimTarget) {
		GolVec3 position;
		p_racer->m_visuals.m_carEntity->GetPosition(&position);

		GolVec3 direction;
		p_racer->m_visuals.m_carEntity->GetOrientationRow0(&direction);

		if (p_racer->m_controlMode != Racer::c_controlAi) {
			setup.m_targetPoint = m_targetPoints->FindTargetInCone(
				&position,
				&direction,
				g_aimMinDistanceSquared,
				g_aimMaxDistanceSquared,
				g_aimPointConeCosine
			);
		}

		if (!setup.m_targetPoint) {
			setup.m_targetRacer = m_raceState->FindNearestRacerInCone(
				&position,
				&direction,
				g_aimMinDistanceSquared,
				g_aimMaxDistanceSquared,
				g_aimRacerConeCosine
			);
		}
	}

	setup.m_aimTarget = m_aimTarget;
	setup.m_initialTimerMs = 0;

	CannonballAction* action = static_cast<CannonballAction*>(m_freeCannonballActions);
	if (!action) {
		action = static_cast<CannonballAction*>(ReclaimAction(c_brickColorRed, p_level, -1, -1, -1));
	}
	else {
		m_freeCannonballActions = action->m_next;
	}

	action->m_next = m_activeActions;
	m_activeActions = action;
	LegoU32 result = action->Activate(&setup);
	action->m_level = p_level;
	return result;
}

// FUNCTION: LEGORACERS 0x0045ab50
LegoU32 RacePowerupManager::FireGrapplingHook(Racer* p_racer, LegoU32 p_level)
{
	TargetPointList::Entry* entry = NULL;

	GolVec3 position;
	p_racer->m_visuals.m_carEntity->GetPosition(&position);

	GolVec3 direction;
	p_racer->m_visuals.m_carEntity->GetOrientationRow0(&direction);

	Racer* target = m_raceState->FindFarthestRacerInCone(
		&position,
		&direction,
		g_hookAimMinDistanceSquared,
		g_hookAimFarMaxDistanceSquared,
		g_hookAimFarConeCosine
	);
	if (!target) {
		target = m_raceState->FindNearestRacerInCone(
			&position,
			&direction,
			g_hookAimMinDistanceSquared,
			g_hookAimMaxDistanceSquared,
			g_hookAimWideConeCosine
		);
		if (!target && p_racer->m_controlMode != Racer::c_controlAi) {
			entry = m_targetPoints->FindTargetInCone(
				&position,
				&direction,
				g_aimMinDistanceSquared,
				g_aimMaxDistanceSquared,
				g_aimPointConeCosine
			);
		}
	}

	GrapplingHookAction* action = static_cast<GrapplingHookAction*>(m_freeGrapplingHookActions);
	if (!action) {
		action = static_cast<GrapplingHookAction*>(ReclaimAction(c_brickColorRed, p_level, -1, -1, -1));
	}
	else {
		m_freeGrapplingHookActions = action->m_next;
	}

	PowerupAction* next = m_activeActions;
	TargetPointList::Entry* setupEntry = entry;
	action->m_next = next;
	GolWorldDatabase* worldDatabase = m_worldDatabase;
	m_activeActions = action;
	GrapplingHookAction* activeAction = static_cast<GrapplingHookAction*>(m_activeActions);
	LegoU32 result =
		activeAction
			->Activate(worldDatabase->GetModelEntities(), p_racer, target, setupEntry, GetMaterialAnimationTracks(), 0);
	action->m_level = p_level;
	return result;
}

// FUNCTION: LEGORACERS 0x0045ac80
void RacePowerupManager::FireLightning(Racer* p_racer, LegoU32 p_level)
{
	LightningAction* action = static_cast<LightningAction*>(m_freeLightningActions);
	if (!action) {
		action = static_cast<LightningAction*>(ReclaimAction(c_brickColorRed, p_level, -1, -1, -1));
	}
	else {
		m_freeLightningActions = action->m_next;
	}

	action->m_next = m_activeActions;
	m_activeActions = action;
	action->Activate(p_racer, m_aimTarget);
	action->m_level = p_level;
}

// FUNCTION: LEGORACERS 0x0045ace0
void RacePowerupManager::DropOilSlick(Racer* p_racer, LegoU32 p_level)
{
	OilSlickAction* action = static_cast<OilSlickAction*>(m_freeOilSlickActions);
	if (!action) {
		action = static_cast<OilSlickAction*>(ReclaimAction(c_brickColorYellow, p_level, -1, -1, -1));
	}
	else {
		m_freeOilSlickActions = action->m_next;
	}

	action->m_next = m_activeActions;
	m_activeActions = action;
	action->Activate(p_racer);
	action->m_level = p_level;
}

// FUNCTION: LEGORACERS 0x0045ad30
LegoU32 RacePowerupManager::ThrowDynamite(Racer* p_racer, LegoU32 p_level)
{
	DynamiteAction* action = static_cast<DynamiteAction*>(m_freeDynamiteActions);
	if (!action) {
		action = static_cast<DynamiteAction*>(ReclaimAction(c_brickColorYellow, p_level, -1, -1, -1));
	}
	else {
		m_freeDynamiteActions = action->m_next;
	}

	action->m_next = m_activeActions;
	m_activeActions = action;

	GolVec3 position;
	p_racer->m_visuals.m_carEntity->GetPosition(&position);

	GolVec3 direction;
	p_racer->m_visuals.m_carEntity->GetOrientationRow0(&direction);
	direction.m_x = -direction.m_x;
	direction.m_y = -direction.m_y;
	direction.m_z = -direction.m_z;

	Racer* target = m_raceState->FindNearestRacerInCone(
		&position,
		&direction,
		g_dynamiteAimMinDistanceSquared,
		g_dynamiteAimMaxDistanceSquared,
		g_dynamiteAimConeCosine
	);
	LegoU32 result = action->Activate(p_racer, target);
	action->m_level = p_level;
	return result;
}

// FUNCTION: LEGORACERS 0x0045adf0
void RacePowerupManager::ActivateMagnet(Racer* p_racer, LegoU32 p_level)
{
	MagnetAction* action = static_cast<MagnetAction*>(m_freeMagnetActions);
	if (!action) {
		action = static_cast<MagnetAction*>(ReclaimAction(c_brickColorYellow, p_level, -1, -1, -1));
	}
	else {
		m_freeMagnetActions = action->m_next;
	}

	action->m_next = m_activeActions;
	m_activeActions = action;

	GolAnimatedEntity* model0;
	if (m_worldDatabase->GetAnimatedEntityEntries() == NULL) {
		model0 = NULL;
	}
	else {
		model0 = m_worldDatabase->GetAnimatedEntityByName("magnet");
	}

	GolAnimatedEntity* model1;
	if (m_worldDatabase->GetAnimatedEntityEntries() == NULL) {
		model1 = NULL;
	}
	else {
		model1 = m_worldDatabase->GetAnimatedEntityByName("magring");
	}

	GolAnimatedEntity* model2;
	if (m_worldDatabase->GetAnimatedEntityEntries() == NULL) {
		model2 = NULL;
	}
	else {
		model2 = m_worldDatabase->GetAnimatedEntityByName("insd");
	}

	action->Activate(p_racer, model0, model1, model2);
	action->m_level = p_level;
}

// FUNCTION: LEGORACERS 0x0045aeb0
void RacePowerupManager::CastCurse(Racer* p_racer, LegoU32 p_level)
{
	GolAnimatedEntity* model0;
	GolAnimatedEntity* model1;
	GolAnimatedEntity* model2;

	CurseAction* action = static_cast<CurseAction*>(m_freeCurseActions);
	if (!action) {
		action = static_cast<CurseAction*>(ReclaimAction(c_brickColorYellow, p_level, -1, -1, -1));
	}
	else {
		m_freeCurseActions = action->m_next;
	}

	action->m_next = m_activeActions;
	m_activeActions = action;

	if (m_worldDatabase->GetAnimatedEntityEntries() == NULL) {
		model0 = NULL;
	}
	else {
		model0 = m_worldDatabase->GetAnimatedEntityByName("curse");
	}

	if (m_worldDatabase->GetAnimatedEntityEntries() == NULL) {
		model1 = NULL;
	}
	else {
		model1 = m_worldDatabase->GetAnimatedEntityByName("cgreen");
	}

	if (m_worldDatabase->GetAnimatedEntityEntries() == NULL) {
		model2 = NULL;
	}
	else {
		model2 = m_worldDatabase->GetAnimatedEntityByName("cgreen2");
	}

	action->Activate(p_racer, model0, model1, model2, m_aimTarget);
	action->m_level = p_level;
}

// FUNCTION: LEGORACERS 0x0045af80
void RacePowerupManager::FireHomingMissiles(Racer* p_racer, LegoU32 p_level)
{
	for (LegoU32 i = 0; i < 3; i++) {
		HomingMissileAction* action = static_cast<HomingMissileAction*>(m_freeHomingMissileActions);
		if (!action) {
			action = static_cast<HomingMissileAction*>(ReclaimAction(c_brickColorRed, p_level, -1, -1, -1));
		}
		else {
			m_freeHomingMissileActions = action->m_next;
		}

		action->m_next = m_activeActions;
		m_activeActions = action;

		GolAnimatedEntity* model0;
		if (m_worldDatabase->GetAnimatedEntityEntries() == NULL) {
			model0 = NULL;
		}
		else {
			model0 = m_worldDatabase->GetAnimatedEntityByName("dmissil");
		}

		GolAnimatedEntity* model1;
		if (m_worldDatabase->GetAnimatedEntityEntries() == NULL) {
			model1 = NULL;
		}
		else {
			model1 = m_worldDatabase->GetAnimatedEntityByName("dmissil");
		}

		action->Activate(model1, model0, p_racer, i);
		action->m_level = p_level;
	}
}

// FUNCTION: LEGORACERS 0x0045b030
void RacePowerupManager::UseBluePowerup(Racer* p_racer, LegoU32 p_level)
{
	if (25 - m_usedEffectEntityCount >= 2) {
		LegoU32 subtype = p_level;
		ShieldAction* action = static_cast<ShieldAction*>(m_freeShieldActions);
		if (action == NULL) {
			action = static_cast<ShieldAction*>(ReclaimAction(c_brickColorBlue, 0, 1, 2, 3));
		}
		else {
			m_freeShieldActions = action->GetNext();
		}

		action->SetNext(m_activeActions);
		m_activeActions = action;

		GolAnimatedEntity* model;
		GolAnimatedEntity* inputModel;
		switch (subtype) {
		case 0:
			if (m_worldDatabase->GetAnimatedEntityEntries() == NULL) {
				model = NULL;
			}
			else {
				model = m_worldDatabase->GetAnimatedEntityByName("shield0");
			}

			if (m_worldDatabase->GetAnimatedEntityEntries()) {
				inputModel = m_worldDatabase->GetAnimatedEntityByName("shldin0");
			}
			else {
				inputModel = NULL;
			}
			break;
		case 1:
			if (m_worldDatabase->GetAnimatedEntityEntries() == NULL) {
				model = NULL;
			}
			else {
				model = m_worldDatabase->GetAnimatedEntityByName("shield1");
			}

			if (m_worldDatabase->GetAnimatedEntityEntries()) {
				inputModel = m_worldDatabase->GetAnimatedEntityByName("shldin1");
			}
			else {
				inputModel = NULL;
			}
			break;
		case 2:
			if (m_worldDatabase->GetAnimatedEntityEntries() == NULL) {
				model = NULL;
			}
			else {
				model = m_worldDatabase->GetAnimatedEntityByName("shield2");
			}

			if (m_worldDatabase->GetAnimatedEntityEntries()) {
				inputModel = m_worldDatabase->GetAnimatedEntityByName("shldin2");
			}
			else {
				inputModel = NULL;
			}
			break;
		case 3:
			if (m_worldDatabase->GetAnimatedEntityEntries() == NULL) {
				model = NULL;
			}
			else {
				model = m_worldDatabase->GetAnimatedEntityByName("shield3");
			}

			if (m_worldDatabase->GetAnimatedEntityEntries()) {
				inputModel = m_worldDatabase->GetAnimatedEntityByName("shldin3");
			}
			else {
				inputModel = NULL;
			}
			break;
		default:
			model = NULL;
			inputModel = NULL;
			break;
		}

		action->Activate(p_racer, subtype, model, inputModel);
		action->SetLevel(subtype);
	}
}

// FUNCTION: LEGORACERS 0x0045b1e0
void RacePowerupManager::UseGreenPowerup(Racer* p_racer, LegoU32 p_level)
{
	if (p_level == 3) {
		ActivateWarp(p_racer, 3);
	}
	else if (25 - m_usedEffectEntityCount >= 3) {
		TurboAction* action = static_cast<TurboAction*>(m_freeTurboActions);
		if (!action) {
			action = static_cast<TurboAction*>(ReclaimAction(c_brickColorGreen, 0, 1, 2, -1));
		}
		else {
			m_freeTurboActions = action->m_next;
		}

		action->m_next = m_activeActions;
		m_activeActions = action;
		action->Activate(p_racer, p_level);
		action->m_level = p_level;
	}
}

// FUNCTION: LEGORACERS 0x0045b260
LegoU32 RacePowerupManager::ActivateWarp(Racer* p_racer, LegoU32 p_level)
{
	WarpAction* action = static_cast<WarpAction*>(m_freeWarpActions);
	if (!action) {
		action = static_cast<WarpAction*>(ReclaimAction(c_brickColorGreen, p_level, -1, -1, -1));
	}
	else {
		m_freeWarpActions = action->m_next;
	}

	action->m_next = m_activeActions;
	m_activeActions = action;

	GolModelEntity* model;
	if (m_worldDatabase->GetModelEntityEntries() == NULL) {
		model = NULL;
	}
	else {
		model = m_worldDatabase->GetModelEntityByName("warpprt");
	}

	LegoU32 result = action->Activate(p_racer, model, m_aimTarget);
	action->m_level = p_level;
	return result;
}

// FUNCTION: LEGORACERS 0x0045b2e0
PowerupAction* RacePowerupManager::ReclaimAction(
	LegoU32 p_brickColor,
	LegoU32 p_level1,
	LegoS32 p_level2,
	LegoS32 p_level3,
	LegoS32 p_level4
)
{
	PowerupAction* previous = NULL;
	PowerupAction* bestPrevious = NULL;
	PowerupAction* best = NULL;
	LegoS32 bestScore = 0;
	LegoU32 bestPriority = 0xffffffff;

	for (PowerupAction* action = m_activeActions; action != NULL; action = action->GetNext()) {
		if (action->GetBrickColor() == static_cast<LegoS32>(p_brickColor)) {
			LegoU32 subtype = action->GetLevel();
			if (subtype == p_level1 || subtype == static_cast<LegoU32>(p_level2) ||
				subtype == static_cast<LegoU32>(p_level3) || subtype == static_cast<LegoU32>(p_level4)) {
				LegoS32 score = action->GetState();
				if (score > bestScore) {
					bestPriority = action->GetStateTimerMs();
					bestScore = action->GetState();
					best = action;
					bestPrevious = previous;
				}
				else if (score == bestScore) {
					LegoU32 priority = action->GetStateTimerMs();
					if (priority < bestPriority) {
						bestScore = action->GetState();
						bestPriority = priority;
						best = action;
						bestPrevious = previous;
					}
				}
			}
		}

		previous = action;
	}

	if (bestPrevious == NULL) {
		m_activeActions = best->GetNext();
	}
	else {
		bestPrevious->SetNext(best->GetNext());
	}

	best->SetNext(NULL);
	best->Deactivate();

	return best;
}

// STUB: LEGORACERS 0x0045b3a0
PowerupExplosion* __stdcall RacePowerupManager::ReclaimExplosion(PowerupExplosion** p_head)
{
	PowerupExplosion* selected = NULL;
	PowerupExplosion* selectedPrevious = NULL;
	LegoU32 selectedRemaining = 0xffffffff;
	LegoS32 targetState = PowerupExplosion::c_stateScarFading;
	LegoU32 pass = 0;
	PowerupExplosion* current = *p_head;
	PowerupExplosion* head = current;

	for (;;) {
		PowerupExplosion* previous = NULL;

		while (current != NULL) {
			if (current->GetState() == targetState && current->GetRemainingMs() < selectedRemaining) {
				selectedRemaining = current->GetRemainingMs();
				selected = current;
				selectedPrevious = previous;
			}

			previous = current;
			current = current->GetNext();
		}

		if (selected == NULL) {
			current = head;
			targetState = PowerupExplosion::c_stateExploding;
			pass++;
			if (pass < 3) {
				continue;
			}

			PowerupExplosion* result = current;
			*p_head = result->GetNext();
			result->SetNext(NULL);
			return result;
		}

		break;
	}

	if (selectedPrevious == NULL) {
		*p_head = selected->GetNext();
		selected->SetNext(selectedPrevious);
		return selected;
	}

	selectedPrevious->SetNext(selected->GetNext());
	selected->SetNext(NULL);
	return selected;
}

// FUNCTION: LEGORACERS 0x0045b470
void RacePowerupManager::SpawnExplosion(const GolVec3* p_position, undefined4 p_leavesScar, Racer* p_racer)
{
	PowerupExplosion* item = m_freeExplosions;
	if (item == NULL) {
		item = ReclaimExplosion(&m_activeExplosions);
	}
	else {
		m_freeExplosions = item->GetNext();
	}

	item->SetNext(m_activeExplosions);
	m_activeExplosions = item;
	item->Spawn(p_position, p_leavesScar, p_racer);
}

// FUNCTION: LEGORACERS 0x0045b4d0
void RacePowerupManager::FUN_0045b4d0(const GolVec3* p_position, undefined4 p_leavesScar, Racer* p_racer)
{
	SpawnExplosion(p_position, p_leavesScar, p_racer);
}

// FUNCTION: LEGORACERS 0x0045b4f0
void RacePowerupManager::SpawnSpikeExplosion(const GolVec3* p_position, undefined4 p_leavesScar, Racer* p_racer)
{
	PowerupExplosion* item = m_freeSpikeExplosions;
	if (item == NULL) {
		item = ReclaimExplosion(&m_activeSpikeExplosions);
	}
	else {
		m_freeSpikeExplosions = item->GetNext();
	}

	item->SetNext(m_activeSpikeExplosions);
	m_activeSpikeExplosions = item;
	item->Spawn(p_position, p_leavesScar, p_racer);
}

// FUNCTION: LEGORACERS 0x0045b550
void RacePowerupManager::SpawnBrickDebris(const GolVec3* p_position, const GolVec3* p_direction, Racer* p_racer)
{
	GolVec3 position;

	g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
	LegoU32 count = (static_cast<LegoU32>(g_randomTable[g_randomTableIndex]) % c_randomBurstMax) + 1;
	if (count != 0) {
		BrickDebris* brickDebris = &m_brickDebris;
		LegoU32 remaining = count;

		do {
			g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
			position.m_z = 0.0f;
			LegoS32 offsetX = g_randomTable[g_randomTableIndex] % c_randomOffsetRange;
			position.m_x = p_direction->m_x + offsetX * 0.0040000002f - g_unk0x004b02e0;

			g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
			LegoS32 offsetY = g_randomTable[g_randomTableIndex] % c_randomOffsetRange;

			position.m_y = p_direction->m_y + offsetY * 0.0040000002f - g_unk0x004b02e0;
			brickDebris->Spawn(p_position, &position, p_racer);
		} while (--remaining != 0);
	}
}

// FUNCTION: LEGORACERS 0x0045b640
void RacePowerupManager::CancelShield(Racer* p_racer)
{
	for (LegoU32 i = 0; i < m_actionPoolCounts[8]; i++) {
		ShieldAction* action = &m_shieldActions[i];
		if (action->GetState() > 1 && action->m_racer == p_racer) {
			action->SetState(6);
		}
	}
}

// FUNCTION: LEGORACERS 0x0045b690 FOLDED
void RacePowerupManager::CancelTurbo(Racer* p_racer)
{
	for (LegoU32 i = 0; i < m_actionPoolCounts[9]; i++) {
		if (m_turboActions[i].m_state > 1 && m_turboActions[i].m_racer == p_racer) {
			m_turboActions[i].m_state = 6;
			m_turboActions[i].m_racer = NULL;
		}
	}
}

// FUNCTION: LEGORACERS 0x0045b6f0
void RacePowerupManager::CancelMagnetHold(Racer* p_racer)
{
	for (LegoU32 i = 0; i < m_actionPoolCounts[0]; i++) {
		MagnetAction* action = &m_magnetActions[i];
		if (action->GetState() > 1 && action->m_heldRacer == p_racer) {
			action->SetState(MagnetAction::c_stateDone);
		}
	}
}

// FUNCTION: LEGORACERS 0x0045b740
void RacePowerupManager::CancelWarp(Racer* p_racer)
{
	for (LegoU32 i = 0; i < m_actionPoolCounts[10]; i++) {
		WarpAction* item = &m_warpActions[i];
		if (item->m_racer == p_racer) {
			if (item->m_state == WarpAction::c_stateStarting) {
				item->m_state = WarpAction::c_stateDone;
			}
			else if (item->m_state == WarpAction::c_stateActive) {
				item->m_stateTimerMs = 0;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x0045b7a0
void RacePowerupManager::UpdateProjectileSound(SpatialSoundInstance* p_sound, LegoU32 p_level, LegoS32 p_state)
{
	Racer* racer = m_raceState->GetCurrentRacer();
	if (racer == NULL) {
		if (p_sound->IsPlaying()) {
			p_sound->Stop();
		}
		return;
	}

	WeaponActionBase* nearest = NULL;
	LegoFloat nearestDistanceSquared = FLT_MAX;
	SoundVector referencePosition;
	GolVec3 position;
	GolVec3 direction;

	racer->m_visuals.GetCarEntity()->GetPosition(&referencePosition);

	for (PowerupAction* node = m_activeActions; node != NULL; node = node->GetNext()) {
		if (node->GetBrickColor() == 1 && node->GetLevel() == p_level && node->GetState() == p_state) {
			WeaponActionBase* resource = static_cast<WeaponActionBase*>(node);
			resource->GetProjectilePosition(&position);

			LegoFloat dx = referencePosition.m_x - position.m_x;
			LegoFloat dy = referencePosition.m_y - position.m_y;
			LegoFloat dz = referencePosition.m_z - position.m_z;
			LegoFloat distanceSquared = dz * dz + dy * dy + dx * dx;
			if (distanceSquared < nearestDistanceSquared) {
				nearestDistanceSquared = distanceSquared;
				nearest = resource;
			}
		}
	}

	if (nearestDistanceSquared < g_projectileSoundRangeSquared) {
		if (!p_sound->IsPlaying()) {
			p_sound->Play(TRUE);
		}

		nearest->GetProjectilePosition(&referencePosition);
		nearest->GetProjectileVelocity(&direction);

		p_sound->m_position = referencePosition;
		p_sound->m_velocity.m_x = direction.m_x;
		p_sound->m_velocity.m_y = direction.m_y;
		p_sound->m_velocity.m_z = direction.m_z;
	}
	else if (p_sound->IsPlaying()) {
		p_sound->Stop();
	}
}

// FUNCTION: LEGORACERS 0x0045b900
void RacePowerupManager::SetBricksAudible()
{
	LegoU32 i;

	for (i = 0; i < m_colorBrickCount; i++) {
		m_colorBricks[i].SetAudible();
	}

	for (i = 0; i < m_whiteBrickCount; i++) {
		m_whiteBricks[i].SetAudible();
	}
}

// FUNCTION: LEGORACERS 0x0045b950
void RacePowerupManager::ClearBricksAudible()
{
	LegoU32 i;

	for (i = 0; i < m_colorBrickCount; i++) {
		m_colorBricks[i].ClearAudible();
	}

	for (i = 0; i < m_whiteBrickCount; i++) {
		m_whiteBricks[i].ClearAudible();
	}
}

// FUNCTION: LEGORACERS 0x0045b9a0
LegoBool32 RacePowerupManager::IsProjectileEntity(GolWorldEntity* p_entity)
{
	PowerupAction* node = m_activeActions;
	while (node != NULL) {
		if (node->GetBrickColor() == 1 &&
			static_cast<WeaponActionBase*>(node)->GetProjectileWorldEntity() == p_entity) {
			break;
		}

		node = node->GetNext();
	}

	if (node == NULL) {
		return FALSE;
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0045b9e0 FOLDED
GolAnimatedEntity* RacePowerupManager::AllocateEffectEntity()
{
	LegoU32 index = 0;
	LegoU32 flags = m_effectEntityUsedMask;
	LegoU32 count = m_usedEffectEntityCount;

	if (count == sizeOfArray(m_effectEntities)) {
		return NULL;
	}

	for (; flags & 1; index++) {
		if (index >= sizeOfArray(m_effectEntities)) {
			break;
		}

		flags >>= 1;
	}

	m_effectEntityUsedMask |= 1 << index;
	m_usedEffectEntityCount = count + 1;
	return &m_effectEntities[index];
}

// FUNCTION: LEGORACERS 0x0045ba40 FOLDED
LegoU32 RacePowerupManager::ReleaseEffectEntity(GolAnimatedEntity* p_entity)
{
	LegoS32 index = p_entity - m_effectEntities;

	m_effectEntityUsedMask &= ~(1 << index);
	m_usedEffectEntityCount--;

	return m_usedEffectEntityCount;
}

// FUNCTION: LEGORACERS 0x0045ba90
GolMaterial* RacePowerupManager::GetBrickMaterial(LegoU32* p_brickColor)
{
	switch (*p_brickColor) {
	case c_brickColorRed:
		return m_brickMaterials[c_brickMaterialRed];
	case c_brickColorBlue:
		return m_brickMaterials[c_brickMaterialBlue];
	case c_brickColorGreen:
		return m_brickMaterials[c_brickMaterialGreen];
	case c_brickColorYellow:
		return m_brickMaterials[c_brickMaterialYellow];
	default:
		return NULL;
	}
}

// FUNCTION: LEGORACERS 0x0045bae0
GolMaterial* RacePowerupManager::GetTrailMaterial(LegoU32* p_brickColor)
{
	switch (*p_brickColor) {
	case c_brickColorRed:
		return m_brickMaterials[c_trailMaterialRed];
	case c_brickColorBlue:
		return m_brickMaterials[c_trailMaterialBlue];
	case c_brickColorGreen:
		return m_brickMaterials[c_trailMaterialGreen];
	case c_brickColorYellow:
		return m_brickMaterials[c_trailMaterialYellow];
	default:
		return NULL;
	}
}

// FUNCTION: LEGORACERS 0x0045bb30
void RacePowerupManager::ResetEffects()
{
	LegoU32 i;

	for (i = 0; i < m_colorBrickCount; i++) {
		m_colorBricks[i].Respawn();
	}

	for (i = 0; i < m_whiteBrickCount; i++) {
		m_whiteBricks[i].Respawn();
	}

	PowerupExplosion* explosion = m_activeExplosions;
	while (explosion != NULL) {
		explosion->Deactivate();
		explosion = explosion->GetNext();
	}

	PowerupExplosion* spikeExplosion = m_activeSpikeExplosions;
	while (spikeExplosion != NULL) {
		spikeExplosion->Deactivate();
		spikeExplosion = spikeExplosion->GetNext();
	}

	m_brickDebris.ReleaseAll();

	PowerupAction* action = m_activeActions;
	while (action != NULL) {
		action->SetState(6);
		action = action->GetNext();
	}

	Update(0);
}
