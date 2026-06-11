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
LegoBool32 MainIntroScreen::VTable0x8c(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	if (m_initialized) {
		Destroy();
	}

	if (!MenuSceneScreen::VTable0x8c(p_context, p_createParams)) {
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
	m_unk0x368.m_unk0x2cc = FALSE;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00480ad0
void MainIntroScreen::VTable0x4c()
{
	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA\\MAININTR");
	}

	CreateRegion(&m_unk0x368, m_unk0x28c);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}
}

// FUNCTION: LEGORACERS 0x00480b20
void MainIntroScreen::VTable0x84()
{
	m_context->m_menuStack.Pop();
	m_context->m_menuStack.Push(c_menuLegal);
}

// FUNCTION: LEGORACERS 0x00480b50 FOLDED
LegoBool32 MainIntroScreen::VTable0x78(undefined4 p_unk0x04)
{
	m_unk0x368.m_unk0x2cc = TRUE;
	return MenuSceneScreen::VTable0x78(p_unk0x04);
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
