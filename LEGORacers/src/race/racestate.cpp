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
#include "race/raceeventtable.h"
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
DECOMP_SIZE_ASSERT(RaceState::Racer::SetupParams, 0x88)
DECOMP_SIZE_ASSERT(RaceState::Racer::CarVisuals, 0x3d0)
DECOMP_SIZE_ASSERT(RaceState::Racer::CarVisuals::InitParams, 0x68)
DECOMP_SIZE_ASSERT(RaceState::Racer::RigidBody, 0xd0)
DECOMP_SIZE_ASSERT(RaceState::Racer::BoxBody, 0xe4)
DECOMP_SIZE_ASSERT(RaceState::Racer::CarBody, 0x74c)
DECOMP_SIZE_ASSERT(RaceState::Racer::Physics, 0x888)
DECOMP_SIZE_ASSERT(RaceState::Racer::DriveController, 0x54)
DECOMP_SIZE_ASSERT(RaceState::Racer::SpatialSoundResource, 0x30)
DECOMP_SIZE_ASSERT(RaceState::RaceRoster, 0x194)
DECOMP_SIZE_ASSERT(RaceState::RaceSetup, 0x1c)

extern const LegoFloat g_ghostAnimationRateScale;
extern const LegoFloat g_ghostSampleFractionScale;
extern const LegoFloat g_sweepCannonRadiansToTableIndex;
extern const LegoFloat g_negativeRadiansToTableIndex;
extern const LegoFloat g_violetShoalTwo;
extern LegoU32 g_impostorFlags0;
extern LegoU32 g_impostorFlags1;
extern LegoFloat g_cosineTable[1024];

// GLOBAL: LEGORACERS 0x004b02e0
extern const LegoFloat g_unk0x004b02e0 = 0.2f;

// GLOBAL: LEGORACERS 0x004b0424
static const LegoFloat g_statMax = 100.0f;

// GLOBAL: LEGORACERS 0x004b0544
extern const LegoFloat g_unk0x004b0544 = 0.050000001f;

// GLOBAL: LEGORACERS 0x004b094c
extern const LegoFloat g_enginePitchFloor = 0.40000001f;

// GLOBAL: LEGORACERS 0x004b0950
extern const LegoFloat g_enginePitchDriveBand = 0.1f;

// GLOBAL: LEGORACERS 0x004b0954
extern const LegoFloat g_enginePitchSpeedRange = 0.17f;

// GLOBAL: LEGORACERS 0x004b0958
extern const LegoFloat g_shieldSoundMinDistance = 30.0f;

// GLOBAL: LEGORACERS 0x004b095c
extern const LegoFloat g_shieldSoundMaxDistance = 300.0f;

// GLOBAL: LEGORACERS 0x004b0960
extern const LegoFloat g_shieldHitSoundMinDistance = 200.0f;

// GLOBAL: LEGORACERS 0x004b0964
extern const LegoFloat g_shieldHitSoundMaxDistance = 600.0f;

// GLOBAL: LEGORACERS 0x004b0970
extern const LegoFloat g_collisionRestitution = 0.75f;

// GLOBAL: LEGORACERS 0x004b0988
extern const LegoFloat g_engineDriveMinSpeed = 0.015f;

// GLOBAL: LEGORACERS 0x004b098c
extern const LegoFloat g_engineVolumeNormal = 0.69999999f;

// GLOBAL: LEGORACERS 0x004b0990
extern const LegoFloat g_engineVolumeFinished = 0.5f;

// GLOBAL: LEGORACERS 0x004b0994
extern const LegoFloat g_engineFadeVolumeScale = 2.2439947f;

// GLOBAL: LEGORACERS 0x004b0998
extern const LegoFloat g_engineVolumeRampScale = 0.059999999f;

// GLOBAL: LEGORACERS 0x004b099c
extern const LegoFloat g_engineVolumeRampRate = 0.030000029f;

// GLOBAL: LEGORACERS 0x004b09a0
extern const LegoFloat g_brakeSoundMinSpeed = 0.0099999998f;

// GLOBAL: LEGORACERS 0x004b09a4
extern const LegoFloat g_brakePitchScale = 1.0f;

// GLOBAL: LEGORACERS 0x004b0974
extern const LegoFloat g_aiRedTargetMinDistanceSquared = 100.0f;

// GLOBAL: LEGORACERS 0x004b0978
extern const LegoFloat g_aiRedTargetMaxDistanceSquared = 62500.0f;

// GLOBAL: LEGORACERS 0x004b097c
extern const LegoFloat g_aiRedTargetConeCosine = 0.95999998f;

// GLOBAL: LEGORACERS 0x004b0980
extern const LegoFloat g_shieldShoveConeCosine = 0.69999999f;

// GLOBAL: LEGORACERS 0x004b0984
extern const LegoFloat g_statChanceBase = 0.2f;

// GLOBAL: LEGORACERS 0x004b09a8
extern const LegoFloat g_bodyPointZ = 3.5f;

// GLOBAL: LEGORACERS 0x004b09ac
static const LegoFloat g_statChanceStep = 0.0111111114f;

// GLOBAL: LEGORACERS 0x004b09b8
extern const LegoFloat g_aiAggressionRange = 30.0f;

// GLOBAL: LEGORACERS 0x004b09bc
extern const LegoFloat g_aiAggressionScale = 0.001953125f;

// GLOBAL: LEGORACERS 0x004b09c4
extern const LegoFloat g_carAnimationMaxSpeed = 9.9999997e-05f;

// GLOBAL: LEGORACERS 0x004b09c8
extern const LegoFloat g_carAnimationMinSpeed = -9.9999997e-05f;

// GLOBAL: LEGORACERS 0x004b09d0
extern const LegoFloat g_engineIdleRampScale = 1.5f;

// GLOBAL: LEGORACERS 0x004b09d4
extern const LegoFloat g_shieldShoveStrength = 200.0f;

// GLOBAL: LEGORACERS 0x004b09dc
extern const LegoFloat g_rubberBandScale = 0.050000001f;

// GLOBAL: LEGORACERS 0x004b0a08
extern const LegoFloat g_proximityPitchFloor = 0.40000001f;

// GLOBAL: LEGORACERS 0x004b0a0c
extern const LegoFloat g_proximityPitchBand = 0.1f;

// GLOBAL: LEGORACERS 0x004b0a10
extern const LegoFloat g_proximityPitchSpeedRange = 0.17f;

// GLOBAL: LEGORACERS 0x004b0a14
extern const LegoFloat g_carModelScale = 250000.0f;

// GLOBAL: LEGORACERS 0x004b0a18
extern const LegoFloat g_proximitySoundMinDistance = 30.0f;

// GLOBAL: LEGORACERS 0x004b0a1c
extern const LegoFloat g_unk0x004b0a1c = 2.0f;

// GLOBAL: LEGORACERS 0x004b0a20
extern const LegoFloat g_proximitySoundMaxDistance = 200.0f;

// GLOBAL: LEGORACERS 0x004b0ac0
extern const LegoFloat g_hiddenModelDistance = -1.0f;

// GLOBAL: LEGORACERS 0x004b0af0
extern const LegoFloat g_unk0x004b0af0 = 15.0f;

// GLOBAL: LEGORACERS 0x004b0af4
extern const LegoFloat g_shadowProbeHeight = 6.0f;

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
extern const LegoFloat g_shadowFadeNearSquared = 2500.0f;

// GLOBAL: LEGORACERS 0x004b0b3c
extern const LegoFloat g_shadowFadeFarSquared = 10000.0f;

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
LegoFloat g_statChanceScale = ((1.0f - g_statChanceBase) * g_statMax) * g_statChanceStep;

// GLOBAL: LEGORACERS 0x004c67a8
LegoFloat g_proximitySoundMaxDistanceSquared = g_proximitySoundMaxDistance * g_proximitySoundMaxDistance;

// GLOBAL: LEGORACERS 0x004c67ac
undefined4 g_unk0x004c67ac;

// GLOBAL: LEGORACERS 0x004c67b0
RaceState::RacerProgressEntry RaceState::g_racerProgressEntries[RaceState::c_racerProgressEntryCount];

// GLOBAL: LEGORACERS 0x004bef3c
const LegoChar* g_racerDatabaseNames[3] = {"drivers", "champs", "chassis"};

// GLOBAL: LEGORACERS 0x004bef70
LegoU32 g_raceLapCount = 3;

// GLOBAL: LEGORACERS 0x004c6b34
LegoFloat g_cursePhaseScale = g_twoPi * g_pathMinSegmentLengthSquared;

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

	if (m_brakeSound) {
		m_soundSource->ReleaseSound(m_brakeSoundResource);
		m_brakeSound = NULL;
	}

	if (m_curseSound) {
		m_soundSource->ReleaseSound(m_curseSound);
		m_curseSound = NULL;
	}

	m_displayName.Reset();
	m_visuals.Destroy();
	m_physics.Destroy();
	m_driveController.Destroy();
	Reset();
}

// FUNCTION: LEGORACERS 0x00436bd0
void RaceState::Racer::Reset()
{
	m_soundSource = NULL;
	m_currentZone = 0;
	m_previousZone = 2;
	m_zoneBeforePrevious = 1;
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
	m_flags = 0;
	m_controlMode = 2;
	m_aiPowerupCheckIntervalMs = 150;
	m_unk0xd38 = 0;
	m_tauntCooldownMs = 0;
	m_reactionCooldownMs = 0;
	m_scrapeSoundCooldownMs = 0;
	m_airborneMs = 0;
	m_voiceBank = 1000;
	m_unk0xd3c = 0;
	m_enginePitchScale = 1.0f;
	m_turboLevel = 0;
	m_shieldLevel = 0;
	m_shoveForceSlot = 0;
	m_turboSoundL0 = NULL;
	m_turboSoundL1 = NULL;
	m_turboSoundL2 = NULL;
	m_ghostSound = NULL;
	m_engineIdleSound = NULL;
	m_engineDriveSound = NULL;
	m_engineFastSound = NULL;
	m_brakeSound = NULL;
	m_curseSound = NULL;
	m_activeEngineSound = 0;
	m_engineIdleVolume = 0;
	m_engineDriveVolume = 0;
	m_engineFastVolume = 0;
	m_shieldHitCooldownMs = 0;
	m_curseTimerMs = 0;
	m_timeBehindDisplayMs = 0;
	m_timeBehind = 0;

	LegoU8 invalidIndex = 0xff;
	m_facingForwardMs = 0;
	m_lookTargetPosition.m_x = 0;
	m_aiRedUseChance = invalidIndex;
	m_aiYellowUseChance = invalidIndex;
	m_aiGreenUseChance = invalidIndex;
	m_aiBlueUseChance = invalidIndex;
	m_driverStat4 = invalidIndex;
	m_driverStat5 = invalidIndex;
	m_lookTargetPosition.m_y = 0;

	DroppableBrick* field0xd5c = NULL;
	m_lookTargetPosition.m_z = 0;
	m_aiAggression = 0;
	m_actionSource.m_x = 0;
	m_actionSource.m_y = 0;
	m_actionSource.m_z = 0;
	m_actionSource.m_velocity.m_x = 0;
	m_actionSource.m_velocity.m_y = 0;
	m_actionSource.m_velocity.m_z = 0;
	m_actionSource.m_forward.m_x = 0;
	m_actionSource.m_forward.m_y = 0;
	m_actionSource.m_forward.m_z = 0;
	m_checkpoint = 0;
	m_checkpointForward = 1;
	m_checkpointGraph = 0;
	m_trail = NULL;
	m_checkpointCount = 0xffffffff;
	m_unk0xdb0 = 0;
	m_whiteBrickCount = 0;
	m_whiteBricks[0] = field0xd5c;
	m_whiteBricks[1] = field0xd5c;
	m_whiteBricks[2] = field0xd5c;
	m_cameraController = NULL;
	m_cameraViewIndex = 0;
	m_forceFeedback = 0;
	m_displayNameBuffer = 0;
	m_aiChargeColor = 0;
	m_aiChargeTarget = 0;
	m_lapCount = 0;
	m_speedRampTimerMs = 0;
}

// FUNCTION: LEGORACERS 0x00436df0
void RaceState::Racer::Initialize(
	RaceState::RacerContext* p_context,
	CarVisuals::InitParams* p_field0x018Params,
	SetupParams* p_params,
	RaceState* p_raceState,
	LegoU32 p_racerIndex
)
{
	if (m_raceState) {
		Destroy();
	}

	m_materialIndex = p_racerIndex;
	m_routeRecord = p_context->m_routeRecord;
	m_soundSource = p_context->m_soundSource;
	m_powerupManager = p_context->m_powerupManager;
	m_checkpointGraph = p_context->m_checkpointGraph;
	m_raceState = p_raceState;
	m_lapTimes[5] = p_racerIndex + 1;
	m_enginePitchScale = p_params->m_enginePitchScale;
	m_aiChargeColor = p_params->m_aiChargeColor;
	m_aiChargeTarget = p_params->m_aiChargeTarget;
	m_lapCount = p_params->m_lapCount;

	if (p_params->m_displayNameWide) {
		m_displayName.CopyFromBufSelection(p_params->m_displayNameWide, 0);
	}
	else {
		GolString::CopyStringToBuf16(p_params->m_displayName, &m_displayNameBuffer);
		m_displayName.CopyFromBufSelection(&m_displayNameBuffer, 0);
	}

	LegoU32 soundBase = p_params->m_voiceBank;
	m_voiceBank = soundBase;
	if (soundBase == 1000) {
		m_tauntSoundId = 26;
	}
	else if (soundBase == 1100) {
		m_tauntSoundId = 28;
	}
	else if (soundBase == 1112) {
		m_tauntSoundId = 27;
	}
	else if (soundBase == 1124) {
		m_tauntSoundId = 29;
	}
	else if (soundBase == 1136) {
		m_tauntSoundId = 30;
	}
	else if (soundBase == 1148 || soundBase == 1160) {
		m_tauntSoundId = 31;
	}

	LegoU32 colorValue = p_params->m_driverStats[0];
	LegoFloat colorScale = static_cast<LegoFloat>(colorValue);
	colorScale *= g_statChanceScale;
	colorScale *= g_carBuildPreviewMouseScale;
	colorScale += g_statChanceBase;
	if (colorScale > 1.0f) {
		colorScale = 1.0f;
	}
	m_aiRedUseChance = static_cast<LegoU8>(colorScale * 255.0f);

	colorValue = p_params->m_driverStats[1];
	colorScale = static_cast<LegoFloat>(colorValue);
	colorScale *= g_statChanceScale;
	colorScale *= g_carBuildPreviewMouseScale;
	colorScale += g_statChanceBase;
	if (colorScale > 1.0f) {
		colorScale = 1.0f;
	}
	m_aiYellowUseChance = static_cast<LegoU8>(colorScale * 255.0f);

	colorValue = p_params->m_driverStats[2];
	colorScale = static_cast<LegoFloat>(colorValue);
	colorScale *= g_statChanceScale;
	colorScale *= g_carBuildPreviewMouseScale;
	colorScale += g_statChanceBase;
	if (colorScale > 1.0f) {
		colorScale = 1.0f;
	}
	m_aiGreenUseChance = static_cast<LegoU8>(colorScale * 255.0f);

	colorValue = p_params->m_driverStats[3];
	colorScale = static_cast<LegoFloat>(colorValue);
	colorScale *= g_statChanceScale;
	colorScale *= g_carBuildPreviewMouseScale;
	colorScale += g_statChanceBase;
	if (colorScale > 1.0f) {
		colorScale = 1.0f;
	}
	m_aiBlueUseChance = static_cast<LegoU8>(colorScale * 255.0f);

	colorValue = p_params->m_driverStats[4];
	colorScale = static_cast<LegoFloat>(colorValue);
	colorScale *= g_statChanceScale;
	colorScale *= g_carBuildPreviewMouseScale;
	colorScale += g_statChanceBase;
	if (colorScale > 1.0f) {
		colorScale = 1.0f;
	}
	m_driverStat4 = static_cast<LegoU8>(colorScale * 255.0f);

	colorValue = p_params->m_driverStats[5];
	colorScale = static_cast<LegoFloat>(colorValue);
	colorScale *= g_statChanceScale;
	colorScale *= g_carBuildPreviewMouseScale;
	colorScale += g_statChanceBase;
	if (colorScale > 1.0f) {
		colorScale = 1.0f;
	}
	m_driverStat5 = static_cast<LegoU8>(colorScale * 255.0f);

	LegoS32 unk0xd22 = m_aiBlueUseChance;
	unk0xd22 = m_aiYellowUseChance - unk0xd22;
	unk0xd22 -= m_aiGreenUseChance;
	unk0xd22 += m_aiRedUseChance;
	if (unk0xd22 < 0) {
		m_aiAggression = 0;
	}
	else {
		LegoFloat d22Scale = static_cast<LegoFloat>(unk0xd22);
		d22Scale *= g_aiAggressionScale;
		d22Scale *= g_aiAggressionRange;
		m_aiAggression = static_cast<LegoU8>(d22Scale);
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
	if (p_context->m_cheatFlags & 1) {
		m_flags |= c_flagCheatNslwj;
	}
	if (p_context->m_cheatFlags & 0x40) {
		m_flags |= c_flagCheatRedOnly;
	}
	if (p_context->m_cheatFlags & 0x80) {
		m_flags |= c_flagCheatMaxPowerups;
	}
	if (p_context->m_cheatFlags & state) {
		m_flags |= c_flagCheatFlySkyHigh;
	}

	m_visuals.Initialize(p_field0x018Params, p_context);
	InitializePhysics(p_context, p_params);
	ResetRaceProgress();
}

// FUNCTION: LEGORACERS 0x004371c0
void RaceState::Racer::InitializePhysics(RacerContext* p_context, SetupParams* p_params)
{
	RaceEventTable* eventTable;
	void* unk0x2c;
	GolBoundedEntity* unk0x0c;
	GolBoundedEntity* unk0x10;
	if (p_context) {
		eventTable = p_context->m_eventTable;
		unk0x2c = p_context->m_unk0x2c;
		unk0x0c = p_context->m_trackWorld;
		unk0x10 = p_context->m_triggerWorld;
	}
	else {
		eventTable = m_physics.m_eventTable;
		unk0x2c = m_physics.m_unk0x6f8;
		unk0x0c = m_physics.m_collisionWorlds[0];
		unk0x10 = m_physics.m_triggerCollidable;
	}

	GolVec3 position;
	GolVec3 vector;
	LegoFloat deltaX;
	LegoFloat deltaY;
	LegoFloat unk0x58;
	LegoU32 unk0x84;
	LegoU32 unk0x86;
	LegoU32 unk0x85;
	if (p_params) {
		deltaY = p_params->m_rearWheelY1 - p_params->m_rearWheelY0;
		unk0x58 = p_params->m_mass;
		memcpy(&position, &p_params->m_centerOfMass, sizeof(position));

		deltaX = p_params->m_anchorWheelPosition.m_x - p_params->m_rearWheelX;
		unk0x86 = p_params->m_topSpeedStat;
		LegoFloat valueFloat = p_params->m_weight;
		unk0x85 = p_params->m_accelerationStat;
		memcpy(&vector, &p_params->m_anchorWheelPosition, sizeof(vector));
		valueFloat *= g_unk0x004b0544;

		LegoU32 value = static_cast<LegoU32>(valueFloat);
		unk0x84 = p_params->m_handlingStat + value;
		if (unk0x84 > 100) {
			unk0x84 = 100;
		}

		unk0x86 += value;
		if (unk0x86 > 100) {
			unk0x86 = 100;
		}

		if (value > p_params->m_accelerationStat) {
			unk0x85 = 0;
		}
		else {
			unk0x85 = p_params->m_accelerationStat - value;
		}
	}
	else {
		unk0x58 = m_physics.m_mass;
		unk0x84 = m_physics.m_handlingStat;
		memcpy(&position, &m_physics.m_centerOfMassLocal, sizeof(position));
		unk0x86 = m_physics.m_topSpeedStat;
		memcpy(&vector, &m_physics.m_anchorWheelOffset, sizeof(vector));
		deltaY = m_physics.m_trackWidth;
		deltaX = m_physics.m_wheelbase;
		unk0x85 = m_physics.m_accelerationStat;
	}

	Physics* field0x3e8 = &m_physics;
	field0x3e8->Initialize(
		this,
		eventTable,
		unk0x2c,
		m_visuals.m_carEntity,
		unk0x0c,
		unk0x10,
		m_soundSource,
		unk0x58,
		8.0f,
		5.0f,
		6.2f
	);
	m_physics.m_soundsEnabled = 0;
	m_physics.m_racer = this;

	if (m_flags & c_flagCheatNslwj) {
		field0x3e8->m_flags |= Physics::c_flagIgnoreSurfaces;
	}

	field0x3e8->SetHandlingStat(unk0x84);
	field0x3e8->SetAccelerationStat(unk0x85);
	field0x3e8->SetTopSpeedStat(unk0x86);

	LegoFloat halfHeight = m_visuals.m_shadowWidth;
	halfHeight *= 0.5f;
	LegoFloat halfWidth = m_visuals.m_shadowLength;
	halfWidth *= 0.5f;
	field0x3e8->SetCenterOfMass(&position);
	field0x3e8->SetWheelGeometry(&vector, deltaY, deltaX);

	GolVec3 corner;
	corner.m_x = halfWidth;
	corner.m_y = -halfHeight;
	corner.m_z = g_bodyPointZ;
	field0x3e8->SetBodyPoint(0, &corner);

	corner.m_x = halfWidth;
	corner.m_y = halfHeight;
	corner.m_z = g_bodyPointZ;
	field0x3e8->SetBodyPoint(1, &corner);

	corner.m_x = -halfWidth;
	corner.m_y = -halfHeight;
	corner.m_z = g_bodyPointZ;
	field0x3e8->SetBodyPoint(2, &corner);

	corner.m_x = -halfWidth;
	corner.m_y = halfHeight;
	corner.m_z = g_bodyPointZ;
	field0x3e8->SetBodyPoint(3, &corner);

	m_driveController.Initialize(field0x3e8);
}

// FUNCTION: LEGORACERS 0x004374c0
void RaceState::Racer::ResetRaceProgress()
{
	LegoU32 flags = m_flags;
	flags &= ~(c_flagFinished | c_flagFacingForwardPending | c_flagFacingForward);
	flags |= c_flagPreStart;
	m_flags = flags;

	if (m_routeRecord) {
		m_physics.AttachRoute(m_routeRecord);
		m_physics.m_routePaused = 1;
	}

	LegoU32 invalidValue = 0xffffffff;
	m_checkpoint = 0;
	m_currentZone = 0;
	m_lapsCompleted = 0;
	m_facingForwardMs = 0;
	m_checkpointForward = 1;
	m_previousZone = 2;
	m_zoneBeforePrevious = 1;
	m_lapTransitionCount = invalidValue;
	m_checkpointCount = invalidValue;
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
	LegoFloat value = m_physics.m_forwardSpeed;
	CarVisuals* field;

	if (value > g_carAnimationMinSpeed && value < g_carAnimationMaxSpeed) {
		value = 0.0f;
	}
	else if (value < 0.0f) {
		field = &m_visuals;
		field->PlayReverseAnimation();
		value = -value;
		goto setSpeed;
	}

	field = &m_visuals;
	field->PlayForwardAnimation();

setSpeed:
	GolAnimatedEntity* entity = field->m_carEntity;
	LegoFloat speed = value * g_ghostAnimationRateScale;
	entity->SetUnk0xb8(speed);

	if (field->m_secondaryEntity) {
		field->m_secondaryEntity->SetUnk0xb8(speed);
	}

	field->Update(p_elapsedMs);
}

// FUNCTION: LEGORACERS 0x004377f0
void RaceState::Racer::UpdateTimers(LegoU32 p_elapsedMs)
{
	if (m_flags & c_flagPreStart) {
		return;
	}

	LegoU32 lap = m_lapsCompleted;
	if (lap < m_lapCount) {
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

	if ((m_physics.m_flags & Physics::c_flagSpinOut) && !m_physics.m_routeMode) {
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

	if (!m_physics.m_contactCount) {
		m_airborneMs += p_elapsedMs;
	}
	else {
		m_airborneMs = 0;
	}

	countdown = m_shieldHitCooldownMs;
	if (p_elapsedMs > countdown) {
		m_shieldHitCooldownMs = 0;
	}
	else {
		m_shieldHitCooldownMs = countdown - p_elapsedMs;
	}

	countdown = m_curseTimerMs;
	if (p_elapsedMs > countdown) {
		if (m_flags & c_flagCursed) {
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
	if (p_elapsedMs < countdown && (m_flags & c_flagSpeedRamping)) {
		countdown -= p_elapsedMs;
		m_speedRampTimerMs = countdown;
		m_physics.m_speedRampScale =
			countdown > 500 ? static_cast<LegoFloat>(static_cast<LegoS32>(countdown - 500)) * g_ghostSampleFractionScale
							: 0.0f;
	}
	else {
		m_speedRampTimerMs = 0;
		m_physics.m_speedRampScale = 1.0f;
	}

	m_flags &= ~c_flagSpeedRamping;
	m_visuals.m_carEntity->VTable0x04(&m_actionSource);
	m_visuals.m_carEntity->GetOrientationRow0(&m_actionSource.m_forward);
	GolVec3& velocity = m_actionSource.m_velocity;
	velocity = m_physics.m_velocity;

	if (!m_tauntCooldownMs && m_controlMode == 2) {
		if (m_raceState
				->FindNearestRacerInCone(&m_actionSource, &m_actionSource.m_forward, 0.0f, 169.0f, 0.30000001f)) {
			PlayTaunt();
			g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
			m_tauntCooldownMs = g_randomTable[g_randomTableIndex] * 8 + 2000;
		}
		else {
			m_tauntCooldownMs = 2000;
		}
	}

	if (!m_controlMode) {
		UpdateFacing(p_elapsedMs);
		UpdateLookTarget(p_elapsedMs);
	}
	else {
		m_facingForwardMs = 0;
		m_flags &= ~(c_flagFacingForwardPending | c_flagFacingForward);
	}

	if (m_physics.m_wallContact) {
		if (m_forceFeedback) {
			m_forceFeedback->FUN_00422100();
		}

		if (!m_scrapeSoundCooldownMs) {
			SoundVector position;
			m_visuals.m_carEntity->VTable0x04(&position);

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

	LegoU32 flags = m_flags;
	if ((flags & c_flagCheatFlySkyHigh) && !(flags & c_flagHalted)) {
		m_powerupManager->UseGreenPowerup(this, 2);
	}
}

// FUNCTION: LEGORACERS 0x00437b50
void RaceState::Racer::UpdateDriftLean()
{
	GolVec3 direction;

	if (!(m_driveController.m_flags & DriveController::c_flagSliding)) {
		EndDrift();
		return;
	}

	direction = m_physics.m_facingDirection;

	LegoFloat value = 1.0f - (m_physics.m_carEntity->GetOrientation().m_m[0][0] * direction.m_x +
							  m_physics.m_carEntity->GetOrientation().m_m[0][1] * direction.m_y +
							  m_physics.m_carEntity->GetOrientation().m_m[0][2] * direction.m_z);

	if (m_physics.m_turnRadius < 0.0f) {
		value = -value;
	}

	m_visuals.m_rollLean += value * 0.059999999f;
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
			LegoU32 flags = m_flags;
			if ((flags & c_flagTurbo) && i == m_turboLevel && i < 3) {
				if (!resource->VTable0x0c()) {
					resource->VTable0x04(1);
				}

				GolVec3 position;
				m_visuals.m_carEntity->VTable0x04(&position);
				resource->m_position = position;
				resource->m_velocity = m_physics.m_velocity;
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
		m_visuals.m_curseEntity.VTable0x04(&position);
		m_curseSound->m_position = position;
	}
}

// FUNCTION: LEGORACERS 0x00437d40
void RaceState::Racer::UpdateEngineSound(LegoU32 p_elapsedMs)
{
	if (!(m_flags & c_flagEngineSounds) || !m_engineIdleSound) {
		return;
	}

	SoundVector position;
	m_visuals.m_carEntity->VTable0x04(&position);

	GolVec3 velocity = m_physics.m_velocity;
	LegoFloat frequencyScale;

	if (m_engineIdleSound && m_engineDriveSound && m_engineFastSound) {
		if (m_physics.m_thrust == 0.0f && !(m_driveController.m_flags & DriveController::c_flagTurbo)) {
			if (m_physics.m_speed > g_engineDriveMinSpeed) {
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

		LegoFloat elapsedStep = static_cast<LegoFloat>(p_elapsedMs) * g_engineVolumeRampRate;
		elapsedStep *= g_engineVolumeRampScale;
		LegoFloat targetVolume = (m_flags & c_flagFinished) ? g_engineVolumeFinished : g_engineVolumeNormal;

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
				increment *= g_engineIdleRampScale;
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
			volume *= g_engineFadeVolumeScale;
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
			volume *= g_engineFadeVolumeScale;
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
			volume *= g_engineFadeVolumeScale;
			volume *= g_negativeRadiansToTableIndex;
			LegoS32 index = (c_volumeTableBase - static_cast<LegoS32>(volume)) & c_volumeTableMask;
			volume = g_cosineTable[index];
			volume *= targetVolume;
			m_engineFastSound->SetVolume(volume);
		}

		frequencyScale = m_enginePitchScale;
		if (frequencyScale < 0.0f) {
			frequencyScale = 0.0f;
		}
		else if (frequencyScale > 1.0f) {
			frequencyScale = 1.0f;
		}

		m_engineIdleSound->SetPosition(position);
		m_engineIdleSound->SetVelocity(velocity);
		m_engineIdleSound->SetFrequencyScale(frequencyScale);

		frequencyScale = m_physics.m_speed / g_enginePitchSpeedRange;
		LegoBool32 boostSoundElapsed = m_airborneMs > c_boostSoundElapsedThreshold;
		frequencyScale *= 1.0f - g_enginePitchFloor - g_enginePitchDriveBand;
		frequencyScale *= m_enginePitchScale;
		frequencyScale += g_enginePitchFloor;
		if (boostSoundElapsed) {
			frequencyScale += g_enginePitchDriveBand;
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

		frequencyScale = m_physics.m_speed / g_enginePitchSpeedRange;
		frequencyScale *= 1.0f - g_enginePitchFloor;
		frequencyScale *= m_enginePitchScale;
		frequencyScale += g_enginePitchFloor;
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

	if (m_brakeSound) {
		if (m_physics.m_forwardSpeed >= g_brakeSoundMinSpeed && m_physics.m_thrust < 0.0f) {
			m_brakeSound->SetPosition(position);
			m_brakeSound->SetVelocity(velocity);
			frequencyScale = m_physics.m_speed;
			frequencyScale = g_enginePitchSpeedRange - frequencyScale;
			frequencyScale *= g_brakePitchScale;
			frequencyScale = 1.0f - frequencyScale;
			m_brakeSound->SetFrequencyScale(frequencyScale);
			return;
		}

		m_soundSource->ReleaseSound(m_brakeSoundResource);
		m_brakeSound = NULL;
		return;
	}

	if (m_physics.m_forwardSpeed > g_brakeSoundMinSpeed && m_physics.m_thrust < 0.0f) {
		m_soundSource
			->PlaySpatialSoundById(2, &position, g_shieldSoundMinDistance, g_shieldSoundMaxDistance, 1.0f, 1.0f);
		m_brakeSound = m_soundSource->AcquireSoundById(3);

		if (m_brakeSound) {
			m_brakeSound->Play(TRUE);
			LegoFloat maxDistance = g_shieldSoundMaxDistance;
			LegoFloat minDistance = g_shieldSoundMinDistance;
			m_brakeSound->SetDistanceRangeWithMinSquared(minDistance * minDistance, maxDistance);
			m_brakeSound->SetPosition(position);
			m_brakeSound->SetVelocity(velocity);
			frequencyScale = m_physics.m_speed;
			frequencyScale = g_enginePitchSpeedRange - frequencyScale;
			frequencyScale *= g_brakePitchScale;
			frequencyScale = 1.0f - frequencyScale;
			m_brakeSound->SetFrequencyScale(frequencyScale);
		}
	}
}

// FUNCTION: LEGORACERS 0x00438500
void RaceState::Racer::StopEngineSounds()
{
	if (m_controlMode != 2) {
		LegoU32 flags = m_flags;
		flags &= ~c_flagEngineSounds;
		m_flags = flags;

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
		LegoU32 flags = m_flags;
		m_flags = flags & ~c_flagShoveActive;

		if (!(flags & c_flagDrifting)) {
			EndDrift();
		}

		if (m_shoveForceSlot == 1) {
			m_physics.EndExternalForce0();
		}
		else if (m_shoveForceSlot == 2) {
			m_physics.EndExternalForce1();
		}

		m_shoveForceSlot = 0;

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

	if (firstRacer->m_flags & c_flagGhost) {
		return;
	}

	if (secondRacer && (secondRacer->m_flags & c_flagGhost)) {
		return;
	}

	if (firstRacer->m_physics.m_flags & Physics::c_flagSpinOut) {
		return;
	}

	if (secondRacer && (secondRacer->m_physics.m_flags & Physics::c_flagSpinOut)) {
		return;
	}

	GolVec3 collisionNormal = collision->m_normal;
	GolVec3 impulse = collisionNormal;
	impulse.m_x *= collision->m_penetrationDepth;
	impulse.m_y *= collision->m_penetrationDepth;
	impulse.m_z *= collision->m_penetrationDepth;

	firstRacer->m_physics.MoveBy(&impulse);

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

	firstRacer->m_physics.ApplyDirectionalImpulse(&collisionNormal, impulseScale);
	if (firstRacer->m_forceFeedback) {
		firstRacer->m_forceFeedback->FUN_004220e0();
	}

	if (!secondRacer) {
		return;
	}

	secondRacer->m_physics.ApplyDirectionalImpulse(&collisionNormal, -impulseScale);
	if (secondRacer->m_forceFeedback) {
		secondRacer->m_forceFeedback->FUN_004220e0();
	}

	if (firstRacer->m_controlMode == 2 && secondRacer->m_controlMode == 2) {
		if (firstRacer->m_physics.m_speedRampScale == 1.0f) {
			firstRacer->m_speedRampTimerMs = 750;
		}

		if (secondRacer->m_physics.m_speedRampScale == 1.0f) {
			secondRacer->m_speedRampTimerMs = 750;
		}
	}
	else if (firstRacer->m_physics.m_speed > secondRacer->m_physics.m_speed) {
		SoundVector* contactPosition = reinterpret_cast<SoundVector*>(&collision->m_contactPoint);

		if (!firstRacer->m_scrapeSoundCooldownMs && !secondRacer->m_scrapeSoundCooldownMs) {
			SoundVector soundDirection;
			soundDirection.m_x = firstRacer->m_physics.m_velocity.m_x;
			soundDirection.m_y = firstRacer->m_physics.m_velocity.m_y;
			soundDirection.m_z = firstRacer->m_physics.m_velocity.m_z;
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

		m_visuals.m_particleAnimation->FUN_00489d70("carsprk", &collision->m_contactPoint, NULL, NULL);

		if (firstRacer->m_flags & c_flagShielded) {
			secondRacer->PlayReaction(FALSE);
		}
		else {
			firstRacer->PlayReaction(FALSE);
		}
	}
	else {
		firstRacer->PlayReaction(FALSE);
	}

	if ((firstRacer->m_flags & c_flagShielded) && !(secondRacer->m_flags & c_flagShielded)) {
		if (firstRacer->m_shieldLevel == 1) {
			GolVec3 secondForward;
			secondRacer->m_visuals.m_carEntity->GetOrientationRow0(&secondForward);
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
			secondRacer->m_physics.StartSpin(1.0f, 0.0089999996f, 0);
		}
		else if (firstRacer->m_shieldLevel == 3) {
			secondRacer->m_physics.StartSpin(2.0f, 0.0089999996f, 0);
		}
	}

	if ((secondRacer->m_flags & c_flagShielded) && !(firstRacer->m_flags & c_flagShielded)) {
		if (secondRacer->m_shieldLevel == 1) {
			GolVec3 firstForward;
			firstRacer->m_visuals.m_carEntity->GetOrientationRow0(&firstForward);
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
			firstRacer->m_physics.StartSpin(1.0f, 0.0089999996f, 0);
		}
		else if (secondRacer->m_shieldLevel == 3) {
			firstRacer->m_physics.StartSpin(2.0f, 0.0089999996f, 0);
		}
	}

	if ((firstRacer->m_flags & c_flagCursed) && !(secondRacer->m_flags & c_flagCursed) && firstRacer->m_curseTickMs &&
		!(secondRacer->m_flags & c_flagShielded)) {
		secondRacer->AttachCurse(&firstRacer->m_visuals.m_curseEntity, firstRacer->m_curseTimerMs);
		firstRacer->RemoveCurse();
	}
	else if (
		(secondRacer->m_flags & c_flagCursed) && !(firstRacer->m_flags & c_flagCursed) && secondRacer->m_curseTickMs &&
		!(firstRacer->m_flags & c_flagShielded)
	) {
		firstRacer->AttachCurse(&secondRacer->m_visuals.m_curseEntity, secondRacer->m_curseTimerMs);
		secondRacer->RemoveCurse();
	}

	firstRacer->m_flags |= c_flagSpeedRamping;
	secondRacer->m_flags |= c_flagSpeedRamping;
}

// FUNCTION: LEGORACERS 0x00438e60
void RaceState::Racer::ApplyShove(GolVec3* p_unk0x04)
{
	LegoEventQueue::Descriptor descriptor;
	if (m_flags & c_flagShoveActive) {
		return;
	}

	descriptor.m_unk0x04 = 0;
	descriptor.m_unk0x0c = 0;
	descriptor.m_unk0x00 = 1;
	descriptor.m_unk0x08 = 1;
	descriptor.m_unk0x10 = 750;
	if (m_raceState->GetRoster()->FUN_0042fb50(this, &descriptor) == NULL) {
		return;
	}

	m_physics.StartSteering(2.5f, 0.89999998f, 3.1415927f);
	LegoU32 flags = m_physics.m_flags;
	if (!(flags & Physics::c_flagExternalForce0)) {
		m_physics.StartExternalForce0(p_unk0x04);
		m_shoveForceSlot = 1;
	}
	else if (!(flags & Physics::c_flagExternalForce1)) {
		m_physics.StartExternalForce1(p_unk0x04);
		m_shoveForceSlot = 2;
	}

	m_flags |= c_flagShoveActive;
}

// FUNCTION: LEGORACERS 0x00438f20
void RaceState::Racer::AiConsiderPowerup()
{
	if (m_powerupManager->GetUsedEffectEntityCount() >= 20) {
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
					if ((m_flags & c_flagFinished) && m_whiteBrickCount == 3) {
						return;
					}
					if (m_physics.m_flags & Physics::c_flagSpinning) {
						return;
					}

					AiUsePowerup();
				}
				return;
			case 1: {
				GolVec3 position;
				m_visuals.m_carEntity->VTable0x04(&position);

				GolVec3 direction;
				m_visuals.m_carEntity->GetOrientationRow0(&direction);

				if (!m_raceState->FindNearestRacerInCone(
						&position,
						&direction,
						g_aiRedTargetMinDistanceSquared,
						g_aiRedTargetMaxDistanceSquared,
						g_aiRedTargetConeCosine
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
		PlayTaunt();
		return;
	}

	LegoU32 flags = m_flags;
	LegoU32 index = m_whiteBrickCount;

	if (flags & c_flagCheatRedOnly) {
		m_powerupManager->UseRedPowerup(this, 1);
	}
	else {
		if (flags & c_flagCheatMaxPowerups) {
			index = 3;
		}

		switch (state) {
		case 3:
			if (!((flags & c_flagCheatFlySkyHigh) && index != 3)) {
				m_powerupManager->UseGreenPowerup(this, index);
			}
			break;
		case 1:
			m_powerupManager->UseRedPowerup(this, index);
			break;
		case 4:
			PlayReaction(TRUE);
			m_powerupManager->UseYellowPowerup(this, index);
			break;
		case 2:
			PlayReaction(TRUE);
			m_powerupManager->UseBluePowerup(this, index);
			break;
		default:
			return;
		}
	}

	m_heldPowerupColor = 0;
	ReturnAllWhiteBricks();
}

// FUNCTION: LEGORACERS 0x00439210
LegoU32 RaceState::Racer::CollectColorBrick(LegoU32 p_brickColor)
{
	m_aiPowerupCheckMs = 0;
	m_heldPowerupColor = p_brickColor;
	m_aiPowerupCheckIntervalMs = 300;
	return p_brickColor;
}

// FUNCTION: LEGORACERS 0x00439240
void RaceState::Racer::PlayReaction(LegoBool32 p_positive)
{
	if (m_reactionCooldownMs <= 0) {
		SoundVector position;
		m_visuals.m_carEntity->VTable0x04(&position);

		LegoU32 randomIndex;
		if (p_positive) {
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
void RaceState::Racer::OnRaceStart()
{
	LegoU32 value = m_flags & 0xfffffffd;
	m_flags = value;

	value = 1;
	m_physics.m_soundsEnabled = value;

	if (m_routeRecord) {
		m_physics.m_routePaused = 0;
	}

	m_zoneBeforePrevious = value;
	value = m_controlMode;
	m_currentZone = 0;
	m_previousZone = 2;

	if (value == 2) {
		g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
		value = g_randomTable[g_randomTableIndex];
		if ((value & 0xff) < m_aiGreenUseChance) {
			m_powerupManager->UseGreenPowerup(this, 0);
		}
	}
}

// FUNCTION: LEGORACERS 0x004393d0
void RaceState::Racer::StartEngine()
{
	SoundVector position;
	m_visuals.m_carEntity->VTable0x04(&position);

	m_soundSource
		->PlaySpatialSoundById(0x3e, &position, g_shieldSoundMinDistance, g_shieldSoundMaxDistance, 1.0f, 1.0f);
	m_flags |= c_flagEngineSounds;
}

// FUNCTION: LEGORACERS 0x00439420
LegoBool32 RaceState::Racer::CollectWhiteBrick(DroppableBrick* p_brick)
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

		m_whiteBricks[index] = p_brick;
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
			m_visuals.m_carEntity->VTable0x04(&position);
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
	LegoU32 flags = m_flags;
	if (!(flags & c_flagHalted)) {
		m_flags = flags | c_flagHalted;
		m_physics.EndSpin();
		m_physics.StartSliding();
	}
}

// FUNCTION: LEGORACERS 0x004395a0
void RaceState::Racer::Resume()
{
	LegoU32 flags = m_flags;
	if (flags & c_flagHalted) {
		m_flags = flags & ~c_flagHalted;
		m_physics.StopSliding();
	}
}

// FUNCTION: LEGORACERS 0x004395d0
void RaceState::Racer::EnterGhostMode()
{
	m_flags |= c_flagGhost;
	RemoveCurse();
	m_visuals.StopSkidEffects();
	m_visuals.HideModels();
	m_visuals.m_flags &= ~(CarVisuals::c_flagShadowEnabled | CarVisuals::c_flagShadowVisible);
	m_visuals.StopTurboEffects();
	m_visuals.StopSlideSkid();
	Physics* field0x3e8 = &m_physics;
	field0x3e8->EndSpin();

	if (m_controlMode == 2 && m_physics.m_routeMode) {
		field0x3e8->StartRouteGhost();
	}
	else {
		field0x3e8->m_flags |= Physics::c_flagNoTrackCollision;
	}

	if (m_forceFeedback) {
		m_forceFeedback->FUN_00422030(3);
	}
}

// FUNCTION: LEGORACERS 0x00439660
void RaceState::Racer::LeaveGhostMode()
{
	m_flags &= ~c_flagGhost;

	CarVisuals* field = &m_visuals;
	field->ShowModels();

	if (m_controlMode == 2 && m_physics.m_routeMode) {
		m_physics.EndRouteGhost();
		field->m_flags |= CarVisuals::c_flagShadowEnabled;
		return;
	}

	m_physics.m_flags &= ~Physics::c_flagNoTrackCollision;
	field->m_flags |= CarVisuals::c_flagShadowEnabled;
}

// FUNCTION: LEGORACERS 0x004396c0
void RaceState::Racer::StartTurbo(LegoU32 p_level)
{
	m_flags |= c_flagTurbo;

	if (m_controlMode != 2) {
		m_visuals.StartTurboEffects();
	}

	m_driveController.m_flags =
		(m_driveController.m_flags & ~DriveController::c_flagTurboWeakened) | DriveController::c_flagTurbo;
	m_physics.SnapFacingDirection();
	m_physics.StartBoost();
	m_turboLevel = p_level;

	if (m_forceFeedback) {
		m_forceFeedback->FUN_00422030(p_level);
	}
}

// FUNCTION: LEGORACERS 0x00439730
void RaceState::Racer::ClearActiveAction()
{
	m_flags &= ~c_flagTurbo;
	m_visuals.StopTurboEffects();
	m_driveController.m_flags &= ~(DriveController::c_flagTurbo | DriveController::c_flagTurboWeakened);
	m_physics.EndBoost();
}

// FUNCTION: LEGORACERS 0x00439770
LegoU32 RaceState::Racer::StartShield(LegoU32 p_level)
{
	m_flags |= c_flagShielded;
	m_shieldLevel = p_level;
	return p_level;
}

// FUNCTION: LEGORACERS 0x00439790
void RaceState::Racer::EndShield()
{
	m_flags &= ~c_flagShielded;
}

// FUNCTION: LEGORACERS 0x004397a0
void RaceState::Racer::StartSpinOut()
{
	m_physics.StartSpinOut();
}

// FUNCTION: LEGORACERS 0x004397b0
void RaceState::Racer::EndSpinOut()
{
	m_physics.EndSpinOut();
}

// FUNCTION: LEGORACERS 0x004397c0
void RaceState::Racer::StartDrift(LegoBool32 p_left)
{
	if (!(m_flags & c_flagDrifting) || p_left != m_driveController.m_slideLeft) {
		m_driveController.EngageSlide(p_left);

		if (m_driveController.m_flags & DriveController::c_flagSliding) {
			m_flags |= c_flagDrifting;

			if (!m_controlMode && !(m_physics.m_flags & Physics::c_flagSliding)) {
				SoundVector position;
				m_visuals.StartDust();

				if (!(m_visuals.m_flags & CarVisuals::c_flagSkidding)) {
					m_visuals.StartSkidEffects();
				}

				m_visuals.m_carEntity->VTable0x04(&position);
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

	if (m_flags & c_flagDrifting) {
		if (m_driveController.m_flags & DriveController::c_flagSliding) {
			m_driveController.ReleaseSlide();
		}

		LegoU8 flags0xaa8 = static_cast<LegoU8>(m_physics.m_flags);
		LegoU8 testFlag = Physics::c_flagSliding;
		if (!(testFlag & flags0xaa8)) {
			if (m_driveController.m_flags & DriveController::c_flagSlideBoost) {
				m_visuals.m_carEntity->VTable0x04(&position);
				m_soundSource->PlaySpatialSoundById(
					0x41,
					&position,
					g_shieldSoundMinDistance,
					g_shieldSoundMaxDistance,
					1.0f,
					1.0f
				);
			}

			if (!(m_driveController.m_flags & DriveController::c_flagTurbo)) {
				m_visuals.StopSkidEffects();
			}
		}

		LegoU32 flags0xd04 = m_flags;
		flags0xd04 &= ~c_flagDrifting;
		m_flags = flags0xd04;
	}
}

// FUNCTION: LEGORACERS 0x00439900
void RaceState::Racer::AttachCurse(GolAnimatedEntity* p_curseEntity, LegoU32 p_durationMs)
{
	LegoU32 flags0xd04 = m_flags;
	m_curseTimerMs = p_durationMs;
	flags0xd04 |= c_flagCursed;
	m_curseTickMs = 1000;
	m_flags = flags0xd04;

	LegoU32 flags0xc70 = m_driveController.m_flags;
	flags0xc70 |= DriveController::c_flagCursed;
	GolAnimatedEntity* entity = &m_visuals.m_curseEntity;
	m_driveController.m_flags = flags0xc70;

	LegoU32 flags0x384 = m_visuals.m_reactionFlags;
	flags0x384 |= CarVisuals::c_flags0x384Bit1;
	m_visuals.m_reactionFlags = flags0x384;

	entity->FUN_0040d550(
		p_curseEntity->GetModel(0),
		p_curseEntity->VTable0x58(0),
		p_curseEntity->GetModelPart(0),
		p_curseEntity->GetModelDistance(0)
	);

	for (LegoU32 i = 1; i < 3; i++) {
		if (p_curseEntity->GetModel(i)) {
			entity->FUN_10023940(
				p_curseEntity->GetModel(i),
				p_curseEntity->VTable0x58(i),
				p_curseEntity->GetModelPart(i),
				p_curseEntity->GetModelDistance(i)
			);
		}
	}

	entity->FUN_0040dad0(0);
	entity->SetPartAnimationEnabled(TRUE);
	entity->CopyOrientationFrom(*p_curseEntity);
	entity->CopyPositionFrom(*p_curseEntity);

	m_soundDac = m_soundSource->AcquireSoundById(8);
	if (m_soundDac) {
		m_soundDac->Play(TRUE);
		m_soundDac->SetDistanceRangeWithMinSquared(
			g_shieldSoundMinDistance * g_shieldSoundMinDistance,
			g_shieldSoundMaxDistance
		);

		GolVec3 position;
		p_curseEntity->VTable0x04(&position);
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
	m_visuals.FlashColor(&transform, p_durationMs);
	m_physics.StartCurseSlow();
}

// FUNCTION: LEGORACERS 0x00439b00
void RaceState::Racer::RemoveCurse()
{
	if (m_curseSound) {
		m_soundSource->ReleaseSound(m_curseSound);
		m_curseSound = NULL;
	}

	LegoU32 flags0xd04 = m_flags;
	m_curseTimerMs = 0;
	flags0xd04 &= ~c_flagCursed;
	m_flags = flags0xd04;

	m_driveController.m_flags &= ~DriveController::c_flagCursed;
	m_visuals.m_curseEntity.VTable0x54();
	m_visuals.EndFlash();
	m_physics.EndCurseSlow();
}

// FUNCTION: LEGORACERS 0x00439b70
void RaceState::Racer::EnterOpenTrack()
{
	LegoU32 state = m_currentZone;
	if (state) {
		LegoU32 oldState = m_previousZone;
		m_previousZone = state;
		m_zoneBeforePrevious = oldState;
		m_currentZone = 0;
	}
}

// FUNCTION: LEGORACERS 0x00439ba0
LegoU32 RaceState::Racer::CrossFinishLine()
{
	LegoU32 result = m_currentZone;
	if (result != 1) {
		if (result == 0 && m_previousZone == 2 && m_zoneBeforePrevious == 1) {
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
						result = m_lapCount;
						if (m_lapsCompleted < result) {
							m_timeBehindDisplayMs = 2000;
						}
					}
				}
			}
		}

		LegoU32 state = m_currentZone;
		m_zoneBeforePrevious = m_previousZone;
		m_previousZone = state;
		m_currentZone = 1;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00439c40
void RaceState::Racer::EnterPostLineZone()
{
	LegoU32 state = m_currentZone;
	if (state != 2) {
		LegoU32 oldState = m_previousZone;
		m_previousZone = state;
		m_zoneBeforePrevious = oldState;
		m_currentZone = 2;
	}
}

// FUNCTION: LEGORACERS 0x00439c70
void RaceState::Racer::ComputeStandingsDeltas(StandingsDeltaEntry* p_entries)
{
	m_raceState->ComputeStandingsDeltas(this, p_entries);
}

// FUNCTION: LEGORACERS 0x00439c90
void RaceState::Racer::PlayTaunt()
{
	SoundVector position;
	m_visuals.m_carEntity->VTable0x04(&position);

	m_soundSource->PlaySpatialSoundById(
		m_tauntSoundId,
		&position,
		g_shieldSoundMinDistance,
		g_shieldSoundMaxDistance,
		1.0f,
		1.0f
	);
	m_physics.m_eventTable->FireEventsAt(999, 999, &position);
}

// FUNCTION: LEGORACERS 0x00439cf0
void RaceState::Racer::UpdateFacing(LegoU32 p_elapsedMs)
{
	CheckpointGraph::Entry* field0xcc4 = m_checkpoint;
	if (field0xcc4) {
		LegoU32 flags = m_flags;
		LegoBool32 isBlocked = FALSE;

		if (flags & c_flagGhost) {
			m_facingForwardMs = 0;
			m_flags = flags & ~(c_flagFacingForwardPending | c_flagFacingForward);
			return;
		}

		LegoU32 countdown = m_facingForwardMs;
		if (countdown) {
			if (p_elapsedMs >= countdown) {
				m_facingForwardMs = 0;
				m_flags = flags & ~c_flagFacingForward;
			}
			else {
				m_facingForwardMs = countdown - p_elapsedMs;
			}
		}

		GolVec3 direction = m_physics.m_facingDirection;
		for (LegoU32 i = 0; i < sizeOfArray(field0xcc4->m_next.m_items); i++) {
			if (isBlocked) {
				break;
			}

			if (field0xcc4->m_next.m_items[i] != 0xff) {
				m_checkpointGraph->GetCheckpoint(field0xcc4->m_next.m_items[i]);
				field0xcc4 = m_checkpoint;
				LegoFloat dot = direction.m_z * field0xcc4->m_planeNormal.m_z +
								direction.m_y * field0xcc4->m_planeNormal.m_y +
								direction.m_x * field0xcc4->m_planeNormal.m_x;
				if (dot <= g_unk0x004b02e0) {
					isBlocked = TRUE;
				}
			}
		}

		flags = m_flags;
		if (flags & c_flagFacingForwardPending) {
			if (isBlocked) {
				m_facingForwardMs = 0;
				m_flags = flags & ~c_flagFacingForwardPending;
			}
			else if (!m_facingForwardMs) {
				m_flags = (flags & ~(c_flagFacingForwardPending | c_flagFacingForward)) | c_flagFacingForward;
			}
		}
		else {
			if (!(flags & c_flagFacingForward)) {
				if (!isBlocked) {
					m_facingForwardMs = 500;
					m_flags = flags | c_flagFacingForwardPending;
				}
			}
			else if (!isBlocked) {
				m_facingForwardMs = 500;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00439e60
void RaceState::Racer::SetLookTarget(GolVec3* p_unk0x04)
{
	m_flags |= c_flagHasLookTarget;
	m_lookTargetPosition.m_x = p_unk0x04->m_x;
	m_lookTargetPosition.m_y = p_unk0x04->m_y;
	m_lookTargetPosition.m_z = p_unk0x04->m_z;
}

// FUNCTION: LEGORACERS 0x00439e90
void RaceState::Racer::ClearLookTarget()
{
	m_flags &= ~c_flagHasLookTarget;
}

// FUNCTION: LEGORACERS 0x00439ea0
void RaceState::Racer::UpdateLookTarget(LegoU32)
{
	LegoU32 flags = m_flags & ~(c_flagLookTargetLeft | c_flagLookTargetRight);
	m_flags = flags;

	if (m_flags & c_flagHasLookTarget) {
		GolVec3 direction = m_physics.m_facingDirection;
		GolVec3 position;
		m_visuals.m_carEntity->VTable0x04(&position);

		GolVec3 delta;
		delta.m_x = m_lookTargetPosition.m_x - position.m_x;
		delta.m_y = m_lookTargetPosition.m_y - position.m_y;
		delta.m_z = m_lookTargetPosition.m_z - position.m_z;
		GolMath::NormalizeVector3(delta, &delta);

		LegoFloat forwardDot = direction.m_z * delta.m_z + direction.m_y * delta.m_y + direction.m_x * delta.m_x;
		if (forwardDot < 0.5f) {
			GolVec3 side;
			side.m_x = direction.m_y - 0.0f;
			side.m_y = 0.0f - direction.m_x;
			side.m_z = 0.0f;
			if (GOLVECTOR3_DOT(side, delta) > 0.0f) {
				m_flags |= c_flagLookTargetLeft;
			}
			else {
				m_flags |= c_flagLookTargetRight;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00439fc0
void RaceState::Racer::OnCheckpointCrossed(CheckpointGraph::Entry* p_unk0x04, GolBoundingVolume::Field0x0c* p_unk0x08)
{
	LegoBool32 isForward;
	if (p_unk0x08->m_normal.m_z * p_unk0x04->m_planeNormal.m_z +
			p_unk0x08->m_normal.m_y * p_unk0x04->m_planeNormal.m_y +
			p_unk0x08->m_normal.m_x * p_unk0x04->m_planeNormal.m_x <
		0.0f) {
		isForward = FALSE;
	}
	else {
		isForward = TRUE;
	}

	if (p_unk0x04 != m_checkpoint || isForward != m_checkpointForward) {
		if (p_unk0x04->m_lapFraction == 0.0f) {
			LegoU32 flags = m_flags;
			if (isForward) {
				if (!(flags & c_flagCrossedBackward)) {
					m_checkpointCount++;
				}
			}
			else {
				m_checkpointForward = isForward;
				m_flags = flags | c_flagCrossedBackward;
				m_currentZone = 0;
				m_previousZone = 2;
				m_zoneBeforePrevious = 2;
				m_checkpoint = p_unk0x04;
				return;
			}

			m_flags = flags & ~c_flagCrossedBackward;
		}
		else {
			LegoU32 flags = m_flags;
			if (!(flags & c_flagCrossedBackward)) {
				m_checkpoint = p_unk0x04;
				m_checkpointForward = isForward;
				return;
			}

			m_checkpointCount--;
			m_flags = flags & ~c_flagCrossedBackward;
		}

		m_checkpoint = p_unk0x04;
		m_checkpointForward = isForward;
	}
}

// FUNCTION: LEGORACERS 0x0043a0a0
LegoFloat RaceState::Racer::GetRaceProgress()
{
	if (m_checkpoint) {
		return static_cast<LegoFloat>(m_checkpointCount) + m_checkpoint->m_lapFraction;
	}

	return 0.0f;
}

// FUNCTION: LEGORACERS 0x0043a0c0
void RaceState::Racer::FUN_0043a0c0()
{
	m_trail->m_unk0x03c = (m_trail->m_unk0x03c + 1) & 3;
}

// FUNCTION: LEGORACERS 0x0043a0e0
void RaceState::Racer::SwitchToAiControl()
{
	RaceRouteRecord* unk0xe2c = m_routeRecord;
	m_controlMode = 2;

	if (!unk0xe2c) {
		unk0xe2c = m_raceState->FindNearestRouteRecord(this);
		m_routeRecord = unk0xe2c;

		if (unk0xe2c) {
			m_driveController.StartReturnToPath(unk0xe2c);
		}
		else {
			m_driveController.m_flags |= 0x80;
		}
	}
}

// FUNCTION: LEGORACERS 0x0043a130
void RaceState::Racer::StartMagnetHold()
{
	m_flags |= c_flagMagnetHeld;

	if (m_controlMode != 2) {
		m_driveController.m_flags |= DriveController::c_flagBrakeToStop;
		m_visuals.StartSkidEffects();
	}

	if (m_physics.m_routeMode) {
		m_physics.m_routeBaseSpeed = 0.0f;
		if (!(m_physics.m_flags & Physics::c_flagRoutePushed)) {
			m_physics.m_routeTargetSpeed = 0.0f;
		}
	}

	Resume();
}

// FUNCTION: LEGORACERS 0x0043a1a0
void RaceState::Racer::EndMagnetHold()
{
	LegoU32 flags0xd04 = m_flags;
	LegoU32 state = m_controlMode;
	flags0xd04 &= ~c_flagMagnetHeld;
	m_flags = flags0xd04;

	if (state != 2) {
		LegoU32 flags0x014 = m_driveController.m_flags;
		flags0x014 &= ~DriveController::c_flagBrakeToStop;
		m_driveController.m_flags = flags0x014;
		m_visuals.StopSkidEffects();
	}

	if (m_physics.m_routeMode) {
		LegoU32 flags0xaa8 = m_physics.m_flags;
		m_physics.m_routeBaseSpeed = 1.0f;
		if (!(flags0xaa8 & Physics::c_flagRoutePushed)) {
			m_physics.m_routeTargetSpeed = 1.0f;
		}
	}

	Resume();
}

// FUNCTION: LEGORACERS 0x0043a210
void RaceState::Racer::SetStandingsPosition(LegoU32 p_position)
{
	if (!(m_flags & c_flagPreStart)) {
		LegoU32 unk0xd00 = m_lapTimes[5];
		if (p_position < unk0xd00) {
			PlayReaction(TRUE);
		}
		else if (p_position > unk0xd00) {
			PlayReaction(FALSE);
		}

		m_lapTimes[5] = p_position;
	}
	else {
		m_lapTimes[5] = p_position;
	}
}

// FUNCTION: LEGORACERS 0x0043a270
void RaceState::Racer::AbsorbShieldHit()
{
	LegoU32 soundId = 1;
	SoundVector position;
	m_visuals.m_carEntity->VTable0x04(&position);

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

	m_soundSource->PlaySpatialSoundById(
		soundId,
		&position,
		g_shieldHitSoundMinDistance,
		g_shieldHitSoundMaxDistance,
		1.0f,
		1.0f
	);
	m_shieldHitCooldownMs = 500;
}

// FUNCTION: LEGORACERS 0x0043a300
void RaceState::Racer::SetCameraView(LegoU32 p_viewIndex, LegoBool32 p_flag)
{
	if (m_cameraController) {
		m_cameraController->FUN_004283f0(p_viewIndex, p_flag);
		m_cameraController->m_unk0x000 = TRUE;
		m_cameraViewIndex = p_viewIndex;

		if (p_flag) {
			m_flags |= c_flagBit22;
		}
		else {
			m_flags &= ~c_flagBit22;
		}
	}
}

// FUNCTION: LEGORACERS 0x0043a360
void RaceState::Racer::ReapplyCameraView()
{
	if (m_cameraController) {
		m_cameraController->FUN_004283f0(m_cameraViewIndex, m_flags & 0x00400000);
		m_cameraController->m_unk0x000 = TRUE;
	}
}

// FUNCTION: LEGORACERS 0x0043a390
void RaceState::Racer::CycleCameraView()
{
	LegoU32 flags = m_flags;
	if (!(flags & c_flagFinished) && (flags & c_flagEngineSounds)) {
		RaceCameraController* controller = m_cameraController;
		if (controller) {
			LegoU32 index = m_cameraViewIndex;
			LegoBool32 enabled = flags & c_flagBit22;
			index++;
			index &= 3;
			m_cameraViewIndex = index;
			controller->FUN_004283f0(index, enabled);
			m_cameraController->m_unk0x000 = TRUE;
		}
	}
}

// FUNCTION: LEGORACERS 0x0043a3e0
void RaceState::Racer::InvalidateCamera()
{
	if (m_cameraController) {
		m_cameraController->m_unk0x000 = TRUE;
	}
}

// FUNCTION: LEGORACERS 0x0043a3f0
void RaceState::Racer::StartLookBack()
{
	m_cameraController->m_lookBack = TRUE;
}

// FUNCTION: LEGORACERS 0x0043a400
void RaceState::Racer::EndLookBack()
{
	m_cameraController->m_lookBack = FALSE;
}

// FUNCTION: LEGORACERS 0x0043a410
RaceState::RaceSetup::RaceSetup()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0043a420
RaceState::RaceSetup::~RaceSetup()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0043a430
void RaceState::RaceSetup::Reset()
{
	m_racers = NULL;
	m_racerCount = 0;
	m_updateDelayMs = 0;
	m_rubberBandBoost = 0.0f;
}

// FUNCTION: LEGORACERS 0x0043a440
void RaceState::RaceSetup::Destroy()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0043a450
void RaceState::RaceSetup::Initialize(Racer* p_racers, LegoU32 p_racerCount)
{
	if (m_racers) {
		Destroy();
	}

	m_racers = p_racers;
	m_racerCount = p_racerCount;
	m_updateDelayMs = 15000;
}

// FUNCTION: LEGORACERS 0x0043a480
LegoU32 RaceState::RaceSetup::Update(LegoU32 p_elapsedMs)
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
			if (state != ignoredState && m_racers[racerIndex].GetRaceProgress() > bestProgress) {
				bestProgress = m_racers[racerIndex].GetRaceProgress();
			}

			result = m_racerCount;
			racerIndex++;
		} while (racerIndex < result);

		if (bestProgress == g_minSoundPan) {
		ResetRacerPacing:
			result = m_racerCount;
			LegoU32 index = 0;
			if (result > 0) {
				LegoU32 flags0xaa8Mask = Racer::Physics::c_flagRoutePushed;
				do {
					Racer* racer = &m_racers[index];
					if (!(racer->m_flags & c_rubberBandFlags)) {
						LegoU32 flags0xaa8 = racer->m_physics.m_flags;
						racer->m_physics.m_routeBaseSpeed = 1.0f;
						if (!(flags0xaa8Mask & flags0xaa8)) {
							racer->m_physics.m_routeTargetSpeed = 1.0f;
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
				LegoU32 flags0xaa8Mask = Racer::Physics::c_flagRoutePushed;
				do {
					if (racerIndex) {
						if (!(m_racers[racerIndex].m_flags & c_rubberBandFlags)) {
							if (m_racers[racerIndex].GetRaceProgress() > bestProgress) {
								LegoFloat adjustment = 1.0f - g_rubberBandScale;
								adjustment += m_rubberBandBoost;
								Racer::Physics* field0x3e8 = &m_racers[racerIndex].m_physics;
								LegoU32 flags0xaa8 = field0x3e8->m_flags;
								field0x3e8->m_routeBaseSpeed = adjustment;
								if (!(flags0xaa8Mask & flags0xaa8)) {
									field0x3e8->m_routeTargetSpeed = adjustment;
								}
							}
							else if (m_racers[racerIndex].GetRaceProgress() < bestProgress) {
								LegoFloat adjustment = g_rubberBandScale + m_rubberBandBoost;
								adjustment += 1.0f;
								Racer::Physics* field0x3e8 = &m_racers[racerIndex].m_physics;
								LegoU32 flags0xaa8 = field0x3e8->m_flags;
								field0x3e8->m_routeBaseSpeed = adjustment;
								if (!(flags0xaa8Mask & flags0xaa8)) {
									field0x3e8->m_routeTargetSpeed = adjustment;
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
	m_roster.m_racers = NULL;
	m_roster.m_unk0x058 = 0;
	m_roster.m_racerCount = 0;
	m_roster.m_unk0x05c = 0;

	LegoS32 i;
	for (i = 0; i < sizeOfArray(m_roster.m_unk0x064); i++) {
		m_roster.m_unk0x064[i] = 0;
		m_roster.m_startPositions[i].m_x = 0.0f;
		m_roster.m_startPositions[i].m_y = 0.0f;
		m_roster.m_startPositions[i].m_z = 0.0f;
		m_roster.m_startDirections[i].m_x = 0.0f;
		m_roster.m_startDirections[i].m_y = 0.0f;
		m_roster.m_startDirections[i].m_z = 0.0f;
		m_roster.m_startUps[i].m_x = 0.0f;
		m_roster.m_startUps[i].m_y = 0.0f;
		m_roster.m_startUps[i].m_z = 0.0f;
		m_roster.m_placementSlots[i] = 0;
	}

	m_roster.m_proximitySoundResource = NULL;
	m_roster.m_unk0x080[0] = NULL;
	m_roster.m_unk0x080[1] = NULL;
	m_roster.m_unk0x080[2] = NULL;

	for (i = 0; i < sizeOfArray(m_roster.m_customCarModels); i++) {
		m_roster.m_customCarModels[i] = 0;
		m_roster.m_customCarEntities[i] = 0;
	}

	m_roster.m_customCarCount = 0;
	m_roster.m_routeRecords = NULL;
	m_setup.m_textureList = 0;
	m_setup.m_materialLibrary = 0;
	m_setup.m_lapCount = 0;
}

// FUNCTION: LEGORACERS 0x0043b030
void RaceState::Destroy()
{
	m_setup.Destroy();

	if (m_setup.m_materialLibrary) {
		m_roster.m_golExport->DestroyMaterialList(m_setup.m_materialLibrary);
		m_setup.m_materialLibrary = NULL;
	}

	if (m_setup.m_textureList) {
		m_roster.m_golExport->DestroyTextureList(m_setup.m_textureList);
		m_setup.m_textureList = NULL;
	}

	LegoS32 i;
	for (i = 0; i < 2; i++) {
		if (m_roster.m_customCarModels[i]) {
			delete m_roster.m_customCarModels[i];
			m_roster.m_customCarModels[i] = NULL;
		}

		if (m_roster.m_customCarEntities[i]) {
			delete m_roster.m_customCarEntities[i];
			m_roster.m_customCarEntities[i] = NULL;
		}
	}

	GolNameTable* table = &m_chassisTable;
	table->Clear();

	table = &m_championList;
	table->Clear();

	table = &m_driverTable;
	table->Clear();

	if (m_roster.m_proximitySoundResource) {
		m_roster.m_unk0x05c->ReleaseSound(m_roster.m_proximitySoundResource);
		m_roster.m_proximitySoundResource = NULL;
	}

	LegoU32 racerIndex;
	for (racerIndex = 0; racerIndex < m_roster.m_racerCount; racerIndex++) {
		if (m_roster.m_unk0x064[racerIndex]) {
			m_roster.m_unk0x064[racerIndex]->m_active = 0;
			m_roster.m_unk0x064[racerIndex] = NULL;
		}
	}

	LegoEventQueue* queue = &m_roster;
	queue->Destroy();

	if (m_roster.m_racers) {
		for (racerIndex = 0; racerIndex < m_roster.m_racerCount; racerIndex++) {
			(*(m_roster.m_racers + racerIndex)).Destroy();
		}

		delete[] m_roster.m_racers;

		m_roster.m_racers = NULL;
	}

	Reset();
}

// FUNCTION: LEGORACERS 0x0043b190
void RaceState::CreateRacers(CreateRacersParams* p_params, RacerContext* p_context, LegoBool32 p_binary)
{
	m_roster.m_field0x010 = p_context->m_checkpointGraph;
	m_roster.m_unk0x05c = p_context->m_soundSource;
	m_roster.m_powerupManager = p_context->m_powerupManager;
	m_roster.m_golExport = p_context->m_golExport;
	m_roster.m_timeRaceManager = p_params->m_timeRaceManager;
	m_roster.m_routeRecords = p_params->m_routeRecords;
	m_setup.m_lapCount = p_params->m_lapCount;
	static_cast<LegoEventQueue*>(&m_roster)->VTable0x08(100);

	m_roster.m_raceState = this;
	m_roster.m_racerCount = p_params->m_racerCount;
	m_roster.m_racers = new Racer[m_roster.m_racerCount];
	if (m_roster.m_racers == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_setup.m_textureList = m_roster.m_golExport->CreateTextureList();
	m_setup.m_materialLibrary = m_roster.m_golExport->CreateMaterialList();
	m_setup.m_textureList->VTable0x1c(p_context->m_renderer, m_roster.m_racerCount);
	m_setup.m_materialLibrary->VTable0x1c(p_context->m_renderer, m_roster.m_racerCount);

	DriverCosmeticTable::LoadParams driverParams;
	driverParams.m_golExport = p_context->m_golExport;
	driverParams.m_renderer = p_context->m_renderer;
	driverParams.m_entryCapacity = m_roster.m_racerCount;
	driverParams.m_filename = g_racerDatabaseNames[0];
	driverParams.m_binary = p_binary;
	m_driverTable.Load(&driverParams);

	ChampionDefinitionList::LoadParams championParams;
	championParams.m_golExport = p_context->m_golExport;
	championParams.m_renderer = p_context->m_renderer;
	championParams.m_entryCapacity = m_roster.m_racerCount;
	championParams.m_fileName = g_racerDatabaseNames[1];
	championParams.m_binary = p_binary;
	m_championList.FUN_0041d370(&championParams);

	ChassisModelTable::Params chassisParams;
	chassisParams.m_golExport = p_context->m_golExport;
	chassisParams.m_renderer = p_context->m_renderer;
	chassisParams.m_instantiateCount = m_roster.m_racerCount;
	chassisParams.m_filename = g_racerDatabaseNames[2];
	chassisParams.m_binary = p_binary;
	m_chassisTable.FUN_0041db10(&chassisParams);

	for (LegoU32 i = 0; i < m_roster.m_racerCount; i++) {
		p_context->m_routeRecord = p_params->m_racerRoutes[i];
		CreateRacer(p_params->m_slots[i], p_context, i, p_params->m_unk0x3c);
	}

	m_chassisTable.FUN_0041dae0();
	m_championList.ClearDefinitions();
	m_driverTable.ClearEntries();
	m_setup.m_textureList->LoadTextures();
	m_setup.m_materialLibrary->FUN_10026970();
	m_setup.Initialize(m_roster.m_racers, m_roster.m_racerCount);
}

// STUB: LEGORACERS 0x0043b480
void RaceState::CreateRacer(
	LegoRacers::Context::PlayerSetupSlot* p_slot,
	RacerContext* p_context,
	LegoU32 p_racerIndex,
	undefined4 p_unk0x10
)
{
	Racer::SetupParams racerParams;
	Racer::CarVisuals::InitParams initParams;
	::memset(&racerParams, 0, sizeof(racerParams));
	::memset(&initParams, 0, sizeof(initParams));

	ChampionDefinitionList::ChampionDefinition* championDefinition = NULL;
	ChassisModelTable::Item* chassisItem;
	if (p_slot->m_driverName[0]) {
		DriverCosmeticTable::Entry* driverEntry =
			static_cast<DriverCosmeticTable::Entry*>(m_driverTable.GetName(p_slot->m_driverName));

		initParams.m_driverEntity = m_driverTable.LoadEntry(p_slot->m_driverName);
		championDefinition = static_cast<ChampionDefinitionList::ChampionDefinition*>(
			m_championList.GetName(driverEntry->m_championName)
		);
		initParams.m_bodyModel = m_championList.FUN_0041d780(driverEntry->m_championName);
		chassisItem = static_cast<ChassisModelTable::Item*>(m_chassisTable.GetName(championDefinition->m_chassisName));
		m_chassisTable.InstantiateModels(chassisItem, &initParams.m_carEntity, &initParams.m_secondaryModel);

		racerParams.m_handlingStat = chassisItem->m_handlingStat;
		racerParams.m_accelerationStat = chassisItem->m_accelerationStat;
		racerParams.m_topSpeedStat = chassisItem->m_topSpeedStat;
		racerParams.m_driverStats[0] = driverEntry->m_redStat;
		racerParams.m_driverStats[1] = driverEntry->m_yellowStat;
		racerParams.m_driverStats[2] = driverEntry->m_greenStat;
		racerParams.m_driverStats[3] = driverEntry->m_blueStat;
		racerParams.m_driverStats[4] = driverEntry->m_stat4;
		racerParams.m_driverStats[5] = driverEntry->m_stat5;
		racerParams.m_voiceBank = driverEntry->m_voiceBankIndex * 12 + 1100;

		switch (driverEntry->m_aiChargeColor) {
		case 1:
		case 2:
		case 3:
		case 4:
			racerParams.m_aiChargeColor = driverEntry->m_aiChargeColor;
			break;
		default:
			racerParams.m_aiChargeColor = 0;
			break;
		}

		racerParams.m_aiChargeTarget = driverEntry->m_aiChargeTarget;
		racerParams.m_displayNameWide = m_driverTable.GetStringBuffer(p_slot->m_driverName);
	}
	else {
		LegoU32 customIndex = m_roster.m_customCarCount;
		m_roster.m_customCarModels[customIndex] = new GolModelEntity;
		if (m_roster.m_customCarModels[customIndex] == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_roster.m_customCarEntities[customIndex] = new GolAnimatedEntity;
		if (m_roster.m_customCarEntities[customIndex] == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		p_slot->m_textures->LoadTextures();
		p_slot->m_materials->FUN_10026970();
		initParams.m_bodyModel = m_roster.m_customCarModels[customIndex];
		initParams.m_bodyModel->VTable0x50(p_slot->m_model, g_carModelScale);

		if (p_slot->m_altModel == NULL) {
			LegoChar fallbackName[3];
			fallbackName[0] = 'b';
			fallbackName[1] = 'b';
			fallbackName[2] = '\0';
			m_driverTable.GetName(fallbackName);
			initParams.m_driverEntity = m_driverTable.LoadEntry(fallbackName);
		}
		else {
			p_slot->m_altTextures->LoadTextures();
			p_slot->m_altMaterials->FUN_10026970();
			initParams.m_driverEntity = m_roster.m_customCarEntities[customIndex];
			initParams.m_driverEntity->FUN_0040d550(
				p_slot->m_altModel,
				m_driverTable.m_rootNode,
				&m_driverTable.m_modelParts,
				g_carModelScale
			);
		}

		chassisItem = static_cast<ChassisModelTable::Item*>(m_chassisTable.GetName(p_slot->m_chassisName));
		m_chassisTable.InstantiateModels(chassisItem, &initParams.m_carEntity, &initParams.m_secondaryModel);
		racerParams.m_handlingStat = chassisItem->m_handlingStat;
		racerParams.m_accelerationStat = chassisItem->m_accelerationStat;
		racerParams.m_topSpeedStat = chassisItem->m_topSpeedStat;

		for (LegoU32 i = 0; i < sizeOfArray(racerParams.m_driverStats); i++) {
			racerParams.m_driverStats[i] = 100;
		}

		racerParams.m_voiceBank = p_racerIndex * 100 + 1000;
		::strcpy(racerParams.m_displayName, p_slot->m_playerName);
		m_roster.m_customCarCount = customIndex + 1;
	}

	initParams.m_driverMountOffset = chassisItem->m_driverMountOffset;
	initParams.m_racer = &m_roster.m_racers[p_racerIndex];
	initParams.m_shadowWidth = chassisItem->m_shadowSize.m_x;
	initParams.m_shadowLength = chassisItem->m_shadowSize.m_y;
	initParams.m_frontSkidWidth = chassisItem->m_skidWidths.m_x;
	initParams.m_rearSkidWidth = chassisItem->m_skidWidths.m_y;
	::strncpy(initParams.m_materialName, "carshad", sizeof(initParams.m_materialName));
	initParams.m_materialName[sizeof(initParams.m_materialName) - 1] = static_cast<LegoChar>('0' + p_racerIndex);

	for (LegoU32 i = 0; i < sizeOfArray(initParams.m_wheelOffsets); i++) {
		initParams.m_wheelOffsets[i] = chassisItem->m_wheelOffsets[i];
	}

	racerParams.m_anchorWheelPosition = chassisItem->m_wheelPositions[1];
	racerParams.m_rearWheelY0 = chassisItem->m_wheelPositions[2].m_y;
	racerParams.m_rearWheelX = chassisItem->m_wheelPositions[3].m_x;
	racerParams.m_rearWheelY1 = chassisItem->m_wheelPositions[3].m_y;

	racerParams.m_lapCount = m_setup.m_lapCount;
	racerParams.m_eventTable = p_context->m_eventTable;
	racerParams.m_unk0x64 = p_context->m_unk0x2c;
	racerParams.m_trackWorld = p_context->m_trackWorld;
	racerParams.m_enginePitchScale = chassisItem->m_enginePitchScale;

	if (championDefinition) {
		racerParams.m_centerOfMass.m_x = championDefinition->m_centerOfMassX;
		racerParams.m_centerOfMass.m_y = championDefinition->m_centerOfMassY;
		racerParams.m_centerOfMass.m_z = championDefinition->m_centerOfMassZ;
		racerParams.m_mass = championDefinition->m_mass;
		racerParams.m_weight = 0.0f;
	}
	else {
		racerParams.m_centerOfMass.m_x =
			p_slot->m_unk0x18 * g_carBuildModelTextureCoordinateScale + chassisItem->m_centerOfMass.m_x;
		racerParams.m_centerOfMass.m_y =
			p_slot->m_unk0x1c * g_carBuildModelTextureCoordinateScale + chassisItem->m_centerOfMass.m_y;
		racerParams.m_centerOfMass.m_z = chassisItem->m_centerOfMass.m_z;
		racerParams.m_mass = chassisItem->m_baseMass + p_slot->m_unk0x14;
		racerParams.m_weight = p_slot->m_unk0x14;
	}

	m_roster.m_placementSlots[p_racerIndex] = p_racerIndex;
	if (m_roster.m_timeRaceManager) {
		if (m_roster.m_timeRaceManager->HasRecordRunLapTimes()) {
			m_roster.m_placementSlots[p_racerIndex] = 2;
		}
		else {
			m_roster.m_placementSlots[p_racerIndex] = 1;
		}
	}
	else if (p_unk0x10 && p_racerIndex == 0) {
		m_roster.m_placementSlots[0] = 2;
	}

	LegoU32 placementIndex = m_roster.m_placementSlots[p_racerIndex];
	initParams.m_carEntity->VTable0x08(m_roster.m_startPositions[placementIndex]);
	initParams.m_carEntity->VTable0x40(m_roster.m_startDirections[placementIndex], m_roster.m_startUps[placementIndex]);

	m_roster.m_racers[p_racerIndex].Initialize(p_context, &initParams, &racerParams, this, p_racerIndex);

	PurpleDune0x7c* shadowTexture = m_setup.m_textureList->GetItem(p_racerIndex);
	DuskwindBananaRelic0x24* shadowMaterial = m_setup.m_materialLibrary->GetItem(p_racerIndex);
	shadowTexture->SetNameFromBuffer(chassisItem->m_shadowName);
	shadowTexture->SetTextureFlags(GoldDune0x38::c_unk0x36Bit2 | GoldDune0x38::c_unk0x36Bit3);
	shadowMaterial->SetName(chassisItem->m_shadowName);

	DuskWindBananaRelicParams shadowMaterialParams;
	::memset(&shadowMaterialParams, 0, sizeof(shadowMaterialParams));
	shadowMaterialParams.m_unk0x00 =
		DuskwindBananaRelic0x24::c_flag0x08Bit2 | DuskwindBananaRelic0x24::c_flag0x08Bit3 |
		DuskwindBananaRelic0x24::c_flag0x08Bit5 | DuskwindBananaRelic0x24::c_flag0x08Bit7 |
		DuskwindBananaRelic0x24::c_flag0x08Bit9 | DuskwindBananaRelic0x24::c_flag0x08Bit10 |
		DuskwindBananaRelic0x24::c_flag0x08Bit13 | DuskwindBananaRelic0x24::c_flag0x08Bit15 |
		DuskwindBananaRelic0x24::c_flag0x08Bit20 | DuskwindBananaRelic0x24::c_flag0x08Bit22;
	shadowMaterialParams.m_unk0x04 = shadowTexture;
	shadowMaterial->FUN_100257e0(p_context->m_renderer, shadowMaterialParams);

	Racer* racer = &m_roster.m_racers[p_racerIndex];
	racer->m_driveController.m_previewCursor = &m_sharedRouteCursor;

	LegoEventQueue::Descriptor descriptor;
	descriptor.m_unk0x00 = 3;
	descriptor.m_unk0x04 = 5;
	descriptor.m_unk0x08 = 0;
	descriptor.m_unk0x0c = 0;
	descriptor.m_data = &racer->m_physics;
	descriptor.m_unk0x14 = 0;
	m_roster.m_unk0x064[p_racerIndex] = m_roster.FUN_0042fb50(racer, &descriptor);
}

// FUNCTION: LEGORACERS 0x0043bc10
void RaceState::LoadStartPositions(const LegoChar* p_name, LegoBool32 p_binary, LegoBool32 p_mirror)
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
	parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(SpbTxtParser::e_startPosition));
	LegoU32 count = parser->ReadBracketedCountAndLeftCurly();

	if (count > 0) {
		LegoU32 remaining = count;
		do {
			parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(SpbTxtParser::e_startPosition));
			LegoU32 index = parser->ReadInteger();
			parser->ReadLeftCurly();

			GolFileParser::ParserTokenType token = parser->GetNextToken();
			while (token != GolFileParser::e_rightCurly) {
				switch (token) {
				case SpbTxtParser::e_position:
					m_roster.m_startPositions[index].m_x = parser->ReadFloat();
					m_roster.m_startPositions[index].m_y = parser->ReadFloat();
					m_roster.m_startPositions[index].m_z = parser->ReadFloat();
					if (p_mirror) {
						m_roster.m_startPositions[index].m_y = -m_roster.m_startPositions[index].m_y;
					}
					break;
				case SpbTxtParser::e_orientation:
					m_roster.m_startDirections[index].m_x = parser->ReadFloat();
					m_roster.m_startDirections[index].m_y = parser->ReadFloat();
					m_roster.m_startDirections[index].m_z = parser->ReadFloat();
					m_roster.m_startUps[index].m_x = parser->ReadFloat();
					m_roster.m_startUps[index].m_y = parser->ReadFloat();
					m_roster.m_startUps[index].m_z = parser->ReadFloat();
					if (p_mirror) {
						m_roster.m_startDirections[index].m_y = -m_roster.m_startDirections[index].m_y;
						m_roster.m_startUps[index].m_y = -m_roster.m_startUps[index].m_y;
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
void RaceState::InitializeRacerVisuals(GolD3DRenderDevice* p_renderer, GolExport* p_golExport)
{
	for (LegoU32 i = 0; i < m_roster.m_racerCount; i++) {
		m_roster.m_racers[i].m_visuals.InitializeVisuals(p_renderer, p_golExport);
	}
}

// FUNCTION: LEGORACERS 0x0043beb0
void RaceState::RecordBestTimes(LegoRacers::Context* p_context)
{
	LegoU32 bestLapTime = c_invalidTime;
	LegoU32 bestRaceTime = c_invalidTime;
	LegoU32 bestRacerIndex = c_invalidTime;
	LegoU32 racerCount = m_roster.m_racerCount;

	if (racerCount > 0) {
		LegoU32 racerIndex;

		racerIndex = 0;
		do {
			if (!p_context->m_playerSetupSlots[racerIndex].m_unk0x10) {
				Racer* racer = &m_roster.m_racers[racerIndex];
				LegoU32 lapCount = m_setup.m_lapCount;
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
void RaceState::DrawRacersTransparent(GolD3DRenderDevice* p_renderer)
{
	for (LegoU32 i = 0; i < m_roster.m_racerCount; i++) {
		m_roster.m_racers[i].m_visuals.DrawTransparent(p_renderer);
	}
}

// FUNCTION: LEGORACERS 0x0043c030
void RaceState::UpdateRacers(LegoU32 p_elapsedMs)
{
	Racer* racer = m_roster.m_racers;
	Racer* end = racer + m_roster.m_racerCount;

	for (; racer < end; racer++) {
		if (racer->m_driveController.m_flags & Racer::DriveController::c_flagBrakeToStop) {
			racer->m_driveController.UpdateBrakeToStop(p_elapsedMs);
		}
		else {
			if (racer->m_controlMode != 2) {
				racer->m_driveController.Update(p_elapsedMs);
			}
			else if (racer->m_driveController.m_flags & Racer::DriveController::c_flagReturnToPath) {
				racer->m_driveController.UpdateReturnToPath(p_elapsedMs);
			}
		}
	}

	for (racer = m_roster.m_racers; racer < end; racer++) {
		racer->m_physics.Update(p_elapsedMs);
	}

	for (racer = m_roster.m_racers; racer < end; racer++) {
		if (racer->m_flags & Racer::c_flagDrifting) {
			racer->UpdateDriftLean();
		}
	}

	RaceRoster* queue = &m_roster;
	queue->VTable0x10(p_elapsedMs);

	for (racer = m_roster.m_racers; racer < end; racer++) {
		racer->UpdateCarAnimation(p_elapsedMs);
	}

	for (racer = m_roster.m_racers; racer < end; racer++) {
		racer->UpdateEngineSound(p_elapsedMs);
		racer->UpdateSpatialSounds();
	}

	for (racer = m_roster.m_racers; racer < end; racer++) {
		racer->UpdateTimers(p_elapsedMs);
	}

	UpdateStandings();
	m_setup.Update(p_elapsedMs);
}

// STUB: LEGORACERS 0x0043c1b0
void RaceState::UpdateStandings()
{
	RacerProgressEntry* entries = g_racerProgressEntries;
	LegoU32 racerCount = m_roster.m_racerCount;

	LegoU32 racerIndex;
	for (racerIndex = 0; racerIndex < racerCount; racerIndex++) {
		Racer* racer = &m_roster.m_racers[racerIndex];
		entries[racerIndex].m_racer = racer;
		entries[racerIndex].m_progress = racer->GetRaceProgress();
	}

	LegoU32 sortIndex;
	for (sortIndex = 0; sortIndex + 1 < racerCount; sortIndex++) {
		LegoU32 minIndex = sortIndex;
		LegoFloat minProgress = entries[sortIndex].m_progress;

		LegoU32 scanIndex;
		for (scanIndex = sortIndex + 1; scanIndex < racerCount; scanIndex++) {
			if (minProgress > entries[scanIndex].m_progress) {
				minProgress = entries[scanIndex].m_progress;
				minIndex = scanIndex;
			}
		}

		if (minIndex > sortIndex) {
			LegoFloat progress = entries[sortIndex].m_progress;
			entries[sortIndex].m_progress = entries[minIndex].m_progress;
			entries[minIndex].m_progress = progress;

			Racer* racer = entries[sortIndex].m_racer;
			entries[sortIndex].m_racer = entries[minIndex].m_racer;
			entries[minIndex].m_racer = racer;
		}
	}

	LegoU32 groupStart;
	for (groupStart = 0; groupStart + 1 < racerCount;) {
		LegoU32 groupEnd = groupStart + 1;
		while (groupEnd < racerCount && entries[groupStart].m_progress == entries[groupEnd].m_progress) {
			groupEnd++;
		}

		CheckpointGraph::Entry* pathField = entries[groupStart].m_racer->m_checkpoint;
		if (groupEnd > groupStart + 1 && pathField) {
			LegoU32 tiedIndex;
			for (tiedIndex = groupStart; tiedIndex < groupEnd; tiedIndex++) {
				GolVec3 position;
				entries[tiedIndex].m_racer->m_visuals.m_carEntity->VTable0x04(&position);

				LegoFloat nearestPlaneDistance = FLT_MAX;
				LegoU32 planeIndex;
				for (planeIndex = 0; planeIndex < sizeOfArray(pathField->m_next.m_items); planeIndex++) {
					if (pathField->m_next.m_items[planeIndex] != 0xff) {
						CheckpointGraph::Entry* plane =
							m_roster.m_field0x010->GetCheckpoint(pathField->m_next.m_items[planeIndex]);
						LegoFloat distance = plane->m_planeNormal.m_x * position.m_x +
											 plane->m_planeNormal.m_y * position.m_y +
											 plane->m_planeNormal.m_z * position.m_z + plane->m_planeDistance;
						if (distance < nearestPlaneDistance) {
							nearestPlaneDistance = distance;
						}
					}
				}

				entries[tiedIndex].m_tieBreakDistance = nearestPlaneDistance;
			}

			LegoU32 tiedSortIndex;
			for (tiedSortIndex = groupStart; tiedSortIndex + 1 < groupEnd; tiedSortIndex++) {
				LegoU32 maxIndex = tiedSortIndex;
				LegoFloat maxDistance = entries[tiedSortIndex].m_tieBreakDistance;

				LegoU32 tiedScanIndex;
				for (tiedScanIndex = tiedSortIndex + 1; tiedScanIndex < groupEnd; tiedScanIndex++) {
					if (maxDistance < entries[tiedScanIndex].m_tieBreakDistance) {
						maxDistance = entries[tiedScanIndex].m_tieBreakDistance;
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
		if (!(entries[rankIndex].m_racer->m_flags & Racer::c_flagFinished)) {
			entries[rankIndex].m_racer->SetStandingsPosition(racerCount - rankIndex);
		}
	}

	SpatialSoundInstance* sound = m_roster.m_proximitySound;
	Racer* trackedRacer = m_roster.m_racer080;
	if (sound && trackedRacer) {
		GolVec3 trackedPosition;
		trackedRacer->m_visuals.m_carEntity->VTable0x04(&trackedPosition);

		Racer* nearestRacer = NULL;
		LegoFloat nearestDistanceSquared = FLT_MAX;
		LegoU32 nearestIndex;
		for (nearestIndex = 0; nearestIndex < racerCount; nearestIndex++) {
			Racer* racer = &m_roster.m_racers[nearestIndex];
			if (racer != trackedRacer) {
				GolVec3 position;
				racer->m_visuals.m_carEntity->VTable0x04(&position);

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

		if (nearestDistanceSquared >= g_proximitySoundMaxDistance * g_proximitySoundMaxDistance) {
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
			nearestRacer->m_visuals.m_carEntity->VTable0x04(&position);
			sound->SetPosition(position);

			GolVec3 velocity = nearestRacer->m_physics.m_velocity;
			velocity.m_x *= 2.0f;
			velocity.m_y *= 2.0f;
			velocity.m_z *= 2.0f;
			sound->SetVelocity(velocity);

			LegoFloat frequencyScale = nearestRacer->m_physics.m_speed / g_proximityPitchSpeedRange;
			frequencyScale *= 1.0f - g_proximityPitchFloor - g_proximityPitchBand;
			frequencyScale *= nearestRacer->m_enginePitchScale;
			frequencyScale += g_proximityPitchFloor;

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
void RaceState::UpdateShadows(GolCamera* p_camera)
{
	LegoU32 i = 0;
	if (i < m_roster.m_racerCount) {
		do {
			m_roster.m_racers[i].m_visuals.UpdateShadow(p_camera);
			i++;
		} while (i < m_roster.m_racerCount);
	}
}

// FUNCTION: LEGORACERS 0x0043ccb0
void RaceState::StartRace()
{
	for (LegoU32 i = 0; i < m_roster.m_racerCount; i++) {
		m_roster.m_racers[i].OnRaceStart();
	}

	SpatialSoundInstance* sound = m_roster.m_soundSource->AcquireSoundById(0x4f);
	m_roster.m_proximitySound = sound;
	if (sound) {
		LegoFloat maxDistance = g_proximitySoundMaxDistance;
		sound->m_minDistanceSquared = g_proximitySoundMinDistance * g_proximitySoundMinDistance;
		sound->m_maxDistanceSquared = maxDistance * maxDistance;
		m_roster.m_proximitySound->SetVolume(0.8f);
	}
}

// FUNCTION: LEGORACERS 0x0043cd30
void RaceState::DrawRacerEntities(GolRenderDevice* p_renderer, Racer* p_racer)
{
	for (LegoU32 i = 0; i < m_roster.m_racerCount; i++) {
		if (p_racer != &m_roster.m_racers[i] || p_racer->m_cameraViewIndex != 3 ||
			(p_racer->m_flags & Racer::c_flagFinished) || !(p_racer->m_flags & Racer::c_flagEngineSounds)) {
			m_roster.m_racers[i].m_visuals.m_entityGroup.VTable0x1c(*p_renderer);
		}
	}
}

// FUNCTION: LEGORACERS 0x0043d120
void RaceState::StopProximitySound()
{
	RaceResourceManager::Resource* resource = m_roster.m_proximitySoundResource;
	if (resource) {
		m_roster.m_unk0x05c->ReleaseSound(resource);
		m_roster.m_proximitySoundResource = NULL;
	}
}
