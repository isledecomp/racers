#include "menu/screens/pickmemorycardscreen.h"

DECOMP_SIZE_ASSERT(PickMemoryCardScreen, 0x2548)

// STUB: LEGORACERS 0x004846b0
PickMemoryCardScreen::PickMemoryCardScreen()
{
	STUB(0x004846b0);
}

// STUB: LEGORACERS 0x00484820
PickMemoryCardScreen::~PickMemoryCardScreen()
{
	STUB(0x00484820);
}

// STUB: LEGORACERS 0x00484960
void PickMemoryCardScreen::VTable0x4c()
{
	STUB(0x00484960);
}

// STUB: LEGORACERS 0x00484980
LegoBool32 PickMemoryCardScreen::VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*)
{
	STUB(0x00484980);
	return FALSE;
}

// FUNCTION: LEGORACERS 0x004849c0 FOLDED
LegoBool32 PickMemoryCardScreen::Destroy()
{
	if (!m_initialized) {
		return TRUE;
	}

	m_cursorHelper->SetCursorEnabled(TRUE);
	return ImaginaryTool0x368::Destroy();
}

// STUB: LEGORACERS 0x004849e0
void PickMemoryCardScreen::VTable0x38(ObscureVantage0x58*)
{
	STUB(0x004849e0);
}

// STUB: LEGORACERS 0x00484b50
void PickMemoryCardScreen::VTable0x84()
{
	STUB(0x00484b50);
}

// STUB: LEGORACERS 0x00484be0
LegoBool32 PickMemoryCardScreen::VTable0x78(undefined4)
{
	STUB(0x00484be0);
	return FALSE;
}
