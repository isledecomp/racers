#include "menu/screens/optionsscreen.h"

#include "menu/menutoolcontext0x4bc8.h"
#include "menu/menutoolcreateparams0x30.h"

#include <string.h>

DECOMP_SIZE_ASSERT(OptionsScreen, 0x6750)

// FUNCTION: LEGORACERS 0x00475510
OptionsScreen::OptionsScreen()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00475630
OptionsScreen::~OptionsScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00475700
void OptionsScreen::Reset()
{
	m_unk0x51a8 = 0;
	::memset(m_unk0x646c, 0, sizeof(m_unk0x646c));
	OptionsScreenBase0x51ac::Reset();
}

// STUB: LEGORACERS 0x00475730
void OptionsScreen::VTable0x98()
{
	STUB(0x00475730);
}

// FUNCTION: LEGORACERS 0x00475970
LegoBool32 OptionsScreen::VTable0x8c(MenuToolContext0x4bc8* p_context, MenuToolCreateParams0x30* p_createParams)
{
	return OptionsScreenBase0x51ac::VTable0x8c(p_context, p_createParams) != FALSE;
}

// FUNCTION: LEGORACERS 0x00475990
void OptionsScreen::VTable0x38(ObscureVantage0x58* p_widget)
{
	if (p_widget == &m_unk0x51ac) {
		FUN_0047fdc0(&m_unk0x549c, 0x99, 0x46, 0x72);
		FUN_0046c730(&m_unk0x549c, 0xbd);
	}
	else if (p_widget == &m_unk0x549c) {
		m_unk0x369 = 3;
		m_unk0x284->FUN_00468cf0();
	}

	OptionsScreenBase0x51ac::VTable0x38(p_widget);
	if (m_unk0x360 != 0xffff) {
		m_unk0x364 = TRUE;
	}

	m_unk0x35c = p_widget;
}

// STUB: LEGORACERS 0x00475a10
void OptionsScreen::VTable0x9c()
{
	STUB(0x00475a10);
}

// STUB: LEGORACERS 0x00475a20
void OptionsScreen::VTable0xa0()
{
	STUB(0x00475a20);
}

// STUB: LEGORACERS 0x00475ad0
void OptionsScreen::VTable0xa4()
{
	STUB(0x00475ad0);
}
