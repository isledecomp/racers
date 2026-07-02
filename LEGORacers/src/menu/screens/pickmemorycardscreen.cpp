#include "menu/screens/pickmemorycardscreen.h"

#include "menu/menudialog.h"
#include "menu/menugamecontext.h"
#include "menu/menuscreencreateparams.h"

DECOMP_SIZE_ASSERT(PickMemoryCardScreen, 0x2548)

// FUNCTION: LEGORACERS 0x004846b0
PickMemoryCardScreen::PickMemoryCardScreen()
{
	Reset();
	m_unk0x2544 = 0;
}

// FUNCTION: LEGORACERS 0x00484820
PickMemoryCardScreen::~PickMemoryCardScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00484960
void PickMemoryCardScreen::CreateWidgets()
{
	CreateImage(&m_photoImage, 0x49, 0x49);
}

// FUNCTION: LEGORACERS 0x00484980
LegoBool32 PickMemoryCardScreen::Initialize(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	if (!MenuGameScreen::Initialize(p_context, p_createParams)) {
		return FALSE;
	}

	m_cursor->SetCursorEnabled(FALSE);
	MenuGameScreen::SetupLighting();
	return TRUE;
}

// FUNCTION: LEGORACERS 0x004849c0 FOLDED
LegoBool32 PickMemoryCardScreen::Destroy()
{
	if (!m_initialized) {
		return TRUE;
	}

	m_cursor->SetCursorEnabled(TRUE);
	return MenuGameScreen::Destroy();
}

// FUNCTION: LEGORACERS 0x004849e0
void PickMemoryCardScreen::OnIconUnfocused(MenuWidget* p_source)
{
	if (p_source == &m_slot0Button) {
		m_context->m_modelBuilder.SetSaveSlot(0);
		m_nextMenuId = 15;
		m_navPending = TRUE;
	}
	else if (p_source == &m_slot1Button) {
		m_context->m_modelBuilder.SetSaveSlot(1);
		m_nextMenuId = 15;
		m_navPending = TRUE;
	}
	else if (p_source == &m_slot2Button) {
		m_context->m_modelBuilder.SetSaveSlot(2);
		m_nextMenuId = 15;
		m_navPending = TRUE;
	}
	else if (p_source == &m_slot3Button) {
		m_context->m_modelBuilder.SetSaveSlot(3);
		m_nextMenuId = 15;
		m_navPending = TRUE;
	}
	else if (p_source == &m_noCardButton) {
		m_context->m_modelBuilder.SetSaveSlot(2);
		m_nextMenuId = 15;
		m_navPending = TRUE;
	}
	else if (p_source == &m_backButton) {
		CreateTextButton(&m_confirmYesButton, 0x99, 0x46, 0x73);
		CreateTextButton(&m_confirmNoButton, 0x99, 0x45, 0x74);
		ShowConfirmDialog(&m_confirmYesButton, &m_confirmNoButton, 0x77);
	}
	else if (p_source == &m_confirmYesButton) {
		m_dialog->DismissTop();
		m_nextMenuId = 3;
		m_navPending = TRUE;
	}
	else if (p_source == &m_confirmNoButton) {
		m_dialog->DismissTop();
	}

	m_clickedWidget = p_source;
}

// FUNCTION: LEGORACERS 0x00484b50
void PickMemoryCardScreen::Navigate()
{
	switch (m_nextMenuId) {
	case 15:
		m_context->m_menuStack.Pop();

		if (!(m_context->m_modelBuilder.GetMenuFlowFlags() & DriverModelBuilder::c_menuFlowLoadRacer)) {
			m_context->m_menuStack.Push(m_nextMenuId);
		}

		m_context->m_menuStack.Push(144);

		if ((LegoU32) m_context->m_modelBuilder.GetSaveSlot() < 2) {
			m_context->m_menuStack.Push(47);
		}
		break;

	case 3:
		m_context->m_menuStack.Pop();
		break;
	}
}

// FUNCTION: LEGORACERS 0x00484be0
LegoBool32 PickMemoryCardScreen::Update(undefined4 p_arg)
{
	m_context->m_modelBuilder.SetSaveSlot(0);
	m_nextMenuId = 15;
	m_navPending = TRUE;
	return MenuGameScreen::Update(p_arg);
}
