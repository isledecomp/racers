#include "imaginarychisel0x658.h"

#include "bronzefalcon0xc8770.h"
#include "golapp.h"
#include "golfont0xa0.h"
#include "golhashtable.h"
#include "golstream.h"
#include "legoracers.h"
#include "menutoolcontext0x4bc8.h"
#include "menutoolcreateparams0x30.h"

#include <string.h>

DECOMP_SIZE_ASSERT(ImaginaryChisel0x658, 0x658)
DECOMP_SIZE_ASSERT(ImaginaryChisel0x658::HelperAt0x368, 0x2d0)

// STUB: LEGORACERS 0x00466090 FOLDED
undefined4 ImaginaryChisel0x658::HelperAt0x368::VTable0x2c(void*, undefined4, undefined4)
{
	STUB(0x00466090);
	return 0;
}

// STUB: LEGORACERS 0x00466a10
ImaginaryChisel0x658::HelperAt0x368::HelperAt0x368()
{
	STUB(0x00466a10);
}

// STUB: LEGORACERS 0x00466aa0
ImaginaryChisel0x658::HelperAt0x368::~HelperAt0x368()
{
	STUB(0x00466aa0);
}

// STUB: LEGORACERS 0x00466d60
undefined4 ImaginaryChisel0x658::HelperAt0x368::VTable0x08()
{
	STUB(0x00466d60);
	return 0;
}

// STUB: LEGORACERS 0x00466d90
undefined4 ImaginaryChisel0x658::HelperAt0x368::VTable0x3c(undefined4)
{
	STUB(0x00466d90);
	return 0;
}

// STUB: LEGORACERS 0x00466e40
undefined4 ImaginaryChisel0x658::HelperAt0x368::VTable0x38(Rect*, Rect*)
{
	STUB(0x00466e40);
	return 0;
}

// STUB: LEGORACERS 0x00466ec0
undefined4 ImaginaryChisel0x658::HelperAt0x368::VTable0x30(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4)
{
	STUB(0x00466ec0);
	return 0;
}

// STUB: LEGORACERS 0x00466f20
undefined4 ImaginaryChisel0x658::HelperAt0x368::VTable0x34(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4)
{
	STUB(0x00466f20);
	return 0;
}

// FUNCTION: LEGORACERS 0x004796a0
ImaginaryChisel0x658::ImaginaryChisel0x658() : m_unk0x64c(NULL), m_unk0x650(NULL), m_unk0x654(0)
{
}

// FUNCTION: LEGORACERS 0x00479730
ImaginaryChisel0x658::~ImaginaryChisel0x658()
{
	VTable0x74();
}

// FUNCTION: LEGORACERS 0x004797a0
LegoBool32 ImaginaryChisel0x658::VTable0x8c(MenuToolContext0x4bc8* p_context, MenuToolCreateParams0x30* p_createParams)
{
	if (m_unk0x04) {
		VTable0x74();
	}

	m_unk0x64c = p_createParams->m_renderer;
	p_context->m_context->m_golApp->ClearFileSourceDirectoryCaches();
	m_unk0x650 = m_unk0x64c->GetUnk0x0c();

	if (!ImaginaryTool0x368::VTable0x8c(p_context, p_createParams)) {
		return FALSE;
	}

	LegoChar fontName[8];
	::strncpy(fontName, "font_ths", sizeof(fontName));

	GolFont0xa0* font = m_unk0x64c->FindFontByName(fontName);
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

	m_unk0xc4->SetUnk0x41(FALSE);
	m_unk0x654 = TRUE;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x004799b0
void ImaginaryChisel0x658::VTable0x74()
{
	m_unk0x638.ReleaseOwnedBuffers();
	m_unk0x368.VTable0x08();

	if (m_unk0x64c && m_unk0x650) {
		m_unk0x64c->VTable0x20(m_unk0x650);
	}

	m_unk0x64c = NULL;
	m_unk0x650 = NULL;
	ImaginaryTool0x368::VTable0x74();
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
	m_unk0xc4->SetUnk0x41(TRUE);
	m_unk0x354->m_unk0x04.Pop();
	m_unk0x354->m_unk0x04.Push(2);
}
