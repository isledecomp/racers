#include "unk0x10056440.h"

#include "types.h"

DECOMP_SIZE_ASSERT(Unk0x10056440, 0xc8ac8)

// Destructor of sub-object at m_unk0x04 (called as __thiscall in original).
// STUB: GOLDP 0x10001110
void FUN_10001110(LegoS32 p_a1)
{
	// TODO
}

// STUB: GOLDP 0x10007060
Unk0x10056440::~Unk0x10056440()
{
	FUN_10001110((LegoS32) &m_unk0x04);
}
