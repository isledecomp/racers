#include "audio/spatialsoundinstance.h"
#include "audio/streamingsoundinstance.h"
#include "golconstants.h"
#include "golmath.h"
#include "race/raceeventtable.h"
#include "race/raceforcefeedback.h"
#include "race/racer/racerouterecord.h"
#include "race/racer/racersoundsource.h"
#include "race/racestate.h"
#include "race/triggerworld.h"

#include <float.h>
#include <math.h>
#include <string.h>

extern LegoFloat g_arcCosineTable[1024];
extern const LegoS32 g_wheelDiagonalIndices[];
extern const LegoS32 g_wheelLengthwiseIndices[];
extern const LegoS32 g_wheelSidewaysIndices[];

// GLOBAL: LEGORACERS 0x004b0448
extern const LegoFloat g_routeBaseMaxSpeed = 120.0f;

// GLOBAL: LEGORACERS 0x004b0450
extern const LegoFloat g_routeBoostMaxSpeed = 176.0f;

// GLOBAL: LEGORACERS 0x004b0454
extern const LegoFloat g_movingSpeedThreshold = 0.04f;

// GLOBAL: LEGORACERS 0x004b0438
extern const LegoFloat g_unk0x004b0438 = 1.0f;

// GLOBAL: LEGORACERS 0x004b043c
extern const LegoFloat g_unk0x004b043c = 0.5f;

// GLOBAL: LEGORACERS 0x004b0440
extern const LegoFloat g_unk0x004b0440 = 2.0f;

// GLOBAL: LEGORACERS 0x004b0458
extern const LegoFloat g_defaultLateralGrip = 3.0f;

// GLOBAL: LEGORACERS 0x004b045c
extern const LegoFloat g_unk0x004b045c = 1.0f;

// GLOBAL: LEGORACERS 0x004b0460
extern const LegoFloat g_defaultSupportThreshold = 0.5f;

// GLOBAL: LEGORACERS 0x004b0464
extern const LegoFloat g_defaultFriction = 0.25f;

// GLOBAL: LEGORACERS 0x004b0468
extern const LegoFloat g_wheelParticleMinSpeed = 0.008f;

// GLOBAL: LEGORACERS 0x004b0474
extern const LegoFloat g_surfaceSoundMinSpeed = 0.0089999996f;

// GLOBAL: LEGORACERS 0x004b0478
extern const LegoFloat g_surfaceSoundPitchSpeed = 0.22f;

// GLOBAL: LEGORACERS 0x004b047c
extern const LegoFloat g_surfaceSoundFadeInMs = 280.0f;

// GLOBAL: LEGORACERS 0x004b0484
extern const LegoFloat g_routePushImpulseMax = 300.0f;

// GLOBAL: LEGORACERS 0x004b0488
extern const LegoFloat g_routeSpinOutSpeed = 0.1f;

// GLOBAL: LEGORACERS 0x004b048c
extern const LegoFloat g_routeWallBackSpeed = -0.1f;

// GLOBAL: LEGORACERS 0x004b0490
extern const LegoFloat g_routeSpinSpeed = 0.3f;

// GLOBAL: LEGORACERS 0x004b0494
extern const LegoFloat g_routeBoostSpeed = 1.7f;

// GLOBAL: LEGORACERS 0x004b0498
extern const LegoFloat g_routeGhostSpeed = 4.5f;

// GLOBAL: LEGORACERS 0x004b049c
extern const LegoFloat g_routeCurseSpeed = 0.5f;

// GLOBAL: LEGORACERS 0x004b04a0
extern const LegoFloat g_routeMaxPlaybackSpeed = 2.75f;

// GLOBAL: LEGORACERS 0x004b04a4
extern const LegoFloat g_routeMinPlaybackSpeed = -0.5f;

// GLOBAL: LEGORACERS 0x004b04a8
extern const LegoFloat g_routeSlideLiftTarget = 6.0f;

// GLOBAL: LEGORACERS 0x004b04ac
extern const LegoFloat g_routeSlideLiftRate = 3.0f;

// GLOBAL: LEGORACERS 0x004b04b0
extern const LegoFloat g_slideLiftReleaseRate = 15.0f;

// GLOBAL: LEGORACERS 0x004b04b8
extern const LegoFloat g_routePlaybackDecel = 0.0020000001f;

// GLOBAL: LEGORACERS 0x004b04bc
extern const LegoFloat g_routePlaybackAccel = 0.00048828125f;

// GLOBAL: LEGORACERS 0x004b04c0
extern const LegoFloat g_routePlaybackAccelBoost = 0.0099999998f;

// GLOBAL: LEGORACERS 0x004b04c4
extern const LegoFloat g_routePlaybackDecelPushed = 0.000732421875f;

// GLOBAL: LEGORACERS 0x004b04c8
extern const LegoFloat g_routePlaybackAccelPushed = 0.0020000001f;

// GLOBAL: LEGORACERS 0x004b04cc
extern const LegoFloat g_routeSideOffsetDecay = 0.001953125f;

// GLOBAL: LEGORACERS 0x004b04d0
extern const LegoFloat g_routeSpinOutJumpVelocity = 50.0f;

// GLOBAL: LEGORACERS 0x004b04d4
extern const LegoFloat g_routeJumpGravity = -100.0f;

// GLOBAL: LEGORACERS 0x004b04d8
extern const LegoFloat g_worldMaxZ = 340.0f;

// GLOBAL: LEGORACERS 0x004b04dc
extern const LegoFloat g_worldMinZ = -250.0f;

// GLOBAL: LEGORACERS 0x004b04e0
extern const LegoFloat g_routeBoostRampMs = 2000.0f;

// GLOBAL: LEGORACERS 0x004b054c
extern const LegoFloat g_handlingStatScale = 0.003f;

// GLOBAL: LEGORACERS 0x004b0b90
extern const LegoFloat g_boxInertiaFactor = 0.083333336f;

// GLOBAL: LEGORACERS 0x004b0cd8
extern const LegoFloat g_physicsSoundMinDistance = 30.0f;

// GLOBAL: LEGORACERS 0x004b0cdc
extern const LegoFloat g_physicsSoundMaxDistance = 300.0f;

// GLOBAL: LEGORACERS 0x004b0ce4
extern const LegoFloat g_carGravity = 39.0f;

// GLOBAL: LEGORACERS 0x004b0ce8
extern const LegoFloat g_uprightTiltMaxAngle = 0.78539819f;

// GLOBAL: LEGORACERS 0x004b0cec
extern const LegoFloat g_uprightTiltMinCosine = 0.70710677f;

// GLOBAL: LEGORACERS 0x004b0cf0
extern const LegoFloat g_defaultMaxSpeed = 110.0f;

// GLOBAL: LEGORACERS 0x004b0cf4
extern const LegoFloat g_wheelContactPadding = 0.4f;

// GLOBAL: LEGORACERS 0x004b0cf8
extern const LegoFloat g_defaultRideHeight = 0.2f;

// GLOBAL: LEGORACERS 0x004b0cfc
extern const LegoFloat g_wheelSupportSweepScale = 0.04f;

// GLOBAL: LEGORACERS 0x004b0d00
extern const LegoFloat g_slideSweepScale = 0.01f;

// GLOBAL: LEGORACERS 0x004b0d04
extern const LegoFloat g_airborneDropStep = 0.008f;

// GLOBAL: LEGORACERS 0x004b0d08
extern const LegoFloat g_wallHorizontalDamping = 0.30000001f;

// GLOBAL: LEGORACERS 0x004b0d20
extern const LegoFloat g_defaultSlideLiftTarget = 6.0f;

// GLOBAL: LEGORACERS 0x004b0d24
extern const LegoFloat g_defaultSlideLiftRate = 3.0f;

// GLOBAL: LEGORACERS 0x004b0d28
extern const LegoFloat g_slideBankRate = 0.005f;

// GLOBAL: LEGORACERS 0x004b0d2c
extern const LegoFloat g_landingBounceThreshold = 0.05f;

// GLOBAL: LEGORACERS 0x004b0d30
extern const LegoFloat g_landingBounceScale = 1.3f;

// GLOBAL: LEGORACERS 0x004b0d34
extern const LegoFloat g_landingBounceScaleFourWheel = 1.15f;

extern LegoU32 g_defaultPowerslideFactorBits;
extern const LegoFloat g_minTurnRadius;
extern const LegoFloat g_wallMaxRiseSpeed;
extern const LegoFloat g_carBuildModelHeightScale;
extern const LegoFloat g_carBuildModelTextureCoordinateScale;
extern const LegoFloat g_unk0x004b0430;
extern const LegoFloat g_unk0x004b0434;
extern const LegoFloat g_unk0x004b0544;
extern const LegoFloat g_ghostSpeedScale;
extern const LegoFloat g_twoPi;

// GLOBAL: LEGORACERS 0x004c4868
RacerPhysics::RouteCursorInstance g_routeProbeCursor;

// GLOBAL: LEGORACERS 0x004c48e0
GolMatrix3 g_routeProbeOrientation;

// GLOBAL: LEGORACERS 0x004c6c04
RacerPhysics::SavedWheelStateBlock g_carBodySavedWheels;

// GLOBAL: LEGORACERS 0x004c6df0
RacerPhysics::SavedState g_carBodySavedState;

// FUNCTION: LEGORACERS 0x00429020
RacerPhysics::RacerPhysics()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004290b0
RacerPhysics::~RacerPhysics()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00429120
void RacerPhysics::Reset()
{
	m_ownerRacer = NULL;
	m_eventTable = NULL;
	m_unk0x6f8 = 0;
	m_triggerCollidable = NULL;
	SetHandlingStat(0x21);
	SetAccelerationStat(0x21);
	SetTopSpeedStat(0x21);

	m_surfaceSoundMs = 0;
	m_maxSpeedSetting = g_routeBaseMaxSpeed;
	m_routeMode = 0;
	m_routeMotion.m_sink = 0.0f;
	m_routeMotion.m_sideOffset = 0.0f;
	m_routeMotion.m_jumpHeight = 0.0f;
	m_routeMotion.m_jumpVelocity = 0.0f;
	m_routeSpinRate = 0;
	m_routeSpinAngle = 0;
	m_routeTiltRate = 0;
	m_routeTiltAngle = 0;
	m_routeTiltHeight = 0;
	m_slideLift = 0;
	m_slideBankAngle = 0;
	m_slideBankTarget = 0;
	m_routePaused = 0;
	m_resetPosition.m_x = 0.0f;
	m_resetPosition.m_y = 0.0f;
	m_resetPosition.m_z = 0.0f;
	m_resetRotation.m_x = 0.0f;
	m_resetRotation.m_y = 0.0f;
	m_resetRotation.m_z = 0.0f;
	m_resetRotation.m_w = 1.0f;
	m_surfaceSound = NULL;
	m_routeBaseSpeed = 1.0f;
	m_routeTargetSpeed = 1.0f;
	m_surfaceSoundId = -1;
}

// FUNCTION: LEGORACERS 0x00429210
void RacerPhysics::Initialize(
	Racer* p_racer,
	RaceEventTable* p_eventTable,
	void* p_unk0x0c,
	GolAnimatedEntity* p_carEntity,
	GolBoundedEntity* p_trackWorld,
	GolBoundedEntity* p_triggerWorld,
	RacerSoundSource* p_soundSource,
	LegoFloat p_mass,
	LegoFloat p_sizeX,
	LegoFloat p_sizeY,
	LegoFloat p_sizeZ
)
{
	if (m_ownerRacer != NULL) {
		Destroy();
	}

	m_ownerRacer = p_racer;
	m_eventTable = p_eventTable;
	m_unk0x6f8 = p_unk0x0c;
	m_triggerCollidable = p_triggerWorld;
	RacerCarBody::Initialize(
		p_carEntity,
		p_trackWorld,
		p_triggerWorld,
		p_soundSource,
		p_mass,
		p_sizeX,
		p_sizeY,
		p_sizeZ
	);
	p_carEntity->GetPosition(&m_resetPosition);
	GolMath::FUN_1002f5a0(p_carEntity->GetOrientation(), &m_resetRotation);
	m_surfaceSoundMs = 0;
}

// FUNCTION: LEGORACERS 0x004292b0
void RacerPhysics::Destroy()
{
	StopSurfaceSound();
	m_routeCursor.Destroy();
	Reset();
	RacerCarBody::Destroy();
}

// FUNCTION: LEGORACERS 0x004292e0
void RacerPhysics::StartBoost()
{
	LegoU32 flags = m_flags;
	if (!(flags & c_flagCurseSlow)) {
		m_flags = flags | c_flagBoost;

		if (m_routeMode) {
			LegoFloat value = g_routeBoostSpeed;
			m_routeCursor.m_playbackSpeed = value;
		}

		m_maxSpeedSetting = g_routeBoostMaxSpeed;
		m_gripScale = 1.5f;
		SetMaxSpeed(g_routeBoostMaxSpeed);
	}
}

// FUNCTION: LEGORACERS 0x00429330
void RacerPhysics::EndBoost()
{
	LegoU32 flags = m_flags & ~c_flagBoost;
	m_flags = flags;

	if (m_routeMode && !(flags & (c_flagSpinning | c_flagBoost | c_flagRoutePushed))) {
		m_routeTargetSpeed = 1.0f;
	}

	m_gripScale = 1.0f;
	m_maxSpeedSetting = g_routeBaseMaxSpeed;
	SetMaxSpeed(g_routeBaseMaxSpeed);
}

// FUNCTION: LEGORACERS 0x00429380
void RacerPhysics::StartCurseSlow()
{
	if (m_flags & c_flagBoost) {
		EndBoost();
	}

	m_flags |= c_flagCurseSlow;

	if (m_routeMode) {
		LegoFloat value = g_routeCurseSpeed;
		m_routeCursor.m_playbackSpeed = value;
	}
}

// FUNCTION: LEGORACERS 0x004293c0
void RacerPhysics::EndCurseSlow()
{
	LegoU32 flags = m_flags & ~c_flagCurseSlow;
	m_flags = flags;

	if (m_routeMode && !(flags & (c_flagSpinning | c_flagBoost | c_flagRoutePushed))) {
		m_routeTargetSpeed = 1.0f;
	}
}

// FUNCTION: LEGORACERS 0x004293f0
void RacerPhysics::Update(LegoS32 p_elapsedMs)
{
	GolVec3 soundPosition;
	GolVec3 position;

	if (m_routeMode) {
		UpdateRouteMotion(p_elapsedMs);
	}
	else {
		RacerCarBody::Update(static_cast<LegoS32>(p_elapsedMs));

		if (m_contactCount == 4 && !m_wallContact) {
			LegoU32 racerFlags = m_ownerRacer->m_flags;
			if (!(racerFlags & Racer::c_flagEngineSounds) || !(racerFlags & Racer::c_flagPreStart)) {
				GolOrientedEntity* entity0 = &m_physicsEntity;
				entity0->GetPosition(&m_resetPosition);
				GolMath::FUN_1002f5a0(m_physicsEntity.GetOrientation(), &m_resetRotation);
			}
		}

		GolOrientedEntity* entity = &m_physicsEntity;
		entity->GetPosition(&position);
		if (position.m_z < g_worldMinZ || position.m_z > g_worldMaxZ) {
			entity->SetPosition(m_resetPosition);
			GolMath::FUN_00449340(&m_resetRotation, &m_physicsEntity.GetOrientation().m_m[0][0]);
			m_velocity.m_x = 0.0f;
			m_velocity.m_y = 0.0f;
			m_velocity.m_z = 0.0f;
			m_angularMomentum.m_x = 0.0f;
			m_angularMomentum.m_y = 0.0f;
			m_angularMomentum.m_z = 0.0f;
		}

		LegoU32 racerFlags = m_ownerRacer->m_flags;
		if ((racerFlags & Racer::c_flagEngineSounds) && (racerFlags & Racer::c_flagPreStart)) {
			entity->SetPosition(m_resetPosition);
			GolMath::FUN_00449340(&m_resetRotation, &m_physicsEntity.GetOrientation().m_m[0][0]);
			m_velocity.m_x = 0.0f;
			m_velocity.m_y = 0.0f;
			m_velocity.m_z = 0.0f;
			m_angularMomentum.m_x = 0.0f;
			m_angularMomentum.m_y = 0.0f;
			m_angularMomentum.m_z = 0.0f;
		}
	}

	if (m_surfaceSound == NULL) {
		return;
	}

	if (m_contactCount && !(m_flags & c_flagSliding) &&
		(m_speed >= g_surfaceSoundMinSpeed || m_speed <= -g_surfaceSoundMinSpeed)) {
		LegoS32 soundAge = static_cast<LegoS32>(m_surfaceSoundMs);
		soundAge += p_elapsedMs;
		m_surfaceSoundMs = soundAge;

		m_carEntity->GetPosition(&soundPosition);
		m_surfaceSound->SetPosition(soundPosition);
		m_surfaceSound->SetVelocity(m_velocity);

		LegoFloat frequencyScale = m_speed / g_surfaceSoundPitchSpeed + g_carBuildModelHeightScale;
		if (frequencyScale < g_unk0x004b043c) {
			frequencyScale = g_unk0x004b043c;
		}
		else if (frequencyScale > g_unk0x004b0440) {
			frequencyScale = g_unk0x004b0440;
		}
		m_surfaceSound->SetFrequencyScale(frequencyScale);

		LegoFloat volume = static_cast<LegoFloat>(static_cast<LegoS32>(m_surfaceSoundMs)) / g_surfaceSoundFadeInMs;
		if (volume > g_unk0x004b0438) {
			volume = g_unk0x004b0438;
		}
		m_surfaceSound->SetVolume(volume);
	}
	else {
		StopSurfaceSound();
	}
}

// FUNCTION: LEGORACERS 0x00429680
void RacerPhysics::MoveBy(GolVec3* p_delta)
{
	if (m_routeMode) {
		GolVec3 direction = *p_delta;
		m_routeCursor.SeekByDelta(&direction);
		UpdateRouteRotation(0);

		const GolVec3& side = m_carEntity->GetOrientation().m_rows[1];
		LegoFloat dot = side.m_z * direction.m_z;
		dot += side.m_y * direction.m_y;
		dot += side.m_x * direction.m_x;
		m_routeMotion.m_sideOffset = dot;

		if (dot > 0.0f) {
			if (m_routeCursor.m_widthRight < dot) {
				dot = m_routeCursor.m_widthRight;
				m_routeMotion.m_sideOffset = dot;
			}
		}
		else if (m_routeCursor.m_widthLeft < -dot) {
			m_routeMotion.m_sideOffset = -m_routeCursor.m_widthLeft;
		}

		ApplyRoutePosition();
	}
	else {
		RacerCarBody::MoveBy(p_delta);
	}
}

// FUNCTION: LEGORACERS 0x00429770
void RacerPhysics::ApplyDirectionalImpulse(GolVec3* p_direction, LegoFloat p_magnitude)
{
	if (!m_routeMode) {
		RacerCarBody::ApplyDirectionalImpulse(p_direction, p_magnitude);
		return;
	}

	LegoFloat dot = m_facingDirection.m_z * p_direction->m_z;
	dot += m_facingDirection.m_y * p_direction->m_y;
	dot += m_facingDirection.m_x * p_direction->m_x;
	if (p_magnitude < 0.0f) {
		dot = -dot;
		p_magnitude = -p_magnitude;
	}

	if (p_magnitude > g_routePushImpulseMax) {
		p_magnitude = g_routePushImpulseMax;
	}
	LegoFloat scaled = p_magnitude / g_routePushImpulseMax;

	if (dot >= 0.0f) {
		LegoFloat amount = (1.0f - dot) * g_unk0x004b0544;
		LegoFloat value;
		if (m_flags & c_flagSpinning) {
			value = g_routeSpinSpeed;
			value += 0.1f;
		}
		else {
			value = m_routeCursor.m_playbackSpeed;
			value += scaled;
		}
		amount += value;

		if (amount > g_routeMaxPlaybackSpeed) {
			amount = g_routeMaxPlaybackSpeed;
		}
		m_routeCursor.m_playbackSpeed = amount;
	}
	else {
		LegoFloat amount = (dot + 1.0f) * g_carBuildModelTextureCoordinateScale;
		LegoFloat value;
		if (m_flags & c_flagSpinning) {
			value = g_routeSpinSpeed - 0.1f;
		}
		else {
			value = m_routeCursor.m_playbackSpeed - scaled;
		}
		value -= amount;

		if (value < g_routeMinPlaybackSpeed) {
			value = g_routeMinPlaybackSpeed;
		}
		m_routeCursor.m_playbackSpeed = value;
	}
}

// FUNCTION: LEGORACERS 0x004298a0
void RacerPhysics::StartExternalForce0(GolVec3* p_force)
{
	if (!m_routeMode) {
		RacerCarBody::StartExternalForce0(p_force);
	}
	else {
		StartRoutePush(p_force);
	}
}

// FUNCTION: LEGORACERS 0x004298d0
void RacerPhysics::EndExternalForce0()
{
	if (!m_routeMode) {
		RacerCarBody::EndExternalForce0();
	}
	else {
		EndRoutePush();
	}
}

// FUNCTION: LEGORACERS 0x004298f0
void RacerPhysics::StartExternalForce1(GolVec3* p_force)
{
	if (!m_routeMode) {
		RacerCarBody::StartExternalForce1(p_force);
	}
	else {
		StartRoutePush(p_force);
	}
}

// FUNCTION: LEGORACERS 0x00429920
void RacerPhysics::EndExternalForce1()
{
	if (!m_routeMode) {
		RacerCarBody::EndExternalForce1();
	}
	else {
		EndRoutePush();
	}
}

// FUNCTION: LEGORACERS 0x00429940
void RacerPhysics::EndRoutePush()
{
	LegoU32 flags = m_flags;
	flags &= ~c_flagRoutePushed;
	m_flags = flags;

	if (m_flags & c_flagSpinning) {
		m_routeTargetSpeed = g_routeSpinSpeed;
		return;
	}

	if (m_routeBaseSpeed < 0.0f) {
		m_routeBaseSpeed = 1.0f;
	}

	m_routeTargetSpeed = m_routeBaseSpeed;
}

// FUNCTION: LEGORACERS 0x00429990
void RacerPhysics::StartRoutePush(GolVec3* p_force)
{
	LegoU32 flags = m_flags | c_flagRoutePushed;
	m_flags = flags;

	LegoFloat dot = m_facingDirection.m_x * p_force->m_x + m_facingDirection.m_y * p_force->m_y +
					m_facingDirection.m_z * p_force->m_z;
	if (dot >= 0.0f) {
		if (flags & c_flagSpinning) {
			LegoFloat value = g_routeSpinSpeed;
			value += 0.1f;
			m_routeTargetSpeed = value;
		}
		else {
			m_routeTargetSpeed = dot / g_routePushImpulseMax + m_routeCursor.m_playbackSpeed;
		}

		if (m_routeTargetSpeed > g_routeMaxPlaybackSpeed) {
			m_routeTargetSpeed = g_routeMaxPlaybackSpeed;
		}
	}
	else {
		if (flags & c_flagSpinning) {
			m_routeTargetSpeed = g_routeSpinSpeed - 0.1f;
		}
		else {
			m_routeTargetSpeed = dot / g_routePushImpulseMax + m_routeCursor.m_playbackSpeed;
		}

		if (m_routeTargetSpeed < g_routeMinPlaybackSpeed) {
			m_routeTargetSpeed = g_routeMinPlaybackSpeed;
		}
	}
}

// FUNCTION: LEGORACERS 0x00429a70
void RacerPhysics::ApplyImpulse(GolVec3* p_impulse, GolVec3* p_point)
{
	if (!m_routeMode) {
		RacerCarBody::ApplyImpulse(p_impulse, p_point);
	}
}

// FUNCTION: LEGORACERS 0x00429a90
void RacerPhysics::StartRouteGhost()
{
	if (m_routeMode == 0) {
		return;
	}

	LegoU32& flags = m_flags;
	flags |= c_flagSliding | c_flagBoost | c_flagRouteGhost;
	LegoFloat value = g_routeGhostSpeed;
	m_routeCursor.m_playbackSpeed = value;

	if (!(flags & c_flagSliding)) {
		m_slideLift = 0.0f;
		m_slideBankAngle = 0.0f;
	}

	m_slideLiftTarget = g_routeSlideLiftTarget;
	m_slideBankTarget = 0.0f;
	m_slideLiftRate = g_routeSlideLiftRate;
}

// FUNCTION: LEGORACERS 0x00429af0
void RacerPhysics::EndRouteGhost()
{
	if (m_routeMode) {
		m_routeCursor.m_playbackSpeed = m_routeBaseSpeed;
		m_slideLiftTarget = 0;
		m_slideBankTarget = 0;
		m_slideLiftRate = g_slideLiftReleaseRate;
		m_flags &= ~(c_flagSliding | c_flagBoost | c_flagRouteGhost);
	}
}

// FUNCTION: LEGORACERS 0x00429b40
void RacerPhysics::StartSliding()
{
	if (!m_routeMode) {
		RacerCarBody::StartSliding();
		return;
	}

	if (!(m_flags & c_flagSliding)) {
		ApplyPitchImpulse(-0.003f, 250);
		m_slideLift = 0;
		m_flags |= c_flagSliding;
		m_slideBankAngle = 0;
		m_slideBankTarget = 0;
		m_slideLiftTarget = g_routeSlideLiftTarget;
		m_slideLiftRate = g_routeSlideLiftRate;
	}
}

// FUNCTION: LEGORACERS 0x00429bc0
void RacerPhysics::StopSliding()
{
	if (!m_routeMode) {
		RacerCarBody::StopSliding();
	}
	else {
		m_slideLiftTarget = 0.0f;
		m_slideBankTarget = 0;
		m_slideLiftRate = g_slideLiftReleaseRate;
		m_flags &= ~c_flagSliding;
	}
}

// FUNCTION: LEGORACERS 0x00429c00
void RacerPhysics::StartSpinOut()
{
	RacerCarBody::StartSpinOut();
	m_routeMotion.m_jumpVelocity = g_routeSpinOutJumpVelocity;
	LegoFloat unk0x778 = g_routeSpinOutSpeed;
	m_routeCursor.m_playbackSpeed = unk0x778;
}

// FUNCTION: LEGORACERS 0x00429c30
void RacerPhysics::EndSpinOut()
{
	if (!m_routeMode) {
		RacerCarBody::EndSpinOut();
	}
}

// FUNCTION: LEGORACERS 0x00429c40
void RacerPhysics::StartSpin(LegoFloat p_turns, LegoFloat p_rate, LegoFloat p_alignFraction)
{
	if (!m_routeMode) {
		RacerCarBody::StartSpin(p_turns, p_rate, p_alignFraction);
		return;
	}

	LegoU32 flags = m_flags;
	if (!(flags & c_flagSpinning)) {
		LegoFloat scaled = p_turns;
		scaled *= g_twoPi;
		scaled /= p_rate;
		m_yawImpulseMs = static_cast<LegoS32>(scaled);
		m_routeSpinRate = p_rate;
		m_routeSpinAngle = 0;
		m_flags = flags | c_flagSpinning;

		if (m_contactCount) {
			LegoFloat value = g_routeSpinSpeed;
			m_routeCursor.m_playbackSpeed = value;
		}
	}
}

// FUNCTION: LEGORACERS 0x00429cd0
void RacerPhysics::EndSpin()
{
	if (!m_routeMode) {
		RacerCarBody::EndSpin();
	}
	else {
		m_flags &= ~(c_flagSpinning | c_flagSpinFresh);
	}
}

// FUNCTION: LEGORACERS 0x00429cf0
void RacerPhysics::ApplyPitchImpulse(LegoFloat p_rate, LegoU32 p_durationMs)
{
	if (!m_routeMode) {
		RacerCarBody::ApplyPitchImpulse(p_rate, p_durationMs);
		return;
	}

	if (!m_pitchImpulseMs) {
		m_routeTiltAngle = 0;
		m_routeTiltRate = -p_rate;
		m_pitchImpulseMs = p_durationMs;
	}
}

// FUNCTION: LEGORACERS 0x00429d40
void RacerPhysics::UpdateRouteMotion(LegoU32 p_elapsedMs)
{
	if (p_elapsedMs == 0) {
		return;
	}

	if (m_routePaused != 0) {
		return;
	}

	if (m_flags & c_flagSliding) {
		UpdateRouteSlideBank();
	}

	if (m_flags & c_flagBoost) {
		if (m_routeCursor.m_currentTime < g_routeBoostRampMs) {
			LegoFloat speedScale = m_routeCursor.m_currentTime;
			speedScale -= g_routeBoostRampMs;
			speedScale /= g_routeBoostRampMs;
			speedScale = -speedScale;
			m_routeTargetSpeed = speedScale * (g_routeMaxPlaybackSpeed - g_routeBoostSpeed) + g_routeBoostSpeed;
		}
	}

	SaveRouteState();

	for (;;) {
		if (p_elapsedMs != 0) {
			GolVec3 previousPosition;
			m_carEntity->GetPosition(&previousPosition);

			LegoFloat elapsed = static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs));
			LegoU32 flags = m_flags;
			LegoU32 suspendedMask = flags & c_flagRoutePushed;
			if (suspendedMask || !(flags & (c_flagSpinning | c_flagBoost | c_flagCurseSlow)) || m_contactCount == 0) {
				LegoFloat currentSpeed = m_routeCursor.m_playbackSpeed;
				if (currentSpeed < m_routeTargetSpeed) {
					LegoFloat rate;
					if (suspendedMask) {
						rate = g_routePlaybackAccelPushed;
					}
					else if (flags & c_flagBoost) {
						rate = g_routePlaybackAccelBoost;
					}
					else {
						rate = g_routePlaybackAccel;
					}

					currentSpeed += rate * elapsed;
					if (currentSpeed > m_routeTargetSpeed) {
						currentSpeed = m_routeTargetSpeed;
					}
					m_routeCursor.m_playbackSpeed = currentSpeed;
				}
				else if (currentSpeed > m_routeTargetSpeed) {
					LegoFloat rate;
					if (suspendedMask) {
						rate = g_routePlaybackDecelPushed;
					}
					else {
						rate = g_routePlaybackDecel;
					}

					currentSpeed -= rate * elapsed;
					if (currentSpeed < m_routeTargetSpeed) {
						currentSpeed = m_routeTargetSpeed;
					}
					m_routeCursor.m_playbackSpeed = currentSpeed;
				}
			}

			m_routeCursor.Advance(elapsed);

			if (m_routeMotion.m_sideOffset > 0.0f) {
				m_routeMotion.m_sideOffset -= g_routeSideOffsetDecay * elapsed;
				if (m_routeMotion.m_sideOffset < 0.0f) {
					m_routeMotion.m_sideOffset = 0.0f;
				}
			}
			else if (m_routeMotion.m_sideOffset < 0.0f) {
				m_routeMotion.m_sideOffset += g_routeSideOffsetDecay * elapsed;
				if (m_routeMotion.m_sideOffset > 0.0f) {
					m_routeMotion.m_sideOffset = 0.0f;
				}
			}

			if ((m_flags & c_flagSliding) || m_slideLift != 0.0f) {
				UpdateSlideBank(p_elapsedMs);
			}

			if (m_routeMotion.m_jumpVelocity != 0.0f || m_routeMotion.m_jumpHeight != 0.0f) {
				LegoFloat time = elapsed * 0.001f;
				m_routeMotion.m_jumpVelocity += g_routeJumpGravity * time;
				m_routeMotion.m_jumpHeight += time * m_routeMotion.m_jumpVelocity;
				if (m_routeMotion.m_jumpHeight <= 0.0f) {
					m_routeMotion.m_jumpHeight = 0.0f;
					m_routeMotion.m_jumpVelocity = 0.0f;
					m_flags &= ~c_flagSpinOut;
				}
			}

			UpdateRouteRotation(p_elapsedMs);
			ApplyRoutePosition();

			GolVec3 currentPosition;
			m_carEntity->GetPosition(&currentPosition);

			LegoFloat invElapsed = 1.0f / elapsed;
			m_velocity.m_x = currentPosition.m_x - previousPosition.m_x;
			m_velocity.m_y = currentPosition.m_y - previousPosition.m_y;
			m_velocity.m_z = currentPosition.m_z - previousPosition.m_z;
			m_velocity *= invElapsed;

			UpdateVelocityStats();
			m_physicsEntity.CopyTransformFrom(*m_carEntity);
		}

		if (m_wallContact != 0) {
			LegoFloat speed = g_routeWallBackSpeed;
			m_routeCursor.m_playbackSpeed = speed;
			ClearWallContacts();
			SaveRouteState();
			p_elapsedMs = m_stepRemainderMs;
		}
		else {
			p_elapsedMs = ResolveWallCollisions(p_elapsedMs, FALSE);
		}

		if (m_wallContact == 0) {
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x0042a100
void RacerPhysics::UpdateRouteSlideBank()
{
	GolQuat rotation = m_routeCursor.m_rotation;
	GolMath::FUN_00449340(&rotation, &g_routeProbeOrientation.m_m[0][0]);

	GolVec3 currentDirection = g_routeProbeOrientation.m_rows[1];
	g_routeProbeCursor = m_routeCursor;
	g_routeProbeCursor.Advance(500.0f);

	rotation = g_routeProbeCursor.m_rotation;
	GolMath::FUN_00449340(&rotation, &g_routeProbeOrientation.m_m[0][0]);

	LegoFloat dot = g_routeProbeOrientation.m_rows[0].m_z * currentDirection.m_z;
	dot += g_routeProbeOrientation.m_rows[0].m_y * currentDirection.m_y;
	dot += g_routeProbeOrientation.m_rows[0].m_x * currentDirection.m_x;
	dot *= 8.0f;

	if (dot > 1.0f) {
		dot = 1.0f;
	}
	else if (dot < -1.0f) {
		dot = -1.0f;
	}

	m_slideBankTarget = 0.78539819f * dot;
}

// FUNCTION: LEGORACERS 0x0042a220
void RacerPhysics::SaveRouteState()
{
	SaveState();

	m_savedRouteMotion.m_sink = m_routeMotion.m_sink;
	m_savedRouteMotion.m_jumpVelocity = m_routeMotion.m_jumpVelocity;
	m_savedRouteMotion.m_sideOffset = m_routeMotion.m_sideOffset;
	m_savedRouteCursor = m_routeCursor;
	m_savedRouteSpinRate = m_routeSpinRate;
	m_savedRouteMotion.m_jumpHeight = m_routeMotion.m_jumpHeight;
	m_savedRouteSpinAngle = m_routeSpinAngle;
}

// STUB: LEGORACERS 0x0042a290
void RacerPhysics::UpdateRouteRotation(LegoU32 p_elapsedMs)
{
	GolQuat rotation = m_routeCursor.m_rotation;
	GolMath::FUN_00449340(&rotation, &m_carEntity->GetOrientation().m_m[0][0]);

	if ((m_flags & c_flagSliding) || m_slideBankAngle != 0.0f) {
		const GolMatrix3& orientation = m_carEntity->GetOrientation();
		GolVec3 axis = orientation.m_rows[0];
		GolVec3 forward = orientation.m_rows[2];
		GolVec3 rotatedForward;
		GolMath::RotateAboutAxis(&forward, &rotatedForward, &axis, m_slideBankAngle);
		m_carEntity->SetDirectionUp(axis, rotatedForward);
	}

	LegoU32 elapsedMs = p_elapsedMs;
	LegoU32 timer = m_pitchImpulseMs;
	if (timer != 0 || m_routeTiltAngle != 0.0f) {
		if (timer != 0) {
			if (elapsedMs >= timer) {
				m_pitchImpulseMs = 0;
				m_routeTiltRate = -(m_routeTiltRate * g_carBuildModelTextureCoordinateScale);
			}
			else {
				m_pitchImpulseMs = timer - elapsedMs;
			}
		}

		LegoBool32 wasNonNegative = m_routeTiltAngle >= 0.0f;
		const GolMatrix3& orientation = m_carEntity->GetOrientation();
		GolVec3 axis = orientation.m_rows[0];
		GolVec3 forward = orientation.m_rows[2];

		m_routeTiltAngle += m_routeTiltRate * static_cast<LegoFloat>(static_cast<LegoS32>(elapsedMs));
		LegoBool32 applyTiltRotation = TRUE;
		if (m_pitchImpulseMs == 0) {
			LegoBool32 isNonNegative = m_routeTiltAngle >= 0.0f;
			if (wasNonNegative != isNonNegative) {
				m_routeTiltAngle = 0.0f;
				m_routeTiltHeight = 0.0f;
				applyTiltRotation = FALSE;
			}
		}

		if (applyTiltRotation) {
			m_carEntity->LocalToWorld(m_anchorWheelOffset, &m_wheelProbes[1].m_wheelPosition);

			GolVec3 rotatedForward;
			GolMath::RotateAboutAxis(&forward, &rotatedForward, &axis, m_routeTiltAngle);
			m_carEntity->SetDirectionUp(axis, rotatedForward);

			GolVec3 transformed;
			m_carEntity->LocalToWorld(m_anchorWheelOffset, &transformed);
			m_routeTiltHeight = transformed.m_z - m_wheelProbes[1].m_wheelPosition.m_z;
		}
	}

	if (m_yawImpulseMs == 0) {
		return;
	}

	if (p_elapsedMs >= m_yawImpulseMs) {
		m_yawImpulseMs = 0;
		EndSpin();
		return;
	}

	m_yawImpulseMs -= p_elapsedMs;

	GolVec3 right;
	GolVec3 forward;
	m_carEntity->GetAxes(&right, &forward);

	m_routeSpinAngle += m_routeSpinRate * static_cast<LegoFloat>(static_cast<LegoS32>(elapsedMs));

	GolVec3 rotatedRight;
	GolMath::RotateAboutAxis(&right, &rotatedRight, &forward, m_routeSpinAngle);
	m_carEntity->SetDirectionUp(rotatedRight, forward);
}

// FUNCTION: LEGORACERS 0x0042a570
void RacerPhysics::ApplyRoutePosition()
{
	GolVec3 position = m_routeCursor.m_position;
	GolOrientedEntity* entity = m_carEntity;
	const GolMatrix3& orientation = entity->GetOrientation();
	GolVec3 side;
	side.m_x = orientation.m_m[1][0];
	side.m_y = orientation.m_m[1][1];
	side.m_z = orientation.m_m[1][2];
	LegoFloat sideOffset = m_routeMotion.m_sideOffset;

	position.m_z = position.m_z - m_routeMotion.m_sink + m_routeTiltHeight + m_routeMotion.m_jumpHeight + m_slideLift;
	GolVec3 scaledSide;
	scaledSide.m_x = side.m_x * sideOffset;
	scaledSide.m_y = side.m_y * sideOffset;
	scaledSide.m_z = side.m_z * sideOffset;
	position.m_x += scaledSide.m_x;
	position.m_y += scaledSide.m_y;
	position.m_z += scaledSide.m_z;
	entity->SetPosition(position);

	m_contactCount = m_routeCursor.m_pointType;
	entity = m_carEntity;
	entity->LocalToWorld(m_centerOfMassLocal, &m_centerOfMassWorld);
	m_carEntity->GetOrientationRow0(&m_facingDirection);
	UpdateWorldInverseInertia();
}

// FUNCTION: LEGORACERS 0x0042a670
void RacerPhysics::AttachRoute(RaceRouteRecord* p_record)
{
	m_routeMode = TRUE;
	m_routeCursor.Attach(p_record);

	GolVec3 position = p_record->m_startPosition;
	GolQuat rotation = p_record->m_startRotation;
	m_carEntity->SetPosition(position);
	m_carEntity->SetOrientationFromQuaternion(rotation);
	m_carEntity->LocalToWorld(m_centerOfMassLocal, &m_centerOfMassWorld);

	for (LegoU32 i = 0; i < sizeOfArray(m_bodyPointsLocal); i++) {
		m_carEntity->LocalToWorld(m_bodyPointsLocal[i], &m_bodyPointsWorld[i]);
	}
}

// FUNCTION: LEGORACERS 0x0042a7f0
LegoBool32 RacerPhysics::IsMoving()
{
	if (m_speed < g_movingSpeedThreshold && -g_movingSpeedThreshold < m_speed) {
		return FALSE;
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0042a830
LegoU32 RacerPhysics::OnCollisionRecord(
	GolVec3* p_point,
	RaceEventRecord* p_record,
	GolBoundedEntity* p_world,
	GolBoundingVolume::HitTriangle* p_context
)
{
	if (p_world == m_triggerCollidable) {
		if (!p_context) {
			return FALSE;
		}

		LegoS32 eventKind = p_record->m_kind;
		if (static_cast<LegoChar>(eventKind) >= '0' && static_cast<LegoChar>(eventKind) <= '9') {
			m_ownerRacer->OnCheckpointCrossed(p_record->m_pathField, p_context);
			return FALSE;
		}
	}

	RaceEventRecord::Target* target = p_record->m_target;
	if (!target) {
		return TRUE;
	}

	if (target->m_flags & RaceEventRecord::Target::c_flagFinish) {
		m_ownerRacer->m_lapsCompleted = m_ownerRacer->m_lapCount;
	}

	if (target->m_flags & RaceEventRecord::Target::c_flagTouchEvent) {
		m_eventTable->FireEventsAt(target->m_touchEventId, target->m_touchEventId, p_point);
		m_eventTable->FireEventsForRacer(target->m_touchEventId, target->m_touchEventId, m_ownerRacer);
	}

	return (~target->m_flags >> 16) & 1;
}

// FUNCTION: LEGORACERS 0x0042a900
void RacerPhysics::UpdateWheelSurfaces()
{
	RacerPhysics* self = this;
	WheelProbe* entry = self->m_wheelProbes;
	WheelProbe* end = self->m_wheelProbes + sizeOfArray(self->m_wheelProbes);

	if (entry >= end) {
		return;
	}

	do {
		RaceEventRecord* record = entry->m_hitRecord;
		RaceEventRecord::Target* target0;
		if (record == NULL) {
			target0 = NULL;
		}
		else {
			target0 = record->m_target;
		}

		record = entry->m_previousHitRecord;
		RaceEventRecord::Target* target1;
		if (record == NULL) {
			target1 = NULL;
		}
		else {
			target1 = record->m_target;
		}

		if (target0) {
			self->ApplyWheelSurface(entry, target0);
		}
		else {
			self->ResetWheelSurface(entry);
			if (!target1) {
				entry++;
				continue;
			}
		}

		RaceEventRecord* record0 = entry->m_hitRecord;
		RaceEventRecord* record1 = entry->m_previousHitRecord;
		if (record0 != record1) {
			LegoBool32 notify0 = target0 != NULL;
			LegoBool32 notify1 = target1 != NULL;

			for (WheelProbe* other = self->m_wheelProbes; other < end; other++) {
				if (other == entry) {
					continue;
				}

				RaceEventRecord* otherRecord1 = other->m_previousHitRecord;
				if (record0 == otherRecord1 || (record0 == other->m_hitRecord && other < entry)) {
					notify0 = FALSE;
				}

				if (record1 == other->m_hitRecord || (record1 == otherRecord1 && other < entry)) {
					notify1 = FALSE;
				}
			}

			if (notify1) {
				self->NotifySurfaceLeave(entry, target1);
			}

			if (notify0) {
				self->NotifySurfaceEnter(entry, target0);
			}
		}

		entry++;
	} while (entry < end);
}

// FUNCTION: LEGORACERS 0x0042aa30
void RacerPhysics::NotifySurfaceEnter(WheelProbe* p_probe, RaceEventRecord::Target* p_target)
{
	if (p_target->m_flags & RaceEventRecord::Target::c_flagEnterEvent) {
		m_eventTable->StartEventsAt(p_target->m_enterEventId, &p_probe->m_wheelPosition);
		m_eventTable->StartEventsForRacer(p_target->m_enterEventId, m_ownerRacer);
	}
}

// FUNCTION: LEGORACERS 0x0042aa70
void RacerPhysics::NotifySurfaceLeave(WheelProbe* p_probe, RaceEventRecord::Target* p_target)
{
	if (p_target->m_flags & RaceEventRecord::Target::c_flagSurfaceSound) {
		if (p_target->m_surfaceSoundId == m_surfaceSoundId) {
			StopSurfaceSound();
		}
	}

	if (p_target->m_flags & RaceEventRecord::Target::c_flagLeaveEvent) {
		m_eventTable->EndEventsAt(p_target->m_leaveEventId, &p_probe->m_wheelPosition);
		m_eventTable->EndEventsForRacer(p_target->m_leaveEventId, m_ownerRacer);
	}
}

// FUNCTION: LEGORACERS 0x0042aad0
void RacerPhysics::ApplyWheelSurface(WheelProbe* p_probe, RaceEventRecord::Target* p_target)
{
	if (!(p_probe->m_flags & 1)) {
		ResetWheelSurface(p_probe);
		return;
	}

	if (p_target->m_flags & RaceEventRecord::Target::c_flagSurfaceSound) {
		PlaySurfaceSound(p_target->m_surfaceSoundId);
	}

	LegoU32 disabledMask = c_flagIgnoreSurfaces;
	if ((p_target->m_flags & RaceEventRecord::Target::c_flagRollingResistance) && !(m_flags & disabledMask)) {
		LegoFloat value = p_target->m_rollingResistance;
		p_probe->m_rollingResistance = value;
		if (m_ownerRacer->m_forceFeedback) {
			m_ownerRacer->m_forceFeedback->SetSurfaceIntensity(value);
		}
	}
	else {
		p_probe->m_rollingResistance = 0.0f;
		if (m_ownerRacer->m_forceFeedback) {
			m_ownerRacer->m_forceFeedback->SetSurfaceIntensity(0.0f);
		}
	}

	if ((p_target->m_flags & RaceEventRecord::Target::c_flagSupportThreshold) && !(m_flags & disabledMask)) {
		LegoFloat value = p_target->m_supportThreshold;
		p_probe->m_supportThreshold = value;
	}
	else {
		p_probe->m_supportThreshold = g_defaultSupportThreshold;
	}

	if ((p_target->m_flags & RaceEventRecord::Target::c_flagFriction) && !(m_flags & disabledMask)) {
		LegoFloat value = p_target->m_friction;
		p_probe->m_friction = value;
	}
	else {
		p_probe->m_friction = g_defaultFriction;
	}

	if ((p_target->m_flags & RaceEventRecord::Target::c_flagLateralGrip) && !(m_flags & disabledMask)) {
		LegoFloat value = p_target->m_lateralGrip;
		p_probe->m_lateralGrip = value;
	}
	else {
		p_probe->m_lateralGrip = g_defaultLateralGrip;
	}

	if ((p_target->m_flags & RaceEventRecord::Target::c_flagUnk0x54) && !(m_flags & disabledMask)) {
		LegoFloat value = p_target->m_unk0x54;
		p_probe->m_unk0x060 = value;
	}
	else {
		p_probe->m_unk0x060 = g_unk0x004b045c;
	}

	if ((p_target->m_flags & RaceEventRecord::Target::c_flagSurfaceForce) && !(m_flags & disabledMask)) {
		p_probe->m_surfaceForce = p_target->m_surfaceForce;
	}
	else {
		p_probe->m_surfaceForce.m_x = 0.0f;
		p_probe->m_surfaceForce.m_y = 0.0f;
		p_probe->m_surfaceForce.m_z = 0.0f;
	}

	if ((p_target->m_flags & RaceEventRecord::Target::c_flagWheelParticle) &&
		!(m_flags & (c_flagSliding | c_flagSpinOut)) && m_forwardSpeed > g_wheelParticleMinSpeed &&
		m_ownerRacer->m_controlMode != 2) {
		GolName name;
		::memcpy(name, p_target->m_wheelParticleName, sizeof(GolName));
		m_ownerRacer->m_visuals.SetWheelParticle(p_probe - m_wheelProbes, name);
		return;
	}

	m_ownerRacer->m_visuals.ClearWheelParticle(p_probe - m_wheelProbes);
}

// FUNCTION: LEGORACERS 0x0042acb0
void RacerPhysics::ResetWheelSurface(WheelProbe* p_probe)
{
	p_probe->m_rollingResistance = 0.0f;
	p_probe->m_supportThreshold = g_defaultSupportThreshold;
	p_probe->m_friction = g_defaultFriction;
	p_probe->m_lateralGrip = g_defaultLateralGrip;
	p_probe->m_unk0x060 = g_unk0x004b045c;
	p_probe->m_surfaceForce.m_x = 0.0f;
	p_probe->m_surfaceForce.m_y = 0.0f;
	p_probe->m_surfaceForce.m_z = 0.0f;

	LegoU32 index = p_probe - m_wheelProbes;
	m_ownerRacer->m_visuals.ClearWheelParticle(index);
	if (m_ownerRacer->m_forceFeedback) {
		m_ownerRacer->m_forceFeedback->SetSurfaceIntensity(0.0f);
	}
}

// FUNCTION: LEGORACERS 0x0042ad30
void RacerPhysics::SetThrust(LegoFloat p_thrust)
{
	LegoFloat amount = m_accelerationScale;
	amount *= p_thrust;
	RacerCarBody::SetThrust(amount);
}

// FUNCTION: LEGORACERS 0x0042ad50
void RacerPhysics::SetMaxSpeed(LegoFloat p_maxSpeed)
{
	LegoFloat amount = m_topSpeedScale;
	amount *= p_maxSpeed;
	RacerCarBody::SetMaxSpeed(amount);
}

// FUNCTION: LEGORACERS 0x0042ad70
void RacerPhysics::SetHandlingStat(LegoS32 p_stat)
{
	m_handlingStat = p_stat;
	m_handlingScale = static_cast<LegoFloat>(p_stat) * g_handlingStatScale + 0.7f;
}

// FUNCTION: LEGORACERS 0x0042ada0
void RacerPhysics::SetAccelerationStat(LegoS32 p_stat)
{
	m_accelerationStat = p_stat;
	m_accelerationScale = 1.0f - static_cast<LegoFloat>(50 - p_stat) * 0.001f;
}

// FUNCTION: LEGORACERS 0x0042add0
void RacerPhysics::SetTopSpeedStat(LegoS32 p_stat)
{
	m_topSpeedStat = p_stat;
	m_topSpeedScale = 1.0f - static_cast<LegoFloat>(50 - p_stat) * 0.001f;
	EndBoost();
}

// STUB: LEGORACERS 0x0042af90 FOLDED
SpatialSoundInstance* RacerPhysics::PlaySurfaceSound(LegoS32 p_soundId)
{
	if (m_surfaceSound != NULL) {
		if (p_soundId == m_surfaceSoundId) {
			return m_surfaceSound;
		}

		StopSurfaceSound();
	}

	m_surfaceSoundMs = 0;
	m_surfaceSoundId = p_soundId;
	m_surfaceSound = m_soundSource->AcquireSoundById(static_cast<LegoU32>(p_soundId));

	if (m_surfaceSound != NULL) {
		GolVec3 position;
		m_surfaceSound->SetDistanceRangeWithMinSquared(g_unk0x004b0430 * g_unk0x004b0430, g_unk0x004b0434);
		m_surfaceSound->Play(TRUE);
		m_carEntity->GetPosition(&position);
		m_surfaceSound->SetPositionAndVelocity(position, m_velocity);
	}

	return m_surfaceSound;
}

// FUNCTION: LEGORACERS 0x0042b060 FOLDED
void RacerPhysics::StopSurfaceSound()
{
	if (m_surfaceSound != NULL) {
		if (m_surfaceSound->IsPlaying()) {
			m_surfaceSound->Stop();
		}

		m_soundSource->ReleaseSound(m_surfaceSound);
		m_surfaceSoundId = -1;
		m_surfaceSound = NULL;
		m_surfaceSoundMs = 0;
	}
}

// FUNCTION: LEGORACERS 0x00440950
RacerRigidBody::RacerRigidBody()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00440970 FOLDED
void RacerRigidBody::Reset()
{
	m_body = NULL;
	m_centerOfMassLocal.m_x = 0.0f;
	m_centerOfMassLocal.m_y = 0.0f;
	m_centerOfMassLocal.m_z = 0.0f;
	m_centerOfMassWorld.m_x = 0.0f;
	m_centerOfMassWorld.m_y = 0.0f;
	m_centerOfMassWorld.m_z = 0.0f;

	m_angularVelocity.m_x = 0.0f;
	m_angularVelocity.m_y = 0.0f;
	m_angularVelocity.m_z = 0.0f;
	m_angularMomentum.m_x = 0.0f;
	m_angularMomentum.m_y = 0.0f;
	m_angularMomentum.m_z = 0.0f;
	m_force.m_x = 0.0f;
	m_force.m_y = 0.0f;
	m_force.m_z = 0.0f;
	m_torque.m_x = 0.0f;
	m_torque.m_y = 0.0f;
	m_torque.m_z = 0.0f;

	m_mass = 1.0f;
	m_inverseMass = 1.0f;
}

// FUNCTION: LEGORACERS 0x004409f0 FOLDED
void RacerRigidBody::Initialize(GolOrientedEntity* p_body, LegoFloat p_mass)
{
	if (m_body != NULL) {
		Reset();
	}

	LegoFloat inverseMass = p_mass;
	inverseMass = 1.0f / inverseMass;
	m_body = p_body;
	m_mass = p_mass;
	m_velocity.m_x = 0.0f;
	m_velocity.m_y = 0.0f;
	m_velocity.m_z = 0.0f;
	m_inverseMass = inverseMass;
	ComputeInertiaTensor();
	UpdateWorldInverseInertia();
}

// FUNCTION: LEGORACERS 0x00440a50 FOLDED
void RacerRigidBody::Destroy()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00440a60 FOLDED
void RacerRigidBody::UpdateWorldInverseInertia()
{
	m_body->FUN_00410f30(m_inverseInertiaTensor, &m_worldInverseInertia);
}

// FUNCTION: LEGORACERS 0x00440a80 FOLDED
void RacerRigidBody::UpdateAngularVelocity()
{
	LegoFloat value = m_worldInverseInertia.m_m[2][0] * m_angularMomentum.m_z;
	value += m_worldInverseInertia.m_m[1][0] * m_angularMomentum.m_y;
	m_angularVelocity.m_x = value + m_worldInverseInertia.m_m[0][0] * m_angularMomentum.m_x;

	value = m_worldInverseInertia.m_m[2][1] * m_angularMomentum.m_z;
	value += m_worldInverseInertia.m_m[1][1] * m_angularMomentum.m_y;
	m_angularVelocity.m_y = value + m_worldInverseInertia.m_m[0][1] * m_angularMomentum.m_x;

	value = m_worldInverseInertia.m_m[2][2] * m_angularMomentum.m_z;
	value += m_worldInverseInertia.m_m[1][2] * m_angularMomentum.m_y;
	m_angularVelocity.m_z = value + m_worldInverseInertia.m_m[0][2] * m_angularMomentum.m_x;
}

// FUNCTION: LEGORACERS 0x00440b10
void RacerCarBody::AddForce(GolVec3* p_force)
{
	m_force.m_x += p_force->m_x;
	m_force.m_y += p_force->m_y;
	m_force.m_z += p_force->m_z;
}

// FUNCTION: LEGORACERS 0x00440b50
void RacerCarBody::AddForceAtPoint(GolVec3* p_force, GolVec3* p_point)
{
	GolVec3 offset;
	offset.m_x = p_point->m_x - m_centerOfMassWorld.m_x;
	offset.m_y = p_point->m_y - m_centerOfMassWorld.m_y;
	offset.m_z = p_point->m_z - m_centerOfMassWorld.m_z;

	GolVec3 torque;
	LegoFloat value = offset.m_y;
	value *= p_force->m_z;
	LegoFloat crossValue = p_force->m_y;
	crossValue *= offset.m_z;
	torque.m_x = value - crossValue;

	value = offset.m_z;
	value *= p_force->m_x;
	crossValue = p_force->m_z;
	crossValue *= offset.m_x;
	torque.m_y = value - crossValue;

	value = p_force->m_y;
	value *= offset.m_x;
	crossValue = offset.m_y;
	crossValue *= p_force->m_x;
	torque.m_z = value - crossValue;

	m_torque.m_x += torque.m_x;
	m_torque.m_y += torque.m_y;
	m_torque.m_z += torque.m_z;
}

// FUNCTION: LEGORACERS 0x00440bd0
void RacerCarBody::AddAngularImpulse(GolVec3* p_impulse)
{
	GolVec3 local;
	m_body->RotateToLocal(*p_impulse, &local);

	GolVec3 transformed;
	transformed.m_x = m_inertiaTensor.m_m[0][0];
	transformed.m_x *= local.m_x;
	transformed.m_y = m_inertiaTensor.m_m[0][1];
	transformed.m_y *= local.m_x;
	transformed.m_z = m_inertiaTensor.m_m[0][2];
	transformed.m_z *= local.m_x;

	LegoFloat value = m_inertiaTensor.m_m[1][0];
	value *= local.m_y;
	transformed.m_x += value;
	value = m_inertiaTensor.m_m[1][1];
	value *= local.m_y;
	transformed.m_y += value;
	value = m_inertiaTensor.m_m[1][2];
	value *= local.m_y;
	transformed.m_z += value;

	value = m_inertiaTensor.m_m[2][0];
	value *= local.m_z;
	transformed.m_x += value;
	value = m_inertiaTensor.m_m[2][1];
	value *= local.m_z;
	transformed.m_y += value;
	value = m_inertiaTensor.m_m[2][2];
	value *= local.m_z;
	transformed.m_z += value;

	GolVec3 world;
	m_body->RotateToWorld(transformed, &world);
	m_angularMomentum.m_x += world.m_x;
	m_angularMomentum.m_y += world.m_y;
	m_angularMomentum.m_z += world.m_z;
}

// FUNCTION: LEGORACERS 0x00440cb0
void RacerCarBody::CancelAngularMomentum(GolVec3* p_direction, GolVec3* p_point)
{
	GolVec3 offset;
	offset.m_x = p_point->m_x - m_centerOfMassWorld.m_x;
	offset.m_y = p_point->m_y - m_centerOfMassWorld.m_y;
	offset.m_z = p_point->m_z - m_centerOfMassWorld.m_z;

	GolVec3 axis;
	LegoFloat value = offset.m_y;
	value *= p_direction->m_z;
	LegoFloat crossValue = p_direction->m_y;
	crossValue *= offset.m_z;
	axis.m_x = value - crossValue;

	value = offset.m_z;
	value *= p_direction->m_x;
	crossValue = p_direction->m_z;
	crossValue *= offset.m_x;
	axis.m_y = value - crossValue;

	value = p_direction->m_y;
	value *= offset.m_x;
	crossValue = offset.m_y;
	crossValue *= p_direction->m_x;
	axis.m_z = value - crossValue;
	GolMath::NormalizeVector3(axis, &axis);

	LegoFloat dot = axis.m_z;
	dot *= m_angularMomentum.m_z;
	value = m_angularMomentum.m_y;
	value *= axis.m_y;
	dot += value;
	value = axis.m_x;
	value *= m_angularMomentum.m_x;
	dot += value;

	if (dot >= 0.0f) {
		GolVec3 scaled;
		scaled.m_x = axis.m_x * dot;
		scaled.m_y = axis.m_y * dot;
		scaled.m_z = axis.m_z * dot;
		m_angularMomentum.m_x -= scaled.m_x;
		m_angularMomentum.m_y -= scaled.m_y;
		m_angularMomentum.m_z -= scaled.m_z;
	}
}

// FUNCTION: LEGORACERS 0x00440da0
void RacerCarBody::CancelAngularMomentumAlong(GolVec3* p_axis)
{
	LegoFloat dot = m_angularMomentum.m_z * p_axis->m_z;
	dot += m_angularMomentum.m_y * p_axis->m_y;
	dot += m_angularMomentum.m_x * p_axis->m_x;
	GolVec3 scaled;
	scaled.m_x = dot * p_axis->m_x;
	scaled.m_y = p_axis->m_y;
	scaled.m_y *= dot;
	scaled.m_z = dot * p_axis->m_z;
	m_angularMomentum.m_x -= scaled.m_x;
	m_angularMomentum.m_y -= scaled.m_y;
	m_angularMomentum.m_z -= scaled.m_z;
}

// FUNCTION: LEGORACERS 0x00440e10 FOLDED
void RacerRigidBody::Update(LegoS32 p_elapsedMs)
{
	UpdateAngularVelocity();

	LegoFloat elapsed = static_cast<LegoFloat>(p_elapsedMs);
	{
		GolVec3 linearDelta;
		linearDelta.m_x = m_force.m_x;
		linearDelta.m_x *= elapsed;
		linearDelta.m_x *= m_inverseMass;
		linearDelta.m_y = m_force.m_y;
		linearDelta.m_y *= elapsed;
		linearDelta.m_y *= m_inverseMass;
		linearDelta.m_z = m_force.m_z;
		linearDelta.m_z *= elapsed;
		linearDelta.m_z *= m_inverseMass;

		LegoFloat halfElapsed = elapsed * 0.5f;

		GolVec3 position;
		m_body->GetPosition(&position);
		LegoFloat velocityTerm = m_velocity.m_x;
		velocityTerm *= elapsed;
		LegoFloat accelerationTerm = halfElapsed;
		accelerationTerm *= linearDelta.m_x;
		position.m_x += velocityTerm + accelerationTerm;

		velocityTerm = m_velocity.m_y;
		velocityTerm *= elapsed;
		accelerationTerm = halfElapsed;
		accelerationTerm *= linearDelta.m_y;
		position.m_y += velocityTerm + accelerationTerm;

		velocityTerm = m_velocity.m_z;
		velocityTerm *= elapsed;
		accelerationTerm = halfElapsed;
		accelerationTerm *= linearDelta.m_z;
		position.m_z += velocityTerm + accelerationTerm;
		m_body->SetPosition(position);

		if (linearDelta.m_x == 0.0f && linearDelta.m_y == 0.0f && linearDelta.m_z == 0.0f) {
			const LegoFloat velocityThreshold = 9.9999997e-05f;

			if (m_velocity.m_x < velocityThreshold && -velocityThreshold < m_velocity.m_x) {
				m_velocity.m_x = 0.0f;
			}
			if (m_velocity.m_y < velocityThreshold && -velocityThreshold < m_velocity.m_y) {
				m_velocity.m_y = 0.0f;
			}
			if (m_velocity.m_z < velocityThreshold && -velocityThreshold < m_velocity.m_z) {
				m_velocity.m_z = 0.0f;
			}
		}

		m_velocity.m_x += linearDelta.m_x;
		m_velocity.m_y += linearDelta.m_y;
		m_velocity.m_z += linearDelta.m_z;
	}

	LegoFloat angularStepZ;
	LegoFloat angularStepY;
	LegoFloat angularStepX;
	angularStepX = m_angularVelocity.m_x;
	angularStepX *= elapsed;
	angularStepY = m_angularVelocity.m_y;
	angularStepY *= elapsed;
	angularStepZ = m_angularVelocity.m_z;
	angularStepZ *= elapsed;

	GolVec3 right;
	GolVec3 forward;
	m_body->GetAxes(&right, &forward);

	GolVec3 newRight;
	LegoFloat value = right.m_y;
	value *= angularStepZ;
	newRight.m_x = right.m_x - value;
	value = right.m_z;
	value *= angularStepY;
	newRight.m_x += value;

	value = right.m_x;
	value *= angularStepZ;
	newRight.m_y = right.m_y + value;
	value = right.m_z;
	value *= angularStepX;
	newRight.m_y -= value;

	value = right.m_x;
	value *= angularStepY;
	newRight.m_z = right.m_z - value;
	value = right.m_y;
	value *= angularStepX;
	newRight.m_z += value;

	GolVec3 newForward;
	value = forward.m_y;
	value *= angularStepZ;
	newForward.m_x = forward.m_x - value;
	value = forward.m_z;
	value *= angularStepY;
	newForward.m_x += value;

	value = forward.m_x;
	value *= angularStepZ;
	newForward.m_y = forward.m_y + value;
	value = forward.m_z;
	value *= angularStepX;
	newForward.m_y -= value;

	value = forward.m_x;
	value *= angularStepY;
	newForward.m_z = forward.m_z - value;
	value = forward.m_y;
	value *= angularStepX;
	newForward.m_z += value;
	GolOrientedEntity* entity = m_body;
	entity->SetDirectionUp(newRight, newForward);

	LegoFloat angularDeltaY = m_torque.m_y;
	angularDeltaY *= elapsed;
	LegoFloat angularDeltaZ = m_torque.m_z;
	angularDeltaZ *= elapsed;
	LegoFloat velocityTerm = elapsed;
	velocityTerm *= m_torque.m_x;
	m_angularMomentum.m_x += velocityTerm;
	m_angularMomentum.m_y += angularDeltaY;
	m_angularMomentum.m_z += angularDeltaZ;

	if (m_torque.m_x == 0.0f && m_torque.m_y == 0.0f && m_torque.m_z == 0.0f) {
		LegoFloat angularStepLengthSq =
			angularStepX * angularStepX + angularStepY * angularStepY + angularStepZ * angularStepZ;
		if (angularStepLengthSq < 0.00060000003f) {
			m_angularVelocity.m_x = 0.0f;
			m_angularVelocity.m_y = 0.0f;
			m_angularVelocity.m_z = 0.0f;
			m_angularMomentum.m_x = 0.0f;
			m_angularMomentum.m_y = 0.0f;
			m_angularMomentum.m_z = 0.0f;
		}
	}

	m_force.m_x = 0.0f;
	m_force.m_y = 0.0f;
	m_force.m_z = 0.0f;
	m_torque.m_x = 0.0f;
	m_torque.m_y = 0.0f;
	m_torque.m_z = 0.0f;
}

// FUNCTION: LEGORACERS 0x00441190
void RacerCarBody::SetCenterOfMass(GolVec3* p_centerOfMass)
{
	::memcpy(&m_centerOfMassLocal, p_centerOfMass, sizeof(m_centerOfMassLocal));
	m_body->LocalToWorld(m_centerOfMassLocal, &m_centerOfMassWorld);
}

// FUNCTION: LEGORACERS 0x004411c0 FOLDED
GolOrientedEntity* RacerRigidBody::GetEntity()
{
	return m_body;
}

// FUNCTION: LEGORACERS 0x004411d0
RacerBoxBody::RacerBoxBody()
{
	m_sizeX = 0.0f;
	m_sizeY = 0.0f;
	m_sizeZ = 0.0f;
	m_speedRampScale = 0.0f;
	m_racer = NULL;
}

// FUNCTION: LEGORACERS 0x00441210
void RacerBoxBody::Initialize(
	GolOrientedEntity* p_body,
	LegoFloat p_mass,
	LegoFloat p_sizeX,
	LegoFloat p_sizeY,
	LegoFloat p_sizeZ
)
{
	m_sizeX = p_sizeX;
	m_sizeY = p_sizeY;
	m_sizeZ = p_sizeZ;
	m_speedRampScale = 1.0f;
	m_racer = NULL;
	RacerRigidBody::Initialize(p_body, p_mass);
}

// FUNCTION: LEGORACERS 0x00441260 FOLDED
void RacerBoxBody::ComputeInertiaTensor()
{
	LegoFloat xSquared = m_sizeX * m_sizeX;
	LegoFloat ySquared = m_sizeY * m_sizeY;
	LegoFloat zSquared = m_sizeZ * m_sizeZ;
	LegoFloat scaledMass = m_mass / m_sizeX;

	m_inertiaTensor.m_m[0][1] = 0.0f;
	m_inertiaTensor.m_m[0][2] = 0.0f;
	m_inertiaTensor.m_m[1][0] = 0.0f;
	m_inertiaTensor.m_m[1][2] = 0.0f;
	m_inertiaTensor.m_m[2][0] = 0.0f;
	m_inertiaTensor.m_m[2][1] = 0.0f;
	m_inverseInertiaTensor.m_m[0][1] = 0.0f;
	m_inverseInertiaTensor.m_m[0][2] = 0.0f;
	m_inverseInertiaTensor.m_m[1][0] = 0.0f;
	m_inverseInertiaTensor.m_m[1][2] = 0.0f;
	m_inverseInertiaTensor.m_m[2][0] = 0.0f;
	m_inverseInertiaTensor.m_m[2][1] = 0.0f;

	LegoFloat xInertia = scaledMass * (zSquared + ySquared) * g_boxInertiaFactor;
	m_inertiaTensor.m_m[0][0] = xInertia;
	LegoFloat yInertia = (m_mass / m_sizeY) * (zSquared + xSquared) * g_boxInertiaFactor;
	m_inertiaTensor.m_m[1][1] = yInertia;
	LegoFloat zInertia = (m_mass / m_sizeZ) * (ySquared + xSquared) * g_boxInertiaFactor;
	m_inertiaTensor.m_m[2][2] = zInertia;
	m_inverseInertiaTensor.m_m[0][0] = 1.0f / xInertia;
	m_inverseInertiaTensor.m_m[1][1] = 1.0f / yInertia;
	m_inverseInertiaTensor.m_m[2][2] = 1.0f / zInertia;
}

// FUNCTION: LEGORACERS 0x00444b10
RacerCarBody::RacerCarBody()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00444b40
void RacerCarBody::Reset()
{
	m_carEntity = NULL;
	::memset(m_collisionWorlds, 0, sizeof(m_collisionWorlds));
	m_collisionWorldCount = 0;
	m_soundSource = NULL;
	m_gravityForce = 0;
	m_gravity = g_carGravity;
	m_facingDirection.m_x = 1.0f;
	m_facingDirection.m_y = 0.0f;
	m_facingDirection.m_z = 0.0f;
	m_supportNormal.m_x = 0.0f;
	m_supportNormal.m_y = 0.0f;
	m_supportNormal.m_z = 0.0f;
	m_supportForce.m_x = 0.0f;
	m_supportForce.m_y = 0.0f;
	m_supportForce.m_z = 0.0f;
	m_externalForce0.m_x = 0;
	m_externalForce0.m_y = 0;
	m_externalForce0.m_z = 0;
	m_externalForce1.m_x = 0;
	m_externalForce1.m_y = 0;
	m_externalForce1.m_z = 0;
	m_contactOffsetX = 0;
	m_contactOffsetY = 0;
	m_unk0x654 = -10.95f;
	m_rideHeight = g_defaultRideHeight;
	m_forwardVelocity.m_x = 0.0f;
	m_forwardVelocity.m_y = 0.0f;
	m_forwardVelocity.m_z = 0.0f;
	m_velocityDirection.m_x = 1.0f;
	m_velocityDirection.m_y = 0.0f;
	m_velocityDirection.m_z = 0.0f;
	m_forwardSpeed = 0.0f;
	m_speed = 0;
	m_unk0x5f0 = 0;
	m_slipRatio = 0;
	m_thrust = 0;
	m_unk0x62c = 0;
	m_centripetalForce = 0;
	m_turnRadius = 0;
	m_yawRate = 0;
	m_savedPosition.m_x = 0.0f;
	m_savedPosition.m_y = 0.0f;
	m_savedPosition.m_z = 0.0f;
	m_wallContact = 0;
	m_stepRemainderMs = 0;

	for (LegoU32 i = 0; i < sizeOfArray(m_bodyPointsLocal); i++) {
		m_bodyPointsLocal[i].m_x = 0.0f;
		m_bodyPointsLocal[i].m_y = 0.0f;
		m_bodyPointsLocal[i].m_z = 0.0f;
		m_bodyPointsWorld[i].m_x = 0.0f;
		m_bodyPointsWorld[i].m_y = 0.0f;
		m_bodyPointsWorld[i].m_z = 0.0f;
		m_bodyPointHit[i] = 0;
	}

	::memset(m_wheelProbes, 0, sizeof(m_wheelProbes));
	::memset(m_planeCache, 0, sizeof(m_planeCache));
	m_planeCacheCount = 0;
	m_contactCount = 0;
	m_rollImpulseMs = 0;
	m_pitchImpulseMs = 0;
	m_yawImpulseMs = 0;
	m_spinStopAtMs = 0;
	m_spinPeriodMs = 0;
	m_flags = 0;
	m_steeringGain = 1.0f;
	m_steeringAlignmentMin = -1.0f;
	m_facingLagMax = 3.1415927f;
	m_spinSound = NULL;
	m_skidSound = NULL;
	m_soundsEnabled = 1;
	m_airborneMs = 0;
	m_slideLift = 0;
	m_slideLiftTarget = g_defaultSlideLiftTarget;
	m_slideLiftRate = g_defaultSlideLiftRate;
	m_slideBankTarget = 0;
	m_slideBankAngle = 0;
	m_visualBankAngle = 0;
	LegoU32 unk0x6d8 = g_defaultPowerslideFactorBits;
	m_spinOutMs = 0;
	m_powerslideFactorBits = unk0x6d8;
	SetMaxSpeed(g_defaultMaxSpeed);
	m_gripScale = 1.0f;
}

// FUNCTION: LEGORACERS 0x00444d90
void RacerCarBody::Initialize(
	GolAnimatedEntity* p_carEntity,
	GolBoundedEntity* p_trackWorld,
	GolBoundedEntity* p_triggerWorld,
	RacerSoundSource* p_soundSource,
	LegoFloat p_mass,
	LegoFloat p_sizeX,
	LegoFloat p_sizeY,
	LegoFloat p_sizeZ
)
{
	RacerCarBody* field = this;

	if (field->m_body != NULL) {
		field->Destroy();
	}

	field->m_collisionWorldCount = 1;
	field->m_collisionWorlds[0] = p_trackWorld;

	if (p_triggerWorld != NULL) {
		field->m_collisionWorlds[1] = p_triggerWorld;
		field->m_collisionWorldCount = 2;
	}

	field->m_soundSource = p_soundSource;
	field->m_carEntity = p_carEntity;

	GolOrientedEntity* entity = &field->m_physicsEntity;
	entity->CopyOrientationFrom(*p_carEntity);
	entity->CopyPositionFrom(*p_carEntity);
	field->RacerBoxBody::Initialize(entity, p_mass, p_sizeX, p_sizeY, p_sizeZ);

	LegoFloat scaledAngle = p_mass;
	scaledAngle *= 0.001f;
	const GolMatrix3& orientation = entity->GetOrientation();
	field->m_facingDirection.m_x = orientation.m_m[0][0];
	field->m_facingDirection.m_y = orientation.m_m[0][1];
	field->m_facingDirection.m_z = orientation.m_m[0][2];
	scaledAngle *= 0.001f;
	field->m_massScale = scaledAngle;
}

// FUNCTION: LEGORACERS 0x00444e90
void RacerCarBody::Destroy()
{
	Reset();
	RacerRigidBody::Destroy();

	if (m_spinSound) {
		m_soundSource->ReleaseSound(m_spinSound);
		m_spinSound = NULL;
	}

	if (m_skidSound) {
		m_soundSource->ReleaseSound(m_skidSound);
		m_skidSound = NULL;
	}
}

// FUNCTION: LEGORACERS 0x00444ef0
void RacerCarBody::Update(LegoS32 p_elapsedMs)
{
	LegoU32 elapsedMs = p_elapsedMs;
	LegoBool32 recoveredCollision = FALSE;
	GolVec3 direction;
	GolVec3 position;

	ClearWallContacts();

	if (m_flags & c_flagSpinOut) {
		if (elapsedMs >= m_spinOutMs) {
			EndSpinOut();
		}
		else {
			m_spinOutMs -= elapsedMs;
		}
	}

	LegoU32 flags = m_flags;
	if (flags & c_flagSpinning) {
		if (flags & c_flagSpinFresh) {
			m_flags = flags & ~c_flagSpinFresh;
		}
		else {
			LegoU32 timer = m_yawImpulseMs;
			if (elapsedMs >= timer) {
				if (timer != 0) {
					elapsedMs = timer;
					m_yawImpulseMs = 0;
				}
				else {
					EndSpin();
				}
			}
			else {
				m_yawImpulseMs = timer - elapsedMs;
			}
		}
	}
	else {
		LegoU32 timer = m_yawImpulseMs;
		if (elapsedMs >= timer) {
			const GolVec3& forward = m_physicsEntity.GetOrientation().m_rows[2];
			m_yawImpulseMs = 0;
			direction.m_x = forward.m_x;
			direction.m_y = forward.m_y;
			direction.m_z = forward.m_z;
			CancelAngularMomentumAlong(&direction);
			m_flags &= ~c_flagYawImpulse;
		}
		else {
			m_yawImpulseMs = timer - elapsedMs;
		}
	}

	if (elapsedMs > m_spinStopAtMs) {
		m_spinStopAtMs = 0;
	}
	else {
		m_spinStopAtMs -= elapsedMs;
	}

	if (m_rollImpulseMs != 0) {
		if (elapsedMs >= m_rollImpulseMs) {
			const GolVec3& right = m_physicsEntity.GetOrientation().m_rows[0];
			m_rollImpulseMs = 0;
			direction.m_x = right.m_x;
			direction.m_y = right.m_y;
			direction.m_z = right.m_z;
			CancelAngularMomentumAlong(&direction);
		}
		else {
			m_rollImpulseMs -= elapsedMs;
		}
	}

	if (m_pitchImpulseMs != 0) {
		if (elapsedMs >= m_pitchImpulseMs) {
			const GolVec3& up = m_physicsEntity.GetOrientation().m_rows[1];
			m_pitchImpulseMs = 0;
			direction.m_x = up.m_x;
			direction.m_y = up.m_y;
			direction.m_z = up.m_z;
			CancelAngularMomentumAlong(&direction);
		}
		else {
			m_pitchImpulseMs -= elapsedMs;
		}
	}

	if (m_flags & c_flagSliding) {
		ComputeSlideBankTarget();
	}

	m_stepRemainderMs = elapsedMs;
	SaveState();

	for (;;) {
		if (m_wallContact == 0) {
			if (elapsedMs == 0) {
				break;
			}
		}

		if (elapsedMs != 0) {
			AccumulateForces();
			RacerRigidBody::Update(elapsedMs);
			LimitUprightTilt();

			if (m_flags & c_flagSliding) {
				UpdateSlideBank(elapsedMs);
				UpdateSlideContacts(elapsedMs);
			}
			else {
				UpdateWheelContacts(elapsedMs);
			}

			UpdateFacingDirection(elapsedMs);
			UpdateVelocityStats();
			UpdateWheelSurfaces();
			m_physicsEntity.LocalToWorld(m_centerOfMassLocal, &m_centerOfMassWorld);
			UpdateWorldInverseInertia();
		}

		if (m_wallContact != 0) {
			if (elapsedMs != 0) {
				LegoU32 result = ResolveWallCollisions(elapsedMs, !(m_flags & c_flagNoTrackCollision));
				if (m_wallContact != 0) {
					elapsedMs = result;
					continue;
				}
			}

			ApplyWallResponse();
			UpdateVelocityStats();
			recoveredCollision = TRUE;
			ClearWallContacts();
			SaveState();
			m_stepRemainderMs -= elapsedMs;
			elapsedMs = m_stepRemainderMs;
			continue;
		}

		elapsedMs = ResolveWallCollisions(elapsedMs, !(m_flags & c_flagNoTrackCollision));
		if (elapsedMs != 0) {
			continue;
		}

		if (!recoveredCollision) {
			continue;
		}

		break;
	}

	if (recoveredCollision) {
		m_wallContact = TRUE;
	}

	if (m_contactCount == 0) {
		m_airborneMs += p_elapsedMs;
	}
	else {
		m_airborneMs = 0;
	}

	m_physicsEntity.GetPosition(&position);

	if (m_skidSound != NULL) {
		m_skidSound->SetPosition(position);
		m_skidSound->SetVelocity(m_velocity);

		if (m_flags & c_flagPowerslide) {
			m_skidSound->SetFrequencyScale(
				(m_powerslideFactor * 0.5f + 1.4f) - ((0.17f - m_forwardSpeed) * g_ghostSpeedScale)
			);
		}
		else {
			m_skidSound->SetFrequencyScale(1.4f - ((0.17f - m_forwardSpeed) * g_ghostSpeedScale));
		}
	}

	if (m_spinSound != NULL) {
		m_spinSound->SetPosition(position);
	}

	UpdateVisualBank(p_elapsedMs);
}

// FUNCTION: LEGORACERS 0x004452b0
void RacerCarBody::UpdateVisualBank(LegoS32 p_elapsedMs)
{
	LegoFloat targetAngle;
	LegoFloat minTargetAngle;

	if (m_flags & c_flagSliding) {
		targetAngle = -m_slideBankAngle;
	}
	else if (m_flags & c_flagPowerslide) {
		if (m_turnRadius <= -g_minTurnRadius || m_turnRadius >= g_minTurnRadius) {
			targetAngle = m_turnRadius;
			targetAngle = 1.0f / targetAngle;
			targetAngle = -targetAngle;
			targetAngle *= g_minTurnRadius;
			targetAngle *= m_powerslideFactor;

			LegoFloat speedScale = m_speed;
			speedScale *= g_floatConst1000;
			speedScale /= m_maxSpeed;
			targetAngle *= speedScale;

			if (targetAngle > 0.5f) {
				targetAngle = 0.5f;
			}
			else {
				minTargetAngle = g_unk0x004b043c;
				minTargetAngle = -minTargetAngle;
				if (targetAngle < minTargetAngle) {
					targetAngle = minTargetAngle;
				}
			}
		}
		else {
			targetAngle = 0.0f;
		}
	}
	else {
		targetAngle = 0.0f;
	}

	if (targetAngle < m_visualBankAngle) {
		m_visualBankAngle -= static_cast<LegoFloat>(p_elapsedMs) * 0.0020000001f;
		if (m_visualBankAngle < targetAngle) {
			m_visualBankAngle = targetAngle;
		}
	}
	else if (targetAngle > m_visualBankAngle) {
		m_visualBankAngle += static_cast<LegoFloat>(p_elapsedMs) * 0.0020000001f;
		if (m_visualBankAngle > targetAngle) {
			m_visualBankAngle = targetAngle;
		}
	}

	LegoFloat angleMagnitude = m_visualBankAngle;
	if (angleMagnitude < 0.0f) {
		angleMagnitude = -angleMagnitude;
	}

	if (angleMagnitude != 0.0f) {
		GolVec3 position;
		GolVec3 right;
		GolVec3 forward;
		GolVec3 rotatedForward;

		m_physicsEntity.GetAxes(&right, &forward);
		m_physicsEntity.GetPosition(&position);

		LegoFloat offset = static_cast<LegoFloat>(tan(angleMagnitude)) * (m_trackWidth * 0.5f);
		GolMath::RotateAboutAxis(&forward, &rotatedForward, &right, m_visualBankAngle);
		position.m_z += offset;
		m_carEntity->SetDirectionUp(right, rotatedForward);
		m_carEntity->SetPosition(position);
	}
	else {
		GolOrientedEntity* entity = m_carEntity;
		entity->CopyOrientationFrom(m_physicsEntity);
		entity->CopyPositionFrom(m_physicsEntity);
	}
}

// FUNCTION: LEGORACERS 0x00445500
void RacerCarBody::AccumulateForces()
{
	LegoFloat steeringAmount = 0.0f;
	GolVec3 force;

	LegoFloat baseForce = -m_gravity;
	baseForce *= m_massScale;
	LegoU8 flags0x6c0 = static_cast<LegoU8>(m_flags);
	m_yawRate = 0.0f;
	m_gravityForce = baseForce;

	if (flags0x6c0 & c_flagSteering) {
		const GolVec3& right = m_physicsEntity.GetOrientation().m_rows[0];
		steeringAmount = right.m_x * m_velocityDirection.m_x + right.m_y * m_velocityDirection.m_y +
						 right.m_z * m_velocityDirection.m_z;
		if (steeringAmount <= 0.0f) {
			StopSteering();
		}
	}

	if (m_contactCount == 0) {
		force.m_x = 0.0f;
		force.m_z = m_gravityForce * 4.0f;
		force.m_y = 0.0f;
		AddForce(&force);

		LegoFloat scale = m_thrust * m_massScale;
		force.m_x = m_facingDirection.m_x * scale;
		force.m_y = m_facingDirection.m_y;
		force.m_y *= scale;
		force.m_z = m_facingDirection.m_z;
		force.m_z *= scale;
		LegoFloat forwardLimit = -m_gravityForce;
		if (force.m_z > forwardLimit) {
			force.m_z = forwardLimit;
		}
		AddForce(&force);

		if (m_turnRadius != 0.0f && !(m_flags & c_flagYawImpulse)) {
			ApplyYawImpulse(m_forwardSpeed / m_turnRadius, 200);
		}
	}
	else {
		LegoFloat average0x054 = GetAverageSupportThreshold();
		LegoFloat average0x058 = GetAverageFriction();
		LegoFloat forceMagnitude = static_cast<LegoFloat>(sqrt(
			m_supportForce.m_z * m_supportForce.m_z + m_supportForce.m_y * m_supportForce.m_y +
			m_supportForce.m_x * m_supportForce.m_x
		));
		LegoFloat forceThreshold = m_gravity;
		forceThreshold *= m_massScale;
		forceThreshold *= average0x054;
		if (forceMagnitude > forceThreshold) {
			AddForce(&m_supportForce);
		}

		if (m_flags & c_flagSliding) {
			WheelProbe* entry = m_wheelProbes;
			GolVec3* axlePoint = &m_frontAxleMid;
			for (LegoU32 i = 0; i < 2; i++) {
				if (entry->m_flags & 1) {
					if (m_contactCount < 1) {
						AddForceAtPoint(&entry->m_contactForce, axlePoint);
					}

					CancelAngularMomentum(&m_supportNormal, &m_frontAxleMid + (i == 0));
				}
				entry++;
				axlePoint++;
			}
		}
		else if (m_rollImpulseMs == 0 && m_pitchImpulseMs == 0) {
			WheelProbe* entry = m_wheelProbes;
			const LegoS32* entryIndex = g_wheelDiagonalIndices;
			while (entryIndex < &g_wheelDiagonalIndices[sizeOfArray(m_wheelProbes)]) {
				if (entry->m_flags & 1) {
					if (m_contactCount < 3) {
						AddForceAtPoint(&entry->m_contactForce, &entry->m_wheelPosition);
					}

					CancelAngularMomentum(&m_supportNormal, &m_wheelProbes[*entryIndex].m_wheelPosition);
				}
				entry++;
				entryIndex++;
			}
		}

		LegoFloat contactScale;
		if (!(m_flags & (c_flagSteering | c_flagSpinning))) {
			contactScale = 1.0f;
		}
		else {
			LegoFloat scale = m_gravity;
			scale *= m_massScale;
			scale *= average0x058;
			scale *= m_slipRatio;
			scale = -scale;
			force.m_x = m_velocityDirection.m_x * scale;
			force.m_y = m_velocityDirection.m_y;
			force.m_y *= scale;
			force.m_z = m_velocityDirection.m_z;
			force.m_z *= scale;
			AddForce(&force);
			contactScale = 1.0f - m_slipRatio;
		}

		if (!(m_flags & c_flagSpinning) && !(m_flags & c_flagYawImpulse)) {
			LegoFloat scale = m_mass * -0.0099999998f;
			scale *= contactScale;
			force.m_x = m_lateralVelocity.m_x * scale;
			force.m_y = m_lateralVelocity.m_y;
			force.m_y *= scale;
			force.m_z = m_lateralVelocity.m_z;
			force.m_z *= scale;
			AddForce(&force);

			if (m_thrust != 0.0f) {
				scale = m_thrust * m_massScale;
				if (m_contactCount >= 3 && !(m_flags & c_flagSteering)) {
					const GolVec3& right = m_physicsEntity.GetOrientation().m_rows[0];
					force.m_x = right.m_x * scale;
					force.m_y = right.m_y;
					force.m_y *= scale;
					force.m_z = right.m_z;
					force.m_z *= scale;
				}
				else {
					force.m_x = m_facingDirection.m_x * scale;
					force.m_y = m_facingDirection.m_y;
					force.m_y *= scale;
					force.m_z = m_facingDirection.m_z;
					force.m_z *= scale;
				}
				AddForce(&force);
			}
			else {
				scale = m_mass * -0.001f;
				force.m_x = m_forwardVelocity.m_x * scale;
				force.m_y = m_forwardVelocity.m_y;
				force.m_y *= scale;
				force.m_z = m_forwardVelocity.m_z;
				force.m_z *= scale;
				AddForce(&force);
			}

			if (m_turnRadius != 0.0f) {
				force.m_x = -m_facingDirection.m_y;
				force.m_y = m_facingDirection.m_x;
				force.m_z = 0.0f;
				GolMath::NormalizeVector3(force, &force);

				scale = m_mass;
				scale *= m_forwardSpeed;
				scale *= m_forwardSpeed;
				scale /= m_turnRadius;
				m_centripetalForce = scale;
				force.m_x = force.m_x * scale;
				force.m_y *= scale;
				force.m_z *= scale;
				AddForce(&force);

				if (m_flags & c_flagSteering) {
					if (steeringAmount >= m_steeringAlignmentMin) {
						scale = m_forwardSpeed / m_turnRadius;
						m_yawRate = scale;
						steeringAmount = m_steeringGain;
						steeringAmount *= scale;
					}
					else {
						steeringAmount = 0.0f;
					}
				}
				else {
					if (m_forwardSpeed < 0.03f && m_forwardSpeed > 0.00050000002f) {
						scale = 0.03f / m_turnRadius;
					}
					else {
						scale = m_forwardSpeed / m_turnRadius;
					}

					m_yawRate = scale;
					steeringAmount = scale;
				}
				ApplyYawImpulse(steeringAmount, 200);
			}
		}
		else {
			LegoFloat scale = m_mass * -0.0020000001f;
			force.m_x = m_lateralVelocity.m_x * scale;
			force.m_y = m_lateralVelocity.m_y;
			force.m_y *= scale;
			force.m_z = m_lateralVelocity.m_z;
			force.m_z *= scale;
			AddForce(&force);
		}
	}

	if (!(m_flags & (c_flagSliding | c_flagSpinOut))) {
		GolVec3 sum;
		sum.m_x = 0.0f;
		sum.m_y = 0.0f;
		sum.m_z = 0.0f;
		WheelProbe* entry = m_wheelProbes;
		while (entry < &m_wheelProbes[sizeOfArray(m_wheelProbes)]) {
			sum.m_x += entry->m_surfaceForce.m_x;
			sum.m_y += entry->m_surfaceForce.m_y;
			sum.m_z += entry->m_surfaceForce.m_z;
			entry++;
		}

		LegoFloat scale = m_massScale * 0.25f;
		force.m_x = sum.m_x * scale;
		force.m_y = sum.m_y;
		force.m_y *= scale;
		force.m_z = sum.m_z;
		force.m_z *= scale;
		AddForce(&force);
	}

	LegoFloat drag = 0.0f;
	if (!(m_flags & c_flagSliding)) {
		WheelProbe* entry = m_wheelProbes;
		while (entry < &m_wheelProbes[sizeOfArray(m_wheelProbes)]) {
			drag += entry->m_rollingResistance;
			entry++;
		}
		drag *= 0.25f;
	}
	drag += m_dragCoefficient;
	drag *= m_speed;
	drag = -drag;
	force.m_x = m_velocity.m_x * drag;
	force.m_y = m_velocity.m_y;
	force.m_y *= drag;
	force.m_z = m_velocity.m_z;
	force.m_z *= drag;
	AddForce(&force);

	if (m_flags & c_flagExternalForce0) {
		AddForce(&m_externalForce0);
	}

	if (m_flags & c_flagExternalForce1) {
		AddForce(&m_externalForce1);
	}
}

// FUNCTION: LEGORACERS 0x00445bb0
void RacerCarBody::ApplyPitchImpulse(LegoFloat p_rate, LegoU32 p_durationMs)
{
	if (m_rollImpulseMs) {
		return;
	}

	m_pitchImpulseMs = p_durationMs;

	const GolMatrix34& transform = m_physicsEntity.GetTransform();
	GolVec3 direction;
	direction.m_x = transform.m_m[1][0];
	direction.m_y = transform.m_m[1][1];
	direction.m_z = transform.m_m[1][2];
	CancelAngularMomentumAlong(&direction);

	direction.m_x *= p_rate;
	direction.m_y *= p_rate;
	direction.m_z *= p_rate;
	AddAngularImpulse(&direction);
}

// FUNCTION: LEGORACERS 0x00445c30
void RacerCarBody::ApplyYawImpulse(LegoFloat p_rate, LegoU32 p_durationMs)
{
	m_yawImpulseMs = p_durationMs;

	const GolMatrix34& transform = m_physicsEntity.GetTransform();
	GolVec3 direction;
	direction.m_x = transform.m_m[2][0];
	direction.m_y = transform.m_m[2][1];
	direction.m_z = transform.m_m[2][2];
	CancelAngularMomentumAlong(&direction);

	direction.m_x *= p_rate;
	direction.m_y *= p_rate;
	direction.m_z *= p_rate;
	AddAngularImpulse(&direction);
}

// FUNCTION: LEGORACERS 0x00445d10
void RacerCarBody::LimitUprightTilt()
{
	GolVec3 forward;
	GolVec3 axis;
	GolVec3 right;

	m_physicsEntity.GetAxes(&right, &forward);
	if (forward.m_z < g_uprightTiltMinCosine) {
		axis.m_x = forward.m_y;
		axis.m_y = -forward.m_x;
		axis.m_z = 0.0f;
		GolMath::NormalizeVector3(axis, &axis);

		LegoFloat sine;
		LegoFloat cosine;
		GolMath::SinCos(g_uprightTiltMaxAngle, &sine, &cosine);

		forward.m_x = -(sine * axis.m_y);
		forward.m_y = sine * axis.m_x;
		forward.m_z = cosine;
		m_physicsEntity.FUN_00410b00(forward, right);
	}
}

// STUB: LEGORACERS 0x00445dc0
void RacerCarBody::UpdateWheelContacts(LegoS32 p_elapsedMs)
{
	LegoU32 flags = m_flags;
	if (flags & c_flagAtRest) {
		if (m_velocity.m_x == 0.0f && m_velocity.m_y == 0.0f && m_velocity.m_z == 0.0f &&
			m_angularVelocity.m_x == 0.0f && m_angularVelocity.m_y == 0.0f && m_angularVelocity.m_z == 0.0f) {
			return;
		}

		m_flags = flags & ~c_flagAtRest;
	}

	WheelProbe* entries = m_wheelProbes;
	WheelProbe* entriesEnd = &m_wheelProbes[sizeOfArray(m_wheelProbes)];
	AgePlaneCache();

	LegoU32 previousContactCount = m_contactCount;

	GolVec3 position;
	m_physicsEntity.GetPosition(&position);

	LegoFloat verticalOffset = -(position.m_z - m_savedPosition.m_z);
	if (verticalOffset < 0.0f) {
		verticalOffset = 0.0f;
	}

	LegoFloat sweepHeight = m_carEntity->GetBoundsRadius() + verticalOffset;
	LegoFloat sweepDistance;
	LegoBool32 resetFromAir;
	if (m_contactCount != 0 && !(m_flags & c_flagSpinOut)) {
		sweepDistance = static_cast<LegoFloat>(p_elapsedMs) * g_wheelSupportSweepScale;
		resetFromAir = FALSE;
	}
	else {
		sweepDistance = 0.0f;
		resetFromAir = TRUE;
	}

	m_contactCount = 0;
	ComputeWheelPositions();

	WheelProbe* entry;
	for (entry = entries; entry < entriesEnd; entry++) {
		entry->m_flags &= ~(WheelProbe::c_flagContact | WheelProbe::c_flagHit);
		entry->m_contactForce.m_z = 0.0f;
		entry->m_contactForce.m_y = 0.0f;
		entry->m_contactForce.m_x = 0.0f;
		entry->m_hitDistanceSquared = -FLT_MAX;
	}

	LegoFloat bestDistance = -FLT_MAX;
	WheelProbe* selectedEntry = NULL;
	GolBoundingVolume::HitTriangle* eventContext = g_carBodySavedWheels.GetEventContext();
	GolBoundingVolume::HitTriangle* collisionContext = eventContext;

	for (LegoU32 resourceIndex = 1; resourceIndex < m_collisionWorldCount; resourceIndex++) {
		GolBoundedEntity* resource = m_collisionWorlds[resourceIndex];
		ComputeWheelRaysLocal(resource, sweepHeight, sweepDistance);

		entry = entries;
		while (entry < entriesEnd) {
			if (!(entry->m_flags & WheelProbe::c_flagHit)) {
				GolBoundingVolume* query = resource->GetUnk0x58();
				query->SetUnk0x24(resource->GetMaterialTable());

				GolVec3 hitPoint;
				RaceEventRecord* hitRecord;
				if (query->FUN_00403fa0(
						&entry->m_rayStart,
						&entry->m_rayEnd,
						collisionContext,
						&hitPoint,
						&hitRecord,
						NULL
					)) {
					entry->m_hitRecord = hitRecord;
					entry->m_flags |= WheelProbe::c_flagHit;
					resource->LocalToWorld(hitPoint, &entry->m_hitPoint);

					GolVec3 collisionNormal = eventContext->m_normal;
					resource->RotateToWorld(collisionNormal, &entry->m_contactForce);

					LegoFloat deltaX = entry->m_rayEnd.m_x - hitPoint.m_x;
					LegoFloat deltaY = entry->m_rayEnd.m_y - hitPoint.m_y;
					LegoFloat deltaZ = entry->m_rayEnd.m_z - hitPoint.m_z;
					entry->m_hitDistanceSquared = deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ;

					if (entry->m_hitDistanceSquared > bestDistance) {
						selectedEntry = entry;
						bestDistance = entry->m_hitDistanceSquared;
					}
				}
			}

			entry++;
		}
	}

	GolBoundedEntity* baseResource = m_collisionWorlds[0];
	entry = entries;
	while (entry < entriesEnd) {
		if (entry->m_flags & WheelProbe::c_flagHit) {
			entry++;
			continue;
		}

		entry->m_rayStart.m_x = entry->m_wheelPosition.m_x;
		entry->m_rayStart.m_y = entry->m_wheelPosition.m_y;
		entry->m_rayStart.m_z = entry->m_wheelPosition.m_z + sweepHeight;
		entry->m_rayEnd.m_x = entry->m_wheelPosition.m_x;
		entry->m_rayEnd.m_y = entry->m_wheelPosition.m_y;
		entry->m_rayEnd.m_z = entry->m_wheelPosition.m_z - sweepDistance;

		if (!TestCachedPlanes(entry)) {
			GolBoundingVolume* query = baseResource->GetUnk0x58();
			query->SetUnk0x24(baseResource->GetMaterialTable());

			RaceEventRecord* hitRecord;
			if (query->FUN_00403fa0(
					&entry->m_rayStart,
					&entry->m_rayEnd,
					collisionContext,
					&entry->m_hitPoint,
					&hitRecord,
					NULL
				)) {
				entry->m_hitRecord = hitRecord;
				entry->m_cachedPlane = CachePlane(eventContext, entry->m_hitRecord);
			}
			else {
				entry++;
				continue;
			}
		}

		entry->m_contactForce = entry->m_cachedPlane->m_plane.m_normal;

		LegoFloat deltaX = entry->m_rayEnd.m_x - entry->m_hitPoint.m_x;
		LegoFloat deltaY = entry->m_rayEnd.m_y - entry->m_hitPoint.m_y;
		LegoFloat deltaZ = entry->m_rayEnd.m_z - entry->m_hitPoint.m_z;
		entry->m_hitDistanceSquared = deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ;

		if (entry->m_hitDistanceSquared > bestDistance) {
			selectedEntry = entry;
			bestDistance = entry->m_hitDistanceSquared;
		}

		entry->m_flags |= WheelProbe::c_flagHit;
		entry++;
	}

	if (selectedEntry == NULL) {
		if (previousContactCount == 0) {
			return;
		}

		m_velocity.m_z -= g_airborneDropStep;
		return;
	}

	LegoFloat contactLimit = static_cast<LegoFloat>(sqrt(bestDistance)) - g_wheelContactPadding;
	if (contactLimit < 0.0f) {
		contactLimit = 0.0f;
	}

	LegoFloat contactLimitSquared = contactLimit * contactLimit;
	m_supportNormal.m_x = 0.0f;
	m_supportNormal.m_y = 0.0f;
	m_supportNormal.m_z = 0.0f;

	entry = entries;
	while (entry < entriesEnd) {
		if (entry->m_hitDistanceSquared >= contactLimitSquared) {
			m_supportNormal.m_x += entry->m_contactForce.m_x;
			m_supportNormal.m_y += entry->m_contactForce.m_y;
			m_supportNormal.m_z += entry->m_contactForce.m_z;
			entry->m_flags |= WheelProbe::c_flagContact;
			m_contactCount++;
		}
		else {
			entry->m_flags &= ~WheelProbe::c_flagContact;
			entry->m_contactForce.m_x = 0.0f;
			entry->m_contactForce.m_y = 0.0f;
			entry->m_contactForce.m_z = 0.0f;
		}

		entry++;
	}

	SnapToContacts(selectedEntry);

	if (m_contactCount >= 3) {
		const GolMatrix34& transform = m_physicsEntity.GetTransform();
		m_supportNormal.m_x = transform.m_m[2][0];
		m_supportNormal.m_y = transform.m_m[2][1];
		m_supportNormal.m_z = transform.m_m[2][2];

		entry = entries;
		while (entry < entriesEnd) {
			entry->m_flags |= WheelProbe::c_flagContact;
			entry++;
		}

		m_contactCount = 4;
	}
	else {
		GolMath::NormalizeVector3(m_supportNormal, &m_supportNormal);
	}

	if (resetFromAir) {
		if (m_airborneMs > 400) {
			LegoFloat dot = m_velocity.m_z * m_supportNormal.m_z + m_velocity.m_y * m_supportNormal.m_y +
							m_velocity.m_x * m_supportNormal.m_x;
			if (dot < 0.0f) {
				if (dot < -g_landingBounceThreshold) {
					LegoFloat scaled = dot * g_landingBounceScaleFourWheel;
					m_contactCount = 0;
					m_velocity.m_z -= scaled;

					entry = entries;
					while (entry < entriesEnd) {
						entry->m_flags &= ~WheelProbe::c_flagContact;
						entry++;
					}
					return;
				}

				m_velocity.m_z -= dot;
			}
		}
	}

	LegoFloat responseScale = m_gravityForce * m_supportNormal.m_z;
	m_supportForce.m_x = -(m_supportNormal.m_x * responseScale);
	m_supportForce.m_y = -(m_supportNormal.m_y * responseScale);
	m_supportForce.m_z = m_gravityForce - m_supportNormal.m_z * responseScale;

	g_carBodySavedState.m_contactForce.m_x = 0.0f;
	g_carBodySavedState.m_contactForce.m_y = 0.0f;
	g_carBodySavedState.m_contactForce.m_z = -(m_gravityForce * (1.0f / static_cast<LegoFloat>(m_contactCount + 8)));

	entry = entries;
	while (entry < entriesEnd) {
		if (entry->m_flags & WheelProbe::c_flagContact) {
			entry->m_contactForce = g_carBodySavedState.m_contactForce;
		}
		entry++;
	}
}

// FUNCTION: LEGORACERS 0x004464a0
void RacerCarBody::UpdateSlideBank(LegoS32 p_elapsedMs)
{
	if (m_slideLift < m_slideLiftTarget) {
		LegoFloat delta = m_slideLiftRate;
		LegoFloat elapsed = static_cast<LegoFloat>(p_elapsedMs);
		delta *= elapsed;
		delta *= 0.001f;
		m_slideLift += delta;
		if (m_slideLift > m_slideLiftTarget) {
			m_slideLift = m_slideLiftTarget;
		}
	}
	else if (m_slideLift > m_slideLiftTarget) {
		LegoFloat delta = m_slideLiftRate;
		LegoFloat elapsed = static_cast<LegoFloat>(p_elapsedMs);
		delta *= elapsed;
		delta *= 0.001f;
		m_slideLift -= delta;
		if (m_slideLift < m_slideLiftTarget) {
			m_slideLift = m_slideLiftTarget;
		}
	}

	if (m_slideBankAngle < m_slideBankTarget) {
		m_slideBankAngle += static_cast<LegoFloat>(p_elapsedMs) * g_slideBankRate;
		if (m_slideBankAngle > m_slideBankTarget) {
			m_slideBankAngle = m_slideBankTarget;
		}
	}
	else if (m_slideBankAngle > m_slideBankTarget) {
		m_slideBankAngle -= static_cast<LegoFloat>(p_elapsedMs) * g_slideBankRate;
		if (m_slideBankAngle < m_slideBankTarget) {
			m_slideBankAngle = m_slideBankTarget;
		}
	}
}

// STUB: LEGORACERS 0x004465c0
void RacerCarBody::UpdateSlideContacts(LegoU32 p_elapsedMs)
{
	LegoU32 flags = m_flags;
	if (flags & c_flagAtRest) {
		if (m_velocity.m_x == 0.0f && m_velocity.m_y == 0.0f && m_velocity.m_z == 0.0f &&
			m_angularVelocity.m_x == 0.0f && m_angularVelocity.m_y == 0.0f && m_angularVelocity.m_z == 0.0f) {
			return;
		}

		m_flags = flags & ~c_flagAtRest;
	}

	AgePlaneCache();

	LegoFloat elapsedMs = static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs));
	ComputeWheelPositions();

	LegoFloat average = m_wheelProbes[0].m_wheelPosition.m_x;
	average += m_wheelProbes[1].m_wheelPosition.m_x;
	m_frontAxleMid.m_x = average * 0.5f;
	average = m_wheelProbes[0].m_wheelPosition.m_y;
	average += m_wheelProbes[1].m_wheelPosition.m_y;
	m_frontAxleMid.m_y = average * 0.5f;
	average = m_wheelProbes[0].m_wheelPosition.m_z;
	average += m_wheelProbes[1].m_wheelPosition.m_z;
	m_frontAxleMid.m_z = average * 0.5f;
	average = m_wheelProbes[3].m_wheelPosition.m_x;
	average += m_wheelProbes[2].m_wheelPosition.m_x;
	m_rearAxleMid.m_x = average * 0.5f;
	average = m_wheelProbes[2].m_wheelPosition.m_y;
	average += m_wheelProbes[3].m_wheelPosition.m_y;
	m_rearAxleMid.m_y = average * 0.5f;
	average = m_wheelProbes[2].m_wheelPosition.m_z;
	average += m_wheelProbes[3].m_wheelPosition.m_z;
	m_rearAxleMid.m_z = average * 0.5f;

	LegoU32 previousContactCount = m_contactCount;

	GolVec3 position;
	m_physicsEntity.GetPosition(&position);

	LegoFloat verticalOffset = -(position.m_z - m_savedPosition.m_z);
	if (verticalOffset < 0.0f) {
		verticalOffset = 0.0f;
	}

	LegoFloat sweepHeight = m_carEntity->GetBoundsRadius() + verticalOffset;
	LegoBool32 resetFromAir;
	LegoFloat sweepDistance;
	if (m_contactCount != 0) {
		sweepDistance = elapsedMs * g_slideSweepScale;
		resetFromAir = FALSE;
	}
	else {
		sweepDistance = 0.0f;
		resetFromAir = TRUE;
	}
	sweepDistance += m_slideLift;

	WheelProbe* entries = m_wheelProbes;
	WheelProbe* entriesEnd = &m_wheelProbes[2];
	WheelProbe* entry;
	m_contactCount = 0;

	GolVec3* sweepCenter = &m_frontAxleMid;
	for (entry = entries; entry < entriesEnd; entry++, sweepCenter++) {
		entry->m_rayStart.m_x = sweepCenter->m_x;
		entry->m_rayStart.m_y = sweepCenter->m_y;
		entry->m_rayStart.m_z = sweepCenter->m_z + sweepHeight;
		entry->m_rayEnd.m_x = sweepCenter->m_x;
		entry->m_rayEnd.m_y = sweepCenter->m_y;
		entry->m_rayEnd.m_z = sweepCenter->m_z - sweepDistance;
		entry->m_flags &= ~(WheelProbe::c_flagContact | WheelProbe::c_flagHit);
		entry->m_contactForce.m_x = 0.0f;
		entry->m_contactForce.m_y = 0.0f;
		entry->m_contactForce.m_z = 0.0f;
		entry->m_hitDistanceSquared = -FLT_MAX;
	}

	LegoFloat bestDistance = -FLT_MAX;
	WheelProbe* selectedEntry = NULL;
	LegoS32 selectedIndex = 0;
	GolBoundingVolume::HitTriangle* eventContext = g_carBodySavedWheels.GetEventContext();
	GolBoundingVolume::HitTriangle* collisionContext = eventContext;

	for (LegoU32 resourceIndex = 1; resourceIndex < m_collisionWorldCount; resourceIndex++) {
		GolBoundedEntity* resource = m_collisionWorlds[resourceIndex];

		LegoS32 entryIndex = 0;
		for (entry = entries; entry < entriesEnd; entry++, entryIndex++) {
			if (entry->m_flags & WheelProbe::c_flagHit) {
				continue;
			}

			GolVec3 start;
			GolVec3 end;
			resource->WorldToLocal(entry->m_rayStart, &start);
			resource->WorldToLocal(entry->m_rayEnd, &end);

			GolBoundingVolume* query = resource->GetUnk0x58();
			query->SetUnk0x24(resource->GetMaterialTable());

			GolVec3 hitPoint;
			RaceEventRecord* hitRecord;
			if (!query->FUN_00403fa0(&start, &end, collisionContext, &hitPoint, &hitRecord, NULL)) {
				continue;
			}

			entry->m_flags |= WheelProbe::c_flagHit;
			resource->LocalToWorld(hitPoint, &entry->m_hitPoint);

			GolVec3 collisionNormal = eventContext->m_normal;
			resource->RotateToWorld(collisionNormal, &entry->m_contactForce);

			if (entryIndex == 0) {
				m_wheelProbes[0].m_hitRecord = hitRecord;
				m_wheelProbes[1].m_hitRecord = hitRecord;
			}
			else {
				m_wheelProbes[2].m_hitRecord = hitRecord;
				m_wheelProbes[3].m_hitRecord = hitRecord;
			}

			LegoFloat deltaX = end.m_x - hitPoint.m_x;
			LegoFloat deltaY = end.m_y - hitPoint.m_y;
			LegoFloat deltaZ = end.m_z - hitPoint.m_z;
			entry->m_hitDistanceSquared = deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ;

			if (entry->m_hitDistanceSquared > bestDistance) {
				selectedEntry = entry;
				selectedIndex = entryIndex;
				bestDistance = entry->m_hitDistanceSquared;
			}
		}
	}

	GolBoundedEntity* baseResource = m_collisionWorlds[0];
	LegoS32 entryIndex = 0;
	for (entry = entries; entry < entriesEnd; entry++, entryIndex++) {
		if (!(entry->m_flags & WheelProbe::c_flagHit)) {
			if (!TestCachedPlanes(entry)) {
				GolBoundingVolume* query = baseResource->GetUnk0x58();
				query->SetUnk0x24(baseResource->GetMaterialTable());

				RaceEventRecord* hitRecord;
				if (!query->FUN_00403fa0(
						&entry->m_rayStart,
						&entry->m_rayEnd,
						collisionContext,
						&entry->m_hitPoint,
						&hitRecord,
						NULL
					)) {
					continue;
				}

				entry->m_cachedPlane = CachePlane(eventContext, hitRecord);

				if (entryIndex == 0) {
					m_wheelProbes[0].m_hitRecord = hitRecord;
					m_wheelProbes[1].m_hitRecord = hitRecord;
				}
				else {
					m_wheelProbes[2].m_hitRecord = hitRecord;
					m_wheelProbes[3].m_hitRecord = hitRecord;
				}
			}

			entry->m_contactForce = entry->m_cachedPlane->m_plane.m_normal;

			LegoFloat deltaX = entry->m_rayEnd.m_x - entry->m_hitPoint.m_x;
			LegoFloat deltaY = entry->m_rayEnd.m_y - entry->m_hitPoint.m_y;
			LegoFloat deltaZ = entry->m_rayEnd.m_z - entry->m_hitPoint.m_z;
			entry->m_hitDistanceSquared = deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ;

			if (entry->m_hitDistanceSquared > bestDistance) {
				selectedEntry = entry;
				selectedIndex = entryIndex;
				bestDistance = entry->m_hitDistanceSquared;
			}

			entry->m_flags |= WheelProbe::c_flagHit;
		}
	}

	if (selectedEntry == NULL) {
		if (previousContactCount == 0) {
			return;
		}

		m_velocity.m_z -= g_airborneDropStep;
		return;
	}

	LegoFloat contactLimit = static_cast<LegoFloat>(sqrt(bestDistance)) - g_wheelContactPadding;
	if (contactLimit < 0.0f) {
		contactLimit = 0.0f;
	}

	LegoFloat contactLimitSquared = contactLimit * contactLimit;
	m_supportNormal.m_x = 0.0f;
	m_supportNormal.m_y = 0.0f;
	m_supportNormal.m_z = 0.0f;

	for (entry = entries; entry < entriesEnd; entry++) {
		if (entry->m_hitDistanceSquared >= contactLimitSquared) {
			m_supportNormal.m_x += entry->m_contactForce.m_x;
			m_supportNormal.m_y += entry->m_contactForce.m_y;
			m_supportNormal.m_z += entry->m_contactForce.m_z;
			entry->m_flags |= WheelProbe::c_flagContact;
			m_contactCount++;
		}
		else {
			entry->m_flags &= ~WheelProbe::c_flagContact;
			entry->m_contactForce.m_x = 0.0f;
			entry->m_contactForce.m_y = 0.0f;
			entry->m_contactForce.m_z = 0.0f;
		}
	}

	if (m_contactCount >= 2) {
		GolVec3 direction;
		direction.m_x = m_wheelProbes[0].m_hitPoint.m_x - m_wheelProbes[1].m_hitPoint.m_x;
		direction.m_y = m_wheelProbes[0].m_hitPoint.m_y - m_wheelProbes[1].m_hitPoint.m_y;
		direction.m_z = m_wheelProbes[0].m_hitPoint.m_z - m_wheelProbes[1].m_hitPoint.m_z;

		GolVec3 up;
		up.m_x = m_physicsEntity.GetTransform().m_m[2][0];
		up.m_y = m_physicsEntity.GetTransform().m_m[2][1];
		up.m_z = m_physicsEntity.GetTransform().m_m[2][2];
		m_physicsEntity.SetDirectionUp(direction, up);

		m_supportNormal.m_x = m_physicsEntity.GetTransform().m_m[2][0];
		m_supportNormal.m_y = m_physicsEntity.GetTransform().m_m[2][1];
		m_supportNormal.m_z = m_physicsEntity.GetTransform().m_m[2][2];
	}
	else {
		GolMath::NormalizeVector3(m_supportNormal, &m_supportNormal);
	}

	GolVec3* selectedCenter = selectedIndex == 0 ? &m_frontAxleMid : &m_rearAxleMid;
	GolVec3 delta;
	delta.m_x = selectedEntry->m_hitPoint.m_x - selectedCenter->m_x;
	delta.m_y = selectedEntry->m_hitPoint.m_y - selectedCenter->m_y;
	delta.m_z = selectedEntry->m_hitPoint.m_z - selectedCenter->m_z + m_slideLift;

	GolVec3 newPosition;
	m_physicsEntity.GetPosition(&newPosition);
	newPosition.m_x += delta.m_x;
	newPosition.m_y += delta.m_y;
	newPosition.m_z += delta.m_z;
	m_physicsEntity.SetPosition(newPosition);

	m_frontAxleMid.m_x += delta.m_x;
	m_frontAxleMid.m_y += delta.m_y;
	m_frontAxleMid.m_z += delta.m_z;
	m_rearAxleMid.m_x += delta.m_x;
	m_rearAxleMid.m_y += delta.m_y;
	m_rearAxleMid.m_z += delta.m_z;

	if (resetFromAir) {
		LegoFloat dot = m_velocity.m_z * m_supportNormal.m_z + m_velocity.m_y * m_supportNormal.m_y +
						m_velocity.m_x * m_supportNormal.m_x;
		if (dot < 0.0f) {
			if (dot < -g_landingBounceThreshold) {
				LegoFloat scaled = dot * g_landingBounceScale;
				m_contactCount = 0;
				m_velocity.m_z -= scaled;

				for (entry = entries; entry < entriesEnd; entry++) {
					entry->m_flags &= ~WheelProbe::c_flagContact;
				}
				return;
			}

			m_velocity.m_z -= dot;
		}
	}

	LegoFloat responseScale = m_gravityForce * m_supportNormal.m_z;
	m_supportForce.m_x = -(m_supportNormal.m_x * responseScale);
	m_supportForce.m_y = -(m_supportNormal.m_y * responseScale);
	m_supportForce.m_z = m_gravityForce - m_supportNormal.m_z * responseScale;

	g_carBodySavedState.m_contactForce.m_x = 0.0f;
	g_carBodySavedState.m_contactForce.m_y = 0.0f;
	g_carBodySavedState.m_contactForce.m_z = -(m_gravityForce * 0.5f);

	for (entry = entries; entry < entriesEnd; entry++) {
		if (entry->m_flags & WheelProbe::c_flagContact) {
			entry->m_contactForce = g_carBodySavedState.m_contactForce;
		}
	}
}

// FUNCTION: LEGORACERS 0x00446e60
void RacerCarBody::SetWheelGeometry(GolVec3* p_anchorWheel, LegoFloat p_trackWidth, LegoFloat p_wheelbase)
{
	::memcpy(&m_anchorWheelOffset, p_anchorWheel, sizeof(m_anchorWheelOffset));
	m_trackWidth = p_trackWidth;
	m_wheelbase = p_wheelbase;
	ComputeWheelPositions();
}

// FUNCTION: LEGORACERS 0x00446ea0
void RacerCarBody::SetBodyPoint(LegoU32 p_index, GolVec3* p_point)
{
	GolVec3* source = &m_bodyPointsLocal[p_index];
	*source = *p_point;
	m_physicsEntity.LocalToWorld(*source, &m_bodyPointsWorld[p_index]);
}

// FUNCTION: LEGORACERS 0x00446fa0
void RacerCarBody::SnapFacingDirection()
{
	m_facingDirection.m_x = m_physicsEntity.GetOrientation().m_rows[0].m_x;
	m_facingDirection.m_y = m_physicsEntity.GetOrientation().m_rows[0].m_y;
	m_facingDirection.m_z = m_physicsEntity.GetOrientation().m_rows[0].m_z;
	UpdateVelocityStats();
}

// FUNCTION: LEGORACERS 0x00446fd0
void RacerCarBody::UpdateFacingDirection(LegoU32 p_elapsedMs)
{
	LegoFloat sine;
	LegoFloat cosine;
	GolVec3 direction;
	GolVec3 axis;

	direction.m_x = m_physicsEntity.GetOrientation().m_rows[0].m_x;
	direction.m_y = m_physicsEntity.GetOrientation().m_rows[0].m_y;
	direction.m_z = m_physicsEntity.GetOrientation().m_rows[0].m_z;

	if (m_contactCount != 0) {
		if (!(m_forwardSpeed < 0.03f)) {
			if (m_contactCount <= 2) {
				LegoFloat dot = m_supportNormal.m_z;
				dot *= direction.m_z;
				LegoFloat value = m_supportNormal.m_y;
				value *= direction.m_y;
				dot += value;
				value = direction.m_x;
				value *= m_supportNormal.m_x;
				dot += value;

				axis.m_x = dot;
				axis.m_x *= m_supportNormal.m_x;
				axis.m_y = m_supportNormal.m_y;
				axis.m_y *= dot;
				LegoFloat projectedZ = dot;
				projectedZ *= m_supportNormal.m_z;

				direction.m_x -= axis.m_x;
				direction.m_y -= axis.m_y;
				direction.m_z -= projectedZ;
				GolMath::NormalizeVector3(direction, &direction);
			}
			else {
				if ((m_flags & c_flagSteering) && m_thrust > 0.0f) {
					GolVec3* current = &m_facingDirection;
					LegoFloat dot = m_facingDirection.m_z;
					dot *= direction.m_z;
					LegoFloat value = current->m_y;
					value *= direction.m_y;
					dot += value;
					value = direction.m_x;
					value *= current->m_x;
					dot += value;
					if (dot > 1.0f) {
						dot = 1.0f;
					}

					LegoS32 tableIndex = static_cast<LegoS32>((dot + 1.0f) * -511.5f);
					LegoFloat angle = *(g_arcCosineTable - tableIndex);
					LegoFloat step = m_yawRate;
					LegoFloat elapsed = static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs));
					step *= elapsed;
					if (step > 0.0f) {
						angle += step;
					}
					else {
						angle -= step;
					}

					if (angle > m_facingLagMax) {
						value = direction.m_z;
						value *= current->m_y;
						LegoFloat crossValue = current->m_z;
						crossValue *= direction.m_y;
						axis.m_x = value - crossValue;
						value = current->m_z;
						value *= direction.m_x;
						crossValue = direction.m_z;
						crossValue *= current->m_x;
						axis.m_y = value - crossValue;
						value = direction.m_y;
						value *= current->m_x;
						crossValue = current->m_y;
						crossValue *= direction.m_x;
						axis.m_z = value - crossValue;
						GolMath::RotateAboutAxis(&direction, current, &axis, m_facingLagMax);
						GolMath::NormalizeVector3(*current, current);
						return;
					}

					GolMath::SinCos(step, &cosine, &sine);
					value = current->m_x;
					value *= sine;
					LegoFloat crossValue = m_facingDirection.m_y;
					crossValue *= cosine;
					current->m_x = value - crossValue;
					value = m_facingDirection.m_y;
					value *= sine;
					crossValue = current->m_x;
					crossValue *= cosine;
					m_facingDirection.m_y = value + crossValue;
					GolMath::NormalizeVector3(*current, current);
					return;
				}

				RotateFacingToward(p_elapsedMs, &direction);
				return;
			}
		}
	}

	RotateFacingToward(p_elapsedMs, &direction);
}

// FUNCTION: LEGORACERS 0x00447230
void RacerCarBody::RotateFacingToward(LegoS32 p_elapsedMs, GolVec3* p_target)
{
	GolVec3* current = &m_facingDirection;
	GolVec3* target = p_target;

	LegoFloat dot = current->m_z;
	dot *= target->m_z;
	LegoFloat value = current->m_y;
	value *= target->m_y;
	dot += value;
	value = target->m_x;
	value *= current->m_x;
	dot += value;

	if (dot > 0.98000002f) {
		current->m_x = target->m_x;
		current->m_y = target->m_y;
		current->m_z = target->m_z;
		return;
	}

	LegoFloat maxStep = static_cast<LegoFloat>(p_elapsedMs);
	maxStep *= 0.0025f;
	LegoS32 tableIndex = static_cast<LegoS32>((dot + 1.0f) * -511.5f);
	LegoFloat angle = *(g_arcCosineTable - tableIndex);
	if (maxStep > angle) {
		current->m_x = target->m_x;
		current->m_y = target->m_y;
		current->m_z = target->m_z;
		return;
	}

	GolVec3 axis;
	value = target->m_y;
	value *= current->m_z;
	LegoFloat crossValue = current->m_y;
	crossValue *= target->m_z;
	axis.m_x = value - crossValue;
	value = target->m_z;
	value *= current->m_x;
	crossValue = current->m_z;
	crossValue *= target->m_x;
	axis.m_y = value - crossValue;
	value = current->m_y;
	value *= target->m_x;
	crossValue = target->m_y;
	crossValue *= current->m_x;
	axis.m_z = value - crossValue;
	GolMath::RotateAboutAxis(current, current, &axis, maxStep);
	GolMath::NormalizeVector3(*current, current);
}

// FUNCTION: LEGORACERS 0x00447330
void RacerCarBody::UpdateVelocityStats()
{
	GolVec3* velocity = &m_velocity;

	if (m_velocity.m_x == 0.0f && m_velocity.m_y == 0.0f && m_velocity.m_z == 0.0f) {
		m_speed = 0.0f;
		m_velocityDirection.m_x = m_physicsEntity.GetOrientation().m_rows[0].m_x;
		m_velocityDirection.m_y = m_physicsEntity.GetOrientation().m_rows[0].m_y;
		m_velocityDirection.m_z = m_physicsEntity.GetOrientation().m_rows[0].m_z;

		if (m_angularVelocity.m_x == 0.0f && m_angularVelocity.m_y == 0.0f && m_angularVelocity.m_z == 0.0f) {
			m_flags |= c_flagAtRest;
		}
		else {
			m_flags &= ~c_flagAtRest;
		}
	}
	else {
		LegoFloat speed = static_cast<LegoFloat>(
			sqrt(velocity->m_x * velocity->m_x + velocity->m_y * velocity->m_y + velocity->m_z * velocity->m_z)
		);
		m_speed = speed;
		GolMath::NormalizeVector3(*velocity, &m_velocityDirection);
		m_flags &= ~c_flagAtRest;
	}

	LegoFloat forwardSpeed = velocity->m_z;
	forwardSpeed *= m_facingDirection.m_z;
	LegoFloat contribution = velocity->m_y;
	contribution *= m_facingDirection.m_y;
	forwardSpeed += contribution;
	contribution = velocity->m_x;
	contribution *= m_facingDirection.m_x;
	forwardSpeed += contribution;
	{
		LegoFloat projected = forwardSpeed;
		projected *= m_facingDirection.m_x;
		m_forwardVelocity.m_x = projected;

		projected = m_facingDirection.m_y;
		projected *= forwardSpeed;
		m_forwardVelocity.m_y = projected;

		projected = m_facingDirection.m_z;
		projected *= forwardSpeed;
		m_forwardVelocity.m_z = projected;
	}

	m_lateralVelocity.m_x = velocity->m_x - forwardSpeed * m_facingDirection.m_x;
	m_lateralVelocity.m_y = velocity->m_y - m_facingDirection.m_y * forwardSpeed;
	m_lateralVelocity.m_z = velocity->m_z - m_facingDirection.m_z * forwardSpeed;
	m_forwardSpeed = forwardSpeed;
}

// FUNCTION: LEGORACERS 0x004474c0
void RacerCarBody::SaveState()
{
	RacerCarBody* self = this;
	GolOrientedEntity* entity = &self->m_physicsEntity;
	entity->GetPosition(&self->m_savedPosition);

	self->m_savedVelocity = self->m_velocity;

	entity->CopyOrientation(&self->m_savedOrientation);

	g_carBodySavedState.m_worldInverseInertia.m_m[0][0] = self->m_worldInverseInertia.m_m[0][0];
	g_carBodySavedState.m_worldInverseInertia.m_m[0][1] = self->m_worldInverseInertia.m_m[0][1];
	g_carBodySavedState.m_worldInverseInertia.m_m[0][2] = self->m_worldInverseInertia.m_m[0][2];
	g_carBodySavedState.m_worldInverseInertia.m_m[1][0] = self->m_worldInverseInertia.m_m[1][0];
	g_carBodySavedState.m_worldInverseInertia.m_m[1][1] = self->m_worldInverseInertia.m_m[1][1];
	g_carBodySavedState.m_worldInverseInertia.m_m[1][2] = self->m_worldInverseInertia.m_m[1][2];
	g_carBodySavedState.m_worldInverseInertia.m_m[2][0] = self->m_worldInverseInertia.m_m[2][0];
	g_carBodySavedState.m_worldInverseInertia.m_m[2][1] = self->m_worldInverseInertia.m_m[2][1];
	g_carBodySavedState.m_worldInverseInertia.m_m[2][2] = self->m_worldInverseInertia.m_m[2][2];
	g_carBodySavedState.m_angularVelocity = self->m_angularVelocity;
	g_carBodySavedState.m_angularMomentum = self->m_angularMomentum;
	g_carBodySavedState.m_slideLift = self->m_slideLift;
	g_carBodySavedState.m_slideBankAngle = self->m_slideBankAngle;
	g_carBodySavedState.m_facingDirection = self->m_facingDirection;

	WheelProbe* entry = self->m_wheelProbes;
	SavedWheelState* snapshotEntry = g_carBodySavedWheels.GetEntries();
	while (entry < self->m_wheelProbes + sizeOfArray(self->m_wheelProbes)) {
		snapshotEntry->m_wheelPosition = entry->m_wheelPosition;

		RaceEventRecord* record = entry->m_hitRecord;
		entry->m_previousHitRecord = record;
		snapshotEntry->m_hitRecord = record;

		snapshotEntry->m_flags = entry->m_flags;
		snapshotEntry->m_rollingResistance = entry->m_rollingResistance;
		snapshotEntry->m_supportThreshold = entry->m_supportThreshold;
		snapshotEntry->m_friction = entry->m_friction;
		snapshotEntry->m_lateralGrip = entry->m_lateralGrip;
		snapshotEntry->m_unk0x054 = entry->m_unk0x060;
		snapshotEntry->m_surfaceForce = entry->m_surfaceForce;

		entry++;
		snapshotEntry++;
	}

	GolVec3* source = self->m_bodyPointsWorld;
	GolVec3* dest = g_carBodySavedState.m_bodyPointsWorld;
	while (dest < &g_carBodySavedState.m_facingDirection) {
		*dest = *source;
		source++;
		dest++;
	}
}

// FUNCTION: LEGORACERS 0x00447690
void RacerCarBody::RestoreState()
{
	RacerCarBody* self = this;
	GolOrientedEntity* entity = &self->m_physicsEntity;
	entity->SetPosition(self->m_savedPosition);

	self->m_velocity = self->m_savedVelocity;

	entity->SetOrientationMatrix(self->m_savedOrientation);

	self->m_worldInverseInertia.m_m[0][0] = g_carBodySavedState.m_worldInverseInertia.m_m[0][0];
	self->m_worldInverseInertia.m_m[0][1] = g_carBodySavedState.m_worldInverseInertia.m_m[0][1];
	self->m_worldInverseInertia.m_m[0][2] = g_carBodySavedState.m_worldInverseInertia.m_m[0][2];
	self->m_worldInverseInertia.m_m[1][0] = g_carBodySavedState.m_worldInverseInertia.m_m[1][0];
	self->m_worldInverseInertia.m_m[1][1] = g_carBodySavedState.m_worldInverseInertia.m_m[1][1];
	self->m_worldInverseInertia.m_m[1][2] = g_carBodySavedState.m_worldInverseInertia.m_m[1][2];
	self->m_worldInverseInertia.m_m[2][0] = g_carBodySavedState.m_worldInverseInertia.m_m[2][0];
	self->m_worldInverseInertia.m_m[2][1] = g_carBodySavedState.m_worldInverseInertia.m_m[2][1];
	self->m_worldInverseInertia.m_m[2][2] = g_carBodySavedState.m_worldInverseInertia.m_m[2][2];
	self->m_angularVelocity = g_carBodySavedState.m_angularVelocity;
	self->m_angularMomentum = g_carBodySavedState.m_angularMomentum;
	self->m_slideLift = g_carBodySavedState.m_slideLift;
	self->m_slideBankAngle = g_carBodySavedState.m_slideBankAngle;
	self->m_facingDirection = g_carBodySavedState.m_facingDirection;

	WheelProbe* entry = self->m_wheelProbes;
	SavedWheelState* snapshotEntry = g_carBodySavedWheels.GetEntries();
	while (entry < self->m_wheelProbes + sizeOfArray(self->m_wheelProbes)) {
		entry->m_wheelPosition = snapshotEntry->m_wheelPosition;
		entry->m_hitRecord = snapshotEntry->m_hitRecord;
		entry->m_flags = snapshotEntry->m_flags;
		entry->m_rollingResistance = snapshotEntry->m_rollingResistance;
		entry->m_supportThreshold = snapshotEntry->m_supportThreshold;
		entry->m_friction = snapshotEntry->m_friction;
		entry->m_lateralGrip = snapshotEntry->m_lateralGrip;
		entry->m_unk0x060 = snapshotEntry->m_unk0x054;
		entry->m_surfaceForce = snapshotEntry->m_surfaceForce;

		entry++;
		snapshotEntry++;
	}

	GolVec3* source = g_carBodySavedState.m_bodyPointsWorld;
	GolVec3* dest = self->m_bodyPointsWorld;
	while (source < &g_carBodySavedState.m_facingDirection) {
		*dest = *source;
		source++;
		dest++;
	}

	entity->LocalToWorld(self->m_centerOfMassLocal, &self->m_centerOfMassWorld);
	self->UpdateVelocityStats();
}

// FUNCTION: LEGORACERS 0x00447880
void RacerCarBody::ClearWallContacts()
{
	m_bodyPointHit[0] = 0;
	m_bodyPointHit[1] = 0;
	m_bodyPointHit[2] = 0;
	m_bodyPointHit[3] = 0;
	m_wallContact = 0;
}

// STUB: LEGORACERS 0x004478b0
LegoU32 RacerCarBody::ResolveWallCollisions(LegoU32 p_elapsedMs, LegoBool32 p_queryTrack)
{
	RaceEventRecord* hitRecord = NULL;
	m_wallContact = 0;
	LegoFloat bestDistance = -FLT_MAX;
	LegoFloat hitAmount;
	LegoFloat selectedHitAmount = 0.0f;

	GolOrientedEntity* entity = &m_physicsEntity;
	for (LegoU32 i = 0; i < sizeOfArray(m_bodyPointsLocal); i++) {
		entity->LocalToWorld(m_bodyPointsLocal[i], &m_bodyPointsWorld[i]);
		m_bodyPointHit[i] = 0;
	}

	for (LegoU32 resourceIndex = 1; resourceIndex < m_collisionWorldCount; resourceIndex++) {
		GolBoundedEntity* resource = m_collisionWorlds[resourceIndex];

		for (LegoS32 pointIndex = 0; pointIndex < sizeOfArray(m_bodyPointsWorld); pointIndex++) {
			if (!m_bodyPointHit[pointIndex]) {
				resource->WorldToLocal(
					g_carBodySavedState.m_bodyPointsWorld[pointIndex],
					&g_carBodySavedState.m_rayStartsLocal[pointIndex]
				);
				resource->WorldToLocal(m_bodyPointsWorld[pointIndex], &g_carBodySavedState.m_rayEndsLocal[pointIndex]);

				GolBoundingVolume* query = resource->GetUnk0x58();
				query->SetUnk0x24(resource->GetMaterialTable());

				GolVec3 hitPoint;
				if (query->FUN_00403fa0(
						&g_carBodySavedState.m_rayStartsLocal[pointIndex],
						&g_carBodySavedState.m_rayEndsLocal[pointIndex],
						g_carBodySavedWheels.GetEventContext(),
						&hitPoint,
						&hitRecord,
						&hitAmount
					)) {
					GolVec3 worldNormal;
					GolVec3 collisionNormal = g_carBodySavedWheels.GetEventContext()->m_normal;
					resource->RotateToWorld(collisionNormal, &worldNormal);

					LegoFloat dot =
						(hitPoint.m_x - g_carBodySavedState.m_rayEndsLocal[pointIndex].m_x) * collisionNormal.m_x;
					dot += (hitPoint.m_y - g_carBodySavedState.m_rayEndsLocal[pointIndex].m_y) * collisionNormal.m_y;
					dot += (hitPoint.m_z - g_carBodySavedState.m_rayEndsLocal[pointIndex].m_z) * collisionNormal.m_z;

					if (dot > 0.0f) {
						if (hitRecord && !OnCollisionRecord(
											 &hitPoint,
											 hitRecord,
											 resource,
											 g_carBodySavedWheels.GetEventContext()
										 )) {
							continue;
						}

						LegoFloat deltaX = g_carBodySavedState.m_rayEndsLocal[pointIndex].m_x - hitPoint.m_x;
						LegoFloat deltaY = g_carBodySavedState.m_rayEndsLocal[pointIndex].m_y - hitPoint.m_y;
						LegoFloat deltaZ = g_carBodySavedState.m_rayEndsLocal[pointIndex].m_z - hitPoint.m_z;
						LegoFloat distance = deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ;

						if (distance > bestDistance) {
							bestDistance = distance;
							m_wallNormal = worldNormal;
							m_bodyPointHit[pointIndex] = 1;
							selectedHitAmount = hitAmount;
							m_wallContact++;
						}
					}
				}
			}
		}
	}

	if (p_queryTrack) {
		GolBoundedEntity* resource = m_collisionWorlds[0];

		for (LegoS32 pointIndex = 0; pointIndex < sizeOfArray(m_bodyPointsWorld); pointIndex++) {
			if (!m_bodyPointHit[pointIndex]) {
				GolBoundingVolume* query = resource->GetUnk0x58();
				query->SetUnk0x24(resource->GetMaterialTable());

				GolVec3 hitPoint;
				if (query->FUN_00403fa0(
						&g_carBodySavedState.m_bodyPointsWorld[pointIndex],
						&m_bodyPointsWorld[pointIndex],
						g_carBodySavedWheels.GetEventContext(),
						&hitPoint,
						&hitRecord,
						&hitAmount
					)) {
					LegoFloat dot = (hitPoint.m_x - m_bodyPointsWorld[pointIndex].m_x) *
									g_carBodySavedWheels.GetEventContext()->m_normal.m_x;
					dot += (hitPoint.m_y - m_bodyPointsWorld[pointIndex].m_y) *
						   g_carBodySavedWheels.GetEventContext()->m_normal.m_y;
					dot += (hitPoint.m_z - m_bodyPointsWorld[pointIndex].m_z) *
						   g_carBodySavedWheels.GetEventContext()->m_normal.m_z;

					if (dot >= 0.0f) {
						if (hitRecord && !OnCollisionRecord(
											 &hitPoint,
											 hitRecord,
											 resource,
											 g_carBodySavedWheels.GetEventContext()
										 )) {
							continue;
						}

						GolVec3 collisionNormal = g_carBodySavedWheels.GetEventContext()->m_normal;
						LegoFloat deltaX = m_bodyPointsWorld[pointIndex].m_x - hitPoint.m_x;
						LegoFloat deltaY = m_bodyPointsWorld[pointIndex].m_y - hitPoint.m_y;
						LegoFloat deltaZ = m_bodyPointsWorld[pointIndex].m_z - hitPoint.m_z;
						LegoFloat distance = deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ;

						if (distance > bestDistance) {
							bestDistance = distance;
							m_wallNormal = collisionNormal;
							m_bodyPointHit[pointIndex] = 1;
							selectedHitAmount = hitAmount;
							LegoU32 collisionCount = m_wallContact;
							collisionCount++;
							m_wallContact = collisionCount;
						}
					}
				}
			}
		}
	}

	if (!m_wallContact) {
		return 0;
	}

	LegoU32 result =
		static_cast<LegoS32>(static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs)) * selectedHitAmount);
	if (result < 5) {
		result = 0;
	}
	else {
		result -= 5;
	}
	RestoreState();
	return result;
}

// FUNCTION: LEGORACERS 0x00447cf0
void RacerCarBody::ApplyWallResponse()
{
	GolVec3* velocity = &m_velocity;
	GolVec3* direction = &m_wallNormal;

	if (m_flags & c_flagSteering) {
		StopSteering();
	}

	LegoFloat dot = velocity->m_z;
	dot *= direction->m_z;
	dot += velocity->m_y * direction->m_y;
	LegoFloat contribution = velocity->m_x;
	contribution *= direction->m_x;
	dot += contribution;
	if (dot < 0.0f) {
		GolVec3 scaled;
		scaled.m_x = direction->m_x * dot;
		scaled.m_y = direction->m_y;
		scaled.m_y *= dot;
		scaled.m_z = direction->m_z;
		scaled.m_z *= dot;
		velocity->m_x -= scaled.m_x;
		velocity->m_y -= scaled.m_y;
		velocity->m_z -= scaled.m_z;
	}

	const GolMatrix3& orientation = m_physicsEntity.GetOrientation();
	LegoFloat row0X = orientation.m_rows[0].m_x;
	LegoU32 flags = m_flags;
	LegoFloat row0Y = orientation.m_rows[0].m_y;
	LegoFloat row0Z = orientation.m_rows[0].m_z;

	if (!(flags & c_flagSpinning)) {
		LegoFloat rowDot = row0X * direction->m_x + row0Y * direction->m_y + row0Z * direction->m_z;

		if (rowDot < 0.0f) {
			LegoFloat sideDot = orientation.m_rows[1].m_x * direction->m_x +
								orientation.m_rows[1].m_y * direction->m_y + orientation.m_rows[1].m_z * direction->m_z;

			LegoFloat amount;
			if (sideDot < 0.0f) {
				amount = ((sideDot + 1.0f) * 0.5f) + 0.5f;
				amount *= 0.0040000002f;
				amount = -amount;
			}
			else {
				amount = (((1.0f - sideDot) * 0.5f) + 0.5f) * 0.0040000002f;
			}

			ApplyYawImpulse(amount, 200);
			m_flags |= c_flagYawImpulse;
		}
	}

	if (dot < 0.0f) {
		LegoFloat scale = g_wallHorizontalDamping * dot;
		LegoFloat scaledValue = direction->m_x;
		scaledValue *= scale;
		velocity->m_x -= scaledValue;
		scaledValue = direction->m_y;
		scaledValue *= scale;
		velocity->m_y -= scaledValue;
		scaledValue = 0.15000001f * dot;
		scaledValue *= direction->m_z;
		velocity->m_z -= scaledValue;
	}

	GolVec3 scaled;
	scaled.m_x = direction->m_x * 0.0040000002f;
	scaled.m_y = direction->m_y * 0.0040000002f;
	scaled.m_z = direction->m_z * 0.0040000002f;
	velocity->m_x += scaled.m_x;
	velocity->m_y += scaled.m_y;
	velocity->m_z += scaled.m_z;

	if (!(velocity->m_z < g_wallMaxRiseSpeed)) {
		velocity->m_z = g_wallMaxRiseSpeed;
	}
}

// FUNCTION: LEGORACERS 0x00448070 FOLDED
void RacerCarBody::StopSteering()
{
	LegoU32 flags = m_flags;
	SpatialSoundInstance* resource = m_skidSound;

	flags &= ~(c_flagSteering | c_flagBit9);
	m_steeringAlignmentMin = -1.0f;
	m_facingLagMax = 3.1415927f;
	m_flags = flags;

	if (resource != NULL) {
		m_soundSource->ReleaseSound(resource);
		m_skidSound = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004480c0
void RacerCarBody::ApplyImpulse(GolVec3* p_impulse, GolVec3*)
{
	GolVec3 scaled;
	scaled.m_x = m_inverseMass;
	scaled.m_x *= p_impulse->m_x;
	scaled.m_y = p_impulse->m_y * m_inverseMass;
	scaled.m_z = p_impulse->m_z * m_inverseMass;

	m_velocity.m_x += scaled.m_x;
	m_velocity.m_y += scaled.m_y;
	m_velocity.m_z += scaled.m_z;
}

// FUNCTION: LEGORACERS 0x00448110
void RacerCarBody::ApplyDirectionalImpulse(GolVec3* p_direction, LegoFloat p_magnitude)
{
	GolVec3 scaled;
	LegoFloat scale = m_inverseMass;
	scale *= p_magnitude;
	scaled.m_x = scale * p_direction->m_x;
	scaled.m_y = p_direction->m_y;
	scaled.m_y *= scale;

	m_velocity.m_x += scaled.m_x;
	m_velocity.m_y += scaled.m_y;
	m_velocity.m_z += p_direction->m_z * scale;
}

// FUNCTION: LEGORACERS 0x00448160
void RacerCarBody::StartSpin(LegoFloat p_turns, LegoFloat p_rate, LegoFloat p_alignFraction)
{
	if (m_flags & c_flagSpinning) {
		return;
	}

	const GolMatrix34& transform = m_physicsEntity.GetTransform();
	GolVec3 direction;
	direction.m_x = transform.m_m[2][0];
	direction.m_y = transform.m_m[2][1];
	direction.m_z = transform.m_m[2][2];
	CancelAngularMomentumAlong(&direction);

	LegoS32 speed = static_cast<LegoS32>(g_twoPi / p_rate);
	m_spinPeriodMs = speed;
	ApplyYawImpulse(p_rate, static_cast<LegoS32>(static_cast<LegoFloat>(speed) * p_turns));
	m_flags = (m_flags & ~(c_flagSpinning | c_flagSpinFresh | 1)) | (c_flagSpinning | c_flagSpinFresh);

	if (p_alignFraction > 0.0f) {
		if (p_alignFraction > p_turns) {
			p_alignFraction = p_turns;
		}

		m_spinStopAtMs =
			static_cast<LegoS32>(static_cast<LegoFloat>(static_cast<LegoS32>(m_spinPeriodMs)) * p_alignFraction);
	}

	if (!m_spinSound) {
		if (m_soundsEnabled) {
			m_spinSound = m_soundSource->AcquireSoundById(0x3c);
		}

		if (m_spinSound) {
			m_spinSound->SetDistanceRangeWithMinSquared(
				g_physicsSoundMinDistance * g_physicsSoundMinDistance,
				g_physicsSoundMaxDistance
			);
			m_spinSound->Play(TRUE);
		}
	}
}

// FUNCTION: LEGORACERS 0x00448290
void RacerCarBody::FinishSpin()
{
	if (m_spinStopAtMs) {
		if (m_spinStopAtMs > m_spinPeriodMs) {
			do {
				m_spinStopAtMs -= m_spinPeriodMs;
			} while (m_spinStopAtMs > m_spinPeriodMs);
		}

		m_yawImpulseMs = m_spinStopAtMs;
		m_spinStopAtMs = 0;
		m_spinPeriodMs = 0;
	}
}

// FUNCTION: LEGORACERS 0x004482e0
void RacerCarBody::EndSpin()
{
	if (m_flags & c_flagSpinning) {
		m_yawImpulseMs = 0;

		const GolVec3& orientationRow = m_physicsEntity.GetOrientation().m_rows[2];
		GolVec3 direction;
		direction.m_x = orientationRow.m_x;
		direction.m_y = orientationRow.m_y;
		direction.m_z = orientationRow.m_z;
		CancelAngularMomentumAlong(&direction);
		m_flags &= ~(c_flagSpinning | c_flagSpinFresh | c_flagYawImpulse);

		if (m_spinSound != NULL) {
			m_spinSound->Stop();
			m_soundSource->ReleaseSound(m_spinSound);
			m_spinSound = NULL;
		}
	}
}

// FUNCTION: LEGORACERS 0x00448370
void RacerCarBody::SetThrust(LegoFloat p_thrust)
{
	m_thrust = p_thrust;
	UpdateDragCoefficient();
}

// FUNCTION: LEGORACERS 0x00448390
void RacerCarBody::SetMaxSpeed(LegoFloat p_maxSpeed)
{
	m_maxSpeed = p_maxSpeed;
	UpdateDragCoefficient();
}

// FUNCTION: LEGORACERS 0x004483b0
void RacerCarBody::UpdateDragCoefficient()
{
	if (m_thrust < 0.0f) {
		m_dragCoefficient = (m_mass * -m_thrust) / (m_maxSpeed * m_maxSpeed);
	}
	else if (m_thrust > 0.0f) {
		m_dragCoefficient = (m_mass * m_thrust) / (m_maxSpeed * m_maxSpeed);
	}
	else {
		m_dragCoefficient = 0.0f;
	}
}

// FUNCTION: LEGORACERS 0x00448430
void RacerCarBody::SnapToContacts(WheelProbe* p_probe)
{
	GolVec3 position;
	GolVec3 direction1;
	GolVec3 direction0;
	GolVec3 offset;
	WheelProbe* selectedEntry;
	if (m_contactCount > 1 && !m_rollImpulseMs && !m_pitchImpulseMs) {
		LegoU32 currentIndex = 0;
		selectedEntry = m_wheelProbes;

		if (m_contactCount < 4) {
			selectedEntry = p_probe;
			currentIndex = p_probe - m_wheelProbes;
		}

		LegoU32 entryIndex = g_wheelLengthwiseIndices[currentIndex];
		if (m_wheelProbes[entryIndex].m_flags & 1) {
			LegoU32 upperIndex;
			if (entryIndex < currentIndex) {
				upperIndex = currentIndex;
			}
			else {
				upperIndex = entryIndex;
				entryIndex = currentIndex;
			}

			const GolVec3& upper = m_wheelProbes[upperIndex].m_hitPoint;
			const GolVec3& lower = m_wheelProbes[entryIndex].m_hitPoint;
			direction0.m_x = lower.m_x - upper.m_x;
			direction0.m_y = lower.m_y - upper.m_y;
			direction0.m_z = lower.m_z - upper.m_z;
		}
		else {
			direction0.m_x = m_physicsEntity.GetOrientation().m_m[0][0];
			direction0.m_y = m_physicsEntity.GetOrientation().m_m[0][1];
			direction0.m_z = m_physicsEntity.GetOrientation().m_m[0][2];
		}

		entryIndex = g_wheelSidewaysIndices[currentIndex];
		if (m_wheelProbes[entryIndex].m_flags & 1) {
			LegoU32 lowerIndex;
			if (entryIndex > currentIndex) {
				lowerIndex = currentIndex;
			}
			else {
				lowerIndex = entryIndex;
				entryIndex = currentIndex;
			}

			const GolVec3& lower = m_wheelProbes[lowerIndex].m_hitPoint;
			const GolVec3& upper = m_wheelProbes[entryIndex].m_hitPoint;
			direction1.m_x = upper.m_x - lower.m_x;
			direction1.m_y = upper.m_y - lower.m_y;
			direction1.m_z = upper.m_z - lower.m_z;
		}
		else {
			direction1.m_x = m_physicsEntity.GetOrientation().m_m[1][0];
			direction1.m_y = m_physicsEntity.GetOrientation().m_m[1][1];
			direction1.m_z = m_physicsEntity.GetOrientation().m_m[1][2];
		}

		m_physicsEntity.FUN_00410a00(direction0, direction1);
	}
	else {
		selectedEntry = p_probe;
	}

	offset.m_x = selectedEntry->m_hitPoint.m_x - selectedEntry->m_wheelPosition.m_x + m_contactOffsetX;
	offset.m_y = selectedEntry->m_hitPoint.m_y - selectedEntry->m_wheelPosition.m_y + m_contactOffsetY;
	offset.m_z = selectedEntry->m_hitPoint.m_z - selectedEntry->m_wheelPosition.m_z + m_rideHeight;

	GolOrientedEntity* entity = &m_physicsEntity;
	entity->GetPosition(&position);
	position += offset;
	entity->SetPosition(position);
	ComputeWheelPositions();
}

// FUNCTION: LEGORACERS 0x00448660
void RacerCarBody::StartSliding()
{
	m_flags |= c_flagSliding;
	ApplyPitchImpulse(-0.003f, 150);
	m_slideLift = 0;
	m_slideBankAngle = 0;
	m_slideBankTarget = 0;
	ComputeWheelPositions();

	LegoFloat center = m_wheelProbes[0].m_wheelPosition.m_x;
	center += m_wheelProbes[1].m_wheelPosition.m_x;
	m_frontAxleMid.m_x = center * 0.5f;

	center = m_wheelProbes[0].m_wheelPosition.m_y;
	center += m_wheelProbes[1].m_wheelPosition.m_y;
	m_frontAxleMid.m_y = center * 0.5f;

	center = m_wheelProbes[0].m_wheelPosition.m_z;
	center += m_wheelProbes[1].m_wheelPosition.m_z;
	m_frontAxleMid.m_z = center * 0.5f;

	center = m_wheelProbes[2].m_wheelPosition.m_x;
	center += m_wheelProbes[3].m_wheelPosition.m_x;
	m_rearAxleMid.m_x = center * 0.5f;

	center = m_wheelProbes[2].m_wheelPosition.m_y;
	center += m_wheelProbes[3].m_wheelPosition.m_y;
	m_rearAxleMid.m_y = center * 0.5f;

	center = m_wheelProbes[2].m_wheelPosition.m_z;
	center += m_wheelProbes[3].m_wheelPosition.m_z;
	m_rearAxleMid.m_z = center * 0.5f;
}

// FUNCTION: LEGORACERS 0x00448730
void RacerCarBody::StopSliding()
{
	m_flags &= ~c_flagSliding;
	m_slideLift = 0;
	m_slideBankAngle = 0;
	m_slideBankTarget = 0;
}

// FUNCTION: LEGORACERS 0x00448760
void RacerCarBody::StartExternalForce0(GolVec3* p_force)
{
	LegoFloat scale = m_massScale;
	m_externalForce0.m_x = p_force->m_x * scale;
	LegoFloat y = p_force->m_y;
	y *= scale;
	m_externalForce0.m_y = y;
	LegoFloat z = p_force->m_z;
	z *= scale;
	m_externalForce0.m_z = z;
	m_flags |= c_flagExternalForce0;
}

// FUNCTION: LEGORACERS 0x004487a0
void RacerCarBody::EndExternalForce0()
{
	m_flags &= ~c_flagExternalForce0;
}

// FUNCTION: LEGORACERS 0x004487b0
void RacerCarBody::StartExternalForce1(GolVec3* p_force)
{
	LegoFloat scale = m_massScale;
	m_externalForce1.m_x = p_force->m_x * scale;
	LegoFloat y = p_force->m_y;
	y *= scale;
	m_externalForce1.m_y = y;
	LegoFloat z = p_force->m_z;
	z *= scale;
	m_externalForce1.m_z = z;
	m_flags |= c_flagExternalForce1;
}

// FUNCTION: LEGORACERS 0x004487f0
void RacerCarBody::EndExternalForce1()
{
	m_flags &= ~c_flagExternalForce1;
}

// FUNCTION: LEGORACERS 0x00448800
void RacerCarBody::StartSpinOut()
{
	m_spinOutMs = 600;
	m_flags |= c_flagSpinOut;
}

// FUNCTION: LEGORACERS 0x00448820
void RacerCarBody::EndSpinOut()
{
	m_spinOutMs = 0;
	m_flags &= ~c_flagSpinOut;
}

// FUNCTION: LEGORACERS 0x00449060
GolOrientedEntity* RacerCarBody::GetEntity()
{
	return m_carEntity;
}

// FUNCTION: LEGORACERS 0x004490b0
void RacerCarBody::MoveBy(GolVec3* p_delta)
{
	ClearWallContacts();
	SaveState();

	GolVec3 position;
	m_carEntity->GetPosition(&position);

	GolVec3 targetPosition;
	targetPosition.m_x = position.m_x + p_delta->m_x;
	targetPosition.m_y = position.m_y + p_delta->m_y;
	targetPosition.m_z = position.m_z + p_delta->m_z;
	m_carEntity->SetPosition(targetPosition);

	m_physicsEntity.SetPosition(targetPosition);
	ResolveWallCollisions(0, !(m_flags & c_flagNoTrackCollision));

	if (m_wallContact) {
		m_carEntity->SetPosition(position);
		m_physicsEntity.SetPosition(position);
	}
}
