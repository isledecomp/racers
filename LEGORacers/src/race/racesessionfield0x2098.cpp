#include "decomp.h"
#include "race/racesession.h"

DECOMP_SIZE_ASSERT(RaceSession::Field0x2098, 0x90)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::Resource, 0x20)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::Resource0x24, 0x24)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::Resource0x2c, 0x2c)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::Resource0x30, 0x30)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::Resource0x34, 0x34)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::Resource0x38, 0x38)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::Resource0x48, 0x48)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::Resource0x5c, 0x5c)
DECOMP_SIZE_ASSERT(RaceSession::Field0x2098::Resource0x64, 0x64)

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RaceSession::Field0x2098::Resource::VTable0x00(RaceState::Racer*)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RaceSession::Field0x2098::Resource::VTable0x04(undefined4)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RaceSession::Field0x2098::Resource::VTable0x08(RaceState::Racer*)
{
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void RaceSession::Field0x2098::Resource::VTable0x0c()
{
}

// FUNCTION: LEGORACERS 0x0045ed40
RaceSession::Field0x2098::Resource::Resource()
{
	m_unk0x04 = NULL;
	m_eventIds[0] = -1;
	m_eventIds[1] = -1;
	m_eventIds[2] = -1;
	m_state0x18 = 0;
	m_unk0x14 = 0;
	m_flags0x1c = 0;
}

// FUNCTION: LEGORACERS 0x0045ed90
RaceSession::Field0x2098::Resource::~Resource()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0045eda0
void RaceSession::Field0x2098::Resource::Reset()
{
	m_unk0x04 = NULL;
	m_eventIds[0] = -1;
	m_eventIds[1] = -1;
	m_eventIds[2] = -1;
	m_state0x18 = 0;
	m_unk0x14 = 0;
}

// FUNCTION: LEGORACERS 0x0045edc0
void RaceSession::Field0x2098::Resource::VTable0x14(LegoU32)
{
	if (m_state0x18 == c_state0x18Five) {
		VTable0x0c();
	}
}

// FUNCTION: LEGORACERS 0x0045edd0
void RaceSession::Field0x2098::Resource::FUN_0045edd0(LegoU32 p_unk0x04, LegoU32 p_unk0x08)
{
	LegoS32 current = -1;
	LegoS32 next = -1;

	switch (p_unk0x04) {
	case 2:
		p_unk0x04 = 0;
		break;
	case 3:
		p_unk0x04 = 1;
		break;
	case 4:
		p_unk0x04 = 2;
		break;
	default:
		p_unk0x04 = 3;
		break;
	}

	if (p_unk0x04 != 3) {
		current = m_eventIds[p_unk0x04];
	}

	if (p_unk0x08 != 3) {
		next = m_eventIds[p_unk0x08];
	}

	if (current != -1) {
		if (next != -1) {
			m_unk0x04->FUN_00462580(next, current, NULL);
		}
		else {
			m_unk0x04->FUN_00462140(current, NULL);
		}
	}
	else if (next != -1) {
		m_unk0x04->FUN_00461ef0(next, NULL);
	}
}

// FUNCTION: LEGORACERS 0x0045eee0 FOLDED
void RaceSession::Field0x2098::Resource::FUN_0045eee0(RaceState::Racer* p_racer)
{
	LegoU8 flags = m_flags0x1c;
	if (flags & c_flags0x1cBit2) {
		LegoU32 state = m_state0x18;
		if (state == c_state0x18One || state == c_state0x18Four) {
			VTable0x00(p_racer);
			if (m_flags0x1c & c_flags0x1cBit1) {
				return;
			}

			VTable0x08(p_racer);
			return;
		}
	}

	if (m_state0x18 != c_state0x18One && !(flags & c_flags0x1cBit1)) {
		VTable0x08(p_racer);
	}
}

// FUNCTION: LEGORACERS 0x0045ef40
RaceSession::Field0x2098::Field0x2098()
{
	m_unk0x5c = NULL;
	m_unk0x60 = NULL;
	m_unk0x64 = NULL;
	m_unk0x68 = NULL;
	m_unk0x6c = NULL;
	m_unk0x70 = NULL;
	m_unk0x74 = NULL;
	m_unk0x78 = NULL;
	m_unk0x7c = NULL;
	m_unk0x80 = NULL;
	m_unk0x84 = NULL;
	m_unk0x88 = NULL;
	m_unk0x8c = NULL;
	m_unk0x00 = 0;
	m_unk0x04 = 0;
	m_unk0x08 = 0;
	m_unk0x0c = 0;
	m_unk0x10 = 0;
	m_unk0x14 = 0;
	m_unk0x20 = 0;
	m_unk0x24 = 0;
}

// FUNCTION: LEGORACERS 0x0045ef90
RaceSession::Field0x2098::~Field0x2098()
{
	Destroy();
}

// STUB: LEGORACERS 0x0045efa0
void RaceSession::Field0x2098::FUN_0045efa0(void*)
{
	STUB(0x45efa0);
}

// FUNCTION: LEGORACERS 0x00461ba0
void RaceSession::Field0x2098::Destroy()
{
	if (m_unk0x5c) {
		delete[] m_unk0x5c;
		m_unk0x5c = NULL;
	}

	if (m_unk0x60) {
		delete[] m_unk0x60;
		m_unk0x60 = NULL;
	}

	if (m_unk0x64) {
		delete[] m_unk0x64;
		m_unk0x64 = NULL;
	}

	if (m_unk0x68) {
		delete[] m_unk0x68;
		m_unk0x68 = NULL;
	}

	if (m_unk0x6c) {
		delete[] m_unk0x6c;
		m_unk0x6c = NULL;
	}

	if (m_unk0x70) {
		delete[] m_unk0x70;
		m_unk0x70 = NULL;
	}

	if (m_unk0x74) {
		delete[] m_unk0x74;
		m_unk0x74 = NULL;
	}

	if (m_unk0x78) {
		delete[] m_unk0x78;
		m_unk0x78 = NULL;
	}

	if (m_unk0x7c) {
		delete[] m_unk0x7c;
		m_unk0x7c = NULL;
	}

	if (m_unk0x80) {
		delete[] m_unk0x80;
		m_unk0x80 = NULL;
	}

	if (m_unk0x84) {
		delete[] m_unk0x84;
		m_unk0x84 = NULL;
	}

	if (m_unk0x88) {
		delete[] m_unk0x88;
		m_unk0x88 = NULL;
	}

	if (m_unk0x8c) {
		delete[] m_unk0x8c;
		m_unk0x8c = NULL;
	}

	m_unk0x00 = 0;
	m_unk0x04 = 0;
	m_unk0x08 = 0;
	m_unk0x0c = 0;
	m_unk0x10 = 0;
	m_unk0x14 = 0;
	m_unk0x20 = 0;
	m_unk0x24 = 0;
}

// FUNCTION: LEGORACERS 0x00461cc0
void RaceSession::Field0x2098::FUN_00461cc0(LegoU32 p_elapsedMs)
{
	LegoU32 i;

	if (m_unk0x5c) {
		for (i = 0; i < m_unk0x28; i++) {
			m_unk0x5c[i].VTable0x14(p_elapsedMs);
		}
	}

	if (m_unk0x60) {
		for (i = 0; i < m_unk0x2c; i++) {
			m_unk0x60[i].VTable0x14(p_elapsedMs);
		}
	}

	if (m_unk0x64) {
		for (i = 0; i < m_unk0x30; i++) {
			m_unk0x64[i].VTable0x14(p_elapsedMs);
		}
	}

	if (m_unk0x68) {
		for (i = 0; i < m_unk0x34; i++) {
			m_unk0x68[i].VTable0x14(p_elapsedMs);
		}
	}

	if (m_unk0x70) {
		for (i = 0; i < m_unk0x3c; i++) {
			m_unk0x70[i].VTable0x14(p_elapsedMs);
		}
	}

	if (m_unk0x74) {
		for (i = 0; i < m_unk0x40; i++) {
			m_unk0x74[i].VTable0x14(p_elapsedMs);
		}
	}

	if (m_unk0x78) {
		for (i = 0; i < m_unk0x4c; i++) {
			m_unk0x78[i].VTable0x14(p_elapsedMs);
		}
	}

	if (m_unk0x7c) {
		for (i = 0; i < m_unk0x44; i++) {
			m_unk0x7c[i].VTable0x14(p_elapsedMs);
		}
	}

	if (m_unk0x80) {
		for (i = 0; i < m_unk0x48; i++) {
			m_unk0x80[i].VTable0x14(p_elapsedMs);
		}
	}

	if (m_unk0x84) {
		for (i = 0; i < m_unk0x50; i++) {
			m_unk0x84[i].VTable0x14(p_elapsedMs);
		}
	}

	if (m_unk0x88) {
		for (i = 0; i < m_unk0x54; i++) {
			m_unk0x88[i].VTable0x14(p_elapsedMs);
		}
	}

	if (m_unk0x8c) {
		LegoU32 count = m_unk0x58;

		for (i = 0; i < count; i++) {
			m_unk0x8c[i].VTable0x14(p_elapsedMs);
			count = m_unk0x58;
		}
	}
}

// FUNCTION: LEGORACERS 0x00462c60
void RaceSession::Field0x2098::FUN_00462c60()
{
	LegoU32 i;

	if (m_unk0x5c) {
		for (i = 0; i < m_unk0x28; i++) {
			m_unk0x5c[i].SetState0x18(Resource::c_state0x18Five);
		}
	}

	if (m_unk0x60) {
		for (i = 0; i < m_unk0x2c; i++) {
			m_unk0x60[i].SetState0x18(Resource::c_state0x18Five);
		}
	}

	if (m_unk0x64) {
		for (i = 0; i < m_unk0x30; i++) {
			m_unk0x64[i].SetState0x18(Resource::c_state0x18Five);
		}
	}

	if (m_unk0x68) {
		for (i = 0; i < m_unk0x34; i++) {
			m_unk0x68[i].SetState0x18(Resource::c_state0x18Five);
		}
	}

	if (m_unk0x70) {
		for (i = 0; i < m_unk0x3c; i++) {
			m_unk0x70[i].SetState0x18(Resource::c_state0x18Five);
		}
	}

	if (m_unk0x74) {
		for (i = 0; i < m_unk0x40; i++) {
			m_unk0x74[i].SetState0x18(Resource::c_state0x18Five);
		}
	}

	if (m_unk0x78) {
		for (i = 0; i < m_unk0x4c; i++) {
			m_unk0x78[i].SetState0x18(Resource::c_state0x18Five);
		}
	}

	if (m_unk0x84) {
		for (i = 0; i < m_unk0x50; i++) {
			m_unk0x84[i].SetState0x18(Resource::c_state0x18Five);
		}
	}

	FUN_00461cc0(0);
}

// FUNCTION: LEGORACERS 0x00462da0
void RaceSession::Field0x2098::FUN_00462da0(RaceState::Racer* p_racer)
{
	LegoU32 i;

	if (m_unk0x7c) {
		for (i = 0; i < m_unk0x44; i++) {
			Resource* resource = &m_unk0x7c[i];
			resource->FUN_0045eee0(p_racer);
		}
	}

	if (m_unk0x80) {
		for (i = 0; i < m_unk0x48; i++) {
			Resource* resource = &m_unk0x80[i];
			resource->FUN_0045eee0(p_racer);
		}
	}

	if (m_unk0x88) {
		for (i = 0; i < m_unk0x54; i++) {
			Resource* resource = &m_unk0x88[i];
			resource->FUN_0045eee0(p_racer);
		}
	}

	if (m_unk0x8c) {
		LegoU32 count = m_unk0x58;

		for (i = 0; i < count; i++) {
			Resource* resource = &m_unk0x8c[i];
			resource->FUN_0045eee0(p_racer);
			count = m_unk0x58;
		}
	}
}
