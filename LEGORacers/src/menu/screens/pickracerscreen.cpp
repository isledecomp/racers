#include "menu/screens/pickracerscreen.h"

DECOMP_SIZE_ASSERT(PickRacerScreen, 0x4c8c)

// STUB: LEGORACERS 0x00484c10
PickRacerScreen::PickRacerScreen()
{
	STUB(0x00484c10);
}

// STUB: LEGORACERS 0x00484ce0
PickRacerScreen::~PickRacerScreen()
{
	STUB(0x00484ce0);
}

// STUB: LEGORACERS 0x004891a0 FOLDED
void PickRacerScreen::VTable0x10(ObscureVantage0x58*)
{
	STUB(0x004891a0);
}

// STUB: LEGORACERS 0x00484d90
void PickRacerScreen::VTable0x4c()
{
	STUB(0x00484d90);
}

// STUB: LEGORACERS 0x00484e40
LegoBool32 PickRacerScreen::VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*)
{
	STUB(0x00484e40);
	return FALSE;
}

// STUB: LEGORACERS 0x00484f40
void PickRacerScreen::VTable0x38(ObscureVantage0x58*)
{
	STUB(0x00484f40);
}

// STUB: LEGORACERS 0x00485090
void PickRacerScreen::VTable0x44(ObscureVantage0x58*)
{
	STUB(0x00485090);
}

// STUB: LEGORACERS 0x004850a0
void PickRacerScreen::VTable0x84()
{
	STUB(0x004850a0);
}

// STUB: LEGORACERS 0x00486a00
LegoBool32 PickRacerScreen::VTable0x78(undefined4)
{
	STUB(0x00486a00);
	return FALSE;
}

// STUB: LEGORACERS 0x00488eb0
void PickRacerScreen::Reset()
{
	STUB(0x00488eb0);
}

// FUNCTION: LEGORACERS 0x00486020 FOLDED
void PickRacerScreen::VTable0x80()
{
	ColorRGBA materialColor;
	ColorRGBA lightColor;

	materialColor.m_red = 0x78;
	materialColor.m_grn = 0x78;
	materialColor.m_blu = 0x78;
	lightColor.m_red = 0xff;
	lightColor.m_grn = 0xff;
	lightColor.m_blu = 0xff;

	FUN_0047fec0(&materialColor, &lightColor);
}

// STUB: LEGORACERS 0x004860f0 FOLDED
LegoBool32 PickRacerScreen::Destroy()
{
	STUB(0x004860f0);
	return FALSE;
}

// STUB: LEGORACERS 0x004869b0 FOLDED
LegoBool32 PickRacerScreen::VTable0x88()
{
	STUB(0x004869b0);
	return FALSE;
}
