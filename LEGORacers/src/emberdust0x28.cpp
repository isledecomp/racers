#include "emberdust0x28.h"

#include "types.h"

DECOMP_SIZE_ASSERT(CoralBreeze0x28, 0x28)
DECOMP_SIZE_ASSERT(EmberDust0x28, 0x28)

// FUNCTION: LEGORACERS 0x41c200
EmberDust0x28::EmberDust0x28()
{
	m_unk0x0c = 0;
}

// FUNCTION: LEGORACERS 0x41c240
EmberDust0x28::~EmberDust0x28()
{
	VTable0x04();
}

// FUNCTION: LEGORACERS 0x41c250
undefined4 EmberDust0x28::VTable0x00(undefined4)
{
	return VTable0x04();
}

// STUB: LEGORACERS 0x41c260
undefined4 EmberDust0x28::VTable0x04()
{
	// TODO
	STUB(0x41c260);
	return 0;
}
