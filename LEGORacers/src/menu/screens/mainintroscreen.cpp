#include "menu/screens/mainintroscreen.h"

#include "audio/musicgroup.h"
#include "audio/musicinstance.h"
#include "golerror.h"
#include "golhashtable.h"
#include "menu/menugamecontext.h"
#include "menu/menuscreencreateparams.h"
#include "menu/menuscreenid.h"

DECOMP_SIZE_ASSERT(MainIntroScreen, 0x658)

// FUNCTION: LEGORACERS 0x004809b0
MainIntroScreen::MainIntroScreen()
{
}

// FUNCTION: LEGORACERS 0x004809f0
MainIntroScreen::~MainIntroScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00480a40
LegoBool32 MainIntroScreen::Initialize(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	if (m_initialized) {
		Destroy();
	}

	if (!MenuSceneScreen::Initialize(p_context, p_createParams)) {
		return FALSE;
	}

	if (p_context->m_modelBuilder.GetMusicInstance()) {
		p_context->m_modelBuilder.GetMusicGroup()->DestroyMusicInstance(p_context->m_modelBuilder.GetMusicInstance());
		p_context->m_modelBuilder.SetMusicInstance(NULL);
	}

	p_context->m_modelBuilder.SetMusicInstance(p_context->m_modelBuilder.GetMusicGroup()->CreateMusicInstance(19));
	if (!p_context->m_modelBuilder.GetMusicInstance()) {
		GOL_FATALERROR(c_golErrorGeneral);
	}

	p_context->m_modelBuilder.GetMusicInstance()->Play(TRUE);
	m_sceneWidget.m_skippable = FALSE;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00480ad0
void MainIntroScreen::CreateWidgets()
{
	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA\\MAININTR");
	}

	CreateRegion(&m_sceneWidget, m_resourceMenuId);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}
}

// FUNCTION: LEGORACERS 0x00480b20
void MainIntroScreen::Navigate()
{
	m_context->m_menuStack.Pop();
	m_context->m_menuStack.Push(c_menuLegal);
}

// FUNCTION: LEGORACERS 0x00480b50 FOLDED
LegoBool32 MainIntroScreen::Update(undefined4 p_elapsedMs)
{
	m_sceneWidget.m_skippable = TRUE;
	return MenuSceneScreen::Update(p_elapsedMs);
}

// FUNCTION: LEGORACERS 0x004884f0 FOLDED
LegoBool32 MainIntroScreen::Destroy()
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
