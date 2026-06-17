#include "golmath.h"
#include "race/racestate.h"

#include <string.h>

// GLOBAL: LEGORACERS 0x004b0448
extern const LegoFloat g_unk0x004b0448 = 120.0f;

// GLOBAL: LEGORACERS 0x004b04b0
extern const LegoFloat g_unk0x004b04b0 = 15.0f;

// GLOBAL: LEGORACERS 0x004b054c
extern const LegoFloat g_unk0x004b054c = 0.003f;

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
	m_unk0x098[3] = 0;
	m_unk0x098[4] = 0;
	m_unk0x098[5] = 0;
	m_unk0x098[6] = 0;
	m_unk0x098[7] = 0;
	m_unk0x098[8] = 0;
	m_unk0x098[9] = 0;
	m_unk0x098[10] = 0;
	m_unk0x098[11] = 0;

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
	m_unk0x5f8 = 1.0f;
	m_unk0x5fc = 0;
	m_unk0x600 = 0;
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
