#include "menu/screens/garagescreen.h"

DECOMP_SIZE_ASSERT(GarageScreen, 0x6410)

// FUNCTION: LEGORACERS 0x0047e2b0
GarageScreen::GarageScreen()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0047e400
GarageScreen::~GarageScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0047e530
void GarageScreen::Reset()
{
	m_unk0x640c = 0;
	m_unk0x6408 = 0;
	RacerPickScreenBase0x3ff4::Reset();
}

// FUNCTION: LEGORACERS 0x0047e550
void GarageScreen::FUN_0047e550()
{
	FUN_0047fdc0(&m_unk0x40c8, 0x90, 0x42, 0x28);
	FUN_0047fdc0(&m_unk0x43b8, 0x91, 0x42, 0x29);
	FUN_0047fdc0(&m_unk0x46a8, 0x92, 0x42, 0x2a);
	FUN_0047fdc0(&m_unk0x4998, 0x93, 0x42, 0x2c);
	FUN_0047fdc0(&m_unk0x4c88, 0x94, 0x42, 0x2d);
	FUN_0047fdc0(&m_unk0x5848, 0x3f, 0x43, 3);
	FUN_0046bf80(&m_unk0x4050, 0x3a, 0x3a, 3);
	m_unk0x4050.FUN_0046f6b0(0x14);
}

// FUNCTION: LEGORACERS 0x0047e600
void GarageScreen::FUN_0047e600()
{
	FUN_0047fdc0(&m_unk0x5268, 0x0f, 0x42, 9);
	FUN_0047fdc0(&m_unk0x5558, 0x98, 0x42, 0x0a);
	FUN_0047fdc0(&m_unk0x4f78, 0x11, 0x42, 0x0b);
	FUN_0047e9c0();
}

// FUNCTION: LEGORACERS 0x0047e650
void GarageScreen::VTable0x4c()
{
	FUN_0046bef0(&m_unk0x3ff4, 0x49, 0x49);
	RacerPickScreenBase0x3ff4::VTable0x4c();
	FUN_0047e550();
	FUN_0047e600();
}

// STUB: LEGORACERS 0x0047e680
LegoBool32 GarageScreen::VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*)
{
	STUB(0x0047e680);
	return FALSE;
}

// FUNCTION: LEGORACERS 0x0047e9c0
void GarageScreen::FUN_0047e9c0()
{
	m_unk0x4f78.ClearFlags(2);
	m_unk0x5268.ClearFlags(2);
	m_unk0x5558.ClearFlags(2);
}

// STUB: LEGORACERS 0x0047ec00
void GarageScreen::VTable0x84()
{
	STUB(0x0047ec00);
}

// STUB: LEGORACERS 0x0047ee50
void GarageScreen::VTable0x38(ObscureVantage0x58*)
{
	STUB(0x0047ee50);
}

// STUB: LEGORACERS 0x0047f030
LegoBool32 GarageScreen::VTable0x78(undefined4)
{
	STUB(0x0047f030);
	return FALSE;
}
