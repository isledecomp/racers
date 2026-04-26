#include "awakekite0x20.h"

#include "bronzefalcon0xc8770.h"

DECOMP_SIZE_ASSERT(AwakeKite0x20, 0x20)

// FUNCTION: GOLDP 0x10005d10
AwakeKite0x20::AwakeKite0x20()
{
	m_unk0x1c = 0;
}

// STUB: GOLDP 0x10005d50
AwakeKite0x20::~AwakeKite0x20()
{
}

// STUB: GOLDP 0x10005dc0
void AwakeKite0x20::VTable0x0c()
{
	STUB(0x10005dc0);
}

// STUB: GOLDP 0x10005ec0
void AwakeKite0x20::VTable0x08()
{
	STUB(0x10005ec0);
}

// FUNCTION: GOLDP 0x10005ef0
UtopianPan0xa4* AwakeKite0x20::VTable0x20(undefined4 p_index)
{
	return &m_unk0x1c[p_index];
}

// STUB: GOLDP 0x10005f10
void AwakeKite0x20::VTable0x10()
{
	STUB(0x10005f10);
}

// STUB: GOLDP 0x10005f50
void AwakeKite0x20::VTable0x14()
{
	STUB(0x10005f50);
}
