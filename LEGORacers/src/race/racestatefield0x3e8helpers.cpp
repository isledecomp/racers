#include "golmath.h"
#include "race/raceeventtable0x90.h"
#include "race/racestate.h"

#include <string.h>

// GLOBAL: LEGORACERS 0x004b0448
extern const LegoFloat g_unk0x004b0448 = 120.0f;

// GLOBAL: LEGORACERS 0x004b0484
extern const LegoFloat g_unk0x004b0484 = 300.0f;

// GLOBAL: LEGORACERS 0x004b0488
extern const LegoFloat g_unk0x004b0488 = 0.1f;

// GLOBAL: LEGORACERS 0x004b0490
extern const LegoFloat g_unk0x004b0490 = 0.3f;

// GLOBAL: LEGORACERS 0x004b04a0
extern const LegoFloat g_unk0x004b04a0 = 2.75f;

// GLOBAL: LEGORACERS 0x004b04a4
extern const LegoFloat g_unk0x004b04a4 = -0.5f;

// GLOBAL: LEGORACERS 0x004b04b0
extern const LegoFloat g_unk0x004b04b0 = 15.0f;

// GLOBAL: LEGORACERS 0x004b04d0
extern const LegoFloat g_unk0x004b04d0 = 50.0f;

// GLOBAL: LEGORACERS 0x004b054c
extern const LegoFloat g_unk0x004b054c = 0.003f;

// GLOBAL: LEGORACERS 0x004b0b90
extern const LegoFloat g_unk0x004b0b90 = 0.083333336f;

// GLOBAL: LEGORACERS 0x004b0ce4
extern const LegoFloat g_unk0x004b0ce4 = 39.0f;

// GLOBAL: LEGORACERS 0x004b0cf0
extern const LegoFloat g_unk0x004b0cf0 = 110.0f;

// GLOBAL: LEGORACERS 0x004b0cf8
extern const LegoFloat g_unk0x004b0cf8 = 0.2f;

// GLOBAL: LEGORACERS 0x004b0d20
extern const LegoFloat g_unk0x004b0d20 = 6.0f;

// GLOBAL: LEGORACERS 0x004b0d24
extern const LegoFloat g_unk0x004b0d24 = 3.0f;

extern LegoU32 g_unk0x004b0d80;
extern const LegoFloat g_carBuildModelTextureCoordinateScale;
extern const LegoFloat g_unk0x004b0544;

// FUNCTION: LEGORACERS 0x00429120
void RaceState::Racer::Field0x3e8::Reset()
{
	m_unk0x6f0 = NULL;
	m_unk0x6f4 = NULL;
	m_unk0x6f8 = 0;
	m_unk0x6fc = 0;
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
	LegoS32 p_unk0x14,
	undefined4 p_unk0x18,
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
	GolMath::FUN_1002f5a0(p_unk0x10->GetTransform(), &m_unk0x70c);
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

// FUNCTION: LEGORACERS 0x004293c0
void RaceState::Racer::Field0x3e8::FUN_004293c0()
{
	LegoU32 flags = m_flags0x6c0 & ~c_flags0x6c0Bit19;
	m_flags0x6c0 = flags;

	if (m_unk0x744 && !(flags & (c_flags0x6c0Bit1 | c_flags0x6c0Bit16 | c_flags0x6c0Bit18))) {
		m_unk0x7ec = 1.0f;
	}
}

// STUB: LEGORACERS 0x004293f0
void RaceState::Racer::Field0x3e8::VTable0x04(LegoU32)
{
	STUB(0x4293f0);
}

// FUNCTION: LEGORACERS 0x00429770
void RaceState::Racer::Field0x3e8::VTable0x20(GolVec3* p_unk0x04, LegoFloat p_unk0x08)
{
	if (!m_unk0x744) {
		FUN_00448110(p_unk0x04, p_unk0x08);
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
		FUN_00448760(p_unk0x04);
	}
	else {
		FUN_00429990(p_unk0x04);
	}
}

// FUNCTION: LEGORACERS 0x004298d0
void RaceState::Racer::Field0x3e8::VTable0x44()
{
	if (!m_unk0x744) {
		FUN_004487a0();
	}
	else {
		FUN_00429940();
	}
}

// FUNCTION: LEGORACERS 0x004298f0
void RaceState::Racer::Field0x3e8::VTable0x48(GolVec3* p_unk0x04)
{
	if (!m_unk0x744) {
		FUN_004487b0(p_unk0x04);
	}
	else {
		FUN_00429990(p_unk0x04);
	}
}

// FUNCTION: LEGORACERS 0x00429920
void RaceState::Racer::Field0x3e8::VTable0x4c()
{
	if (!m_unk0x744) {
		FUN_004487f0();
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
void RaceState::Racer::Field0x3e8::VTable0x1c(GolVec3* p_unk0x04, LegoFloat p_unk0x08)
{
	if (!m_unk0x744) {
		FUN_004480c0(p_unk0x04, p_unk0x08);
	}
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

// STUB: LEGORACERS 0x00429b40
void RaceState::Racer::Field0x3e8::VTable0x30()
{
	STUB(0x429b40);
}

// FUNCTION: LEGORACERS 0x00429bc0
void RaceState::Racer::Field0x3e8::VTable0x34()
{
	if (!m_unk0x744) {
		FUN_00448730();
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
	FUN_00448800();
	LegoFloat unk0x778 = g_unk0x004b0488;
	m_unk0x7c4.m_w = g_unk0x004b04d0;
	m_unk0x74c.m_unk0x2c = unk0x778;
}

// FUNCTION: LEGORACERS 0x00429c30
void RaceState::Racer::Field0x3e8::VTable0x3c()
{
	if (!m_unk0x744) {
		FUN_00448820();
	}
}

// STUB: LEGORACERS 0x00429c40
void RaceState::Racer::Field0x3e8::VTable0x24(LegoFloat, LegoFloat, undefined4)
{
	STUB(0x429c40);
}

// FUNCTION: LEGORACERS 0x00429cd0
void RaceState::Racer::Field0x3e8::VTable0x2c()
{
	if (!m_unk0x744) {
		FUN_004482e0();
	}
	else {
		m_flags0x6c0 &= ~(c_flags0x6c0Bit1 | c_flags0x6c0Bit2);
	}
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

// FUNCTION: LEGORACERS 0x0042a830
LegoU32 RaceState::Racer::Field0x3e8::VTable0x0c(
	GolVec3* p_unk0x04,
	EventRecord* p_unk0x08,
	undefined4 p_unk0x0c,
	EventContext* p_unk0x10
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

	EventTarget* target = p_unk0x08->m_target;
	if (!target) {
		return TRUE;
	}

	if (target->m_flags0x08 & EventTarget::c_flags0x08Bit18) {
		m_unk0x6f0->m_lapsCompleted = m_unk0x6f0->m_unk0xce0;
	}

	if (target->m_flags0x08 & EventTarget::c_flags0x08Bit3) {
		m_unk0x6f4->FUN_00462580(target->m_unk0x14, target->m_unk0x14, p_unk0x04);
		m_unk0x6f4->FUN_00462ae0(target->m_unk0x14, target->m_unk0x14, m_unk0x6f0);
	}

	return (~target->m_flags0x08 >> 16) & 1;
}

// STUB: LEGORACERS 0x0042a900
void RaceState::Racer::Field0x3e8::VTable0x10()
{
	STUB(0x42a900);
}

// FUNCTION: LEGORACERS 0x0042ad30
void RaceState::Racer::Field0x3e8::VTable0x14(LegoFloat p_unk0x04)
{
	FUN_00448370(m_unk0x72c * p_unk0x04);
}

// FUNCTION: LEGORACERS 0x0042ad50
void RaceState::Racer::Field0x3e8::VTable0x18(LegoFloat p_unk0x04)
{
	FUN_00448390(m_unk0x730 * p_unk0x04);
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

// FUNCTION: LEGORACERS 0x00440970
void RaceState::Racer::Field0x3e8::FUN_00440970()
{
	m_unk0x004 = NULL;
	m_unk0x014.m_x = 0.0f;
	m_unk0x014.m_y = 0.0f;
	m_unk0x014.m_z = 0.0f;
	m_unk0x020.m_x = 0.0f;
	m_unk0x020.m_y = 0.0f;
	m_unk0x020.m_z = 0.0f;

	m_unk0x098[0] = 0;
	m_unk0x098[1] = 0;
	m_unk0x098[2] = 0;
	m_unk0x0a4.m_x = 0.0f;
	m_unk0x0a4.m_y = 0.0f;
	m_unk0x0a4.m_z = 0.0f;
	m_unk0x0b0[0] = 0;
	m_unk0x0b0[1] = 0;
	m_unk0x0b0[2] = 0;
	m_unk0x0b0[3] = 0;
	m_unk0x0b0[4] = 0;
	m_unk0x0b0[5] = 0;

	m_unk0x0c8 = 1.0f;
	m_unk0x0cc = 1.0f;
}

// FUNCTION: LEGORACERS 0x004409f0
void RaceState::Racer::Field0x3e8::FUN_004409f0(GolOrientedEntity* p_unk0x04, LegoFloat p_unk0x08)
{
	if (m_unk0x004 != NULL) {
		FUN_00440970();
	}

	m_unk0x0cc = 1.0f / p_unk0x08;
	m_unk0x004 = p_unk0x04;
	m_unk0x0c8 = p_unk0x08;
	m_unk0x008.m_x = 0.0f;
	m_unk0x008.m_y = 0.0f;
	m_unk0x008.m_z = 0.0f;
	VTable0x00();
	FUN_00440a60();
}

// FUNCTION: LEGORACERS 0x00440a50
void RaceState::Racer::Field0x3e8::FUN_00440a50()
{
	FUN_00440970();
}

// FUNCTION: LEGORACERS 0x00440a60
void RaceState::Racer::Field0x3e8::FUN_00440a60()
{
	m_unk0x004->FUN_00410f30(m_unk0x050, &m_unk0x074);
}

// FUNCTION: LEGORACERS 0x00440da0
void RaceState::Racer::Field0x3e8::FUN_00440da0(GolVec3* p_unk0x04)
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

// FUNCTION: LEGORACERS 0x00441190
void RaceState::Racer::Field0x3e8::FUN_00441190(GolVec3* p_unk0x04)
{
	::memcpy(&m_unk0x014, p_unk0x04, sizeof(m_unk0x014));
	m_unk0x004->VTable0x2c(m_unk0x014, &m_unk0x020);
}

// FUNCTION: LEGORACERS 0x00441210
void RaceState::Racer::Field0x3e8::FUN_00441210(
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

// FUNCTION: LEGORACERS 0x00441260
void RaceState::Racer::Field0x3e8::VTable0x00()
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

// FUNCTION: LEGORACERS 0x00444b40
void RaceState::Racer::Field0x3e8::FUN_00444b40()
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
	m_unk0x174 = 0;
	m_unk0x178 = 0;
	m_unk0x17c = 0;
	m_unk0x180 = 0;
	m_unk0x184 = 0;
	m_unk0x188 = 0;
	m_unk0x630 = 0;
	m_unk0x634 = 0;
	m_unk0x638 = 0;
	m_unk0x63c = 0;
	m_unk0x640 = 0;
	m_unk0x644 = 0;
	m_unk0x18c = 0;
	m_unk0x190 = 0;
	m_unk0x654 = -10.95f;
	m_unk0x194 = g_unk0x004b0cf8;
	m_unk0x60c = 0;
	m_unk0x610 = 0;
	m_unk0x614 = 0;
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
	m_unk0x690 = 0;
	m_unk0x694 = 0;
	m_unk0x698 = 0;
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
void RaceState::Racer::Field0x3e8::FUN_00444d90(
	GolAnimatedEntity* p_unk0x04,
	LegoS32 p_unk0x08,
	undefined4 p_unk0x0c,
	Field0x004* p_unk0x10,
	LegoFloat p_unk0x14,
	LegoFloat p_unk0x18,
	LegoFloat p_unk0x1c,
	LegoFloat p_unk0x20
)
{
	Field0x3e8* field = this;

	if (field->m_unk0x004 != NULL) {
		field->FUN_00444e90();
	}

	field->m_unk0x154 = 1;
	field->m_unk0x140[0] = p_unk0x08;

	if (p_unk0x0c != 0) {
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
void RaceState::Racer::Field0x3e8::FUN_00444e90()
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

// FUNCTION: LEGORACERS 0x00446e60
void RaceState::Racer::Field0x3e8::FUN_00446e60(GolVec3* p_unk0x04, LegoFloat p_unk0x08, LegoFloat p_unk0x0c)
{
	::memcpy(&m_unk0x358, p_unk0x04, sizeof(m_unk0x358));
	m_unk0x364 = p_unk0x08;
	m_unk0x368 = p_unk0x0c;
	FUN_00448c70();
}

// FUNCTION: LEGORACERS 0x00446ea0
void RaceState::Racer::Field0x3e8::FUN_00446ea0(LegoU32 p_unk0x04, GolVec3* p_unk0x08)
{
	GolVec3* source = &m_unk0x370[p_unk0x04];
	*source = *p_unk0x08;
	m_unk0x0e4.VTable0x2c(*source, &m_unk0x3a0[p_unk0x04]);
}

// FUNCTION: LEGORACERS 0x004480c0
void RaceState::Racer::Field0x3e8::FUN_004480c0(GolVec3* p_unk0x04, LegoFloat)
{
	GolVec3 scaled;
	LegoFloat x = p_unk0x04->m_x * m_unk0x0cc;
	scaled.m_y = p_unk0x04->m_y * m_unk0x0cc;
	scaled.m_z = p_unk0x04->m_z * m_unk0x0cc;

	m_unk0x008.m_x += x;
	m_unk0x008.m_y += scaled.m_y;
	m_unk0x008.m_z += scaled.m_z;
}

// FUNCTION: LEGORACERS 0x00448110
void RaceState::Racer::Field0x3e8::FUN_00448110(GolVec3* p_unk0x04, LegoFloat p_unk0x08)
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

// FUNCTION: LEGORACERS 0x00448290
void RaceState::Racer::Field0x3e8::VTable0x28()
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
void RaceState::Racer::Field0x3e8::FUN_004482e0()
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
void RaceState::Racer::Field0x3e8::FUN_00448370(LegoFloat p_unk0x04)
{
	m_unk0x628 = p_unk0x04;
	FUN_004483b0();
}

// FUNCTION: LEGORACERS 0x00448390
void RaceState::Racer::Field0x3e8::FUN_00448390(LegoFloat p_unk0x04)
{
	m_unk0x608 = p_unk0x04;
	FUN_004483b0();
}

// FUNCTION: LEGORACERS 0x004483b0
void RaceState::Racer::Field0x3e8::FUN_004483b0()
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

// FUNCTION: LEGORACERS 0x00448730
void RaceState::Racer::Field0x3e8::FUN_00448730()
{
	m_flags0x6c0 &= ~c_flags0x6c0Bit3;
	m_unk0x658 = 0;
	m_unk0x680 = 0;
	m_unk0x67c = 0;
}

// FUNCTION: LEGORACERS 0x00448760
void RaceState::Racer::Field0x3e8::FUN_00448760(GolVec3* p_unk0x04)
{
	LegoFloat scale = m_unk0x15c;
	m_unk0x630 = p_unk0x04->m_x * scale;
	LegoFloat y = p_unk0x04->m_y;
	y *= scale;
	m_unk0x634 = y;
	LegoFloat z = p_unk0x04->m_z;
	z *= scale;
	m_unk0x638 = z;
	m_flags0x6c0 |= c_flags0x6c0Bit5;
}

// FUNCTION: LEGORACERS 0x004487a0
void RaceState::Racer::Field0x3e8::FUN_004487a0()
{
	m_flags0x6c0 &= ~c_flags0x6c0Bit5;
}

// FUNCTION: LEGORACERS 0x004487b0
void RaceState::Racer::Field0x3e8::FUN_004487b0(GolVec3* p_unk0x04)
{
	LegoFloat scale = m_unk0x15c;
	m_unk0x63c = p_unk0x04->m_x * scale;
	LegoFloat y = p_unk0x04->m_y;
	y *= scale;
	m_unk0x640 = y;
	LegoFloat z = p_unk0x04->m_z;
	z *= scale;
	m_unk0x644 = z;
	m_flags0x6c0 |= c_flags0x6c0Bit6;
}

// FUNCTION: LEGORACERS 0x004487f0
void RaceState::Racer::Field0x3e8::FUN_004487f0()
{
	m_flags0x6c0 &= ~c_flags0x6c0Bit6;
}

// FUNCTION: LEGORACERS 0x00448800
void RaceState::Racer::Field0x3e8::FUN_00448800()
{
	m_unk0x6e0 = 600;
	m_flags0x6c0 |= c_flags0x6c0Bit7;
}

// FUNCTION: LEGORACERS 0x00448820
void RaceState::Racer::Field0x3e8::FUN_00448820()
{
	m_unk0x6e0 = 0;
	m_flags0x6c0 &= ~c_flags0x6c0Bit7;
}

// FUNCTION: LEGORACERS 0x00449060
GolOrientedEntity* RaceState::Racer::Field0x3e8::VTable0x08()
{
	return m_unk0x13c;
}
