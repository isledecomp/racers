#include "amethystwake0x4dd4.h"

#include <golerror.h>
#include <stddef.h>

DECOMP_SIZE_ASSERT(AmethystWake0x4dd4, 0x4dd4)

// GLOBAL: LEGORACERS 0x004c4918
AmethystWake0x4dd4* g_unk0x4c4918 = NULL;

// FUNCTION: LEGORACERS 0x0042b1e0
void AmethystWake0x4dd4::FUN_0042b1e0(LegoBool32* p_unk0x00)
{
	g_unk0x4c4918 = new AmethystWake0x4dd4();
	if (!g_unk0x4c4918) {
		GolFatalError(c_golErrorOutOfMemory, NULL, 0);
	}

	g_unk0x4c4918->FUN_0042cb90(p_unk0x00);
	g_unk0x4c4918->FUN_0042d510();
	g_unk0x4c4918->FUN_0042ccc0();

	if (g_unk0x4c4918) {
		delete g_unk0x4c4918;
	}
}

// STUB: LEGORACERS 0x0042c5d0
AmethystWake0x4dd4::AmethystWake0x4dd4()
{
	// TODO
	STUB(0x42c5d0);
}

// STUB: LEGORACERS 0x0042c910
AmethystWake0x4dd4::~AmethystWake0x4dd4()
{
	// TODO
	STUB(0x42c910);
}

// STUB: LEGORACERS 0x0042cb90
void AmethystWake0x4dd4::FUN_0042cb90(LegoBool32*)
{
	// TODO
	STUB(0x42cb90);
}

// STUB: LEGORACERS 0x0042ccc0
LegoS32 AmethystWake0x4dd4::FUN_0042ccc0()
{
	// TODO
	STUB(0x42ccc0);
	return 0;
}

// STUB: LEGORACERS 0x0042d510
void AmethystWake0x4dd4::FUN_0042d510()
{
	// TODO
	STUB(0x42d510);
}

// FUNCTION: LEGORACERS 0x0042e700
void AmethystWake0x4dd4::VTable0x00()
{
	m_unk0x4dd0 = 0;
	*m_unk0x04 = 0;
}

// STUB: LEGORACERS 0x0042e810
void AmethystWake0x4dd4::VTable0x1c(undefined4)
{
	// TODO
	STUB(0x42e810);
}

// FUNCTION: LEGORACERS 0x0042e830
void AmethystWake0x4dd4::VTable0x28()
{
	m_unk0x4cc4 = 1;
}

// FUNCTION: LEGORACERS 0x0042e840
void AmethystWake0x4dd4::VTable0x2c()
{
	m_unk0x4cc4 = 0;
}

// FUNCTION: LEGORACERS 0x0042e850
void AmethystWake0x4dd4::VTable0x24(undefined4 p_arg1, undefined4 p_arg2)
{
	m_unk0x4cb4 = p_arg1 - m_unk0x4cbc;
	m_unk0x4cb8 = p_arg2 - m_unk0x4cc0;
}
