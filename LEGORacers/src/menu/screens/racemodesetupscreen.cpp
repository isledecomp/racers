#include "menu/screens/racemodesetupscreen.h"

#include "golname.h"
#include "golstringtable.h"
#include "menu/menugamecontext.h"
#include "menu/menuscreencreateparams.h"
#include "race/data/racenameentry.h"
#include "save/savesystem.h"

#include <string.h>

DECOMP_SIZE_ASSERT(RaceModeSetupScreen, 0x2e60)

// GLOBAL: LEGORACERS 0x004c2204
LegoChar g_veronicaVoltageName[] = "VV";

// FUNCTION: LEGORACERS 0x00487850
RaceModeSetupScreen::RaceModeSetupScreen()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004879b0
RaceModeSetupScreen::~RaceModeSetupScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00487ae0
void RaceModeSetupScreen::Reset()
{
	m_unk0x2e08 = 0;
	m_unk0x2e0c = 0;
	m_unk0x2e10 = 0;
	::memset(m_unk0x2e14, 0, sizeof(m_unk0x2e14));
	::memset(m_unk0x2e32, 0, sizeof(m_unk0x2e32));
	m_unk0x2e48.CopyFromBufSelection(m_unk0x2e14, sizeOfArray(m_unk0x2e14) - 1);
	m_unk0x2e54.CopyFromBufSelection(m_unk0x2e32, sizeOfArray(m_unk0x2e32) - 1);
	MenuGameScreen::Reset();
}

// FUNCTION: LEGORACERS 0x00487b50
void RaceModeSetupScreen::VTable0x4c()
{
	CreateImage(&m_unk0x1908, 0x49, 0x49);
	SingleRaceSelectBase::VTable0x4c();

	undefined4 textId;
	if (m_menuId != 6) {
		textId = 0x0f;
	}
	else {
		textId = 0x0e + ((m_context->m_modelBuilder.GetUnk0x78() & 2) ? 0x0b : 0);
	}

	CreateTextLabel(&m_unk0x1964, 0x3a, 0x3a, textId);
	m_unk0x1964.FUN_0046f6b0(0x14);
	CreateCarousel(&m_unk0x1fc0, 0x3d, 0x3b);
	CreateSelector(&m_unk0x2054, &m_unk0x1fc0, 0x69, 0x4c);
	FUN_0047fdc0(&m_unk0x19dc, 0x40, 0x46, 0x72);
	FUN_0047fdc0(&m_unk0x1ccc, 0x3f, 0x43, 2);

	for (LegoS32 i = 0; i < sizeOfArray(m_unk0x2a48); i++) {
		CreateTextLabel(&m_unk0x2a48[i], 0x96, 0x37, 0x70);
	}

	if (m_menuId == 0x1d) {
		CreateTextLabel(&m_unk0x2c28, 0x6a, 0x37, 0x70);
		CreateTextLabel(&m_unk0x2ca0, 0x6c, 0x37, 0x70);
		CreateTextLabel(&m_unk0x2d18, 0x6b, 0x37, 0x70);
		m_unk0x2e10 = 1;
		FUN_004881a0();
		CreateTextLabel(&m_unk0x2d90, 0x6d, 0x37, 0x49);
		m_unk0x2d90.ClearFlags(2);
	}
}

// FUNCTION: LEGORACERS 0x00487ca0
LegoBool32 RaceModeSetupScreen::VTable0x8c(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	m_menuId = p_createParams->m_menuId;
	p_createParams->m_menuId = 6;
	m_unk0x1fbc = p_context->m_context->m_racerCount;

	LegoBool32 result = SingleRaceSelectBase::VTable0x8c(p_context, p_createParams);
	if (!result) {
		return FALSE;
	}

	VTable0x44(&m_unk0xbe8);
	m_unk0x19dc.VTable0x4c(0);
	m_unk0x2e08 = 2500;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00487d10
void RaceModeSetupScreen::VTable0x3c(MenuIcon* p_unk0x04)
{
	m_unk0x358 = p_unk0x04;
	FUN_00488010();
}

// FUNCTION: LEGORACERS 0x00487d40
void RaceModeSetupScreen::VTable0x38(MenuWidget* p_source)
{
	MenuWidget* source = p_source;
	if (source == &m_unk0x19dc) {
		CircuitDefinitionList::CircuitDefinition* circuitDefinition = m_unk0x1904;
		if (circuitDefinition) {
			LegoRacers::Context* context = m_context->m_context;
			::memcpy(context->m_circuitName, circuitDefinition->GetName(), sizeof(GolName));

			RaceNameEntry* raceNameEntry = m_unk0x1904->GetRaceNameEntry(m_unk0x1fc0.GetUnk0x6c());
			if (raceNameEntry) {
				::memcpy(context->m_raceSlots[0].m_raceName, raceNameEntry->GetName(), sizeof(GolName));
				::memcpy(context->m_raceSlots[0].m_folderName, raceNameEntry->GetFolderName(), sizeof(GolName));
				context->m_raceSlots[0].m_enabled = TRUE;
				context->m_raceSlots[0].m_mirror = raceNameEntry->GetMirror();
			}

			// Both branches assign the same id in the original; the flag test is real but inert
			if (m_context->m_modelBuilder.GetUnk0x78() & 2) {
				m_unk0x360 = 0x13;
			}
			else {
				m_unk0x360 = 0x13;
			}
		}
	}
	else if (source == &m_unk0x1ccc) {
		m_context->m_modelBuilder.SetUnk0x78(m_context->m_modelBuilder.GetUnk0x78() & ~2);
		m_unk0x360 = 2;
	}

	if (m_unk0x360 != 0xffff) {
		m_unk0x364 = TRUE;
	}

	m_unk0x35c = source;
}

// FUNCTION: LEGORACERS 0x00487e10
void RaceModeSetupScreen::VTable0x44(MenuWidget* p_source)
{
	GolString string;
	LegoBool32 isComplete = FALSE;

	if (p_source == &m_unk0xbe8) {
		LegoU32 circuitIndex = m_unk0xb54.GetUnk0x6c();
		m_unk0x1904 = m_context->m_circuitList.GetEntry(circuitIndex);

		if (m_unk0x1904) {
			LegoU8 mask = static_cast<LegoU8>(1 << m_context->m_circuitList.GetEntryIndex(m_unk0x1904));
			LegoU8 flags = m_context->m_saveSystem.GetGameState().GetUnlockedCircuits();
			if (flags & mask) {
				isComplete = TRUE;
			}
		}

		m_unk0x1fc0.FUN_0046da60();
		for (LegoS32 i = 0; i < sizeOfArray(m_unk0x2a48); i++) {
			RaceNameEntry* raceNameEntry = m_unk0x1904->GetRaceNameEntry(i);
			if (raceNameEntry) {
				raceNameEntry->CopyDisplayString(&string);
				m_unk0x2a48[i].VTable0x40(&string, TRUE);
				m_unk0x1fc0.FUN_0046d9c0(&m_unk0x2a48[i]);
			}
		}
		m_unk0x1fc0.VTable0x50(0);

		if (isComplete) {
			m_unk0x19dc.VTable0x44(5);
			m_unk0x1860.ClearFlags(2);
		}
		else {
			m_unk0x19dc.VTable0x48(5);
			m_unk0x1860.SetFlags(2);
		}
	}

	FUN_00488010();
}

// FUNCTION: LEGORACERS 0x00487f90
void RaceModeSetupScreen::VTable0x84()
{
	if (m_unk0x360 == 2) {
		m_context->m_context->m_racerCount = m_unk0x1fbc;
		m_context->m_menuStack.Pop();
		return;
	}

	if (m_menuId == 6) {
		m_context->m_context->m_raceMode = LegoRacers::Context::c_raceModeSingle;
	}
	else {
		m_context->m_context->m_raceMode = LegoRacers::Context::c_raceModeTimeRace;
		m_context->m_context->m_racerCount = 0;
	}

	m_context->m_menuStack.Push(m_unk0x360);
}

// FUNCTION: LEGORACERS 0x00488010
void RaceModeSetupScreen::FUN_00488010()
{
	GolName frameName;
	GolName driverName;
	GolName raceName;
	driverName[0] = '\0';

	LegoU32 selectedEntryIndex = m_unk0x1fc0.GetUnk0x6c();
	RaceNameEntry* raceNameEntry = m_unk0x1904->GetRaceNameEntry(selectedEntryIndex);
	if (!raceNameEntry) {
		return;
	}

	::memcpy(frameName, raceNameEntry->GetThemeName(), sizeof(GolName));
	if (m_menuId != 0x1d) {
		::memcpy(driverName, raceNameEntry->GetMascotName(), sizeof(GolName));
	}
	else {
		::strcpy(driverName, g_veronicaVoltageName);
	}

	GolNameTable* frameNames = &m_unk0x368.m_unk0x58;
	CutsceneDefinition::Frame* frame;
	if (!frameNames->GetNameEntries()) {
		frame = NULL;
	}
	else {
		frame = static_cast<CutsceneDefinition::Frame*>(frameNames->GetName(frameName));
	}

	LegoChar* raceNameSource = raceNameEntry->GetName();
	::memcpy(raceName, raceNameSource, sizeof(GolName));
	m_unk0x2e0c = m_context->m_raceNames.GetEntryIndexByName(raceName);
	if (frame && frame != m_unk0x368.m_unk0x2b0) {
		m_unk0x368.FUN_00466d00(frame);
		m_unk0x368.m_unk0x2b0->SetFlags(CutsceneDefinition::Frame::c_flagLoop);
		m_unk0x2e10 = TRUE;
		FUN_004881a0();
	}

	LegoU32 circuitIndex = m_context->m_circuitList.GetEntryIndex(m_unk0x1904);
	LegoU32 visualStateIndex = circuitIndex * 4;
	visualStateIndex += selectedEntryIndex;
	FUN_00488cb0(visualStateIndex);
	if (driverName[0]) {
		FUN_00488b40(driverName);
	}
}

// FUNCTION: LEGORACERS 0x00488150
LegoBool32 RaceModeSetupScreen::VTable0x78(undefined4 p_elapsed)
{
	if (p_elapsed > m_unk0x2e08) {
		m_unk0x2e10 = (m_unk0x2e10 == 0);
		FUN_004881a0();
	}
	else {
		m_unk0x2e08 -= p_elapsed;
	}

	return MenuSceneScreen::VTable0x78(p_elapsed);
}

// FUNCTION: LEGORACERS 0x004881a0
void RaceModeSetupScreen::FUN_004881a0()
{
	GolString string;
	LegoU32 bestTime = 0xffffffff;

	if (m_menuId != 0x1d) {
		return;
	}

	::memset(m_unk0x2e14, 0, sizeof(m_unk0x2e14));
	::memset(m_unk0x2e32, 0, sizeof(m_unk0x2e32));

	undefined2 buffer[15];
	::memset(buffer, 0, sizeof(buffer));
	string.CopyFromBufSelection(buffer, 14);

	LegoBool32 raceTime = (m_unk0x2e10 == FALSE);
	LegoU16 unlockedMask = m_context->m_saveSystem.GetGameState().GetUnlockedRaces();
	LegoU32 time = m_context->m_saveSystem.GetGameState().GetBestTime(m_unk0x2e0c, raceTime, &string);
	if (time && time < 0xffffffff) {
		bestTime = time;
		m_unk0x2e48.GolStrcpy(&string);
	}

	if (m_unk0x2e10) {
		m_unk0x2d18.VTable0x44(0x46, 0);
	}
	else {
		m_unk0x2d18.VTable0x44(0x47, 0);
	}

	if (bestTime != 0xffffffff) {
		LegoChar time[9];
		FUN_004246d0(time, bestTime);
		GolString::CopyStringToBuf16(time, m_unk0x2e32);
		m_unk0x2ca0.VTable0x40(&m_unk0x2e48, 0);
	}
	else if (m_unk0x2e10) {
		m_unk0x2ca0.VTable0x44(0xbe, 0);
	}
	else {
		m_unk0x2ca0.VTable0x44(0xbf, 0);
	}

	m_unk0x2c28.VTable0x40(&m_unk0x2e54, 0);
	m_unk0x2e08 = 2500;

	if (static_cast<LegoU16>(unlockedMask & (1 << m_unk0x2e0c))) {
		m_unk0x2d90.SetFlags(2);
	}
	else {
		m_unk0x2d90.ClearFlags(2);
	}
}
