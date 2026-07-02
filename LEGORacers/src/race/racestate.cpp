#include "audio/soundnode.h"
#include "audio/spatialsoundinstance.h"
#include "camera/golcamera.h"
#include "cmbmodelpart0x34.h"
#include "duskwindbananarelic0x24.h"
#include "golbinparser.h"
#include "golerror.h"
#include "golmateriallibrary.h"
#include "material/goltexturelist.h"
#include "menu/runtime/cutsceneparticle.h"
#include "menu/runtime/cutsceneplayer.h"
#include "race/cobalttrail0x140.h"
#include "race/racecameracontroller.h"
#include "race/raceeventtable0x90.h"
#include "race/raceforcefeedback.h"
#include "race/racesession.h"
#include "race/timeracemanager.h"
#include "render/gold3drenderdevice.h"
#include "surface/purpledune0x7c.h"
#include "util/racerbillboardrenderstate0x33c.h"

#include <float.h>
#include <math.h>
#include <string.h>

extern LegoU16 g_randomTable[1024];
extern LegoU32 g_randomTableIndex;
extern LegoFloat g_carBuildPreviewMouseScale;
extern const LegoFloat g_carBuildModelTextureCoordinateScale;
extern LegoFloat g_minSoundPan;

DECOMP_SIZE_ASSERT(RaceState, 0x320)
DECOMP_SIZE_ASSERT(RaceState::Racer, 0xe34)
DECOMP_SIZE_ASSERT(RaceEventRecord, 0x20)
DECOMP_SIZE_ASSERT(RaceEventRecord::Target, 0x5c)
DECOMP_SIZE_ASSERT(RaceState::RacerProgressEntry, 0x0c)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x36df0Params, 0x88)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x371c0, 0x30)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x371c0Vehicle, 0x88)
DECOMP_SIZE_ASSERT(RaceState::Racer::CarVisuals, 0x3d0)
DECOMP_SIZE_ASSERT(RaceState::Racer::CarVisuals::InitParams, 0x68)
DECOMP_SIZE_ASSERT(RaceState::Racer::CarVisuals::PhysicsView, 0x6c4)
DECOMP_SIZE_ASSERT(RaceState::Racer::CarVisuals::PhysicsView::WheelContact, 0x70)
DECOMP_SIZE_ASSERT(RaceState::Racer::PhysicsBase0xd0, 0xd0)
DECOMP_SIZE_ASSERT(RaceState::Racer::PhysicsBase0xe4, 0xe4)
DECOMP_SIZE_ASSERT(RaceState::Racer::PhysicsBase0x74c, 0x74c)
DECOMP_SIZE_ASSERT(RaceState::Racer::Physics, 0x888)
DECOMP_SIZE_ASSERT(RaceState::Racer::DriveController, 0x54)
DECOMP_SIZE_ASSERT(RaceState::Racer::SpatialSoundResource, 0x30)
DECOMP_SIZE_ASSERT(RaceState::Field0x0f0, 0x194)
DECOMP_SIZE_ASSERT(RaceState::Field0x284, 0x1c)

extern const LegoFloat g_ghostAnimationRateScale;
extern const LegoFloat g_ghostSampleFractionScale;
extern const LegoFloat g_item0x40RadiansToTableIndex;
extern const LegoFloat g_negativeRadiansToTableIndex;
extern const LegoFloat g_violetShoalTwo;
extern LegoU32 g_unk0x004bef68;
extern LegoU32 g_unk0x004bef6c;
extern LegoFloat g_cosineTable[1024];

// GLOBAL: LEGORACERS 0x004b02e0
extern const LegoFloat g_unk0x004b02e0 = 0.2f;

// GLOBAL: LEGORACERS 0x004b0424
static const LegoFloat g_unk0x004b0424 = 100.0f;

// GLOBAL: LEGORACERS 0x004b0544
extern const LegoFloat g_unk0x004b0544 = 0.050000001f;

// GLOBAL: LEGORACERS 0x004b094c
extern const LegoFloat g_unk0x004b094c = 0.40000001f;

// GLOBAL: LEGORACERS 0x004b0950
extern const LegoFloat g_unk0x004b0950 = 0.1f;

// GLOBAL: LEGORACERS 0x004b0954
extern const LegoFloat g_unk0x004b0954 = 0.17f;

// GLOBAL: LEGORACERS 0x004b0958
extern const LegoFloat g_shieldSoundMinDistance = 30.0f;

// GLOBAL: LEGORACERS 0x004b095c
extern const LegoFloat g_shieldSoundMaxDistance = 300.0f;

// GLOBAL: LEGORACERS 0x004b0960
extern const LegoFloat g_unk0x004b0960 = 200.0f;

// GLOBAL: LEGORACERS 0x004b0964
extern const LegoFloat g_unk0x004b0964 = 600.0f;

// GLOBAL: LEGORACERS 0x004b0970
extern const LegoFloat g_collisionRestitution = 0.75f;

// GLOBAL: LEGORACERS 0x004b0988
extern const LegoFloat g_unk0x004b0988 = 0.015f;

// GLOBAL: LEGORACERS 0x004b098c
extern const LegoFloat g_unk0x004b098c = 0.69999999f;

// GLOBAL: LEGORACERS 0x004b0990
extern const LegoFloat g_unk0x004b0990 = 0.5f;

// GLOBAL: LEGORACERS 0x004b0994
extern const LegoFloat g_unk0x004b0994 = 2.2439947f;

// GLOBAL: LEGORACERS 0x004b0998
extern const LegoFloat g_unk0x004b0998 = 0.059999999f;

// GLOBAL: LEGORACERS 0x004b099c
extern const LegoFloat g_unk0x004b099c = 0.030000029f;

// GLOBAL: LEGORACERS 0x004b09a0
extern const LegoFloat g_unk0x004b09a0 = 0.0099999998f;

// GLOBAL: LEGORACERS 0x004b09a4
extern const LegoFloat g_unk0x004b09a4 = 1.0f;

// GLOBAL: LEGORACERS 0x004b0974
extern const LegoFloat g_unk0x004b0974 = 100.0f;

// GLOBAL: LEGORACERS 0x004b0978
extern const LegoFloat g_unk0x004b0978 = 62500.0f;

// GLOBAL: LEGORACERS 0x004b097c
extern const LegoFloat g_unk0x004b097c = 0.95999998f;

// GLOBAL: LEGORACERS 0x004b0980
extern const LegoFloat g_shieldShoveConeCosine = 0.69999999f;

// GLOBAL: LEGORACERS 0x004b0984
extern const LegoFloat g_unk0x004b0984 = 0.2f;

// GLOBAL: LEGORACERS 0x004b09a8
extern const LegoFloat g_unk0x004b09a8 = 3.5f;

// GLOBAL: LEGORACERS 0x004b09ac
static const LegoFloat g_unk0x004b09ac = 0.0111111114f;

// GLOBAL: LEGORACERS 0x004b09b8
extern const LegoFloat g_unk0x004b09b8 = 30.0f;

// GLOBAL: LEGORACERS 0x004b09bc
extern const LegoFloat g_unk0x004b09bc = 0.001953125f;

// GLOBAL: LEGORACERS 0x004b09c4
extern const LegoFloat g_unk0x004b09c4 = 9.9999997e-05f;

// GLOBAL: LEGORACERS 0x004b09c8
extern const LegoFloat g_unk0x004b09c8 = -9.9999997e-05f;

// GLOBAL: LEGORACERS 0x004b09d0
extern const LegoFloat g_unk0x004b09d0 = 1.5f;

// GLOBAL: LEGORACERS 0x004b09d4
extern const LegoFloat g_shieldShoveStrength = 200.0f;

// GLOBAL: LEGORACERS 0x004b09dc
extern const LegoFloat g_unk0x004b09dc = 0.050000001f;

// GLOBAL: LEGORACERS 0x004b0a08
extern const LegoFloat g_unk0x004b0a08 = 0.40000001f;

// GLOBAL: LEGORACERS 0x004b0a0c
extern const LegoFloat g_unk0x004b0a0c = 0.1f;

// GLOBAL: LEGORACERS 0x004b0a10
extern const LegoFloat g_unk0x004b0a10 = 0.17f;

// GLOBAL: LEGORACERS 0x004b0a14
extern const LegoFloat g_unk0x004b0a14 = 250000.0f;

// GLOBAL: LEGORACERS 0x004b0a18
extern const LegoFloat g_unk0x004b0a18 = 30.0f;

// GLOBAL: LEGORACERS 0x004b0a1c
extern const LegoFloat g_unk0x004b0a1c = 2.0f;

// GLOBAL: LEGORACERS 0x004b0a20
extern const LegoFloat g_unk0x004b0a20 = 200.0f;

// GLOBAL: LEGORACERS 0x004b0ac0
extern const LegoFloat g_unk0x004b0ac0 = -1.0f;

// GLOBAL: LEGORACERS 0x004b0af0
extern const LegoFloat g_unk0x004b0af0 = 15.0f;

// GLOBAL: LEGORACERS 0x004b0af4
extern const LegoFloat g_unk0x004b0af4 = 6.0f;

// GLOBAL: LEGORACERS 0x004b0b24
extern const LegoFloat g_unk0x004b0b24 = 40000.0f;

// GLOBAL: LEGORACERS 0x004b0b28
extern const LegoFloat g_unk0x004b0b28 = 30.0f;

// GLOBAL: LEGORACERS 0x004b0b2c
extern const LegoFloat g_unk0x004b0b2c = 100.0f;

// GLOBAL: LEGORACERS 0x004b0b30
extern const LegoFloat g_unk0x004b0b30 = 0.0099999998f;

// GLOBAL: LEGORACERS 0x004b0b34
extern const LegoFloat g_unk0x004b0b34 = 0.029999999f;

// GLOBAL: LEGORACERS 0x004b0b38
extern const LegoFloat g_unk0x004b0b38 = 2500.0f;

// GLOBAL: LEGORACERS 0x004b0b3c
extern const LegoFloat g_unk0x004b0b3c = 10000.0f;

// GLOBAL: LEGORACERS 0x004b0b40
extern const LegoFloat g_unk0x004b0b40 = -0.60000002f;

// GLOBAL: LEGORACERS 0x004b0b44
extern const LegoFloat g_unk0x004b0b44 = -0.2f;

// GLOBAL: LEGORACERS 0x004b0b4c
extern const LegoFloat g_fadeAlphaScale = 191.0f;

// GLOBAL: LEGORACERS 0x004b0b50
extern const LegoFloat g_racerBillboardScale = 1.15f;

extern const LegoFloat g_twoPi;
extern const LegoFloat g_pathMinSegmentLengthSquared;

// GLOBAL: LEGORACERS 0x004c67a4
LegoFloat g_unk0x004c67a4 = ((1.0f - g_unk0x004b0984) * g_unk0x004b0424) * g_unk0x004b09ac;

// GLOBAL: LEGORACERS 0x004c67a8
LegoFloat g_unk0x004c67a8 = g_unk0x004b0a20 * g_unk0x004b0a20;

// GLOBAL: LEGORACERS 0x004c67ac
undefined4 g_unk0x004c67ac;

// GLOBAL: LEGORACERS 0x004c67b0
RaceState::RacerProgressEntry RaceState::g_racerProgressEntries[RaceState::c_racerProgressEntryCount];

// GLOBAL: LEGORACERS 0x004bef3c
const LegoChar* g_unk0x004bef3c[3] = {"drivers", "champs", "chassis"};

// GLOBAL: LEGORACERS 0x004bef70
LegoU32 g_unk0x004bef70 = 3;

// GLOBAL: LEGORACERS 0x004c6b34
LegoFloat g_unk0x004c6b34 = g_twoPi * g_pathMinSegmentLengthSquared;

// FUNCTION: LEGORACERS 0x00436990
RaceState::Racer::Racer()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00436a20
RaceState::Racer::~Racer()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00436aa0
void RaceState::Racer::Destroy()
{
	if (m_ghostSound) {
		m_soundSource->ReleaseSound(m_ghostSound);
		m_ghostSound = NULL;
	}

	if (m_turboSoundL2) {
		m_soundSource->ReleaseSound(m_turboSoundL2);
		m_turboSoundL2 = NULL;
	}

	if (m_turboSoundL1) {
		m_soundSource->ReleaseSound(m_turboSoundL1);
		m_turboSoundL1 = NULL;
	}

	if (m_turboSoundL0) {
		m_soundSource->ReleaseSound(m_turboSoundL0);
		m_turboSoundL0 = NULL;
	}

	if (m_engineIdleSound) {
		m_soundSource->ReleaseSound(m_soundD9c);
		m_engineIdleSound = NULL;
	}

	if (m_engineDriveSound) {
		m_soundSource->ReleaseSound(m_soundDa0);
		m_engineDriveSound = NULL;
	}

	if (m_engineFastSound) {
		m_soundSource->ReleaseSound(m_soundDa4);
		m_engineFastSound = NULL;
	}

	if (m_unk0xda8) {
		m_soundSource->ReleaseSound(m_soundDa8);
		m_unk0xda8 = NULL;
	}

	if (m_curseSound) {
		m_soundSource->ReleaseSound(m_curseSound);
		m_curseSound = NULL;
	}

	m_displayName.Reset();
	m_unk0x018.Destroy();
	m_unk0x3e8.Destroy();
	m_unk0xc70.Destroy();
	Reset();
}

// FUNCTION: LEGORACERS 0x00436bd0
void RaceState::Racer::Reset()
{
	m_soundSource = NULL;
	m_unk0xd0c = 0;
	m_unk0xd10 = 2;
	m_unk0xd14 = 1;
	m_aiPowerupCheckMs = 0;
	m_raceState = NULL;

	LegoU32 lapTime;
	m_lapsCompleted = 0;
	lapTime = 0;
	m_lapTransitionCount = 0xffffffff;
	m_lapTimes[0] = lapTime;
	m_lapTimes[1] = lapTime;
	m_lapTimes[2] = lapTime;
	m_lapTimes[3] = lapTime;
	m_lapTimes[4] = lapTime;
	m_heldPowerupColor = 0;
	m_unk0xd04 = 0;
	m_controlMode = 2;
	m_aiPowerupCheckIntervalMs = 150;
	m_unk0xd38 = 0;
	m_tauntCooldownMs = 0;
	m_reactionCooldownMs = 0;
	m_scrapeSoundCooldownMs = 0;
	m_airborneMs = 0;
	m_voiceBank = 1000;
	m_unk0xd3c = 0;
	m_unk0xd54 = 1.0f;
	m_turboLevel = 0;
	m_shieldLevel = 0;
	m_shoveReleaseAction = 0;
	m_turboSoundL0 = NULL;
	m_turboSoundL1 = NULL;
	m_turboSoundL2 = NULL;
	m_ghostSound = NULL;
	m_engineIdleSound = NULL;
	m_engineDriveSound = NULL;
	m_engineFastSound = NULL;
	m_unk0xda8 = NULL;
	m_curseSound = NULL;
	m_activeEngineSound = 0;
	m_engineIdleVolume = 0;
	m_engineDriveVolume = 0;
	m_engineFastVolume = 0;
	m_unk0xd74 = 0;
	m_curseTimerMs = 0;
	m_timeBehindDisplayMs = 0;
	m_timeBehind = 0;

	LegoU8 invalidIndex = 0xff;
	m_unk0xd78 = 0;
	m_unk0xdf8.m_x = 0;
	m_aiRedUseChance = invalidIndex;
	m_aiYellowUseChance = invalidIndex;
	m_aiGreenUseChance = invalidIndex;
	m_aiBlueUseChance = invalidIndex;
	m_unk0xd20 = invalidIndex;
	m_unk0xd21 = invalidIndex;
	m_unk0xdf8.m_y = 0;

	DroppableBrick* field0xd5c = NULL;
	m_unk0xdf8.m_z = 0;
	m_unk0xd22 = 0;
	m_actionSource.m_x = 0;
	m_actionSource.m_y = 0;
	m_actionSource.m_z = 0;
	m_actionSource.m_velocity.m_x = 0;
	m_actionSource.m_velocity.m_y = 0;
	m_actionSource.m_velocity.m_z = 0;
	m_actionSource.m_right.m_x = 0;
	m_actionSource.m_right.m_y = 0;
	m_actionSource.m_right.m_z = 0;
	m_unk0xcc4 = 0;
	m_unk0xcc8 = 1;
	m_unk0x010 = 0;
	m_unk0xe30 = NULL;
	m_unk0xd18 = 0xffffffff;
	m_unk0xdb0 = 0;
	m_whiteBrickCount = 0;
	m_whiteBricks[0] = field0xd5c;
	m_whiteBricks[1] = field0xd5c;
	m_whiteBricks[2] = field0xd5c;
	m_cameraController = NULL;
	m_unk0xdb8 = 0;
	m_unk0x014 = 0;
	m_unk0xdbc = 0;
	m_aiChargeColor = 0;
	m_aiChargeTarget = 0;
	m_unk0xce0 = 0;
	m_speedRampTimerMs = 0;
}

// FUNCTION: LEGORACERS 0x00436df0
void RaceState::Racer::FUN_00436df0(
	RaceState::Field0x3b190Params0x08* p_context,
	CarVisuals::InitParams* p_field0x018Params,
	Field0x36df0Params* p_params,
	RaceState* p_raceState,
	LegoU32 p_racerIndex
)
{
	if (m_raceState) {
		Destroy();
	}

	m_materialIndex = p_racerIndex;
	m_unk0xe2c = p_context->m_unk0x34;
	m_soundSource = p_context->m_resourceMgr;
	m_unk0x008 = p_context->m_unk0x18;
	m_unk0x010 = p_context->m_racerField0x010;
	m_raceState = p_raceState;
	m_lapTimes[5] = p_racerIndex + 1;
	m_unk0xd54 = p_params->m_unk0x78;
	m_aiChargeColor = p_params->m_unk0x7c;
	m_aiChargeTarget = p_params->m_unk0x80;
	m_unk0xce0 = p_params->m_unk0x72;

	if (p_params->m_stringChars) {
		m_displayName.CopyFromBufSelection(p_params->m_stringChars, 0);
	}
	else {
		GolString::CopyStringToBuf16(p_params->m_displayName, &m_unk0xdbc);
		m_displayName.CopyFromBufSelection(&m_unk0xdbc, 0);
	}

	LegoU32 soundBase = p_params->m_unk0x74;
	m_voiceBank = soundBase;
	if (soundBase == 1000) {
		m_unk0xd23 = 26;
	}
	else if (soundBase == 1100) {
		m_unk0xd23 = 28;
	}
	else if (soundBase == 1112) {
		m_unk0xd23 = 27;
	}
	else if (soundBase == 1124) {
		m_unk0xd23 = 29;
	}
	else if (soundBase == 1136) {
		m_unk0xd23 = 30;
	}
	else if (soundBase == 1148 || soundBase == 1160) {
		m_unk0xd23 = 31;
	}

	LegoU32 colorValue = p_params->m_unk0x6c[0];
	LegoFloat colorScale = static_cast<LegoFloat>(colorValue);
	colorScale *= g_unk0x004c67a4;
	colorScale *= g_carBuildPreviewMouseScale;
	colorScale += g_unk0x004b0984;
	if (colorScale > 1.0f) {
		colorScale = 1.0f;
	}
	m_aiRedUseChance = static_cast<LegoU8>(colorScale * 255.0f);

	colorValue = p_params->m_unk0x6c[1];
	colorScale = static_cast<LegoFloat>(colorValue);
	colorScale *= g_unk0x004c67a4;
	colorScale *= g_carBuildPreviewMouseScale;
	colorScale += g_unk0x004b0984;
	if (colorScale > 1.0f) {
		colorScale = 1.0f;
	}
	m_aiYellowUseChance = static_cast<LegoU8>(colorScale * 255.0f);

	colorValue = p_params->m_unk0x6c[2];
	colorScale = static_cast<LegoFloat>(colorValue);
	colorScale *= g_unk0x004c67a4;
	colorScale *= g_carBuildPreviewMouseScale;
	colorScale += g_unk0x004b0984;
	if (colorScale > 1.0f) {
		colorScale = 1.0f;
	}
	m_aiGreenUseChance = static_cast<LegoU8>(colorScale * 255.0f);

	colorValue = p_params->m_unk0x6c[3];
	colorScale = static_cast<LegoFloat>(colorValue);
	colorScale *= g_unk0x004c67a4;
	colorScale *= g_carBuildPreviewMouseScale;
	colorScale += g_unk0x004b0984;
	if (colorScale > 1.0f) {
		colorScale = 1.0f;
	}
	m_aiBlueUseChance = static_cast<LegoU8>(colorScale * 255.0f);

	colorValue = p_params->m_unk0x6c[4];
	colorScale = static_cast<LegoFloat>(colorValue);
	colorScale *= g_unk0x004c67a4;
	colorScale *= g_carBuildPreviewMouseScale;
	colorScale += g_unk0x004b0984;
	if (colorScale > 1.0f) {
		colorScale = 1.0f;
	}
	m_unk0xd20 = static_cast<LegoU8>(colorScale * 255.0f);

	colorValue = p_params->m_unk0x6c[5];
	colorScale = static_cast<LegoFloat>(colorValue);
	colorScale *= g_unk0x004c67a4;
	colorScale *= g_carBuildPreviewMouseScale;
	colorScale += g_unk0x004b0984;
	if (colorScale > 1.0f) {
		colorScale = 1.0f;
	}
	m_unk0xd21 = static_cast<LegoU8>(colorScale * 255.0f);

	LegoS32 unk0xd22 = m_aiBlueUseChance;
	unk0xd22 = m_aiYellowUseChance - unk0xd22;
	unk0xd22 -= m_aiGreenUseChance;
	unk0xd22 += m_aiRedUseChance;
	if (unk0xd22 < 0) {
		m_unk0xd22 = 0;
	}
	else {
		LegoFloat d22Scale = static_cast<LegoFloat>(unk0xd22);
		d22Scale *= g_unk0x004b09bc;
		d22Scale *= g_unk0x004b09b8;
		m_unk0xd22 = static_cast<LegoU8>(d22Scale);
	}

	LegoU32 randomIndex = g_randomTableIndex;
	randomIndex++;
	randomIndex &= c_randomTableMask;
	g_randomTableIndex = randomIndex;
	LegoU32 randomValue = g_randomTable[randomIndex];
	m_tauntCooldownMs = randomValue * 8 + 2000;

	randomIndex = g_randomTableIndex;
	randomIndex++;
	randomIndex &= c_randomTableMask;
	g_randomTableIndex = randomIndex;
	randomValue = g_randomTable[randomIndex];
	m_reactionCooldownMs = randomValue * 4 + 5000;

	LegoU32 state = 2;
	m_controlMode = state;
	if (p_context->m_flags0x3c & 1) {
		m_unk0xd04 |= c_flags0xd04Bit26;
	}
	if (p_context->m_flags0x3c & 0x40) {
		m_unk0xd04 |= c_flagCheatRedOnly;
	}
	if (p_context->m_flags0x3c & 0x80) {
		m_unk0xd04 |= c_flagCheatMaxPowerups;
	}
	if (p_context->m_flags0x3c & state) {
		m_unk0xd04 |= c_flagCheatFastForward;
	}

	m_unk0x018.Initialize(p_field0x018Params, p_context);
	FUN_004371c0(&p_context->m_field0x371c0, &p_params->m_vehicle);
	ResetRaceProgress();
}

// FUNCTION: LEGORACERS 0x004371c0
void RaceState::Racer::FUN_004371c0(Field0x371c0* p_unk0x04, Field0x371c0Vehicle* p_unk0x08)
{
	RaceEventTable0x90* eventTable;
	undefined4 unk0x2c;
	GolBoundedEntity* unk0x0c;
	GolBoundedEntity* unk0x10;
	if (p_unk0x04) {
		eventTable = p_unk0x04->m_unk0x028;
		unk0x2c = p_unk0x04->m_unk0x02c;
		unk0x0c = p_unk0x04->m_unk0x00c;
		unk0x10 = p_unk0x04->m_unk0x010;
	}
	else {
		eventTable = m_unk0x3e8.m_unk0x6f4;
		unk0x2c = m_unk0x3e8.m_unk0x6f8;
		unk0x0c = m_unk0x3e8.m_unk0x140[0];
		unk0x10 = m_unk0x3e8.m_unk0x6fc;
	}

	GolVec3 position;
	GolVec3 vector;
	LegoFloat deltaX;
	LegoFloat deltaY;
	LegoFloat unk0x58;
	LegoU32 unk0x84;
	LegoU32 unk0x86;
	LegoU32 unk0x85;
	if (p_unk0x08) {
		deltaY = p_unk0x08->m_unk0x044 - p_unk0x08->m_unk0x038;
		unk0x58 = p_unk0x08->m_unk0x058;
		memcpy(&position, &p_unk0x08->m_unk0x04c, sizeof(position));

		deltaX = p_unk0x08->m_unk0x028.m_x - p_unk0x08->m_unk0x040;
		unk0x86 = p_unk0x08->m_unk0x086;
		LegoFloat valueFloat = p_unk0x08->m_unk0x05c;
		unk0x85 = p_unk0x08->m_unk0x085;
		memcpy(&vector, &p_unk0x08->m_unk0x028, sizeof(vector));
		valueFloat *= g_unk0x004b0544;

		LegoU32 value = static_cast<LegoU32>(valueFloat);
		unk0x84 = p_unk0x08->m_unk0x084 + value;
		if (unk0x84 > 100) {
			unk0x84 = 100;
		}

		unk0x86 += value;
		if (unk0x86 > 100) {
			unk0x86 = 100;
		}

		if (value > p_unk0x08->m_unk0x085) {
			unk0x85 = 0;
		}
		else {
			unk0x85 = p_unk0x08->m_unk0x085 - value;
		}
	}
	else {
		unk0x58 = m_unk0x3e8.m_unk0x0c8;
		unk0x84 = m_unk0x3e8.m_unk0x71c;
		memcpy(&position, &m_unk0x3e8.m_unk0x014, sizeof(position));
		unk0x86 = m_unk0x3e8.m_unk0x724;
		memcpy(&vector, &m_unk0x3e8.m_unk0x358, sizeof(vector));
		deltaY = m_unk0x3e8.m_unk0x364;
		deltaX = m_unk0x3e8.m_unk0x368;
		unk0x85 = m_unk0x3e8.m_unk0x720;
	}

	Physics* field0x3e8 = &m_unk0x3e8;
	field0x3e8->FUN_00429210(
		this,
		eventTable,
		unk0x2c,
		m_unk0x018.m_carEntity,
		unk0x0c,
		unk0x10,
		m_soundSource,
		unk0x58,
		8.0f,
		5.0f,
		6.2f
	);
	m_unk0x3e8.m_unk0x6ec = 0;
	m_unk0x3e8.m_racer = this;

	if (m_unk0xd04 & c_flags0xd04Bit26) {
		field0x3e8->m_flags0x6c0 |= Physics::c_flags0x6c0Bit20;
	}

	field0x3e8->FUN_0042ad70(unk0x84);
	field0x3e8->FUN_0042ada0(unk0x85);
	field0x3e8->FUN_0042add0(unk0x86);

	LegoFloat halfHeight = m_unk0x018.m_shadowWidth;
	halfHeight *= 0.5f;
	LegoFloat halfWidth = m_unk0x018.m_shadowLength;
	halfWidth *= 0.5f;
	field0x3e8->FUN_00441190(&position);
	field0x3e8->FUN_00446e60(&vector, deltaY, deltaX);

	GolVec3 corner;
	corner.m_x = halfWidth;
	corner.m_y = -halfHeight;
	corner.m_z = g_unk0x004b09a8;
	field0x3e8->FUN_00446ea0(0, &corner);

	corner.m_x = halfWidth;
	corner.m_y = halfHeight;
	corner.m_z = g_unk0x004b09a8;
	field0x3e8->FUN_00446ea0(1, &corner);

	corner.m_x = -halfWidth;
	corner.m_y = -halfHeight;
	corner.m_z = g_unk0x004b09a8;
	field0x3e8->FUN_00446ea0(2, &corner);

	corner.m_x = -halfWidth;
	corner.m_y = halfHeight;
	corner.m_z = g_unk0x004b09a8;
	field0x3e8->FUN_00446ea0(3, &corner);

	m_unk0xc70.FUN_0041fbd0(field0x3e8);
}

// FUNCTION: LEGORACERS 0x004374c0
void RaceState::Racer::ResetRaceProgress()
{
	LegoU32 flags = m_unk0xd04;
	flags &= ~(c_flags0xd04Bit12 | c_flags0xd04Bit13 | c_flags0xd04Bit14);
	flags |= c_flagPreStart;
	m_unk0xd04 = flags;

	if (m_unk0xe2c) {
		m_unk0x3e8.FUN_0042a670(m_unk0xe2c);
		m_unk0x3e8.m_unk0x748 = 1;
	}

	LegoU32 invalidValue = 0xffffffff;
	m_unk0xcc4 = 0;
	m_unk0xd0c = 0;
	m_lapsCompleted = 0;
	m_unk0xd78 = 0;
	m_unk0xcc8 = 1;
	m_unk0xd10 = 2;
	m_unk0xd14 = 1;
	m_lapTransitionCount = invalidValue;
	m_unk0xd18 = invalidValue;
}

// FUNCTION: LEGORACERS 0x00437540
void RaceState::Racer::InitializeSounds(RaceCameraController* p_cameraController, LegoBool32 p_state)
{
	m_controlMode = p_state;
	m_cameraController = p_cameraController;

	m_soundD8c = m_soundSource->AcquireSoundById(0x2a);
	if (m_soundD8c) {
		m_soundD8c->SetDistanceRangeWithMinSquared(
			g_shieldSoundMinDistance * g_shieldSoundMinDistance,
			g_shieldSoundMaxDistance
		);
	}

	m_soundD90 = m_soundSource->AcquireSoundById(0x2b);
	if (m_soundD90) {
		m_soundD90->SetDistanceRangeWithMinSquared(
			g_shieldSoundMinDistance * g_shieldSoundMinDistance,
			g_shieldSoundMaxDistance
		);
	}

	m_soundD94 = m_soundSource->AcquireSoundById(0x2c);
	if (m_soundD94) {
		m_soundD94->SetDistanceRangeWithMinSquared(
			g_shieldSoundMinDistance * g_shieldSoundMinDistance,
			g_shieldSoundMaxDistance
		);
	}

	m_soundD98 = m_soundSource->AcquireSoundById(0x2d);
	if (m_soundD98) {
		m_soundD98->SetDistanceRangeWithMinSquared(
			g_shieldSoundMinDistance * g_shieldSoundMinDistance,
			g_shieldSoundMaxDistance
		);
	}

	m_engineIdleVolume = 0.0f;
	m_engineDriveVolume = 0.0f;
	m_engineFastVolume = 0.0f;

	m_engineIdleSound = m_soundSource->AcquireSoundById(0x20);
	m_engineIdleSound->VTable0x14(0xff);
	m_engineIdleSound->Play(TRUE);
	m_engineIdleSound->SetDistanceRangeWithMinSquared(
		g_shieldSoundMinDistance * g_shieldSoundMinDistance,
		g_shieldSoundMaxDistance
	);
	m_engineIdleSound->SetVolume(m_engineIdleVolume);

	m_activeEngineSound = 0;
	m_engineDriveSound = m_soundSource->AcquireSoundById(0x0a);
	m_engineDriveSound->SetDistanceRangeWithMinSquared(
		g_shieldSoundMinDistance * g_shieldSoundMinDistance,
		g_shieldSoundMaxDistance
	);
	m_engineDriveSound->VTable0x14(0xff);
	m_engineDriveSound->SetVolume(m_engineDriveVolume);

	m_engineFastSound = m_soundSource->AcquireSoundById(0x3d);
	m_engineFastSound->SetDistanceRangeWithMinSquared(
		g_shieldSoundMinDistance * g_shieldSoundMinDistance,
		g_shieldSoundMaxDistance
	);
	m_engineFastSound->VTable0x14(0xff);
	m_engineFastSound->SetVolume(m_engineFastVolume);
}

// FUNCTION: LEGORACERS 0x00437740
void RaceState::Racer::UpdateCarAnimation(LegoU32 p_elapsedMs)
{
	LegoFloat value = m_unk0x3e8.m_unk0x618;
	CarVisuals* field;

	if (value > g_unk0x004b09c8 && value < g_unk0x004b09c4) {
		value = 0.0f;
	}
	else if (value < 0.0f) {
		field = &m_unk0x018;
		field->PlayReverseAnimation();
		value = -value;
		goto setSpeed;
	}

	field = &m_unk0x018;
	field->PlayForwardAnimation();

setSpeed:
	GolAnimatedEntity* entity = field->m_carEntity;
	LegoFloat speed = value * g_ghostAnimationRateScale;
	entity->SetUnk0xb8(speed);

	if (field->m_unk0x040) {
		field->m_unk0x040->SetUnk0xb8(speed);
	}

	field->Update(p_elapsedMs);
}

// FUNCTION: LEGORACERS 0x004377f0
void RaceState::Racer::UpdateTimers(LegoU32 p_elapsedMs)
{
	if (m_unk0xd04 & c_flagPreStart) {
		return;
	}

	LegoU32 lap = m_lapsCompleted;
	if (lap < m_unk0xce0) {
		m_lapTimes[lap] += p_elapsedMs;
	}

	LegoU32 countdown = m_aiPowerupCheckIntervalMs;
	m_aiPowerupCheckMs += p_elapsedMs;
	if (m_aiPowerupCheckMs > countdown) {
		m_aiPowerupCheckMs = 0;
		m_aiPowerupCheckIntervalMs = 150;

		if (m_controlMode == 2 && m_heldPowerupColor) {
			AiConsiderPowerup();
		}
	}

	if ((m_unk0x3e8.m_flags0x6c0 & c_flags0xaa8Bit7) && !m_unk0x3e8.m_unk0x744) {
		EndSpinOut();
	}

	countdown = m_tauntCooldownMs;
	if (p_elapsedMs > countdown) {
		m_tauntCooldownMs = 0;
	}
	else {
		m_tauntCooldownMs = countdown - p_elapsedMs;
	}

	countdown = m_reactionCooldownMs;
	if (p_elapsedMs > countdown) {
		m_reactionCooldownMs = 0;
	}
	else {
		m_reactionCooldownMs = countdown - p_elapsedMs;
	}

	countdown = m_scrapeSoundCooldownMs;
	if (p_elapsedMs > countdown) {
		m_scrapeSoundCooldownMs = 0;
	}
	else {
		m_scrapeSoundCooldownMs = countdown - p_elapsedMs;
	}

	if (!m_unk0x3e8.m_unk0x36c) {
		m_airborneMs += p_elapsedMs;
	}
	else {
		m_airborneMs = 0;
	}

	countdown = m_unk0xd74;
	if (p_elapsedMs > countdown) {
		m_unk0xd74 = 0;
	}
	else {
		m_unk0xd74 = countdown - p_elapsedMs;
	}

	countdown = m_curseTimerMs;
	if (p_elapsedMs > countdown) {
		if (m_unk0xd04 & c_flagCursed) {
			RemoveCurse();
		}
	}
	else {
		m_curseTimerMs = countdown - p_elapsedMs;
	}

	countdown = m_timeBehindDisplayMs;
	if (p_elapsedMs > countdown) {
		m_timeBehindDisplayMs = 0;
	}
	else {
		m_timeBehindDisplayMs = countdown - p_elapsedMs;
	}

	countdown = m_speedRampTimerMs;
	if (p_elapsedMs < countdown && (m_unk0xd04 & c_flagSpeedRamping)) {
		countdown -= p_elapsedMs;
		m_speedRampTimerMs = countdown;
		m_unk0x3e8.m_unk0x0dc =
			countdown > 500 ? static_cast<LegoFloat>(static_cast<LegoS32>(countdown - 500)) * g_ghostSampleFractionScale
							: 0.0f;
	}
	else {
		m_speedRampTimerMs = 0;
		m_unk0x3e8.m_unk0x0dc = 1.0f;
	}

	m_unk0xd04 &= ~c_flagSpeedRamping;
	m_unk0x018.m_carEntity->VTable0x04(&m_actionSource);
	m_unk0x018.m_carEntity->GetOrientationRow0(&m_actionSource.m_right);
	GolVec3& velocity = m_actionSource.m_velocity;
	velocity = m_unk0x3e8.m_unk0x008;

	if (!m_tauntCooldownMs && m_controlMode == 2) {
		if (m_raceState->FindNearestRacerInCone(&m_actionSource, &m_actionSource.m_right, 0.0f, 169.0f, 0.30000001f)) {
			FUN_00439c90();
			g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
			m_tauntCooldownMs = g_randomTable[g_randomTableIndex] * 8 + 2000;
		}
		else {
			m_tauntCooldownMs = 2000;
		}
	}

	if (!m_controlMode) {
		FUN_00439cf0(p_elapsedMs);
		FUN_00439ea0(p_elapsedMs);
	}
	else {
		m_unk0xd78 = 0;
		m_unk0xd04 &= ~(c_flags0xd04Bit13 | c_flags0xd04Bit14);
	}

	if (m_unk0x3e8.m_unk0x3ec) {
		if (m_unk0x014) {
			m_unk0x014->FUN_00422100();
		}

		if (!m_scrapeSoundCooldownMs) {
			SoundVector position;
			m_unk0x018.m_carEntity->VTable0x04(&position);

			g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
			LegoS32 randomValue = g_randomTable[g_randomTableIndex];
			if (randomValue % 2) {
				m_soundSource->PlaySpatialSoundById(
					0x19,
					&position,
					g_shieldSoundMinDistance,
					g_shieldSoundMaxDistance,
					1.0f,
					1.0f
				);
			}
			else {
				m_soundSource->PlaySpatialSoundById(
					0x38,
					&position,
					g_shieldSoundMinDistance,
					g_shieldSoundMaxDistance,
					1.0f,
					1.0f
				);
			}

			m_scrapeSoundCooldownMs = 250;
		}
	}

	LegoU32 flags = m_unk0xd04;
	if ((flags & c_flagCheatFastForward) && !(flags & c_flagHalted)) {
		m_unk0x008->UseGreenPowerup(this, 2);
	}
}

// FUNCTION: LEGORACERS 0x00437b50
void RaceState::Racer::UpdateDriftLean()
{
	GolVec3 direction;

	if (!(m_unk0xc70.m_unk0x014 & DriveController::c_flags0x014Bit2)) {
		EndDrift();
		return;
	}

	direction = m_unk0x3e8.m_unk0x168;

	LegoFloat value = 1.0f - (m_unk0x3e8.m_unk0x13c->GetOrientation().m_m[0][0] * direction.m_x +
							  m_unk0x3e8.m_unk0x13c->GetOrientation().m_m[0][1] * direction.m_y +
							  m_unk0x3e8.m_unk0x13c->GetOrientation().m_m[0][2] * direction.m_z);

	if (m_unk0x3e8.m_unk0x64c < 0.0f) {
		value = -value;
	}

	m_unk0x018.m_rollLean += value * 0.059999999f;
}

// STUB: LEGORACERS 0x00437be0
void RaceState::Racer::UpdateSpatialSounds()
{
	for (LegoU32 i = 0; i <= 3; i++) {
		SpatialSoundResource* resource = NULL;

		switch (i) {
		case 0:
			resource = m_turboSoundL0;
			break;
		case 1:
			resource = m_turboSoundL1;
			break;
		case 2:
			resource = m_turboSoundL2;
			break;
		case 3:
			resource = m_ghostSound;
			break;
		default:
			continue;
		}

		if (resource) {
			LegoU32 flags = m_unk0xd04;
			if ((flags & c_flagTurbo) && i == m_turboLevel && i < 3) {
				if (!resource->VTable0x0c()) {
					resource->VTable0x04(1);
				}

				GolVec3 position;
				m_unk0x018.m_carEntity->VTable0x04(&position);
				resource->m_unk0x018 = position;
				resource->m_unk0x024 = m_unk0x3e8.m_unk0x008;
			}
			else if ((flags & c_flagGhost) && i == 3) {
				if (!resource->VTable0x0c()) {
					resource->VTable0x04(1);
				}
			}
			else if (resource->VTable0x0c()) {
				resource->VTable0x08();
			}
		}
	}

	if (m_curseSound) {
		GolVec3 position;
		m_unk0x018.m_curseEntity.VTable0x04(&position);
		m_curseSound->m_unk0x018 = position;
	}
}

// FUNCTION: LEGORACERS 0x00437d40
void RaceState::Racer::UpdateEngineSound(LegoU32 p_elapsedMs)
{
	if (!(m_unk0xd04 & c_flagEngineSounds) || !m_engineIdleSound) {
		return;
	}

	SoundVector position;
	m_unk0x018.m_carEntity->VTable0x04(&position);

	GolVec3 velocity = m_unk0x3e8.m_unk0x008;
	LegoFloat frequencyScale;

	if (m_engineIdleSound && m_engineDriveSound && m_engineFastSound) {
		if (m_unk0x3e8.m_unk0x628 == 0.0f && !(m_unk0xc70.m_unk0x014 & DriveController::c_flags0x014Bit0)) {
			if (m_unk0x3e8.m_unk0x604 > g_unk0x004b0988) {
				if (!m_engineFastSound->IsPlaying()) {
					m_engineFastSound->Play(TRUE);
					m_activeEngineSound = 2;
				}
			}
			else if (!m_engineIdleSound->IsPlaying()) {
				m_engineIdleSound->Play(TRUE);
				m_activeEngineSound = 0;
			}
		}
		else if (!m_engineDriveSound->IsPlaying()) {
			m_engineDriveSound->Play(TRUE);
			m_activeEngineSound = 1;
		}

		LegoFloat elapsedStep = static_cast<LegoFloat>(p_elapsedMs) * g_unk0x004b099c;
		elapsedStep *= g_unk0x004b0998;
		LegoFloat targetVolume = (m_unk0xd04 & c_flags0xd04Bit12) ? g_unk0x004b0990 : g_unk0x004b098c;

		switch (m_activeEngineSound) {
		case 2:
			if (m_engineFastVolume < targetVolume) {
				m_engineFastVolume += elapsedStep;
			}
			if (m_engineFastVolume > targetVolume) {
				m_engineFastVolume = targetVolume;
			}
			if (elapsedStep > m_engineIdleVolume) {
				m_engineIdleVolume = 0.0f;
			}
			else {
				m_engineIdleVolume -= elapsedStep;
			}
			if (elapsedStep > m_engineDriveVolume) {
				m_engineDriveVolume = 0.0f;
			}
			else {
				m_engineDriveVolume -= elapsedStep;
			}
			break;
		case 1:
			if (m_engineDriveVolume < targetVolume) {
				m_engineDriveVolume += elapsedStep;
			}
			if (m_engineDriveVolume > targetVolume) {
				m_engineDriveVolume = targetVolume;
			}
			if (elapsedStep > m_engineIdleVolume) {
				m_engineIdleVolume = 0.0f;
			}
			else {
				m_engineIdleVolume -= elapsedStep;
			}
			if (elapsedStep > m_engineFastVolume) {
				m_engineFastVolume = 0.0f;
			}
			else {
				m_engineFastVolume -= elapsedStep;
			}
			break;
		case 0:
			if (m_engineIdleVolume < targetVolume) {
				LegoFloat increment = elapsedStep;
				increment *= g_unk0x004b09d0;
				m_engineIdleVolume += increment;
			}
			if (m_engineIdleVolume > targetVolume) {
				m_engineIdleVolume = targetVolume;
			}
			if (elapsedStep > m_engineDriveVolume) {
				m_engineDriveVolume = 0.0f;
			}
			else {
				m_engineDriveVolume -= elapsedStep;
			}
			if (elapsedStep > m_engineFastVolume) {
				m_engineFastVolume = 0.0f;
			}
			else {
				m_engineFastVolume -= elapsedStep;
			}
			break;
		}

		if (m_engineIdleVolume == targetVolume) {
			m_engineIdleSound->SetVolume(targetVolume);
		}
		else if (m_engineIdleVolume == 0.0f) {
			m_engineIdleSound->Stop();
		}
		else {
			LegoFloat volume = m_engineIdleVolume;
			volume *= g_unk0x004b0994;
			volume *= g_negativeRadiansToTableIndex;
			LegoS32 index = (c_volumeTableBase - static_cast<LegoS32>(volume)) & c_volumeTableMask;
			volume = g_cosineTable[index];
			volume *= targetVolume;
			m_engineIdleSound->SetVolume(volume);
		}

		if (m_engineDriveVolume == targetVolume) {
			m_engineDriveSound->SetVolume(targetVolume);
		}
		else if (m_engineDriveVolume == 0.0f) {
			m_engineDriveSound->Stop();
		}
		else {
			LegoFloat volume = m_engineDriveVolume;
			volume *= g_unk0x004b0994;
			volume *= g_negativeRadiansToTableIndex;
			LegoS32 index = (c_volumeTableBase - static_cast<LegoS32>(volume)) & c_volumeTableMask;
			volume = g_cosineTable[index];
			volume *= targetVolume;
			m_engineDriveSound->SetVolume(volume);
		}

		if (m_engineFastVolume == targetVolume) {
			m_engineFastSound->SetVolume(targetVolume);
		}
		else if (m_engineFastVolume == 0.0f) {
			m_engineFastSound->Stop();
		}
		else {
			LegoFloat volume = m_engineFastVolume;
			volume *= g_unk0x004b0994;
			volume *= g_negativeRadiansToTableIndex;
			LegoS32 index = (c_volumeTableBase - static_cast<LegoS32>(volume)) & c_volumeTableMask;
			volume = g_cosineTable[index];
			volume *= targetVolume;
			m_engineFastSound->SetVolume(volume);
		}

		frequencyScale = m_unk0xd54;
		if (frequencyScale < 0.0f) {
			frequencyScale = 0.0f;
		}
		else if (frequencyScale > 1.0f) {
			frequencyScale = 1.0f;
		}

		m_engineIdleSound->SetPosition(position);
		m_engineIdleSound->SetVelocity(velocity);
		m_engineIdleSound->SetFrequencyScale(frequencyScale);

		frequencyScale = m_unk0x3e8.m_unk0x604 / g_unk0x004b0954;
		LegoBool32 boostSoundElapsed = m_airborneMs > c_boostSoundElapsedThreshold;
		frequencyScale *= 1.0f - g_unk0x004b094c - g_unk0x004b0950;
		frequencyScale *= m_unk0xd54;
		frequencyScale += g_unk0x004b094c;
		if (boostSoundElapsed) {
			frequencyScale += g_unk0x004b0950;
		}
		if (frequencyScale < 0.0f) {
			frequencyScale = 0.0f;
		}
		else if (frequencyScale > 1.0f) {
			frequencyScale = 1.0f;
		}

		m_engineDriveSound->SetPosition(position);
		m_engineDriveSound->SetVelocity(velocity);
		m_engineDriveSound->SetFrequencyScale(frequencyScale);

		frequencyScale = m_unk0x3e8.m_unk0x604 / g_unk0x004b0954;
		frequencyScale *= 1.0f - g_unk0x004b094c;
		frequencyScale *= m_unk0xd54;
		frequencyScale += g_unk0x004b094c;
		if (frequencyScale < 0.0f) {
			frequencyScale = 0.0f;
		}
		else if (frequencyScale > 1.0f) {
			frequencyScale = 1.0f;
		}

		m_engineFastSound->SetPosition(position);
		m_engineFastSound->SetVelocity(velocity);
		m_engineFastSound->SetFrequencyScale(frequencyScale);
	}

	if (m_unk0xda8) {
		if (m_unk0x3e8.m_unk0x618 >= g_unk0x004b09a0 && m_unk0x3e8.m_unk0x628 < 0.0f) {
			m_unk0xda8->SetPosition(position);
			m_unk0xda8->SetVelocity(velocity);
			frequencyScale = m_unk0x3e8.m_unk0x604;
			frequencyScale = g_unk0x004b0954 - frequencyScale;
			frequencyScale *= g_unk0x004b09a4;
			frequencyScale = 1.0f - frequencyScale;
			m_unk0xda8->SetFrequencyScale(frequencyScale);
			return;
		}

		m_soundSource->ReleaseSound(m_soundDa8);
		m_unk0xda8 = NULL;
		return;
	}

	if (m_unk0x3e8.m_unk0x618 > g_unk0x004b09a0 && m_unk0x3e8.m_unk0x628 < 0.0f) {
		m_soundSource
			->PlaySpatialSoundById(2, &position, g_shieldSoundMinDistance, g_shieldSoundMaxDistance, 1.0f, 1.0f);
		m_unk0xda8 = m_soundSource->AcquireSoundById(3);

		if (m_unk0xda8) {
			m_unk0xda8->Play(TRUE);
			LegoFloat maxDistance = g_shieldSoundMaxDistance;
			LegoFloat minDistance = g_shieldSoundMinDistance;
			m_unk0xda8->SetDistanceRangeWithMinSquared(minDistance * minDistance, maxDistance);
			m_unk0xda8->SetPosition(position);
			m_unk0xda8->SetVelocity(velocity);
			frequencyScale = m_unk0x3e8.m_unk0x604;
			frequencyScale = g_unk0x004b0954 - frequencyScale;
			frequencyScale *= g_unk0x004b09a4;
			frequencyScale = 1.0f - frequencyScale;
			m_unk0xda8->SetFrequencyScale(frequencyScale);
		}
	}
}

// FUNCTION: LEGORACERS 0x00438500
void RaceState::Racer::StopEngineSounds()
{
	if (m_controlMode != 2) {
		LegoU32 flags = m_unk0xd04;
		flags &= ~c_flagEngineSounds;
		m_unk0xd04 = flags;

		if (m_engineIdleSound) {
			m_engineIdleSound->Stop();
		}

		if (m_engineIdleSound) {
			m_engineDriveSound->Stop();
		}

		if (m_engineIdleSound) {
			m_engineFastSound->Stop();
		}
	}
}

// STUB: LEGORACERS 0x00438560
void RaceState::Racer::VTable0x00(LegoEventQueue::CallbackData* p_data)
{
	if (p_data->m_unk0x00 == 1) {
		LegoU32 flags = m_unk0xd04;
		m_unk0xd04 = flags & ~c_flagShoveActive;

		if (!(flags & c_flagDrifting)) {
			EndDrift();
		}

		if (m_shoveReleaseAction == 1) {
			m_unk0x3e8.VTable0x44();
		}
		else if (m_shoveReleaseAction == 2) {
			m_unk0x3e8.VTable0x4c();
		}

		m_shoveReleaseAction = 0;

		return;
	}

	if (p_data->m_unk0x00 != 3) {
		return;
	}

	LegoEventQueue::Field0x30::CollisionCallbackData* collision =
		static_cast<LegoEventQueue::Field0x30::CollisionCallbackData*>(p_data->m_data);
	LegoEventQueue::Descriptor::Field0x10* firstTarget = p_data->m_target0;
	LegoEventQueue::Descriptor::Field0x10* secondTarget = collision->m_secondTarget;
	Racer* firstRacer = static_cast<Racer*>(firstTarget->m_owner);
	Racer* secondRacer = static_cast<Racer*>(secondTarget->m_owner);

	if (firstRacer->m_unk0xd04 & c_flagGhost) {
		return;
	}

	if (secondRacer && (secondRacer->m_unk0xd04 & c_flagGhost)) {
		return;
	}

	if (firstRacer->m_unk0x3e8.m_flags0x6c0 & c_flags0xaa8Bit7) {
		return;
	}

	if (secondRacer && (secondRacer->m_unk0x3e8.m_flags0x6c0 & c_flags0xaa8Bit7)) {
		return;
	}

	GolVec3 collisionNormal = collision->m_normal;
	GolVec3 impulse = collisionNormal;
	impulse.m_x *= collision->m_penetrationDepth;
	impulse.m_y *= collision->m_penetrationDepth;
	impulse.m_z *= collision->m_penetrationDepth;

	firstRacer->m_unk0x3e8.FUN_00429680(&impulse);

	GolVec3 relativeVelocity;
	relativeVelocity.m_x = firstTarget->m_velocity.m_x - secondTarget->m_velocity.m_x;
	relativeVelocity.m_y = firstTarget->m_velocity.m_y - secondTarget->m_velocity.m_y;
	relativeVelocity.m_z = firstTarget->m_velocity.m_z - secondTarget->m_velocity.m_z;

	LegoFloat impulseNumerator = -GOLVECTOR3_DOT(relativeVelocity, collisionNormal) * (g_collisionRestitution + 1.0f);

	LegoFloat collisionNormalLengthSquared = GOLVECTOR3_DOT(collisionNormal, collisionNormal);
	LegoFloat inverseMassTerm =
		(firstTarget->m_inverseMass + secondTarget->m_inverseMass) * collisionNormalLengthSquared;

	GolVec3 firstContactOffset;
	firstContactOffset.m_x = firstTarget->m_position.m_x - collision->m_contactPoint.m_x;
	firstContactOffset.m_y = firstTarget->m_position.m_y - collision->m_contactPoint.m_y;
	firstContactOffset.m_z = firstTarget->m_position.m_z - collision->m_contactPoint.m_z;
	GolMath::NormalizeVector3(firstContactOffset, &firstContactOffset);

	GolVec3 secondContactOffset;
	secondContactOffset.m_x = secondTarget->m_position.m_x - collision->m_contactPoint.m_x;
	secondContactOffset.m_y = secondTarget->m_position.m_y - collision->m_contactPoint.m_y;
	secondContactOffset.m_z = secondTarget->m_position.m_z - collision->m_contactPoint.m_z;
	GolMath::NormalizeVector3(secondContactOffset, &secondContactOffset);

	GolVec3 firstAngularAxis;
	firstAngularAxis.m_x = firstContactOffset.m_y * collisionNormal.m_z - collisionNormal.m_y * firstContactOffset.m_z;
	firstAngularAxis.m_y = firstContactOffset.m_z * collisionNormal.m_x - collisionNormal.m_z * firstContactOffset.m_x;
	firstAngularAxis.m_z = firstContactOffset.m_x * collisionNormal.m_y - firstContactOffset.m_y * collisionNormal.m_x;

	const GolMatrix3& firstInertia = firstTarget->m_inverseInertia;
	GolVec3 firstAngular;
	firstAngular.m_x = firstInertia.m_m[2][0] * firstAngularAxis.m_z + firstInertia.m_m[1][0] * firstAngularAxis.m_y +
					   firstInertia.m_m[0][0] * firstAngularAxis.m_x;
	firstAngular.m_y = firstInertia.m_m[2][1] * firstAngularAxis.m_z + firstInertia.m_m[1][1] * firstAngularAxis.m_y +
					   firstInertia.m_m[0][1] * firstAngularAxis.m_x;
	firstAngular.m_z = firstInertia.m_m[2][2] * firstAngularAxis.m_z + firstInertia.m_m[1][2] * firstAngularAxis.m_y +
					   firstInertia.m_m[0][2] * firstAngularAxis.m_x;

	GolVec3 firstAngularContribution;
	firstAngularContribution.m_x =
		firstAngular.m_y * firstContactOffset.m_z - firstAngular.m_z * firstContactOffset.m_y;
	firstAngularContribution.m_y =
		firstAngular.m_z * firstContactOffset.m_x - firstAngular.m_x * firstContactOffset.m_z;
	firstAngularContribution.m_z =
		firstAngular.m_x * firstContactOffset.m_y - firstAngular.m_y * firstContactOffset.m_x;

	GolVec3 secondAngularAxis;
	secondAngularAxis.m_x =
		secondContactOffset.m_y * collisionNormal.m_z - collisionNormal.m_y * secondContactOffset.m_z;
	secondAngularAxis.m_y =
		secondContactOffset.m_z * collisionNormal.m_x - collisionNormal.m_z * secondContactOffset.m_x;
	secondAngularAxis.m_z =
		secondContactOffset.m_x * collisionNormal.m_y - secondContactOffset.m_y * collisionNormal.m_x;

	const GolMatrix3& secondInertia = secondTarget->m_inverseInertia;
	GolVec3 secondAngular;
	secondAngular.m_x = secondInertia.m_m[2][0] * secondAngularAxis.m_z +
						secondInertia.m_m[1][0] * secondAngularAxis.m_y +
						secondInertia.m_m[0][0] * secondAngularAxis.m_x;
	secondAngular.m_y = secondInertia.m_m[2][1] * secondAngularAxis.m_z +
						secondInertia.m_m[1][1] * secondAngularAxis.m_y +
						secondInertia.m_m[0][1] * secondAngularAxis.m_x;
	secondAngular.m_z = secondInertia.m_m[2][2] * secondAngularAxis.m_z +
						secondInertia.m_m[1][2] * secondAngularAxis.m_y +
						secondInertia.m_m[0][2] * secondAngularAxis.m_x;

	GolVec3 secondAngularContribution;
	secondAngularContribution.m_x =
		secondAngular.m_y * secondContactOffset.m_z - secondAngular.m_z * secondContactOffset.m_y;
	secondAngularContribution.m_y =
		secondAngular.m_z * secondContactOffset.m_x - secondAngular.m_x * secondContactOffset.m_z;
	secondAngularContribution.m_z =
		secondAngular.m_x * secondContactOffset.m_y - secondAngular.m_y * secondContactOffset.m_x;

	GolVec3 angularContribution;
	angularContribution.m_x = firstAngularContribution.m_x + secondAngularContribution.m_x;
	angularContribution.m_y = firstAngularContribution.m_y + secondAngularContribution.m_y;
	angularContribution.m_z = firstAngularContribution.m_z + secondAngularContribution.m_z;

	LegoFloat impulseDenominator = GOLVECTOR3_DOT(collisionNormal, angularContribution) + inverseMassTerm;
	LegoFloat impulseScale = impulseNumerator / impulseDenominator;

	firstRacer->m_unk0x3e8.VTable0x20(&collisionNormal, impulseScale);
	if (firstRacer->m_unk0x014) {
		firstRacer->m_unk0x014->FUN_004220e0();
	}

	if (!secondRacer) {
		return;
	}

	secondRacer->m_unk0x3e8.VTable0x20(&collisionNormal, -impulseScale);
	if (secondRacer->m_unk0x014) {
		secondRacer->m_unk0x014->FUN_004220e0();
	}

	if (firstRacer->m_controlMode == 2 && secondRacer->m_controlMode == 2) {
		if (firstRacer->m_unk0x3e8.m_unk0x0dc == 1.0f) {
			firstRacer->m_speedRampTimerMs = 750;
		}

		if (secondRacer->m_unk0x3e8.m_unk0x0dc == 1.0f) {
			secondRacer->m_speedRampTimerMs = 750;
		}
	}
	else if (firstRacer->m_unk0x3e8.m_unk0x604 > secondRacer->m_unk0x3e8.m_unk0x604) {
		SoundVector* contactPosition = reinterpret_cast<SoundVector*>(&collision->m_contactPoint);

		if (!firstRacer->m_scrapeSoundCooldownMs && !secondRacer->m_scrapeSoundCooldownMs) {
			SoundVector soundDirection;
			soundDirection.m_x = firstRacer->m_unk0x3e8.m_unk0x008.m_x;
			soundDirection.m_y = firstRacer->m_unk0x3e8.m_unk0x008.m_y;
			soundDirection.m_z = firstRacer->m_unk0x3e8.m_unk0x008.m_z;
			GolMath::NormalizeVector3(soundDirection, &soundDirection);

			g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
			LegoU32 soundId = (g_randomTable[g_randomTableIndex] & 1) ? 0x37 : 0x18;
			m_soundSource->PlaySpatialSoundById(
				soundId,
				contactPosition,
				g_shieldSoundMinDistance,
				g_shieldSoundMaxDistance,
				1.0f,
				1.0f
			);

			firstRacer->m_scrapeSoundCooldownMs = 250;
			secondRacer->m_scrapeSoundCooldownMs = 250;
		}

		m_unk0x018.m_particleAnimation->FUN_00489d70("carsprk", &collision->m_contactPoint, NULL, NULL);

		if (firstRacer->m_unk0xd04 & c_flagShielded) {
			secondRacer->PlayReaction(FALSE);
		}
		else {
			firstRacer->PlayReaction(FALSE);
		}
	}
	else {
		firstRacer->PlayReaction(FALSE);
	}

	if ((firstRacer->m_unk0xd04 & c_flagShielded) && !(secondRacer->m_unk0xd04 & c_flagShielded)) {
		if (firstRacer->m_shieldLevel == 1) {
			GolVec3 secondForward;
			secondRacer->m_unk0x018.m_carEntity->GetOrientationRow0(&secondForward);
			LegoFloat dot = GOLVECTOR3_DOT(secondForward, secondContactOffset);

			if (dot > -g_shieldShoveConeCosine && dot < g_shieldShoveConeCosine) {
				GolVec3 shove = secondContactOffset;
				shove.m_x *= g_shieldShoveStrength;
				shove.m_y *= g_shieldShoveStrength;
				shove.m_z *= g_shieldShoveStrength;
				secondRacer->ApplyShove(&shove);
			}
		}
		else if (firstRacer->m_shieldLevel == 2) {
			secondRacer->m_unk0x3e8.VTable0x24(1.0f, 0.0089999996f, 0);
		}
		else if (firstRacer->m_shieldLevel == 3) {
			secondRacer->m_unk0x3e8.VTable0x24(2.0f, 0.0089999996f, 0);
		}
	}

	if ((secondRacer->m_unk0xd04 & c_flagShielded) && !(firstRacer->m_unk0xd04 & c_flagShielded)) {
		if (secondRacer->m_shieldLevel == 1) {
			GolVec3 firstForward;
			firstRacer->m_unk0x018.m_carEntity->GetOrientationRow0(&firstForward);
			LegoFloat dot = GOLVECTOR3_DOT(firstForward, firstContactOffset);

			if (dot > -g_shieldShoveConeCosine && dot < g_shieldShoveConeCosine) {
				GolVec3 shove = firstContactOffset;
				shove.m_x *= g_shieldShoveStrength;
				shove.m_y *= g_shieldShoveStrength;
				shove.m_z *= g_shieldShoveStrength;
				firstRacer->ApplyShove(&shove);
			}
		}
		else if (secondRacer->m_shieldLevel == 2) {
			firstRacer->m_unk0x3e8.VTable0x24(1.0f, 0.0089999996f, 0);
		}
		else if (secondRacer->m_shieldLevel == 3) {
			firstRacer->m_unk0x3e8.VTable0x24(2.0f, 0.0089999996f, 0);
		}
	}

	if ((firstRacer->m_unk0xd04 & c_flagCursed) && !(secondRacer->m_unk0xd04 & c_flagCursed) &&
		firstRacer->m_curseTickMs && !(secondRacer->m_unk0xd04 & c_flagShielded)) {
		secondRacer->AttachCurse(&firstRacer->m_unk0x018.m_curseEntity, firstRacer->m_curseTimerMs);
		firstRacer->RemoveCurse();
	}
	else if (
		(secondRacer->m_unk0xd04 & c_flagCursed) && !(firstRacer->m_unk0xd04 & c_flagCursed) &&
		secondRacer->m_curseTickMs && !(firstRacer->m_unk0xd04 & c_flagShielded)
	) {
		firstRacer->AttachCurse(&secondRacer->m_unk0x018.m_curseEntity, secondRacer->m_curseTimerMs);
		secondRacer->RemoveCurse();
	}

	firstRacer->m_unk0xd04 |= c_flagSpeedRamping;
	secondRacer->m_unk0xd04 |= c_flagSpeedRamping;
}

// FUNCTION: LEGORACERS 0x00438e60
void RaceState::Racer::ApplyShove(GolVec3* p_unk0x04)
{
	LegoEventQueue::Descriptor descriptor;
	if (m_unk0xd04 & c_flagShoveActive) {
		return;
	}

	descriptor.m_unk0x04 = 0;
	descriptor.m_unk0x0c = 0;
	descriptor.m_unk0x00 = 1;
	descriptor.m_unk0x08 = 1;
	descriptor.m_unk0x10 = 750;
	if (m_raceState->GetUnk0x0f0()->FUN_0042fb50(this, &descriptor) == NULL) {
		return;
	}

	m_unk0x3e8.FUN_00447f30(2.5f, 0.89999998f, 3.1415927f);
	LegoU32 flags = m_unk0x3e8.m_flags0x6c0;
	if (!(flags & Physics::c_flags0x6c0Bit5)) {
		m_unk0x3e8.VTable0x40(p_unk0x04);
		m_shoveReleaseAction = 1;
	}
	else if (!(flags & Physics::c_flags0x6c0Bit6)) {
		m_unk0x3e8.VTable0x48(p_unk0x04);
		m_shoveReleaseAction = 2;
	}

	m_unk0xd04 |= c_flagShoveActive;
}

// FUNCTION: LEGORACERS 0x00438f20
void RaceState::Racer::AiConsiderPowerup()
{
	if (m_unk0x008->GetUsedEffectEntityCount() >= 20) {
		m_aiPowerupCheckIntervalMs = 1000;
	}
	else {
		LegoU32 state = m_aiChargeColor;
		if (state && state == m_heldPowerupColor && m_whiteBrickCount < m_aiChargeTarget) {
			m_aiPowerupCheckIntervalMs = 1000;
		}
		else {
			switch (m_heldPowerupColor) {
			case 3:
				g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
				if ((g_randomTable[g_randomTableIndex] & 0xff) >= m_aiGreenUseChance) {
					m_aiPowerupCheckIntervalMs = 1000;
				}
				else {
					if ((m_unk0xd04 & c_flags0xd04Bit12) && m_whiteBrickCount == 3) {
						return;
					}
					if (m_unk0x3e8.m_flags0x6c0 & c_flags0xaa8Bit1) {
						return;
					}

					AiUsePowerup();
				}
				return;
			case 1: {
				GolVec3 position;
				m_unk0x018.m_carEntity->VTable0x04(&position);

				GolVec3 direction;
				m_unk0x018.m_carEntity->GetOrientationRow0(&direction);

				if (!m_raceState->FindNearestRacerInCone(
						&position,
						&direction,
						g_unk0x004b0974,
						g_unk0x004b0978,
						g_unk0x004b097c
					)) {
					return;
				}
				g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
				if ((g_randomTable[g_randomTableIndex] & 0xff) >= m_aiRedUseChance) {
					m_aiPowerupCheckIntervalMs = 1000;
				}
				else {
					AiUsePowerup();
				}
				return;
			}
			case 4:
				g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
				if ((g_randomTable[g_randomTableIndex] & 0xff) >= m_aiYellowUseChance) {
					m_aiPowerupCheckIntervalMs = 1000;
				}
				else {
					AiUsePowerup();
				}
				return;
			case 2:
				g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
				if ((g_randomTable[g_randomTableIndex] & 0xff) >= m_aiBlueUseChance) {
					m_aiPowerupCheckIntervalMs = 1000;
				}
				else {
					AiUsePowerup();
				}
				return;
			default:
				return;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00439100
void RaceState::Racer::AiUsePowerup()
{
	LegoU32 state = m_heldPowerupColor;
	if (!state) {
		FUN_00439c90();
		return;
	}

	LegoU32 flags = m_unk0xd04;
	LegoU32 index = m_whiteBrickCount;

	if (flags & c_flagCheatRedOnly) {
		m_unk0x008->UseRedPowerup(this, 1);
	}
	else {
		if (flags & c_flagCheatMaxPowerups) {
			index = 3;
		}

		switch (state) {
		case 3:
			if (!((flags & c_flagCheatFastForward) && index != 3)) {
				m_unk0x008->UseGreenPowerup(this, index);
			}
			break;
		case 1:
			m_unk0x008->UseRedPowerup(this, index);
			break;
		case 4:
			PlayReaction(TRUE);
			m_unk0x008->UseYellowPowerup(this, index);
			break;
		case 2:
			PlayReaction(TRUE);
			m_unk0x008->UseBluePowerup(this, index);
			break;
		default:
			return;
		}
	}

	m_heldPowerupColor = 0;
	ReturnAllWhiteBricks();
}

// FUNCTION: LEGORACERS 0x00439210
LegoU32 RaceState::Racer::CollectColorBrick(LegoU32 p_unk0x04)
{
	m_aiPowerupCheckMs = 0;
	m_heldPowerupColor = p_unk0x04;
	m_aiPowerupCheckIntervalMs = 300;
	return p_unk0x04;
}

// FUNCTION: LEGORACERS 0x00439240
void RaceState::Racer::PlayReaction(LegoBool32 p_unk0x04)
{
	if (m_reactionCooldownMs <= 0) {
		SoundVector position;
		m_unk0x018.m_carEntity->VTable0x04(&position);

		LegoU32 randomIndex;
		if (p_unk0x04) {
			randomIndex = (g_randomTableIndex + 1) & c_randomTableMask;
			LegoU32 randomValue = g_randomTable[randomIndex];
			g_randomTableIndex = randomIndex;
			m_soundSource->PlaySpatialSoundById(
				randomValue % c_feedbackVariantCount + m_voiceBank + c_feedbackHighOffset,
				&position,
				100.0f,
				400.0f,
				1.0f,
				1.0f
			);
		}
		else {
			randomIndex = (g_randomTableIndex + 1) & c_randomTableMask;
			g_randomTableIndex = randomIndex;
			LegoU32 randomValue = g_randomTable[randomIndex];
			m_soundSource->PlaySpatialSoundById(
				m_voiceBank + randomValue % c_feedbackVariantCount,
				&position,
				100.0f,
				400.0f,
				1.0f,
				1.0f
			);
		}

		randomIndex = (g_randomTableIndex + 1) & c_randomTableMask;
		g_randomTableIndex = randomIndex;
		LegoU16 randomValue = g_randomTable[randomIndex];
		m_reactionCooldownMs = randomValue * 4 + 5000;
	}
}

// STUB: LEGORACERS 0x00439340
void RaceState::Racer::FUN_00439340()
{
	LegoU32 value = m_unk0xd04 & 0xfffffffd;
	m_unk0xd04 = value;

	value = 1;
	m_unk0x3e8.m_unk0x6ec = value;

	if (m_unk0xe2c) {
		m_unk0x3e8.m_unk0x748 = 0;
	}

	m_unk0xd14 = value;
	value = m_controlMode;
	m_unk0xd0c = 0;
	m_unk0xd10 = 2;

	if (value == 2) {
		g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
		value = g_randomTable[g_randomTableIndex];
		if ((value & 0xff) < m_aiGreenUseChance) {
			m_unk0x008->UseGreenPowerup(this, 0);
		}
	}
}

// FUNCTION: LEGORACERS 0x004393d0
void RaceState::Racer::FUN_004393d0()
{
	SoundVector position;
	m_unk0x018.m_carEntity->VTable0x04(&position);

	m_soundSource
		->PlaySpatialSoundById(0x3e, &position, g_shieldSoundMinDistance, g_shieldSoundMaxDistance, 1.0f, 1.0f);
	m_unk0xd04 |= c_flagEngineSounds;
}

// FUNCTION: LEGORACERS 0x00439420
LegoBool32 RaceState::Racer::CollectWhiteBrick(DroppableBrick* p_unk0x04)
{
	if (m_whiteBrickCount != sizeOfArray(m_whiteBricks)) {
		LegoU32 index = 0;
		DroppableBrick** current = m_whiteBricks;

		while (TRUE) {
			if (!*current) {
				break;
			}

			index++;
			current++;

			if (index >= sizeOfArray(m_whiteBricks)) {
				return FALSE;
			}
		}

		m_whiteBricks[index] = p_unk0x04;
		m_soundSource->PlaySoundById(m_whiteBrickCount + 11);

		LegoU32 count = m_whiteBrickCount + 1;
		m_whiteBrickCount = count;

		if (count == sizeOfArray(m_whiteBricks)) {
			PlayReaction(TRUE);
		}

		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00439490
RaceState::Racer::DroppableBrick* RaceState::Racer::DropWhiteBrick()
{
	DroppableBrick* result;
	LegoU32 index;

	if (!m_whiteBrickCount) {
		return NULL;
	}

	index = 0;
	DroppableBrick** current = m_whiteBricks;
	while (index < sizeOfArray(m_whiteBricks)) {
		if (*current) {
			result = m_whiteBricks[index];
			m_whiteBricks[index] = NULL;

			GolVec3 position;
			m_unk0x018.m_carEntity->VTable0x04(&position);
			m_whiteBrickCount--;
			result->DropAt(position);
			return result;
		}

		index++;
		current++;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00439520
LegoU32 RaceState::Racer::ReturnAllWhiteBricks()
{
	LegoU32 result = m_whiteBrickCount;

	if (result) {
		DroppableBrick** current = m_whiteBricks;
		LegoS32 remaining = sizeOfArray(m_whiteBricks);
		do {
			if (*current) {
				(*current)->ReturnHome();
				result = m_whiteBrickCount - 1;
				m_whiteBrickCount = result;
				*current = NULL;
			}

			current++;
		} while (--remaining);
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00439570
void RaceState::Racer::Halt()
{
	LegoU32 flags = m_unk0xd04;
	if (!(flags & c_flagHalted)) {
		m_unk0xd04 = flags | c_flagHalted;
		m_unk0x3e8.VTable0x2c();
		m_unk0x3e8.VTable0x30();
	}
}

// FUNCTION: LEGORACERS 0x004395a0
void RaceState::Racer::Resume()
{
	LegoU32 flags = m_unk0xd04;
	if (flags & c_flagHalted) {
		m_unk0xd04 = flags & ~c_flagHalted;
		m_unk0x3e8.VTable0x34();
	}
}

// FUNCTION: LEGORACERS 0x004395d0
void RaceState::Racer::EnterGhostMode()
{
	m_unk0xd04 |= c_flagGhost;
	RemoveCurse();
	m_unk0x018.StopSkidEffects();
	m_unk0x018.HideModels();
	m_unk0x018.m_flags &= ~(CarVisuals::c_flagShadowEnabled | CarVisuals::c_flagShadowVisible);
	m_unk0x018.StopTurboEffects();
	m_unk0x018.StopSlideSkid();
	Physics* field0x3e8 = &m_unk0x3e8;
	field0x3e8->VTable0x2c();

	if (m_controlMode == 2 && m_unk0x3e8.m_unk0x744) {
		field0x3e8->FUN_00429a90();
	}
	else {
		field0x3e8->m_flags0x6c0 |= c_flags0xaa8Bit12;
	}

	if (m_unk0x014) {
		m_unk0x014->FUN_00422030(3);
	}
}

// FUNCTION: LEGORACERS 0x00439660
void RaceState::Racer::LeaveGhostMode()
{
	m_unk0xd04 &= ~c_flagGhost;

	CarVisuals* field = &m_unk0x018;
	field->ShowModels();

	if (m_controlMode == 2 && m_unk0x3e8.m_unk0x744) {
		m_unk0x3e8.FUN_00429af0();
		field->m_flags |= CarVisuals::c_flagShadowEnabled;
		return;
	}

	m_unk0x3e8.m_flags0x6c0 &= ~c_flags0xaa8Bit12;
	field->m_flags |= CarVisuals::c_flagShadowEnabled;
}

// FUNCTION: LEGORACERS 0x004396c0
void RaceState::Racer::StartTurbo(LegoU32 p_unk0x04)
{
	m_unk0xd04 |= c_flagTurbo;

	if (m_controlMode != 2) {
		m_unk0x018.StartTurboEffects();
	}

	m_unk0xc70.m_unk0x014 =
		(m_unk0xc70.m_unk0x014 & ~DriveController::c_flags0x014Bit8) | DriveController::c_flags0x014Bit0;
	m_unk0x3e8.FUN_00446fa0();
	m_unk0x3e8.FUN_004292e0();
	m_turboLevel = p_unk0x04;

	if (m_unk0x014) {
		m_unk0x014->FUN_00422030(p_unk0x04);
	}
}

// FUNCTION: LEGORACERS 0x00439730
void RaceState::Racer::ClearActiveAction()
{
	m_unk0xd04 &= ~c_flagTurbo;
	m_unk0x018.StopTurboEffects();
	m_unk0xc70.m_unk0x014 &= ~(DriveController::c_flags0x014Bit0 | DriveController::c_flags0x014Bit8);
	m_unk0x3e8.FUN_00429330();
}

// FUNCTION: LEGORACERS 0x00439770
LegoU32 RaceState::Racer::StartShield(LegoU32 p_unk0x04)
{
	m_unk0xd04 |= c_flagShielded;
	m_shieldLevel = p_unk0x04;
	return p_unk0x04;
}

// FUNCTION: LEGORACERS 0x00439790
void RaceState::Racer::EndShield()
{
	m_unk0xd04 &= ~c_flagShielded;
}

// FUNCTION: LEGORACERS 0x004397a0
void RaceState::Racer::StartSpinOut()
{
	m_unk0x3e8.VTable0x38();
}

// FUNCTION: LEGORACERS 0x004397b0
void RaceState::Racer::EndSpinOut()
{
	m_unk0x3e8.VTable0x3c();
}

// FUNCTION: LEGORACERS 0x004397c0
void RaceState::Racer::StartDrift(LegoBool32 p_unk0x04)
{
	if (!(m_unk0xd04 & c_flagDrifting) || p_unk0x04 != m_unk0xc70.m_unk0x030) {
		m_unk0xc70.FUN_00420260(p_unk0x04);

		if (m_unk0xc70.m_unk0x014 & DriveController::c_flags0x014Bit2) {
			m_unk0xd04 |= c_flagDrifting;

			if (!m_controlMode && !(m_unk0x3e8.m_flags0x6c0 & c_flags0xaa8Bit3)) {
				SoundVector position;
				m_unk0x018.StartDust();

				if (!(m_unk0x018.m_flags & CarVisuals::c_flagSkidding)) {
					m_unk0x018.StartSkidEffects();
				}

				m_unk0x018.m_carEntity->VTable0x04(&position);
				m_soundSource->PlaySpatialSoundById(
					0x39,
					&position,
					g_shieldSoundMinDistance,
					g_shieldSoundMaxDistance,
					1.0f,
					1.0f
				);
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00439870
void RaceState::Racer::EndDrift()
{
	SoundVector position;

	if (m_unk0xd04 & c_flagDrifting) {
		if (m_unk0xc70.m_unk0x014 & DriveController::c_flags0x014Bit2) {
			m_unk0xc70.FUN_004202c0();
		}

		LegoU8 flags0xaa8 = static_cast<LegoU8>(m_unk0x3e8.m_flags0x6c0);
		LegoU8 testFlag = c_flags0xaa8Bit3;
		if (!(testFlag & flags0xaa8)) {
			if (m_unk0xc70.m_unk0x014 & DriveController::c_flags0x014Bit3) {
				m_unk0x018.m_carEntity->VTable0x04(&position);
				m_soundSource->PlaySpatialSoundById(
					0x41,
					&position,
					g_shieldSoundMinDistance,
					g_shieldSoundMaxDistance,
					1.0f,
					1.0f
				);
			}

			if (!(m_unk0xc70.m_unk0x014 & DriveController::c_flags0x014Bit0)) {
				m_unk0x018.StopSkidEffects();
			}
		}

		LegoU32 flags0xd04 = m_unk0xd04;
		flags0xd04 &= ~c_flagDrifting;
		m_unk0xd04 = flags0xd04;
	}
}

// FUNCTION: LEGORACERS 0x00439900
void RaceState::Racer::AttachCurse(GolAnimatedEntity* p_unk0x04, LegoU32 p_durationMs)
{
	LegoU32 flags0xd04 = m_unk0xd04;
	m_curseTimerMs = p_durationMs;
	flags0xd04 |= c_flagCursed;
	m_curseTickMs = 1000;
	m_unk0xd04 = flags0xd04;

	LegoU32 flags0xc70 = m_unk0xc70.m_unk0x014;
	flags0xc70 |= DriveController::c_flags0x014Bit4;
	GolAnimatedEntity* entity = &m_unk0x018.m_curseEntity;
	m_unk0xc70.m_unk0x014 = flags0xc70;

	LegoU32 flags0x384 = m_unk0x018.m_reactionFlags;
	flags0x384 |= CarVisuals::c_flags0x384Bit1;
	m_unk0x018.m_reactionFlags = flags0x384;

	entity->FUN_0040d550(
		p_unk0x04->GetModel(0),
		p_unk0x04->VTable0x58(0),
		p_unk0x04->GetModelPart(0),
		p_unk0x04->GetModelDistance(0)
	);

	for (LegoU32 i = 1; i < 3; i++) {
		if (p_unk0x04->GetModel(i)) {
			entity->FUN_10023940(
				p_unk0x04->GetModel(i),
				p_unk0x04->VTable0x58(i),
				p_unk0x04->GetModelPart(i),
				p_unk0x04->GetModelDistance(i)
			);
		}
	}

	entity->FUN_0040dad0(0);
	entity->SetPartAnimationEnabled(TRUE);
	entity->CopyOrientationFrom(*p_unk0x04);
	entity->CopyPositionFrom(*p_unk0x04);

	m_soundDac = m_soundSource->AcquireSoundById(8);
	if (m_soundDac) {
		m_soundDac->Play(TRUE);
		m_soundDac->SetDistanceRangeWithMinSquared(
			g_shieldSoundMinDistance * g_shieldSoundMinDistance,
			g_shieldSoundMaxDistance
		);

		GolVec3 position;
		p_unk0x04->VTable0x04(&position);
		m_soundDac->SetPosition(position);
	}

	ColorTransform0x20 transform;
	transform.m_redShift = 0;
	transform.m_grnShift = 1;
	transform.m_bluShift = 0;
	transform.m_alpShift = 1;
	transform.m_redOffset = 0x40;
	transform.m_grnOffset = 0;
	transform.m_bluOffset = 0;
	transform.m_alpOffset = 0;
	m_unk0x018.FlashColor(&transform, p_durationMs);
	m_unk0x3e8.FUN_00429380();
}

// FUNCTION: LEGORACERS 0x00439b00
void RaceState::Racer::RemoveCurse()
{
	if (m_curseSound) {
		m_soundSource->ReleaseSound(m_curseSound);
		m_curseSound = NULL;
	}

	LegoU32 flags0xd04 = m_unk0xd04;
	m_curseTimerMs = 0;
	flags0xd04 &= ~c_flagCursed;
	m_unk0xd04 = flags0xd04;

	m_unk0xc70.m_unk0x014 &= ~DriveController::c_flags0x014Bit4;
	m_unk0x018.m_curseEntity.VTable0x54();
	m_unk0x018.EndFlash();
	m_unk0x3e8.FUN_004293c0();
}

// FUNCTION: LEGORACERS 0x00439b70
void RaceState::Racer::FUN_00439b70()
{
	LegoU32 state = m_unk0xd0c;
	if (state) {
		LegoU32 oldState = m_unk0xd10;
		m_unk0xd10 = state;
		m_unk0xd14 = oldState;
		m_unk0xd0c = 0;
	}
}

// FUNCTION: LEGORACERS 0x00439ba0
LegoU32 RaceState::Racer::FUN_00439ba0()
{
	LegoU32 result = m_unk0xd0c;
	if (result != 1) {
		if (result == 0 && m_unk0xd10 == 2 && m_unk0xd14 == 1) {
			LegoU32 lapTransitionCount = m_lapTransitionCount + 1;
			m_lapTransitionCount = lapTransitionCount;

			if (static_cast<LegoS32>(lapTransitionCount) > 0) {
				result = m_lapsCompleted;
				if (lapTransitionCount > result) {
					RaceState* raceState = m_raceState;
					m_lapsCompleted = result + 1;
					result = raceState->GetTimeBehind(this);
					m_timeBehind = result;

					if (result) {
						result = m_unk0xce0;
						if (m_lapsCompleted < result) {
							m_timeBehindDisplayMs = 2000;
						}
					}
				}
			}
		}

		LegoU32 state = m_unk0xd0c;
		m_unk0xd14 = m_unk0xd10;
		m_unk0xd10 = state;
		m_unk0xd0c = 1;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00439c40
void RaceState::Racer::FUN_00439c40()
{
	LegoU32 state = m_unk0xd0c;
	if (state != 2) {
		LegoU32 oldState = m_unk0xd10;
		m_unk0xd10 = state;
		m_unk0xd14 = oldState;
		m_unk0xd0c = 2;
	}
}

// FUNCTION: LEGORACERS 0x00439c70
void RaceState::Racer::ComputeStandingsDeltas(Records::StandingsDeltaEntry* p_entries)
{
	m_raceState->ComputeStandingsDeltas(this, p_entries);
}

// FUNCTION: LEGORACERS 0x00439c90
void RaceState::Racer::FUN_00439c90()
{
	SoundVector position;
	m_unk0x018.m_carEntity->VTable0x04(&position);

	m_soundSource
		->PlaySpatialSoundById(m_unk0xd23, &position, g_shieldSoundMinDistance, g_shieldSoundMaxDistance, 1.0f, 1.0f);
	m_unk0x3e8.m_unk0x6f4->FUN_00462580(999, 999, &position);
}

// FUNCTION: LEGORACERS 0x00439cf0
void RaceState::Racer::FUN_00439cf0(LegoU32 p_elapsedMs)
{
	RaceSessionField0x27f4::Entry* field0xcc4 = m_unk0xcc4;
	if (field0xcc4) {
		LegoU32 flags = m_unk0xd04;
		LegoBool32 isBlocked = FALSE;

		if (flags & c_flagGhost) {
			m_unk0xd78 = 0;
			m_unk0xd04 = flags & ~(c_flags0xd04Bit13 | c_flags0xd04Bit14);
			return;
		}

		LegoU32 countdown = m_unk0xd78;
		if (countdown) {
			if (p_elapsedMs >= countdown) {
				m_unk0xd78 = 0;
				m_unk0xd04 = flags & ~c_flags0xd04Bit14;
			}
			else {
				m_unk0xd78 = countdown - p_elapsedMs;
			}
		}

		GolVec3 direction = m_unk0x3e8.m_unk0x168;
		for (LegoU32 i = 0; i < sizeOfArray(field0xcc4->m_unk0x20.m_items); i++) {
			if (isBlocked) {
				break;
			}

			if (field0xcc4->m_unk0x20.m_items[i] != 0xff) {
				m_unk0x010->FUN_0041e940(field0xcc4->m_unk0x20.m_items[i]);
				field0xcc4 = m_unk0xcc4;
				LegoFloat dot = direction.m_z * field0xcc4->m_unk0x00.m_z + direction.m_y * field0xcc4->m_unk0x00.m_y +
								direction.m_x * field0xcc4->m_unk0x00.m_x;
				if (dot <= g_unk0x004b02e0) {
					isBlocked = TRUE;
				}
			}
		}

		flags = m_unk0xd04;
		if (flags & c_flags0xd04Bit13) {
			if (isBlocked) {
				m_unk0xd78 = 0;
				m_unk0xd04 = flags & ~c_flags0xd04Bit13;
			}
			else if (!m_unk0xd78) {
				m_unk0xd04 = (flags & ~(c_flags0xd04Bit13 | c_flags0xd04Bit14)) | c_flags0xd04Bit14;
			}
		}
		else {
			if (!(flags & c_flags0xd04Bit14)) {
				if (!isBlocked) {
					m_unk0xd78 = 500;
					m_unk0xd04 = flags | c_flags0xd04Bit13;
				}
			}
			else if (!isBlocked) {
				m_unk0xd78 = 500;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00439e60
void RaceState::Racer::FUN_00439e60(GolVec3* p_unk0x04)
{
	m_unk0xd04 |= c_flags0xd04Bit15;
	m_unk0xdf8.m_x = p_unk0x04->m_x;
	m_unk0xdf8.m_y = p_unk0x04->m_y;
	m_unk0xdf8.m_z = p_unk0x04->m_z;
}

// FUNCTION: LEGORACERS 0x00439e90
void RaceState::Racer::FUN_00439e90()
{
	m_unk0xd04 &= ~c_flags0xd04Bit15;
}

// FUNCTION: LEGORACERS 0x00439ea0
void RaceState::Racer::FUN_00439ea0(LegoU32)
{
	LegoU32 flags = m_unk0xd04 & ~(c_flags0xd04Bit16 | c_flags0xd04Bit17);
	m_unk0xd04 = flags;

	if (m_unk0xd04 & c_flags0xd04Bit15) {
		GolVec3 direction = m_unk0x3e8.m_unk0x168;
		GolVec3 position;
		m_unk0x018.m_carEntity->VTable0x04(&position);

		GolVec3 delta;
		delta.m_x = m_unk0xdf8.m_x - position.m_x;
		delta.m_y = m_unk0xdf8.m_y - position.m_y;
		delta.m_z = m_unk0xdf8.m_z - position.m_z;
		GolMath::NormalizeVector3(delta, &delta);

		LegoFloat forwardDot = direction.m_z * delta.m_z + direction.m_y * delta.m_y + direction.m_x * delta.m_x;
		if (forwardDot < 0.5f) {
			GolVec3 side;
			side.m_x = direction.m_y - 0.0f;
			side.m_y = 0.0f - direction.m_x;
			side.m_z = 0.0f;
			if (GOLVECTOR3_DOT(side, delta) > 0.0f) {
				m_unk0xd04 |= c_flags0xd04Bit16;
			}
			else {
				m_unk0xd04 |= c_flags0xd04Bit17;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00439fc0
void RaceState::Racer::FUN_00439fc0(RaceSessionField0x27f4::Entry* p_unk0x04, GolBoundingVolume::Field0x0c* p_unk0x08)
{
	LegoBool32 isForward;
	if (p_unk0x08->m_normal.m_z * p_unk0x04->m_unk0x00.m_z + p_unk0x08->m_normal.m_y * p_unk0x04->m_unk0x00.m_y +
			p_unk0x08->m_normal.m_x * p_unk0x04->m_unk0x00.m_x <
		0.0f) {
		isForward = FALSE;
	}
	else {
		isForward = TRUE;
	}

	if (p_unk0x04 != m_unk0xcc4 || isForward != m_unk0xcc8) {
		if (p_unk0x04->m_unk0x1c == 0.0f) {
			LegoU32 flags = m_unk0xd04;
			if (isForward) {
				if (!(flags & c_flags0xd04Bit19)) {
					m_unk0xd18++;
				}
			}
			else {
				m_unk0xcc8 = isForward;
				m_unk0xd04 = flags | c_flags0xd04Bit19;
				m_unk0xd0c = 0;
				m_unk0xd10 = 2;
				m_unk0xd14 = 2;
				m_unk0xcc4 = p_unk0x04;
				return;
			}

			m_unk0xd04 = flags & ~c_flags0xd04Bit19;
		}
		else {
			LegoU32 flags = m_unk0xd04;
			if (!(flags & c_flags0xd04Bit19)) {
				m_unk0xcc4 = p_unk0x04;
				m_unk0xcc8 = isForward;
				return;
			}

			m_unk0xd18--;
			m_unk0xd04 = flags & ~c_flags0xd04Bit19;
		}

		m_unk0xcc4 = p_unk0x04;
		m_unk0xcc8 = isForward;
	}
}

// FUNCTION: LEGORACERS 0x0043a0a0
LegoFloat RaceState::Racer::FUN_0043a0a0()
{
	if (m_unk0xcc4) {
		return static_cast<LegoFloat>(m_unk0xd18) + m_unk0xcc4->m_unk0x1c;
	}

	return 0.0f;
}

// FUNCTION: LEGORACERS 0x0043a0c0
void RaceState::Racer::FUN_0043a0c0()
{
	m_unk0xe30->m_unk0x03c = (m_unk0xe30->m_unk0x03c + 1) & 3;
}

// FUNCTION: LEGORACERS 0x0043a0e0
void RaceState::Racer::FUN_0043a0e0()
{
	Records::Entry* unk0xe2c = m_unk0xe2c;
	m_controlMode = 2;

	if (!unk0xe2c) {
		unk0xe2c = m_raceState->FindNearestRouteRecord(this);
		m_unk0xe2c = unk0xe2c;

		if (unk0xe2c) {
			m_unk0xc70.FUN_004202f0(unk0xe2c);
		}
		else {
			m_unk0xc70.m_unk0x014 |= 0x80;
		}
	}
}

// FUNCTION: LEGORACERS 0x0043a130
void RaceState::Racer::StartMagnetHold()
{
	m_unk0xd04 |= c_flags0xd04Bit20;

	if (m_controlMode != 2) {
		m_unk0xc70.m_unk0x014 |= DriveController::c_flags0x014Bit7;
		m_unk0x018.StartSkidEffects();
	}

	if (m_unk0x3e8.m_unk0x744) {
		m_unk0x3e8.m_unk0x7e8 = 0.0f;
		if (!(m_unk0x3e8.m_flags0x6c0 & c_flags0xaa8Bit18)) {
			m_unk0x3e8.m_unk0x7ec = 0.0f;
		}
	}

	Resume();
}

// FUNCTION: LEGORACERS 0x0043a1a0
void RaceState::Racer::EndMagnetHold()
{
	LegoU32 flags0xd04 = m_unk0xd04;
	LegoU32 state = m_controlMode;
	flags0xd04 &= ~c_flags0xd04Bit20;
	m_unk0xd04 = flags0xd04;

	if (state != 2) {
		LegoU32 flags0x014 = m_unk0xc70.m_unk0x014;
		flags0x014 &= ~DriveController::c_flags0x014Bit7;
		m_unk0xc70.m_unk0x014 = flags0x014;
		m_unk0x018.StopSkidEffects();
	}

	if (m_unk0x3e8.m_unk0x744) {
		LegoU32 flags0xaa8 = m_unk0x3e8.m_flags0x6c0;
		m_unk0x3e8.m_unk0x7e8 = 1.0f;
		if (!(flags0xaa8 & c_flags0xaa8Bit18)) {
			m_unk0x3e8.m_unk0x7ec = 1.0f;
		}
	}

	Resume();
}

// FUNCTION: LEGORACERS 0x0043a210
void RaceState::Racer::FUN_0043a210(LegoU32 p_unk0x04)
{
	if (!(m_unk0xd04 & c_flagPreStart)) {
		LegoU32 unk0xd00 = m_lapTimes[5];
		if (p_unk0x04 < unk0xd00) {
			PlayReaction(TRUE);
		}
		else if (p_unk0x04 > unk0xd00) {
			PlayReaction(FALSE);
		}

		m_lapTimes[5] = p_unk0x04;
	}
	else {
		m_lapTimes[5] = p_unk0x04;
	}
}

// FUNCTION: LEGORACERS 0x0043a270
void RaceState::Racer::AbsorbShieldHit()
{
	LegoU32 soundId = 1;
	SoundVector position;
	m_unk0x018.m_carEntity->VTable0x04(&position);

	LegoU32 randomIndex = (g_randomTableIndex + 1) & c_randomTableMask;
	g_randomTableIndex = randomIndex;
	LegoS32 randomValue = g_randomTable[randomIndex];
	switch (randomValue % 3) {
	case 1:
		soundId = 0x46;
		break;
	case 2:
		soundId = 0x47;
		break;
	}

	m_soundSource->PlaySpatialSoundById(soundId, &position, g_unk0x004b0960, g_unk0x004b0964, 1.0f, 1.0f);
	m_unk0xd74 = 500;
}

// FUNCTION: LEGORACERS 0x0043a300
void RaceState::Racer::FUN_0043a300(LegoU32 p_unk0x04, LegoBool32 p_unk0x08)
{
	if (m_cameraController) {
		m_cameraController->FUN_004283f0(p_unk0x04, p_unk0x08);
		m_cameraController->m_unk0x000 = TRUE;
		m_unk0xdb8 = p_unk0x04;

		if (p_unk0x08) {
			m_unk0xd04 |= c_flags0xd04Bit22;
		}
		else {
			m_unk0xd04 &= ~c_flags0xd04Bit22;
		}
	}
}

// FUNCTION: LEGORACERS 0x0043a360
void RaceState::Racer::FUN_0043a360()
{
	if (m_cameraController) {
		m_cameraController->FUN_004283f0(m_unk0xdb8, m_unk0xd04 & 0x00400000);
		m_cameraController->m_unk0x000 = TRUE;
	}
}

// FUNCTION: LEGORACERS 0x0043a390
void RaceState::Racer::FUN_0043a390()
{
	LegoU32 flags = m_unk0xd04;
	if (!(flags & c_flags0xd04Bit12) && (flags & c_flagEngineSounds)) {
		RaceCameraController* controller = m_cameraController;
		if (controller) {
			LegoU32 index = m_unk0xdb8;
			LegoBool32 enabled = flags & c_flags0xd04Bit22;
			index++;
			index &= 3;
			m_unk0xdb8 = index;
			controller->FUN_004283f0(index, enabled);
			m_cameraController->m_unk0x000 = TRUE;
		}
	}
}

// FUNCTION: LEGORACERS 0x0043a3e0
void RaceState::Racer::FUN_0043a3e0()
{
	if (m_cameraController) {
		m_cameraController->m_unk0x000 = TRUE;
	}
}

// FUNCTION: LEGORACERS 0x0043a3f0
void RaceState::Racer::FUN_0043a3f0()
{
	m_cameraController->m_unk0x004 = TRUE;
}

// FUNCTION: LEGORACERS 0x0043a400
void RaceState::Racer::FUN_0043a400()
{
	m_cameraController->m_unk0x004 = FALSE;
}

// FUNCTION: LEGORACERS 0x0043a410
RaceState::Field0x284::Field0x284()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0043a420
RaceState::Field0x284::~Field0x284()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0043a430
void RaceState::Field0x284::Reset()
{
	m_racers = NULL;
	m_racerCount = 0;
	m_updateDelayMs = 0;
	m_unk0x0c = 0.0f;
}

// FUNCTION: LEGORACERS 0x0043a440
void RaceState::Field0x284::Destroy()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0043a450
void RaceState::Field0x284::FUN_0043a450(Racer* p_racers, LegoU32 p_racerCount)
{
	if (m_racers) {
		Destroy();
	}

	m_racers = p_racers;
	m_racerCount = p_racerCount;
	m_updateDelayMs = 15000;
}

// FUNCTION: LEGORACERS 0x0043a480
LegoU32 RaceState::Field0x284::FUN_0043a480(LegoU32 p_elapsedMs)
{
	LegoU32 delayMs = m_updateDelayMs;
	LegoFloat bestProgress = -1.0f;
	LegoU32 result;

	if (p_elapsedMs > delayMs) {
		result = m_racerCount;
		LegoU32 racerIndex = 0;
		LegoU32 ignoredState;
		m_updateDelayMs = 0;

		if (result <= 0) {
			goto ResetRacerPacing;
		}

		ignoredState = 2;
		do {
			LegoU32 state = m_racers[racerIndex].m_controlMode;
			if (state != ignoredState && m_racers[racerIndex].FUN_0043a0a0() > bestProgress) {
				bestProgress = m_racers[racerIndex].FUN_0043a0a0();
			}

			result = m_racerCount;
			racerIndex++;
		} while (racerIndex < result);

		if (bestProgress == g_minSoundPan) {
		ResetRacerPacing:
			result = m_racerCount;
			LegoU32 index = 0;
			if (result > 0) {
				LegoU32 flags0xaa8Mask = c_racerFlags0xaa8Bit18;
				do {
					Racer* racer = &m_racers[index];
					if (!(racer->m_unk0xd04 & c_racerFlags0xd04RubberBandMask)) {
						LegoU32 flags0xaa8 = racer->m_unk0x3e8.m_flags0x6c0;
						racer->m_unk0x3e8.m_unk0x7e8 = 1.0f;
						if (!(flags0xaa8Mask & flags0xaa8)) {
							racer->m_unk0x3e8.m_unk0x7ec = 1.0f;
						}
					}

					result = m_racerCount;
					index++;
				} while (index < result);
			}
		}
		else {
			result = m_racerCount;
			racerIndex = 0;
			if (result > 0) {
				LegoU32 flags0xaa8Mask = c_racerFlags0xaa8Bit18;
				do {
					if (racerIndex) {
						if (!(m_racers[racerIndex].m_unk0xd04 & c_racerFlags0xd04RubberBandMask)) {
							if (m_racers[racerIndex].FUN_0043a0a0() > bestProgress) {
								LegoFloat adjustment = 1.0f - g_unk0x004b09dc;
								adjustment += m_unk0x0c;
								Racer::Physics* field0x3e8 = &m_racers[racerIndex].m_unk0x3e8;
								LegoU32 flags0xaa8 = field0x3e8->m_flags0x6c0;
								field0x3e8->m_unk0x7e8 = adjustment;
								if (!(flags0xaa8Mask & flags0xaa8)) {
									field0x3e8->m_unk0x7ec = adjustment;
								}
							}
							else if (m_racers[racerIndex].FUN_0043a0a0() < bestProgress) {
								LegoFloat adjustment = g_unk0x004b09dc + m_unk0x0c;
								adjustment += 1.0f;
								Racer::Physics* field0x3e8 = &m_racers[racerIndex].m_unk0x3e8;
								LegoU32 flags0xaa8 = field0x3e8->m_flags0x6c0;
								field0x3e8->m_unk0x7e8 = adjustment;
								if (!(flags0xaa8Mask & flags0xaa8)) {
									field0x3e8->m_unk0x7ec = adjustment;
								}
							}
						}
					}

					result = m_racerCount;
					racerIndex++;
				} while (racerIndex < result);
			}
		}
	}
	else {
		result = delayMs - p_elapsedMs;
		m_updateDelayMs = result;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0043ae40
RaceState::RaceState()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0043aee0
RaceState::~RaceState()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0043af80
void RaceState::Reset()
{
	m_unk0x0f0.m_racers = NULL;
	m_unk0x0f0.m_unk0x058 = 0;
	m_unk0x0f0.m_racerCount = 0;
	m_unk0x0f0.m_unk0x05c = 0;

	LegoS32 i;
	for (i = 0; i < sizeOfArray(m_unk0x0f0.m_unk0x064); i++) {
		m_unk0x0f0.m_unk0x064[i] = 0;
		m_unk0x0f0.m_unk0x0a4[i].m_x = 0.0f;
		m_unk0x0f0.m_unk0x0a4[i].m_y = 0.0f;
		m_unk0x0f0.m_unk0x0a4[i].m_z = 0.0f;
		m_unk0x0f0.m_unk0x0ec[i].m_x = 0.0f;
		m_unk0x0f0.m_unk0x0ec[i].m_y = 0.0f;
		m_unk0x0f0.m_unk0x0ec[i].m_z = 0.0f;
		m_unk0x0f0.m_unk0x134[i].m_x = 0.0f;
		m_unk0x0f0.m_unk0x134[i].m_y = 0.0f;
		m_unk0x0f0.m_unk0x134[i].m_z = 0.0f;
		m_unk0x0f0.m_unk0x17c[i] = 0;
	}

	m_unk0x0f0.m_unk0x07c = NULL;
	m_unk0x0f0.m_unk0x080[0] = NULL;
	m_unk0x0f0.m_unk0x080[1] = NULL;
	m_unk0x0f0.m_unk0x080[2] = NULL;

	for (i = 0; i < sizeOfArray(m_unk0x0f0.m_unk0x08c); i++) {
		m_unk0x0f0.m_unk0x08c[i] = 0;
		m_unk0x0f0.m_unk0x094[i] = 0;
	}

	m_unk0x0f0.m_unk0x09c = 0;
	m_unk0x0f0.m_routeRecords = NULL;
	m_unk0x284.m_unk0x10 = 0;
	m_unk0x284.m_unk0x14 = 0;
	m_unk0x284.m_lapCount = 0;
}

// FUNCTION: LEGORACERS 0x0043b030
void RaceState::Destroy()
{
	m_unk0x284.Destroy();

	if (m_unk0x284.m_unk0x14) {
		m_unk0x0f0.m_golExport->DestroyMaterialList(m_unk0x284.m_unk0x14);
		m_unk0x284.m_unk0x14 = NULL;
	}

	if (m_unk0x284.m_unk0x10) {
		m_unk0x0f0.m_golExport->DestroyTextureList(m_unk0x284.m_unk0x10);
		m_unk0x284.m_unk0x10 = NULL;
	}

	LegoS32 i;
	for (i = 0; i < 2; i++) {
		if (m_unk0x0f0.m_unk0x08c[i]) {
			delete m_unk0x0f0.m_unk0x08c[i];
			m_unk0x0f0.m_unk0x08c[i] = NULL;
		}

		if (m_unk0x0f0.m_unk0x094[i]) {
			delete m_unk0x0f0.m_unk0x094[i];
			m_unk0x0f0.m_unk0x094[i] = NULL;
		}
	}

	GolNameTable* table = &m_unk0x0b4;
	table->Clear();

	table = &m_unk0x080;
	table->Clear();

	table = &m_unk0x000;
	table->Clear();

	if (m_unk0x0f0.m_unk0x07c) {
		m_unk0x0f0.m_unk0x05c->ReleaseSound(m_unk0x0f0.m_unk0x07c);
		m_unk0x0f0.m_unk0x07c = NULL;
	}

	LegoU32 racerIndex;
	for (racerIndex = 0; racerIndex < m_unk0x0f0.m_racerCount; racerIndex++) {
		if (m_unk0x0f0.m_unk0x064[racerIndex]) {
			m_unk0x0f0.m_unk0x064[racerIndex]->m_active = 0;
			m_unk0x0f0.m_unk0x064[racerIndex] = NULL;
		}
	}

	LegoEventQueue* queue = &m_unk0x0f0;
	queue->Destroy();

	if (m_unk0x0f0.m_racers) {
		for (racerIndex = 0; racerIndex < m_unk0x0f0.m_racerCount; racerIndex++) {
			(*(m_unk0x0f0.m_racers + racerIndex)).Destroy();
		}

		delete[] m_unk0x0f0.m_racers;

		m_unk0x0f0.m_racers = NULL;
	}

	Reset();
}

// FUNCTION: LEGORACERS 0x0043b190
void RaceState::FUN_0043b190(Field0x3b190Params0x04* p_unk0x04, Field0x3b190Params0x08* p_unk0x08, LegoBool32 p_binary)
{
	m_unk0x0f0.m_field0x010 = p_unk0x08->m_racerField0x010;
	m_unk0x0f0.m_unk0x05c = p_unk0x08->m_resourceMgr;
	m_unk0x0f0.m_unk0x060 = p_unk0x08->m_unk0x18;
	m_unk0x0f0.m_golExport = p_unk0x08->m_golExport;
	m_unk0x0f0.m_timeRaceManager = p_unk0x04->m_timeRaceManager;
	m_unk0x0f0.m_routeRecords = p_unk0x04->m_routeRecords;
	m_unk0x284.m_lapCount = p_unk0x04->m_lapCount;
	static_cast<LegoEventQueue*>(&m_unk0x0f0)->VTable0x08(100);

	m_unk0x0f0.m_unk0x04c = this;
	m_unk0x0f0.m_racerCount = p_unk0x04->m_racerCount;
	m_unk0x0f0.m_racers = new Racer[m_unk0x0f0.m_racerCount];
	if (m_unk0x0f0.m_racers == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x284.m_unk0x10 = m_unk0x0f0.m_golExport->CreateTextureList();
	m_unk0x284.m_unk0x14 = m_unk0x0f0.m_golExport->CreateMaterialList();
	m_unk0x284.m_unk0x10->VTable0x1c(p_unk0x08->m_renderer, m_unk0x0f0.m_racerCount);
	m_unk0x284.m_unk0x14->VTable0x1c(p_unk0x08->m_renderer, m_unk0x0f0.m_racerCount);

	DriverCosmeticTable::LoadParams driverParams;
	driverParams.m_golExport = p_unk0x08->m_golExport;
	driverParams.m_renderer = p_unk0x08->m_renderer;
	driverParams.m_entryCapacity = m_unk0x0f0.m_racerCount;
	driverParams.m_filename = g_unk0x004bef3c[0];
	driverParams.m_binary = p_binary;
	m_unk0x000.Load(&driverParams);

	ChampionDefinitionList::LoadParams championParams;
	championParams.m_golExport = p_unk0x08->m_golExport;
	championParams.m_renderer = p_unk0x08->m_renderer;
	championParams.m_entryCapacity = m_unk0x0f0.m_racerCount;
	championParams.m_fileName = g_unk0x004bef3c[1];
	championParams.m_binary = p_binary;
	m_unk0x080.FUN_0041d370(&championParams);

	ChassisModelTable::Params chassisParams;
	chassisParams.m_golExport = p_unk0x08->m_golExport;
	chassisParams.m_renderer = p_unk0x08->m_renderer;
	chassisParams.m_instantiateCount = m_unk0x0f0.m_racerCount;
	chassisParams.m_filename = g_unk0x004bef3c[2];
	chassisParams.m_binary = p_binary;
	m_unk0x0b4.FUN_0041db10(&chassisParams);

	for (LegoU32 i = 0; i < m_unk0x0f0.m_racerCount; i++) {
		p_unk0x08->m_unk0x34 = p_unk0x04->m_unk0x20[i];
		FUN_0043b480(p_unk0x04->m_unk0x04[i], p_unk0x08, i, p_unk0x04->m_unk0x3c);
	}

	m_unk0x0b4.FUN_0041dae0();
	m_unk0x080.ClearDefinitions();
	m_unk0x000.ClearEntries();
	m_unk0x284.m_unk0x10->LoadTextures();
	m_unk0x284.m_unk0x14->FUN_10026970();
	m_unk0x284.FUN_0043a450(m_unk0x0f0.m_racers, m_unk0x0f0.m_racerCount);
}

// STUB: LEGORACERS 0x0043b480
void RaceState::FUN_0043b480(
	LegoRacers::Context::PlayerSetupSlot* p_unk0x04,
	Field0x3b190Params0x08* p_unk0x08,
	LegoU32 p_unk0x0c,
	undefined4 p_unk0x10
)
{
	Racer::Field0x36df0Params racerParams;
	Racer::CarVisuals::InitParams initParams;
	::memset(&racerParams, 0, sizeof(racerParams));
	::memset(&initParams, 0, sizeof(initParams));

	ChampionDefinitionList::ChampionDefinition* championDefinition = NULL;
	ChassisModelTable::Item* chassisItem;
	if (p_unk0x04->m_driverName[0]) {
		DriverCosmeticTable::Entry* driverEntry =
			static_cast<DriverCosmeticTable::Entry*>(m_unk0x000.GetName(p_unk0x04->m_driverName));

		initParams.m_driverEntity = m_unk0x000.LoadEntry(p_unk0x04->m_driverName);
		championDefinition =
			static_cast<ChampionDefinitionList::ChampionDefinition*>(m_unk0x080.GetName(driverEntry->m_unk0x1a));
		initParams.m_bodyModel = m_unk0x080.FUN_0041d780(driverEntry->m_unk0x1a);
		chassisItem = static_cast<ChassisModelTable::Item*>(m_unk0x0b4.GetName(championDefinition->m_unk0x18));
		m_unk0x0b4.InstantiateModels(chassisItem, &initParams.m_carEntity, &initParams.m_unk0x04);

		racerParams.m_vehicle.m_unk0x084 = chassisItem->m_unk0x100;
		racerParams.m_vehicle.m_unk0x085 = chassisItem->m_unk0x101;
		racerParams.m_vehicle.m_unk0x086 = chassisItem->m_unk0x102;
		racerParams.m_unk0x6c[0] = driverEntry->m_unk0x24;
		racerParams.m_unk0x6c[1] = driverEntry->m_unk0x25;
		racerParams.m_unk0x6c[2] = driverEntry->m_unk0x26;
		racerParams.m_unk0x6c[3] = driverEntry->m_unk0x27;
		racerParams.m_unk0x6c[4] = driverEntry->m_unk0x28;
		racerParams.m_unk0x6c[5] = driverEntry->m_unk0x29;
		racerParams.m_unk0x74 = driverEntry->m_unk0x2a * 12 + 1100;

		switch (driverEntry->m_unk0x22) {
		case 1:
		case 2:
		case 3:
		case 4:
			racerParams.m_unk0x7c = driverEntry->m_unk0x22;
			break;
		default:
			racerParams.m_unk0x7c = 0;
			break;
		}

		racerParams.m_unk0x80 = driverEntry->m_unk0x23;
		racerParams.m_stringChars = m_unk0x000.GetStringBuffer(p_unk0x04->m_driverName);
	}
	else {
		LegoU32 customIndex = m_unk0x0f0.m_unk0x09c;
		m_unk0x0f0.m_unk0x08c[customIndex] = new GolModelEntity;
		if (m_unk0x0f0.m_unk0x08c[customIndex] == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_unk0x0f0.m_unk0x094[customIndex] = new GolAnimatedEntity;
		if (m_unk0x0f0.m_unk0x094[customIndex] == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		p_unk0x04->m_textures->LoadTextures();
		p_unk0x04->m_materials->FUN_10026970();
		initParams.m_bodyModel = m_unk0x0f0.m_unk0x08c[customIndex];
		initParams.m_bodyModel->VTable0x50(p_unk0x04->m_model, g_unk0x004b0a14);

		if (p_unk0x04->m_altModel == NULL) {
			LegoChar fallbackName[3];
			fallbackName[0] = 'b';
			fallbackName[1] = 'b';
			fallbackName[2] = '\0';
			m_unk0x000.GetName(fallbackName);
			initParams.m_driverEntity = m_unk0x000.LoadEntry(fallbackName);
		}
		else {
			p_unk0x04->m_altTextures->LoadTextures();
			p_unk0x04->m_altMaterials->FUN_10026970();
			initParams.m_driverEntity = m_unk0x0f0.m_unk0x094[customIndex];
			initParams.m_driverEntity
				->FUN_0040d550(p_unk0x04->m_altModel, m_unk0x000.m_rootNode, &m_unk0x000.m_modelParts, g_unk0x004b0a14);
		}

		chassisItem = static_cast<ChassisModelTable::Item*>(m_unk0x0b4.GetName(p_unk0x04->m_chassisName));
		m_unk0x0b4.InstantiateModels(chassisItem, &initParams.m_carEntity, &initParams.m_unk0x04);
		racerParams.m_vehicle.m_unk0x084 = chassisItem->m_unk0x100;
		racerParams.m_vehicle.m_unk0x085 = chassisItem->m_unk0x101;
		racerParams.m_vehicle.m_unk0x086 = chassisItem->m_unk0x102;

		for (LegoU32 i = 0; i < sizeOfArray(racerParams.m_unk0x6c); i++) {
			racerParams.m_unk0x6c[i] = 100;
		}

		racerParams.m_unk0x74 = p_unk0x0c * 100 + 1000;
		::strcpy(racerParams.m_displayName, p_unk0x04->m_playerName);
		m_unk0x0f0.m_unk0x09c = customIndex + 1;
	}

	initParams.m_driverMountOffset = chassisItem->m_unk0xc4;
	initParams.m_racer = &m_unk0x0f0.m_racers[p_unk0x0c];
	initParams.m_shadowWidth = chassisItem->m_unk0xdc.m_x;
	initParams.m_shadowLength = chassisItem->m_unk0xdc.m_y;
	initParams.m_frontSkidWidth = chassisItem->m_unk0xe4.m_x;
	initParams.m_rearSkidWidth = chassisItem->m_unk0xe4.m_y;
	::strncpy(initParams.m_materialName, "carshad", sizeof(initParams.m_materialName));
	initParams.m_materialName[sizeof(initParams.m_materialName) - 1] = static_cast<LegoChar>('0' + p_unk0x0c);

	for (LegoU32 i = 0; i < sizeOfArray(initParams.m_wheelOffsets); i++) {
		initParams.m_wheelOffsets[i] = chassisItem->m_unk0x58[i];
	}

	racerParams.m_vehicle.m_unk0x028 = chassisItem->m_unk0x88[1];
	racerParams.m_vehicle.m_unk0x038 = chassisItem->m_unk0x88[2].m_y;
	racerParams.m_vehicle.m_unk0x040 = chassisItem->m_unk0x88[3].m_x;
	racerParams.m_vehicle.m_unk0x044 = chassisItem->m_unk0x88[3].m_y;

	racerParams.m_unk0x72 = m_unk0x284.m_lapCount;
	racerParams.m_vehicle.m_unk0x060 = p_unk0x08->m_unk0x28;
	racerParams.m_vehicle.m_unk0x064 = p_unk0x08->m_unk0x2c;
	racerParams.m_vehicle.m_unk0x068 = p_unk0x08->m_unk0x0c;
	racerParams.m_unk0x78 = chassisItem->m_unk0xec;

	if (championDefinition) {
		racerParams.m_vehicle.m_unk0x04c.m_x = championDefinition->m_unk0x24;
		racerParams.m_vehicle.m_unk0x04c.m_y = championDefinition->m_unk0x28;
		racerParams.m_vehicle.m_unk0x04c.m_z = championDefinition->m_unk0x2c;
		racerParams.m_vehicle.m_unk0x058 = championDefinition->m_unk0x20;
		racerParams.m_vehicle.m_unk0x05c = 0.0f;
	}
	else {
		racerParams.m_vehicle.m_unk0x04c.m_x =
			p_unk0x04->m_unk0x18 * g_carBuildModelTextureCoordinateScale + chassisItem->m_unk0xb8.m_x;
		racerParams.m_vehicle.m_unk0x04c.m_y =
			p_unk0x04->m_unk0x1c * g_carBuildModelTextureCoordinateScale + chassisItem->m_unk0xb8.m_y;
		racerParams.m_vehicle.m_unk0x04c.m_z = chassisItem->m_unk0xb8.m_z;
		racerParams.m_vehicle.m_unk0x058 = chassisItem->m_unk0xd0 + p_unk0x04->m_unk0x14;
		racerParams.m_vehicle.m_unk0x05c = p_unk0x04->m_unk0x14;
	}

	m_unk0x0f0.m_unk0x17c[p_unk0x0c] = p_unk0x0c;
	if (m_unk0x0f0.m_timeRaceManager) {
		if (m_unk0x0f0.m_timeRaceManager->HasRecordRunLapTimes()) {
			m_unk0x0f0.m_unk0x17c[p_unk0x0c] = 2;
		}
		else {
			m_unk0x0f0.m_unk0x17c[p_unk0x0c] = 1;
		}
	}
	else if (p_unk0x10 && p_unk0x0c == 0) {
		m_unk0x0f0.m_unk0x17c[0] = 2;
	}

	LegoU32 placementIndex = m_unk0x0f0.m_unk0x17c[p_unk0x0c];
	initParams.m_carEntity->VTable0x08(m_unk0x0f0.m_unk0x0a4[placementIndex]);
	initParams.m_carEntity->VTable0x40(m_unk0x0f0.m_unk0x0ec[placementIndex], m_unk0x0f0.m_unk0x134[placementIndex]);

	m_unk0x0f0.m_racers[p_unk0x0c].FUN_00436df0(p_unk0x08, &initParams, &racerParams, this, p_unk0x0c);

	PurpleDune0x7c* shadowTexture = m_unk0x284.m_unk0x10->GetItem(p_unk0x0c);
	DuskwindBananaRelic0x24* shadowMaterial = m_unk0x284.m_unk0x14->GetItem(p_unk0x0c);
	shadowTexture->SetNameFromBuffer(chassisItem->m_unk0x50);
	shadowTexture->SetTextureFlags(GoldDune0x38::c_unk0x36Bit2 | GoldDune0x38::c_unk0x36Bit3);
	shadowMaterial->SetName(chassisItem->m_unk0x50);

	DuskWindBananaRelicParams shadowMaterialParams;
	::memset(&shadowMaterialParams, 0, sizeof(shadowMaterialParams));
	shadowMaterialParams.m_unk0x00 =
		DuskwindBananaRelic0x24::c_flag0x08Bit2 | DuskwindBananaRelic0x24::c_flag0x08Bit3 |
		DuskwindBananaRelic0x24::c_flag0x08Bit5 | DuskwindBananaRelic0x24::c_flag0x08Bit7 |
		DuskwindBananaRelic0x24::c_flag0x08Bit9 | DuskwindBananaRelic0x24::c_flag0x08Bit10 |
		DuskwindBananaRelic0x24::c_flag0x08Bit13 | DuskwindBananaRelic0x24::c_flag0x08Bit15 |
		DuskwindBananaRelic0x24::c_flag0x08Bit20 | DuskwindBananaRelic0x24::c_flag0x08Bit22;
	shadowMaterialParams.m_unk0x04 = shadowTexture;
	shadowMaterial->FUN_100257e0(p_unk0x08->m_renderer, shadowMaterialParams);

	Racer* racer = &m_unk0x0f0.m_racers[p_unk0x0c];
	racer->m_unk0xc70.m_unk0x050 = &m_unk0x2a0;

	LegoEventQueue::Descriptor descriptor;
	descriptor.m_unk0x00 = 3;
	descriptor.m_unk0x04 = 5;
	descriptor.m_unk0x08 = 0;
	descriptor.m_unk0x0c = 0;
	descriptor.m_data = &racer->m_unk0x3e8;
	descriptor.m_unk0x14 = 0;
	m_unk0x0f0.m_unk0x064[p_unk0x0c] = m_unk0x0f0.FUN_0042fb50(racer, &descriptor);
}

// FUNCTION: LEGORACERS 0x0043bc10
void RaceState::FUN_0043bc10(const LegoChar* p_name, LegoBool32 p_binary, LegoBool32 p_mirror)
{
	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".spb");
	}
	else {
		parser = new SpbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_name);
	parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
	LegoU32 count = parser->ReadBracketedCountAndLeftCurly();

	if (count > 0) {
		LegoU32 remaining = count;
		do {
			parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
			LegoU32 index = parser->ReadInteger();
			parser->ReadLeftCurly();

			GolFileParser::ParserTokenType token = parser->GetNextToken();
			while (token != GolFileParser::e_rightCurly) {
				switch (token) {
				case GolFileParser::e_unknown0x28:
					m_unk0x0f0.m_unk0x0a4[index].m_x = parser->ReadFloat();
					m_unk0x0f0.m_unk0x0a4[index].m_y = parser->ReadFloat();
					m_unk0x0f0.m_unk0x0a4[index].m_z = parser->ReadFloat();
					if (p_mirror) {
						m_unk0x0f0.m_unk0x0a4[index].m_y = -m_unk0x0f0.m_unk0x0a4[index].m_y;
					}
					break;
				case GolFileParser::e_unknown0x29:
					m_unk0x0f0.m_unk0x0ec[index].m_x = parser->ReadFloat();
					m_unk0x0f0.m_unk0x0ec[index].m_y = parser->ReadFloat();
					m_unk0x0f0.m_unk0x0ec[index].m_z = parser->ReadFloat();
					m_unk0x0f0.m_unk0x134[index].m_x = parser->ReadFloat();
					m_unk0x0f0.m_unk0x134[index].m_y = parser->ReadFloat();
					m_unk0x0f0.m_unk0x134[index].m_z = parser->ReadFloat();
					if (p_mirror) {
						m_unk0x0f0.m_unk0x0ec[index].m_y = -m_unk0x0f0.m_unk0x0ec[index].m_y;
						m_unk0x0f0.m_unk0x134[index].m_y = -m_unk0x0f0.m_unk0x134[index].m_y;
					}
					break;
				default:
					parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
					break;
				}

				token = parser->GetNextToken();
			}
		} while (--remaining);
	}

	parser->ReadRightCurly();
	parser->Dispose();
	if (parser != NULL) {
		delete parser;
	}
}

// FUNCTION: LEGORACERS 0x0043be60
void RaceState::FUN_0043be60(GolD3DRenderDevice* p_renderer, GolExport* p_golExport)
{
	for (LegoU32 i = 0; i < m_unk0x0f0.m_racerCount; i++) {
		m_unk0x0f0.m_racers[i].m_unk0x018.InitializeVisuals(p_renderer, p_golExport);
	}
}

// FUNCTION: LEGORACERS 0x0043beb0
void RaceState::RecordBestTimes(LegoRacers::Context* p_context)
{
	LegoU32 bestLapTime = c_invalidTime;
	LegoU32 bestRaceTime = c_invalidTime;
	LegoU32 bestRacerIndex = c_invalidTime;
	LegoU32 racerCount = m_unk0x0f0.m_racerCount;

	if (racerCount > 0) {
		LegoU32 racerIndex;

		racerIndex = 0;
		do {
			if (!p_context->m_playerSetupSlots[racerIndex].m_unk0x10) {
				Racer* racer = &m_unk0x0f0.m_racers[racerIndex];
				LegoU32 lapCount = m_unk0x284.m_lapCount;
				if (lapCount <= racer->m_lapsCompleted) {
					if (lapCount) {
						LegoU32 remaining = lapCount;
						LegoU32 raceTime = 0;
						LegoU32* lapTimes = racer->m_lapTimes;

						do {
							LegoU32 lapTime = *lapTimes;
							if (lapTime < bestLapTime) {
								bestLapTime = lapTime;
								bestRacerIndex = racerIndex;
							}
							raceTime += lapTime;
							lapTimes++;
						} while (--remaining);

						if (raceTime < bestRaceTime) {
							bestRaceTime = raceTime;
						}
					}
					else if (0 < bestRaceTime) {
						bestRaceTime = 0;
					}
				}
			}

			racerIndex++;
		} while (racerIndex < racerCount);
	}

	if (bestLapTime < c_invalidTime) {
		LegoU32* lapRecord = &p_context->m_bestLapTimes[p_context->m_currentRaceIndex];
		if (!*lapRecord || bestLapTime <= *lapRecord) {
			*lapRecord = bestLapTime;
			p_context->m_bestLapHolders[p_context->m_currentRaceIndex] = bestRacerIndex;
		}
	}

	if (bestRaceTime < c_invalidTime) {
		LegoU32* raceRecord = &p_context->m_bestRaceTimes[p_context->m_currentRaceIndex];
		if (!*raceRecord || bestRaceTime <= *raceRecord) {
			*raceRecord = bestRaceTime;
			p_context->m_bestRaceHolders[p_context->m_currentRaceIndex] = bestRacerIndex;
		}
	}
}

// FUNCTION: LEGORACERS 0x0043bff0
void RaceState::FUN_0043bff0(GolD3DRenderDevice* p_renderer)
{
	for (LegoU32 i = 0; i < m_unk0x0f0.m_racerCount; i++) {
		m_unk0x0f0.m_racers[i].m_unk0x018.DrawTransparent(p_renderer);
	}
}

// FUNCTION: LEGORACERS 0x0043c030
void RaceState::FUN_0043c030(LegoU32 p_elapsedMs)
{
	Racer* racer = m_unk0x0f0.m_racers;
	Racer* end = racer + m_unk0x0f0.m_racerCount;

	for (; racer < end; racer++) {
		if (racer->m_unk0xc70.m_unk0x014 & Racer::DriveController::c_flags0x014Bit7) {
			racer->m_unk0xc70.FUN_0041fd60(p_elapsedMs);
		}
		else {
			if (racer->m_controlMode != 2) {
				racer->m_unk0xc70.FUN_0041fc00(p_elapsedMs);
			}
			else if (racer->m_unk0xc70.m_unk0x014 & Racer::DriveController::c_flags0x014Bit6) {
				racer->m_unk0xc70.FUN_004203b0(p_elapsedMs);
			}
		}
	}

	for (racer = m_unk0x0f0.m_racers; racer < end; racer++) {
		racer->m_unk0x3e8.VTable0x04(p_elapsedMs);
	}

	for (racer = m_unk0x0f0.m_racers; racer < end; racer++) {
		if (racer->m_unk0xd04 & Racer::c_flagDrifting) {
			racer->UpdateDriftLean();
		}
	}

	Field0x0f0* queue = &m_unk0x0f0;
	queue->VTable0x10(p_elapsedMs);

	for (racer = m_unk0x0f0.m_racers; racer < end; racer++) {
		racer->UpdateCarAnimation(p_elapsedMs);
	}

	for (racer = m_unk0x0f0.m_racers; racer < end; racer++) {
		racer->UpdateEngineSound(p_elapsedMs);
		racer->UpdateSpatialSounds();
	}

	for (racer = m_unk0x0f0.m_racers; racer < end; racer++) {
		racer->UpdateTimers(p_elapsedMs);
	}

	FUN_0043c1b0();
	m_unk0x284.FUN_0043a480(p_elapsedMs);
}

// STUB: LEGORACERS 0x0043c1b0
void RaceState::FUN_0043c1b0()
{
	RacerProgressEntry* entries = g_racerProgressEntries;
	LegoU32 racerCount = m_unk0x0f0.m_racerCount;

	LegoU32 racerIndex;
	for (racerIndex = 0; racerIndex < racerCount; racerIndex++) {
		Racer* racer = &m_unk0x0f0.m_racers[racerIndex];
		entries[racerIndex].m_racer = racer;
		entries[racerIndex].m_unk0x08 = racer->FUN_0043a0a0();
	}

	LegoU32 sortIndex;
	for (sortIndex = 0; sortIndex + 1 < racerCount; sortIndex++) {
		LegoU32 minIndex = sortIndex;
		LegoFloat minProgress = entries[sortIndex].m_unk0x08;

		LegoU32 scanIndex;
		for (scanIndex = sortIndex + 1; scanIndex < racerCount; scanIndex++) {
			if (minProgress > entries[scanIndex].m_unk0x08) {
				minProgress = entries[scanIndex].m_unk0x08;
				minIndex = scanIndex;
			}
		}

		if (minIndex > sortIndex) {
			LegoFloat progress = entries[sortIndex].m_unk0x08;
			entries[sortIndex].m_unk0x08 = entries[minIndex].m_unk0x08;
			entries[minIndex].m_unk0x08 = progress;

			Racer* racer = entries[sortIndex].m_racer;
			entries[sortIndex].m_racer = entries[minIndex].m_racer;
			entries[minIndex].m_racer = racer;
		}
	}

	LegoU32 groupStart;
	for (groupStart = 0; groupStart + 1 < racerCount;) {
		LegoU32 groupEnd = groupStart + 1;
		while (groupEnd < racerCount && entries[groupStart].m_unk0x08 == entries[groupEnd].m_unk0x08) {
			groupEnd++;
		}

		RaceSessionField0x27f4::Entry* pathField = entries[groupStart].m_racer->m_unk0xcc4;
		if (groupEnd > groupStart + 1 && pathField) {
			LegoU32 tiedIndex;
			for (tiedIndex = groupStart; tiedIndex < groupEnd; tiedIndex++) {
				GolVec3 position;
				entries[tiedIndex].m_racer->m_unk0x018.m_carEntity->VTable0x04(&position);

				LegoFloat nearestPlaneDistance = FLT_MAX;
				LegoU32 planeIndex;
				for (planeIndex = 0; planeIndex < sizeOfArray(pathField->m_unk0x20.m_items); planeIndex++) {
					if (pathField->m_unk0x20.m_items[planeIndex] != 0xff) {
						RaceSessionField0x27f4::Entry* plane =
							m_unk0x0f0.m_field0x010->FUN_0041e940(pathField->m_unk0x20.m_items[planeIndex]);
						LegoFloat distance = plane->m_unk0x00.m_x * position.m_x + plane->m_unk0x00.m_y * position.m_y +
											 plane->m_unk0x00.m_z * position.m_z + plane->m_unk0x0c;
						if (distance < nearestPlaneDistance) {
							nearestPlaneDistance = distance;
						}
					}
				}

				entries[tiedIndex].m_unk0x04 = nearestPlaneDistance;
			}

			LegoU32 tiedSortIndex;
			for (tiedSortIndex = groupStart; tiedSortIndex + 1 < groupEnd; tiedSortIndex++) {
				LegoU32 maxIndex = tiedSortIndex;
				LegoFloat maxDistance = entries[tiedSortIndex].m_unk0x04;

				LegoU32 tiedScanIndex;
				for (tiedScanIndex = tiedSortIndex + 1; tiedScanIndex < groupEnd; tiedScanIndex++) {
					if (maxDistance < entries[tiedScanIndex].m_unk0x04) {
						maxDistance = entries[tiedScanIndex].m_unk0x04;
						maxIndex = tiedScanIndex;
					}
				}

				if (maxIndex > tiedSortIndex) {
					RacerProgressEntry progressEntry = entries[tiedSortIndex];
					entries[tiedSortIndex] = entries[maxIndex];
					entries[maxIndex] = progressEntry;
				}
			}
		}

		groupStart++;
	}

	LegoU32 rankIndex;
	for (rankIndex = 0; rankIndex < racerCount; rankIndex++) {
		if (!(entries[rankIndex].m_racer->m_unk0xd04 & Racer::c_flags0xd04Bit12)) {
			entries[rankIndex].m_racer->FUN_0043a210(racerCount - rankIndex);
		}
	}

	SpatialSoundInstance* sound = m_unk0x0f0.m_sound;
	Racer* trackedRacer = m_unk0x0f0.m_racer080;
	if (sound && trackedRacer) {
		GolVec3 trackedPosition;
		trackedRacer->m_unk0x018.m_carEntity->VTable0x04(&trackedPosition);

		Racer* nearestRacer = NULL;
		LegoFloat nearestDistanceSquared = FLT_MAX;
		LegoU32 nearestIndex;
		for (nearestIndex = 0; nearestIndex < racerCount; nearestIndex++) {
			Racer* racer = &m_unk0x0f0.m_racers[nearestIndex];
			if (racer != trackedRacer) {
				GolVec3 position;
				racer->m_unk0x018.m_carEntity->VTable0x04(&position);

				LegoFloat deltaX = trackedPosition.m_x - position.m_x;
				LegoFloat deltaY = trackedPosition.m_y - position.m_y;
				LegoFloat deltaZ = trackedPosition.m_z - position.m_z;
				LegoFloat distanceSquared = deltaZ * deltaZ + deltaY * deltaY + deltaX * deltaX;
				if (distanceSquared < nearestDistanceSquared) {
					nearestDistanceSquared = distanceSquared;
					nearestRacer = racer;
				}
			}
		}

		if (nearestDistanceSquared >= g_unk0x004b0a20 * g_unk0x004b0a20) {
			if (sound->IsPlaying()) {
				sound->Stop();
				return;
			}
		}
		else {
			if (!sound->IsPlaying()) {
				sound->Play(TRUE);
			}

			GolVec3 position;
			nearestRacer->m_unk0x018.m_carEntity->VTable0x04(&position);
			sound->SetPosition(position);

			GolVec3 velocity = nearestRacer->m_unk0x3e8.m_unk0x008;
			velocity.m_x *= 2.0f;
			velocity.m_y *= 2.0f;
			velocity.m_z *= 2.0f;
			sound->SetVelocity(velocity);

			LegoFloat frequencyScale = nearestRacer->m_unk0x3e8.m_unk0x604 / g_unk0x004b0a10;
			frequencyScale *= 1.0f - g_unk0x004b0a08 - g_unk0x004b0a0c;
			frequencyScale *= nearestRacer->m_unk0xd54;
			frequencyScale += g_unk0x004b0a08;

			if (frequencyScale < 0.0f) {
				frequencyScale = 0.0f;
			}
			else if (frequencyScale > 1.0f) {
				frequencyScale = 1.0f;
			}

			if (nearestRacer->m_airborneMs > Racer::c_boostSoundElapsedThreshold) {
				frequencyScale += g_unk0x004b02e0;
			}

			sound->SetFrequencyScale(frequencyScale);
		}
	}
}

// FUNCTION: LEGORACERS 0x0043c6a0
void RaceState::FUN_0043c6a0(GolCamera* p_camera)
{
	LegoU32 i = 0;
	if (i < m_unk0x0f0.m_racerCount) {
		do {
			m_unk0x0f0.m_racers[i].m_unk0x018.UpdateShadow(p_camera);
			i++;
		} while (i < m_unk0x0f0.m_racerCount);
	}
}

// FUNCTION: LEGORACERS 0x0043ccb0
void RaceState::FUN_0043ccb0()
{
	for (LegoU32 i = 0; i < m_unk0x0f0.m_racerCount; i++) {
		m_unk0x0f0.m_racers[i].FUN_00439340();
	}

	SpatialSoundInstance* sound = m_unk0x0f0.m_soundSource->AcquireSoundById(0x4f);
	m_unk0x0f0.m_sound = sound;
	if (sound) {
		LegoFloat maxDistance = g_unk0x004b0a20;
		sound->m_minDistanceSquared = g_unk0x004b0a18 * g_unk0x004b0a18;
		sound->m_maxDistanceSquared = maxDistance * maxDistance;
		m_unk0x0f0.m_sound->SetVolume(0.8f);
	}
}

// FUNCTION: LEGORACERS 0x0043cd30
void RaceState::FUN_0043cd30(GolRenderDevice* p_renderer, Racer* p_racer)
{
	for (LegoU32 i = 0; i < m_unk0x0f0.m_racerCount; i++) {
		if (p_racer != &m_unk0x0f0.m_racers[i] || p_racer->m_unk0xdb8 != 3 ||
			(p_racer->m_unk0xd04 & c_racerFlags0xd04Bit12) || !(p_racer->m_unk0xd04 & c_racerFlags0xd04Bit10)) {
			m_unk0x0f0.m_racers[i].m_unk0x018.m_entityGroup.VTable0x1c(*p_renderer);
		}
	}
}

// FUNCTION: LEGORACERS 0x0043d120
void RaceState::FUN_0043d120()
{
	RaceResourceManager::Resource* resource = m_unk0x0f0.m_unk0x07c;
	if (resource) {
		m_unk0x0f0.m_unk0x05c->ReleaseSound(resource);
		m_unk0x0f0.m_unk0x07c = NULL;
	}
}
