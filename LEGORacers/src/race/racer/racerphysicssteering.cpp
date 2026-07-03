#include "audio/spatialsoundinstance.h"
#include "race/racer/racerouterecord.h"
#include "race/racer/racersoundsource.h"
#include "race/racestate.h"

// GLOBAL: LEGORACERS 0x004b0d80
LegoU32 g_defaultPowerslideFactorBits = 0x3e4ccccd;

// GLOBAL: LEGORACERS 0x004b0d84
extern const LegoFloat g_wallMaxRiseSpeed = 0.30000001f;

// GLOBAL: LEGORACERS 0x004b0d88
extern const LegoFloat g_fallbackTurnRadius = 100.0f;

// GLOBAL: LEGORACERS 0x004b0d38
extern const LegoFloat g_skidSoundAlignmentMax = 0.89999998f;

// GLOBAL: LEGORACERS 0x004b0cd0
extern const LegoFloat g_minTurnRadius = 40.0f;

// GLOBAL: LEGORACERS 0x004b0cd4
extern const LegoFloat g_maxTurnRadius = 4096.0f;

// GLOBAL: LEGORACERS 0x004b0430
extern const LegoFloat g_unk0x004b0430 = 30.0f;

// GLOBAL: LEGORACERS 0x004b0434
extern const LegoFloat g_unk0x004b0434 = 300.0f;

extern const LegoFloat g_sweepCannonRadiansToTableIndex;
extern const LegoFloat g_physicsSoundMinDistance;
extern const LegoFloat g_physicsSoundMaxDistance;

// GLOBAL: LEGORACERS 0x004b046c
extern const LegoFloat g_powerslideMinSpeed = 0.050000001f;

// GLOBAL: LEGORACERS 0x004b0470
extern const LegoFloat g_steeringMaxSpeed = 0.155f;

// GLOBAL: LEGORACERS 0x004b0550
extern const LegoFloat g_powerslideAlignmentMin = 0.85000002f;

extern LegoFloat g_cosineTable[1024];

inline static LegoFloat GetCosineTableValue(LegoS32 p_index)
{
	return g_cosineTable[p_index];
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
		m_skidSound = m_soundSource->AcquireSoundById(0x3a);
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
