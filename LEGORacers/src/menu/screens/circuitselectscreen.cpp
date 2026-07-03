#include "menu/screens/circuitselectscreen.h"

#include "audio/musicgroup.h"
#include "audio/musicinstance.h"
#include "golhashtable.h"
#include "golstring.h"
#include "menu/menugamecontext.h"
#include "menu/menuscreencreateparams.h"
#include "menu/menuscreenid.h"

#include <stdio.h>

DECOMP_SIZE_ASSERT(CircuitSelectScreen, 0x658)

// FUNCTION: LEGORACERS 0x00479a80
CircuitSelectScreen::CircuitSelectScreen()
{
}

// FUNCTION: LEGORACERS 0x00479ac0
CircuitSelectScreen::~CircuitSelectScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00479b10
LegoBool32 CircuitSelectScreen::Initialize(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	if (m_initialized) {
		Destroy();
	}

	if (!MenuSceneScreen::Initialize(p_context, p_createParams)) {
		return FALSE;
	}

	LegoS32 musicId = 1;
	switch (m_resourceMenuId - c_menuCircuit1) {
	case 0:
		musicId = 5;
		break;
	case 1:
		musicId = 6;
		break;
	case 2:
		musicId = 7;
		break;
	case 3:
		musicId = 8;
		break;
	case 4:
		musicId = 9;
		break;
	case 5:
		musicId = 10;
		break;
	}

	StartMenuMusic(p_context, musicId, FALSE);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00479bd0
LegoBool32 CircuitSelectScreen::Destroy()
{
	if (!m_initialized) {
		return TRUE;
	}

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

// FUNCTION: LEGORACERS 0x00479c40
void CircuitSelectScreen::CreateWidgets()
{
	struct ResourcePathLocals {
		LegoChar m_name[12];
		GolString m_string;
		LegoChar m_path[20];
	} locals;

	m_menuNameStrings->CopyStringByIndex(&locals.m_string, m_resourceMenuId);
	locals.m_string.CopyToString(locals.m_name);
	::sprintf(locals.m_path, "MENUDATA\\%s", locals.m_name);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString(locals.m_path);
	}

	CreateRegion(&m_sceneWidget, m_resourceMenuId);
	m_sceneWidget.m_skippable = FALSE;
}

// FUNCTION: LEGORACERS 0x00479d10
void CircuitSelectScreen::Navigate()
{
	m_context->m_menuStack.Pop();

	if (m_context->m_menuStack.Peek() == c_menuMainMenu) {
		m_context->m_menuStack.ResetSize();
		m_context->m_menuStack.Push(c_menuMainMenu);
	}
	else {
		m_context->m_menuStack.ResetSize();
	}
}

// FUNCTION: LEGORACERS 0x00480b50 FOLDED
LegoBool32 CircuitSelectScreen::Update(undefined4 p_elapsedMs)
{
	m_sceneWidget.m_skippable = TRUE;
	return MenuSceneScreen::Update(p_elapsedMs);
}
