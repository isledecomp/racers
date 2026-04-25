#include "celestialforge0x48.h"

DECOMP_SIZE_ASSERT(CelestialForge0x48, 0x48)

// FUNCTION: LEGORACERS 0x00440220
CelestialForge0x48::CelestialForge0x48()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00440230
CelestialForge0x48::~CelestialForge0x48()
{
	FUN_004402a0();
}

// FUNCTION: LEGORACERS 0x00440240
void CelestialForge0x48::Reset()
{
	LegoS32 i;

	m_unk0x00 = 0;
	m_context = NULL;
	m_unk0x08 = 0;
	m_unk0x0c = 0;

	for (i = 0; i < sizeOfArray(m_unk0x10); i++) {
		m_unk0x10[i] = 0;
		m_unk0x28[i] = 0;
	}

	m_unk0x40 = 0;
	m_unk0x44 = 1;
}

// FUNCTION: LEGORACERS 0x00440270
undefined4 CelestialForge0x48::SetContext(LegoRacers::Context* p_context)
{
	LegoRacers::Context* previous = m_context;

	if (previous) {
		FUN_004402a0();
		previous = p_context;
	}

	m_context = p_context;
	return (undefined4) previous;
}

// FUNCTION: LEGORACERS 0x004402a0
void CelestialForge0x48::FUN_004402a0()
{
	Reset();
}
