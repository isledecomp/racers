#include "audio/spatialsoundinstance.h"
#include "race/racestate.h"

DECOMP_SIZE_ASSERT(RaceState::Racer::Field0xc70::Field0x000, 0x868)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0xc70::Field0x000::Field0x13c, 0x4c)

// GLOBAL: LEGORACERS 0x004b0d80
LegoU32 g_unk0x004b0d80 = 0x3e4ccccd;

// GLOBAL: LEGORACERS 0x004b0cd0
extern const LegoFloat g_unk0x004b0cd0 = 40.0f;

// GLOBAL: LEGORACERS 0x004b0cd4
extern const LegoFloat g_unk0x004b0cd4 = 4096.0f;

// GLOBAL: LEGORACERS 0x004b0430
extern const LegoFloat g_unk0x004b0430 = 30.0f;

// GLOBAL: LEGORACERS 0x004b0434
extern const LegoFloat g_unk0x004b0434 = 300.0f;

// GLOBAL: LEGORACERS 0x004b046c
extern const LegoFloat g_unk0x004b046c = 0.050000001f;

// GLOBAL: LEGORACERS 0x004b0470
extern const LegoFloat g_unk0x004b0470 = 0.155f;

// GLOBAL: LEGORACERS 0x004b0550
extern const LegoFloat g_unk0x004b0550 = 0.85000002f;

// GLOBAL: LEGORACERS 0x004b0554
extern const LegoFloat g_unk0x004b0554 = 0.89999998f;

extern LegoFloat g_cosineTable[1024];

// FUNCTION: LEGORACERS 0x0042a730
void RaceState::Racer::Field0xc70::Field0x000::FUN_0042a730(Field0x00c::Entry* p_entry)
{
	m_unk0x744 = TRUE;
	m_unk0x74c.FUN_004a5220(p_entry);

	GolVec3 position = p_entry->m_unk0x024;
	GolQuat rotation = p_entry->m_unk0x030;

	m_unk0x13c->VTable0x08(&position);
	GolMath::FUN_00449340(&rotation, &m_unk0x13c->m_unk0x28.m_m[0][0]);
	m_unk0x13c->VTable0x2c(&m_unk0x014, &m_unk0x020);

	for (LegoS32 i = 0; i < 4; i++) {
		m_unk0x13c->VTable0x2c(&m_unk0x370[i], &m_unk0x3a0[i]);
	}
}

// FUNCTION: LEGORACERS 0x0042ae10
LegoFloat RaceState::Racer::Field0xc70::Field0x000::FUN_0042ae10()
{
	return FUN_00445cb0();
}

// FUNCTION: LEGORACERS 0x0042ae20
LegoBool32 RaceState::Racer::Field0xc70::Field0x000::FUN_0042ae20()
{
	if (m_unk0x3ec) {
		return FALSE;
	}

	if (!(m_flags0x6c0 & c_flags0x6c0Bit3) && m_unk0x36c < 3) {
		return FALSE;
	}

	LegoFloat dot = m_unk0x13c->m_unk0x28.m_rows[0].m_x * m_unk0x5f8.m_x +
					m_unk0x13c->m_unk0x28.m_rows[0].m_y * m_unk0x5f8.m_y +
					m_unk0x13c->m_unk0x28.m_rows[0].m_z * m_unk0x5f8.m_z;
	if (dot <= g_unk0x004b0550) {
		return FALSE;
	}

	if (m_unk0x618 < g_unk0x004b046c) {
		return FALSE;
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0042aea0
LegoBool32 RaceState::Racer::Field0xc70::Field0x000::FUN_0042aea0(LegoFloat p_unk0x04)
{
	LegoFloat dot = m_unk0x13c->m_unk0x28.m_rows[0].m_x * m_unk0x5f8.m_x +
					m_unk0x13c->m_unk0x28.m_rows[0].m_y * m_unk0x5f8.m_y +
					m_unk0x13c->m_unk0x28.m_rows[0].m_z * m_unk0x5f8.m_z;
	if (dot <= 0.0f) {
		return FALSE;
	}

	if ((p_unk0x04 < 0.0f && m_unk0x64c > 0.0f) || (p_unk0x04 > 0.0f && m_unk0x64c < 0.0f)) {
		return FALSE;
	}

	if (!(m_flags0x6c0 & c_flags0x6c0Bit0)) {
		LegoFloat dotValue = dot;
		if (dotValue < g_unk0x004b0554) {
			return FALSE;
		}
	}

	if (m_unk0x3ec) {
		return FALSE;
	}

	if (m_unk0x604 > g_unk0x004b0470) {
		return FALSE;
	}

	return TRUE;
}

// STUB: LEGORACERS 0x0042af90
SpatialSoundInstance* RaceState::Racer::Field0xc70::Field0x000::FUN_0042af90(LegoU32 p_unk0x04)
{
	if (m_unk0x740 != NULL) {
		if (p_unk0x04 == m_unk0x73c) {
			return m_unk0x740;
		}

		FUN_0042b060();
	}

	m_unk0x738 = 0;
	m_unk0x73c = p_unk0x04;
	m_unk0x740 = m_unk0x158->FUN_00443bd0(p_unk0x04);

	if (m_unk0x740 != NULL) {
		GolVec3 position;
		m_unk0x740->SetDistanceRangeWithMinSquared(g_unk0x004b0430 * g_unk0x004b0430, g_unk0x004b0434);
		m_unk0x740->Play(TRUE);
		m_unk0x13c->VTable0x04(&position);
		m_unk0x740->SetPosition(&position);
		m_unk0x740->SetVelocity(m_unk0x008);
	}

	return m_unk0x740;
}

// FUNCTION: LEGORACERS 0x0042b060 FOLDED
void RaceState::Racer::Field0xc70::Field0x000::FUN_0042b060()
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

// FUNCTION: LEGORACERS 0x0042b0c0
void RaceState::Racer::Field0xc70::Field0x000::FUN_0042b0c0()
{
	GolVec3 direction;
	direction.m_x = 0.0f;
	m_unk0x74c.m_unk0x2c = 1.0f;
	direction.m_y = 0.0f;
	direction.m_z = 0.0f;
	m_unk0x74c.FUN_004a5750(&direction);

	m_unk0x7e8 = 1.0f;
	m_unk0x7c4.m_x = 0.0f;
	m_unk0x7c4.m_y = 0.0f;
	m_unk0x7c4.m_z = 0.0f;
	m_unk0x7c4.m_w = 0.0f;
	m_unk0x7ec = 1.0f;
}

// STUB: LEGORACERS 0x00445cb0
LegoFloat RaceState::Racer::Field0xc70::Field0x000::FUN_00445cb0()
{
	STUB(0x00445cb0);
	return 0.0f;
}

// FUNCTION: LEGORACERS 0x00446ef0
void RaceState::Racer::Field0xc70::Field0x000::FUN_00446ef0(LegoFloat p_unk0x04)
{
	if (p_unk0x04 > 0.0f) {
		if (p_unk0x04 < g_unk0x004b0cd0) {
			m_unk0x64c = g_unk0x004b0cd0;
		}
		else if (p_unk0x04 <= g_unk0x004b0cd4) {
			m_unk0x64c = p_unk0x04;
		}
		else {
			m_unk0x64c = 0.0f;
		}
	}
	else if (p_unk0x04 < 0.0f) {
		if (p_unk0x04 > -g_unk0x004b0cd0) {
			m_unk0x64c = -g_unk0x004b0cd0;
		}
		else if (p_unk0x04 >= -g_unk0x004b0cd4) {
			m_unk0x64c = p_unk0x04;
		}
		else {
			m_unk0x64c = 0.0f;
		}
	}
	else {
		m_unk0x64c = 0.0f;
	}
}

// STUB: LEGORACERS 0x00447f30
void RaceState::Racer::Field0xc70::Field0x000::FUN_00447f30(
	LegoFloat p_unk0x04,
	LegoFloat p_unk0x08,
	LegoFloat p_unk0x0c
)
{
	LegoU32 flags = m_flags0x6c0;
	m_unk0x6c4 = p_unk0x04;

	flags |= c_flags0x6c0Bit0;
	m_unk0x6d0 = p_unk0x08;
	m_flags0x6c0 = flags;
	m_unk0x6cc = p_unk0x0c;

	LegoFloat angle = m_unk0x6cc;
	m_unk0x6c8 = g_cosineTable[static_cast<LegoS32>(angle * 162.97466f) & 0x3ff];

	if (m_unk0x6e8 != NULL) {
		return;
	}

	GolVec3 direction;
	direction.m_x = m_unk0x10c.m_x;
	direction.m_y = m_unk0x10c.m_y;
	direction.m_z = m_unk0x10c.m_z;
	if ((flags & c_flags0x6c0Bit3) || m_unk0x3ec) {
		return;
	}

	if (!(flags & c_flags0x6c0Bit10)) {
		LegoFloat dot = m_unk0x5f8.m_z * direction.m_z;
		dot += m_unk0x5f8.m_y * direction.m_y;
		dot += m_unk0x5f8.m_x * direction.m_x;
		if (dot >= g_unk0x004b0554) {
			return;
		}
	}

	if (m_unk0x6ec) {
		m_unk0x6e8 = m_unk0x158->FUN_00443bd0(0x3a);
	}

	if (m_unk0x6e8 != NULL) {
		m_unk0x6e8->SetDistanceRangeWithMinSquared(g_unk0x004b0430 * g_unk0x004b0430, g_unk0x004b0434);
		m_unk0x6e8->SetVolume(0.80000001f);
		m_unk0x6e8->Play(TRUE);
	}
}

// FUNCTION: LEGORACERS 0x00448070
void RaceState::Racer::Field0xc70::Field0x000::FUN_00448070()
{
	LegoU32 flags = m_flags0x6c0;
	RaceResourceManager::Resource* resource = m_resource;

	flags &= ~(c_flags0x6c0Bit0 | c_flags0x6c0Bit9);
	m_unk0x6c8 = -1.0f;
	m_unk0x6cc = 3.1415927f;
	m_flags0x6c0 = flags;

	if (resource != NULL) {
		m_unk0x158->FUN_00443c10(resource);
		m_resource = NULL;
	}
}

// STUB: LEGORACERS 0x00449070
undefined4 RaceState::Racer::Field0xc70::Field0x000::FUN_00449070(undefined4 p_unk0x04)
{
	LegoU32 flags = m_flags0x6c0;
	flags |= c_flags0x6c0Bit10;
	m_flags0x6c0 = flags;

	m_unk0x6d8 = p_unk0x04;
	return p_unk0x04;
}

// FUNCTION: LEGORACERS 0x00449090
undefined4 RaceState::Racer::Field0xc70::Field0x000::FUN_00449090()
{
	LegoU32 flags = m_flags0x6c0;
	flags &= ~c_flags0x6c0Bit10;
	m_flags0x6c0 = flags;

	LegoU32 value = g_unk0x004b0d80;
	m_unk0x6d8 = value;
	return value;
}
