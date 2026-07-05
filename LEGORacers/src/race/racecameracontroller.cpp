#include "race/racecameracontroller.h"

#include "audio/soundnode.h"
#include "camera/golcamera.h"
#include "camera/goltransform.h"
#include "decomp.h"
#include "render/gold3drenderdevice.h"

#include <math.h>

DECOMP_SIZE_ASSERT(RaceCameraController, 0x150)
DECOMP_SIZE_ASSERT(RaceCameraController::Profile, 0x18)

// GLOBAL: LEGORACERS 0x004b0314
extern const LegoFloat g_shakeFovMax = 80.0f;

// GLOBAL: LEGORACERS 0x004b0318
extern const LegoFloat g_shakeFovMin = 40.0f;

// GLOBAL: LEGORACERS 0x004b031c
extern const LegoFloat g_unk0x004b031c = 0.02f;

// GLOBAL: LEGORACERS 0x004b0320
extern const LegoFloat g_unk0x004b0320 = 0.1f;

// GLOBAL: LEGORACERS 0x004b0328
const RaceCameraController::Profile g_cameraProfiles[8] = {
	{1, 5.0f, 35.0f, 20.0f, 0.1f, 0.25f},
	{1, 8.0f, 25.0f, 30.0f, 0.1f, 0.25f},
	{1, 8.0f, 45.0f, 10.0f, 0.05f, 0.25f},
	{2, 0.0f, 0.0f, 0.0f, 0.1f, 0.25f},
	{3, 20.0f, 15.0f, 32.0f, 0.18f, 0.35f},
	{1, 8.0f, 20.0f, 22.0f, 0.1f, 0.25f},
	{1, 7.0f, 15.0f, 45.0f, 0.1f, 0.25f},
	{1, 4.0f, 30.0f, 15.0f, 0.05f, 0.25f},
};

// GLOBAL: LEGORACERS 0x004b03e8
extern const LegoFloat g_lagTimeScale = 250.0f;

// GLOBAL: LEGORACERS 0x004b03ec
extern const LegoFloat g_degreesToRadians = 0.017453292f;

// GLOBAL: LEGORACERS 0x004b03f8
extern const LegoFloat g_transitionTurnRate = 0.0015707964f;

// GLOBAL: LEGORACERS 0x004b03fc
extern const LegoFloat g_cameraMinDistance = 12.0f;

// GLOBAL: LEGORACERS 0x004b0408
extern const LegoFloat g_unk0x004b0408 = -3.1415927f;

// GLOBAL: LEGORACERS 0x004b040c
extern const LegoFloat g_viewAngleDeadband = 0.014f;

// GLOBAL: LEGORACERS 0x004b0410
extern const LegoFloat g_unk0x004b0410 = -0.014f;

// GLOBAL: LEGORACERS 0x004b0418
extern const LegoFloat g_unk0x004b0418 = -0.30000001f;

// GLOBAL: LEGORACERS 0x004b041c
extern const LegoFloat g_turnLookAheadScale = 80.0f;

// GLOBAL: LEGORACERS 0x004b0420
extern const LegoFloat g_transitionProgressScale = 0.00050000002f;

// FUNCTION: LEGORACERS 0x00427b70
void RaceCameraController::SetPositionLag(LegoFloat p_amount)
{
	m_positionLag = (1.0f - p_amount) / (g_lagTimeScale * p_amount);
}

// FUNCTION: LEGORACERS 0x00427b90
void RaceCameraController::SetRotationLag(LegoFloat p_amount)
{
	m_rotationLag = (1.0f - p_amount) / (g_lagTimeScale * p_amount);
}

// FUNCTION: LEGORACERS 0x00427bb0
void RaceCameraController::SetPitchAngle(LegoFloat p_degrees)
{
	GolMath::SinCos(g_degreesToRadians * p_degrees, &m_pitchSine, &m_pitchCosine);
}

// FUNCTION: LEGORACERS 0x00427be0
void RaceCameraController::SetHeightAngle(LegoFloat p_degrees)
{
	m_heightSine = static_cast<LegoFloat>(sin(g_degreesToRadians * p_degrees));
}

// FUNCTION: LEGORACERS 0x00427c00
void RaceCameraController::UpdateListener()
{
	if (m_listenerNode == NULL || m_racer == NULL) {
		return;
	}

	GolVec3 velocity = m_racer->m_physics.m_velocity;
	GolVec3 right;
	GolVec3 forward;
	m_racer->m_visuals.m_carEntity->GetAxes(&right, &forward);

	GolVec3 position;
	m_racer->m_visuals.m_carEntity->GetPosition(&position);

	{
		SoundNode* soundNode = m_listenerNode;
		soundNode->m_velocity.m_x = velocity.m_x;
		soundNode->m_velocity.m_y = velocity.m_y;
		soundNode->m_velocity.m_z = velocity.m_z;
		soundNode->m_unk0x44 = TRUE;
	}

	{
		SoundNode* soundNode = m_listenerNode;
		SoundVector* rightVector = &soundNode->m_right;
		SoundVector* forwardVector = &soundNode->m_forward;
		rightVector->m_x = right.m_x;
		rightVector->m_y = right.m_y;
		rightVector->m_z = right.m_z;
		forwardVector->m_x = forward.m_x;
		forwardVector->m_y = forward.m_y;
		forwardVector->m_z = forward.m_z;

		SoundVector* orientation = &soundNode->m_orientation;
		orientation->m_x = forwardVector->m_y * rightVector->m_z - forwardVector->m_z * rightVector->m_y;
		orientation->m_y = forwardVector->m_z * rightVector->m_x - forwardVector->m_x * rightVector->m_z;
		orientation->m_z = rightVector->m_y * forwardVector->m_x - forwardVector->m_y * rightVector->m_x;
		GolMath::NormalizeVector3(*orientation, orientation);
		soundNode->m_unk0x44 = TRUE;
	}

	{
		SoundNode* soundNode = m_listenerNode;
		soundNode->m_position.m_x = position.m_x;
		soundNode->m_position.m_y = position.m_y;
		soundNode->m_position.m_z = position.m_z;
		soundNode->m_unk0x44 = TRUE;
	}
}

// FUNCTION: LEGORACERS 0x00427d30
void RaceCameraController::UpdateFollow()
{
	GolCamera* camera = m_camera;
	if (camera == NULL) {
		return;
	}

	GolVec3 right;
	GolVec3 forward;
	if (m_mode == c_modeChase && m_lookBack) {
		GolVec3 position;
		position.m_x = m_lastRacerPosition.m_x + m_lastRacerPosition.m_x - m_smoothedTransform.m_position.m_x;
		position.m_y = m_lastRacerPosition.m_y + m_lastRacerPosition.m_y - m_smoothedTransform.m_position.m_y;
		position.m_z = m_smoothedTransform.m_position.m_z;
		camera->GetTransform()->SetPosition(&position);
		camera->m_flags |= GolCamera::c_flagViewDirty;

		right.m_x = -m_smoothedTransform.m_orientation.m_rows[2].m_x;
		right.m_y = -m_smoothedTransform.m_orientation.m_rows[2].m_y;
		forward.m_x = -m_smoothedTransform.m_orientation.m_rows[1].m_x;
		forward.m_y = -m_smoothedTransform.m_orientation.m_rows[1].m_y;
		right.m_z = m_smoothedTransform.m_orientation.m_rows[2].m_z;
		forward.m_z = m_smoothedTransform.m_orientation.m_rows[1].m_z;

		camera->GetTransform()->SetDirectionUp(&right, &forward);
		camera->m_flags |= GolCamera::c_flagViewDirty;
		return;
	}
	if (m_mode == c_modeCockpit && m_lookBack) {
		camera->GetTransform()->SetPosition(&m_smoothedTransform.m_position);
		camera->m_flags |= GolCamera::c_flagViewDirty;

		forward.m_x = m_smoothedTransform.m_orientation.m_rows[1].m_x;
		right.m_x = -m_smoothedTransform.m_orientation.m_rows[2].m_x;
		right.m_y = -m_smoothedTransform.m_orientation.m_rows[2].m_y;
		forward.m_y = m_smoothedTransform.m_orientation.m_rows[1].m_y;
		right.m_z = -m_smoothedTransform.m_orientation.m_rows[2].m_z;
		forward.m_z = m_smoothedTransform.m_orientation.m_rows[1].m_z;

		camera->GetTransform()->SetDirectionUp(&right, &forward);
		camera->m_flags |= GolCamera::c_flagViewDirty;
		return;
	}
	camera->GetTransform()->SetPosition(&m_smoothedTransform.m_position);
	camera->m_flags |= GolCamera::c_flagViewDirty;
	camera->GetTransform()->SetDirectionUp(
		&m_smoothedTransform.m_orientation.m_rows[2],
		&m_smoothedTransform.m_orientation.m_rows[1]
	);
	camera->m_flags |= GolCamera::c_flagViewDirty;
}

extern LegoU16 g_randomTable[1024];
extern LegoU32 g_randomTableIndex;
extern const LegoFloat g_halfPi;
extern const LegoFloat g_hazardPi;
extern const LegoFloat g_statMax;
extern const LegoFloat g_hazardPi;
extern const LegoFloat g_twoPi;
extern const LegoFloat g_brickSettleRate;
extern const LegoFloat g_unk0x004afde0;
extern const LegoFloat g_warpPortalHeightOffset;

// FUNCTION: LEGORACERS 0x00427e80
void RaceCameraController::UpdateShake()
{
	if (static_cast<LegoU32>(m_elapsedMs) > m_shakeMs) {
		m_shakeMs = 0;
	}
	else {
		m_shakeMs -= m_elapsedMs;
	}

	if (m_racer->m_flags & 0x10) {
		m_shakeAmount = 0.0f;
		m_shakeMs = 0;
	}
	else if (!m_shakeMs) {
		m_shakeMs = 500;
		m_baseFov = m_camera->m_fov;

		if (m_racer->m_flags & 0x800) {
			if ((m_shakeAmount > 0.0f || m_baseFov <= g_shakeFovMin) && m_baseFov < g_shakeFovMax) {
				g_randomTableIndex = (g_randomTableIndex + 1) & 0x3ff;
				m_shakeAmount =
					-(static_cast<LegoFloat>(
						  static_cast<LegoU16>(g_randomTable[g_randomTableIndex]) %
						  static_cast<LegoS32>(g_shakeFovMax - m_baseFov)
					  ) *
					  0.5f);
			}
			else {
				g_randomTableIndex = (g_randomTableIndex + 1) & 0x3ff;
				m_shakeAmount = static_cast<LegoFloat>(
									static_cast<LegoU16>(g_randomTable[g_randomTableIndex]) %
									static_cast<LegoS32>(m_baseFov - g_shakeFovMin)
								) *
								0.5f;
			}
		}
		else {
			if (m_camera->m_fov != m_targetFov) {
				m_shakeAmount = (m_baseFov - m_targetFov) * 0.5f;
			}
			else {
				m_shakeAmount = 0.0f;
				m_shakeMs = 0;
			}
		}
	}

	if (m_shakeMs) {
		LegoS32 remaining = 500;
		GolCamera* camera = m_camera;
		remaining -= m_shakeMs;
		LegoFloat phase = static_cast<LegoFloat>(remaining);
		phase *= g_unk0x004b031c;
		phase *= g_unk0x004b0320;
		phase *= g_hazardPi;
		LegoFloat angle = static_cast<LegoFloat>(cos(phase));
		LegoFloat fov = angle * m_shakeAmount + (m_baseFov - m_shakeAmount);
		camera->m_flags |= GolCamera::c_flagProjectionDirty;
		camera->m_fov = fov;
		m_renderer->ApplyCamera();
	}
	else if (m_camera->m_fov != m_targetFov) {
		GolCamera* camera = m_camera;
		LegoFloat fov = m_targetFov;
		camera->m_flags |= GolCamera::c_flagProjectionDirty;
		camera->m_fov = fov;
		m_renderer->ApplyCamera();
	}
}

// FUNCTION: LEGORACERS 0x004280a0
void RaceCameraController::ApplySmoothing()
{
	GolMath::Matrix3ToQuat(m_rawTransform.m_orientation, &m_rawRotation);

	if (m_frameDirty & 1) {
		m_smoothedTransform = m_rawTransform;
		m_smoothedRotation = m_rawRotation;
	}
	else {
		LegoFloat positionAmount = 1.0f / (m_positionLag * m_elapsed + 1.0f);
		GolVec3 positionDelta;
		positionDelta.m_x = m_previousTransform.m_position.m_x - m_rawTransform.m_position.m_x;
		positionDelta.m_y = m_previousTransform.m_position.m_y - m_rawTransform.m_position.m_y;
		positionDelta.m_z = m_previousTransform.m_position.m_z - m_rawTransform.m_position.m_z;

		GolVec3 scaledPositionDelta;
		scaledPositionDelta.m_x = positionDelta.m_x * positionAmount;
		scaledPositionDelta.m_y = positionDelta.m_y * positionAmount;
		scaledPositionDelta.m_z = positionDelta.m_z * positionAmount;
		m_smoothedTransform.m_position.m_x = scaledPositionDelta.m_x + m_rawTransform.m_position.m_x;
		m_smoothedTransform.m_position.m_y = scaledPositionDelta.m_y + m_rawTransform.m_position.m_y;
		m_smoothedTransform.m_position.m_z = scaledPositionDelta.m_z + m_rawTransform.m_position.m_z;

		LegoFloat rotationAmount = 1.0f / (m_rotationLag * m_elapsed + 1.0f);
		GolMath::LerpQuat(m_rawRotation, m_previousRotation, rotationAmount, &m_smoothedRotation);
		GolMath::QuatToMatrix3(&m_smoothedRotation, &m_smoothedTransform.m_m[0][0]);
	}

	UpdateFollow();
	UpdateListener();
}

// FUNCTION: LEGORACERS 0x004281b0
void RaceCameraController::Reset()
{
	m_racer = NULL;
	m_dirty = TRUE;
	SetView(0, FALSE);
	m_targetPositionRate = 0.09f;
	m_turnLeadRate = 0.0044444446f;
	m_viewAngleRate = 0.016666668f;
	m_shakeMs = 0;
	m_listenerNode = NULL;
	m_lookBack = FALSE;
	m_alternate = FALSE;
}

// FUNCTION: LEGORACERS 0x00428200
RaceCameraController::RaceCameraController()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00428210
void RaceCameraController::Initialize(GolCamera* p_camera, GolD3DRenderDevice* p_renderer)
{
	m_camera = p_camera;
	m_renderer = p_renderer;
	m_targetFov = p_camera->GetFov();
}

// FUNCTION: LEGORACERS 0x00428230
void RaceCameraController::SetRacer(Racer* p_racer)
{
	if (m_racer != p_racer) {
		m_racer = p_racer;
		m_racer->m_visuals.m_carEntity->GetPosition(&m_lastRacerPosition);
		LegoU32 flags = m_racer->m_driveController.m_flags;
		m_followDistanceScale = 1.0f;
		m_turboActive = flags & 1;
		GolAnimatedEntity* entity = m_racer->m_visuals.m_carEntity;
		m_viewDirection.m_x = entity->GetOrientation().m_rows[0].m_x;
		m_viewDirection.m_y = entity->GetOrientation().m_rows[0].m_y;
		m_viewDirection.m_z = entity->GetOrientation().m_rows[0].m_z;
	}
}

// FUNCTION: LEGORACERS 0x004282a0
void RaceCameraController::SetOrientation(GolVec3* p_direction, GolVec3* p_up)
{
	BuildOrientation(p_direction, p_up, &m_smoothedTransform.m_orientation);
	m_previousTransform.m_orientation = m_smoothedTransform.m_orientation;
}

// FUNCTION: LEGORACERS 0x004282d0
void RaceCameraController::BuildOrientation(GolVec3* p_direction, GolVec3* p_up, GolMatrix3* p_dest)
{
	GolVec3* source = p_direction;
	GolVec3* up = &p_dest->m_rows[1];
	GolVec3* back = &p_dest->m_rows[2];

	GolMath::NormalizeVector3(*source, back);

	GolVec3 forward;
	GolMath::NormalizeVector3(*source, &forward);

	LegoFloat dot = p_up->m_z * forward.m_z;
	dot += p_up->m_y * forward.m_y;
	dot += forward.m_x * p_up->m_x;

	GolVec3 projection;
	projection.m_x = forward.m_x * dot;
	projection.m_y = forward.m_y * dot;
	projection.m_z = forward.m_z * dot;

	up->m_x = p_up->m_x - projection.m_x;
	up->m_y = p_up->m_y - projection.m_y;
	up->m_z = p_up->m_z - projection.m_z;

	GolMath::NormalizeVector3(*up, up);

	GolVec3* right = &p_dest->m_rows[0];
	right->m_x = up->m_y * back->m_z - up->m_z * back->m_y;
	right->m_y = up->m_z * back->m_x - back->m_z * up->m_x;
	right->m_z = back->m_y * up->m_x - up->m_y * back->m_x;
}

// FUNCTION: LEGORACERS 0x00428390
void RaceCameraController::SnapPosition(GolVec3* p_position)
{
	m_previousTransform.m_position = *p_position;
	m_smoothedTransform.m_position = *p_position;
}

// FUNCTION: LEGORACERS 0x004283d0
void RaceCameraController::SetMode(LegoU8 p_mode)
{
	if (m_mode != p_mode) {
		m_mode = p_mode;
		m_transitionMs = 0;
	}
}

// FUNCTION: LEGORACERS 0x004283f0
void RaceCameraController::SetView(LegoS32 p_viewIndex, LegoBool32 p_alternate)
{
	LegoS32 profileIndex = p_viewIndex;
	m_alternate = p_alternate;
	if (p_alternate && profileIndex < 3) {
		profileIndex += 5;
	}

	SetMode(g_cameraProfiles[profileIndex].m_mode);

	if (m_mode == c_modeFinish) {
		m_blendHeightSine = m_heightSine;
		m_blendPitchSine = m_pitchSine;
		m_blendPitchCosine = m_pitchCosine;
		m_blendFollowDistance = m_followDistance;
	}

	SetPitchAngle(g_cameraProfiles[profileIndex].m_pitchAngle);
	SetHeightAngle(g_cameraProfiles[profileIndex].m_heightAngle);
	m_followDistance = g_cameraProfiles[profileIndex].GetFollowDistance();
	SetPositionLag(g_cameraProfiles[profileIndex].m_positionLag);
	SetRotationLag(g_cameraProfiles[profileIndex].m_rotationLag);

	if (m_mode == c_modeFinish) {
		m_blendHeightSine -= m_heightSine;
		m_blendPitchSine -= m_pitchSine;
		m_blendPitchCosine -= m_pitchCosine;
		m_blendFollowDistance -= m_followDistance;
	}

	m_lookBack = FALSE;
}

// FUNCTION: LEGORACERS 0x00428500
GolVec3* RaceCameraController::GetViewDirection(GolVec3* p_dest)
{
	if (m_mode == c_modeFinish) {
		GolVec3* source = &m_viewDirection;
		p_dest->m_x = source->m_x;
		p_dest->m_y = source->m_y;
		p_dest->m_z = source->m_z;
	}
	else {
		p_dest->m_x = m_smoothedTransform.m_orientation.m_rows[2].m_x;
		p_dest->m_y = m_smoothedTransform.m_orientation.m_rows[2].m_y;
		p_dest->m_z = m_smoothedTransform.m_orientation.m_rows[2].m_z;
	}

	return p_dest;
}

// FUNCTION: LEGORACERS 0x00428540
void RaceCameraController::Update(LegoFloat p_elapsedMs)
{
	if (m_racer == NULL) {
		m_dirty = TRUE;
		return;
	}

	if (m_camera->m_trackedEntity) {
		m_camera->UpdateFromTrackedEntity();
		return;
	}

	if (p_elapsedMs <= 0.0f) {
		if (!(m_dirty & 1)) {
			return;
		}
		p_elapsedMs = 0.0f;
	}

	m_frameDirty = m_dirty;
	m_dirty &= 0xf0;
	if (p_elapsedMs <= g_statMax) {
		m_elapsed = p_elapsedMs;
	}
	else {
		m_elapsed = g_statMax;
	}

	m_elapsedMs = static_cast<LegoS32>(m_elapsed);
	UpdateShake();

	if (m_mode) {
		m_previousTransform = m_smoothedTransform;
		m_previousRotation = m_smoothedRotation;
	}

	switch (m_mode) {
	case 0: {
		m_racer->m_visuals.m_carEntity->GetPosition(&m_lastRacerPosition);

		if (m_transitionMs == 0.0f) {
			GolMath::Matrix3ToQuat(m_previousTransform.m_orientation, &m_previousRotation);
			GolMath::Matrix3ToQuat(m_rawTransform.m_orientation, &m_rawRotation);
		}

		m_transitionMs += m_elapsed;
		LegoFloat amount;
		if (m_transitionMs <= 2000.0f) {
			amount = m_transitionMs * g_transitionProgressScale;
		}
		else {
			m_transitionMs = 2000.0f;
			amount = 1.0f;
		}

		m_smoothedTransform.m_position.m_x =
			(m_rawTransform.m_position.m_x - m_previousTransform.m_position.m_x) * amount +
			m_previousTransform.m_position.m_x;
		m_smoothedTransform.m_position.m_y =
			(m_rawTransform.m_position.m_y - m_previousTransform.m_position.m_y) * amount +
			m_previousTransform.m_position.m_y;
		m_smoothedTransform.m_position.m_z =
			(m_rawTransform.m_position.m_z - m_previousTransform.m_position.m_z) * amount +
			m_previousTransform.m_position.m_z;
		GolMath::LerpQuat(m_previousRotation, m_rawRotation, amount, &m_smoothedRotation);
		GolMath::QuatToMatrix3(&m_smoothedRotation, &m_smoothedTransform.m_m[0][0]);
		UpdateFollow();
		UpdateListener();
		return;
	}
	case 1:
	case 3: {
		Racer* racer = m_racer;
		GolAnimatedEntity* entity = racer->m_visuals.m_carEntity;
		GolVec3 targetPosition;
		entity->GetPosition(&targetPosition);

		GolVec3 desiredDirection = entity->GetOrientation().m_rows[0];
		if (desiredDirection.m_x == 0.0f && desiredDirection.m_y == 0.0f) {
			if (m_viewDirection.m_x == 0.0f && m_viewDirection.m_y == 0.0f) {
				m_viewDirection.m_x = 1.0f;
				m_viewDirection.m_y = 0.0f;
				m_viewDirection.m_z = 0.0f;
			}
			desiredDirection = m_viewDirection;
		}
		desiredDirection.m_z = 0.0f;

		GolVec2 desiredDirection2D;
		desiredDirection2D.m_x = desiredDirection.m_x;
		desiredDirection2D.m_y = desiredDirection.m_y;
		GolMath::NormalizeVector2(desiredDirection2D, &desiredDirection2D);
		desiredDirection.m_x = desiredDirection2D.m_x;
		desiredDirection.m_y = desiredDirection2D.m_y;

		if (m_viewDirection.m_z != 0.0f) {
			m_viewDirection.m_z = 0.0f;
			GolVec2 direction2D;
			direction2D.m_x = m_viewDirection.m_x;
			direction2D.m_y = m_viewDirection.m_y;
			GolMath::NormalizeVector2(direction2D, &direction2D);
			m_viewDirection.m_x = direction2D.m_x;
			m_viewDirection.m_y = direction2D.m_y;
		}

		if (m_frameDirty & 1) {
			m_turnLeadAngle = 0.0f;
			m_viewDirection = desiredDirection;
		}
		else {
			if (racer->m_physics.m_flags & RacerPhysics::c_flagSpinning) {
				desiredDirection = m_viewDirection;
			}
			else {
				LegoFloat turnAmount;
				if (racer->m_physics.m_turnRadius == 0.0f) {
					turnAmount = 0.0f;
				}
				else {
					turnAmount = racer->m_physics.m_forwardSpeed * g_turnLookAheadScale / racer->m_physics.m_turnRadius;
					if (turnAmount < g_unk0x004b0418) {
						turnAmount = g_unk0x004b0418;
					}
					else if (turnAmount > -g_unk0x004b0418) {
						turnAmount = -g_unk0x004b0418;
					}
				}

				m_turnLeadAngle =
					turnAmount + 1.0f / (m_turnLeadRate * m_elapsed + 1.0f) * (m_turnLeadAngle - turnAmount);

				LegoFloat turnSin;
				LegoFloat turnCos;
				GolMath::SinCos(m_turnLeadAngle, &turnSin, &turnCos);

				LegoFloat oldX = desiredDirection.m_x;
				desiredDirection.m_x = turnCos * desiredDirection.m_x - turnSin * desiredDirection.m_y;
				desiredDirection.m_y = turnCos * desiredDirection.m_y + turnSin * oldX;

				LegoFloat currentAngle = VectorToAngle(m_viewDirection.m_x, m_viewDirection.m_y);
				LegoFloat desiredAngle = VectorToAngle(desiredDirection.m_x, desiredDirection.m_y);
				LegoFloat delta = currentAngle - desiredAngle;
				if (delta < g_unk0x004b0410 || delta > g_viewAngleDeadband) {
					while (delta < g_unk0x004b0408) {
						delta += g_twoPi;
					}
					while (delta > -g_unk0x004b0408) {
						delta -= g_twoPi;
					}

					LegoFloat angleAmount = 1.0f / (m_viewAngleRate * m_elapsed + 1.0f);
					LegoFloat angle = delta * angleAmount + desiredAngle;
					GolMath::SinCos(angle, &desiredDirection.m_y, &desiredDirection.m_x);
				}
			}

			LegoFloat positionAmount = 1.0f / (m_targetPositionRate * m_elapsed + 1.0f);
			targetPosition.m_x = (m_lastRacerPosition.m_x - targetPosition.m_x) * positionAmount + targetPosition.m_x;
			targetPosition.m_y = (m_lastRacerPosition.m_y - targetPosition.m_y) * positionAmount + targetPosition.m_y;
			targetPosition.m_z = (m_lastRacerPosition.m_z - targetPosition.m_z) * positionAmount + targetPosition.m_z;
		}
		m_lastRacerPosition = targetPosition;

		if (m_turboActive) {
			m_turboActive = racer->m_driveController.m_flags & DriveController::c_flagTurbo;
		}
		else {
			m_turboActive = racer->m_driveController.m_flags & DriveController::c_flagTurbo;
			if (m_turboActive) {
				switch (racer->m_turboLevel) {
				case 0:
					m_followDistanceScale = -0.2f;
					break;
				case 1:
					m_followDistanceScale = -0.4f;
					break;
				case 2:
					m_followDistanceScale = -0.6f;
					break;
				case 3:
					m_followDistanceScale = 1.0f;
					break;
				default:
					break;
				}
			}
		}

		LegoFloat cameraDistance;
		if (m_followDistanceScale >= 1.0f) {
			cameraDistance = m_followDistance;
		}
		else {
			LegoFloat transitionStep;
			if (m_alternate) {
				transitionStep = m_elapsed * 0.0040000002f;
			}
			else {
				transitionStep = m_elapsed * g_brickSettleRate;
			}
			m_followDistanceScale += transitionStep;

			if (m_followDistanceScale <= 1.0f) {
				cameraDistance = m_followDistanceScale * m_followDistance;
				if (m_followDistanceScale < 0.0f) {
					cameraDistance = -cameraDistance;
				}
				if (cameraDistance < g_cameraMinDistance) {
					cameraDistance = g_cameraMinDistance;
				}
			}
			else {
				m_followDistanceScale = 1.0f;
				cameraDistance = m_followDistance;
			}
		}

		if (desiredDirection.m_x != 0.0f || desiredDirection.m_y != 0.0f) {
			m_viewDirection = desiredDirection;
		}

		GolVec3 up;
		up.m_x = 0.0f;
		up.m_y = 0.0f;
		up.m_z = -1.0f;
		m_viewDirection.m_z = 0.0f;

		GolVec2 direction2D;
		direction2D.m_x = m_viewDirection.m_x;
		direction2D.m_y = m_viewDirection.m_y;
		GolMath::NormalizeVector2(direction2D, &direction2D);
		m_viewDirection.m_x = direction2D.m_x;
		m_viewDirection.m_y = direction2D.m_y;

		LegoFloat verticalOffset = m_heightSine;
		LegoFloat height;
		GolVec3 cameraOffset;
		if (m_mode == c_modeFinish) {
			m_transitionMs += m_elapsed;
			if (m_transitionMs <= 2000.0f) {
				LegoFloat profileAmount = 1.0f - m_transitionMs * g_transitionProgressScale;
				cameraDistance = m_blendFollowDistance * profileAmount + m_followDistance;
				height = m_blendPitchSine * profileAmount + m_pitchSine;
				verticalOffset = m_blendHeightSine * profileAmount + m_heightSine;
				LegoFloat sideDistance = m_blendPitchCosine * profileAmount + m_pitchCosine;

				LegoFloat turnSin;
				LegoFloat turnCos;
				GolMath::SinCos(m_transitionMs * g_transitionTurnRate, &turnSin, &turnCos);
				cameraOffset.m_x = (m_viewDirection.m_x * turnCos - m_viewDirection.m_y * turnSin) * sideDistance;
				cameraOffset.m_y = (m_viewDirection.m_x * turnSin + m_viewDirection.m_y * turnCos) * sideDistance;
			}
			else {
				m_transitionMs = 2000.0f;
				cameraDistance = m_followDistance;
				cameraOffset.m_x = -(m_pitchCosine * m_viewDirection.m_x);
				cameraOffset.m_y = -(m_viewDirection.m_y * m_pitchCosine);
				height = m_pitchSine;
			}
		}
		else {
			cameraOffset.m_x = m_pitchCosine * m_viewDirection.m_x;
			cameraOffset.m_y = m_viewDirection.m_y * m_pitchCosine;
			height = m_pitchSine;
		}

		cameraOffset.m_z = -height;
		if (m_frameDirty & 1) {
			m_rawTransform.m_position.m_x = m_lastRacerPosition.m_x - cameraOffset.m_x * cameraDistance;
			m_rawTransform.m_position.m_y = m_lastRacerPosition.m_y - cameraOffset.m_y * cameraDistance;
			m_rawTransform.m_position.m_z =
				m_lastRacerPosition.m_z - (cameraOffset.m_z - verticalOffset) * cameraDistance;
		}
		else {
			m_rawTransform.m_position.m_x =
				m_lastRacerPosition.m_x - m_previousTransform.m_orientation.m_rows[2].m_x * cameraDistance;
			m_rawTransform.m_position.m_y =
				m_lastRacerPosition.m_y - m_previousTransform.m_orientation.m_rows[2].m_y * cameraDistance;
			m_rawTransform.m_position.m_z =
				m_lastRacerPosition.m_z -
				(m_previousTransform.m_orientation.m_rows[2].m_z - verticalOffset) * cameraDistance;
		}

		BuildOrientation(&cameraOffset, &up, &m_rawTransform.m_orientation);
		ApplySmoothing();
		return;
	}
	case 2: {
		Racer* racer = m_racer;
		GolAnimatedEntity* entity = racer->m_visuals.m_carEntity;
		entity->GetPosition(&m_lastRacerPosition);

		GolVec3 right = entity->GetOrientation().m_rows[0];
		GolVec3 up = entity->GetOrientation().m_rows[2];
		up.m_x = -up.m_x;
		up.m_y = -up.m_y;
		up.m_z = -up.m_z;
		BuildOrientation(&right, &up, &m_rawTransform.m_orientation);

		entity->GetPosition(&m_rawTransform.m_position);
		if (m_alternate) {
			m_rawTransform.m_position.m_z += g_warpPortalHeightOffset;
			ApplySmoothing();
			return;
		}

		m_rawTransform.m_position.m_z += g_unk0x004afde0;
		ApplySmoothing();
		return;
	}
	default:
		return;
	}
}

// FUNCTION: LEGORACERS 0x00428f40
LegoFloat RaceCameraController::VectorToAngle(LegoFloat p_x, LegoFloat p_y)
{
	LegoFloat absY;
	if (p_y < 0.0f) {
		absY = -p_y;
	}
	else {
		absY = p_y;
	}

	LegoFloat absX;
	if (p_x < 0.0f) {
		absX = -p_x;
	}
	else {
		absX = p_x;
	}

	if (absY < absX) {
		if (p_x > 0.0f) {
			LegoFloat angle = static_cast<LegoFloat>(acos(p_y));
			angle = -angle;
			return angle + g_halfPi;
		}
		return static_cast<LegoFloat>(acos(p_y)) + g_halfPi;
	}

	if (p_y > 0.0f) {
		LegoFloat angle = static_cast<LegoFloat>(acos(p_x));
		return angle;
	}

	LegoFloat angle = static_cast<LegoFloat>(acos(p_x));
	return -angle;
}
