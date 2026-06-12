#include "menu/screens/picklanguagescreen.h"

#include "menu/menugamecontext.h"
#include "menu/menuscreencreateparams.h"
#include "menu/menuscreenid.h"
#include "save/savegame.h"

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
	CreateImage(&m_unk0x368, 0x49, 0x49);
	CreateTextLabel(&m_unk0x3c4, 0x3a, 0x3a, 0x9c);
	m_unk0x3c4.FUN_0046f6b0(0x14);
	CreateCarousel(&m_unk0xe30, 0x3d, 0x3b);
	CreateSelector(&m_unk0x43c, &m_unk0xe30, 0x137, 0x4c);

	for (LegoS32 i = 0; i < 9; i++) {
		CreateTextLabel(&m_unk0xec4[i], 0x96, 0x37, i + 0x9d);
		m_unk0xe30.FUN_0046d9c0(&m_unk0xec4[i]);
	}

	FUN_0047fdc0(&m_unk0x12fc, 0x3f, 0x43, 0x10);
}

// FUNCTION: LEGORACERS 0x004845c0
LegoBool32 PickLanguageScreen::VTable0x8c(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	LegoU32 languageIndex = p_context->m_saveSystem.GetLanguageIndex();
	if (!MenuGameScreen::VTable0x8c(p_context, p_createParams)) {
		return FALSE;
	}

	m_unk0xe30.VTable0x50(languageIndex);
	m_unk0x43c.VTable0x4c(5);

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00484620
void PickLanguageScreen::VTable0x44(MenuWidget* p_unk0x04)
{
	if (p_unk0x04 == &m_unk0x43c) {
		GameState& state = m_context->m_saveSystem.GetGameState();
		state.SetLanguageIndex((LegoU8) m_unk0xe30.GetUnk0x6c());
		state.SetDirty(TRUE);
	}
}

// FUNCTION: LEGORACERS 0x00484650
void PickLanguageScreen::VTable0x38(MenuWidget* p_unk0x04)
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
