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
void PickMemoryCardScreen::VTable0x4c()
{
	CreateImage(&m_unk0x368, 0x49, 0x49);
}

// FUNCTION: LEGORACERS 0x00484980
LegoBool32 PickMemoryCardScreen::VTable0x8c(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	if (!MenuGameScreen::VTable0x8c(p_context, p_createParams)) {
		return FALSE;
	}

	m_cursor->SetCursorEnabled(FALSE);
	MenuGameScreen::VTable0x80();
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
void PickMemoryCardScreen::VTable0x38(MenuWidget* p_source)
{
	if (p_source == &m_unk0x4f4) {
		m_context->m_modelBuilder.SetUnk0x84(0);
		m_unk0x360 = 15;
		m_unk0x364 = TRUE;
	}
	else if (p_source == &m_unk0x7e4) {
		m_context->m_modelBuilder.SetUnk0x84(1);
		m_unk0x360 = 15;
		m_unk0x364 = TRUE;
	}
	else if (p_source == &m_unk0xad4) {
		m_context->m_modelBuilder.SetUnk0x84(2);
		m_unk0x360 = 15;
		m_unk0x364 = TRUE;
	}
	else if (p_source == &m_unk0xdc4) {
		m_context->m_modelBuilder.SetUnk0x84(3);
		m_unk0x360 = 15;
		m_unk0x364 = TRUE;
	}
	else if (p_source == &m_unk0x10b4) {
		m_context->m_modelBuilder.SetUnk0x84(2);
		m_unk0x360 = 15;
		m_unk0x364 = TRUE;
	}
	else if (p_source == &m_unk0x13a4) {
		FUN_0047fdc0(&m_unk0x1c74, 0x99, 0x46, 0x73);
		FUN_0047fdc0(&m_unk0x1f64, 0x99, 0x45, 0x74);
		FUN_0046c6f0(&m_unk0x1c74, &m_unk0x1f64, 0x77);
	}
	else if (p_source == &m_unk0x1c74) {
		m_unk0x284->FUN_00468cf0();
		m_unk0x360 = 3;
		m_unk0x364 = TRUE;
	}
	else if (p_source == &m_unk0x1f64) {
		m_unk0x284->FUN_00468cf0();
	}

	m_unk0x35c = p_source;
}

// FUNCTION: LEGORACERS 0x00484b50
void PickMemoryCardScreen::VTable0x84()
{
	switch (m_unk0x360) {
	case 15:
		m_context->m_menuStack.Pop();

		if (!(m_context->m_modelBuilder.GetUnk0x78() & 8)) {
			m_context->m_menuStack.Push(m_unk0x360);
		}

		m_context->m_menuStack.Push(144);

		if ((LegoU32) m_context->m_modelBuilder.GetUnk0x84() < 2) {
			m_context->m_menuStack.Push(47);
		}
		break;

	case 3:
		m_context->m_menuStack.Pop();
		break;
	}
}

// FUNCTION: LEGORACERS 0x00484be0
LegoBool32 PickMemoryCardScreen::VTable0x78(undefined4 p_arg)
{
	m_context->m_modelBuilder.SetUnk0x84(0);
	m_unk0x360 = 15;
	m_unk0x364 = TRUE;
	return MenuGameScreen::VTable0x78(p_arg);
}
