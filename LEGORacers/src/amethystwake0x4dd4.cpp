#include "amethystwake0x4dd4.h"

#include "golhashtable.h"
#include "golstream.h"

#include <golerror.h>
#include <stddef.h>

DECOMP_SIZE_ASSERT(AmethystWake0x4dd4, 0x4dd4)

// GLOBAL: LEGORACERS 0x004c4918
AmethystWake0x4dd4* g_unk0x4c4918 = NULL;

// GLOBAL: LEGORACERS 0x004beb78
LegoFloat g_unk0x4beb78[7] = {0.04f, 0.04f, 0.04f, 0.04f, 0.39f, 0.4f, 0.04f};

// FUNCTION: LEGORACERS 0x0042b1e0
void AmethystWake0x4dd4::FUN_0042b1e0(LegoRacers::Context* p_context)
{
	g_unk0x4c4918 = new AmethystWake0x4dd4();
	if (!g_unk0x4c4918) {
		GolFatalError(c_golErrorOutOfMemory, NULL, 0);
	}

	g_unk0x4c4918->FUN_0042cb90(p_context);
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

// FUNCTION: LEGORACERS 0x0042cb90
LegoS32 AmethystWake0x4dd4::FUN_0042cb90(LegoRacers::Context* p_context)
{
	LegoBool32 flag = FALSE;
	m_context = p_context;
	m_unk0x4cd4 = p_context->m_unk0x04->GetGolExport();
	m_unk0x4cd8 = p_context->m_unk0x04->GetUnk0x80c();

	if (g_hashTable) {
		GolHashTable* hashTable = g_hashTable;
		hashTable->SetUnk0x1c(hashTable->FUN_0044c810("MENUDATA"));
	}

	FUN_0042d020();
	FUN_0042d0e0();
	FUN_0042d300(m_unk0x1b42, TRUE);
	FUN_0042d1e0();
	FUN_0042e1f0();
	FUN_0042cde0();
	FUN_0042ced0();
	FUN_0042cf00();
	FUN_0042cd60();

	if (FUN_0042e490()) {
		flag = TRUE;
	}
	if (FUN_0042e680()) {
		flag = TRUE;
	}

	m_unk0x4cd8->VTable0x34(7, g_unk0x4beb78);

	m_unk0x08.FUN_0047fa00(10);
	m_unk0x08.FUN_0047fa70(m_context->m_unk0x1c);

	if (flag && FUN_0042e450()) {
		m_unk0x08.FUN_0047fa70(48);
	}

	LegoU16 top = m_unk0x08.FUN_0047fac0();
	FUN_0042d3e0(top);

	m_unk0x4bd0.FUN_00468af0(m_unk0x4d98, 2, m_unk0x4c74);
	return 1;
}

// STUB: LEGORACERS 0x0042ccc0
LegoS32 AmethystWake0x4dd4::FUN_0042ccc0()
{
	// TODO
	STUB(0x42ccc0);
	return 0;
}

// STUB: LEGORACERS 0x0042cd60
void AmethystWake0x4dd4::FUN_0042cd60()
{
	// TODO
	STUB(0x42cd60);
}

// STUB: LEGORACERS 0x0042cde0
void AmethystWake0x4dd4::FUN_0042cde0()
{
	// TODO
	STUB(0x42cde0);
}

// STUB: LEGORACERS 0x0042ced0
void AmethystWake0x4dd4::FUN_0042ced0()
{
	// TODO
	STUB(0x42ced0);
}

// STUB: LEGORACERS 0x0042cf00
void AmethystWake0x4dd4::FUN_0042cf00()
{
	// TODO
	STUB(0x42cf00);
}

// STUB: LEGORACERS 0x0042d020
void AmethystWake0x4dd4::FUN_0042d020()
{
	// TODO
	STUB(0x42d020);
}

// STUB: LEGORACERS 0x0042d0e0
void AmethystWake0x4dd4::FUN_0042d0e0()
{
	// TODO
	STUB(0x42d0e0);
}

// STUB: LEGORACERS 0x0042d1e0
void AmethystWake0x4dd4::FUN_0042d1e0()
{
	// TODO
	STUB(0x42d1e0);
}

// STUB: LEGORACERS 0x0042d300
LegoBool AmethystWake0x4dd4::FUN_0042d300(LegoU32, LegoBool)
{
	// TODO
	STUB(0x42d300);
	return FALSE;
}

// STUB: LEGORACERS 0x0042d3e0
void AmethystWake0x4dd4::FUN_0042d3e0(LegoU16)
{
	// TODO
	STUB(0x42d3e0);
}

// STUB: LEGORACERS 0x0042d510
void AmethystWake0x4dd4::FUN_0042d510()
{
	// TODO
	STUB(0x42d510);
}

// STUB: LEGORACERS 0x0042e1f0
void AmethystWake0x4dd4::FUN_0042e1f0()
{
	// TODO
	STUB(0x42e1f0);
}

// STUB: LEGORACERS 0x0042e450
LegoS32 AmethystWake0x4dd4::FUN_0042e450()
{
	// TODO
	STUB(0x42e450);
	return FALSE;
}

// STUB: LEGORACERS 0x0042e490
LegoS32 AmethystWake0x4dd4::FUN_0042e490()
{
	// TODO
	STUB(0x42e490);
	return FALSE;
}

// STUB: LEGORACERS 0x0042e680
LegoS32 AmethystWake0x4dd4::FUN_0042e680()
{
	// TODO
	STUB(0x42e680);
	return FALSE;
}

// FUNCTION: LEGORACERS 0x0042e700
void AmethystWake0x4dd4::VTable0x00()
{
	m_unk0x4dd0 = 0;
	m_context->m_unk0x00 = FALSE;
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
