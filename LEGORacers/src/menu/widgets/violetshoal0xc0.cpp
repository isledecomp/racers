#include "menu/widgets/violetshoal0xc0.h"

DECOMP_SIZE_ASSERT(VioletShoal0xc0, 0xc0)

// FUNCTION: LEGORACERS 0x0046c9f0 FOLDED
void VioletShoal0xc0::VTable0x5c(undefined4*, undefined4*)
{
}

// FUNCTION: LEGORACERS 0x0046ca00
VioletShoal0xc0::VioletShoal0xc0()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046ca80
VioletShoal0xc0::~VioletShoal0xc0()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x0046cad0
void VioletShoal0xc0::Reset()
{
	m_unk0xa4 = 1.0f;
	m_unk0x80 = 0;
	m_unk0x84 = 0;
	m_unk0x7c = 0;
	m_unk0xa0 = 0;
	m_unk0x9c = 0;
	m_unk0xbc = 0;
	ObscureCarousel0x78::Reset();
}

// STUB: LEGORACERS 0x0046cba0
LegoBool32 VioletShoal0xc0::VTable0x08()
{
	STUB(0x0046cba0);
	return FALSE;
}

// STUB: LEGORACERS 0x0046d1d0
void VioletShoal0xc0::VTable0x48(VisualState0x4*, VisualState0x4*)
{
	STUB(0x0046d1d0);
}

// STUB: LEGORACERS 0x0046d210
void VioletShoal0xc0::VTable0x4c(VisualState0x4*, VisualState0x4*)
{
	STUB(0x0046d210);
}

// STUB: LEGORACERS 0x0046d240
void VioletShoal0xc0::VTable0x40()
{
	STUB(0x0046d240);
}

// STUB: LEGORACERS 0x0046d2a0
void VioletShoal0xc0::VTable0x44(undefined4)
{
	STUB(0x0046d2a0);
}

// STUB: LEGORACERS 0x0046d350
LegoS32 VioletShoal0xc0::VTable0x54()
{
	STUB(0x0046d350);
	return 0;
}

// STUB: LEGORACERS 0x0046d470
LegoS32 VioletShoal0xc0::VTable0x58()
{
	STUB(0x0046d470);
	return 0;
}

// STUB: LEGORACERS 0x0046d5a0
void VioletShoal0xc0::SetParent(ObscureVantage0x58*)
{
	STUB(0x0046d5a0);
}

// STUB: LEGORACERS 0x0046d5c0
ObscureVantage0x58* VioletShoal0xc0::VTable0x30(InputEventQueue::Event*, undefined4, undefined4)
{
	STUB(0x0046d5c0);
	return NULL;
}

// STUB: LEGORACERS 0x0046d670
ObscureVantage0x58* VioletShoal0xc0::VTable0x38(Rect*, Rect*)
{
	STUB(0x0046d670);
	return NULL;
}

// STUB: LEGORACERS 0x0046d780
undefined4 VioletShoal0xc0::VTable0x3c(undefined4)
{
	STUB(0x0046d780);
	return 0;
}
