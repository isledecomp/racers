#include "menu/screens/racemodesetupscreen.h"

#include "menu/menutoolcreateparams0x30.h"

DECOMP_SIZE_ASSERT(RaceModeSetupScreen, 0x2e60)

// STUB: LEGORACERS 0x00487850
RaceModeSetupScreen::RaceModeSetupScreen()
{
	STUB(0x00487850);
}

// STUB: LEGORACERS 0x004879b0
RaceModeSetupScreen::~RaceModeSetupScreen()
{
	STUB(0x004879b0);
}

// STUB: LEGORACERS 0x00487ae0
void RaceModeSetupScreen::Reset()
{
	STUB(0x00487ae0);
}

// STUB: LEGORACERS 0x00487b50
void RaceModeSetupScreen::VTable0x4c()
{
	FUN_0046bef0(&m_unk0x1908, 0x49, 0x49);
	SingleRaceSelectBase::VTable0x4c();

	STUB(0x00487b50);
}

// STUB: LEGORACERS 0x00487ca0
LegoBool32 RaceModeSetupScreen::VTable0x8c(MenuToolContext0x4bc8* p_context, MenuToolCreateParams0x30* p_createParams)
{
	m_menuId = p_createParams->m_menuId;
	p_createParams->m_menuId = 6;

	LegoBool32 result = SingleRaceSelectBase::VTable0x8c(p_context, p_createParams);

	STUB(0x00487ca0);
	return result;
}

// STUB: LEGORACERS 0x00487d10
void RaceModeSetupScreen::VTable0x3c(ObscureIcon0x1a8*)
{
	STUB(0x00487d10);
}

// STUB: LEGORACERS 0x00487d40
void RaceModeSetupScreen::VTable0x38(ObscureVantage0x58*)
{
	STUB(0x00487d40);
}

// STUB: LEGORACERS 0x00487e10
void RaceModeSetupScreen::VTable0x44(ObscureVantage0x58*)
{
	STUB(0x00487e10);
}

// STUB: LEGORACERS 0x00487f90
void RaceModeSetupScreen::VTable0x84()
{
	STUB(0x00487f90);
}

// STUB: LEGORACERS 0x00488150
LegoBool32 RaceModeSetupScreen::VTable0x78(undefined4)
{
	STUB(0x00488150);
	return FALSE;
}
