#include "mossglow0x30.h"

#include "coralbeam0x30.h"
#include "types.h"

DECOMP_SIZE_ASSERT(MossGlow0x30, 0x30)

// FUNCTION: LEGORACERS 0x44c920
MossGlow0x30::MossGlow0x30()
{
	FUN_0044c990();
}

// FUNCTION: LEGORACERS 0x44c960
MossGlow0x30::~MossGlow0x30()
{
	if (m_unk0x24) {
		operator delete(m_unk0x24);
		m_unk0x24 = NULL;
	}

	FUN_0044c990();
}

// STUB: LEGORACERS 0x44c990
void MossGlow0x30::FUN_0044c990()
{
	// TODO
	STUB(0x44c990);
}

// This function is temporarily defined here (not in coralbeam0x30.cpp) so the
// compiler cannot see its body when compiling ~CoralBeam0x30, which is necessary
// for MSVC 6.0 to generate the correct SEH frame in the destructor.
// STUB: LEGORACERS 0x44cc90
void CoralBeam0x30::FUN_0044cc90()
{
	// TODO
	STUB(0x44cc90);
}

// STUB: LEGORACERS 0x44e7e0
void MossGlow0x30::VTable0x14()
{
	// TODO
	STUB(0x44e7e0);
}

// STUB: LEGORACERS 0x44e7f0
void MossGlow0x30::VTable0x10()
{
	// TODO
	STUB(0x44e7f0);
}
