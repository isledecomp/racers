#include "menu/screens/picklanguagescreen.h"

#include "menu/menuscreenid.h"
#include "menu/menutoolcontext0x4bc8.h"
#include "menu/menutoolcreateparams0x30.h"
#include "save/peridottrace0x4e0.h"

DECOMP_SIZE_ASSERT(PickLanguageScreen, 0x15ec)

// FUNCTION: LEGORACERS 0x00484360
PickLanguageScreen::PickLanguageScreen()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00484450
PickLanguageScreen::~PickLanguageScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00484510
void PickLanguageScreen::VTable0x4c()
{
	FUN_0046bef0(&m_unk0x368, 0x49, 0x49);
	FUN_0046bf80(&m_unk0x3c4, 0x3a, 0x3a, 0x9c);
	m_unk0x3c4.FUN_0046f6b0(0x14);
	FUN_0046c240(&m_unk0xe30, 0x3d, 0x3b);
	FUN_0046c2b0(&m_unk0x43c, &m_unk0xe30, 0x137, 0x4c);

	for (LegoS32 i = 0; i < 9; i++) {
		FUN_0046bf80(&m_unk0xec4[i], 0x96, 0x37, i + 0x9d);
		m_unk0xe30.FUN_0046d9c0(&m_unk0xec4[i]);
	}

	FUN_0047fdc0(&m_unk0x12fc, 0x3f, 0x43, 0x10);
}

// FUNCTION: LEGORACERS 0x004845c0
LegoBool32 PickLanguageScreen::VTable0x8c(MenuToolContext0x4bc8* p_context, MenuToolCreateParams0x30* p_createParams)
{
	LegoU32 languageIndex = p_context->m_unk0x258.GetLanguageIndex();
	if (!ImaginaryTool0x368::VTable0x8c(p_context, p_createParams)) {
		return FALSE;
	}

	m_unk0xe30.VTable0x50(languageIndex);
	m_unk0x43c.VTable0x4c(5);

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00484620
void PickLanguageScreen::VTable0x44(ObscureVantage0x58* p_unk0x04)
{
	if (p_unk0x04 == &m_unk0x43c) {
		GameState& state = m_context->m_unk0x258.GetUnk0x18c4();
		state.SetLanguageIndex((LegoU8) m_unk0xe30.GetUnk0x6c());
		state.SetUnk0x00(TRUE);
	}
}

// FUNCTION: LEGORACERS 0x00484650
void PickLanguageScreen::VTable0x38(ObscureVantage0x58* p_unk0x04)
{
	if (p_unk0x04 == &m_unk0x12fc) {
		m_unk0x364 = TRUE;
	}

	m_unk0x35c = p_unk0x04;
}

// FUNCTION: LEGORACERS 0x00484680
void PickLanguageScreen::VTable0x84()
{
	m_context->m_menuStack.Pop();
	m_context->m_menuStack.Push(c_menuSaveAll);
}
