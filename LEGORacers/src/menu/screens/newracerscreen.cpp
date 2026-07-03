#include "menu/screens/newracerscreen.h"

#include "menu/menudialog.h"
#include "menu/menugamecontext.h"
#include "menu/menuscreencreateparams.h"
#include "menu/menuscreenid.h"
#include "save/memorycardsavegame.h"
#include "save/saverecordlist.h"

DECOMP_SIZE_ASSERT(NewRacerScreen, 0x770)

// FUNCTION: LEGORACERS 0x00481fe0
NewRacerScreen::NewRacerScreen()
{
	m_saveSlot = 0;
}

// FUNCTION: LEGORACERS 0x00482090
NewRacerScreen::~NewRacerScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00482120
LegoBool32 NewRacerScreen::Initialize(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	if (m_initialized) {
		Destroy();
	}

	m_saveSlot = p_context->m_modelBuilder.GetSaveSlot();
	p_createParams->m_cursor->SetCursorEnabled(FALSE);
	return MenuGameScreen::Initialize(p_context, p_createParams) != FALSE;
}

// FUNCTION: LEGORACERS 0x00482160
void NewRacerScreen::CreateWidgets()
{
	CreateImage(&m_photoImage, 0x49, 0x49);

	SaveRecordList* records;

	if (m_saveSlot >= 2) {
		records = &m_context->m_saveSystem.GetSessionSave();
		if (!records->GetAvailableRecordCount()) {
			CreateImage(&m_statusPanelImage, 0x53, 0x53);
			CreateImage(&m_statusIconImage, 0x54, 0x54);
			CreateTextButton(&m_okButton, 0x99, 0x46, 0x72);
			ShowPopupDialog(&m_okButton, 0xbb);
			m_cursor->SetCursorEnabled(TRUE);
			return;
		}
	}
	else {
		MemoryCardSaveGame* memoryCardSave = &m_context->m_saveSystem.GetMemoryCardSaves()[m_saveSlot];
		records = memoryCardSave;
		if (!memoryCardSave->IsUsable() || !memoryCardSave->GetAvailableRecordCount()) {
			CreateImage(&m_statusPanelImage, 0x53, 0x53);
			CreateImage(&m_statusIconImage, 0x54, 0x54);
			CreateTextButton(&m_okButton, 0x99, 0x46, 0x72);
			ShowPopupDialog(&m_okButton, 0xbc);
			m_cursor->SetCursorEnabled(TRUE);
			return;
		}
	}

	if (m_context->m_modelBuilder.GetMenuFlowFlags() & DriverModelBuilder::c_menuFlowLoadRacer) {
		SaveRecordList::Record* record =
			records->AllocateRecordCopy(m_context->m_saveSystem.GetActiveRecord().GetSelectedRecord());
		m_nextMenuId = c_menuGarage;

		SaveRecordList::Record* oldRecord = m_context->m_saveSystem.GetActiveRecord().GetSelectedRecord();
		if (oldRecord->m_recordSource == TRUE && record->m_recordSource != TRUE) {
			m_context->m_saveSystem.GetSessionSave().RemoveRecord(oldRecord);
		}

		m_context->m_saveSystem.GetActiveRecord().SetSelectedRecord(record);
		m_navPending = TRUE;
	}
	else {
		SaveRecordList::Record* record = records->AllocateRecord();
		m_context->m_saveSystem.GetActiveRecord().SetSelectedRecord(record);
		m_nextMenuId = c_menuEditDriver;
		m_navPending = TRUE;
	}
}

// FUNCTION: LEGORACERS 0x00482310
void NewRacerScreen::Navigate()
{
	m_context->m_menuStack.Pop();

	if (m_nextMenuId == c_menuGarage) {
		m_context->m_menuStack.Pop();
		m_context->m_menuStack.Push(c_menuGarage);
	}
}

// FUNCTION: LEGORACERS 0x00482350
void NewRacerScreen::OnIconUnfocused(MenuWidget* p_source)
{
	if (p_source == &m_okButton) {
		m_dialog->DismissTop();
		m_navPending = TRUE;
		m_nextMenuId = c_menuGarage;
	}
}

// FUNCTION: LEGORACERS 0x004849c0 FOLDED
LegoBool32 NewRacerScreen::Destroy()
{
	if (!m_initialized) {
		return TRUE;
	}

	m_cursor->SetCursorEnabled(TRUE);
	return MenuGameScreen::Destroy();
}
