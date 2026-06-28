#include "audio/spatialsoundinstance.h"
#include "golconstants.h"
#include "golmath.h"
#include "race/raceeventtable0x90.h"
#include "race/raceforcefeedback.h"
#include "race/racesessionfield0x32b4.h"
#include "race/racestate.h"

#include <float.h>
#include <math.h>
#include <string.h>

extern LegoFloat g_arcCosineTable[1024];
extern const LegoS32 g_raceStateField0x3e8MirrorEntryIndices[];
extern const LegoS32 g_raceStateField0x3e8ContactEntryIndices0x4b0d50[];
extern const LegoS32 g_raceStateField0x3e8ContactEntryIndices0x4b0d60[];

// GLOBAL: LEGORACERS 0x004b0448
extern const LegoFloat g_unk0x004b0448 = 120.0f;

// GLOBAL: LEGORACERS 0x004b0450
extern const LegoFloat g_unk0x004b0450 = 176.0f;

// GLOBAL: LEGORACERS 0x004b0454
extern const LegoFloat g_unk0x004b0454 = 0.04f;

// GLOBAL: LEGORACERS 0x004b0438
extern const LegoFloat g_unk0x004b0438 = 1.0f;

// GLOBAL: LEGORACERS 0x004b043c
extern const LegoFloat g_unk0x004b043c = 0.5f;

// GLOBAL: LEGORACERS 0x004b0440
extern const LegoFloat g_unk0x004b0440 = 2.0f;

// GLOBAL: LEGORACERS 0x004b0458
extern const LegoFloat g_unk0x004b0458 = 3.0f;

// GLOBAL: LEGORACERS 0x004b045c
extern const LegoFloat g_unk0x004b045c = 1.0f;

// GLOBAL: LEGORACERS 0x004b0460
extern const LegoFloat g_unk0x004b0460 = 0.5f;

// GLOBAL: LEGORACERS 0x004b0464
extern const LegoFloat g_unk0x004b0464 = 0.25f;

// GLOBAL: LEGORACERS 0x004b0468
extern const LegoFloat g_unk0x004b0468 = 0.008f;

// GLOBAL: LEGORACERS 0x004b0474
extern const LegoFloat g_unk0x004b0474 = 0.0089999996f;

// GLOBAL: LEGORACERS 0x004b0478
extern const LegoFloat g_unk0x004b0478 = 0.22f;

// GLOBAL: LEGORACERS 0x004b047c
extern const LegoFloat g_unk0x004b047c = 280.0f;

// GLOBAL: LEGORACERS 0x004b0484
extern const LegoFloat g_unk0x004b0484 = 300.0f;

// GLOBAL: LEGORACERS 0x004b0488
extern const LegoFloat g_unk0x004b0488 = 0.1f;

// GLOBAL: LEGORACERS 0x004b048c
extern const LegoFloat g_unk0x004b048c = -0.1f;

// GLOBAL: LEGORACERS 0x004b0490
extern const LegoFloat g_unk0x004b0490 = 0.3f;

// GLOBAL: LEGORACERS 0x004b0494
extern const LegoFloat g_unk0x004b0494 = 1.7f;

// GLOBAL: LEGORACERS 0x004b0498
extern const LegoFloat g_unk0x004b0498 = 4.5f;

// GLOBAL: LEGORACERS 0x004b049c
extern const LegoFloat g_unk0x004b049c = 0.5f;

// GLOBAL: LEGORACERS 0x004b04a0
extern const LegoFloat g_unk0x004b04a0 = 2.75f;

// GLOBAL: LEGORACERS 0x004b04a4
extern const LegoFloat g_unk0x004b04a4 = -0.5f;

// GLOBAL: LEGORACERS 0x004b04a8
extern const LegoFloat g_unk0x004b04a8 = 6.0f;

// GLOBAL: LEGORACERS 0x004b04ac
extern const LegoFloat g_unk0x004b04ac = 3.0f;

// GLOBAL: LEGORACERS 0x004b04b0
extern const LegoFloat g_unk0x004b04b0 = 15.0f;

// GLOBAL: LEGORACERS 0x004b04b8
extern const LegoFloat g_unk0x004b04b8 = 0.0020000001f;

// GLOBAL: LEGORACERS 0x004b04bc
extern const LegoFloat g_unk0x004b04bc = 0.00048828125f;

// GLOBAL: LEGORACERS 0x004b04c0
extern const LegoFloat g_unk0x004b04c0 = 0.0099999998f;

// GLOBAL: LEGORACERS 0x004b04c4
extern const LegoFloat g_unk0x004b04c4 = 0.000732421875f;

// GLOBAL: LEGORACERS 0x004b04c8
extern const LegoFloat g_unk0x004b04c8 = 0.0020000001f;

// GLOBAL: LEGORACERS 0x004b04cc
extern const LegoFloat g_unk0x004b04cc = 0.001953125f;

// GLOBAL: LEGORACERS 0x004b04d0
extern const LegoFloat g_unk0x004b04d0 = 50.0f;

// GLOBAL: LEGORACERS 0x004b04d4
extern const LegoFloat g_unk0x004b04d4 = -100.0f;

// GLOBAL: LEGORACERS 0x004b04d8
extern const LegoFloat g_unk0x004b04d8 = 340.0f;

// GLOBAL: LEGORACERS 0x004b04dc
extern const LegoFloat g_unk0x004b04dc = -250.0f;

// GLOBAL: LEGORACERS 0x004b04e0
extern const LegoFloat g_unk0x004b04e0 = 2000.0f;

// GLOBAL: LEGORACERS 0x004b054c
extern const LegoFloat g_unk0x004b054c = 0.003f;

// GLOBAL: LEGORACERS 0x004b0b90
extern const LegoFloat g_unk0x004b0b90 = 0.083333336f;

// GLOBAL: LEGORACERS 0x004b0cd8
extern const LegoFloat g_unk0x004b0cd8 = 30.0f;

// GLOBAL: LEGORACERS 0x004b0cdc
extern const LegoFloat g_unk0x004b0cdc = 300.0f;

// GLOBAL: LEGORACERS 0x004b0ce4
extern const LegoFloat g_unk0x004b0ce4 = 39.0f;

// GLOBAL: LEGORACERS 0x004b0ce8
extern const LegoFloat g_unk0x004b0ce8 = 0.78539819f;

// GLOBAL: LEGORACERS 0x004b0cec
extern const LegoFloat g_unk0x004b0cec = 0.70710677f;

// GLOBAL: LEGORACERS 0x004b0cf0
extern const LegoFloat g_unk0x004b0cf0 = 110.0f;

// GLOBAL: LEGORACERS 0x004b0cf4
extern const LegoFloat g_raceStateField0x3e8ContactLimitPadding = 0.4f;

// GLOBAL: LEGORACERS 0x004b0cf8
extern const LegoFloat g_unk0x004b0cf8 = 0.2f;

// GLOBAL: LEGORACERS 0x004b0cfc
extern const LegoFloat g_raceStateField0x3e8SupportSweepDistanceScale = 0.04f;

// GLOBAL: LEGORACERS 0x004b0d00
extern const LegoFloat g_raceStateField0x3e8SweepDistanceScale = 0.01f;

// GLOBAL: LEGORACERS 0x004b0d04
extern const LegoFloat g_raceStateField0x3e8AirborneDropStep = 0.008f;

// GLOBAL: LEGORACERS 0x004b0d08
extern const LegoFloat g_unk0x004b0d08 = 0.30000001f;

// GLOBAL: LEGORACERS 0x004b0d20
extern const LegoFloat g_unk0x004b0d20 = 6.0f;

// GLOBAL: LEGORACERS 0x004b0d24
extern const LegoFloat g_unk0x004b0d24 = 3.0f;

// GLOBAL: LEGORACERS 0x004b0d28
extern const LegoFloat g_unk0x004b0d28 = 0.005f;

// GLOBAL: LEGORACERS 0x004b0d2c
extern const LegoFloat g_raceStateField0x3e8BounceThreshold = 0.05f;

// GLOBAL: LEGORACERS 0x004b0d30
extern const LegoFloat g_raceStateField0x3e8BounceScale = 1.3f;

// GLOBAL: LEGORACERS 0x004b0d34
extern const LegoFloat g_raceStateField0x3e8FourContactBounceScale = 1.15f;

extern LegoU32 g_unk0x004b0d80;
extern const LegoFloat g_unk0x004b0cd0;
extern const LegoFloat g_unk0x004b0d84;
extern const LegoFloat g_carBuildModelHeightScale;
extern const LegoFloat g_carBuildModelTextureCoordinateScale;
extern const LegoFloat g_unk0x004b0430;
extern const LegoFloat g_unk0x004b0434;
extern const LegoFloat g_unk0x004b0544;
extern const LegoFloat g_ghostSpeedScale;
extern const LegoFloat g_twoPi;

// GLOBAL: LEGORACERS 0x004c4868
RaceState::Racer::Field0x3e8::Field0x74cInstance g_raceStateField0x3e8PathState0x004c4868;

// GLOBAL: LEGORACERS 0x004c48e0
GolMatrix3 g_raceStateField0x3e8PathOrientation0x004c48e0;

// GLOBAL: LEGORACERS 0x004c6c04
RaceState::Racer::Field0x3e8::SnapshotEntryBlock g_raceStateField0x3e8SnapshotEntries;

// GLOBAL: LEGORACERS 0x004c6df0
RaceState::Racer::Field0x3e8::Snapshot g_raceStateField0x3e8Snapshot;

#define g_raceStateField0x3e8Snapshot0x000 g_raceStateField0x3e8Snapshot.m_unk0x000
#define g_raceStateField0x3e8Snapshot0x030 g_raceStateField0x3e8Snapshot.m_unk0x030
#define g_raceStateField0x3e8Snapshot0x03c g_raceStateField0x3e8Snapshot.m_unk0x03c
#define g_raceStateField0x3e8Snapshot0x040 g_raceStateField0x3e8Snapshot.m_unk0x040
#define g_raceStateField0x3e8Snapshot0x070 g_raceStateField0x3e8Snapshot.m_unk0x070
#define g_raceStateField0x3e8Snapshot0x0a0 g_raceStateField0x3e8Snapshot.m_unk0x0a0
#define g_raceStateField0x3e8Snapshot0x0ac g_raceStateField0x3e8Snapshot.m_unk0x0ac
#define g_raceStateField0x3e8Snapshot0x0b0 g_raceStateField0x3e8Snapshot.m_unk0x0b0
#define g_raceStateField0x3e8Snapshot0x0b4 g_raceStateField0x3e8Snapshot.m_unk0x0b4
#define g_raceStateField0x3e8Snapshot0x0b8 g_raceStateField0x3e8Snapshot.m_unk0x0b8
#define g_raceStateField0x3e8Snapshot0x0c4 g_raceStateField0x3e8Snapshot.m_unk0x0c4
#define g_raceStateField0x3e8Snapshot0x0e8 g_raceStateField0x3e8Snapshot.m_unk0x0e8

// FUNCTION: LEGORACERS 0x00429020
RaceState::Racer::Field0x3e8::Field0x3e8()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004290b0
RaceState::Racer::Field0x3e8::~Field0x3e8()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00429120
void RaceState::Racer::Field0x3e8::Reset()
{
	m_unk0x6f0 = NULL;
	m_unk0x6f4 = NULL;
	m_unk0x6f8 = 0;
	m_unk0x6fc = NULL;
	FUN_0042ad70(0x21);
	FUN_0042ada0(0x21);
	FUN_0042add0(0x21);

	m_unk0x738 = 0;
	m_unk0x734 = g_unk0x004b0448;
	m_unk0x744 = 0;
	m_unk0x7c4.m_x = 0.0f;
	m_unk0x7c4.m_z = 0.0f;
	m_unk0x7c4.m_y = 0.0f;
	m_unk0x7c4.m_w = 0.0f;
	m_unk0x7d4 = 0;
	m_unk0x7d8 = 0;
	m_unk0x7dc = 0;
	m_unk0x7e0 = 0;
	m_unk0x7e4 = 0;
	m_unk0x658 = 0;
	m_unk0x680 = 0;
	m_unk0x67c = 0;
	m_unk0x748 = 0;
	m_unk0x700.m_x = 0.0f;
	m_unk0x700.m_y = 0.0f;
	m_unk0x700.m_z = 0.0f;
	m_unk0x70c.m_x = 0.0f;
	m_unk0x70c.m_y = 0.0f;
	m_unk0x70c.m_z = 0.0f;
	m_unk0x70c.m_w = 1.0f;
	m_soundResource = NULL;
	m_unk0x7e8 = 1.0f;
	m_unk0x7ec = 1.0f;
	m_unk0x73c = -1;
}

// FUNCTION: LEGORACERS 0x00429210
void RaceState::Racer::Field0x3e8::FUN_00429210(
	Racer* p_racer,
	RaceEventTable0x90* p_unk0x08,
	undefined4 p_unk0x0c,
	GolAnimatedEntity* p_unk0x10,
	GolBoundedEntity* p_unk0x14,
	GolBoundedEntity* p_unk0x18,
	Field0x004* p_unk0x1c,
	LegoFloat p_unk0x20,
	LegoFloat p_unk0x24,
	LegoFloat p_unk0x28,
	LegoFloat p_unk0x2c
)
{
	if (m_unk0x6f0 != NULL) {
		Destroy();
	}

	m_unk0x6f0 = p_racer;
	m_unk0x6f4 = p_unk0x08;
	m_unk0x6f8 = p_unk0x0c;
	m_unk0x6fc = p_unk0x18;
	FUN_00444d90(p_unk0x10, p_unk0x14, p_unk0x18, p_unk0x1c, p_unk0x20, p_unk0x24, p_unk0x28, p_unk0x2c);
	p_unk0x10->VTable0x04(&m_unk0x700);
	GolMath::FUN_1002f5a0(p_unk0x10->GetOrientation(), &m_unk0x70c);
	m_unk0x738 = 0;
}

// FUNCTION: LEGORACERS 0x004292b0
void RaceState::Racer::Field0x3e8::Destroy()
{
	FUN_0042b060();
	m_unk0x74c.Destroy();
	Reset();
	FUN_00444e90();
}

// FUNCTION: LEGORACERS 0x004292e0
void RaceState::Racer::Field0x3e8::FUN_004292e0()
{
	LegoU32 flags = m_flags0x6c0;
	if (!(flags & c_flags0x6c0Bit19)) {
		m_flags0x6c0 = flags | c_flags0x6c0Bit16;

		if (m_unk0x744) {
			LegoFloat value = g_unk0x004b0494;
			m_unk0x74c.m_unk0x2c = value;
		}

		m_unk0x734 = g_unk0x004b0450;
		m_unk0x5f4 = 1.5f;
		VTable0x18(g_unk0x004b0450);
	}
}

// FUNCTION: LEGORACERS 0x00429330
void RaceState::Racer::Field0x3e8::FUN_00429330()
{
	LegoU32 flags = m_flags0x6c0 & ~c_flags0x6c0Bit16;
	m_flags0x6c0 = flags;

	if (m_unk0x744 && !(flags & (c_flags0x6c0Bit1 | c_flags0x6c0Bit16 | c_flags0x6c0Bit18))) {
		m_unk0x7ec = 1.0f;
	}

	m_unk0x5f4 = 1.0f;
	m_unk0x734 = g_unk0x004b0448;
	VTable0x18(g_unk0x004b0448);
}

// FUNCTION: LEGORACERS 0x00429380
void RaceState::Racer::Field0x3e8::FUN_00429380()
{
	if (m_flags0x6c0 & c_flags0x6c0Bit16) {
		FUN_00429330();
	}

	m_flags0x6c0 |= c_flags0x6c0Bit19;

	if (m_unk0x744) {
		LegoFloat value = g_unk0x004b049c;
		m_unk0x74c.m_unk0x2c = value;
	}
}

// FUNCTION: LEGORACERS 0x004293c0
void RaceState::Racer::Field0x3e8::FUN_004293c0()
{
	LegoU32 flags = m_flags0x6c0 & ~c_flags0x6c0Bit19;
	m_flags0x6c0 = flags;

	if (m_unk0x744 && !(flags & (c_flags0x6c0Bit1 | c_flags0x6c0Bit16 | c_flags0x6c0Bit18))) {
		m_unk0x7ec = 1.0f;
	}
}

// FUNCTION: LEGORACERS 0x004293f0
void RaceState::Racer::Field0x3e8::VTable0x04(LegoS32 p_elapsedMs)
{
	GolVec3 soundPosition;
	GolVec3 position;

	if (m_unk0x744) {
		FUN_00429d40(p_elapsedMs);
	}
	else {
		Field0x3e8Base0x74c::VTable0x04(static_cast<LegoS32>(p_elapsedMs));

		if (m_unk0x36c == 4 && !m_unk0x3ec) {
			LegoU32 racerFlags = m_unk0x6f0->m_unk0xd04;
			if (!(racerFlags & Racer::c_flags0xd04Bit10) || !(racerFlags & Racer::c_flags0xd04Bit1)) {
				GolOrientedEntity* entity0 = &m_unk0x0e4;
				entity0->VTable0x04(&m_unk0x700);
				GolMath::FUN_1002f5a0(m_unk0x0e4.GetOrientation(), &m_unk0x70c);
			}
		}

		GolOrientedEntity* entity = &m_unk0x0e4;
		entity->VTable0x04(&position);
		if (position.m_z < g_unk0x004b04dc || position.m_z > g_unk0x004b04d8) {
			entity->VTable0x08(m_unk0x700);
			GolMath::FUN_00449340(&m_unk0x70c, &m_unk0x0e4.GetOrientation().m_m[0][0]);
			m_unk0x008.m_x = 0.0f;
			m_unk0x008.m_y = 0.0f;
			m_unk0x008.m_z = 0.0f;
			m_unk0x0a4.m_x = 0.0f;
			m_unk0x0a4.m_y = 0.0f;
			m_unk0x0a4.m_z = 0.0f;
		}

		LegoU32 racerFlags = m_unk0x6f0->m_unk0xd04;
		if ((racerFlags & Racer::c_flags0xd04Bit10) && (racerFlags & Racer::c_flags0xd04Bit1)) {
			entity->VTable0x08(m_unk0x700);
			GolMath::FUN_00449340(&m_unk0x70c, &m_unk0x0e4.GetOrientation().m_m[0][0]);
			m_unk0x008.m_x = 0.0f;
			m_unk0x008.m_y = 0.0f;
			m_unk0x008.m_z = 0.0f;
			m_unk0x0a4.m_x = 0.0f;
			m_unk0x0a4.m_y = 0.0f;
			m_unk0x0a4.m_z = 0.0f;
		}
	}

	if (m_unk0x740 == NULL) {
		return;
	}

	if (m_unk0x36c && !(m_flags0x6c0 & c_flags0x6c0Bit3) &&
		(m_unk0x604 >= g_unk0x004b0474 || m_unk0x604 <= -g_unk0x004b0474)) {
		LegoS32 soundAge = static_cast<LegoS32>(m_unk0x738);
		soundAge += p_elapsedMs;
		m_unk0x738 = soundAge;

		m_unk0x13c->VTable0x04(&soundPosition);
		m_unk0x740->SetPosition(soundPosition);
		m_unk0x740->SetVelocity(m_unk0x008);

		LegoFloat frequencyScale = m_unk0x604 / g_unk0x004b0478 + g_carBuildModelHeightScale;
		if (frequencyScale < g_unk0x004b043c) {
			frequencyScale = g_unk0x004b043c;
		}
		else if (frequencyScale > g_unk0x004b0440) {
			frequencyScale = g_unk0x004b0440;
		}
		m_unk0x740->SetFrequencyScale(frequencyScale);

		LegoFloat volume = static_cast<LegoFloat>(static_cast<LegoS32>(m_unk0x738)) / g_unk0x004b047c;
		if (volume > g_unk0x004b0438) {
			volume = g_unk0x004b0438;
		}
		m_unk0x740->SetVolume(volume);
	}
	else {
		FUN_0042b060();
	}
}

// FUNCTION: LEGORACERS 0x00429680
void RaceState::Racer::Field0x3e8::FUN_00429680(GolVec3* p_unk0x04)
{
	if (m_unk0x744) {
		GolVec3 direction = *p_unk0x04;
		m_unk0x74c.FUN_004a5750(&direction);
		FUN_0042a290(0);

		const GolVec3& side = m_unk0x13c->GetOrientation().m_rows[1];
		LegoFloat dot = side.m_z * direction.m_z;
		dot += side.m_y * direction.m_y;
		dot += side.m_x * direction.m_x;
		m_unk0x7c4.m_z = dot;

		if (dot > 0.0f) {
			if (m_unk0x74c.m_unk0x24 < dot) {
				dot = m_unk0x74c.m_unk0x24;
				m_unk0x7c4.m_z = dot;
			}
		}
		else if (m_unk0x74c.m_unk0x20 < -dot) {
			m_unk0x7c4.m_z = -m_unk0x74c.m_unk0x20;
		}

		FUN_0042a570();
	}
	else {
		FUN_004490b0(p_unk0x04);
	}
}

// FUNCTION: LEGORACERS 0x00429770
void RaceState::Racer::Field0x3e8::VTable0x20(GolVec3* p_unk0x04, LegoFloat p_unk0x08)
{
	if (!m_unk0x744) {
		Field0x3e8Base0x74c::VTable0x20(p_unk0x04, p_unk0x08);
		return;
	}

	LegoFloat dot = m_unk0x168.m_z * p_unk0x04->m_z;
	dot += m_unk0x168.m_y * p_unk0x04->m_y;
	dot += m_unk0x168.m_x * p_unk0x04->m_x;
	if (p_unk0x08 < 0.0f) {
		dot = -dot;
		p_unk0x08 = -p_unk0x08;
	}

	if (p_unk0x08 > g_unk0x004b0484) {
		p_unk0x08 = g_unk0x004b0484;
	}
	LegoFloat scaled = p_unk0x08 / g_unk0x004b0484;

	if (dot >= 0.0f) {
		LegoFloat amount = (1.0f - dot) * g_unk0x004b0544;
		LegoFloat value;
		if (m_flags0x6c0 & c_flags0x6c0Bit1) {
			value = g_unk0x004b0490;
			value += 0.1f;
		}
		else {
			value = m_unk0x74c.m_unk0x2c;
			value += scaled;
		}
		amount += value;

		if (amount > g_unk0x004b04a0) {
			amount = g_unk0x004b04a0;
		}
		m_unk0x74c.m_unk0x2c = amount;
	}
	else {
		LegoFloat amount = (dot + 1.0f) * g_carBuildModelTextureCoordinateScale;
		LegoFloat value;
		if (m_flags0x6c0 & c_flags0x6c0Bit1) {
			value = g_unk0x004b0490 - 0.1f;
		}
		else {
			value = m_unk0x74c.m_unk0x2c - scaled;
		}
		value -= amount;

		if (value < g_unk0x004b04a4) {
			value = g_unk0x004b04a4;
		}
		m_unk0x74c.m_unk0x2c = value;
	}
}

// FUNCTION: LEGORACERS 0x004298a0
void RaceState::Racer::Field0x3e8::VTable0x40(GolVec3* p_unk0x04)
{
	if (!m_unk0x744) {
		Field0x3e8Base0x74c::VTable0x40(p_unk0x04);
	}
	else {
		FUN_00429990(p_unk0x04);
	}
}

// FUNCTION: LEGORACERS 0x004298d0
void RaceState::Racer::Field0x3e8::VTable0x44()
{
	if (!m_unk0x744) {
		Field0x3e8Base0x74c::VTable0x44();
	}
	else {
		FUN_00429940();
	}
}

// FUNCTION: LEGORACERS 0x004298f0
void RaceState::Racer::Field0x3e8::VTable0x48(GolVec3* p_unk0x04)
{
	if (!m_unk0x744) {
		Field0x3e8Base0x74c::VTable0x48(p_unk0x04);
	}
	else {
		FUN_00429990(p_unk0x04);
	}
}

// FUNCTION: LEGORACERS 0x00429920
void RaceState::Racer::Field0x3e8::VTable0x4c()
{
	if (!m_unk0x744) {
		Field0x3e8Base0x74c::VTable0x4c();
	}
	else {
		FUN_00429940();
	}
}

// FUNCTION: LEGORACERS 0x00429940
void RaceState::Racer::Field0x3e8::FUN_00429940()
{
	LegoU32 flags = m_flags0x6c0;
	flags &= ~c_flags0x6c0Bit18;
	m_flags0x6c0 = flags;

	if (m_flags0x6c0 & c_flags0x6c0Bit1) {
		m_unk0x7ec = g_unk0x004b0490;
		return;
	}

	if (m_unk0x7e8 < 0.0f) {
		m_unk0x7e8 = 1.0f;
	}

	m_unk0x7ec = m_unk0x7e8;
}

// FUNCTION: LEGORACERS 0x00429990
void RaceState::Racer::Field0x3e8::FUN_00429990(GolVec3* p_unk0x04)
{
	LegoU32 flags = m_flags0x6c0 | c_flags0x6c0Bit18;
	m_flags0x6c0 = flags;

	LegoFloat dot = m_unk0x168.m_x * p_unk0x04->m_x + m_unk0x168.m_y * p_unk0x04->m_y + m_unk0x168.m_z * p_unk0x04->m_z;
	if (dot >= 0.0f) {
		if (flags & c_flags0x6c0Bit1) {
			LegoFloat value = g_unk0x004b0490;
			value += 0.1f;
			m_unk0x7ec = value;
		}
		else {
			m_unk0x7ec = dot / g_unk0x004b0484 + m_unk0x74c.m_unk0x2c;
		}

		if (m_unk0x7ec > g_unk0x004b04a0) {
			m_unk0x7ec = g_unk0x004b04a0;
		}
	}
	else {
		if (flags & c_flags0x6c0Bit1) {
			m_unk0x7ec = g_unk0x004b0490 - 0.1f;
		}
		else {
			m_unk0x7ec = dot / g_unk0x004b0484 + m_unk0x74c.m_unk0x2c;
		}

		if (m_unk0x7ec < g_unk0x004b04a4) {
			m_unk0x7ec = g_unk0x004b04a4;
		}
	}
}

// FUNCTION: LEGORACERS 0x00429a70
void RaceState::Racer::Field0x3e8::VTable0x1c(GolVec3* p_unk0x04, GolVec3* p_unk0x08)
{
	if (!m_unk0x744) {
		Field0x3e8Base0x74c::VTable0x1c(p_unk0x04, p_unk0x08);
	}
}

// FUNCTION: LEGORACERS 0x00429a90
void RaceState::Racer::Field0x3e8::FUN_00429a90()
{
	if (m_unk0x744 == 0) {
		return;
	}

	LegoU32& flags = m_flags0x6c0;
	flags |= c_flags0x6c0Bit3 | c_flags0x6c0Bit16 | c_flags0x6c0Bit17;
	LegoFloat value = g_unk0x004b0498;
	m_unk0x74c.m_unk0x2c = value;

	if (!(flags & c_flags0x6c0Bit3)) {
		m_unk0x658 = 0.0f;
		m_unk0x680 = 0.0f;
	}

	m_unk0x65c = g_unk0x004b04a8;
	m_unk0x67c = 0.0f;
	m_unk0x660 = g_unk0x004b04ac;
}

// FUNCTION: LEGORACERS 0x00429af0
void RaceState::Racer::Field0x3e8::FUN_00429af0()
{
	if (m_unk0x744) {
		m_unk0x74c.m_unk0x2c = m_unk0x7e8;
		m_unk0x65c = 0;
		m_unk0x67c = 0;
		m_unk0x660 = g_unk0x004b04b0;
		m_flags0x6c0 &= ~(c_flags0x6c0Bit3 | c_flags0x6c0Bit16 | c_flags0x6c0Bit17);
	}
}

// FUNCTION: LEGORACERS 0x00429b40
void RaceState::Racer::Field0x3e8::VTable0x30()
{
	if (!m_unk0x744) {
		Field0x3e8Base0x74c::VTable0x30();
		return;
	}

	if (!(m_flags0x6c0 & c_flags0x6c0Bit3)) {
		FUN_00429cf0(-0.003f, 250);
		m_unk0x658 = 0;
		m_flags0x6c0 |= c_flags0x6c0Bit3;
		m_unk0x680 = 0;
		m_unk0x67c = 0;
		m_unk0x65c = g_unk0x004b04a8;
		m_unk0x660 = g_unk0x004b04ac;
	}
}

// FUNCTION: LEGORACERS 0x00429bc0
void RaceState::Racer::Field0x3e8::VTable0x34()
{
	if (!m_unk0x744) {
		Field0x3e8Base0x74c::VTable0x34();
	}
	else {
		m_unk0x65c = 0.0f;
		m_unk0x67c = 0;
		m_unk0x660 = g_unk0x004b04b0;
		m_flags0x6c0 &= ~c_flags0x6c0Bit3;
	}
}

// FUNCTION: LEGORACERS 0x00429c00
void RaceState::Racer::Field0x3e8::VTable0x38()
{
	Field0x3e8Base0x74c::VTable0x38();
	m_unk0x7c4.m_w = g_unk0x004b04d0;
	LegoFloat unk0x778 = g_unk0x004b0488;
	m_unk0x74c.m_unk0x2c = unk0x778;
}

// FUNCTION: LEGORACERS 0x00429c30
void RaceState::Racer::Field0x3e8::VTable0x3c()
{
	if (!m_unk0x744) {
		Field0x3e8Base0x74c::VTable0x3c();
	}
}

// FUNCTION: LEGORACERS 0x00429c40
void RaceState::Racer::Field0x3e8::VTable0x24(LegoFloat p_unk0x04, LegoFloat p_unk0x08, LegoFloat p_unk0x0c)
{
	if (!m_unk0x744) {
		Field0x3e8Base0x74c::VTable0x24(p_unk0x04, p_unk0x08, p_unk0x0c);
		return;
	}

	LegoU32 flags = m_flags0x6c0;
	if (!(flags & c_flags0x6c0Bit1)) {
		LegoFloat scaled = p_unk0x04;
		scaled *= g_twoPi;
		scaled /= p_unk0x08;
		m_unk0x5e0 = static_cast<LegoS32>(scaled);
		m_unk0x7d4 = p_unk0x08;
		m_unk0x7d8 = 0;
		m_flags0x6c0 = flags | c_flags0x6c0Bit1;

		if (m_unk0x36c) {
			LegoFloat value = g_unk0x004b0490;
			m_unk0x74c.m_unk0x2c = value;
		}
	}
}

// FUNCTION: LEGORACERS 0x00429cd0
void RaceState::Racer::Field0x3e8::VTable0x2c()
{
	if (!m_unk0x744) {
		Field0x3e8Base0x74c::VTable0x2c();
	}
	else {
		m_flags0x6c0 &= ~(c_flags0x6c0Bit1 | c_flags0x6c0Bit2);
	}
}

// FUNCTION: LEGORACERS 0x00429cf0
void RaceState::Racer::Field0x3e8::FUN_00429cf0(LegoFloat p_unk0x04, LegoU32 p_unk0x08)
{
	if (!m_unk0x744) {
		FUN_00445bb0(p_unk0x04, p_unk0x08);
		return;
	}

	if (!m_unk0x5dc) {
		m_unk0x7e0 = 0;
		m_unk0x7dc = -p_unk0x04;
		m_unk0x5dc = p_unk0x08;
	}
}

// STUB: LEGORACERS 0x00429d40
void RaceState::Racer::Field0x3e8::FUN_00429d40(LegoU32 p_elapsedMs)
{
	if (p_elapsedMs == 0) {
		return;
	}

	if (m_unk0x748 != 0) {
		return;
	}

	if (m_flags0x6c0 & c_flags0x6c0Bit3) {
		FUN_0042a100();
	}

	if (m_flags0x6c0 & c_flags0x6c0Bit16) {
		if (m_unk0x74c.m_unk0x30 < g_unk0x004b04e0) {
			LegoFloat speedScale = m_unk0x74c.m_unk0x30;
			speedScale -= g_unk0x004b04e0;
			speedScale /= g_unk0x004b04e0;
			speedScale = -speedScale;
			m_unk0x7ec = speedScale * (g_unk0x004b04a0 - g_unk0x004b0494) + g_unk0x004b0494;
		}
	}

	FUN_0042a220();

	LegoU32 elapsedMs = p_elapsedMs;
	for (;;) {
		if (elapsedMs != 0) {
			GolVec3 previousPosition;
			m_unk0x13c->VTable0x04(&previousPosition);

			LegoFloat elapsed = static_cast<LegoFloat>(static_cast<LegoS32>(elapsedMs));
			LegoU32 flags = m_flags0x6c0;
			LegoU32 suspendedMask = flags & c_flags0x6c0Bit18;
			if (suspendedMask || !(flags & (c_flags0x6c0Bit1 | c_flags0x6c0Bit16 | c_flags0x6c0Bit19)) ||
				m_unk0x36c == 0) {
				LegoFloat currentSpeed = m_unk0x74c.m_unk0x2c;
				if (currentSpeed < m_unk0x7ec) {
					LegoFloat rate;
					if (suspendedMask) {
						rate = g_unk0x004b04c8;
					}
					else if (flags & c_flags0x6c0Bit16) {
						rate = g_unk0x004b04c0;
					}
					else {
						rate = g_unk0x004b04bc;
					}

					currentSpeed += rate * elapsed;
					if (currentSpeed > m_unk0x7ec) {
						currentSpeed = m_unk0x7ec;
					}
					m_unk0x74c.m_unk0x2c = currentSpeed;
				}
				else if (currentSpeed > m_unk0x7ec) {
					LegoFloat rate;
					if (suspendedMask) {
						rate = g_unk0x004b04c4;
					}
					else {
						rate = g_unk0x004b04b8;
					}

					currentSpeed -= rate * elapsed;
					if (currentSpeed < m_unk0x7ec) {
						currentSpeed = m_unk0x7ec;
					}
					m_unk0x74c.m_unk0x2c = currentSpeed;
				}
			}

			m_unk0x74c.FUN_004a5320(elapsed);

			if (m_unk0x7c4.m_z > 0.0f) {
				m_unk0x7c4.m_z -= g_unk0x004b04cc * elapsed;
				if (m_unk0x7c4.m_z < 0.0f) {
					m_unk0x7c4.m_z = 0.0f;
				}
			}
			else if (m_unk0x7c4.m_z < 0.0f) {
				m_unk0x7c4.m_z += g_unk0x004b04cc * elapsed;
				if (m_unk0x7c4.m_z > 0.0f) {
					m_unk0x7c4.m_z = 0.0f;
				}
			}

			if ((m_flags0x6c0 & c_flags0x6c0Bit3) || m_unk0x658 != 0.0f) {
				FUN_004464a0(elapsedMs);
			}

			if (m_unk0x7c4.m_w != 0.0f || m_unk0x7c4.m_y != 0.0f) {
				LegoFloat time = elapsed * 0.001f;
				m_unk0x7c4.m_w += g_unk0x004b04d4 * time;
				m_unk0x7c4.m_y += time * m_unk0x7c4.m_w;
				if (m_unk0x7c4.m_y <= 0.0f) {
					m_unk0x7c4.m_y = 0.0f;
					m_unk0x7c4.m_w = 0.0f;
					m_flags0x6c0 &= ~c_flags0x6c0Bit7;
				}
			}

			FUN_0042a290(elapsedMs);
			FUN_0042a570();

			GolVec3 currentPosition;
			m_unk0x13c->VTable0x04(&currentPosition);

			LegoFloat invElapsed = 1.0f / elapsed;
			m_unk0x008.m_x = currentPosition.m_x - previousPosition.m_x;
			m_unk0x008.m_y = currentPosition.m_y - previousPosition.m_y;
			m_unk0x008.m_z = currentPosition.m_z - previousPosition.m_z;
			m_unk0x008 *= invElapsed;

			FUN_00447330();
			m_unk0x0e4.CopyTransformFrom(*m_unk0x13c);
		}

		if (m_unk0x3ec != 0) {
			LegoFloat speed = g_unk0x004b048c;
			m_unk0x74c.m_unk0x2c = speed;
			FUN_00447880();
			FUN_0042a220();
			elapsedMs = m_unk0x3f0;
		}
		else {
			elapsedMs = FUN_004478b0(elapsedMs, FALSE);
		}

		if (m_unk0x3ec == 0) {
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x0042a100
void RaceState::Racer::Field0x3e8::FUN_0042a100()
{
	GolQuat rotation = m_unk0x74c.m_unk0x0c;
	GolMath::FUN_00449340(&rotation, &g_raceStateField0x3e8PathOrientation0x004c48e0.m_m[0][0]);

	GolVec3 currentDirection = g_raceStateField0x3e8PathOrientation0x004c48e0.m_rows[1];
	g_raceStateField0x3e8PathState0x004c4868 = m_unk0x74c;
	g_raceStateField0x3e8PathState0x004c4868.FUN_004a5320(500.0f);

	rotation = g_raceStateField0x3e8PathState0x004c4868.m_unk0x0c;
	GolMath::FUN_00449340(&rotation, &g_raceStateField0x3e8PathOrientation0x004c48e0.m_m[0][0]);

	LegoFloat dot = g_raceStateField0x3e8PathOrientation0x004c48e0.m_rows[0].m_z * currentDirection.m_z;
	dot += g_raceStateField0x3e8PathOrientation0x004c48e0.m_rows[0].m_y * currentDirection.m_y;
	dot += g_raceStateField0x3e8PathOrientation0x004c48e0.m_rows[0].m_x * currentDirection.m_x;
	dot *= 8.0f;

	if (dot > 1.0f) {
		dot = 1.0f;
	}
	else if (dot < -1.0f) {
		dot = -1.0f;
	}

	m_unk0x67c = 0.78539819f * dot;
}

// FUNCTION: LEGORACERS 0x0042a220
void RaceState::Racer::Field0x3e8::FUN_0042a220()
{
	FUN_004474c0();

	m_unk0x868.m_x = m_unk0x7c4.m_x;
	m_unk0x868.m_w = m_unk0x7c4.m_w;
	m_unk0x868.m_z = m_unk0x7c4.m_z;
	m_unk0x7f0 = m_unk0x74c;
	m_unk0x878 = m_unk0x7d4;
	m_unk0x868.m_y = m_unk0x7c4.m_y;
	m_unk0x87c = m_unk0x7d8;
}

// STUB: LEGORACERS 0x0042a290
void RaceState::Racer::Field0x3e8::FUN_0042a290(LegoU32 p_elapsedMs)
{
	GolQuat rotation = m_unk0x74c.m_unk0x0c;
	GolMath::FUN_00449340(&rotation, &m_unk0x13c->GetOrientation().m_m[0][0]);

	if ((m_flags0x6c0 & c_flags0x6c0Bit3) || m_unk0x680 != 0.0f) {
		const GolMatrix3& orientation = m_unk0x13c->GetOrientation();
		GolVec3 axis = orientation.m_rows[0];
		GolVec3 forward = orientation.m_rows[2];
		GolVec3 rotatedForward;
		GolMath::FUN_004496a0(&forward, &rotatedForward, &axis, m_unk0x680);
		m_unk0x13c->VTable0x40(axis, rotatedForward);
	}

	LegoU32 elapsedMs = p_elapsedMs;
	LegoU32 timer = m_unk0x5dc;
	if (timer != 0 || m_unk0x7e0 != 0.0f) {
		if (timer != 0) {
			if (elapsedMs >= timer) {
				m_unk0x5dc = 0;
				m_unk0x7dc = -(m_unk0x7dc * g_carBuildModelTextureCoordinateScale);
			}
			else {
				m_unk0x5dc = timer - elapsedMs;
			}
		}

		LegoBool32 wasNonNegative = m_unk0x7e0 >= 0.0f;
		const GolMatrix3& orientation = m_unk0x13c->GetOrientation();
		GolVec3 axis = orientation.m_rows[0];
		GolVec3 forward = orientation.m_rows[2];

		m_unk0x7e0 += m_unk0x7dc * static_cast<LegoFloat>(static_cast<LegoS32>(elapsedMs));
		LegoBool32 applyTiltRotation = TRUE;
		if (m_unk0x5dc == 0) {
			LegoBool32 isNonNegative = m_unk0x7e0 >= 0.0f;
			if (wasNonNegative != isNonNegative) {
				m_unk0x7e0 = 0.0f;
				m_unk0x7e4 = 0.0f;
				applyTiltRotation = FALSE;
			}
		}

		if (applyTiltRotation) {
			m_unk0x13c->VTable0x2c(m_unk0x358, &m_unk0x198[1].m_unk0x00c);

			GolVec3 rotatedForward;
			GolMath::FUN_004496a0(&forward, &rotatedForward, &axis, m_unk0x7e0);
			m_unk0x13c->VTable0x40(axis, rotatedForward);

			GolVec3 transformed;
			m_unk0x13c->VTable0x2c(m_unk0x358, &transformed);
			m_unk0x7e4 = transformed.m_z - m_unk0x198[1].m_unk0x00c.m_z;
		}
	}

	if (m_unk0x5e0 == 0) {
		return;
	}

	if (p_elapsedMs >= m_unk0x5e0) {
		m_unk0x5e0 = 0;
		VTable0x2c();
		return;
	}

	m_unk0x5e0 -= p_elapsedMs;

	GolVec3 right;
	GolVec3 forward;
	m_unk0x13c->VTable0x48(&right, &forward);

	m_unk0x7d8 += m_unk0x7d4 * static_cast<LegoFloat>(static_cast<LegoS32>(elapsedMs));

	GolVec3 rotatedRight;
	GolMath::FUN_004496a0(&right, &rotatedRight, &forward, m_unk0x7d8);
	m_unk0x13c->VTable0x40(rotatedRight, forward);
}

// FUNCTION: LEGORACERS 0x0042a570
void RaceState::Racer::Field0x3e8::FUN_0042a570()
{
	GolVec3 position = m_unk0x74c.m_unk0x00;
	GolOrientedEntity* entity = m_unk0x13c;
	const GolMatrix3& orientation = entity->GetOrientation();
	GolVec3 side;
	side.m_x = orientation.m_m[1][0];
	side.m_y = orientation.m_m[1][1];
	side.m_z = orientation.m_m[1][2];
	LegoFloat sideOffset = m_unk0x7c4.m_z;

	position.m_z = position.m_z - m_unk0x7c4.m_x + m_unk0x7e4 + m_unk0x7c4.m_y + m_unk0x658;
	GolVec3 scaledSide;
	scaledSide.m_x = side.m_x * sideOffset;
	scaledSide.m_y = side.m_y * sideOffset;
	scaledSide.m_z = side.m_z * sideOffset;
	position.m_x += scaledSide.m_x;
	position.m_y += scaledSide.m_y;
	position.m_z += scaledSide.m_z;
	entity->VTable0x08(position);

	m_unk0x36c = m_unk0x74c.m_unk0x1c;
	entity = m_unk0x13c;
	entity->VTable0x2c(m_unk0x014, &m_unk0x020);
	m_unk0x13c->GetOrientationRow0(&m_unk0x168);
	FUN_00440a60();
}

// FUNCTION: LEGORACERS 0x0042a670
void RaceState::Racer::Field0x3e8::FUN_0042a670(Field0x00c::Entry* p_entry)
{
	m_unk0x744 = TRUE;
	m_unk0x74c.FUN_004a5200(p_entry);

	GolVec3 position = p_entry->m_unk0x008;
	GolQuat rotation = p_entry->m_unk0x014;
	m_unk0x13c->VTable0x08(position);
	m_unk0x13c->SetOrientationFromQuaternion(rotation);
	m_unk0x13c->VTable0x2c(m_unk0x014, &m_unk0x020);

	for (LegoU32 i = 0; i < sizeOfArray(m_unk0x370); i++) {
		m_unk0x13c->VTable0x2c(m_unk0x370[i], &m_unk0x3a0[i]);
	}
}

// FUNCTION: LEGORACERS 0x0042a7f0
LegoBool32 RaceState::Racer::Field0x3e8::FUN_0042a7f0()
{
	if (m_unk0x604 < g_unk0x004b0454 && -g_unk0x004b0454 < m_unk0x604) {
		return FALSE;
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0042a830
LegoU32 RaceState::Racer::Field0x3e8::VTable0x0c(
	GolVec3* p_unk0x04,
	RaceEventRecord* p_unk0x08,
	GolBoundedEntity* p_unk0x0c,
	GolBoundingVolume::Field0x0c* p_unk0x10
)
{
	if (p_unk0x0c == m_unk0x6fc) {
		if (!p_unk0x10) {
			return FALSE;
		}

		LegoS32 eventKind = p_unk0x08->m_unk0x18;
		if (static_cast<LegoChar>(eventKind) >= '0' && static_cast<LegoChar>(eventKind) <= '9') {
			m_unk0x6f0->FUN_00439fc0(p_unk0x08->m_pathField, p_unk0x10);
			return FALSE;
		}
	}

	RaceEventRecord::Target* target = p_unk0x08->m_target;
	if (!target) {
		return TRUE;
	}

	if (target->m_flags0x08 & RaceEventRecord::Target::c_flags0x08Bit18) {
		m_unk0x6f0->m_lapsCompleted = m_unk0x6f0->m_unk0xce0;
	}

	if (target->m_flags0x08 & RaceEventRecord::Target::c_flags0x08Bit3) {
		m_unk0x6f4->FUN_00462580(target->m_unk0x14, target->m_unk0x14, p_unk0x04);
		m_unk0x6f4->FUN_00462ae0(target->m_unk0x14, target->m_unk0x14, m_unk0x6f0);
	}

	return (~target->m_flags0x08 >> 16) & 1;
}

// FUNCTION: LEGORACERS 0x0042a900
void RaceState::Racer::Field0x3e8::VTable0x10()
{
	Field0x3e8* self = this;
	Field0x198* entry = self->m_unk0x198;
	Field0x198* end = self->m_unk0x198 + sizeOfArray(self->m_unk0x198);

	if (entry >= end) {
		return;
	}

	do {
		RaceEventRecord* record = entry->m_unk0x03c;
		RaceEventRecord::Target* target0;
		if (record == NULL) {
			target0 = NULL;
		}
		else {
			target0 = record->m_target;
		}

		record = entry->m_unk0x040;
		RaceEventRecord::Target* target1;
		if (record == NULL) {
			target1 = NULL;
		}
		else {
			target1 = record->m_target;
		}

		if (target0) {
			self->FUN_0042aad0(entry, target0);
		}
		else {
			self->FUN_0042acb0(entry);
			if (!target1) {
				entry++;
				continue;
			}
		}

		RaceEventRecord* record0 = entry->m_unk0x03c;
		RaceEventRecord* record1 = entry->m_unk0x040;
		if (record0 != record1) {
			LegoBool32 notify0 = target0 != NULL;
			LegoBool32 notify1 = target1 != NULL;

			for (Field0x198* other = self->m_unk0x198; other < end; other++) {
				if (other == entry) {
					continue;
				}

				RaceEventRecord* otherRecord1 = other->m_unk0x040;
				if (record0 == otherRecord1 || (record0 == other->m_unk0x03c && other < entry)) {
					notify0 = FALSE;
				}

				if (record1 == other->m_unk0x03c || (record1 == otherRecord1 && other < entry)) {
					notify1 = FALSE;
				}
			}

			if (notify1) {
				self->FUN_0042aa70(entry, target1);
			}

			if (notify0) {
				self->FUN_0042aa30(entry, target0);
			}
		}

		entry++;
	} while (entry < end);
}

// FUNCTION: LEGORACERS 0x0042aa30
void RaceState::Racer::Field0x3e8::FUN_0042aa30(Field0x198* p_unk0x04, RaceEventRecord::Target* p_unk0x08)
{
	if (p_unk0x08->m_flags0x08 & RaceEventRecord::Target::c_flags0x08Unk0x0c) {
		m_unk0x6f4->FUN_00461ef0(p_unk0x08->m_unk0x0c, &p_unk0x04->m_unk0x00c);
		m_unk0x6f4->FUN_004628c0(p_unk0x08->m_unk0x0c, m_unk0x6f0);
	}
}

// FUNCTION: LEGORACERS 0x0042aa70
void RaceState::Racer::Field0x3e8::FUN_0042aa70(Field0x198* p_unk0x04, RaceEventRecord::Target* p_unk0x08)
{
	if (p_unk0x08->m_flags0x08 & RaceEventRecord::Target::c_flags0x08Unk0x34) {
		if (p_unk0x08->m_unk0x34 == m_unk0x73c) {
			FUN_0042b060();
		}
	}

	if (p_unk0x08->m_flags0x08 & RaceEventRecord::Target::c_flags0x08Unk0x10) {
		m_unk0x6f4->FUN_00462140(p_unk0x08->m_unk0x10, &p_unk0x04->m_unk0x00c);
		m_unk0x6f4->FUN_004629d0(p_unk0x08->m_unk0x10, m_unk0x6f0);
	}
}

// FUNCTION: LEGORACERS 0x0042aad0
void RaceState::Racer::Field0x3e8::FUN_0042aad0(Field0x198* p_unk0x04, RaceEventRecord::Target* p_unk0x08)
{
	if (!(p_unk0x04->m_flags0x048 & 1)) {
		FUN_0042acb0(p_unk0x04);
		return;
	}

	if (p_unk0x08->m_flags0x08 & RaceEventRecord::Target::c_flags0x08Unk0x34) {
		FUN_0042af90(p_unk0x08->m_unk0x34);
	}

	LegoU32 disabledMask = c_flags0x6c0Bit20;
	if ((p_unk0x08->m_flags0x08 & RaceEventRecord::Target::c_flags0x08Unk0x58) && !(m_flags0x6c0 & disabledMask)) {
		LegoFloat value = p_unk0x08->m_unk0x58;
		p_unk0x04->m_unk0x050 = value;
		if (m_unk0x6f0->m_unk0x014) {
			m_unk0x6f0->m_unk0x014->FUN_00421fe0(value);
		}
	}
	else {
		p_unk0x04->m_unk0x050 = 0.0f;
		if (m_unk0x6f0->m_unk0x014) {
			m_unk0x6f0->m_unk0x014->FUN_00421fe0(0.0f);
		}
	}

	if ((p_unk0x08->m_flags0x08 & RaceEventRecord::Target::c_flags0x08Unk0x48) && !(m_flags0x6c0 & disabledMask)) {
		LegoFloat value = p_unk0x08->m_unk0x48;
		p_unk0x04->m_unk0x054 = value;
	}
	else {
		p_unk0x04->m_unk0x054 = g_unk0x004b0460;
	}

	if ((p_unk0x08->m_flags0x08 & RaceEventRecord::Target::c_flags0x08Unk0x4c) && !(m_flags0x6c0 & disabledMask)) {
		LegoFloat value = p_unk0x08->m_unk0x4c;
		p_unk0x04->m_unk0x058 = value;
	}
	else {
		p_unk0x04->m_unk0x058 = g_unk0x004b0464;
	}

	if ((p_unk0x08->m_flags0x08 & RaceEventRecord::Target::c_flags0x08Unk0x50) && !(m_flags0x6c0 & disabledMask)) {
		LegoFloat value = p_unk0x08->m_unk0x50;
		p_unk0x04->m_unk0x05c = value;
	}
	else {
		p_unk0x04->m_unk0x05c = g_unk0x004b0458;
	}

	if ((p_unk0x08->m_flags0x08 & RaceEventRecord::Target::c_flags0x08Unk0x54) && !(m_flags0x6c0 & disabledMask)) {
		LegoFloat value = p_unk0x08->m_unk0x54;
		p_unk0x04->m_unk0x060 = value;
	}
	else {
		p_unk0x04->m_unk0x060 = g_unk0x004b045c;
	}

	if ((p_unk0x08->m_flags0x08 & RaceEventRecord::Target::c_flags0x08Unk0x28) && !(m_flags0x6c0 & disabledMask)) {
		p_unk0x04->m_unk0x064 = p_unk0x08->m_unk0x28;
	}
	else {
		p_unk0x04->m_unk0x064.m_x = 0.0f;
		p_unk0x04->m_unk0x064.m_y = 0.0f;
		p_unk0x04->m_unk0x064.m_z = 0.0f;
	}

	if ((p_unk0x08->m_flags0x08 & RaceEventRecord::Target::c_flags0x08Unk0x40) &&
		!(m_flags0x6c0 & (c_flags0x6c0Bit3 | c_flags0x6c0Bit7)) && m_unk0x618 > g_unk0x004b0468 &&
		m_unk0x6f0->m_unk0xd08 != 2) {
		GolName name;
		::memcpy(name, p_unk0x08->m_unk0x40, sizeof(GolName));
		m_unk0x6f0->m_unk0x018.FUN_0043dd50(p_unk0x04 - m_unk0x198, name);
		return;
	}

	m_unk0x6f0->m_unk0x018.FUN_0043de90(p_unk0x04 - m_unk0x198);
}

// FUNCTION: LEGORACERS 0x0042acb0
void RaceState::Racer::Field0x3e8::FUN_0042acb0(Field0x198* p_unk0x04)
{
	p_unk0x04->m_unk0x050 = 0.0f;
	p_unk0x04->m_unk0x054 = g_unk0x004b0460;
	p_unk0x04->m_unk0x058 = g_unk0x004b0464;
	p_unk0x04->m_unk0x05c = g_unk0x004b0458;
	p_unk0x04->m_unk0x060 = g_unk0x004b045c;
	p_unk0x04->m_unk0x064.m_x = 0.0f;
	p_unk0x04->m_unk0x064.m_y = 0.0f;
	p_unk0x04->m_unk0x064.m_z = 0.0f;

	LegoU32 index = p_unk0x04 - m_unk0x198;
	m_unk0x6f0->m_unk0x018.FUN_0043de90(index);
	if (m_unk0x6f0->m_unk0x014) {
		m_unk0x6f0->m_unk0x014->FUN_00421fe0(0.0f);
	}
}

// FUNCTION: LEGORACERS 0x0042ad30
void RaceState::Racer::Field0x3e8::VTable0x14(LegoFloat p_unk0x04)
{
	LegoFloat amount = m_unk0x72c;
	amount *= p_unk0x04;
	Field0x3e8Base0x74c::VTable0x14(amount);
}

// FUNCTION: LEGORACERS 0x0042ad50
void RaceState::Racer::Field0x3e8::VTable0x18(LegoFloat p_unk0x04)
{
	LegoFloat amount = m_unk0x730;
	amount *= p_unk0x04;
	Field0x3e8Base0x74c::VTable0x18(amount);
}

// FUNCTION: LEGORACERS 0x0042ad70
void RaceState::Racer::Field0x3e8::FUN_0042ad70(LegoS32 p_unk0x04)
{
	m_unk0x71c = p_unk0x04;
	m_unk0x728 = static_cast<LegoFloat>(p_unk0x04) * g_unk0x004b054c + 0.7f;
}

// FUNCTION: LEGORACERS 0x0042ada0
void RaceState::Racer::Field0x3e8::FUN_0042ada0(LegoS32 p_unk0x04)
{
	m_unk0x720 = p_unk0x04;
	m_unk0x72c = 1.0f - static_cast<LegoFloat>(50 - p_unk0x04) * 0.001f;
}

// FUNCTION: LEGORACERS 0x0042add0
void RaceState::Racer::Field0x3e8::FUN_0042add0(LegoS32 p_unk0x04)
{
	m_unk0x724 = p_unk0x04;
	m_unk0x730 = 1.0f - static_cast<LegoFloat>(50 - p_unk0x04) * 0.001f;
	FUN_00429330();
}

// STUB: LEGORACERS 0x0042af90 FOLDED
SpatialSoundInstance* RaceState::Racer::Field0x3e8::FUN_0042af90(LegoS32 p_unk0x04)
{
	if (m_unk0x740 != NULL) {
		if (p_unk0x04 == m_unk0x73c) {
			return m_unk0x740;
		}

		FUN_0042b060();
	}

	m_unk0x738 = 0;
	m_unk0x73c = p_unk0x04;
	m_unk0x740 = m_unk0x158->FUN_00443bd0(static_cast<LegoU32>(p_unk0x04));

	if (m_unk0x740 != NULL) {
		GolVec3 position;
		m_unk0x740->SetDistanceRangeWithMinSquared(g_unk0x004b0430 * g_unk0x004b0430, g_unk0x004b0434);
		m_unk0x740->Play(TRUE);
		m_unk0x13c->VTable0x04(&position);
		m_unk0x740->SetPositionAndVelocity(position, m_unk0x008);
	}

	return m_unk0x740;
}

// FUNCTION: LEGORACERS 0x0042b060 FOLDED
void RaceState::Racer::Field0x3e8::FUN_0042b060()
{
	if (m_soundResource != NULL) {
		if (m_soundResource->VTable0x0c()) {
			m_soundResource->VTable0x08();
		}

		m_unk0x158->FUN_00443c10(m_soundResource);
		m_unk0x73c = -1;
		m_soundResource = NULL;
		m_unk0x738 = 0;
	}
}

// FUNCTION: LEGORACERS 0x00440950
RaceState::Racer::Field0x3e8Base0xd0::Field0x3e8Base0xd0()
{
	FUN_00440970();
}

// FUNCTION: LEGORACERS 0x00440970 FOLDED
void RaceState::Racer::Field0x3e8Base0xd0::FUN_00440970()
{
	m_unk0x004 = NULL;
	m_unk0x014.m_x = 0.0f;
	m_unk0x014.m_y = 0.0f;
	m_unk0x014.m_z = 0.0f;
	m_unk0x020.m_x = 0.0f;
	m_unk0x020.m_y = 0.0f;
	m_unk0x020.m_z = 0.0f;

	m_unk0x098.m_x = 0.0f;
	m_unk0x098.m_y = 0.0f;
	m_unk0x098.m_z = 0.0f;
	m_unk0x0a4.m_x = 0.0f;
	m_unk0x0a4.m_y = 0.0f;
	m_unk0x0a4.m_z = 0.0f;
	m_unk0x0b0.m_x = 0.0f;
	m_unk0x0b0.m_y = 0.0f;
	m_unk0x0b0.m_z = 0.0f;
	m_unk0x0bc.m_x = 0.0f;
	m_unk0x0bc.m_y = 0.0f;
	m_unk0x0bc.m_z = 0.0f;

	m_unk0x0c8 = 1.0f;
	m_unk0x0cc = 1.0f;
}

// FUNCTION: LEGORACERS 0x004409f0 FOLDED
void RaceState::Racer::Field0x3e8Base0xd0::FUN_004409f0(GolOrientedEntity* p_unk0x04, LegoFloat p_unk0x08)
{
	if (m_unk0x004 != NULL) {
		FUN_00440970();
	}

	LegoFloat inverseMass = p_unk0x08;
	inverseMass = 1.0f / inverseMass;
	m_unk0x004 = p_unk0x04;
	m_unk0x0c8 = p_unk0x08;
	m_unk0x008.m_x = 0.0f;
	m_unk0x008.m_y = 0.0f;
	m_unk0x008.m_z = 0.0f;
	m_unk0x0cc = inverseMass;
	VTable0x00();
	FUN_00440a60();
}

// FUNCTION: LEGORACERS 0x00440a50 FOLDED
void RaceState::Racer::Field0x3e8Base0xd0::FUN_00440a50()
{
	FUN_00440970();
}

// FUNCTION: LEGORACERS 0x00440a60 FOLDED
void RaceState::Racer::Field0x3e8Base0xd0::FUN_00440a60()
{
	m_unk0x004->FUN_00410f30(m_unk0x050, &m_unk0x074);
}

// FUNCTION: LEGORACERS 0x00440a80 FOLDED
void RaceState::Racer::Field0x3e8Base0xd0::FUN_00440a80()
{
	LegoFloat value = m_unk0x074.m_m[2][0] * m_unk0x0a4.m_z;
	value += m_unk0x074.m_m[1][0] * m_unk0x0a4.m_y;
	m_unk0x098.m_x = value + m_unk0x074.m_m[0][0] * m_unk0x0a4.m_x;

	value = m_unk0x074.m_m[2][1] * m_unk0x0a4.m_z;
	value += m_unk0x074.m_m[1][1] * m_unk0x0a4.m_y;
	m_unk0x098.m_y = value + m_unk0x074.m_m[0][1] * m_unk0x0a4.m_x;

	value = m_unk0x074.m_m[2][2] * m_unk0x0a4.m_z;
	value += m_unk0x074.m_m[1][2] * m_unk0x0a4.m_y;
	m_unk0x098.m_z = value + m_unk0x074.m_m[0][2] * m_unk0x0a4.m_x;
}

// FUNCTION: LEGORACERS 0x00440b10
void RaceState::Racer::Field0x3e8Base0x74c::FUN_00440b10(GolVec3* p_unk0x04)
{
	m_unk0x0b0.m_x += p_unk0x04->m_x;
	m_unk0x0b0.m_y += p_unk0x04->m_y;
	m_unk0x0b0.m_z += p_unk0x04->m_z;
}

// FUNCTION: LEGORACERS 0x00440b50
void RaceState::Racer::Field0x3e8Base0x74c::FUN_00440b50(GolVec3* p_unk0x04, GolVec3* p_unk0x08)
{
	GolVec3 offset;
	offset.m_x = p_unk0x08->m_x - m_unk0x020.m_x;
	offset.m_y = p_unk0x08->m_y - m_unk0x020.m_y;
	offset.m_z = p_unk0x08->m_z - m_unk0x020.m_z;

	GolVec3 torque;
	LegoFloat value = offset.m_y;
	value *= p_unk0x04->m_z;
	LegoFloat crossValue = p_unk0x04->m_y;
	crossValue *= offset.m_z;
	torque.m_x = value - crossValue;

	value = offset.m_z;
	value *= p_unk0x04->m_x;
	crossValue = p_unk0x04->m_z;
	crossValue *= offset.m_x;
	torque.m_y = value - crossValue;

	value = p_unk0x04->m_y;
	value *= offset.m_x;
	crossValue = offset.m_y;
	crossValue *= p_unk0x04->m_x;
	torque.m_z = value - crossValue;

	m_unk0x0bc.m_x += torque.m_x;
	m_unk0x0bc.m_y += torque.m_y;
	m_unk0x0bc.m_z += torque.m_z;
}

// FUNCTION: LEGORACERS 0x00440bd0
void RaceState::Racer::Field0x3e8Base0x74c::FUN_00440bd0(GolVec3* p_unk0x04)
{
	GolVec3 local;
	m_unk0x004->VTable0x38(*p_unk0x04, &local);

	GolVec3 transformed;
	transformed.m_x = m_unk0x02c.m_m[0][0];
	transformed.m_x *= local.m_x;
	transformed.m_y = m_unk0x02c.m_m[0][1];
	transformed.m_y *= local.m_x;
	transformed.m_z = m_unk0x02c.m_m[0][2];
	transformed.m_z *= local.m_x;

	LegoFloat value = m_unk0x02c.m_m[1][0];
	value *= local.m_y;
	transformed.m_x += value;
	value = m_unk0x02c.m_m[1][1];
	value *= local.m_y;
	transformed.m_y += value;
	value = m_unk0x02c.m_m[1][2];
	value *= local.m_y;
	transformed.m_z += value;

	value = m_unk0x02c.m_m[2][0];
	value *= local.m_z;
	transformed.m_x += value;
	value = m_unk0x02c.m_m[2][1];
	value *= local.m_z;
	transformed.m_y += value;
	value = m_unk0x02c.m_m[2][2];
	value *= local.m_z;
	transformed.m_z += value;

	GolVec3 world;
	m_unk0x004->VTable0x34(transformed, &world);
	m_unk0x0a4.m_x += world.m_x;
	m_unk0x0a4.m_y += world.m_y;
	m_unk0x0a4.m_z += world.m_z;
}

// FUNCTION: LEGORACERS 0x00440cb0
void RaceState::Racer::Field0x3e8Base0x74c::FUN_00440cb0(GolVec3* p_unk0x04, GolVec3* p_unk0x08)
{
	GolVec3 offset;
	offset.m_x = p_unk0x08->m_x - m_unk0x020.m_x;
	offset.m_y = p_unk0x08->m_y - m_unk0x020.m_y;
	offset.m_z = p_unk0x08->m_z - m_unk0x020.m_z;

	GolVec3 axis;
	LegoFloat value = offset.m_y;
	value *= p_unk0x04->m_z;
	LegoFloat crossValue = p_unk0x04->m_y;
	crossValue *= offset.m_z;
	axis.m_x = value - crossValue;

	value = offset.m_z;
	value *= p_unk0x04->m_x;
	crossValue = p_unk0x04->m_z;
	crossValue *= offset.m_x;
	axis.m_y = value - crossValue;

	value = p_unk0x04->m_y;
	value *= offset.m_x;
	crossValue = offset.m_y;
	crossValue *= p_unk0x04->m_x;
	axis.m_z = value - crossValue;
	GolMath::NormalizeVector3(axis, &axis);

	LegoFloat dot = axis.m_z;
	dot *= m_unk0x0a4.m_z;
	value = m_unk0x0a4.m_y;
	value *= axis.m_y;
	dot += value;
	value = axis.m_x;
	value *= m_unk0x0a4.m_x;
	dot += value;

	if (dot >= 0.0f) {
		GolVec3 scaled;
		scaled.m_x = axis.m_x * dot;
		scaled.m_y = axis.m_y * dot;
		scaled.m_z = axis.m_z * dot;
		m_unk0x0a4.m_x -= scaled.m_x;
		m_unk0x0a4.m_y -= scaled.m_y;
		m_unk0x0a4.m_z -= scaled.m_z;
	}
}

// FUNCTION: LEGORACERS 0x00440da0
void RaceState::Racer::Field0x3e8Base0x74c::FUN_00440da0(GolVec3* p_unk0x04)
{
	LegoFloat dot = m_unk0x0a4.m_z * p_unk0x04->m_z;
	dot += m_unk0x0a4.m_y * p_unk0x04->m_y;
	dot += m_unk0x0a4.m_x * p_unk0x04->m_x;
	GolVec3 scaled;
	scaled.m_x = dot * p_unk0x04->m_x;
	scaled.m_y = p_unk0x04->m_y;
	scaled.m_y *= dot;
	scaled.m_z = dot * p_unk0x04->m_z;
	m_unk0x0a4.m_x -= scaled.m_x;
	m_unk0x0a4.m_y -= scaled.m_y;
	m_unk0x0a4.m_z -= scaled.m_z;
}

// FUNCTION: LEGORACERS 0x00440e10 FOLDED
void RaceState::Racer::Field0x3e8Base0xd0::VTable0x04(LegoS32 p_elapsedMs)
{
	FUN_00440a80();

	LegoFloat elapsed = static_cast<LegoFloat>(p_elapsedMs);
	{
		GolVec3 linearDelta;
		linearDelta.m_x = m_unk0x0b0.m_x;
		linearDelta.m_x *= elapsed;
		linearDelta.m_x *= m_unk0x0cc;
		linearDelta.m_y = m_unk0x0b0.m_y;
		linearDelta.m_y *= elapsed;
		linearDelta.m_y *= m_unk0x0cc;
		linearDelta.m_z = m_unk0x0b0.m_z;
		linearDelta.m_z *= elapsed;
		linearDelta.m_z *= m_unk0x0cc;

		LegoFloat halfElapsed = elapsed * 0.5f;

		GolVec3 position;
		m_unk0x004->VTable0x04(&position);
		LegoFloat velocityTerm = m_unk0x008.m_x;
		velocityTerm *= elapsed;
		LegoFloat accelerationTerm = halfElapsed;
		accelerationTerm *= linearDelta.m_x;
		position.m_x += velocityTerm + accelerationTerm;

		velocityTerm = m_unk0x008.m_y;
		velocityTerm *= elapsed;
		accelerationTerm = halfElapsed;
		accelerationTerm *= linearDelta.m_y;
		position.m_y += velocityTerm + accelerationTerm;

		velocityTerm = m_unk0x008.m_z;
		velocityTerm *= elapsed;
		accelerationTerm = halfElapsed;
		accelerationTerm *= linearDelta.m_z;
		position.m_z += velocityTerm + accelerationTerm;
		m_unk0x004->VTable0x08(position);

		if (linearDelta.m_x == 0.0f && linearDelta.m_y == 0.0f && linearDelta.m_z == 0.0f) {
			const LegoFloat velocityThreshold = 9.9999997e-05f;

			if (m_unk0x008.m_x < velocityThreshold && -velocityThreshold < m_unk0x008.m_x) {
				m_unk0x008.m_x = 0.0f;
			}
			if (m_unk0x008.m_y < velocityThreshold && -velocityThreshold < m_unk0x008.m_y) {
				m_unk0x008.m_y = 0.0f;
			}
			if (m_unk0x008.m_z < velocityThreshold && -velocityThreshold < m_unk0x008.m_z) {
				m_unk0x008.m_z = 0.0f;
			}
		}

		m_unk0x008.m_x += linearDelta.m_x;
		m_unk0x008.m_y += linearDelta.m_y;
		m_unk0x008.m_z += linearDelta.m_z;
	}

	LegoFloat angularStepZ;
	LegoFloat angularStepY;
	LegoFloat angularStepX;
	angularStepX = m_unk0x098.m_x;
	angularStepX *= elapsed;
	angularStepY = m_unk0x098.m_y;
	angularStepY *= elapsed;
	angularStepZ = m_unk0x098.m_z;
	angularStepZ *= elapsed;

	GolVec3 right;
	GolVec3 forward;
	m_unk0x004->VTable0x48(&right, &forward);

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
	GolOrientedEntity* entity = m_unk0x004;
	entity->VTable0x40(newRight, newForward);

	LegoFloat angularDeltaY = m_unk0x0bc.m_y;
	angularDeltaY *= elapsed;
	LegoFloat angularDeltaZ = m_unk0x0bc.m_z;
	angularDeltaZ *= elapsed;
	LegoFloat velocityTerm = elapsed;
	velocityTerm *= m_unk0x0bc.m_x;
	m_unk0x0a4.m_x += velocityTerm;
	m_unk0x0a4.m_y += angularDeltaY;
	m_unk0x0a4.m_z += angularDeltaZ;

	if (m_unk0x0bc.m_x == 0.0f && m_unk0x0bc.m_y == 0.0f && m_unk0x0bc.m_z == 0.0f) {
		LegoFloat angularStepLengthSq =
			angularStepX * angularStepX + angularStepY * angularStepY + angularStepZ * angularStepZ;
		if (angularStepLengthSq < 0.00060000003f) {
			m_unk0x098.m_x = 0.0f;
			m_unk0x098.m_y = 0.0f;
			m_unk0x098.m_z = 0.0f;
			m_unk0x0a4.m_x = 0.0f;
			m_unk0x0a4.m_y = 0.0f;
			m_unk0x0a4.m_z = 0.0f;
		}
	}

	m_unk0x0b0.m_x = 0.0f;
	m_unk0x0b0.m_y = 0.0f;
	m_unk0x0b0.m_z = 0.0f;
	m_unk0x0bc.m_x = 0.0f;
	m_unk0x0bc.m_y = 0.0f;
	m_unk0x0bc.m_z = 0.0f;
}

// FUNCTION: LEGORACERS 0x00441190
void RaceState::Racer::Field0x3e8Base0x74c::FUN_00441190(GolVec3* p_unk0x04)
{
	::memcpy(&m_unk0x014, p_unk0x04, sizeof(m_unk0x014));
	m_unk0x004->VTable0x2c(m_unk0x014, &m_unk0x020);
}

// FUNCTION: LEGORACERS 0x004411c0 FOLDED
GolOrientedEntity* RaceState::Racer::Field0x3e8Base0xd0::VTable0x08()
{
	return m_unk0x004;
}

// FUNCTION: LEGORACERS 0x004411d0
RaceState::Racer::Field0x3e8Base0xe4::Field0x3e8Base0xe4()
{
	m_unk0x0d0 = 0.0f;
	m_unk0x0d4 = 0.0f;
	m_unk0x0d8 = 0.0f;
	m_unk0x0dc = 0.0f;
	m_racer = NULL;
}

// FUNCTION: LEGORACERS 0x00441210
void RaceState::Racer::Field0x3e8Base0xe4::FUN_00441210(
	GolOrientedEntity* p_unk0x04,
	LegoFloat p_unk0x08,
	LegoFloat p_unk0x0c,
	LegoFloat p_unk0x10,
	LegoFloat p_unk0x14
)
{
	m_unk0x0d0 = p_unk0x0c;
	m_unk0x0d4 = p_unk0x10;
	m_unk0x0d8 = p_unk0x14;
	m_unk0x0dc = 1.0f;
	m_racer = NULL;
	FUN_004409f0(p_unk0x04, p_unk0x08);
}

// FUNCTION: LEGORACERS 0x00441260 FOLDED
void RaceState::Racer::Field0x3e8Base0xe4::VTable0x00()
{
	LegoFloat xSquared = m_unk0x0d0 * m_unk0x0d0;
	LegoFloat ySquared = m_unk0x0d4 * m_unk0x0d4;
	LegoFloat zSquared = m_unk0x0d8 * m_unk0x0d8;
	LegoFloat scaledMass = m_unk0x0c8 / m_unk0x0d0;

	m_unk0x02c.m_m[0][1] = 0.0f;
	m_unk0x02c.m_m[0][2] = 0.0f;
	m_unk0x02c.m_m[1][0] = 0.0f;
	m_unk0x02c.m_m[1][2] = 0.0f;
	m_unk0x02c.m_m[2][0] = 0.0f;
	m_unk0x02c.m_m[2][1] = 0.0f;
	m_unk0x050.m_m[0][1] = 0.0f;
	m_unk0x050.m_m[0][2] = 0.0f;
	m_unk0x050.m_m[1][0] = 0.0f;
	m_unk0x050.m_m[1][2] = 0.0f;
	m_unk0x050.m_m[2][0] = 0.0f;
	m_unk0x050.m_m[2][1] = 0.0f;

	LegoFloat xInertia = scaledMass * (zSquared + ySquared) * g_unk0x004b0b90;
	m_unk0x02c.m_m[0][0] = xInertia;
	LegoFloat yInertia = (m_unk0x0c8 / m_unk0x0d4) * (zSquared + xSquared) * g_unk0x004b0b90;
	m_unk0x02c.m_m[1][1] = yInertia;
	LegoFloat zInertia = (m_unk0x0c8 / m_unk0x0d8) * (ySquared + xSquared) * g_unk0x004b0b90;
	m_unk0x02c.m_m[2][2] = zInertia;
	m_unk0x050.m_m[0][0] = 1.0f / xInertia;
	m_unk0x050.m_m[1][1] = 1.0f / yInertia;
	m_unk0x050.m_m[2][2] = 1.0f / zInertia;
}

// FUNCTION: LEGORACERS 0x00444b10
RaceState::Racer::Field0x3e8Base0x74c::Field0x3e8Base0x74c()
{
	FUN_00444b40();
}

// FUNCTION: LEGORACERS 0x00444b40
void RaceState::Racer::Field0x3e8Base0x74c::FUN_00444b40()
{
	m_unk0x13c = NULL;
	::memset(m_unk0x140, 0, sizeof(m_unk0x140));
	m_unk0x154 = 0;
	m_unk0x158 = NULL;
	m_unk0x164 = 0;
	m_unk0x160 = g_unk0x004b0ce4;
	m_unk0x168.m_x = 1.0f;
	m_unk0x168.m_y = 0.0f;
	m_unk0x168.m_z = 0.0f;
	m_unk0x174.m_x = 0.0f;
	m_unk0x174.m_y = 0.0f;
	m_unk0x174.m_z = 0.0f;
	m_unk0x180.m_x = 0.0f;
	m_unk0x180.m_y = 0.0f;
	m_unk0x180.m_z = 0.0f;
	m_unk0x630.m_x = 0;
	m_unk0x630.m_y = 0;
	m_unk0x630.m_z = 0;
	m_unk0x63c.m_x = 0;
	m_unk0x63c.m_y = 0;
	m_unk0x63c.m_z = 0;
	m_unk0x18c = 0;
	m_unk0x190 = 0;
	m_unk0x654 = -10.95f;
	m_unk0x194 = g_unk0x004b0cf8;
	m_unk0x60c.m_x = 0.0f;
	m_unk0x60c.m_y = 0.0f;
	m_unk0x60c.m_z = 0.0f;
	m_unk0x5f8.m_x = 1.0f;
	m_unk0x5f8.m_y = 0.0f;
	m_unk0x5f8.m_z = 0.0f;
	m_unk0x618 = 0.0f;
	m_unk0x604 = 0;
	m_unk0x5f0 = 0;
	m_unk0x6d0 = 0;
	m_unk0x628 = 0;
	m_unk0x62c = 0;
	m_unk0x648 = 0;
	m_unk0x64c = 0;
	m_unk0x650 = 0;
	m_unk0x690.m_x = 0.0f;
	m_unk0x690.m_y = 0.0f;
	m_unk0x690.m_z = 0.0f;
	m_unk0x3ec = 0;
	m_unk0x3f0 = 0;

	for (LegoU32 i = 0; i < sizeOfArray(m_unk0x370); i++) {
		m_unk0x370[i].m_x = 0.0f;
		m_unk0x370[i].m_y = 0.0f;
		m_unk0x370[i].m_z = 0.0f;
		m_unk0x3a0[i].m_x = 0.0f;
		m_unk0x3a0[i].m_y = 0.0f;
		m_unk0x3a0[i].m_z = 0.0f;
		m_unk0x3d0[i] = 0;
	}

	::memset(m_unk0x198, 0, sizeof(m_unk0x198));
	::memset(m_unk0x3f4, 0, sizeof(m_unk0x3f4));
	m_unk0x5d4 = 0;
	m_unk0x36c = 0;
	m_unk0x5d8 = 0;
	m_unk0x5dc = 0;
	m_unk0x5e0 = 0;
	m_unk0x5e4 = 0;
	m_unk0x5e8 = 0;
	m_flags0x6c0 = 0;
	m_unk0x6c4 = 1.0f;
	m_unk0x6c8 = -1.0f;
	m_unk0x6cc = 3.1415927f;
	m_unk0x6e4 = NULL;
	m_unk0x6e8 = NULL;
	m_unk0x6ec = 1;
	m_unk0x6dc = 0;
	m_unk0x658 = 0;
	m_unk0x65c = g_unk0x004b0d20;
	m_unk0x660 = g_unk0x004b0d24;
	m_unk0x67c = 0;
	m_unk0x680 = 0;
	m_unk0x6d4 = 0;
	LegoU32 unk0x6d8 = g_unk0x004b0d80;
	m_unk0x6e0 = 0;
	m_unk0x6d8 = unk0x6d8;
	VTable0x18(g_unk0x004b0cf0);
	m_unk0x5f4 = 1.0f;
}

// FUNCTION: LEGORACERS 0x00444d90
void RaceState::Racer::Field0x3e8Base0x74c::FUN_00444d90(
	GolAnimatedEntity* p_unk0x04,
	GolBoundedEntity* p_unk0x08,
	GolBoundedEntity* p_unk0x0c,
	Field0x004* p_unk0x10,
	LegoFloat p_unk0x14,
	LegoFloat p_unk0x18,
	LegoFloat p_unk0x1c,
	LegoFloat p_unk0x20
)
{
	Field0x3e8Base0x74c* field = this;

	if (field->m_unk0x004 != NULL) {
		field->FUN_00444e90();
	}

	field->m_unk0x154 = 1;
	field->m_unk0x140[0] = p_unk0x08;

	if (p_unk0x0c != NULL) {
		field->m_unk0x140[1] = p_unk0x0c;
		field->m_unk0x154 = 2;
	}

	field->m_unk0x158 = p_unk0x10;
	field->m_unk0x13c = p_unk0x04;

	GolOrientedEntity* entity = &field->m_unk0x0e4;
	entity->CopyOrientationFrom(*p_unk0x04);
	entity->CopyPositionFrom(*p_unk0x04);
	field->FUN_00441210(entity, p_unk0x14, p_unk0x18, p_unk0x1c, p_unk0x20);

	LegoFloat scaledAngle = p_unk0x14;
	scaledAngle *= 0.001f;
	const GolMatrix3& orientation = entity->GetOrientation();
	field->m_unk0x168.m_x = orientation.m_m[0][0];
	field->m_unk0x168.m_y = orientation.m_m[0][1];
	field->m_unk0x168.m_z = orientation.m_m[0][2];
	scaledAngle *= 0.001f;
	field->m_unk0x15c = scaledAngle;
}

// FUNCTION: LEGORACERS 0x00444e90
void RaceState::Racer::Field0x3e8Base0x74c::FUN_00444e90()
{
	FUN_00444b40();
	FUN_00440a50();

	if (m_unk0x6e4) {
		m_unk0x158->FUN_00443c10(m_unk0x6e4);
		m_unk0x6e4 = NULL;
	}

	if (m_unk0x6e8) {
		m_unk0x158->FUN_00443c10(m_unk0x6e8);
		m_unk0x6e8 = NULL;
	}
}

// FUNCTION: LEGORACERS 0x00444ef0
void RaceState::Racer::Field0x3e8Base0x74c::VTable0x04(LegoS32 p_elapsedMs)
{
	LegoU32 elapsedMs = p_elapsedMs;
	LegoBool32 recoveredCollision = FALSE;
	GolVec3 direction;
	GolVec3 position;

	FUN_00447880();

	if (m_flags0x6c0 & c_flags0x6c0Bit7) {
		if (elapsedMs >= m_unk0x6e0) {
			VTable0x3c();
		}
		else {
			m_unk0x6e0 -= elapsedMs;
		}
	}

	LegoU32 flags = m_flags0x6c0;
	if (flags & c_flags0x6c0Bit1) {
		if (flags & c_flags0x6c0Bit2) {
			m_flags0x6c0 = flags & ~c_flags0x6c0Bit2;
		}
		else {
			LegoU32 timer = m_unk0x5e0;
			if (elapsedMs >= timer) {
				if (timer != 0) {
					elapsedMs = timer;
					m_unk0x5e0 = 0;
				}
				else {
					VTable0x2c();
				}
			}
			else {
				m_unk0x5e0 = timer - elapsedMs;
			}
		}
	}
	else {
		LegoU32 timer = m_unk0x5e0;
		if (elapsedMs >= timer) {
			const GolVec3& forward = m_unk0x0e4.GetOrientation().m_rows[2];
			m_unk0x5e0 = 0;
			direction.m_x = forward.m_x;
			direction.m_y = forward.m_y;
			direction.m_z = forward.m_z;
			FUN_00440da0(&direction);
			m_flags0x6c0 &= ~c_flags0x6c0Bit11;
		}
		else {
			m_unk0x5e0 = timer - elapsedMs;
		}
	}

	if (elapsedMs > m_unk0x5e4) {
		m_unk0x5e4 = 0;
	}
	else {
		m_unk0x5e4 -= elapsedMs;
	}

	if (m_unk0x5d8 != 0) {
		if (elapsedMs >= m_unk0x5d8) {
			const GolVec3& right = m_unk0x0e4.GetOrientation().m_rows[0];
			m_unk0x5d8 = 0;
			direction.m_x = right.m_x;
			direction.m_y = right.m_y;
			direction.m_z = right.m_z;
			FUN_00440da0(&direction);
		}
		else {
			m_unk0x5d8 -= elapsedMs;
		}
	}

	if (m_unk0x5dc != 0) {
		if (elapsedMs >= m_unk0x5dc) {
			const GolVec3& up = m_unk0x0e4.GetOrientation().m_rows[1];
			m_unk0x5dc = 0;
			direction.m_x = up.m_x;
			direction.m_y = up.m_y;
			direction.m_z = up.m_z;
			FUN_00440da0(&direction);
		}
		else {
			m_unk0x5dc -= elapsedMs;
		}
	}

	if (m_flags0x6c0 & c_flags0x6c0Bit3) {
		FUN_00448840();
	}

	m_unk0x3f0 = elapsedMs;
	FUN_004474c0();

	for (;;) {
		if (m_unk0x3ec == 0) {
			if (elapsedMs == 0) {
				break;
			}
		}

		if (elapsedMs != 0) {
			FUN_00445500();
			Field0x3e8Base0xd0::VTable0x04(elapsedMs);
			FUN_00445d10();

			if (m_flags0x6c0 & c_flags0x6c0Bit3) {
				FUN_004464a0(elapsedMs);
				FUN_004465c0(elapsedMs);
			}
			else {
				FUN_00445dc0(elapsedMs);
			}

			FUN_00446fd0(elapsedMs);
			FUN_00447330();
			VTable0x10();
			m_unk0x0e4.VTable0x2c(m_unk0x014, &m_unk0x020);
			FUN_00440a60();
		}

		if (m_unk0x3ec != 0) {
			if (elapsedMs != 0) {
				LegoU32 result = FUN_004478b0(elapsedMs, !(m_flags0x6c0 & c_flags0x6c0Bit12));
				if (m_unk0x3ec != 0) {
					elapsedMs = result;
					continue;
				}
			}

			FUN_00447cf0();
			FUN_00447330();
			recoveredCollision = TRUE;
			FUN_00447880();
			FUN_004474c0();
			m_unk0x3f0 -= elapsedMs;
			elapsedMs = m_unk0x3f0;
			continue;
		}

		elapsedMs = FUN_004478b0(elapsedMs, !(m_flags0x6c0 & c_flags0x6c0Bit12));
		if (elapsedMs != 0) {
			continue;
		}

		if (!recoveredCollision) {
			continue;
		}

		break;
	}

	if (recoveredCollision) {
		m_unk0x3ec = TRUE;
	}

	if (m_unk0x36c == 0) {
		m_unk0x6dc += p_elapsedMs;
	}
	else {
		m_unk0x6dc = 0;
	}

	m_unk0x0e4.VTable0x04(&position);

	if (m_sound6e8 != NULL) {
		m_sound6e8->SetPosition(position);
		m_sound6e8->SetVelocity(m_unk0x008);

		if (m_flags0x6c0 & c_flags0x6c0Bit10) {
			m_sound6e8->SetFrequencyScale((m_float0x6d8 * 0.5f + 1.4f) - ((0.17f - m_unk0x618) * g_ghostSpeedScale));
		}
		else {
			m_sound6e8->SetFrequencyScale(1.4f - ((0.17f - m_unk0x618) * g_ghostSpeedScale));
		}
	}

	if (m_sound6e4 != NULL) {
		m_sound6e4->SetPosition(position);
	}

	FUN_004452b0(p_elapsedMs);
}

// FUNCTION: LEGORACERS 0x004452b0
void RaceState::Racer::Field0x3e8Base0x74c::FUN_004452b0(LegoS32 p_elapsedMs)
{
	LegoFloat targetAngle;
	LegoFloat minTargetAngle;

	if (m_flags0x6c0 & c_flags0x6c0Bit3) {
		targetAngle = -m_unk0x680;
	}
	else if (m_flags0x6c0 & c_flags0x6c0Bit10) {
		if (m_unk0x64c <= -g_unk0x004b0cd0 || m_unk0x64c >= g_unk0x004b0cd0) {
			targetAngle = m_unk0x64c;
			targetAngle = 1.0f / targetAngle;
			targetAngle = -targetAngle;
			targetAngle *= g_unk0x004b0cd0;
			targetAngle *= m_float0x6d8;

			LegoFloat speedScale = m_unk0x604;
			speedScale *= g_floatConst1000;
			speedScale /= m_unk0x608;
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

	if (targetAngle < m_unk0x6d4) {
		m_unk0x6d4 -= static_cast<LegoFloat>(p_elapsedMs) * 0.0020000001f;
		if (m_unk0x6d4 < targetAngle) {
			m_unk0x6d4 = targetAngle;
		}
	}
	else if (targetAngle > m_unk0x6d4) {
		m_unk0x6d4 += static_cast<LegoFloat>(p_elapsedMs) * 0.0020000001f;
		if (m_unk0x6d4 > targetAngle) {
			m_unk0x6d4 = targetAngle;
		}
	}

	LegoFloat angleMagnitude = m_unk0x6d4;
	if (angleMagnitude < 0.0f) {
		angleMagnitude = -angleMagnitude;
	}

	if (angleMagnitude != 0.0f) {
		GolVec3 position;
		GolVec3 right;
		GolVec3 forward;
		GolVec3 rotatedForward;

		m_unk0x0e4.VTable0x48(&right, &forward);
		m_unk0x0e4.VTable0x04(&position);

		LegoFloat offset = static_cast<LegoFloat>(tan(angleMagnitude)) * (m_unk0x364 * 0.5f);
		GolMath::FUN_004496a0(&forward, &rotatedForward, &right, m_unk0x6d4);
		position.m_z += offset;
		m_unk0x13c->VTable0x40(right, rotatedForward);
		m_unk0x13c->VTable0x08(position);
	}
	else {
		GolOrientedEntity* entity = m_unk0x13c;
		entity->CopyOrientationFrom(m_unk0x0e4);
		entity->CopyPositionFrom(m_unk0x0e4);
	}
}

// FUNCTION: LEGORACERS 0x00445500
void RaceState::Racer::Field0x3e8Base0x74c::FUN_00445500()
{
	LegoFloat steeringAmount = 0.0f;
	GolVec3 force;

	LegoFloat baseForce = -m_unk0x160;
	baseForce *= m_unk0x15c;
	LegoU8 flags0x6c0 = static_cast<LegoU8>(m_flags0x6c0);
	m_unk0x650 = 0.0f;
	m_unk0x164 = baseForce;

	if (flags0x6c0 & c_flags0x6c0Bit0) {
		const GolVec3& right = m_unk0x0e4.GetOrientation().m_rows[0];
		steeringAmount = right.m_x * m_unk0x5f8.m_x + right.m_y * m_unk0x5f8.m_y + right.m_z * m_unk0x5f8.m_z;
		if (steeringAmount <= 0.0f) {
			FUN_00448070();
		}
	}

	if (m_unk0x36c == 0) {
		force.m_x = 0.0f;
		force.m_z = m_unk0x164 * 4.0f;
		force.m_y = 0.0f;
		FUN_00440b10(&force);

		LegoFloat scale = m_unk0x628 * m_unk0x15c;
		force.m_x = m_unk0x168.m_x * scale;
		force.m_y = m_unk0x168.m_y;
		force.m_y *= scale;
		force.m_z = m_unk0x168.m_z;
		force.m_z *= scale;
		LegoFloat forwardLimit = -m_unk0x164;
		if (force.m_z > forwardLimit) {
			force.m_z = forwardLimit;
		}
		FUN_00440b10(&force);

		if (m_unk0x64c != 0.0f && !(m_flags0x6c0 & c_flags0x6c0Bit11)) {
			FUN_00445c30(m_unk0x618 / m_unk0x64c, 200);
		}
	}
	else {
		LegoFloat average0x054 = FUN_00448990();
		LegoFloat average0x058 = FUN_004489c0();
		LegoFloat forceMagnitude = static_cast<LegoFloat>(
			sqrt(m_unk0x180.m_z * m_unk0x180.m_z + m_unk0x180.m_y * m_unk0x180.m_y + m_unk0x180.m_x * m_unk0x180.m_x)
		);
		LegoFloat forceThreshold = m_unk0x160;
		forceThreshold *= m_unk0x15c;
		forceThreshold *= average0x054;
		if (forceMagnitude > forceThreshold) {
			FUN_00440b10(&m_unk0x180);
		}

		if (m_flags0x6c0 & c_flags0x6c0Bit3) {
			Field0x198* entry = m_unk0x198;
			GolVec3* axlePoint = &m_unk0x664;
			for (LegoU32 i = 0; i < 2; i++) {
				if (entry->m_flags0x048 & 1) {
					if (m_unk0x36c < 1) {
						FUN_00440b50(&entry->m_unk0x000, axlePoint);
					}

					FUN_00440cb0(&m_unk0x174, &m_unk0x664 + (i == 0));
				}
				entry++;
				axlePoint++;
			}
		}
		else if (m_unk0x5d8 == 0 && m_unk0x5dc == 0) {
			Field0x198* entry = m_unk0x198;
			const LegoS32* entryIndex = g_raceStateField0x3e8MirrorEntryIndices;
			while (entryIndex < &g_raceStateField0x3e8MirrorEntryIndices[sizeOfArray(m_unk0x198)]) {
				if (entry->m_flags0x048 & 1) {
					if (m_unk0x36c < 3) {
						FUN_00440b50(&entry->m_unk0x000, &entry->m_unk0x00c);
					}

					FUN_00440cb0(&m_unk0x174, &m_unk0x198[*entryIndex].m_unk0x00c);
				}
				entry++;
				entryIndex++;
			}
		}

		LegoFloat contactScale;
		if (!(m_flags0x6c0 & (c_flags0x6c0Bit0 | c_flags0x6c0Bit1))) {
			contactScale = 1.0f;
		}
		else {
			LegoFloat scale = m_unk0x160;
			scale *= m_unk0x15c;
			scale *= average0x058;
			scale *= m_unk0x6d0;
			scale = -scale;
			force.m_x = m_unk0x5f8.m_x * scale;
			force.m_y = m_unk0x5f8.m_y;
			force.m_y *= scale;
			force.m_z = m_unk0x5f8.m_z;
			force.m_z *= scale;
			FUN_00440b10(&force);
			contactScale = 1.0f - m_unk0x6d0;
		}

		if (!(m_flags0x6c0 & c_flags0x6c0Bit1) && !(m_flags0x6c0 & c_flags0x6c0Bit11)) {
			LegoFloat scale = m_unk0x0c8 * -0.0099999998f;
			scale *= contactScale;
			force.m_x = m_unk0x61c.m_x * scale;
			force.m_y = m_unk0x61c.m_y;
			force.m_y *= scale;
			force.m_z = m_unk0x61c.m_z;
			force.m_z *= scale;
			FUN_00440b10(&force);

			if (m_unk0x628 != 0.0f) {
				scale = m_unk0x628 * m_unk0x15c;
				if (m_unk0x36c >= 3 && !(m_flags0x6c0 & c_flags0x6c0Bit0)) {
					const GolVec3& right = m_unk0x0e4.GetOrientation().m_rows[0];
					force.m_x = right.m_x * scale;
					force.m_y = right.m_y;
					force.m_y *= scale;
					force.m_z = right.m_z;
					force.m_z *= scale;
				}
				else {
					force.m_x = m_unk0x168.m_x * scale;
					force.m_y = m_unk0x168.m_y;
					force.m_y *= scale;
					force.m_z = m_unk0x168.m_z;
					force.m_z *= scale;
				}
				FUN_00440b10(&force);
			}
			else {
				scale = m_unk0x0c8 * -0.001f;
				force.m_x = m_unk0x60c.m_x * scale;
				force.m_y = m_unk0x60c.m_y;
				force.m_y *= scale;
				force.m_z = m_unk0x60c.m_z;
				force.m_z *= scale;
				FUN_00440b10(&force);
			}

			if (m_unk0x64c != 0.0f) {
				force.m_x = -m_unk0x168.m_y;
				force.m_y = m_unk0x168.m_x;
				force.m_z = 0.0f;
				GolMath::NormalizeVector3(force, &force);

				scale = m_unk0x0c8;
				scale *= m_unk0x618;
				scale *= m_unk0x618;
				scale /= m_unk0x64c;
				m_unk0x648 = scale;
				force.m_x = force.m_x * scale;
				force.m_y *= scale;
				force.m_z *= scale;
				FUN_00440b10(&force);

				if (m_flags0x6c0 & c_flags0x6c0Bit0) {
					if (steeringAmount >= m_unk0x6c8) {
						scale = m_unk0x618 / m_unk0x64c;
						m_unk0x650 = scale;
						steeringAmount = m_unk0x6c4;
						steeringAmount *= scale;
					}
					else {
						steeringAmount = 0.0f;
					}
				}
				else {
					if (m_unk0x618 < 0.03f && m_unk0x618 > 0.00050000002f) {
						scale = 0.03f / m_unk0x64c;
					}
					else {
						scale = m_unk0x618 / m_unk0x64c;
					}

					m_unk0x650 = scale;
					steeringAmount = scale;
				}
				FUN_00445c30(steeringAmount, 200);
			}
		}
		else {
			LegoFloat scale = m_unk0x0c8 * -0.0020000001f;
			force.m_x = m_unk0x61c.m_x * scale;
			force.m_y = m_unk0x61c.m_y;
			force.m_y *= scale;
			force.m_z = m_unk0x61c.m_z;
			force.m_z *= scale;
			FUN_00440b10(&force);
		}
	}

	if (!(m_flags0x6c0 & (c_flags0x6c0Bit3 | c_flags0x6c0Bit7))) {
		GolVec3 sum;
		sum.m_x = 0.0f;
		sum.m_y = 0.0f;
		sum.m_z = 0.0f;
		Field0x198* entry = m_unk0x198;
		while (entry < &m_unk0x198[sizeOfArray(m_unk0x198)]) {
			sum.m_x += entry->m_unk0x064.m_x;
			sum.m_y += entry->m_unk0x064.m_y;
			sum.m_z += entry->m_unk0x064.m_z;
			entry++;
		}

		LegoFloat scale = m_unk0x15c * 0.25f;
		force.m_x = sum.m_x * scale;
		force.m_y = sum.m_y;
		force.m_y *= scale;
		force.m_z = sum.m_z;
		force.m_z *= scale;
		FUN_00440b10(&force);
	}

	LegoFloat drag = 0.0f;
	if (!(m_flags0x6c0 & c_flags0x6c0Bit3)) {
		Field0x198* entry = m_unk0x198;
		while (entry < &m_unk0x198[sizeOfArray(m_unk0x198)]) {
			drag += entry->m_unk0x050;
			entry++;
		}
		drag *= 0.25f;
	}
	drag += m_unk0x5ec;
	drag *= m_unk0x604;
	drag = -drag;
	force.m_x = m_unk0x008.m_x * drag;
	force.m_y = m_unk0x008.m_y;
	force.m_y *= drag;
	force.m_z = m_unk0x008.m_z;
	force.m_z *= drag;
	FUN_00440b10(&force);

	if (m_flags0x6c0 & c_flags0x6c0Bit5) {
		FUN_00440b10(&m_unk0x630);
	}

	if (m_flags0x6c0 & c_flags0x6c0Bit6) {
		FUN_00440b10(&m_unk0x63c);
	}
}

// FUNCTION: LEGORACERS 0x00445bb0
void RaceState::Racer::Field0x3e8Base0x74c::FUN_00445bb0(LegoFloat p_unk0x04, LegoU32 p_unk0x08)
{
	if (m_unk0x5d8) {
		return;
	}

	m_unk0x5dc = p_unk0x08;

	const GolMatrix34& transform = m_unk0x0e4.GetTransform();
	GolVec3 direction;
	direction.m_x = transform.m_m[1][0];
	direction.m_y = transform.m_m[1][1];
	direction.m_z = transform.m_m[1][2];
	FUN_00440da0(&direction);

	direction.m_x *= p_unk0x04;
	direction.m_y *= p_unk0x04;
	direction.m_z *= p_unk0x04;
	FUN_00440bd0(&direction);
}

// FUNCTION: LEGORACERS 0x00445c30
void RaceState::Racer::Field0x3e8Base0x74c::FUN_00445c30(LegoFloat p_unk0x04, LegoU32 p_unk0x08)
{
	m_unk0x5e0 = p_unk0x08;

	const GolMatrix34& transform = m_unk0x0e4.GetTransform();
	GolVec3 direction;
	direction.m_x = transform.m_m[2][0];
	direction.m_y = transform.m_m[2][1];
	direction.m_z = transform.m_m[2][2];
	FUN_00440da0(&direction);

	direction.m_x *= p_unk0x04;
	direction.m_y *= p_unk0x04;
	direction.m_z *= p_unk0x04;
	FUN_00440bd0(&direction);
}

// FUNCTION: LEGORACERS 0x00445d10
void RaceState::Racer::Field0x3e8Base0x74c::FUN_00445d10()
{
	GolVec3 forward;
	GolVec3 axis;
	GolVec3 right;

	m_unk0x0e4.VTable0x48(&right, &forward);
	if (forward.m_z < g_unk0x004b0cec) {
		axis.m_x = forward.m_y;
		axis.m_y = -forward.m_x;
		axis.m_z = 0.0f;
		GolMath::NormalizeVector3(axis, &axis);

		LegoFloat sine;
		LegoFloat cosine;
		GolMath::FUN_00449170(g_unk0x004b0ce8, &sine, &cosine);

		forward.m_x = -(sine * axis.m_y);
		forward.m_y = sine * axis.m_x;
		forward.m_z = cosine;
		m_unk0x0e4.FUN_00410b00(forward, right);
	}
}

// STUB: LEGORACERS 0x00445dc0
void RaceState::Racer::Field0x3e8Base0x74c::FUN_00445dc0(LegoS32 p_elapsedMs)
{
	LegoU32 flags = m_flags0x6c0;
	if (flags & c_flags0x6c0Bit8) {
		if (m_unk0x008.m_x == 0.0f && m_unk0x008.m_y == 0.0f && m_unk0x008.m_z == 0.0f && m_unk0x098.m_x == 0.0f &&
			m_unk0x098.m_y == 0.0f && m_unk0x098.m_z == 0.0f) {
			return;
		}

		m_flags0x6c0 = flags & ~c_flags0x6c0Bit8;
	}

	Field0x198* entries = m_unk0x198;
	Field0x198* entriesEnd = &m_unk0x198[sizeOfArray(m_unk0x198)];
	FUN_00448a50();

	LegoU32 previousContactCount = m_unk0x36c;

	GolVec3 position;
	m_unk0x0e4.VTable0x04(&position);

	LegoFloat verticalOffset = -(position.m_z - m_unk0x690.m_z);
	if (verticalOffset < 0.0f) {
		verticalOffset = 0.0f;
	}

	LegoFloat sweepHeight = m_unk0x13c->FUN_10028710() + verticalOffset;
	LegoFloat sweepDistance;
	LegoBool32 resetFromAir;
	if (m_unk0x36c != 0 && !(m_flags0x6c0 & c_flags0x6c0Bit7)) {
		sweepDistance = static_cast<LegoFloat>(p_elapsedMs) * g_raceStateField0x3e8SupportSweepDistanceScale;
		resetFromAir = FALSE;
	}
	else {
		sweepDistance = 0.0f;
		resetFromAir = TRUE;
	}

	m_unk0x36c = 0;
	FUN_00448c70();

	Field0x198* entry;
	for (entry = entries; entry < entriesEnd; entry++) {
		entry->m_flags0x048 &= ~(Field0x198::c_flags0x048Active | Field0x198::c_flags0x048Hit);
		entry->m_unk0x000.m_z = 0.0f;
		entry->m_unk0x000.m_y = 0.0f;
		entry->m_unk0x000.m_x = 0.0f;
		entry->m_unk0x04c = -FLT_MAX;
	}

	LegoFloat bestDistance = -FLT_MAX;
	Field0x198* selectedEntry = NULL;
	GolBoundingVolume::Field0x0c* eventContext = g_raceStateField0x3e8SnapshotEntries.GetEventContext();
	GolBoundingVolume::Field0x0c* collisionContext = eventContext;

	for (LegoU32 resourceIndex = 1; resourceIndex < m_unk0x154; resourceIndex++) {
		GolBoundedEntity* resource = m_unk0x140[resourceIndex];
		FUN_00448d90(resource, sweepHeight, sweepDistance);

		entry = entries;
		while (entry < entriesEnd) {
			if (!(entry->m_flags0x048 & Field0x198::c_flags0x048Hit)) {
				GolBoundingVolume* query = resource->GetUnk0x58();
				query->SetUnk0x24(resource->GetMaterialTable());

				GolVec3 hitPoint;
				RaceEventRecord* hitRecord;
				if (query->FUN_00403fa0(
						&entry->m_unk0x018,
						&entry->m_unk0x024,
						collisionContext,
						&hitPoint,
						&hitRecord,
						NULL
					)) {
					entry->m_unk0x03c = hitRecord;
					entry->m_flags0x048 |= Field0x198::c_flags0x048Hit;
					resource->VTable0x2c(hitPoint, &entry->m_unk0x030);

					GolVec3 collisionNormal = eventContext->m_unk0x24;
					resource->VTable0x34(collisionNormal, &entry->m_unk0x000);

					LegoFloat deltaX = entry->m_unk0x024.m_x - hitPoint.m_x;
					LegoFloat deltaY = entry->m_unk0x024.m_y - hitPoint.m_y;
					LegoFloat deltaZ = entry->m_unk0x024.m_z - hitPoint.m_z;
					entry->m_unk0x04c = deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ;

					if (entry->m_unk0x04c > bestDistance) {
						selectedEntry = entry;
						bestDistance = entry->m_unk0x04c;
					}
				}
			}

			entry++;
		}
	}

	GolBoundedEntity* baseResource = m_unk0x140[0];
	entry = entries;
	while (entry < entriesEnd) {
		if (entry->m_flags0x048 & Field0x198::c_flags0x048Hit) {
			entry++;
			continue;
		}

		entry->m_unk0x018.m_x = entry->m_unk0x00c.m_x;
		entry->m_unk0x018.m_y = entry->m_unk0x00c.m_y;
		entry->m_unk0x018.m_z = entry->m_unk0x00c.m_z + sweepHeight;
		entry->m_unk0x024.m_x = entry->m_unk0x00c.m_x;
		entry->m_unk0x024.m_y = entry->m_unk0x00c.m_y;
		entry->m_unk0x024.m_z = entry->m_unk0x00c.m_z - sweepDistance;

		if (!FUN_00448ae0(entry)) {
			GolBoundingVolume* query = baseResource->GetUnk0x58();
			query->SetUnk0x24(baseResource->GetMaterialTable());

			RaceEventRecord* hitRecord;
			if (query->FUN_00403fa0(
					&entry->m_unk0x018,
					&entry->m_unk0x024,
					collisionContext,
					&entry->m_unk0x030,
					&hitRecord,
					NULL
				)) {
				entry->m_unk0x03c = hitRecord;
				entry->m_unk0x044 = FUN_00448a70(eventContext, entry->m_unk0x03c);
			}
			else {
				entry++;
				continue;
			}
		}

		entry->m_unk0x000 = entry->m_unk0x044->m_unk0x000.m_unk0x24;

		LegoFloat deltaX = entry->m_unk0x024.m_x - entry->m_unk0x030.m_x;
		LegoFloat deltaY = entry->m_unk0x024.m_y - entry->m_unk0x030.m_y;
		LegoFloat deltaZ = entry->m_unk0x024.m_z - entry->m_unk0x030.m_z;
		entry->m_unk0x04c = deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ;

		if (entry->m_unk0x04c > bestDistance) {
			selectedEntry = entry;
			bestDistance = entry->m_unk0x04c;
		}

		entry->m_flags0x048 |= Field0x198::c_flags0x048Hit;
		entry++;
	}

	if (selectedEntry == NULL) {
		if (previousContactCount == 0) {
			return;
		}

		m_unk0x008.m_z -= g_raceStateField0x3e8AirborneDropStep;
		return;
	}

	LegoFloat contactLimit = static_cast<LegoFloat>(sqrt(bestDistance)) - g_raceStateField0x3e8ContactLimitPadding;
	if (contactLimit < 0.0f) {
		contactLimit = 0.0f;
	}

	LegoFloat contactLimitSquared = contactLimit * contactLimit;
	m_unk0x174.m_x = 0.0f;
	m_unk0x174.m_y = 0.0f;
	m_unk0x174.m_z = 0.0f;

	entry = entries;
	while (entry < entriesEnd) {
		if (entry->m_unk0x04c >= contactLimitSquared) {
			m_unk0x174.m_x += entry->m_unk0x000.m_x;
			m_unk0x174.m_y += entry->m_unk0x000.m_y;
			m_unk0x174.m_z += entry->m_unk0x000.m_z;
			entry->m_flags0x048 |= Field0x198::c_flags0x048Active;
			m_unk0x36c++;
		}
		else {
			entry->m_flags0x048 &= ~Field0x198::c_flags0x048Active;
			entry->m_unk0x000.m_x = 0.0f;
			entry->m_unk0x000.m_y = 0.0f;
			entry->m_unk0x000.m_z = 0.0f;
		}

		entry++;
	}

	FUN_00448430(selectedEntry);

	if (m_unk0x36c >= 3) {
		const GolMatrix34& transform = m_unk0x0e4.GetTransform();
		m_unk0x174.m_x = transform.m_m[2][0];
		m_unk0x174.m_y = transform.m_m[2][1];
		m_unk0x174.m_z = transform.m_m[2][2];

		entry = entries;
		while (entry < entriesEnd) {
			entry->m_flags0x048 |= Field0x198::c_flags0x048Active;
			entry++;
		}

		m_unk0x36c = 4;
	}
	else {
		GolMath::NormalizeVector3(m_unk0x174, &m_unk0x174);
	}

	if (resetFromAir) {
		if (m_unk0x6dc > 400) {
			LegoFloat dot =
				m_unk0x008.m_z * m_unk0x174.m_z + m_unk0x008.m_y * m_unk0x174.m_y + m_unk0x008.m_x * m_unk0x174.m_x;
			if (dot < 0.0f) {
				if (dot < -g_raceStateField0x3e8BounceThreshold) {
					LegoFloat scaled = dot * g_raceStateField0x3e8FourContactBounceScale;
					m_unk0x36c = 0;
					m_unk0x008.m_z -= scaled;

					entry = entries;
					while (entry < entriesEnd) {
						entry->m_flags0x048 &= ~Field0x198::c_flags0x048Active;
						entry++;
					}
					return;
				}

				m_unk0x008.m_z -= dot;
			}
		}
	}

	LegoFloat responseScale = m_unk0x164 * m_unk0x174.m_z;
	m_unk0x180.m_x = -(m_unk0x174.m_x * responseScale);
	m_unk0x180.m_y = -(m_unk0x174.m_y * responseScale);
	m_unk0x180.m_z = m_unk0x164 - m_unk0x174.m_z * responseScale;

	g_raceStateField0x3e8Snapshot0x0b8.m_x = 0.0f;
	g_raceStateField0x3e8Snapshot0x0b8.m_y = 0.0f;
	g_raceStateField0x3e8Snapshot0x0b8.m_z = -(m_unk0x164 * (1.0f / static_cast<LegoFloat>(m_unk0x36c + 8)));

	entry = entries;
	while (entry < entriesEnd) {
		if (entry->m_flags0x048 & Field0x198::c_flags0x048Active) {
			entry->m_unk0x000 = g_raceStateField0x3e8Snapshot0x0b8;
		}
		entry++;
	}
}

// FUNCTION: LEGORACERS 0x004464a0
void RaceState::Racer::Field0x3e8Base0x74c::FUN_004464a0(LegoS32 p_elapsedMs)
{
	if (m_unk0x658 < m_unk0x65c) {
		LegoFloat delta = m_unk0x660;
		LegoFloat elapsed = static_cast<LegoFloat>(p_elapsedMs);
		delta *= elapsed;
		delta *= 0.001f;
		m_unk0x658 += delta;
		if (m_unk0x658 > m_unk0x65c) {
			m_unk0x658 = m_unk0x65c;
		}
	}
	else if (m_unk0x658 > m_unk0x65c) {
		LegoFloat delta = m_unk0x660;
		LegoFloat elapsed = static_cast<LegoFloat>(p_elapsedMs);
		delta *= elapsed;
		delta *= 0.001f;
		m_unk0x658 -= delta;
		if (m_unk0x658 < m_unk0x65c) {
			m_unk0x658 = m_unk0x65c;
		}
	}

	if (m_unk0x680 < m_unk0x67c) {
		m_unk0x680 += static_cast<LegoFloat>(p_elapsedMs) * g_unk0x004b0d28;
		if (m_unk0x680 > m_unk0x67c) {
			m_unk0x680 = m_unk0x67c;
		}
	}
	else if (m_unk0x680 > m_unk0x67c) {
		m_unk0x680 -= static_cast<LegoFloat>(p_elapsedMs) * g_unk0x004b0d28;
		if (m_unk0x680 < m_unk0x67c) {
			m_unk0x680 = m_unk0x67c;
		}
	}
}

// STUB: LEGORACERS 0x004465c0
void RaceState::Racer::Field0x3e8Base0x74c::FUN_004465c0(LegoU32 p_elapsedMs)
{
	LegoU32 flags = m_flags0x6c0;
	if (flags & c_flags0x6c0Bit8) {
		if (m_unk0x008.m_x == 0.0f && m_unk0x008.m_y == 0.0f && m_unk0x008.m_z == 0.0f && m_unk0x098.m_x == 0.0f &&
			m_unk0x098.m_y == 0.0f && m_unk0x098.m_z == 0.0f) {
			return;
		}

		m_flags0x6c0 = flags & ~c_flags0x6c0Bit8;
	}

	FUN_00448a50();

	LegoFloat elapsedMs = static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs));
	FUN_00448c70();

	LegoFloat average = m_unk0x198[0].m_unk0x00c.m_x;
	average += m_unk0x198[1].m_unk0x00c.m_x;
	m_unk0x664.m_x = average * 0.5f;
	average = m_unk0x198[0].m_unk0x00c.m_y;
	average += m_unk0x198[1].m_unk0x00c.m_y;
	m_unk0x664.m_y = average * 0.5f;
	average = m_unk0x198[0].m_unk0x00c.m_z;
	average += m_unk0x198[1].m_unk0x00c.m_z;
	m_unk0x664.m_z = average * 0.5f;
	average = m_unk0x198[3].m_unk0x00c.m_x;
	average += m_unk0x198[2].m_unk0x00c.m_x;
	m_unk0x670.m_x = average * 0.5f;
	average = m_unk0x198[2].m_unk0x00c.m_y;
	average += m_unk0x198[3].m_unk0x00c.m_y;
	m_unk0x670.m_y = average * 0.5f;
	average = m_unk0x198[2].m_unk0x00c.m_z;
	average += m_unk0x198[3].m_unk0x00c.m_z;
	m_unk0x670.m_z = average * 0.5f;

	LegoU32 previousContactCount = m_unk0x36c;

	GolVec3 position;
	m_unk0x0e4.VTable0x04(&position);

	LegoFloat verticalOffset = -(position.m_z - m_unk0x690.m_z);
	if (verticalOffset < 0.0f) {
		verticalOffset = 0.0f;
	}

	LegoFloat sweepHeight = m_unk0x13c->FUN_10028710() + verticalOffset;
	LegoBool32 resetFromAir;
	LegoFloat sweepDistance;
	if (m_unk0x36c != 0) {
		sweepDistance = elapsedMs * g_raceStateField0x3e8SweepDistanceScale;
		resetFromAir = FALSE;
	}
	else {
		sweepDistance = 0.0f;
		resetFromAir = TRUE;
	}
	sweepDistance += m_unk0x658;

	Field0x198* entries = m_unk0x198;
	Field0x198* entriesEnd = &m_unk0x198[2];
	Field0x198* entry;
	m_unk0x36c = 0;

	GolVec3* sweepCenter = &m_unk0x664;
	for (entry = entries; entry < entriesEnd; entry++, sweepCenter++) {
		entry->m_unk0x018.m_x = sweepCenter->m_x;
		entry->m_unk0x018.m_y = sweepCenter->m_y;
		entry->m_unk0x018.m_z = sweepCenter->m_z + sweepHeight;
		entry->m_unk0x024.m_x = sweepCenter->m_x;
		entry->m_unk0x024.m_y = sweepCenter->m_y;
		entry->m_unk0x024.m_z = sweepCenter->m_z - sweepDistance;
		entry->m_flags0x048 &= ~(Field0x198::c_flags0x048Active | Field0x198::c_flags0x048Hit);
		entry->m_unk0x000.m_x = 0.0f;
		entry->m_unk0x000.m_y = 0.0f;
		entry->m_unk0x000.m_z = 0.0f;
		entry->m_unk0x04c = -FLT_MAX;
	}

	LegoFloat bestDistance = -FLT_MAX;
	Field0x198* selectedEntry = NULL;
	LegoS32 selectedIndex = 0;
	GolBoundingVolume::Field0x0c* eventContext = g_raceStateField0x3e8SnapshotEntries.GetEventContext();
	GolBoundingVolume::Field0x0c* collisionContext = eventContext;

	for (LegoU32 resourceIndex = 1; resourceIndex < m_unk0x154; resourceIndex++) {
		GolBoundedEntity* resource = m_unk0x140[resourceIndex];

		LegoS32 entryIndex = 0;
		for (entry = entries; entry < entriesEnd; entry++, entryIndex++) {
			if (entry->m_flags0x048 & Field0x198::c_flags0x048Hit) {
				continue;
			}

			GolVec3 start;
			GolVec3 end;
			resource->VTable0x30(entry->m_unk0x018, &start);
			resource->VTable0x30(entry->m_unk0x024, &end);

			GolBoundingVolume* query = resource->GetUnk0x58();
			query->SetUnk0x24(resource->GetMaterialTable());

			GolVec3 hitPoint;
			RaceEventRecord* hitRecord;
			if (!query->FUN_00403fa0(&start, &end, collisionContext, &hitPoint, &hitRecord, NULL)) {
				continue;
			}

			entry->m_flags0x048 |= Field0x198::c_flags0x048Hit;
			resource->VTable0x2c(hitPoint, &entry->m_unk0x030);

			GolVec3 collisionNormal = eventContext->m_unk0x24;
			resource->VTable0x34(collisionNormal, &entry->m_unk0x000);

			if (entryIndex == 0) {
				m_unk0x198[0].m_unk0x03c = hitRecord;
				m_unk0x198[1].m_unk0x03c = hitRecord;
			}
			else {
				m_unk0x198[2].m_unk0x03c = hitRecord;
				m_unk0x198[3].m_unk0x03c = hitRecord;
			}

			LegoFloat deltaX = end.m_x - hitPoint.m_x;
			LegoFloat deltaY = end.m_y - hitPoint.m_y;
			LegoFloat deltaZ = end.m_z - hitPoint.m_z;
			entry->m_unk0x04c = deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ;

			if (entry->m_unk0x04c > bestDistance) {
				selectedEntry = entry;
				selectedIndex = entryIndex;
				bestDistance = entry->m_unk0x04c;
			}
		}
	}

	GolBoundedEntity* baseResource = m_unk0x140[0];
	LegoS32 entryIndex = 0;
	for (entry = entries; entry < entriesEnd; entry++, entryIndex++) {
		if (!(entry->m_flags0x048 & Field0x198::c_flags0x048Hit)) {
			if (!FUN_00448ae0(entry)) {
				GolBoundingVolume* query = baseResource->GetUnk0x58();
				query->SetUnk0x24(baseResource->GetMaterialTable());

				RaceEventRecord* hitRecord;
				if (!query->FUN_00403fa0(
						&entry->m_unk0x018,
						&entry->m_unk0x024,
						collisionContext,
						&entry->m_unk0x030,
						&hitRecord,
						NULL
					)) {
					continue;
				}

				entry->m_unk0x044 = FUN_00448a70(eventContext, hitRecord);

				if (entryIndex == 0) {
					m_unk0x198[0].m_unk0x03c = hitRecord;
					m_unk0x198[1].m_unk0x03c = hitRecord;
				}
				else {
					m_unk0x198[2].m_unk0x03c = hitRecord;
					m_unk0x198[3].m_unk0x03c = hitRecord;
				}
			}

			entry->m_unk0x000 = entry->m_unk0x044->m_unk0x000.m_unk0x24;

			LegoFloat deltaX = entry->m_unk0x024.m_x - entry->m_unk0x030.m_x;
			LegoFloat deltaY = entry->m_unk0x024.m_y - entry->m_unk0x030.m_y;
			LegoFloat deltaZ = entry->m_unk0x024.m_z - entry->m_unk0x030.m_z;
			entry->m_unk0x04c = deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ;

			if (entry->m_unk0x04c > bestDistance) {
				selectedEntry = entry;
				selectedIndex = entryIndex;
				bestDistance = entry->m_unk0x04c;
			}

			entry->m_flags0x048 |= Field0x198::c_flags0x048Hit;
		}
	}

	if (selectedEntry == NULL) {
		if (previousContactCount == 0) {
			return;
		}

		m_unk0x008.m_z -= g_raceStateField0x3e8AirborneDropStep;
		return;
	}

	LegoFloat contactLimit = static_cast<LegoFloat>(sqrt(bestDistance)) - g_raceStateField0x3e8ContactLimitPadding;
	if (contactLimit < 0.0f) {
		contactLimit = 0.0f;
	}

	LegoFloat contactLimitSquared = contactLimit * contactLimit;
	m_unk0x174.m_x = 0.0f;
	m_unk0x174.m_y = 0.0f;
	m_unk0x174.m_z = 0.0f;

	for (entry = entries; entry < entriesEnd; entry++) {
		if (entry->m_unk0x04c >= contactLimitSquared) {
			m_unk0x174.m_x += entry->m_unk0x000.m_x;
			m_unk0x174.m_y += entry->m_unk0x000.m_y;
			m_unk0x174.m_z += entry->m_unk0x000.m_z;
			entry->m_flags0x048 |= Field0x198::c_flags0x048Active;
			m_unk0x36c++;
		}
		else {
			entry->m_flags0x048 &= ~Field0x198::c_flags0x048Active;
			entry->m_unk0x000.m_x = 0.0f;
			entry->m_unk0x000.m_y = 0.0f;
			entry->m_unk0x000.m_z = 0.0f;
		}
	}

	if (m_unk0x36c >= 2) {
		GolVec3 direction;
		direction.m_x = m_unk0x198[0].m_unk0x030.m_x - m_unk0x198[1].m_unk0x030.m_x;
		direction.m_y = m_unk0x198[0].m_unk0x030.m_y - m_unk0x198[1].m_unk0x030.m_y;
		direction.m_z = m_unk0x198[0].m_unk0x030.m_z - m_unk0x198[1].m_unk0x030.m_z;

		GolVec3 up;
		up.m_x = m_unk0x0e4.GetTransform().m_m[2][0];
		up.m_y = m_unk0x0e4.GetTransform().m_m[2][1];
		up.m_z = m_unk0x0e4.GetTransform().m_m[2][2];
		m_unk0x0e4.VTable0x40(direction, up);

		m_unk0x174.m_x = m_unk0x0e4.GetTransform().m_m[2][0];
		m_unk0x174.m_y = m_unk0x0e4.GetTransform().m_m[2][1];
		m_unk0x174.m_z = m_unk0x0e4.GetTransform().m_m[2][2];
	}
	else {
		GolMath::NormalizeVector3(m_unk0x174, &m_unk0x174);
	}

	GolVec3* selectedCenter = selectedIndex == 0 ? &m_unk0x664 : &m_unk0x670;
	GolVec3 delta;
	delta.m_x = selectedEntry->m_unk0x030.m_x - selectedCenter->m_x;
	delta.m_y = selectedEntry->m_unk0x030.m_y - selectedCenter->m_y;
	delta.m_z = selectedEntry->m_unk0x030.m_z - selectedCenter->m_z + m_unk0x658;

	GolVec3 newPosition;
	m_unk0x0e4.VTable0x04(&newPosition);
	newPosition.m_x += delta.m_x;
	newPosition.m_y += delta.m_y;
	newPosition.m_z += delta.m_z;
	m_unk0x0e4.VTable0x08(newPosition);

	m_unk0x664.m_x += delta.m_x;
	m_unk0x664.m_y += delta.m_y;
	m_unk0x664.m_z += delta.m_z;
	m_unk0x670.m_x += delta.m_x;
	m_unk0x670.m_y += delta.m_y;
	m_unk0x670.m_z += delta.m_z;

	if (resetFromAir) {
		LegoFloat dot =
			m_unk0x008.m_z * m_unk0x174.m_z + m_unk0x008.m_y * m_unk0x174.m_y + m_unk0x008.m_x * m_unk0x174.m_x;
		if (dot < 0.0f) {
			if (dot < -g_raceStateField0x3e8BounceThreshold) {
				LegoFloat scaled = dot * g_raceStateField0x3e8BounceScale;
				m_unk0x36c = 0;
				m_unk0x008.m_z -= scaled;

				for (entry = entries; entry < entriesEnd; entry++) {
					entry->m_flags0x048 &= ~Field0x198::c_flags0x048Active;
				}
				return;
			}

			m_unk0x008.m_z -= dot;
		}
	}

	LegoFloat responseScale = m_unk0x164 * m_unk0x174.m_z;
	m_unk0x180.m_x = -(m_unk0x174.m_x * responseScale);
	m_unk0x180.m_y = -(m_unk0x174.m_y * responseScale);
	m_unk0x180.m_z = m_unk0x164 - m_unk0x174.m_z * responseScale;

	g_raceStateField0x3e8Snapshot0x0b8.m_x = 0.0f;
	g_raceStateField0x3e8Snapshot0x0b8.m_y = 0.0f;
	g_raceStateField0x3e8Snapshot0x0b8.m_z = -(m_unk0x164 * 0.5f);

	for (entry = entries; entry < entriesEnd; entry++) {
		if (entry->m_flags0x048 & Field0x198::c_flags0x048Active) {
			entry->m_unk0x000 = g_raceStateField0x3e8Snapshot0x0b8;
		}
	}
}

// FUNCTION: LEGORACERS 0x00446e60
void RaceState::Racer::Field0x3e8Base0x74c::FUN_00446e60(GolVec3* p_unk0x04, LegoFloat p_unk0x08, LegoFloat p_unk0x0c)
{
	::memcpy(&m_unk0x358, p_unk0x04, sizeof(m_unk0x358));
	m_unk0x364 = p_unk0x08;
	m_unk0x368 = p_unk0x0c;
	FUN_00448c70();
}

// FUNCTION: LEGORACERS 0x00446ea0
void RaceState::Racer::Field0x3e8Base0x74c::FUN_00446ea0(LegoU32 p_unk0x04, GolVec3* p_unk0x08)
{
	GolVec3* source = &m_unk0x370[p_unk0x04];
	*source = *p_unk0x08;
	m_unk0x0e4.VTable0x2c(*source, &m_unk0x3a0[p_unk0x04]);
}

// FUNCTION: LEGORACERS 0x00446fa0
void RaceState::Racer::Field0x3e8Base0x74c::FUN_00446fa0()
{
	m_unk0x168.m_x = m_unk0x0e4.GetOrientation().m_rows[0].m_x;
	m_unk0x168.m_y = m_unk0x0e4.GetOrientation().m_rows[0].m_y;
	m_unk0x168.m_z = m_unk0x0e4.GetOrientation().m_rows[0].m_z;
	FUN_00447330();
}

// FUNCTION: LEGORACERS 0x00446fd0
void RaceState::Racer::Field0x3e8Base0x74c::FUN_00446fd0(LegoU32 p_elapsedMs)
{
	LegoFloat sine;
	LegoFloat cosine;
	GolVec3 direction;
	GolVec3 axis;

	direction.m_x = m_unk0x0e4.GetOrientation().m_rows[0].m_x;
	direction.m_y = m_unk0x0e4.GetOrientation().m_rows[0].m_y;
	direction.m_z = m_unk0x0e4.GetOrientation().m_rows[0].m_z;

	if (m_unk0x36c != 0) {
		if (!(m_unk0x618 < 0.03f)) {
			if (m_unk0x36c <= 2) {
				LegoFloat dot = m_unk0x174.m_z;
				dot *= direction.m_z;
				LegoFloat value = m_unk0x174.m_y;
				value *= direction.m_y;
				dot += value;
				value = direction.m_x;
				value *= m_unk0x174.m_x;
				dot += value;

				axis.m_x = dot;
				axis.m_x *= m_unk0x174.m_x;
				axis.m_y = m_unk0x174.m_y;
				axis.m_y *= dot;
				LegoFloat projectedZ = dot;
				projectedZ *= m_unk0x174.m_z;

				direction.m_x -= axis.m_x;
				direction.m_y -= axis.m_y;
				direction.m_z -= projectedZ;
				GolMath::NormalizeVector3(direction, &direction);
			}
			else {
				if ((m_flags0x6c0 & c_flags0x6c0Bit0) && m_unk0x628 > 0.0f) {
					GolVec3* current = &m_unk0x168;
					LegoFloat dot = m_unk0x168.m_z;
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
					LegoFloat step = m_unk0x650;
					LegoFloat elapsed = static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs));
					step *= elapsed;
					if (step > 0.0f) {
						angle += step;
					}
					else {
						angle -= step;
					}

					if (angle > m_unk0x6cc) {
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
						GolMath::FUN_004496a0(&direction, current, &axis, m_unk0x6cc);
						GolMath::NormalizeVector3(*current, current);
						return;
					}

					GolMath::FUN_00449170(step, &cosine, &sine);
					value = current->m_x;
					value *= sine;
					LegoFloat crossValue = m_unk0x168.m_y;
					crossValue *= cosine;
					current->m_x = value - crossValue;
					value = m_unk0x168.m_y;
					value *= sine;
					crossValue = current->m_x;
					crossValue *= cosine;
					m_unk0x168.m_y = value + crossValue;
					GolMath::NormalizeVector3(*current, current);
					return;
				}

				FUN_00447230(p_elapsedMs, &direction);
				return;
			}
		}
	}

	FUN_00447230(p_elapsedMs, &direction);
}

// FUNCTION: LEGORACERS 0x00447230
void RaceState::Racer::Field0x3e8Base0x74c::FUN_00447230(LegoS32 p_elapsedMs, GolVec3* p_unk0x08)
{
	GolVec3* current = &m_unk0x168;
	GolVec3* target = p_unk0x08;

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
	GolMath::FUN_004496a0(current, current, &axis, maxStep);
	GolMath::NormalizeVector3(*current, current);
}

// FUNCTION: LEGORACERS 0x00447330
void RaceState::Racer::Field0x3e8Base0x74c::FUN_00447330()
{
	GolVec3* velocity = &m_unk0x008;

	if (m_unk0x008.m_x == 0.0f && m_unk0x008.m_y == 0.0f && m_unk0x008.m_z == 0.0f) {
		m_unk0x604 = 0.0f;
		m_unk0x5f8.m_x = m_unk0x0e4.GetOrientation().m_rows[0].m_x;
		m_unk0x5f8.m_y = m_unk0x0e4.GetOrientation().m_rows[0].m_y;
		m_unk0x5f8.m_z = m_unk0x0e4.GetOrientation().m_rows[0].m_z;

		if (m_unk0x098.m_x == 0.0f && m_unk0x098.m_y == 0.0f && m_unk0x098.m_z == 0.0f) {
			m_flags0x6c0 |= c_flags0x6c0Bit8;
		}
		else {
			m_flags0x6c0 &= ~c_flags0x6c0Bit8;
		}
	}
	else {
		LegoFloat speed = static_cast<LegoFloat>(
			sqrt(velocity->m_x * velocity->m_x + velocity->m_y * velocity->m_y + velocity->m_z * velocity->m_z)
		);
		m_unk0x604 = speed;
		GolMath::NormalizeVector3(*velocity, &m_unk0x5f8);
		m_flags0x6c0 &= ~c_flags0x6c0Bit8;
	}

	LegoFloat forwardSpeed = velocity->m_z;
	forwardSpeed *= m_unk0x168.m_z;
	LegoFloat contribution = velocity->m_y;
	contribution *= m_unk0x168.m_y;
	forwardSpeed += contribution;
	contribution = velocity->m_x;
	contribution *= m_unk0x168.m_x;
	forwardSpeed += contribution;
	{
		LegoFloat projected = forwardSpeed;
		projected *= m_unk0x168.m_x;
		m_unk0x60c.m_x = projected;

		projected = m_unk0x168.m_y;
		projected *= forwardSpeed;
		m_unk0x60c.m_y = projected;

		projected = m_unk0x168.m_z;
		projected *= forwardSpeed;
		m_unk0x60c.m_z = projected;
	}

	m_unk0x61c.m_x = velocity->m_x - forwardSpeed * m_unk0x168.m_x;
	m_unk0x61c.m_y = velocity->m_y - m_unk0x168.m_y * forwardSpeed;
	m_unk0x61c.m_z = velocity->m_z - m_unk0x168.m_z * forwardSpeed;
	m_unk0x618 = forwardSpeed;
}

// FUNCTION: LEGORACERS 0x004474c0
void RaceState::Racer::Field0x3e8Base0x74c::FUN_004474c0()
{
	Field0x3e8Base0x74c* self = this;
	GolOrientedEntity* entity = &self->m_unk0x0e4;
	entity->VTable0x04(&self->m_unk0x690);

	self->m_unk0x684 = self->m_unk0x008;

	entity->VTable0x44(&self->m_unk0x69c);

	g_raceStateField0x3e8Snapshot0x0c4.m_m[0][0] = self->m_unk0x074.m_m[0][0];
	g_raceStateField0x3e8Snapshot0x0c4.m_m[0][1] = self->m_unk0x074.m_m[0][1];
	g_raceStateField0x3e8Snapshot0x0c4.m_m[0][2] = self->m_unk0x074.m_m[0][2];
	g_raceStateField0x3e8Snapshot0x0c4.m_m[1][0] = self->m_unk0x074.m_m[1][0];
	g_raceStateField0x3e8Snapshot0x0c4.m_m[1][1] = self->m_unk0x074.m_m[1][1];
	g_raceStateField0x3e8Snapshot0x0c4.m_m[1][2] = self->m_unk0x074.m_m[1][2];
	g_raceStateField0x3e8Snapshot0x0c4.m_m[2][0] = self->m_unk0x074.m_m[2][0];
	g_raceStateField0x3e8Snapshot0x0c4.m_m[2][1] = self->m_unk0x074.m_m[2][1];
	g_raceStateField0x3e8Snapshot0x0c4.m_m[2][2] = self->m_unk0x074.m_m[2][2];
	g_raceStateField0x3e8Snapshot0x0e8 = self->m_unk0x098;
	g_raceStateField0x3e8Snapshot0x0a0 = self->m_unk0x0a4;
	g_raceStateField0x3e8Snapshot0x0ac = self->m_unk0x658;
	g_raceStateField0x3e8Snapshot0x0b0 = self->m_unk0x680;
	g_raceStateField0x3e8Snapshot0x030 = self->m_unk0x168;

	Field0x198* entry = self->m_unk0x198;
	SnapshotEntry* snapshotEntry = g_raceStateField0x3e8SnapshotEntries.GetEntries();
	while (entry < self->m_unk0x198 + sizeOfArray(self->m_unk0x198)) {
		snapshotEntry->m_unk0x000 = entry->m_unk0x00c;

		RaceEventRecord* record = entry->m_unk0x03c;
		entry->m_unk0x040 = record;
		snapshotEntry->m_unk0x030 = record;

		snapshotEntry->m_flags0x03c = entry->m_flags0x048;
		snapshotEntry->m_unk0x044 = entry->m_unk0x050;
		snapshotEntry->m_unk0x048 = entry->m_unk0x054;
		snapshotEntry->m_unk0x04c = entry->m_unk0x058;
		snapshotEntry->m_unk0x050 = entry->m_unk0x05c;
		snapshotEntry->m_unk0x054 = entry->m_unk0x060;
		snapshotEntry->m_unk0x058 = entry->m_unk0x064;

		entry++;
		snapshotEntry++;
	}

	GolVec3* source = self->m_unk0x3a0;
	GolVec3* dest = g_raceStateField0x3e8Snapshot0x000;
	while (dest < &g_raceStateField0x3e8Snapshot0x030) {
		*dest = *source;
		source++;
		dest++;
	}
}

// FUNCTION: LEGORACERS 0x00447690
void RaceState::Racer::Field0x3e8Base0x74c::FUN_00447690()
{
	Field0x3e8Base0x74c* self = this;
	GolOrientedEntity* entity = &self->m_unk0x0e4;
	entity->VTable0x08(self->m_unk0x690);

	self->m_unk0x008 = self->m_unk0x684;

	entity->VTable0x3c(self->m_unk0x69c);

	self->m_unk0x074.m_m[0][0] = g_raceStateField0x3e8Snapshot0x0c4.m_m[0][0];
	self->m_unk0x074.m_m[0][1] = g_raceStateField0x3e8Snapshot0x0c4.m_m[0][1];
	self->m_unk0x074.m_m[0][2] = g_raceStateField0x3e8Snapshot0x0c4.m_m[0][2];
	self->m_unk0x074.m_m[1][0] = g_raceStateField0x3e8Snapshot0x0c4.m_m[1][0];
	self->m_unk0x074.m_m[1][1] = g_raceStateField0x3e8Snapshot0x0c4.m_m[1][1];
	self->m_unk0x074.m_m[1][2] = g_raceStateField0x3e8Snapshot0x0c4.m_m[1][2];
	self->m_unk0x074.m_m[2][0] = g_raceStateField0x3e8Snapshot0x0c4.m_m[2][0];
	self->m_unk0x074.m_m[2][1] = g_raceStateField0x3e8Snapshot0x0c4.m_m[2][1];
	self->m_unk0x074.m_m[2][2] = g_raceStateField0x3e8Snapshot0x0c4.m_m[2][2];
	self->m_unk0x098 = g_raceStateField0x3e8Snapshot0x0e8;
	self->m_unk0x0a4 = g_raceStateField0x3e8Snapshot0x0a0;
	self->m_unk0x658 = g_raceStateField0x3e8Snapshot0x0ac;
	self->m_unk0x680 = g_raceStateField0x3e8Snapshot0x0b0;
	self->m_unk0x168 = g_raceStateField0x3e8Snapshot0x030;

	Field0x198* entry = self->m_unk0x198;
	SnapshotEntry* snapshotEntry = g_raceStateField0x3e8SnapshotEntries.GetEntries();
	while (entry < self->m_unk0x198 + sizeOfArray(self->m_unk0x198)) {
		entry->m_unk0x00c = snapshotEntry->m_unk0x000;
		entry->m_unk0x03c = snapshotEntry->m_unk0x030;
		entry->m_flags0x048 = snapshotEntry->m_flags0x03c;
		entry->m_unk0x050 = snapshotEntry->m_unk0x044;
		entry->m_unk0x054 = snapshotEntry->m_unk0x048;
		entry->m_unk0x058 = snapshotEntry->m_unk0x04c;
		entry->m_unk0x05c = snapshotEntry->m_unk0x050;
		entry->m_unk0x060 = snapshotEntry->m_unk0x054;
		entry->m_unk0x064 = snapshotEntry->m_unk0x058;

		entry++;
		snapshotEntry++;
	}

	GolVec3* source = g_raceStateField0x3e8Snapshot0x000;
	GolVec3* dest = self->m_unk0x3a0;
	while (source < &g_raceStateField0x3e8Snapshot0x030) {
		*dest = *source;
		source++;
		dest++;
	}

	entity->VTable0x2c(self->m_unk0x014, &self->m_unk0x020);
	self->FUN_00447330();
}

// FUNCTION: LEGORACERS 0x00447880
void RaceState::Racer::Field0x3e8Base0x74c::FUN_00447880()
{
	m_unk0x3d0[0] = 0;
	m_unk0x3d0[1] = 0;
	m_unk0x3d0[2] = 0;
	m_unk0x3d0[3] = 0;
	m_unk0x3ec = 0;
}

// STUB: LEGORACERS 0x004478b0
LegoU32 RaceState::Racer::Field0x3e8Base0x74c::FUN_004478b0(LegoU32 p_elapsedMs, LegoBool32 p_unk0x08)
{
	RaceEventRecord* hitRecord = NULL;
	m_unk0x3ec = 0;
	LegoFloat bestDistance = -FLT_MAX;
	LegoFloat hitAmount;
	LegoFloat selectedHitAmount = 0.0f;

	GolOrientedEntity* entity = &m_unk0x0e4;
	for (LegoU32 i = 0; i < sizeOfArray(m_unk0x370); i++) {
		entity->VTable0x2c(m_unk0x370[i], &m_unk0x3a0[i]);
		m_unk0x3d0[i] = 0;
	}

	for (LegoU32 resourceIndex = 1; resourceIndex < m_unk0x154; resourceIndex++) {
		GolBoundedEntity* resource = m_unk0x140[resourceIndex];

		for (LegoS32 pointIndex = 0; pointIndex < sizeOfArray(m_unk0x3a0); pointIndex++) {
			if (!m_unk0x3d0[pointIndex]) {
				resource->VTable0x30(
					g_raceStateField0x3e8Snapshot0x000[pointIndex],
					&g_raceStateField0x3e8Snapshot0x070[pointIndex]
				);
				resource->VTable0x30(m_unk0x3a0[pointIndex], &g_raceStateField0x3e8Snapshot0x040[pointIndex]);

				GolBoundingVolume* query = resource->GetUnk0x58();
				query->SetUnk0x24(resource->GetMaterialTable());

				GolVec3 hitPoint;
				if (query->FUN_00403fa0(
						&g_raceStateField0x3e8Snapshot0x070[pointIndex],
						&g_raceStateField0x3e8Snapshot0x040[pointIndex],
						g_raceStateField0x3e8SnapshotEntries.GetEventContext(),
						&hitPoint,
						&hitRecord,
						&hitAmount
					)) {
					GolVec3 worldNormal;
					GolVec3 collisionNormal = g_raceStateField0x3e8SnapshotEntries.GetEventContext()->m_unk0x24;
					resource->VTable0x34(collisionNormal, &worldNormal);

					LegoFloat dot =
						(hitPoint.m_x - g_raceStateField0x3e8Snapshot0x040[pointIndex].m_x) * collisionNormal.m_x;
					dot += (hitPoint.m_y - g_raceStateField0x3e8Snapshot0x040[pointIndex].m_y) * collisionNormal.m_y;
					dot += (hitPoint.m_z - g_raceStateField0x3e8Snapshot0x040[pointIndex].m_z) * collisionNormal.m_z;

					if (dot > 0.0f) {
						if (hitRecord && !VTable0x0c(
											 &hitPoint,
											 hitRecord,
											 resource,
											 g_raceStateField0x3e8SnapshotEntries.GetEventContext()
										 )) {
							continue;
						}

						LegoFloat deltaX = g_raceStateField0x3e8Snapshot0x040[pointIndex].m_x - hitPoint.m_x;
						LegoFloat deltaY = g_raceStateField0x3e8Snapshot0x040[pointIndex].m_y - hitPoint.m_y;
						LegoFloat deltaZ = g_raceStateField0x3e8Snapshot0x040[pointIndex].m_z - hitPoint.m_z;
						LegoFloat distance = deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ;

						if (distance > bestDistance) {
							bestDistance = distance;
							m_unk0x3e0 = worldNormal;
							m_unk0x3d0[pointIndex] = 1;
							selectedHitAmount = hitAmount;
							m_unk0x3ec++;
						}
					}
				}
			}
		}
	}

	if (p_unk0x08) {
		GolBoundedEntity* resource = m_unk0x140[0];

		for (LegoS32 pointIndex = 0; pointIndex < sizeOfArray(m_unk0x3a0); pointIndex++) {
			if (!m_unk0x3d0[pointIndex]) {
				GolBoundingVolume* query = resource->GetUnk0x58();
				query->SetUnk0x24(resource->GetMaterialTable());

				GolVec3 hitPoint;
				if (query->FUN_00403fa0(
						&g_raceStateField0x3e8Snapshot0x000[pointIndex],
						&m_unk0x3a0[pointIndex],
						g_raceStateField0x3e8SnapshotEntries.GetEventContext(),
						&hitPoint,
						&hitRecord,
						&hitAmount
					)) {
					LegoFloat dot = (hitPoint.m_x - m_unk0x3a0[pointIndex].m_x) *
									g_raceStateField0x3e8SnapshotEntries.GetEventContext()->m_unk0x24.m_x;
					dot += (hitPoint.m_y - m_unk0x3a0[pointIndex].m_y) *
						   g_raceStateField0x3e8SnapshotEntries.GetEventContext()->m_unk0x24.m_y;
					dot += (hitPoint.m_z - m_unk0x3a0[pointIndex].m_z) *
						   g_raceStateField0x3e8SnapshotEntries.GetEventContext()->m_unk0x24.m_z;

					if (dot >= 0.0f) {
						if (hitRecord && !VTable0x0c(
											 &hitPoint,
											 hitRecord,
											 resource,
											 g_raceStateField0x3e8SnapshotEntries.GetEventContext()
										 )) {
							continue;
						}

						GolVec3 collisionNormal = g_raceStateField0x3e8SnapshotEntries.GetEventContext()->m_unk0x24;
						LegoFloat deltaX = m_unk0x3a0[pointIndex].m_x - hitPoint.m_x;
						LegoFloat deltaY = m_unk0x3a0[pointIndex].m_y - hitPoint.m_y;
						LegoFloat deltaZ = m_unk0x3a0[pointIndex].m_z - hitPoint.m_z;
						LegoFloat distance = deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ;

						if (distance > bestDistance) {
							bestDistance = distance;
							m_unk0x3e0 = collisionNormal;
							m_unk0x3d0[pointIndex] = 1;
							selectedHitAmount = hitAmount;
							LegoU32 collisionCount = m_unk0x3ec;
							collisionCount++;
							m_unk0x3ec = collisionCount;
						}
					}
				}
			}
		}
	}

	if (!m_unk0x3ec) {
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
	FUN_00447690();
	return result;
}

// FUNCTION: LEGORACERS 0x00447cf0
void RaceState::Racer::Field0x3e8Base0x74c::FUN_00447cf0()
{
	GolVec3* velocity = &m_unk0x008;
	GolVec3* direction = &m_unk0x3e0;

	if (m_flags0x6c0 & c_flags0x6c0Bit0) {
		FUN_00448070();
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

	const GolMatrix3& orientation = m_unk0x0e4.GetOrientation();
	LegoFloat row0X = orientation.m_rows[0].m_x;
	LegoU32 flags = m_flags0x6c0;
	LegoFloat row0Y = orientation.m_rows[0].m_y;
	LegoFloat row0Z = orientation.m_rows[0].m_z;

	if (!(flags & c_flags0x6c0Bit1)) {
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

			FUN_00445c30(amount, 200);
			m_flags0x6c0 |= c_flags0x6c0Bit11;
		}
	}

	if (dot < 0.0f) {
		LegoFloat scale = g_unk0x004b0d08 * dot;
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

	if (!(velocity->m_z < g_unk0x004b0d84)) {
		velocity->m_z = g_unk0x004b0d84;
	}
}

// FUNCTION: LEGORACERS 0x00448070 FOLDED
void RaceState::Racer::Field0x3e8Base0x74c::FUN_00448070()
{
	LegoU32 flags = m_flags0x6c0;
	RaceResourceManager::Resource* resource = m_unk0x6e8;

	flags &= ~(c_flags0x6c0Bit0 | c_flags0x6c0Bit9);
	m_unk0x6c8 = -1.0f;
	m_unk0x6cc = 3.1415927f;
	m_flags0x6c0 = flags;

	if (resource != NULL) {
		m_unk0x158->FUN_00443c10(resource);
		m_unk0x6e8 = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004480c0
void RaceState::Racer::Field0x3e8Base0x74c::VTable0x1c(GolVec3* p_unk0x04, GolVec3*)
{
	GolVec3 scaled;
	scaled.m_x = m_unk0x0cc;
	scaled.m_x *= p_unk0x04->m_x;
	scaled.m_y = p_unk0x04->m_y * m_unk0x0cc;
	scaled.m_z = p_unk0x04->m_z * m_unk0x0cc;

	m_unk0x008.m_x += scaled.m_x;
	m_unk0x008.m_y += scaled.m_y;
	m_unk0x008.m_z += scaled.m_z;
}

// FUNCTION: LEGORACERS 0x00448110
void RaceState::Racer::Field0x3e8Base0x74c::VTable0x20(GolVec3* p_unk0x04, LegoFloat p_unk0x08)
{
	GolVec3 scaled;
	LegoFloat scale = m_unk0x0cc;
	scale *= p_unk0x08;
	scaled.m_x = scale * p_unk0x04->m_x;
	scaled.m_y = p_unk0x04->m_y;
	scaled.m_y *= scale;

	m_unk0x008.m_x += scaled.m_x;
	m_unk0x008.m_y += scaled.m_y;
	m_unk0x008.m_z += p_unk0x04->m_z * scale;
}

// FUNCTION: LEGORACERS 0x00448160
void RaceState::Racer::Field0x3e8Base0x74c::VTable0x24(LegoFloat p_unk0x04, LegoFloat p_unk0x08, LegoFloat p_unk0x0c)
{
	if (m_flags0x6c0 & c_flags0x6c0Bit1) {
		return;
	}

	const GolMatrix34& transform = m_unk0x0e4.GetTransform();
	GolVec3 direction;
	direction.m_x = transform.m_m[2][0];
	direction.m_y = transform.m_m[2][1];
	direction.m_z = transform.m_m[2][2];
	FUN_00440da0(&direction);

	LegoS32 speed = static_cast<LegoS32>(g_twoPi / p_unk0x08);
	m_unk0x5e8 = speed;
	FUN_00445c30(p_unk0x08, static_cast<LegoS32>(static_cast<LegoFloat>(speed) * p_unk0x04));
	m_flags0x6c0 = (m_flags0x6c0 & ~(c_flags0x6c0Bit1 | c_flags0x6c0Bit2 | 1)) | (c_flags0x6c0Bit1 | c_flags0x6c0Bit2);

	if (p_unk0x0c > 0.0f) {
		if (p_unk0x0c > p_unk0x04) {
			p_unk0x0c = p_unk0x04;
		}

		m_unk0x5e4 = static_cast<LegoS32>(static_cast<LegoFloat>(static_cast<LegoS32>(m_unk0x5e8)) * p_unk0x0c);
	}

	if (!m_unk0x6e4) {
		if (m_unk0x6ec) {
			m_sound6e4 = m_unk0x158->FUN_00443bd0(0x3c);
		}

		if (m_sound6e4) {
			m_sound6e4->SetDistanceRangeWithMinSquared(g_unk0x004b0cd8 * g_unk0x004b0cd8, g_unk0x004b0cdc);
			m_sound6e4->Play(TRUE);
		}
	}
}

// FUNCTION: LEGORACERS 0x00448290
void RaceState::Racer::Field0x3e8Base0x74c::VTable0x28()
{
	if (m_unk0x5e4) {
		if (m_unk0x5e4 > m_unk0x5e8) {
			do {
				m_unk0x5e4 -= m_unk0x5e8;
			} while (m_unk0x5e4 > m_unk0x5e8);
		}

		m_unk0x5e0 = m_unk0x5e4;
		m_unk0x5e4 = 0;
		m_unk0x5e8 = 0;
	}
}

// FUNCTION: LEGORACERS 0x004482e0
void RaceState::Racer::Field0x3e8Base0x74c::VTable0x2c()
{
	if (m_flags0x6c0 & c_flags0x6c0Bit1) {
		m_unk0x5e0 = 0;

		const GolVec3& orientationRow = m_unk0x0e4.GetOrientation().m_rows[2];
		GolVec3 direction;
		direction.m_x = orientationRow.m_x;
		direction.m_y = orientationRow.m_y;
		direction.m_z = orientationRow.m_z;
		FUN_00440da0(&direction);
		m_flags0x6c0 &= ~(c_flags0x6c0Bit1 | c_flags0x6c0Bit2 | c_flags0x6c0Bit11);

		if (m_unk0x6e4 != NULL) {
			m_unk0x6e4->VTable0x08();
			m_unk0x158->FUN_00443c10(m_unk0x6e4);
			m_unk0x6e4 = NULL;
		}
	}
}

// FUNCTION: LEGORACERS 0x00448370
void RaceState::Racer::Field0x3e8Base0x74c::VTable0x14(LegoFloat p_unk0x04)
{
	m_unk0x628 = p_unk0x04;
	FUN_004483b0();
}

// FUNCTION: LEGORACERS 0x00448390
void RaceState::Racer::Field0x3e8Base0x74c::VTable0x18(LegoFloat p_unk0x04)
{
	m_unk0x608 = p_unk0x04;
	FUN_004483b0();
}

// FUNCTION: LEGORACERS 0x004483b0
void RaceState::Racer::Field0x3e8Base0x74c::FUN_004483b0()
{
	if (m_unk0x628 < 0.0f) {
		m_unk0x5ec = (m_unk0x0c8 * -m_unk0x628) / (m_unk0x608 * m_unk0x608);
	}
	else if (m_unk0x628 > 0.0f) {
		m_unk0x5ec = (m_unk0x0c8 * m_unk0x628) / (m_unk0x608 * m_unk0x608);
	}
	else {
		m_unk0x5ec = 0.0f;
	}
}

// FUNCTION: LEGORACERS 0x00448430
void RaceState::Racer::Field0x3e8Base0x74c::FUN_00448430(Field0x198* p_unk0x04)
{
	GolVec3 position;
	GolVec3 direction1;
	GolVec3 direction0;
	GolVec3 offset;
	Field0x198* selectedEntry;
	if (m_unk0x36c > 1 && !m_unk0x5d8 && !m_unk0x5dc) {
		LegoU32 currentIndex = 0;
		selectedEntry = m_unk0x198;

		if (m_unk0x36c < 4) {
			selectedEntry = p_unk0x04;
			currentIndex = p_unk0x04 - m_unk0x198;
		}

		LegoU32 entryIndex = g_raceStateField0x3e8ContactEntryIndices0x4b0d50[currentIndex];
		if (m_unk0x198[entryIndex].m_flags0x048 & 1) {
			LegoU32 upperIndex;
			if (entryIndex < currentIndex) {
				upperIndex = currentIndex;
			}
			else {
				upperIndex = entryIndex;
				entryIndex = currentIndex;
			}

			const GolVec3& upper = m_unk0x198[upperIndex].m_unk0x030;
			const GolVec3& lower = m_unk0x198[entryIndex].m_unk0x030;
			direction0.m_x = lower.m_x - upper.m_x;
			direction0.m_y = lower.m_y - upper.m_y;
			direction0.m_z = lower.m_z - upper.m_z;
		}
		else {
			direction0.m_x = m_unk0x0e4.GetOrientation().m_m[0][0];
			direction0.m_y = m_unk0x0e4.GetOrientation().m_m[0][1];
			direction0.m_z = m_unk0x0e4.GetOrientation().m_m[0][2];
		}

		entryIndex = g_raceStateField0x3e8ContactEntryIndices0x4b0d60[currentIndex];
		if (m_unk0x198[entryIndex].m_flags0x048 & 1) {
			LegoU32 lowerIndex;
			if (entryIndex > currentIndex) {
				lowerIndex = currentIndex;
			}
			else {
				lowerIndex = entryIndex;
				entryIndex = currentIndex;
			}

			const GolVec3& lower = m_unk0x198[lowerIndex].m_unk0x030;
			const GolVec3& upper = m_unk0x198[entryIndex].m_unk0x030;
			direction1.m_x = upper.m_x - lower.m_x;
			direction1.m_y = upper.m_y - lower.m_y;
			direction1.m_z = upper.m_z - lower.m_z;
		}
		else {
			direction1.m_x = m_unk0x0e4.GetOrientation().m_m[1][0];
			direction1.m_y = m_unk0x0e4.GetOrientation().m_m[1][1];
			direction1.m_z = m_unk0x0e4.GetOrientation().m_m[1][2];
		}

		m_unk0x0e4.FUN_00410a00(direction0, direction1);
	}
	else {
		selectedEntry = p_unk0x04;
	}

	offset.m_x = selectedEntry->m_unk0x030.m_x - selectedEntry->m_unk0x00c.m_x + m_unk0x18c;
	offset.m_y = selectedEntry->m_unk0x030.m_y - selectedEntry->m_unk0x00c.m_y + m_unk0x190;
	offset.m_z = selectedEntry->m_unk0x030.m_z - selectedEntry->m_unk0x00c.m_z + m_unk0x194;

	GolOrientedEntity* entity = &m_unk0x0e4;
	entity->VTable0x04(&position);
	position += offset;
	entity->VTable0x08(position);
	FUN_00448c70();
}

// FUNCTION: LEGORACERS 0x00448660
void RaceState::Racer::Field0x3e8Base0x74c::VTable0x30()
{
	m_flags0x6c0 |= c_flags0x6c0Bit3;
	FUN_00445bb0(-0.003f, 150);
	m_unk0x658 = 0;
	m_unk0x680 = 0;
	m_unk0x67c = 0;
	FUN_00448c70();

	LegoFloat center = m_unk0x198[0].m_unk0x00c.m_x;
	center += m_unk0x198[1].m_unk0x00c.m_x;
	m_unk0x664.m_x = center * 0.5f;

	center = m_unk0x198[0].m_unk0x00c.m_y;
	center += m_unk0x198[1].m_unk0x00c.m_y;
	m_unk0x664.m_y = center * 0.5f;

	center = m_unk0x198[0].m_unk0x00c.m_z;
	center += m_unk0x198[1].m_unk0x00c.m_z;
	m_unk0x664.m_z = center * 0.5f;

	center = m_unk0x198[2].m_unk0x00c.m_x;
	center += m_unk0x198[3].m_unk0x00c.m_x;
	m_unk0x670.m_x = center * 0.5f;

	center = m_unk0x198[2].m_unk0x00c.m_y;
	center += m_unk0x198[3].m_unk0x00c.m_y;
	m_unk0x670.m_y = center * 0.5f;

	center = m_unk0x198[2].m_unk0x00c.m_z;
	center += m_unk0x198[3].m_unk0x00c.m_z;
	m_unk0x670.m_z = center * 0.5f;
}

// FUNCTION: LEGORACERS 0x00448730
void RaceState::Racer::Field0x3e8Base0x74c::VTable0x34()
{
	m_flags0x6c0 &= ~c_flags0x6c0Bit3;
	m_unk0x658 = 0;
	m_unk0x680 = 0;
	m_unk0x67c = 0;
}

// FUNCTION: LEGORACERS 0x00448760
void RaceState::Racer::Field0x3e8Base0x74c::VTable0x40(GolVec3* p_unk0x04)
{
	LegoFloat scale = m_unk0x15c;
	m_unk0x630.m_x = p_unk0x04->m_x * scale;
	LegoFloat y = p_unk0x04->m_y;
	y *= scale;
	m_unk0x630.m_y = y;
	LegoFloat z = p_unk0x04->m_z;
	z *= scale;
	m_unk0x630.m_z = z;
	m_flags0x6c0 |= c_flags0x6c0Bit5;
}

// FUNCTION: LEGORACERS 0x004487a0
void RaceState::Racer::Field0x3e8Base0x74c::VTable0x44()
{
	m_flags0x6c0 &= ~c_flags0x6c0Bit5;
}

// FUNCTION: LEGORACERS 0x004487b0
void RaceState::Racer::Field0x3e8Base0x74c::VTable0x48(GolVec3* p_unk0x04)
{
	LegoFloat scale = m_unk0x15c;
	m_unk0x63c.m_x = p_unk0x04->m_x * scale;
	LegoFloat y = p_unk0x04->m_y;
	y *= scale;
	m_unk0x63c.m_y = y;
	LegoFloat z = p_unk0x04->m_z;
	z *= scale;
	m_unk0x63c.m_z = z;
	m_flags0x6c0 |= c_flags0x6c0Bit6;
}

// FUNCTION: LEGORACERS 0x004487f0
void RaceState::Racer::Field0x3e8Base0x74c::VTable0x4c()
{
	m_flags0x6c0 &= ~c_flags0x6c0Bit6;
}

// FUNCTION: LEGORACERS 0x00448800
void RaceState::Racer::Field0x3e8Base0x74c::VTable0x38()
{
	m_unk0x6e0 = 600;
	m_flags0x6c0 |= c_flags0x6c0Bit7;
}

// FUNCTION: LEGORACERS 0x00448820
void RaceState::Racer::Field0x3e8Base0x74c::VTable0x3c()
{
	m_unk0x6e0 = 0;
	m_flags0x6c0 &= ~c_flags0x6c0Bit7;
}

// FUNCTION: LEGORACERS 0x00449060
GolOrientedEntity* RaceState::Racer::Field0x3e8Base0x74c::VTable0x08()
{
	return m_unk0x13c;
}

// FUNCTION: LEGORACERS 0x004490b0
void RaceState::Racer::Field0x3e8Base0x74c::FUN_004490b0(GolVec3* p_unk0x04)
{
	FUN_00447880();
	FUN_004474c0();

	GolVec3 position;
	m_unk0x13c->VTable0x04(&position);

	GolVec3 targetPosition;
	targetPosition.m_x = position.m_x + p_unk0x04->m_x;
	targetPosition.m_y = position.m_y + p_unk0x04->m_y;
	targetPosition.m_z = position.m_z + p_unk0x04->m_z;
	m_unk0x13c->VTable0x08(targetPosition);

	m_unk0x0e4.VTable0x08(targetPosition);
	FUN_004478b0(0, !(m_flags0x6c0 & c_flags0x6c0Bit12));

	if (m_unk0x3ec) {
		m_unk0x13c->VTable0x08(position);
		m_unk0x0e4.VTable0x08(position);
	}
}
