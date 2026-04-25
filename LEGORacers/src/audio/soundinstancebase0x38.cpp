#include "audio/soundinstancebase0x38.h"

DECOMP_SIZE_ASSERT(SoundInstanceBase0x38, 0x38)

// GLOBAL: LEGORACERS 0x004afab8
LegoFloat g_unk0x4afab8 = 1.0f;

// GLOBAL: LEGORACERS 0x004afabc
LegoFloat g_unk0x4afabc = 0.0f;

// GLOBAL: LEGORACERS 0x004afac0
LegoFloat g_unk0x4afac0 = 1.0f;

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void SoundInstanceBase0x38::VTable0x08()
{
}

// FUNCTION: LEGORACERS 0x00417bf0
SoundInstanceBase0x38::SoundInstanceBase0x38()
{
	m_unk0x04 = g_unk0x4afab8;
	m_unk0x08 = g_unk0x4afac0;
	m_unk0x0c = g_unk0x4afab8;
	m_unk0x10 = g_unk0x4afabc;
	m_unk0x14 = g_unk0x4afac0;
	m_unk0x18 = 0.0f;
	m_unk0x1c = 0.0f;
	m_unk0x20 = 0.0f;
	m_unk0x24 = 0.0f;
	m_unk0x28 = 0.0f;
	m_unk0x2c = 0.0f;
	m_unk0x30 = 8.0f;
	m_unk0x34 = 1024.0f;
}

// FUNCTION: LEGORACERS 0x00417c70
SoundInstanceBase0x38::~SoundInstanceBase0x38()
{
}

// STUB: LEGORACERS 0x00417ff0
void SoundInstanceBase0x38::VTable0x18(undefined4)
{
	STUB(0x417ff0);
}

// FUNCTION: LEGORACERS 0x0044e7e0 FOLDED
undefined4 SoundInstanceBase0x38::VTable0x0c()
{
	return 0;
}

// FUNCTION: LEGORACERS 0x0044e7e0 FOLDED
undefined4 SoundInstanceBase0x38::VTable0x10()
{
	return 0;
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void SoundInstanceBase0x38::VTable0x04(undefined4)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void SoundInstanceBase0x38::VTable0x14(undefined4)
{
}
