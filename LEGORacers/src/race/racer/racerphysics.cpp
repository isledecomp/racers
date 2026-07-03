#include "audio/spatialsoundinstance.h"
#include "audio/streamingsoundinstance.h"
#include "golcamerabase.h"
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

extern const LegoFloat g_carBuildModelHeightScale;
extern const LegoFloat g_carBuildModelTextureCoordinateScale;
extern const LegoFloat g_surfaceSoundMaxDistance;
extern const LegoFloat g_surfaceSoundMinDistance;
extern const LegoFloat g_twoPi;
extern const LegoFloat g_unk0x004b0544;

// GLOBAL: LEGORACERS 0x004c4868
RacerPhysics::RouteCursorInstance g_routeProbeCursor;

// GLOBAL: LEGORACERS 0x004c48e0
GolMatrix3 g_routeProbeOrientation;

// GLOBAL: LEGORACERS 0x004b0430
extern const LegoFloat g_surfaceSoundMinDistance = 30.0f;

// GLOBAL: LEGORACERS 0x004b0434
extern const LegoFloat g_surfaceSoundMaxDistance = 300.0f;

// GLOBAL: LEGORACERS 0x004b0438
extern const LegoFloat g_surfaceVolumeMax = 1.0f;

// GLOBAL: LEGORACERS 0x004b043c
extern const LegoFloat g_unk0x004b043c = 0.5f;

// GLOBAL: LEGORACERS 0x004b0440
extern const LegoFloat g_surfaceFrequencyMax = 2.0f;

// GLOBAL: LEGORACERS 0x004b0448
extern const LegoFloat g_routeBaseMaxSpeed = 120.0f;

// GLOBAL: LEGORACERS 0x004b0450
extern const LegoFloat g_routeBoostMaxSpeed = 176.0f;

// GLOBAL: LEGORACERS 0x004b0454
extern const LegoFloat g_movingSpeedThreshold = 0.04f;

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

// GLOBAL: LEGORACERS 0x004b046c
extern const LegoFloat g_powerslideMinSpeed = 0.050000001f;

// GLOBAL: LEGORACERS 0x004b0470
extern const LegoFloat g_steeringMaxSpeed = 0.155f;

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

// GLOBAL: LEGORACERS 0x004b0550
extern const LegoFloat g_powerslideAlignmentMin = 0.85000002f;

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
	m_surfaceTable = 0;
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
	void* p_surfaceTable,
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
	m_surfaceTable = p_surfaceTable;
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
	GolMath::Matrix3ToQuat(p_carEntity->GetOrientation(), &m_resetRotation);
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
				GolMath::Matrix3ToQuat(m_physicsEntity.GetOrientation(), &m_resetRotation);
			}
		}

		GolOrientedEntity* entity = &m_physicsEntity;
		entity->GetPosition(&position);
		if (position.m_z < g_worldMinZ || position.m_z > g_worldMaxZ) {
			entity->SetPosition(m_resetPosition);
			GolMath::QuatToMatrix3(&m_resetRotation, &m_physicsEntity.GetOrientation().m_m[0][0]);
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
			GolMath::QuatToMatrix3(&m_resetRotation, &m_physicsEntity.GetOrientation().m_m[0][0]);
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
		else if (frequencyScale > g_surfaceFrequencyMax) {
			frequencyScale = g_surfaceFrequencyMax;
		}
		m_surfaceSound->SetFrequencyScale(frequencyScale);

		LegoFloat volume = static_cast<LegoFloat>(static_cast<LegoS32>(m_surfaceSoundMs)) / g_surfaceSoundFadeInMs;
		if (volume > g_surfaceVolumeMax) {
			volume = g_surfaceVolumeMax;
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
	LegoFloat playbackSpeed = g_routeSpinOutSpeed;
	m_routeCursor.m_playbackSpeed = playbackSpeed;
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
	GolMath::QuatToMatrix3(&rotation, &g_routeProbeOrientation.m_m[0][0]);

	GolVec3 currentDirection = g_routeProbeOrientation.m_rows[1];
	g_routeProbeCursor = m_routeCursor;
	g_routeProbeCursor.Advance(500.0f);

	rotation = g_routeProbeCursor.m_rotation;
	GolMath::QuatToMatrix3(&rotation, &g_routeProbeOrientation.m_m[0][0]);

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
	GolMath::QuatToMatrix3(&rotation, &m_carEntity->GetOrientation().m_m[0][0]);

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

// FUNCTION: LEGORACERS 0x0042a730
void RacerPhysics::AttachRouteAtLoop(RaceRouteRecord* p_record)
{
	m_routeMode = TRUE;
	m_routeCursor.AttachAtLoop(p_record);

	GolVec3 position = p_record->m_loopPosition;
	GolQuat rotation = p_record->m_loopRotation;

	m_carEntity->SetPosition(position);
	GolMath::QuatToMatrix3(&rotation, &m_carEntity->GetOrientation().m_m[0][0]);
	m_carEntity->LocalToWorld(m_centerOfMassLocal, &m_centerOfMassWorld);

	for (LegoS32 i = 0; i < 4; i++) {
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
		m_ownerRacer->m_controlMode != Racer::c_controlAi) {
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

// FUNCTION: LEGORACERS 0x0042ae10
LegoFloat RacerPhysics::GetMinTurnRadius()
{
	return ComputeMinTurnRadius();
}

// FUNCTION: LEGORACERS 0x0042ae20
LegoBool32 RacerPhysics::CanPowerslide()
{
	if (m_wallContact) {
		return FALSE;
	}

	if (!(m_flags & c_flagSliding) && m_contactCount < 3) {
		return FALSE;
	}

	GolOrientedEntity* entity = m_carEntity;
	LegoFloat dot = entity->m_orientation.m_rows[0].m_x;
	LegoFloat y = entity->m_orientation.m_rows[0].m_y;
	LegoFloat z = m_velocityDirection.m_z * entity->m_orientation.m_rows[0].m_z;
	z += y * m_velocityDirection.m_y;
	dot *= m_velocityDirection.m_x;
	dot += z;
	if (dot <= g_powerslideAlignmentMin) {
		return FALSE;
	}

	if (m_forwardSpeed < g_powerslideMinSpeed) {
		return FALSE;
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0042aea0
LegoBool32 RacerPhysics::CanSteer(LegoFloat p_turnRadius)
{
	GolOrientedEntity* entity = m_carEntity;
	LegoFloat dot = entity->m_orientation.m_rows[0].m_x;
	LegoFloat y = entity->m_orientation.m_rows[0].m_y;
	LegoFloat z = m_velocityDirection.m_z * entity->m_orientation.m_rows[0].m_z;
	z += y * m_velocityDirection.m_y;
	dot *= m_velocityDirection.m_x;
	dot += z;
	if (dot <= 0.0f) {
		return FALSE;
	}

	if ((p_turnRadius < 0.0f && m_turnRadius > 0.0f) || (p_turnRadius > 0.0f && m_turnRadius < 0.0f)) {
		return FALSE;
	}

	if (!(m_flags & c_flagSteering)) {
		LegoFloat dotValue = dot;
		if (dotValue < 0.89999998f) {
			return FALSE;
		}
	}

	if (m_wallContact) {
		return FALSE;
	}

	if (m_speed > g_steeringMaxSpeed) {
		return FALSE;
	}

	return TRUE;
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
		m_surfaceSound->SetDistanceRangeWithMinSquared(
			g_surfaceSoundMinDistance * g_surfaceSoundMinDistance,
			g_surfaceSoundMaxDistance
		);
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

// FUNCTION: LEGORACERS 0x0042b0c0
void RacerPhysics::ResetRouteMotion()
{
	GolVec3 direction;
	direction.m_x = 0.0f;
	m_routeCursor.m_playbackSpeed = 1.0f;
	direction.m_y = 0.0f;
	direction.m_z = 0.0f;
	m_routeCursor.SeekByDelta(&direction);

	m_routeBaseSpeed = 1.0f;
	m_routeMotion.m_sink = 0.0f;
	m_routeMotion.m_jumpHeight = 0.0f;
	m_routeMotion.m_sideOffset = 0.0f;
	m_routeMotion.m_jumpVelocity = 0.0f;
	m_routeTargetSpeed = 1.0f;
}
