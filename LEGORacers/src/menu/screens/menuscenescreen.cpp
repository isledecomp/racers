#include "menu/screens/menuscenescreen.h"

#include "app/golapp.h"
#include "app/legoracers.h"
#include "font/golfont.h"
#include "golhashtable.h"
#include "golname.h"
#include "golstream.h"
#include "menu/menugamecontext.h"
#include "menu/menuscreencreateparams.h"
#include "menu/menuscreenid.h"
#include "render/gold3drenderdevice.h"

#include <string.h>

DECOMP_SIZE_ASSERT(MenuSceneScreen, 0x658)

// FUNCTION: LEGORACERS 0x004796a0
MenuSceneScreen::MenuSceneScreen() : m_renderer(NULL), m_savedCamera(NULL), m_firstUpdate(0)
{
}

// FUNCTION: LEGORACERS 0x00479730
MenuSceneScreen::~MenuSceneScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004797a0
LegoBool32 MenuSceneScreen::Initialize(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	if (m_initialized) {
		Destroy();
	}

	m_renderer = p_createParams->m_renderer;
	p_context->m_context->m_golApp->ClearFileSourceDirectoryCaches();
	m_savedCamera = m_renderer->GetCurrentCamera();

	if (!MenuGameScreen::Initialize(p_context, p_createParams)) {
		return FALSE;
	}

	GolName fontName;
	::strncpy(fontName, "font_ths", sizeof(fontName));

	GolFont* font = m_renderer->FindFontByName(fontName);
	if (font) {
		font->SetColor(0xff, 0xff, 0xff, 0xff);
	}

	CutscenePlayer* resourceHelper = &m_sceneWidget.m_player;
	if (resourceHelper->GetTextVisualCount() && p_context->m_context->m_languageIndex) {
		LegoChar languageFile[12];
		languageFile[0] = '\0';

		switch (p_context->m_context->m_languageIndex) {
		case 1:
			::strcpy(languageFile, "spanish");
			break;
		case 2:
			::strcpy(languageFile, "french");
			break;
		case 3:
			::strcpy(languageFile, "german");
			break;
		case 4:
			::strcpy(languageFile, "italian");
			break;
		case 5:
			::strcpy(languageFile, "danish");
			break;
		case 6:
			::strcpy(languageFile, "swedish");
			break;
		case 7:
			::strcpy(languageFile, "norwegi");
			break;
		case 8:
			::strcpy(languageFile, "dutch");
			break;
		case 9:
			break;
		case 10:
			::strcpy(languageFile, "finnish");
			break;
		}

		::strcat(languageFile, ".srf");
		m_languageStrings.UseOwnedBuffers();

		if (m_languageStrings.Load(languageFile)) {
			resourceHelper->SetStringTable(&m_languageStrings);
			resourceHelper->RefreshTextVisuals();
		}
	}

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}

	m_cursor->SetCursorEnabled(FALSE);
	m_firstUpdate = TRUE;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x004799b0
LegoBool32 MenuSceneScreen::Destroy()
{
	m_languageStrings.ReleaseOwnedBuffers();
	m_sceneWidget.Destroy();

	if (m_renderer && m_savedCamera) {
		m_renderer->SetCamera(m_savedCamera);
	}

	m_renderer = NULL;
	m_savedCamera = NULL;
	return MenuGameScreen::Destroy();
}

// FUNCTION: LEGORACERS 0x00479a10
LegoBool32 MenuSceneScreen::Update(undefined4 p_elapsedMs)
{
	if (m_firstUpdate) {
		p_elapsedMs = 0x11;
		m_firstUpdate = FALSE;
	}

	if (m_sceneWidget.m_finished) {
		m_navPending = TRUE;
	}

	return MenuGameScreen::Update(p_elapsedMs);
}

// FUNCTION: LEGORACERS 0x00479a50
void MenuSceneScreen::Navigate()
{
	m_cursor->SetCursorEnabled(TRUE);
	m_context->m_menuStack.Pop();
	m_context->m_menuStack.Push(c_menuMainMenu);
}
