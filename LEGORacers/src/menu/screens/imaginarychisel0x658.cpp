#include "menu/screens/imaginarychisel0x658.h"

#include "app/golapp.h"
#include "app/legoracers.h"
#include "font/golfont0xa0.h"
#include "golhashtable.h"
#include "golname.h"
#include "golstream.h"
#include "menu/menuscreenid.h"
#include "menu/menutoolcontext0x4bc8.h"
#include "menu/menutoolcreateparams0x30.h"
#include "render/gold3drenderdevice.h"

#include <string.h>

DECOMP_SIZE_ASSERT(ImaginaryChisel0x658, 0x658)

// FUNCTION: LEGORACERS 0x004796a0
ImaginaryChisel0x658::ImaginaryChisel0x658() : m_renderer(NULL), m_unk0x650(NULL), m_unk0x654(0)
{
}

// FUNCTION: LEGORACERS 0x00479730
ImaginaryChisel0x658::~ImaginaryChisel0x658()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004797a0
LegoBool32 ImaginaryChisel0x658::VTable0x8c(MenuToolContext0x4bc8* p_context, MenuToolCreateParams0x30* p_createParams)
{
	if (m_initialized) {
		Destroy();
	}

	m_renderer = p_createParams->m_renderer;
	p_context->m_context->m_golApp->ClearFileSourceDirectoryCaches();
	m_unk0x650 = m_renderer->GetUnk0x0c();

	if (!ImaginaryTool0x368::VTable0x8c(p_context, p_createParams)) {
		return FALSE;
	}

	GolName fontName;
	::strncpy(fontName, "font_ths", sizeof(fontName));

	GolFont0xa0* font = m_renderer->FindFontByName(fontName);
	if (font) {
		font->SetColor(0xff, 0xff, 0xff, 0xff);
	}

	CrimsonPebble0x228* resourceHelper = &m_unk0x368.m_unk0x84;
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

	m_cursorHelper->SetCursorEnabled(FALSE);
	m_unk0x654 = TRUE;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x004799b0
LegoBool32 ImaginaryChisel0x658::Destroy()
{
	m_unk0x638.ReleaseOwnedBuffers();
	m_unk0x368.VTable0x08();

	if (m_renderer && m_unk0x650) {
		m_renderer->VTable0x20(m_unk0x650);
	}

	m_renderer = NULL;
	m_unk0x650 = NULL;
	return ImaginaryTool0x368::Destroy();
}

// FUNCTION: LEGORACERS 0x00479a10
LegoBool32 ImaginaryChisel0x658::VTable0x78(undefined4 p_unk0x04)
{
	if (m_unk0x654) {
		p_unk0x04 = 0x11;
		m_unk0x654 = FALSE;
	}

	if (m_unk0x368.m_unk0x2c8) {
		m_unk0x364 = TRUE;
	}

	return ImaginaryTool0x368::VTable0x78(p_unk0x04);
}

// FUNCTION: LEGORACERS 0x00479a50
void ImaginaryChisel0x658::VTable0x84()
{
	m_cursorHelper->SetCursorEnabled(TRUE);
	m_context->m_menuStack.Pop();
	m_context->m_menuStack.Push(c_menuMainMenu);
}
