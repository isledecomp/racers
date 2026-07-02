#include "menu/screens/garagescreen.h"

#include "menu/menudialog.h"
#include "menu/menugamecontext.h"
#include "menu/menuscreenid.h"

#include <string.h>

DECOMP_SIZE_ASSERT(GarageScreen, 0x6410)

// FUNCTION: LEGORACERS 0x0047e2b0
GarageScreen::GarageScreen()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0047e400
GarageScreen::~GarageScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0047e530
void GarageScreen::Reset()
{
	m_nextPage = 0;
	m_page = 0;
	RacerPickScreenBase::Reset();
}

// FUNCTION: LEGORACERS 0x0047e550
void GarageScreen::CreateMainButtons()
{
	CreateTextButton(&m_newRacerButton, 0x90, 0x42, 0x28);
	CreateTextButton(&m_editButton, 0x91, 0x42, 0x29);
	CreateTextButton(&m_loadButton, 0x92, 0x42, 0x2a);
	CreateTextButton(&m_deleteButton, 0x93, 0x42, 0x2c);
	CreateTextButton(&m_testDriveButton, 0x94, 0x42, 0x2d);
	CreateTextButton(&m_backButton, 0x3f, 0x43, 3);
	CreateTextLabel(&m_infoLabel, 0x3a, 0x3a, 3);
	m_infoLabel.WrapText(0x14);
}

// FUNCTION: LEGORACERS 0x0047e600
void GarageScreen::CreateEditButtons()
{
	CreateTextButton(&m_editDriverButton, 0x0f, 0x42, 9);
	CreateTextButton(&m_licenseButton, 0x98, 0x42, 0x0a);
	CreateTextButton(&m_editCarButton, 0x11, 0x42, 0x0b);
	HideEditButtons();
}

// FUNCTION: LEGORACERS 0x0047e650
void GarageScreen::CreateWidgets()
{
	CreateImage(&m_photoImage, 0x49, 0x49);
	RacerPickScreenBase::CreateWidgets();
	CreateMainButtons();
	CreateEditButtons();
}

// FUNCTION: LEGORACERS 0x0047e680
LegoBool32 GarageScreen::Initialize(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	if (!IsMenuMusicPlaying(p_context)) {
		StartMenuMusic(p_context, TRUE, TRUE);
	}

	if (p_context->m_menuStack.GetSize() == 1) {
		p_context->m_menuStack.ResetSize();
		p_context->m_menuStack.Push(c_menuMainMenu);
		p_context->m_menuStack.Push(c_menuGarage);
	}

	p_context->m_modelBuilder.SetMenuFlowFlags(
		p_context->m_modelBuilder.GetMenuFlowFlags() &
		~(DriverModelBuilder::c_menuFlowNewRacer | DriverModelBuilder::c_menuFlowLoadRacer)
	);
	p_context->m_context->m_flags &= ~LegoRacers::Context::c_flagReturnToGarage;
	p_context->m_saveSystem.GetActiveRecord().SetSelectedRecordCount(0);

	undefined4 params[3];
	params[0] = 1;
	params[1] = 1;
	params[2] = 0xffff2;

	if (!RacerPickScreenBase::Initialize(p_context, p_createParams, params)) {
		return FALSE;
	}

	SetupLighting();
	ShowMainButtons();
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0047e740
void GarageScreen::ShowMainButtons()
{
	m_newRacerButton.SetFlags(2);
	m_editButton.SetFlags(2);
	m_loadButton.SetFlags(2);
	m_deleteButton.SetFlags(2);
	m_testDriveButton.SetFlags(2);
	ActivateNameSelectors(0);
	m_backButton.SetTextByIndex(2);
	m_infoLabel.SetStringByIndex(3, TRUE);
	m_infoLabel.WrapText(0x14);

	if (m_recordCounts[0]) {
		m_editButton.Enable(5);
		m_deleteButton.Enable(5);
		m_testDriveButton.Enable(5);

		if (m_recordCounts[0] == 0xd1) {
			m_newRacerButton.Disable(5);
			m_loadButton.Disable(5);
			m_editButton.Select(4);
		}
		else {
			m_newRacerButton.Enable(5);
			m_loadButton.Enable(5);
			m_newRacerButton.Select(4);
		}

		if (static_cast<LegoS32>(m_recordCounts[0]) > 1) {
			EnableNameSelectors(0);
			SwapSlotModel(0);
			RebuildNameCarousel(0);
		}
		else {
			DisableNameSelectors(0);
			SwapSlotModel(0);
			RebuildNameCarousel(0);
		}
	}
	else {
		m_newRacerButton.Enable(5);
		m_editButton.Disable(5);
		m_loadButton.Disable(5);
		m_deleteButton.Disable(5);
		m_testDriveButton.Disable(5);
		m_newRacerButton.Select(5);
		DisableNameSelectors(0);
		DetachSlotWidgets(0);
		RebuildNameCarousel(0);
	}
}

// FUNCTION: LEGORACERS 0x0047e900
void GarageScreen::HideMainButtons()
{
	m_newRacerButton.ClearFlags(2);
	m_editButton.ClearFlags(2);
	m_loadButton.ClearFlags(2);
	m_deleteButton.ClearFlags(2);
	m_testDriveButton.ClearFlags(2);
	DisableNameSelectors(0);
}

// FUNCTION: LEGORACERS 0x0047e950
void GarageScreen::ShowEditButtons()
{
	m_editCarButton.SetFlags(2);
	m_editDriverButton.SetFlags(2);
	m_licenseButton.SetFlags(2);
	m_editDriverButton.Select(5);
	m_backButton.SetTextByIndex(3);
	m_infoLabel.SetStringByIndex(4, TRUE);
	m_infoLabel.WrapText(0x14);
}

// FUNCTION: LEGORACERS 0x0047e9c0
void GarageScreen::HideEditButtons()
{
	m_editCarButton.ClearFlags(2);
	m_editDriverButton.ClearFlags(2);
	m_licenseButton.ClearFlags(2);
}

// FUNCTION: LEGORACERS 0x0047e9f0
void GarageScreen::RefreshRecordAvailability(MenuGameContext* p_context)
{
	SaveRecordCursor modelState;

	modelState.SetSaveSystem(&p_context->m_saveSystem);
	modelState.Begin(0xffff2);
	m_recordCounts[0] = modelState.CountRecords(0xffff2);
	modelState.Close();
}

// FUNCTION: LEGORACERS 0x0047ea50
void GarageScreen::DeleteSelectedRecord()
{
	SaveRecordList* records = NULL;
	SaveRecordCursor* modelState = &m_recordCursors[0];
	SaveRecordList::Record* record = modelState->GetSelectedRecord();
	SaveRecordList::Record* nextRecord = modelState->SelectNext();

	switch (record->m_recordSource) {
	case 1:
		records = &m_context->m_saveSystem.GetSessionSave();
		break;
	case 2:
		records = &m_context->m_saveSystem.GetMemoryCardSaves()[record->m_saveIndex];
		break;
	}

	records->RemoveRecord(record);
	m_navPending = TRUE;
	m_nextMenuId = c_menuGarage;
	modelState->Begin(modelState->GetSourceMask());

	if (nextRecord != NULL && nextRecord != record) {
		modelState->SeekTo(nextRecord);
	}

	RefreshRecordAvailability(m_context);
	ShowMainButtons();

	if (m_recordCounts[0]) {
		m_deleteButton.Select(5);
	}
}

// FUNCTION: LEGORACERS 0x0047eb20
void GarageScreen::StartTestDrive()
{
	LegoRacers::Context* context = m_context->m_context;
	GolName name;
	::strcpy(name, "test");

	GolNameTable* raceNames = &m_context->m_raceNames;
	RaceNameEntry* raceName = static_cast<RaceNameEntry*>(raceNames->GetName(name));

	context->m_circuitName[0] = '\0';
	context->m_raceMode = LegoRacers::Context::c_raceModeSingle;
	::memcpy(context->m_raceSlots[0].m_folderName, raceName->GetFolderName(), sizeof(GolName));
	::memcpy(context->m_raceSlots[0].m_raceName, raceName->GetName(), sizeof(GolName));
	context->m_raceSlots[0].m_enabled = TRUE;
	context->m_raceSlots[0].m_mirror = raceName->GetMirror();
	context->m_racerCount = 1;
	context->m_flags |= LegoRacers::Context::c_flagReturnToGarage;

	m_context->m_saveSystem.GetActiveRecord().SetSelectedRecordCount(1);
	undefined4 flags = m_context->m_modelBuilder.GetMenuFlowFlags();
	flags &= 0xfffffffd;
	m_context->m_modelBuilder.SetMenuFlowFlags(flags);
	SaveRecordList::Record* record = m_recordCursors[0].GetSelectedRecord();
	m_context->m_saveSystem.GetActiveRecord().SetSelectedRecord(record);
	m_nextMenuId = 0x41;
}

// FUNCTION: LEGORACERS 0x0047ec00
void GarageScreen::Navigate()
{
	switch (m_nextMenuId) {
	case c_menuGarage:
		m_context->m_menuStack.Push(c_menuSaveAll);
		return;
	case c_menuMainMenu:
		m_context->m_saveSystem.GetActiveRecord().SetSelectedRecord(0, NULL);
		m_context->m_saveSystem.GetActiveRecord().SetSelectedRecord(1, NULL);
		m_context->m_menuStack.Pop();
		StopMenuMusic(m_context);
		CommitRecordSelections();
		return;
	case c_menuNewRacer:
		m_context->m_menuStack.Push(c_menuPickMem);
		m_context->m_saveSystem.GetActiveRecord().Initialize(4, 0, 0, NULL);
		m_context->m_modelBuilder.SetMenuFlowFlags(
			m_context->m_modelBuilder.GetMenuFlowFlags() | DriverModelBuilder::c_menuFlowNewRacer
		);
		CommitRecordSelections();
		return;
	case c_menuEditDriver:
	case c_menuDriverLicense:
	case c_menuEditCar: {
		{
			SaveRecordCursor* modelState = &m_recordCursors[0];
			SaveRecordList::Record* record = modelState->GetSelectedRecord();
			m_context->m_saveSystem.GetActiveRecord().SetSelectedRecord(0, record);
			m_context->m_saveSystem.GetActiveRecord().CopyFrom(modelState->GetSelectedRecord());
			m_context->m_menuStack.Push(m_nextMenuId);
		}
		CommitRecordSelections();
		return;
	}
	case 0x41:
		m_context->m_menuStack.ResetSize();
		CommitRecordSelections();
		return;
	case c_menuPickMem: {
		m_context->m_menuStack.Push(c_menuPickMem);
		SaveRecordList::Record* record = m_recordCursors[0].GetSelectedRecord();
		m_context->m_saveSystem.GetActiveRecord().SetSelectedRecord(0, record);
		m_context->m_modelBuilder.SetMenuFlowFlags(
			m_context->m_modelBuilder.GetMenuFlowFlags() | DriverModelBuilder::c_menuFlowLoadRacer
		);
		CommitRecordSelections();
		return;
	}
	}

	m_context->m_menuStack.Push(m_nextMenuId);
	CommitRecordSelections();
}

// FUNCTION: LEGORACERS 0x0047ee50
void GarageScreen::OnIconUnfocused(MenuWidget* p_source)
{
	if (p_source == &m_backButton) {
		if (!m_page) {
			m_nextMenuId = c_menuMainMenu;
		}
		else {
			m_nextPage = 0;
		}
	}
	else {
		switch (m_page) {
		case 1:
			if (p_source == &m_editCarButton) {
				m_nextMenuId = c_menuEditCar;
			}
			else if (p_source == &m_editDriverButton) {
				m_nextMenuId = c_menuEditDriver;
			}
			else if (p_source == &m_licenseButton) {
				m_nextMenuId = c_menuDriverLicense;
			}
			break;
		case 0:
			if (p_source == &m_newRacerButton) {
				m_nextMenuId = c_menuNewRacer;
			}
			else if (p_source == &m_editButton) {
				m_nextPage = 1;
			}
			else if (p_source == &m_loadButton) {
				m_nextMenuId = c_menuPickMem;
			}
			else if (p_source == &m_deleteButton) {
				CreateTextButton(&m_confirmYesButton, 0x99, 0x46, 0x73);
				CreateTextButton(&m_confirmNoButton, 0x99, 0x45, 0x74);
				ShowConfirmDialog(&m_confirmYesButton, &m_confirmNoButton, 0x76);
			}
			else if (p_source == &m_testDriveButton) {
				StartTestDrive();
			}
			else if (p_source == &m_confirmYesButton) {
				DeleteSelectedRecord();
				m_dialog->DismissTop();
			}
			else if (p_source == &m_confirmNoButton) {
				m_dialog->DismissTop();
			}
			break;
		}
	}

	if (m_nextMenuId != 0xffff) {
		m_navPending = TRUE;
		m_driverEntities[0].SetFlags(m_driverEntities[0].GetFlags() & ~0x10000);
	}

	m_clickedWidget = p_source;
}

// FUNCTION: LEGORACERS 0x0047efe0
void GarageScreen::ApplyPageChange()
{
	switch (m_page) {
	case 0:
		HideMainButtons();
		break;
	case 1:
		HideEditButtons();
		break;
	}

	m_page = m_nextPage;

	switch (m_page) {
	case 1:
		ShowEditButtons();
		break;
	case 0:
		ShowMainButtons();
		break;
	}
}

// FUNCTION: LEGORACERS 0x0047f030
LegoBool32 GarageScreen::Update(undefined4 p_elapsed)
{
	if (m_nextPage != m_page && !(m_clickedWidget->GetAnimFlags() & 1)) {
		ApplyPageChange();
	}

	SaveRecordCursor* modelState = &m_recordCursors[0];
	if (modelState->GetSelectedRecord() != NULL) {
		if (modelState->GetSelectedRecord()->m_recordSource == 1) {
			m_loadButton.SetTextByIndex(0x2b);
		}
		else {
			m_loadButton.SetTextByIndex(0x2a);
		}
	}

	return RacerModelScreenBase::Update(p_elapsed);
}
