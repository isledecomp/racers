#include "race/racestate.h"

#include <math.h>

extern LegoU16 g_randomTable[1024];
extern LegoU32 g_randomTableIndex;
extern LegoFloat g_carBuildPreviewMouseScale;
extern LegoFloat g_minSoundPan;
extern const LegoFloat g_violetShoalTwo;

// GLOBAL: LEGORACERS 0x004b0058
extern const LegoFloat g_driveMaxTurnRadius = 4096.0f;

// GLOBAL: LEGORACERS 0x004b005c
extern const LegoFloat g_inverseMinTurnRadius = 0.025f;

// GLOBAL: LEGORACERS 0x004b0060
extern const LegoFloat g_inverseMaxTurnRadius = 0.00025f;

// GLOBAL: LEGORACERS 0x004b0064
extern const LegoFloat g_fullThrottleThrust = 54.0f;

// GLOBAL: LEGORACERS 0x004b0068
extern const LegoFloat g_brakeThrustScale = 2.0f;

// GLOBAL: LEGORACERS 0x004b006c
extern const LegoFloat g_lowSpeedThreshold = 0.04f;

// GLOBAL: LEGORACERS 0x004b0070
extern const LegoFloat g_lowSpeedSteerScale = 0.2f;

// GLOBAL: LEGORACERS 0x004b0074
extern const LegoFloat g_unk0x004b0074 = 1.0f;

// GLOBAL: LEGORACERS 0x004b0078
extern const LegoFloat g_returnPathMinClosing = 0.00050000002f;

// GLOBAL: LEGORACERS 0x004b007c
extern const LegoFloat g_slideSteerAssistMin = 0.050000001f;

// GLOBAL: LEGORACERS 0x004b0088
extern const LegoFloat g_returnPathArriveDistance = 3.0f;

// GLOBAL: LEGORACERS 0x004b008c
extern const LegoFloat g_returnPathNearDistance = 30.0f;

// GLOBAL: LEGORACERS 0x004b0090
extern const LegoFloat g_returnPathMaxAdvanceDistance = 80.0f;

// GLOBAL: LEGORACERS 0x004b0094
extern const LegoFloat g_returnPathThrust = 18.0f;

// GLOBAL: LEGORACERS 0x004c4810
LegoFloat g_turboThrust = g_fullThrottleThrust * 8.0f;

// FUNCTION: LEGORACERS 0x0041fb50
DriveController::DriveController()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0041fb60
DriveController::~DriveController()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0041fb70
void DriveController::Destroy()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0041fb80
void DriveController::Reset()
{
	m_physics = NULL;
	m_returnRecord = NULL;
	m_previousTurnRadius = 0.0f;
	m_turnRadius = 0.0f;
	m_thrust = 0.0f;
	m_flags = 0;
	m_slideMs = 0;
	m_curseSteerOffset = 0.0f;
	m_curseThrottleOffset = 0.0f;
	m_curseJitterMs = 0;
	m_returnPreviewMs = 0;
	m_returnPosition.m_x = 0.0f;
	m_returnPosition.m_y = 0.0f;
	m_returnPosition.m_z = 0.0f;
	m_returnRotation.m_x = 0.0f;
	m_returnRotation.m_y = 0.0f;
	m_returnRotation.m_z = 0.0f;
	m_returnRotation.m_w = 0.0f;
	m_stuckMs = 0;
	m_slideLeft = 0;
	m_previewCursor = NULL;
}

// FUNCTION: LEGORACERS 0x0041fbd0
void DriveController::Initialize(RacerPhysics* p_physics)
{
	if (m_physics) {
		Destroy();
	}
	m_physics = p_physics;
}

// FUNCTION: LEGORACERS 0x0041fc00
void DriveController::Update(LegoU32 p_elapsedMs)
{
	LegoU32 flags = m_flags;
	m_previousTurnRadius = m_turnRadius;
	LegoU32 countdown = m_curseJitterMs;
	flags &= ~c_flagBit1;
	m_flags = flags;

	LegoU32 elapsedMs = p_elapsedMs;
	if (elapsedMs > countdown) {
		if (flags & c_flagCursed) {
			g_randomTableIndex = (g_randomTableIndex + 1) & 0x3ff;
			m_curseJitterMs = static_cast<LegoS32>(g_randomTable[g_randomTableIndex]) % 500;

			g_randomTableIndex = (g_randomTableIndex + 1) & 0x3ff;
			LegoS32 random = static_cast<LegoS32>(g_randomTable[g_randomTableIndex]) % 400;
			m_curseSteerOffset = static_cast<LegoFloat>(random) * g_carBuildPreviewMouseScale - g_violetShoalTwo;

			g_randomTableIndex = (g_randomTableIndex + 1) & 0x3ff;
			random = static_cast<LegoS32>(g_randomTable[g_randomTableIndex]) % 200;
			m_curseThrottleOffset = static_cast<LegoFloat>(random) * g_carBuildPreviewMouseScale - 1.0f;
		}
	}
	else {
		m_curseJitterMs = countdown - elapsedMs;
	}

	flags = m_flags;
	if (flags & c_flagSliding) {
		if (m_physics->m_forwardSpeed < 0.03f) {
			m_slideMs = 0;
			ReleaseSlide();
		}
		else {
			m_slideMs += elapsedMs;
		}
	}
	else if (flags & c_flagSlideBoost) {
		LegoU32 timerMs = m_slideMs;
		timerMs += elapsedMs;
		LegoU32 compareMs = timerMs;
		m_slideMs = timerMs;
		if (compareMs >= 300) {
			flags &= ~c_flagSlideBoost;
			m_slideMs = 0;
			m_flags = flags;
		}
	}

	flags = m_flags;
	if ((flags & c_flagTurbo) && m_physics->m_wallContact) {
		flags |= c_flagTurboWeakened;
		m_flags = flags;
	}

	ApplySteering();
	ApplyThrust();
}

// FUNCTION: LEGORACERS 0x0041fd60
void DriveController::UpdateBrakeToStop(LegoU32)
{
	if (m_physics->m_forwardSpeed > 0.0f) {
		m_thrust = -(g_fullThrottleThrust + g_fullThrottleThrust);
	}
	else {
		m_thrust = 0.0f;
	}

	ApplySteering();
	ApplyThrust();
}

// FUNCTION: LEGORACERS 0x0041fdb0
void DriveController::UpdateStuckDetection(LegoU32 p_elapsedMs)
{
	RacerPhysics* physics = m_physics;
	m_stuckMs += p_elapsedMs;

	if (physics->m_flags & RacerPhysics::c_flagSpinning) {
		LegoU32 flags = m_flags;
		m_stuckMs = 0;
		m_flags = flags & ~c_flagReversing;
		return;
	}

	LegoU32 flags = m_flags;
	if (flags & c_flagReversing) {
		if (m_stuckMs >= 2000) {
			m_stuckMs = 0;
			m_flags = flags & ~c_flagReversing;
		}
	}
	else {
		if (physics->m_forwardSpeed > 0.009f || -0.009f > physics->m_forwardSpeed) {
			m_stuckMs = 0;
		}
		else if (m_stuckMs >= 1000) {
			m_stuckMs = 0;
			m_flags = flags | c_flagReversing;
		}
	}
}

// FUNCTION: LEGORACERS 0x0041fe60
void DriveController::SetSteeringInput(LegoFloat p_input)
{
	if (m_flags & c_flagCursed) {
		p_input = -p_input;
	}

	p_input *= m_physics->m_handlingScale;
	LegoFloat value = (g_inverseMinTurnRadius - g_inverseMaxTurnRadius) * p_input;
	if (p_input > 0.0f) {
		m_turnRadius = 1.0f / (g_inverseMaxTurnRadius + value);
	}
	else if (p_input < 0.0f) {
		m_turnRadius = 1.0f / (value - g_inverseMaxTurnRadius);
	}
	else {
		m_turnRadius = 0.0f;
	}
}

// FUNCTION: LEGORACERS 0x0041fee0
void DriveController::ApplySteering()
{
	if (m_turnRadius == 0.0f && m_previousTurnRadius == 0.0f) {
		m_physics->SetTurnRadius(0.0f);
		m_previousTurnRadius = 0.0f;
		m_physics->StopSteering();
		return;
	}

	if (m_turnRadius != 0.0f && m_physics->m_speed < g_lowSpeedThreshold) {
		LegoFloat value = m_turnRadius;
		value *= g_lowSpeedSteerScale;
		m_turnRadius = value;
	}

	LegoFloat magnitude = m_turnRadius;
	if (magnitude < 0.0f) {
		magnitude = -magnitude;
	}

	LegoU32 flags = m_flags;
	if (flags & c_flagSliding) {
		if (!m_physics->CanSteer(m_turnRadius) || magnitude <= 0.0f) {
			m_physics->StopSteering();
			m_physics->SetTurnRadius(m_turnRadius);
			return;
		}

		LegoFloat limit = m_physics->ComputeMinTurnRadius();
		LegoFloat value = 1.0f - (magnitude / limit);
		if (value < g_slideSteerAssistMin) {
			value = g_slideSteerAssistMin;
		}

		LegoFloat scale;
		LegoFloat amount;
		if (m_slideLeft == 1) {
			scale = value + value + 1.0f;
			amount = 0.25f;
		}
		else {
			scale = value + 1.0f;
			amount = 0.85f;
		}

		m_physics->StartSteering(scale, amount, 3.1415927f);

		if (magnitude < limit) {
			value = ((limit - magnitude) * 0.5f) * 0.5f + magnitude;
			if (m_turnRadius < 0.0f) {
				value = -value;
			}
			m_turnRadius = value;
		}
	}
	else if (!(flags & c_flagBit1)) {
		LegoFloat limit = m_physics->GetMinTurnRadius();

		if (m_physics->CanSteer(m_turnRadius) && magnitude < limit && magnitude > 0.0f) {
			m_physics->StartSteering(1.0f - (magnitude / limit) + 1.0f, 0.85f, 0.70709997f);
		}
		else {
			m_physics->StopSteering();
		}

		if (magnitude < limit) {
			LegoFloat value = (limit + magnitude) * 0.5f;
			if (m_turnRadius < 0.0f) {
				value = -value;
			}
			m_turnRadius = value;
		}
	}

	m_physics->SetTurnRadius(m_turnRadius);
}

// FUNCTION: LEGORACERS 0x00420130
void DriveController::SetThrottleInput(LegoFloat p_input)
{
	if (m_flags & c_flagCursed) {
		p_input += m_curseThrottleOffset;

		if (p_input > 1.0f) {
			p_input = 1.0f;
		}
		else if (p_input < g_minSoundPan) {
			p_input = g_minSoundPan;
		}
	}

	if ((p_input < 0.0f && m_physics->m_forwardSpeed > 0.0f) || (p_input > 0.0f && m_physics->m_forwardSpeed < 0.0f)) {
		LegoFloat value = g_fullThrottleThrust * p_input;
		m_thrust = value * g_brakeThrustScale;
		return;
	}

	m_thrust = g_fullThrottleThrust * p_input;
}

// FUNCTION: LEGORACERS 0x004201e0
void DriveController::ApplyThrust()
{
	LegoU32 flags = m_flags;

	if ((flags & c_flagSlideBoost) && m_thrust > 0.0f) {
		LegoFloat value = m_thrust;
		value *= 8.0f;
		m_thrust = value;
	}

	if (flags & c_flagTurbo) {
		if (flags & c_flagTurboWeakened) {
			m_physics->SetThrust(0.5f * g_turboThrust);
		}
		else {
			m_physics->SetThrust(g_turboThrust);
		}
	}
	else {
		if (!(flags & c_flagBit1)) {
			m_physics->SetThrust(m_thrust);
		}
		else {
			LegoFloat value = m_thrust;
			value *= g_unk0x004b0074;
			m_physics->SetThrust(value);
		}
	}
}

// FUNCTION: LEGORACERS 0x00420260
void DriveController::EngageSlide(LegoBool32 p_left)
{
	LegoU32 flags = m_flags;
	m_flags = flags & ~c_flagSlideBoost;

	if (m_physics->CanPowerslide()) {
		m_flags |= c_flagSliding;
		m_slideMs = 0;
		m_slideLeft = p_left;

		if (!p_left) {
			m_physics->StartPowerslide(0x3e99999a);
			return;
		}

		m_physics->StartPowerslide(0x3ecccccd);
	}
}

// FUNCTION: LEGORACERS 0x004202c0
undefined4 DriveController::ReleaseSlide()
{
	LegoU32 flags = m_flags;
	flags &= ~4;
	m_flags = flags;
	m_physics->StopSteering();

	flags = m_flags;
	flags &= ~8;
	m_slideMs = 0;
	m_flags = flags;
	return m_physics->EndPowerslide();
}

// FUNCTION: LEGORACERS 0x004202f0
GolQuat* DriveController::StartReturnToPath(RaceRouteRecord* p_record)
{
	LegoU32 flags = m_flags;
	m_returnPreviewMs = 1000;
	flags |= 0x40;
	m_returnRecord = p_record;
	m_flags = flags;
	ReleaseSlide();

	RaceRouteRecord* value = m_returnRecord;
	m_turnRadius = 0;
	m_previewCursor->AttachAtLoop(value);

	m_previewCursor->m_playbackSpeed = 1.0f;
	m_previewCursor->Advance(static_cast<LegoFloat>(m_returnPreviewMs));

	GolQuat* basis = &m_returnRotation;
	RacerPhysics::RouteCursorInstance* previewCursor = m_previewCursor;
	m_returnPosition = previewCursor->m_position;
	GolQuat* result = &previewCursor->m_rotation;
	basis->m_x = result->m_x;
	basis->m_y = result->m_y;
	basis->m_z = result->m_z;
	basis->m_w = result->m_w;
	return result;
}

// FUNCTION: LEGORACERS 0x00420380
void DriveController::EndReturnToPath()
{
	LegoU32 flags = m_flags;
	flags &= ~c_flagReturnToPath;
	m_returnRecord = NULL;
	m_flags = flags;

	m_returnPreviewMs = 0;
	m_turnRadius = 0.0f;
	m_thrust = 0.0f;
	m_physics->SetTurnRadius(0.0f);
	m_physics->SetThrust(0.0f);
}

// FUNCTION: LEGORACERS 0x004203b0
void DriveController::UpdateReturnToPath(LegoU32 p_elapsedMs)
{
	GolVec3 delta;
	GolVec3 pathDirection;
	GolVec3 referenceDirection;
	GolVec3 activePathDirection;
	GolVec3 targetPosition;
	GolMatrix34 basis;

	m_physics->m_carEntity->GetPosition(&targetPosition);
	delta.m_x = m_returnPosition.m_x - targetPosition.m_x;
	delta.m_y = m_returnPosition.m_y - targetPosition.m_y;
	delta.m_z = m_returnPosition.m_z - targetPosition.m_z;

	LegoFloat distance =
		static_cast<LegoFloat>(sqrt(delta.m_z * delta.m_z + delta.m_y * delta.m_y + delta.m_x * delta.m_x));

	if (distance < g_returnPathArriveDistance) {
		m_physics->AttachRouteAtLoop(m_returnRecord);
		m_physics->ResetRouteMotion();
		m_physics->m_routeCursor.Advance(static_cast<LegoFloat>(m_returnPreviewMs));
		EndReturnToPath();
		return;
	}

	m_previousTurnRadius = m_turnRadius;
	UpdateStuckDetection(p_elapsedMs);

	if (m_physics->m_contactCount >= 3) {
		m_physics->m_carEntity->GetOrientationRow0(&referenceDirection);
	}
	else {
		referenceDirection = m_physics->m_facingDirection;
	}

	m_physics->m_carEntity->GetOrientationRow1(&pathDirection);
	LegoBool32 positiveDirection;
	if (pathDirection.m_z * delta.m_z + pathDirection.m_y * delta.m_y + pathDirection.m_x * delta.m_x >= 0.0f) {
		activePathDirection = pathDirection;
		positiveDirection = TRUE;
	}
	else {
		activePathDirection.m_x = -pathDirection.m_x;
		activePathDirection.m_y = -pathDirection.m_y;
		activePathDirection.m_z = -pathDirection.m_z;
		positiveDirection = FALSE;
	}

	LegoFloat inverseDistance = 1.0f / distance;
	delta.m_x = inverseDistance * delta.m_x;
	delta.m_y = inverseDistance * delta.m_y;
	delta.m_z = inverseDistance * delta.m_z;

	LegoFloat closingSpeed =
		delta.m_z * activePathDirection.m_z + delta.m_y * activePathDirection.m_y + delta.m_x * activePathDirection.m_x;
	if (closingSpeed < g_returnPathMinClosing) {
		m_turnRadius = g_driveMaxTurnRadius;
	}
	else {
		m_turnRadius = distance / (closingSpeed + closingSpeed);
	}

	if (!positiveDirection) {
		m_turnRadius = -m_turnRadius;
	}

	LegoU8 flags = static_cast<LegoU8>(m_flags);
	if (flags & c_flagReversing) {
		m_thrust = g_returnPathThrust;
		m_turnRadius = -m_turnRadius;
		m_thrust = -g_fullThrottleThrust;
	}
	else {
		m_thrust = g_returnPathThrust;
	}

	LegoBool32 updatePath = FALSE;
	if (distance < g_returnPathNearDistance) {
		updatePath = TRUE;
	}
	else {
		GolMath::QuatToMatrix3(&m_returnRotation, &basis.m_m[0][0]);
		if (basis.m_m[0][0] * referenceDirection.m_x + basis.m_m[0][1] * referenceDirection.m_y +
				basis.m_m[0][2] * referenceDirection.m_z <
			0.5f) {
			updatePath = TRUE;
		}
	}

	if (updatePath && distance <= g_returnPathMaxAdvanceDistance) {
		m_returnPreviewMs += 250;
		m_previewCursor->AttachAtLoop(m_returnRecord);
		m_previewCursor->Advance(static_cast<LegoFloat>(m_returnPreviewMs));
		m_returnPosition = m_previewCursor->m_position;
		m_returnRotation = m_previewCursor->m_rotation;
	}

	ApplySteering();
	ApplyThrust();
}
