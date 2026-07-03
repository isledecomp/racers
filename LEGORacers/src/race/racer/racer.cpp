#include "audio/soundnode.h"
#include "audio/spatialsoundinstance.h"
#include "audio/streamingsoundinstance.h"
#include "camera/golcamera.h"
#include "cmbmodelpart.h"
#include "golbinparser.h"
#include "golerror.h"
#include "golmaterial.h"
#include "golmateriallibrary.h"
#include "material/goltexturelist.h"
#include "menu/runtime/cutsceneparticle.h"
#include "menu/runtime/cutsceneplayer.h"
#include "race/racecameracontroller.h"
#include "race/raceeventtable.h"
#include "race/raceforcefeedback.h"
#include "race/racehud.h"
#include "race/racesession.h"
#include "race/timeracemanager.h"
#include "render/gold3drenderdevice.h"
#include "surface/gold3dtexture.h"
#include "util/carshadowrenderstate.h"

#include <float.h>
#include <math.h>
#include <string.h>

extern LegoU16 g_randomTable[1024];
extern LegoU32 g_randomTableIndex;
extern LegoFloat g_carBuildPreviewMouseScale;
extern const LegoFloat g_carBuildModelTextureCoordinateScale;
extern LegoFloat g_minSoundPan;

DECOMP_SIZE_ASSERT(RaceState, 0x320)
DECOMP_SIZE_ASSERT(Racer, 0xe34)
DECOMP_SIZE_ASSERT(RaceEventRecord, 0x20)
DECOMP_SIZE_ASSERT(RaceEventRecord::Target, 0x5c)
DECOMP_SIZE_ASSERT(RaceState::RacerProgressEntry, 0x0c)
DECOMP_SIZE_ASSERT(Racer::SetupParams, 0x88)
DECOMP_SIZE_ASSERT(CarVisuals, 0x3d0)
DECOMP_SIZE_ASSERT(CarVisuals::InitParams, 0x68)
DECOMP_SIZE_ASSERT(RacerRigidBody, 0xd0)
DECOMP_SIZE_ASSERT(RacerBoxBody, 0xe4)
DECOMP_SIZE_ASSERT(RacerCarBody, 0x74c)
DECOMP_SIZE_ASSERT(RacerPhysics, 0x888)
DECOMP_SIZE_ASSERT(DriveController, 0x54)
DECOMP_SIZE_ASSERT(RaceRoster, 0x194)
DECOMP_SIZE_ASSERT(RaceSetup, 0x1c)

extern const LegoFloat g_ghostAnimationRateScale;
extern const LegoFloat g_ghostSampleFractionScale;
extern const LegoFloat g_sweepCannonRadiansToTableIndex;
extern const LegoFloat g_negativeRadiansToTableIndex;
extern const LegoFloat g_violetShoalTwo;
extern LegoU32 g_silhouetteClearFlag;
extern LegoU32 g_silhouetteFlattenFlag;
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
extern const LegoFloat g_lookTargetRangeSquared = 40000.0f;

// GLOBAL: LEGORACERS 0x004b0b28
extern const LegoFloat g_pitchLeanRate = 30.0f;

// GLOBAL: LEGORACERS 0x004b0b2c
extern const LegoFloat g_rollLeanRate = 100.0f;

// GLOBAL: LEGORACERS 0x004b0b30
extern const LegoFloat g_pitchLeanDamping = 0.0099999998f;

// GLOBAL: LEGORACERS 0x004b0b34
extern const LegoFloat g_rollLeanDamping = 0.029999999f;

// GLOBAL: LEGORACERS 0x004b0b38
extern const LegoFloat g_shadowFadeNearSquared = 2500.0f;

// GLOBAL: LEGORACERS 0x004b0b3c
extern const LegoFloat g_shadowFadeFarSquared = 10000.0f;

// GLOBAL: LEGORACERS 0x004b0b40
extern const LegoFloat g_lookAtDotBehind = -0.60000002f;

// GLOBAL: LEGORACERS 0x004b0b44
extern const LegoFloat g_lookAtDotBeside = -0.2f;

// GLOBAL: LEGORACERS 0x004b0b4c
extern const LegoFloat g_fadeAlphaScale = 191.0f;

// GLOBAL: LEGORACERS 0x004b0b50
extern const LegoFloat g_carShadowScale = 1.15f;

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
Racer::Racer()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00436a20
Racer::~Racer()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00436aa0
void Racer::Destroy()
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
		m_soundSource->ReleaseSound(m_engineIdleSound);
		m_engineIdleSound = NULL;
	}

	if (m_engineDriveSound) {
		m_soundSource->ReleaseSound(m_engineDriveSound);
		m_engineDriveSound = NULL;
	}

	if (m_engineFastSound) {
		m_soundSource->ReleaseSound(m_engineFastSound);
		m_engineFastSound = NULL;
	}

	if (m_brakeSound) {
		m_soundSource->ReleaseSound(m_brakeSound);
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
void Racer::Reset()
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
	m_controlMode = c_controlAi;
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

	DroppableBrick* brick = NULL;
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
	m_hud = NULL;
	m_checkpointCount = 0xffffffff;
	m_unk0xdb0 = 0;
	m_whiteBrickCount = 0;
	m_whiteBricks[0] = brick;
	m_whiteBricks[1] = brick;
	m_whiteBricks[2] = brick;
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
void Racer::Initialize(
	RacerContext* p_context,
	CarVisuals::InitParams* p_visualsParams,
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
	m_standingsPosition = p_racerIndex + 1;
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

	LegoS32 aggressionScore = m_aiBlueUseChance;
	aggressionScore = m_aiYellowUseChance - aggressionScore;
	aggressionScore -= m_aiGreenUseChance;
	aggressionScore += m_aiRedUseChance;
	if (aggressionScore < 0) {
		m_aiAggression = 0;
	}
	else {
		LegoFloat aggressionScaled = static_cast<LegoFloat>(aggressionScore);
		aggressionScaled *= g_aiAggressionScale;
		aggressionScaled *= g_aiAggressionRange;
		m_aiAggression = static_cast<LegoU8>(aggressionScaled);
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

	m_visuals.Initialize(p_visualsParams, p_context);
	InitializePhysics(p_context, p_params);
	ResetRaceProgress();
}

// FUNCTION: LEGORACERS 0x004371c0
void Racer::InitializePhysics(RacerContext* p_context, SetupParams* p_params)
{
	RaceEventTable* eventTable;
	void* surfaceTable;
	GolBoundedEntity* trackWorld;
	GolBoundedEntity* triggerWorld;
	if (p_context) {
		eventTable = p_context->m_eventTable;
		surfaceTable = p_context->m_surfaceTable;
		trackWorld = p_context->m_trackWorld;
		triggerWorld = p_context->m_triggerWorld;
	}
	else {
		eventTable = m_physics.m_eventTable;
		surfaceTable = m_physics.m_surfaceTable;
		trackWorld = m_physics.m_collisionWorlds[0];
		triggerWorld = m_physics.m_triggerCollidable;
	}

	GolVec3 position;
	GolVec3 vector;
	LegoFloat deltaX;
	LegoFloat deltaY;
	LegoFloat mass;
	LegoU32 handlingStat;
	LegoU32 topSpeedStat;
	LegoU32 accelerationStat;
	if (p_params) {
		deltaY = p_params->m_rearWheelY1 - p_params->m_rearWheelY0;
		mass = p_params->m_mass;
		memcpy(&position, &p_params->m_centerOfMass, sizeof(position));

		deltaX = p_params->m_anchorWheelPosition.m_x - p_params->m_rearWheelX;
		topSpeedStat = p_params->m_topSpeedStat;
		LegoFloat valueFloat = p_params->m_weight;
		accelerationStat = p_params->m_accelerationStat;
		memcpy(&vector, &p_params->m_anchorWheelPosition, sizeof(vector));
		valueFloat *= g_unk0x004b0544;

		LegoU32 value = static_cast<LegoU32>(valueFloat);
		handlingStat = p_params->m_handlingStat + value;
		if (handlingStat > 100) {
			handlingStat = 100;
		}

		topSpeedStat += value;
		if (topSpeedStat > 100) {
			topSpeedStat = 100;
		}

		if (value > p_params->m_accelerationStat) {
			accelerationStat = 0;
		}
		else {
			accelerationStat = p_params->m_accelerationStat - value;
		}
	}
	else {
		mass = m_physics.m_mass;
		handlingStat = m_physics.m_handlingStat;
		memcpy(&position, &m_physics.m_centerOfMassLocal, sizeof(position));
		topSpeedStat = m_physics.m_topSpeedStat;
		memcpy(&vector, &m_physics.m_anchorWheelOffset, sizeof(vector));
		deltaY = m_physics.m_trackWidth;
		deltaX = m_physics.m_wheelbase;
		accelerationStat = m_physics.m_accelerationStat;
	}

	RacerPhysics* physics = &m_physics;
	physics->Initialize(
		this,
		eventTable,
		surfaceTable,
		m_visuals.m_carEntity,
		trackWorld,
		triggerWorld,
		m_soundSource,
		mass,
		8.0f,
		5.0f,
		6.2f
	);
	m_physics.m_soundsEnabled = 0;
	m_physics.m_racer = this;

	if (m_flags & c_flagCheatNslwj) {
		physics->m_flags |= RacerPhysics::c_flagIgnoreSurfaces;
	}

	physics->SetHandlingStat(handlingStat);
	physics->SetAccelerationStat(accelerationStat);
	physics->SetTopSpeedStat(topSpeedStat);

	LegoFloat halfHeight = m_visuals.m_shadowWidth;
	halfHeight *= 0.5f;
	LegoFloat halfWidth = m_visuals.m_shadowLength;
	halfWidth *= 0.5f;
	physics->SetCenterOfMass(&position);
	physics->SetWheelGeometry(&vector, deltaY, deltaX);

	GolVec3 corner;
	corner.m_x = halfWidth;
	corner.m_y = -halfHeight;
	corner.m_z = g_bodyPointZ;
	physics->SetBodyPoint(0, &corner);

	corner.m_x = halfWidth;
	corner.m_y = halfHeight;
	corner.m_z = g_bodyPointZ;
	physics->SetBodyPoint(1, &corner);

	corner.m_x = -halfWidth;
	corner.m_y = -halfHeight;
	corner.m_z = g_bodyPointZ;
	physics->SetBodyPoint(2, &corner);

	corner.m_x = -halfWidth;
	corner.m_y = halfHeight;
	corner.m_z = g_bodyPointZ;
	physics->SetBodyPoint(3, &corner);

	m_driveController.Initialize(physics);
}

// FUNCTION: LEGORACERS 0x004374c0
void Racer::ResetRaceProgress()
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
void Racer::InitializeSounds(RaceCameraController* p_cameraController, LegoBool32 p_state)
{
	m_controlMode = p_state;
	m_cameraController = p_cameraController;

	m_turboSoundL0 = m_soundSource->AcquireSoundById(c_soundTurboL0);
	if (m_turboSoundL0) {
		m_turboSoundL0->SetDistanceRangeWithMinSquared(
			g_shieldSoundMinDistance * g_shieldSoundMinDistance,
			g_shieldSoundMaxDistance
		);
	}

	m_turboSoundL1 = m_soundSource->AcquireSoundById(c_soundTurboL1);
	if (m_turboSoundL1) {
		m_turboSoundL1->SetDistanceRangeWithMinSquared(
			g_shieldSoundMinDistance * g_shieldSoundMinDistance,
			g_shieldSoundMaxDistance
		);
	}

	m_turboSoundL2 = m_soundSource->AcquireSoundById(c_soundTurboL2);
	if (m_turboSoundL2) {
		m_turboSoundL2->SetDistanceRangeWithMinSquared(
			g_shieldSoundMinDistance * g_shieldSoundMinDistance,
			g_shieldSoundMaxDistance
		);
	}

	m_ghostSound = m_soundSource->AcquireSoundById(c_soundGhost);
	if (m_ghostSound) {
		m_ghostSound->SetDistanceRangeWithMinSquared(
			g_shieldSoundMinDistance * g_shieldSoundMinDistance,
			g_shieldSoundMaxDistance
		);
	}

	m_engineIdleVolume = 0.0f;
	m_engineDriveVolume = 0.0f;
	m_engineFastVolume = 0.0f;

	m_engineIdleSound = m_soundSource->AcquireSoundById(c_soundEngineIdle);
	m_engineIdleSound->SetPriority(0xff);
	m_engineIdleSound->Play(TRUE);
	m_engineIdleSound->SetDistanceRangeWithMinSquared(
		g_shieldSoundMinDistance * g_shieldSoundMinDistance,
		g_shieldSoundMaxDistance
	);
	m_engineIdleSound->SetVolume(m_engineIdleVolume);

	m_activeEngineSound = 0;
	m_engineDriveSound = m_soundSource->AcquireSoundById(c_soundEngineDrive);
	m_engineDriveSound->SetDistanceRangeWithMinSquared(
		g_shieldSoundMinDistance * g_shieldSoundMinDistance,
		g_shieldSoundMaxDistance
	);
	m_engineDriveSound->SetPriority(0xff);
	m_engineDriveSound->SetVolume(m_engineDriveVolume);

	m_engineFastSound = m_soundSource->AcquireSoundById(c_soundEngineFast);
	m_engineFastSound->SetDistanceRangeWithMinSquared(
		g_shieldSoundMinDistance * g_shieldSoundMinDistance,
		g_shieldSoundMaxDistance
	);
	m_engineFastSound->SetPriority(0xff);
	m_engineFastSound->SetVolume(m_engineFastVolume);
}

// FUNCTION: LEGORACERS 0x00437740
void Racer::UpdateCarAnimation(LegoU32 p_elapsedMs)
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
	entity->SetMsPerFrame(speed);

	if (field->m_secondaryEntity) {
		field->m_secondaryEntity->SetMsPerFrame(speed);
	}

	field->Update(p_elapsedMs);
}

// FUNCTION: LEGORACERS 0x004377f0
void Racer::UpdateTimers(LegoU32 p_elapsedMs)
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

		if (m_controlMode == c_controlAi && m_heldPowerupColor) {
			AiConsiderPowerup();
		}
	}

	if ((m_physics.m_flags & RacerPhysics::c_flagSpinOut) && !m_physics.m_routeMode) {
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
	m_visuals.m_carEntity->GetPosition(&m_actionSource);
	m_visuals.m_carEntity->GetOrientationRow0(&m_actionSource.m_forward);
	GolVec3& velocity = m_actionSource.m_velocity;
	velocity = m_physics.m_velocity;

	if (!m_tauntCooldownMs && m_controlMode == c_controlAi) {
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
			m_forceFeedback->PlayScrapeRumble();
		}

		if (!m_scrapeSoundCooldownMs) {
			SoundVector position;
			m_visuals.m_carEntity->GetPosition(&position);

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
void Racer::UpdateDriftLean()
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
void Racer::UpdateSpatialSounds()
{
	for (LegoU32 i = 0; i <= 3; i++) {
		SpatialSoundInstance* resource = NULL;

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
				if (!resource->IsPlaying()) {
					resource->Play(TRUE);
				}

				GolVec3 position;
				m_visuals.m_carEntity->GetPosition(&position);
				resource->SetPosition(position);
				resource->SetVelocity(m_physics.m_velocity);
			}
			else if ((flags & c_flagGhost) && i == 3) {
				if (!resource->IsPlaying()) {
					resource->Play(TRUE);
				}
			}
			else if (resource->IsPlaying()) {
				resource->Stop();
			}
		}
	}

	if (m_curseSound) {
		GolVec3 position;
		m_visuals.m_curseEntity.GetPosition(&position);
		m_curseSound->SetPosition(position);
	}
}

// FUNCTION: LEGORACERS 0x00437d40
void Racer::UpdateEngineSound(LegoU32 p_elapsedMs)
{
	if (!(m_flags & c_flagEngineSounds) || !m_engineIdleSound) {
		return;
	}

	SoundVector position;
	m_visuals.m_carEntity->GetPosition(&position);

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

		m_soundSource->ReleaseSound(m_brakeSound);
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
void Racer::StopEngineSounds()
{
	if (m_controlMode != c_controlAi) {
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
void Racer::OnEvent(LegoEventQueue::CallbackData* p_data)
{
	if (p_data->m_type == LegoEventQueue::Descriptor::c_typeTimer) {
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

	if (p_data->m_type != 3) {
		return;
	}

	CollisionEventQueue::CollisionCallbackData* collision =
		static_cast<CollisionEventQueue::CollisionCallbackData*>(p_data->m_data);
	LegoEventQueue::Descriptor::RigidBody* firstTarget = p_data->m_target0;
	LegoEventQueue::Descriptor::RigidBody* secondTarget = collision->m_secondTarget;
	Racer* firstRacer = static_cast<Racer*>(firstTarget->m_owner);
	Racer* secondRacer = static_cast<Racer*>(secondTarget->m_owner);

	if (firstRacer->m_flags & c_flagGhost) {
		return;
	}

	if (secondRacer && (secondRacer->m_flags & c_flagGhost)) {
		return;
	}

	if (firstRacer->m_physics.m_flags & RacerPhysics::c_flagSpinOut) {
		return;
	}

	if (secondRacer && (secondRacer->m_physics.m_flags & RacerPhysics::c_flagSpinOut)) {
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
	firstContactOffset.m_x = firstTarget->m_centerOfMassWorld.m_x - collision->m_contactPoint.m_x;
	firstContactOffset.m_y = firstTarget->m_centerOfMassWorld.m_y - collision->m_contactPoint.m_y;
	firstContactOffset.m_z = firstTarget->m_centerOfMassWorld.m_z - collision->m_contactPoint.m_z;
	GolMath::NormalizeVector3(firstContactOffset, &firstContactOffset);

	GolVec3 secondContactOffset;
	secondContactOffset.m_x = secondTarget->m_centerOfMassWorld.m_x - collision->m_contactPoint.m_x;
	secondContactOffset.m_y = secondTarget->m_centerOfMassWorld.m_y - collision->m_contactPoint.m_y;
	secondContactOffset.m_z = secondTarget->m_centerOfMassWorld.m_z - collision->m_contactPoint.m_z;
	GolMath::NormalizeVector3(secondContactOffset, &secondContactOffset);

	GolVec3 firstAngularAxis;
	firstAngularAxis.m_x = firstContactOffset.m_y * collisionNormal.m_z - collisionNormal.m_y * firstContactOffset.m_z;
	firstAngularAxis.m_y = firstContactOffset.m_z * collisionNormal.m_x - collisionNormal.m_z * firstContactOffset.m_x;
	firstAngularAxis.m_z = firstContactOffset.m_x * collisionNormal.m_y - firstContactOffset.m_y * collisionNormal.m_x;

	const GolMatrix3& firstInertia = firstTarget->m_worldInverseInertia;
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

	const GolMatrix3& secondInertia = secondTarget->m_worldInverseInertia;
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
		firstRacer->m_forceFeedback->PlayLightRumble();
	}

	if (!secondRacer) {
		return;
	}

	secondRacer->m_physics.ApplyDirectionalImpulse(&collisionNormal, -impulseScale);
	if (secondRacer->m_forceFeedback) {
		secondRacer->m_forceFeedback->PlayLightRumble();
	}

	if (firstRacer->m_controlMode == Racer::c_controlAi && secondRacer->m_controlMode == Racer::c_controlAi) {
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

		m_visuals.m_particleAnimation->SpawnParticle("carsprk", &collision->m_contactPoint, NULL, NULL);

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
void Racer::ApplyShove(GolVec3* p_impulse)
{
	LegoEventQueue::Descriptor descriptor;
	if (m_flags & c_flagShoveActive) {
		return;
	}

	descriptor.m_flags = 0;
	descriptor.m_hitThreshold = 0;
	descriptor.m_type = LegoEventQueue::Descriptor::c_typeTimer;
	descriptor.m_maxFireCount = 1;
	descriptor.m_intervalMs = 750;
	if (m_raceState->GetRoster()->AllocateEvent(this, &descriptor) == NULL) {
		return;
	}

	m_physics.StartSteering(2.5f, 0.89999998f, 3.1415927f);
	LegoU32 flags = m_physics.m_flags;
	if (!(flags & RacerPhysics::c_flagExternalForce0)) {
		m_physics.StartExternalForce0(p_impulse);
		m_shoveForceSlot = 1;
	}
	else if (!(flags & RacerPhysics::c_flagExternalForce1)) {
		m_physics.StartExternalForce1(p_impulse);
		m_shoveForceSlot = 2;
	}

	m_flags |= c_flagShoveActive;
}

// FUNCTION: LEGORACERS 0x00438f20
void Racer::AiConsiderPowerup()
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
					if (m_physics.m_flags & RacerPhysics::c_flagSpinning) {
						return;
					}

					AiUsePowerup();
				}
				return;
			case 1: {
				GolVec3 position;
				m_visuals.m_carEntity->GetPosition(&position);

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
void Racer::AiUsePowerup()
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
LegoU32 Racer::CollectColorBrick(LegoU32 p_brickColor)
{
	m_aiPowerupCheckMs = 0;
	m_heldPowerupColor = p_brickColor;
	m_aiPowerupCheckIntervalMs = 300;
	return p_brickColor;
}

// FUNCTION: LEGORACERS 0x00439240
void Racer::PlayReaction(LegoBool32 p_positive)
{
	if (m_reactionCooldownMs <= 0) {
		SoundVector position;
		m_visuals.m_carEntity->GetPosition(&position);

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
void Racer::OnRaceStart()
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
void Racer::StartEngine()
{
	SoundVector position;
	m_visuals.m_carEntity->GetPosition(&position);

	m_soundSource->PlaySpatialSoundById(
		c_soundEngineStart,
		&position,
		g_shieldSoundMinDistance,
		g_shieldSoundMaxDistance,
		1.0f,
		1.0f
	);
	m_flags |= c_flagEngineSounds;
}

// FUNCTION: LEGORACERS 0x00439420
LegoBool32 Racer::CollectWhiteBrick(DroppableBrick* p_brick)
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
DroppableBrick* Racer::DropWhiteBrick()
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
			m_visuals.m_carEntity->GetPosition(&position);
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
LegoU32 Racer::ReturnAllWhiteBricks()
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
void Racer::Halt()
{
	LegoU32 flags = m_flags;
	if (!(flags & c_flagHalted)) {
		m_flags = flags | c_flagHalted;
		m_physics.EndSpin();
		m_physics.StartSliding();
	}
}

// FUNCTION: LEGORACERS 0x004395a0
void Racer::Resume()
{
	LegoU32 flags = m_flags;
	if (flags & c_flagHalted) {
		m_flags = flags & ~c_flagHalted;
		m_physics.StopSliding();
	}
}

// FUNCTION: LEGORACERS 0x004395d0
void Racer::EnterGhostMode()
{
	m_flags |= c_flagGhost;
	RemoveCurse();
	m_visuals.StopSkidEffects();
	m_visuals.HideModels();
	m_visuals.m_flags &= ~(CarVisuals::c_flagShadowEnabled | CarVisuals::c_flagShadowVisible);
	m_visuals.StopTurboEffects();
	m_visuals.StopSlideSkid();
	RacerPhysics* physics = &m_physics;
	physics->EndSpin();

	if (m_controlMode == c_controlAi && m_physics.m_routeMode) {
		physics->StartRouteGhost();
	}
	else {
		physics->m_flags |= RacerPhysics::c_flagNoTrackCollision;
	}

	if (m_forceFeedback) {
		m_forceFeedback->PlayTurboRumble(3);
	}
}

// FUNCTION: LEGORACERS 0x00439660
void Racer::LeaveGhostMode()
{
	m_flags &= ~c_flagGhost;

	CarVisuals* field = &m_visuals;
	field->ShowModels();

	if (m_controlMode == c_controlAi && m_physics.m_routeMode) {
		m_physics.EndRouteGhost();
		field->m_flags |= CarVisuals::c_flagShadowEnabled;
		return;
	}

	m_physics.m_flags &= ~RacerPhysics::c_flagNoTrackCollision;
	field->m_flags |= CarVisuals::c_flagShadowEnabled;
}

// FUNCTION: LEGORACERS 0x004396c0
void Racer::StartTurbo(LegoU32 p_level)
{
	m_flags |= c_flagTurbo;

	if (m_controlMode != c_controlAi) {
		m_visuals.StartTurboEffects();
	}

	m_driveController.m_flags =
		(m_driveController.m_flags & ~DriveController::c_flagTurboWeakened) | DriveController::c_flagTurbo;
	m_physics.SnapFacingDirection();
	m_physics.StartBoost();
	m_turboLevel = p_level;

	if (m_forceFeedback) {
		m_forceFeedback->PlayTurboRumble(p_level);
	}
}

// FUNCTION: LEGORACERS 0x00439730
void Racer::ClearActiveAction()
{
	m_flags &= ~c_flagTurbo;
	m_visuals.StopTurboEffects();
	m_driveController.m_flags &= ~(DriveController::c_flagTurbo | DriveController::c_flagTurboWeakened);
	m_physics.EndBoost();
}

// FUNCTION: LEGORACERS 0x00439770
LegoU32 Racer::StartShield(LegoU32 p_level)
{
	m_flags |= c_flagShielded;
	m_shieldLevel = p_level;
	return p_level;
}

// FUNCTION: LEGORACERS 0x00439790
void Racer::EndShield()
{
	m_flags &= ~c_flagShielded;
}

// FUNCTION: LEGORACERS 0x004397a0
void Racer::StartSpinOut()
{
	m_physics.StartSpinOut();
}

// FUNCTION: LEGORACERS 0x004397b0
void Racer::EndSpinOut()
{
	m_physics.EndSpinOut();
}

// FUNCTION: LEGORACERS 0x004397c0
void Racer::StartDrift(LegoBool32 p_left)
{
	if (!(m_flags & c_flagDrifting) || p_left != m_driveController.m_slideLeft) {
		m_driveController.EngageSlide(p_left);

		if (m_driveController.m_flags & DriveController::c_flagSliding) {
			m_flags |= c_flagDrifting;

			if (!m_controlMode && !(m_physics.m_flags & RacerPhysics::c_flagSliding)) {
				SoundVector position;
				m_visuals.StartDust();

				if (!(m_visuals.m_flags & CarVisuals::c_flagSkidding)) {
					m_visuals.StartSkidEffects();
				}

				m_visuals.m_carEntity->GetPosition(&position);
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
void Racer::EndDrift()
{
	SoundVector position;

	if (m_flags & c_flagDrifting) {
		if (m_driveController.m_flags & DriveController::c_flagSliding) {
			m_driveController.ReleaseSlide();
		}

		LegoU8 physicsFlags = static_cast<LegoU8>(m_physics.m_flags);
		LegoU8 testFlag = RacerPhysics::c_flagSliding;
		if (!(testFlag & physicsFlags)) {
			if (m_driveController.m_flags & DriveController::c_flagSlideBoost) {
				m_visuals.m_carEntity->GetPosition(&position);
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

		LegoU32 flags = m_flags;
		flags &= ~c_flagDrifting;
		m_flags = flags;
	}
}

// FUNCTION: LEGORACERS 0x00439900
void Racer::AttachCurse(GolAnimatedEntity* p_curseEntity, LegoU32 p_durationMs)
{
	LegoU32 flags = m_flags;
	m_curseTimerMs = p_durationMs;
	flags |= c_flagCursed;
	m_curseTickMs = 1000;
	m_flags = flags;

	LegoU32 controllerFlags = m_driveController.m_flags;
	controllerFlags |= DriveController::c_flagCursed;
	GolAnimatedEntity* entity = &m_visuals.m_curseEntity;
	m_driveController.m_flags = controllerFlags;

	LegoU32 reactionFlags = m_visuals.m_reactionFlags;
	reactionFlags |= CarVisuals::c_reactionHit;
	m_visuals.m_reactionFlags = reactionFlags;

	entity->SetModel(
		p_curseEntity->GetModel(0),
		p_curseEntity->GetSceneNode(0),
		p_curseEntity->GetModelPart(0),
		p_curseEntity->GetModelDistance(0)
	);

	for (LegoU32 i = 1; i < 3; i++) {
		if (p_curseEntity->GetModel(i)) {
			entity->AddModel(
				p_curseEntity->GetModel(i),
				p_curseEntity->GetSceneNode(i),
				p_curseEntity->GetModelPart(i),
				p_curseEntity->GetModelDistance(i)
			);
		}
	}

	entity->PlayPart(0);
	entity->SetPartAnimationEnabled(TRUE);
	entity->CopyOrientationFrom(*p_curseEntity);
	entity->CopyPositionFrom(*p_curseEntity);

	m_curseSound = m_soundSource->AcquireSoundById(8);
	if (m_curseSound) {
		m_curseSound->Play(TRUE);
		m_curseSound->SetDistanceRangeWithMinSquared(
			g_shieldSoundMinDistance * g_shieldSoundMinDistance,
			g_shieldSoundMaxDistance
		);

		GolVec3 position;
		p_curseEntity->GetPosition(&position);
		m_curseSound->SetPosition(position);
	}

	ColorTransform transform;
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
void Racer::RemoveCurse()
{
	if (m_curseSound) {
		m_soundSource->ReleaseSound(m_curseSound);
		m_curseSound = NULL;
	}

	LegoU32 flags = m_flags;
	m_curseTimerMs = 0;
	flags &= ~c_flagCursed;
	m_flags = flags;

	m_driveController.m_flags &= ~DriveController::c_flagCursed;
	m_visuals.m_curseEntity.ResetModelState();
	m_visuals.EndFlash();
	m_physics.EndCurseSlow();
}

// FUNCTION: LEGORACERS 0x00439b70
void Racer::EnterOpenTrack()
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
LegoU32 Racer::CrossFinishLine()
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
void Racer::EnterPostLineZone()
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
void Racer::ComputeStandingsDeltas(StandingsDeltaEntry* p_entries)
{
	m_raceState->ComputeStandingsDeltas(this, p_entries);
}

// FUNCTION: LEGORACERS 0x00439c90
void Racer::PlayTaunt()
{
	SoundVector position;
	m_visuals.m_carEntity->GetPosition(&position);

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
void Racer::UpdateFacing(LegoU32 p_elapsedMs)
{
	CheckpointGraph::Entry* checkpoint = m_checkpoint;
	if (checkpoint) {
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
		for (LegoU32 i = 0; i < sizeOfArray(checkpoint->m_next.m_items); i++) {
			if (isBlocked) {
				break;
			}

			if (checkpoint->m_next.m_items[i] != 0xff) {
				m_checkpointGraph->GetCheckpoint(checkpoint->m_next.m_items[i]);
				checkpoint = m_checkpoint;
				LegoFloat dot = direction.m_z * checkpoint->m_planeNormal.m_z +
								direction.m_y * checkpoint->m_planeNormal.m_y +
								direction.m_x * checkpoint->m_planeNormal.m_x;
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
void Racer::SetLookTarget(GolVec3* p_position)
{
	m_flags |= c_flagHasLookTarget;
	m_lookTargetPosition.m_x = p_position->m_x;
	m_lookTargetPosition.m_y = p_position->m_y;
	m_lookTargetPosition.m_z = p_position->m_z;
}

// FUNCTION: LEGORACERS 0x00439e90
void Racer::ClearLookTarget()
{
	m_flags &= ~c_flagHasLookTarget;
}

// FUNCTION: LEGORACERS 0x00439ea0
void Racer::UpdateLookTarget(LegoU32)
{
	LegoU32 flags = m_flags & ~(c_flagLookTargetLeft | c_flagLookTargetRight);
	m_flags = flags;

	if (m_flags & c_flagHasLookTarget) {
		GolVec3 direction = m_physics.m_facingDirection;
		GolVec3 position;
		m_visuals.m_carEntity->GetPosition(&position);

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
void Racer::OnCheckpointCrossed(CheckpointGraph::Entry* p_entry, GolBoundingVolume::HitTriangle* p_record)
{
	LegoBool32 isForward;
	if (p_record->m_normal.m_z * p_entry->m_planeNormal.m_z + p_record->m_normal.m_y * p_entry->m_planeNormal.m_y +
			p_record->m_normal.m_x * p_entry->m_planeNormal.m_x <
		0.0f) {
		isForward = FALSE;
	}
	else {
		isForward = TRUE;
	}

	if (p_entry != m_checkpoint || isForward != m_checkpointForward) {
		if (p_entry->m_lapFraction == 0.0f) {
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
				m_checkpoint = p_entry;
				return;
			}

			m_flags = flags & ~c_flagCrossedBackward;
		}
		else {
			LegoU32 flags = m_flags;
			if (!(flags & c_flagCrossedBackward)) {
				m_checkpoint = p_entry;
				m_checkpointForward = isForward;
				return;
			}

			m_checkpointCount--;
			m_flags = flags & ~c_flagCrossedBackward;
		}

		m_checkpoint = p_entry;
		m_checkpointForward = isForward;
	}
}

// FUNCTION: LEGORACERS 0x0043a0a0
LegoFloat Racer::GetRaceProgress()
{
	if (m_checkpoint) {
		return static_cast<LegoFloat>(m_checkpointCount) + m_checkpoint->m_lapFraction;
	}

	return 0.0f;
}

// FUNCTION: LEGORACERS 0x0043a0c0
void Racer::CycleHudGadget()
{
	m_hud->m_gadgetMode = (m_hud->m_gadgetMode + 1) & 3;
}

// FUNCTION: LEGORACERS 0x0043a0e0
void Racer::SwitchToAiControl()
{
	RaceRouteRecord* routeRecord = m_routeRecord;
	m_controlMode = c_controlAi;

	if (!routeRecord) {
		routeRecord = m_raceState->FindNearestRouteRecord(this);
		m_routeRecord = routeRecord;

		if (routeRecord) {
			m_driveController.StartReturnToPath(routeRecord);
		}
		else {
			m_driveController.m_flags |= 0x80;
		}
	}
}

// FUNCTION: LEGORACERS 0x0043a130
void Racer::StartMagnetHold()
{
	m_flags |= c_flagMagnetHeld;

	if (m_controlMode != c_controlAi) {
		m_driveController.m_flags |= DriveController::c_flagBrakeToStop;
		m_visuals.StartSkidEffects();
	}

	if (m_physics.m_routeMode) {
		m_physics.m_routeBaseSpeed = 0.0f;
		if (!(m_physics.m_flags & RacerPhysics::c_flagRoutePushed)) {
			m_physics.m_routeTargetSpeed = 0.0f;
		}
	}

	Resume();
}

// FUNCTION: LEGORACERS 0x0043a1a0
void Racer::EndMagnetHold()
{
	LegoU32 flags = m_flags;
	LegoU32 state = m_controlMode;
	flags &= ~c_flagMagnetHeld;
	m_flags = flags;

	if (state != 2) {
		LegoU32 controllerFlags = m_driveController.m_flags;
		controllerFlags &= ~DriveController::c_flagBrakeToStop;
		m_driveController.m_flags = controllerFlags;
		m_visuals.StopSkidEffects();
	}

	if (m_physics.m_routeMode) {
		LegoU32 physicsFlags = m_physics.m_flags;
		m_physics.m_routeBaseSpeed = 1.0f;
		if (!(physicsFlags & RacerPhysics::c_flagRoutePushed)) {
			m_physics.m_routeTargetSpeed = 1.0f;
		}
	}

	Resume();
}

// FUNCTION: LEGORACERS 0x0043a210
void Racer::SetStandingsPosition(LegoU32 p_position)
{
	if (!(m_flags & c_flagPreStart)) {
		LegoU32 previousPosition = m_standingsPosition;
		if (p_position < previousPosition) {
			PlayReaction(TRUE);
		}
		else if (p_position > previousPosition) {
			PlayReaction(FALSE);
		}

		m_standingsPosition = p_position;
	}
	else {
		m_standingsPosition = p_position;
	}
}

// FUNCTION: LEGORACERS 0x0043a270
void Racer::AbsorbShieldHit()
{
	LegoU32 soundId = 1;
	SoundVector position;
	m_visuals.m_carEntity->GetPosition(&position);

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
void Racer::SetCameraView(LegoU32 p_viewIndex, LegoBool32 p_flag)
{
	if (m_cameraController) {
		m_cameraController->SetView(p_viewIndex, p_flag);
		m_cameraController->m_dirty = TRUE;
		m_cameraViewIndex = p_viewIndex;

		if (p_flag) {
			m_flags |= c_flagSplitScreen;
		}
		else {
			m_flags &= ~c_flagSplitScreen;
		}
	}
}

// FUNCTION: LEGORACERS 0x0043a360
void Racer::ReapplyCameraView()
{
	if (m_cameraController) {
		m_cameraController->SetView(m_cameraViewIndex, m_flags & c_flagSplitScreen);
		m_cameraController->m_dirty = TRUE;
	}
}

// FUNCTION: LEGORACERS 0x0043a390
void Racer::CycleCameraView()
{
	LegoU32 flags = m_flags;
	if (!(flags & c_flagFinished) && (flags & c_flagEngineSounds)) {
		RaceCameraController* controller = m_cameraController;
		if (controller) {
			LegoU32 index = m_cameraViewIndex;
			LegoBool32 enabled = flags & c_flagSplitScreen;
			index++;
			index &= 3;
			m_cameraViewIndex = index;
			controller->SetView(index, enabled);
			m_cameraController->m_dirty = TRUE;
		}
	}
}

// FUNCTION: LEGORACERS 0x0043a3e0
void Racer::InvalidateCamera()
{
	if (m_cameraController) {
		m_cameraController->m_dirty = TRUE;
	}
}

// FUNCTION: LEGORACERS 0x0043a3f0
void Racer::StartLookBack()
{
	m_cameraController->m_lookBack = TRUE;
}

// FUNCTION: LEGORACERS 0x0043a400
void Racer::EndLookBack()
{
	m_cameraController->m_lookBack = FALSE;
}
