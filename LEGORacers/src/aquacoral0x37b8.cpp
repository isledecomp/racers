#include "aquacoral0x37b8.h"

#include <golerror.h>
#include <stddef.h>

DECOMP_SIZE_ASSERT(AquaCoral0x37b8, 0x37b8)

// GLOBAL: LEGORACERS 0x004c4914
AquaCoral0x37b8* g_unk0x4c4914 = NULL;

// FUNCTION: LEGORACERS 0x0042b130
void AquaCoral0x37b8::FUN_0042b130(LegoBool32* p_unk0x00)
{
	g_unk0x4c4914 = new AquaCoral0x37b8();
	if (!g_unk0x4c4914) {
		GolFatalError(c_golErrorOutOfMemory, NULL, 0);
	}

	g_unk0x4c4914->FUN_0042c280(p_unk0x00);
	g_unk0x4c4914->FUN_0042c330();
	g_unk0x4c4914->FUN_0042c380();

	if (g_unk0x4c4914) {
		delete g_unk0x4c4914;
	}
}

// FUNCTION: LEGORACERS 0x0042c1b0
AquaCoral0x37b8::AquaCoral0x37b8()
{
	m_unk0x00 = 0;
}

// FUNCTION: LEGORACERS 0x0042c210
AquaCoral0x37b8::~AquaCoral0x37b8()
{
	FUN_0042c380();
}

// STUB: LEGORACERS 0x0042c280
void AquaCoral0x37b8::FUN_0042c280(LegoBool32*)
{
	// TODO
	STUB(0x42c280);
}

// STUB: LEGORACERS 0x0042c330
void AquaCoral0x37b8::FUN_0042c330()
{
	// TODO
	STUB(0x42c330);
}

// STUB: LEGORACERS 0x0042c380
void AquaCoral0x37b8::FUN_0042c380()
{
	// TODO
	STUB(0x42c380);
}
