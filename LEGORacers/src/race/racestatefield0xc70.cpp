#include "race/racestate.h"

#include <math.h>

extern LegoU16 g_unk0x004befec[1024];
extern LegoU32 g_unk0x004c6ee4;
extern LegoFloat g_carBuildPreviewMouseScale;
extern const LegoFloat g_violetShoalTwo;

// GLOBAL: LEGORACERS 0x004b0064
extern const LegoFloat g_unk0x004b0064 = 54.0f;

// GLOBAL: LEGORACERS 0x004b006c
extern const LegoFloat g_unk0x004b006c = 0.04f;

// GLOBAL: LEGORACERS 0x004b0070
extern const LegoFloat g_unk0x004b0070 = 0.2f;

// GLOBAL: LEGORACERS 0x004b0074
extern const LegoFloat g_unk0x004b0074 = 1.0f;

// GLOBAL: LEGORACERS 0x004b007c
extern const LegoFloat g_unk0x004b007c = 0.050000001f;

// GLOBAL: LEGORACERS 0x004c4810
LegoFloat g_unk0x004c4810;

// FUNCTION: LEGORACERS 0x0041fb70
void RaceState::Racer::Field0xc70::Destroy()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0041fb80
void RaceState::Racer::Field0xc70::Reset()
{
	m_unk0x000 = NULL;
	m_unk0x004 = NULL;
	m_unk0x008 = 0.0f;
	m_unk0x00c = 0.0f;
	m_unk0x010 = 0.0f;
	m_unk0x014 = 0;
	m_unk0x02c = 0;
	m_unk0x018 = 0.0f;
	m_unk0x01c = 0.0f;
	m_unk0x020 = 0;
	m_unk0x024 = 0;
	m_unk0x034.m_x = 0.0f;
	m_unk0x034.m_y = 0.0f;
	m_unk0x034.m_z = 0.0f;
	m_unk0x040.m_x = 0.0f;
	m_unk0x040.m_y = 0.0f;
	m_unk0x040.m_z = 0.0f;
	m_unk0x040.m_w = 0.0f;
	m_unk0x028 = 0;
	m_unk0x030 = 0;
	m_unk0x050 = NULL;
}

// FUNCTION: LEGORACERS 0x0041fbd0
void RaceState::Racer::Field0xc70::FUN_0041fbd0(Field0x3e8* p_unk0x04)
{
	if (m_field0x000) {
		Destroy();
	}
	m_field0x000 = p_unk0x04;
}

// FUNCTION: LEGORACERS 0x0041fc00
void RaceState::Racer::Field0xc70::FUN_0041fc00(LegoU32 p_elapsedMs)
{
	LegoU32 flags = m_unk0x014;
	m_unk0x008 = m_unk0x00c;
	LegoU32 countdown = m_unk0x020;
	flags &= ~c_flags0x014Bit1;
	m_unk0x014 = flags;

	LegoU32 elapsedMs = p_elapsedMs;
	if (elapsedMs > countdown) {
		if (flags & c_flags0x014Bit4) {
			g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & 0x3ff;
			m_unk0x020 = static_cast<LegoS32>(g_unk0x004befec[g_unk0x004c6ee4]) % 500;

			g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & 0x3ff;
			LegoS32 random = static_cast<LegoS32>(g_unk0x004befec[g_unk0x004c6ee4]) % 400;
			m_unk0x018 = static_cast<LegoFloat>(random) * g_carBuildPreviewMouseScale - g_violetShoalTwo;

			g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & 0x3ff;
			random = static_cast<LegoS32>(g_unk0x004befec[g_unk0x004c6ee4]) % 200;
			m_unk0x01c = static_cast<LegoFloat>(random) * g_carBuildPreviewMouseScale - 1.0f;
		}
	}
	else {
		m_unk0x020 = countdown - elapsedMs;
	}

	flags = m_unk0x014;
	if (flags & c_flags0x014Bit2) {
		if (m_unk0x000->m_unk0x618 < 0.03f) {
			m_unk0x02c = 0;
			FUN_004202c0();
		}
		else {
			m_unk0x02c += elapsedMs;
		}
	}
	else if (flags & c_flags0x014Bit3) {
		LegoU32 timerMs = m_unk0x02c;
		timerMs += elapsedMs;
		LegoU32 compareMs = timerMs;
		m_unk0x02c = timerMs;
		if (compareMs >= 300) {
			flags &= ~c_flags0x014Bit3;
			m_unk0x02c = 0;
			m_unk0x014 = flags;
		}
	}

	flags = m_unk0x014;
	if ((flags & c_flags0x014Bit0) && m_unk0x000->m_unk0x3ec) {
		flags |= c_flags0x014Bit8;
		m_unk0x014 = flags;
	}

	FUN_0041fee0();
	FUN_004201e0();
}

// FUNCTION: LEGORACERS 0x0041fd60
void RaceState::Racer::Field0xc70::FUN_0041fd60(LegoU32)
{
	if (m_unk0x000->m_unk0x618 > 0.0f) {
		m_unk0x010 = -(g_unk0x004b0064 + g_unk0x004b0064);
	}
	else {
		m_unk0x010 = 0.0f;
	}

	FUN_0041fee0();
	FUN_004201e0();
}

// FUNCTION: LEGORACERS 0x0041fdb0
void RaceState::Racer::Field0xc70::FUN_0041fdb0(LegoU32 p_elapsedMs)
{
	Field0x000* field0x000 = m_unk0x000;
	m_unk0x028 += p_elapsedMs;

	if (field0x000->m_flags0x6c0 & Field0x000::c_flags0x6c0Bit1) {
		LegoU32 flags = m_unk0x014;
		m_unk0x028 = 0;
		m_unk0x014 = flags & ~c_flags0x014Bit5;
		return;
	}

	LegoU32 flags = m_unk0x014;
	if (flags & c_flags0x014Bit5) {
		if (m_unk0x028 >= 2000) {
			m_unk0x028 = 0;
			m_unk0x014 = flags & ~c_flags0x014Bit5;
		}
	}
	else {
		if (field0x000->m_unk0x618 > 0.009f || -0.009f > field0x000->m_unk0x618) {
			m_unk0x028 = 0;
		}
		else if (m_unk0x028 >= 1000) {
			m_unk0x028 = 0;
			m_unk0x014 = flags | c_flags0x014Bit5;
		}
	}
}

// FUNCTION: LEGORACERS 0x0041fee0
void RaceState::Racer::Field0xc70::FUN_0041fee0()
{
	if (m_unk0x00c == 0.0f && m_unk0x008 == 0.0f) {
		m_unk0x000->FUN_00446ef0(0.0f);
		m_unk0x008 = 0.0f;
		m_unk0x000->FUN_00448070();
		return;
	}

	if (m_unk0x00c != 0.0f && m_unk0x000->m_unk0x604 < g_unk0x004b006c) {
		LegoFloat value = m_unk0x00c;
		value *= g_unk0x004b0070;
		m_unk0x00c = value;
	}

	LegoFloat magnitude = m_unk0x00c;
	if (magnitude < 0.0f) {
		magnitude = -magnitude;
	}

	LegoU32 flags = m_unk0x014;
	if (flags & c_flags0x014Bit2) {
		if (!m_unk0x000->FUN_0042aea0(m_unk0x00c) || magnitude <= 0.0f) {
			m_unk0x000->FUN_00448070();
			m_unk0x000->FUN_00446ef0(m_unk0x00c);
			return;
		}

		LegoFloat limit = m_unk0x000->FUN_00445cb0();
		LegoFloat value = 1.0f - (magnitude / limit);
		if (value < g_unk0x004b007c) {
			value = g_unk0x004b007c;
		}

		LegoFloat scale;
		LegoFloat amount;
		if (m_unk0x030 == 1) {
			scale = value + value + 1.0f;
			amount = 0.25f;
		}
		else {
			scale = value + 1.0f;
			amount = 0.85f;
		}

		m_unk0x000->FUN_00447f30(scale, amount, 3.1415927f);

		if (magnitude < limit) {
			value = ((limit - magnitude) * 0.5f) * 0.5f + magnitude;
			if (m_unk0x00c < 0.0f) {
				value = -value;
			}
			m_unk0x00c = value;
		}
	}
	else if (!(flags & c_flags0x014Bit1)) {
		LegoFloat limit = m_unk0x000->FUN_0042ae10();

		if (m_unk0x000->FUN_0042aea0(m_unk0x00c) && magnitude < limit && magnitude > 0.0f) {
			m_unk0x000->FUN_00447f30(1.0f - (magnitude / limit) + 1.0f, 0.85f, 0.70709997f);
		}
		else {
			m_unk0x000->FUN_00448070();
		}

		if (magnitude < limit) {
			LegoFloat value = (limit + magnitude) * 0.5f;
			if (m_unk0x00c < 0.0f) {
				value = -value;
			}
			m_unk0x00c = value;
		}
	}

	m_unk0x000->FUN_00446ef0(m_unk0x00c);
}

// STUB: LEGORACERS 0x00420130
void RaceState::Racer::Field0xc70::FUN_00420130(LegoFloat p_unk0x04)
{
	LegoFloat value = p_unk0x04;
	if (m_unk0x014 & c_flags0x014Bit4) {
		value += m_unk0x01c;

		if (value > 1.0f) {
			value = 1.0f;
		}
		else if (value < -1.0f) {
			value = -1.0f;
		}
	}

	if (value < 0.0f) {
		if (m_unk0x000->m_unk0x618 > 0.0f) {
			m_unk0x010 = g_unk0x004b0064 * value * 2.0f;
			return;
		}
	}
	else if (value > 0.0f && m_unk0x000->m_unk0x618 < 0.0f) {
		m_unk0x010 = g_unk0x004b0064 * value * 2.0f;
		return;
	}

	m_unk0x010 = g_unk0x004b0064 * value;
}

// FUNCTION: LEGORACERS 0x004201e0
void RaceState::Racer::Field0xc70::FUN_004201e0()
{
	LegoU32 flags = m_unk0x014;

	if ((flags & c_flags0x014Bit3) && m_unk0x010 > 0.0f) {
		LegoFloat value = m_unk0x010;
		value *= 8.0f;
		m_unk0x010 = value;
	}

	if (flags & c_flags0x014Bit0) {
		if (flags & c_flags0x014Bit8) {
			m_unk0x000->VTable0x14(0.5f * g_unk0x004c4810);
		}
		else {
			m_unk0x000->VTable0x14(g_unk0x004c4810);
		}
	}
	else {
		if (!(flags & c_flags0x014Bit1)) {
			m_unk0x000->VTable0x14(m_unk0x010);
		}
		else {
			LegoFloat value = m_unk0x010;
			value *= g_unk0x004b0074;
			m_unk0x000->VTable0x14(value);
		}
	}
}

// STUB: LEGORACERS 0x00420260
undefined4 RaceState::Racer::Field0xc70::FUN_00420260(LegoBool32 p_unk0x04)
{
	LegoU32 flags = m_unk0x014;
	m_unk0x014 = flags & ~c_flags0x014Bit3;

	if (m_unk0x000->FUN_0042ae20()) {
		m_unk0x014 |= c_flags0x014Bit2;
		m_unk0x02c = 0;
		m_unk0x030 = p_unk0x04;

		if (p_unk0x04) {
			return m_unk0x000->FUN_00449070(0x3ecccccd);
		}
		else {
			return m_unk0x000->FUN_00449070(0x3e99999a);
		}
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x004202c0
undefined4 RaceState::Racer::Field0xc70::FUN_004202c0()
{
	LegoU32 flags = m_unk0x014;
	flags &= ~4;
	m_unk0x014 = flags;
	m_unk0x000->FUN_00448070();

	flags = m_unk0x014;
	flags &= ~8;
	m_unk0x02c = 0;
	m_unk0x014 = flags;
	return m_unk0x000->FUN_00449090();
}

// FUNCTION: LEGORACERS 0x004202f0
GolQuat* RaceState::Racer::Field0xc70::FUN_004202f0(Field0x00c::Entry* p_unk0x04)
{
	LegoU32 flags = m_unk0x014;
	m_unk0x024 = 1000;
	flags |= 0x40;
	m_unk0x004 = p_unk0x04;
	m_unk0x014 = flags;
	FUN_004202c0();

	Field0x00c::Entry* value = m_unk0x004;
	m_unk0x00c = 0;
	m_unk0x050->FUN_004a5220(value);

	m_unk0x050->m_unk0x2c = 1.0f;
	m_unk0x050->FUN_004a5320(static_cast<LegoFloat>(m_unk0x024));

	GolQuat* basis = &m_unk0x040;
	Field0x050* field0x50 = m_unk0x050;
	m_unk0x034 = field0x50->m_unk0x00;
	GolQuat* result = &field0x50->m_unk0x0c;
	basis->m_x = result->m_x;
	basis->m_y = result->m_y;
	basis->m_z = result->m_z;
	basis->m_w = result->m_w;
	return result;
}

// FUNCTION: LEGORACERS 0x00420380
void RaceState::Racer::Field0xc70::FUN_00420380()
{
	LegoU32 flags = m_unk0x014;
	flags &= ~c_flags0x014Bit6;
	m_unk0x004 = NULL;
	m_unk0x014 = flags;

	m_unk0x024 = 0;
	m_unk0x00c = 0.0f;
	m_unk0x010 = 0.0f;
	m_unk0x000->FUN_00446ef0(0.0f);
	m_unk0x000->VTable0x14(0.0f);
}

// STUB: LEGORACERS 0x004203b0
void RaceState::Racer::Field0xc70::FUN_004203b0(LegoU32 p_elapsedMs)
{
	GolVec3 delta;
	GolVec3 referenceDirection;
	GolVec3 pathDirection;
	GolVec3 normalizedDelta;
	GolVec3 targetPosition;
	GolMatrix34 basis;

	m_unk0x000->m_unk0x13c->VTable0x04(&targetPosition);
	delta.m_x = m_unk0x034.m_x - targetPosition.m_x;
	delta.m_y = m_unk0x034.m_y - targetPosition.m_y;
	delta.m_z = m_unk0x034.m_z - targetPosition.m_z;

	LegoFloat distance =
		static_cast<LegoFloat>(sqrt(delta.m_z * delta.m_z + delta.m_y * delta.m_y + delta.m_x * delta.m_x));

	if (distance < 3.0f) {
		m_unk0x000->FUN_0042a730(m_unk0x004);
		m_unk0x000->FUN_0042b0c0();
		m_unk0x000->m_unk0x74c.FUN_004a5320(static_cast<LegoFloat>(m_unk0x024));
		FUN_00420380();
		return;
	}

	m_unk0x008 = m_unk0x00c;
	FUN_0041fdb0(p_elapsedMs);

	if (m_unk0x000->m_unk0x36c < 3) {
		referenceDirection = m_unk0x000->m_unk0x168;
	}
	else {
		referenceDirection = m_unk0x000->m_unk0x13c->m_unk0x28.m_rows[0];
	}

	pathDirection = m_unk0x000->m_unk0x13c->m_unk0x28.m_rows[1];
	LegoBool32 positiveDirection;
	if (pathDirection.m_z * delta.m_z + pathDirection.m_y * delta.m_y + pathDirection.m_x * delta.m_x < 0.0f) {
		pathDirection.m_x = -pathDirection.m_x;
		pathDirection.m_y = -pathDirection.m_y;
		pathDirection.m_z = -pathDirection.m_z;
		positiveDirection = FALSE;
	}
	else {
		positiveDirection = TRUE;
	}

	LegoFloat inverseDistance = 1.0f / distance;
	normalizedDelta.m_x = inverseDistance * delta.m_x;
	normalizedDelta.m_y = inverseDistance * delta.m_y;
	normalizedDelta.m_z = inverseDistance * delta.m_z;

	LegoFloat closingSpeed = pathDirection.m_z * normalizedDelta.m_z + pathDirection.m_y * normalizedDelta.m_y +
							 pathDirection.m_x * normalizedDelta.m_x;
	if (closingSpeed >= 0.00050000002f) {
		m_unk0x00c = distance / (closingSpeed + closingSpeed);
	}
	else {
		m_unk0x00c = 4096.0f;
	}

	if (!positiveDirection) {
		m_unk0x00c = -m_unk0x00c;
	}

	m_unk0x010 = 18.0f;
	if (m_unk0x014 & c_flags0x014Bit5) {
		m_unk0x00c = -m_unk0x00c;
		m_unk0x010 = -54.0f;
	}

	if (distance < 30.0f) {
		if (distance <= 80.0f) {
			m_unk0x024 += 250;
			m_unk0x050->FUN_004a5220(m_unk0x004);
			m_unk0x050->FUN_004a5320(static_cast<LegoFloat>(m_unk0x024));
			m_unk0x034 = m_unk0x050->m_unk0x00;
			m_unk0x040 = m_unk0x050->m_unk0x0c;
		}
	}
	else {
		GolMath::FUN_00449340(&m_unk0x040, &basis.m_m[0][0]);
		if (referenceDirection.m_z * basis.m_m[0][2] + referenceDirection.m_y * basis.m_m[0][1] +
				referenceDirection.m_x * basis.m_m[0][0] <
			0.5f) {
			if (distance <= 80.0f) {
				m_unk0x024 += 250;
				m_unk0x050->FUN_004a5220(m_unk0x004);
				m_unk0x050->FUN_004a5320(static_cast<LegoFloat>(m_unk0x024));
				m_unk0x034 = m_unk0x050->m_unk0x00;
				m_unk0x040 = m_unk0x050->m_unk0x0c;
			}
		}
	}

	FUN_0041fee0();
	FUN_004201e0();
}
