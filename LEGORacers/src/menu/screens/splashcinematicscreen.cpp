#include "menu/screens/splashcinematicscreen.h"

#include "audio/musicgroup.h"
#include "audio/musicinstance.h"
#include "golhashtable.h"
#include "golstream.h"
#include "menu/menuscreenid.h"
#include "menu/menutoolcontext0x4bc8.h"
#include "menu/menutoolcreateparams0x30.h"

DECOMP_SIZE_ASSERT(SplashCinematicScreen, 0x658)

// FUNCTION: LEGORACERS 0x00488380
SplashCinematicScreen::SplashCinematicScreen()
{
}

// FUNCTION: LEGORACERS 0x004883c0
SplashCinematicScreen::~SplashCinematicScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00488410
LegoBool32 SplashCinematicScreen::VTable0x8c(MenuToolContext0x4bc8* p_context, MenuToolCreateParams0x30* p_createParams)
{
	Destroy();

	m_menuId = p_createParams->m_menuId;
	p_createParams->m_menuId = 1;

	if (!ImaginaryChisel0x658::VTable0x8c(p_context, p_createParams)) {
		return FALSE;
	}

	undefined4 nextMenu = 0;
	undefined4 pushExtra = FALSE;

	switch (m_menuId) {
	case 43:
		nextMenu = 0x15;
		break;
	case 41:
		nextMenu = 0x14;
		break;
	case 1:
		nextMenu = 0x12;
		break;
	case 39:
		nextMenu = 0x11;
		pushExtra = TRUE;
		break;
	}

	if (nextMenu) {
		FUN_00480470(p_context, nextMenu, pushExtra);
	}

	m_unk0x368.m_unk0x2cc = 0;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x004884f0 FOLDED
LegoBool32 SplashCinematicScreen::Destroy()
{
	if (m_context) {
		if (m_context->m_unk0x4b40.GetMusicGroup()) {
			if (m_context->m_unk0x4b40.GetMusicInstance()) {
				m_context->m_unk0x4b40.GetMusicInstance()->Stop();
				m_context->m_unk0x4b40.GetMusicGroup()->DestroyMusicInstance(m_context->m_unk0x4b40.GetMusicInstance());
				m_context->m_unk0x4b40.SetMusicInstance(NULL);
			}
		}
	}

	return ImaginaryChisel0x658::Destroy();
}

// FUNCTION: LEGORACERS 0x00488550
void SplashCinematicScreen::VTable0x4c()
{
	switch (m_menuId) {
	case c_menuN64Intro:
		if (g_hashTable) {
			g_hashTable->SetCurrentEntryFromString("MENUDATA\\N64INTR");
		}
		break;
	case c_menuLegoIntro:
		if (g_hashTable) {
			g_hashTable->SetCurrentEntryFromString("MENUDATA\\LEGOINTR");
		}
		break;
	case c_menuSplash:
		if (g_hashTable) {
			g_hashTable->SetCurrentEntryFromString("MENUDATA\\HVSINTRO");
		}
		break;
	case c_menuLegal:
		if (g_hashTable) {
			g_hashTable->SetCurrentEntryFromString("MENUDATA\\LEGAL");
		}
		break;
	case c_menuCredits:
		if (g_hashTable) {
			g_hashTable->SetCurrentEntryFromString("MENUDATA\\CREDITS");
		}
		break;
	}

	FUN_0046c5b0(&m_unk0x368, m_menuId);
}

// FUNCTION: LEGORACERS 0x00488630
void SplashCinematicScreen::VTable0x84()
{
	m_context->m_menuStack.Pop();
	m_cursorHelper->SetCursorEnabled(TRUE);

	switch (m_menuId) {
	case c_menuN64Intro:
		m_context->m_menuStack.Push(c_menuLegoIntro);
		return;
	case c_menuLegoIntro:
		m_context->m_menuStack.Push(c_menuSplash);
		return;
	case c_menuSplash:
		m_context->m_menuStack.Push(c_menuMainIntro);
		return;
	case c_menuLegal:
		m_context->m_menuStack.Push(c_menuMainMenu);
		m_context->m_menuStack.Push(c_menuLoadAll);
		return;
	case c_menuCredits:
		if (!m_context->m_menuStack.GetSize()) {
			m_context->m_menuStack.Push(c_menuMainMenu);
		}
		return;
	}
}

// FUNCTION: LEGORACERS 0x00488720
LegoBool32 SplashCinematicScreen::VTable0x78(undefined4 p_unk0x04)
{
	if (m_menuId != c_menuLegoIntro) {
		m_unk0x368.m_unk0x2cc = 1;
	}

	return ImaginaryChisel0x658::VTable0x78(p_unk0x04);
}
