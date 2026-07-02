#include "menu/screens/picklanguagescreen.h"

#include "menu/menugamecontext.h"
#include "menu/menuscreencreateparams.h"
#include "menu/menuscreenid.h"

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
void PickLanguageScreen::CreateWidgets()
{
	CreateImage(&m_photoImage, 0x49, 0x49);
	CreateTextLabel(&m_infoLabel, 0x3a, 0x3a, 0x9c);
	m_infoLabel.WrapText(0x14);
	CreateCarousel(&m_languageCarousel, 0x3d, 0x3b);
	CreateSelector(&m_languageSelector, &m_languageCarousel, 0x137, 0x4c);

	for (LegoS32 i = 0; i < 9; i++) {
		CreateTextLabel(&m_languageLabels[i], 0x96, 0x37, i + 0x9d);
		m_languageCarousel.AddItem(&m_languageLabels[i]);
	}

	CreateTextButton(&m_backButton, 0x3f, 0x43, 0x10);
}

// FUNCTION: LEGORACERS 0x004845c0
LegoBool32 PickLanguageScreen::Initialize(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	LegoU32 languageIndex = p_context->m_saveSystem.GetLanguageIndex();
	if (!MenuGameScreen::Initialize(p_context, p_createParams)) {
		return FALSE;
	}

	m_languageCarousel.SetSelection(languageIndex);
	m_languageSelector.Select(5);

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00484620
void PickLanguageScreen::OnWidgetValueChanged(MenuWidget* p_source)
{
	if (p_source == &m_languageSelector) {
		GameState& state = m_context->m_saveSystem.GetGameState();
		state.SetLanguageIndex((LegoU8) m_languageCarousel.GetSelectedIndex());
		state.SetDirty(TRUE);
	}
}

// FUNCTION: LEGORACERS 0x00484650
void PickLanguageScreen::OnIconUnfocused(MenuWidget* p_source)
{
	if (p_source == &m_backButton) {
		m_navPending = TRUE;
	}

	m_clickedWidget = p_source;
}

// FUNCTION: LEGORACERS 0x00484680
void PickLanguageScreen::Navigate()
{
	m_context->m_menuStack.Pop();
	m_context->m_menuStack.Push(c_menuSaveAll);
}
