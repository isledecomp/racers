#include "menu/screens/splashcinematicscreen.h"

#include "audio/musicgroup.h"
#include "audio/musicinstance.h"
#include "golhashtable.h"
#include "golstream.h"
#include "menu/menugamecontext.h"
#include "menu/menuscreencreateparams.h"
#include "menu/menuscreenid.h"

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
LegoBool32 SplashCinematicScreen::Initialize(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	Destroy();

	m_menuId = p_createParams->m_menuId;
	p_createParams->m_menuId = 1;

	if (!MenuSceneScreen::Initialize(p_context, p_createParams)) {
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
		StartMenuMusic(p_context, nextMenu, pushExtra);
	}

	m_sceneWidget.m_skippable = 0;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x004884f0 FOLDED
LegoBool32 SplashCinematicScreen::Destroy()
{
	if (m_context) {
		if (m_context->m_modelBuilder.GetMusicGroup()) {
			if (m_context->m_modelBuilder.GetMusicInstance()) {
				m_context->m_modelBuilder.GetMusicInstance()->Stop();
				m_context->m_modelBuilder.GetMusicGroup()->DestroyMusicInstance(
					m_context->m_modelBuilder.GetMusicInstance()
				);
				m_context->m_modelBuilder.SetMusicInstance(NULL);
			}
		}
	}

	return MenuSceneScreen::Destroy();
}

// FUNCTION: LEGORACERS 0x00488550
void SplashCinematicScreen::CreateWidgets()
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

	CreateRegion(&m_sceneWidget, m_menuId);
}

// FUNCTION: LEGORACERS 0x00488630
void SplashCinematicScreen::Navigate()
{
	m_context->m_menuStack.Pop();
	m_cursor->SetCursorEnabled(TRUE);

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
LegoBool32 SplashCinematicScreen::Update(undefined4 p_elapsedMs)
{
	if (m_menuId != c_menuLegoIntro) {
		m_sceneWidget.m_skippable = 1;
	}

	return MenuSceneScreen::Update(p_elapsedMs);
}
