#include "decomp.h"
#include "golmath.h"
#include "race/racesession.h"

DECOMP_SIZE_ASSERT(RaceSession::Field0x6dc::Field0xf8, 0xf8)

extern const LegoFloat g_unk0x004afde0;

// GLOBAL: LEGORACERS 0x004b0170
extern const LegoFloat g_raceSessionField0xf8CollisionStartOffset = 5.0f;

// GLOBAL: LEGORACERS 0x004b0238
const LegoFloat g_raceSessionField0xf8CollisionHitLift = 6.0f;

// GLOBAL: LEGORACERS 0x004b0240
const LegoFloat g_raceSessionField0xf8OscillationGrowth = 6.0f;

// GLOBAL: LEGORACERS 0x004b0244
const LegoFloat g_raceSessionField0xf8PathDistanceLimitSquared = 90000.0f;

// GLOBAL: LEGORACERS 0x004b0268
const LegoFloat g_raceSessionField0xf8CollisionProbeDepth = 50.0f;

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
RaceSession::Field0x6dc::Field0xa8* RaceSession::Field0x6dc::Field0xf8::VTable0x10(undefined4 p_flags)
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
	Field0xa8::~Field0xa8();
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

	RaceState::Racer* target = m_unk0x0a0;
	if (target == NULL || m_unk0x0f0 > c_targetRefreshMs || (target->m_unk0x3e8.m_flags0x6c0 & c_racerFlags0xaa8Bit7) ||
		(target->m_unk0xd04 & c_racerFlags0xd04InvalidTargetMask)) {
		m_unk0x0f0 = 0;
		target = p_unk0x08->FUN_0043c6e0(&m_unk0x0a8, &m_unk0x0d0, p_unk0x0c, p_unk0x10, p_unk0x14);
		m_unk0x0a0 = target;

		while (target != NULL) {
			if (target != m_unk0x09c && !(target->m_unk0x3e8.m_flags0x6c0 & c_racerFlags0xaa8Bit7) &&
				!(target->m_unk0xd04 & c_racerFlags0xd04InvalidTargetMask)) {
				break;
			}

			target = p_unk0x08->FUN_0043c7f0(target, &m_unk0x0a8, &m_unk0x0d0, p_unk0x0c, p_unk0x10, p_unk0x14);
			m_unk0x0a0 = target;
		}
	}

	if (!m_unk0x0e8 && m_unk0x0ec != NULL) {
		RaceState::Racer::Field0xcc4* pathField = m_unk0x0ec;
		GolVec3 point = pathField->m_unk0x10;
		for (;;) {
			GolVec3 delta = point - m_unk0x0a8;
			if (GOLVECTOR3_DOT(delta, m_unk0x0d0) > 0.0f &&
				GOLVECTOR3_DOT(pathField->m_unk0x00, m_unk0x0a8) + pathField->m_unk0x0c >= g_unk0x004afde0) {
				break;
			}

			pathField = m_unk0x09c->m_unk0x010->FUN_0041e940(pathField->m_unk0x20[0]);
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

// STUB: LEGORACERS 0x00423980
void RaceSession::Field0x6dc::Field0xf8::FUN_00423980()
{
	STUB(0x00423980);

	m_unk0x008->VTable0x04(&m_unk0x0a8);
	m_unk0x0b4 = 0.0f;
	m_unk0x0e8 = 0;
	m_unk0x0f0 = 0;
	m_unk0x0ec = NULL;
}

// STUB: LEGORACERS 0x00423a20
LegoS32 RaceSession::Field0x6dc::Field0xf8::VTable0x18(LegoU32 p_elapsedMs)
{
	STUB(0x00423a20);

	return Field0xa8::VTable0x18(p_elapsedMs);
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
