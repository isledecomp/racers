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

// FUNCTION: LEGORACERS 0x004246d0 FOLDED
LegoU32 RaceModeSetupScreen::FormatTime(LegoChar* p_buffer, LegoU32 p_time)
{
	LegoU32 millisecondsPerHour = 3600000;
	LegoS32 divisor = 10;
	LegoU32 time = p_time % millisecondsPerHour;
	LegoS32 digitOffset;

	p_buffer[8] = '\0';
	if (time >= 600000) {
		digitOffset = 7;
		p_buffer[5] = ':';
		p_buffer[2] = ':';
	}
	else {
		digitOffset = 6;
		p_buffer[4] = ':';
		p_buffer[1] = ':';
		p_buffer[7] = '\0';
	}

	LegoU32 centiseconds = time / 10;
	p_buffer[digitOffset] = static_cast<LegoChar>(centiseconds % 10 + '0');
	centiseconds /= 10;
	p_buffer[digitOffset - 1] = static_cast<LegoChar>(centiseconds % 10 + '0');

	LegoU32 seconds = centiseconds / divisor;
	LegoS32 secondsWithinMinute = static_cast<LegoS32>(seconds % 60);
	LegoU32 minutes = seconds / 60;
	p_buffer[digitOffset - 3] = static_cast<LegoChar>(secondsWithinMinute % divisor + '0');
	p_buffer[digitOffset - 4] = static_cast<LegoChar>((secondsWithinMinute / divisor) % divisor + '0');

	p_buffer[digitOffset - 6] = static_cast<LegoChar>(minutes % divisor + '0');
	LegoU32 extraMinutes = minutes / divisor;
	if (extraMinutes) {
		p_buffer[digitOffset - 7] = static_cast<LegoChar>(extraMinutes % divisor + '0');
		extraMinutes /= divisor;
	}

	return extraMinutes;
}

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
	m_recordToggleMs = 0;
	m_selectedRaceIndex = 0;
	m_showLapTime = 0;
	::memset(m_holderNameBuffer, 0, sizeof(m_holderNameBuffer));
	::memset(m_timeBuffer, 0, sizeof(m_timeBuffer));
	m_holderNameString.CopyFromBufSelection(m_holderNameBuffer, sizeOfArray(m_holderNameBuffer) - 1);
	m_timeString.CopyFromBufSelection(m_timeBuffer, sizeOfArray(m_timeBuffer) - 1);
	MenuGameScreen::Reset();
}

// FUNCTION: LEGORACERS 0x00487b50
void RaceModeSetupScreen::CreateWidgets()
{
	CreateImage(&m_photoImage, 0x49, 0x49);
	SingleRaceSelectBase::CreateWidgets();

	undefined4 textId;
	if (m_menuId != 6) {
		textId = 0x0f;
	}
	else {
		textId =
			0x0e + ((m_context->m_modelBuilder.GetMenuFlowFlags() & DriverModelBuilder::c_menuFlowVersus) ? 0x0b : 0);
	}

	CreateTextLabel(&m_infoLabel, 0x3a, 0x3a, textId);
	m_infoLabel.WrapText(0x14);
	CreateCarousel(&m_raceCarousel, 0x3d, 0x3b);
	CreateSelector(&m_raceSelector, &m_raceCarousel, 0x69, 0x4c);
	CreateTextButton(&m_startButton, 0x40, 0x46, 0x72);
	CreateTextButton(&m_backButton, 0x3f, 0x43, 2);

	for (LegoS32 i = 0; i < sizeOfArray(m_raceLabels); i++) {
		CreateTextLabel(&m_raceLabels[i], 0x96, 0x37, 0x70);
	}

	if (m_menuId == 0x1d) {
		CreateTextLabel(&m_timeLabel, 0x6a, 0x37, 0x70);
		CreateTextLabel(&m_holderNameLabel, 0x6c, 0x37, 0x70);
		CreateTextLabel(&m_recordTypeLabel, 0x6b, 0x37, 0x70);
		m_showLapTime = 1;
		UpdateBestTimePanel();
		CreateTextLabel(&m_unlockedLabel, 0x6d, 0x37, 0x49);
		m_unlockedLabel.ClearFlags(2);
	}
}

// FUNCTION: LEGORACERS 0x00487ca0
LegoBool32 RaceModeSetupScreen::Initialize(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	m_menuId = p_createParams->m_menuId;
	p_createParams->m_menuId = 6;
	m_savedRacerCount = p_context->m_context->m_racerCount;

	LegoBool32 result = SingleRaceSelectBase::Initialize(p_context, p_createParams);
	if (!result) {
		return FALSE;
	}

	OnWidgetValueChanged(&m_trackSelector);
	m_startButton.Select(0);
	m_recordToggleMs = 2500;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00487d10
void RaceModeSetupScreen::OnIconSelected(MenuIcon* p_icon)
{
	m_selectedIcon = p_icon;
	UpdateRacePreview();
}

// FUNCTION: LEGORACERS 0x00487d40
void RaceModeSetupScreen::OnIconUnfocused(MenuWidget* p_source)
{
	MenuWidget* source = p_source;
	if (source == &m_startButton) {
		CircuitDefinitionList::CircuitDefinition* circuitDefinition = m_circuitEntry;
		if (circuitDefinition) {
			LegoRacers::Context* context = m_context->m_context;
			::memcpy(context->m_circuitName, circuitDefinition->GetName(), sizeof(GolName));

			RaceNameEntry* raceNameEntry = m_circuitEntry->GetRaceNameEntry(m_raceCarousel.GetSelectedIndex());
			if (raceNameEntry) {
				::memcpy(context->m_raceSlots[0].m_raceName, raceNameEntry->GetName(), sizeof(GolName));
				::memcpy(context->m_raceSlots[0].m_folderName, raceNameEntry->GetFolderName(), sizeof(GolName));
				context->m_raceSlots[0].m_enabled = TRUE;
				context->m_raceSlots[0].m_mirror = raceNameEntry->GetMirror();
			}

			// Both branches assign the same id in the original; the flag test is real but inert
			if (m_context->m_modelBuilder.GetMenuFlowFlags() & DriverModelBuilder::c_menuFlowVersus) {
				m_nextMenuId = 0x13;
			}
			else {
				m_nextMenuId = 0x13;
			}
		}
	}
	else if (source == &m_backButton) {
		m_context->m_modelBuilder.SetMenuFlowFlags(
			m_context->m_modelBuilder.GetMenuFlowFlags() & ~DriverModelBuilder::c_menuFlowVersus
		);
		m_nextMenuId = 2;
	}

	if (m_nextMenuId != 0xffff) {
		m_navPending = TRUE;
	}

	m_clickedWidget = source;
}

// FUNCTION: LEGORACERS 0x00487e10
void RaceModeSetupScreen::OnWidgetValueChanged(MenuWidget* p_source)
{
	GolString string;
	LegoBool32 isComplete = FALSE;

	if (p_source == &m_trackSelector) {
		LegoU32 circuitIndex = m_trackCarousel.GetSelectedIndex();
		m_circuitEntry = m_context->m_circuitList.GetEntry(circuitIndex);

		if (m_circuitEntry) {
			LegoU8 mask = static_cast<LegoU8>(1 << m_context->m_circuitList.GetEntryIndex(m_circuitEntry));
			LegoU8 flags = m_context->m_saveSystem.GetGameState().GetUnlockedCircuits();
			if (flags & mask) {
				isComplete = TRUE;
			}
		}

		m_raceCarousel.RemoveAllItems();
		for (LegoS32 i = 0; i < sizeOfArray(m_raceLabels); i++) {
			RaceNameEntry* raceNameEntry = m_circuitEntry->GetRaceNameEntry(i);
			if (raceNameEntry) {
				raceNameEntry->CopyDisplayString(&string);
				m_raceLabels[i].SetString(&string, TRUE);
				m_raceCarousel.AddItem(&m_raceLabels[i]);
			}
		}
		m_raceCarousel.SetSelection(0);

		if (isComplete) {
			m_startButton.Enable(5);
			m_sceneOverlay.ClearFlags(2);
		}
		else {
			m_startButton.Disable(5);
			m_sceneOverlay.SetFlags(2);
		}
	}

	UpdateRacePreview();
}

// FUNCTION: LEGORACERS 0x00487f90
void RaceModeSetupScreen::Navigate()
{
	if (m_nextMenuId == 2) {
		m_context->m_context->m_racerCount = m_savedRacerCount;
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

	m_context->m_menuStack.Push(m_nextMenuId);
}

// FUNCTION: LEGORACERS 0x00488010
void RaceModeSetupScreen::UpdateRacePreview()
{
	GolName frameName;
	GolName driverName;
	GolName raceName;
	driverName[0] = '\0';

	LegoU32 selectedEntryIndex = m_raceCarousel.GetSelectedIndex();
	RaceNameEntry* raceNameEntry = m_circuitEntry->GetRaceNameEntry(selectedEntryIndex);
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

	GolNameTable* frameNames = &m_sceneWidget.m_definition;
	CutsceneDefinition::Frame* frame;
	if (!frameNames->GetNameEntries()) {
		frame = NULL;
	}
	else {
		frame = static_cast<CutsceneDefinition::Frame*>(frameNames->GetName(frameName));
	}

	LegoChar* raceNameSource = raceNameEntry->GetName();
	::memcpy(raceName, raceNameSource, sizeof(GolName));
	m_selectedRaceIndex = m_context->m_raceNames.GetEntryIndexByName(raceName);
	if (frame && frame != m_sceneWidget.m_frame) {
		m_sceneWidget.SetFrame(frame);
		m_sceneWidget.m_frame->SetFlags(CutsceneDefinition::Frame::c_flagLoop);
		m_showLapTime = TRUE;
		UpdateBestTimePanel();
	}

	LegoU32 circuitIndex = m_context->m_circuitList.GetEntryIndex(m_circuitEntry);
	LegoU32 visualStateIndex = circuitIndex * 4;
	visualStateIndex += selectedEntryIndex;
	ApplyThemeColor(visualStateIndex);
	if (driverName[0]) {
		SetPreviewDriver(driverName);
	}
}

// FUNCTION: LEGORACERS 0x00488150
LegoBool32 RaceModeSetupScreen::Update(undefined4 p_elapsed)
{
	if (p_elapsed > m_recordToggleMs) {
		m_showLapTime = (m_showLapTime == 0);
		UpdateBestTimePanel();
	}
	else {
		m_recordToggleMs -= p_elapsed;
	}

	return MenuSceneScreen::Update(p_elapsed);
}

// FUNCTION: LEGORACERS 0x004881a0
void RaceModeSetupScreen::UpdateBestTimePanel()
{
	GolString string;
	LegoU32 bestTime = 0xffffffff;

	if (m_menuId != 0x1d) {
		return;
	}

	::memset(m_holderNameBuffer, 0, sizeof(m_holderNameBuffer));
	::memset(m_timeBuffer, 0, sizeof(m_timeBuffer));

	undefined2 buffer[15];
	::memset(buffer, 0, sizeof(buffer));
	string.CopyFromBufSelection(buffer, 14);

	LegoBool32 raceTime = (m_showLapTime == FALSE);
	LegoU16 unlockedMask = m_context->m_saveSystem.GetGameState().GetUnlockedRaces();
	LegoU32 time = m_context->m_saveSystem.GetGameState().GetBestTime(m_selectedRaceIndex, raceTime, &string);
	if (time && time < 0xffffffff) {
		bestTime = time;
		m_holderNameString.GolStrcpy(&string);
	}

	if (m_showLapTime) {
		m_recordTypeLabel.SetStringByIndex(0x46, 0);
	}
	else {
		m_recordTypeLabel.SetStringByIndex(0x47, 0);
	}

	if (bestTime != 0xffffffff) {
		LegoChar time[9];
		FormatTime(time, bestTime);
		GolString::CopyStringToBuf16(time, m_timeBuffer);
		m_holderNameLabel.SetString(&m_holderNameString, 0);
	}
	else if (m_showLapTime) {
		m_holderNameLabel.SetStringByIndex(0xbe, 0);
	}
	else {
		m_holderNameLabel.SetStringByIndex(0xbf, 0);
	}

	m_timeLabel.SetString(&m_timeString, 0);
	m_recordToggleMs = 2500;

	if (static_cast<LegoU16>(unlockedMask & (1 << m_selectedRaceIndex))) {
		m_unlockedLabel.SetFlags(2);
	}
	else {
		m_unlockedLabel.ClearFlags(2);
	}
}
