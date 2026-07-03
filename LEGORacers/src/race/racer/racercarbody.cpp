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

extern LegoFloat g_arcCosineTable[1024];
extern LegoU32 g_defaultPowerslideFactorBits;
extern const LegoFloat g_ghostSpeedScale;
extern const LegoFloat g_maxTurnRadius;
extern const LegoFloat g_minTurnRadius;
extern const LegoFloat g_physicsSoundMaxDistance;
extern const LegoFloat g_physicsSoundMinDistance;
extern const LegoFloat g_sweepCannonRadiansToTableIndex;
extern const LegoFloat g_twoPi;
extern const LegoFloat g_unk0x004b043c;
extern const LegoFloat g_wallMaxRiseSpeed;
extern const LegoS32 g_wheelDiagonalIndices[];
extern const LegoS32 g_wheelLengthwiseIndices[];
extern const LegoS32 g_wheelSidewaysIndices[];

// GLOBAL: LEGORACERS 0x004c6c04
RacerPhysics::SavedWheelStateBlock g_carBodySavedWheels;

// GLOBAL: LEGORACERS 0x004c6df0
RacerPhysics::SavedState g_carBodySavedState;

extern LegoFloat g_cosineTable[1024];

inline static LegoFloat GetCosineTableValue(LegoS32 p_index)
{
	return g_cosineTable[p_index];
}

// GLOBAL: LEGORACERS 0x004b0cd0
extern const LegoFloat g_minTurnRadius = 40.0f;

// GLOBAL: LEGORACERS 0x004b0cd4
extern const LegoFloat g_maxTurnRadius = 4096.0f;

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

// GLOBAL: LEGORACERS 0x004b0d38
extern const LegoFloat g_skidSoundAlignmentMax = 0.89999998f;

// GLOBAL: LEGORACERS 0x004b0d3c
extern const LegoFloat g_slideBankMaxAngle = 0.78539819f;

// GLOBAL: LEGORACERS 0x004b0d40
extern const LegoS32 g_wheelDiagonalIndices[] = {3, 2, 1, 0};

// GLOBAL: LEGORACERS 0x004b0d50
extern const LegoS32 g_wheelLengthwiseIndices[] = {2, 3, 0, 1};

// GLOBAL: LEGORACERS 0x004b0d60
extern const LegoS32 g_wheelSidewaysIndices[] = {1, 0, 3, 2};

// GLOBAL: LEGORACERS 0x004b0d80
LegoU32 g_defaultPowerslideFactorBits = 0x3e4ccccd;

// GLOBAL: LEGORACERS 0x004b0d84
extern const LegoFloat g_wallMaxRiseSpeed = 0.30000001f;

// GLOBAL: LEGORACERS 0x004b0d88
extern const LegoFloat g_fallbackTurnRadius = 100.0f;

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
	LegoU32 factorBits = g_defaultPowerslideFactorBits;
	m_spinOutMs = 0;
	m_powerslideFactorBits = factorBits;
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
	LegoU8 flags = static_cast<LegoU8>(m_flags);
	m_yawRate = 0.0f;
	m_gravityForce = baseForce;

	if (flags & c_flagSteering) {
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
		LegoFloat averageSupportThreshold = GetAverageSupportThreshold();
		LegoFloat averageFriction = GetAverageFriction();
		LegoFloat forceMagnitude = static_cast<LegoFloat>(sqrt(
			m_supportForce.m_z * m_supportForce.m_z + m_supportForce.m_y * m_supportForce.m_y +
			m_supportForce.m_x * m_supportForce.m_x
		));
		LegoFloat forceThreshold = m_gravity;
		forceThreshold *= m_massScale;
		forceThreshold *= averageSupportThreshold;
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
			scale *= averageFriction;
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

// FUNCTION: LEGORACERS 0x00445cb0
LegoFloat RacerPhysics::ComputeMinTurnRadius()
{
	LegoFloat scale = GetAverageLateralGrip();
	scale *= m_gravity * m_massScale;

	if (scale == 0.0f) {
		if (m_contactCount == 0) {
			return g_fallbackTurnRadius;
		}

		return g_maxTurnRadius;
	}

	LegoFloat value = m_forwardSpeed;
	LegoFloat valueSquared = value * value;
	return valueSquared * m_mass / scale;
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
		m_physicsEntity.SetUpDirection(forward, right);
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
				GolBoundingVolume* query = resource->GetBoundingVolume();
				query->SetMaterialTable(resource->GetMaterialTable());

				GolVec3 hitPoint;
				RaceEventRecord* hitRecord;
				if (query->IntersectSegment(
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
			GolBoundingVolume* query = baseResource->GetBoundingVolume();
			query->SetMaterialTable(baseResource->GetMaterialTable());

			RaceEventRecord* hitRecord;
			if (query->IntersectSegment(
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

			GolBoundingVolume* query = resource->GetBoundingVolume();
			query->SetMaterialTable(resource->GetMaterialTable());

			GolVec3 hitPoint;
			RaceEventRecord* hitRecord;
			if (!query->IntersectSegment(&start, &end, collisionContext, &hitPoint, &hitRecord, NULL)) {
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
				GolBoundingVolume* query = baseResource->GetBoundingVolume();
				query->SetMaterialTable(baseResource->GetMaterialTable());

				RaceEventRecord* hitRecord;
				if (!query->IntersectSegment(
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

// FUNCTION: LEGORACERS 0x00446ef0
void RacerPhysics::SetTurnRadius(LegoFloat p_turnRadius)
{
	if (p_turnRadius > 0.0f) {
		if (p_turnRadius < g_minTurnRadius) {
			m_turnRadius = g_minTurnRadius;
		}
		else if (p_turnRadius <= g_maxTurnRadius) {
			m_turnRadius = p_turnRadius;
		}
		else {
			m_turnRadius = 0.0f;
		}
	}
	else if (p_turnRadius < 0.0f) {
		if (p_turnRadius > -g_minTurnRadius) {
			m_turnRadius = -g_minTurnRadius;
		}
		else if (p_turnRadius >= -g_maxTurnRadius) {
			m_turnRadius = p_turnRadius;
		}
		else {
			m_turnRadius = 0.0f;
		}
	}
	else {
		m_turnRadius = 0.0f;
	}
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

				GolBoundingVolume* query = resource->GetBoundingVolume();
				query->SetMaterialTable(resource->GetMaterialTable());

				GolVec3 hitPoint;
				if (query->IntersectSegment(
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
				GolBoundingVolume* query = resource->GetBoundingVolume();
				query->SetMaterialTable(resource->GetMaterialTable());

				GolVec3 hitPoint;
				if (query->IntersectSegment(
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

// FUNCTION: LEGORACERS 0x00447f30
void RacerCarBody::StartSteering(LegoFloat p_gain, LegoFloat p_slipRatio, LegoFloat p_maxAngle)
{
	LegoU32 flags = m_flags;
	LegoFloat angle = p_maxAngle;
	m_steeringGain = p_gain;

	flags |= c_flagSteering;
	m_slipRatio = p_slipRatio;
	m_flags = flags;
	m_facingLagMax = p_maxAngle;
	m_steeringAlignmentMin =
		GetCosineTableValue(static_cast<LegoS32>(angle * g_sweepCannonRadiansToTableIndex) & 0x3ff);

	if (m_skidSound != NULL) {
		return;
	}

	GolVec3 direction;
	direction.m_x = m_physicsEntity.GetOrientation().m_rows[0].m_x;
	direction.m_y = m_physicsEntity.GetOrientation().m_rows[0].m_y;
	direction.m_z = m_physicsEntity.GetOrientation().m_rows[0].m_z;
	if ((flags & c_flagSliding) || m_wallContact) {
		return;
	}

	if (!(flags & c_flagPowerslide)) {
		LegoFloat dot = m_velocityDirection.m_z;
		dot *= direction.m_z;
		LegoFloat yDot = m_velocityDirection.m_y;
		yDot *= direction.m_y;
		dot += yDot;
		dot += m_velocityDirection.m_x * direction.m_x;
		if (dot >= g_skidSoundAlignmentMax) {
			return;
		}
	}

	if (m_soundsEnabled) {
		m_skidSound = m_soundSource->AcquireSoundById(c_soundSkid);
	}

	if (m_skidSound != NULL) {
		m_skidSound->SetDistanceRangeWithMinSquared(
			g_physicsSoundMinDistance * g_physicsSoundMinDistance,
			g_physicsSoundMaxDistance
		);
		m_skidSound->SetVolume(0.80000001f);
		m_skidSound->Play(TRUE);
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
			m_spinSound = m_soundSource->AcquireSoundById(c_soundSpin);
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

		m_physicsEntity.SetDirectionSide(direction0, direction1);
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

// FUNCTION: LEGORACERS 0x00448840
void RacerCarBody::ComputeSlideBankTarget()
{
	if (m_turnRadius > 0.0f) {
		LegoFloat value = m_turnRadius / g_maxTurnRadius;
		if (value > 1.0f) {
			value = 1.0f;
		}

		m_slideBankTarget = -(1.0f - value) * g_slideBankMaxAngle;
	}
	else if (m_turnRadius < 0.0f) {
		LegoFloat value = -m_turnRadius / g_maxTurnRadius;
		if (value > 1.0f) {
			value = 1.0f;
		}

		m_slideBankTarget = (1.0f - value) * g_slideBankMaxAngle;
	}
	else {
		m_slideBankTarget = 0.0f;
	}
}

// FUNCTION: LEGORACERS 0x004488e0
LegoU32 RacerCarBody::AddCollisionWorld(GolBoundedEntity* p_world)
{
	LegoU32 result = m_collisionWorldCount;
	LegoU32 i = 0;
	for (; i < result; i++) {
		if (m_collisionWorlds[i] == p_world) {
			return result;
		}
	}

	if (result < sizeOfArray(m_collisionWorlds)) {
		m_collisionWorlds[result] = p_world;
		result = m_collisionWorldCount + 1;
		m_collisionWorldCount = result;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00448930
void RacerCarBody::RemoveCollisionWorld(GolBoundedEntity* p_world)
{
	LegoU32 count = m_collisionWorldCount;
	LegoU32 index = 0;
	if (count > 0) {
		for (; index < count; index++) {
			if (m_collisionWorlds[index] == p_world) {
				LegoU32 nextIndex = index + 1;
				if (nextIndex < count) {
					GolBoundedEntity** entry = &m_collisionWorlds[nextIndex - 1];
					do {
						nextIndex++;
						*entry = entry[1];
						entry++;
					} while (nextIndex < m_collisionWorldCount);
				}

				m_collisionWorldCount--;
				return;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00448990
LegoFloat RacerCarBody::GetAverageSupportThreshold()
{
	LegoFloat result = 0.0f;
	WheelProbe* entry = m_wheelProbes;
	while (entry < &m_wheelProbes[sizeOfArray(m_wheelProbes)]) {
		result += entry->m_supportThreshold;
		entry++;
	}

	return result * 0.25f;
}

// FUNCTION: LEGORACERS 0x004489c0
LegoFloat RacerCarBody::GetAverageFriction()
{
	LegoFloat result = 0.0f;
	WheelProbe* entry = m_wheelProbes;
	while (entry < &m_wheelProbes[sizeOfArray(m_wheelProbes)]) {
		result += entry->m_friction;
		entry++;
	}

	return result * 0.25f;
}

// FUNCTION: LEGORACERS 0x004489f0
LegoFloat RacerPhysics::GetAverageLateralGrip()
{
	LegoFloat total = 0.0f;
	LegoS32 count = 0;

	for (WheelProbe* entry = m_wheelProbes; entry < &m_wheelProbes[4]; entry++) {
		if (entry->m_flags & WheelProbe::c_flagContact) {
			total += entry->m_lateralGrip;
			count++;
		}
	}

	if (count) {
		LegoFloat countFloat = static_cast<LegoFloat>(count);
		return total / countFloat * m_gripScale;
	}

	return 0.0f;
}

// FUNCTION: LEGORACERS 0x00448a50
void RacerCarBody::AgePlaneCache()
{
	CollisionCacheRecord* entry = m_planeCache;
	CollisionCacheRecord* end = &m_planeCache[sizeOfArray(m_planeCache)];
	while (entry < end) {
		entry->m_age++;
		entry++;
	}
}

// FUNCTION: LEGORACERS 0x00448a70
RacerPhysics::CollisionCacheRecord* RacerCarBody::CachePlane(
	GolBoundingVolume::HitTriangle* p_plane,
	RaceEventRecord* p_record
)
{
	CollisionCacheRecord* result;
	LegoU32 count = m_planeCacheCount;
	if (count < sizeOfArray(m_planeCache)) {
		result = &m_planeCache[count];
		m_planeCacheCount = count + 1;
	}
	else {
		CollisionCacheRecord* entry = m_planeCache;
		CollisionCacheRecord* end = &m_planeCache[sizeOfArray(m_planeCache)];
		LegoU32 age = 0;
		result = entry;
		while (entry < end) {
			if (age < entry->m_age) {
				result = entry;
				age = entry->m_age;
			}

			entry++;
		}
	}

	result->m_plane = *p_plane;
	result->m_record = p_record;
	result->m_age = 0;

	return result;
}

// FUNCTION: LEGORACERS 0x00448ae0
LegoBool32 RacerCarBody::TestCachedPlanes(WheelProbe* p_probe)
{
	if (p_probe->m_cachedPlane != NULL) {
		if (TestCachedPlane(p_probe, p_probe->m_cachedPlane)) {
			p_probe->m_cachedPlane->m_age = 0;
			p_probe->m_hitRecord = p_probe->m_cachedPlane->m_record;

			return TRUE;
		}
	}

	CollisionCacheRecord* entry = m_planeCache;
	CollisionCacheRecord* end = &m_planeCache[m_planeCacheCount];
	while (entry < end) {
		if (p_probe->m_cachedPlane != entry && TestCachedPlane(p_probe, entry)) {
			p_probe->m_cachedPlane = entry;
			p_probe->m_hitRecord = entry->m_record;
			entry->m_age = 0;

			return TRUE;
		}

		entry++;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00448b80
LegoBool32 RacerCarBody::TestCachedPlane(WheelProbe* p_probe, CollisionCacheRecord* p_record)
{
	GolVec3 scaled;
	LegoFloat start = p_record->m_plane.m_normal.m_z * p_probe->m_rayStart.m_z;
	start += p_record->m_plane.m_normal.m_y * p_probe->m_rayStart.m_y;
	start += p_probe->m_rayStart.m_x * p_record->m_plane.m_normal.m_x;
	start += p_record->m_plane.m_planeDistance;
	LegoFloat end = p_record->m_plane.m_normal.m_z * p_probe->m_rayEnd.m_z;
	end += p_probe->m_rayEnd.m_y * p_record->m_plane.m_normal.m_y;
	end += p_probe->m_rayEnd.m_x * p_record->m_plane.m_normal.m_x;
	end += p_record->m_plane.m_planeDistance;

	LegoBool32 startNonNegative = start >= 0.0f;
	LegoBool32 endNonNegative = end >= 0.0f;
	if (startNonNegative == endNonNegative) {
		return FALSE;
	}

	if (startNonNegative) {
		end = -end;
	}
	else {
		start = -start;
	}

	GolVec3* point = &p_probe->m_hitPoint;
	point->m_x = p_probe->m_rayEnd.m_x - p_probe->m_rayStart.m_x;
	point->m_y = p_probe->m_rayEnd.m_y - p_probe->m_rayStart.m_y;
	point->m_z = p_probe->m_rayEnd.m_z - p_probe->m_rayStart.m_z;

	LegoFloat amount = start / (start + end);
	scaled.m_x = amount * point->m_x;
	scaled.m_y = point->m_y;
	scaled.m_y *= amount;
	scaled.m_z = amount;
	scaled.m_z *= p_probe->m_hitPoint.m_z;

	point->m_x = scaled.m_x + p_probe->m_rayStart.m_x;
	point->m_y = scaled.m_y + p_probe->m_rayStart.m_y;
	point->m_z = scaled.m_z + p_probe->m_rayStart.m_z;

	return GolMath::PointInTriangle(point, p_record->m_plane.GetFloatData());
}

// FUNCTION: LEGORACERS 0x00448c70
void RacerCarBody::ComputeWheelPositions()
{
	GolOrientedEntity* entity = &m_physicsEntity;
	WheelProbe* points = m_wheelProbes;
	GolVec3* anchor = &points[1].m_wheelPosition;
	entity->LocalToWorld(m_anchorWheelOffset, anchor);

	GolVec3 lengthOffset;
	entity->GetOrientationRow0(&lengthOffset);
	LegoFloat lengthScale = m_wheelbase;
	LegoFloat lengthY = lengthOffset.m_y;
	lengthOffset.m_x *= lengthScale;
	lengthOffset.m_y = lengthY * lengthScale;
	lengthOffset.m_z *= lengthScale;

	GolVec3 widthOffset;
	entity->GetOrientationRow1(&widthOffset);
	LegoFloat widthScale = m_trackWidth;
	LegoFloat widthY = widthOffset.m_y;
	widthOffset.m_x *= widthScale;
	widthOffset.m_y = widthY * widthScale;
	widthOffset.m_z *= widthScale;

	points[0].m_wheelPosition.m_x = anchor->m_x - widthOffset.m_x;
	points[0].m_wheelPosition.m_y = anchor->m_y - widthOffset.m_y;
	points[0].m_wheelPosition.m_z = anchor->m_z - widthOffset.m_z;

	points[3].m_wheelPosition.m_x = anchor->m_x - lengthOffset.m_x;
	points[3].m_wheelPosition.m_y = anchor->m_y - lengthOffset.m_y;
	points[3].m_wheelPosition.m_z = anchor->m_z - lengthOffset.m_z;

	points[2].m_wheelPosition.m_x = points[0].m_wheelPosition.m_x - lengthOffset.m_x;
	points[2].m_wheelPosition.m_y = points[0].m_wheelPosition.m_y - lengthOffset.m_y;
	points[2].m_wheelPosition.m_z = points[0].m_wheelPosition.m_z - lengthOffset.m_z;
}

// STUB: LEGORACERS 0x00448d90
void RacerCarBody::ComputeWheelRaysLocal(GolBoundedEntity* p_world, LegoFloat p_sweepHeight, LegoFloat p_sweepDistance)
{
	const GolMatrix3& resourceOrientation = p_world->GetOrientation();
	GolVec3 zHeight;
	zHeight.m_x = resourceOrientation.m_m[0][2] * p_sweepDistance;
	zHeight.m_y = resourceOrientation.m_m[1][2] * p_sweepDistance;
	zHeight.m_z = resourceOrientation.m_m[2][2] * p_sweepDistance;

	GolVec3 zDistance;
	zDistance.m_x = resourceOrientation.m_m[0][2] * p_sweepHeight;
	zDistance.m_y = resourceOrientation.m_m[1][2] * p_sweepHeight;
	zDistance.m_z = resourceOrientation.m_m[2][2] * p_sweepHeight;

	WheelProbe* entries = m_wheelProbes;

	GolVec3 center;
	p_world->WorldToLocal(entries[1].m_wheelPosition, &center);

	entries[1].m_rayStart.m_x = center.m_x + zHeight.m_x;
	entries[1].m_rayStart.m_y = center.m_y + zHeight.m_y;
	entries[1].m_rayStart.m_z = center.m_z + zHeight.m_z;
	entries[1].m_rayEnd.m_x = center.m_x - zDistance.m_x;
	entries[1].m_rayEnd.m_y = center.m_y - zDistance.m_y;
	entries[1].m_rayEnd.m_z = center.m_z - zDistance.m_z;

	GolVec3 row0;
	row0.m_x = m_physicsEntity.GetOrientation().m_m[0][0];
	row0.m_y = m_physicsEntity.GetOrientation().m_m[0][1];
	row0.m_z = m_physicsEntity.GetOrientation().m_m[0][2];

	GolVec3 row1;
	row1.m_x = m_physicsEntity.GetOrientation().m_m[1][0];
	row1.m_y = m_physicsEntity.GetOrientation().m_m[1][1];
	row1.m_z = m_physicsEntity.GetOrientation().m_m[1][2];

	GolVec3 localRow0;
	p_world->RotateToLocal(row0, &localRow0);

	GolVec3 localRow1;
	p_world->RotateToLocal(row1, &localRow1);

	localRow0.m_x *= m_wheelbase;
	localRow0.m_y *= m_wheelbase;
	localRow0.m_z *= m_wheelbase;
	localRow1.m_x *= m_trackWidth;
	localRow1.m_y *= m_trackWidth;
	localRow1.m_z *= m_trackWidth;

	GolVec3 corner;
	corner.m_x = center.m_x - localRow1.m_x;
	corner.m_y = center.m_y - localRow1.m_y;
	corner.m_z = center.m_z - localRow1.m_z;

	entries[0].m_rayStart.m_x = corner.m_x + zHeight.m_x;
	entries[0].m_rayStart.m_y = corner.m_y + zHeight.m_y;
	entries[0].m_rayStart.m_z = corner.m_z + zHeight.m_z;
	entries[0].m_rayEnd.m_x = corner.m_x - zDistance.m_x;
	entries[0].m_rayEnd.m_y = corner.m_y - zDistance.m_y;
	entries[0].m_rayEnd.m_z = corner.m_z - zDistance.m_z;

	GolVec3 corner2;
	corner2.m_x = center.m_x - localRow0.m_x;
	corner2.m_y = center.m_y - localRow0.m_y;
	corner2.m_z = center.m_z - localRow0.m_z;

	entries[3].m_rayStart.m_x = corner2.m_x + zHeight.m_x;
	entries[3].m_rayStart.m_y = corner2.m_y + zHeight.m_y;
	entries[3].m_rayStart.m_z = corner2.m_z + zHeight.m_z;
	GolCameraBase::Subtract(&corner2, &zDistance, &entries[3].m_rayEnd);

	GolCameraBase::Subtract(&corner, &localRow0, &corner2);
	GolCameraBase::Add(&corner2, &zHeight, &entries[2].m_rayStart);
	GolCameraBase::Subtract(&corner2, &zDistance, &entries[2].m_rayEnd);
}
// FUNCTION: LEGORACERS 0x00449060
GolOrientedEntity* RacerCarBody::GetEntity()
{
	return m_carEntity;
}

// FUNCTION: LEGORACERS 0x00449070
undefined4 RacerPhysics::StartPowerslide(undefined4 p_factorBits)
{
	LegoU32 flags = m_flags;
	flags |= c_flagPowerslide;
	m_flags = flags;

	m_powerslideFactorBits = p_factorBits;
	return p_factorBits;
}

// FUNCTION: LEGORACERS 0x00449090
undefined4 RacerPhysics::EndPowerslide()
{
	LegoU32 flags = m_flags;
	flags &= ~c_flagPowerslide;
	m_flags = flags;

	LegoU32 value = g_defaultPowerslideFactorBits;
	m_powerslideFactorBits = value;
	return value;
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
