#include "menu/screens/pickracerscreen.h"

#include "menu/menugamecontext.h"
#include "menu/menuscreenid.h"

DECOMP_SIZE_ASSERT(PickRacerScreen, 0x4c8c)

// FUNCTION: LEGORACERS 0x00484c10
PickRacerScreen::PickRacerScreen()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00484ce0
PickRacerScreen::~PickRacerScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00484d90
void PickRacerScreen::CreateWidgets()
{
	undefined2 textId = 0x14;

	CreateImage(&m_photoImage, 0x49, 0x49);
	RacerPickScreenBase::CreateWidgets();

	if (m_context->m_modelBuilder.GetMenuFlowFlags() & DriverModelBuilder::c_menuFlowVersus) {
		textId = m_context->m_saveSystem.GetActiveRecord().GetSelectedRecordCountAsU16();
		textId += 0x15;
	}

	CreateTextLabel(&m_infoLabel, 0x3a, 0x3a, textId);
	m_infoLabel.WrapText(0x14);
	CreateTextButton(&m_controlsButton, 9, 0x42, 0xb9);
	CreateTextButton(&m_startButton, 0x41, 0x46, 0x72);
	CreateTextButton(&m_nextPlayerButton, 0x40, 0x46, 0x72);
	CreateTextButton(&m_backButton, 0x3f, 0x45, 0x1f);
}

// FUNCTION: LEGORACERS 0x00484e40
LegoBool32 PickRacerScreen::Initialize(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	undefined4 params[3];
	params[0] = 1;
	params[1] = 1;
	params[2] = 0xffff3;

	if (!p_context->m_modelBuilder.HasMenuResources()) {
		LoadPartResources(p_context, FALSE);
	}

	if (!RacerPickScreenBase::Initialize(p_context, p_createParams, params)) {
		return FALSE;
	}

	SetupLighting();

	if (p_context->m_modelBuilder.GetMenuFlowFlags() & DriverModelBuilder::c_menuFlowVersus) {
		m_nameSelectors[0].SetAcceptUnfocusedInput(TRUE);

		if (p_context->m_saveSystem.GetActiveRecord().GetSelectedRecordCount() == 0) {
			m_startButton.ClearFlags(2);
			m_nextPlayerButton.Select(0);
		}
		else {
			m_nextPlayerButton.ClearFlags(2);
			m_startButton.Select(0);
		}
	}
	else {
		m_nextPlayerButton.ClearFlags(2);
		m_startButton.Select(0);
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00484f40
void PickRacerScreen::OnIconUnfocused(MenuWidget* p_source)
{
	if (p_source == &m_controlsButton) {
		m_nextMenuId = static_cast<LegoU16>(
			m_context->m_saveSystem.GetActiveRecord().GetSelectedRecordCountAsU16() + c_menuControl1
		);
		m_driverEntities[0].SetFlags(m_driverEntities[0].GetFlags() & ~0x10000);
	}
	else if (p_source == &m_startButton) {
		if (m_context->m_modelBuilder.GetMenuFlowFlags() & DriverModelBuilder::c_menuFlowVersus) {
			m_context->m_context->m_racerCount = 0;
		}

		PlayRandomNamedAnimation(0);
		MenuGameContext* context = m_context;
		SaveRecordList::Record* record = m_recordCursors[0].GetSelectedRecord();
		context->m_saveSystem.GetActiveRecord().SetSelectedRecord(
			context->m_saveSystem.GetActiveRecord().GetSelectedRecordCount(),
			record
		);
		m_context->m_saveSystem.GetActiveRecord().SetSelectedRecordCount(
			m_context->m_saveSystem.GetActiveRecord().GetSelectedRecordCount() + 1
		);
		m_nextMenuId = 0x41;
	}
	else if (p_source == &m_nextPlayerButton) {
		PlayRandomNamedAnimation(0);
		MenuGameContext* context = m_context;
		SaveRecordList::Record* record = m_recordCursors[0].GetSelectedRecord();
		context->m_saveSystem.GetActiveRecord().SetSelectedRecord(
			context->m_saveSystem.GetActiveRecord().GetSelectedRecordCount(),
			record
		);
		m_context->m_saveSystem.GetActiveRecord().SetSelectedRecordCount(
			m_context->m_saveSystem.GetActiveRecord().GetSelectedRecordCount() + 1
		);
		m_nextMenuId = c_menuPickRacerP2;
	}
	else if (p_source == &m_backButton) {
		m_nextMenuId = 0x3f;

		if (m_context->m_saveSystem.GetActiveRecord().GetSelectedRecordCount() != 0) {
			m_context->m_saveSystem.GetActiveRecord().SetSelectedRecordCount(
				m_context->m_saveSystem.GetActiveRecord().GetSelectedRecordCount() - 1
			);
		}

		m_driverEntities[0].SetFlags(m_driverEntities[0].GetFlags() & ~0x10000);
	}

	if (m_nextMenuId != 0xffff) {
		m_navPending = TRUE;
	}

	m_clickedWidget = p_source;
}

// FUNCTION: LEGORACERS 0x00485090
void PickRacerScreen::OnWidgetValueChanged(MenuWidget* p_source)
{
	RacerPickScreenBase::OnWidgetValueChanged(p_source);
}

// FUNCTION: LEGORACERS 0x004850a0
void PickRacerScreen::Navigate()
{
	switch (m_nextMenuId) {
	case c_menuControl1:
	case c_menuControl2:
	case c_menuPickRacerP2:
		m_context->m_menuStack.Push(m_nextMenuId);
		CommitRecordSelections();
		return;
	case 0x3f:
		m_context->m_menuStack.Pop();
		CommitRecordSelections();
		return;
	case 0x41:
		if (m_context->m_context->m_raceMode == LegoRacers::Context::c_raceModeCircuit &&
			m_context->m_saveSystem.GetActiveRecord().GetSelectedRecordCount() == 1) {
			CircuitDefinitionList::CircuitDefinition* circuitDefinition =
				static_cast<CircuitDefinitionList::CircuitDefinition*>(
					m_context->m_circuitList.GetName(m_context->m_context->m_circuitName)
				);
			LegoU32 raceIndex = m_context->m_circuitList.GetEntryIndex(circuitDefinition);
			m_context->m_menuStack.Push(static_cast<LegoU16>(raceIndex + c_menuCircuit1));
			m_context->m_context->m_racerCount = 5;
		}
		else {
			m_context->m_menuStack.ResetSize();
		}

		if (m_context->m_modelBuilder.GetMenuFlowFlags() & DriverModelBuilder::c_menuFlowVersus) {
			m_context->m_context->m_racerCount = 0;
		}
		else {
			m_context->m_context->m_racerCount += m_context->m_saveSystem.GetActiveRecord().GetSelectedRecordCount();
		}

		m_navPending = TRUE;
		m_context->m_modelBuilder.SetMenuFlowFlags(
			m_context->m_modelBuilder.GetMenuFlowFlags() & ~DriverModelBuilder::c_menuFlowVersus
		);
		break;
	}

	CommitRecordSelections();
}
