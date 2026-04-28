#include "peridottrace0x4e0.h"

DECOMP_SIZE_ASSERT(PeridotTrace0x4a8, 0x4a8)
DECOMP_SIZE_ASSERT(PeridotTrace0x4e0, 0x4e0)
DECOMP_SIZE_ASSERT(PeridotTraceActionBase0x34, 0x34)
DECOMP_SIZE_ASSERT(PeridotTraceAction0x34, 0x34)
DECOMP_SIZE_ASSERT(PeridotTraceState0x438, 0x438)
DECOMP_SIZE_ASSERT(PeridotTraceBuffer0x250, 0x250)

// STUB: LEGORACERS 0x0042b290
PeridotTraceBuffer0x250::PeridotTraceBuffer0x250()
{
	// TODO
	STUB(0x42b290);
}

// STUB: LEGORACERS 0x0042b2b0
PeridotTraceBuffer0x250::~PeridotTraceBuffer0x250()
{
	// TODO
	STUB(0x42b2b0);
}

// STUB: LEGORACERS 0x0042e880
PeridotTraceState0x438::PeridotTraceState0x438()
{
	// TODO
	STUB(0x42e880);
}

// STUB: LEGORACERS 0x0042e890
PeridotTraceState0x438::~PeridotTraceState0x438()
{
	// TODO
	STUB(0x42e890);
}

// FUNCTION: LEGORACERS 0x0042f200
void PeridotTraceState0x438::FUN_0042f200(LegoU8 p_unk0x04)
{
	m_unk0x00 = 1;
	m_unk0x24 |= p_unk0x04;
}

// FUNCTION: LEGORACERS 0x0042f250
LegoBool32 PeridotTraceState0x438::FUN_0042f250(LegoU32 p_unk0x04)
{
	LegoBool32 result = FALSE;

	if (!static_cast<LegoU16>(m_unk0x26 & p_unk0x04)) {
		result = TRUE;
		m_unk0x26 |= p_unk0x04;
		m_unk0x00 = result;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0042f280
LegoBool32 PeridotTraceState0x438::FUN_0042f280() const
{
	return m_unk0x26 == 0x0fff;
}

// STUB: LEGORACERS 0x00442660
PeridotTrace0x4a8::PeridotTrace0x4a8()
{
	// TODO
	STUB(0x442660);
}

// STUB: LEGORACERS 0x00442680
PeridotTrace0x4a8::~PeridotTrace0x4a8()
{
	// TODO
	STUB(0x442680);
}

// STUB: LEGORACERS 0x004437e0
PeridotTrace0x4e0::PeridotTrace0x4e0()
{
	// TODO
	STUB(0x4437e0);
}

// STUB: LEGORACERS 0x00443840
PeridotTrace0x4e0::~PeridotTrace0x4e0()
{
	// TODO
	STUB(0x443840);
}

// STUB: LEGORACERS 0x004438e0
void PeridotTrace0x4e0::FUN_004438e0()
{
	// TODO
	STUB(0x4438e0);
}

// STUB: LEGORACERS 0x0044e0a0
PeridotTraceActionBase0x34::~PeridotTraceActionBase0x34()
{
	// TODO
	STUB(0x44e0a0);
}

// STUB: LEGORACERS 0x00450e30
PeridotTraceActionBase0x34::PeridotTraceActionBase0x34()
{
	// TODO
	STUB(0x450e30);
}
