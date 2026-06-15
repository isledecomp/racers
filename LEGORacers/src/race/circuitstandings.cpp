#include "race/circuitstandings.h"

#include <memory.h>

DECOMP_SIZE_ASSERT(CircuitStandings, 0x48)

// GLOBAL: LEGORACERS 0x004b0b58
const LegoU32 g_unk0x004b0b58[6] = {30, 20, 10, 3, 2, 1};

// FUNCTION: LEGORACERS 0x00440220
CircuitStandings::CircuitStandings()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00440230
CircuitStandings::~CircuitStandings()
{
	Shutdown();
}

// FUNCTION: LEGORACERS 0x00440240
void CircuitStandings::Reset()
{
	LegoS32 i;

	m_unk0x00 = 0;
	m_context = NULL;
	m_unk0x08 = 0;
	m_unk0x0c = 0;

	for (i = 0; i < sizeOfArray(m_points); i++) {
		m_points[i] = 0;
		m_unk0x28[i] = 0;
	}

	m_unk0x40 = 0;
	m_unk0x44 = 1;
}

// FUNCTION: LEGORACERS 0x00440270
undefined4 CircuitStandings::SetContext(LegoRacers::Context* p_context)
{
	LegoRacers::Context* previous = m_context;

	if (previous) {
		Shutdown();
		previous = p_context;
	}

	m_context = p_context;
	return (undefined4) previous;
}

// FUNCTION: LEGORACERS 0x004402a0
void CircuitStandings::Shutdown()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004402b0
void CircuitStandings::FUN_004402b0()
{
	undefined4* values = m_unk0x28;
	LegoS32 remaining = sizeOfArray(m_unk0x28);
	do {
		*values++ = 0;
	} while (--remaining);
}

// FUNCTION: LEGORACERS 0x004402c0
void CircuitStandings::FUN_004402c0(LegoU32 p_unk0x04, LegoU32 p_unk0x08)
{
	m_unk0x28[p_unk0x04] = g_unk0x004b0b58[p_unk0x08];
	m_points[p_unk0x04] += g_unk0x004b0b58[p_unk0x08];
}

// FUNCTION: LEGORACERS 0x004402f0
undefined4 CircuitStandings::GetPoints(LegoU32 p_index)
{
	return m_points[p_index];
}

// FUNCTION: LEGORACERS 0x00440300
LegoS32 CircuitStandings::GetRank(LegoU32 p_index)
{
	LegoS32 result = 0;

	for (LegoU32 i = 0; i < sizeOfArray(m_points); i++) {
		if (i != p_index && m_points[i] > m_points[p_index]) {
			result++;
		}
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00440330
void CircuitStandings::FUN_00440330(LegoU32 p_elapsedMs)
{
	if (p_elapsedMs > m_unk0x40) {
		m_unk0x40 = 400;
	}
	else {
		m_unk0x40 -= p_elapsedMs;
	}
}

// STUB: LEGORACERS 0x00440350
void CircuitStandings::FUN_00440350(LegoBool32)
{
	STUB(0x00440350);
}

// FUNCTION: LEGORACERS 0x00440860
void CircuitStandings::ClearPoints()
{
	for (LegoS32 i = 0; i < sizeOfArray(m_points); i++) {
		m_points[i] = 0;
		m_unk0x28[i] = 0;
	}
}
