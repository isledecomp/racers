#include "celestialforge0x90.h"

DECOMP_SIZE_ASSERT(CelestialForge0x90, 0x90)

// FUNCTION: LEGORACERS 0x00440220
CelestialForge0x90::CelestialForge0x90()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00440230
CelestialForge0x90::~CelestialForge0x90()
{
	FUN_004402a0();
}

// FUNCTION: LEGORACERS 0x00440240
void CelestialForge0x90::Reset()
{
	LegoS32 i;

	m_unk0x00 = 0;
	m_unk0x04 = 0;
	m_unk0x08 = 0;
	m_unk0x0c = 0;

	for (i = 0; i < sizeOfArray(m_unk0x10); i++) {
		m_unk0x10[i] = 0;
		m_unk0x28[i] = 0;
	}

	m_unk0x40 = 0;
	m_unk0x44 = 1;
}

// FUNCTION: LEGORACERS 0x004402a0
void CelestialForge0x90::FUN_004402a0()
{
	Reset();
}
