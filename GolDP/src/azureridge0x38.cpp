#include "azureridge0x38.h"

DECOMP_SIZE_ASSERT(AzureRidge0x38, 0x38)

// FUNCTION: GOLDP 0x1001d730
AzureRidge0x38::AzureRidge0x38()
{
	m_unk0x30 = 0;
	m_unk0x34 = 0;
}

// TODO: The base class destructor is inline but must not be inlined here
// (the original generates a tail call). This pragma is a workaround;
// the original code likely didn't need it because the compiler made
// a different inlining decision for non-trivial destructor bodies.
// FUNCTION: GOLDP 0x1001d770
#pragma inline_depth(0)
AzureRidge0x38::~AzureRidge0x38()
{
	m_unk0x30 = 0;
	m_unk0x34 = 0;
}
#pragma inline_depth()

// STUB: GOLDP 0x1001d790
void AzureRidge0x38::VTable0x30(GolDrawState*, undefined4, undefined4, undefined4)
{
	STUB(0x1001d790);
}

// STUB: GOLDP 0x1001d7c0
void AzureRidge0x38::VTable0x34()
{
	STUB(0x1001d7c0);
}

// STUB: GOLDP 0x1001d7e0
void AzureRidge0x38::VTable0x38(undefined4)
{
	STUB(0x1001d7e0);
}
