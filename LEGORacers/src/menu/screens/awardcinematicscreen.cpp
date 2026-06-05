#include "menu/screens/awardcinematicscreen.h"

#include "audio/musicgroup.h"
#include "audio/musicinstance.h"
#include "core/gol.h"
#include "golhashtable.h"
#include "menu/menuscreenid.h"
#include "menu/menutoolcontext0x4bc8.h"
#include "menu/menutoolcreateparams0x30.h"
#include "model/sapphirereef0x2030.h"

DECOMP_SIZE_ASSERT(AwardCinematicScreen, 0x7b0)

// FUNCTION: LEGORACERS 0x00475c30
AwardCinematicScreen::AwardCinematicScreen() : m_unk0x79c(NULL), m_unk0x7a4(0), m_unk0x7a8(0), m_unk0x7ac(0)
{
	m_unk0x7a0 = -1;
}

// FUNCTION: LEGORACERS 0x00475cd0
AwardCinematicScreen::~AwardCinematicScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00475d30
LegoBool32 AwardCinematicScreen::VTable0x8c(MenuToolContext0x4bc8* p_context, MenuToolCreateParams0x30* p_createParams)
{
	if (m_initialized) {
		Destroy();
	}

	m_unk0x7ac = 0;
	m_unk0x7a8 = 0;
	m_unk0x7a4 = 0;

	if (p_createParams->m_menuId == c_menuWinRrCar && p_context->m_unk0x21f4.FUN_0049a0e0()) {
		p_context->m_unk0x21f4.FUN_00499f00();
	}

	if (!ImaginaryChisel0x658::VTable0x8c(p_context, p_createParams)) {
		return FALSE;
	}

	undefined4 musicId = 1;

	switch (m_unk0x28c) {
	case c_menuChampAward1:
		musicId = 2;
		break;
	case c_menuChampAward2:
		musicId = 3;
		break;
	case c_menuChampAward3:
		musicId = 4;
		break;
	case c_menuChampAward4:
		musicId = 0x0b;
		break;
	case c_menuWinCar:
		musicId = 0x0d;
		break;
	case c_menuWinRrCar:
		musicId = 0x0e;
		break;
	case c_menuWinVvCar:
		musicId = 0x0f;
		break;
	case c_menuCircuit7:
		musicId = 0x0c;
		break;
	}

	FUN_00480470(p_context, musicId, FALSE);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00475e50
LegoBool32 AwardCinematicScreen::Destroy()
{
	if (!m_initialized) {
		return TRUE;
	}

	FUN_004801e0();
	FUN_004800c0(m_context);
	m_unk0x658.FUN_00479590();
	m_unk0x6a8.VTable0x54();

	if (m_unk0x79c) {
		m_golExport->VTable0x48(m_unk0x79c);
		m_unk0x79c = NULL;
	}

	m_unk0x7a0 = -1;

	if (m_context) {
		if (m_context->m_unk0x4b40.GetMusicGroup() && m_context->m_unk0x4b40.GetMusicInstance()) {
			m_context->m_unk0x4b40.GetMusicInstance()->Stop();
			m_context->m_unk0x4b40.GetMusicGroup()->DestroyMusicInstance(m_context->m_unk0x4b40.GetMusicInstance());
			m_context->m_unk0x4b40.SetMusicInstance(NULL);
		}
	}

	LegoBool32 result = ImaginaryChisel0x658::Destroy();
	if (m_unk0x28c == c_menuWinRrCar) {
		MenuToolContext0x4bc8* context = m_context;
		if (context->m_unk0x21f4.FUN_0049a0e0()) {
			m_context->m_unk0x21f4.FUN_00499ee0();
		}
	}

	return result;
}

// STUB: LEGORACERS 0x00475f40
void AwardCinematicScreen::VTable0x4c()
{
	STUB(0x00475f40);
}

// FUNCTION: LEGORACERS 0x00476a00
void AwardCinematicScreen::VTable0x84()
{
	m_context->m_menuStack.Pop();

	if (m_context->m_menuStack.GetSize()) {
		if (m_context->m_menuStack.Peek() == c_menuMainMenu) {
			m_context->m_menuStack.ResetSize();
			m_context->m_menuStack.Push(c_menuMainMenu);
		}
		else {
			m_context->m_menuStack.ResetSize();
		}
	}
	else {
		m_context->m_menuStack.ResetSize();
		if (m_unk0x7a0 != -1) {
			if (m_unk0x7a0 == 6) {
				m_context->m_menuStack.Push(c_menuWinRrCar);
			}
			else {
				m_context->m_menuStack.Push(c_menuWinCar);
			}
		}
		else {
			if (m_unk0x28c == c_menuWinRrCar) {
				m_context->m_menuStack.Push(c_menuCredits);
			}
			else {
				m_context->m_menuStack.Push(c_menuMainMenu);
			}
		}
	}

	if (m_unk0x7a4 || m_unk0x7a8 || m_unk0x7ac) {
		m_context->m_menuStack.Push(c_menuSaveAll);
		m_context->m_unk0x4b40.SetUnk0x78(m_context->m_unk0x4b40.GetUnk0x78() | 0x10);
	}
}

// FUNCTION: LEGORACERS 0x00476ad0
LegoBool32 AwardCinematicScreen::VTable0x78(undefined4 p_unk0x04)
{
	if (m_unk0x28c == c_menuCircuit7) {
		m_unk0x368.m_unk0x2cc = TRUE;
	}

	return ImaginaryChisel0x658::VTable0x78(p_unk0x04);
}
