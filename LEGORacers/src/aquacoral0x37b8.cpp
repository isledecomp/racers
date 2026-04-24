#include "aquacoral0x37b8.h"

#include "golhashtable.h"
#include "ironflame0x944.h"

#include <golerror.h>
#include <golstream.h>

DECOMP_SIZE_ASSERT(AquaCoral0x37b8, 0x37b8)

// GLOBAL: LEGORACERS 0x004c4914
AquaCoral0x37b8* g_unk0x4c4914 = NULL;

// FUNCTION: LEGORACERS 0x0042b130
void AquaCoral0x37b8::FUN_0042b130(LegoRacers::Context* p_context)
{
	g_unk0x4c4914 = new AquaCoral0x37b8();
	if (!g_unk0x4c4914) {
		GolFatalError(c_golErrorOutOfMemory, NULL, 0);
	}

	g_unk0x4c4914->FUN_0042c280(p_context);
	g_unk0x4c4914->FUN_0042c330();
	g_unk0x4c4914->FUN_0042c380();

	if (g_unk0x4c4914) {
		delete g_unk0x4c4914;
	}
}

// FUNCTION: LEGORACERS 0x0042c1b0
AquaCoral0x37b8::AquaCoral0x37b8()
{
	m_context = NULL;
}

// FUNCTION: LEGORACERS 0x0042c210
AquaCoral0x37b8::~AquaCoral0x37b8()
{
	FUN_0042c380();
}

// FUNCTION: LEGORACERS 0x0042c280
LegoS32 AquaCoral0x37b8::FUN_0042c280(LegoRacers::Context* p_context)
{
	m_context = p_context;
	m_context->m_unk0x1e &= ~8;

	if (p_context->m_unk0x24 == 2) {
		GolHashTable* hashTable = g_hashTable;
		if (hashTable) {
			hashTable->SetUnk0x1c(hashTable->FUN_0044c810("GAMEDATA\\COMMON"));
		}
		m_unk0x3400.FUN_00422420(
			p_context->m_unk0x04->GetUnk0x80c(),
			p_context->m_unk0x04->GetGolExport(),
			p_context->m_unk0x18,
			p_context->m_unk0x3c
		);
	}

	if (p_context->m_unk0x1e & 2) {
		p_context->m_unk0x1c = 3;
	}
	else {
		p_context->m_unk0x1c = 2;
	}

	p_context->m_unk0xd8 = 0;
	p_context->m_unk0x04->FUN_00416490();

	if (!p_context->m_unk0x24) {
		return m_unk0x04.FUN_0041ed10(m_context, &m_unk0x98);
	}

	return FUN_0042c4e0();
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

// STUB: LEGORACERS 0x0042c4e0
LegoS32 AquaCoral0x37b8::FUN_0042c4e0()
{
	// TODO
	STUB(0x42c4e0);
	return 0;
}
