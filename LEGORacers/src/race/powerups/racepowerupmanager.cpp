#include "audio/spatialsoundinstance.h"
#include "cmbmodelpart0x34.h"
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
DECOMP_SIZE_ASSERT(RacePowerupManager::Field0x54, 0x04)
DECOMP_SIZE_ASSERT(RacePowerupManager::PickupBrick, 0x54)
DECOMP_SIZE_ASSERT(RacePowerupManager::ColorBrick, 0x68)
DECOMP_SIZE_ASSERT(RacePowerupManager::WhiteBrick, 0x68)
DECOMP_SIZE_ASSERT(RacePowerupManager::PwbTxtParser, 0x1fc)
DECOMP_SIZE_ASSERT(RacePowerupManager::Field0x1958Resource, 0x30)
DECOMP_SIZE_ASSERT(RacePowerupManager::Field0x18bc, 0x80)
DECOMP_SIZE_ASSERT(RacePowerupManager::Field0x18bc::Entry, 0x14)
DECOMP_SIZE_ASSERT(RacePowerupManager::Field0x050::Entry, 0x14)
DECOMP_SIZE_ASSERT(RacePowerupManager::MagnetAction, 0x84)
DECOMP_SIZE_ASSERT(RacePowerupManager::OilSlickAction, 0x190)
DECOMP_SIZE_ASSERT(RacePowerupManager::DynamiteAction, 0x17c)
DECOMP_SIZE_ASSERT(RacePowerupManager::CurseAction, 0x68)
DECOMP_SIZE_ASSERT(RacePowerupManager::PowerupActionBase, 0x18)
DECOMP_SIZE_ASSERT(RacePowerupManager::HazardActionBase, 0x2c)
DECOMP_SIZE_ASSERT(RacePowerupManager::WeaponActionBase, 0x30)
DECOMP_SIZE_ASSERT(RacePowerupManager::CannonballAction, 0xe8)
DECOMP_SIZE_ASSERT(RacePowerupManager::GrapplingHookAction, 0x290)
DECOMP_SIZE_ASSERT(RacePowerupManager::LightningAction, 0x24c)
DECOMP_SIZE_ASSERT(RacePowerupManager::HomingMissileAction, 0x224)
DECOMP_SIZE_ASSERT(RacePowerupManager::ShieldAction, 0x2c)
DECOMP_SIZE_ASSERT(RacePowerupManager::TurboAction, 0x34)
DECOMP_SIZE_ASSERT(RacePowerupManager::WarpAction, 0xe4)
DECOMP_SIZE_ASSERT(RacePowerupManager::PowerupAction, 0x18)

extern LegoU16 g_unk0x004befec[1024];
extern LegoU32 g_unk0x004c6ee4;
extern const LegoFloat g_unk0x004b02e0;
extern const LegoFloat g_unk0x004b1840;
extern const LegoFloat g_unk0x004b1844;
extern const LegoFloat g_unk0x004b1848;
extern const LegoFloat g_unk0x004b184c;
extern const LegoFloat g_unk0x004b1850;
extern const LegoFloat g_unk0x004b1854;
extern const LegoFloat g_unk0x004b1858;
extern const LegoFloat g_unk0x004b185c;
extern const LegoFloat g_unk0x004b1860;
extern const LegoFloat g_unk0x004b1864;
extern const LegoFloat g_unk0x004b1868;
extern const LegoFloat g_unk0x004b186c;

// GLOBAL: LEGORACERS 0x004b183c
extern const LegoFloat g_unk0x004b183c = 200.0f;

// GLOBAL: LEGORACERS 0x004b1870
extern const LegoFloat g_unk0x004b1870 = 500.0f;

// GLOBAL: LEGORACERS 0x004b1874
extern const LegoFloat g_unk0x004b1874 = 0.0040000002f;

// GLOBAL: LEGORACERS 0x004b1878
extern const LegoFloat g_unk0x004b1878 = 6.2831855f;

// GLOBAL: LEGORACERS 0x004c7644
LegoFloat g_unk0x004c7644 = g_unk0x004b1870 * g_unk0x004b1870;

// FUNCTION: LEGORACERS 0x00451350
RacePowerupManager::PowerupActionBase::PowerupActionBase()
{
	m_state = 0;
	m_stateTimerMs = 0;
	m_next = NULL;
	m_soundSource = NULL;
	m_level = 0;
}

// FUNCTION: LEGORACERS 0x00451370
RacePowerupManager::PowerupAction* RacePowerupManager::PowerupActionBase::Destroy(undefined4 p_flags)
{
	PowerupActionBase* result = this;
	this->~PowerupActionBase();
	if (p_flags & 1) {
		::operator delete(result);
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00451390
RacePowerupManager::PowerupActionBase::~PowerupActionBase()
{
}

// FUNCTION: LEGORACERS 0x004513a0 FOLDED
void RacePowerupManager::PowerupActionBase::Update(LegoU32 p_elapsedMs)
{
	if (p_elapsedMs >= m_stateTimerMs) {
		m_stateTimerMs = 0;
		VTable0x14();
	}
	else {
		m_stateTimerMs -= p_elapsedMs;
	}
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RacePowerupManager::PowerupActionBase::VTable0x00(LegoEventQueue::CallbackData*)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RacePowerupManager::PowerupActionBase::VTable0x0c(GolD3DRenderDevice*)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RacePowerupManager::PowerupActionBase::VTable0x10(GolD3DRenderDevice*)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RacePowerupManager::PowerupActionBase::VTable0x14()
{
}

// FUNCTION: LEGORACERS 0x0044e7e0 FOLDED
LegoS32 RacePowerupManager::PowerupActionBase::GetBrickColor()
{
	return 0;
}

void RacePowerupManager::HazardActionBase::VTable0x14()
{
}

void RacePowerupManager::WeaponActionBase::VTable0x14()
{
}

// FUNCTION: LEGORACERS 0x0044f580 FOLDED
LegoS32 RacePowerupManager::TurboAction::GetBrickColor()
{
	return c_brickColorGreen;
}

// FUNCTION: LEGORACERS 0x0044f580 FOLDED
LegoS32 RacePowerupManager::WarpAction::GetBrickColor()
{
	return c_brickColorGreen;
}

// FUNCTION: LEGORACERS 0x004513e0 FOLDED
void RacePowerupManager::PowerupActionBase::Deactivate()
{
	m_state = 1;
}

void RacePowerupManager::HazardActionBase::OnHitRacer(RaceState::Racer*)
{
}

void RacePowerupManager::WeaponActionBase::OnHitRacer(RaceState::Racer*)
{
}

// FUNCTION: LEGORACERS 0x004513f0
RacePowerupManager::Field0x18bc::Entry::Entry()
{
	m_unk0x0c = 0;
	m_unk0x10 = 0;
}

// FUNCTION: LEGORACERS 0x00451410
RacePowerupManager::Field0x18bc::Entry::~Entry()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00451460
void RacePowerupManager::Field0x18bc::Entry::Reset()
{
	m_unk0x00.Clear();
	m_unk0x0c = 0;
	m_unk0x10 = 0;
}

// FUNCTION: LEGORACERS 0x00451480
void RacePowerupManager::Field0x18bc::Entry::FUN_00451480(GolD3DRenderDevice* p_renderer)
{
	if (m_unk0x10) {
		Reset();
	}

	m_unk0x00.Initialize(p_renderer, 1);
	m_unk0x10 = 1;
}

// FUNCTION: LEGORACERS 0x004514b0
void RacePowerupManager::Field0x18bc::Entry::FUN_004514b0(
	GolAnimatedEntity* p_sourceEntity,
	GolAnimatedEntity* p_entity,
	const GolVec3* p_position,
	const GolVec3* p_direction,
	LegoU32 p_partIndex,
	void* p_billboardPosition
)
{
	m_unk0x0c = p_entity;
	m_unk0x0c->FUN_0040d550(
		p_sourceEntity->GetModel(0),
		p_sourceEntity->VTable0x58(0),
		p_sourceEntity->GetModelPart(0),
		p_sourceEntity->GetModelDistance(0)
	);

	LegoU32 i;
	for (i = 1; i < 3; i++) {
		if (p_sourceEntity->GetModel(i)) {
			m_unk0x0c->FUN_10023940(
				p_sourceEntity->GetModel(i),
				p_sourceEntity->VTable0x58(i),
				p_sourceEntity->GetModelPart(i),
				p_sourceEntity->GetModelDistance(i)
			);
		}
	}

	p_partIndex %= p_sourceEntity->GetModelPart(0)->GetPartCount();
	m_unk0x0c->FUN_0040dad0(p_partIndex);

	LegoU32 flags = m_unk0x0c->GetFlags();
	flags |= GolAnimatedEntity::c_flagPartAnimation;
	m_unk0x0c->SetFlags(flags);

	flags = m_unk0x0c->GetFlags();
	flags &= ~GolAnimatedEntity::c_flagLoopCurrentPart;
	m_unk0x0c->SetFlags(flags);

	if (p_billboardPosition) {
		m_unk0x00.SetPosition(0, p_billboardPosition);
		m_unk0x0c->SetPrimaryMaterialTable(&m_unk0x00);
	}

	GolVec3 up;
	up.m_x = 0.0f;
	up.m_y = 0.0f;
	up.m_z = 1.0f;
	m_unk0x0c->VTable0x08(*p_position);
	m_unk0x0c->VTable0x40(*p_direction, up);
	m_unk0x10 = 2;
}

// FUNCTION: LEGORACERS 0x004515d0
void RacePowerupManager::Field0x18bc::Entry::FUN_004515d0(LegoU32 p_elapsedMs)
{
	if (m_unk0x10 == 2) {
		m_unk0x0c->VTable0x10(p_elapsedMs);
		if (m_unk0x0c->FUN_0040e360()) {
			m_unk0x0c->VTable0x54();
			m_unk0x10 = 3;
		}
	}
}

// FUNCTION: LEGORACERS 0x00451610
void RacePowerupManager::Field0x18bc::Entry::FUN_00451610(GolD3DRenderDevice* p_renderer)
{
	if (m_unk0x10 == 2) {
		p_renderer->VTable0x94(m_unk0x0c);
	}
}

// FUNCTION: LEGORACERS 0x00451630
void RacePowerupManager::Field0x18bc::Entry::FUN_00451630()
{
	m_unk0x0c = NULL;
	m_unk0x10 = 1;
}

// FUNCTION: LEGORACERS 0x00451640
RacePowerupManager::Field0x18bc::Field0x18bc()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004516a0
RacePowerupManager::Field0x18bc::~Field0x18bc()
{
	FUN_00451700();
}

// FUNCTION: LEGORACERS 0x00451700
LegoS32 RacePowerupManager::Field0x18bc::FUN_00451700()
{
	LegoS32 i;

	for (i = 0; i < sizeOfArray(m_entries); i++) {
		m_entries[i].Reset();
	}

	return Reset();
}

// FUNCTION: LEGORACERS 0x00451730
LegoS32 RacePowerupManager::Field0x18bc::Reset()
{
	m_brickModels[0] = NULL;
	m_brickModels[1] = NULL;
	m_brickModels[2] = NULL;
	m_brickModels[3] = NULL;
	m_unk0x74 = 0;
	m_unk0x78 = 0;
	m_unk0x7c = 0;

	return 0;
}

// FUNCTION: LEGORACERS 0x00451750
void RacePowerupManager::Field0x18bc::FUN_00451750(RacePowerupManager* p_unk0x04, GolD3DRenderDevice* p_renderer)
{
	if (m_unk0x74) {
		FUN_00451700();
	}

	m_unk0x74 = p_unk0x04;

	const LegoChar* name = "brick1\0\0brick2\0\0brick3\0\0brick4\0";
	const LegoChar* endName = name + (sizeof(GolName) * 4);
	GolAnimatedEntity** entity = m_brickModels;
	GolWorldDatabase* worldDatabase = p_unk0x04->m_unk0x05c;

	while (name < endName) {
		GolAnimatedEntity* model;
		if (worldDatabase->GetUnk0xc0NameEntries() == NULL) {
			model = NULL;
		}
		else {
			model = worldDatabase->GetUnk0xc0Name(name);
		}
		*entity = model;

		name += sizeof(GolName);
		entity++;
	}

	Entry* entry = m_entries;
	LegoS32 i;
	for (i = 5; i != 0; i--) {
		entry->FUN_00451480(p_renderer);
		entry++;
	}
}

// FUNCTION: LEGORACERS 0x004517c0
void RacePowerupManager::Field0x18bc::FUN_004517c0(
	const GolVec3* p_position,
	const GolVec3* p_direction,
	RaceState::Racer* p_racer
)
{
	DuskwindBananaRelic0x24* material;
	material = NULL;
	LegoS32 entryIndex;

	entryIndex = 0;
	while (TRUE) {
		if (m_entries[entryIndex].m_unk0x10 != 2) {
			break;
		}

		entryIndex++;
		if (entryIndex >= sizeOfArray(m_entries)) {
			break;
		}
	}

	if (entryIndex != sizeOfArray(m_entries)) {
		GolAnimatedEntity* entity = m_unk0x74->AllocateEffectEntity();
		if (entity) {
			LegoU32 sourceIndex = m_unk0x78;
			m_unk0x78 = sourceIndex + 1;
			if (m_unk0x78 == 4) {
				m_unk0x78 = 0;
			}

			if (p_racer) {
				material = m_unk0x74->m_raceState->GetMaterialLibrary()->GetItem(p_racer->m_unk0xe04);
			}

			m_entries[entryIndex]
				.FUN_004514b0(m_brickModels[sourceIndex], entity, p_position, p_direction, m_unk0x7c, material);
			m_unk0x7c++;
		}
	}
}

// FUNCTION: LEGORACERS 0x00451860
void RacePowerupManager::Field0x18bc::FUN_00451860(LegoU32 p_elapsedMs)
{
	Entry* entry = m_entries;
	LegoS32 i;

	for (i = 5; i != 0; i--) {
		entry->FUN_004515d0(p_elapsedMs);
		if (entry->GetUnk0x10() == 3) {
			m_unk0x74->ReleaseEffectEntity(entry->GetUnk0x0c());
			entry->FUN_00451630();
		}

		entry++;
	}
}

// FUNCTION: LEGORACERS 0x004518a0
void RacePowerupManager::Field0x18bc::FUN_004518a0(GolD3DRenderDevice* p_renderer)
{
	Entry* entry = m_entries;
	LegoS32 i;

	for (i = 5; i != 0; i--) {
		entry->FUN_00451610(p_renderer);
		entry++;
	}
}

// FUNCTION: LEGORACERS 0x004518d0
void RacePowerupManager::Field0x18bc::FUN_004518d0()
{
	Entry* entry = m_entries;
	LegoS32 i;

	for (i = 5; i != 0; i--) {
		entry->FUN_00451630();
		entry++;
	}
}

// FUNCTION: LEGORACERS 0x00457990
RacePowerupManager::RacePowerupManager()
{
	FUN_00457a90();
}

// FUNCTION: LEGORACERS 0x00457a20
RacePowerupManager::~RacePowerupManager()
{
	FUN_00459e20();
}

// FUNCTION: LEGORACERS 0x00457a90
void RacePowerupManager::FUN_00457a90()
{
	m_golExport = 0;
	m_renderer = NULL;
	m_colorBricks = NULL;
	m_brickEvents = NULL;
	m_colorBrickCount = 0;
	m_whiteBricks = NULL;
	m_whiteBrickCount = 0;
	m_raceState = NULL;
	m_unk0x068 = 0;
	m_unk0x06c = 0;
	m_soundSource = 0;
	m_unk0x040 = 0;
	m_unk0x1958 = 0;
	m_unk0x195c = 0;
	m_unk0x1960 = 0;
	m_unk0x1964 = 0;
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
	m_unk0x199c = 0;
	m_unk0x19a0 = 0;
	m_unk0x064 = 0;
	m_unk0x070 = 0;
	m_unk0x048 = 0;
	m_unk0x060 = 0;
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
	m_unk0x04c = 0;
	m_unk0x050 = 0;
	m_unk0x1878 = 0;
	m_usedEffectEntityCount = 0;
	m_cameraFov = 0;
	m_brickModel = 0;
	m_brickBlendModel = 0;
	m_unk0x1970 = 0;
	m_unk0x1974 = 0;

	DuskwindBananaRelic0x24** entry = m_brickMaterials;
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
		FUN_00459e20();
	}

	m_golExport = p_params->m_golExport;
	m_renderer = p_params->m_renderer;
	m_raceState = p_params->m_raceState;
	m_unk0x06c = p_params->m_unk0x0c;
	m_unk0x070 = p_params->m_unk0x10;
	m_unk0x068 = p_params->m_unk0x14;
	m_soundSource = p_params->m_unk0x18;
	m_cutsceneAnimation0x040 = p_params->m_unk0x1c;
	m_trailManager = p_params->m_trailManager;
	m_unk0x060 = p_params->m_unk0x2c;
	m_unk0x048 = p_params->m_unk0x24;
	m_unk0x04c = p_params->m_unk0x28;
	m_unk0x050 = p_params->m_unk0x30;
	m_cameraFov = p_params->m_cameraFov;
	m_unk0x058 = p_params->m_unk0x38;
}

// FUNCTION: LEGORACERS 0x00457c90
void RacePowerupManager::FUN_00457c90(const LegoChar* p_unk0x04, const LegoChar* p_unk0x08, LegoBool32 p_binary)
{
	m_unk0x05c = m_golExport->VTable0x08();
	m_unk0x05c->VTable0x14(m_renderer, p_unk0x04, p_binary, 1.0f);
	m_unk0x014.VTable0x04(m_renderer, p_unk0x08, p_binary);
	m_unk0x064 = m_golExport->VTable0x08();
	m_unk0x064->VTable0x14(m_renderer, "turbo3", p_binary, 1.0f);
}

// FUNCTION: LEGORACERS 0x00457cf0
void RacePowerupManager::FUN_00457cf0(LegoBool32 p_unk0x04)
{
	FUN_00457d30(p_unk0x04);
	m_unk0x008.Initialize(m_renderer, m_actionPoolCounts[5] + m_actionPoolCounts[0]);
	m_unk0x18bc.FUN_00451750(this, m_renderer);
}

// FUNCTION: LEGORACERS 0x00457d30
void RacePowerupManager::FUN_00457d30(LegoBool32 p_mirror)
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

	m_explosionPool = new Explosion[m_explosionPoolCount];
	if (!m_explosionPool) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_spikeExplosionPool = new Explosion[m_spikeExplosionPoolCount];
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
void RacePowerupManager::FUN_00458940()
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
	FUN_0045a340();
	FUN_004590f0();
	CreateExplosionPools();

	m_sound0x1958 = m_soundSource->AcquireSoundById(7);
	if (m_sound0x1958 != NULL) {
		m_sound0x1958->SetDistanceRangeWithMinSquared(g_unk0x004b183c * g_unk0x004b183c, g_unk0x004b1870);
	}

	m_sound0x195c = m_soundSource->AcquireSoundById(0x34);
	if (m_sound0x195c != NULL) {
		m_sound0x195c->SetDistanceRangeWithMinSquared(g_unk0x004b183c * g_unk0x004b183c, g_unk0x004b1870);
	}

	m_sound0x1960 = m_soundSource->AcquireSoundById(0x17);
	if (m_sound0x1960 != NULL) {
		m_sound0x1960->SetDistanceRangeWithMinSquared(g_unk0x004b183c * g_unk0x004b183c, g_unk0x004b1870);
	}

	m_sound0x1964 = m_soundSource->AcquireSoundById(0x13);
	if (m_sound0x1964 != NULL) {
		m_sound0x1964->SetDistanceRangeWithMinSquared(g_unk0x004b183c * g_unk0x004b183c, g_unk0x004b1870);
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

	m_brickModel = m_unk0x05c->FindUnk0xc0("gen");
	m_brickBlendModel = m_unk0x05c->FindUnk0xc0("genblen");
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
			case GolFileParser::e_unknown0x30:
				p_parser->ReadStringWithMaxLength(sizeof(GolName));
				// Intentional fall-through: the original consumes the following integer too.
			case GolFileParser::e_unknown0x31:
				p_parser->ReadInteger();
				break;
			default:
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}

			token = p_parser->GetNextToken();
		}

		if (!(m_unk0x058 & 0x44)) {
			if (m_unk0x058 & 8) {
				state = 4;
			}
			else if (m_unk0x058 & 0x10) {
				state = i * sizeof(ColorBrick);
			}
		}
		else {
			state = 1;
		}

		if (p_mirror) {
			position.m_y = -position.m_y;
		}

		DuskwindBananaRelic0x24* material0 = GetBrickMaterial(&state);
		DuskwindBananaRelic0x24* material1 = GetTrailMaterial(&state);
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

	m_unk0x1970 = m_unk0x05c->FindUnk0xc0("enh");
	m_unk0x1974 = m_unk0x05c->FindUnk0xc0("enhblen");

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
			case GolFileParser::e_unknown0x30:
				p_parser->ReadStringWithMaxLength(sizeof(GolName));
				// Intentional fall-through: the original consumes the following integer too.
			case GolFileParser::e_unknown0x31:
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

		m_whiteBricks[i].Initialize(this, m_soundSource, &position, m_unk0x1970, m_unk0x1974);
		m_whiteBricks[i].CaptureHomePosition();
	}

	if (p_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_rightCurly);
	}
}

// FUNCTION: LEGORACERS 0x004590f0
void RacePowerupManager::FUN_004590f0()
{
	LegoU8 i = 0;

	if (m_actionPoolCounts[0] - 1 > 0) {
		do {
			m_magnetActions[i].SetNext(&m_magnetActions[i + 1]);
			m_magnetActions[i].Initialize(
				this,
				m_raceState,
				m_unk0x068,
				m_unk0x040,
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
		m_unk0x068,
		m_unk0x040,
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
				m_unk0x06c,
				m_unk0x068,
				m_cutsceneAnimation0x040,
				m_renderer,
				m_golExport
			);
			m_oilSlickActions[i].SetSoundSource(m_soundSource);
			i++;
		} while (i < m_actionPoolCounts[1] - 1);
	}

	m_oilSlickActions[m_actionPoolCounts[1] - 1].SetNext(NULL);
	m_oilSlickActions[m_actionPoolCounts[1] - 1]
		.Initialize(this, m_raceState, m_unk0x06c, m_unk0x068, m_cutsceneAnimation0x040, m_renderer, m_golExport);
	m_oilSlickActions[m_actionPoolCounts[1] - 1].SetSoundSource(m_soundSource);
	m_freeOilSlickActions = m_oilSlickActions;

	i = 0;
	if (m_actionPoolCounts[2] - 1 > 0) {
		do {
			m_dynamiteActions[i].SetNext(&m_dynamiteActions[i + 1]);
			m_dynamiteActions[i]
				.Initialize(m_raceState, m_unk0x068, this, m_unk0x040, m_unk0x05c->FindUnk0xb4("barrel"));
			m_dynamiteActions[i].SetSoundSource(m_soundSource);
			i++;
		} while (i < m_actionPoolCounts[2] - 1);
	}

	m_dynamiteActions[m_actionPoolCounts[2] - 1].SetNext(NULL);
	m_dynamiteActions[m_actionPoolCounts[2] - 1]
		.Initialize(m_raceState, m_unk0x068, this, m_unk0x040, m_unk0x05c->FindUnk0xb4("barrel"));
	m_dynamiteActions[m_actionPoolCounts[2] - 1].SetSoundSource(m_soundSource);
	m_freeDynamiteActions = m_dynamiteActions;

	i = 0;
	if (m_actionPoolCounts[3] - 1 > 0) {
		do {
			m_curseActions[i].SetNext(&m_curseActions[i + 1]);
			m_curseActions[i].Initialize(m_raceState, m_unk0x068, this);
			m_curseActions[i].SetSoundSource(m_soundSource);
			i++;
		} while (i < m_actionPoolCounts[3] - 1);
	}

	m_curseActions[m_actionPoolCounts[3] - 1].SetNext(NULL);
	m_curseActions[m_actionPoolCounts[3] - 1].Initialize(m_raceState, m_unk0x068, this);
	m_curseActions[m_actionPoolCounts[3] - 1].SetSoundSource(m_soundSource);
	m_freeCurseActions = m_curseActions;

	i = 0;
	if (m_actionPoolCounts[4] - 1 > 0) {
		do {
			m_cannonballActions[i].SetNext(&m_cannonballActions[i + 1]);
			m_cannonballActions[i].Initialize(&m_golExport, m_unk0x068);
			m_cannonballActions[i].SetSoundSource(m_soundSource);
			i++;
		} while (i < m_actionPoolCounts[4] - 1);
	}

	m_cannonballActions[m_actionPoolCounts[4] - 1].SetNext(NULL);
	m_cannonballActions[m_actionPoolCounts[4] - 1].Initialize(&m_golExport, m_unk0x068);
	m_cannonballActions[m_actionPoolCounts[4] - 1].SetSoundSource(m_soundSource);
	m_freeCannonballActions = m_cannonballActions;

	i = 0;
	if (m_actionPoolCounts[5] - 1 > 0) {
		do {
			m_grapplingHookActions[i].SetNext(&m_grapplingHookActions[i + 1]);
			m_grapplingHookActions[i].Initialize(this, m_unk0x068, i);
			m_grapplingHookActions[i].SetSoundSource(m_soundSource);
			i++;
		} while (i < m_actionPoolCounts[5] - 1);
	}

	m_grapplingHookActions[m_actionPoolCounts[5] - 1].SetNext(NULL);
	m_grapplingHookActions[m_actionPoolCounts[5] - 1].Initialize(this, m_unk0x068, m_actionPoolCounts[5] - 1);
	m_grapplingHookActions[m_actionPoolCounts[5] - 1].SetSoundSource(m_soundSource);
	m_freeGrapplingHookActions = m_grapplingHookActions;

	i = 0;
	if (m_actionPoolCounts[6] - 1 > 0) {
		do {
			m_lightningActions[i].SetNext(&m_lightningActions[i + 1]);
			m_lightningActions[i].Initialize(m_golExport, this);
			m_lightningActions[i].SetSoundSource(m_soundSource);
			m_lightningActions[i].FUN_00454a70();
			i++;
		} while (i < m_actionPoolCounts[6] - 1);
	}

	m_lightningActions[m_actionPoolCounts[6] - 1].SetNext(NULL);
	m_lightningActions[m_actionPoolCounts[6] - 1].Initialize(m_golExport, this);
	m_lightningActions[m_actionPoolCounts[6] - 1].SetSoundSource(m_soundSource);
	m_lightningActions[m_actionPoolCounts[6] - 1].FUN_00454a70();
	m_freeLightningActions = m_lightningActions;

	i = 0;
	if (m_actionPoolCounts[7] - 1 > 0) {
		do {
			m_homingMissileActions[i].SetNext(&m_homingMissileActions[i + 1]);
			m_homingMissileActions[i].Initialize(&m_golExport, m_unk0x068);
			m_homingMissileActions[i].SetSoundSource(m_soundSource);
			i++;
		} while (i < m_actionPoolCounts[7] - 1);
	}

	m_homingMissileActions[m_actionPoolCounts[7] - 1].SetNext(NULL);
	m_homingMissileActions[m_actionPoolCounts[7] - 1].Initialize(&m_golExport, m_unk0x068);
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
			m_turboActions[i].Initialize(this, m_cutsceneAnimation0x040);
			m_turboActions[i].SetSoundSource(m_soundSource);
			i++;
		} while (i < m_actionPoolCounts[9] - 1);
	}

	m_turboActions[m_actionPoolCounts[9] - 1].SetNext(NULL);
	m_turboActions[m_actionPoolCounts[9] - 1].Initialize(this, m_cutsceneAnimation0x040);
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
	Explosion::Params params;
	params.m_golExport = m_golExport;
	params.m_collidable = m_unk0x06c;
	params.m_model = m_unk0x05c->FindUnk0xb4("Explsn");
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
	params.m_model = m_unk0x05c->FindUnk0xb4("spikexp");
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
void RacePowerupManager::FUN_00459e20()
{
	if (m_unk0x1964 != NULL) {
		m_soundSource->FUN_00443c10(m_unk0x1964);
		m_unk0x1964 = NULL;
	}

	if (m_unk0x1960 != NULL) {
		m_soundSource->FUN_00443c10(m_unk0x1960);
		m_unk0x1960 = NULL;
	}

	if (m_unk0x195c != NULL) {
		m_soundSource->FUN_00443c10(m_unk0x195c);
		m_unk0x195c = NULL;
	}

	if (m_unk0x1958 != NULL) {
		m_soundSource->FUN_00443c10(m_unk0x1958);
		m_unk0x1958 = NULL;
	}

	m_unk0x008.Clear();

	if (m_spikeExplosionPool != NULL) {
		LegoU32 i;

		for (i = 0; i < m_spikeExplosionPoolCount; i++) {
			m_spikeExplosionPool[i].Destroy();
		}

		if (m_spikeExplosionPool != NULL) {
			m_spikeExplosionPool->Destroy(3);
		}
		m_spikeExplosionPool = NULL;
	}

	if (m_explosionPool != NULL) {
		LegoU32 i;

		for (i = 0; i < m_explosionPoolCount; i++) {
			m_explosionPool[i].Destroy();
		}

		if (m_explosionPool != NULL) {
			m_explosionPool->Destroy(3);
		}
		m_explosionPool = NULL;
	}

	if (m_warpActions != NULL) {
		LegoU32 i;

		for (i = 0; i < m_actionPoolCounts[10]; i++) {
			m_warpActions[i].FUN_0045d540();
		}

		if (m_warpActions != NULL) {
			m_warpActions->Destroy(3);
		}
		m_warpActions = NULL;
	}

	if (m_turboActions != NULL) {
		LegoU32 i;

		for (i = 0; i < m_actionPoolCounts[9]; i++) {
			m_turboActions[i].FUN_0045c8b0();
		}

		if (m_turboActions != NULL) {
			m_turboActions->Destroy(3);
		}
		m_turboActions = NULL;
	}

	if (m_shieldActions != NULL) {
		LegoU32 i;

		for (i = 0; i < m_actionPoolCounts[8]; i++) {
			m_shieldActions[i].FUN_0045bd10();
		}

		if (m_shieldActions != NULL) {
			m_shieldActions->Destroy(3);
		}
		m_shieldActions = NULL;
	}

	if (m_homingMissileActions != NULL) {
		LegoU32 i;

		for (i = 0; i < m_actionPoolCounts[7]; i++) {
			m_homingMissileActions[i].FUN_00456540();
		}

		if (m_homingMissileActions != NULL) {
			m_homingMissileActions->Destroy(3);
		}
		m_homingMissileActions = NULL;
	}

	if (m_lightningActions != NULL) {
		LegoU32 i;

		for (i = 0; i < m_actionPoolCounts[6]; i++) {
			m_lightningActions[i].FUN_00454ab0();
		}

		if (m_lightningActions != NULL) {
			m_lightningActions->Destroy(3);
		}
		m_lightningActions = NULL;
	}

	if (m_grapplingHookActions != NULL) {
		LegoU32 i;

		for (i = 0; i < m_actionPoolCounts[5]; i++) {
			m_grapplingHookActions[i].FUN_00453d90();
		}

		if (m_grapplingHookActions != NULL) {
			m_grapplingHookActions->Destroy(3);
		}
		m_grapplingHookActions = NULL;
	}

	if (m_cannonballActions != NULL) {
		LegoU32 i;

		for (i = 0; i < m_actionPoolCounts[4]; i++) {
			m_cannonballActions[i].Destroy();
		}

		if (m_cannonballActions != NULL) {
			m_cannonballActions->Destroy(3);
		}
		m_cannonballActions = NULL;
	}

	if (m_curseActions != NULL) {
		LegoU32 i;

		for (i = 0; i < m_actionPoolCounts[3]; i++) {
			m_curseActions[i].FUN_00452510();
		}

		if (m_curseActions != NULL) {
			m_curseActions->Destroy(3);
		}
		m_curseActions = NULL;
	}

	if (m_dynamiteActions != NULL) {
		LegoU32 i;

		for (i = 0; i < m_actionPoolCounts[2]; i++) {
			m_dynamiteActions[i].FUN_00452eb0();
		}

		if (m_dynamiteActions != NULL) {
			m_dynamiteActions->Destroy(3);
		}
		m_dynamiteActions = NULL;
	}

	if (m_oilSlickActions != NULL) {
		LegoU32 i;

		for (i = 0; i < m_actionPoolCounts[1]; i++) {
			m_oilSlickActions[i].FUN_00457170();
		}

		if (m_oilSlickActions != NULL) {
			m_oilSlickActions->Destroy(3);
		}
		m_oilSlickActions = NULL;
	}

	if (m_magnetActions != NULL) {
		LegoU32 i;

		for (i = 0; i < m_actionPoolCounts[0]; i++) {
			m_magnetActions[i].FUN_004557c0();
		}

		if (m_magnetActions != NULL) {
			m_magnetActions->Destroy(3);
		}
		m_magnetActions = NULL;
	}

	if (m_golExport != NULL && m_unk0x05c != 0) {
		m_golExport->VTable0x3c(m_unk0x05c);
		m_unk0x05c = 0;
	}

	m_unk0x014.VTable0x08();
	m_unk0x060 = 0;

	if (m_golExport != NULL && m_unk0x064 != 0) {
		m_golExport->VTable0x3c(m_unk0x064);
		m_unk0x064 = 0;
	}

	if (m_brickEvents != NULL) {
		LegoU32 i;

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

	LegoS32 i;
	for (i = 25; i != 0; i--) {
		m_effectEntities[25 - i].VTable0x54();
	}

	FUN_00457a90();
}

// FUNCTION: LEGORACERS 0x0045a340
void RacePowerupManager::FUN_0045a340()
{
	LegoEventQueue* eventQueue = m_raceState->GetEventQueue();
	LegoEventQueue::Descriptor descriptor;

	descriptor.m_unk0x00 = 4;
	descriptor.m_unk0x04 = 1;
	descriptor.m_unk0x08 = 0;
	descriptor.m_unk0x0c = 0;

	LegoU32 i;
	for (i = 0; i < m_colorBrickCount; i++) {
		ColorBrick* entry = &m_colorBricks[i];
		descriptor.m_data = entry->GetWorldEntity();
		m_brickEvents[i] = eventQueue->FUN_0042fb50(entry, &descriptor);
	}

	WhiteBrick* entries0x02c = m_whiteBricks;
	for (i = 0; i < m_whiteBrickCount; i++) {
		WhiteBrick* entry = &entries0x02c[i];
		descriptor.m_data = entry->GetWorldEntity();
		m_brickEvents[m_colorBrickCount + i] = eventQueue->FUN_0042fb50(entry, &descriptor);
	}
}

// FUNCTION: LEGORACERS 0x0045a3f0
void RacePowerupManager::FUN_0045a3f0(LegoU32 p_elapsedMs)
{
	if (m_brickModel != NULL) {
		m_brickModel->VTable0x10(p_elapsedMs);
	}
	if (m_brickBlendModel != NULL) {
		m_brickBlendModel->VTable0x10(p_elapsedMs);
	}
	if (m_unk0x1970 != NULL) {
		m_unk0x1970->VTable0x10(p_elapsedMs);
	}
	if (m_unk0x1974 != NULL) {
		m_unk0x1974->VTable0x10(p_elapsedMs);
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
	FUN_0045a3f0(p_elapsedMs);

	m_unk0x199c += static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs)) * g_unk0x004b1874;
	if (m_unk0x199c > g_unk0x004b1878) {
		m_unk0x199c -= g_unk0x004b1878;
	}

	PowerupAction* node0x1880;
	for (node0x1880 = m_activeActions; node0x1880 != NULL; node0x1880 = node0x1880->GetNext()) {
		node0x1880->Update(p_elapsedMs);
	}

	Explosion* node0x270;
	for (node0x270 = m_activeExplosions; node0x270 != NULL; node0x270 = node0x270->GetNext()) {
		node0x270->Update(p_elapsedMs);
	}

	for (node0x270 = m_activeSpikeExplosions; node0x270 != NULL; node0x270 = node0x270->GetNext()) {
		node0x270->Update(p_elapsedMs);
	}

	m_unk0x18bc.FUN_00451860(p_elapsedMs);

	node0x1880 = m_activeActions;
	PowerupAction* previous0x1880 = NULL;
	while (node0x1880 != NULL) {
		PowerupAction* next0x1880 = node0x1880->GetNext();
		if (node0x1880->GetState() == 6) {
			if (previous0x1880 == NULL) {
				m_activeActions = next0x1880;
			}
			else {
				previous0x1880->SetNext(next0x1880);
			}

			node0x1880->Deactivate();

			switch (node0x1880->GetBrickColor()) {
			case 1:
				switch (node0x1880->GetLevel()) {
				case 0:
					node0x1880->SetNext(m_freeCannonballActions);
					m_freeCannonballActions = node0x1880;
					break;
				case 1:
					node0x1880->SetNext(m_freeGrapplingHookActions);
					m_freeGrapplingHookActions = node0x1880;
					break;
				case 2:
					node0x1880->SetNext(m_freeLightningActions);
					m_freeLightningActions = node0x1880;
					break;
				case 3:
					node0x1880->SetNext(m_freeHomingMissileActions);
					m_freeHomingMissileActions = node0x1880;
					break;
				}
				break;
			case 4:
				switch (node0x1880->GetLevel()) {
				case 0:
					node0x1880->SetNext(m_freeOilSlickActions);
					m_freeOilSlickActions = node0x1880;
					break;
				case 1:
					node0x1880->SetNext(m_freeDynamiteActions);
					m_freeDynamiteActions = node0x1880;
					break;
				case 2:
					node0x1880->SetNext(m_freeMagnetActions);
					m_freeMagnetActions = node0x1880;
					break;
				case 3:
					node0x1880->SetNext(m_freeCurseActions);
					m_freeCurseActions = node0x1880;
					break;
				}
				break;
			case 2:
				node0x1880->SetNext(m_freeShieldActions);
				m_freeShieldActions = node0x1880;
				break;
			case 3:
				if (node0x1880->GetLevel() > 2) {
					if (node0x1880->GetLevel() == 3) {
						node0x1880->SetNext(m_freeWarpActions);
						m_freeWarpActions = node0x1880;
					}
				}
				else {
					node0x1880->SetNext(m_freeTurboActions);
					m_freeTurboActions = node0x1880;
				}
				break;
			}
		}
		else {
			previous0x1880 = node0x1880;
		}

		node0x1880 = next0x1880;
	}

	node0x270 = m_activeExplosions;
	Explosion* previous0x270 = NULL;
	while (node0x270 != NULL) {
		Explosion* next0x270 = node0x270->GetNext();
		if (node0x270->GetState() == Explosion::c_stateIdle) {
			if (previous0x270 == NULL) {
				m_activeExplosions = next0x270;
			}
			else {
				previous0x270->SetNext(next0x270);
			}

			node0x270->SetNext(m_freeExplosions);
			m_freeExplosions = node0x270;
		}
		else {
			previous0x270 = node0x270;
		}

		node0x270 = next0x270;
	}

	node0x270 = m_activeSpikeExplosions;
	previous0x270 = NULL;
	while (node0x270 != NULL) {
		Explosion* next0x270 = node0x270->GetNext();
		if (node0x270->GetState() == Explosion::c_stateIdle) {
			if (previous0x270 == NULL) {
				m_activeSpikeExplosions = next0x270;
			}
			else {
				previous0x270->SetNext(next0x270);
			}

			node0x270->SetNext(m_freeSpikeExplosions);
			m_freeSpikeExplosions = node0x270;
		}
		else {
			previous0x270 = node0x270;
		}

		node0x270 = next0x270;
	}

	if (m_unk0x060 != NULL) {
		m_unk0x060->FUN_00416090(p_elapsedMs);
	}

	if (m_unk0x1958 != NULL) {
		FUN_0045b7a0(m_unk0x1958, 0, 3);
	}
	if (m_unk0x195c != NULL) {
		FUN_0045b7a0(m_unk0x195c, 3, 3);
	}
	if (m_unk0x1960 != NULL) {
		FUN_0045b7a0(m_unk0x1960, 1, 3);
	}
	if (m_unk0x1964 != NULL) {
		FUN_0045b7a0(m_unk0x1964, 1, 4);
	}
}

// FUNCTION: LEGORACERS 0x0045a7b0
void RacePowerupManager::FUN_0045a7b0(LegoBool32 p_unk0x04)
{
	if (!p_unk0x04) {
		LegoU32 i;

		for (i = 0; i < m_colorBrickCount; i++) {
			m_colorBricks[i].VTable0x10(m_renderer);
		}

		for (i = 0; i < m_whiteBrickCount; i++) {
			m_whiteBricks[i].VTable0x10(m_renderer);
		}
	}

	PowerupAction* node0x1880 = m_activeActions;
	while (node0x1880 != NULL) {
		if (!p_unk0x04 || (node0x1880->GetBrickColor() == 3 && node0x1880->GetLevel() == 3)) {
			node0x1880->VTable0x0c(m_renderer);
		}

		node0x1880 = node0x1880->GetNext();
	}

	if (!p_unk0x04) {
		Explosion* node0x193c = m_activeExplosions;
		while (node0x193c != NULL) {
			node0x193c->FUN_004513d0(m_renderer);
			node0x193c = node0x193c->GetNext();
		}

		Explosion* node0x1940 = m_activeSpikeExplosions;
		while (node0x1940 != NULL) {
			node0x1940->FUN_004513d0(m_renderer);
			node0x1940 = node0x1940->GetNext();
		}
	}

	m_unk0x18bc.FUN_004518a0(m_renderer);
}

// FUNCTION: LEGORACERS 0x0045a8a0
void RacePowerupManager::FUN_0045a8a0()
{
	LegoU32 i;

	for (i = 0; i < m_colorBrickCount; i++) {
		m_colorBricks[i].VTable0x14(m_renderer);
	}

	for (i = 0; i < m_whiteBrickCount; i++) {
		m_whiteBricks[i].VTable0x14(m_renderer);
	}

	PowerupAction* node0x1880 = m_activeActions;
	while (node0x1880 != NULL) {
		node0x1880->VTable0x10(m_renderer);
		node0x1880 = node0x1880->GetNext();
	}

	Explosion* node0x193c = m_activeExplosions;
	while (node0x193c != NULL) {
		node0x193c->Draw(m_renderer);
		node0x193c = node0x193c->GetNext();
	}

	Explosion* node0x1940 = m_activeSpikeExplosions;
	while (node0x1940 != NULL) {
		node0x1940->Draw(m_renderer);
		node0x1940 = node0x1940->GetNext();
	}
}

// FUNCTION: LEGORACERS 0x0045a950
void RacePowerupManager::UseRedPowerup(RaceState::Racer* p_racer, LegoU32 p_unk0x08)
{
	switch (p_unk0x08) {
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
void RacePowerupManager::UseYellowPowerup(RaceState::Racer* p_racer, LegoU32 p_unk0x08)
{
	switch (p_unk0x08) {
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
LegoU32 RacePowerupManager::FireCannonball(RaceState::Racer* p_racer, LegoU32 p_unk0x08)
{
	ActionSetup setup;
	setup.m_racer = p_racer;
	setup.m_targetPoint = NULL;
	setup.m_targetRacer = NULL;

	if (!m_aimTarget) {
		GolVec3 position;
		p_racer->m_unk0x018.m_unk0x044->VTable0x04(&position);

		GolVec3 direction;
		p_racer->m_unk0x018.m_unk0x044->GetOrientationRow0(&direction);

		if (p_racer->m_unk0xd08 != 2) {
			setup.m_targetPoint =
				m_unk0x050->FUN_0045c6a0(&position, &direction, g_unk0x004b1840, g_unk0x004b1844, g_unk0x004b184c);
		}

		if (!setup.m_targetPoint) {
			setup.m_targetRacer =
				m_raceState->FUN_0043ca60(&position, &direction, g_unk0x004b1840, g_unk0x004b1844, g_unk0x004b1848);
		}
	}

	setup.m_aimTarget = m_aimTarget;
	setup.m_initialTimerMs = 0;

	CannonballAction* action = static_cast<CannonballAction*>(m_freeCannonballActions);
	if (!action) {
		action = static_cast<CannonballAction*>(ReclaimAction(c_brickColorRed, p_unk0x08, -1, -1, -1));
	}
	else {
		m_freeCannonballActions = action->m_next;
	}

	action->m_next = m_activeActions;
	m_activeActions = action;
	LegoU32 result = action->Activate(&setup);
	action->m_level = p_unk0x08;
	return result;
}

// FUNCTION: LEGORACERS 0x0045ab50
LegoU32 RacePowerupManager::FireGrapplingHook(RaceState::Racer* p_racer, LegoU32 p_unk0x08)
{
	Field0x050::Entry* entry = NULL;

	GolVec3 position;
	p_racer->m_unk0x018.m_unk0x044->VTable0x04(&position);

	GolVec3 direction;
	p_racer->m_unk0x018.m_unk0x044->GetOrientationRow0(&direction);

	RaceState::Racer* target =
		m_raceState->FUN_0043c910(&position, &direction, g_unk0x004b185c, g_unk0x004b1860, g_unk0x004b1868);
	if (!target) {
		target = m_raceState->FUN_0043ca60(&position, &direction, g_unk0x004b185c, g_unk0x004b1864, g_unk0x004b186c);
		if (!target && p_racer->m_unk0xd08 != 2) {
			entry = m_unk0x050->FUN_0045c6a0(&position, &direction, g_unk0x004b1840, g_unk0x004b1844, g_unk0x004b184c);
		}
	}

	GrapplingHookAction* action = static_cast<GrapplingHookAction*>(m_freeGrapplingHookActions);
	if (!action) {
		action = static_cast<GrapplingHookAction*>(ReclaimAction(c_brickColorRed, p_unk0x08, -1, -1, -1));
	}
	else {
		m_freeGrapplingHookActions = action->m_next;
	}

	PowerupAction* next = m_activeActions;
	Field0x050::Entry* setupEntry = entry;
	action->m_next = next;
	GolWorldDatabase* worldDatabase = m_unk0x05c;
	m_activeActions = action;
	GrapplingHookAction* activeAction = static_cast<GrapplingHookAction*>(m_activeActions);
	LegoU32 result =
		activeAction
			->Activate(worldDatabase->GetUnk0x9c(), p_racer, target, setupEntry, GetMaterialAnimationItems0x18(), 0);
	action->m_level = p_unk0x08;
	return result;
}

// FUNCTION: LEGORACERS 0x0045ac80
void RacePowerupManager::FireLightning(RaceState::Racer* p_racer, LegoU32 p_unk0x08)
{
	LightningAction* action = static_cast<LightningAction*>(m_freeLightningActions);
	if (!action) {
		action = static_cast<LightningAction*>(ReclaimAction(c_brickColorRed, p_unk0x08, -1, -1, -1));
	}
	else {
		m_freeLightningActions = action->m_next;
	}

	action->m_next = m_activeActions;
	m_activeActions = action;
	action->Activate(p_racer, m_aimTarget);
	action->m_level = p_unk0x08;
}

// FUNCTION: LEGORACERS 0x0045ace0
void RacePowerupManager::DropOilSlick(RaceState::Racer* p_racer, LegoU32 p_unk0x08)
{
	OilSlickAction* action = static_cast<OilSlickAction*>(m_freeOilSlickActions);
	if (!action) {
		action = static_cast<OilSlickAction*>(ReclaimAction(c_brickColorYellow, p_unk0x08, -1, -1, -1));
	}
	else {
		m_freeOilSlickActions = action->m_next;
	}

	action->m_next = m_activeActions;
	m_activeActions = action;
	action->Activate(p_racer);
	action->m_level = p_unk0x08;
}

// FUNCTION: LEGORACERS 0x0045ad30
LegoU32 RacePowerupManager::ThrowDynamite(RaceState::Racer* p_racer, LegoU32 p_unk0x08)
{
	DynamiteAction* action = static_cast<DynamiteAction*>(m_freeDynamiteActions);
	if (!action) {
		action = static_cast<DynamiteAction*>(ReclaimAction(c_brickColorYellow, p_unk0x08, -1, -1, -1));
	}
	else {
		m_freeDynamiteActions = action->m_next;
	}

	action->m_next = m_activeActions;
	m_activeActions = action;

	GolVec3 position;
	p_racer->m_unk0x018.m_unk0x044->VTable0x04(&position);

	GolVec3 direction;
	p_racer->m_unk0x018.m_unk0x044->GetOrientationRow0(&direction);
	direction.m_x = -direction.m_x;
	direction.m_y = -direction.m_y;
	direction.m_z = -direction.m_z;

	RaceState::Racer* target =
		m_raceState->FUN_0043ca60(&position, &direction, g_unk0x004b1850, g_unk0x004b1854, g_unk0x004b1858);
	LegoU32 result = action->Activate(p_racer, target);
	action->m_level = p_unk0x08;
	return result;
}

// FUNCTION: LEGORACERS 0x0045adf0
void RacePowerupManager::ActivateMagnet(RaceState::Racer* p_racer, LegoU32 p_unk0x08)
{
	MagnetAction* action = static_cast<MagnetAction*>(m_freeMagnetActions);
	if (!action) {
		action = static_cast<MagnetAction*>(ReclaimAction(c_brickColorYellow, p_unk0x08, -1, -1, -1));
	}
	else {
		m_freeMagnetActions = action->m_next;
	}

	action->m_next = m_activeActions;
	m_activeActions = action;

	GolAnimatedEntity* model0;
	if (m_unk0x05c->GetUnk0xc0NameEntries() == NULL) {
		model0 = NULL;
	}
	else {
		model0 = m_unk0x05c->GetUnk0xc0Name("magnet");
	}

	GolAnimatedEntity* model1;
	if (m_unk0x05c->GetUnk0xc0NameEntries() == NULL) {
		model1 = NULL;
	}
	else {
		model1 = m_unk0x05c->GetUnk0xc0Name("magring");
	}

	GolAnimatedEntity* model2;
	if (m_unk0x05c->GetUnk0xc0NameEntries() == NULL) {
		model2 = NULL;
	}
	else {
		model2 = m_unk0x05c->GetUnk0xc0Name("insd");
	}

	action->Activate(p_racer, model0, model1, model2);
	action->m_level = p_unk0x08;
}

// FUNCTION: LEGORACERS 0x0045aeb0
void RacePowerupManager::CastCurse(RaceState::Racer* p_racer, LegoU32 p_unk0x08)
{
	GolAnimatedEntity* model0;
	GolAnimatedEntity* model1;
	GolAnimatedEntity* model2;

	CurseAction* action = static_cast<CurseAction*>(m_freeCurseActions);
	if (!action) {
		action = static_cast<CurseAction*>(ReclaimAction(c_brickColorYellow, p_unk0x08, -1, -1, -1));
	}
	else {
		m_freeCurseActions = action->m_next;
	}

	action->m_next = m_activeActions;
	m_activeActions = action;

	if (m_unk0x05c->GetUnk0xc0NameEntries() == NULL) {
		model0 = NULL;
	}
	else {
		model0 = m_unk0x05c->GetUnk0xc0Name("curse");
	}

	if (m_unk0x05c->GetUnk0xc0NameEntries() == NULL) {
		model1 = NULL;
	}
	else {
		model1 = m_unk0x05c->GetUnk0xc0Name("cgreen");
	}

	if (m_unk0x05c->GetUnk0xc0NameEntries() == NULL) {
		model2 = NULL;
	}
	else {
		model2 = m_unk0x05c->GetUnk0xc0Name("cgreen2");
	}

	action->Activate(p_racer, model0, model1, model2, m_aimTarget);
	action->m_level = p_unk0x08;
}

// FUNCTION: LEGORACERS 0x0045af80
void RacePowerupManager::FireHomingMissiles(RaceState::Racer* p_racer, LegoU32 p_unk0x08)
{
	for (LegoU32 i = 0; i < 3; i++) {
		HomingMissileAction* action = static_cast<HomingMissileAction*>(m_freeHomingMissileActions);
		if (!action) {
			action = static_cast<HomingMissileAction*>(ReclaimAction(c_brickColorRed, p_unk0x08, -1, -1, -1));
		}
		else {
			m_freeHomingMissileActions = action->m_next;
		}

		action->m_next = m_activeActions;
		m_activeActions = action;

		GolAnimatedEntity* model0;
		if (m_unk0x05c->GetUnk0xc0NameEntries() == NULL) {
			model0 = NULL;
		}
		else {
			model0 = m_unk0x05c->GetUnk0xc0Name("dmissil");
		}

		GolAnimatedEntity* model1;
		if (m_unk0x05c->GetUnk0xc0NameEntries() == NULL) {
			model1 = NULL;
		}
		else {
			model1 = m_unk0x05c->GetUnk0xc0Name("dmissil");
		}

		action->Activate(model1, model0, p_racer, i);
		action->m_level = p_unk0x08;
	}
}

// FUNCTION: LEGORACERS 0x0045b030
void RacePowerupManager::UseBluePowerup(RaceState::Racer* p_racer, LegoU32 p_unk0x08)
{
	if (25 - m_usedEffectEntityCount >= 2) {
		LegoU32 subtype = p_unk0x08;
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
			if (m_unk0x05c->GetUnk0xc0NameEntries() == NULL) {
				model = NULL;
			}
			else {
				model = m_unk0x05c->GetUnk0xc0Name("shield0");
			}

			if (m_unk0x05c->GetUnk0xc0NameEntries()) {
				inputModel = m_unk0x05c->GetUnk0xc0Name("shldin0");
			}
			else {
				inputModel = NULL;
			}
			break;
		case 1:
			if (m_unk0x05c->GetUnk0xc0NameEntries() == NULL) {
				model = NULL;
			}
			else {
				model = m_unk0x05c->GetUnk0xc0Name("shield1");
			}

			if (m_unk0x05c->GetUnk0xc0NameEntries()) {
				inputModel = m_unk0x05c->GetUnk0xc0Name("shldin1");
			}
			else {
				inputModel = NULL;
			}
			break;
		case 2:
			if (m_unk0x05c->GetUnk0xc0NameEntries() == NULL) {
				model = NULL;
			}
			else {
				model = m_unk0x05c->GetUnk0xc0Name("shield2");
			}

			if (m_unk0x05c->GetUnk0xc0NameEntries()) {
				inputModel = m_unk0x05c->GetUnk0xc0Name("shldin2");
			}
			else {
				inputModel = NULL;
			}
			break;
		case 3:
			if (m_unk0x05c->GetUnk0xc0NameEntries() == NULL) {
				model = NULL;
			}
			else {
				model = m_unk0x05c->GetUnk0xc0Name("shield3");
			}

			if (m_unk0x05c->GetUnk0xc0NameEntries()) {
				inputModel = m_unk0x05c->GetUnk0xc0Name("shldin3");
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
void RacePowerupManager::UseGreenPowerup(RaceState::Racer* p_racer, LegoU32 p_unk0x08)
{
	if (p_unk0x08 == 3) {
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
		action->Activate(p_racer, p_unk0x08);
		action->m_level = p_unk0x08;
	}
}

// FUNCTION: LEGORACERS 0x0045b260
LegoU32 RacePowerupManager::ActivateWarp(RaceState::Racer* p_racer, LegoU32 p_unk0x08)
{
	WarpAction* action = static_cast<WarpAction*>(m_freeWarpActions);
	if (!action) {
		action = static_cast<WarpAction*>(ReclaimAction(c_brickColorGreen, p_unk0x08, -1, -1, -1));
	}
	else {
		m_freeWarpActions = action->m_next;
	}

	action->m_next = m_activeActions;
	m_activeActions = action;

	GolModelEntity* model;
	if (m_unk0x05c->GetUnk0xb4NameEntries() == NULL) {
		model = NULL;
	}
	else {
		model = m_unk0x05c->GetUnk0xb4Name("warpprt");
	}

	LegoU32 result = action->Activate(p_racer, model, m_aimTarget);
	action->m_level = p_unk0x08;
	return result;
}

// FUNCTION: LEGORACERS 0x0045b2e0
RacePowerupManager::PowerupAction* RacePowerupManager::ReclaimAction(
	LegoU32 p_unk0x04,
	LegoU32 p_unk0x08,
	LegoS32 p_unk0x0c,
	LegoS32 p_unk0x10,
	LegoS32 p_unk0x14
)
{
	PowerupAction* previous = NULL;
	PowerupAction* bestPrevious = NULL;
	PowerupAction* best = NULL;
	LegoS32 bestScore = 0;
	LegoU32 bestPriority = 0xffffffff;

	for (PowerupAction* action = m_activeActions; action != NULL; action = action->GetNext()) {
		if (action->GetBrickColor() == static_cast<LegoS32>(p_unk0x04)) {
			LegoU32 subtype = action->GetLevel();
			if (subtype == p_unk0x08 || subtype == static_cast<LegoU32>(p_unk0x0c) ||
				subtype == static_cast<LegoU32>(p_unk0x10) || subtype == static_cast<LegoU32>(p_unk0x14)) {
				LegoS32 score = action->GetState();
				if (score > bestScore) {
					bestPriority = action->GetStateTimer();
					bestScore = action->GetState();
					best = action;
					bestPrevious = previous;
				}
				else if (score == bestScore) {
					LegoU32 priority = action->GetStateTimer();
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
RacePowerupManager::Explosion* __stdcall RacePowerupManager::ReclaimExplosion(Explosion** p_head)
{
	Explosion* selected = NULL;
	Explosion* selectedPrevious = NULL;
	LegoU32 selectedRemaining = 0xffffffff;
	LegoS32 targetState = Explosion::c_stateScarFading;
	LegoU32 pass = 0;
	Explosion* current = *p_head;
	Explosion* head = current;

	for (;;) {
		Explosion* previous = NULL;

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
			targetState = Explosion::c_stateExploding;
			pass++;
			if (pass < 3) {
				continue;
			}

			Explosion* result = current;
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
void RacePowerupManager::SpawnExplosion(const GolVec3* p_position, undefined4 p_unk0x08, RaceState::Racer* p_racer)
{
	Explosion* item = m_freeExplosions;
	if (item == NULL) {
		item = ReclaimExplosion(&m_activeExplosions);
	}
	else {
		m_freeExplosions = item->GetNext();
	}

	item->SetNext(m_activeExplosions);
	m_activeExplosions = item;
	item->Spawn(p_position, p_unk0x08, p_racer);
}

// FUNCTION: LEGORACERS 0x0045b4d0
void RacePowerupManager::FUN_0045b4d0(const GolVec3* p_position, undefined4 p_unk0x08, RaceState::Racer* p_racer)
{
	SpawnExplosion(p_position, p_unk0x08, p_racer);
}

// FUNCTION: LEGORACERS 0x0045b4f0
void RacePowerupManager::SpawnSpikeExplosion(const GolVec3* p_position, undefined4 p_unk0x08, RaceState::Racer* p_racer)
{
	Explosion* item = m_freeSpikeExplosions;
	if (item == NULL) {
		item = ReclaimExplosion(&m_activeSpikeExplosions);
	}
	else {
		m_freeSpikeExplosions = item->GetNext();
	}

	item->SetNext(m_activeSpikeExplosions);
	m_activeSpikeExplosions = item;
	item->Spawn(p_position, p_unk0x08, p_racer);
}

// FUNCTION: LEGORACERS 0x0045b550
void RacePowerupManager::FUN_0045b550(const GolVec3* p_unk0x04, const GolVec3* p_position, RaceState::Racer* p_racer)
{
	GolVec3 position;

	g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
	LegoU32 count = (static_cast<LegoU32>(g_unk0x004befec[g_unk0x004c6ee4]) % c_randomBurstMax) + 1;
	if (count != 0) {
		Field0x18bc* field0x18bc = &m_unk0x18bc;
		LegoU32 remaining = count;

		do {
			g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
			position.m_z = 0.0f;
			LegoS32 offsetX = g_unk0x004befec[g_unk0x004c6ee4] % c_randomOffsetRange;
			position.m_x = p_position->m_x + offsetX * 0.0040000002f - g_unk0x004b02e0;

			g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
			LegoS32 offsetY = g_unk0x004befec[g_unk0x004c6ee4] % c_randomOffsetRange;

			position.m_y = p_position->m_y + offsetY * 0.0040000002f - g_unk0x004b02e0;
			field0x18bc->FUN_004517c0(p_unk0x04, &position, p_racer);
		} while (--remaining != 0);
	}
}

// FUNCTION: LEGORACERS 0x0045b640
void RacePowerupManager::FUN_0045b640(RaceState::Racer* p_racer)
{
	for (LegoU32 i = 0; i < m_actionPoolCounts[8]; i++) {
		ShieldAction* action = &m_shieldActions[i];
		if (action->GetState() > 1 && action->m_unk0x20 == p_racer) {
			action->SetState(6);
		}
	}
}

// FUNCTION: LEGORACERS 0x0045b690 FOLDED
void RacePowerupManager::FUN_0045b690(RaceState::Racer* p_racer)
{
	for (LegoU32 i = 0; i < m_actionPoolCounts[9]; i++) {
		if (m_turboActions[i].m_state > 1 && m_turboActions[i].m_unk0x018 == p_racer) {
			m_turboActions[i].m_state = 6;
			m_turboActions[i].m_unk0x018 = NULL;
		}
	}
}

// FUNCTION: LEGORACERS 0x0045b6f0
void RacePowerupManager::FUN_0045b6f0(RaceState::Racer* p_racer)
{
	for (LegoU32 i = 0; i < m_actionPoolCounts[0]; i++) {
		MagnetAction* action = &m_magnetActions[i];
		if (action->GetState() > 1 && action->m_unk0x78 == p_racer) {
			action->SetState(6);
		}
	}
}

// FUNCTION: LEGORACERS 0x0045b740
void RacePowerupManager::FUN_0045b740(RaceState::Racer* p_racer)
{
	for (LegoU32 i = 0; i < m_actionPoolCounts[10]; i++) {
		WarpAction* item = &m_warpActions[i];
		if (item->m_unk0x0a8 == p_racer) {
			if (item->m_state == 2) {
				item->m_state = 6;
			}
			else if (item->m_state == 3) {
				item->m_stateTimerMs = 0;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x0045b7a0
void RacePowerupManager::FUN_0045b7a0(Field0x1958Resource* p_resource, LegoU32 p_unk0x08, LegoS32 p_unk0x0c)
{
	RaceState::Racer* racer = m_raceState->GetCurrentRacer();
	if (racer == NULL) {
		if (p_resource->VTable0x0c()) {
			p_resource->VTable0x08();
		}
		return;
	}

	WeaponActionBase* nearest = NULL;
	LegoFloat nearestDistanceSquared = FLT_MAX;
	GolVec3 referencePosition;
	GolVec3 position;
	GolVec3 direction;

	racer->m_unk0x018.GetUnk0x044()->VTable0x04(&referencePosition);

	for (PowerupAction* node = m_activeActions; node != NULL; node = node->GetNext()) {
		if (node->GetBrickColor() == 1 && node->GetLevel() == p_unk0x08 && node->GetState() == p_unk0x0c) {
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

	if (nearestDistanceSquared < g_unk0x004c7644) {
		if (!p_resource->VTable0x0c()) {
			p_resource->VTable0x04(1);
		}

		nearest->GetProjectilePosition(&referencePosition);
		nearest->GetProjectileVelocity(&direction);

		p_resource->m_unk0x18 = referencePosition;
		p_resource->m_unk0x24.m_x = direction.m_x;
		p_resource->m_unk0x24.m_y = direction.m_y;
		p_resource->m_unk0x24.m_z = direction.m_z;
	}
	else if (p_resource->VTable0x0c()) {
		p_resource->VTable0x08();
	}
}

// FUNCTION: LEGORACERS 0x0045b900
void RacePowerupManager::FUN_0045b900()
{
	LegoU32 i;

	for (i = 0; i < m_colorBrickCount; i++) {
		m_colorBricks[i].SetFlags0x50Bit0();
	}

	for (i = 0; i < m_whiteBrickCount; i++) {
		m_whiteBricks[i].SetFlags0x50Bit0();
	}
}

// FUNCTION: LEGORACERS 0x0045b950
void RacePowerupManager::FUN_0045b950()
{
	LegoU32 i;

	for (i = 0; i < m_colorBrickCount; i++) {
		m_colorBricks[i].ClearFlags0x50Bit0();
	}

	for (i = 0; i < m_whiteBrickCount; i++) {
		m_whiteBricks[i].ClearFlags0x50Bit0();
	}
}

// FUNCTION: LEGORACERS 0x0045b9a0
LegoBool32 RacePowerupManager::FUN_0045b9a0(RaceState::Racer* p_racer)
{
	PowerupAction* node = m_activeActions;
	while (node != NULL) {
		if (node->GetBrickColor() == 1 && static_cast<ShieldAction*>(node)->FUN_0045bc40() == p_racer) {
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
	LegoU32 flags = m_unk0x1878;
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

	m_unk0x1878 |= 1 << index;
	m_usedEffectEntityCount = count + 1;
	return &m_effectEntities[index];
}

// FUNCTION: LEGORACERS 0x0045ba40 FOLDED
LegoU32 RacePowerupManager::ReleaseEffectEntity(GolAnimatedEntity* p_entity)
{
	LegoS32 index = p_entity - m_effectEntities;

	m_unk0x1878 &= ~(1 << index);
	m_usedEffectEntityCount--;

	return m_usedEffectEntityCount;
}

// FUNCTION: LEGORACERS 0x0045ba90
DuskwindBananaRelic0x24* RacePowerupManager::GetBrickMaterial(LegoU32* p_unk0x04)
{
	switch (*p_unk0x04) {
	case 1:
		return m_brickMaterials[c_brickMaterialRed];
	case 2:
		return m_brickMaterials[c_brickMaterialBlue];
	case 3:
		return m_brickMaterials[c_brickMaterialGreen];
	case 4:
		return m_brickMaterials[c_brickMaterialYellow];
	default:
		return NULL;
	}
}

// FUNCTION: LEGORACERS 0x0045bae0
DuskwindBananaRelic0x24* RacePowerupManager::GetTrailMaterial(LegoU32* p_unk0x04)
{
	switch (*p_unk0x04) {
	case 1:
		return m_brickMaterials[c_trailMaterialRed];
	case 2:
		return m_brickMaterials[c_trailMaterialBlue];
	case 3:
		return m_brickMaterials[c_trailMaterialGreen];
	case 4:
		return m_brickMaterials[c_trailMaterialYellow];
	default:
		return NULL;
	}
}

// FUNCTION: LEGORACERS 0x0045bb30
void RacePowerupManager::FUN_0045bb30()
{
	LegoU32 i;

	for (i = 0; i < m_colorBrickCount; i++) {
		m_colorBricks[i].Respawn();
	}

	for (i = 0; i < m_whiteBrickCount; i++) {
		m_whiteBricks[i].Respawn();
	}

	Explosion* node0x193c = m_activeExplosions;
	while (node0x193c != NULL) {
		node0x193c->Deactivate();
		node0x193c = node0x193c->GetNext();
	}

	Explosion* node0x1940 = m_activeSpikeExplosions;
	while (node0x1940 != NULL) {
		node0x1940->Deactivate();
		node0x1940 = node0x1940->GetNext();
	}

	m_unk0x18bc.FUN_004518d0();

	PowerupAction* node0x1880 = m_activeActions;
	while (node0x1880 != NULL) {
		node0x1880->SetState(6);
		node0x1880 = node0x1880->GetNext();
	}

	Update(0);
}
