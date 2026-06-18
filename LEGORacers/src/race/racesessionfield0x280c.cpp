#include "core/gol.h"
#include "race/racesession.h"
#include "render/gold3drenderdevice.h"
#include "render/rectangle.h"

#include <stdlib.h>

DECOMP_SIZE_ASSERT(RaceSession::Field0x280c, 0x30)

// FUNCTION: LEGORACERS 0x0042f3b0
RaceSession::Field0x280c::Field0x280c()
{
	m_renderer = NULL;
	m_unk0x04 = NULL;
	m_unk0x08 = NULL;
	m_unk0x0c = 0;
	m_unk0x10 = 0.0f;
	m_unk0x14 = 0;
	m_unk0x18 = NULL;
	m_unk0x28 = 0;
	m_unk0x2c = 0;
}

// FUNCTION: LEGORACERS 0x0042f3e0
RaceSession::Field0x280c::~Field0x280c()
{
	FUN_0042f430();
}

// FUNCTION: LEGORACERS 0x0042f430
void RaceSession::Field0x280c::FUN_0042f430()
{
	m_unk0x1c.Reset();
	AwakeKite0x20* field0x08 = m_unk0x08;
	m_renderer = NULL;
	m_unk0x28 = 0;

	if (field0x08) {
		m_unk0x04->VTable0x68(field0x08);
		m_unk0x08 = NULL;
	}

	LegoS32* field0x18 = m_unk0x18;
	m_unk0x04 = NULL;
	m_unk0x0c = 0;
	m_unk0x10 = 0;
	m_unk0x14 = 0;

	if (field0x18) {
		delete[] field0x18;
		m_unk0x18 = NULL;
	}
}

// FUNCTION: LEGORACERS 0x0042f790
void RaceSession::Field0x280c::FUN_0042f790(LegoFloat p_unk0x04)
{
	m_unk0x10 = p_unk0x04;
}

// FUNCTION: LEGORACERS 0x0042f7a0
void RaceSession::Field0x280c::FUN_0042f7a0()
{
	m_renderer->VTable0x64(&m_unk0x1c, m_unk0x28, m_unk0x2c, 25, 1.0f, 1.0f, NULL, 0);

	LegoU32 count = static_cast<LegoU32>(static_cast<LegoFloat>(m_unk0x14) * m_unk0x10);
	for (LegoU32 i = 0; i < count; i++) {
		Rect destRect;
		destRect.m_top = m_unk0x18[i * 2 + 1] - 8;
		destRect.m_bottom = m_unk0x18[i * 2 + 1] + 8;
		destRect.m_left = m_unk0x18[i * 2] - 8;
		destRect.m_right = m_unk0x18[i * 2] + 8;

		m_renderer->VTable0x78(m_unk0x0c, 0, &destRect, NULL);
	}
}
