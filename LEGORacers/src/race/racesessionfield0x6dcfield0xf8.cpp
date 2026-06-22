#include "decomp.h"
#include "golmath.h"
#include "race/racesession.h"

#include <float.h>
#include <math.h>

DECOMP_SIZE_ASSERT(RaceSession::Field0x6dc::Field0xf8, 0xf8)

extern const LegoFloat g_unk0x004afde0;

// GLOBAL: LEGORACERS 0x004b0170
extern const LegoFloat g_raceSessionField0xf8CollisionStartOffset = 5.0f;

// GLOBAL: LEGORACERS 0x004b0224
extern const LegoFloat g_raceSessionField0xf8TargetHeightOffset = 5.0f;

// GLOBAL: LEGORACERS 0x004b022c
extern const LegoFloat g_raceSessionField0xf8TargetSnapDistanceSquared = 3600.0f;

// GLOBAL: LEGORACERS 0x004b0230
extern const LegoFloat g_raceSessionField0xf8TargetDirectHitDistanceSquared = 9.0f;

// GLOBAL: LEGORACERS 0x004b0234
extern const LegoFloat g_raceSessionField0xf8GroundProbeStartOffset = 2.0f;

// GLOBAL: LEGORACERS 0x004b0238
const LegoFloat g_raceSessionField0xf8CollisionHitLift = 6.0f;

// GLOBAL: LEGORACERS 0x004b023c
extern const LegoFloat g_raceSessionField0xf8DescentRate = 6.0f;

// GLOBAL: LEGORACERS 0x004b0240
const LegoFloat g_raceSessionField0xf8OscillationGrowth = 6.0f;

// GLOBAL: LEGORACERS 0x004b0244
const LegoFloat g_raceSessionField0xf8PathDistanceLimitSquared = 90000.0f;

// GLOBAL: LEGORACERS 0x004b0268
extern const LegoFloat g_raceSessionField0xf8CollisionProbeDepth = 50.0f;

// FUNCTION: LEGORACERS 0x00423590
RaceSession::Field0x6dc::Field0xf8::Field0xf8()
{
	m_unk0x0c4.m_x = 0.0f;
	m_unk0x0c4.m_y = 0.0f;
	m_unk0x0c4.m_z = 0.0f;
	m_unk0x0d0.m_y = 0.0f;
	m_unk0x0d0.m_z = 0.0f;
	m_unk0x0a8.m_x = 0.0f;
	m_unk0x0a8.m_y = 0.0f;
	m_unk0x0a8.m_z = 0.0f;
	m_unk0x0b4 = 0;
	m_unk0x0b8 = 0;
	m_unk0x0bc = 0;
	m_unk0x0c0 = 0;
	m_unk0x0e8 = 0;
	m_unk0x0ec = 0;
	m_unk0x0f0 = 0;
	m_unk0x0d0.m_x = 1.0f;
}

// FUNCTION: LEGORACERS 0x00423610
RaceSessionField0x6dcField0xa8* RaceSession::Field0x6dc::Field0xf8::VTable0x10(undefined4 p_flags)
{
	Field0xf8* result = this;
	FUN_00423630();
	if (p_flags & 1) {
		::operator delete(result);
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00423630
void RaceSession::Field0x6dc::Field0xf8::FUN_00423630()
{
	RaceSessionField0x6dcField0xa8::~RaceSessionField0x6dcField0xa8();
}

// STUB: LEGORACERS 0x00423640
void RaceSession::Field0x6dc::Field0xf8::FUN_00423640(
	LegoU32 p_elapsedMs,
	RaceState::Racer::Field0x00c* p_unk0x08,
	LegoFloat p_unk0x0c,
	LegoFloat p_unk0x10,
	LegoFloat p_unk0x14
)
{
	m_unk0x0f0 += p_elapsedMs;

	RaceState::Racer* noTarget = NULL;
	RaceState::Racer* target = m_unk0x0a0;
	if (target == noTarget || m_unk0x0f0 > c_targetRefreshMs ||
		(target->m_unk0x3e8.m_flags0x6c0 & c_racerFlags0xaa8Bit7) ||
		(target->m_unk0xd04 & c_racerFlags0xd04InvalidTargetMask)) {
		m_unk0x0f0 = 0;
		target = p_unk0x08->FUN_0043c6e0(&m_unk0x0a8, &m_unk0x0d0, p_unk0x0c, p_unk0x10, p_unk0x14);
		m_unk0x0a0 = target;

		while (target != noTarget) {
			if (target != m_unk0x09c && !(target->m_unk0x3e8.m_flags0x6c0 & c_racerFlags0xaa8Bit7) &&
				!(target->m_unk0xd04 & c_racerFlags0xd04InvalidTargetMask)) {
				break;
			}

			target = p_unk0x08->FUN_0043c7f0(target, &m_unk0x0a8, &m_unk0x0d0, p_unk0x0c, p_unk0x10, p_unk0x14);
			m_unk0x0a0 = target;
		}
	}

	if (!m_unk0x0e8 && m_unk0x0ec != NULL) {
		RaceSessionField0x27f4::Entry* pathField = m_unk0x0ec;
		GolVec3 point = pathField->m_unk0x10;
		for (;;) {
			GolVec3 delta = point - m_unk0x0a8;
			if (GOLVECTOR3_DOT(delta, m_unk0x0d0) > 0.0f &&
				GOLVECTOR3_DOT(pathField->m_unk0x00, m_unk0x0a8) + pathField->m_unk0x0c >= g_unk0x004afde0) {
				break;
			}

			pathField = m_unk0x09c->m_unk0x010->FUN_0041e940(pathField->m_unk0x20.m_items[0]);
			m_unk0x0ec = pathField;
			if (pathField != NULL) {
				point = pathField->m_unk0x10;
				delta = point - m_unk0x0a8;
				if (GOLVECTOR3_DOT(delta, delta) > g_raceSessionField0xf8PathDistanceLimitSquared ||
					GOLVECTOR3_DOT(pathField->m_unk0x00, m_unk0x0d0) > 0.0f) {
					m_unk0x0ec = NULL;
				}
			}

			if (m_unk0x0ec == NULL) {
				break;
			}
		}

		if (m_unk0x0ec != NULL) {
			GolVec3 hit = point;
			GolVec3 start = point;
			GolVec3 end = point;
			start.m_z += g_raceSessionField0xf8CollisionStartOffset;
			end.m_z -= g_raceSessionField0xf8CollisionProbeDepth;

			RaceSessionField0x32b4::Field0x0c record;
			if (m_unk0x00c->FUN_0041f730(&start, &end, &record, &hit)) {
				m_unk0x0e8 = 1;
				m_unk0x0dc.m_x = hit.m_x;
				m_unk0x0dc.m_y = hit.m_y;
				m_unk0x0dc.m_z = hit.m_z + g_raceSessionField0xf8CollisionHitLift;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00423980
void RaceSession::Field0x6dc::Field0xf8::FUN_00423980()
{
	m_unk0x008->VTable0x04(&m_unk0x0a8);
	m_unk0x0b4 = 0.0f;
	m_unk0x0e8 = 0;
	m_unk0x0f0 = 0;

	GolVec3 forward;
	GolVec3* direction = &m_unk0x0d0;
	m_unk0x008->VTable0x48(direction, &forward);
	m_unk0x0f0 = 0;

	RaceState::Racer* racer = m_unk0x09c;
	if (racer != NULL) {
		RaceSessionField0x27f4::Entry* pathField = racer->m_unk0xcc4;
		m_unk0x0ec = pathField;
		if (pathField != NULL) {
			forward.m_x = pathField->m_unk0x00.m_x;
			forward.m_y = pathField->m_unk0x00.m_y;
			LegoFloat dot = direction->m_z;
			dot *= pathField->m_unk0x00.m_z;
			LegoFloat yDot = direction->m_y;
			yDot *= forward.m_y;
			dot += yDot;
			dot += forward.m_x * direction->m_x;
			if (dot > 0.0f) {
				m_unk0x0ec = NULL;
			}
		}
	}
	else {
		m_unk0x0ec = NULL;
	}
}

// STUB: LEGORACERS 0x00423a20
LegoS32 RaceSession::Field0x6dc::Field0xf8::VTable0x18(LegoU32 p_elapsedMs)
{
	LegoU32 state = m_unk0x004;
	if (state != 1) {
		return state;
	}

	m_unk0x050 += p_elapsedMs;
	if (static_cast<LegoU32>(m_unk0x050) >= m_unk0x058) {
		m_unk0x004 = 4;
		m_unk0x008->VTable0x04(&m_unk0x028);
		return 4;
	}

	LegoFloat elapsedSeconds = static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs)) * 0.001f;
	LegoFloat targetDistanceSquared;
	GolVec3 nextPosition;
	GolVec3 previousPosition;
	GolVec3 start;
	GolVec3 end;
	RaceSessionField0x32b4::Field0x0c record;

	RaceState::Racer* target = m_unk0x0a0;
	if (target != NULL) {
		target->m_unk0x018.m_unk0x044->VTable0x04(&m_unk0x01c);
		m_unk0x01c.m_z += g_raceSessionField0xf8TargetHeightOffset;
		m_unk0x0d0.m_x = m_unk0x01c.m_x - m_unk0x0a8.m_x;
		m_unk0x0d0.m_y = m_unk0x01c.m_y - m_unk0x0a8.m_y;
		m_unk0x0d0.m_z = m_unk0x01c.m_z - m_unk0x0a8.m_z;
		targetDistanceSquared = m_unk0x0d0.m_z * m_unk0x0d0.m_z;
		targetDistanceSquared += m_unk0x0d0.m_y * m_unk0x0d0.m_y;
		targetDistanceSquared += m_unk0x0d0.m_x * m_unk0x0d0.m_x;
	}
	else {
		targetDistanceSquared = FLT_MAX;
	}

	GolVec3* direction = &m_unk0x0d0;
	if (targetDistanceSquared < g_raceSessionField0xf8TargetSnapDistanceSquared) {
		GolMath::NormalizeVector3(*direction, direction);

		LegoFloat speed =
			static_cast<LegoFloat>(sqrt(m_unk0x03c * m_unk0x03c + m_unk0x038 * m_unk0x038 + m_unk0x034 * m_unk0x034));
		m_unk0x0c4.m_x = speed * direction->m_x;
		m_unk0x0c4.m_y = speed * direction->m_y;
		m_unk0x0c4.m_z = speed * direction->m_z;

		if (targetDistanceSquared < g_raceSessionField0xf8TargetDirectHitDistanceSquared) {
			m_unk0x028 = m_unk0x01c;
			m_unk0x008->VTable0x08(m_unk0x028);
			m_unk0x004 = 4;
			return 4;
		}

		nextPosition.m_x = m_unk0x0a8.m_x + m_unk0x0c4.m_x * elapsedSeconds;
		nextPosition.m_y = m_unk0x0a8.m_y + m_unk0x0c4.m_y * elapsedSeconds;
		nextPosition.m_z = m_unk0x0a8.m_z + m_unk0x0c4.m_z * elapsedSeconds;

		targetDistanceSquared = (m_unk0x01c.m_z - nextPosition.m_z) * direction->m_z;
		targetDistanceSquared += (m_unk0x01c.m_y - nextPosition.m_y) * direction->m_y;
		targetDistanceSquared += (m_unk0x01c.m_x - nextPosition.m_x) * direction->m_x;
		if (targetDistanceSquared <= 0.0f) {
			m_unk0x028 = m_unk0x01c;
			m_unk0x008->VTable0x08(m_unk0x028);
			m_unk0x004 = 4;
			return 4;
		}
	}
	else {
		if (m_unk0x0e8) {
			end.m_x = m_unk0x0dc.m_x - m_unk0x0a8.m_x;
			end.m_y = m_unk0x0dc.m_y - m_unk0x0a8.m_y;
			end.m_z = m_unk0x0dc.m_z - m_unk0x0a8.m_z;
			if (GOLVECTOR3_DOT(end, m_unk0x0d0) > 0.0f) {
				m_unk0x0d0.m_x = end.m_x;
				m_unk0x0d0.m_y = end.m_y;
				m_unk0x0d0.m_z = end.m_z;
			}
			else {
				m_unk0x0e8 = 0;
			}
		}

		GolMath::NormalizeVector3(*direction, direction);
		m_unk0x0c4.m_x = m_unk0x04c * direction->m_x;
		m_unk0x0c4.m_y = m_unk0x04c * direction->m_y;
		m_unk0x0c4.m_z = m_unk0x04c * direction->m_z;
		nextPosition.m_x = m_unk0x0a8.m_x + m_unk0x0c4.m_x * elapsedSeconds;
		nextPosition.m_y = m_unk0x0a8.m_y + m_unk0x0c4.m_y * elapsedSeconds;
		nextPosition.m_z = m_unk0x0a8.m_z + m_unk0x0c4.m_z * elapsedSeconds;

		start.m_x = nextPosition.m_x;
		start.m_y = nextPosition.m_y;
		start.m_z = nextPosition.m_z;
		end.m_x = nextPosition.m_x;
		end.m_y = nextPosition.m_y;
		end.m_z = nextPosition.m_z;
		start.m_z += g_raceSessionField0xf8GroundProbeStartOffset;
		end.m_z -= g_raceSessionField0xf8CollisionHitLift;

		if (m_unk0x00c->FUN_0041f730(&start, &end, &record, &m_unk0x028)) {
			nextPosition.m_z = m_unk0x028.m_z + g_raceSessionField0xf8CollisionHitLift;
			if (m_unk0x0a8.m_z > nextPosition.m_z) {
				LegoFloat descentLimit = m_unk0x0a8.m_z - g_raceSessionField0xf8DescentRate * elapsedSeconds;
				if (descentLimit > nextPosition.m_z) {
					nextPosition.m_z = descentLimit;
				}
			}
		}
	}

	m_unk0x0a8 = nextPosition;
	FUN_00423ed0(elapsedSeconds, direction, &nextPosition);

	m_unk0x008->VTable0x04(&previousPosition);

	if (m_unk0x00c->FUN_0041f730(&previousPosition, &nextPosition, &record, &m_unk0x028)) {
		m_unk0x05c.m_x = record.m_unk0x24.m_x;
		m_unk0x05c.m_y = record.m_unk0x24.m_y;
		m_unk0x05c.m_z = record.m_unk0x24.m_z;
		m_unk0x008->VTable0x08(m_unk0x028);
		m_unk0x004 = 3;
		return 3;
	}

	m_unk0x008->VTable0x08(nextPosition);
	return 1;
}

// FUNCTION: LEGORACERS 0x00423ea0
void RaceSession::Field0x6dc::Field0xf8::VTable0x1c(GolVec3* p_unk0x04)
{
	p_unk0x04->m_x = m_unk0x0c4.m_x;
	p_unk0x04->m_y = m_unk0x0c4.m_y;
	p_unk0x04->m_z = m_unk0x0c4.m_z;
}

// FUNCTION: LEGORACERS 0x00423ed0
void RaceSession::Field0x6dc::Field0xf8::FUN_00423ed0(
	LegoFloat p_elapsedSeconds,
	GolVec3* p_unk0x08,
	GolVec3* p_unk0x0c
)
{
	m_unk0x0b4 += g_raceSessionField0xf8OscillationGrowth * p_elapsedSeconds;
	if (m_unk0x0b8 <= m_unk0x0b4) {
		m_unk0x0b4 = m_unk0x0b8;
	}

	LegoFloat cosine;
	LegoFloat angleDelta = m_unk0x0c0;
	angleDelta *= p_elapsedSeconds;
	p_elapsedSeconds = m_unk0x0bc + angleDelta;
	m_unk0x0bc = p_elapsedSeconds;
	GolMath::FUN_00449170(p_elapsedSeconds, &p_elapsedSeconds, &cosine);

	LegoFloat xSine = p_elapsedSeconds * p_unk0x08->m_x;
	LegoFloat ySine = p_unk0x08->m_y;
	ySine *= p_elapsedSeconds;
	LegoFloat oneMinusCosine = 1.0f - cosine;
	LegoFloat zY = p_unk0x08->m_z * p_unk0x08->m_y * oneMinusCosine;
	p_unk0x0c->m_x += ((p_unk0x08->m_z * p_unk0x08->m_x * oneMinusCosine) - ySine) * m_unk0x0b4;
	p_unk0x0c->m_y += (zY + xSine) * m_unk0x0b4;
	p_unk0x0c->m_z += ((p_unk0x08->m_z * p_unk0x08->m_z * oneMinusCosine) + cosine) * m_unk0x0b4;
}
