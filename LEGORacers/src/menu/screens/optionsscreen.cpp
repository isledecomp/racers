#include "menu/screens/optionsscreen.h"

#include "menu/menutoolcontext0x4bc8.h"
#include "menu/menutoolcreateparams0x30.h"

#include <string.h>

DECOMP_SIZE_ASSERT(OptionsScreen, 0x6750)

// STUB: LEGORACERS 0x00475510
OptionsScreen::OptionsScreen()
{
	STUB(0x00475510);
}

// STUB: LEGORACERS 0x00475630
OptionsScreen::~OptionsScreen()
{
	STUB(0x00475630);
}

// FUNCTION: LEGORACERS 0x00475700
void OptionsScreen::Reset()
{
	m_unk0x51a8 = 0;
	::memset(m_unk0x646c, 0, sizeof(m_unk0x646c));
	FUN_00482de0();
}

// FUNCTION: LEGORACERS 0x00475970
LegoBool32 OptionsScreen::VTable0x8c(MenuToolContext0x4bc8* p_context, MenuToolCreateParams0x30* p_createParams)
{
	return FUN_004831d0(p_context, p_createParams) != FALSE;
}

// STUB: LEGORACERS 0x00475990
void OptionsScreen::VTable0x38(ObscureVantage0x58*)
{
	STUB(0x00475990);
}

// FUNCTION: LEGORACERS 0x00482de0
void OptionsScreen::FUN_00482de0()
{
	m_unk0x368 = FALSE;
	m_unk0x369 = FALSE;
	m_unk0x36c = 0;
	m_unk0x370 = NULL;
	ImaginaryTool0x368::Reset();
}

// STUB: LEGORACERS 0x004831a0
void OptionsScreen::VTable0x4c()
{
	STUB(0x004831a0);
}

// FUNCTION: LEGORACERS 0x004831d0
LegoBool32 OptionsScreen::FUN_004831d0(MenuToolContext0x4bc8* p_context, MenuToolCreateParams0x30* p_createParams)
{
	m_unk0x370 = &p_context->m_unk0x258.GetUnk0x18c4();

	if (!ImaginaryTool0x368::VTable0x8c(p_context, p_createParams)) {
		return FALSE;
	}

	if (!FUN_00480440(p_context)) {
		FUN_00480470(p_context, 0, TRUE);
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00483220
void OptionsScreen::VTable0x84()
{
	switch (m_unk0x360) {
	case 2:
		m_context->m_menuStack.Pop();
		m_context->m_menuStack.Push(0x30);
		break;
	case 0x0a:
	case 0x0b:
	case 0x27:
	case 0x2c:
		m_context->m_menuStack.Push(m_unk0x360);
		// intentional fallthrough
	default:
		m_context->m_menuStack.Push(0x30);
		break;
	}
}

// STUB: LEGORACERS 0x004833e0
void OptionsScreen::VTable0x44(ObscureVantage0x58*)
{
	STUB(0x004833e0);
}

// STUB: LEGORACERS 0x004838e0
LegoBool32 OptionsScreen::VTable0x78(undefined4)
{
	STUB(0x004838e0);
	return FALSE;
}
