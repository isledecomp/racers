#include "menu/widgets/embervault0x330.h"

DECOMP_SIZE_ASSERT(EmberVault0x330, 0x330)

// FUNCTION: LEGORACERS 0x00471850
EmberVault0x330::EmberVault0x330()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004718d0
EmberVault0x330::~EmberVault0x330()
{
	VTable0x08();
}

// STUB: LEGORACERS 0x00471b20
void EmberVault0x330::VTable0x70()
{
	STUB(0x00471b20);
}

// STUB: LEGORACERS 0x00471b70
ObscureVantage0x58* EmberVault0x330::VTable0x38(Rect*, Rect*)
{
	STUB(0x00471b70);
	return NULL;
}

// STUB: LEGORACERS 0x00471c00
ObscureVantage0x58* EmberVault0x330::VTable0x30(InputEventQueue::Event*, undefined4, undefined4)
{
	STUB(0x00471c00);
	return NULL;
}
