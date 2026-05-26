#include "menu/screens/circuitselectscreen.h"

DECOMP_SIZE_ASSERT(CircuitSelectScreen, 0x658)

// STUB: LEGORACERS 0x00479a80
CircuitSelectScreen::CircuitSelectScreen()
{
	STUB(0x00479a80);
}

// STUB: LEGORACERS 0x00479ac0
CircuitSelectScreen::~CircuitSelectScreen()
{
	STUB(0x00479ac0);
}

// STUB: LEGORACERS 0x00479b10
LegoBool32 CircuitSelectScreen::VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*)
{
	STUB(0x00479b10);
	return FALSE;
}

// STUB: LEGORACERS 0x00479bd0
LegoBool32 CircuitSelectScreen::Destroy()
{
	STUB(0x00479bd0);
	return FALSE;
}

// STUB: LEGORACERS 0x00479c40
void CircuitSelectScreen::VTable0x4c()
{
	STUB(0x00479c40);
}

// STUB: LEGORACERS 0x00479d10
void CircuitSelectScreen::VTable0x84()
{
	STUB(0x00479d10);
}

// FUNCTION: LEGORACERS 0x00480b50 FOLDED
LegoBool32 CircuitSelectScreen::VTable0x78(undefined4 p_unk0x04)
{
	m_unk0x368.m_unk0x2cc = TRUE;
	return ImaginaryChisel0x658::VTable0x78(p_unk0x04);
}
