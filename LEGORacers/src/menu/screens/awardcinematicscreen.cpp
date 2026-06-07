#include "menu/screens/awardcinematicscreen.h"

#include "audio/musicgroup.h"
#include "audio/musicinstance.h"
#include "core/gol.h"
#include "golhashtable.h"
#include "golstring.h"
#include "menu/menugamecontext.h"
#include "menu/menuscreencreateparams.h"
#include "menu/menuscreenid.h"
#include "model/carbuildmodel.h"

#include <stdio.h>
#include <string.h>

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
LegoBool32 AwardCinematicScreen::VTable0x8c(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	if (m_initialized) {
		Destroy();
	}

	m_unk0x7ac = 0;
	m_unk0x7a8 = 0;
	m_unk0x7a4 = 0;

	if (p_createParams->m_menuId == c_menuWinRrCar && p_context->m_unk0x21f4.IsInitialized()) {
		p_context->m_unk0x21f4.FUN_00499f00();
	}

	if (!MenuSceneScreen::VTable0x8c(p_context, p_createParams)) {
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

	LegoBool32 result = MenuSceneScreen::Destroy();
	if (m_unk0x28c == c_menuWinRrCar) {
		MenuGameContext* context = m_context;
		if (context->m_unk0x21f4.IsInitialized()) {
			m_context->m_unk0x21f4.FUN_00499ee0();
		}
	}

	return result;
}

// STUB: LEGORACERS 0x00475f40
void AwardCinematicScreen::VTable0x4c()
{
	struct ResourcePathLocals {
		LegoChar m_name[12];
		GolString m_string;
		LegoChar m_path[20];
	} locals;

	if (m_unk0x28c != c_menuWinVvCar) {
		if (!m_context->m_unk0x4b40.HasMenuResources()) {
			FUN_00480210(m_context, FALSE);
		}

		if (!m_context->m_unk0x425c.HasEntries()) {
			FUN_00480310();
		}
	}

	m_menuNameStrings->CopyStringByIndex(&locals.m_string, m_unk0x28c);
	locals.m_string.CopyToString(locals.m_name);
	::sprintf(locals.m_path, "MENUDATA\\%s", locals.m_name);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString(locals.m_path);
	}

	CreateRegion(&m_unk0x368, m_unk0x28c);
	m_unk0x368.m_unk0x2cc = FALSE;
	FUN_004767b0();
}

// FUNCTION: LEGORACERS 0x004767b0
LegoBool32 AwardCinematicScreen::FUN_004767b0()
{
	GameState* gameState = &m_context->m_unk0x258.GetUnk0x18c4();
	LegoU16 menuId = m_unk0x28c;

	if (menuId != c_menuChampAward1 && menuId != c_menuChampAward2 && menuId != c_menuChampAward3) {
		return FALSE;
	}

	LegoRacers::Context* context = m_context->m_context;
	PeridotTraceBase0x24* trace = NULL;

	switch (context->m_playerRecordStates[0].m_unk0x00) {
	case 1:
	case 3:
		trace = &m_context->m_unk0x258.GetUnk0x108();
		break;
	case 2:
		trace = &m_context->m_unk0x258.GetUnk0xa58()[context->m_playerRecordStates[0].m_unk0x04];
		break;
	default:
		return FALSE;
	}

	if (trace == NULL) {
		return FALSE;
	}

	RaceDefinitionList::RaceDefinition* raceDefinition =
		static_cast<RaceDefinitionList::RaceDefinition*>(m_context->m_raceList.GetName(context->m_unk0x2d));
	m_unk0x7a4 = FUN_00476890(trace, raceDefinition);

	if (m_unk0x28c != c_menuChampAward1 && m_unk0x28c != c_menuChampAward2) {
		return FALSE;
	}

	m_unk0x7a8 = FUN_00476990(gameState, raceDefinition);
	m_unk0x7ac = FUN_004768f0(gameState, raceDefinition);
	return m_unk0x7ac;
}

// FUNCTION: LEGORACERS 0x00476890
LegoBool32 AwardCinematicScreen::FUN_00476890(
	PeridotTraceBase0x24* p_trace,
	RaceDefinitionList::RaceDefinition* p_raceDefinition
)
{
	PeridotTraceBase0x24::Record* record =
		p_trace->FUN_0042b9b0(m_context->m_context->m_playerRecordStates[0].m_unk0x08);
	if (record == NULL) {
		return FALSE;
	}

	return record->FUN_0042b640(m_context->m_raceList.GetEntryIndex(p_raceDefinition), m_unk0x28c - 0x15);
}

// FUNCTION: LEGORACERS 0x004768f0
LegoBool32 AwardCinematicScreen::FUN_004768f0(
	GameState* p_gameState,
	RaceDefinitionList::RaceDefinition* p_raceDefinition
)
{
	GolName menuName;
	::memcpy(menuName, p_raceDefinition->GetMenuName(), sizeof(menuName));

	if (menuName[0] != '\0') {
		RaceDefinitionList::RaceDefinition* menuRaceDefinition =
			static_cast<RaceDefinitionList::RaceDefinition*>(m_context->m_raceList.GetName(menuName));
		LegoU8 mask = static_cast<LegoU8>(1 << m_context->m_raceList.GetEntryIndex(menuRaceDefinition));

		if (!(p_gameState->FUN_0042f1f0() & mask)) {
			p_gameState->FUN_0042f220(mask);
			m_context->m_unk0x4b40.SetUnk0x78(m_context->m_unk0x4b40.GetUnk0x78() | 4);
			return TRUE;
		}
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00476990
LegoBool32 AwardCinematicScreen::FUN_00476990(
	GameState* p_gameState,
	RaceDefinitionList::RaceDefinition* p_raceDefinition
)
{
	if (m_unk0x28c != c_menuChampAward1) {
		return FALSE;
	}

	m_unk0x7a0 = p_raceDefinition->GetStringIndex();
	if (m_unk0x7a0 == -1) {
		return FALSE;
	}

	LegoU8 mask = static_cast<LegoU8>(1 << m_unk0x7a0);
	if (p_gameState->FUN_0042f1e0() & mask) {
		m_unk0x7a0 = -1;
		return FALSE;
	}

	p_gameState->FUN_0042f200(mask);
	return TRUE;
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

	return MenuSceneScreen::VTable0x78(p_unk0x04);
}
