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
MenuSceneScreen::MenuSceneScreen() : m_renderer(NULL), m_unk0x650(NULL), m_unk0x654(0)
{
}

// FUNCTION: LEGORACERS 0x00479730
MenuSceneScreen::~MenuSceneScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004797a0
LegoBool32 MenuSceneScreen::VTable0x8c(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	if (m_initialized) {
		Destroy();
	}

	m_renderer = p_createParams->m_renderer;
	p_context->m_context->m_golApp->ClearFileSourceDirectoryCaches();
	m_unk0x650 = m_renderer->GetUnk0x0c();

	if (!MenuGameScreen::VTable0x8c(p_context, p_createParams)) {
		return FALSE;
	}

	GolName fontName;
	::strncpy(fontName, "font_ths", sizeof(fontName));

	GolFont* font = m_renderer->FindFontByName(fontName);
	if (font) {
		font->SetColor(0xff, 0xff, 0xff, 0xff);
	}

	CutscenePlayer* resourceHelper = &m_unk0x368.m_unk0x84;
	if (resourceHelper->GetUnk0x118() && p_context->m_context->m_languageIndex) {
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
		m_unk0x638.UseOwnedBuffers();

		if (m_unk0x638.Load(languageFile)) {
			resourceHelper->SetStringTable(&m_unk0x638);
			resourceHelper->FUN_004a24e0();
		}
	}

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}

	m_cursor->SetCursorEnabled(FALSE);
	m_unk0x654 = TRUE;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x004799b0
LegoBool32 MenuSceneScreen::Destroy()
{
	m_unk0x638.ReleaseOwnedBuffers();
	m_unk0x368.VTable0x08();

	if (m_renderer && m_unk0x650) {
		m_renderer->VTable0x20(m_unk0x650);
	}

	m_renderer = NULL;
	m_unk0x650 = NULL;
	return MenuGameScreen::Destroy();
}

// FUNCTION: LEGORACERS 0x00479a10
LegoBool32 MenuSceneScreen::VTable0x78(undefined4 p_unk0x04)
{
	if (m_unk0x654) {
		p_unk0x04 = 0x11;
		m_unk0x654 = FALSE;
	}

	if (m_unk0x368.m_unk0x2c8) {
		m_unk0x364 = TRUE;
	}

	return MenuGameScreen::VTable0x78(p_unk0x04);
}

// FUNCTION: LEGORACERS 0x00479a50
void MenuSceneScreen::VTable0x84()
{
	m_cursor->SetCursorEnabled(TRUE);
	m_context->m_menuStack.Pop();
	m_context->m_menuStack.Push(c_menuMainMenu);
}
