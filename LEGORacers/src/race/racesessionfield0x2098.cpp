#include "decomp.h"
#include "race/racesession.h"

DECOMP_SIZE_ASSERT(RaceSession::Field0x2098, 0x90)

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

// FUNCTION: LEGORACERS 0x00461ba0
void RaceSession::Field0x2098::Destroy()
{
	if (m_unk0x5c) {
		m_unk0x5c->VTable0x10(3);
		m_unk0x5c = NULL;
	}

	if (m_unk0x60) {
		m_unk0x60->VTable0x10(3);
		m_unk0x60 = NULL;
	}

	if (m_unk0x64) {
		m_unk0x64->VTable0x10(3);
		m_unk0x64 = NULL;
	}

	if (m_unk0x68) {
		m_unk0x68->VTable0x10(3);
		m_unk0x68 = NULL;
	}

	if (m_unk0x6c) {
		delete[] m_unk0x6c;
		m_unk0x6c = NULL;
	}

	if (m_unk0x70) {
		m_unk0x70->VTable0x10(3);
		m_unk0x70 = NULL;
	}

	if (m_unk0x74) {
		m_unk0x74->VTable0x10(3);
		m_unk0x74 = NULL;
	}

	if (m_unk0x78) {
		m_unk0x78->VTable0x10(3);
		m_unk0x78 = NULL;
	}

	if (m_unk0x7c) {
		m_unk0x7c->VTable0x10(3);
		m_unk0x7c = NULL;
	}

	if (m_unk0x80) {
		m_unk0x80->VTable0x10(3);
		m_unk0x80 = NULL;
	}

	if (m_unk0x84) {
		m_unk0x84->VTable0x10(3);
		m_unk0x84 = NULL;
	}

	if (m_unk0x88) {
		m_unk0x88->VTable0x10(3);
		m_unk0x88 = NULL;
	}

	if (m_unk0x8c) {
		m_unk0x8c->VTable0x10(3);
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

// STUB: LEGORACERS 0x00461cc0
void RaceSession::Field0x2098::FUN_00461cc0(LegoU32)
{
	STUB(0x00461cc0);
}
