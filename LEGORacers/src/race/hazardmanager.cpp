#include "audio/spatialsoundinstance.h"
#include "camera/golcamera.h"
#include "cmbmodelpart0x34.h"
#include "decomp.h"
#include "golanimatedentity.h"
#include "golbinparser.h"
#include "golerror.h"
#include "golfileparser.h"
#include "golmath.h"
#include "golmodelbase.h"
#include "golmodelentity.h"
#include "golnametable.h"
#include "golscenenode.h"
#include "goltransformbase.h"
#include "mabmaterialanimation0x14.h"
#include "mabmaterialanimationitem0x18.h"
#include "menu/runtime/cutsceneparticle.h"
#include "menu/runtime/cutsceneplayer.h"
#include "race/hazardmanager.h"
#include "race/raceeventtable0x90.h"
#include "race/racesession.h"
#include "render/gold3drenderdevice.h"
#include "world/golworlddatabase.h"

#include <float.h>
#include <string.h>

inline void* operator new(size_t, void* p_pointer)
{
	return p_pointer;
}

inline void operator delete(void*, void*)
{
}

DECOMP_SIZE_ASSERT(HazardManager, 0x08)
DECOMP_SIZE_ASSERT(HazardManager::Context, 0x60)
DECOMP_SIZE_ASSERT(HazardManager::HzbTxtParser, 0x1fc)
DECOMP_SIZE_ASSERT(HazardManager::Hazard, 0x10)
DECOMP_SIZE_ASSERT(HazardManager::WarpPadHazard, 0x18)
DECOMP_SIZE_ASSERT(HazardManager::OscillatorHazard, 0x20)
DECOMP_SIZE_ASSERT(HazardManager::CurseDropHazard, 0x18)
DECOMP_SIZE_ASSERT(HazardManager::SweepCannonHazard, 0x58)
DECOMP_SIZE_ASSERT(HazardManager::FallingPillarHazard, 0x20)
DECOMP_SIZE_ASSERT(HazardManager::SphinxHazard, 0x24)
DECOMP_SIZE_ASSERT(HazardManager::HammerHazard, 0x18)
DECOMP_SIZE_ASSERT(HazardManager::GhostHazard, 0x220)
DECOMP_SIZE_ASSERT(HazardManager::LavaGeyserHazard, 0x5c)
DECOMP_SIZE_ASSERT(HazardManager::CodePuzzleHazard, 0x3c)
DECOMP_SIZE_ASSERT(HazardManager::RocketHazard, 0x5c)
DECOMP_SIZE_ASSERT(HazardManager::SnowfallHazard, 0x20)
DECOMP_SIZE_ASSERT(HazardManager::SmokeVentHazard, 0x20)
DECOMP_SIZE_ASSERT(HazardManager::MovingObstacleHazard, 0x17c)
DECOMP_SIZE_ASSERT(HazardManager::LauncherHazard, 0x124)
DECOMP_SIZE_ASSERT(HazardManager::TriggeredAnimationHazard, 0x30)
DECOMP_SIZE_ASSERT(HazardManager::MultiLauncherHazard, 0x140)
DECOMP_SIZE_ASSERT(HazardManager::RollingRockHazard, 0x204)
DECOMP_SIZE_ASSERT(HazardManager::CannonballRainHazard, 0x44)
DECOMP_SIZE_ASSERT(HazardManager::GrabberHazard, 0x60)

extern LegoFloat g_cosineTable[1024];
extern const LegoFloat g_negativeRadiansToTableIndex;
extern const LegoFloat g_twoPi;
extern const LegoFloat g_boxInertiaFactor;
extern LegoU16 g_randomTable[1024];
extern LegoU32 g_randomTableIndex;
extern LegoFloat g_carBuildPreviewMouseScale;

// GLOBAL: LEGORACERS 0x004b0b48
extern const LegoFloat g_sweepCannonRadiansToTableIndex = 162.974655f;

// GLOBAL: LEGORACERS 0x004b03f0
extern const LegoFloat g_hazardPi = 3.1415927f;

// GLOBAL: LEGORACERS 0x004b4270
extern const LegoFloat g_sweepCannonTrackedEntityZOffset = 17.0f;

// GLOBAL: LEGORACERS 0x004b42e8
extern const LegoFloat g_rollingRockModelDistance = FLT_MAX;

// GLOBAL: LEGORACERS 0x004b42ec
extern const LegoFloat g_unk0x004b42ec = 20000.0f;

// GLOBAL: LEGORACERS 0x004b4338
extern const LegoFloat g_sphinxInactiveModelDistance = -1.0f;

// GLOBAL: LEGORACERS 0x004b43a0
extern const LegoFloat g_cannonballRainTransformOffsetScale = 35.0f;

// GLOBAL: LEGORACERS 0x004b43c0
extern const LegoFloat g_ghostLoopSoundMinDistance = 30.0f;

// GLOBAL: LEGORACERS 0x004b43c4
extern const LegoFloat g_ghostSoundMaxDistance = 300.0f;

// GLOBAL: LEGORACERS 0x004b43c8
extern const LegoFloat g_ghostOneShotSoundMinDistance = 200.0f;

// GLOBAL: LEGORACERS 0x004b43cc
extern const LegoFloat g_ghostTriggerRadiusPadding = 8.0f;

// GLOBAL: LEGORACERS 0x004b43d0
extern const LegoFloat g_ghostImpulseVectorZ = 150.0f;

// GLOBAL: LEGORACERS 0x004b43d4
extern const LegoFloat g_ghostFrequencyScaleJitter = 0.4f;

// GLOBAL: LEGORACERS 0x004b43d8
extern const LegoFloat g_ghostRacerSearchDistanceSquared = 3600.0f;

extern const LegoFloat g_violetShoalTwo;

// GLOBAL: LEGORACERS 0x004b4414
extern const LegoFloat g_item0x2aTriggerStart0 = 22.0f;

// GLOBAL: LEGORACERS 0x004b4418
extern const LegoFloat g_item0x2aTriggerEnd0 = 28.0f;

// GLOBAL: LEGORACERS 0x004b441c
extern const LegoFloat g_item0x2aTriggerStart1 = 72.0f;

// GLOBAL: LEGORACERS 0x004b4420
extern const LegoFloat g_item0x2aTriggerEnd1 = 78.0f;

// GLOBAL: LEGORACERS 0x004b4424
extern const LegoFloat g_item0x2aResetStart0 = 0.0f;

// GLOBAL: LEGORACERS 0x004b4428
extern const LegoFloat g_item0x2aResetEnd0 = 20.0f;

// GLOBAL: LEGORACERS 0x004b442c
extern const LegoFloat g_item0x2aResetStart1 = 40.0f;

// GLOBAL: LEGORACERS 0x004b4430
extern const LegoFloat g_item0x2aResetEnd1 = 60.0f;

// GLOBAL: LEGORACERS 0x004b44b8
extern const LegoFloat g_lavaGeyserSoundMaxDistance = 300.0f;

// GLOBAL: LEGORACERS 0x004b44bc
extern const LegoFloat g_lavaGeyserSoundMinDistance = 200.0f;

// GLOBAL: LEGORACERS 0x004b44c8
extern const LegoFloat g_lavaGeyserLavaStartFrames[3] = {0.0f, 61.0f, 119.0f};

// GLOBAL: LEGORACERS 0x004b44d4
extern const LegoFloat g_lavaGeyserLavaEndFrames[3] = {26.0f, 86.0f, 146.0f};

// GLOBAL: LEGORACERS 0x004b4514
extern const LegoFloat g_grabberTriggerRadius = 45.0f;

// GLOBAL: LEGORACERS 0x004b4548
extern const LegoFloat g_rocketInactiveModelDistance = -1.0f;

// GLOBAL: LEGORACERS 0x004b4568
extern const LegoFloat g_rocketTriggerRadius = 350.0f;

// GLOBAL: LEGORACERS 0x004b45b0
extern const GolVec3 g_smokeVentSmokeOffsets[4] = {
	{-24.45f, 26.74f, -19.56f},
	{-35.72f, 9.41f, -18.41f},
	{-6.9f, -9.13f, -15.49f},
	{4.37f, 8.54f, -16.65f},
};

// GLOBAL: LEGORACERS 0x004b461c
extern const LegoFloat g_snowfallCameraForwardScale = 100.0f;

// GLOBAL: LEGORACERS 0x004b4620
extern const LegoFloat g_snowfallCameraVerticalOffset = -40.0f;

// GLOBAL: LEGORACERS 0x004b46b4
extern const LegoFloat g_launcherMaxDistanceSquared = FLT_MAX;

// GLOBAL: LEGORACERS 0x004c22fc
extern const ColorRGBA g_launcherTrailColor = {0x32, 0x32, 0x32, 0x64};

extern const LegoFloat g_unk0x004afde0;

static const LegoFloat g_warpPadActionPositionX = 132.673004f;
static const LegoFloat g_warpPadActionPositionY = 86.304001f;
static const LegoFloat g_warpPadActionPositionZ = 14.722000f;
static const LegoFloat g_warpPadActionDirectionX = 1.0f;
static const LegoFloat g_warpPadActionDirectionY = -0.5f;
static const LegoFloat g_warpPadActionDirectionZ = 0.0f;
static const LegoFloat g_oscillatorCycleMs = 10000.0f;
static const LegoFloat g_oscillatorInvCycleMs = 0.0001f;
static const LegoFloat g_oscillatorTau = 6.2831855f;
static const LegoFloat g_oscillatorCosineIndexScale = -162.974655f;
static const GolVec3 g_curseDropActionDirection = {1.0f, 0.0f, 0.0f};
static const GolVec3 g_curseDropActionPositions[] = {
	{-357.582703f, 458.126984f, -11.665112f},
	{-351.203125f, 518.713013f, -94.215683f},
	{-362.258179f, 397.303925f, -94.959518f},
};

// GLOBAL: LEGORACERS 0x004c22d8
extern const GolVec3 g_lavaGeyserLavaPositions[3] = {
	{577.0f, -444.0f, 7.3340001f},
	{605.0f, -500.0f, 19.0f},
	{525.0f, -505.0f, 4.6f},
};

// FUNCTION: LEGORACERS 0x0048a400
HazardManager::Hazard::Hazard()
{
	m_eventTable = NULL;
	m_state = 0;
	m_triggerId = 0;
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void HazardManager::Hazard::VTable0x00(LegoEventQueue::CallbackData*)
{
}

// FUNCTION: LEGORACERS 0x0048a440
HazardManager::Hazard::~Hazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048a450
LegoS32 HazardManager::Hazard::Reset()
{
	m_eventTable = NULL;
	m_state = 0;
	m_triggerId = 0;

	return 0;
}

// FUNCTION: LEGORACERS 0x0048a460
void HazardManager::Hazard::Update(undefined4)
{
	if (m_state == 3) {
		OnDeactivate(NULL);
	}
}

// FUNCTION: LEGORACERS 0x0048a470
void HazardManager::Hazard::Activate(void* p_unk0x04)
{
	if (m_state == 1) {
		OnActivate(p_unk0x04);
	}
}

// FUNCTION: LEGORACERS 0x0048a490
void HazardManager::Hazard::Deactivate(void* p_unk0x04)
{
	if (m_state != 1) {
		OnDeactivate(p_unk0x04);
	}
}

// FUNCTION: LEGORACERS 0x0046c9f0 FOLDED
void HazardManager::Hazard::UpdatePerRacer(GolCamera*, RaceState::Racer*)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void HazardManager::Hazard::Draw(GolD3DRenderDevice*)
{
}

// FUNCTION: LEGORACERS 0x0044e7e0 FOLDED
LegoBool32 HazardManager::Hazard::CanRetrigger()
{
	return FALSE;
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void HazardManager::Hazard::ResetState()
{
}

// FUNCTION: LEGORACERS 0x0046c9f0 FOLDED
void HazardManager::Hazard::OnEventStart(LegoS32, void*)
{
}

// FUNCTION: LEGORACERS 0x0046c9f0 FOLDED
void HazardManager::Hazard::OnEventEnd(LegoS32, void*)
{
}

// FUNCTION: LEGORACERS 0x0048a4b0
HazardManager::HazardManager()
{
	m_entries = NULL;
	m_count = 0;
}

// FUNCTION: LEGORACERS 0x0048a4c0
HazardManager::~HazardManager()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0048a4d0
void HazardManager::LoadHazards(void* p_context, const LegoChar* p_name, LegoBool32 p_binary)
{
	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".hzb");
	}
	else {
		parser = new HzbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_name);
	parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
	m_count = parser->ReadBracketedCountAndLeftCurly();

	if (m_count == 0) {
		parser->Dispose();
		delete parser;
		return;
	}

	m_entries = new Hazard*[m_count];
	if (m_entries == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	Context* context = static_cast<Context*>(p_context);
	for (LegoU32 i = 0; i < m_count; i++) {
		m_entries[i] = NULL;

		switch (parser->GetNextToken()) {
		case GolFileParser::e_unknown0x28:
			m_entries[i] = new FallingPillarHazard;
			break;
		case GolFileParser::e_unknown0x29:
			m_entries[i] = new SphinxHazard;
			break;
		case GolFileParser::e_unknown0x2a:
			m_entries[i] = new HammerHazard;
			break;
		case GolFileParser::e_unknown0x2b:
			m_entries[i] = new GhostHazard;
			break;
		case GolFileParser::e_unknown0x2c:
			m_entries[i] = new LavaGeyserHazard;
			break;
		case GolFileParser::e_unknown0x2d:
			m_entries[i] = new CodePuzzleHazard;
			break;
		case GolFileParser::e_unknown0x2e:
			m_entries[i] = new RocketHazard;
			break;
		case GolFileParser::e_unknown0x2f:
			m_entries[i] = new SnowfallHazard;
			break;
		case GolFileParser::e_unknown0x30:
			m_entries[i] = new SmokeVentHazard;
			break;
		case GolFileParser::e_unknown0x32:
			m_entries[i] = new MovingObstacleHazard;
			break;
		case GolFileParser::e_unknown0x33:
			m_entries[i] = new LauncherHazard;
			break;
		case GolFileParser::e_unknown0x34:
			m_entries[i] = new TriggeredAnimationHazard;
			break;
		case GolFileParser::e_unknown0x36:
			m_entries[i] = new OscillatorHazard;
			break;
		case GolFileParser::e_unknown0x3d:
			m_entries[i] = new MultiLauncherHazard;
			break;
		case GolFileParser::e_unknown0x3e:
			m_entries[i] = new RollingRockHazard;
			break;
		case GolFileParser::e_unknown0x3f:
			m_entries[i] = new CurseDropHazard;
			break;
		case GolFileParser::e_unknown0x40:
			m_entries[i] = new SweepCannonHazard;
			break;
		case GolFileParser::e_unknown0x43:
			m_entries[i] = new CannonballRainHazard;
			break;
		case GolFileParser::e_unknown0x48:
			m_entries[i] = new GrabberHazard;
			break;
		case GolFileParser::e_unknown0x49:
			m_entries[i] = new WarpPadHazard;
			break;
		default:
			break;
		}

		if (m_entries[i] == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_entries[i]->Load(context, parser);
	}

	parser->ReadRightCurly();
	parser->Dispose();
	delete parser;
}

// FUNCTION: LEGORACERS 0x0048aa70
void HazardManager::Destroy()
{
	LegoU32 i;

	if (m_entries) {
		for (i = 0; i < m_count; i++) {
			m_entries[i]->Reset();
			delete m_entries[i];
		}

		delete[] m_entries;
		m_entries = NULL;
	}

	m_count = 0;
}

// FUNCTION: LEGORACERS 0x0048aad0
void HazardManager::NotifyEventStart(LegoS32 p_unk0x04, void* p_unk0x08)
{
	LegoU32 i;

	for (i = 0; i < m_count; i++) {
		Hazard* item = m_entries[i];
		if (item->m_triggerId != -1 && item->m_triggerId == p_unk0x04) {
			item->Activate(NULL);
		}

		m_entries[i]->OnEventStart(p_unk0x04, p_unk0x08);
	}
}

// FUNCTION: LEGORACERS 0x0048ab20
void HazardManager::NotifyEventEnd(LegoS32 p_unk0x04, void* p_unk0x08)
{
	LegoU32 i;

	for (i = 0; i < m_count; i++) {
		Hazard* item = m_entries[i];
		if (item->m_triggerId != -1 && item->m_triggerId == p_unk0x04) {
			item->Deactivate(NULL);
		}

		m_entries[i]->OnEventEnd(p_unk0x04, p_unk0x08);
	}
}

// FUNCTION: LEGORACERS 0x0048ab70
void HazardManager::ForceActivate(LegoS32 p_unk0x04)
{
	LegoU32 i;

	for (i = 0; i < m_count; i++) {
		Hazard* item = m_entries[i];
		if (item->m_triggerId != -1 && item->m_triggerId == p_unk0x04) {
			item->m_state = 3;
		}
	}
}

// FUNCTION: LEGORACERS 0x0048abb0
void HazardManager::NotifyEventPair(LegoS32 p_unk0x04, LegoS32 p_unk0x08, void* p_unk0x0c)
{
	LegoU32 i;

	for (i = 0; i < m_count; i++) {
		Hazard* item = m_entries[i];
		if (item->m_triggerId != -1 && item->m_triggerId == p_unk0x04) {
			item->Activate(NULL);
		}

		item = m_entries[i];
		if (item->m_triggerId != -1 && item->m_triggerId == p_unk0x08) {
			item->Deactivate(NULL);
		}

		m_entries[i]->OnEventStart(p_unk0x04, p_unk0x0c);
		m_entries[i]->OnEventEnd(p_unk0x08, p_unk0x0c);
	}
}

// FUNCTION: LEGORACERS 0x0048ac30
void HazardManager::DispatchEventStart(LegoS32 p_unk0x04, void* p_context)
{
	Context* context = static_cast<Context*>(p_context);
	undefined unk0x08[12];
	LegoU32 i;

	for (i = 0; i < m_count; i++) {
		Hazard* item = m_entries[i];
		if (item->m_triggerId != -1 && item->CanRetrigger()) {
			item = m_entries[i];
			if (item->m_triggerId == p_unk0x04) {
				item->Activate(p_context);
			}
		}

		context->m_positionProvider->GetPosition(unk0x08);
		m_entries[i]->OnEventStart(p_unk0x04, unk0x08);
	}
}

// FUNCTION: LEGORACERS 0x0048aca0
void HazardManager::DispatchEventEnd(LegoS32 p_unk0x04, void* p_context)
{
	Context* context = static_cast<Context*>(p_context);
	undefined unk0x08[12];
	LegoU32 i;

	for (i = 0; i < m_count; i++) {
		Hazard* item = m_entries[i];
		if (item->m_triggerId != -1 && item->CanRetrigger()) {
			item = m_entries[i];
			if (item->m_triggerId == p_unk0x04) {
				item->Deactivate(p_context);
			}
		}

		context->m_positionProvider->GetPosition(unk0x08);
		m_entries[i]->OnEventEnd(p_unk0x04, unk0x08);
	}
}

// FUNCTION: LEGORACERS 0x0048ad10
void HazardManager::DispatchEventPair(LegoS32 p_unk0x04, LegoS32 p_unk0x08, void* p_context)
{
	Context* context = static_cast<Context*>(p_context);
	undefined unk0x0c[12];
	LegoU32 i;

	for (i = 0; i < m_count; i++) {
		Hazard* item = m_entries[i];
		if (item->m_triggerId != -1) {
			if (item->CanRetrigger()) {
				item = m_entries[i];
				if (item->m_triggerId == p_unk0x04) {
					item->Activate(p_context);
				}
			}
		}

		item = m_entries[i];
		if (item->m_triggerId != -1 && item->CanRetrigger()) {
			item = m_entries[i];
			if (item->m_triggerId == p_unk0x08) {
				item->Deactivate(p_context);
			}
		}

		context->m_positionProvider->GetPosition(unk0x0c);
		m_entries[i]->OnEventStart(p_unk0x04, unk0x0c);
		m_entries[i]->OnEventEnd(p_unk0x08, unk0x0c);
	}
}

// FUNCTION: LEGORACERS 0x0048add0
void HazardManager::Update(undefined4 p_unk0x04)
{
	LegoU32 i;

	for (i = 0; i < m_count; i++) {
		m_entries[i]->Update(p_unk0x04);
	}
}

// FUNCTION: LEGORACERS 0x0048ae00
void HazardManager::UpdatePerRacer(GolCamera* p_unk0x04, RaceState::Racer* p_unk0x08)
{
	LegoU32 i;

	for (i = 0; i < m_count; i++) {
		m_entries[i]->UpdatePerRacer(p_unk0x04, p_unk0x08);
	}
}

// FUNCTION: LEGORACERS 0x0048ae30
void HazardManager::Draw(GolD3DRenderDevice* p_renderer)
{
	LegoU32 i;

	for (i = 0; i < m_count; i++) {
		m_entries[i]->Draw(p_renderer);
	}
}

// FUNCTION: LEGORACERS 0x0048ae60
void HazardManager::ResetAll()
{
	LegoU32 i;

	for (i = 0; i < m_count; i++) {
		m_entries[i]->ResetState();
	}
}

// FUNCTION: LEGORACERS 0x0048ae80
HazardManager::WarpPadHazard::WarpPadHazard()
{
	m_unk0x10 = NULL;
	m_unk0x14 = 0;
}

// FUNCTION: LEGORACERS 0x0048aec0
HazardManager::WarpPadHazard::~WarpPadHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048af10
void HazardManager::WarpPadHazard::Load(Context* p_context, GolFileParser*)
{
	if (m_state) {
		Reset();
	}

	m_triggerId = 0;
	m_unk0x10 = p_context->GetPowerupManager();
	m_unk0x14 = p_context->GetMirror();
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0048af50
#pragma code_seg(".text$zz_itemi_reset")
LegoS32 HazardManager::WarpPadHazard::Reset()
{
	OnDeactivate(NULL);
	m_unk0x10 = NULL;
	m_unk0x14 = 0;
	return Hazard::Reset();
}
#pragma code_seg()

// FUNCTION: LEGORACERS 0x0048af80
void HazardManager::WarpPadHazard::OnActivate(void* p_racer)
{
	RaceState::Racer* racer = static_cast<RaceState::Racer*>(p_racer);
	if (racer && m_state != 2 && !(racer->GetFlags() & c_flagGhost)) {
		RacePowerupManager::ActionTarget target;
		target.m_direction.m_x = g_warpPadActionDirectionX;
		target.m_direction.m_y = g_warpPadActionDirectionY;
		target.m_direction.m_z = g_warpPadActionDirectionZ;
		target.m_position.m_x = g_warpPadActionPositionX;
		target.m_position.m_y = g_warpPadActionPositionY;
		target.m_position.m_z = g_warpPadActionPositionZ;

		if (m_unk0x14) {
			target.m_direction.m_y = -g_warpPadActionDirectionY;
			target.m_position.m_y = -g_warpPadActionPositionY;
		}

		target.m_source = NULL;
		m_unk0x10->SetAimTarget(&target);
		m_unk0x10->ActivateWarp(racer, 3);
		m_unk0x10->SetAimTarget(NULL);
		m_state = 2;
	}
}

// FUNCTION: LEGORACERS 0x0048b040
void HazardManager::WarpPadHazard::OnDeactivate(void* p_unk0x04)
{
	if (p_unk0x04) {
		m_state = 1;
	}
}

#pragma code_seg(".text$zz_itemi_vt14")
// FUNCTION: LEGORACERS 0x0048b060 FOLDED
void HazardManager::CurseDropHazard::Update(undefined4 p_unk0x04)
{
	if (m_state != 1) {
		Hazard::Update(p_unk0x04);
	}
}

// FUNCTION: LEGORACERS 0x0048b060 FOLDED
void HazardManager::WarpPadHazard::Update(undefined4 p_unk0x04)
{
	if (m_state != 1) {
		Hazard::Update(p_unk0x04);
	}
}
#pragma code_seg()

// FUNCTION: LEGORACERS 0x00452430 FOLDED
#pragma code_seg(".text$animatedpartresource_vt18")
LegoBool32 HazardManager::WarpPadHazard::CanRetrigger()
{
	return 1;
}
#pragma code_seg()

// FUNCTION: LEGORACERS 0x0048b080
HazardManager::OscillatorHazard::OscillatorHazard()
{
	m_unk0x10 = NULL;
	m_unk0x14 = 0.0f;
	m_unk0x18 = 0.0f;
	m_unk0x1c = 0.0f;
}

// FUNCTION: LEGORACERS 0x0048b0c0
HazardManager::OscillatorHazard::~OscillatorHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048b110
void HazardManager::OscillatorHazard::Load(Context* p_context, GolFileParser* p_parser)
{
	if (m_state) {
		Reset();
	}

	m_triggerId = -1;
	m_eventTable = p_context->GetEventTable();

	GolName name;
	::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));

	m_unk0x10 = p_context->GetTrackDatabase()->FindUnk0xb4(name);
	if (!m_unk0x10) {
		m_unk0x10 = p_context->GetTrackDatabase()->FindUnk0xc0(name);
	}

	if (!m_unk0x10) {
		m_unk0x10 = p_context->GetSharedDatabase()->FindUnk0xb4(name);
	}

	if (!m_unk0x10) {
		m_unk0x10 = p_context->GetSharedDatabase()->FindUnk0xc0(name);
	}

	m_unk0x14 = p_parser->ReadFloat();
	m_unk0x18 = p_parser->ReadFloat();
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0048b220
void HazardManager::OscillatorHazard::OnActivate(void*)
{
	m_state = 2;
	m_unk0x1c = 0.0f;
}

// FUNCTION: LEGORACERS 0x0048b240
void HazardManager::OscillatorHazard::Update(undefined4 p_elapsedMs)
{
	Hazard::Update(p_elapsedMs);

	m_unk0x1c += static_cast<LegoFloat>(static_cast<LegoU32>(p_elapsedMs));
	if (m_unk0x1c >= g_oscillatorCycleMs) {
		m_unk0x1c -= g_oscillatorCycleMs;
	}

	LegoFloat scaledTime = m_unk0x1c;
	scaledTime *= g_oscillatorInvCycleMs;
	scaledTime *= g_oscillatorTau;
	scaledTime *= g_oscillatorCosineIndexScale;

	LegoS32 index = -256 - static_cast<LegoS32>(scaledTime);
	index &= 0x3ff;
	LegoFloat scale = g_cosineTable[index];

	LegoFloat amount = m_unk0x14;
	amount *= scale;
	m_unk0x10->FUN_00411700(amount);

	amount = m_unk0x18;
	amount *= scale;
	m_unk0x10->FUN_00411730(amount);
}

// FUNCTION: LEGORACERS 0x0048b2f0
HazardManager::CurseDropHazard::CurseDropHazard()
{
	m_unk0x10 = NULL;
	m_unk0x14 = 0;
}

// FUNCTION: LEGORACERS 0x0048b330
HazardManager::CurseDropHazard::~CurseDropHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048b380
void HazardManager::CurseDropHazard::Load(Context* p_context, GolFileParser*)
{
	if (m_state) {
		Reset();
	}

	m_unk0x10 = p_context->GetPowerupManager();
	m_unk0x14 = p_context->GetMirror();
	m_triggerId = 8;
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0048b3c0
void HazardManager::CurseDropHazard::OnActivate(void*)
{
	RacePowerupManager::ActionTarget target;
	target.m_direction = g_curseDropActionDirection;

	g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
	LegoS32 positionIndex = g_randomTable[g_randomTableIndex] % c_positionCount;
	target.m_source = NULL;
	target.m_position = g_curseDropActionPositions[positionIndex];
	if (m_unk0x14) {
		target.m_position.m_y = -target.m_position.m_y;
	}

	m_unk0x10->SetAimTarget(&target);
	m_unk0x10->UseYellowPowerup(NULL, 3);
	m_unk0x10->SetAimTarget(NULL);
	m_state = 2;
}

LegoS32 HazardManager::CurseDropHazard::Reset()
{
	OnDeactivate(NULL);
	m_unk0x10 = NULL;
	m_unk0x14 = 0;
	return Hazard::Reset();
}

// FUNCTION: LEGORACERS 0x0048d470 FOLDED
void HazardManager::CurseDropHazard::OnDeactivate(void*)
{
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0048b480
HazardManager::SweepCannonHazard::SweepCannonHazard()
{
	ClearFields();
}

// FUNCTION: LEGORACERS 0x0048b4f0
HazardManager::SweepCannonHazard::~SweepCannonHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048b540
void HazardManager::SweepCannonHazard::ClearFields()
{
	m_unk0x38 = NULL;
	m_unk0x34 = NULL;
	m_unk0x48 = 0;
	m_unk0x4c = 0;
	m_unk0x50 = 0;
	m_unk0x3c = 0.0f;
	m_unk0x40 = 0.0f;
	m_unk0x44 = 0.0f;
	m_unk0x10.m_x = 0.0f;
	m_unk0x10.m_y = 0.0f;
	m_unk0x10.m_z = 0.0f;
	m_unk0x10.m_velocity.m_x = 0.0f;
	m_unk0x10.m_velocity.m_y = 0.0f;
	m_unk0x10.m_velocity.m_z = 0.0f;
	m_unk0x10.m_forward.m_x = 0.0f;
	m_unk0x10.m_forward.m_y = 0.0f;
	m_unk0x10.m_forward.m_z = 0.0f;
	m_unk0x54 = 0;
}

// FUNCTION: LEGORACERS 0x0048b580
void HazardManager::SweepCannonHazard::Load(Context* p_context, GolFileParser* p_parser)
{
	if (m_state) {
		Reset();
	}

	GolName name;
	name[0] = '\0';

	m_unk0x54 = p_context->GetMirror();
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token;
	while ((token = p_parser->GetNextToken()) != GolFileParser::e_rightCurly) {
		switch (token) {
		case GolFileParser::e_unknown0x42:
			::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));
			break;
		case GolFileParser::e_unknown0x37:
			m_unk0x10.m_x = p_parser->ReadFloat();
			m_unk0x10.m_y = p_parser->ReadFloat();
			m_unk0x10.m_z = p_parser->ReadFloat();
			if (m_unk0x54) {
				m_unk0x10.m_y = -m_unk0x10.m_y;
			}
			break;
		case GolFileParser::e_unknown0x46:
			m_unk0x50 = p_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x3b:
			m_triggerId = p_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x47:
			m_unk0x3c = p_parser->ReadFloat();
			m_unk0x40 = p_parser->ReadFloat();
			m_unk0x44 = p_parser->ReadFloat();
			break;
		default:
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}
	}

	m_unk0x34 = p_context->GetPowerupManager();
	if (name[0]) {
		m_unk0x38 = p_context->GetTrackDatabase()->FindUnk0xc0(name);
	}
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0048b700
LegoS32 HazardManager::SweepCannonHazard::Reset()
{
	OnDeactivate(NULL);
	ClearFields();
	return Hazard::Reset();
}

// FUNCTION: LEGORACERS 0x0048b720
void HazardManager::SweepCannonHazard::OnActivate(void*)
{
	m_unk0x4c = c_actionCooldownMs;
	m_state = 2;
}

// FUNCTION: LEGORACERS 0x0048b740
void HazardManager::SweepCannonHazard::Update(undefined4 p_elapsedMs)
{
	if (m_state != 1) {
		RacePowerupManager::ActionTarget target;
		Hazard::Update(p_elapsedMs);

		LegoU32 elapsedMs = static_cast<LegoU32>(p_elapsedMs);
		m_unk0x48 += elapsedMs;
		if (m_unk0x48 >= m_unk0x50) {
			m_unk0x48 = 0;
		}

		LegoU32 currentTime = m_unk0x48;
		LegoU32 halfPeriod = m_unk0x50 >> 1;
		LegoFloat lateralAngle = static_cast<LegoFloat>(static_cast<LegoS32>(currentTime)) /
								 static_cast<LegoFloat>(static_cast<LegoS32>(halfPeriod));
		lateralAngle *= m_unk0x3c;
		if (currentTime > halfPeriod) {
			lateralAngle = g_hazardPi - lateralAngle;
		}

		LegoS32 index = static_cast<LegoS32>(lateralAngle * g_sweepCannonRadiansToTableIndex) & 0x3ff;
		m_unk0x10.m_forward.m_x = g_cosineTable[index];

		index = (0xffffff00 - static_cast<LegoS32>(lateralAngle * g_negativeRadiansToTableIndex)) & 0x3ff;
		m_unk0x10.m_forward.m_y = g_cosineTable[index];
		if (m_unk0x54) {
			m_unk0x10.m_forward.m_y = -m_unk0x10.m_forward.m_y;
		}

		LegoU32 quarterPeriod = m_unk0x50 >> 2;
		LegoFloat verticalAngle = static_cast<LegoFloat>(static_cast<LegoS32>(currentTime)) /
								  static_cast<LegoFloat>(static_cast<LegoS32>(quarterPeriod));
		verticalAngle *= g_twoPi;
		verticalAngle *= g_sweepCannonRadiansToTableIndex;
		index = static_cast<LegoS32>(verticalAngle) & 0x3ff;
		m_unk0x10.m_forward.m_z = g_cosineTable[index] * m_unk0x40 + m_unk0x44;

		GolMath::NormalizeVector3(m_unk0x10.m_forward, &m_unk0x10.m_forward);

		if (m_unk0x38) {
			m_unk0x38->VTable0x04(&m_unk0x10);
			m_unk0x10.m_z -= g_sweepCannonTrackedEntityZOffset;
		}

		m_unk0x4c += elapsedMs;
		if (m_unk0x4c >= c_actionCooldownMs) {
			target.m_source = &m_unk0x10;
			m_unk0x34->SetAimTarget(&target);
			m_unk0x34->UseRedPowerup(NULL, 2);
			m_unk0x34->SetAimTarget(NULL);
			m_unk0x4c = 0;
		}
	}
}

void HazardManager::SweepCannonHazard::OnDeactivate(void*)
{
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0048b890
HazardManager::FallingPillarHazard::FallingPillarHazard()
{
	m_unk0x10 = NULL;
	m_unk0x14 = 0;
	m_unk0x18 = NULL;
	m_unk0x1c = 0;
}

// FUNCTION: LEGORACERS 0x0048b8d0
HazardManager::FallingPillarHazard::~FallingPillarHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048b920
void HazardManager::FallingPillarHazard::Load(Context* p_context, GolFileParser*)
{
	if (m_state) {
		Reset();
	}

	m_triggerId = 0x0a;
	m_eventTable = p_context->GetEventTable();
	m_unk0x14 = p_context->GetParticleAnimation();
	m_unk0x10 = p_context->GetTrackDatabase()->FindUnk0xc0("piltop");

	GolNameTable* nameTable = p_context->GetColliderTable();
	m_unk0x18 = nameTable->GetNameEntries() == NULL ? NULL : static_cast<HazardManager::ColliderRecord*>(nameTable->GetName("pilcol"));

	m_unk0x10->SetFlags(m_unk0x10->GetFlags() & ~GolAnimatedEntity::c_flagPartAnimation);
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0048b9b0 FOLDED
LegoS32 HazardManager::FallingPillarHazard::Reset()
{
	OnDeactivate(NULL);
	m_unk0x10 = NULL;
	m_unk0x14 = 0;
	m_unk0x18 = NULL;
	m_unk0x1c = 0;
	return Hazard::Reset();
}

// FUNCTION: LEGORACERS 0x0048b9b0 FOLDED
LegoS32 HazardManager::OscillatorHazard::Reset()
{
	OnDeactivate(NULL);
	m_unk0x10 = NULL;
	m_unk0x14 = 0.0f;
	m_unk0x18 = 0.0f;
	m_unk0x1c = 0.0f;
	return Hazard::Reset();
}

// FUNCTION: LEGORACERS 0x0048b9e0
void HazardManager::FallingPillarHazard::OnActivate(void*)
{
	m_unk0x10->SetFlags(m_unk0x10->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_unk0x10->FUN_0040dad0(0);
	m_unk0x10->SetFlags(m_unk0x10->GetFlags() & ~GolAnimatedEntity::c_flagLoopCurrentPart);
	m_unk0x1c = 0;
	m_state = 2;
}

void HazardManager::FallingPillarHazard::OnDeactivate(void*)
{
}

// FUNCTION: LEGORACERS 0x0048ba20
void HazardManager::FallingPillarHazard::Update(undefined4 p_elapsedMs)
{
	if (m_state != 1) {
		Hazard::Update(p_elapsedMs);

		if (m_unk0x1c == 0 && m_unk0x10->GetUnk0xb4() > 50.0f) {
			m_unk0x18->m_flags &= ~ColliderRecord::c_flagBit16;
			m_unk0x18->m_flags &= ~ColliderRecord::c_flagBit17;
			m_eventTable->FireEventsAt(7, 7, NULL);
			m_unk0x1c = 1;
		}
	}
}

// FUNCTION: LEGORACERS 0x0048ba90
void HazardManager::FallingPillarHazard::ResetState()
{
	m_state = 1;
	m_unk0x1c = 0;
	m_unk0x18->m_flags |= ColliderRecord::c_flagBit16;
	m_unk0x18->m_flags |= ColliderRecord::c_flagBit17;
	m_unk0x10->SetFlags(m_unk0x10->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_unk0x10->FUN_0040dae0(0, 0);
	m_unk0x10->VTable0x5c(0);
	m_unk0x10->SetFlags(m_unk0x10->GetFlags() & ~GolAnimatedEntity::c_flagPartAnimation);
}

// FUNCTION: LEGORACERS 0x0048bb00
HazardManager::RollingRockHazard::RollingRockHazard()
	: m_unk0x1e8(NULL), m_unk0x1ec(NULL), m_unk0x1f0(NULL), m_unk0x1f4(0.0f), m_unk0x1f8(0.0f), m_unk0x1fc(0.0f),
	  m_unk0x200(0)
{
}

// FUNCTION: LEGORACERS 0x0048bba0
HazardManager::RollingRockHazard::~RollingRockHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048bbf0
void HazardManager::RollingRockHazard::Load(Context* p_context, GolFileParser* p_parser)
{
	if (m_state) {
		Reset();
	}

	m_eventTable = p_context->GetEventTable();
	m_unk0x1ec = p_context->GetEventQueue();

	p_parser->ReadLeftCurly();

	GolName name;
	::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));
	m_unk0x1e8 = p_context->GetTrackDatabase()->FindUnk0xc0(name);

	LegoU32 state = 1;
	if (!::strncmp(name, "rk", 2)) {
		m_unk0x200 = state;
	}

	m_triggerId = p_parser->ReadInteger();
	LegoFloat activeValue = p_parser->ReadFloat();
	m_unk0x1f4 = p_parser->ReadFloat();
	m_unk0x1f8 = p_parser->ReadFloat();
	m_unk0x1fc = p_parser->ReadFloat();
	p_parser->ReadRightCurly();

	GolAnimatedEntity* entity = m_unk0x1e8;
	entity->FUN_0040d650();
	entity->SetActiveValue(activeValue);
	m_unk0x0f4.FUN_100234c0(m_unk0x1e8->VTable0x58(0), m_unk0x1e8->GetModelPart(), g_rollingRockModelDistance);

	LegoFloat radius = m_unk0x1f4 * 0.5f;
	LegoFloat halfDimension = m_unk0x1f8 * 0.5f;
	if (halfDimension > radius) {
		radius = halfDimension;
	}

	halfDimension = m_unk0x1fc * 0.5f;
	if (halfDimension > radius) {
		radius = halfDimension;
	}

	m_unk0x0f4.FUN_10026fa0(radius);
	m_unk0x10.Initialize(&m_unk0x0f4, g_unk0x004b42ec, m_unk0x1f4, m_unk0x1f8, m_unk0x1fc);
	m_state = state;
}

// FUNCTION: LEGORACERS 0x0048bda0
void HazardManager::RollingRockHazard::Reset()
{
	OnDeactivate(NULL);
	m_unk0x200 = 0;
	m_unk0x1f4 = 0.0f;
	m_unk0x1f8 = 0.0f;
	m_unk0x1fc = 0.0f;
	m_unk0x1e8 = NULL;
	m_unk0x1ec = NULL;
	m_unk0x1f0 = NULL;
	m_unk0x0f4.VTable0x54();
	m_unk0x10.Destroy();
	Hazard::Reset();
}

// FUNCTION: LEGORACERS 0x0048be00
void HazardManager::RollingRockHazard::OnActivate(void*)
{
	LegoEventQueue::Descriptor descriptor;
	descriptor.m_unk0x00 = 3;
	descriptor.m_unk0x04 = 1;
	descriptor.m_unk0x0c = 0;
	descriptor.m_data = &m_unk0x10;

	m_unk0x1f0 = m_unk0x1ec->FUN_0042fb50(this, &descriptor);
	m_state = 2;
}

// FUNCTION: LEGORACERS 0x0048be50
void HazardManager::RollingRockHazard::OnDeactivate(void*)
{
	if (m_unk0x1f0 != NULL) {
		m_unk0x1f0->m_active = 0;
		m_unk0x1f0 = NULL;
	}

	m_state = 1;
}

// STUB: LEGORACERS 0x0048be70
void HazardManager::RollingRockHazard::Update(undefined4 p_elapsedMs)
{
	if (m_state != 1) {
		Hazard::Update(p_elapsedMs);

		GolSceneNode* node = m_unk0x1e8->VTable0x58(0);
		GolTransformBase* transform = node->VTable0x18(1);

		GolVec3 localPosition;
		localPosition.m_x = 0.0f;
		localPosition.m_y = 0.0f;
		localPosition.m_z = 0.0f;

		GolVec3 right;
		GolVec3 forward;
		transform->VTable0x20(&right, &forward);

		GolVec3 origin = localPosition;
		transform->VTable0x04(&origin, &localPosition);

		if (m_unk0x200) {
			do {
				GolVec3 transformedRight = right;
				GolVec3 transformedForward = forward;
				transform->VTable0x0c(&transformedRight, &right);
				transform->VTable0x0c(&transformedForward, &forward);
				transform = transform->m_unk0x04;
			} while (transform != NULL);
		}

		LegoFloat scale = m_unk0x1e8->GetModel(0)->GetScale() * m_unk0x1e8->GetUnk0x58();
		localPosition.m_x *= scale;
		localPosition.m_y *= scale;
		localPosition.m_z *= scale;
		GolVec3 worldPosition;
		m_unk0x1e8->VTable0x2c(localPosition, &worldPosition);
		m_unk0x10.m_centerOfMassWorld = worldPosition;

		if (m_unk0x200) {
			GolVec3 worldRight;
			GolVec3 worldForward;
			m_unk0x1e8->VTable0x34(right, &worldRight);
			m_unk0x1e8->VTable0x34(forward, &worldForward);
			m_unk0x0f4.VTable0x40(worldRight, worldForward);
		}

		m_unk0x0f4.SetCenter(worldPosition);
	}
}

// FUNCTION: LEGORACERS 0x0048c020
HazardManager::SphinxHazard::SphinxHazard()
{
	m_unk0x10 = 0;
	m_unk0x14 = NULL;
	m_unk0x18 = NULL;
	m_unk0x1c = NULL;
	m_unk0x20 = NULL;
}

// FUNCTION: LEGORACERS 0x0048c070
HazardManager::SphinxHazard::~SphinxHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048c0c0
void HazardManager::SphinxHazard::Load(Context* p_context, GolFileParser*)
{
	if (m_state) {
		Reset();
	}

	m_triggerId = 0x0c;
	m_eventTable = p_context->GetEventTable();
	m_unk0x10 = p_context->GetParticleAnimation();
	m_unk0x14 = p_context->GetSharedDatabase();

	GolNameTable* nameTable = p_context->GetColliderTable();
	m_unk0x20 = nameTable->GetNameEntries() == NULL ? NULL : static_cast<HazardManager::ColliderRecord*>(nameTable->GetName("sphinx"));
	m_unk0x1c = m_unk0x14->FindUnk0xc0("blowup");
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0048c150
LegoS32 HazardManager::SphinxHazard::Reset()
{
	OnDeactivate(NULL);
	m_unk0x10 = 0;
	m_unk0x14 = NULL;
	m_unk0x18 = NULL;
	m_unk0x1c = NULL;
	m_unk0x20 = NULL;
	return Hazard::Reset();
}

// FUNCTION: LEGORACERS 0x0048c180
void HazardManager::SphinxHazard::OnActivate(void*)
{
	MabMaterialAnimation0x14* animation = NULL;
	if (m_unk0x1c->GetModelDistance(0) == g_sphinxInactiveModelDistance) {
		return;
	}

	int(__cdecl * compare)(const LegoChar*, const LegoChar*, size_t) = ::strncmp;
	LegoU32 i = 0;
	while (i < m_unk0x14->GetUnk0x74()) {
		GolName name;
		::strncpy(name, m_unk0x14->GetUnk0x78()[i], sizeof(name));
		if (compare(name, "blowup", sizeof(name)) == 0) {
			animation = m_unk0x14->VTable0x4c(i);
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
		m_unk0x18 = item2;

		GolVec3 position;
		m_unk0x1c->VTable0x04(&position);
		m_eventTable->StartEventsAt(0x10, &position);
	}

	m_unk0x20->m_flags |= ColliderRecord::c_flagBit16;
	m_unk0x20->m_flags |= ColliderRecord::c_flagBit17;
	m_state = 2;
}

// FUNCTION: LEGORACERS 0x0048c2a0
void HazardManager::SphinxHazard::OnDeactivate(void*)
{
	if (m_unk0x18 != NULL && m_unk0x18->IsAssigned()) {
		return;
	}

	for (LegoS32 i = 0; i < c_modelDistanceCount; i++) {
		m_unk0x1c->SetModelDistance(i, g_sphinxInactiveModelDistance);
	}

	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0048c2e0
void HazardManager::SphinxHazard::Update(undefined4 p_elapsedMs)
{
	if (m_state == 1) {
		return;
	}

	Hazard::Update(p_elapsedMs);
	if (m_unk0x18 != NULL) {
		if (m_unk0x18->IsAssigned()) {
			return;
		}

		GolVec3 position;
		m_unk0x1c->VTable0x04(&position);
		m_eventTable->EndEventsAt(0x10, &position);
		OnDeactivate(NULL);
		return;
	}
	OnDeactivate(NULL);
}

// FUNCTION: LEGORACERS 0x0048c340
void HazardManager::SphinxHazard::ResetState()
{
	MabMaterialAnimation0x14* animation = NULL;
	if (m_state == 1 && m_unk0x1c->GetModelDistance(0) != g_sphinxInactiveModelDistance) {
		return;
	}

	int(__cdecl * compare)(const LegoChar*, const LegoChar*, size_t) = ::strncmp;
	m_unk0x20->m_flags &= ~ColliderRecord::c_flagBit16;
	m_unk0x20->m_flags &= ~ColliderRecord::c_flagBit17;
	m_unk0x1c->SetModelDistance(0, 640000.0f);

	LegoU32 i = 0;
	while (TRUE) {
		if (i >= m_unk0x14->GetUnk0x74()) {
			break;
		}

		GolName name;
		::strncpy(name, m_unk0x14->GetUnk0x78()[i], sizeof(name));
		if (compare(name, "blowup", sizeof(name)) == 0) {
			animation = m_unk0x14->VTable0x4c(i);
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

// FUNCTION: LEGORACERS 0x0048c440
HazardManager::CannonballRainHazard::CannonballRainHazard()
{
	ClearFields();
}

// FUNCTION: LEGORACERS 0x0048c4b0
HazardManager::CannonballRainHazard::~CannonballRainHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048c500
void HazardManager::CannonballRainHazard::ClearFields()
{
	m_unk0x38 = NULL;
	m_unk0x34 = NULL;
	m_unk0x3c = 0;
	m_unk0x40 = 0;
	m_unk0x18.m_x = 0.0f;
	m_unk0x18.m_y = 0.0f;
	m_unk0x18.m_z = 0.0f;
	m_unk0x24.m_x = 0.0f;
	m_unk0x24.m_y = 0.0f;
	m_unk0x24.m_z = 0.0f;
	m_unk0x10[0] = '\0';
}

// FUNCTION: LEGORACERS 0x0048c530
void HazardManager::CannonballRainHazard::Load(Context* p_context, GolFileParser* p_parser)
{
	if (m_state) {
		Reset();
	}

	GolName entityName;
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token;
	while ((token = p_parser->GetNextToken()) != GolFileParser::e_rightCurly) {
		switch (token) {
		case GolFileParser::e_unknown0x45:
			::strncpy(m_unk0x10, p_parser->ReadStringWithMaxLength(sizeof(m_unk0x10)), sizeof(m_unk0x10));
			break;
		case GolFileParser::e_unknown0x42:
			::strncpy(entityName, p_parser->ReadStringWithMaxLength(sizeof(entityName)), sizeof(entityName));
			break;
		case GolFileParser::e_unknown0x3b:
			m_triggerId = p_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x44:
			m_unk0x40 = p_parser->ReadInteger();
			break;
		default:
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}
	}

	m_unk0x34 = p_context->GetPowerupManager();
	m_unk0x38 = p_context->GetTrackDatabase()->FindUnk0xc0(entityName);
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0048c650
LegoS32 HazardManager::CannonballRainHazard::Reset()
{
	OnDeactivate(NULL);
	ClearFields();
	return Hazard::Reset();
}

// FUNCTION: LEGORACERS 0x0048c670
void HazardManager::CannonballRainHazard::OnActivate(void*)
{
	m_state = 2;
	m_unk0x3c = m_unk0x40;
}

// FUNCTION: LEGORACERS 0x0048c680
void HazardManager::CannonballRainHazard::Update(undefined4 p_elapsedMs)
{
	if (m_state == 1) {
		return;
	}

	LegoU32 elapsedMs = p_elapsedMs;
	Hazard::Update(p_elapsedMs);

	m_unk0x3c += elapsedMs;
	if (m_unk0x3c < m_unk0x40) {
		return;
	}

	m_unk0x38->VTable0x5c(0);
	GolSceneNode* node = m_unk0x38->VTable0x58(0);
	GolTransformBase* transform = node->VTable0x18(1);

	GolVec3 position;
	transform->GetPosition(&position);

	GolVec3 right;
	transform->GetRight(&right);

	LegoFloat scale = m_unk0x38->GetModel(0)->GetScale();
	scale *= m_unk0x38->GetUnk0x58();
	position.m_x *= scale;
	position.m_y *= scale;
	position.m_z *= scale;

	m_unk0x38->VTable0x2c(position, &m_unk0x24);

	GolVec3 transformedRight;
	m_unk0x38->VTable0x34(right, &transformedRight);

	LegoFloat transformedOffset = transformedRight.m_x;
	transformedOffset *= g_cannonballRainTransformOffsetScale;
	m_unk0x24.m_x -= transformedOffset;
	m_unk0x30 = 30.0f;
	transformedOffset = transformedRight.m_y;
	transformedOffset *= g_cannonballRainTransformOffsetScale;
	m_unk0x24.m_y -= transformedOffset;
	transformedOffset = transformedRight.m_z;
	transformedOffset *= g_cannonballRainTransformOffsetScale;
	m_unk0x24.m_z -= transformedOffset;

	g_randomTableIndex++;
	g_randomTableIndex &= c_randomTableMask;
	LegoS32 random = g_randomTable[g_randomTableIndex] % 4;
	m_unk0x18.m_x = static_cast<LegoFloat>(random) + m_unk0x24.m_x - g_violetShoalTwo;

	g_randomTableIndex++;
	g_randomTableIndex &= c_randomTableMask;
	random = g_randomTable[g_randomTableIndex] % 4;
	m_unk0x18.m_y = static_cast<LegoFloat>(random) + m_unk0x24.m_y - g_violetShoalTwo;
	if (m_unk0x18.m_x == m_unk0x24.m_x && m_unk0x18.m_y == m_unk0x24.m_y) {
		LegoFloat positionX = m_unk0x18.m_x;
		positionX += g_violetShoalTwo;
		m_unk0x18.m_x = positionX;
	}

	LegoFloat positionZ = m_unk0x24.m_z;
	positionZ += 1.0f;
	m_unk0x18.m_z = positionZ;

	RacePowerupManager::ActionTarget target;
	target.m_materialName = m_unk0x10;
	m_unk0x34->SetAimTarget(&target);
	m_unk0x34->UseRedPowerup(NULL, 0);
	m_unk0x34->SetAimTarget(NULL);
	m_unk0x3c = 0;
}

// FUNCTION: LEGORACERS 0x0048d470 FOLDED
void HazardManager::CannonballRainHazard::OnDeactivate(void*)
{
	m_state = 1;
}

void HazardManager::OscillatorHazard::OnDeactivate(void*)
{
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0048c850
HazardManager::GhostHazard::GhostHazard()
{
	ClearFields();
}

// FUNCTION: LEGORACERS 0x0048c8e0
HazardManager::GhostHazard::~GhostHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048c930
void HazardManager::GhostHazard::ClearFields()
{
	m_unk0x50 = NULL;
	m_unk0x54 = NULL;
	m_unk0x38 = NULL;
	m_unk0x3c = NULL;
	m_unk0x40 = NULL;
	m_unk0x44 = NULL;
	m_unk0x48 = NULL;
	m_unk0x4c = NULL;
	m_unk0x58 = NULL;
	m_unk0x5c = 0;
	m_unk0x60 = 0;
	m_unk0x64 = 0;
	m_unk0x68 = 0.0f;
	m_unk0x6c = 0;
}

// FUNCTION: LEGORACERS 0x0048c960
void HazardManager::GhostHazard::Load(Context* p_context, GolFileParser*)
{
	if (m_state) {
		Reset();
	}

	Context* context = p_context;
	m_triggerId = 10;
	m_eventTable = context->GetEventTable();
	m_unk0x40 = context->GetEventQueue();
	m_unk0x48 = context->GetParticleAnimation();
	m_unk0x54 = context->GetSoundSource();
	m_unk0x58 = context->GetRaceState();

	m_unk0x38 = context->GetTrackDatabase()->FindUnk0xc0("ghostly");
	m_unk0x3c = context->GetTrackDatabase()->FindUnk0xb4("gtrail");

	{
		GolModelEntity* modelEntity = m_unk0x70;
		LegoS32 i = sizeOfArray(m_unk0x70);
		do {
			modelEntity->VTable0x50(m_unk0x3c->GetModel(0), m_unk0x3c->GetModelDistance(0));
			modelEntity++;
		} while (--i);
	}

	LegoS32 i;
	for (i = 0; i < sizeOfArray(m_unk0x70); i++) {
		m_unk0x3c->SetModelDistance(i, 0.0f);
	}

	m_unk0x10.FUN_10026fa0(m_unk0x38->GetModel(0)->GetRadius() + g_ghostTriggerRadiusPadding);

	LegoU32 frameCount = 0;
	CmbModelPartData0x28* partData = m_unk0x38->GetModelPart()->GetPartData();
	LegoFloat inverseDuration = 1.0f / partData->GetUnk0x00();
	frameCount = partData->GetFrameCount();
	LegoFloat frameCountFloat = static_cast<LegoFloat>(frameCount);
	m_unk0x60 = static_cast<LegoS32>(inverseDuration * frameCountFloat);
	m_unk0x6c = 0;
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0048ca80
LegoS32 HazardManager::GhostHazard::Reset()
{
	OnDeactivate(NULL);

	GolModelEntity* modelEntity = m_unk0x70;
	LegoS32 i = sizeOfArray(m_unk0x70);
	do {
		modelEntity->VTable0x54();
		modelEntity++;
	} while (--i);

	ClearFields();
	return Hazard::Reset();
}

// FUNCTION: LEGORACERS 0x0048cac0
void HazardManager::GhostHazard::OnActivate(void*)
{
	LegoEventQueue::Descriptor descriptor;
	descriptor.m_unk0x00 = 4;
	descriptor.m_unk0x04 = 1;
	descriptor.m_unk0x08 = 0;
	descriptor.m_unk0x0c = 0;
	descriptor.m_worldEntity = &m_unk0x10;

	m_unk0x44 = m_unk0x40->FUN_0042fb50(this, &descriptor);
	m_unk0x5c = 0;
	m_unk0x64 = 0x1f4;
	m_unk0x50 = m_unk0x54->AcquireSoundById(0xbc4);

	if (m_unk0x50 != NULL) {
		m_unk0x50->Play(TRUE);
		m_unk0x50->SetDistanceRangeWithMinSquared(
			g_ghostLoopSoundMinDistance * g_ghostLoopSoundMinDistance,
			g_ghostSoundMaxDistance
		);
	}

	m_state = 2;
}

// FUNCTION: LEGORACERS 0x0048cb60
void HazardManager::GhostHazard::OnDeactivate(void*)
{
	if (m_unk0x4c != NULL) {
		m_unk0x48->FUN_00489f30(m_unk0x4c);
		m_unk0x4c = NULL;
	}

	if (m_unk0x44 != NULL) {
		m_unk0x44->m_active = 0;
		m_unk0x44 = NULL;
	}

	if (m_unk0x50 != NULL) {
		m_unk0x54->ReleaseSound(m_resource0x50);
		m_unk0x50 = NULL;
	}

	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0048cbb0
void HazardManager::GhostHazard::Update(undefined4 p_elapsedMs)
{
	LegoU32 elapsedMs = static_cast<LegoU32>(p_elapsedMs);
	m_unk0x6c += elapsedMs;

	if (m_state != 1) {
		LegoU32 frameOffset;
		LegoU32 frame = static_cast<LegoS32>(m_unk0x38->GetUnk0xb4() / m_unk0x38->GetUnk0xb8());
		LegoFloat scale = m_unk0x38->GetModel(0)->GetScale() * m_unk0x38->GetUnk0x58();
		GolSceneNode* node = m_unk0x38->VTable0x58(0);
		GolTransformBase* transform = node->VTable0x18(1);

		Hazard::Update(elapsedMs);

		SoundVector position;
		transform->GetPosition(&position);
		position.m_x *= scale;
		position.m_y *= scale;
		position.m_z *= scale;

		GolVec3 worldPosition;
		m_unk0x38->VTable0x2c(position, &worldPosition);
		m_unk0x10.SetCenter(worldPosition);

		if (m_unk0x4c == NULL) {
			m_unk0x4c = m_unk0x48->FUN_00489d70("ghsttrl", NULL, NULL, NULL);
		}

		if (m_unk0x4c != NULL) {
			worldPosition.m_z -= 5.0f;
			if (m_unk0x4c->m_particle != NULL) {
				m_unk0x4c->m_particle->FUN_00489660(&worldPosition);
			}
			worldPosition.m_z += 5.0f;
		}

		if (m_unk0x6c > c_racerSearchIntervalMs) {
			m_unk0x6c = 0;
			if (m_unk0x58->FindNearestRacerInRange(&position, 0.0f, g_ghostRacerSearchDistanceSquared) != NULL) {
				m_unk0x54->PlaySpatialSoundById(
					c_soundId0xbc5,
					&position,
					g_ghostOneShotSoundMinDistance,
					g_ghostSoundMaxDistance,
					1.0f,
					1.0f
				);
			}
		}

		GolModelEntity* modelEntity;
		for (frameOffset = c_trailFrameOffsetStep, modelEntity = m_unk0x70; frameOffset < c_trailFrameOffsetEnd;
			 frameOffset += c_trailFrameOffsetStep, modelEntity++) {
			LegoU32 trailFrame;
			if (frameOffset < frame) {
				trailFrame = frame - frameOffset;
			}
			else {
				trailFrame = m_unk0x60 - frameOffset + frame;
			}

			GolQuat rotation;
			m_unk0x38->FUN_0040e420(0, 1, 0, trailFrame, &rotation);
			m_unk0x38->FUN_0040e3c0(0, 1, 0, trailFrame, &position);

			GolMatrix3 orientation;
			GolMath::FUN_00449340(&rotation, &orientation.m_m[0][0]);
			modelEntity->VTable0x3c(orientation);

			position.m_x *= scale;
			position.m_y *= scale;
			position.m_z *= scale;
			modelEntity->VTable0x08(position);
		}

		if (m_unk0x50 != NULL) {
			m_unk0x38->VTable0x2c(position, &worldPosition);
			m_unk0x50->SetPosition(&worldPosition);

			LegoU32 soundElapsedMs = m_unk0x64;
			soundElapsedMs += static_cast<LegoU32>(p_elapsedMs);
			m_unk0x64 = soundElapsedMs;
			if (soundElapsedMs >= c_soundFrequencyUpdateMs) {
				m_unk0x64 = 0;

				LegoU32 randomIndex = g_randomTableIndex + 1;
				randomIndex &= c_randomTableMask;
				g_randomTableIndex = randomIndex;

				LegoU16 randomValue = g_randomTable[randomIndex];
				LegoS32 randomFrequency = randomValue;
				randomFrequency %= c_randomFrequencyVariantCount;
				LegoFloat frequencyScale = static_cast<LegoFloat>(randomFrequency);
				frequencyScale *= g_carBuildPreviewMouseScale;
				frequencyScale *= g_ghostFrequencyScaleJitter;
				m_unk0x68 = frequencyScale;
			}

			LegoFloat phase = static_cast<LegoFloat>(static_cast<LegoS32>(m_unk0x64));
			phase *= 0.002f;
			phase *= g_hazardPi;
			phase *= g_negativeRadiansToTableIndex;
			LegoS32 index = 0xffffff00 - static_cast<LegoS32>(phase);
			index &= c_randomTableMask;
			m_unk0x50->SetFrequencyScale(1.0f - g_cosineTable[index] * m_unk0x68);
		}
	}
}

// FUNCTION: LEGORACERS 0x0048ce90
void HazardManager::GhostHazard::VTable0x00(LegoEventQueue::CallbackData* p_data)
{
	RaceState::Racer* racer = static_cast<RaceState::Racer*>(p_data->m_data);
	RaceState::Racer::Physics* field0x3e8 = &racer->m_physics;

	if ((field0x3e8->m_flags & RaceState::Racer::Physics::c_flagSpinning) || field0x3e8->m_forwardSpeed == 0.0f ||
		(racer->m_flags & c_racerFlags0xd04Bit0)) {
		return;
	}

	field0x3e8->StartSpin(1.0f, 0.01f, 0.0f);
	racer->StartSpinOut();

	GolVec3 impulse;
	impulse.m_y = 0.0f;
	impulse.m_z = 0.0f;

	field0x3e8->m_velocity.m_x = 0.0f;
	field0x3e8->m_velocity.m_y = impulse.m_y;
	field0x3e8->m_velocity.m_z = impulse.m_z;

	impulse.m_y = impulse.m_x = 0.0f;
	LegoFloat impulseZ = g_ghostImpulseVectorZ;
	impulse.m_z = impulseZ;
	field0x3e8->ApplyImpulse(&impulse, &impulse);

	racer->PlayReaction(FALSE);

	SoundVector position;
	racer->m_visuals.m_carEntity->VTable0x04(&position);
	m_unk0x54->PlaySpatialSoundById(
		c_soundId0xbc7,
		&position,
		g_ghostOneShotSoundMinDistance,
		g_ghostSoundMaxDistance,
		1.0f,
		1.0f
	);
}

// FUNCTION: LEGORACERS 0x0048cf90
void HazardManager::GhostHazard::Draw(GolD3DRenderDevice* p_renderer)
{
	if (m_state != 1) {
		LegoS32 alpha = 0x2a;
		GolModelEntity* modelEntity = &m_unk0x70[2];
		LegoS32 i = sizeOfArray(m_unk0x70);

		do {
			p_renderer->SetAlphaOverride(alpha, TRUE);
			p_renderer->VTable0x94(modelEntity);
			alpha += 0x2a;
			modelEntity--;
		} while (--i);

		p_renderer->ClearAlphaOverride();
	}
}

// FUNCTION: LEGORACERS 0x0048cff0
HazardManager::HammerHazard::HammerHazard()
{
	m_unk0x10 = NULL;
}

// FUNCTION: LEGORACERS 0x0048d030
HazardManager::HammerHazard::~HammerHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048d080
void HazardManager::HammerHazard::Load(Context* p_context, GolFileParser*)
{
	if (m_state) {
		Reset();
	}

	m_triggerId = 0x32;
	m_eventTable = p_context->GetEventTable();

	GolName name;
	::strncpy(name, "rkhamm", sizeof(name));
	name[6] = '0';
	name[7] = '2';

	m_unk0x10 = p_context->GetTrackDatabase()->FindUnk0xc0(name);
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0048d110
LegoS32 HazardManager::HammerHazard::Reset()
{
	OnDeactivate(NULL);
	m_unk0x10 = NULL;
	return Hazard::Reset();
}

// FUNCTION: LEGORACERS 0x0048d130
void HazardManager::HammerHazard::OnActivate(void*)
{
	m_unk0x14 = 7;
	m_state = 2;
}

// FUNCTION: LEGORACERS 0x0048d150
void HazardManager::HammerHazard::Update(undefined4 p_elapsedMs)
{
	if (m_state == 1) {
		return;
	}

	Hazard::Update(p_elapsedMs);
	if (!m_unk0x10) {
		return;
	}

	LegoFloat frame = m_unk0x10->GetUnk0xb4();
	LegoU32 state = m_unk0x14;
	LegoU32 active = state;
	active &= 1;
	if (active) {
		if ((frame > g_item0x2aTriggerStart0 && frame < g_item0x2aTriggerEnd0) ||
			(frame > g_item0x2aTriggerStart1 && frame < g_item0x2aTriggerEnd1)) {
			m_eventTable->FireEventsAt(0x2b, 0x2b, NULL);
			m_unk0x14 &= ~1;
		}
	}
	else if (
		(frame > g_item0x2aResetStart0 && frame < g_item0x2aResetEnd0) ||
		(frame > g_item0x2aResetStart1 && frame < g_item0x2aResetEnd1)
	) {
		m_unk0x14 = state | 1;
	}
}

// FUNCTION: LEGORACERS 0x0048d240
HazardManager::CodePuzzleHazard::CodePuzzleHazard()
{
	ClearFields();
}

// FUNCTION: LEGORACERS 0x0048d2b0
HazardManager::CodePuzzleHazard::~CodePuzzleHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048d300
void HazardManager::CodePuzzleHazard::Load(Context* p_context, GolFileParser*)
{
	if (m_state) {
		Reset();
	}

	m_triggerId = -1;
	m_eventTable = p_context->GetEventTable();

	GolWorldDatabase* worldDatabase = p_context->GetTrackDatabase();
	GolModelEntity* modelEntity;
	if (!worldDatabase->GetUnk0xb4NameEntries()) {
		modelEntity = NULL;
	}
	else {
		modelEntity = worldDatabase->GetUnk0xb4Name("mmcode1");
	}
	m_unk0x10 = modelEntity;

	worldDatabase = p_context->GetTrackDatabase();
	if (!worldDatabase->GetUnk0xb4NameEntries()) {
		modelEntity = NULL;
	}
	else {
		modelEntity = worldDatabase->GetUnk0xb4Name("mmcode2");
	}
	m_unk0x14 = modelEntity;

	worldDatabase = p_context->GetTrackDatabase();
	if (!worldDatabase->GetUnk0xb4NameEntries()) {
		modelEntity = NULL;
	}
	else {
		modelEntity = worldDatabase->GetUnk0xb4Name("mmcode3");
	}
	m_unk0x18 = modelEntity;

	MabMaterialAnimation0x14* animation = p_context->GetTrackDatabase()->VTable0x4c(0);
	m_unk0x1c = &animation->GetUnk0x0c()[5];
	m_unk0x20 = &animation->GetUnk0x0c()[4];
	m_unk0x24 = &animation->GetUnk0x0c()[3];
	m_unk0x1c->SetUnk0x0c(0.003f);
	m_unk0x20->SetUnk0x0c(0.004f);
	m_unk0x24->SetUnk0x0c(0.005f);
	m_unk0x28 = animation->GetUnk0x04();
	m_unk0x2c = animation->GetUnk0x08();
	m_state = 1;
	OnActivate(NULL);
}

// FUNCTION: LEGORACERS 0x0048d400
LegoS32 HazardManager::CodePuzzleHazard::Reset()
{
	return ClearFields();
}

// FUNCTION: LEGORACERS 0x0048d410
LegoS32 HazardManager::CodePuzzleHazard::ClearFields()
{
	m_unk0x10 = NULL;
	m_unk0x14 = NULL;
	m_unk0x18 = NULL;
	m_unk0x1c = NULL;
	m_unk0x20 = NULL;
	m_unk0x24 = NULL;
	m_unk0x30 = 0;
	m_unk0x31 = 0;
	m_unk0x32 = 0;
	m_unk0x33 = 0;
	m_unk0x34 = 0;
	m_unk0x35 = 0;
	m_unk0x36 = 0;
	m_unk0x38 = 0;
	m_unk0x28 = NULL;
	m_unk0x2c = 0;
	return 0;
}

// FUNCTION: LEGORACERS 0x0048d450
void HazardManager::CodePuzzleHazard::OnActivate(void*)
{
	m_unk0x36 = 0;
	ResetCodeModels();
	m_unk0x38 = 1;
	m_state = 2;
}

// FUNCTION: LEGORACERS 0x0048d470 FOLDED
void HazardManager::CodePuzzleHazard::OnDeactivate(void*)
{
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0048d480
void HazardManager::CodePuzzleHazard::OnEventStart(LegoS32 p_unk0x04, void* p_unk0x08)
{
	if (p_unk0x04 == m_unk0x33 || p_unk0x04 == m_unk0x34 || p_unk0x04 == m_unk0x35) {
		m_unk0x36 = 0;
	}
	else if (p_unk0x04 == m_unk0x30) {
		m_unk0x36 = 1;
	}
	else if (p_unk0x04 == m_unk0x31) {
		if (m_unk0x36 == 1) {
			m_unk0x36 = 3;
		}
	}
	else if (p_unk0x04 == m_unk0x32 && m_unk0x36 == 3) {
		m_eventTable->FireEventsAt(c_successFirstEvent, c_successFirstEvent, NULL);
		m_unk0x36 = 0;
		m_unk0x1c->FUN_10025da0(m_unk0x1c->GetUnk0x00(), m_unk0x1c->GetUnk0x04(), TRUE);
		m_unk0x20->FUN_10025da0(m_unk0x20->GetUnk0x00(), m_unk0x20->GetUnk0x04(), TRUE);
		m_unk0x24->FUN_10025da0(m_unk0x24->GetUnk0x00(), m_unk0x24->GetUnk0x04(), TRUE);
		m_unk0x38 = c_delayMs;
		ResetCodeModels();
		m_eventTable->StartEventsAt(c_successSecondEvent, NULL);
	}

	switch (p_unk0x04) {
	case 200:
	case 202:
	case 204:
		m_eventTable->FireEventsAt(c_goodInputEvent, c_goodInputEvent, static_cast<GolVec3*>(p_unk0x08));
		return;
	case 201:
	case 203:
	case 205:
		m_eventTable->FireEventsAt(c_badInputEvent, c_badInputEvent, static_cast<GolVec3*>(p_unk0x08));
		return;
	case 207:
		if (m_unk0x30 == c_firstCodeEvent) {
			m_eventTable->FireEventsAt(c_correctCodeEvent, c_correctCodeEvent, static_cast<GolVec3*>(p_unk0x08));
		}
		else {
			m_eventTable->FireEventsAt(c_wrongCodeEvent, c_wrongCodeEvent, static_cast<GolVec3*>(p_unk0x08));
		}
		break;
	case 208:
		if (m_unk0x31 == c_secondCodeEvent) {
			m_eventTable->FireEventsAt(c_correctCodeEvent, c_correctCodeEvent, static_cast<GolVec3*>(p_unk0x08));
		}
		else {
			m_eventTable->FireEventsAt(c_wrongCodeEvent, c_wrongCodeEvent, static_cast<GolVec3*>(p_unk0x08));
		}
		break;
	case 209:
		if (m_unk0x32 == c_thirdCodeEvent) {
			m_eventTable->FireEventsAt(c_correctCodeEvent, c_correctCodeEvent, static_cast<GolVec3*>(p_unk0x08));
		}
		else {
			m_eventTable->FireEventsAt(c_wrongCodeEvent, c_wrongCodeEvent, static_cast<GolVec3*>(p_unk0x08));
		}
		break;
	default:
		return;
	}
}

// FUNCTION: LEGORACERS 0x0048d660
void HazardManager::CodePuzzleHazard::Update(undefined4 p_elapsedMs)
{
	LegoU32 timer = m_unk0x38;
	if (timer > 0) {
		LegoU32 elapsedMs = p_elapsedMs;
		if (elapsedMs >= timer) {
			m_unk0x38 = 0;
			m_eventTable->EndEventsAt(c_successSecondEvent, NULL);

			if (m_unk0x30 == c_firstCodeEvent) {
				m_unk0x1c->FUN_00410480();
			}
			else {
				m_unk0x1c->FUN_00410490();
			}
			m_unk0x1c->FUN_004104c0(0, m_unk0x28, m_unk0x2c);
			m_unk0x1c->FUN_00410470();

			if (m_unk0x31 == c_secondCodeEvent) {
				m_unk0x20->FUN_00410480();
			}
			else {
				m_unk0x20->FUN_00410490();
			}
			m_unk0x20->FUN_004104c0(0, m_unk0x28, m_unk0x2c);
			m_unk0x20->FUN_00410470();

			if (m_unk0x32 == c_thirdCodeEvent) {
				m_unk0x24->FUN_00410480();
			}
			else {
				m_unk0x24->FUN_00410490();
			}
			m_unk0x24->FUN_004104c0(0, m_unk0x28, m_unk0x2c);
			m_unk0x24->FUN_00410470();
		}
		else {
			m_unk0x38 = timer - elapsedMs;
		}
	}
}

// FUNCTION: LEGORACERS 0x0048d730
void HazardManager::CodePuzzleHazard::ResetCodeModels()
{
	g_randomTableIndex++;
	g_randomTableIndex &= c_randomTableMask;
	LegoS32 random = g_randomTable[g_randomTableIndex];
	if (random % 2) {
		m_unk0x30 = c_firstCodeEvent;
		m_unk0x33 = c_firstCodeEvent + 1;
	}
	else {
		m_unk0x30 = c_firstCodeEvent + 1;
		m_unk0x33 = c_firstCodeEvent;
	}

	g_randomTableIndex++;
	g_randomTableIndex &= c_randomTableMask;
	random = g_randomTable[g_randomTableIndex];
	if (random % 2) {
		m_unk0x31 = c_secondCodeEvent;
		m_unk0x34 = c_secondCodeEvent + 1;
	}
	else {
		m_unk0x31 = c_secondCodeEvent + 1;
		m_unk0x34 = c_secondCodeEvent;
	}

	g_randomTableIndex++;
	g_randomTableIndex &= c_randomTableMask;
	random = g_randomTable[g_randomTableIndex];
	if (random % 2) {
		m_unk0x32 = c_thirdCodeEvent;
		m_unk0x35 = c_thirdCodeEvent + 1;
	}
	else {
		m_unk0x32 = c_thirdCodeEvent + 1;
		m_unk0x35 = c_thirdCodeEvent;
	}
}

// FUNCTION: LEGORACERS 0x0048d7f0
HazardManager::LavaGeyserHazard::LavaGeyserHazard()
{
	ClearFields();
}

// FUNCTION: LEGORACERS 0x0048d870
HazardManager::LavaGeyserHazard::~LavaGeyserHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048d8c0
LegoS32 HazardManager::LavaGeyserHazard::ClearFields()
{
	m_unk0x3c = NULL;
	m_unk0x40 = NULL;
	m_unk0x44 = NULL;
	m_unk0x38 = NULL;
	m_unk0x48 = NULL;
	m_unk0x4c = NULL;
	m_unk0x50 = 0;
	m_unk0x54 = 0;
	m_unk0x58 = 0;

	return 0;
}

// FUNCTION: LEGORACERS 0x0048d8e0
void HazardManager::LavaGeyserHazard::Load(Context* p_context, GolFileParser*)
{
	if (m_state) {
		Reset();
	}

	m_triggerId = 0;
	m_eventTable = p_context->GetEventTable();
	m_unk0x3c = p_context->GetEventQueue();
	m_unk0x44 = p_context->GetParticleAnimation();
	m_unk0x4c = p_context->GetSoundSource();
	m_unk0x58 = p_context->GetMirror();
	m_unk0x38 = p_context->GetTrackDatabase()->FindUnk0xc0("mmlavbl");
	m_unk0x10.FUN_10026fa0(m_unk0x38->GetModel(0)->GetRadius());
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0048d960
LegoS32 HazardManager::LavaGeyserHazard::Reset()
{
	OnDeactivate(NULL);
	ClearFields();
	return Hazard::Reset();
}

// FUNCTION: LEGORACERS 0x0048d980
void HazardManager::LavaGeyserHazard::OnActivate(void*)
{
	LegoEventQueue::Descriptor descriptor;
	m_unk0x50 = 0;
	m_unk0x54 = 0;
	descriptor.m_unk0x08 = 0;
	descriptor.m_unk0x0c = 0;
	descriptor.m_unk0x00 = 4;
	descriptor.m_unk0x04 = 1;
	descriptor.m_worldEntity = &m_unk0x10;

	m_unk0x40 = m_unk0x3c->FUN_0042fb50(this, &descriptor);
	m_state = 2;
}

// FUNCTION: LEGORACERS 0x0048d9d0
void HazardManager::LavaGeyserHazard::OnDeactivate(void*)
{
	if (m_unk0x40) {
		m_unk0x40->m_active = 0;
		m_unk0x40 = NULL;
	}

	if (m_unk0x48) {
		m_unk0x4c->ReleaseSound(m_soundResource);
		m_unk0x48 = NULL;
	}

	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0048da10
void HazardManager::LavaGeyserHazard::Update(undefined4 p_elapsedMs)
{
	if (m_state == 1) {
		return;
	}

	LegoFloat frame = m_unk0x38->GetUnk0xb4();
	LegoFloat scale = m_unk0x38->GetModel(0)->GetScale() * m_unk0x38->GetUnk0x58();
	GolSceneNode* node = m_unk0x38->VTable0x58(0);
	GolTransformBase* transform = node->VTable0x18(0);
	LegoU32 elapsedMs = p_elapsedMs;
	Hazard::Update(p_elapsedMs);

	{
		GolVec3 localPosition;
		transform->GetPosition(&localPosition);
		localPosition.m_x *= scale;
		localPosition.m_y *= scale;
		localPosition.m_z *= scale;

		GolVec3 position;
		m_unk0x38->VTable0x2c(localPosition, &position);
		m_unk0x10.SetCenter(position);

		if (m_unk0x48) {
			m_unk0x48->SetPosition(&position);
		}
	}

	GolVec3 effectPosition;
	if (m_unk0x50 == 0) {
		for (LegoS32 i = 0; i < c_lavaPositionCount; i++) {
			if (frame > g_lavaGeyserLavaStartFrames[i] && frame < g_lavaGeyserLavaEndFrames[i]) {
				effectPosition = g_lavaGeyserLavaPositions[i];
				if (m_unk0x58) {
					effectPosition.m_y = -effectPosition.m_y;
				}

				m_unk0x44->FUN_00489d70("lavasmk", &effectPosition, NULL, NULL);
				m_unk0x50 = c_smokeCooldownMs;
			}
		}
	}
	else if (elapsedMs > m_unk0x50) {
		m_unk0x50 = 0;
	}
	else {
		m_unk0x50 -= elapsedMs;
	}

	if (m_unk0x54 == 0) {
		for (LegoS32 i = 0; i < c_lavaPositionCount; i++) {
			LegoFloat startFrame = g_lavaGeyserLavaStartFrames[i];
			startFrame += g_unk0x004afde0;
			if (frame > g_lavaGeyserLavaStartFrames[i] && startFrame > frame) {
				effectPosition = g_lavaGeyserLavaPositions[i];
				if (m_unk0x58) {
					effectPosition.m_y = -effectPosition.m_y;
				}

				m_eventTable->FireEventsAt(c_eventId, c_eventId, &effectPosition);
				m_unk0x54 = c_eventCooldownMs;
				if (m_unk0x48) {
					m_unk0x4c->ReleaseSound(m_soundResource);
					m_unk0x48 = NULL;
				}
			}

			LegoFloat endFrame = g_lavaGeyserLavaEndFrames[i];
			endFrame += g_unk0x004afde0;
			if (frame > g_lavaGeyserLavaEndFrames[i] && endFrame > frame) {
				effectPosition = g_lavaGeyserLavaPositions[i];
				if (m_unk0x58) {
					effectPosition.m_y = -effectPosition.m_y;
				}

				m_eventTable->FireEventsAt(c_eventId, c_eventId, &effectPosition);
				m_unk0x54 = c_eventCooldownMs;
				m_unk0x48 = m_unk0x4c->AcquireSoundById(c_soundId);
				if (m_unk0x48) {
					m_unk0x48->Play(TRUE);
					LegoFloat maxDistance = g_lavaGeyserSoundMaxDistance;
					LegoFloat minDistance = g_lavaGeyserSoundMinDistance;
					m_unk0x48->SetDistanceRangeWithMinSquared(minDistance * minDistance, maxDistance);
				}
			}
		}
	}
	else if (elapsedMs > m_unk0x54) {
		m_unk0x54 = 0;
		return;
	}
	else {
		m_unk0x54 -= elapsedMs;
	}
}

// FUNCTION: LEGORACERS 0x0048dcd0
void HazardManager::LavaGeyserHazard::VTable0x00(LegoEventQueue::CallbackData* p_data)
{
	RaceState::Racer* racer = static_cast<RaceState::Racer*>(p_data->m_data);
	RaceState::Racer::Physics* field0x3e8 = &racer->m_physics;
	if (!(field0x3e8->m_flags & RaceState::Racer::Physics::c_flagSpinning) && field0x3e8->m_forwardSpeed != 0.0f) {
		field0x3e8->StartSpin(1.0f, 0.01f, 0.0f);
		racer->PlayReaction(FALSE);
	}
}

// FUNCTION: LEGORACERS 0x0048dd20
HazardManager::GrabberHazard::GrabberHazard()
{
	ClearFields();
}

// FUNCTION: LEGORACERS 0x0048dda0
HazardManager::GrabberHazard::~GrabberHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048ddf0
LegoS32 HazardManager::GrabberHazard::ClearFields()
{
	m_unk0x38 = NULL;
	m_unk0x44 = NULL;
	m_unk0x48 = 0.0f;
	m_unk0x4c = 0.0f;
	m_unk0x50 = 0.0f;
	m_unk0x40 = NULL;
	m_unk0x58 = 0;
	m_unk0x5c = 0;

	return 0;
}

// FUNCTION: LEGORACERS 0x0048de10
void HazardManager::GrabberHazard::Load(Context* p_context, GolFileParser* p_parser)
{
	if (m_state) {
		Reset();
	}

	GolName entityName;
	entityName[0] = '\0';
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token;
	while ((token = p_parser->GetNextToken()) != GolFileParser::e_rightCurly) {
		switch (token) {
		case GolFileParser::e_unknown0x3b:
			m_triggerId = p_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x42:
			::strncpy(entityName, p_parser->ReadStringWithMaxLength(sizeof(entityName)), sizeof(entityName));
			m_unk0x50 = p_parser->ReadFloat();
			m_unk0x48 = p_parser->ReadFloat();
			m_unk0x4c = p_parser->ReadFloat();
			break;
		default:
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}
	}

	m_unk0x3c = p_context->GetEventQueue();
	m_unk0x38 = p_context->GetTrackDatabase()->FindUnk0xc0(entityName);
	m_unk0x10.FUN_10026fa0(g_grabberTriggerRadius);
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0048df00
LegoS32 HazardManager::GrabberHazard::Reset()
{
	OnDeactivate(NULL);
	ClearFields();
	return Hazard::Reset();
}

// FUNCTION: LEGORACERS 0x0048df20
void HazardManager::GrabberHazard::OnActivate(void*)
{
	LegoEventQueue::Descriptor descriptor;
	descriptor.m_unk0x00 = 4;
	descriptor.m_unk0x04 = 1;
	descriptor.m_unk0x08 = 0;
	descriptor.m_unk0x0c = 0;
	descriptor.m_worldEntity = &m_unk0x10;

	m_unk0x40 = m_unk0x3c->FUN_0042fb50(this, &descriptor);
	m_unk0x58 = 0;
	m_unk0x5c = 0;
	m_state = 2;
}

// FUNCTION: LEGORACERS 0x0048df70
void HazardManager::GrabberHazard::OnDeactivate(void*)
{
	ReleaseRacer();
	if (m_unk0x40) {
		m_unk0x40->m_active = 0;
		m_unk0x40 = NULL;
	}

	m_state = 1;
	m_unk0x58 = 0;
	m_unk0x5c = 0;
}

// FUNCTION: LEGORACERS 0x0048dfa0
void HazardManager::GrabberHazard::Update(undefined4 p_elapsedMs)
{
	if (m_state == 1) {
		return;
	}

	LegoU32 elapsedMs = p_elapsedMs;
	Hazard::Update(p_elapsedMs);

	GolVec3 position;
	GetGrabPosition(&position);
	m_unk0x10.SetCenter(position);

	if (m_unk0x54) {
		if (elapsedMs >= m_unk0x54) {
			m_unk0x54 = 0;
			ReleaseRacer();
			m_unk0x58 = 0;
			m_unk0x5c = 0;
		}
		else {
			m_unk0x54 -= elapsedMs;
		}
	}

	if (m_unk0x5c) {
		if (elapsedMs >= m_unk0x5c) {
			m_unk0x5c = 0;
			switch (m_unk0x58) {
			case c_stateOne:
				ReleaseRacer();
				m_unk0x54 = 0;
				m_unk0x58 = c_stateTwo;
				m_unk0x5c = c_timerMs;
				break;
			case c_stateTwo:
				m_unk0x58 = 0;
				return;
			default:
				return;
			}
		}
		else {
			m_unk0x5c -= elapsedMs;
		}
	}
}

// FUNCTION: LEGORACERS 0x0048e050
void HazardManager::GrabberHazard::VTable0x00(LegoEventQueue::CallbackData* p_data)
{
	LegoFloat frame = m_unk0x38->GetActiveValue();
	if (m_unk0x58 == c_stateTwo) {
		return;
	}

	RaceState::Racer* racer = static_cast<RaceState::Racer*>(p_data->m_data);
	RaceState::Racer::Physics* field0x3e8 = &racer->m_physics;
	if ((frame <= m_unk0x48 || frame >= m_unk0x4c) && !(racer->m_flags & c_racerFlags0xd04Bit0)) {
		if (m_unk0x44 == NULL || m_unk0x44 == racer) {
			if (m_unk0x44 == NULL) {
				m_unk0x58 = c_stateOne;
				m_unk0x5c = c_timerMs;
			}
		}
		else {
			return;
		}

		m_unk0x44 = racer;
		racer->m_flags |= c_racerFlags0xd04Bit29;

		RaceState::Racer* currentRacer = m_unk0x44;
		if (currentRacer->m_physics.m_routeMode) {
			LegoU32 flags = currentRacer->m_physics.m_flags;
			currentRacer->m_physics.m_routeBaseSpeed = -0.4f;
			if (!(flags & RaceState::Racer::Physics::c_flagRoutePushed)) {
				currentRacer->m_physics.m_routeTargetSpeed = -0.4f;
				m_unk0x54 = c_restoreTimerMs;
				return;
			}
		}
		else {
			GolVec3 position;
			GetGrabPosition(&position);

			GolVec3 racerPosition;
			RaceState::Racer::CarVisuals* racerField = &m_unk0x44->m_visuals;
			racerField->m_carEntity->VTable0x04(&racerPosition);

			GolVec3 force;
			force.m_x = position.m_x - racerPosition.m_x;
			force.m_y = position.m_y - racerPosition.m_y;
			force.m_z = 0.0f;
			GolMath::NormalizeVector3(force, &force);
			LegoFloat scale = m_unk0x50;
			force.m_x = scale * force.m_x;
			force.m_y = force.m_y * scale;
			force.m_z = force.m_z * scale;
			field0x3e8->StartExternalForce1(&force);
		}

		m_unk0x54 = c_restoreTimerMs;
	}
}

// FUNCTION: LEGORACERS 0x0048e1c0
void HazardManager::GrabberHazard::GetGrabPosition(GolVec3* p_position)
{
	LegoFloat scale = m_unk0x38->GetModel(0)->GetScale() * m_unk0x38->GetUnk0x58();
	GolSceneNode* node = m_unk0x38->VTable0x58(0);
	GolTransformBase* transform = node->VTable0x18(0);

	GolVec3 localPosition;
	transform->GetPosition(&localPosition);
	localPosition.m_x *= scale;
	localPosition.m_y *= scale;
	localPosition.m_z *= scale;

	m_unk0x38->VTable0x2c(localPosition, p_position);
}

// FUNCTION: LEGORACERS 0x0048e230
void HazardManager::GrabberHazard::ReleaseRacer()
{
	if (m_unk0x44) {
		m_unk0x44->m_physics.EndExternalForce1();
		m_unk0x44->m_flags &= ~c_racerFlags0xd04Bit29;

		RaceState::Racer* racer = m_unk0x44;
		if (racer->m_physics.m_routeMode) {
			LegoU32 flags = racer->m_physics.m_flags;
			LegoFloat value = 1.0f;
			racer->m_physics.m_routeBaseSpeed = value;
			if (!(flags & RaceState::Racer::Physics::c_flagRoutePushed)) {
				racer->m_physics.m_routeTargetSpeed = value;
			}
		}

		m_unk0x44 = NULL;
	}
}

// FUNCTION: LEGORACERS 0x0048e2a0
HazardManager::RocketHazard::RocketHazard()
{
	ClearFields();
}

// FUNCTION: LEGORACERS 0x0048e320
HazardManager::RocketHazard::~RocketHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048e370
LegoS32 HazardManager::RocketHazard::ClearFields()
{
	m_unk0x4c[0] = 0.0f;
	m_unk0x4c[1] = 0.0f;
	m_unk0x4c[2] = 0.0f;
	m_unk0x40 = NULL;
	m_unk0x44 = NULL;
	m_unk0x48 = NULL;
	m_unk0x38 = NULL;
	m_unk0x3c = NULL;
	m_unk0x58 = 1;

	return 0;
}

// FUNCTION: LEGORACERS 0x0048e3a0
void HazardManager::RocketHazard::Load(Context* p_context, GolFileParser*)
{
	if (m_state) {
		Reset();
	}

	m_triggerId = 1;
	m_eventTable = p_context->GetEventTable();
	m_unk0x38 = p_context->GetEventQueue();

	GolNameTable* nameTable = p_context->GetColliderTable();
	m_unk0x48 = nameTable->GetNameEntries() == NULL ? NULL : static_cast<HazardManager::ColliderRecord*>(nameTable->GetName("mmrocc"));

	GolWorldDatabase* worldDatabase = p_context->GetTrackDatabase();
	GolModelEntity* modelEntity;
	if (!worldDatabase->GetUnk0xb4NameEntries()) {
		modelEntity = NULL;
	}
	else {
		modelEntity = worldDatabase->GetUnk0xb4Name("mmrocof");
	}
	m_unk0x40 = modelEntity;

	worldDatabase = p_context->GetTrackDatabase();
	if (!worldDatabase->GetUnk0xb4NameEntries()) {
		modelEntity = NULL;
	}
	else {
		modelEntity = worldDatabase->GetUnk0xb4Name("mmrocon");
	}
	m_unk0x44 = modelEntity;

	for (LegoS32 i = 0; i < c_modelDistanceCount; i++) {
		m_unk0x4c[i] = m_unk0x40->GetModelDistance(i);
	}

	ShowOffModel();

	GolVec3 position;
	m_unk0x40->VTable0x04(&position);
	m_unk0x10.SetCenter(position);
	m_unk0x10.FUN_10026fa0(g_rocketTriggerRadius);
	m_unk0x58 = 1;
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0048e490
LegoS32 HazardManager::RocketHazard::Reset()
{
	OnDeactivate(NULL);
	ClearFields();
	return Hazard::Reset();
}

// FUNCTION: LEGORACERS 0x0048e4b0
void HazardManager::RocketHazard::OnActivate(void*)
{
	LegoEventQueue::Descriptor descriptor;
	descriptor.m_unk0x08 = 0;
	descriptor.m_unk0x0c = 0;
	descriptor.m_unk0x00 = 4;
	descriptor.m_unk0x04 = 1;
	descriptor.m_worldEntity = &m_unk0x10;

	m_unk0x3c = m_unk0x38->FUN_0042fb50(this, &descriptor);
	m_state = 2;
}

// FUNCTION: LEGORACERS 0x0048e500
void HazardManager::RocketHazard::OnDeactivate(void*)
{
	ShowOffModel();
	if (m_unk0x3c) {
		m_unk0x3c->m_active = 0;
		m_unk0x3c = NULL;
	}
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0048e530
void HazardManager::RocketHazard::Update(undefined4 p_elapsedMs)
{
	if (m_state != 1) {
		Hazard::Update(p_elapsedMs);

		LegoU32 state = m_unk0x58;
		if (state == 0) {
			if (m_unk0x44->GetModelDistance(0) == g_rocketInactiveModelDistance) {
				ShowOnModel();
				m_unk0x58 = 1;
				return;
			}
		}
		else if (state == 1 && m_unk0x40->GetModelDistance(0) == g_rocketInactiveModelDistance) {
			ShowOffModel();
		}
		m_unk0x58 = 1;
	}
}

// FUNCTION: LEGORACERS 0x0048e5a0
void HazardManager::RocketHazard::ShowOnModel()
{
	for (LegoS32 i = 0; i < c_modelDistanceCount; i++) {
		if (m_unk0x44) {
			m_unk0x44->SetModelDistance(i, m_unk0x4c[i]);
		}

		if (m_unk0x40) {
			m_unk0x40->SetModelDistance(i, g_rocketInactiveModelDistance);
		}
	}

	if (m_eventTable) {
		m_eventTable->StartEventsAt(c_eventId, NULL);
	}

	if (m_unk0x48) {
		m_unk0x48->m_flags |= ColliderRecord::c_flagBit16;
		m_unk0x48->m_flags |= ColliderRecord::c_flagBit17;
	}
}

// FUNCTION: LEGORACERS 0x0048e600
void HazardManager::RocketHazard::ShowOffModel()
{
	for (LegoS32 i = 0; i < c_modelDistanceCount; i++) {
		if (m_unk0x44) {
			m_unk0x44->SetModelDistance(i, g_rocketInactiveModelDistance);
		}

		if (m_unk0x40) {
			m_unk0x40->SetModelDistance(i, m_unk0x4c[i]);
		}
	}

	if (m_eventTable) {
		m_eventTable->EndEventsAt(c_eventId, NULL);
	}

	if (m_unk0x48) {
		m_unk0x48->m_flags &= ~ColliderRecord::c_flagBit16;
		m_unk0x48->m_flags &= ~ColliderRecord::c_flagBit17;
	}
}

// FUNCTION: LEGORACERS 0x0048e660
void HazardManager::RocketHazard::VTable0x00(LegoEventQueue::CallbackData* p_data)
{
	if (p_data->m_field0x0e0->GetFlags() & c_field0x0e0Flags0xd04Bit0) {
		m_unk0x58 = 0;
	}
}

// FUNCTION: LEGORACERS 0x0048e680
HazardManager::SmokeVentHazard::SmokeVentHazard()
{
	m_unk0x10 = NULL;
	m_unk0x14 = NULL;
	m_unk0x18 = NULL;
	m_unk0x1c = 0;
}

// FUNCTION: LEGORACERS 0x0048e6c0
HazardManager::SmokeVentHazard::~SmokeVentHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048e710
void HazardManager::SmokeVentHazard::Load(Context* p_context, GolFileParser*)
{
	if (m_state) {
		Reset();
	}

	m_triggerId = 10;
	m_eventTable = p_context->GetEventTable();
	m_unk0x14 = p_context->GetParticleAnimation();
	m_unk0x1c = p_context->GetMirror();
	m_unk0x10 = p_context->GetTrackDatabase()->FindUnk0xc0("dp_def");
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0048e780
LegoS32 HazardManager::SmokeVentHazard::Reset()
{
	OnDeactivate(NULL);
	m_unk0x10 = NULL;
	m_unk0x14 = NULL;
	m_unk0x1c = 0;
	return Hazard::Reset();
}

// FUNCTION: LEGORACERS 0x0048e7b0
void HazardManager::SmokeVentHazard::OnActivate(void*)
{
	m_state = 2;
}

// FUNCTION: LEGORACERS 0x0048e7c0
void HazardManager::SmokeVentHazard::OnDeactivate(void*)
{
	if (m_unk0x18) {
		m_unk0x14->FUN_00489f30(m_unk0x18);
		m_unk0x18 = NULL;
	}

	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0048e7f0
void HazardManager::SmokeVentHazard::Update(undefined4 p_elapsedMs)
{
	if (m_state == 1) {
		return;
	}

	LegoFloat scale = m_unk0x10->GetModel(0)->GetScale() * m_unk0x10->GetUnk0x58();
	LegoFloat inverseScale = 1.0f / scale;
	Hazard::Update(p_elapsedMs);

	GolSceneNode* node = m_unk0x10->VTable0x58(0);
	GolTransformBase* transform = node->VTable0x18(0);

	GolVec3 vector;
	transform->GetPosition(&vector);
	vector.m_x *= scale;
	vector.m_y *= scale;
	vector.m_z *= scale;

	GolVec3 position;
	m_unk0x10->VTable0x2c(vector, &position);

	if (m_unk0x18 || (m_unk0x18 = m_unk0x14->FUN_00489d70("smoke", NULL, NULL, NULL)) != NULL) {
		g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
		LegoU32 offsetIndex = g_randomTable[g_randomTableIndex] & 3;
		vector.m_x = g_smokeVentSmokeOffsets[offsetIndex].m_x;
		vector.m_x *= inverseScale;
		vector.m_y = g_smokeVentSmokeOffsets[offsetIndex].m_y;
		vector.m_y *= inverseScale;
		vector.m_z = g_smokeVentSmokeOffsets[offsetIndex].m_z;

		LegoU32 flipOffset = m_unk0x1c;
		vector.m_z *= inverseScale;
		if (flipOffset) {
			vector.m_y = -vector.m_y;
		}

		transform->VTable0x04(&vector, &position);
		vector.m_x = position.m_x * scale;
		vector.m_y = position.m_y * scale;
		vector.m_z = position.m_z * scale;

		m_unk0x10->VTable0x2c(vector, &position);

		CutsceneParticleRef* particleRef = m_unk0x18;
		GolAnimatedEntity* entity = m_unk0x10;
		CutsceneParticle* particle = particleRef->m_particle;
		if (particle) {
			entity->VTable0x44(particle->GetUnk0x160());
		}

		particleRef = m_unk0x18;
		if (particleRef->m_particle) {
			particleRef->m_particle->FUN_00489660(&position);
		}
	}
}

// FUNCTION: LEGORACERS 0x0048e980
HazardManager::SnowfallHazard::SnowfallHazard()
{
	ClearFields();
}

// FUNCTION: LEGORACERS 0x0048e9f0
HazardManager::SnowfallHazard::~SnowfallHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048ea40
LegoS32 HazardManager::SnowfallHazard::ClearFields()
{
	m_unk0x10 = NULL;
	m_unk0x14 = NULL;
	m_unk0x18 = 0;
	m_unk0x1c = 0;
	return 0;
}

// FUNCTION: LEGORACERS 0x0048ea50
void HazardManager::SnowfallHazard::Load(Context* p_context, GolFileParser*)
{
	if (m_state) {
		Reset();
	}

	m_triggerId = -1;
	m_unk0x10 = p_context->GetParticleAnimation();
	m_state = 1;
	OnActivate(NULL);
}

// FUNCTION: LEGORACERS 0x0048ea90
LegoS32 HazardManager::SnowfallHazard::Reset()
{
	OnDeactivate(NULL);
	ClearFields();
	return Hazard::Reset();
}

// FUNCTION: LEGORACERS 0x0048eab0
void HazardManager::SnowfallHazard::OnActivate(void*)
{
	m_unk0x1c = 1;
	m_state = 2;
}

// FUNCTION: LEGORACERS 0x0048ead0
void HazardManager::SnowfallHazard::OnDeactivate(void*)
{
	if (m_unk0x14) {
		m_unk0x10->FUN_00489f30(m_unk0x14);
		m_unk0x14 = NULL;
	}

	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0048eb00
void HazardManager::SnowfallHazard::Update(undefined4 p_elapsedMs)
{
	if (m_state == 1) {
		return;
	}

	LegoU32 elapsedMs = p_elapsedMs;
	Hazard::Update(p_elapsedMs);
	m_unk0x18 += elapsedMs;
	if (m_unk0x18 > c_snowResetMs && m_unk0x14) {
		m_unk0x10->FUN_00489f30(m_unk0x14);
		m_unk0x14 = NULL;
	}

	if (m_unk0x1c && !m_unk0x14) {
		m_unk0x14 = m_unk0x10->FUN_00489d70("snow", NULL, NULL, NULL);
		if (m_unk0x14) {
			m_unk0x18 = 0;
		}
	}
}

// FUNCTION: LEGORACERS 0x0048eb70
void HazardManager::SnowfallHazard::UpdatePerRacer(GolCamera* p_camera, RaceState::Racer* p_racer)
{
	if (p_racer->m_visuals.m_hasColorTransform) {
		m_unk0x1c = 0;
		if (m_unk0x14) {
			m_unk0x10->FUN_00489f30(m_unk0x14);
			m_unk0x14 = NULL;
		}
	}
	else {
		m_unk0x1c = 1;
	}

	if (m_unk0x14) {
		GolVec3 position;
		GolVec3 direction;
		GolVec3 up;
		p_camera->GetTransform()->VTable0x1c(&direction, &up);

		p_camera->GetTransform()->GetPosition(&position);
		position.m_x = g_snowfallCameraForwardScale * direction.m_x + position.m_x;
		position.m_y = g_snowfallCameraForwardScale * direction.m_y + position.m_y;
		LegoFloat scaledZ = g_snowfallCameraForwardScale * direction.m_z;

		direction.m_z = 0.0f;
		scaledZ += position.m_z;
		position.m_z = scaledZ + g_snowfallCameraVerticalOffset * up.m_z;
		GolMath::NormalizeVector3(direction, &direction);

		up.m_x = 0.0f;
		g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
		up.m_y = 0.0f;
		LegoU16 randomValue = g_randomTable[g_randomTableIndex];
		up.m_z = 1.0f;

		LegoFloat lateral = direction.m_y;
		lateral -= up.m_x;
		LegoU32 remainder = static_cast<LegoU32>(randomValue) % 200;
		LegoS32 offsetInt = static_cast<LegoS32>(remainder - 100);
		LegoFloat offset = static_cast<LegoFloat>(offsetInt);
		CutsceneParticleRef* ref = m_unk0x14;
		position.m_x = lateral * offset + position.m_x;
		position.m_y = (up.m_y - direction.m_x) * offset + position.m_y;

		if (ref->m_particle) {
			ref->m_particle->FUN_00489540(&direction, &up);
		}

		ref = m_unk0x14;
		if (ref->m_particle) {
			ref->m_particle->FUN_00489660(&position);
		}
	}
}

// FUNCTION: LEGORACERS 0x0048ece0
void HazardManager::SnowfallHazard::ResetState()
{
	if (m_unk0x14) {
		m_unk0x10->FUN_00489f30(m_unk0x14);
		m_unk0x14 = NULL;
	}

	m_state = 1;
	OnActivate(NULL);
}

// FUNCTION: LEGORACERS 0x0048ed10
HazardManager::TriggeredAnimationHazard::TriggeredAnimationHazard()
{
	ClearFields();
}

// FUNCTION: LEGORACERS 0x0048ed80
HazardManager::TriggeredAnimationHazard::~TriggeredAnimationHazard()
{
	Reset();
}

// STUB: LEGORACERS 0x0048edd0
void HazardManager::TriggeredAnimationHazard::ClearFields()
{
	m_triggerId = -1;
	m_unk0x10[0] = NULL;
	m_unk0x10[1] = NULL;
	m_unk0x10[2] = NULL;
	m_unk0x10[3] = NULL;
	m_unk0x20 = NULL;
	m_unk0x24.Clear();
}

// FUNCTION: LEGORACERS 0x0048ee00
void HazardManager::TriggeredAnimationHazard::Load(Context* p_context, GolFileParser* p_parser)
{
	if (m_state) {
		Reset();
	}

	GolName name;
	name[0] = '\0';

	GolName modelNames[c_entityCount];
	LegoS32 i;
	for (i = 0; i < c_entityCount; i++) {
		modelNames[i][0] = '\0';
	}

	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	if (token != GolFileParser::e_rightCurly) {
		GolName* modelName = modelNames;
		do {
			switch (token) {
			case GolFileParser::e_unknown0x3b:
				m_triggerId = p_parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x41:
				::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));
				break;
			case GolFileParser::e_unknown0x42:
				::strncpy(*modelName, p_parser->ReadStringWithMaxLength(sizeof(*modelName)), sizeof(*modelName));
				modelName++;
				break;
			default:
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		} while ((token = p_parser->GetNextToken()) != GolFileParser::e_rightCurly);
	}

	m_eventTable = p_context->GetEventTable();
	GolNameTable* nameTable = p_context->GetColliderTable();
	m_unk0x20 = nameTable->GetNameEntries() == NULL ? NULL : static_cast<HazardManager::ColliderRecord*>(nameTable->GetName(name));

	GolAnimatedEntity** entity = m_unk0x10;
	GolName* modelName = modelNames;
	LegoS32 count = c_entityCount;
	do {
		if ((*modelName)[0] != '\0') {
			*entity = p_context->GetTrackDatabase()->FindUnk0xc0(*modelName);
			(*entity)->SetFlags((*entity)->GetFlags() & ~GolAnimatedEntity::c_flagPartAnimation);
		}
		entity++;
		modelName++;
	} while (--count);

	for (i = 0; i < 3; i++) {
		(&m_unk0x24.m_x)[i] = m_unk0x10[0]->GetModelDistance(i);
	}
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0048ef50
LegoS32 HazardManager::TriggeredAnimationHazard::Reset()
{
	OnDeactivate(NULL);
	ClearFields();
	return Hazard::Reset();
}

// FUNCTION: LEGORACERS 0x0048ef70
void HazardManager::TriggeredAnimationHazard::OnActivate(void*)
{
	GolAnimatedEntity** entity = m_unk0x10;
	LegoS32 count = c_entityCount;
	do {
		if (*entity != NULL) {
			for (LegoS32 i = 0; i < c_modelDistanceCount; i++) {
				(*entity)->SetModelDistance(i, 0.0f);
			}
			(*entity)->SetFlags((*entity)->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
			(*entity)->SetFlags((*entity)->GetFlags() & ~GolAnimatedEntity::c_flagLoopCurrentPart);
		}
		entity++;
	} while (--count);

	m_eventTable->FireEventsAt(9, 9, NULL);
	m_state = 2;
}

// FUNCTION: LEGORACERS 0x0048efe0
void HazardManager::TriggeredAnimationHazard::OnDeactivate(void*)
{
	{
		LegoU32 i;
		for (i = 0; i < c_entityCount; i++) {
			GolAnimatedEntity* entity = m_unk0x10[i];
			if (entity != NULL && !entity->FUN_0040e360()) {
				return;
			}
		}
	}

	LegoS32 i;
	for (i = 0; i < c_entityCount; i++) {
		GolAnimatedEntity* entity = m_unk0x10[i];
		if (entity != NULL) {
			entity->SetFlags(entity->GetFlags() & ~GolAnimatedEntity::c_flagPartAnimation);
		}
	}

	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0048f030
void HazardManager::TriggeredAnimationHazard::Update(undefined4 p_elapsedMs)
{
	if (m_state != 1) {
		Hazard::Update(p_elapsedMs);

		if (m_unk0x20 != NULL) {
			m_unk0x20->m_flags |= ColliderRecord::c_flagBit16;
			m_unk0x20->m_flags |= ColliderRecord::c_flagBit17;
		}

		if (m_unk0x10[0]->FUN_0040e360()) {
			OnDeactivate(NULL);
		}
	}
}

// FUNCTION: LEGORACERS 0x0048f080
void HazardManager::TriggeredAnimationHazard::Draw(GolD3DRenderDevice* p_renderer)
{
	if (m_state == 1) {
		return;
	}

	for (LegoS32 i = 0; i < c_entityCount; i++) {
		GolAnimatedEntity** entity = &m_unk0x10[i];
		if (*entity != NULL) {
			LegoS32 j;
			LegoFloat* modelDistances = &m_unk0x24.m_x;
			for (j = 0; j < c_modelDistanceCount; j++) {
				(*entity)->SetModelDistance(j, modelDistances[j]);
			}

			CmbModelPartData0x28* partData = (*entity)->GetModelPart(0)->GetPartData();
			LegoU16 frameCount = partData[(*entity)->GetCurrentPartIndex()].GetFrameCount();
			LegoS32 alpha = static_cast<LegoS32>(
				(static_cast<LegoFloat>(frameCount) - (*entity)->GetUnk0xb4()) / static_cast<LegoFloat>(frameCount) *
				255.0f
			);

			p_renderer->SetAlphaOverride(alpha, TRUE);
			p_renderer->VTable0x94(*entity);
			p_renderer->ClearAlphaOverride();

			for (j = 0; j < c_modelDistanceCount; j++) {
				(*entity)->SetModelDistance(j, 0.0f);
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x0048f160
void HazardManager::TriggeredAnimationHazard::ResetState()
{
	if (m_unk0x20 != NULL) {
		m_unk0x20->m_flags &= ~ColliderRecord::c_flagBit16;
		m_unk0x20->m_flags &= ~ColliderRecord::c_flagBit17;
	}

	GolAnimatedEntity** entity = m_unk0x10;
	LegoS32 count = c_entityCount;
	do {
		if (*entity != NULL) {
			(*entity)->SetFlags((*entity)->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
			(*entity)->FUN_0040dae0(0, 0);
			(*entity)->VTable0x5c(0);
			(*entity)->SetFlags((*entity)->GetFlags() & ~GolAnimatedEntity::c_flagPartAnimation);

			LegoFloat* modelDistances = &m_unk0x24.m_x;
			for (LegoS32 i = 0; i < c_modelDistanceCount; i++) {
				(*entity)->SetModelDistance(i, modelDistances[i]);
			}
		}
		entity++;
	} while (--count);

	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0048f200
HazardManager::MultiLauncherHazard::MultiLauncherHazard()
{
	m_unk0x124 = NULL;
	m_unk0x128 = NULL;
	m_unk0x12c = NULL;
	m_unk0x130 = NULL;
	m_unk0x134 = 0;
	m_unk0x138 = 0;
}

// FUNCTION: LEGORACERS 0x0048f260
HazardManager::MultiLauncherHazard::~MultiLauncherHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048f2b0
void HazardManager::MultiLauncherHazard::Load(Context* p_context, GolFileParser* p_parser)
{
	if (m_state) {
		Reset();
	}

	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	while (token != GolFileParser::e_unknown0x33) {
		if (token == GolFileParser::e_unknown0x38) {
			p_parser->ReadLeftBracket();
			m_unk0x138 = p_parser->ReadInteger();
			p_parser->ReadRightBracket();

			m_unk0x12c = static_cast<GolVec3*>(::operator new(sizeof(GolVec3) * m_unk0x138));
			if (m_unk0x12c == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}

			m_unk0x130 = static_cast<LegoS32*>(::operator new(sizeof(LegoS32) * m_unk0x138));
			if (m_unk0x130 == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}

			p_parser->ReadLeftCurly();
			for (LegoU32 i = 0; i < m_unk0x138; i++) {
				m_unk0x12c[i].m_x = p_parser->ReadFloat();
				m_unk0x12c[i].m_y = p_parser->ReadFloat();
				m_unk0x12c[i].m_z = p_parser->ReadFloat();
				m_unk0x130[i] = p_parser->ReadInteger();

				if (p_context->GetMirror()) {
					m_unk0x12c[i].m_y = -m_unk0x12c[i].m_y;
				}
			}

			p_parser->ReadRightCurly();
		}
		else if (token == GolFileParser::e_unknown0x37) {
			p_parser->ReadLeftBracket();
			m_unk0x134 = p_parser->ReadInteger();
			p_parser->ReadRightBracket();

			m_unk0x124 = static_cast<GolVec3*>(::operator new(sizeof(GolVec3) * m_unk0x134));
			if (m_unk0x124 == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}

			m_unk0x128 = static_cast<LegoS32*>(::operator new(sizeof(LegoS32) * m_unk0x134));
			if (m_unk0x128 == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}

			p_parser->ReadLeftCurly();
			for (LegoU32 i = 0; i < m_unk0x134; i++) {
				m_unk0x124[i].m_x = p_parser->ReadFloat();
				m_unk0x124[i].m_y = p_parser->ReadFloat();
				m_unk0x124[i].m_z = p_parser->ReadFloat();
				m_unk0x128[i] = p_parser->ReadInteger();

				if (p_context->GetMirror()) {
					m_unk0x124[i].m_y = -m_unk0x124[i].m_y;
				}
			}

			p_parser->ReadRightCurly();
		}

		token = p_parser->GetNextToken();
	}

	LauncherHazard::Load(p_context, p_parser);
	p_parser->ReadRightCurly();

	m_triggerId = -1;
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0048f520
void HazardManager::MultiLauncherHazard::Reset()
{
	OnDeactivate(NULL);

	if (m_unk0x130 != NULL) {
		::operator delete(m_unk0x130);
		m_unk0x130 = NULL;
	}
	if (m_unk0x12c != NULL) {
		::operator delete(m_unk0x12c);
		m_unk0x12c = NULL;
	}
	if (m_unk0x128 != NULL) {
		::operator delete(m_unk0x128);
		m_unk0x128 = NULL;
	}
	if (m_unk0x124 != NULL) {
		::operator delete(m_unk0x124);
		m_unk0x124 = NULL;
	}

	m_unk0x134 = 0;
	m_unk0x138 = 0;
	LauncherHazard::Reset();
}

// FUNCTION: LEGORACERS 0x0048f5b0
void HazardManager::MultiLauncherHazard::OnActivate(void*)
{
	g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
	LegoU32 sourceIndex = static_cast<LegoU32>(g_randomTable[g_randomTableIndex]) % m_unk0x134;

	g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
	m_unk0x13c = static_cast<LegoU32>(g_randomTable[g_randomTableIndex]) % m_unk0x138;

	m_unk0xe0 = m_unk0x124[sourceIndex];
	m_unk0xec = m_unk0x12c[m_unk0x13c];

	if (m_eventTable != NULL) {
		LegoS32 eventId = m_unk0x128[sourceIndex];
		m_eventTable->FireEventsAt(eventId, eventId, &m_unk0xe0);
	}

	LauncherHazard::OnActivate(NULL);
}

// FUNCTION: LEGORACERS 0x0048f680
void HazardManager::MultiLauncherHazard::OnDeactivate(void*)
{
	if (m_eventTable != NULL) {
		LegoS32 eventId = m_unk0x130[m_unk0x13c];
		m_eventTable->FireEventsAt(eventId, eventId, &m_unk0xec);
	}

	LauncherHazard::OnDeactivate(NULL);
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0048f6c0
void HazardManager::MultiLauncherHazard::Update(undefined4 p_elapsedMs)
{
	if (m_state != 1) {
		LauncherHazard::Update(p_elapsedMs);
	}
}

// FUNCTION: LEGORACERS 0x0048f6e0
HazardManager::LauncherHazard::LauncherHazard()
{
	ClearFields();
}

// FUNCTION: LEGORACERS 0x0048f760
HazardManager::LauncherHazard::~LauncherHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048f7c0
void HazardManager::LauncherHazard::ClearFields()
{
	m_unk0x108 = -1;
	m_unk0x10c = 0;
	m_unk0x118 = 0;
	m_unk0x114 = 0;
	m_unk0x110 = 0;
	m_unk0x11c = 0;
	m_unk0x120 = 0;
	m_unk0xe0.Clear();
	m_unk0xec.Clear();
	m_unk0xf8.Clear();
	m_unk0x104 = 0.0f;
}

// FUNCTION: LEGORACERS 0x0048f830
void HazardManager::LauncherHazard::Load(Context* p_context, GolFileParser* p_parser)
{
	if (m_state) {
		Reset();
	}

	m_triggerId = -1;
	m_eventTable = p_context->GetEventTable();
	m_unk0x10c = p_context->GetSkyState();
	m_unk0x118 = p_context->GetGolExport();
	m_unk0x110 = p_context->GetPowerupManager();
	m_unk0x11c = p_context->GetUnk0x3c();

	m_unk0x114 = static_cast<GolBillboard*>(m_unk0x118->VTable0x30());
	DuskwindBananaRelic0x24* material = p_context->GetRenderer()->FindMaterialByName("cannonb");
	m_unk0x114->VTable0x4c(material, 5.0f, 5.0f, g_launcherMaxDistanceSquared);

	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case GolFileParser::e_unknown0x37:
			m_unk0xe0.m_x = p_parser->ReadFloat();
			m_unk0xe0.m_y = p_parser->ReadFloat();
			m_unk0xe0.m_z = p_parser->ReadFloat();
			break;
		case GolFileParser::e_unknown0x38:
			m_unk0xec.m_x = p_parser->ReadFloat();
			m_unk0xec.m_y = p_parser->ReadFloat();
			m_unk0xec.m_z = p_parser->ReadFloat();
			break;
		case GolFileParser::e_unknown0x39:
			m_unk0xf8.m_x = p_parser->ReadFloat();
			m_unk0xf8.m_y = p_parser->ReadFloat();
			m_unk0xf8.m_z = p_parser->ReadFloat();
			break;
		case GolFileParser::e_unknown0x3a: {
			LegoFloat radius = p_parser->ReadFloat();
			m_unk0x104 = radius * radius;
			break;
		}
		case GolFileParser::e_unknown0x3b:
			m_unk0x108 = p_parser->ReadInteger();
			break;
		default:
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}

		token = p_parser->GetNextToken();
	}

	if (p_context->GetMirror()) {
		m_unk0xe0.m_y = -m_unk0xe0.m_y;
		m_unk0xec.m_y = -m_unk0xec.m_y;
		m_unk0xf8.m_y = -m_unk0xf8.m_y;
	}

	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0048f9f0
void HazardManager::LauncherHazard::Reset()
{
	OnDeactivate(NULL);
	if (m_unk0x114 != NULL) {
		m_unk0x118->VTable0x64(m_unk0x114);
		m_unk0x114 = NULL;
	}

	ClearFields();
	Hazard::Reset();
}

// FUNCTION: LEGORACERS 0x0048fa30
void HazardManager::LauncherHazard::OnEventStart(LegoS32 p_unk0x04, void* p_unk0x08)
{
	if (m_unk0x108 == -1 || p_unk0x04 != m_unk0x108 || m_state != 1) {
		return;
	}

	GolVec3* position = static_cast<GolVec3*>(p_unk0x08);
	if (position != NULL) {
		LegoFloat dx = m_unk0xf8.m_x - position->m_x;
		LegoFloat dy = m_unk0xf8.m_y - position->m_y;
		LegoFloat dz = m_unk0xf8.m_z - position->m_z;
		if (dx * dx + dy * dy + dz * dz >= m_unk0x104) {
			return;
		}
	}

	OnActivate(NULL);
}

// FUNCTION: LEGORACERS 0x0048faa0
void HazardManager::LauncherHazard::OnActivate(void*)
{
	m_state = 2;
	m_unk0x10.SetCenter(m_unk0xe0);

	PowerupProjectile::Params projectileParams;
	projectileParams.m_collisionWorld = m_unk0x10c;
	projectileParams.m_gravity = -32.176f;
	projectileParams.m_eventQueue = NULL;
	projectileParams.m_targetOffset.m_x = 0.0f;
	projectileParams.m_targetOffset.m_y = 0.0f;
	projectileParams.m_targetOffset.m_z = 0.0f;
	projectileParams.m_speed = 180.0f;
	projectileParams.m_lifetimeMs = 3000;
	projectileParams.m_launchHeight = 0.0f;
	projectileParams.m_worldEntity = &m_unk0x10;

	m_unk0x38.LaunchAtPosition(&projectileParams, &m_unk0xec);

	RaceTrailManager::Trail::Params trailParams;
	trailParams.m_unk0x00 = 0x12c;
	trailParams.m_unk0x04 = 4;
	trailParams.m_unk0x0c = 1;
	trailParams.m_unk0x10 = 0;
	trailParams.m_unk0x14 = 0.1f;
	trailParams.m_unk0x18 = 0.0f;
	trailParams.m_unk0x08 = 4;

	RaceTrailManager::Trail::Params* trailParamsPtr = &trailParams;
	m_unk0x120 = static_cast<RaceTrailManager*>(m_unk0x11c)->FUN_004939b0(trailParamsPtr);
	if (m_unk0x120 != NULL) {
		RaceTrailManager::Trail* item = static_cast<RaceTrailManager::Trail*>(m_unk0x120);
		item->FUN_00492ab0(&g_launcherTrailColor);
	}

	m_eventTable->FireEventsAt(6, 6, &m_unk0xe0);
}

// FUNCTION: LEGORACERS 0x0048fba0
void HazardManager::LauncherHazard::OnDeactivate(void*)
{
	m_unk0x38.Deactivate();

	if (m_unk0x120 != NULL) {
		RaceTrailManager* manager = static_cast<RaceTrailManager*>(m_unk0x11c);
		RaceTrailManager::Trail* item = static_cast<RaceTrailManager::Trail*>(m_unk0x120);
		manager->FUN_00493a10(item);
		m_unk0x120 = NULL;
	}

	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0048fbe0
void HazardManager::LauncherHazard::Update(undefined4 p_elapsedMs)
{
	if (m_state == 1) {
		return;
	}

	Hazard::Update(p_elapsedMs);

	PowerupProjectile* projectile = &m_unk0x38;
	if (projectile->GetState() != 0) {
		if (projectile->Update(p_elapsedMs) == 3) {
			GolVec3 position = projectile->GetHitPosition();
			m_unk0x110->SpawnExplosion(&position, 0, 0);
			projectile->Deactivate();
			m_eventTable->FireEventsAt(7, 7, &position);

			if (m_unk0x120 != NULL) {
				RaceTrailManager* manager = static_cast<RaceTrailManager*>(m_unk0x11c);
				RaceTrailManager::Trail* item = static_cast<RaceTrailManager::Trail*>(m_unk0x120);
				manager->FUN_00493a10(item);
				m_unk0x120 = NULL;
			}
		}
	}

	if (projectile->GetState() == 0) {
		OnDeactivate(NULL);
	}

	if (m_unk0x120 == NULL) {
		return;
	}

	GolVec3 center;
	projectile->GetWorldEntity()->FUN_100286d0(&center);

	GolVec3 velocity;
	projectile->GetVelocity(&velocity);

	GolVec2 perpendicular;
	perpendicular.m_x = velocity.m_y;
	perpendicular.m_y = -velocity.m_x;
	if (perpendicular.m_x == 0.0f && perpendicular.m_y == 0.0f) {
		return;
	}

	GolMath::NormalizeVector2(perpendicular, &perpendicular);
	LegoFloat widthX = perpendicular.m_x * 3.0f;
	LegoFloat widthY = perpendicular.m_y * 3.0f;

	GolVec3 positions[4];
	positions[0].m_x = center.m_x - widthX * 0.5f;
	positions[0].m_y = center.m_y - widthY * 0.5f;
	positions[0].m_z = center.m_z + 3.0f * 0.5f;
	positions[1].m_x = positions[0].m_x;
	positions[1].m_y = positions[0].m_y;
	positions[1].m_z = positions[0].m_z - 3.0f;
	positions[2].m_x = positions[0].m_x + widthX;
	positions[2].m_y = positions[0].m_y + widthY;
	positions[2].m_z = positions[1].m_z;
	positions[3].m_x = positions[2].m_x;
	positions[3].m_y = positions[2].m_y;
	positions[3].m_z = positions[1].m_z + 3.0f;

	RaceTrailManager::Trail* item = static_cast<RaceTrailManager::Trail*>(m_unk0x120);
	item->FUN_00492ee0(p_elapsedMs, positions, center);
}

// FUNCTION: LEGORACERS 0x0048fde0
void HazardManager::LauncherHazard::Draw(GolD3DRenderDevice* p_renderer)
{
	if (m_state != 1 && m_unk0x38.GetState() == PowerupProjectile::c_stateFlying) {
		GolVec3 position;
		m_unk0x10.FUN_100286d0(&position);
		m_unk0x114->VTable0x08(position);
		p_renderer->VTable0xb4(*m_unk0x114);
	}
}

// FUNCTION: LEGORACERS 0x0048fe30
HazardManager::MovingObstacleHazard::MovingObstacleHazard()
{
	m_unk0x160.FUN_004a00b0();
	m_unk0x38 = NULL;
	m_unk0x3c = NULL;
	m_unk0x40 = NULL;
	m_unk0x16c = NULL;
	m_sound0x170 = NULL;
	m_unk0x174 = NULL;
	m_unk0x178 = 0;
}

// FUNCTION: LEGORACERS 0x0048fee0
HazardManager::MovingObstacleHazard::~MovingObstacleHazard()
{
	Reset();
	m_unk0x160.Destroy();
}

// FUNCTION: LEGORACERS 0x0048ff50
void HazardManager::MovingObstacleHazard::Load(Context* p_context, GolFileParser*)
{
	if (m_state) {
		Reset();
	}

	m_triggerId = 1;
	m_eventTable = p_context->GetEventTable();
	m_unk0x40 = p_context->GetEventQueue();
	m_unk0x16c = p_context->GetTrackCollidable();
	m_unk0x174 = p_context->GetSoundSource();
	m_unk0x38 = p_context->GetTrackDatabase()->FindUnk0xc0("crane");

	GolVec3 position;
	position.m_x = 0.0f;
	position.m_y = 0.0f;
	position.m_z = 0.0f;
	m_unk0x10.ClearVelocity();
	m_unk0x10.SetCenter(position);
	m_unk0x10.FUN_10026fa0(3.0f);

	m_unk0x160.Initialize(p_context->GetRenderer(), 1);
	m_unk0x160.AssignEntryByName(0, "crneshd");
	m_unk0x44.FUN_00414950(p_context->GetGolExport(), p_context->GetRenderer(), 0x20);
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x00490040
LegoS32 HazardManager::MovingObstacleHazard::Reset()
{
	OnDeactivate(NULL);
	m_unk0x44.FUN_004149f0();
	m_unk0x160.Clear();
	m_unk0x38 = NULL;
	return Hazard::Reset();
}

// FUNCTION: LEGORACERS 0x00490070
void HazardManager::MovingObstacleHazard::OnActivate(void*)
{
	LegoEventQueue::Descriptor descriptor;
	descriptor.m_unk0x00 = 4;
	descriptor.m_unk0x04 = 1;
	descriptor.m_unk0x08 = 0;
	descriptor.m_unk0x0c = 0;
	descriptor.m_worldEntity = &m_unk0x10;

	m_unk0x3c = m_unk0x40->FUN_0042fb50(this, &descriptor);
	m_sound0x170 = m_unk0x174->AcquireSoundById(c_soundId);
	if (m_sound0x170 != NULL) {
		GolVec3 position;
		m_unk0x38->VTable0x04(&position);
		m_sound0x170->Play(TRUE);
		m_sound0x170->SetPosition(position);
		m_sound0x170->SetFrequencyScale(1.0f);
		LegoFloat maxDistance = 300.0f;
		m_sound0x170->SetDistanceRangeWithMinSquared(10000.0f, maxDistance);
	}

	m_unk0x178 = c_flags0x178Bit1;
	m_state = 2;
}

// FUNCTION: LEGORACERS 0x00490140
void HazardManager::MovingObstacleHazard::OnDeactivate(void*)
{
	if (m_unk0x3c != NULL) {
		m_unk0x3c->m_active = 0;
		m_unk0x3c = NULL;
	}

	if (m_sound0x170 != NULL) {
		m_unk0x174->ReleaseSound(m_unk0x170);
		m_sound0x170 = NULL;
	}

	m_state = 1;
}

// FUNCTION: LEGORACERS 0x00490190
void HazardManager::MovingObstacleHazard::Update(undefined4 p_elapsedMs)
{
	if (m_state == 1) {
		return;
	}

	Hazard::Update(p_elapsedMs);

	GolSceneNode* node = m_unk0x38->VTable0x58(0);
	GolTransformBase* transform = node->VTable0x18(3);

	GolVec3 offset;
	offset.m_x = 0.0f;
	offset.m_y = 0.0f;
	offset.m_z = 0.0f;
	GolVec3 position;
	do {
		position = offset;
		transform->VTable0x04(&position, &offset);
		transform = transform->m_unk0x04;
	} while (transform != NULL);

	LegoFloat scale = m_unk0x38->GetModel(0)->GetScale() * m_unk0x38->GetUnk0x58();
	offset.m_x *= scale;
	offset.m_y *= scale;
	offset.m_z *= scale;

	m_unk0x38->VTable0x2c(offset, &position);
	m_unk0x10.SetCenter(position);

	LegoFloat frame = m_unk0x38->GetUnk0xb4();
	if ((m_unk0x178 & c_flags0x178Bit1) != 0) {
		if ((frame > 150.0f && frame < 180.0f) || (frame > 0.0f && frame < 30.0f)) {
			m_eventTable->FireEventsAt(c_eventId0x14, c_eventId0x14, &position);
			m_unk0x178 &= ~c_flags0x178Bit1;
		}
	}
	else if ((frame > 60.0f && frame < 120.0f) || (frame > 210.0f && frame < 270.0f)) {
		m_unk0x178 |= c_flags0x178Bit1;
	}

	m_unk0x178 &= ~c_flags0x178Bit0;
}

// FUNCTION: LEGORACERS 0x00490330
void HazardManager::MovingObstacleHazard::UpdatePerRacer(GolCamera* p_camera, RaceState::Racer*)
{
	if (m_state == 1 || (m_unk0x178 & c_flags0x178Bit0) != 0) {
		return;
	}

	GolVec3 position;
	m_unk0x10.FUN_100286d0(&position);

	GolVec3 cameraPosition;
	p_camera->GetTransform()->GetPosition(&cameraPosition);

	LegoFloat dx = position.m_x - cameraPosition.m_x;
	LegoFloat dy = position.m_y - cameraPosition.m_y;
	LegoFloat dz = position.m_z - cameraPosition.m_z;
	LegoFloat distanceSquared = dx * dx + dy * dy + dz * dz;
	if (distanceSquared >= m_unk0x38->GetModelDistance(0)) {
		return;
	}

	m_unk0x44.m_unk0x104 = 13.0f;
	m_unk0x44.m_unk0x108 = 13.0f;
	m_unk0x44.m_unk0x10c = 15.0f;
	m_unk0x44.m_unk0x0e8.m_x = position.m_x;
	m_unk0x44.m_unk0x0e8.m_y = position.m_y;
	m_unk0x44.m_unk0x0e8.m_z = position.m_z;
	m_unk0x44.GetUnk0x010().SetPrimaryMaterialTable(&m_unk0x160);

	GolVec3 up;
	GolVec3 forward;
	m_unk0x38->VTable0x48(&up, &forward);

	forward.m_x = 0.0f;
	forward.m_y = 0.0f;
	forward.m_z = -1.0f;
	m_unk0x44.FUN_00414c90(&forward, &up);
	m_unk0x44.FUN_00414a30(m_unk0x16c);

	m_unk0x178 |= c_flags0x178Bit0;
}

// FUNCTION: LEGORACERS 0x00490460
void HazardManager::MovingObstacleHazard::Draw(GolD3DRenderDevice* p_renderer)
{
	if (m_state != 1 && (m_unk0x178 & c_flags0x178Bit0) != 0) {
		m_unk0x44.FUN_00415a40(p_renderer);
	}
}

// FUNCTION: LEGORACERS 0x00490490
void HazardManager::MovingObstacleHazard::VTable0x00(LegoEventQueue::CallbackData* p_data)
{
	RaceState::Racer* racer = static_cast<RaceState::Racer*>(p_data->m_data);
	RaceState::Racer::Physics* field0x3e8 = &racer->m_physics;
	if (!(field0x3e8->m_flags & RaceState::Racer::Physics::c_flagSpinning) && field0x3e8->m_forwardSpeed != 0.0f) {
		field0x3e8->StartSpin(1.0f, 0.01f, 0.0f);

		GolVec3 position;
		racer->m_visuals.m_carEntity->VTable0x04(&position);
		m_eventTable->FireEventsAt(c_eventId0x15, c_eventId0x15, &position);
	}
}

// FUNCTION: LEGORACERS 0x0048d470 FOLDED
void HazardManager::HammerHazard::OnDeactivate(void*)
{
	m_state = 1;
}
